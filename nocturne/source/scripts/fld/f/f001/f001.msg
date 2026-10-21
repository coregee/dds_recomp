// messages of fld/f/f001/f001
[speaker 0] Newscaster
[speaker 1] Rubbernecker
[speaker 2] Young man
[speaker 3] Woman
[speaker 4] Man
[speaker 5] High school girl
[speaker 6] Young officer
[speaker 7] Reporter
[speaker 8] High school boy
[speaker 9] Tacky lady
[speaker 10] Not so tacky lady
[speaker 11] Old man
[speaker 12] Shabby man
[speaker 13] Tourist girl
[speaker 14] Police officer
[speaker 15] Ugly high school girl
[speaker 16] Even uglier high school girl

[msg SHIBUYA2 speaker 0] // Newscaster
{F2 08 FF FF}{speed 6}A riot broke out yesterday at Yoyogi
Park, regarding the construction of
a communications tower.
{wait}
---
{F2 08 FF FF}The demonstration got out of hand,
and there have been several deaths
and injuries reported.
{wait}
---
{F2 08 FF FF}Also, {color 1}Hikawa{color 0}, the top
executive of Cybers Communication,
is still missing.
{wait}

[msg SHIBUYA3]
{F2 08 FF FF}{speed 6}> The news continues...
{wait}

[msg SHIBUYA4 speaker 0] // Newscaster
{F2 08 FF FF}{speed 6}Now, for the latest in sports,
we move over to Mannaka!
{wait}

[msg SHIBUYA5 speaker 0] // Newscaster
{F2 08 FF FF}{speed 6}Now, for the latest in
entertainment, we move over
to Ashimoto!
{wait}

[msg SHIBUYA6 speaker 0] // Newscaster
{F2 08 FF FF}{speed 6}And now, over to Kei for
the latest in sports!
{wait}

[msg SHIBUYA7 speaker 0] // Newscaster
{F2 08 FF FF}{speed 6}Stay tuned to see what the weather
forecast has planned.
{wait}

[msg DAREMOINAI]
{F2 08 FF FF}{speed 6}> No one is here.
{wait}

[msg YOUHANAI]
{F2 08 FF FF}{speed 6}> You have no business here.
{wait}

[msg YOYOGI]
{F2 08 FF FF}{speed 6}> Yoyogi Park is sealed off.
{wait}

[msg BUNIN]
{F2 08 FF FF}{speed 6}> There is a note on the door.
{wait}
---
{F2 08 FF FF}{speed 6}"The entrance to the annex is
closed. Please use the entrance
to the main building."
{wait}

[msg SHIBUYANPC speaker 1] // Rubbernecker
{F2 08 FF FF}{speed 6}Hey, hey! Yoyogi Park's all closed
off, 'cause there was a riot.
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

[msg F001_MACHIBITO_01_01 speaker 2] // Young man
{F2 08 FF FF}{speed 6}The riot at Yoyogi Park?
{wait}
---
{F2 08 FF FF}Oh, you mean that thing they're
showing on TV?
{wait}
---
{F2 08 FF FF}It doesn't seem real to me!
I feel like this riot happened
in another world or something...
{wait}
---
{F2 08 FF FF}Well, I don't really have anything
to do with it anyway.
{wait}

[msg F001_MACHIBITO_02_01]
{F2 08 FF FF}{speed 6}> You can overhear a couple's
conversation.
{wait}

[msg F001_MACHIBITO_02_02 speaker 3] // Woman
{F2 08 FF FF}{speed 6}Did you hear about the riot?!
Three people died, right???
Eeek! I'm so scared!!
{wait}

[msg F001_MACHIBITO_02_03 speaker 4] // Man
{F2 08 FF FF}You're such a scaredy-cat!
C'mon, baby, every night we
start our own 'riot of love'!
{wait}

[msg F001_MACHIBITO_02_04 speaker 3] // Woman
{F2 08 FF FF}{speed 6}You're such a pervert!
But, I love that about you!!
*giggle*
{wait}

[msg F001_MACHIBITO_03_02 speaker 5] // High school girl
{F2 08 FF FF}{speed 6}Oh hey, {firstname 0}.
{wait}
---
{F2 08 FF FF}You said you were going to visit
Ms. {lastname 1} today, right?
{wait}
---
{F2 08 FF FF}Just because she's beautiful,
don't go doing weird things to her,
okay!?
{wait}

[msg F001_MACHIBITO_04 speaker 6] // Young officer
{F2 08 FF FF}{speed 6}Due to investigations, the {color 1}entrances
to Yoyogi Park{color 0} have been closed off.
{wait}
---
{F2 08 FF FF}We ask for your cooperation.
{wait}

[msg F001_MACHIBITO09_01]
{F2 08 FF FF}{speed 6}> There is a live report going on...
{wait}

[msg F001_MACHIBITO09_02 speaker 7] // Reporter
{F2 08 FF FF}{speed 6}I feel that the demonstrators'
actions were out of line...
{wait}
---
{F2 08 FF FF}But, even I can't forgive Cybers
Communication for destroying
the park for their own profits!
{wait}

[msg F001_MACHIBITO09_03]
{F2 08 FF FF}{speed 6}> The reporter's impassioned speech
continues...
{wait}

[msg F001_MACHIBITO06 speaker 8] // High school boy
{F2 08 FF FF}{speed 6}Yo, {firstname 0}. What's up?
{wait}
---
{F2 08 FF FF}...Did you hear the rumor about
Yoyogi Park?
{wait}

[sel F001_MACHIBITO06_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F001_MACHIBITO06_YES speaker 8] // High school boy
{F2 08 FF FF}{speed 6}Well... it's just a rumor.
{wait}

[msg F001_MACHIBITO06_NO speaker 8] // High school boy
{F2 08 FF FF}{speed 6}I heard, on the night of the riot,
a {color 1}demon{color 0} was spotted at Yoyogi Park.
{wait}
---
{F2 08 FF FF}It was a terrible demon that killed
all those people!
{wait}
---
{F2 08 FF FF}Well... it's just a rumor.
{wait}

[msg F001_MACHIBITO_07_01]
{F2 08 FF FF}{speed 6}> You can hear some ladies talking.
{wait}

[msg F001_MACHIBITO_07_02 speaker 9] // Tacky lady
{F2 08 FF FF}{speed 6}Did you hear???
About Shinjuku Medical Center...
{wait}

[msg F001_MACHIBITO_07_03 speaker 10] // Not so tacky lady
{F2 08 FF FF}{speed 6}You mean the rumor that it's being
run by some crazy group called
the {color 1}Gaea cult{color 255}?
{wait}

[msg F001_MACHIBITO_07_04 speaker 9] // Tacky lady
{F2 08 FF FF}{speed 6}That's the one!! Aren't cults
horrifying??? You never know
what they're gonna to do!!
{wait}

[msg F001_MACHIBITO_07_05 speaker 10] // Not so tacky lady
{F2 08 FF FF}{speed 6}The Yoyogi Park riot...
The Gaea cult controlling
Shinjuki Medical Center...
{wait}
---
{F2 08 FF FF}But, we don't have anything
to do with it!
{wait}

[msg F001_MACHIBITO_05 speaker 11] // Old man
{F2 08 FF FF}{speed 6}Not again... I need ma' pills!
{wait}
---
{F2 08 FF FF}The {color 1}hospital{color 0} up ahead hasn't been
open for a while. What's goin' on?
{wait}

[msg F001_MACHIBITO_08 speaker 12] // Shabby man
{F2 08 FF FF}{speed 6}By gum! Lately, I've been havin' me
a recurrin' dream...
{wait}
---
{F2 08 FF FF}It's a dream where da world
becomes round...
{wait}
---
{F2 08 FF FF}By gum! I means ter say...
Da world IS round, but it got
round-er, ya see!?
{wait}
---
{F2 08 FF FF}I think it's a prophetic dream,
but no one believes me... By gum!
{wait}

[msg F001_GIMMIC01]
{F2 08 FF FF}{speed 6}> The news is showing on
the giant video display...
{wait}

[msg F001_MACHIBITO_10 speaker 13] // Tourist girl
{F2 08 FF FF}{speed 6}Wowie!
{wait}
---
{F2 08 FF FF}What's up with everyone here?
{wait}
---
{F2 08 FF FF}Everyone's so dang crabby,
even after the riot!
{wait}
---
{F2 08 FF FF}By the way... Do you wanna have
a good time with me???
{wait}

[msg F001_MACHIBITO_11_01 speaker 14] // Police officer
{F2 08 FF FF}{speed 6}Geez, kids today...
{wait}
---
{F2 08 FF FF}There were even fatalities,
yet it's like a carnival here.
{wait}
---
{F2 08 FF FF}Just a while back, a {color 1}long-haired man{color 0}
walked in.
{wait}

[msg F001_MACHIBITO_11_02 speaker 14] // Police officer
{F2 08 FF FF}{speed 6}Kids today are so thoughtless...
{wait}

[msg F001_MACHIBITO12_01]
{F2 08 FF FF}{speed 6}> You overhear a conversation
between some high school girls...
{wait}

[msg F001_MACHIBITO12_02 speaker 15] // Ugly high school girl
{F2 08 FF FF}{speed 6}...Don'tcha think that Hikawa guy's
cool?
{wait}

[msg F001_MACHIBITO12_03 speaker 16] // Even uglier high school girl
{F2 08 FF FF}{speed 6}As if! He's got all those bad rumors
about him floating around!
{wait}

[msg F001_MACHIBITO12_04 speaker 15] // Ugly high school girl
{F2 08 FF FF}{speed 6}Oh, gawd! That's what makes him so
cool!
{wait}

[msg F001_MACHIBITO13 speaker 2] // Young man
{F2 08 FF FF}{speed 6}I just saw this {color 1}foreign guy in red{color 0}.
{wait}
---
{F2 08 FF FF}He had a giant sword on his back,
and looked dangerous!
{wait}
---
{F2 08 FF FF}But, I swear I've seen him
somewhere before... Hmmm...
{wait}

