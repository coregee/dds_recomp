// messages of fld/f/f028/f028
[speaker 0] Isamu's shadow
[speaker 1] Hijiri
[speaker 2] Specter
[speaker 3] Soul
[speaker 4] Shadow

[sel YN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg EXIT]
{F2 08 FF FF}{speed 6}> Will you proceed?
{wait}

[msg ISAMU_R01 speaker 0] // Isamu's shadow
{F2 08 FF FF}{speed 6}Blah.
{wait}

[msg ISAMU_R02 speaker 0] // Isamu's shadow
{F2 08 FF FF}{speed 6}Blah.
{wait}

[msg ISAMU_R03 speaker 0] // Isamu's shadow
{F2 08 FF FF}{speed 6}Blah.
{wait}

[msg ISAMU_R04 speaker 0] // Isamu's shadow
{F2 08 FF FF}{speed 6}Blah.
{wait}
---
{F2 08 FF FF}Blah.
{wait}

[msg ISAMU_R05 speaker 0] // Isamu's shadow
{F2 08 FF FF}{speed 6}Blah.
{wait}

[msg HIJIRI_SYS_01]
{F2 08 FF FF}{speed 6}> You can hear a voice...
{wait}

[msg HIJIRI_01 speaker 1] // Hijiri
{F2 08 FF FF}{speed 6}Did... you find... {firstname 2}...?
{wait}

[sel HIJIRI_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg HIJIRI_01_YES speaker 1] // Hijiri
{F2 08 FF FF}{speed 6}...Really?
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}Then, get outta... there.
{wait}

[msg HIJIRI_01_NO speaker 1] // Hijiri
{F2 08 FF FF}{speed 6}He may be up... ahead. When you...
find... him... get yourself... out...
{wait}

[msg HIJIRI_02 speaker 1] // Hijiri
{F2 08 FF FF}{speed 6}The terminal's... acting... up...
{wait}
---
{F2 08 FF FF}It's not... like it... should be...
{wait}
---
{F2 08 FF FF}............
{wait}

[msg HIJIRI_SYS_02]
{F2 08 FF FF}{speed 6}> You cannot hear Hijiri's voice
anymore.
{wait}

[msg SPECTOR01 speaker 2] // Specter
{F2 08 FF FF}{speed 6}I, fiNaLLy, fOUnD yoUu...!!
{wait}
---
{F2 08 FF FF}YoooOoUUuuu!! I, LOoK, fOR
YOuuUU!!
{wait}
---
{F2 08 FF FF}ThIS, tiME, I kILL yOu aND fEeL
gOod!
{wait}

[msg SPECTOR02 speaker 2] // Specter
{F2 08 FF FF}{speed 6}FoR mY haPpiNeSS...
{wait}
---
{F2 08 FF FF}DiEEeeeeeEe...!!
{wait}

[msg SPECTOR_WIN]
{F2 08 FF FF}{speed 6}> You defeated Specter.
{wait}

[msg SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I do what I like.
{wait}
---
{F2 08 FF FF}No one tells me what to do...
{wait}

[msg SINEN02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I have the strength to be able to live
on my own.
{wait}
---
{F2 08 FF FF}Leave...
{wait}

[msg SINEN03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Society didn't shun me, I shunned
the society!
{wait}
---
{F2 08 FF FF}I don't need anyone else!
{wait}

[msg SINEN04 speaker 3] // Soul
{F2 08 FF FF}{speed 6}In the end, the only one you can
trust is yourself.
{wait}
---
{F2 08 FF FF}You need to create your own
future...
{wait}

[msg SINEN05 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I don't want to talk to anyone.
Scram!
{wait}

[msg SINEN06 speaker 3] // Soul
{F2 08 FF FF}{speed 6}I think, therefore I am...
{wait}

[msg SINEN07 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...To be strong is to be solitary.
{wait}

[msg MONBAN1 speaker 4] // Shadow
{F2 08 FF FF}{speed 6}..............................
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}.....................Hmm?.....
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}.....................Hmm......
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}.....................You......
{wait}

[msg MONBAN1_2ND speaker 4] // Shadow
{F2 08 FF FF}{speed 6}...Came...... again...
{wait}

[msg MONBAN1_Q speaker 4] // Shadow
{F2 08 FF FF}{speed 6}...You...... want to pass...?
{wait}

[sel MONBAN1_SEL]
{F2 08 FF FF}Yeah.........
---
{F2 08 FF FF}Not really...
---
{F2 08 FF FF}.............

[msg MONBAN1_Y speaker 4] // Shadow
{F2 08 FF FF}{speed 6}......I see......
{wait}

[msg MONBAN1_N speaker 4] // Shadow
{F2 08 FF FF}{speed 6}..............................
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}.......................Then...
{wait}
---
{F2 08 FF FF}......Go over there...........
{wait}

[msg MONBAN1_MUSI speaker 4] // Shadow
{F2 08 FF FF}{speed 6}..............................
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}.......................Then...
{wait}
---
{F2 08 FF FF}.....Stay there...............
{wait}

[msg MONBAN2 speaker 4] // Shadow
{F2 08 FF FF}{speed 6}..............................
{wait}
---
{F2 08 FF FF}..............................
{wait}
---
{F2 08 FF FF}.....................You......
{wait}
---
{F2 08 FF FF}.........What's your name.....?
{wait}

[sel MONBAN2_SEL]
{F2 08 FF FF}Say your name.
---
{F2 08 FF FF}Ignore him.

[msg MONBAN2_NANORU speaker 4] // Shadow
{F2 08 FF FF}{speed 6}......I see..................
{wait}
---
{F2 08 FF FF}...You're... {firstname 2}'s...
{wait}
---
{F2 08 FF FF}.............................
{wait}

[msg MONBAN2_MUSI speaker 4] // Shadow
{F2 08 FF FF}{speed 6}.............................
{wait}
---
{F2 08 FF FF}......You......... quiet.....
{wait}
---
{F2 08 FF FF}.............Cool............
{wait}

[msg MONBAN3 speaker 4] // Shadow
{F2 08 FF FF}{speed 6}.............................
{wait}
---
{F2 08 FF FF}....................You......
{wait}
---
{F2 08 FF FF}.........Solitude............
{wait}
---
{F2 08 FF FF}......You like... solitude...?
{wait}

[sel MONBAN3_SEL]
{F2 08 FF FF}Uh-huh.......
---
{F2 08 FF FF}Nah..........
---
{F2 08 FF FF}.............

[msg MONBAN3_Y speaker 4] // Shadow
{F2 08 FF FF}{speed 6}....................You......
{wait}
---
{F2 08 FF FF}......Understand.... maybe...
{wait}
---
{F2 08 FF FF}...................Cool......
{wait}

[msg MONBAN3_N speaker 4] // Shadow
{F2 08 FF FF}{speed 6}.....................You.....
{wait}
---
{F2 08 FF FF}......No good..... maybe.....
{wait}
---
{F2 08 FF FF}...Differ from... Master
{firstname 2}...
{wait}

[msg MONBAN3_MUSI speaker 4] // Shadow
{F2 08 FF FF}{speed 6}.............................
{wait}
---
{F2 08 FF FF}......You...... are cool.....
{wait}
---
{F2 08 FF FF}...................Cool......
{wait}

[msg MONBAN4 speaker 4] // Shadow
{F2 08 FF FF}{speed 6}..............................
{wait}
---
{F2 08 FF FF}......Can......... you.........
{wait}
---
{F2 08 FF FF}........live...... on your own?
{wait}

[sel MONBAN4_SEL]
{F2 08 FF FF}Of course........
---
{F2 08 FF FF}Don't think so...
---
{F2 08 FF FF}.............

[msg MONBAN4_Y speaker 4] // Shadow
{F2 08 FF FF}{speed 6}...............I see.............
{wait}
---
{F2 08 FF FF}......Keep...... it up............
{wait}
---
{F2 08 FF FF}...I'll... live on my own... too...
{wait}
---
{F2 08 FF FF}......I am........... you.........
{wait}

[msg MONBAN4_N speaker 4] // Shadow
{F2 08 FF FF}{speed 6}..................I see..........
{wait}
---
{F2 08 FF FF}...Talk to... Master {firstname 2}...
{wait}
---
{F2 08 FF FF}...We all...... live on our own...
{wait}
---
{F2 08 FF FF}...You are............ me.........
{wait}

[msg MONBAN4_MUSI speaker 4] // Shadow
{F2 08 FF FF}{speed 6}.............................
{wait}
---
{F2 08 FF FF}...Talk to... Master {firstname 2}...
{wait}
---
{F2 08 FF FF}...We all... live on our own...
{wait}
---
{F2 08 FF FF}...You are............ me......
{wait}

[msg MONBAN_END_SYS]
{F2 08 FF FF}{speed 6}> The shadow disappeared.
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

[msg F028_KAIFUKU_01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...You again?
{wait}
---
{F2 08 FF FF}How many times you plan on comin'
here? I don't want to talk to no one!
{wait}
---
{F2 08 FF FF}I'll heal you, so just go home...
Pest.
{wait}

[msg F028_KAIFUKU_02]
{F2 08 FF FF}{speed 6}> ............
{wait}
---
{F2 08 FF FF}> You have been healed.
{wait}

[msg F028_KAIFUKU_03 speaker 3] // Soul
{F2 08 FF FF}No matter how many times
you visit me, I'll heal you.
Anything to make you go away!
{wait}

[msg F028_SINEN01 speaker 3] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}Geez, we've been having a lot of
visitors lately!
{wait}
---
{F2 08 FF FF}A human kid came in and began
living here not too long ago.
{wait}
---
{F2 08 FF FF}Well, I don't care who comes,
as long as they don't bother me.
{wait}

[msg F028_SINEN02 speaker 3] // Soul
{F2 08 FF FF}{speed 6}...What?
{wait}
---
{F2 08 FF FF}You seem friendly, but I'm not in
the mood for chatting.
{wait}
---
{F2 08 FF FF}"Believe no one."
"The truth is within you!"
You've heard it all before, right?
{wait}
---
{F2 08 FF FF}So, keep it to yourself, would you?
{wait}
---
{F2 08 FF FF}...Um, I'm babbling, aren't I?
{wait}

[msg F028_SINEN03 speaker 3] // Soul
{F2 08 FF FF}{speed 6}Are you planning to continue on
ahead, mister? I wouldn't!
{wait}
---
{F2 08 FF FF}No one likes to be disturbed...
{wait}
---
{F2 08 FF FF}And if you try to force your way
through, you'll run into even more
trouble!
{wait}

[msg F028_SINEN04 speaker 3] // Soul
{F2 08 FF FF}{speed 6}OoOoHh...YoOOuuUUuuu!!
{wait}
---
{F2 08 FF FF}...That's what a demon I just met
over there said.
{wait}
---
{F2 08 FF FF}But, he was much madder...
and fiercer...
{wait}

[msg F028_SINEN speaker 3] // Soul
{F2 08 FF FF}{speed 6}OoOoHh...YoOOuuuuUUuuu!!
{wait}
---
{F2 08 FF FF}...Oh! Did I scare you? I'm trying to
impersonate that demon I met.
{wait}
---
{F2 08 FF FF}But, it's no good! I gotta be
madder... and fiercer...!
{wait}

