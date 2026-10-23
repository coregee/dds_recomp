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
PUSHFX PUSHREG POPIX POPFX PROC COMM END JUMP CALL RUN GOTO ADD SUB MUL DIV
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

## The interpreter

`source/src/script/vm.cpp` is the VM, rewritten and tested against the
original instructions (`script_tests.cpp`).

- **A running script** is a *process work* (`scrProcessWork_s`, 0xF4 bytes
  from the pool): one procedure of a loaded file, its code pointer, a stack
  and its own local variables. `scrAddScript2` makes one from a `.bf` in
  memory, `scrAddScript3` loads the file first; the `scrStartScript*`
  functions also start a process (named after the procedure) that runs it.
  All works are kept in a list (0x54E994) so `scrAllReleaseScript` can end
  them. A script with messages gets its own message window
  ([messages.md](messages.md)); an empty message section counts as none.
- **A frame:** the process calls `scrTraceCode`, which runs code words until
  the procedure ends or a command asks to wait. A command returning 0 isn't
  done: the same `COMM` runs again next frame, and `scrGetCommandTimer` tells
  it how many frames it has waited (that is how `SYNC`, `WAIT`, `FADE_*` and
  `SCR_WAIT` work).
- **The stack** has 28 tagged entries: int, float, a global int or float
  variable (by number, read when used), a return address (`CALL`) or a
  string. The last entry is also the *register* commands return results in
  (`PUSHREG`). Global variables are 256 ints and 256 floats in the global
  work; locals are allocated per work from the header's counts.
- **Commands** read their arguments with `scrGetIntPara(n)` and friends from
  the work of the running `COMM` (0x551C78); `COMM` then drops them.

Quirks kept as they are:

- Arithmetic is integer only when both operands are ints (or int
  variables); otherwise both are converted to float. Comparisons, `AND` and
  `OR` always give an int; float `AND` / `OR` test truth in double precision.
- `MINUS` on a variable entry negates the variable itself.
- `NOT` and `IF` pop nothing when the top entry is a string or a return
  address.
- `scrStartScript1a/2/3` don't check that the script was added; the callers
  pass procedures that exist.

The commands every script has (`scrCommonCommand`,
`source/src/script/commands.cpp`) are rewritten with it: `BIT_CHK` /
`BIT_ON` / `BIT_OFF`, `RND` (1..n), `SYNC`, `WAIT`, `PUT` / `PUTS` (debug
prints), `FADE_IN` / `FADE_OUT` (mode 0 black, 1 white), `SEL_JMP`, the pad,
`SCR_RUN` / `SCR_KILL` / `SCR_WAIT` / `SCR_STAT` / `SCR_TIME` (other
procedures of the same script as processes of their own), and the screen
effects, lights, fog, quake and field of view
([screen-effects.md](screen-effects.md)). The parameter commands (`prm_*`: items, Magatama, Macca, the
stock, boss refights; `parameter_commands.cpp`) are described in
[party-and-field.md](party-and-field.md); the other modules' commands are
still the original.

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
