// messages of fld/f/f039/f039
[speaker 0] Bishamon

[msg f039_KITA]
{F2 08 FF FF}{speed 6}> There is a temple.
{wait}

[sel f039_SEL0]
{F2 08 FF FF}Have {color 1}Bishamon's thing{color 0}.
---
{F2 08 FF FF}Don't have it.

[msg f039_KITA02]
{F2 08 FF FF}{speed 6}> The {color 1}Kimon Stone{color 0} began to shine.
{wait}

[msg f039_KITA02_02]
{F2 08 FF FF}{speed 6}> The seal has been broken.
{wait}

[msg f039_KITA03]
{F2 08 FF FF}{speed 6}> Will you enter?
{wait}

[sel f039_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg f039_KITA04]
{F2 08 FF FF}{speed 6}> The temple is sealed with a powerful
spell.
{wait}

[msg f039_INAI]
{F2 08 FF FF}{speed 6}> No one is here.
{wait}

[msg f039_BOSS01 speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}So, it is you, {firstname 0},
who has broken my seal!
{wait}
---
{F2 08 FF FF}I have heard rumors of you.
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}But, I sense something different
about you...
{wait}
---
{F2 08 FF FF}You are not an ordinary demon,
are you?
{wait}

[sel f039_B_SEL]
{F2 08 FF FF}That's right.
---
{F2 08 FF FF}I'm average.

[sel f039_B_SEL2]
{F2 08 FF FF}Sure.
---
{F2 08 FF FF}I'll pass.

[msg f039_BOSS01_02YES speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}Ha! I knew it!
{wait}
---
{F2 08 FF FF}Then, show me what power
you possess!!
{wait}

[msg f039_BOSS01_02NO speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}You are humble. Very well.
{wait}
---
{F2 08 FF FF}So, how about it, {firstname 0}?
Will you fight me?
{wait}
---
{F2 08 FF FF}There is no need to hold back!
{wait}

[msg f039_BOSS01_03]
{F2 08 FF FF}{speed 6}> Do you accept Bishamon's
challenge?
{wait}

[msg f039_BOSS01_03YES speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}I guarded the Tokyo of old with
my comrades.
{wait}
---
{F2 08 FF FF}I will show you my power!
{wait}

[msg f039_BOSS01_03NO speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}What a bore...
{wait}
---
{F2 08 FF FF}Begone!
{wait}

[msg f039_BOSS01_04 speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}Now, do you feel like fighting me?
{wait}

[msg BOSS02 speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}...Hmmm!
{wait}
---
{F2 08 FF FF}Just as he said, your powers are
far greater than what I have
imagined.
{wait}
---
{F2 08 FF FF}Now, like my comrades, I must lend
my powers to him.
{wait}
---
{F2 08 FF FF}I would like to fight you again,
but...
{wait}
---
{F2 08 FF FF}...I must be going.
{wait}

[msg BOSS02_02 speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}Take this.
{wait}

[msg H_GET]
{F2 08 FF FF}{speed 6}> You obtained the Magatama
{color 2}Gundari{color 0}.
{wait}

[msg BOSS02_03 speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}If you have enough power to obtain
all of these...
{wait}
---
{F2 08 FF FF}Then, you will be able to set foot
into the world I am going to.
{wait}

[msg BOSS02_04 speaker 0] // Bishamon
{F2 08 FF FF}{speed 6}If that should happen... then we shall
meet again!
{wait}

[msg BOSS03]
{F2 08 FF FF}{speed 6}> Bishamon disappeared.
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
{F2 08 FF FF}{speed 6}> Message Test
Now, for the basics...
{wait}

[msg INFTEST1]
{F2 08 FF FF}{speed 6}> Message Test
Next are the choices.
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

