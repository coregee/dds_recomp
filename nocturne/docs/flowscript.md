# FlowScript (`.bf`): event, field and AI scripts

The game's scripted behaviour — events, field maps, facilities, battle
messages and the enemy AI scripts — is Atlus FlowScript, a bytecode run by a
small stack VM in the executable (`scrCodeFunc_*`, the `scr*` functions).
`tools/flowscript.py` reads it, writes it out as source, and proves both
forms against the original bytes.

## Where the scripts are

| Script | Where | Procedures |
|---|---|---:|
| enemy AI | embedded in `SLUS_209.11` at 0x4F0800 (`nbInitAiScript`) | 141 |
| (unnamed) | embedded at 0x3267A8 | 1 |
| events, field maps, facilities, results | 191 `.bf` files in `DDS3.IMG` | 3,270 |

The sources are in `source/scripts/` (`exe/ai.flow` for the AI), mirroring
the archive paths. Each script has:

- **`.flowasm`** — the exact form. `python tools/flowscript.py assemble x.flowasm
  x.bf` rebuilds the original file byte for byte (all 193 do:
  `flowscript.py roundtrip`).
- **`.flow`** — the readable form, decompiled from it.
- **`.msg`** — the script's message table as text (see
  [messages.md](messages.md)); the `.flowasm` names it and `assemble` encodes
  it back. The one older-format table (`event/scr/scene11`, MSG0) stays
  inline in its `.flowasm` as hex.

`python tools/flowscript.py export` regenerates all three from the disc, and
the 31 message tables that are files of their own as `<name>.bmd.msg`.

## The format

FlowScript version 1, as the interpreter reads it:

- A 0x20-byte header: `"FLW0"` at 8, the section count at 0x10, local
  variable counts at 0x14 / 0x16.
- Section descriptors `{type, element size, count, offset}`:
  0 procedures and 1 jump labels (`{char name[24]; u32 instruction; u32 0}`),
  2 code, 3 the message table, 4 strings. The strings section's count is
  often wrong (sometimes 0); the strings run to the end of the file.
- Code is 4-byte words `{u16 opcode, s16 operand}`; `PUSHI` and `PUSHF` take
  the following word as their value.

Opcodes 0..34 (`scrCodeFunc_*` table at 0x2FA528): `PUSHI PUSHF PUSHIX
PUSHIF PUSHREG POPIX POPFX PROC COMM END JUMP CALL RUN GOTO ADD SUB MUL DIV
MINUS NOT OR AND EQ NEQ S L SE LE IF PUSHIS PUSHLIX PUSHLFX POPLIX POPLFX
PUSHSTR`.

- Binary operators pop the **left** operand first: the compiler pushes the
  right operand, then the left. `S`/`L`/`SE`/`LE` are `<`/`>`/`<=`/`>=`.
  `OR`/`AND` evaluate both sides.
- `COMM n` calls entry n of the command table at 0x52E350 (`{handler,
  argument count}`). Arguments are pushed last first, so argument 0 is on
  top; `PUSHREG` pushes the result.
- `IF label` pops a value and jumps when it is zero.
- `END` returns; `JUMP` continues in another procedure; `CALL` calls one.

## Command names

`reference/names/script-commands.tsv` names the 471 commands. 423 names
come from the HD remaster: its `ScrCommandTable..cctor` builds the same table,
and the names were read from its machine code (each entry's MethodInfo
reference and array index); all 97 names already known on the PS2 side agree.
Two more come from the PS2 function map; the remaining 46 are `COMM_xxx`.

## The decompiled form

```c
void tousou()
{
    if (AI_CHK_PLV(AI_GET_MYLV() + 15) == 1)
    {
        ...
    }
    AI();
}
```

- Commands are called by name; `var<n>` / `local<n>` are the global and local
  integer variables (`fvar` / `flocal` for floats).
- `- 5` is the unary minus applied to 5 (as compiled); `-5` is the literal.
- `itfMesMngMessage(3) /* fol_007: ... */` and `itfMesMngSelect` name the
  dialog and quote the start of its text (a message's first page, a
  selection's options).

The decompiler rebuilds `if` / `else` / `else if` / `while` from the
original compiler's patterns: every branch ends with a jump to its end label,
an `else if` chain shares one end label, `else { if … }` nests its own.
`flowscript.py verify` compiles every decompiled procedure again with those
same rules and compares it instruction by instruction with the original:
**3,321 of 3,338 procedures match exactly**, including all of the AI.

Not decompiled:

- 17 procedures in the early test scripts under `event/scr/` (`ctest*`,
  `scene*`, `gameover`) call commands with fewer arguments than the final
  table says; they were evidently compiled against an older command set.
- The negotiation scripts (`nego/script/*`, `battle/script/nego`) don't
  follow the command table at all (a message call lands on `BLUR_ALLOFF`), so
  they keep numeric commands and have no `.flow`. Nothing in the executable
  loads them by name; whether and how they run is open.
