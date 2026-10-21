// messages of fld/f/f012/f012
[speaker 0] Berith
[speaker 1] Soul

[msg HAKABA]
{F2 08 FF FF}{speed 6}> There is mud left lying around.
{wait}
---
{F2 08 FF FF}> The mud is shaped somewhat like
bodies.
{wait}

[msg SHIMI01]
{F2 08 FF FF}{speed 6}> There is a stain in the shape of
a human.
{wait}
---
{F2 08 FF FF}> Something is in its hand.
Will you take it?
{wait}

[sel SHIMI01_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg SHIMI02]
{F2 08 FF FF}{speed 6}> You obtained the {color 1}Afterlife Bell{color 0}.
{wait}

[msg SHIMI03]
{F2 08 FF FF}{speed 6}> There is a stain in the shape of
a human.
{wait}

[msg F20_AREA01_MOBAHN1 speaker 0] // Berith
{F2 08 FF FF}{speed 6}Halt!
{wait}
---
{F2 08 FF FF}This is the {color 1}Assembly of Nihilo{color 0},
the place for those who seek
silence.
{wait}
---
{F2 08 FF FF}I cannot let anyone see
our commander or the Maiden.
{wait}
---
{F2 08 FF FF}Leave these grounds immediately!
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

[msg F012_SINEN01_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}If you travel north from here,
you'll reach {color 1}Ikebukuro{color 0}.
{wait}
---
{F2 08 FF FF}All the Mantra demons are there.
May their souls rest in peace...
{wait}

[msg F012_SINEN01_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}I heard Gozu-Tennoh was defeated.
May his soul rest in peace...
{wait}

[msg F012_SINEN01_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}I hear something's going on at
the Mantra's headquarters.
May their souls rest in peace...
{wait}

[msg F012_SINEN01_04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}I heard the ghost of Gozu-Tennoh
went inside a human girl.
{wait}
---
{F2 08 FF FF}Yosuga, was it?
May their souls rest in peace...
{wait}

[msg F012_SINEN01_05 speaker 1] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}The Manikin over there died...
{wait}
---
{F2 08 FF FF}He died the instant he became
human.
{wait}
---
{F2 08 FF FF}You see, humans can't live
in the Vortex World...
May his soul rest in peace...
{wait}

