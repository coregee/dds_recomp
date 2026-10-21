"""Atlus message tables (MSG1, `.bmd`) for Nocturne: decode to text, encode back.

    python tools/messages.py roundtrip             check every table re-encodes byte-exact
    python tools/messages.py show <table>          print one table as text
    python tools/messages.py build <in.msg> <out>  build a table from its text

Tables are the .bmd files under game/dds3/ and the message section of every
FlowScript (tools/flowscript.py). `flowscript.py export` writes them to
source/scripts/ as .msg text (see docs/messages.md). The layout, as the game
reads it (itfMesMngInitialize):

    0x00  u8 type (7), 3 bytes 0, u32 size, "MSG1", u32 0,
    0x10  u32 relocation table offset, u32 its size, u32 dialog count,
          u16 relocated flag (0 on disc), u16 version (2)
    0x20  dialog headers {u32 kind (0 message, 1 selection), u32 offset}
          speaker header {u32 offset, u32 count, u32 0, u32 0}
    then  the dialogs, each 4-byte aligned:
            message:   char name[24]; u16 pages; u16 speaker;
                       u32 page offsets[pages]; u32 text size; text
            selection: char name[24]; u16 0; u16 options; u16 0; u16 0;
                       u32 option offsets[options]; u32 text size; text
          speaker name pointers and the names (0-terminated)
          the relocation table (positions of every pointer above)

Offsets count from the end of the 0x20-byte header. The relocation table
lists pointer positions as deltas: an even byte b is +2b; a byte with low
bits 111 is a run of (b >> 3) + 2 pointers 4 bytes apart; low bits 01 start
a 16-bit word w, +(w >> 2) * 4.

Text: ASCII, 0x0A for a new line; a byte 0xF0 | n starts a control code of
n 16-bit units; other bytes from 0x80 are the first of a 2-byte glyph.
"""
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def align4(n):
    return (n + 3) & ~3


# ---- relocation table -----------------------------------------------------------------

def decode_relocations(data):
    positions, pos, i = [], 0, 0
    while i < len(data):
        b = data[i]
        if b & 1 == 0:
            pos += 2 * b
            positions.append(pos)
            i += 1
        elif b & 7 == 7:
            for _ in range((b >> 3) + 2):
                pos += 4
                positions.append(pos)
            i += 1
        else:
            pos += ((b | data[i + 1] << 8) >> 2) * 4
            positions.append(pos)
            i += 2
    return positions


def encode_relocations(positions):
    out = bytearray()
    deltas = []
    previous = 0
    for p in positions:
        deltas.append(p - previous)
        previous = p
    i = 0
    while i < len(deltas):
        run = 0
        while i + run < len(deltas) and deltas[i + run] == 4 and run < 33:
            run += 1
        if run >= 2:
            out.append(((run - 2) << 3) | 7)
            i += run
            continue
        d = deltas[i]
        if d <= 510 and d % 2 == 0:
            out.append(d // 2)
        else:
            w = ((d // 4) << 2) | 1
            out += struct.pack("<H", w)
        i += 1
    return bytes(out)


# ---- text ------------------------------------------------------------------------------

# Control codes, as ps2FontParseMessageTag (0x1C87C8) handles them. Codes
# 0xF1nn take no argument. Codes 0xF2nn take one, stored as two bytes: the
# value + 1, then 0xFF.
NO_ARGUMENT = {
    0x04: "wait",           # end of page: wait for the button
    0x0F: "br",             # new line, unless the font mode breaks lines itself
    0x10: "wait_nospeaker", # end of page: wait, without the speaker's name shown
    0x11: "wait_mode8",     # end of page if font mode 8 is on
    0x12: "lipsync",        # run the window's mouth ("kuti") callback
    0x13: "particle1",      # glyph 80E2 / 80E3 after the last character
    0x14: "particle2",      # glyph 80E4 / 80E5
    0x15: "particle3",      # glyph 80E0 / 80E1
    0x16: "particle4",      # glyph 80E2 or nothing
    0x17: "particle5",      # glyph 80E6 / 80E7
    0x18: "particle6",      # glyph 80E9 80E8 or 80E8
}
ONE_ARGUMENT = {
    0x02: "color",
    0x03: "var",            # a value set by the script (itfMesMngSetVar)
    0x06: "style",
    0x07: "speed",
    0x09: "tp",             # transparency
    0x0A: "fullname",       # names the player entered: 0 the hero, 1 Yuko, 2, 3 classmates
    0x0B: "lastname",       # "Ms. {lastname 1}"
    0x0C: "firstname",      # "My name is {firstname 1} {lastname 1}"
    0x0D: "name",           # the hero's name in the field
}
CODE_NAMES = {**{(0xF1, c): n for c, n in NO_ARGUMENT.items()},
              **{(0xF2, c): n for c, n in ONE_ARGUMENT.items()}}
CODES = {n: k for k, n in CODE_NAMES.items()}
ESCAPED = "\\{["


def text_of(raw, one_line=False):
    """Readable text for one page / option (without its terminating 0).

    New lines stay new lines (`\\x0A` with `one_line`); control codes are
    `{name value}` or, when unnamed or irregular, `{F2 08 FF FF}` (all bytes);
    glyphs outside ASCII are `[XXXX]`; other bytes `\\xNN`. A backslash takes
    the next character literally: `\\\\`, `\\{`, `\\[`, and `\\---` for a line
    that would read as a page break.
    """
    out = []
    i = 0
    while i < len(raw):
        b = raw[i]
        if b >= 0xF0 and i + 2 * (b & 0x0F) <= len(raw) and b & 0x0F:
            size = 2 * (b & 0x0F)
            code = raw[i:i + size]
            name = CODE_NAMES.get((b, code[1]))
            if name and b == 0xF1:
                out.append("{" + name + "}")
            elif name and code[3] == 0xFF:
                out.append("{" + f"{name} {(code[2] - 1) & 0xFF}" + "}")
            else:
                out.append("{" + code.hex(" ").upper() + "}")
            i += size
        elif 0x80 <= b < 0xF0 and i + 1 < len(raw):
            out.append(f"[{raw[i:i + 2].hex().upper()}]")
            i += 2
        elif (b == 0x0A and not one_line) or 0x20 <= b < 0x7F:
            out.append("\\" + chr(b) if chr(b) in ESCAPED else chr(b))
            i += 1
        else:
            out.append(f"\\x{b:02X}")
            i += 1
    lines = "".join(out).split("\n")
    return "\n".join("\\" + line if line == "---" else line for line in lines)


LAYOUT_CODES = re.compile(r"\{(?:[0-9A-F]{2}(?: [0-9A-F]{2})*|wait\w*|speed \d+|style \d+|color \d+|tp \d+|lipsync|br)\}")


def plain(raw):
    """One line of text for a comment: names and variables kept as codes,
    layout codes dropped."""
    text = LAYOUT_CODES.sub("", text_of(raw))
    text = re.sub(r"\\([^x])", r"\1", text)
    return " ".join(text.split())


def bytes_of(text):
    """The bytes `text_of` turned into `text`."""
    out = bytearray()
    i = 0
    while i < len(text):
        c = text[i]
        if c == "{":
            j = text.index("}", i)
            words = text[i + 1:j].split()
            if words[0] in CODES:
                lead, code = CODES[words[0]]
                out += bytes([lead, code])
                if lead == 0xF2:
                    out += bytes([(int(words[1]) + 1) & 0xFF, 0xFF])
            else:
                out += bytes(int(w, 16) for w in words)
            i = j + 1
        elif c == "[":
            j = text.index("]", i)
            out += bytes.fromhex(text[i + 1:j])
            i = j + 1
        elif c == "\\":
            if text[i + 1] == "x":
                out.append(int(text[i + 2:i + 4], 16))
                i += 4
            else:
                out += text[i + 1].encode("ascii")
                i += 2
        else:
            out += c.encode("ascii")
            i += 1
    return bytes(out)


# ---- tables ----------------------------------------------------------------------------

MESSAGE, SELECTION = 0, 1
NO_SPEAKER = 0xFFFF
SPEAKER_VARIABLE = 0x8000     # | n: the name in message variable n (itfMesMngGetVarLocalize)


class Dialog:
    """A message (pages, shown one at a time) or a selection (options)."""

    def __init__(self, kind, name, parts, speaker=NO_SPEAKER):
        self.kind = kind
        self.name = name
        self.parts = parts        # raw bytes of each page / option, without a terminator
        self.speaker = speaker    # messages: index into the speakers, SPEAKER_VARIABLE | n, or none

    def texts(self):
        """The stored parts: a message's pages run on from one another and only
        the last ends in 0; every option ends in 0."""
        if self.kind == MESSAGE:
            return self.parts[:-1] + [self.parts[-1] + b"\0"]
        return [p + b"\0" for p in self.parts]

    def size(self):
        head = 32 if self.kind == MESSAGE else 36
        return head + 4 * len(self.parts) + sum(len(t) for t in self.texts())


def parse_dialog(m, base, kind, starts_from=None):
    """The dialog at m[base:]. A second dialog with an existing name keeps the
    page offsets of the first (`starts_from`), not its own."""
    raw = m[base:base + 24]
    name = raw.split(b"\0")[0].decode("cp932")
    if name.encode("cp932").ljust(24, b"\0") != raw:
        raise ValueError(f"dialog name {raw!r} has bytes after its end")
    speaker = NO_SPEAKER
    if kind == MESSAGE:
        n, speaker = struct.unpack_from("<HH", m, base + 24)
        table = base + 28
    else:
        f18, n, f1c, f1e = struct.unpack_from("<HHHH", m, base + 24)
        if (f18, f1c, f1e) != (0, 0, 0):
            raise ValueError(f"selection {name} has fields {f18, f1c, f1e}")
        table = base + 32
    starts = struct.unpack_from(f"<{n}I", m, table)
    size = struct.unpack_from("<I", m, table + 4 * n)[0]
    text_start = table + 4 * n + 4
    bounds = [s - starts[0] for s in starts] + [size]
    text = m[text_start:text_start + size]
    d = Dialog(kind, name, [], speaker)
    for k, (a, b) in enumerate(zip(bounds, bounds[1:])):
        part = text[a:b]
        terminated = kind == SELECTION or k == n - 1
        if terminated != part.endswith(b"\0"):
            raise ValueError(f"dialog {name} part {k} doesn't end as expected")
        d.parts.append(part[:-1] if terminated else part)
    texts = d.texts()
    own = tuple(text_start - 0x20 + sum(len(t) for t in texts[:k]) for k in range(n))
    if starts != (tuple(starts_from[:n]) if starts_from else own):
        raise ValueError(f"dialog {name} has unexpected page offsets")
    return d, starts


def name_key(name, index):
    """Dialogs with the same name share the first one's header. The compiler
    compared whole names, so two names cut to the 24 stored bytes stay apart."""
    return name if len(name.encode("cp932")) < 24 else (name, index)


class MessageTable:
    """A MSG1 table: dialogs and speaker names.

    Dialog k's header points at the first dialog with dialog k's name (see
    `name_key`). Four event tables use a name twice: the later dialog is still
    stored, with the first one's page offsets, but never shown."""

    def __init__(self, dialogs=None, speakers=None):
        self.dialogs = dialogs or []
        self.speakers = speakers or []    # raw names, without the terminating 0

    @staticmethod
    def parse(m):
        if m[:4] != b"\x07\0\0\0" or m[8:16] != b"MSG1\0\0\0\0":
            raise ValueError("not a MSG1 table")
        size, _, _, reloc_offset, reloc_size, count = struct.unpack_from("<6I", m, 4)
        if struct.unpack_from("<HH", m, 0x1C) != (0, 2) or size != len(m):
            raise ValueError("unexpected MSG1 header")
        headers = [struct.unpack_from("<II", m, 0x20 + 8 * k) for k in range(count)]
        speaker_offset, speaker_count, *zero = struct.unpack_from("<IIII", m, 0x20 + 8 * count)
        t = MessageTable()
        first, position = {}, 8 * count + 16
        for k in range(count):
            position = align4(position)
            key = name_key(m[0x20 + position:0x20 + position + 24].split(b"\0")[0].decode("cp932"), k)
            d, starts = parse_dialog(m, 0x20 + position, headers[k][0], first.get(key, (0, None))[1])
            first.setdefault(key, (position, starts))
            t.dialogs.append(d)
            position += d.size()
        if align4(position) != speaker_offset or zero != [0, 0]:
            raise ValueError("unexpected data after the dialogs")
        offsets = [first[name_key(d.name, k)][0] for k, d in enumerate(t.dialogs)]
        if [(d.kind, o) for d, o in zip(t.dialogs, offsets)] != headers:
            raise ValueError("dialog headers don't follow the naming rule")
        pointers = struct.unpack_from(f"<{speaker_count}I", m, 0x20 + speaker_offset)
        t.speakers = [m[0x20 + p:].split(b"\0", 1)[0] for p in pointers]
        return t

    def shown(self, k):
        """The dialog the game shows for dialog number k."""
        key = name_key(self.dialogs[k].name, k)
        return next(d for j, d in enumerate(self.dialogs) if name_key(d.name, j) == key)

    def serialize(self):
        count = len(self.dialogs)
        start = 8 * count + 16
        body = bytearray()
        pointers = []         # positions (from the end of the header) of every pointer
        first = {}            # name -> (offset, page offsets)

        def pad():
            body.extend(b"\0" * (align4(start + len(body)) - start - len(body)))
            return start + len(body)

        for k, d in enumerate(self.dialogs):
            key = name_key(d.name, k)
            here = pad()
            texts = d.texts()
            if d.kind == MESSAGE:
                head = struct.pack("<HH", len(texts), d.speaker)
            else:
                head = struct.pack("<HHHH", 0, len(texts), 0, 0)
            table = here + 24 + len(head)
            starts, position = [], table + 4 * len(texts) + 4
            for text in texts:
                starts.append(position)
                position += len(text)
            if key in first:
                starts = first[key][1][:len(texts)]
            first.setdefault(key, (here, starts))
            pointers += [table + 4 * i for i in range(len(texts))]
            body += d.name.encode("cp932").ljust(24, b"\0") + head
            body += b"".join(struct.pack("<I", s) for s in starts)
            body += struct.pack("<I", sum(len(x) for x in texts)) + b"".join(texts)
        headers = b"".join(struct.pack("<II", d.kind, first[name_key(d.name, k)][0])
                           for k, d in enumerate(self.dialogs))
        speakers_at = pad()
        names_at = speakers_at + 4 * len(self.speakers)
        for s in self.speakers:
            body += struct.pack("<I", names_at)
            names_at += len(s) + 1
        body += b"".join(s + b"\0" for s in self.speakers)
        pointers += [speakers_at + 4 * i for i in range(len(self.speakers))]
        reloc_at = pad()
        pointers += [4 + 8 * k for k in range(count)] + [8 * count]
        relocations = encode_relocations(sorted(set(pointers)))
        header = (b"\x07\0\0\0" + struct.pack("<I", 0x20 + reloc_at + len(relocations)) + b"MSG1\0\0\0\0"
                  + struct.pack("<IIIHH", 0x20 + reloc_at, len(relocations), count, 0, 2))
        speaker_header = struct.pack("<IIII", speakers_at, len(self.speakers), 0, 0)
        return header + headers + speaker_header + bytes(body) + relocations

    # -- text form --
    #
    #   // comments (before the first dialog)
    #   [speaker 0] Statue
    #
    #   [msg NAME speaker 0] // Statue
    #   page text, its new lines as they are
    #   ---
    #   next page
    #   (blank line)
    #   [sel NAME]
    #   option
    #   ---
    #   option

    def text(self, title=None):
        out = [f"// {title}\n"] if title else []
        for k, s in enumerate(self.speakers):
            out.append(f"[speaker {k}] {text_of(s, one_line=True)}\n")
        if out:
            out.append("\n")
        for d in self.dialogs:
            if d.kind == SELECTION:
                out.append(f"[sel {d.name}]\n")
            elif d.speaker == NO_SPEAKER:
                out.append(f"[msg {d.name}]\n")
            elif d.speaker < len(self.speakers):
                who = text_of(self.speakers[d.speaker], one_line=True)
                out.append(f"[msg {d.name} speaker {d.speaker}] // {who}\n")
            elif d.speaker & SPEAKER_VARIABLE:
                out.append(f"[msg {d.name} speaker var {d.speaker & 0x7FFF}]\n")
            else:
                raise ValueError(f"dialog {d.name} has speaker {d.speaker} of {len(self.speakers)}")
            out.append("\n---\n".join(text_of(p) for p in d.parts) + "\n\n")
        return "".join(out)

    @staticmethod
    def from_text(text):
        t = MessageTable()
        heads = list(HEADER.finditer(text))
        for line in SPEAKER.finditer(text[:heads[0].start()] if heads else text):
            if int(line["index"]) != len(t.speakers):
                raise ValueError(f"speaker {line['index']} out of order")
            t.speakers.append(bytes_of(line["text"]))
        for head, after in zip(heads, heads[1:] + [None]):
            block = text[head.end():after.start() if after else len(text)]
            if not block.endswith("\n\n"):
                raise ValueError(f"dialog {head['name']} doesn't end with a blank line")
            parts = [bytes_of(p) for p in block[:-2].split("\n---\n")]
            if head["kind"] == "sel":
                t.dialogs.append(Dialog(SELECTION, head["name"], parts))
            else:
                speaker = int(head["speaker"]) if head["speaker"] else NO_SPEAKER
                if head["var"]:
                    speaker |= SPEAKER_VARIABLE
                t.dialogs.append(Dialog(MESSAGE, head["name"], parts, speaker))
        return t


HEADER = re.compile(r"^\[(?P<kind>msg|sel) (?P<name>[^\s\]]+)(?: speaker (?P<var>var )?(?P<speaker>\d+))?\][^\n]*\n",
                    re.M)
SPEAKER = re.compile(r"^\[speaker (?P<index>\d+)\] (?P<text>[^\n]*)$", re.M)


# ---- main ------------------------------------------------------------------------------

def all_tables():
    sys.path.insert(0, str(ROOT / "tools"))
    import flowscript
    for name, data in flowscript.all_scripts():
        script = flowscript.Script.parse(data)
        if script.messages[8:12] == b"MSG1":
            yield name, script.messages
    base = ROOT / "game" / "dds3"
    for path in sorted(base.rglob("*.bmd")):
        yield path.relative_to(base).as_posix(), path.read_bytes()


def main(argv):
    sys.stdout.reconfigure(encoding="utf-8")
    if not argv or argv[0] == "roundtrip":
        total = bad = 0
        for name, data in all_tables():
            total += 1
            table = MessageTable.parse(data)
            binary = table.serialize()
            text = MessageTable.from_text(table.text(name)).serialize()
            if binary != data or text != data:
                bad += 1
                print(f"DIFF {name}: binary {'ok' if binary == data else 'differs'}, "
                      f"text {'ok' if text == data else 'differs'}")
        print(f"{total - bad}/{total} message tables re-encode byte-exact, from the table and from the text")
        return 1 if bad else 0
    if argv[0] == "show":
        for name, data in all_tables():
            if name == argv[1]:
                sys.stdout.write(MessageTable.parse(data).text(name))
                return 0
        raise SystemExit(f"no table {argv[1]}")
    if argv[0] == "build":
        text = Path(argv[1]).read_text(encoding="utf-8")
        Path(argv[2]).write_bytes(MessageTable.from_text(text).serialize())
        return 0
    raise SystemExit(__doc__)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
