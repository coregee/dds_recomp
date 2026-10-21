// messages of fld/f/f003/f003
[speaker 0] Guard
[speaker 1] Soul

[msg NIHIRO speaker 0] // Guard
{F2 08 FF FF}{speed 6}Go home!
{wait}

[msg SUBWAY]
{F2 08 FF FF}{speed 6}> Yurakucho Station.
{wait}
---
{F2 08 FF FF}> The entrance is closed tight.
{wait}

[msg KOUSOKU speaker 0] // Guard
{F2 08 FF FF}{speed 6}Everything from here on is under
the Assembly of Nihilo's direct
control!
{wait}
---
{F2 08 FF FF}I can't let a suspicious demon,
like you, through here!
{wait}
---
{F2 08 FF FF}So, get outta here, right now!
{wait}

[msg SHIBA1 speaker 1] // Soul
{F2 08 FF FF}{speed 6}It's dangerous 'round these parts!
{wait}
---
{F2 08 FF FF}There're nothin' but strong demons
from here on out. And I mean,
strong demons!!
{wait}
---
{F2 08 FF FF}They'll mop the floor with a weak
demon, like you...
{wait}
---
{F2 08 FF FF}And I mean, mop the floor!!
{wait}

[msg SHIBA2 speaker 1] // Soul
{F2 08 FF FF}{speed 6}I know you! 
{wait}
---
{F2 08 FF FF}You're that kid who fought it out
with the Nihilo, right?
{wait}
---
{F2 08 FF FF}That's incredible!! A runt, like you,
beating them!!
{wait}

[msg TOJINIHIRO]
{F2 08 FF FF}{speed 6}> The Assembly of Nihilo.
{wait}
---
{F2 08 FF FF}> The door is tightly shut.
{wait}

[msg TOJINIHIRO2]
{F2 08 FF FF}{speed 6}> The Assembly of Nihilo.
Second Entrance.
{wait}
---
{F2 08 FF FF}> The door is tightly shut.
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

[msg F003_SINEN01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Do you see the other
Assembly of Nihilo building
across the railroad tracks?
{wait}
---
{F2 08 FF FF}It doesn't look like the Mantra
attacked that one.
{wait}

[msg F003_SINEN01_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The demons of Nihilo have returned
to Ginza.
{wait}

[msg F003_SINEN01_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}It looks like the new world will
finally be made.
{wait}
---
{F2 08 FF FF}...What kind of world are you hoping
for?
{wait}

[msg F003_SINEN02_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}See that building that's eating up
the Magatsuhi of Tokyo?
{wait}
---
{F2 08 FF FF}That's the Assembly of Nihilo.
{wait}

[msg F003_SINEN02_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Mantra attacked the Assembly
of Nihilo.
{wait}
---
{F2 08 FF FF}Is this the end of Nihilo?
{wait}

[msg F003_SINEN02_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}What's going on?
Didn't the Mantra win???
{wait}
---
{F2 08 FF FF}I heard that a bunch of Magatsuhi
was sucked up from Ikebukuro!!
{wait}

[msg F003_SINEN02_04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Assembly of Nihilo sure is
quiet...
{wait}

[msg F003_SINEN02_05 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Nihilo demons were all worked
up!
{wait}
---
{F2 08 FF FF}They were saying something about
how 'now is the time for creation'!
Weird, huh?
{wait}

[msg F003_SINEN03_00 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Have you already met {color 1}Madame Nyx
at the bar{color 0} in Ginza?
{wait}

[sel F003_SINEN03_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F003_SINEN03_00YES speaker 1] // Soul
{F2 08 FF FF}{speed 6}She's so nice, listening to
everyone's worries!
{wait}
---
{F2 08 FF FF}She's helped me out so many times
when I was in trouble. Her advice is
priceless!
{wait}

[msg F003_SINEN03_00NO speaker 1] // Soul
{F2 08 FF FF}{speed 6}She may technically be a demon...
But she's real nice and will listen to
your worries!
{wait}
---
{F2 08 FF FF}You should see her whenever you're
troubled.
{wait}

[msg F003_SINEN03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}There's a place to get into
the Great Underpass of Ginza
somewhere around here...
{wait}

[msg F003_SINEN04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Hmmm... I guess it's not that easy
to find...
{wait}
---
{F2 08 FF FF}Demons with the {color 1}Lucky Find{color 0} skill can
can supposedly find stuff by just
walking around outside.
{wait}
---
{F2 08 FF FF}So, I was trying to do that.
I mean, I could use the treasure!
But, I guess it's not working...
{wait}

[msg F003_SINEN05 speaker 1] // Soul
{F2 08 FF FF}Hey, hey! There's a bunch of
dangerous demons on the other
end of the highway!
{wait}

[msg F003_SINEN06 speaker 1] // Soul
{F2 08 FF FF}{speed 6}This region is Nihilo's
top priority.
{wait}
---
{F2 08 FF FF}The security here is super-tight.
{wait}

