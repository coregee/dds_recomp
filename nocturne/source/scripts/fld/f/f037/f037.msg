// messages of fld/f/f037/f037
[speaker 0] Debug MES
[speaker 1] Voice
[speaker 2] Thor
[speaker 3] Manikin
[speaker 4] Female Manikin
[speaker 5] Male Manikin
[speaker 6] Manikin kid
[speaker 7] Old Manikin
[speaker 8] Demon
[speaker 9] Soul

[msg f037_MES01 speaker 0] // Debug MES
{F2 08 FF FF}There's an NPC in the 
other room.
{wait}

[sel f037_MES01_SEL]
{F2 08 FF FF}Erase.
---
{F2 08 FF FF}Add.

[msg THOR00]
{F2 08 FF FF}{speed 6}> You can sense a strong power
from the end of the hall.
{wait}

[msg THOR01 speaker 1] // Voice
{F2 08 FF FF}{speed 6}I didn't imagine that we would meet
here...
{wait}

[msg THOR02 speaker 1] // Voice
{F2 08 FF FF}{speed 6}Neither did I imagine that you would
become this strong...
{wait}
---
{F2 08 FF FF}...But in your case, I should have
expected the unexpected.
{wait}
---
{F2 08 FF FF}Do you remember me?
{wait}
---
{F2 08 FF FF}I remember you...
{wait}

[msg THOR03 speaker 2] // Thor
{F2 08 FF FF}{speed 6}...I am Thor. Our paths have not
crossed since the fall of the Mantra.
{wait}

[msg THOR_YOSUGA01 speaker 2] // Thor
{F2 08 FF FF}{speed 6}...It seems that you are a follower
of Yosuga.
{wait}
---
{F2 08 FF FF}I am one as well.
{wait}
---
{F2 08 FF FF}If the situation were different,
we could have created a new world
together...
{wait}

[msg THOR_YOSUGA02 speaker 2] // Thor
{F2 08 FF FF}{speed 6}But, our battle is still unfinished.
{wait}
---
{F2 08 FF FF}As believers of Yosuga, let us decide
who the strongest is!
{wait}
---
{F2 08 FF FF}Come on!
{wait}

[msg THOR_YOSUGA03 speaker 2] // Thor
{F2 08 FF FF}{speed 6}...Well... done.
{wait}
---
{F2 08 FF FF}That power... That sheer will...
...is truly worthy... of Yosuga.
{wait}
---
{F2 08 FF FF}...I am your witness.
{wait}
---
{F2 08 FF FF}It is my honor to die... by your...
hands...
{wait}
---
{F2 08 FF FF}............
{wait}

[msg THOR_YOSUGA04 speaker 2] // Thor
{F2 08 FF FF}{speed 6}Farewell. I hereby pledge to lend
you my power...
{wait}
---
{F2 08 FF FF}And... if you call...
I will rise from the depths of hell
to assist you...
{wait}
---
{F2 08 FF FF}...I entrust you... with... the world
of Yosuga!
{wait}

[msg THOR_YOSUGA05 speaker 2] // Thor
{F2 08 FF FF}{speed 6}Gaaaaaaaaaaaaaahhhhh......!!


[msg THOR_NO_YOSUGA01 speaker 2] // Thor
{F2 08 FF FF}{speed 6}...It seems that you and I have
different objectives in climbing
this tower...
{wait}
---
{F2 08 FF FF}As a follower of Yosuga, I must
annihilate you!
{wait}

[msg THOR_NO_YOSUGA02 speaker 2] // Thor
{F2 08 FF FF}{speed 6}The world of Yosuga shall be built
upon your lifeless body!
{wait}
---
{F2 08 FF FF}Prepare to meet your doom!
{wait}

[msg THOR_NO_YOSUGA03 speaker 2] // Thor
{F2 08 FF FF}{speed 6}How can this be!?
{wait}
---
{F2 08 FF FF}My powers are no match for yours!?
{wait}
---
{F2 08 FF FF}............
{wait}

[msg THOR_NO_YOSUGA04 speaker 2] // Thor
{F2 08 FF FF}{speed 6}...Even so! 
{wait}
---
{F2 08 FF FF}Lady {firstname 3} will certainly
build a strong world with
the teachings of Yosuga as its basis.
{wait}
---
{F2 08 FF FF}Even though I will die here,
Yosuga is... Y-Yosuga is......
{wait}

[msg THOR_NO_YOSUGA05 speaker 2] // Thor
{F2 08 FF FF}{speed 6}Gaaaaaaaaaaaaaahhhhh......!!


[msg THOR04]
{F2 08 FF FF}{speed 6}> You defeated Thor.
{wait}

[msg MANE1 speaker 3] // Manikin
{F2 08 FF FF}{speed 6}I've decided to take a rest here.
Why don't you rest here, too?
{wait}

[msg MANE2 speaker 3] // Manikin
{F2 08 FF FF}{speed 6}It's dangerous from here on.
{wait}

[msg NO_MAGATAMA_ZZZ speaker 1] // Voice
{F2 08 FF FF}{speed 6}Thou hast not the right to see me.
{wait}
---
{F2 08 FF FF}Win all the Magatama and offer
them to me.
{wait}

[msg NO_MAGATAMA]
{F2 08 FF FF}{speed 6}> There is an altar.
{wait}

[msg MAGATAMA_HONO_ZZZ speaker 1] // Voice
{F2 08 FF FF}{speed 6}Offer me your Magatama...
{wait}

[msg MAGATAMA_HONO]
{F2 08 FF FF}{speed 6}> There is an altar.
{wait}

[msg MAGATAMA_DONE]
{F2 08 FF FF}{speed 6}> A stone is already inserted.
{wait}

[msg SAIDAN01]
{F2 08 FF FF}{speed 6}> Which stone will you offer?
{wait}

[sel SAIDAN01_SEL]
{F2 08 FF FF}Earthstone.
---
{F2 08 FF FF}Netherstone.
---
{F2 08 FF FF}Heavenstone.
---
{F2 08 FF FF}None.

[msg SAIDAN01_SIJIMA]
{F2 08 FF FF}{speed 6}> You offered the {color 1}Earthstone{color 0}.


[msg SAIDAN01_MUSUBI]
{F2 08 FF FF}{speed 6}> You offered the {color 1}Netherstone{color 0}.
{wait}

[msg SAIDAN01_YOSUGA]
{F2 08 FF FF}{speed 6}> You offered the {color 1}Heavenstone{color 0}.
{wait}

[msg SAIDAN01_NO]
{F2 08 FF FF}{speed 6}> You didn't offer anything.
{wait}

[msg SAIDAN02]
{F2 08 FF FF}{speed 6}> You threw all three Magatama in!
{wait}

[msg GO_KAGUTUTI speaker 1] // Voice
{F2 08 FF FF}{speed 6}You have proven yourself worthy.
Come to me.
{wait}

[msg SAIDAN_LAST]
{F2 08 FF FF}{speed 6}> Will you go to Kagutsuchi?
{wait}

[sel SAIDAN_LAST_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

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

[msg F037_DOOR01]
{F2 08 FF FF}{speed 6}> You sense a strong power
from beyond the door.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F037_YESNO_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F037_MANE01 speaker 4] // Female Manikin
{F2 08 FF FF}{speed 6}We've come pretty far up!
{wait}
---
{F2 08 FF FF}We're all taking a rest now.
We may be Manikins, but we're
no dummies!
{wait}

[msg F037_MANE02 speaker 5] // Male Manikin
{F2 08 FF FF}{speed 6}There's a Mantra demon up ahead...
{wait}
---
{F2 08 FF FF}He might hit us with his hammer
if we get near him. And I already
have a pounding headache.
{wait}

[msg F037_MANE02_02 speaker 5] // Male Manikin
{F2 08 FF FF}{speed 6}...Is the hammer demon gone?
{wait}

[msg F037_MANE03 speaker 5] // Male Manikin
{F2 08 FF FF}{speed 6}I'm tired of climbing...
{wait}

[msg F037_MANE05 speaker 6] // Manikin kid
{F2 08 FF FF}{speed 6}With everyone here, this place
reminds me of Asakusa!
{wait}

[msg F037_MANE06 speaker 7] // Old Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...Oh, it's you again.
{wait}
---
{F2 08 FF FF}I've decided to follow Futomimi's will
and create a world of Manikins!
{wait}
---
{F2 08 FF FF}So, I came all the way here, just to
tell Kagutsuchi: "Make it!"
{wait}
---
{F2 08 FF FF}But, there's a problem...
{wait}
---
{F2 08 FF FF}I can't think up a Reason!
{wait}

[msg F037_DEVIL01 speaker 8] // Demon
{F2 08 FF FF}{speed 6}What's going on!?
I'm back here again!?
{wait}
---
{F2 08 FF FF}I'll never make it to
Lady {firstname 3}'s side
at this rate!
{wait}
---
{F2 08 FF FF}Let me check my map...
{wait}

[msg F037_MANE04 speaker 5] // Male Manikin
{F2 08 FF FF}{speed 6}Did you know?
{wait}

[msg F037_MANE04_NO speaker 5] // Male Manikin
{F2 08 FF FF}{speed 6}There's an incredible treasure
hidden in this tower that can
manipulate life.
{wait}
---
{F2 08 FF FF}After climbing steep paths,
falling, scraping knees,
finally...
{wait}

[msg F037_MANE04_YES speaker 5] // Male Manikin
{F2 08 FF FF}{speed 6}Yeah, you climbed up this far;
I guess you'd know already.
{wait}

[msg F037_DEVIL02 speaker 8] // Demon
{F2 08 FF FF}{speed 6}I saw Kagutsuchi from the path
straight up north.
{wait}
---
{F2 08 FF FF}Hmph, how arrogant it looks...
{wait}

[msg F037_DEVIL02_01a speaker 8] // Demon
{F2 08 FF FF}{speed 6}Lady {firstname 3} is much more
elegant.
{wait}

[msg F037_DEVIL02_01b speaker 8] // Demon
{F2 08 FF FF}{speed 6}...Lady {firstname 3} was...
much more elegant...
{wait}

[msg F037_DEVIL03_01 speaker 8] // Demon
{F2 08 FF FF}{speed 6}If it isn't the Demi-fiend...
{wait}
---
{F2 08 FF FF}We've been waiting for you,
and that stone you have in
your hands.
{wait}
---
{F2 08 FF FF}Lady {firstname 3} is waiting for
you up ahead. Please go on through.
{wait}

[msg F037_DEVIL03_02 speaker 8] // Demon
{F2 08 FF FF}{speed 6}If it isn't the Demi-fiend...
{wait}
---
{F2 08 FF FF}I'm surprised you have the nerve to
even see us!
{wait}
---
{F2 08 FF FF}Lady {firstname 3} is up ahead.
{wait}
---
{F2 08 FF FF}Yosuga shall take that stone
you have in your hands.
...And your life.
{wait}

[msg F037_DEVIL03_01a speaker 8] // Demon
{F2 08 FF FF}{speed 6}Please lead us to the world of
Yosuga...
{wait}

[msg F037_DEVIL03_02a speaker 8] // Demon
{F2 08 FF FF}{speed 6}It... It can't be...
{wait}
---
{F2 08 FF FF}...Yosuga...
What will happen to Yosuga...?
{wait}
---
{F2 08 FF FF}Lady {firstname 3}......
{wait}
---
{F2 08 FF FF}............
{wait}

[msg F037_SINEN01_01 speaker 9] // Soul
{F2 08 FF FF}{speed 6}The top floor is up ahead.
{wait}
---
{F2 08 FF FF}If you want to see Kagutsuchi, you
need to offer the {color 1}three stones{color 0} to it.
{wait}
---
{F2 08 FF FF}The stones are proof of Reason, so
each leader should be carrying
them.
{wait}

[msg F037_SINEN01_02 speaker 9] // Soul
{F2 08 FF FF}{speed 6}The top floor is up ahead.
{wait}
---
{F2 08 FF FF}If you're ready, go to the pedestal
in front of the shrine.
{wait}

