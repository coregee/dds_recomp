"""Atlus FlowScript (FLW0) for Nocturne: read, disassemble, assemble, decompile.

    python tools/flowscript.py roundtrip            check every script reassembles byte-exact
    python tools/flowscript.py export               write source/scripts/ (.flowasm, .msg, .flow)
    python tools/flowscript.py disasm <script>      print one script's assembly
    python tools/flowscript.py assemble <in.flowasm> <out.bf>

Scripts are the .bf files under game/dds3/ and two scripts embedded in the
executable: the battle AI scripts (0x4F0800, run by nbInitAiScript) and a
small one at 0x3267A8.

The format (FlowScript version 1, as the interpreter at scrCodeFunc_* reads
it): a 0x20-byte header ("FLW0" at 8, section count at 0x10), then section
descriptors {type, element size, count, offset}: 0 procedures and 1 jump
labels ({char name[24]; u32 instruction; u32 reserved}), 2 code (4-byte
words {u16 opcode, s16 operand}; PUSHI/PUSHF take the next word as their
value), 3 the message script (MSG1), 4 strings.

Evaluation is a stack machine: binary operators take the left operand from
the top of the stack (the compiler pushes the right operand first), and a
command's arguments are pushed last first, so argument 0 is on top. COMM
calls entry n of the command table (reference/names/script-commands.tsv);
PUSHREG pushes its result. IF pops a value and jumps to its label when it
is zero.

The .flowasm form is exact: `flowscript.py assemble` rebuilds the original
bytes, taking the message script from its text form (.msg, tools/messages.py).
The .flow form is a readable decompilation generated from it.
"""
import struct
import sys
from pathlib import Path

import messages

ROOT = Path(__file__).resolve().parents[1]
ELF = ROOT / "game" / "SLUS_209.11"
DATA_SEGMENT_DELTA = 0xFF000
EMBEDDED = {"exe/ai": 0x4F0800, "exe/script_3267a8": 0x3267A8}
# Scripts whose COMM numbers don't follow the game's command table (calls
# don't fit its argument counts; a message call lands on BLUR_ALLOFF). They
# keep numeric commands and get no decompilation.
FOREIGN_COMMANDS = ("battle/script/nego", "nego/script/")

OPCODES = ["PUSHI", "PUSHF", "PUSHIX", "PUSHIF", "PUSHREG", "POPIX", "POPFX", "PROC", "COMM", "END",
           "JUMP", "CALL", "RUN", "GOTO", "ADD", "SUB", "MUL", "DIV", "MINUS", "NOT", "OR", "AND",
           "EQ", "NEQ", "S", "L", "SE", "LE", "IF", "PUSHIS", "PUSHLIX", "PUSHLFX", "POPLIX", "POPLFX",
           "PUSHSTR"]
OP = {name: i for i, name in enumerate(OPCODES)}
LABEL_OPERAND = {OP["GOTO"], OP["IF"]}
PROCEDURE_OPERAND = {OP["JUMP"], OP["CALL"]}
SECTION_NAMES = {0: "procedures", 1: "labels", 2: "code", 3: "messages", 4: "strings"}


# ---- commands --------------------------------------------------------------------

def load_commands():
    by_index, by_name, args = {}, {}, {}
    path = ROOT / "reference" / "names" / "script-commands.tsv"
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line or line.startswith(("#", "index")):
            continue
        index, count, _handler, name, _method, _source = line.split("\t")
        by_index[int(index)] = name
        by_name[name] = int(index)
        args[int(index)] = int(count)
    return by_index, by_name, args


COMMAND_NAMES, COMMAND_INDEX, COMMAND_ARGS = load_commands()


def command_name(index):
    return COMMAND_NAMES.get(index, f"COMM_{index:03X}")


def command_index(name):
    if name in COMMAND_INDEX:
        return COMMAND_INDEX[name]
    if name.startswith("COMM_"):
        return int(name[5:], 16)
    raise ValueError(f"unknown command {name}")


# ---- the container ---------------------------------------------------------------

class Label:
    def __init__(self, name, address, reserved=0, raw_name=None):
        self.name, self.address, self.reserved = name, address, reserved
        self.raw_name = raw_name   # the 24 name bytes when they hold more than the name

    def pack(self):
        raw = self.raw_name or self.name.encode("ascii").ljust(24, b"\0")
        return raw + struct.pack("<II", self.address, self.reserved)


class Script:
    """A parsed FlowScript. Sections keep their file order."""

    def __init__(self):
        self.header = b""          # the 0x20 header bytes as found
        self.sections = []         # [(type, element size, count)] in table order
        self.procedures = []
        self.labels = []
        self.code = []             # 32-bit words
        self.messages = b""
        self.strings = b""
        self.string_count = None   # the strings section's count when it isn't the data's size

    @staticmethod
    def parse(data):
        s = Script()
        if data[8:12] != b"FLW0":
            raise ValueError("not a FlowScript")
        s.header = data[:0x20]
        count = struct.unpack_from("<I", data, 0x10)[0]
        for i in range(count):
            kind, size, n, offset = struct.unpack_from("<IIII", data, 0x20 + 16 * i)
            s.sections.append((kind, size, n))
            body = data[offset:offset + size * n]
            if kind in (0, 1):
                labels = []
                for k in range(n):
                    raw = body[32 * k:32 * k + 24]
                    name = raw.split(b"\0")[0].decode("ascii")
                    address, reserved = struct.unpack_from("<II", body, 32 * k + 24)
                    clean = name.encode("ascii").ljust(24, b"\0") == raw
                    labels.append(Label(name, address, reserved, None if clean else raw))
                if kind == 0:
                    s.procedures = labels
                else:
                    s.labels = labels
            elif kind == 2:
                s.code = list(struct.unpack_from(f"<{n}I", body))
            elif kind == 3:
                s.messages = body
            elif kind == 4:
                # The count is often wrong (sometimes 0); the strings run to
                # the end of the file when they are the last section.
                last = offset >= max(o for _, _, _, o in (struct.unpack_from("<IIII", data, 0x20 + 16 * j) for j in range(count)))
                s.strings = data[offset:] if last else body
                if n != len(s.strings):
                    s.string_count = n
            else:
                raise ValueError(f"unknown section type {kind}")
        return s

    def size(self):
        return 0x20 + 16 * len(self.sections) + sum(size * n for _, size, n in self.sections)

    def serialize(self):
        bodies = {0: b"".join(p.pack() for p in self.procedures),
                  1: b"".join(l.pack() for l in self.labels),
                  2: struct.pack(f"<{len(self.code)}I", *self.code),
                  3: self.messages, 4: self.strings}
        counts = {0: len(self.procedures), 1: len(self.labels), 2: len(self.code),
                  3: len(self.messages),
                  4: len(self.strings) if self.string_count is None else self.string_count}
        sizes = {0: 32, 1: 32, 2: 4, 3: 1, 4: 1}
        out = bytearray(self.header)
        offset = 0x20 + 16 * len(self.sections)
        table = bytearray()
        for kind, _, _ in self.sections:
            table += struct.pack("<IIII", kind, sizes[kind], counts[kind], offset)
            offset += len(bodies[kind])
        out[0x10:0x14] = struct.pack("<I", len(self.sections))
        out += table
        for kind, _, _ in self.sections:
            out += bodies[kind]
        return bytes(out)


def embedded_script(address):
    elf = ELF.read_bytes()
    start = address - DATA_SEGMENT_DELTA
    count = struct.unpack_from("<I", elf, start + 0x10)[0]
    end = max(offset + size * n for _, size, n, offset in
              (struct.unpack_from("<IIII", elf, start + 0x20 + 16 * i) for i in range(count)))
    return elf[start:start + end]


def all_scripts():
    """(name, bytes) for every script: the embedded ones, then the .bf files."""
    for name, address in EMBEDDED.items():
        yield name, embedded_script(address)
    base = ROOT / "game" / "dds3"
    for path in sorted(base.rglob("*.bf")):
        yield path.relative_to(base).with_suffix("").as_posix(), path.read_bytes()


# ---- disassembly ---------------------------------------------------------------------

def float_text(bits):
    """The shortest decimal that reads back as exactly these float32 bits."""
    value = struct.unpack("<f", struct.pack("<I", bits))[0]
    for digits in range(1, 18):
        text = f"{value:.{digits}g}"
        if struct.unpack("<I", struct.pack("<f", float(text)))[0] == bits:
            return text if any(c in text for c in ".en") else text + ".0"
    return f"bits:0x{bits:08X}"


def instructions(script):
    """(index, opcode, operand, value) with value the following word for PUSHI/PUSHF."""
    i = 0
    code = script.code
    while i < len(code):
        word = code[i]
        opcode, operand = word & 0xFFFF, struct.unpack("<h", struct.pack("<H", word >> 16))[0]
        if opcode in (OP["PUSHI"], OP["PUSHF"]) and i + 1 < len(code):
            yield i, opcode, operand, code[i + 1]
            i += 2
        else:
            yield i, opcode, operand, None
            i += 1


def foreign(name):
    return name.startswith(FOREIGN_COMMANDS)


def disassemble(script, messages_file=None, numeric_commands=False):
    out = ["; FlowScript assembly. tools/flowscript.py assemble rebuilds the original bytes.\n"]
    out.append(f".header {script.header.hex()}\n")
    out.append(".sections " + " ".join(SECTION_NAMES[k] for k, _, _ in script.sections) + "\n")
    if script.messages:
        out.append(f".messages {messages_file}\n" if messages_file else f".messages hex:{script.messages.hex()}\n")
    if script.strings:
        out.append(f".strings {script.strings.hex()}\n")
    if script.string_count is not None:
        out.append(f".string-count {script.string_count}\n")
    for p in script.procedures:
        if p.reserved or p.raw_name:
            out.append(f".procedure-entry {p.name} reserved={p.reserved} raw={(p.raw_name or b'').hex()}\n")
    out.append(".labels " + " ".join(l.name for l in script.labels) + "\n")
    for l in script.labels:
        if l.reserved or l.raw_name:
            out.append(f".label-entry {l.name} reserved={l.reserved} raw={(l.raw_name or b'').hex()}\n")

    procedures_at = {}
    for index, p in enumerate(script.procedures):
        procedures_at.setdefault(p.address, []).append(index)
    labels_at = {}
    for l in script.labels:
        labels_at.setdefault(l.address, []).append(l.name)
    order = ".procedures " + " ".join(p.name for p in script.procedures)
    by_address = [p.name for p in sorted(script.procedures, key=lambda p: p.address)]
    if by_address != [p.name for p in script.procedures]:
        out.append(order + "\n")

    for index, opcode, operand, value in instructions(script):
        for p in procedures_at.get(index, []):
            out.append(f"\n.procedure {script.procedures[p].name}\n")
        for name in labels_at.get(index, []):
            out.append(f"{name}:\n")
        if opcode >= len(OPCODES):
            out.append(f"    .word 0x{script.code[index]:08X}\n")
            continue
        name = OPCODES[opcode]
        if opcode == OP["PUSHI"]:
            text = f"{name} {struct.unpack('<i', struct.pack('<I', value))[0]}" if value is not None else name
            if operand:
                text += f" ; operand {operand}"
        elif opcode == OP["PUSHF"]:
            text = f"{name} {float_text(value)}"
            if operand:
                text += f" ; operand {operand}"
        elif opcode == OP["COMM"]:
            text = f"{name} #{operand & 0xFFFF}" if numeric_commands else f"{name} {command_name(operand & 0xFFFF)}"
        elif opcode in LABEL_OPERAND:
            text = f"{name} {script.labels[operand].name}" if 0 <= operand < len(script.labels) else f"{name} #{operand}"
        elif opcode in PROCEDURE_OPERAND:
            text = f"{name} {script.procedures[operand].name}" if 0 <= operand < len(script.procedures) else f"{name} #{operand}"
        elif opcode == OP["PROC"]:
            here = procedures_at.get(index, [])
            text = name if here and operand == here[-1] else f"{name} #{operand}"
        elif opcode in (OP["PUSHIS"], OP["PUSHIX"], OP["PUSHIF"], OP["POPIX"], OP["POPFX"], OP["PUSHLIX"],
                        OP["PUSHLFX"], OP["POPLIX"], OP["POPLFX"], OP["PUSHSTR"]):
            text = f"{name} {operand}"
        else:
            text = name if operand == 0 else f"{name} #{operand}"
        out.append(f"    {text}\n")
    # labels at the very end of the code
    for name in labels_at.get(len(script.code), []):
        out.append(f"{name}:\n")
    for p in procedures_at.get(len(script.code), []):
        out.append(f"\n.procedure {script.procedures[p].name}\n")
    return "".join(out)


# ---- assembly ---------------------------------------------------------------------------

def assemble(text, base_dir=Path(".")):
    s = Script()
    label_order, procedure_order = [], None
    label_entries, procedure_entries = {}, {}
    procedure_addresses, label_addresses = [], {}
    code = []
    pending = []    # (word index, kind, name) operands resolved after all labels are known

    def operand_word(opcode, operand):
        return (opcode & 0xFFFF) | ((operand & 0xFFFF) << 16)

    for raw in text.splitlines():
        line = raw.split(";", 1)[0].strip() if not raw.lstrip().startswith(".") else raw.strip()
        if not line or line.startswith(";"):
            continue
        if line.startswith("."):
            directive, _, rest = line.partition(" ")
            rest = rest.strip()
            if directive == ".header":
                s.header = bytes.fromhex(rest)
            elif directive == ".sections":
                names = {v: k for k, v in SECTION_NAMES.items()}
                s.sections = [(names[n], 0, 0) for n in rest.split()]
            elif directive == ".messages":
                if rest.startswith("hex:"):
                    s.messages = bytes.fromhex(rest[4:])
                elif rest.endswith(".msg"):
                    text = (base_dir / rest).read_text(encoding="utf-8")
                    s.messages = messages.MessageTable.from_text(text).serialize()
                else:
                    s.messages = (base_dir / rest).read_bytes()
            elif directive == ".strings":
                s.strings = bytes.fromhex(rest)
            elif directive == ".string-count":
                s.string_count = int(rest)
            elif directive == ".labels":
                label_order = rest.split()
            elif directive == ".procedures":
                procedure_order = rest.split()
            elif directive in (".label-entry", ".procedure-entry"):
                name, reserved, raw_name = rest.split()
                entry = (int(reserved.split("=")[1]), bytes.fromhex(raw_name.split("=")[1]) or None)
                (label_entries if directive == ".label-entry" else procedure_entries)[name] = entry
            elif directive == ".procedure":
                procedure_addresses.append((rest, len(code)))
            elif directive == ".word":
                code.append(int(rest, 0))
            else:
                raise ValueError(f"unknown directive {directive}")
            continue
        if line.endswith(":"):
            label_addresses[line[:-1]] = len(code)
            continue
        parts = line.split(None, 1)
        name, arg = parts[0], parts[1].strip() if len(parts) > 1 else None
        opcode = OP[name]
        if opcode in (OP["PUSHI"], OP["PUSHF"]):
            code.append(operand_word(opcode, 0))
            if opcode == OP["PUSHI"]:
                code.append(int(arg) & 0xFFFFFFFF)
            elif arg.startswith("bits:"):
                code.append(int(arg[5:], 16))
            else:
                code.append(struct.unpack("<I", struct.pack("<f", float(arg)))[0])
        elif opcode == OP["COMM"]:
            code.append(operand_word(opcode, int(arg[1:]) if arg.startswith("#") else command_index(arg)))
        elif opcode in LABEL_OPERAND or opcode in PROCEDURE_OPERAND:
            if arg.startswith("#"):
                code.append(operand_word(opcode, int(arg[1:])))
            else:
                pending.append((len(code), "label" if opcode in LABEL_OPERAND else "procedure", arg))
                code.append(opcode)
        elif opcode == OP["PROC"]:
            if arg is None:
                pending.append((len(code), "proc", None))
                code.append(opcode)
            else:
                code.append(operand_word(opcode, int(arg[1:])))
        else:
            value = 0 if arg is None else int(arg.lstrip("#"))
            code.append(operand_word(opcode, value))

    names = procedure_order or [n for n, _ in procedure_addresses]
    address_of = {}
    for n, a in procedure_addresses:
        address_of[n] = a
    s.procedures = []
    for n in names:
        reserved, raw_name = procedure_entries.get(n, (0, None))
        s.procedures.append(Label(n, address_of[n], reserved, raw_name))
    procedure_index = {p.name: i for i, p in enumerate(s.procedures)}
    s.labels = []
    for n in label_order:
        reserved, raw_name = label_entries.get(n, (0, None))
        s.labels.append(Label(n, label_addresses[n], reserved, raw_name))
    label_index = {l.name: i for i, l in enumerate(s.labels)}
    proc_at = {}
    for n, a in procedure_addresses:
        proc_at[a] = procedure_index[n]
    for at, kind, name in pending:
        if kind == "label":
            value = label_index[name]
        elif kind == "procedure":
            value = procedure_index[name]
        else:
            value = proc_at[at]
        code[at] = (code[at] & 0xFFFF) | ((value & 0xFFFF) << 16)
    s.code = code
    return s


# ---- decompilation ------------------------------------------------------------------------
#
# A readable view: the stack code becomes expressions and statements, and
# the compiler's label patterns become if / else / while:
#
#   if:     <cond> IF Lelse  <then> [GOTO Lend]  Lelse: [<else> Lend:]
#   while:  Ltop: <cond> IF Lend  <body> GOTO Ltop  Lend:
#
# Anything else stays a goto. The view is generated; the .flowasm is exact.

BINARY = {"ADD": "+", "SUB": "-", "MUL": "*", "DIV": "/", "OR": "||", "AND": "&&", "EQ": "==",
          "NEQ": "!=", "S": "<", "L": ">", "SE": "<=", "LE": ">="}
PRECEDENCE = {"||": 1, "&&": 2, "==": 3, "!=": 3, "<": 4, ">": 4, "<=": 4, ">=": 4, "+": 5, "-": 5,
              "*": 6, "/": 6}


class Expr:
    def __init__(self, text, precedence=9, literal=False):
        self.text, self.precedence, self.literal = text, precedence, literal

    def wrapped(self, precedence):
        return f"({self.text})" if self.precedence < precedence else self.text


class Decompiler:
    def __init__(self, script, message_notes=None):
        self.script = script
        self.message_notes = message_notes or {}

    def string_at(self, offset):
        raw = self.script.strings[offset:].split(b"\0", 1)[0]
        return '"' + raw.decode("latin-1").replace("\\", "\\\\").replace('"', '\\"') + '"'

    def statements(self, start, end):
        """Linear statements for code[start:end]; None if the stack doesn't add up."""
        s = self.script
        labels_at = {}
        for l in s.labels:
            labels_at.setdefault(l.address, []).append(l.name)
        out = []
        stack = []
        pending_call = None
        items = [i for i in instructions(s) if start <= i[0] < end]
        for n, (index, opcode, operand, value) in enumerate(items):
            if opcode >= len(OPCODES):
                return None
            op = OPCODES[opcode]
            if pending_call is not None and (op != "PUSHREG" or index in labels_at):
                out.append(("expr", pending_call))
                pending_call = None
            for name in labels_at.get(index, []):
                if stack:
                    return None
                out.append(("label", name))
            if op in ("PUSHI", "PUSHIS"):
                number = struct.unpack("<i", struct.pack("<I", value))[0] if op == "PUSHI" else operand
                stack.append(Expr(str(number), literal=True))
            elif op == "PUSHF":
                stack.append(Expr(float_text(value) + "f", literal=True))
            elif op in ("PUSHIX", "PUSHIF"):
                stack.append(Expr(f"{'var' if op == 'PUSHIX' else 'fvar'}{operand}"))
            elif op in ("PUSHLIX", "PUSHLFX"):
                stack.append(Expr(f"{'local' if op == 'PUSHLIX' else 'flocal'}{operand}"))
            elif op == "PUSHSTR":
                stack.append(Expr(self.string_at(operand)))
            elif op == "PUSHREG":
                if pending_call is None:
                    return None
                stack.append(pending_call)
                pending_call = None
            elif op in ("POPIX", "POPFX", "POPLIX", "POPLFX"):
                if not stack:
                    return None
                prefix = {"POPIX": "var", "POPFX": "fvar", "POPLIX": "local", "POPLFX": "flocal"}[op]
                out.append(("assign", f"{prefix}{operand}", stack.pop()))
            elif op == "COMM":
                index_ = operand & 0xFFFF
                count = COMMAND_ARGS.get(index_, 0)
                if len(stack) < count:
                    return None
                args = [stack.pop() for _ in range(count)]
                text = f"{command_name(index_)}({', '.join(a.text for a in args)})"
                note = self.message_note(index_, args)
                pending_call = Expr(text + note if note else text)
            elif op in BINARY:
                if len(stack) < 2:
                    return None
                left, right = stack.pop(), stack.pop()
                symbol = BINARY[op]
                p = PRECEDENCE[symbol]
                stack.append(Expr(f"{left.wrapped(p)} {symbol} {right.wrapped(p + 1)}", p))
            elif op == "MINUS":
                if not stack:
                    return None
                operand_ = stack.pop()
                # "- 5" is MINUS applied to 5; "-5" is the literal -5.
                stack.append(Expr(f"- {operand_.text}" if operand_.literal else f"-{operand_.wrapped(9)}", 8))
            elif op == "NOT":
                if not stack:
                    return None
                stack.append(Expr(f"!{stack.pop().wrapped(9)}", 8))
            elif op == "IF":
                if not stack:
                    return None
                out.append(("if", stack.pop(), s.labels[operand].name))
            elif op == "GOTO":
                out.append(("goto", s.labels[operand].name))
            elif op == "END":
                out.append(("return",))
            elif op == "JUMP":
                out.append(("jump", s.procedures[operand].name))
            elif op == "CALL":
                out.append(("call", s.procedures[operand].name))
            elif op == "RUN":
                out.append(("run",))
            elif op == "PROC":
                pass
            else:
                return None
            if stack and op in ("IF", "GOTO", "END", "JUMP", "CALL", "RUN") :
                return None
        if pending_call is not None:
            out.append(("expr", pending_call))
        for name in labels_at.get(end, []):
            out.append(("label", name))
        return None if stack else out

    def message_note(self, command, args):
        if command_name(command) in ("itfMesMngMessage", "itfMesMngSelect") and args and args[0].text.isdigit():
            note = self.message_notes.get(int(args[0].text))
            return f" /* {note} */" if note else ""
        return ""

    # -- structuring --

    def structure(self, stmts):
        """Turn label / if / goto patterns into blocks (recursively)."""
        def reaches(name, position):
            """Whether control at `position` falls through labels only to `name`."""
            k = position
            while k < len(stmts) and stmts[k][0] == "label":
                if stmts[k][1] == name:
                    return True
                k += 1
            return False

        def find(name, begin, end):
            """The label's index in [begin, end), `end` if it lies just past the
            block (through labels only), else None."""
            for k in range(begin, end):
                if stmts[k] == ("label", name):
                    return k
            return end if reaches(name, end) else None

        def build(begin, end):
            body = []
            k = begin
            while k < end:
                st = stmts[k]
                if st[0] == "label":
                    # while loop: Ltop: if (c) goto Lend ... goto Ltop  Lend:
                    if k + 1 < end and stmts[k + 1][0] == "if":
                        lend = find(stmts[k + 1][2], k + 2, end)
                        if (lend is not None and lend - 1 > k + 1 and stmts[lend - 1] == ("goto", st[1])
                                and not referenced(st[1], k + 2, lend - 1)):
                            body.append(st)
                            body.append(("while", stmts[k + 1][1], build(k + 2, lend - 1)))
                            k = lend
                            continue
                    body.append(st)
                    k += 1
                    continue
                if st[0] == "if":
                    lelse = find(st[2], k + 1, end)
                    if lelse is not None:
                        last = stmts[lelse - 1] if lelse - 1 > k else None
                        if last and last[0] == "goto" and lelse < end and not reaches(last[1], lelse):
                            lend = find(last[1], lelse + 1, end)
                            if lend is not None:
                                body.append(("ifelse", st[1], build(k + 1, lelse - 1), build(lelse + 1, lend), last[1]))
                                body.append(stmts[lelse])
                                k = lend
                                continue
                        then_end = lelse - 1 if last and last[0] == "goto" and reaches(last[1], lelse) else lelse
                        body.append(("ifthen", st[1], build(k + 1, then_end), st[2]))
                        k = lelse
                        continue
                body.append(st)
                k += 1
            # A jump to just past the block is a fall-through.
            while body and body[-1][0] == "goto" and reaches(body[-1][1], end):
                body.pop()
            return body

        def referenced(name, begin, end):
            return any(s[0] in ("goto", "if") and s[-1] == name for s in stmts[begin:end])

        tree = build(0, len(stmts))
        used = set()

        def collect(nodes):
            for node in nodes:
                if node[0] in ("goto",):
                    used.add(node[1])
                elif node[0] == "if":
                    used.add(node[2])
                elif node[0] in ("ifthen", "while"):
                    collect(node[2])
                elif node[0] == "ifelse":
                    collect(node[2])
                    collect(node[3])
        collect(tree)

        def prune(nodes):
            result = []
            for node in nodes:
                if node[0] == "label" and node[1] not in used:
                    continue
                if node[0] in ("ifthen", "while"):
                    node = (node[0], node[1], prune(node[2])) + node[3:]
                elif node[0] == "ifelse":
                    node = (node[0], node[1], prune(node[2]), prune(node[3]), node[4])
                result.append(node)
            return result
        return prune(tree)

    def render(self, nodes, depth):
        pad = "    " * depth
        out = []
        for node in nodes:
            kind = node[0]
            if kind == "label":
                out.append(f"{'    ' * max(depth - 1, 0)}{node[1]}:")
            elif kind == "expr":
                out.append(f"{pad}{node[1].text};")
            elif kind == "assign":
                out.append(f"{pad}{node[1]} = {node[2].text};")
            elif kind == "return":
                out.append(f"{pad}return;")
            elif kind == "goto":
                out.append(f"{pad}goto {node[1]};")
            elif kind == "if":
                out.append(f"{pad}if (!({node[1].text})) goto {node[2]};")
            elif kind == "jump":
                out.append(f"{pad}jump {node[1]};")
            elif kind == "call":
                out.append(f"{pad}{node[1]}();")
            elif kind == "run":
                out.append(f"{pad}run;")
            elif kind in ("ifthen", "ifelse"):
                out.append(f"{pad}if ({node[1].text})")
                out.append(f"{pad}{{")
                out += self.render(node[2], depth + 1)
                out.append(f"{pad}}}")
                if kind == "ifelse":
                    rest = node[3]
                    shared = (len(rest) == 1 and rest[0][0] in ("ifthen", "ifelse")
                              and rest[0][-1] == node[4])
                    if shared:   # "else if": the chain shares one end label
                        chained = self.render(rest, depth)
                        out.append(f"{pad}else {chained[0].lstrip()}")
                        out += chained[1:]
                    else:
                        out.append(f"{pad}else")
                        out.append(f"{pad}{{")
                        out += self.render(rest, depth + 1)
                        out.append(f"{pad}}}")
            elif kind == "while":
                out.append(f"{pad}while ({node[1].text})")
                out.append(f"{pad}{{")
                out += self.render(node[2], depth + 1)
                out.append(f"{pad}}}")
        return out

    def procedure(self, index):
        s = self.script
        start = s.procedures[index].address
        later = [p.address for p in s.procedures if p.address > start] + [len(s.code)]
        end = min(later)
        lines = [f"void {s.procedures[index].name}()", "{"]
        stmts = self.statements(start, end)
        if stmts is None:
            lines.append("    // not decompiled; see the .flowasm")
        else:
            if stmts and stmts[-1] == ("return",):
                stmts = stmts[:-1]
            lines += self.render(self.structure(stmts), 1)
        lines.append("}")
        return "\n".join(lines)

    def decompile(self, title):
        out = [f"// {title}", "// Decompiled by tools/flowscript.py for reading; the exact form is the .flowasm.", ""]
        seen = set()
        for i, p in enumerate(self.script.procedures):
            if p.address in seen:
                out.append(f"// {p.name}: same code as the procedure above\n")
                continue
            seen.add(p.address)
            out.append(self.procedure(i))
            out.append("")
        return "\n".join(out)


def message_notes(data, width=72):
    """A comment for each dialog of a MSG1 message script, by index: its name
    and the start of its text (a message's first page, a selection's options)."""
    if data[8:12] != b"MSG1":
        return {}
    table = messages.MessageTable.parse(data)
    notes = {}
    for k in range(len(table.dialogs)):
        d = table.shown(k)
        parts = [messages.plain(p) for p in d.parts]
        text = " / ".join(parts) if d.kind == messages.SELECTION else parts[0]
        if len(text) > width:
            text = text[:width - 3].rstrip() + "..."
        notes[k] = f"{d.name}: {text}".replace("*/", "* /")
    return notes


# ---- compiling .flow ------------------------------------------------------------------------
#
# Compiles the decompiled form back to code, following the original
# compiler's patterns, so that a decompilation can be checked against the
# original instructions (`flowscript.py verify`).

import re

TOKEN = re.compile(r"""
    (?P<space>\s+|//[^\n]*|/\*.*?\*/)
  | (?P<float>-?\d+\.\d*(?:e[-+]?\d+)?f|-?\d+e[-+]?\d+f|bits:0x[0-9A-Fa-f]+f?)
  | (?P<int>-?\d+)
  | (?P<string>"(?:\\.|[^"\\])*")
  | (?P<name>[A-Za-z_][A-Za-z_0-9]*)
  | (?P<op>\|\||&&|==|!=|<=|>=|[-+*/<>!=(){};,:])
""", re.S | re.X)


def tokenize(text):
    tokens = []
    pos = 0
    while pos < len(text):
        m = TOKEN.match(text, pos)
        if not m:
            raise SyntaxError(f"bad character at {text[pos:pos + 20]!r}")
        pos = m.end()
        kind = m.lastgroup
        if kind != "space":
            tokens.append((kind, m.group()))
    tokens.append(("end", ""))
    return tokens


class FlowCompiler:
    """Compiles one procedure body at a time into (opcode, operand, value)
    tuples whose label/procedure operands are names."""

    def __init__(self, script):
        self.script = script
        self.procedure_names = {p.name for p in script.procedures}
        self.label_count = 0

    def new_label(self):
        self.label_count += 1
        return f"@{self.label_count}"

    # -- parsing helpers --
    def peek(self, offset=0):
        return self.tokens[self.pos + offset]

    def take(self, value=None):
        token = self.tokens[self.pos]
        if value is not None and token[1] != value:
            raise SyntaxError(f"expected {value!r}, got {token[1]!r}")
        self.pos += 1
        return token

    # -- expressions (compiled right operand first) --
    LEVELS = [["||"], ["&&"], ["==", "!="], ["<", ">", "<=", ">="], ["+", "-"], ["*", "/"]]
    OPS = {"||": "OR", "&&": "AND", "==": "EQ", "!=": "NEQ", "<": "S", ">": "L", "<=": "SE", ">=": "LE",
           "+": "ADD", "-": "SUB", "*": "MUL", "/": "DIV"}

    def expression(self, level=0):
        """Returns code for the expression as a list of instructions."""
        if level == len(self.LEVELS):
            return self.unary()
        left = self.expression(level + 1)
        while self.peek()[1] in self.LEVELS[level]:
            op = self.take()[1]
            right = self.expression(level + 1)
            left = right + left + [(self.OPS[op], 0, None)]
        return left

    def unary(self):
        kind, value = self.peek()
        if value == "-":
            self.take()
            return self.unary() + [("MINUS", 0, None)]
        if value == "!":
            self.take()
            return self.unary() + [("NOT", 0, None)]
        return self.primary()

    def literal(self, kind, text):
        if kind == "int":
            number = int(text)
            if -0x8000 <= number < 0x8000 and self.prefer_short:
                return [("PUSHIS", number, None)]
            return [("PUSHI", 0, number & 0xFFFFFFFF)]
        text = text[:-1] if text.endswith("f") else text
        bits = int(text[5:], 16) if text.startswith("bits:") else struct.unpack("<I", struct.pack("<f", float(text)))[0]
        return [("PUSHF", 0, bits)]

    def primary(self):
        kind, value = self.take()
        if kind in ("int", "float"):
            return self.literal(kind, value)
        if kind == "string":
            raw = value[1:-1].encode("latin-1").replace(b"\\\\", b"\\").replace(b'\\"', b'"') + b"\0"
            return [("PUSHSTR", self.script.strings.find(raw), None)]
        if value == "(":
            code = self.expression()
            self.take(")")
            return code
        if kind == "name":
            m = re.fullmatch(r"(var|fvar|local|flocal)(\d+)", value)
            if m and self.peek()[1] != "(":
                op = {"var": "PUSHIX", "fvar": "PUSHIF", "local": "PUSHLIX", "flocal": "PUSHLFX"}[m.group(1)]
                return [(op, int(m.group(2)), None)]
            return self.call(value) + [("PUSHREG", 0, None)]
        raise SyntaxError(f"unexpected {value!r}")

    def call(self, name):
        self.take("(")
        args = []
        while self.peek()[1] != ")":
            args.append(self.expression())
            if self.peek()[1] == ",":
                self.take(",")
        self.take(")")
        code = []
        for arg in reversed(args):
            code += arg
        return code + [("COMM", command_index(name), None)]

    # -- statements --
    def block(self):
        self.take("{")
        code = []
        while self.peek()[1] != "}":
            code += self.statement()
        self.take("}")
        return code

    def statement(self):
        kind, value = self.peek()
        if value == "return":
            self.take(); self.take(";")
            return [("END", 0, None)]
        if value == "run":
            self.take(); self.take(";")
            return [("RUN", 0, None)]
        if value == "jump":
            self.take(); name = self.take()[1]; self.take(";")
            return [("JUMP", name, None)]
        if value == "goto":
            self.take(); name = self.take()[1]; self.take(";")
            return [("GOTO", name, None)]
        if value == "if":
            return self.if_statement(None)
        if value == "while":
            self.take(); self.take("(")
            condition = self.expression()
            self.take(")")
            body = self.block()
            top, end = self.new_label(), self.new_label()
            return ([("LABEL", top, None)] + condition + [("IF", end, None)] + body
                    + [("GOTO", top, None), ("LABEL", end, None)])
        if kind == "name" and self.peek(1)[1] == ":":
            self.take(); self.take()
            return [("LABEL", value, None)]
        if kind == "name" and self.peek(1)[1] == "=":
            self.take(); self.take()
            m = re.fullmatch(r"(var|fvar|local|flocal)(\d+)", value)
            code = self.expression()
            self.take(";")
            op = {"var": "POPIX", "fvar": "POPFX", "local": "POPLIX", "flocal": "POPLFX"}[m.group(1)]
            return code + [(op, int(m.group(2)), None)]
        if kind == "name" and value in self.procedure_names and self.peek(1)[1] == "(":
            self.take(); self.take("("); self.take(")"); self.take(";")
            return [("CALL", value, None)]
        if kind == "name":
            self.take()
            code = self.call(value)
            self.take(";")
            return code
        raise SyntaxError(f"unexpected {value!r}")

    def if_statement(self, shared_end):
        """if / else: every branch ends with a GOTO to the end label; an
        "else if" chain shares the outermost end label."""
        self.take("if"); self.take("(")
        condition = self.expression()
        self.take(")")
        then = self.block()
        if self.peek()[1] != "else":
            label = shared_end or self.new_label()
            code = condition + [("IF", label, None)] + then + [("GOTO", label, None)]
            return code if shared_end else code + [("LABEL", label, None)]
        self.take("else")
        end = shared_end or self.new_label()
        lelse = self.new_label()
        code = condition + [("IF", lelse, None)] + then + [("GOTO", end, None), ("LABEL", lelse, None)]
        if self.peek()[1] == "if":
            code += self.if_statement(end)
        else:
            code += self.block() + [("GOTO", end, None)]
        return code if shared_end else code + [("LABEL", end, None)]

    def compile_procedure(self, tokens, prefer_short=True):
        self.tokens, self.pos, self.prefer_short = tokens, 0, prefer_short
        code = []
        while self.peek()[0] != "end":
            code += self.statement()
        return code + [("END", 0, None)]


def procedure_bodies(text):
    """{name: tokens of the body} from a .flow file."""
    tokens = tokenize(text)
    bodies = {}
    i = 0
    while tokens[i][0] != "end":
        if tokens[i] == ("name", "void"):
            name = tokens[i + 1][1]
            i += 4   # void name ( )
            depth, start = 0, i
            while True:
                if tokens[i][1] == "{":
                    depth += 1
                elif tokens[i][1] == "}":
                    depth -= 1
                    if depth == 0:
                        break
                i += 1
            bodies[name] = tokens[start + 1:i] + [("end", "")]
        i += 1
    return bodies


def verify(script, flow_text):
    """Compare each decompiled procedure, compiled again, with the original
    code. Returns the names of procedures that differ."""
    compiler = FlowCompiler(script)
    bodies = procedure_bodies(flow_text)
    failures = []
    starts = sorted({p.address for p in script.procedures} | {len(script.code)})
    original_by_start = {}
    for start, end in zip(starts, starts[1:]):
        original_by_start[start] = [i for i in instructions(script) if start <= i[0] < end]
    for p in script.procedures:
        if p.name not in bodies:
            continue
        if bodies[p.name] == [("end", "")] and original_by_start[p.address][-1:] != []:
            # "not decompiled": the arguments don't fit the command table.
            if any(OPCODES[i[1]] != "PROC" for i in original_by_start[p.address] if i[1] < len(OPCODES))                     and len(original_by_start[p.address]) > 2:
                failures.append("?" + p.name)
                continue
        original = original_by_start[p.address]
        compiled = compiler.compile_procedure(bodies[p.name])
        if not same_code(script, original, compiled):
            failures.append(p.name)
    return failures


def same_code(script, original, compiled):
    """Instruction-for-instruction equality, matching labels by position."""
    labels_at = {}
    for l in script.labels:
        labels_at.setdefault(l.address, set()).add(l.name)
    # original: (index, opcode, operand, value); skip its leading PROC
    orig = [i for i in original if OPCODES[i[1]] != "PROC"] if original and original[0][1] < len(OPCODES) else original
    comp = [c for c in compiled if c[0] != "LABEL"]
    if len(orig) != len(comp):
        return False
    # compiled label name -> original instruction index it marks
    position = 0
    compiled_label_at = {}
    for c in compiled:
        if c[0] == "LABEL":
            compiled_label_at[c[1]] = orig[position][0] if position < len(orig) else (orig[-1][0] + (2 if orig[-1][3] is not None else 1))
        else:
            position += 1
    for (index, opcode, operand, value), (name, arg, val) in zip(orig, comp):
        if opcode >= len(OPCODES) or OPCODES[opcode] != name:
            return False
        if name in ("GOTO", "IF"):
            target = script.labels[operand].address
            if arg.startswith("@"):
                if compiled_label_at.get(arg) != target:
                    return False
            elif script.labels[operand].name != arg:
                return False
        elif name in ("JUMP", "CALL"):
            if script.procedures[operand].name != arg:
                return False
        elif name in ("PUSHI", "PUSHF"):
            if value != val:
                return False
        elif name == "PUSHSTR":
            a = script.strings[operand:].split(b"\0", 1)[0]
            b = script.strings[arg:].split(b"\0", 1)[0]
            if a != b:
                return False
        elif name == "COMM":
            if (operand & 0xFFFF) != arg:
                return False
        elif operand != arg:
            return False
    return True


# ---- main ---------------------------------------------------------------------------------

def find_script(name):
    for n, data in all_scripts():
        if n == name:
            return data
    raise SystemExit(f"no script {name}")


def main(argv):
    sys.stdout.reconfigure(encoding="utf-8")
    if not argv or argv[0] == "roundtrip":
        failures = 0
        total = 0
        for name, data in all_scripts():
            total += 1
            script = Script.parse(data)
            rebuilt = assemble(disassemble(script, numeric_commands=foreign(name))).serialize()
            if rebuilt != data:
                failures += 1
                first = next((i for i in range(min(len(rebuilt), len(data))) if rebuilt[i] != data[i]), None)
                print(f"DIFF {name}: {len(data)} vs {len(rebuilt)} bytes, first difference at {first}")
        print(f"{total - failures}/{total} scripts reassemble byte-exact")
        return 1 if failures else 0
    if argv[0] == "decompile":
        script = Script.parse(find_script(argv[1]))
        sys.stdout.write(Decompiler(script, message_notes(script.messages)).decompile(argv[1]) + "\n")
        return 0
    if argv[0] == "export":
        out_root = ROOT / "source" / "scripts"
        for old in out_root.rglob("*.bmd"):
            old.unlink()
        count = 0
        for name, data in all_scripts():
            script = Script.parse(data)
            base = out_root / name
            base.parent.mkdir(parents=True, exist_ok=True)
            message_file = None
            # (scene11 has an older MSG0 table: it stays inline, as hex)
            if script.messages[8:12] == b"MSG1":
                message_file = base.name + ".msg"
                table = messages.MessageTable.parse(script.messages)
                (base.parent / message_file).write_text(table.text(f"messages of {name}"),
                                                        encoding="utf-8", newline="\n")
            asm = disassemble(script, message_file, numeric_commands=foreign(name))
            if assemble(asm, base.parent).serialize() != data:
                raise SystemExit(f"{name} does not round-trip")
            (base.parent / (base.name + ".flowasm")).write_text(asm, encoding="utf-8", newline="\n")
            if foreign(name):
                count += 1
                continue
            title = f"{name} (SLUS_209.11 at 0x{EMBEDDED[name]:08X})" if name in EMBEDDED else f"game/dds3/{name}.bf"
            flow = Decompiler(script, message_notes(script.messages)).decompile(title)
            (base.parent / (base.name + ".flow")).write_text(flow + "\n", encoding="utf-8", newline="\n")
            count += 1
        # message tables that are files of their own
        tables = 0
        for path in sorted((ROOT / "game" / "dds3").rglob("*.bmd")):
            name = path.relative_to(ROOT / "game" / "dds3").as_posix()
            text = messages.MessageTable.parse(path.read_bytes()).text(f"game/dds3/{name}")
            target = out_root / (name + ".msg")
            target.parent.mkdir(parents=True, exist_ok=True)
            target.write_text(text, encoding="utf-8", newline="\n")
            tables += 1
        print(f"exported {count} scripts and {tables} message files to {out_root}")
        return 0
    if argv[0] == "verify":
        total = bad = skipped = 0
        undecoded = []
        for name, data in all_scripts():
            if foreign(name):
                continue
            script = Script.parse(data)
            flow = Decompiler(script, message_notes(script.messages)).decompile(name)
            failures = verify(script, flow)
            total += len({p.address for p in script.procedures})
            differ = [f for f in failures if not f.startswith("?")]
            skipped += len(failures) - len(differ)
            bad += len(differ)
            if differ:
                print(f"{name}: {len(differ)} procedures differ: {' '.join(differ[:6])}")
            if len(failures) > len(differ):
                undecoded.append(name)
        print(f"{total - bad - skipped}/{total} procedures recompile to the original code; "
              f"{skipped} not decompiled (arguments don't fit the command table) in: {' '.join(undecoded)}")
        return 1 if bad else 0
    if argv[0] == "disasm":
        sys.stdout.write(disassemble(Script.parse(find_script(argv[1]))))
        return 0
    if argv[0] == "assemble":
        path = Path(argv[1])
        Path(argv[2]).write_bytes(assemble(path.read_text(encoding="utf-8"), path.parent).serialize())
        return 0
    raise SystemExit(__doc__)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
