# Message tables

All dialogue, narration and menu prompts that scripts show are in Atlus
message tables (MSG1): one inside every script, and 31 more as `.bmd` files
of their own. `tools/messages.py` decodes them; `flowscript.py export`
writes each as text next to its script in `source/scripts/` (`<script>.msg`,
and `<name>.bmd.msg` for the separate files). All 208 tables re-encode to
the original bytes from that text (`python tools/messages.py roundtrip`), and
the scripts are assembled from it.

There are 8,620 dialogs with 15,712 pages and options.

## The text form

```
// messages of event/e600/e601/scr/e601
[speaker 0] Woman's voice
[speaker 1] {firstname 1}

[msg YUUKO_004 speaker 0] // Woman's voice
{F2 08 FF FF}{speed 6}The world will fall for its sins,
and humans will all disappear...
{wait}
---
{F2 08 FF FF}But, I don't want you to meet
the same fate.
{wait}

[sel KAIWA_SEL2]
{F2 08 FF FF}Hooded jacket.
---
{F2 08 FF FF}Leather jacket.
```

- `[msg NAME]` is a message, shown a page at a time; `[sel NAME]` a
  selection, one option per part. Parts are separated by `---` lines and
  the dialog ends with a blank line. A script refers to dialogs by number:
  their order in the file.
- `speaker n` names the speaker from the table's list; `speaker var n` takes
  the name from message variable n (set by the script,
  `itfMesMngGetVarLocalize`).
- New lines are new lines. `{...}` is a control code, `[XXXX]` a 2-byte
  glyph code outside ASCII, `\xNN` any other byte; a backslash makes the next
  character literal (`\\`, `\{`, `\[`, and `\---` for a text line that
  would read as a page break).

In the decompiled scripts, `itfMesMngMessage(3) /* NAME: text... */` and
`itfMesMngSelect` quote the dialog's first page or its options.

## Control codes

A byte `0xF0 | n` starts a code of n 16-bit units: `0xF1` codes are just
the code number, `0xF2` codes carry one argument stored as two bytes, value
+ 1 and `0xFF`. As handled by `ps2FontParseMessageTag` (0x1C87C8) and the
message manager (`ReadytoMessage`, `CalcMessage`):

| Code | Text | Effect |
|---|---|---|
| F1 04 | `{wait}` | end of the page; wait for the button (a page without it turns by itself) |
| F1 10 | `{wait_nospeaker}` | end of the page; wait, and hide the speaker's name and panel for this page (narration, `> ...`) |
| F1 11 | `{wait_mode8}` | end of the page if font mode 8 is on |
| F1 12 | `{lipsync}` | call the window's mouth-movement callback (`itfMesMngSetKutiCallback`, "kuti" = mouth) |
| F1 0F | `{br}` | new line when the font doesn't break lines itself (unused) |
| F1 13..18 | `{particle1..6}` | append glyph 80E2/80E3, 80E4/80E5, 80E0/80E1, 80E2 or nothing, 80E6/80E7, 80E9 80E8 or 80E8, depending on the previous character |
| F2 02 | `{color n}` | text color |
| F2 03 | `{var n}` | a value the script set (`itfMesMngSetVar`: numbers, names) |
| F2 06 | `{style n}` | font style |
| F2 07 | `{speed n}` | drawing speed |
| F2 09 | `{tp n}` | transparency |
| F2 0A / 0B / 0C | `{fullname n}` / `{lastname n}` / `{firstname n}` | a name the player entered: 0 the hero, 1 Yuko, 2 and 3 the classmates (by use: "My name is {firstname 1} {lastname 1}", "Ms. {lastname 1}"; the legacy names `ps2FontAppendNameFirst` / `Second` for 0B / 0C follow Japanese order) |
| F2 0D | `{name n}` | the hero's name as the field shows it |

`F2 08 FF FF` begins nearly every page. The font parser skips it and nothing
found so far reads it, so it stays as raw bytes. Codes are also raw when
they don't have this shape. Unhandled `0xF1` codes (F1 0B appears twice)
are ignored by the game.

## In the game: the message manager

`source/src/interface/message.cpp` (original unit `itfMesManager`,
0x1CD2E0..0x1D10A8) shows the tables; every function there is checked
against the original instructions (see *Testing against the original code*
in `AGENTS.md`).

- A script opens a **window** on its table (`itfMesMngInitialize`): an
  `instanceMes_tag` from a list of 128 (`itfMiscLink*`), which turns the
  table's offsets into addresses once (`itfMesResolveResourceAddress`, using
  the relocation table).
- `MESSAGE(n)` (`itfMesMngMessage`) asks for dialog n and returns "not done"
  until it has been shown. `itfMesMngRequestMessage` hands the `{var n}`
  strings to the font engine, lays out the first page (`ReadytoMessage`), and
  lays out the speaker's name when it changes: a name from the table, or with
  `speaker var n` the string in variable n.
- Each frame (`CalcManagerProc` → `CalcMesFlow`) the panels fade (the
  message panel in by 24 and out by 8 a step up to its alpha, the speaker's
  by 32 up to 200), and `CalcMessage` handles the end of a page: a page that
  ended in `{wait}` or `{wait_nospeaker}` waits for the confirm or cancel
  button, or the skip button held for five frames; a page without one turns
  at once. The confirm, cancel and skip buttons also make the rest of a page
  appear at once, unless `IGNORE_CONFIG` is on. The player's message-speed
  setting does the same from the start of each page.
- `SET_VAR(n, value, type)` (`itfMesMngSetVar`) fills `{var n}`: type 0 a
  number, 4 a floor ("B2F", "3F", "R" above 1000), 1 / 3 / 5 / 8 / 9 the name
  of a devil / item / skill / race / Magatama, 6 / 7 an area / a part of
  one, 10 a name the player entered (0 the hero, 1 Yuko, 2 and 3 the
  classmates); type 2 does nothing.
- `{wait_nospeaker}` hides the speaker's panel for that page; `{lipsync}`
  calls the callback the script installed (`itfMesMngSetKutiCallback`).
- `SELECT(n)` lays out the visible options (`MASK_SELECT` hides some) below
  the message, scrolls the message up by 64 a frame until they fit, lets the
  player move the cursor (wrapping around) or press a button bound with
  `SELECT_DEFKEY`, fades the other options out and scrolls back; the result is
  the option's number among all options.
- `VALIDATE_NEXT(0)` makes pages end without waiting; `MSG_POS` moves the
  text; `WINDOW_TYPE` changes the panel's shape (1 wide, 2 short) and alpha.

The window's state is in `instanceMes_tag::stat`: the low 3 bits are the
message (2 opening, 3 drawing, 4 at the end of a page), bits 3..5 the
selection, 0x300 and 0x3000 the message and speaker panels (fading in,
shown, fading out); the flags above 0xFFFF are set by script commands
(`itfMesMngMarkBitStat` / `ClearBitStat` can only touch those).

## Encoding details

From `tools/messages.py` (the module docstring has the byte layout):

- The 0x20-byte header, dialog headers {kind, offset} and a speaker header,
  then the dialogs in order, each 4-byte aligned, then the speaker names,
  then a relocation table listing every pointer (the game rebases them when
  it loads the table).
- A message's pages run on from one another: only the last ends in a 0
  byte. Every option of a selection ends in 0.
- Two dialogs with the same name share the first one's header entry. Four
  event tables (e510, e670, e721, e731) repeat a name: the second dialog is
  still stored, with the first one's page offsets, but can never be shown.
  Names longer than 24 bytes are cut to 24; the compiler compared the whole
  names, so cut names that collide (in f041..f045 and the fusion messages)
  stay separate dialogs.
- One script, `event/scr/scene11`, has an older-format table (MSG0); it stays
  in its `.flowasm` as hex.

## Unreadable tables

60 tables are mostly glyph codes rather than ASCII: the negotiation tables
(`nego/msg/*`, `battle/script/nego`), `result2/scr/message`,
`title/mseldata.bmd`, the e500-e550 and e800-e810 events, the test scenes
and a few others. The particle codes, which pick between two glyphs by the
preceding character, match Korean particles (은/는, 이/가, 을/를), so these
look like Korean text left from another release (inferred; unverified). Reading
them needs the font's code-to-glyph map, not decoded yet.
