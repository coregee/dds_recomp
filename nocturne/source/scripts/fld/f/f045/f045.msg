// messages of fld/f/f045/f045
[speaker 0] Debug message
[speaker 1] Voice of the door
[speaker 2] Pixie
[speaker 3] Soul
[speaker 4] Izanami
[speaker 5] Izanagi
[speaker 6] Izanagi and Izanami
[speaker 7] Voice
[speaker 8] Dr. Dark
[speaker 9] Voice of Cerberus
[speaker 10] Demon
[speaker 11] Shady Broker

[sel YN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F045_DEBBUG]
{F2 08 FF FF}{speed 6}> Add Candelabrum of Sovereignty
to inventory?
{wait}

[msg F045_DEBBUG2 speaker 0] // Debug message
{F2 08 FF FF}{speed 6}What do you want to do?
{wait}

[sel F045_DEBBUG2_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Mithra flag on
---
{F2 08 FF FF}Thor flag on
---
{F2 08 FF FF}All of the above
---
{F2 08 FF FF}Nothing

[sel F045_DEBBUG3_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Ahriman flag on
---
{F2 08 FF FF}Noah flag on
---
{F2 08 FF FF}Baal Avatar flag on
---
{F2 08 FF FF}All of the above
---
{F2 08 FF FF}Nothing

[msg F045_CLOSE_DOOR1]
{F2 08 FF FF}{speed 6}> The hole is blocked...
{wait}

[msg F045_CLOSE_DOOR2]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F045_SHAFT_Q]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F045_SHAFT_ENT]
{F2 08 FF FF}> Return to the entrance
of the Labyrinth?
{wait}

[msg F045_SHAFT_UP]
{F2 08 FF FF}{speed 6}> Return to the previous Kalpa?
{wait}

[msg MSG_001]
{F2 08 FF FF}{speed 6}> There is a huge pedestal.
{wait}

[msg MSG_001_2]
{F2 08 FF FF}{speed 6}> You do not have a candelabrum
for this pedestal...
{wait}

[msg MSG_002]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Sovereignty{color 0}?
{wait}

[sel STOKERE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg MSG_003]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Sovereignty{color 0}.
{wait}

[msg MSG_003B]
{F2 08 FF FF}{speed 6}> The candelabrum has been lit...
{wait}

[msg MSG_006]
{F2 08 FF FF}{speed 6}> The flames illuminate the passage
beyond.
{wait}

[msg MSG_SW_010]
{F2 08 FF FF}{speed 6}> There is a switch.
Will you activate it?
{wait}

[msg MSG_011_010]
{F2 08 FF FF}{speed 6}> The switch has been activated.
{wait}

[msg NO_NAME]
{F2 08 FF FF}{speed 6}> There is a tombstone without
a name on it...
{wait}

[msg VISER_USE]
{F2 08 FF FF}{speed 6}> Will you put on the Black Visor?
{wait}

[msg LETTER_CHANGE]
{F2 08 FF FF}{speed 6}> The inscription on the tombstone
changed.
{wait}

[msg LETTER_NOCHANGE]
{F2 08 FF FF}{speed 6}> The inscription on the tombstone
remained the same.
{wait}

[msg MITO_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Mithra:
Defeated in {var 0} turn(s)."
{wait}

[msg MITO_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Mithra:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg MITO_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Mithra."
{wait}

[msg MITO_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Mithra...
{wait}

[msg THOR_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Thor:
Defeated in {var 0} turn(s)."
{wait}

[msg THOR_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Thor:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg THOR_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Thor."
{wait}

[msg THOR_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Thor...
{wait}

[msg AHRI_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Ahriman:
Defeated in {var 0} turn(s)."
{wait}

[msg AHRI_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Ahriman:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg AHRI_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Ahriman."
{wait}

[msg AHRI_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Ahriman...
{wait}

[msg NOAH_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Noah:
Defeated in {var 0} turn(s)."
{wait}

[msg NOAH_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Noah:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg NOAH_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Noah."
{wait}

[msg NOAH_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Noah...
{wait}

[msg BAAL_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Baal Avatar:
Defeated in {var 0} turn(s)."
{wait}

[msg BAAL_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Baal Avatar:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg BAAL_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Baal Avatar."
{wait}

[msg BAAL_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Baal Avatar...
{wait}

[msg CHK_AKUMA_001 speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}I shall now test your heart...
{wait}
---
{F2 08 FF FF}If you are a true demon,
then you may see what lies beyond
this door.
{wait}

[msg CHK_AKUMA_001B speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Now, leave here...
{wait}

[msg CHK_DOOR_SYSTEM_01]
{F2 08 FF FF}{speed 6}> You have no demon to present.
{wait}

[msg CHK_DOOR_SYSTEM_02]
{F2 08 FF FF}{speed 6}> The door would not budge...
{wait}

[sel CHK_DOOR_SYSTEM_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}Select a different demon.
---
{F2 08 FF FF}Give up.

[msg CHK_POW_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one of great strength
step forward.
{wait}

[msg CHK_MAG_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one of great magic
step forward.
{wait}

[msg CHK_STA_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one of great vitality
step forward.
{wait}

[msg CHK_QUK_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one of great agility
step forward.
{wait}

[msg CHK_LUK_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one of great luck
step forward.
{wait}

[msg CHK_META_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one brimming with light
step forward.
{wait}

[msg CHK_ZYA_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one whose soul is black
step forward.
{wait}

[msg CHK_BERU_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let one who embodies chaos
step forward.
{wait}

[msg CHK_PIXY_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}If you wish to pass,
let the one who has been with you
the longest step forward.
{wait}

[msg OUT_POW_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's strength does not
meet my expectations!
{wait}

[msg OUT_MAG_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's magic does not
meet my expectations!
{wait}

[msg OUT_STA_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's vitality does not
meet my expectations!
{wait}

[msg OUT_QUK_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's agility does not
meet my expectations!
{wait}

[msg OUT_LUK_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's luck does not
meet my expectations!
{wait}

[msg OUT_DEVIL_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}This is not the one I seek.
{wait}

[msg GO_OUT_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Begone!
{wait}

[msg OK_POW_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's strength
is admirable indeed...
You may pass.
{wait}

[msg OK_MAG_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's magic
is admirable indeed...
You may pass.
{wait}

[msg OK_STA_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's vitality
is admirable indeed...
You may pass.
{wait}

[msg OK_QUK_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's agility
is admirable indeed...
You may pass.
{wait}

[msg OK_LUK_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Your comrade's luck
is admirable indeed...
You may pass.
{wait}

[msg OK_DEVIL_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}You have with you a mighty
comrade... You may pass.
{wait}

[msg OK_DEVIL_DOOR_ZYA speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}You have with you a comrade
as black as night...
You may pass.
{wait}

[msg TAKE_POW_DOOR]
{F2 08 FF FF}{speed 6}> Have {var 0} step forward?
{wait}

[msg TAKE_MAG_DOOR]
{F2 08 FF FF}{speed 6}> Have {var 0} step forward?
{wait}

[msg TAKE_STA_DOOR]
{F2 08 FF FF}{speed 6}> Have {var 0} step forward?
{wait}

[msg TAKE_QUK_DOOR]
{F2 08 FF FF}{speed 6}> Have {var 0} step forward?
{wait}

[msg TAKE_LUK_DOOR]
{F2 08 FF FF}{speed 6}> Have {var 0} step forward?
{wait}

[msg TAKE_DEVIL_DOOR]
{F2 08 FF FF}{speed 6}> Have {var 0} step forward?
{wait}

[msg PIXY_REBIRTH_SYSTEM_01]
{F2 08 FF FF}{speed 6}> {var 0} is acting
strangely...
{wait}

[msg PIXY_REBIRTH_01 speaker var 0]
{F2 08 FF FF}{speed 6}What's happening...?
I feel this... power...
growing inside me...
{wait}
---
{F2 08 FF FF}!!
{wait}

[msg PIXY_REBIRTH_02 speaker 2] // Pixie
{F2 08 FF FF}{speed 6}What? Why are you looking at me
like that?
{wait}
---
{F2 08 FF FF}I've been right here by your side
from the very beginning.
{wait}

[msg PIXY_REBIRTH_03 speaker 2] // Pixie
{F2 08 FF FF}{speed 6}Um, you're not waiting for me
to say my line, are you...?
*sigh* Alright, alright...
{wait}
---
{F2 08 FF FF}I'm {color 4}Pixie{color 0} of the {color 4}Fairy{color 0} clan.
Please take care of me...
{wait}

[msg KAISU_DOOR speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Attention trespassers...
{wait}
---
{F2 08 FF FF}We are the law here.
{wait}
---
{F2 08 FF FF}We will only permit you to use us
{color 1}three times{color 0} before you are forced
to leave.
{wait}

[msg KAISU_DOOR_1ST speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Attention trespassers...
{wait}
---
{F2 08 FF FF}You are only permitted to use us
{color 1}two more times{color 0}!
{wait}

[msg KAISU_DOOR_2ND speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Attention trespassers...
{wait}
---
{F2 08 FF FF}You are only permitted to use us
{color 1}one more time{color 0}!
{wait}

[msg KAISU_DOOR_3RD speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}Attention trespassers...
{wait}
---
{F2 08 FF FF}You have now passed through us
three times.
{wait}
---
{F2 08 FF FF}You will not be allowed to advance
any further!
{wait}

[msg KAISU_DOOR_OUT speaker 1] // Voice of the door
{F2 08 FF FF}{speed 6}We have warned you,
foolish demon!
{wait}
---
{F2 08 FF FF}Leave this instant!
{wait}

[msg GO_ROSINSI]
{F2 08 FF FF}{speed 6}> The lift leads to the deepest part
of the Labyrinth. Ride the lift?
{wait}

[msg BOTTAKURI_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Gee, you look worn out.
{wait}
---
{F2 08 FF FF}Would you like to rest for a while?
Only 500 Macca!
{wait}

[msg BOTTAKURI_NO speaker 3] // Soul
{F2 08 FF FF}{speed 6}Oh... Well, please come again!
{wait}

[msg BOTTAKURI_NOMONEY speaker 3] // Soul
{F2 08 FF FF}{speed 6}Oh, you don't have enough Macca...
Come back when you do.
{wait}

[msg BOTTAKURI_YES_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}You must be thirsty.
Here, have a drink...
{wait}

[msg BOTTAKURI_YES_02]
{F2 08 FF FF}{speed 6}> Your party recovered.
{wait}

[msg BOTTAKURI_YES_03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Go ahead, have some more...
{wait}

[msg BOTTAKURI_YES_04 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Are you feeling better?
Here's some more...
{wait}

[msg BOTTAKURI_YES_05]
{F2 08 FF FF}{speed 6}> Your party recovered some more.
{wait}

[msg BOTTAKURI_YES_06 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...Have... another... drink...


[msg BOTTAKURI_YES_07]
{F2 08 FF FF}{speed 6}> Your wallet feels really light...
{wait}

[msg NOT_GO001]
{F2 08 FF FF}{speed 6}> The lift does not seem to be
working...
{wait}

[msg F045_AREA29_IZA001 speaker 4] // Izanami
{F2 08 FF FF}{speed 6}You have come at last,
{name 0}.
{wait}

[msg F045_AREA29_IZA002 speaker 5] // Izanagi
{F2 08 FF FF}{speed 6}Izanami and I had long watched
over the land of the rising sun.
{wait}
---
{F2 08 FF FF}However, as was destined,
the world fell...
and our power was lost.
{wait}

[msg F045_AREA29_IZA003 speaker 4] // Izanami
{F2 08 FF FF}{speed 6}Unable to wield our strength,
{wait}
---
{F2 08 FF FF}we awaited the one to whom
we could entrust the future.
{wait}

[msg F045_AREA29_IZA003_02 speaker 4] // Izanami
{F2 08 FF FF}{speed 6}...And now you have come.
{wait}

[msg F045_AREA29_IZA004 speaker 5] // Izanagi
{F2 08 FF FF}{speed 6}{name 0}, please accept
our gift.
{wait}
---
{F2 08 FF FF}It will help you create a new world
in this space filled with chaos,
{wait}
---
{F2 08 FF FF}as Izanami and I did when we met
long ago...
{wait}

[msg F045_AREA29_IZA005]
{F2 08 FF FF}{speed 6}> Your body surges with power...
{wait}

[msg F045_AREA29_IZA005_002]
{F2 08 FF FF}{speed 6}> You are now able to attack
more often.
{wait}

[msg F045_AREA29_IZA006 speaker 4] // Izanami
{F2 08 FF FF}{speed 6}Farewell, {name 0}.
{wait}
---
{F2 08 FF FF}Our job is done.
We pray for your success.
{wait}

[msg F045_AREA29_IZA007 speaker 6] // Izanagi and Izanami
{F2 08 FF FF}{speed 6}May the heavens bless you...
{wait}

[msg F045_AREA30_ROSINSI00]
{F2 08 FF FF}{speed 6}> You find yourself in
a strange place.
{wait}

[msg F045_AREA30_ROSINSI01]
{F2 08 FF FF}{speed 6}> A voice echoes in your head...
{wait}

[msg F045_AREA30_ROSINSI02 speaker 7] // Voice
{F2 08 FF FF}{speed 6}...Come...
{wait}
---
{F2 08 FF FF}...Show me... the strength...
of a demon...
{wait}

[msg F045_AREA30_ROSINSI03]
{F2 08 FF FF}{speed 6}> The old man and the woman
disappeared...
{wait}

[msg F045_AREA30_ROSINSI04 speaker 7] // Voice
{F2 08 FF FF}{speed 6}...This way...
{wait}

[msg F045_AREA30_ROSINSI05 speaker 7] // Voice
{F2 08 FF FF}{speed 6}...So, you made it...
{wait}

[msg F045_AREA30_ROSINSI06 speaker 7] // Voice
{F2 08 FF FF}{speed 6}...Your strength... is outstanding...
{wait}

[msg F045_AREA30_ROSINSI07 speaker 7] // Voice
{F2 08 FF FF}{speed 6}...We shall meet again... soon...
{wait}

[msg F045_AREA30_KUROJAKU speaker 8] // Dr. Dark
{F2 08 FF FF}{speed 6}By my master's orders,
I'll treat your wounds.
{wait}

[msg F045_AREA30_KAIFUKU02]
{F2 08 FF FF}{speed 6}> Dr. Dark healed your party.
{wait}

[msg F045_AREA28_KERU_LETSGO speaker 9] // Voice of Cerberus
{F2 08 FF FF}{speed 6}GO ON...
THEY ARE WAITING FOR YOU.
{wait}

[msg EXITWARP]
{F2 08 FF FF}{speed 6}> Will you leave the area?
{wait}

[sel EXITWARP_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg HOSEKI]
{F2 08 FF FF}{speed 6}> There is a Mystical Chest.
Will you open it?
{wait}

[sel HOSEKI_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg HOSEKI_NOGET]
{F2 08 FF FF}{speed 6}> You did not open
the Mystical Chest.
{wait}

[msg HOSEKI_GET]
{F2 08 FF FF}{speed 6}> You obtained
{color 4}{var 0}{color 0} x {var 1}.
{wait}

[msg TAKARA]
{F2 08 FF FF}{speed 6}> You see a Cache Cube.
Will you open it?
{wait}

[sel TAKARA_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg TAKARA_NOGET]
{F2 08 FF FF}{speed 6}> You did not open
the Cache Cube.
{wait}

[msg TAKARA_STILLGET]
{F2 08 FF FF}{speed 6}> It's empty.
{wait}

[msg TAKARA_GET]
{F2 08 FF FF}{speed 6}> You obtained
{color 4}{var 0}{color 0} x {var 1}.
{wait}

[msg TAKARA_DH_GET]
{F2 08 FF FF}{speed 6}> You obtained
the Magatama {color 4}{var 0}{color 0}.
{wait}

[msg TAKARA_MAKA_GET]
{F2 08 FF FF}{speed 6}> You obtained
{color 4}{var 0} Macca{color 0}.
{wait}

[msg TAKARA_DAMAGE]
{F2 08 FF FF}{speed 6}> It's a trap.
{wait}
---
{F2 08 FF FF}> Your party took damage.
{wait}

[msg TAKARA_KARAGET]
{F2 08 FF FF}{speed 6}> It's empty.
{wait}

[msg TAKARASAGASI]
{F2 08 FF FF}{speed 6}> {var 2} found something.
{wait}
---
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}> You obtained
{color 4}{var 0}{color 0} x {var 1}.
{wait}

[msg COMP_OPENERROR]
{F2 08 FF FF}{speed 6}> It can't be used here.
{wait}

[msg COMP_LIGHTMAEND]
{F2 08 FF FF}{speed 6}> The effect of Light wore off.
{wait}

[msg COMP_ESTOMAEND]
{F2 08 FF FF}{speed 6}> The effect of Repel wore off.
{wait}

[msg COMP_REBERAMAEND]
{F2 08 FF FF}{speed 6}> The effect of Attract wore off.
{wait}

[msg COMP_REFUTOMAEND]
{F2 08 FF FF}{speed 6}> The effect of Levitation wore off.
{wait}

[msg WARP_ELV_MSG]
{F2 08 FF FF}{speed 6}> Select a floor.
{wait}

[sel WARP_ELV_SEL1]
{F2 08 FF FF}{var 0}[80EA]
---
{F2 08 FF FF}Quit.

[sel WARP_ELV_SEL2]
{F2 08 FF FF}{var 1}[80EA]
---
{F2 08 FF FF}{var 0}[80EA]
---
{F2 08 FF FF}Quit.

[sel WARP_ELV_SEL3]
{F2 08 FF FF}{var 2}[80EA]
---
{F2 08 FF FF}{var 1}[80EA]
---
{F2 08 FF FF}{var 0}[80EA]
---
{F2 08 FF FF}Quit.

[sel WARP_ELV_SEL4]
{F2 08 FF FF}{var 3}[80EA]
---
{F2 08 FF FF}{var 2}[80EA]
---
{F2 08 FF FF}{var 1}[80EA]
---
{F2 08 FF FF}{var 0}[80EA]
---
{F2 08 FF FF}Quit.

[sel WARP_ELV_SEL5]
{F2 08 FF FF}{var 4}[80EA]
---
{F2 08 FF FF}{var 3}[80EA]
---
{F2 08 FF FF}{var 2}[80EA]
---
{F2 08 FF FF}{var 1}[80EA]
---
{F2 08 FF FF}{var 0}[80EA]
---
{F2 08 FF FF}Quit.

[sel WARP_ELV_SEL6]
{F2 08 FF FF}{var 5}[80EA]
---
{F2 08 FF FF}{var 4}[80EA]
---
{F2 08 FF FF}{var 3}[80EA]
---
{F2 08 FF FF}{var 2}[80EA]
---
{F2 08 FF FF}{var 1}[80EA]
---
{F2 08 FF FF}{var 0}[80EA]
---
{F2 08 FF FF}Quit.

[msg INFTEST0]
{F2 08 FF FF}{speed 6}> Message Test.
First, the basics...
{wait}

[msg INFTEST1]
{F2 08 FF FF}{speed 6}> Message Test.
Next are the choices...
{wait}

[sel INFTEST1_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg INFTEST1_YES]
{F2 08 FF FF}{speed 6}Yes, you say?
{wait}

[msg INFTEST1_NO]
{F2 08 FF FF}{speed 6}No, you say?
{wait}

[msg F045_DOOR01]
{F2 08 FF FF}{speed 6}> The path is blocked.
{wait}

[msg F045_DOOR02]
{F2 08 FF FF}{speed 6}> You sense a strong power from
beyond the door.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F045_DOOR02_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F041_AREA9_KUROJAKU speaker 8] // Dr. Dark
{F2 08 FF FF}{speed 6}It's natural for every living thing
to die... Therefore, medical
treatment contradicts nature.
{wait}
---
{F2 08 FF FF}So... Did you come here to defy
nature and be treated?
{wait}

[sel F041_AREA9_DR_SEL]
{F2 08 FF FF}No.
---
{F2 08 FF FF}Yes.

[msg F041_AREA9_KUROJAKU_YES speaker 8] // Dr. Dark
{F2 08 FF FF}{speed 6}Good. One lives, one dies...
That's the way it should be.
{wait}
---
{F2 08 FF FF}I pray that you find rest soon.
{wait}

[msg F041_AREA9_KUROJAKU_KAIH speaker 8] // Dr. Dark
{F2 08 FF FF}{speed 6}...I am a doctor, after all.
I'll treat your wounds.
{wait}
---
{F2 08 FF FF}But, I'm gonna charge you
{var 0} Macca. Alright?
{wait}

[msg F041_AREA9_KUROJAKU_KAIH]
{F2 08 FF FF}{speed 6}> ......
{wait}
---
{F2 08 FF FF}> Dr. Dark healed your party.
{wait}

[msg F041_AREA9_KUROJAKU_NOMO speaker 8] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}Money first. Get outta here.
{wait}

[msg MSG_F45_A13_AKUMA01 speaker 10] // Demon
{F2 08 FF FF}{speed 6}The angels cast down from heaven
had no other choice but to become
demons...
{wait}
---
{F2 08 FF FF}Are we fallen ones to blame...?
Or is it the fault of those who cast
us down...?
{wait}
---
{F2 08 FF FF}I wonder what our master thinks...
{wait}
---
{F2 08 FF FF}I'd like to ask him one of these days.
{wait}

[msg MSG_F45_A21_MEIROBABA01 speaker 10] // Demon
{F2 08 FF FF}{speed 6}I hear that you can buy demons
with unique abilities somewhere
around here...
{wait}
---
{F2 08 FF FF}But, now I'm lost. What to do...?
{wait}

[msg MSG_F45_A5_AKUMA01 speaker 10] // Demon
{F2 08 FF FF}{speed 6}So, you have made it to
the last floor.
{wait}
---
{F2 08 FF FF}This is where the women loyal to
our master gather.
{wait}
---
{F2 08 FF FF}You have done well in not
disappointing him.
{wait}
---
{F2 08 FF FF}But, if you underestimate us,
you will not live to regret it!
{wait}

[msg MSG_F45_A5_AKUMA02 speaker 10] // Demon
{F2 08 FF FF}{speed 6}What a cute lad! It's rare for young
men to come here.
{wait}
---
{F2 08 FF FF}I'm about to burst!
{wait}
---
{F2 08 FF FF}*sigh* ...I bet I'm nothing but
an old hag to you, right?
{wait}

[sel KAIWA_SEL]
{F2 08 FF FF}More like an 'old bag'.
---
{F2 08 FF FF}Not in the least.

[msg MSG_F45_A5_AKUMA02_02 speaker 10] // Demon
{F2 08 FF FF}{speed 6}You made my day! Here's a token
of my appreciation!
{wait}

[msg MSG_F45_A5_AKUMA02_03 speaker 10] // Demon
{F2 08 FF FF}{speed 6}Is that so...?
{wait}
---
{F2 08 FF FF}You know, it wouldn't kill ya to
throw a compliment my way.
{wait}
---
{F2 08 FF FF}It's called 'being nice', you little
creep.
{wait}

[msg MSG_F45_A5_AKUMA02_04 speaker 10] // Demon
{F2 08 FF FF}{speed 6}Now, don't let anything happen to
that cute little face!
{wait}

[msg MSG_F45_A5_AKUMA02_05]
{F2 08 FF FF}{speed 6}> The demon healed you.
{wait}

[msg MSG_F45_A5_SINEN02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}You're almost to the very bottom
of the Labyrinth.
{wait}
---
{F2 08 FF FF}Our master is waiting there.
Don't give up now!
{wait}

[msg MSG_F45_A5_SINEN04 speaker 3] // Soul
{F2 08 FF FF}{speed 6}You better pay close attention,
or you'll get lost.
{wait}
---
{F2 08 FF FF}Even if you think you've found
a dead-end, make absolutely sure
before you try another direction.
{wait}
---
{F2 08 FF FF}Well, that's my advice. Choose to
follow it if you wish.
{wait}

[msg MSG_F45_A14_SINEN01 speaker 10] // Demon
{F2 08 FF FF}{speed 6}Somewhere in here are doors that
will test your demons.
{wait}
---
{F2 08 FF FF}They test various attributes and
may even kill a demon if they are
inclined to do so.
{wait}
---
{F2 08 FF FF}Some will ask for specific demons.
{wait}
---
{F2 08 FF FF}If you want to go on ahead,
be sure to bring a variety of demons
with you.
{wait}

[msg MSG_F45_A14_SINEN02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}It seems that this floor is full
of demons that live by the call
of the wild.
{wait}
---
{F2 08 FF FF}Wild or not, they're still dangerous.
If you're going to look around,
be on your guard.
{wait}

[msg MSG_F45_A16_AKUMA01 speaker 10] // Demon
{F2 08 FF FF}{speed 6}Everybody here is waiting for
the final battle.
{wait}
---
{F2 08 FF FF}At our master's command, we will
rise to the heavens once again.
{wait}

[msg MSG_F45_A18_AKUMA01 speaker 10] // Demon
{F2 08 FF FF}{speed 6}CAN YOU FEEL IT?
{wait}
---
{F2 08 FF FF}I CAN FEEL GREAT POWER
FROM THIS DOOR,
WHICH LEADS BELOW...
{wait}
---
{F2 08 FF FF}SOMETHING EVEN STRONGER
THAN BEELZEBUB...
{wait}
---
{F2 08 FF FF}IF YOU CHOOSE TO PROCEED,
BE CAREFUL.
{wait}

[msg MSG_F45_A18_AKUMA02 speaker 10] // Demon
{F2 08 FF FF}{speed 6}CAN YOU FEEL IT?
{wait}
---
{F2 08 FF FF}THE GREAT POWER I FELT
IS GONE...
{wait}
---
{F2 08 FF FF}I CANNOT BELIEVE THERE IS
ONE WHO IS EVEN STRONGER!
{wait}

[msg MSG_F45_A16_SINEN002 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Human... or demon...
O one with power.
{wait}
---
{F2 08 FF FF}Would you like me to measure
the movements of your soul?
{wait}

[sel F045_SINEN_SEL]
{F2 08 FF FF}Sure, go ahead.
---
{F2 08 FF FF}No thanks.

[msg MSG_F45_A16_SINEN002_001 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Imagine you are in the mountains...
{wait}
---
{F2 08 FF FF}...and you see a human about to be
attacked by a wild animal.
{wait}
---
{F2 08 FF FF}The animal begins to maul
the defenseless human!
{wait}
---
{F2 08 FF FF}As a fellow human, your heart would
compel you to chase away the beast
and rescue the victim.
{wait}
---
{F2 08 FF FF}Ah...! But, now you're a demon!
{wait}
---
{F2 08 FF FF}Suppose you kill the animal with
your newfound strength...
You crush it barehanded!
{wait}
---
{F2 08 FF FF}The human would then fear you,
since you had proven yourself more
powerful than a wild animal!
{wait}
---
{F2 08 FF FF}With your demonic strength, you can
no longer be human. You are more
dangerous than a wild animal...
{wait}

[msg MSG_F45_A16_SINEN002_002 speaker 3] // Soul
{F2 08 FF FF}{speed 6}It is your choice. Do as your heart
desires.
{wait}

[msg MSG_045_SINEN_X speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}...If you get stronger...
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
{wait}

[msg F041_SINEN_X speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}...I'm glad you made it here.
{wait}
---
{F2 08 FF FF}...If you get stronger...
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
{wait}

[msg F041_SINEN_X2 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}...I've got nothing else to sell you.
...Hey, don't worry.
{wait}
---
{F2 08 FF FF}I'm sure there are other brokers
besides me in this labyrinth.
{wait}

[msg F041_SINEN_LEV001 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}...You're pretty strong.
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
Interested?
{wait}

[msg F041_SINEN_DAM speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}...On second thought, forget what
I just said.
{wait}
---
{F2 08 FF FF}The demon you have there...
Yeah, the one with only one eye...
{wait}
---
{F2 08 FF FF}As long as you've got that demon
with you, I can't sell you mine.
Come back after you get rid of it.
{wait}

[msg F041_SINEN_LEV002 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}...You're pretty strong.
{wait}
---
{F2 08 FF FF}I'll sell you something special.
{wait}
---
{F2 08 FF FF}Wait a minute, your party's full.
{wait}
---
{F2 08 FF FF}If you want a new companion,
make some room first and then
come back.
{wait}

[msg F041_SINEN_LEV003 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}Here's what I'm selling...
{wait}
---
{F2 08 FF FF}...the strongest elephant you
ever saw, with the power of
a demon.
{wait}
---
{F2 08 FF FF}In battle, he'll bust out attacks
that'll crush any enemy!
{wait}
---
{F2 08 FF FF}I'm asking 200000 Macca.
I know it's kinda high, but it's well
worth the price... So, you want it?
{wait}

[sel F041_SINEN_LEV003_SEL]
{F2 08 FF FF}Alright, I'll buy it.
---
{F2 08 FF FF}No thanks.

[msg F041_SINEN_LEV004 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}Excellent choice!
{wait}

[msg F041_SINEN_LEV005]
{F2 08 FF FF}{speed 6}> You purchased a demon from
the Shady Broker.
{wait}

[msg F041_SINEN_LEV006 speaker 10] // Demon
{F2 08 FF FF}{speed 6}...WoOo, I'm... MaSAKadO... sSssS!
{wait}
---
{F2 08 FF FF}NiCE tO mEEt yoUuUUuuu...
{wait}

[msg F041_SINEN_LEV007]
{F2 08 FF FF}{speed 6}> The demon is jiggling...
{wait}

[msg F041_SINEN_LEVIRANAI speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}That's fine. If you change your mind,
feel free to come back anytime.
{wait}

[msg F041_SINEN_KANE speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}Hey, you don't have enough Macca!
{wait}
---
{F2 08 FF FF}Come back when you have more
money, okay?
{wait}

[msg MSG_F45_A26_SINEN001 speaker 3] // Soul
{F2 08 FF FF}{speed 6}At our master's request, I have been
waiting for you...
{wait}
---
{F2 08 FF FF}Yours is an existence unbound by 
this world, and for that reason, 
you have infinite potential.
{wait}
---
{F2 08 FF FF}Will the battle with god occur as
our master wishes...?
{wait}
---
{F2 08 FF FF}Or, will we forever remain in waiting,
while history repeats itself?
{wait}
---
{F2 08 FF FF}...I have thought about this at great
length. May I ask you a question?
{wait}

[sel F045_A26_SINEN_SEL]
{F2 08 FF FF}Go ahead.
---
{F2 08 FF FF}No, you may not.

[msg MSG_F45_A26_SINEN001_001 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Very well.
{wait}
---
{F2 08 FF FF}It is true that all living things
must perish...
{wait}
---
{F2 08 FF FF}Bound by the invisible threads of
fate, humans die tragic deaths...
{wait}
---
{F2 08 FF FF}Does that seem fair to you?
{wait}
---
{F2 08 FF FF}If you lost a loved one in a horrible
accident, would you curse god?
{wait}
---
{F2 08 FF FF}..................
{wait}
---
{F2 08 FF FF}There's no need to answer.
{wait}
---
{F2 08 FF FF}But, if you feel that fate has
cheated you... then go and see
our master.
{wait}
---
{F2 08 FF FF}Yes... Though long frozen,
time shall flow again...
{wait}
---
{F2 08 FF FF}...towards the final battle.
{wait}

[msg MSG_F45_A26_SINEN001_002 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...I see. Then, I will leave you be.
{wait}
---
{F2 08 FF FF}I pray that you may determine your
own destiny.
{wait}

