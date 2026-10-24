# Talks with demons (`nbNegoProcess`)

A talk runs as its own process (`nbInitNegoProcess`, 0x26CCF0) with a record
of its state (`nbNegoProcessData`, `source/include/nocturne/battle/talk.hpp`).
It walks a flow of steps (talk IDs): each step shows a message, maybe a
selection, and chooses the next step among up to eight candidates
(`nbAddNegoIdKouho`). The steps taken are kept in a ring of 14
(`historyindex`, `history`) so that a step can look back
(`nbGetPrevNegoId`, `nbGetBackNoNegoId`).

The process, the helpers and all the steps are rewritten.

## The process

`InitNegoProcessData` sets the talk up: its first step by the talk's type
(0 and 6, an ordinary talk, start at step 0x10007; types 1..5, started by a
talk skill, at 0xC0001..0x100001), what the demon will ask for by the talk
skill's kind (`negoreqtype`), both sides (unit, party, formation, speech
style), and the message tables it needs: per step group a flow table, an
affinity table and an information table, the question table for the
demon's speech style, and the boss, help and fated-pair tables. Each opens
in its own message window. `nbInitNegoProcess` then has the demon take its
talking pose (motion 13, unless it is asleep or stoned), lists the helpers'
skills, turns the music down and starts the talk as a child of the battle's
process (`TalkProcessID`).

Each frame, `nbNegoProcess1` waits while its action still has packets or
wait frames to play. It then runs the current step: the step's flow
function (by the step ID's high half, from the table at 0x4EF468) runs
with the step's phase, which counts up each call. A nonzero result ends the
talk with that result (`endtype`). A step that chose its next step, or left
candidates (the first is taken), moves on, and the step and its message go
into the history. When a step has a message to show (`nowmsgid`), the talk
goes to `nbNegoProcessMessage`, which closes the talk's previous window if
it is another one and opens the message or selection.
`nbNegoProcessMessageChk` waits for it to be read and returns to the steps.
`nbNegoProcessEnd` hands the result to the battle (`talkResult`), and
`nbNegoShutdown` closes the tables, clears `TalkProcessID` and turns the
music back up.

With the battle's debug switch on (stat 0x400000), the talk runs one step a
frame and a debug menu lets the player pick the next step among the
candidates.

## The steps

A step's ID is its group << 16 | its number. Each group's flow function
(`nbNegoFlow*`, the HD remaster's `NbNegoFlow*` classes) runs the step by
its number from its own table. A step queues the steps it may go on to
(`nbAddNegoIdKouho`; without the debug menu, the first is taken unless it
sets `nextnegoid` itself), may show a message or wait, and returns 0, or a
result that ends the talk. `workid` holds steps noted for later: a group
that hands over to another (a question, a helper) says where to go on
after.

| Group | HD class | Source | What it is |
|---|---|---|---|
| 1 | `NbNegoFlowOne` | talk_opening.cpp | the opening: who talks, and how |
| 2 | `NbNegoFlowFullMoon` | talk_fullmoon.cpp | under a full Kagutsuchi: one question, then joining or Macca |
| 3 | `NbNegoFlowStock` | talk_minor.cpp | a short refusal (result 2) |
| 4 | `NbNegoFlowDouchara` | talk_kin.cpp | the demon meets its own kind |
| 5 | `NbNegoFlowInnen` | talk_fated.cpp | a fated pair's scripted exchange |
| 6 | `NbNegoFlowTwo` | talk_bargain.cpp | the bargaining |
| 7 | `NbNegoFlowQuestion` | talk_question.cpp | a question and the answer's Reason |
| 8 | `NbNegoFlowFight` | talk_fight.cpp | a last refusal (and the debug menu's fights) |
| 9 | `NbNegoFlowOk` | talk_deal.cpp | the deal struck: joining, Macca, an item, information |
| 10 | `NbNegoFlowNg` | talk_nodeal.cpp | no deal: partings, attacks, the Death Pact |
| 11 | `NbNegoFlowDrain` | talk_drain.cpp | the demon drains the talker's HP |
| 12 | `NbNegoFlowMukan` | talk_speaksup.cpp | the last enemy speaks up |
| 13 | `NbNegoFlowSensei` | talk_ambush.cpp | an ambushing demon's question or demand |
| 14 | `NbNegoFlowBinjo` | talk_minor.cpp | a demon asks to join |
| 15 | `NbNegoFlowInoti` | talk_mercy.cpp | the last enemy begs for its life |
| 16 | `NbNegoFlowKoketa` | talk_minor.cpp | a taunt after a failed escape |

The talk's result goes to the battle (`talkResult`, SetAction_NEGORESULT):
1 the talk failed (a press turn lost), 2 the demon leaves, 3 it joins,
4 it attacks (the turn lost), 5 its kind leave, 6 the battle ends, 7 and 8
nothing more, 9 it joins and the battle ends.

Some of what the steps read never varies in the game's data: every
demon's gift weights add up to 100 (the fallback items never come up),
every own-question entry is {by stat 1, 70, 30} and no unit has stat 1,
no demon has honbou type 1, no fated pair has more than two gifts, and
drains always take HP (the drawing for MP is of one).

## The message window

`nbDispNegoMessage` notes the message to show (`nowmsgid`: its window,
`nowmsgno`) and whether it is a selection (stat bit 4; otherwise it is also
the step's message, `nowmes`). `nbCheckNegoMessage` waits until the window
is done (a selection: answered, the answer in `nowselect`) and lets it go.
`nbClsNegoMessage` closes the talk's window (`msgwndid`). The messages'
variables: {var 0} the demon and {var 4} its race; {var 1} and {var 5} the
player's side (the Demi-fiend's name and race 0 when he speaks);
{var 3} an amount of Macca and {var 2} an item.

## What changes hands

"Yaru" (give) is what the demon gives, "kure" (give me) what it asks for;
`a` is the player's side, `b` the demon. Macca is rounded to tens and never
0.

| Function | Amount |
|---|---|
| `nbGetNegoYaruMakkaA` | its Macca reward (`dropmakka`) x 5..8 |
| `nbGetNegoKureMakkaA` | its level x 21..30 x 0.8 |
| `nbGetNegoYaruMakkaB` | 40..69% of what it would ask |
| `nbGetNegoKureMakkaB` | 50..69% of what it would ask |
| `nbGetNegoKureHpA` | 14..21% of its max HP (20..29% with event bit 8) |
| `nbGetNegoKureHpB` | 10..19% of its max HP |
| `nbGetNegoKureMpA` / `B` | 10..39% / 10..19% of its max MP |
| `nbGetKureItemA` / `B` | an item by its level band (5 levels each; none at 0 or 100+), from weighted tables at 0x3E2318 / 0x3E23F8 |

What the demon gives as an item, a second item or a stone comes from its
talk record (`DevilTalkFormat`): three lists of four {weight, item} at
+0x16, +0x1E and +0x26 (`nbGetNegoYaruItemA`, `B`, `nbGetNegoYaruStone`).

`nbGetNegoRequestType` and `nbGetNegoTuikaRequestType` ("tuika", extra)
pick what a demon asks for from weighted tables by its `reqtype` /
`tuikareqtype` (0x3E22A8, five kinds; 0x3E23B8, three).

## Helpers, information, answers

Party members on the player's side (but the one talking, `ppartyindex`)
who can talk may help with a talk skill: `nbSetAllHojoSkillWork` lists, per
party slot, its unit's talk skills (skill type 2, IDs from 0x180; kind 7 in
the talk skill table at 0x3E1338: 0x199..0x19F, 0x1A2..0x1A4) and clears the
slot's "used" mark (party flag 0x80); `nbGetHojoSkillWorkCnt` counts those
not used yet. The original writes the list with no limit, on past the eight
slots.

`nbGetInfoMsg` picks the information a demon tells: one of 30 messages (the
second 30 for type 2), eight times in ten one whose event bits are all set
(`nbCheckSelectMesJoukenAri`), else one with none. No message in the game's
table has event bits, so it is always the latter.

`nbSetNegoYesMotion` / `nbSetNegoNoMotion` close the window and have the
demon nod (motion 14) or shake its head (15) with its voice, 15 frames.
`nbGetInnenNegoID` finds a fated pair (`innen`) for this player-side devil
and demon in a table of 64 at 0x3E3158.

`nbSearchHojoSkillWork` uses a helper's skill for one moment of the talk
(type 0..3): the helpers are tried most agile first, and the first not yet
used who has a skill for the moment uses one at random (0x199 at 0;
0x19A, 0x1A2, 0x1A3 at 1; 0x19B, 0x1A3 at 2; at 3 0x19D..0x1A1, 0x1A3,
0x1A4, and 0x19C when the helper is of the demon's race). The skill and the
helper are marked used; the result is the party slot << 16 | the skill.

`nbGetQuestionType` picks the question a demon asks. Two thirds of the
demons have their own set (`privatesel` 1, weights by `privateselindex` at
0x3E2508). The others ask half the time once the player's answers by kind
(`GlobalWork::questionAnswers` [1..3], HD `negoques`) add up to more than
half of all answers ([0]), else eight times in ten. The kind is meant to
depend on how the answers rank, but the original compares the kinds'
indices, which always differ, so it is kind 2 three times in ten and kind
3 otherwise, never kind 1.

## The bargaining (group 6)

The talk skill's record (the table at 0x3E1338, 0x68 bytes) holds what
the demon is asked for, four weights for the round's outcome, and four
good and four bad affinity rules. A rule is a pair of conditions
(`ChkAisyo`), one for the talker toward the demon and one the other way:
speech traits, a level gap of ten, the same race, a particular devil, or
the moon. The first good rule that holds disposes the demon well, else the
first bad rule badly.

Each round the demon asks for something by its talk record's request
weights (an item, Macca, a question, to drain, a fight; Macca as a gift
for the gift-asking skills), never the same kind twice running. Given, the
weights decide: a deal, talk on, a question, or refusal. A good
disposition moves 20 points (10 for Tyrants) from refusal and the
question to the deal, a bad one 20 the other way; the early rounds lean to
talk and, after event 8, to questions; from the fourth round a deal is
sure. Refused, it may haggle a Macca demand down by half up to three
times, or try again. A party member with a talk skill may step in at four
moments of the talk (the helpers' skills, `nbSearchHojoSkillWork`),
taking the talker's place on the field while it works.

Asking Macca of a talker far above its level (6_12), the chance grows by
bands of five levels (20, 40, 60, 80, 97 in a hundred), but the bands
don't meet: at gaps of 9, 14, 19 and 24 levels the chance is none.
