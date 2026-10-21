// messages of fld/f/f031/f031
[speaker 0] Soul
[speaker 1] Cold-sounding woman
[speaker 2] Arrogant-sounding woman
[speaker 3] Cruel-sounding woman
[speaker 4] Women
[speaker 5] Cold-looking woman
[speaker 6] Clotho
[speaker 7] Arrogant-looking woman
[speaker 8] Lachesis
[speaker 9] Cruel-looking woman
[speaker 10] Atropos

[msg GIMMICK_TOUCH]
{F2 08 FF FF}{speed 6}> There is a glowing sphere...
{wait}
---
{F2 08 FF FF}> Will you touch it?
{wait}

[sel GIMMICK_TOUCH_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg CHANGE_AIR]
{F2 08 FF FF}{speed 6}> The atmosphere around you
changed.
{wait}

[msg REVERSE_AIR]
{F2 08 FF FF}{speed 6}> Will you revert the effects?
{wait}

[sel REVERSE_AIR_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg STEP1]
{F2 08 FF FF}{speed 6}> Time passed quickly.
{wait}

[msg RETURN_FLOOR]
{F2 08 FF FF}{speed 6}> Will you return?
{wait}

[sel RETURN_FLOOR_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg OBJ_UGOKANAI]
{F2 08 FF FF}{speed 6}> Nothing happened.
{wait}

[msg SINEN1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}There's blocks obstructing you?
{wait}

[sel SINEN1_SEL]
{F2 08 FF FF}They're blocking me.
---
{F2 08 FF FF}I'm not that square.

[msg SINEN1_YES speaker 0] // Soul
{F2 08 FF FF}{speed 6}I wanna go too, but I have no idea
what to do!
{wait}
---
{F2 08 FF FF}When I touched the glowing ball,
everything felt different...
{wait}
---
{F2 08 FF FF}For some reason, time felt like
it was just flying by.
{wait}
---
{F2 08 FF FF}It seems that the block lowers only
on certain cycles of Kagutsuchi...
{wait}
---
{F2 08 FF FF}Oh, yeah. If you take too much time,
the blocks will fall and drop on you!
{wait}
---
{F2 08 FF FF}If you figure it out, let me know.
{wait}

[msg SINEN1_NO speaker 0] // Soul
{F2 08 FF FF}{speed 6}Then, go home.
{wait}

[msg SINEN1_STOP]
{F2 08 FF FF}{speed 6}Hmmm...
{wait}

[msg SINEN1_STOP2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I'm sure it has something to do with
that mark engraved on it...
{wait}

[msg SANSIMAI_INFO1]
{F2 08 FF FF}{speed 6}> You sense a strong power.
{wait}

[msg KOUMAN1 speaker 1] // Cold-sounding woman
{F2 08 FF FF}{speed 6}Hahahahaha...
{wait}
---
{F2 08 FF FF}Just as Lord Hikawa predicted...
It seems a rat has wandered in!
{wait}

[msg HIJO1 speaker 2] // Arrogant-sounding woman
{F2 08 FF FF}{speed 6}Ohohoho...
{wait}
---
{F2 08 FF FF}I assume you are here for that
woman, but we three sisters are
guarding the Obelisk...
{wait}
---
{F2 08 FF FF}We are not like that useless Ose.
{wait}

[msg REIKOKU1 speaker 3] // Cruel-sounding woman
{F2 08 FF FF}{speed 6}Ahaha... If you want her back,
you must defeat us.
{wait}
---
{F2 08 FF FF}Well, if you can get to us in
the first place.
{wait}

[msg KOUMAN2 speaker 1] // Cold-sounding woman
{F2 08 FF FF}{speed 6}Kagutsuchi repeats the process of
birth and death. It will not wait
for you.
{wait}
---
{F2 08 FF FF}Now... Come!
{wait}

[msg SANSIMAI speaker 4] // Women
{F2 08 FF FF}{speed 6}Ahaha...
Hahahahaha...
Ohohoho...
{wait}

[msg SANSIMAI_INFO2]
{F2 08 FF FF}{speed 6}> The women disappeared.
{wait}

[msg KLOTHO speaker 5] // Cold-looking woman
{F2 08 FF FF}{speed 6}Hahahahaha... So, have you figured
out how the puzzle works?
{wait}

[msg KLOTHO2 speaker 5] // Cold-looking woman
{F2 08 FF FF}{speed 6}I am Clotho, the youngest of
the Moirae Sisters.
{wait}

[msg KLOTHO3 speaker 6] // Clotho
{F2 08 FF FF}{speed 6}I shall wind the thread of your life!
{wait}

[msg KLOTHO4 speaker 6] // Clotho
{F2 08 FF FF}{speed 6}Hahahahaha... You don't give up,
do you?
{wait}

[msg KLOTHO5 speaker 6] // Clotho
{F2 08 FF FF}{speed 6}If you like me that much, I can make
you our lover...
{wait}
---
{F2 08 FF FF}...But unfortunately, we have orders
from Lord Hikawa.
{wait}
---
{F2 08 FF FF}This time, I shall wind what's left of
your life!
{wait}

[msg LACHESIS speaker 7] // Arrogant-looking woman
{F2 08 FF FF}{speed 6}Ohohoho... I will not allow you
past here.
{wait}

[msg LACHESIS2 speaker 7] // Arrogant-looking woman
{F2 08 FF FF}{speed 6}I am Lachesis, the second of
the Moirae Sisters.
{wait}

[msg LACHESIS3 speaker 8] // Lachesis
{F2 08 FF FF}{speed 6}I measure the length of life.
{wait}
---
{F2 08 FF FF}Your thread is reaching its end!
{wait}

[msg LACHESIS4 speaker 8] // Lachesis
{F2 08 FF FF}{speed 6}Ohohoho... Persistent men are not
well-liked, you know!
{wait}

[msg LACHESIS5 speaker 8] // Lachesis
{F2 08 FF FF}{speed 6}It seems that my measurements
were a little off...
{wait}
---
{F2 08 FF FF}I shall end your life for sure
this time!
{wait}

[msg ATROPOS speaker 9] // Cruel-looking woman
{F2 08 FF FF}{speed 6}Ahaha... Were you able to keep up
with Kagutsuchi?
{wait}

[msg ATROPOS2 speaker 9] // Cruel-looking woman
{F2 08 FF FF}{speed 6}I am Atropos, the eldest of
the Moirae Sisters.
{wait}

[msg ATROPOS3 speaker 10] // Atropos
{F2 08 FF FF}{speed 6}How unlucky of you to meet me.
I cut the threads of fate...
In other words...
{wait}
---
{F2 08 FF FF}Your fate is already sealed!
{wait}

[msg ATROPOS4 speaker 10] // Atropos
{F2 08 FF FF}{speed 6}Ahaha... You again?
{wait}

[msg ATROPOS5 speaker 10] // Atropos
{F2 08 FF FF}{speed 6}Are you done with your prayers?
I will cut off any attachments
you have to this world!
{wait}

[msg BOSS3_01 speaker 6] // Clotho
{F2 08 FF FF}{speed 6}Hahahahaha...! We aren't letting you
pass that easily!
{wait}

[msg BOSS3_02 speaker 8] // Lachesis
{F2 08 FF FF}{speed 6}Do not underestimate us!
{wait}

[msg BOSS3_03 speaker 10] // Atropos
{F2 08 FF FF}{speed 6}We three Moirae Sisters will...
{wait}

[msg BOSS3_04 speaker 6] // Clotho
{F2 08 FF FF}{speed 6}Spin!
{wait}

[msg BOSS3_05 speaker 8] // Lachesis
{F2 08 FF FF}{speed 6}Measure!
{wait}

[msg BOSS3_06 speaker 10] // Atropos
{F2 08 FF FF}{speed 6}And snip your fate!!
{wait}

[msg TENJOH]
{F2 08 FF FF}{speed 6}> There is light coming from above.
{wait}
---
{F2 08 FF FF}> Will you ascend?
{wait}

[sel TENJOH_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg f031_H_GET]
{F2 08 FF FF}{speed 6}> You obtained the Magatama
{color 2}Djed{color 0}.
{wait}

[msg f031_FALL_DIE]
{F2 08 FF FF}{speed 6}> If you fall from here, you will lose
your life.
{wait}

[msg f031_YUUKO_RESCUE]
{F2 08 FF FF}{speed 6}> No one is here.
{wait}

[msg f031_GO_KAGUTUTI]
{F2 08 FF FF}{speed 6}> Will you go to the Tower of
Kagutsuchi?
{wait}

[sel f031_GO_KAG_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg BOSS_ROOM_IN]
{F2 08 FF FF}{speed 6}> You sense strong power from
the floor above.
{wait}
---
{F2 08 FF FF}> Will you go up?
{wait}

[sel BOSS_ROOM_SEL]
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

[msg F031_DOOR01]
{F2 08 FF FF}{speed 6}> The door is closed tight...
{wait}

[msg F031_SINEN_01_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}This is the Obelisk.
{wait}
---
{F2 08 FF FF}This is the closest you'll ever get to
Kagutsuchi, in all of Tokyo.
{wait}

[msg F031_SINEN_02_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Maiden is at the top floor.
{wait}
---
{F2 08 FF FF}She is collecting Magatsuhi with
her powers...
{wait}

[msg F031_SINEN_02_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I can't believe it...
{wait}
---
{F2 08 FF FF}You actually stopped the Nightmare
System...
{wait}
---
{F2 08 FF FF}............
{wait}

[msg F031_SINEN_03_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}This tower is protected by
the 'Moirae Sisters'.
{wait}
---
{F2 08 FF FF}As long as they're here, you won't
be able to catch even a glimpse of
the Maiden.
{wait}

[msg F031_SINEN_03_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Nooooo! The Moirae Sisters were...
{wait}

[msg F031_SINEN_04_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Moirae Sisters have set devices
to stop intruders.
{wait}
---
{F2 08 FF FF}You must control the flow of time.
...What does that mean? You will
soon find out...
{wait}

[msg F031_SINEN_04_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}............
{wait}

[msg F031_SINEN_05_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}You must touch the glowing sphere
and control time to deactivate
the device ahead.
{wait}
---
{F2 08 FF FF}But, if you take too much time,
the floor will crumble beneath you.
{wait}
---
{F2 08 FF FF}...A malevolent device, fitting of
the Moirae Sisters.
{wait}

[msg F031_SINEN_05_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hmm... Those devices appear to be
functioning, even though the sisters
were defeated.
{wait}

[msg F031_SINEN_06_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The pillar at the center of
the Obelisk sends collected
Magatsuhi to the bottom.
{wait}
---
{F2 08 FF FF}You saw all that Magatsuhi being
stored at the bottom, right?
{wait}

[msg F031_SINEN_06_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}There's no more Magatsuhi flowing
down the pillar...
{wait}

[msg F031_SINEN_07_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Now that the Nightmare System has
been activated, no one can stop
the Assembly of Nihilo.
{wait}
---
{F2 08 FF FF}The world of stillness is near...
{wait}

[msg F031_SINEN_07_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Nightmare System has been
stopped...
{wait}
---
{F2 08 FF FF}But, knowing Lord Hikawa, it
probably isn't a problem for
him...
{wait}

[msg F031_SINEN_08_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Dang, there it is again...
{wait}
---
{F2 08 FF FF}Do you hear it? The screaming of
a woman, coming from above?
{wait}
---
{F2 08 FF FF}...It's creepy!
{wait}

[msg F031_SINEN_08_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Come to think of it, I stopped
hearing that woman scream...
{wait}
---
{F2 08 FF FF}...That's just as creepy!
{wait}

[msg F031_SINEN_09 speaker 0] // Soul
{F2 08 FF FF}{speed 6}There must be some sort of pattern
to the movement of these blocks...
{wait}
---
{F2 08 FF FF}Is there anyplace where I can
overlook the entire area?
{wait}

[msg F031_SINEN_10 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Commander Hikawa will do anything
to realize his creation.
{wait}
---
{F2 08 FF FF}You never know... To him, even
the Maiden may just be...
{wait}

[msg F031_SINEN_11_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Below here is where the Nihilo hide
all their treasure.
{wait}
---
{F2 08 FF FF}But, no one who has gone looking
for it has ever come back alive...
{wait}

[msg F031_SINEN_11_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Go upstairs if you have business
with the Maiden.
{wait}

[msg F031_SINEN_12_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Moirae Sisters are waiting on
the floor above.
{wait}
---
{F2 08 FF FF}I hope you enjoy being tortured to
death...
{wait}

[msg F031_SINEN_12_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}You're not bad, defeating
the Moirae Sisters.
{wait}
---
{F2 08 FF FF}...Screw Hikawa, I should just follow
you!
{wait}

[msg F031_SINEN_12_03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Everyone went up. I don't think
you'll find a soul down below.
{wait}
---
{F2 08 FF FF}...Still, that was some earthquake.
{wait}

[msg F031_SINEN_13_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}The Moirae Sisters...
{wait}
---
{F2 08 FF FF}Clotho is the 'spinner'...
Um, what was Lachesis?
Atropos is the 'inevitable'...
{wait}
---
{F2 08 FF FF}Hmmm... One spins the thread,
the last one cuts it...
{wait}
---
{F2 08 FF FF}...What goes in the middle?
{wait}

[msg F031_SINEN_13_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I got it!
{wait}
---
{F2 08 FF FF}Lachesis is the 'apportioner'!
{wait}

[msg F031_SINEN_01_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}This is the Obelisk,
{wait}
---
{F2 08 FF FF}the only place in Tokyo that is
connected to Kagutsuchi.
{wait}
---
{F2 08 FF FF}Everyone went upstairs...
{wait}

