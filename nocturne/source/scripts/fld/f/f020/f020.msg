// messages of fld/f/f020/f020
[speaker 0] Mysterious demon
[speaker 1] Demon guard
[speaker 2] Hijiri
[speaker 3] Voice
[speaker 4] Small terminal
[speaker 5] Eligor
[speaker 6] Berith
[speaker 7] Ose
[speaker 8] Kaiwan
[speaker 9] Kaiwan's voice
[speaker 10] Koppa
[speaker 11] Incubus
[speaker 12] Demons
[speaker 13] Soul
[speaker 14] Demon

[msg SECOND_ENT]
{F2 08 FF FF}> Light is coming from the hole. 
{wait}
---
{F2 08 FF FF}> Will you hold your hand over it?
{wait}

[msg SWITCH]
{F2 08 FF FF}{speed 6}> There's a switch.
{wait}
---
{F2 08 FF FF}> Will you operate it?
{wait}

[sel YN_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg CUBE_GARD01 speaker 0] // Mysterious demon
{F2 08 FF FF}{speed 6}Oh, no you don't!
{wait}
---
{F2 08 FF FF}I won't let you get past here.
{wait}
---
{F2 08 FF FF}How's this?
{wait}

[msg CUBE_GARD01_01]
{F2 08 FF FF}{speed 6}> The demon has operated the switch.
{wait}

[msg CUBE_GARD02 speaker 1] // Demon guard
{F2 08 FF FF}How dare you!! You're dead meat!!
{wait}

[msg CUBE_GARD03]
{F2 08 FF FF}> You defeated the demon guard.
{wait}

[msg SAIDAN01_01]
{F2 08 FF FF}{speed 6}> There is a pedestal emitting
white light...
{wait}

[msg SAIDAN02_01]
{F2 08 FF FF}{speed 6}> There is a pedestal emitting
yellow light...
{wait}

[msg SAIDAN03_01]
{F2 08 FF FF}{speed 6}> There is a pedestal emitting
green light...
{wait}

[msg SAIDAN04_01]
{F2 08 FF FF}{speed 6}> There is a pedestal emitting
red light...
{wait}

[msg SAIDAN01_02]
{F2 08 FF FF}{speed 6}> Will you use the White Kila?
{wait}

[msg SAIDAN02_02]
{F2 08 FF FF}{speed 6}> Will you use the Yellow Kila?
{wait}

[msg SAIDAN03_02]
{F2 08 FF FF}{speed 6}> Will you use the Green Kila?
{wait}

[msg SAIDAN04_02]
{F2 08 FF FF}{speed 6}> Will you use the Red Kila?
{wait}

[msg SAIDAN01_04]
{F2 08 FF FF}{speed 6}> The pedestal is no longer emitting
light.
{wait}

[msg SAIDAN02_04]
{F2 08 FF FF}{speed 6}> The pedestal is no longer emitting
light.
{wait}

[msg SAIDAN03_04]
{F2 08 FF FF}{speed 6}> The pedestal is no longer emitting
light.
{wait}

[msg SAIDAN04_04]
{F2 08 FF FF}{speed 6}> The pedestal is no longer emitting
light.
{wait}

[msg TURO_NG]
{F2 08 FF FF}{speed 6}> The floor is too unstable to proceed
ahead.
{wait}

[msg TURO_OK]
{F2 08 FF FF}{speed 6}> The floor is stable.
{wait}

[msg HIJIRI01 speaker 2] // Hijiri
{F2 08 FF FF}This dome is camouflage; the real
thing is downstairs.
{wait}
---
{F2 08 FF FF}You saw that spinning room, right?
I'll fix that, as always.
{wait}
---
{F2 08 FF FF}You'd go even if I told you not to,
right? ...Yeah, that's what I thought.
{wait}

[msg HEISHI01 speaker 1] // Demon guard
{F2 08 FF FF}{speed 6}Alright, that's enough...
{wait}

[msg HEISHI02 speaker 1] // Demon guard
{F2 08 FF FF}{speed 6}*chuckle* Don't even try to resist...
{wait}

[msg HEISHI03 speaker 3] // Voice
{F2 08 FF FF}{speed 6}I found you.
{wait}

[msg HEISHI04 speaker 1] // Demon guard
{F2 08 FF FF}{speed 6}Now, let's finish this...
{wait}

[msg HEISHI_KARI]
{F2 08 FF FF}{speed 6}> You defeated the demon guard.
{wait}

[msg HEISHI_KARI02]
{F2 08 FF FF}{speed 6}> You defeated the demon guards.
{wait}

[msg TERMINAL speaker 4] // Small terminal
{F2 08 FF FF}> Link to the altar?
{wait}

[msg BOSSHOUMOTU01 speaker 5] // Eligor
{F2 08 FF FF}{speed 6}I am Eligor, one of the fallen angels.
{wait}
---
{F2 08 FF FF}I guard this Kila under the order of
our commander.
{wait}

[msg BOSSHOUMOTU02 speaker 5] // Eligor
{F2 08 FF FF}Now... You seem to have some
brains, unlike those Mantra fools.
{wait}

[msg BOSSHOUMOTU03 speaker 5] // Eligor
{F2 08 FF FF}{speed 6}I like those with intelligence.
{wait}
---
{F2 08 FF FF}To show you my respect, I will kill
you painlessly.
{wait}

[msg BOSSHOUMOTU03_02 speaker 5] // Eligor
{F2 08 FF FF}{speed 6}I won't let you have the Kila...
{wait}

[msg BOSSHOUMOTU03_03 speaker 5] // Eligor
{F2 08 FF FF}{speed 6}Die!!


[msg BERI01 speaker 6] // Berith
{F2 08 FF FF}{speed 6}Halt...
{wait}
---
{F2 08 FF FF}I am Berith, the great duke of hell.
{wait}
---
{F2 08 FF FF}Insolent scoundrel, put down
the Kila and begone!
{wait}

[sel BERI01_SEL]
{F2 08 FF FF}If you say so.
---
{F2 08 FF FF}I'm not budging.

[msg BERI01_YES speaker 6] // Berith
{F2 08 FF FF}{speed 6}Then, hurry and begone!
{wait}
---
{F2 08 FF FF}No, wait...
{wait}
---
{F2 08 FF FF}I can see your future...
{wait}
---
{F2 08 FF FF}I can see your face and body
bloodied by my hands...
{wait}
---
{F2 08 FF FF}If that is the future, then so shall
it be! Die!!
{wait}

[msg BERI02 speaker 6] // Berith
{F2 08 FF FF}{speed 6}I see...
{wait}
---
{F2 08 FF FF}Then, prepare yourself...
{wait}
---
{F2 08 FF FF}...for my spear shall pierce through
your insolent skull!
{wait}

[msg BOSS01_WIN]
{F2 08 FF FF}> You defeated Beiji-Weng!
{wait}

[msg BOSS03 speaker 7] // Ose
{F2 08 FF FF}{speed 6}So, you're here...
{wait}
---
{F2 08 FF FF}I'm Ose... one of the fallen angels,
and a mighty warrior of Nihilo.
{wait}
---
{F2 08 FF FF}Commander Hikawa is in the room
behind me.
{wait}

[msg BOSS04 speaker 7] // Ose
{F2 08 FF FF}{speed 6}However...
{wait}
---
{F2 08 FF FF}Only by my death will you gain entry.
I do warn you...  I've never been
defeated!
{wait}

[msg BOSS05 speaker 7] // Ose
{F2 08 FF FF}{speed 6}Prepare for your journey to
oblivion!


[msg BOSS03_WIN]
{F2 08 FF FF}> You defeated Legion!
{wait}

[msg SYOKERA01]
{F2 08 FF FF}> You see the {color 1}Red Kila{color 0} before you.
{wait}
---
{F2 08 FF FF}> Will you take it?
{wait}

[msg SYOKERA01_GET]
{F2 08 FF FF}{speed 6}> You obtained the {color 1}Red Kila{color 0}.
{wait}

[msg SYOKERA03]
{F2 08 FF FF}{speed 6}> You see the {color 1}White Kila{color 0} before you.
{wait}
---
{F2 08 FF FF}> Will you take it?
{wait}

[msg SYOKERA03_GET]
{F2 08 FF FF}{speed 6}> You obtained the {color 1}White Kila{color 0}.
{wait}

[msg SYOKERA_NONE]
{F2 08 FF FF}{speed 6}> It's empty... 
{wait}

[msg KIUN01 speaker 3] // Voice
{F2 08 FF FF}{speed 6}Hahahaha... What took you so long?
{wait}
---
{F2 08 FF FF}Had a hard time figuring out those
switches at the storehouse?
{wait}

[msg KIUN02 speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}I'm Kaiwan...
{wait}

[msg KIUN03 speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}Sorry, but I can't let you have
the Kila. So, take a hike.
{wait}
---
{F2 08 FF FF}Hahahaha!!
{wait}

[msg KIUN_SYS]
{F2 08 FF FF}{speed 6}> Kaiwan fled.
{wait}

[msg KIUN01_BTL speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}No, no...
{wait}
---
{F2 08 FF FF}I am Kaiwan, but I'm not the one
with the Kila.
{wait}
---
{F2 08 FF FF}Can't you tell the difference, fool!?
{wait}

[msg KIUN02_BTL speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}No, no...
{wait}
---
{F2 08 FF FF}I am Kaiwan, but I'm not the one
with the Kila.
{wait}
---
{F2 08 FF FF}Are you blind or something!?
{wait}

[msg KIUN03_BTL speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}No, no...
{wait}
---
{F2 08 FF FF}I am Kaiwan, but I'm not the one
with the Kila.
{wait}
---
{F2 08 FF FF}What an insult! You're gonna pay!
{wait}

[msg KEL01_BTL speaker 9] // Kaiwan's voice
{F2 08 FF FF}{speed 6}Hahahaha! You've met an unlucky
one, alright...
{wait}
---
{F2 08 FF FF}Well, I guess it suits you...
{wait}
---
{F2 08 FF FF}Hahahahahaha!
{wait}

[msg KEL02_BTL speaker 9] // Kaiwan's voice
{F2 08 FF FF}{speed 6}Looks like you've run into some
nasty demons, boy.
{wait}
---
{F2 08 FF FF}I'm sure you'll have fun playing
together!
{wait}

[msg KIUN_T_BTL1 speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}That's right... I'm the real one.
{wait}

[msg KIUN_T_BTL2 speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}It's been fun! It's truly regrettable,
but I have to kill you now.
{wait}

[msg KIUN_T_BTL3 speaker 8] // Kaiwan
{F2 08 FF FF}{speed 6}...Playtime's over.
{wait}

[msg KIUN_SYS_WIN]
{F2 08 FF FF}{speed 6}> You defeated Kaiwan.
{wait}

[msg KIUN_SYS_WIN_NG]
{F2 08 FF FF}{speed 6}> There is no Kila.
{wait}

[msg KIUN_SYS_WIN_GET]
{F2 08 FF FF}{speed 6}> You obtained the {color 1}Green Kila{color 0}.
{wait}

[msg SAIDAN_DVL01 speaker 10] // Koppa
{F2 08 FF FF}{speed 6}Those idiot Mantra demons fell for it
hook, line and sinker.
{wait}
---
{F2 08 FF FF}They're probably getting cocky,
thinking that they destroyed
the core unit.
{wait}

[msg SAIDAN_DVL02 speaker 11] // Incubus
{F2 08 FF FF}{speed 6}Power-shmower. Power's nothing
without brains!
{wait}

[msg SAIDAN_DVL03 speaker 10] // Koppa
{F2 08 FF FF}{speed 6}......Hm?
{wait}

[msg SAIDAN_DVL03_02 speaker 10] // Koppa
{F2 08 FF FF}{speed 6}Who're you?
{wait}

[msg SAIDAN_DVL04 speaker 11] // Incubus
{F2 08 FF FF}{speed 6}Hmmm...
{wait}
---
{F2 08 FF FF}I don't know who you're with, but
it looks like you have some brains.
{wait}
---
{F2 08 FF FF}You just wanna make a name for
yourself by taking Commander
Hikawa's head, huh?
{wait}

[msg SAIDAN_DVL04_02 speaker 10] // Koppa
{F2 08 FF FF}{speed 6}Just our luck... We were getting
bored of the Mantra's stupidity.
{wait}
---
{F2 08 FF FF}We need to welcome our guests and
show them off to their afterlife
comfortably.
{wait}

[msg SAIDAN_DVL05 speaker 12] // Demons
{F2 08 FF FF}{speed 6}Dieeeeeeeeeeee!!


[msg SAIDAN_SYS01]
{F2 08 FF FF}{speed 6}> You obtained the {color 1}Yellow Kila{color 0}.
{wait}

[msg F20_AREA01_MOBAHN1 speaker 6] // Berith
{F2 08 FF FF}{speed 6}Halt!
{wait}
---
{F2 08 FF FF}This is the {color 1}Assembly of Nihilo{color 0},
the place for those who seek
silence.
{wait}
---
{F2 08 FF FF}Demons who only believe in power
are not permitted!
{wait}
---
{F2 08 FF FF}Leave these grounds immediately!
{wait}

[msg f020_H_GET]
{F2 08 FF FF}{speed 6}> You obtained the Magatama
{color 2}Ankh{color 0}.
{wait}

[msg NISE]
{F2 08 FF FF}{speed 6}> No one is here...
{wait}

[msg CUBE04 speaker 13] // Soul
{F2 08 FF FF}{speed 6}There are so many cubes upstairs,
it's easy to get lost!
{wait}
---
{F2 08 FF FF}If I remember correctly, you need to
turn all the switches blue.
{wait}
---
{F2 08 FF FF}Oh yeah... I hear a Mantra demon
got in, so watch out!
{wait}

[msg NISE_ENT]
{F2 08 FF FF}{speed 6}> You can hear sounds coming from
inside the room.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[msg HON_ENT]
{F2 08 FF FF}{speed 6}> You sense a strong power from
beyond the door.
{wait}
---
{F2 08 FF FF}> Will you enter?
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

[msg F020_DOOR01]
{F2 08 FF FF}{speed 6}> You can hear sounds coming from
inside the room.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F020_DOOR01_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F020_DOOR02]
{F2 08 FF FF}{speed 6}> You sense a strong power from
beyond the door.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F020_DOOR02_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F020_KIUNDOOR01]
{F2 08 FF FF}{speed 6}> The door is locked.
{wait}

[msg F020_KIUNDOOR02]
{F2 08 FF FF}{speed 6}> The door is unlocked.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F020_KIUNDOOR02_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F020_DOOR03]
{F2 08 FF FF}{speed 6}> The door is closed tight.
{wait}

[msg F020_DEVIL01 speaker 14] // Demon
{F2 08 FF FF}{speed 6}Hahaha! World of stillness, my ass!
Creation? Yeah, right!
{wait}
---
{F2 08 FF FF}The Assembly of Nihilo is in
shambles! Hahahahahaha!
{wait}

[msg F020_DEVIL02 speaker 14] // Demon
{F2 08 FF FF}{speed 6}We already destroyed the core!
{wait}
---
{F2 08 FF FF}It's all over for Nihilo. The Mantra
has won!
{wait}

[msg F020_DEVIL03 speaker 14] // Demon
{F2 08 FF FF}{speed 6}...Dammit! I haven't seen
the Commander or the Maiden at all.
{wait}
---
{F2 08 FF FF}Oh well... We got all their treasure,
anyway.
{wait}

[msg F020_DEVIL04 speaker 14] // Demon
{F2 08 FF FF}{speed 6}The round thing up ahead is
the core--the heart of this
structure...
{wait}
---
{F2 08 FF FF}...Or at least it was. The whole
thing happened pretty fast.
{wait}
---
{F2 08 FF FF}So, was the report about needing
{color 1}four Kilas{color 0} to unlock the core
a hoax?
{wait}
---
{F2 08 FF FF}...Well, Nihilo probably got scared of
the Mantra and ran away.
{wait}

[msg F020_DEVIL05_01 speaker 14] // Demon
{F2 08 FF FF}{speed 6}Huh?
{wait}
---
{F2 08 FF FF}I can hear something coming from
that door.
{wait}
---
{F2 08 FF FF}...Hell, we won. What's there to
worry about?
{wait}

[msg F020_DEVIL05_02 speaker 14] // Demon
{F2 08 FF FF}{speed 6}Huh?
{wait}
---
{F2 08 FF FF}I can't hear anything coming from
that door anymore.
{wait}
---
{F2 08 FF FF}...Hell, we won. What's there to
worry about?
{wait}

[msg F020_DEVIL06 speaker 14] // Demon
{F2 08 FF FF}{speed 6}You're the demon that won the trial!
So, you decided to come here, huh?
{wait}
---
{F2 08 FF FF}...Well, you're too late.
{wait}
---
{F2 08 FF FF}We already finished our attack.
Hahahahahahaha!
{wait}

[msg F020_SINEN01 speaker 13] // Soul
{F2 08 FF FF}{speed 6}...Oh, a wise guy, eh???
{wait}
---
{F2 08 FF FF}Did you come here after
Commander Hikawa?
{wait}

[msg F020_SINEN01_NO speaker 13] // Soul
{F2 08 FF FF}{speed 6}If you're just here to get in some
rubbernecking, I suggest you turn
back.
{wait}
---
{F2 08 FF FF}I can't guarantee your safety
anywhere past here.
{wait}

[msg F020_SINEN01_YES01 speaker 13] // Soul
{F2 08 FF FF}{speed 6}Commander Hikawa is on Floor B15
of the core.
{wait}
---
{F2 08 FF FF}But, you need the {color 1}four Kilas{color 0},
stakes that control the Magatsuhi
in this structure, to get to him.
{wait}
---
{F2 08 FF FF}You saw those four pedestals on
the way here, right? Use the Kilas
there...
{wait}

[msg F020_SINEN01_YES02 speaker 13] // Soul
{F2 08 FF FF}{speed 6}Occasionally, there are visitors like
you, but they all disappear up ahead.
{wait}
---
{F2 08 FF FF}They all fall prey to the traps made
by the great Commander Hikawa.
{wait}
---
{F2 08 FF FF}So, why tell you all this? I figure
you have the right to know before
you die...
{wait}

[msg F020_SINEN01_YES03 speaker 13] // Soul
{F2 08 FF FF}{speed 6}...Well, even if this place goes down,
we still have an ace up our sleeve.
{wait}

[msg F020_SINEN02_01 speaker 13] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}This is the storehouse for
Magatsuhi.
{wait}
---
{F2 08 FF FF}It's separated into three floors,
and each leads to a storeroom
where a Kila is kept.
{wait}
---
{F2 08 FF FF}You see that switch? It's set up
so that it changes the flow of
Magatsuhi.
{wait}
---
{F2 08 FF FF}*chuckle*
{wait}
---
{F2 08 FF FF}In other words, if you don't use
the switches properly, you'll never
make it to the storerooms.
{wait}

[msg F020_SINEN02_02 speaker 13] // Soul
{F2 08 FF FF}{speed 6}............
{wait}

[msg F020_SINEN03_01 speaker 13] // Soul
{F2 08 FF FF}{speed 6}In each of the storerooms is
a demon guarding the Kila.
{wait}
---
{F2 08 FF FF}Even if someone were to make it
that far, they'd be killed anyway.
{wait}
---
{F2 08 FF FF}So, that's why we don't have to
panic.
{wait}

[msg F020_SINEN03_02 speaker 13] // Soul
{F2 08 FF FF}{speed 6}...Even if you make it to Floor B15,
'he' is guarding Commander Hikawa.
{wait}
---
{F2 08 FF FF}So, that's why we have nothing to
fear.
{wait}

[msg F020_SINEN04 speaker 13] // Soul
{F2 08 FF FF}{speed 6}Oh, a demon...
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}Well... you can get to the storeroom
on the floor above by turning
the three switches blue.
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}An intruder got this far...?
I hope Commander Hikawa isn't
slipping!
{wait}

[msg F020_SINEN05 speaker 13] // Soul
{F2 08 FF FF}{speed 6}The Assembly of Nihilo is aiming for
a world of silence,
{wait}
---
{F2 08 FF FF}a world where we throw away our
individuality and become a part of
the grand universe.
{wait}
---
{F2 08 FF FF}There is no pain or struggling
due to individuality.
{wait}
---
{F2 08 FF FF}...Commander Hikawa is wonderful.
All shall be bliss...
{wait}

[msg F020_SINEN06 speaker 13] // Soul
{F2 08 FF FF}{speed 6}We not only have Commander
Hikawa, but also the Maiden.
{wait}
---
{F2 08 FF FF}She will be the foundation for our
new world.
{wait}
---
{F2 08 FF FF}So, no matter how much demons
like you cause trouble, we won't
be disturbed.
{wait}
---
{F2 08 FF FF}...The world we desire has no need
for emotions in the first place...
{wait}

