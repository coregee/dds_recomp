// messages of fld/f/f043/f043
[speaker 0] Debug message
[speaker 1] Voice of the lady in black
[speaker 2] Dante's voice
[speaker 3] Voice of the door
[speaker 4] White knight
[speaker 5] Red knight
[speaker 6] Black knight
[speaker 7] Pale knight
[speaker 8] Soul
[speaker 9] Mysterious voice
[speaker 10] Black Frost
[speaker 11] Shady Broker
[speaker 12] Dr. Dark
[speaker 13] Demon

[sel YN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F043_DEBBUG]
{F2 08 FF FF}{speed 6}> Add which candelabrum to
your inventory?
{wait}

[sel F043_DEBBUG_SEL]
{F2 08 FF FF}Compassion
---
{F2 08 FF FF}Wisdom
---
{F2 08 FF FF}Insight
---
{F2 08 FF FF}All
---
{F2 08 FF FF}Nothing

[msg F043_DEBBUG2 speaker 0] // Debug message
{F2 08 FF FF}{speed 6}What do you want to do?
{wait}

[sel F043_DEBBUG2_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Kin-Ki flag on
---
{F2 08 FF FF}Sui-Ki flag on
---
{F2 08 FF FF}Fuu-Ki flag on
---
{F2 08 FF FF}All of the above
---
{F2 08 FF FF}Nothing

[sel F043_DEBBUG3_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Ongyo-Ki flag on
---
{F2 08 FF FF}Mara flag on
---
{F2 08 FF FF}Black Frost flag on
---
{F2 08 FF FF}All of the above
---
{F2 08 FF FF}Nothing

[msg F043_CLOSE_DOOR1]
{F2 08 FF FF}{speed 6}> The hole is blocked...
{wait}

[msg F043_CLOSE_DOOR2]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F043_SHAFT_Q]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F043_SHAFT_ENT]
{F2 08 FF FF}{speed 6}> Return to the entrance
of the Labyrinth?
{wait}

[msg F043_SHAFT_UP]
{F2 08 FF FF}{speed 6}> Return to the previous Kalpa?
{wait}

[msg MSG_001]
{F2 08 FF FF}{speed 6}> There is a huge pedestal.
{wait}

[msg MSG_001_2]
{F2 08 FF FF}{speed 6}> You do not have a candelabrum
for this pedestal...
{wait}

[msg MSG_002_JIHI]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Compassion{color 0}?
{wait}

[msg MSG_002_CHIE]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Wisdom{color 0}?
{wait}

[msg MSG_002_RIKAI]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Insight{color 0}?
{wait}

[sel STOKERE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg MSG_003_JIHI]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Compassion{color 0}.
{wait}

[msg MSG_003_CHIE]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Wisdom{color 0}.
{wait}

[msg MSG_003_RIKAI]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Insight{color 0}.
{wait}

[msg MSG_003B]
{F2 08 FF FF}{speed 6}> All of the candelabra
have been lit...
{wait}

[msg MSG_006]
{F2 08 FF FF}{speed 6}> The flames illuminate the passage
beyond.
{wait}

[msg MSG_ANA010]
{F2 08 FF FF}{speed 6}> There is a peephole...
{wait}
---
{F2 08 FF FF}> Will you look through it?
{wait}

[msg MSG_001_010 speaker 1] // Voice of the lady in black
{F2 08 FF FF}{speed 6}Please retrieve the next set
of Candelabra and return them
to the Labyrinth.
{wait}
---
{F2 08 FF FF}We are deeply grateful for
your work.
{wait}

[msg MSG_002_010]
{F2 08 FF FF}{speed 6}> The voice of the lady in black
can be heard through the peephole...
{wait}

[msg MSG_003_010]
{F2 08 FF FF}{speed 6}> The lady's voice could no longer
be heard.
{wait}

[msg MSG_003_DANTE_GO]
{F2 08 FF FF}{speed 6}> Dante exited through the door...
{wait}

[msg MSG_003_DANTE_GO2]
{F2 08 FF FF}{speed 6}> Dante exited through the door...
{wait}

[msg MSG_004_DANTE_01]
{F2 08 FF FF}{speed 6}> It seems as if someone
is watching you...
{wait}

[msg MSG_004_DANTE_02 speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}Hey kid... Didn't I tell you
to lay low?
{wait}
---
{F2 08 FF FF}Playtime's over. Now...
{wait}
---
{F2 08 FF FF}Let's rock!
{wait}

[msg MSG_004_DANTE_03 speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}...Don't disappoint me.
{wait}

[msg MSG_005_DANTE_01 speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}...A game's no fun if you
don't know the rules.
So, here's the deal...
{wait}
---
{F2 08 FF FF}To get past here,
you need to turn on
all the {color 1}switches{color 0} first.
{wait}
---
{F2 08 FF FF}Alright, I'm gonna count to three.
That's how long you've got
to come up with a plan.
{wait}

[msg MSG_005_DANTE_02 speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}One...
{wait}

[msg MSG_005_DANTE_03 speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}Two...
{wait}

[msg MSG_005_DANTE_04 speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}...Three!
{wait}

[msg DANTE_SWITCH_Q]
{F2 08 FF FF}{speed 6}> There is a switch.
Will you activate it?
{wait}

[msg DANTE_SWITCH_DONE]
{F2 08 FF FF}{speed 6}> The switch has been activated.
{wait}

[msg MSG_012_BATTLE_AFTER]
{F2 08 FF FF}{speed 6}> Dante left...
{wait}

[msg JOKEN_SYSTEM_01]
{F2 08 FF FF}{speed 6}> The door is tightly shut...
{wait}

[msg JOKEN_SYSTEM_02]
{F2 08 FF FF}{speed 6}> Will you try to open it?
{wait}

[msg JOKEN_CHK_POW_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Before I allow you to pass through,
I shall test your strength.
{wait}

[msg JOKEN_CHK_MAG_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Before I allow you to pass through,
I shall test your magic.
{wait}

[msg JOKEN_CHK_LUK_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Before I allow you to pass through,
I shall test your luck.
{wait}

[msg JOKEN_NG_POW_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}I cannot let one with such feeble
strength pass through!
{wait}

[msg JOKEN_NG_MAG_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}I cannot let one with such weak
magic pass through!
{wait}

[msg JOKEN_NG_LUK_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}I cannot let one with such meager
luck pass through!
{wait}

[msg JOKEN_OK_POW_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Your strength is worthy of praise!
You may pass.
{wait}

[msg JOKEN_OK_MAG_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Your magic is worthy of praise!
You may pass.
{wait}

[msg JOKEN_OK_LUK_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Your luck is worthy of praise!
You may pass.
{wait}

[msg FIRE_YURE]
{F2 08 FF FF}{speed 6}> The flames of the {color 1}Candelabrum
of Sovereignty{color 0} are flickering wildly...
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

[msg KINKI_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Kin-Ki:
Defeated in {var 0} turn(s)."
{wait}

[msg KINKI_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Kin-Ki:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg KINKI_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Kin-Ki."
{wait}

[msg KINKI_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Kin-Ki...
{wait}

[msg SUIKI_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Sui-Ki:
Defeated in {var 0} turn(s)."
{wait}

[msg SUIKI_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Sui-Ki:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg SUIKI_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Sui-Ki."
{wait}

[msg SUIKI_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Sui-Ki...
{wait}

[msg FUUKI_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Fuu-Ki:
Defeated in {var 0} turn(s)."
{wait}

[msg FUUKI_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Fuu-Ki:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg FUUKI_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Fuu-Ki."
{wait}

[msg FUUKI_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Fuu-Ki...
{wait}

[msg ONGYO_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Ongyo-Ki:
Defeated in {var 0} turn(s)."
{wait}

[msg ONGYO_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Ongyo-Ki:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg ONGYO_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Ongyo-Ki."
{wait}

[msg ONGYO_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Ongyo-Ki...
{wait}

[msg MAARA_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Mara:
Defeated in {var 0} turn(s)."
{wait}

[msg MAARA_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Mara:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg MAARA_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Mara."
{wait}

[msg MAARA_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Mara...
{wait}

[msg JAAKU_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Black Frost:
Defeated in {var 0} turn(s)."
{wait}

[msg JAAKU_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Black Frost:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg JAAKU_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Black Frost."
{wait}

[msg JAAKU_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Black Frost...
{wait}

[msg FOUR_SYSTEM_01]
{F2 08 FF FF}{speed 6}> The flames of the {color 1}Candelabrum
of Sovereignty{color 0} started to flicker
wildly...
{wait}
---
{F2 08 FF FF}> You feel a terrifying presence
in the air...
{wait}

[msg FOUR_W_RIDER_01 speaker 4] // White knight
{F2 08 FF FF}{speed 6}...Well met, you who was once
human.
{wait}
---
{F2 08 FF FF}The moment you stepped into
this Labyrinth, the wheel of fate
began to spin...
{wait}

[msg FOUR_R_RIDER_01 speaker 5] // Red knight
{F2 08 FF FF}{speed 6}Time is a loop that repeats itself.
{wait}
---
{F2 08 FF FF}But, we serve the fallen angel
in order to rise above that fate.
{wait}
---
{F2 08 FF FF}You wish for the same thing,
do you not?
{wait}

[msg FOUR_B_RIDER_01 speaker 6] // Black knight
{F2 08 FF FF}{speed 6}...We know that thou art on a quest
to retrieve the candelabra.
{wait}
---
{F2 08 FF FF}We, the four knights of death,
have what thou seekest.
{wait}
---
{F2 08 FF FF}Thine they shall be,
if thou canst triumph over us.
{wait}

[msg FOUR_P_RIDER_01 speaker 7] // Pale knight
{F2 08 FF FF}{speed 6}{name 0}, the Demi-fiend...
{wait}
---
{F2 08 FF FF}You have conquered a number
of deaths to reach here.
{wait}
---
{F2 08 FF FF}Whether it be you, or one of us...
{wait}
---
{F2 08 FF FF}...it is our master's wish that
one Fiend survives this battle
over the candelabra.
{wait}

[msg FOUR_P_RIDER_02 speaker 7] // Pale knight
{F2 08 FF FF}{speed 6}And when his wish comes true...
{wait}
---
{F2 08 FF FF}...he shall make the decision to
lead his army to the final battle.
{wait}

[msg FOUR_P_RIDER_03 speaker 7] // Pale knight
{F2 08 FF FF}{speed 6}Do you have the resolve to face us
in battle?
{wait}
---
{F2 08 FF FF}Even if it may cost you what is left
of your humanity?
{wait}

[sel FOUR_P_RIDER_SEL]
{F2 08 FF FF}My mind's made up.
---
{F2 08 FF FF}I've had enough.

[msg FOUR_P_RIDER_04_YES speaker 7] // Pale knight
{F2 08 FF FF}{speed 6}Very well. That is just the answer
we were expecting.
{wait}
---
{F2 08 FF FF}...Then, show us the strength that
our master stakes our fate on.
{wait}
---
{F2 08 FF FF}We, the four knights of death,
shall await you in the Vortex World.
{wait}

[msg FOUR_P_RIDER_04_NO speaker 7] // Pale knight
{F2 08 FF FF}{speed 6}...Then, we are through with you.
{wait}
---
{F2 08 FF FF}The wish of our master,
and of all the demons of chaos...
shall never be realized.
{wait}
---
{F2 08 FF FF}Nevertheless, your betrayal cannot
be forgiven.
{wait}
---
{F2 08 FF FF}Prepare for your doom!
{wait}
---
{F2 08 FF FF}The four knights of death shall
claim your head! We await you
in the Vortex World!
{wait}

[msg FOUR_SYSTEM_02]
{F2 08 FF FF}{speed 6}> The four horsemen disappeared...
{wait}

[msg ZOKUSEI_SYSTEM_01]
{F2 08 FF FF}{speed 6}> The door is tightly shut...
{wait}

[msg ZOKUSEI_SYSTEM_02]
{F2 08 FF FF}{speed 6}> ......
{wait}
---
{F2 08 FF FF}> The door would not budge...
{wait}

[msg ZOKUSEI_NG_N_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Only one loyal to neither light
nor darkness may pass...
{wait}

[msg ZOKUSEI_NG_L_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Only a servant of light may pass...
{wait}

[msg ZOKUSEI_NG_D_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Only a servant of darkness
may pass...
{wait}

[msg ZOKUSEI_OK_N_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Glory be to the demon who walks
the path untouched by both light
and darkness...
{wait}

[msg ZOKUSEI_OK_L_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Glory be to the demon of light...
{wait}

[msg ZOKUSEI_OK_D_DOOR speaker 3] // Voice of the door
{F2 08 FF FF}{speed 6}Glory be to the demon of darkness...
{wait}

[msg BOTTAKURI_01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}Gee, you look worn out.
{wait}
---
{F2 08 FF FF}Would you like to rest for a while?
Only 500 Macca!
{wait}

[msg BOTTAKURI_NO speaker 8] // Soul
{F2 08 FF FF}{speed 6}Oh... Well, please come again!
{wait}

[msg BOTTAKURI_NOMONEY speaker 8] // Soul
{F2 08 FF FF}{speed 6}Oh, you don't have enough Macca...
Come back when you do.
{wait}

[msg BOTTAKURI_YES_01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}You must be thirsty.
Here, have a drink...
{wait}

[msg BOTTAKURI_YES_02]
{F2 08 FF FF}{speed 6}> Your party recovered.
{wait}

[msg BOTTAKURI_YES_03 speaker 8] // Soul
{F2 08 FF FF}{speed 6}Go ahead, have some more...
{wait}

[msg BOTTAKURI_YES_04 speaker 8] // Soul
{F2 08 FF FF}{speed 6}Are you feeling better?
Here's some more...
{wait}

[msg BOTTAKURI_YES_05]
{F2 08 FF FF}{speed 6}> Your party recovered some more.
{wait}

[msg BOTTAKURI_YES_06 speaker 8] // Soul
{F2 08 FF FF}{speed 6}...Have... another... drink...


[msg BOTTAKURI_YES_07]
{F2 08 FF FF}{speed 6}> Your wallet feels really light...
{wait}

[msg FROST_001]
{F2 08 FF FF}{speed 6}> You hear a voice...
{wait}

[msg FROST_002 speaker 9] // Mysterious voice
{F2 08 FF FF}{speed 6}Heeeeee hoooooo!
I guess I'm a little too late.
{wait}

[msg FROST_003 speaker 9] // Mysterious voice
{F2 08 FF FF}{speed 6}I tried so hard to get here, too!
{wait}

[msg FROST_004 speaker 10] // Black Frost
{F2 08 FF FF}{speed 6}You do remember me, right?
{wait}
---
{F2 08 FF FF}The "Emperor of Kabukicho"
has finally made his comeback!!
{wait}

[msg FROST_005 speaker 10] // Black Frost
{F2 08 FF FF}{speed 6}Um, if you're wondering how
I managed to make a comeback...
{wait}
---
{F2 08 FF FF}{speed 3}...that's a secret.
{wait}
---
{F2 08 FF FF}Don't ask me why I shrank in size,
either. Okay, hee ho?
{wait}

[msg FROST_006 speaker 10] // Black Frost
{F2 08 FF FF}{speed 6}Anyway, once again I'm aiming
to be the best!
{wait}
---
{F2 08 FF FF}If I tag along with you, hee ho,
I think I can become super-cool
and super-strong!
{wait}
---
{F2 08 FF FF}So, let's go! Heeeeee hoooooo!!
{wait}

[msg FROST_IRU speaker 10] // Black Frost
{F2 08 FF FF}{speed 6}Anyway, once again I'm aiming
to be the best!
{wait}
---
{F2 08 FF FF}If I tag along with you, hee ho,
I think I can become super-cool
and super-strong!
{wait}
---
{F2 08 FF FF}So, let's...
{wait}
---
{F2 08 FF FF}What the!?
I'm in your party already!
Ho noooooo!
{wait}
---
{F2 08 FF FF}I'm no use to you...?
Fine, be that way!
I'm going home!!
{wait}

[msg FROST_007]
{F2 08 FF FF}{speed 6}> Black Frost joined you without
your consent...
{wait}

[msg FROST_IRU002]
{F2 08 FF FF}{speed 6}> Black Frost left...
{wait}

[msg FROST_008]
{F2 08 FF FF}{speed 6}> Black Frost couldn't join you
because your party was full...
{wait}

[msg FROST_009 speaker 10] // Black Frost
{F2 08 FF FF}{speed 6}Ho hee?! You have too many
demons with you! Why, hee ho!?
{wait}
---
{F2 08 FF FF}I'll wait for you, hee ho,
at the Cathedral of Shadows!
{wait}

[msg FROST_010]
{F2 08 FF FF}{speed 6}> Black Frost disappeared...
{wait}

[msg MSG_003_SANTE_MODOSARE speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}What's the matter, kid?
Tired already?
{wait}

[msg MSG_005_SANTE_MODOSARE speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}What's the matter, kid?
Tired already?
{wait}

[msg MSG_007_SANTE_MODOSARE speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}The game's not over yet...
I {color 1}reset{color 0} all the switches.
{wait}

[msg MSG_007_SANTE_MODOSARE2 speaker 2] // Dante's voice
{F2 08 FF FF}{speed 6}What's the matter, kid?
Tired already?
{wait}

[msg F041_A28_SITYOU_001 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}I recently got a hold of this rare
item, but nobody seems to
understand its value...
{wait}
---
{F2 08 FF FF}How about you? Would you be
interested in buying it?
{wait}
---
{F2 08 FF FF}This stone, called a Deathstone,
is supposed to bring death to you.
But, who knows? Maybe you'll find
a use for it.
{wait}
---
{F2 08 FF FF}You can have it for the bargain
price of 100000 Macca. Well,
how 'bout it?
{wait}

[msg F041_A28_SITYOU_002 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}Heheh, I knew you'd want it.
{wait}

[msg F041_A28_SITYOU_003 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}That's fine.
If you change your mind,
feel free to come back anytime.
{wait}

[msg F041_A28_SITYOU_004 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}I recently got a hold of this rare
item, but nobody seems to
understand its value...
{wait}
---
{F2 08 FF FF}I'd consider selling it to you,
if you were a little stronger.
{wait}
---
{F2 08 FF FF}I can tell you right now, though,
that it'll be expensive.
{wait}

[msg F041_A28_SITYOU_005 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}Hey hey hey, you don't have
enough Macca.
{wait}

[msg F041_A28_SITYOU_006]
{F2 08 FF FF}{speed 6}> You purchased the Deathstone
from the Shady Broker.
{wait}

[sel F041_A28_SITYOUSEKI_SEL]
{F2 08 FF FF}Alright, I'll buy it.
---
{F2 08 FF FF}No thanks.

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

[msg MSG_003_DANTE_01]
{F2 08 FF FF}{speed 6}> Will you break your promise
with Dante and proceed?
{wait}

[sel MSG_003_DANTE_01_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F043_DOOR01_01]
{F2 08 FF FF}{speed 6}> The door is locked...
{wait}

[msg F043_DOOR01_02]
{F2 08 FF FF}{speed 6}> You used the {color 1}Star Key{color 0}.
{wait}

[msg F043_KUROJAKU speaker 12] // Dr. Dark
{F2 08 FF FF}{speed 6}Do me a favor...
{wait}
---
{F2 08 FF FF}Don't bother me.
{wait}

[sel F043_DR_SEL]
{F2 08 FF FF}My pleasure.
---
{F2 08 FF FF}Sorry, but I need your help.

[msg F043_KUROJAKU_YES speaker 12] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}

[msg F043_KUROJAKU_KAIHUKU01 speaker 12] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}...Then, give me 10000 Macca.
If you don't like it, then go
somewhere else. So, do you want
my help or not?
{wait}

[msg F043_KUROJAKU_KAIHUKU02]
{F2 08 FF FF}{speed 6}> ......
{wait}
---
{F2 08 FF FF}> Dr. Dark healed your party.
{wait}

[msg MSG_F43_A15_AKUMA01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}I see hesitation in your heart.
{wait}
---
{F2 08 FF FF}Life or death... You must choose...
even if choice defies reason.
{wait}
---
{F2 08 FF FF}I can see it. Your inclination
is taking form...
{wait}
---
{F2 08 FF FF}Would you like to know why your
soul wavers?
{wait}

[sel F043_AKUMA_SEL]
{F2 08 FF FF}Tell me.
---
{F2 08 FF FF}I don't care.

[msg MSG_F43_A15_AKUMA02 speaker 8] // Soul
{F2 08 FF FF}{speed 6}Imagine that you're in a desert...
{wait}
---
{F2 08 FF FF}A turtle walks up to you.
{wait}
---
{F2 08 FF FF}You flip the turtle over, leaving it
on its back.
{wait}
---
{F2 08 FF FF}It struggles to right itself,
but to no avail. For what reason
did you flip the turtle?
{wait}
---
{F2 08 FF FF}You did so because of the distress
in your heart. The helpless turtle
is you!
{wait}
---
{F2 08 FF FF}If you look at things upside-down,
of course they will appear inverted.
{wait}
---
{F2 08 FF FF}Forget your worries and move on.
{wait}

[msg MSG_F43_A15_AKUMA03 speaker 8] // Soul
{F2 08 FF FF}{speed 6}I see. Then be on your way.
{wait}
---
{F2 08 FF FF}Your destination is predetermined;
it cannot be altered.
{wait}

[msg MSG_F43_A15_SINEN01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}"This is the story of a future
not so far off...
{wait}
---
{F2 08 FF FF}where death conquers death,
and fire lights the darkness...
{wait}
---
{F2 08 FF FF}The words of the beginning shall
be spoken.
{wait}
---
{F2 08 FF FF}...We all await those words."
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}I heard that from a demon in
the Labyrinth. I wonder what
it means...
{wait}

[msg F043_DOOR02]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F041_AREA9_KUROJAKU speaker 12] // Dr. Dark
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

[msg F041_AREA9_KUROJAKU_YES speaker 12] // Dr. Dark
{F2 08 FF FF}{speed 6}Good. One lives, one dies...
That's the way it should be.
{wait}
---
{F2 08 FF FF}I pray that you find rest soon.
{wait}

[msg F041_AREA9_KUROJAKU_KAIH speaker 12] // Dr. Dark
{F2 08 FF FF}{speed 6}...I'm a doctor, after all.
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

[msg F041_AREA9_KUROJAKU_NOMO speaker 12] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}Money first. Get outta here.
{wait}

[msg MSG_F43_A15_UN01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}The door up ahead will test your
luck.
{wait}
---
{F2 08 FF FF}If you're unlucky, you won't even be
able to set foot inside the room.
{wait}
---
{F2 08 FF FF}Even if you do manage to get in,
there's no telling where you'll
end up...
{wait}
---
{F2 08 FF FF}So, tell me... Are you feelin' lucky?
{wait}

[msg MSG_F43_A15_TIKARA01 speaker 13] // Demon
{F2 08 FF FF}{speed 6}Hold on! Are you planning to go
through that door?!
{wait}
---
{F2 08 FF FF}Dude, forget it. Only someone
strong like me can go in there!
{wait}
---
{F2 08 FF FF}A puny wimp like you won't be able
to get in.
{wait}
---
{F2 08 FF FF}There are more doors like it inside...
Even I can't get through some of
them!
{wait}
---
{F2 08 FF FF}If you wanna get in, you better build
some muscle. Right now, you're just
a little girlie-man.
{wait}

[msg MSG_F43_A15_MARYOKU01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}This floor has three types of special
doors.
{wait}
---
{F2 08 FF FF}You need a certain amount of
strength, luck or magic to enter
each door.
{wait}
---
{F2 08 FF FF}The door up ahead is one of them.
If you're going in, you better
be prepared.
{wait}

[msg MSG_F43_A15_SINENOBA01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}The Labyrinth of Amala used to have
some incredible treasure.
{wait}
---
{F2 08 FF FF}But, I heard some group stole it...
I don't know the details, though.
{wait}

[msg MSG_F43_A28_AKUMA01 speaker 13] // Demon
{F2 08 FF FF}{speed 6}Hee ho!
{wait}
---
{F2 08 FF FF}I saw an awesome dude with guns
and a giant sword mowing down
demons, hee ho!
{wait}
---
{F2 08 FF FF}It was terrifying!
{wait}

[msg MSG_F43_A28_AKUMA02 speaker 13] // Demon
{F2 08 FF FF}{speed 6}Hee ho!!
{wait}
---
{F2 08 FF FF}The Emperor has returned!!
{wait}
---
{F2 08 FF FF}I want his autograph, hee ho,
so I'm gonna go look for him!!
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
Yeah, that scary one with large
eyes...
{wait}
---
{F2 08 FF FF}As long as you've got that demon
with you, I can't sell you mine.
Come back after you get rid of it.
{wait}

[msg F041_SINEN_DAM02 speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}...On second thought, forget what
I just said.
{wait}
---
{F2 08 FF FF}The demon you have there...
Yeah, the one that looks like it's
always hungry...
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
{F2 08 FF FF}...Wait a minute, your party's full.
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
{F2 08 FF FF}...a demon with a body of steel.
It'll be useful in battle.
{wait}
---
{F2 08 FF FF}Nothing can harm this demon!
It can't even be scratched!
{wait}
---
{F2 08 FF FF}I'm asking 70000 Macca.
I know it's kinda high, but it's well
worth the price... So, you want it?
{wait}

[msg F041_SINEN_LEV003_LILIS speaker 11] // Shady Broker
{F2 08 FF FF}{speed 6}Here's what I'm selling...
{wait}
---
{F2 08 FF FF}...a demon of darkness with
a powerful skill...
{wait}
---
{F2 08 FF FF}I'm telling you, this one's got
some potential!
{wait}
---
{F2 08 FF FF}...I-I can't stress enough
the potential it has! I personally
recommend it!
{wait}
---
{F2 08 FF FF}I'm asking 150000 Macca.
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

[msg F041_SINEN_LEV006 speaker 13] // Demon
{F2 08 FF FF}{speed 6}I am Kaja Mitama.
{wait}
---
{F2 08 FF FF}With my magic, I can weaken
the enemy.
{wait}
---
{F2 08 FF FF}Let me know when I am needed.
{wait}

[msg F041_SINEN_LEV007]
{F2 08 FF FF}{speed 6}> The demon joined your party.
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

[msg MSG_DANTE_MITA01 speaker 8] // Soul
{F2 08 FF FF}{speed 6}Hey, you're not going on ahead,
are you?
{wait}
---
{F2 08 FF FF}If you are, you better be ready.
{wait}
---
{F2 08 FF FF}I saw a guy with guns and a huge
sword walk in not long ago.
{wait}

[msg MSG_DANTE_MITA02 speaker 8] // Soul
{F2 08 FF FF}{speed 6}Looks like you're safe. That's good
to know.
{wait}

