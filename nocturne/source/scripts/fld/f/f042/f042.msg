// messages of fld/f/f042/f042
[speaker 0] Debug message
[speaker 1] Voice of the lady in black
[speaker 2] Noble voice
[speaker 3] Soul
[speaker 4] Demon
[speaker 5] Dr. Dark
[speaker 6] Shady Broker

[sel YN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F042_DEBBUG]
{F2 08 FF FF}{speed 6}> Add which candelabrum to
inventory?
{wait}

[sel F042_DEBBUG_SEL]
{F2 08 FF FF}Dignity
---
{F2 08 FF FF}Eternity
---
{F2 08 FF FF}Both
---
{F2 08 FF FF}Nothing

[msg F042_DEBBUG2 speaker 0] // Debug message
{F2 08 FF FF}{speed 6}What do you want to do?
{wait}

[sel F042_DEBBUG2_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Kaiwan flag on
---
{F2 08 FF FF}Ose flag on
---
{F2 08 FF FF}Moirae Sisters flag on
---
{F2 08 FF FF}Mizuchi flag on
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

[msg MSG_002_IGEN]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Dignity{color 0}?
{wait}

[msg MSG_002_EIEN]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Eternity{color 0}?
{wait}

[sel STOKERE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg MSG_003_IGEN]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Dignity{color 0}.
{wait}

[msg MSG_003_EIEN]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Eternity{color 0}.
{wait}

[msg MSG_004]
{F2 08 FF FF}{speed 6}> You did not light the candelabrum.
{wait}

[msg MSG_003B]
{F2 08 FF FF}{speed 6}> All of the candelabra
have been lit...
{wait}

[msg MSG_003C]
{F2 08 FF FF}{speed 6}> There is room for another
candelabrum on the pedestal...
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
of candelabra and return them
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

[msg F042_CLOSE_DOOR1]
{F2 08 FF FF}{speed 6}> The hole is blocked...
{wait}

[msg F042_CLOSE_DOOR2]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F042_SHAFT_Q]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F042_SHAFT_ENT]
{F2 08 FF FF}{speed 6}> Return to the entrance
of the Labyrinth?
{wait}

[msg F042_SHAFT_UP]
{F2 08 FF FF}{speed 6}> Return to the previous Kalpa?
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

[msg KIUN_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Kaiwan:
Defeated in {var 0} turn(s)."
{wait}

[msg KIUN_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Kaiwan:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg KIUN_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Kaiwan."
{wait}

[msg KIUN_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Kaiwan...
{wait}

[msg OSE_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Ose:
Defeated in {var 0} turn(s)."
{wait}

[msg OSE_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Ose:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg OSE_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Ose."
{wait}

[msg OSE_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Ose...
{wait}

[msg SIMAI_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of the Moirae Sisters:
Defeated in {var 0} turn(s)."
{wait}

[msg SIMAI_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of the Moirae Sisters:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg SIMAI_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lie the Moirae Sisters."
{wait}

[msg SIMAI_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
the Moirae Sisters...
{wait}

[msg MIZ_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Mizuchi:
Defeated in {var 0} turn(s)."
{wait}

[msg MIZ_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Mizuchi:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg MIZ_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Mizuchi."
{wait}

[msg MIZ_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Mizuchi...
{wait}

[msg META_VOICE_SYSTEM_01]
{F2 08 FF FF}{speed 6}> A voice rings out of nowhere...
{wait}

[msg META_VOICE_01 speaker 2] // Noble voice
{F2 08 FF FF}{speed 6}...Fiend, accomplice to
the fallen angel...
{wait}

[msg META_VOICE_02 speaker 2] // Noble voice
{F2 08 FF FF}{speed 6}...Do you know what cause
you serve?
{wait}
---
{F2 08 FF FF}Do you realize which path your
actions are leading you down...?
{wait}

[msg META_VOICE_03 speaker 2] // Noble voice
{F2 08 FF FF}{speed 6}I have watched your every move
from above.
{wait}
---
{F2 08 FF FF}You have been seduced by
darkness,
{wait}
---
{F2 08 FF FF}and now you are about to defy
god's will.
{wait}
---
{F2 08 FF FF}{name 0}, the one with
a demon's body and a human heart,
heed my warning!
{wait}
---
{F2 08 FF FF}End your dealings with the fallen
angel, before your heart is
consumed by darkness!
{wait}

[msg META_VOICE_YES speaker 2] // Noble voice
{F2 08 FF FF}{speed 6}...May you be blessed by the light.
{wait}
---
{F2 08 FF FF}As long as you do not assist him,
his evil plans will surely fail.
{wait}
---
{F2 08 FF FF}Now, return to your world.
Here, the power of chaos will
overwhelm you...
{wait}
---
{F2 08 FF FF}I am one with god...
I am his mouthpiece...
{wait}

[msg META_VOICE_NO speaker 2] // Noble voice
{F2 08 FF FF}{speed 6}...Woe unto you, for you can
no longer discern good from evil...
{wait}
---
{F2 08 FF FF}In this land where demons of chaos
dwell, the last of your humanity
will eventually be lost.
{wait}
---
{F2 08 FF FF}I pray that you return to your world
and rid yourself of darkness,
before it is too late...
{wait}
---
{F2 08 FF FF}before god's vengeance strikes
this cursed land...
{wait}

[msg META_VOICE_SYSTEM_02]
{F2 08 FF FF}{speed 6}> The voice could no longer be heard.
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

[msg BOTTAKURI_YES_02 speaker 3] // Soul
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

[sel F042_YES_NO]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F042_DOOR01_01]
{F2 08 FF FF}{speed 6}> The door is locked...
{wait}

[msg F042_DOOR01_02]
{F2 08 FF FF}{speed 6}> You used the {color 1}Moon Key{color 0}.
{wait}

[msg F042_SHAFT]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F042_SHAFT02]
{F2 08 FF FF}{speed 6}> There is a shaft leading upward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F042_DOOR02]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F042_BOHYO]
{F2 08 FF FF}{speed 6}> There is a tombstone without
a name on it...
{wait}

[msg F042_DEVIL01_01_01 speaker 4] // Demon
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}I can't believe someone would really
come all the way down here...
{wait}
---
{F2 08 FF FF}...You see, I made a bet with
a buddy of mine.
{wait}
---
{F2 08 FF FF}If someone actually made it this far
down, I'd have to give that person
a prize.
{wait}
---
{F2 08 FF FF}Looks like I lost.
Here, take this.
{wait}

[msg F042_DEVIL01_01_02]
{F2 08 FF FF}{speed 6}> You obtained 250000 Macca.
{wait}

[msg F042_DEVIL01_01_03 speaker 4] // Demon
{F2 08 FF FF}{speed 6}I like you. Come back later and I'll
tell you something you might wanna
know.
{wait}

[msg F042_DEVIL01_02 speaker 4] // Demon
{F2 08 FF FF}{speed 6}Alright, I'll tell you something you
might wanna know....
{wait}
---
{F2 08 FF FF}My drinking buddy is somewhere up
in Tokyo having a drink.
{wait}
---
{F2 08 FF FF}He's got the key that opens
the golden doors.
{wait}

[msg F042_DEVIL01_03 speaker 4] // Demon
{F2 08 FF FF}{speed 6}Meet my friend?
{wait}

[msg MSG_F042_TEST speaker 3] // Soul
{F2 08 FF FF}{speed 6}A lot of souls have been gathering
in the Labyrinth.
{wait}
---
{F2 08 FF FF}Everyone around here keeps
arguing about Gaea and Messiah,
whatever those are...
{wait}
---
{F2 08 FF FF}Well, if you walk around, you'll see.
{wait}

[msg MSG_F042_GAIA01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}We believed in living in harmony
with demons.
{wait}
---
{F2 08 FF FF}But, the Order of Messiah wouldn't
accept that, and a conflict erupted.
{wait}
---
{F2 08 FF FF}What we didn't realize was that our
worst enemy was already among us.
{wait}

[msg MSG_F042_MESIA01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...You must never forget to say
your prayers.
{wait}
---
{F2 08 FF FF}If you pray, god will protect you
no matter what happens.
{wait}
---
{F2 08 FF FF}And, you shall eventually join him
in the afterlife... Now, let us pray.
{wait}

[msg MSG_F042_MESIA02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}God spoke to us and foretold
the destruction of Tokyo.
{wait}
---
{F2 08 FF FF}We chased after the Gaea cult
in order to prevent that.
{wait}
---
{F2 08 FF FF}But, we were done in by that
devil summoner...
{wait}
---
{F2 08 FF FF}Hikawa is a dangerous man...
{wait}

[msg F042_KUROJAKU speaker 5] // Dr. Dark
{F2 08 FF FF}{speed 6}Do me a favor...
{wait}
---
{F2 08 FF FF}Don't bother me.
{wait}

[sel F042_DR_SEL]
{F2 08 FF FF}My pleasure.
---
{F2 08 FF FF}Sorry, but I need your help.

[msg F042_KUROJAKU_YES speaker 5] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}

[msg F042_KUROJAKU_KAIHUKU01 speaker 5] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}...Then, give me 10000 Macca.
If you don't like it, then go
somewhere else. So, do you want
my help or not?
{wait}

[msg F042_KUROJAKU_KAIHUKU02]
{F2 08 FF FF}{speed 6}> ......
{wait}
---
{F2 08 FF FF}> Dr. Dark healed your party.
{wait}

[msg MSG_F042_KABE001 speaker 4] // Demon
{F2 08 FF FF}{speed 6}A long, long time ago...
I was summoned by a human,
and we talked of many things.
{wait}
---
{F2 08 FF FF}What he had to say was very
interesting.
{wait}
---
{F2 08 FF FF}Do you want to hear it?
{wait}

[sel F042_AKUMA_SEL]
{F2 08 FF FF}Sure, why not?
---
{F2 08 FF FF}Nah, I'd rather not.

[msg MSG_F042_KABE002 speaker 4] // Demon
{F2 08 FF FF}{speed 6}The man used black magic to
summon me.
{wait}
---
{F2 08 FF FF}This is what he said:
"Kill the man I hate!"
{wait}
---
{F2 08 FF FF}I asked, "Is that what humans do,
kill those they hate?"
{wait}
---
{F2 08 FF FF}He replied, "If you hate, you kill.
That's the way we are."
{wait}
---
{F2 08 FF FF}I admired those words.
It's so demon-like...
the true nature of humans.
{wait}

[msg MSG_F042_KABE003 speaker 4] // Demon
{F2 08 FF FF}{speed 6}I see... If you change your mind,
come back anytime.
{wait}

[msg MSG_F42_NOROI001 speaker 3] // Soul
{F2 08 FF FF}{speed 6}You don't want to go any further.
{wait}
---
{F2 08 FF FF}It's cursed, y'know.
{wait}

[msg MSG_F42_NOROI002 speaker 3] // Soul
{F2 08 FF FF}{speed 6}The curse has been undone.
{wait}
---
{F2 08 FF FF}You can go now.
{wait}

[msg MSG_F42_A22_DEBU01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Y-Y-You know what...?
{wait}
---
{F2 08 FF FF}...If you look real carefully,
you might find a hidden passage.
{wait}
---
{F2 08 FF FF}B-B-But, they're hard to spot.
{wait}

[msg MSG_F42_A4_AKUMA01 speaker 4] // Demon
{F2 08 FF FF}{speed 6}I just heard a voice coming from
your direction.
{wait}
---
{F2 08 FF FF}It was like the voice of
the universe... You weren't harmed,
were you?
{wait}

[msg MSG_F42_A4_AKUMA02 speaker 4] // Demon
{F2 08 FF FF}{speed 6}That incredible power...
It might've been the Great Will
coming to observe us.
{wait}
---
{F2 08 FF FF}Well, not even he can stop our
master's plans now.
{wait}

[msg F041_AREA9_KUROJAKU speaker 5] // Dr. Dark
{F2 08 FF FF}{speed 6}It's natural for every living thing
to die... Treatment, therefore,
contradicts nature.
{wait}
---
{F2 08 FF FF}So... Did you come here to defy
nature and be treated?
{wait}

[sel F041_AREA9_DR_SEL]
{F2 08 FF FF}No.
---
{F2 08 FF FF}Yes.

[msg F041_AREA9_KUROJAKU_YES speaker 5] // Dr. Dark
{F2 08 FF FF}{speed 6}Good. One lives, one dies...
That's the way it should be.
{wait}
---
{F2 08 FF FF}I pray that you find rest soon.
{wait}

[msg F041_AREA9_KUROJAKU_KAIH speaker 5] // Dr. Dark
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

[msg F041_AREA9_KUROJAKU_NOMO speaker 5] // Dr. Dark
{F2 08 FF FF}{speed 6}......
{wait}
---
{F2 08 FF FF}Money first. Get outta here.
{wait}

[msg MSG_F42_A19_SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Hey, see? There, right there!
{wait}
---
{F2 08 FF FF}Oh, come on now.
{wait}
---
{F2 08 FF FF}That wall right there. Open your
eyes and look!
{wait}

[msg MSG_F42_A8_GAIA001 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Everyone, listen!
{wait}
---
{F2 08 FF FF}The world has lost its power under
the reign of god.
{wait}
---
{F2 08 FF FF}Because of that, we are on the
verge of destruction.
{wait}
---
{F2 08 FF FF}But, there is no need to fear.
The Gaea cult will ensure our
survival!
{wait}
---
{F2 08 FF FF}Together, we will resurrect
the strength of the ancient world!
{wait}

[msg MSG_F42_A8_GAIA002]
{F2 08 FF FF}{speed 6}> The soul is still preaching...
{wait}

[msg MSG_F42_A8_GAIA003]
{F2 08 FF FF}{speed 6}> The soul is too busy talking to
notice you.
{wait}

[msg MSG_F42_A8_GAIA_03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}We are just looking for a way
to live in peace with nature
and the ancient gods.
{wait}
---
{F2 08 FF FF}But, the Order of Messiah,
brainwashed by a jealous god,
won't allow us to do so.
{wait}
---
{F2 08 FF FF}...I'm telling you, they're
the ones who should be oppressed,
not us!
{wait}

[msg MSG_F42_A7_MESIA002 speaker 3] // Soul
{F2 08 FF FF}{speed 6}We believe that god's teachings
are absolute.
{wait}
---
{F2 08 FF FF}Everything is his will...
Everything changes at his will...
{wait}
---
{F2 08 FF FF}You must leave this dreaded place
and fulfill the part which you
were originally intended for.
{wait}

[msg MSG_F42_A2_AKUMA01 speaker 4] // Demon
{F2 08 FF FF}{speed 6}I see thou art in anticipation.
{wait}
---
{F2 08 FF FF}There needeth not be reason
to hide it... About that...
{wait}
---
{F2 08 FF FF}I understand thy joy! I cannot
suppress mine own.
{wait}
---
{F2 08 FF FF}As another friend to drink
mead with, I shall tell thee
something interesting.
{wait}
---
{F2 08 FF FF}If thou takest purple Macca
in succession, thine earning
shall be even more.
{wait}
---
{F2 08 FF FF}Try and {color 1}strikest{color 0} anything you can.
I have become rich that way!
Hahahaha!
{wait}

[msg F041_SINEN_X speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}...I'm glad you made it here.
{wait}
---
{F2 08 FF FF}...If you get stronger...
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
{wait}

[msg F041_SINEN_X2 speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}...I've got nothing else
to sell you.
...Hey, don't worry.
{wait}
---
{F2 08 FF FF}I'm sure there are other brokers
besides me in this labyrinth.
{wait}

[msg F041_SINEN_LEV001 speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}...You're pretty strong.
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
Interested?
{wait}

[msg F041_SINEN_DAM speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}...On second thought,
forget what I just said.
{wait}
---
{F2 08 FF FF}The demon you have there...
Yeah, that yellow one...
{wait}
---
{F2 08 FF FF}As long as you've got that demon
with you, I can't sell you mine.
Come back after you get rid of it.
{wait}

[msg F041_SINEN_LEV002 speaker 6] // Shady Broker
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

[msg F041_SINEN_LEV003 speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}Here's what I'm selling...
{wait}
---
{F2 08 FF FF}...a demon that can heal
anything. You'll be glad to have
one around.
{wait}
---
{F2 08 FF FF}With that well-rounded bosom,
I think anyone would rise to
heaven getting healed by her!
{wait}
---
{F2 08 FF FF}I'm asking 30000 Macca.
I know it's kinda high,
but it's well worth the price...
So, you want it?
{wait}

[sel F041_SINEN_LEV003_SEL]
{F2 08 FF FF}Alright, I'll buy it.
---
{F2 08 FF FF}No thanks.

[msg F041_SINEN_LEV004 speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}Excellent choice!
{wait}

[msg F041_SINEN_LEV005]
{F2 08 FF FF}{speed 6}> You purchased a demon from
the Shady Broker.
{wait}

[msg F041_SINEN_LEV006 speaker 4] // Demon
{F2 08 FF FF}{speed 6}I am Nda Mitama.
{wait}
---
{F2 08 FF FF}With my magic, I can
weaken the enemy.
{wait}
---
{F2 08 FF FF}Nice to meet you.
{wait}

[msg F041_SINEN_LEV007]
{F2 08 FF FF}{speed 6}> The demon joined your party.
{wait}

[msg F041_SINEN_LEVIRANAI speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}That's fine.
If you change your mind,
feel free to come back anytime.
{wait}

[msg F041_SINEN_KANE speaker 6] // Shady Broker
{F2 08 FF FF}{speed 6}Hey-hey-hey, you don't have
enough Macca!
{wait}
---
{F2 08 FF FF}Come back when you have more
money, okay?
{wait}

[msg MSG_F42_A12_SINENTUIKA speaker 3] // Soul
{F2 08 FF FF}{speed 6}The floor below is a place
filled with invisible walls.
{wait}
---
{F2 08 FF FF}If you're heading down
below, you better be prepared.
{wait}
---
{F2 08 FF FF}Once you're down there, it
won't be easy coming back up.
{wait}

