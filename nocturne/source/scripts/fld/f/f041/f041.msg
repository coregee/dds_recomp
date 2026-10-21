// messages of fld/f/f041/f041
[speaker 0] Debug message
[speaker 1] Voice of the lady in black
[speaker 2] Dr. Dark
[speaker 3] Soul
[speaker 4] Kamala
[speaker 5] Cerberus
[speaker 6] Demon
[speaker 7] Shady Broker

[sel YN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F041_DEBBUG speaker 0] // Debug message
{F2 08 FF FF}{speed 6}> Add Candelabrum of Foundation
to inventory?
{wait}

[msg F041_DEBBUG2 speaker 0] // Debug message
{F2 08 FF FF}{speed 6}What do you want to do?
{wait}

[sel F041_DEBBUG2_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Forneus flag on
---
{F2 08 FF FF}Troll flag on
---
{F2 08 FF FF}All of the above
---
{F2 08 FF FF}Cerberus flag on
---
{F2 08 FF FF}Hi Score flag on
---
{F2 08 FF FF}Nothing

[sel F041_DEBBUG2_SEL2]
{F2 08 FF FF}Black Visor
---
{F2 08 FF FF}Orthrus flag on
---
{F2 08 FF FF}Yaksini flag on
---
{F2 08 FF FF}All of the above
---
{F2 08 FF FF}Nothing

[msg MSG_001]
{F2 08 FF FF}{speed 6}> There is a huge pedestal.
{wait}

[msg MSG_001_2]
{F2 08 FF FF}{speed 6}> You do not have a candelabrum
for this pedestal...
{wait}

[msg MSG_011_010]
{F2 08 FF FF}{speed 6}> The switch has been activated.
{wait}

[msg MSG_002]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Foundation{color 0}?
{wait}

[sel STOKERE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg MSG_003]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Foundation{color 0}.
{wait}

[msg MSG_004]
{F2 08 FF FF}{speed 6}> You did not light the candelabrum.
{wait}

[msg MSG_003B]
{F2 08 FF FF}{speed 6}> The candelabrum has been lit...
{wait}

[msg MSG_006]
{F2 08 FF FF}{speed 6}> The flames illuminate the passage
beyond.
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

[msg F041_CLOSE_DOOR1]
{F2 08 FF FF}{speed 6}> The hole is blocked...
{wait}

[msg F041_CLOSE_DOOR2]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F041_SHAFT_Q]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F041_SHAFT_ENT]
{F2 08 FF FF}{speed 6}> Return to the entrance
of the Labyrinth?
{wait}

[msg MSG_ANA010]
{F2 08 FF FF}{speed 6}> There is a peephole...
{wait}
---
{F2 08 FF FF}> Will you look through it?
{wait}

[sel STOKERE_SEL2]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg MSG_SW_010]
{F2 08 FF FF}{speed 6}> There is a switch.
Will you activate it?
{wait}

[sel STOKERE_SEL3]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

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

[msg FOL_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Forneus:
Defeated in {var 0} turn(s)."
{wait}

[msg FOL_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Forneus:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg FOL_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Forneus."
{wait}

[msg FOL_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Forneus...
{wait}

[msg TROLL_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Troll:
Defeated in {var 0} turn(s)."
{wait}

[msg TROLL_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Troll:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg TROLL_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Troll."
{wait}

[msg TROLL_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Troll...
{wait}

[msg ORT_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Orthrus:
Defeated in {var 0} turn(s)."
{wait}

[msg ORT_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Orthrus:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg ORT_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Orthrus."
{wait}

[msg ORT_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Orthrus...
{wait}

[msg YAK_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Yaksini:
Defeated in {var 0} turn(s)."
{wait}

[msg YAK_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Yaksini:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg YAK_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Yaksini."
{wait}

[msg YAK_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Yaksini...
{wait}

[msg F041_AREA9_KUROJAKU speaker 2] // Dr. Dark
{F2 08 FF FF}{speed 6}It's natural for every living thing
to die... Treatment, therefore,
contradicts nature.
{wait}
---
{F2 08 FF FF}So... Did you come here to defy
nature and be treated?
{wait}

[sel F041_AREA9_DR_SEL]
{F2 08 FF FF}Of course not.
---
{F2 08 FF FF}Yes, I did.

[msg F041_AREA9_KUROJAKU_YES speaker 2] // Dr. Dark
{F2 08 FF FF}{speed 6}Good. One lives, one dies...
That's the way it should be.
{wait}
---
{F2 08 FF FF}I pray that you find rest soon.
{wait}

[msg F041_AREA9_KUROJAKU_KAIH speaker 2] // Dr. Dark
{F2 08 FF FF}{speed 6}...I am a doctor, after all.
I'll treat your wounds.
{wait}
---
{F2 08 FF FF}But, I'm gonna charge you
{var 0} Macca.
{wait}

[msg F041_AREA9_KUROJAKU_KAIH]
{F2 08 FF FF}{speed 6}> ......
{wait}
---
{F2 08 FF FF}> Dr. Dark healed your party.
{wait}

[msg F041_AREA9_KUROJAKU_NOMO speaker 2] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}Money first. Get outta here.
{wait}

[msg F041_AREA18_SINEN_X02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Hey, are you having difficulties?
{wait}

[msg F041_AREA18_SINEN_X02_NO speaker 3] // Soul
{F2 08 FF FF}{speed 6}Really...? Lucky you... *sigh*
{wait}

[msg F041_AREA18_SINEN_X02_YE speaker 3] // Soul
{F2 08 FF FF}{speed 6}Yeah, I thought so. Same here.
{wait}
---
{F2 08 FF FF}...If you give me some Macca,
I'll tell you what I know.
How about it?
{wait}

[msg F041_AREA18_SINEN_X02_NO speaker 3] // Soul
{F2 08 FF FF}{speed 6}...No money to spare? That's okay,
I don't have any either... *sigh*
{wait}

[msg F041_AREA18_SINEN_X02_YE speaker 3] // Soul
{F2 08 FF FF}{speed 6}Really!? I appreciate it.
{wait}

[msg F041_AREA18_SINEN_X02_YE]
{F2 08 FF FF}{speed 6}> You gave him 2000 Macca.
{wait}

[msg F041_AREA18_SINEN_X02_YE speaker 3] // Soul
{F2 08 FF FF}{speed 6}...Next time you're on the floor
above, pay attention to the ceiling.
{wait}

[msg F041_AREA9_SINEN_KAMARA speaker 3] // Soul
{F2 08 FF FF}{speed 6}Grrrrr...
Are you a human, or a demon?
{wait}

[msg F041_AREA9_SINEN_KAMARA0 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I hate humans. They're so cruel...
{wait}
---
{F2 08 FF FF}Don't come near me!
{wait}

[msg F041_AREA9_SINEN_KAMARA0 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I'm Kamala. I like demons.
They're my friends.
{wait}
---
{F2 08 FF FF}Come see me anytime.
I'll tell you all about the {color 1}Fiends{color 0}.
{wait}

[sel F041_AREA9_SINEN_KAMARAS]
{F2 08 FF FF}I'm a human.
---
{F2 08 FF FF}I'm a demon.

[msg F041_AREA9_SINEN_KAMARA0 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}There are these Fiends that stole
treasures from this Labyrinth,
{wait}
---
{F2 08 FF FF}and they ran away to somewhere
called the Vortex World.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of a Fiend
in... {color 1}a city with a tall, tall building{color 0}.
{wait}
---
{F2 08 FF FF}So, I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of a Fiend
on... {color 1}a highway near a tall building{color 0}.
{wait}
---
{F2 08 FF FF}So, I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg TUIKA_HELL01 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}It's on {color 1}a highway near a tall building{color 0}.
{wait}
---
{F2 08 FF FF}I think you're better off
avoiding that place.
{wait}

[msg TUIKA_TRAN02 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}It's {color 1}underneath Yurakucho{color 0}.
{wait}
---
{F2 08 FF FF}I wouldn't go there, if I were you.
{wait}

[msg TUIKA_03 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}Uh oh, this one's coming after you.
{wait}
---
{F2 08 FF FF}You'd better watch out!
{wait}

[msg TUIKA_04 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}It's in {color 1}a large underground passage{color 0}.
{wait}
---
{F2 08 FF FF}I wouldn't go there, if I were you.
{wait}

[msg TUIKA_05 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}It's in {color 1}a hospital in Shinjuku{color 0}.
{wait}
---
{F2 08 FF FF}I wouldn't go there, if I were you.
{wait}

[msg TUIKA_06 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}It's on {color 1}an underground road
in Asakusa that leads to a park{color 0}.
{wait}
---
{F2 08 FF FF}I wouldn't go there, if I were you.
{wait}

[msg TUIKA_07 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}It's on {color 1}the west side of Yoyogi Park{color 0}.
{wait}
---
{F2 08 FF FF}I wouldn't go there, if I were you.
{wait}

[msg TUIKA_08 speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait, there's another one...
{wait}
---
{F2 08 FF FF}It's {color 1}underneath Yurakucho{color 0}.
{wait}
---
{F2 08 FF FF}I wouldn't go there, if I were you.
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Let's see...
{wait}
---
{F2 08 FF FF}I don't think there are any Fiends
around right now.
{wait}
---
{F2 08 FF FF}So, it's safe to walk around!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, there's a Fiend that's coming
after you.
{wait}
---
{F2 08 FF FF}He's looking for you in different
cities.
{wait}
---
{F2 08 FF FF}Don't let him catch you off-guard!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of a Fiend
in... {color 1}a large underground passage{color 0}.
{wait}
---
{F2 08 FF FF}So, I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of a Fiend
in... {color 1}a hospital in Shinjuku{color 0}.
{wait}
---
{F2 08 FF FF}So, I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of a Fiend
on... {color 1}an underground road
in Asakusa that leads to a park{color 0}.
{wait}
---
{F2 08 FF FF}So, I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}...Huh? Wait a minute.
{wait}
---
{F2 08 FF FF}I sense one in {color 1}the Third Kalpa
of this Labyrinth{color 0} too.
{wait}
---
{F2 08 FF FF}Be careful, okay?
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of a Fiend
in... {color 1}the Third Kalpa of this Labyrinth{color 0}.
{wait}
---
{F2 08 FF FF}I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}But, something's kinda weird...
This one feels different than
the others. I wonder why?
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of a Fiend
on... {color 1}the west side of Yoyogi Park{color 0}.
{wait}
---
{F2 08 FF FF}So, I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Um, I sense the presence of
a Fiend... {color 1}underneath Yurakucho{color 0}.
{wait}
---
{F2 08 FF FF}So, I think you should stay away
from there.
{wait}
---
{F2 08 FF FF}I hope that helps!
{wait}

[msg F041_AREA9_SINEN_KAMARA_ speaker 4] // Kamala
{F2 08 FF FF}{speed 6}Hey, you're back!
I have something important
to tell you. Wanna hear it?
{wait}
---
{F2 08 FF FF}Let's see...
{wait}
---
{F2 08 FF FF}You know what?
I think all the Fiends are gone.
That means...
{wait}
---
{F2 08 FF FF}You don't have to worry about them
anymore! Yay!
{wait}

[msg F041_AREA10_KERU001 speaker 5] // Cerberus
{F2 08 FF FF}{speed 6}WELCOME, MIGHTY DEMON.
LONG HAVE I WAITED FOR ONE
SUCH AS YOU.
{wait}

[msg F041_AREA10_KERU001_02 speaker 5] // Cerberus
{F2 08 FF FF}{speed 6}NOW, COME TO MY MASTER.
{wait}

[msg F041_AREA10_KERU002 speaker 5] // Cerberus
{F2 08 FF FF}{speed 6}HOWEVER, YOU ARE NOT YET
STRONG ENOUGH.
{wait}
---
{F2 08 FF FF}YOU MUST OVERCOME ALL
DEATHS, AND ATTAIN
ULTIMATE STRENGTH.
{wait}
---
{F2 08 FF FF}IT IS THEN THAT YOU WILL
RETURN TO ME.
{wait}
---
{F2 08 FF FF}I WILL BE WAITING...
{wait}

[msg F041_AREA10_KERU002_02]
{F2 08 FF FF}{speed 6}> Cerberus left...
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

[sel F041_YES_NO]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F041_SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}This is the {color 1}Labyrinth of Amala{color 0}.
{wait}
---
{F2 08 FF FF}It is a world completely different
from the Vortex World which you
came from.
{wait}
---
{F2 08 FF FF}It is divided into several regions
called {color 1}Kalpa{color 0}, and at the very bottom
resides our master, the ruler
of chaos...
{wait}
---
{F2 08 FF FF}If your wish is to pursue the path
of creation as a human...
then there is no reason for you to
stay here long.
{wait}

[msg F041_DEVIL01 speaker 6] // Demon
{F2 08 FF FF}{speed 6}A human's soul can learn,
but his body is mortal.
A demon is immortal,
but his soul never changes.
{wait}
---
{F2 08 FF FF}...I wonder how it is for you,
since you're both human and
demon...
{wait}

[msg F041_SINEN02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}There is no place in the Labyrinth
where you can rest.
{wait}
---
{F2 08 FF FF}The demons are all here for
a {color 1}certain reason{color 0},
so I doubt they'll join you.
{wait}
---
{F2 08 FF FF}Prepare yourself well if you don't
want to die.
{wait}

[msg F041_SINEN03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}"On the day we fell from heaven,
time came to a halt for us...
{wait}
---
{F2 08 FF FF}It remains unchanging,
like the still of the night.
{wait}
---
{F2 08 FF FF}We demons await the master's
words, his proclamation of a new
beginning..."
{wait}
---
{F2 08 FF FF}That's what a demon I met earlier
told me, but I have no idea what
it means.
{wait}

[msg F041_SINEN_X speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}...I'm glad you made it here.
{wait}
---
{F2 08 FF FF}...If you get stronger,
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
{wait}

[msg F041_SINEN_X2 speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}...I've got nothing else
to sell you.
...Hey, don't worry.
{wait}
---
{F2 08 FF FF}I'm sure there are other brokers
besides me in this Labyrinth.
{wait}

[msg F041_SINEN_LEV001 speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}...You're pretty strong.
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
Interested?
{wait}

[msg F041_SINEN_DAM speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}...On second thought,
forget what I just said.
{wait}
---
{F2 08 FF FF}The demon you have there...
Yeah, the one that's kinda red
and has long eyes...
{wait}
---
{F2 08 FF FF}As long as you've got that demon
with you, I can't sell you mine.
Come back after you get rid of it.
{wait}

[msg F041_SINEN_LEV002 speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}...You're pretty strong.
{wait}
---
{F2 08 FF FF}I'll sell you something special.
{wait}
---
{F2 08 FF FF}Uh... Wait a minute,
your party's full.
{wait}
---
{F2 08 FF FF}If you want a new companion,
make some room first and then
come back.
{wait}

[msg F041_SINEN_LEV003 speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}Here's what I'm selling...
{wait}
---
{F2 08 FF FF}...a demon that can see through
anything. With this guy around,
any maze is a piece of cake.
{wait}
---
{F2 08 FF FF}It'll be a perfect companion when
exploring a new area.
{wait}
---
{F2 08 FF FF}I'm asking 15000 Macca.
I know it's kinda high,
but it's well worth the price...
So, you want it?
{wait}

[sel F041_SINEN_LEV003_SEL]
{F2 08 FF FF}Alright, I'll buy it.
---
{F2 08 FF FF}No thanks.

[msg F041_SINEN_LEV004 speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}Excellent choice!
{wait}

[msg F041_SINEN_LEV005]
{F2 08 FF FF}{speed 6}> You purchased a demon from
the Shady Broker.
{wait}

[msg F041_SINEN_LEV006 speaker 6] // Demon
{F2 08 FF FF}{speed 6}...I-I... Pisaca!!
{wait}
---
{F2 08 FF FF}Nice... m-meet... you...
{wait}

[msg F041_SINEN_LEV007]
{F2 08 FF FF}{speed 6}> The demon is quivering...
{wait}

[msg F041_SINEN_LEVIRANAI speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}That's fine.
If you change your mind,
feel free to come back anytime.
{wait}

[msg F041_SINEN_KANE speaker 7] // Shady Broker
{F2 08 FF FF}{speed 6}Hey hey hey, you don't have
enough Macca.
{wait}
---
{F2 08 FF FF}Come back when you have more
money, okay?
{wait}

[msg F041_DEVIL02 speaker 6] // Demon
{F2 08 FF FF}{speed 6}You're an outsider, aren't ya?
{wait}

[msg F041_DEVIL02_NO speaker 6] // Demon
{F2 08 FF FF}{speed 6}...I can tell just by looking at you.
{wait}

[msg F041_DEVIL02_YES speaker 6] // Demon
{F2 08 FF FF}{speed 6}...The Labyrinth of Amala is like
a reverse world to most newcomers.
{wait}
---
{F2 08 FF FF}All things have a front and a back,
and only by knowing both sides
can you fully understand them.
{wait}
---
{F2 08 FF FF}The truth of this world can only
be discovered at the very bottom
of the Labyrinth.
{wait}

[msg F041_SINEN04 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Have you noticed the writing
on the tombstones?
{wait}
---
{F2 08 FF FF}It's inscribed as the demons are
killed by you-know-who...
{wait}

[msg F041_SINEN05 speaker 3] // Soul
{F2 08 FF FF}{speed 6}You need a {color 1}key{color 0} to open this vault.
{wait}
---
{F2 08 FF FF}I dunno about the vault on
the other side, though.
{wait}

[msg F041_SINEN06 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Read the writing on the tombstones
while wearing the {color 1}Black Visor{color 0}...
{wait}

[msg F041_SINEN_X02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Hey, are you having difficulties?
{wait}

[msg F041_SINEN_X02_NO speaker 3] // Soul
{F2 08 FF FF}{speed 6}Really...? Lucky you... *sigh*
{wait}

[msg F041_SINEN_X02_YES speaker 3] // Soul
{F2 08 FF FF}{speed 6}Yeah, I thought so. Same here.
{wait}
---
{F2 08 FF FF}...If you give me some Macca,
I'll tell you what I know.
How about it?
{wait}

[msg F041_SINEN_X02_NO02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...No money to spare? That's okay,
I don't have any either... *sigh*
{wait}

[msg F041_SINEN_X02_YES02_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Really!? I appreciate it.
{wait}

[msg F041_SINEN_X02_YES02_02]
{F2 08 FF FF}{speed 6}> You gave him 10000 Macca.
{wait}

[msg F041_SINEN_X02_YES02_03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...Next time you're on the floor
above, pay attention to the ceiling.
{wait}

[msg F041_DOOR01_01]
{F2 08 FF FF}{speed 6}> The door is locked...
{wait}

[msg F041_DOOR01_02]
{F2 08 FF FF}{speed 6}> You used the {color 1}Moon Key{color 0}.
{wait}

[msg F041_SHAFT]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F041_SHAFT02]
{F2 08 FF FF}{speed 6}> There is a shaft leading upward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F041_DOOR02]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F041_BOHYO]
{F2 08 FF FF}{speed 6}> There is a tombstone without
a name on it...
{wait}

[msg F041_KUROJAKU speaker 2] // Dr. Dark
{F2 08 FF FF}{speed 6}Do me a favor...
{wait}
---
{F2 08 FF FF}Don't bother me...
{wait}

[sel F041_DR_SEL]
{F2 08 FF FF}My pleasure.
---
{F2 08 FF FF}Sorry, but I need your help.

[msg F041_KUROJAKU_YES speaker 2] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}

[msg F041_KUROJAKU_KAIHUKU01 speaker 2] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}...Then, give me 10000 Macca.
If you don't like it, then go
somewhere else. So, do you want
me to help you or not?
{wait}

[msg F041_KUROJAKU_KAIHUKU02]
{F2 08 FF FF}{speed 6}> ......
{wait}
---
{F2 08 FF FF}> Dr. Dark healed your party.
{wait}

