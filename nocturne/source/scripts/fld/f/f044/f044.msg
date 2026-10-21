// messages of fld/f/f044/f044
[speaker 0] Debug message
[speaker 1] Voice of the lady in black
[speaker 2] Gramps
[speaker 3] Soul
[speaker 4] Demon
[speaker 5] Manikin
[speaker 6] Soul of a man
[speaker 7] Soul of a woman
[speaker 8] Dr. Dark
[speaker 9] Shady Broker

[sel YN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F044_DEBBUG]
{F2 08 FF FF}{speed 6}> Add which candelabrum to
inventory?
{wait}

[sel F044_DEBBUG_SEL]
{F2 08 FF FF}Knowledge
---
{F2 08 FF FF}Majesty
---
{F2 08 FF FF}Beauty
---
{F2 08 FF FF}Godliness
---
{F2 08 FF FF}All
---
{F2 08 FF FF}Nothing

[msg F044_DEBBUG2 speaker 0] // Debug message
{F2 08 FF FF}{speed 6}What do you want to do?
{wait}

[sel F044_DEBBUG2_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Specter flag on
---
{F2 08 FF FF}Sakahagi flag on
---
{F2 08 FF FF}All of the above
---
{F2 08 FF FF}Nothing

[sel F044_DEBBUG3_SEL]
{F2 08 FF FF}Black Visor flag on
---
{F2 08 FF FF}Aciel flag on
---
{F2 08 FF FF}Skadi flag on
---
{F2 08 FF FF}Albion flag on
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

[msg MSG_002_CHISIKI]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Knowledge{color 0}?
{wait}

[msg MSG_002_OKAN]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Majesty{color 0}?
{wait}

[msg MSG_002_BI]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Beauty{color 0}?
{wait}

[msg MSG_002_SINI]
{F2 08 FF FF}{speed 6}> Will you light the {color 1}Candelabrum
of Godliness{color 0}?
{wait}

[sel STOKERE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg MSG_003_CHISIKI]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Knowledge{color 0}.
{wait}

[msg MSG_003_OKAN]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Majesty{color 0}.
{wait}

[msg MSG_003_BI]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Beauty{color 0}.
{wait}

[msg MSG_003_SINI]
{F2 08 FF FF}{speed 6}> You lit the {color 1}Candelabrum
of Godliness{color 0}.
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

[msg MSG_001_010_Y speaker 1] // Voice of the lady in black
{F2 08 FF FF}{speed 6}Please visit us at the deepest part
of the Labyrinth.
{wait}
---
{F2 08 FF FF}...We will be waiting.
{wait}

[msg MSG_001_010_N speaker 1] // Voice of the lady in black
{F2 08 FF FF}{speed 6}Have you changed your mind?
{wait}

[msg MSG_001_010_Y2 speaker 1] // Voice of the lady in black
{F2 08 FF FF}{speed 6}Then, we will be waiting in
the deepest part of the Labyrinth.
{wait}
---
{F2 08 FF FF}{lipsync}I will open the way to the last
door. Please use the candelabrum
and come see us.
{wait}
---
{F2 08 FF FF}{lipsync}We look forward to seeing you
soon.
{wait}

[msg MSG_001_010_N2 speaker 1] // Voice of the lady in black
{F2 08 FF FF}{speed 6}There is still time...
If you decide to help my master,
please come back to this place.
{wait}
---
{F2 08 FF FF}{lipsync}We will be waiting for you.
{wait}

[msg MSG_002_010]
{F2 08 FF FF}{speed 6}> The voice of the lady in black
can be heard through the peephole...
{wait}

[msg MSG_003_010]
{F2 08 FF FF}{speed 6}> The lady's voice could no longer
be heard.
{wait}

[msg F011_GO_Q]
{F2 08 FF FF}{speed 6}> Will you proceed down the corridor?
{wait}

[msg F011_BACK_Q]
{F2 08 FF FF}{speed 6}> Will you go back?
{wait}

[msg F044_CLOSE_DOOR1]
{F2 08 FF FF}{speed 6}> The hole is blocked...
{wait}

[msg F044_CLOSE_DOOR2]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F044_SHAFT_Q]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
{wait}

[msg F044_SHAFT_ENT]
{F2 08 FF FF}{speed 6}> Return to the entrance
of the Labyrinth?
{wait}

[msg F044_SHAFT_UP]
{F2 08 FF FF}{speed 6}> Return to the previous Kalpa?
{wait}

[msg F044_SHAFT_ROOP]
{F2 08 FF FF}{speed 6}> There is a shaft leading downward.
{wait}
---
{F2 08 FF FF}> Jump in?
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

[msg SPEC_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Specter:
Defeated in {var 0} turn(s)."
{wait}

[msg SPEC_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Specter:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg SPEC_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Specter."
{wait}

[msg SPEC_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Specter...
{wait}

[msg SAKA_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Sakahagi:
Defeated in {var 0} turn(s)."
{wait}

[msg SAKA_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Sakahagi:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg SAKA_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Sakahagi."
{wait}

[msg SAKA_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Sakahagi...
{wait}

[msg ARUSI_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Aciel:
Defeated in {var 0} turn(s)."
{wait}

[msg ARUSI_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Aciel:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg ARUSI_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Aciel."
{wait}

[msg ARUSI_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Aciel...
{wait}

[msg SKA_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Skadi:
Defeated in {var 0} turn(s)."
{wait}

[msg SKA_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Skadi:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg SKA_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Skadi."
{wait}

[msg SKA_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Skadi...
{wait}

[msg ARUBI_BEST_SCORE]
{F2 08 FF FF}{speed 6}> "Record of Albion:
Defeated in {var 0} turn(s)."
{wait}

[msg ARUBI_BEST_SCORE_R]
{F2 08 FF FF}{speed 6}> "Record of Albion:
Defeated in {color 1}{var 0}{color 0} turn(s)."
{wait}

[msg ARUBI_BOHI]
{F2 08 FF FF}{speed 6}> It is inscribed,
"Here lies Albion."
{wait}

[msg ARUBI_REMEMBER]
{F2 08 FF FF}{speed 6}> You recall the battle against
Albion...
{wait}

[msg WAITING_JIJII_01 speaker 2] // Gramps
{F2 08 FF FF}{speed 6}What's the matter, sonny?
What's your hurry?
{wait}
---
{F2 08 FF FF}Everybody runs right by here just
like you, not even giving a second
glance to a poor old guy on the side
of the road.
{wait}
---
{F2 08 FF FF}It's a shame what this world's
coming to... You folks oughtta get
your priorities straight.
{wait}
---
{F2 08 FF FF}Ya see, sometimes you just need to
relax and pay no heed to the time.
{wait}
---
{F2 08 FF FF}Don't you agree?
{wait}

[msg WAITING_JIJII_02 speaker 2] // Gramps
{F2 08 FF FF}{speed 6}What!? You didn't listen to me
one single bit! Come back when
you're not in such a hurry.
{wait}

[msg WAITING_JIJII_03 speaker 2] // Gramps
{F2 08 FF FF}{speed 6}Here ya are again.
Let me ask you the same question...
{wait}
---
{F2 08 FF FF}Sometimes, you just need to relax
and pay no heed to the time.
{wait}
---
{F2 08 FF FF}Don't you agree?
{wait}

[msg WAITING_JIJII_04 speaker 2] // Gramps
{F2 08 FF FF}{speed 6}Oh... I can see that you've been
listening.
{wait}
---
{F2 08 FF FF}You're in a hurry, aren't ya?
You should be on your way.
{wait}
---
{F2 08 FF FF}Come back anytime if you'd like to
talk to me again.
{wait}

[msg WAITING_JIJII_05 speaker 2] // Gramps
{F2 08 FF FF}{speed 6}It's nice to see ya again, sonny.
{wait}
---
{F2 08 FF FF}...You're still in a hurry,
aren't ya? You should be on
your way, then. Don't worry,
we can talk some other time.
{wait}

[msg WAITING_JIJII_06 speaker 2] // Gramps
{F2 08 FF FF}{speed 6}Too bad you don't agree, though
your manner says otherwise.
I hope you change your mind.
{wait}

[msg WAITING_JIJII_07 speaker 2] // Gramps
{F2 08 FF FF}{speed 6}It's a pity that we don't see
eye to eye. But, maybe you'll
come around to my way of thinkin'.
{wait}

[msg SAKAHAGI_1ST_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Work hard every day...
That's how people should lead
their lives.
{wait}
---
{F2 08 FF FF}I contributed to society
by doing just that.
{wait}
---
{F2 08 FF FF}My company grew as a result,
and became highly regarded.
{wait}
---
{F2 08 FF FF}Do you think my life was a success?
{wait}

[msg SAKAHAGI_1ST_YES_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...That's what everybody else
thought, too. People envied me
for my fortune... until that
one day...
{wait}

[msg SAKAHAGI_1ST_YES_02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}For the first time in my life,
I had the urge to kill.
{wait}
---
{F2 08 FF FF}So much anger... All because of
that boy... Even to this day,
I still ache for revenge.
{wait}

[msg SAKAHAGI_1ST_YES_03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...Of course, I didn't have the balls
to do anything about it back then,
when I was still playing by
society's rules.
{wait}

[msg SAKAHAGI_1ST_NO_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I see... Yeah, you might be right.
{wait}
---
{F2 08 FF FF}Just when I thought I'd achieved
happiness, my fortune collapsed
like a house of cards.
{wait}
---
{F2 08 FF FF}You should be careful.
You never know what tomorrow
may bring...
{wait}

[msg SAKAHAGI_2ND_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...So much time has passed,
yet my soul still burns with rage.
{wait}
---
{F2 08 FF FF}I should have taken revenge back
then, for what that boy did to me.
{wait}

[msg SAKAHAGI_2ND_02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I sense that you have power
beyond that possessed by
an ordinary demon.
{wait}
---
{F2 08 FF FF}Would you be willing to lead my
wandering soul to salvation?
{wait}

[msg SAKAHAGI_2ND_YES_01]
{F2 08 FF FF}{speed 6}> You rang the {color 1}Afterlife Bell{color 0}.
{wait}
---
{F2 08 FF FF}> Its pure tone fills the air...
{wait}

[msg SAKAHAGI_2ND_YES_PLUS speaker 3] // Soul
{F2 08 FF FF}{speed 6}Ah...
{wait}
---
{F2 08 FF FF}I can see... my black heart...
A new shape surrounds it...
{wait}
---
{F2 08 FF FF}I am in a place... that gives rise
to many demons...
{wait}
---
{F2 08 FF FF}......
{wait}

[msg SAKAHAGI_2ND_YES_02]
{F2 08 FF FF}{speed 6}> The soul vanished...
{wait}

[msg SAKAHAGI_2ND_NO_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}What was I thinking?
No demon would have that kind
of power.
{wait}

[msg FUTOMIMI_1ST_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...You're a strange-looking demon.
I got a question for you.
{wait}
---
{F2 08 FF FF}Do you think it's wrong to kill
until your heart's content?
{wait}

[msg FUTOMIMI_1ST_YES_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Heh, whatever.
You sound just like a human.
{wait}

[msg FUTOMIMI_1ST_YES_02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Actually, humans can be crueler
than you think, even crueler
than demons...
{wait}

[msg FUTOMIMI_1ST_NO_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I knew you'd understand.
Yeah, I killed lots of humans
when I was still alive.
{wait}
---
{F2 08 FF FF}They're all the same...
Just flesh and blood under
a thin layer of skin.
{wait}

[msg FUTOMIMI_1ST_NO_02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}But, to tell you the truth...
Deep down inside, I've always
wondered what it'd be like to
feel warmth and kindness...
{wait}

[msg FUTOMIMI_2ND_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I lived my life causing nothing but
pain and suffering for others...
{wait}
---
{F2 08 FF FF}I never felt bad about it,
and I don't regret living that way,
either.
{wait}
---
{F2 08 FF FF}But... when I met that girl,
the words just slipped out of
my mouth...
{wait}
---
{F2 08 FF FF}"Everybody has kindness in
their heart."
{wait}
---
{F2 08 FF FF}Why the hell did I say that?
{wait}
---
{F2 08 FF FF}Maybe I was just curious what
warmth and kindness feel like...
{wait}
---
{F2 08 FF FF}If I could live my life again,
I... I'd wanna be the kind of person
who is liked by everyone.
{wait}

[msg FUTOMIMI_2ND_02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Damn it, what am I saying?
Why am I getting all emotional...?
{wait}

[msg FUTOMIMI_2ND_03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}You're really one weird demon.
I've never told anyone about
these feelings before.
{wait}
---
{F2 08 FF FF}Hey, by any chance... Would you be
able to guide my soul from here?
{wait}

[msg FUTOMIMI_2ND_YES_01]
{F2 08 FF FF}{speed 6}> You rang the {color 1}Afterlife Bell{color 0}.
{wait}
---
{F2 08 FF FF}> Its pure tone fills the air...
{wait}

[msg FUTOMIMI_2ND_YES_PLUS speaker 3] // Soul
{F2 08 FF FF}{speed 6}I guess it's time to say goodbye
to this place...
{wait}
---
{F2 08 FF FF}The part of my soul that I was
missing... The "me" that I really
wanted to become...
{wait}
---
{F2 08 FF FF}It's gonna wait with other demons
for a new life...
{wait}
---
{F2 08 FF FF}......
{wait}

[msg FUTOMIMI_2ND_YES_02]
{F2 08 FF FF}{speed 6}> The soul vanished...
{wait}

[msg FUTOMIMI_2ND_NO_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I see...
Forget what I just said, will ya?
{wait}

[msg MSG_SW_010]
{F2 08 FF FF}{speed 6}> There is a switch.
Will you activate it?
{wait}

[msg MSG_011_010]
{F2 08 FF FF}{speed 6}> The switch has been activated.
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

[msg F044_DOOR01_01]
{F2 08 FF FF}{speed 6}> The door is locked...
{wait}

[msg F044_DOOR01_02]
{F2 08 FF FF}{speed 6}> You used the {color 1}Star Key{color 0}.
{wait}

[msg F044_DOOR02]
{F2 08 FF FF}{speed 6}> The path is blocked...
{wait}

[msg F044_DOOR03]
{F2 08 FF FF}{speed 6}> A strong presence can be felt
from behind the door.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F044_DOOR03_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg MSG_F44_A25_AKUMA speaker 4] // Demon
{F2 08 FF FF}{speed 6}OUR LEADER'S ROOM IS THERE!!
{wait}
---
{F2 08 FF FF}BE CAREFUL!!
{wait}

[msg MSG_F44_A26_AKUMA speaker 4] // Demon
{F2 08 FF FF}{speed 6}Y-YOU DEFEATED OUR LEADER!?
WOW!!
{wait}
---
{F2 08 FF FF}THEN, YOU SHOULD LOOK FOR
THE {color 1}STAR KEY{color 0}!
{wait}
---
{F2 08 FF FF}IT CAN UNLOCK
THE GOLDEN DOORS.
{wait}
---
{F2 08 FF FF}IT'S SOMEWHERE IN THIS
LABYRINTH, WHERE IT
USED TO BE CURSED...
{wait}
---
{F2 08 FF FF}THERE'S ANOTHER DEMON
WHO KNOWS WHERE IT IS.
{wait}
---
{F2 08 FF FF}IF YOU CAN GET THE STAR KEY,
MAYBE YOU CAN MAKE IT TO
THE BOTTOM!
{wait}

[msg MSG_F44_A21_KAPUL speaker 5] // Manikin
{F2 08 FF FF}{speed 6}This is a prison for souls...
{wait}
---
{F2 08 FF FF}Once you're inside,
you can never get out.
{wait}
---
{F2 08 FF FF}But, if you do find a way out,
please let me know!
{wait}

[msg MSG_F44_A22_MIHARI speaker 3] // Soul
{F2 08 FF FF}{speed 6}"The sound of the bell unites
a soul and a body..."
{wait}
---
{F2 08 FF FF}There was a guy who managed
to escape this prison,
and that's what he used to say.
{wait}
---
{F2 08 FF FF}I wonder what he's doing now...
{wait}

[msg MSG_F44_A22_SINEN01 speaker 6] // Soul of a man
{F2 08 FF FF}{speed 6}Look, another demon who got lost
in this prison.
{wait}
---
{F2 08 FF FF}Do you think he can find his way
out of here?
{wait}

[msg MSG_F44_A22_SINEN02 speaker 7] // Soul of a woman
{F2 08 FF FF}{speed 6}I don't know...
{wait}
---
{F2 08 FF FF}He'll probably give up, and then
run home and cry about it.
{wait}
---
{F2 08 FF FF}*chuckle*
{wait}

[msg MSG_F44_A22_SINEN03 speaker 6] // Soul of a man
{F2 08 FF FF}{speed 6}Come on, he can't do that.
{wait}
---
{F2 08 FF FF}Think about it. How can he run
home if he doesn't know where
the exit is?
{wait}

[msg MSG_F44_A22_SINEN04 speaker 7] // Soul of a woman
{F2 08 FF FF}{speed 6}Oh... That's true.
{wait}
---
{F2 08 FF FF}...So, this poor demon's lost
and he's all alone? How sad.
{wait}
---
{F2 08 FF FF}...Hey, you there. If you wanna
go home, head north. You'll find
your way out of here eventually.
{wait}

[msg MSG_F44_A22_SINEN05]
{F2 08 FF FF}{speed 6}> The two souls resumed their
conversation...
{wait}

[msg MSG_F44_A22_KODOMOSINEN speaker 3] // Soul
{F2 08 FF FF}{speed 6}Oh, you're sooo close!
You're bound to find the exit
any minute now.
{wait}
---
{F2 08 FF FF}But, which way is it...?
North or south, east or west...?
Good luck finding it.
{wait}
---
{F2 08 FF FF}By the way,
I know exactly where it is.
{wait}

[msg MSG_F44_A22_SINENOTOKO speaker 3] // Soul
{F2 08 FF FF}{speed 6}Don't get too close! It's dangerous!
{wait}
---
{F2 08 FF FF}...Just kidding.
{wait}
---
{F2 08 FF FF}You think this is the exit?
{wait}
---
{F2 08 FF FF}There was a guy who escaped from
here, with something he called
the {color 1}Afterlife Bell{color 0}.
{wait}
---
{F2 08 FF FF}He was saying that the bell has
the power to resurrect the dead.
{wait}
---
{F2 08 FF FF}If that's true, I wonder if he's
come back to life in a cemetery
somewhere...
{wait}

[msg MSG_F44_A22_SINENOTOKO_0 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Man, I should've tagged along.
If only I'd known that there's
a way out...
{wait}
---
{F2 08 FF FF}I wonder if he's come back to life
in a cemetery somewhere...
{wait}

[msg MSG_F44_A21_KEIBISINEN speaker 3] // Soul
{F2 08 FF FF}{speed 6}No one can escape from this prison.
{wait}
---
{F2 08 FF FF}You might as well give up all hope.
{wait}
---
{F2 08 FF FF}Just look at me...
I'm going absolutely nowhere...
{wait}

[msg MSG_F44_A21_AKUMA02 speaker 5] // Manikin
{F2 08 FF FF}{speed 6}There are two souls with
extraordinary power
imprisoned here.
{wait}
---
{F2 08 FF FF}Have you talked to either of them?
{wait}
---
{F2 08 FF FF}Oddly enough, it feels like
I've met them somewhere before...
{wait}

[msg F041_AREA9_KUROJAKU speaker 8] // Dr. Dark
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

[msg MSG_F44_A1_NOROISINEN speaker 3] // Soul
{F2 08 FF FF}{speed 6}Turn back! Right now!
It's dangerous ahead!
{wait}
---
{F2 08 FF FF}Not only is it dangerous,
it's VERY dangerous!!
{wait}
---
{F2 08 FF FF}I mean, it's EXTREMELY
dangerous!!!
{wait}
---
{F2 08 FF FF}If you still insist on going,
I won't try to stop you, but...
{wait}
---
{F2 08 FF FF}Make sure you go straight.
Don't ever, ever turn left!
Okay?
{wait}
---
{F2 08 FF FF}...Please believe me.
{wait}

[msg MSG_F44_A1_NOROISINEN_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}It was dangerous ahead!
{wait}
---
{F2 08 FF FF}It was VERY dangerous!!
{wait}
---
{F2 08 FF FF}I mean, it was EXTREMELY
dangerous!!!
{wait}
---
{F2 08 FF FF}...It's a thing of the past, though.
{wait}

[msg MSG_F44_A8_SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}The cursed areas in this Labyrinth
were created by the Wicked King,
who's in the room ahead.
{wait}
---
{F2 08 FF FF}The curse will be lifted if
the king is defeated, so...
{wait}
---
{F2 08 FF FF}If, by some miracle, you manage
to defeat him, you might want to
go back and revisit each Kalpa.
{wait}
---
{F2 08 FF FF}You know those golden doors
that are in different parts
of the Labyrinth?
{wait}
---
{F2 08 FF FF}I heard there's a guy who knows
how to open them.
{wait}
---
{F2 08 FF FF}If you're lucky,
maybe you'll run into him.
{wait}
---
{F2 08 FF FF}...Of course, I highly doubt
that you'll last long against
the Wicked King, let alone
defeat him.
{wait}

[msg MSG_F44_A8_SINEN01_002 speaker 3] // Soul
{F2 08 FF FF}{speed 6}The curse has been lifted.
{wait}
---
{F2 08 FF FF}That means the Wicked King
has been defeated, but...
{wait}
---
{F2 08 FF FF}Who could it have been?
...It wasn't you, was it?
{wait}

[msg MSG_F44_A9_AKUMA001 speaker 4] // Demon
{F2 08 FF FF}{speed 6}Oh, I'm so in love with our leader!
{wait}
---
{F2 08 FF FF}...Who is he? Sorry, I can't
give out his name. But...
{wait}
---
{F2 08 FF FF}He's so noble, we call him
the Lord of the Flies!
{wait}
---
{F2 08 FF FF}I can't stop thinking about him...
{wait}

[msg MSG_F44_A11_SINENONNA speaker 3] // Soul
{F2 08 FF FF}{speed 6}We call the corridor ahead
the 12 Meters of Eternity.
{wait}
---
{F2 08 FF FF}It's only a short distance
to the other side,
but every time you enter,
you end up somewhere else...
{wait}
---
{F2 08 FF FF}You'll see what I mean once
you try it yourself...
{wait}

[msg MSG_F44_A11_SINENON02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}To continue on, just go down
that ladder.
{wait}
---
{F2 08 FF FF}If you want to go back,
then return through
the 12 Meters of Eternity.
{wait}
---
{F2 08 FF FF}It's really strange...
From the other side, the phase
of Kagutsuchi determines where
you'll end up,
{wait}
---
{F2 08 FF FF}but from this side, you can only
return to the entrance.
{wait}

[msg MSG_F44_A13_SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Too bad!
{wait}
---
{F2 08 FF FF}This is a dead end.
You spent all that precious time
coming here for nothing.
{wait}
---
{F2 08 FF FF}Just so you know, there's a place
nearby that looks like a dead end,
but you can actually go through it.
{wait}
---
{F2 08 FF FF}Have fun looking for it.
{wait}

[msg MSG_F44_A28_SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I think you need to activate that
switch over there to continue.
{wait}
---
{F2 08 FF FF}It looks like you can get to
the other side from the Kalpa above,
so...
{wait}
---
{F2 08 FF FF}Why don't you try to make your way
across?
{wait}

[msg MSG_F44_A28_SINEN01_002 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Hey, you activated the switch.
{wait}
---
{F2 08 FF FF}Now, you can move on. Good luck!
{wait}

[msg F041_SINEN_X speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}...I'm glad you made it here.
{wait}
---
{F2 08 FF FF}...If you get stronger,
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
{wait}

[msg F041_SINEN_X2 speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}...I've got nothing else
to sell you.
...Hey, don't worry.
{wait}
---
{F2 08 FF FF}I'm sure there are other brokers
besides me in this Labyrinth.
{wait}

[msg F041_SINEN_LEV001 speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}...You're pretty strong.
{wait}
---
{F2 08 FF FF}...I'll sell you something special.
Interested?
{wait}

[msg F041_SINEN_DAM speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}...On second thought,
forget what I just said.
{wait}
---
{F2 08 FF FF}The demon you have there...
Yeah, the one that has colorful
wings...
{wait}
---
{F2 08 FF FF}As long as you've got that demon
with you, I can't sell you mine.
Come back after you get rid of it.
{wait}

[msg F041_SINEN_LEV002 speaker 9] // Shady Broker
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

[msg F041_SINEN_LEV003 speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}Here's what I'm selling...
{wait}
---
{F2 08 FF FF}...a demon that wields an assortment
of powerful attack spells.
{wait}
---
{F2 08 FF FF}It's a charming and dependable
companion!
{wait}
---
{F2 08 FF FF}I'm asking 50000 Macca.
I know it's kinda high,
but it's well worth the price...
So, you want it?
{wait}

[msg F041_SINEN_LEV003_SARU speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}Here's what I'm selling...
{wait}
---
{F2 08 FF FF}...a demon that is exceptionally
tough.
{wait}
---
{F2 08 FF FF}It's practically impervious
to any form of attack!
{wait}
---
{F2 08 FF FF}I'm asking 100000 Macca.
I know it's kinda high,
but it's well worth the price...
So, you want it?
{wait}

[sel F041_SINEN_LEV003_SEL]
{F2 08 FF FF}Alright, I'll buy it.
---
{F2 08 FF FF}No thanks.

[msg F041_SINEN_LEV004 speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}Excellent choice!
{wait}

[msg F041_SINEN_LEV005]
{F2 08 FF FF}{speed 6}> You purchased a demon from
the Shady Broker.
{wait}

[msg F041_SINEN_LEV006 speaker 4] // Demon
{F2 08 FF FF}{speed 6}I am Kaja Mitama.
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

[msg F041_SINEN_LEVIRANAI speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}That's fine.
If you change your mind,
feel free to come back anytime.
{wait}

[msg F041_SINEN_KANE speaker 9] // Shady Broker
{F2 08 FF FF}{speed 6}Hey hey hey, you don't have
enough Macca.
{wait}
---
{F2 08 FF FF}Come back when you have more
money, okay?
{wait}

[msg F44_A3_MSG01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Have you been through
the 12 Meters of Eternity yet?
{wait}
---
{F2 08 FF FF}It can take you to different places
like the vault or the maze, but...
{wait}
---
{F2 08 FF FF}I'm warning you, don't go
through it when Kagutsuchi
shines the weakest.
{wait}
---
{F2 08 FF FF}...Why? Whaddya mean, "Why?"!
If you wander into
the Wicked King's room,
you won't come out alive!
{wait}

[msg F44_A3_MSG02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Have you been through
the 12 Meters of Eternity yet?
{wait}
---
{F2 08 FF FF}It can take you to different places
like the vault or the maze, but...
{wait}
---
{F2 08 FF FF}I'm warning you, don't go
through it when Kagutsuchi
shines the weakest.
{wait}
---
{F2 08 FF FF}...Why? Whaddya mean, "Why?"!
If you wander into
the Wicked King's room,
you won't come out alive!
{wait}

[msg F44_A9_MSG01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Have you been using the shafts
that connect the Kalpa?
{wait}
---
{F2 08 FF FF}I heard that your innate abilities,
such as your agility and strength,
affect your performance in there.
{wait}
---
{F2 08 FF FF}If you plan on collecting Macca
in there, then you might want to
train yourself first.
{wait}

[msg F44_A9_MSG02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}If you have any Deathstones
in your possession...
{wait}
---
{F2 08 FF FF}then you can call forth the deaths
that you have conquered, just as
you have created new demons.
{wait}
---
{F2 08 FF FF}It all depends on the light of
Kagutsuchi, though...
{wait}

