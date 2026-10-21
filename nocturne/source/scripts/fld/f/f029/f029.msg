// messages of fld/f/f029/f029
[speaker 0] Soul
[speaker 1] Male Manikin

[msg F29_AREA1_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}This subway leads to Yoyogi Park.
{wait}

[msg F29_AREA2_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Yoyogi's the place where a bunch of
demonstrators died, right?
{wait}
---
{F2 08 FF FF}That's scary!!
{wait}

[msg F29_AREA2_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hey you!! How many times do I have
to tell you?
{wait}
---
{F2 08 FF FF}Stay behind the white line!
{wait}

[msg F29_AREA2_NPC3 speaker 0] // Soul
{F2 08 FF FF}{speed 6}There still seems to be demons
running around Yoyogi.
{wait}

[msg F29_AREA2_NPC4 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Are you going to Yoyogi Park to
participate in the demonstration?
{wait}

[msg F29_AREA7_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Violence cannot be forgiven!!
{wait}

[msg F29_AREA7_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}We are demonstrators that work
hard to make a better city!!
{wait}

[msg F29_AREA7_NPC3 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Apathy is not the answer! We must
fight for what we believe in!!
{wait}

[msg F29_AREA7_NPC4 speaker 0] // Soul
{F2 08 FF FF}{speed 6}What the heck?! What's up with all
these souls?
{wait}

[msg F29_AREA7_NPC5 speaker 0] // Soul
{F2 08 FF FF}{speed 6}For a future without discrimination!
For a city our children can play in!!
{wait}

[msg F29_AREA8_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Yoyogi Park is just beyond the exit.
{wait}
---
{F2 08 FF FF}Now, let's join together and fight for
our beliefs!!
{wait}

[msg F29_AREA8_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Protect our children from
the temptations of juvenile
delinquency!!
{wait}

[msg F29_AREA8_NPC3 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I'll fight it, even if I'm the only one
doing it!
{wait}
---
{F2 08 FF FF}I demand that the government not
not censor my pornography!
{wait}
---
{F2 08 FF FF}...Oops.
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

[msg F029_MANE_DEAD]
{F2 08 FF FF}{speed 6}> There is no response from
the Manikin.
{wait}

[msg F029_MANE01 speaker 1] // Male Manikin
{F2 08 FF FF}{speed 6}J-J-Just awhile back, Sakahagi...
went to Yoyogi...
{wait}
---
{F2 08 FF FF}Th-Th-Thank goodness it was
dark...
{wait}

[msg F029_SINEN01_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}A vicious-looking Manikin passed
by a short while back.
{wait}
---
{F2 08 FF FF}After that, a female human passed
by.
{wait}
---
{F2 08 FF FF}It's usually quiet here, but...
{wait}

[msg F029_SINEN01_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}This is a rather quiet place,
compared to Tokyo in general.
{wait}

[msg F029_SINEN02_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Yoyogi Park is the place that
all the fairies are guarding.
{wait}
---
{F2 08 FF FF}That vicious Manikin won't be able
to do anything just by himself.
{wait}

[msg F029_SINEN02_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}That lady who was heading to
Yoyogi Park was lookin' fiiiiiine!
{wait}

