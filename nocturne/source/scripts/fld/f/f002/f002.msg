// messages of fld/f/f002/f002
[speaker 0] Soul

[msg SINJIKU]
{F2 08 FF FF}{speed 6}> Shinjuku Station...
{wait}
---
{F2 08 FF FF}> It's as quiet as a tomb.
{wait}

[msg SINJIKU2]
{F2 08 FF FF}{speed 6}> Nothing is showing on
the giant screen...
{wait}

[msg KOKOTOKYO speaker 0] // Soul
{F2 08 FF FF}{speed 6}You don't know where you are?
...You're joking, right?
{wait}
---
{F2 08 FF FF}Tokyo, of course!
{wait}
---
{F2 08 FF FF}All of the humans are gone, though.
{wait}

[msg KOKOTOKYO2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hmmm... I just passed through
Shinjuku, so...
{wait}
---
{F2 08 FF FF}If I go south, I should reach
Yoyogi and Shibuya.
{wait}

[msg KOKOTOKYO3 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I just saw a girl heading toward
Shibuya.
{wait}
---
{F2 08 FF FF}I guess she really was a human...
{wait}
---
{F2 08 FF FF}What? You're a human, too!?
{wait}
---
{F2 08 FF FF}Or... are you a demon?
{wait}

[msg KOKOTOKYO4 speaker 0] // Soul
{F2 08 FF FF}{speed 6}*squint* I can see Aoyama over there...
I think.
{wait}
---
{F2 08 FF FF}Looks like it's safe.
{wait}
---
{F2 08 FF FF}But, you can't get there from here.
{wait}
---
{F2 08 FF FF}I already tried going from
Yoyogi Park, and that didn't work...
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

[msg INFTEST1_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}No, you say?
{wait}

[msg F002_SINEN_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}...Huh?
{wait}
---
{F2 08 FF FF}How'd you get out of the hospital?
{wait}
---
{F2 08 FF FF}Wasn't Forneus there?
{wait}

[msg F002_SINEN_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Whatcha lookin' around for?
This your first time in Tokyo?
{wait}

[sel F002_SINEN_02_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F002_SINEN_02_YES speaker 0] // Soul
{F2 08 FF FF}{speed 6}Then, let me tell you something.
This is Shinjuku, and if you go south
from here...
{wait}
---
{F2 08 FF FF}...Well, Tokyo's round, so I'm just
talking relatively here...
{wait}
---
{F2 08 FF FF}If you go south, you'll see
{color 1}Yoyogi Park{color 0} and {color 1}Shibuya{color 0}.
{wait}
---
{F2 08 FF FF}Speaking of which, I saw a human
head toward Shibuya.
{wait}

[msg F002_SINEN_02_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}I see... It's my first time here.
{wait}
---
{F2 08 FF FF}Hmm, according to the guide map...
{wait}

[msg F002_SINEN_02_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}It's like we're all stuck inside of
a sphere here in Tokyo.
{wait}
---
{F2 08 FF FF}Hmmm... Ginza isn't on this side of
the sphere, it seems.
{wait}
---
{F2 08 FF FF}...Man, Tokyo's nothing like
what the guide map says!
{wait}

[msg F002_SINEN_02_03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}...I see.
{wait}
---
{F2 08 FF FF}Shinjuku, Ginza, Ikebukuro,
Asakusa... Then, back around to
Shinjuku.
{wait}
---
{F2 08 FF FF}Tokyo's round, after all...
{wait}

[msg F002_SINEN_02_04 speaker 0] // Soul
{F2 08 FF FF}{speed 6}...I'm getting the hang of it.
{wait}
---
{F2 08 FF FF}The Obelisk of Chiyoda and
the Amala Temple of Sannou...
{wait}
---
{F2 08 FF FF}These two spots are sandwiching
Kagutsuchi from the top and bottom.
{wait}
---
{F2 08 FF FF}...Well, there is no up or down in
Tokyo, since it's round...
{wait}

[msg F002_SINEN_03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}By gum!
{wait}
---
{F2 08 FF FF}It's just like I said...
The world's all round!
{wait}
---
{F2 08 FF FF}But even now, no one believes me!
{wait}
---
{F2 08 FF FF}I hear prophecies from Jupiter!
You believe me, don'tcha? *hic*
{wait}

[sel F002_SINEN_03_SEL]
{F2 08 FF FF}Of course I do.
---
{F2 08 FF FF}You're too whiny.

[msg F002_SINEN_03_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}By gum! Why doesn't anyone
believe me? *hic*
{wait}

[msg F002_SINEN_03_YES speaker 0] // Soul
{F2 08 FF FF}{speed 6}Oh! You believe me!?
{wait}
---
{F2 08 FF FF}Then, I'll tell you somethin' good!
{wait}
---
{F2 08 FF FF}The 'Demi-fiend' is the one that's
going to create the new world...
{wait}
---
{F2 08 FF FF}By gum! You wouldn't be... Naw!
*hic*
{wait}

[msg F002_SINEN_04 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hey, if it isn't {firstname 0}.
{wait}
---
{F2 08 FF FF}...Have you heard of the Tokyo
rumor?
{wait}

[sel F002_SINEN_04_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F002_SINEN_04_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}A guy with a strong will is going to
change this chaotic world...
{wait}
---
{F2 08 FF FF}...That's a good one, huh?
Tokyo's forever in chaos!
Hahahahahahaha!!
{wait}

[msg F002_SINEN_04_YES speaker 0] // Soul
{F2 08 FF FF}{speed 6}...Well, it's just a rumor!
Hahahahahahaha!!
{wait}

[msg F002_SINEN_05 speaker 0] // Soul
{F2 08 FF FF}{speed 6}You can see Yoyogi Park from here.
{wait}
---
{F2 08 FF FF}I wonder if the east side of the park
is being occupied by the fairies.
{wait}

[msg F002_SINEN_05_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I saw all these fairies fly off from
Yoyogi Park.
{wait}

[msg F002_SINEN_05_03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Kagutsuchi's shining bright...
{wait}

