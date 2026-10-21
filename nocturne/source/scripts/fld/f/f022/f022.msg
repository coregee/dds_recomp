// messages of fld/f/f022/f022
[speaker 0] Soul
[speaker 1] Cerberus
[speaker 2] Pixie (temp)
[speaker 3] Mysterious voice
[speaker 4] Lady's voice
[speaker 5] Demon
[speaker 6] Man
[speaker 7] Man on the right
[speaker 8] Man on the left
[speaker 9] People
[speaker 10] Old man
[speaker 11] Manikins
[speaker 12] Old Manikin
[speaker 13] Manikin gatekeeper
[speaker 14] Collector Manikin
[speaker 15] Voice
[speaker 16] Male Manikin
[speaker 17] Manikin kid
[speaker 18] Female Manikin
[speaker 19] Manikin

[msg F22_AREA1_DEBUG]
{F2 08 FF FF}{speed 6}> Cerberus was erased.
{wait}

[msg F22_AREA1_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Are you trying to get to Ikebukuro,
too?
{wait}
---
{F2 08 FF FF}I say you should turn back.
{wait}
---
{F2 08 FF FF}There's a crazy dog blocking
the way up ahead. He's a real
ruffian!
{wait}

[msg F22_AREA1_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hey! Did you see that giant dog?
{wait}

[sel F22_AREA1_NPC2_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F22_AREA1_NPC2_YES speaker 0] // Soul
{F2 08 FF FF}{speed 6}That dog... Maybe it's guarding
the Mantra... Or, maybe it just likes
hounding people.
{wait}

[msg F22_AREA1_NPC2_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}If you rover on up ahead, you'll see
him. Be careful not to get eaten.
He's a doggone menace!
{wait}

[msg F22_AREA3_KEL1 speaker 1] // Cerberus
{F2 08 FF FF}{speed 6}GRRRRRRRRR.........
{wait}

[msg F22_AREA3_KEL2]
{F2 08 FF FF}{speed 6}> There is a ferocious dog blocking
the path!
{wait}

[msg F22_AREA8_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Mantra are collecting Magatsuhi
while using Ikebukuro as their
headquarters.
{wait}
---
{F2 08 FF FF}I saw a bunch of Manikins being
taken there.
{wait}

[msg F22_AREA8_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Eep!! D-D-D-Don't kill me!
{wait}
---
{F2 08 FF FF}Oh, sorry... Wrong demon.
{wait}
---
{F2 08 FF FF}I was just attacked by the Mantra.
Aside from the usual brutality,
they used very harsh language!
{wait}

[msg F22_AREA8_NPC3 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Stability created by regulations, or
chaos resulting from freedom...
{wait}
---
{F2 08 FF FF}Which is the better world...?
That's a difficult choice...
{wait}

[msg F22_AREA8_NPC4 speaker 0] // Soul
{F2 08 FF FF}{speed 6}My, what a handsome boy!
I can give you a massage!
{wait}

[sel F22_AREA8_NPC4_SEL]
{F2 08 FF FF}Okay.
---
{F2 08 FF FF}No thanks.

[msg F22_AREA8_NPC4_YES speaker 0] // Soul
{F2 08 FF FF}{speed 6}Mmmm... You're pretty tense...
Ahhh... How's this...?
{wait}

[msg F22_AREA8_NPC4_KAIHUKU]
{F2 08 FF FF}{speed 6}> You fully recovered!
{wait}

[msg F22_AREA8_NPC4_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}Oh, that's too bad.
{wait}
---
{F2 08 FF FF}If you'd like a relaxing massage,
talk to me anytime!
{wait}

[msg F22_AREA13_NPC1 speaker 2] // Pixie (temp)
{F2 08 FF FF}{speed 6}Hey, do you like this underpass?
{wait}

[sel F22_AREA13_NPC1_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F22_AREA13_NPC1_YES speaker 2] // Pixie (temp)
{F2 08 FF FF}{speed 6}Are you stupid?
I hate this place!!
{wait}
---
{F2 08 FF FF}There's nothing to drink
down here but dirty water!!
{wait}

[msg F22_AREA13_NPC1_NO speaker 2] // Pixie (temp)
{F2 08 FF FF}{speed 6}You, too? Ew! They need to do
something about this dirty water.
{wait}
---
{F2 08 FF FF}I'm all thirsty, and there's
nothing down here. 
{wait}

[msg F22_AREA13_NPC2 speaker 2] // Pixie (temp)
{F2 08 FF FF}{speed 6}What is it?
{wait}

[sel F22_AREA13_NPC2_SEL]
{F2 08 FF FF}Give her clean water.
---
{F2 08 FF FF}Give her nothing.

[msg F22_AREA13_NPC2_YARU speaker 2] // Pixie (temp)
{F2 08 FF FF}{speed 6}You're giving this to me???
Thank you sooo much!!
{wait}
---
{F2 08 FF FF}I'll give you this in return!
{wait}

[msg F22_AREA13_NPC2_TAKARA]
{F2 08 FF FF}{speed 6}> The main character obtained
1 rare item.
{wait}

[msg F22_AREA13_NPC2_NANDEMO speaker 2] // Pixie (temp)
{F2 08 FF FF}Don't talk to me if you've got
nothing to say! Speaking makes
me even thirstier! *cough*
{wait}

[msg F22_AREA13_NPC3 speaker 2] // Pixie (temp)
{F2 08 FF FF}{speed 6}Take good care of my treasure!
It's 'precious' to me!
{wait}

[msg F22_AREA13_YURE]
{F2 08 FF FF}{speed 6}> The flames of the {color 1}Candelabrum
of Sovereignty{color 0} are flickering wildly...
{wait}

[msg F22_AREA13_NAZO speaker 3] // Mysterious voice
{F2 08 FF FF}{speed 6}> You can feel the presence of
a terrifying demon...
{wait_nospeaker}{F2 08 FF FF}{wait}
---
{F2 08 FF FF}The flames of the candelabrum
beckon me to the battlefield!
{wait}
---
{F2 08 FF FF}I do not know who you are, but...
If you have a candelabrum,
it is our destiny to fight.
{wait}
---
{F2 08 FF FF}Let us duel to the death within
my realm, where no one can
interrupt us!
{wait}

[msg F22_AREA13_SHUKU speaker 4] // Lady's voice
{F2 08 FF FF}{speed 6}...So, those holding candelabra did
attract each other...
{wait}
---
{F2 08 FF FF}{firstname 0}, I have a favor to
ask of you.
{wait}
---
{F2 08 FF FF}There is no hurry, but could you
bring your candelabrum to us?
{wait}
---
{F2 08 FF FF}I will allow you access to
the {color 1}Labyrinth of Amala{color 0} from
the terminal.
{wait}
---
{F2 08 FF FF}I will explain the details
once you arrive.
{wait}
---
{F2 08 FF FF}Until then, please make sure
you do not lose the candelabrum...
{wait}

[msg F22_AREA13_SHUKU_02]
{F2 08 FF FF}{speed 6}> You hear a familiar voice.
{wait}

[msg F22_AREA13_SHUKU_03]
{F2 08 FF FF}{speed 6}> You can no longer hear
the lady's voice.
{wait}

[msg F22_AREA13_GOAMARA]
{F2 08 FF FF}{speed 6}> You used the terminal and
headed to the Labyrinth of Amala...
{wait}

[msg F22_AREA20_NPC1_1 speaker 5] // Demon
{F2 08 FF FF}{speed 6}Great timing! I have something to
ask you...
{wait}
---
{F2 08 FF FF}Of those two forces that are
waging war right now--Nihilo and
the Mantra...
{wait}
---
{F2 08 FF FF}Which side are you on?
{wait}

[sel F22_AREA20_NPC1_1_SEL]
{F2 08 FF FF}Mighty Mantra's side.
---
{F2 08 FF FF}Awesome Assembly of Nihilo's side.

[msg F22_AREA20_NPC1_1_MANTOR speaker 5] // Demon
{F2 08 FF FF}{speed 6}The Mantra's city of Ikebukuro is
a place ruled by violence.
{wait}
---
{F2 08 FF FF}You can't complain if you are
maimed. No one complains if you
kill someone.
{wait}
---
{F2 08 FF FF}I see that you have the stomach to
endure that rule.
{wait}

[msg F22_AREA20_NPC1_1_NIHIRO speaker 5] // Demon
{F2 08 FF FF}{speed 6}...You are against rule by power?
Do you not have confidence in your
own power? How odd...
{wait}
---
{F2 08 FF FF}...Allow me to judge your power!!
{wait}

[msg F22_AREA20_NPC1_2 speaker 5] // Demon
{F2 08 FF FF}{speed 6}I am amazed by *pant* your power...
I must *pant* train harder...
{wait}

[msg F22_AREA4_MANE_A speaker 6] // Man
{F2 08 FF FF}{speed 6}......Ah!!
{wait}

[msg F22_AREA4_MANE_I speaker 6] // Man
{F2 08 FF FF}{speed 6}......Whoa!!
{wait}

[msg F22_AREA4_MANE_U speaker 7] // Man on the right
{F2 08 FF FF}{speed 6}......Ack!! He's this far already!?
{wait}

[msg F22_AREA4_MANE_U2 speaker 8] // Man on the left
{F2 08 FF FF}{speed 6}A demon...? Is he a {color 1}Mantra{color 0} demon?
{wait}

[msg F22_AREA4_MANE_E speaker 7] // Man on the right
{F2 08 FF FF}{speed 6}...Huh!? Mantra!?
{wait}
---
{F2 08 FF FF}Ummmmmm......
{wait}
---
{F2 08 FF FF}Anyway, let's report this to
everyone!
{wait}

[msg F22_AREA9_MANE_1 speaker 6] // Man
{F2 08 FF FF}{speed 6}......Ahhh!! H-He's here...!
{wait}

[msg F22_AREA9_MANE_2 speaker 9] // People
{F2 08 FF FF}{speed 6}...Th-The demon's here!
{wait}

[msg F22_AREA9_MANE_3 speaker 9] // People
{F2 08 FF FF}{speed 6}...Th-The Mantra!?
{wait}

[msg F22_AREA9_MANE_MUGON speaker 6] // Man
{F2 08 FF FF}{speed 6}............
{wait}

[msg F22_AREA9_ROJIN0 speaker 10] // Old man
{F2 08 FF FF}{speed 6}A Mantra demon...
{wait}

[msg F22_AREA9_ROJIN1 speaker 10] // Old man
{F2 08 FF FF}{speed 6}......It's over......
{wait}
---
{F2 08 FF FF}...It's all over...
{wait}

[msg F22_AREA9_ROJIN2 speaker 10] // Old man
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}............?
{wait}
---
{F2 08 FF FF}......Huh?
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}Hey, he's not a Mantra! Never seen
a demon of the likes of him in
their army!
{wait}
---
{F2 08 FF FF}...I was worried for nothing. Now,
I can get back to my rocking chair.
{wait}

[msg F22_AREA9_ROJIN2_02 speaker 10] // Old man
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...What?
{wait}
---
{F2 08 FF FF}Are we that peculiar to you?
{wait}

[sel F22_AREA9_ROJIN_SEL]
{F2 08 FF FF}Actually, yeah.
---
{F2 08 FF FF}Not really.

[msg F22_AREA9_ROJIN2_YES speaker 10] // Old man
{F2 08 FF FF}{speed 6}We're {color 1}Manikins{color 0}.
{wait}
---
{F2 08 FF FF}You can probably tell a lot about us
just by seeing where we live.
{wait}
---
{F2 08 FF FF}...Now, go home! Everyone else, do
the same.
{wait}

[msg F22_AREA9_ROJIN2_NO speaker 10] // Old man
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}I thought that you'd never seen
a {color 1}Manikin{color 0} before.
{wait}
---
{F2 08 FF FF}That was a waste of time...
Everyone, back to business!
{wait}

[msg F22_AREA9_MANE_4 speaker 11] // Manikins
{F2 08 FF FF}{speed 6}Oh......
{wait}
---
{F2 08 FF FF}I guess he's not a Mantra demon...
{wait}

[msg F22_AREA9_MANE_5 speaker 11] // Manikins
{F2 08 FF FF}{speed 6}...We were worried for nothing.
{wait}

[msg F22_AREA9_ROJIN3 speaker 12] // Old Manikin
{F2 08 FF FF}{speed 6}From the moment us Manikins are
born, we're destined to become
slaves.
{wait}
---
{F2 08 FF FF}...Even now, many of our people are
suffering at the hands of the Mantra.
{wait}
---
{F2 08 FF FF}But, we have a heart too, y'know!
We can feel pain like anyone else.
{wait}
---
{F2 08 FF FF}Being a slave is miserable...
That's why we escaped to this
underpass...
{wait}
---
{F2 08 FF FF}We live in a constant state of fear
that the Mantra will attack us at any
moment...
{wait}

[msg F22_AREA9_ROJIN4 speaker 12] // Old Manikin
{F2 08 FF FF}{speed 6}That's why we've sealed off the path
up ahead.
{wait}
---
{F2 08 FF FF}I'm sorry, but we can't open
the gate to Ikebukuro.
{wait}
---
{F2 08 FF FF}Please go back...
{wait}
---
{F2 08 FF FF}Now, then... We must return to our
duties.
{wait}

[msg F22_AREA9_INAI]
{F2 08 FF FF}{speed 6}> The Manikins returned to
their rooms.
{wait}

[msg F22_AREA20_MOBAHN1 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}Hey! Stop right there.
{wait}
---
{F2 08 FF FF}This path leads to Ikebukuro,
the base of the Mantra.
{wait}
---
{F2 08 FF FF}It would be real bad if the Mantra
came, so I can't open the gate.
{wait}

[msg F22_AREA20_MOBAHN1_2 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}I can't let you pass.
{wait}
---
{F2 08 FF FF}It wouldn't be good if the Mantra
came, so I can't open the gate.
{wait}

[msg F22_AREA20_MOBAHN2 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}How many times do I have to tell
you? I can't let you pass...
{wait}
---
{F2 08 FF FF}.............
{wait}
---
{F2 08 FF FF}...What's this?
{wait}

[msg F22_AREA20_MOBAHN3]
{F2 08 FF FF}{speed 6}> You gave the gatekeeper
the {color 1}Manikin's Letter{color 0}.
{wait}

[msg F22_AREA20_MOBAHN4 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}...? A letter from him?
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}............?
{wait}
---
{F2 08 FF FF}............!
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}...I got it. If that's the case,
it can't be helped.
{wait}
---
{F2 08 FF FF}...Go ahead and pass.
{wait}

[msg F22_AREA20_MOBAHN4_2 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}Ask me anytime if you want to get
through.
{wait}

[msg F22_AREA20_MOBAHN5 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}...Going through?
{wait}

[msg F22_AREA20_MOBAHN6 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}............
{wait}

[msg F22_AREA20_MOBAHN7 speaker 13] // Manikin gatekeeper
{F2 08 FF FF}{speed 6}...Open the gate?
{wait}

[sel F22_AREA20_MOBAHN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F22_AREA23_SENEN1 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...Hey.
{wait}

[msg F22_AREA23_SENEN2 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Are you that demon everyone is
talking about?
{wait}
---
{F2 08 FF FF}I'm a collector of many things,
especially things that have to do
with humans.
{wait}
---
{F2 08 FF FF}So, I leave the underpass every
so often, convincing the gatekeeper
to let me through.
{wait}

[msg F22_AREA23_SENEN2A speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Well, if you need some advice,
I'll help you.
{wait}
---
{F2 08 FF FF}...Maybe you could help me collect
'stuff'...
{wait}

[msg F22_AREA23_SENEN3 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Is something wrong?
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}...The gatekeeper is preventing you
from passing by to get to Ikebukuro,
huh?
{wait}
---
{F2 08 FF FF}Would you like me to persuade him
to let you through?
{wait}

[sel F22_AREA23_SENEN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F22_AREA23_SENEN_NO speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Are you sure? Okay, suit yourself.
{wait}
---
{F2 08 FF FF}I doubt you'll be able to get that
gatekeeper to let you through.
{wait}
---
{F2 08 FF FF}Come back if you change your mind.
I'll be here.
{wait}

[msg F22_AREA23_SENEN4 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Alright, I'll persuade the gatekeeper
to let you through.
{wait}
---
{F2 08 FF FF}But, only on one condition...
{wait}
---
{F2 08 FF FF}You have to find something that I'm
looking for.
{wait}

[msg F22_AREA23_SENEN5 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}I want a {color 1}Bill{color 0}. It's a small portrait
painted by humans in a greenish
color.
{wait}
---
{F2 08 FF FF}It's small, yet detailed, and it
uses watermarking technology that
changes patterns...
{wait}
---
{F2 08 FF FF}It had value at one time, I think.
I heard that some humans valued it
more than their lives!
{wait}
---
{F2 08 FF FF}I'd like to find one, but I have
no clue as to where I can find it.
{wait}
---
{F2 08 FF FF}I heard that there were plenty
where {color 1}people crowded together{color 0}.
...A city, perhaps?
{wait}

[msg F22_AREA23_SENEN5A speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Maybe you'll be able to do it.
You're a demon, after all.
{wait}
---
{F2 08 FF FF}Anyways... I entrust you with finding
that Bill.
{wait}

[msg F22_AREA23_SENEN6 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}*gasp* A real BILL!!!
{wait}
---
{F2 08 FF FF}We had a deal, right? C'mon, c'mon!
Oh, this is great!!!
{wait}

[msg F22_AREA23_SENEN7]
{F2 08 FF FF}{speed 6}> You handed over the {color 1}Bill{color 0}.
{wait}

[msg F22_AREA23_SENEN8 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}As I said, a deal's a deal.
Hold on a sec.
{wait}

[msg F22_AREA23_SENEN9 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}...Here you go. Give this {color 1}letter{color 0} to
the gatekeeper. This should get you
through.
{wait}

[msg F22_AREA23_SENEN10]
{F2 08 FF FF}{speed 6}> You obtained the {color 1}Manikin's letter{color 0}.
{wait}

[msg F22_AREA23_SENEN11 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}See you later... I hope you get to
Ikebukuro safely.
{wait}

[msg F22_AREA23_SENEN11_2 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Ooooooh... It says '1000' on it!!
Wonder what that's worth...?
{wait}
---
{F2 08 FF FF}Hmmm... Where's the switch to
activate the watermark?
{wait}

[msg F22_AREA23_SENEN12 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}Did you find a Bill? 
{wait}
---
{F2 08 FF FF}I heard that there were plenty
where {color 1}people crowded together{color 0}.
...A city, perhaps?
{wait}

[msg F22_AREA23_SENEN14 speaker 14] // Collector Manikin
{F2 08 FF FF}{speed 6}The Mantra are busy attacking
Nihilo, so now's a great chance to
collect stuff around Ikebukuro!
{wait}
---
{F2 08 FF FF}To go, or not to go...
That is the question!
I'd hate to get killed...
{wait}

[msg F22_AREA23_SENEN15]
{F2 08 FF FF}{speed 6}> No one is here.
{wait}

[msg F22_AREA23_SENEN13]
{F2 08 FF FF}{speed 6}> You feel like
the story progressed.
{wait}
---
{F2 08 FF FF}A {color 4}flag{color 0} seems to
have been raised.
{wait}

[msg F22_AREA0_NPC1]
{F2 08 FF FF}{speed 6}> This is a spare NPC.
{wait}

[msg FIRE_YURE]
{F2 08 FF FF}{speed 6}> The flame of
the {color 1}Candelabrum of Sovereignty{color 0}
is wavering wildly...
{wait}

[msg KEHAI]
{F2 08 FF FF}{speed 6}> You can feel the presence 
of a terrifying demon...
{wait}
---
{F2 08 FF FF}> Will you stay here?
{wait}

[sel YES_NO_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg KEHAI2]
{F2 08 FF FF}{speed 6}> Are you sure?
{wait}

[msg TRY_RUNAWAY]
{F2 08 FF FF}{speed 1}> ............
{wait}

[msg RUNAWAY]
{F2 08 FF FF}{speed 6}> It looks like you'll
be able to get away.
{wait}

[msg SIPPAI]
{F2 08 FF FF}{speed 6}> It looks like you
won't be able to escape.
{wait}

[msg SIPPAI2 speaker 15] // Voice
{F2 08 FF FF}{speed 6}I know that
you have a candelabrum!
{wait}

[msg SIPPAI_KOTEN speaker 15] // Voice
{F2 08 FF FF}{speed 6}The flames of the candelabrum
burn passionately!
You won't escape!
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

[sel F022_YESNO_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F022_MANEKATA01_01 speaker 12] // Old Manikin
{F2 08 FF FF}{speed 6}...Oh, you again.
{wait}
---
{F2 08 FF FF}Is it bothering you that much?
{wait}

[msg F022_MANEKATA01_YES speaker 12] // Old Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...We're Manikins.
{wait}
---
{F2 08 FF FF}Our destiny is to be slaves to
the demons.
{wait}
---
{F2 08 FF FF}...But, we can also feel pain,
you know.
{wait}
---
{F2 08 FF FF}That's why we live in hiding
in this underpass.
{wait}
---
{F2 08 FF FF}...Get it? So, please leave us be.
{wait}

[msg F022_MANEKATA01_NO speaker 12] // Old Manikin
{F2 08 FF FF}{speed 6}...Then, leave us be.
{wait}

[msg F022_MANEKATA02 speaker 16] // Male Manikin
{F2 08 FF FF}{speed 6}We're like humans, but we're not...
{wait}
---
{F2 08 FF FF}We were made to look like them, for
some reason or another. It can't be
helped.
{wait}

[msg F022_MANEKATA03_01 speaker 16] // Male Manikin
{F2 08 FF FF}{speed 6}Eeeeeeeeep! D-D-D-Don't kill me!
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}Oops... Wrong demon.
{wait}

[msg F022_MANEKATA03_02 speaker 16] // Male Manikin
{F2 08 FF FF}{speed 6}I-I-I-I thought I was going to be
killed!
{wait}

[msg F022_MANEKATA03_03 speaker 16] // Male Manikin
{F2 08 FF FF}{speed 6}I've decided to stay here.
I've grown attached to this
place.
{wait}

[msg F022_MANEKATA04 speaker 16] // Male Manikin
{F2 08 FF FF}{speed 6}This underpass is built like a maze,
so it's perfect for a hideout.
{wait}

[msg F022_MANEKATA05 speaker 17] // Manikin kid
{F2 08 FF FF}{speed 6}You! You know {color 1}Gozu-Tennoh{color 0}?
{wait}

[msg F022_MANEKATA05_YES speaker 17] // Manikin kid
{F2 08 FF FF}{speed 6}...You're cool.
{wait}

[msg F022_MANEKATA05_NO speaker 17] // Manikin kid
{F2 08 FF FF}{speed 6}You blow.
{wait}
---
{F2 08 FF FF}Gozu-Tennoh is the leader of
the Mantra!
{wait}

[msg F022_MANEKATA06 speaker 16] // Male Manikin
{F2 08 FF FF}{speed 6}The Mantra and the Assembly of
Nihilo oppose each other because
their ideals differ.
{wait}
---
{F2 08 FF FF}They have different ideas of how
Tokyo should be run, you see.
{wait}

[msg F022_MANEKATA07 speaker 18] // Female Manikin
{F2 08 FF FF}{speed 6}Did you meet the Manikin who
collects junk?
{wait}

[msg F022_MANEKATA07_YES speaker 18] // Female Manikin
{F2 08 FF FF}{speed 6}You did?
{wait}
---
{F2 08 FF FF}He's weird...
{wait}

[msg F022_MANEKATA07_NO speaker 18] // Female Manikin
{F2 08 FF FF}{speed 6}...I see.
{wait}
---
{F2 08 FF FF}He likes things that humans used.
If you want to meet him, he's
downstairs.
{wait}

[msg F022_MANEKATA08_01 speaker 18] // Female Manikin
{F2 08 FF FF}{speed 6}Many of our fellow Manikins are
suffering in Ikebukuro as slaves of
the {color 1}Mantra{color 0}.
{wait}
---
{F2 08 FF FF}...Um, the Mantra are a group of
demons based in Ikebukuro. Dunno
if you knew...
{wait}

[msg F022_MANEKATA08_02 speaker 18] // Female Manikin
{F2 08 FF FF}{speed 6}The Mantra are headed for Nihilo's
headquarters in Ginza.
{wait}
---
{F2 08 FF FF}They used this underpass to get
there, so we all locked ourselves
inside of our rooms.
{wait}

[msg F022_MANEKATA08_03 speaker 18] // Female Manikin
{F2 08 FF FF}{speed 6}Everyone headed to Asakusa, where
Futomimi is.
{wait}
---
{F2 08 FF FF}This place has become desolate
now.
{wait}

[msg F022_MANEKATA08_04 speaker 18] // Female Manikin
{F2 08 FF FF}{speed 6}I prefer this underpass.
{wait}

[msg F022_SINEN01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Ikebukuro is west of here.
{wait}
---
{F2 08 FF FF}If you're going back to Ginza,
head east.
{wait}

[msg F022_SINEN02_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}If the Mantra and Nihilo ever go
at it...
{wait}
---
{F2 08 FF FF}This place'll be toast in no time.
{wait}

[msg F022_SINEN02_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Mantra and Nihilo have finally
started it! Inquiring minds want to
know...
{wait}
---
{F2 08 FF FF}Will the Mantra win with power, or
will Nihilo win with strategy?
{wait}

[msg F022_SINEN02_03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Assembly of Nihilo...
They're quite a dangerous bunch...
{wait}

[msg F022_DEVIL01 speaker 5] // Demon
{F2 08 FF FF}{speed 6}Hitting on me in a place like this?!
{wait}
---
{F2 08 FF FF}Well, demons with a gift for gab
have skills that calm opponents
down when they get upset.
{wait}
---
{F2 08 FF FF}A smooth talker like that would be
popular with the ladies!
{wait}

[msg F022_SINEN03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}This is the Great Underpass of
Ginza that connects Ginza to
Ikebukuro.
{wait}
---
{F2 08 FF FF}...It's a loooooong tunnel full of
poisonous demons!
{wait}

[msg F022_SINEN04 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The terminal up ahead is
an {color 1}S terminal{color 0}.
{wait}
---
{F2 08 FF FF}You can use it to return to
the parent terminal.
{wait}

[msg F022_SINEN05 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Are you headed to Ikebukuro?
{wait}

[msg F022_SINEN05_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}...I see. It's probably for
the best.
{wait}

[msg F022_SINEN05_YES speaker 0] // Soul
{F2 08 FF FF}{speed 6}Ikebukuro's right there after
you get out of this hall.
{wait}
---
{F2 08 FF FF}But, there hasn't been a single
being that's escaped the Mantra's
clutches once they've been caught!
{wait}
---
{F2 08 FF FF}...Gozu-Tennoh isn't a pushover.
You'd better be careful.
{wait}

[msg F022_SINEN05_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}A bunch of Mantra demons came
through here on their way to fight
Nihilo.
{wait}
---
{F2 08 FF FF}Phew!! I'm sooooo glad they didn't
spot me!
{wait}

[msg F022_SINEN05_03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Shijima...
{wait}
---
{F2 08 FF FF}The commander of Nihilo is
planning to create a world
based on the Reason of Shijima.
{wait}
---
{F2 08 FF FF}I think I like the idea...
{wait}

[msg F022_DOOR01]
{F2 08 FF FF}{speed 6}> The door is closed tight.
{wait}

[msg F022_SINEN06_01 speaker 19] // Manikin
{F2 08 FF FF}{speed 6}The g-g-g-grim reaper!
{wait}
---
{F2 08 FF FF}Up ahead! Up ahead!
{wait}

[msg F022_SINEN06_02 speaker 19] // Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...Is the reaper still there?
{wait}

