// messages of fld/f/f036/f036
[speaker 0] Cerberus
[speaker 1] Debug MES
[speaker 2] Demon
[speaker 3] Soul

[msg MIDDLE_BOSS01 speaker 0] // Cerberus
{F2 08 FF FF}{speed 6}LONG TIME NO SEE...
{wait}
---
{F2 08 FF FF}YOUR BEING HERE MEANS THAT
YOU ARE TRYING TO CREATE
A NEW WORLD...
{wait}
---
{F2 08 FF FF}I WON'T ALLOW IT!
{wait}
---
{F2 08 FF FF}I DON'T LIKE THE WORLD
YOU'RE TRYING TO MAKE...
{wait}
---
{F2 08 FF FF}SO...
{wait}
---
{F2 08 FF FF}I WON'T LET YOU GO ANY
FURTHER!
{wait}
---
{F2 08 FF FF}DIE!
{wait}

[msg MIDDLE_BOSS02 speaker 0] // Cerberus
{F2 08 FF FF}{speed 6}LONG TIME NO SEE...
{wait}
---
{F2 08 FF FF}YOUR BEING HERE MEANS THAT
YOU ARE TRYING TO CREATE
A NEW WORLD...
{wait}
---
{F2 08 FF FF}I DON'T CARE WHAT YOU DO...
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}...ON SECOND THOUGHT...
{wait}
---
{F2 08 FF FF}THE WORLD YOU'RE TRYING TO
CREATE...
{wait}
---
{F2 08 FF FF}I THINK I WANT TO SEE IT.
{wait}
---
{F2 08 FF FF}ALRIGHT, I WILL HELP YOU
CREATE THE WORLD!
{wait}
---
{F2 08 FF FF}NO NEED TO WORRY, NOW THAT
I'M HERE.
{wait}
---
{F2 08 FF FF}HAHAHAHAHAHA!
{wait}

[msg MIDDLE_BOSS03]
{F2 08 FF FF}{speed 6}> Cerberus joined your party.
{wait}

[msg f036_MES01 speaker 1] // Debug MES
{F2 08 FF FF}Select your Reason.
{wait}

[sel f036_MES01_SEL]
{F2 08 FF FF}Shijima.
---
{F2 08 FF FF}Musubi.
---
{F2 08 FF FF}Yosuba.
---
{F2 08 FF FF}None.

[msg AREA6_NPC_01 speaker 2] // Demon
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}...Shijima's... Ahriman...
...How frightening...
{wait}
---
{F2 08 FF FF}...I will share with you...
the fear... I have felt...
{wait}

[msg AREA6_NPC_02 speaker 2] // Demon
{F2 08 FF FF}{speed 6}> You obtained the {color 1}memory of
the battle against Ahriman{color 0}.
{wait_nospeaker}{F2 08 FF FF}{wait}
---
{F2 08 FF FF}Ugh...!
{wait}

[msg AREA6_NPC_03 speaker 2] // Demon
{F2 08 FF FF}{speed 6}...Shijima's... Ahriman...
...How frightening...
{wait}
---
{F2 08 FF FF}Ugh...!
{wait}

[msg AREA6_NPC_04]
{F2 08 FF FF}{speed 6}> The demon disappeared.
{wait}

[msg AREA20_NPC_01 speaker 2] // Demon
{F2 08 FF FF}{speed 6}She did it... She did it!
...We've... won...!
{wait}
---
{F2 08 FF FF}Musubi... is... no more...
{wait}
---
{F2 08 FF FF}I leave you with the power...
of Yosuga... Make sure to pass...
on... our legacy...!
{wait}

[msg AREA20_NPC_02 speaker 2] // Demon
{F2 08 FF FF}{speed 6}> You obtained the {color 1}memory of
the battle against Noah{color 0}.
{wait_nospeaker}{F2 08 FF FF}{wait}
---
{F2 08 FF FF}Hahaha...... Yosuga... will...
create the world!!!!
{wait}
---
{F2 08 FF FF}Ugh...!
{wait}

[msg AREA20_NPC_03 speaker 2] // Demon
{F2 08 FF FF}{speed 6}Dammit... Damn... Musubi!
{wait}
---
{F2 08 FF FF}...But, we have...
Lady {firstname 3}......
{wait}
---
{F2 08 FF FF}...Yosuga... will be the ones
to create the world!!!!
{wait}
---
{F2 08 FF FF}Ugh...!
{wait}

[msg AREA20_NPC_04]
{F2 08 FF FF}{speed 6}> The demon disappeared.
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

[msg F036_DOOR01]
{F2 08 FF FF}{speed 6}> You sense a strong power
from beyond the door.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F036_YESNO_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F036_DEVIL01 speaker 2] // Demon
{F2 08 FF FF}{speed 6}That hot chick is here, too.
{wait}
---
{F2 08 FF FF}...DAMN, she's hot!
{wait}

[msg F036_SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Up ahead, the floor appears and
disappears.
{wait}
---
{F2 08 FF FF}If you go the wrong way...
You'll get a taste of gravity.
{wait}
---
{F2 08 FF FF}Darkness awaits you.
{wait}

[msg F036_SINEN02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}This is one tall tower.
We're only halfway up?
{wait}
---
{F2 08 FF FF}...Well, no need to worry about
{firstname 2}. He's eaten all that
Magatsuhi, after all.
{wait}

[msg F036_SINEN02_02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...Are you the Demi-fiend that beat
{firstname 2}?
{wait}

[msg F036_SINEN02_02YES speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}......Why......?
{wait}
---
{F2 08 FF FF}Why don't you understand Musubi?
{wait}

[msg F036_SINEN02_02NO speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}......Liar.
{wait}
---
{F2 08 FF FF}Don't talk to me.
{wait}

[msg F036_SINEN03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}Are you the Demi-fiend?
{wait}

[msg F036_SINEN03_YES speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}I see......
{wait}
---
{F2 08 FF FF}Then, go in. {firstname 2} is
waiting...
{wait}

[msg F036_SINEN03_NO speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}Then... scram...
{wait}

[msg F036_SINEN03_02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}A girl......
{wait}
---
{F2 08 FF FF}......It was a girl......
{wait}
---
{F2 08 FF FF}{firstname 2} was defeated...
by... a girl...
{wait}
---
{F2 08 FF FF}...In...side......
{wait}

[msg F036_SINEN03_03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}Even if... we can't create...
the world of... Musubi...
{wait}
---
{F2 08 FF FF}I'll strive to exist... on my own...
{wait}
---
{F2 08 FF FF}It doesn't... matter... that
{firstname 2} is dead...
{wait}

