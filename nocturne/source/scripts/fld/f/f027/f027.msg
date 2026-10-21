// messages of fld/f/f027/f027
[speaker 0] Manikin kid
[speaker 1] Soul
[speaker 2] Old Manikin
[speaker 3] Female Manikin
[speaker 4] Male Manikin
[speaker 5] Voice
[speaker 6] Collector Manikin
[speaker 7] Male? Manikin
[speaker 8] Demon

[msg PUZZLE_BOY speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}What is it?
{wait}
---
{F2 08 FF FF}You wanna know what games
humans used to play?
{wait}
---
{F2 08 FF FF}I already beat this game...
{wait}
---
{F2 08 FF FF}Well, you won't last a minute.
It's over before it even starts.
{wait}

[msg PUZZLE_BOY2 speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}If you can win, I'll give you
an {color 1}insect-like thing{color 0}.
{wait}
---
{F2 08 FF FF}Okay! Why don't you try?
{wait}

[sel PUZZLE_BOY_SEL]
{F2 08 FF FF}You're on!
---
{F2 08 FF FF}I have better things to do.

[msg PUZZLE_BOY3 speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}Oh, you're back. I don't have
anything for you, but...
{wait}
---
{F2 08 FF FF}I'm not stopping you from playing.
So, why don't you try?
{wait}

[msg PUZZLE_BOY_YES speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}You don't have to go along with me,
you know? Well, it's okay...
{wait}

[msg PUZZLE_BOY_NO speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}Well, I don't mind.
{wait}
---
{F2 08 FF FF}You don't have to push yourself
anyway...
{wait}

[msg PUZZLE_BOY_END speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}You can come again, you know.
{wait}
---
{F2 08 FF FF}Well, I've beaten it anyway.
{wait}

[msg PUZZLE_BOY_WIN speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}Ummm... So...
{wait}
---
{F2 08 FF FF}I guess that means you beat it,
right?
{wait}
---
{F2 08 FF FF}Ugh......
{wait}
---
{F2 08 FF FF}...That's fine. You can have this
{color 1}insect-like thing{color 0}.
{wait}

[msg PUZZLE_BOY_DAME speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}Hey! No playing games right now!
{wait}
---
{F2 08 FF FF}Mifunashiro is in danger!
{wait}

[msg PUZZLE_BOY_WIN2]
{F2 08 FF FF}{speed 6}> You obtained the Magatama
{color 2}Geis{color 0}.
{wait}

[msg PUZZLE_BOY_SHOBO speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}When the going gets tough, it's best
to escape into the world of games...
{wait}

[msg ASAKUSA_SILENT]
{F2 08 FF FF}{speed 6}> The city is silent.
{wait}

[msg F027_MANE_AREA02_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}I'm new here, so I don't know
the details...
{wait}
---
{F2 08 FF FF}But, this place was bustling with
Manikins just a short while back.
{wait}

[msg F027_MANE_AREA12_01 speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}...I'm tired of it all!
{wait}

[msg F027_MANE_AREA12_02 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}Futomimi is dead...
Creation of a new world by
the Manikins is now impossible.
{wait}

[msg F027_MANE_AREA12_02A speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}About the old Manikin that was
here...
{wait}
---
{F2 08 FF FF}Despite saying that he was tired
of it all, he still went to
the Tower of Kagutsuchi.
{wait}

[msg F027_MANE_AREA12_03 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Ah...
{wait}
---
{F2 08 FF FF}Having to live like this again...
*sigh* Life is short...
{wait}

[msg F027_MANE_AREA13_01]
{F2 08 FF FF}{speed 6}> There's no response from
the Manikin.
{wait}

[msg F027_MANE_AREA16_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Manikins are falling apart,
since the dream of their world and
Futomimi are both gone.
{wait}
---
{F2 08 FF FF}I'm not a Musubi, but I think
they should've respected themselves
more.
{wait}

[msg FIRE_YURE]
{F2 08 FF FF}{speed 6}> The flames of the {color 1}Candelabrum
of Sovereignty{color 0} are flickering wildly...
{wait}

[msg KEHAI]
{F2 08 FF FF}{speed 6}> You can feel the presence of
a terrifying demon...
{wait}
---
{F2 08 FF FF}> Will you stay here?
{wait}

[sel YES_NO_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg KEHAI2]
{F2 08 FF FF}{speed 6}> Are you sure?
{wait}

[msg TRY_RUNAWAY]
{F2 08 FF FF}{speed 1}> ............
{wait}

[msg RUNAWAY]
{F2 08 FF FF}{speed 6}> It looks like you'll be able to
get away.
{wait}

[msg SIPPAI]
{F2 08 FF FF}{speed 6}> It looks like you won't be able to
escape...
{wait}

[msg SIPPAI2 speaker 5] // Voice
{F2 08 FF FF}{speed 6}I know you have a candelabrum!
{wait}

[msg SIPPAI_KOTEN speaker 5] // Voice
{F2 08 FF FF}{speed 6}The flames of the candelabrum
burn passionately!
You won't escape!
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

[msg F027_MANE01_01 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}We're still restoring this area.
{wait}
---
{F2 08 FF FF}It'll be a while before you'll be able
to get through here.
{wait}
---
{F2 08 FF FF}Come back later.
{wait}

[msg F027_MANE01_02 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}We finally restored the area. Now,
you can go and look around.
{wait}
---
{F2 08 FF FF}...It's full of demons, though.
{wait}

[msg F027_MANE02_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}This city is pretty shabby. There are
places we can't even get through.
{wait}
---
{F2 08 FF FF}...But, we'll clean it all up, because
it's our city!
{wait}

[msg F027_MANE02_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}We fixed up the area just past those
doors!
{wait}
---
{F2 08 FF FF}Use it if you're going to Ueno or
the {color 1}Asakusa Tunnel{color 0}!
{wait}

[msg F027_MANE03_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Welcome to Asakusa, the city of
the Manikins.
{wait}
---
{F2 08 FF FF}...Ah, it has such a sweet ring to it.
{wait}

[msg F027_MANE03_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Welcome! This is Asakusa, the city
of Manikins.
{wait}
---
{F2 08 FF FF}*sigh* Finally, our creation will begin...
{wait}

[msg F027_MANE04_01 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}We're no longer the slaves we used
to be.
{wait}
---
{F2 08 FF FF}We're free! There's nothing that can
hurt us now!
{wait}
---
{F2 08 FF FF}The Mantra? We don't give a damn!
{wait}

[msg F027_MANE04_02 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}We can't be weak forever!
{wait}
---
{F2 08 FF FF}Now, it's our turn to enslave
the demons!
{wait}
---
{F2 08 FF FF}...That's the mindset we need to be
at.
{wait}

[msg F027_MANE04_03_RED speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}*gasp* I heard from an old friend!
{wait}
---
{F2 08 FF FF}There's {color 1}another demon{color 0} at the Great
Underpass!
{wait}
---
{F2 08 FF FF}It's a horrific demon on a red horse!
{wait}
---
{F2 08 FF FF}But... I'm in Asakusa, so why should
I get all excited?
{wait}

[msg F027_MANE05_01_01 speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}............!?
{wait}
---
{F2 08 FF FF}...Whoa!
{wait}
---
{F2 08 FF FF}It's you! Do you remember me?
{wait}
---
{F2 08 FF FF}...How've you been? Alright?
{wait}

[msg F027_MANE05_01NO speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}...I see. You've been through a lot,
haven't you? I'm not a demon, but
I sort of understand...
{wait}
---
{F2 08 FF FF}Well, we're doing well living in
Asakusa.
{wait}

[msg F027_MANE05_01YES speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}I see, I see!
{wait}
---
{F2 08 FF FF}We're doing well living in Asakusa.
{wait}

[msg F027_MANE05_01_02 speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}This is all thanks to Futomimi's
leadership.
{wait}
---
{F2 08 FF FF}Futomimi is in our holy land of
{color 1}Mifunashiro{color 0}. Go and see him.
{wait}

[msg F027_MANE05_02 speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}This is all thanks to Futomimi's
leadership.
{wait}
---
{F2 08 FF FF}Futomimi is at our holy land of
{color 1}Mifunashiro{color 0}. Go and see him.
{wait}

[msg F027_MANE05_03 speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}Futomimi is deep inside Mifunashiro,
praying to see the future.
{wait}
---
{F2 08 FF FF}Sometimes it takes awhile,
sometimes it doesn't...
{wait}

[msg F027_MANE05_04 speaker 2] // Old Manikin
{F2 08 FF FF}{speed 6}Is it impossible for us Manikins to
participate in the creation?
{wait}
---
{F2 08 FF FF}...No, we have Futomimi! It must be
possible!
{wait}
---
{F2 08 FF FF}We'll make it... A world without
humans or demons--just Manikins!
{wait}

[msg F027_MANE06_01 speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}Our holy land, Mifunashiro, is just
past here.
{wait}

[msg F027_MANE06_02 speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}If everyone's a Manikin, then
everyone's friendly?
{wait}

[msg F027_MANE07 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}It's great that we're free, but what do
we do now?
{wait}
---
{F2 08 FF FF}...I'm not used to this.
{wait}

[msg F027_MANE08_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Uh... Ugh......
{wait}
---
{F2 08 FF FF}It's Sa...{color 1}Sakahagi{color 0}...
{wait}
---
{F2 08 FF FF}Th-That traitor, Sakahagi is going
wild... up ahead...
{wait}

[msg F027_MANE08_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Uh... Ugh......
{wait}
---
{F2 08 FF FF}...Sakahagi left...
{wait}

[msg F027_MANE09 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}S-Sakahagi ruins our peace...
{wait}
---
{F2 08 FF FF}He's an evil Manikin...
{wait}

[msg F027_DOOR01]
{F2 08 FF FF}{speed 6}> You sense a strong power from
beyond the door.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[msg F027_MANE10 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}If you go on further, you'll reach
{color 1}Mifunashiro{color 0}.
{wait}
---
{F2 08 FF FF}It's a place not to be defiled by
demons or humans.
{wait}

[msg F027_MANE11_01 speaker 6] // Collector Manikin
{F2 08 FF FF}{speed 6}Phew!! So busy...
{wait}
---
{F2 08 FF FF}...Oh! It's you!
{wait}
---
{F2 08 FF FF}It's me, remember? Y'know, from
the Underpass and the Prison... Me!
{wait}
---
{F2 08 FF FF}...I was thinking of opening a store
here--making use of all my
experience.
{wait}
---
{F2 08 FF FF}It's a mess now, so it'll be a while
before I'll be able to open up.
{wait}
---
{F2 08 FF FF}But, I'll hook you up, so come on by
after I open!
{wait}

[msg F027_MANE11_02 speaker 6] // Collector Manikin
{F2 08 FF FF}{speed 6}I'm going to start a store that sells
a bunch of rare things.
{wait}
---
{F2 08 FF FF}Come by once I open!
{wait}

[msg F027_MANE11_03 speaker 6] // Collector Manikin
{F2 08 FF FF}{speed 6}The inner areas have been restored,
I hear. We still have a ways to go,
though.
{wait}
---
{F2 08 FF FF}I want to open up soon. Well, better
get back to work.
{wait}

[msg F027_MANE12_01 speaker 7] // Male? Manikin
{F2 08 FF FF}{speed 6}Those days when I used to be
tortured by the Mantra...
{wait}
---
{F2 08 FF FF}Oh, it felt sooooo good!
{wait}

[msg F027_MANE12_02 speaker 7] // Male? Manikin
{F2 08 FF FF}{speed 6}A world... full of peachy Manikins...
{wait}
---
{F2 08 FF FF}...Isn't that just faaaaaaaaaabulous?
{wait}

[msg F027_MANE12_03 speaker 7] // Male? Manikin
{F2 08 FF FF}{speed 6}What's wrong!? What happened!?
Tell me, hun!!
{wait}

[msg F027_MANE13_01 speaker 8] // Demon
{F2 08 FF FF}{speed 6}Things have been heating up in
Ikebukuro lately.
{wait}
---
{F2 08 FF FF}I heard someone saw {color 1}Hikawa{color 0} by
the building that used to be
the Mantra's headquarters.
{wait}

[msg F027_MANE13_02 speaker 8] // Demon
{F2 08 FF FF}{speed 6}Geez... Everyone's so into this
creation stuff.
{wait}

[msg F027_MANE14_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}...We finally restored the area, but
it's filled with demons.
{wait}
---
{F2 08 FF FF}Oh, well.
{wait}
---
{F2 08 FF FF}Futomimi should be ready to give
his prophecy at Mifunashiro.
{wait}
---
{F2 08 FF FF}I think I'll go there. Are you going?
{wait}

[msg F027_MANE14_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Yoyogi Park's in danger, I hear.
{wait}
---
{F2 08 FF FF}Are you going?
{wait}
---
{F2 08 FF FF}You can get there by taking the path
where the Collector Manikin opened
his store.
{wait}

[msg F027_MANE14_03 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}The evil power at Yoyogi Park was
Sakahagi, and he's already been
defeated, I hear.
{wait}
---
{F2 08 FF FF}Thank goodness.
{wait}

[msg F027_MANE15 speaker 8] // Demon
{F2 08 FF FF}{speed 6}The lounge in Ginza and the club in
Shibuya are great places for info.
{wait}
---
{F2 08 FF FF}You visiting them?
{wait}

[msg F027_DEVIL02_01 speaker 8] // Demon
{F2 08 FF FF}{speed 6}There's a strange guy living in
the terminal. You know him?
{wait}

[msg F027_DEVIL02_01YES speaker 8] // Demon
{F2 08 FF FF}{speed 6}Then, you should drop by once in
a while, to check up on him.
{wait}
---
{F2 08 FF FF}Take the advice of a long-time
Asakusa resident!
{wait}

[msg F027_DEVIL02_01NO speaker 8] // Demon
{F2 08 FF FF}{speed 6}I see...
{wait}
---
{F2 08 FF FF}Well, I've been living here longer
than he has.
{wait}

[msg F027_DEVIL02_02 speaker 8] // Demon
{F2 08 FF FF}{speed 6}So, is that guy who lived at
the Asakusa terminal doing okay?
{wait}

[msg F027_DEVIL02_02YES speaker 8] // Demon
{F2 08 FF FF}{speed 6}I see...
{wait}
---
{F2 08 FF FF}Well, tell him I said "hi".
{wait}

[msg F027_DEVIL02_02NO speaker 8] // Demon
{F2 08 FF FF}{speed 6}I see.
{wait}
---
{F2 08 FF FF}I guess it must be pretty rough.
{wait}

[msg F027_MANE17_01 speaker 8] // Demon
{F2 08 FF FF}{speed 6}...What?
{wait}
---
{F2 08 FF FF}We believe in coexistence, so
there's no violence here.
{wait}

[msg F027_MANE17_02 speaker 8] // Demon
{F2 08 FF FF}{speed 6}Looks like something happened
to the Manikins.
{wait}
---
{F2 08 FF FF}Well, we don't really care.
{wait}

[sel F027_YESNO_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F027_MANE18 speaker 0] // Manikin kid
{F2 08 FF FF}{speed 6}You're pretty adventurous, coming
all this way.
{wait}

[msg F027_MANE19_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}The northern part of the city is
restored, and now you can go
inside!
{wait}
---
{F2 08 FF FF}...But, we weren't the first ones
here...
{wait}
---
{F2 08 FF FF}Well, we're still pumped up. I'm
going to help restore the city, too.
{wait}

[msg F027_MANE19_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}The Collector Manikin opened
a store.
{wait}
---
{F2 08 FF FF}He's got a lot of things, from
weird drinks to insect-like things.
{wait}
---
{F2 08 FF FF}It's up ahead on your left.
{wait}

[msg F027_MANE19_03 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}The Collector Manikin opened
a store.
{wait}
---
{F2 08 FF FF}He's got a lot of things, from
weird drinks to insect-like things.
{wait}
---
{F2 08 FF FF}It's up ahead on your left.
{wait}
---
{F2 08 FF FF}...But, sometimes I feel a {color 1}strange
presence{color 0} around there.
{wait}
---
{F2 08 FF FF}It's kinda scary...
{wait}

[msg F027_DEVIL01 speaker 8] // Demon
{F2 08 FF FF}{speed 6}Welcome to the slums of Asakusa!
{wait}

[msg F027_MANE20 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}No...
{wait}
---
{F2 08 FF FF}Futomimi...
{wait}
---
{F2 08 FF FF}Futomimi...!!
{wait}

[msg F027_MANE21]
{F2 08 FF FF}{speed 6}> There is no response from
the Manikin.
{wait}

[msg F027_MANE22_01 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}We're working hard to restore
the city, but there's a bad Manikin
that's ruining our peace.
{wait}
---
{F2 08 FF FF}He's ruthless, tearing off the skins of
other Manikins.
{wait}
---
{F2 08 FF FF}He might be around here, so be
careful! 
{wait}

[msg F027_MANE22_02 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}We're working hard to restore
the city, but there's a bad Manikin
that's ruining our peace.
{wait}
---
{F2 08 FF FF}His name's Sakahagi.
{wait}
---
{F2 08 FF FF}He steals Magatsuhi from other
Manikins and plans to rule other
demons. What a dummy!
{wait}

[msg F027_MANE22_03 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}I hear Sakahagi's dead.
{wait}
---
{F2 08 FF FF}...Hmph, serves him right!
{wait}

[msg F027_SINEN01_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Mantra has fallen and the damn
Manikins have moved into town.
{wait}
---
{F2 08 FF FF}There goes the neighborhood...
{wait}

[msg F027_SINEN01_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Nowadays, those damn Manikins are
talking about creation...
{wait}
---
{F2 08 FF FF}Hope nothin' bad happens.
{wait}

[msg F027_SINEN01_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}There are demons in Mifunashiro!
{wait}

[msg F027_SINEN01_04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Those damn Manikins aren't all
dead yet.
{wait}
---
{F2 08 FF FF}There's still some 'round here.
{wait}

[msg F027_SINEN02_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}What!? What!? The Manikins sure
are noisy!
{wait}

[msg F027_SINEN02_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}What!? What!? The Manikins sure
are bustling!
{wait}

[msg F027_SINEN02_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}What!? What!? What's going on!?
{wait}

[msg F027_SINEN02_04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}...It's become quiet.
{wait}
---
{F2 08 FF FF}Manikins were running about here,
not long ago...
{wait}
---
{F2 08 FF FF}Now, demons are here instead.
{wait}
---
{F2 08 FF FF}Is this the flow of time?
{wait}

[msg F027_MANE23 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}.........
{wait}
---
{F2 08 FF FF}Futomimi......
{wait}
---
{F2 08 FF FF}Mifunashiro's...!!
{wait}

[msg F027_MANE24_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}Shhh!
{wait}
---
{F2 08 FF FF}Sakahagi'll find me! Go away!
{wait}

[msg F027_MANE24_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...Is Sakahagi gone yet?
{wait}

[msg F027_MANE24_03 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...Huh? Creation by Manikins?
{wait}
---
{F2 08 FF FF}...I'm scared of Sakahagi, so I'll stay
like this for a while longer.
{wait}

[msg F027_MANE24_04 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}...Mifunashiro's...!?
{wait}
---
{F2 08 FF FF}...I'm scared.
{wait}

[msg F027_MANE24_05 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}............
{wait}
---
{F2 08 FF FF}...Maybe lying here wasn't such
a great idea.
{wait}

[msg F027_SINEN03_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Looking just at Asakusa, it's
heartwarming to see the Manikins
restore the town...
{wait}
---
{F2 08 FF FF}But, looking at Tokyo as a whole, we
see Nihilo taking over, and that's no
laughing matter.
{wait}
---
{F2 08 FF FF}Nihilo has no rival. Are we just going
to sit here, watching Hikawa make
his world of stillness?
{wait}

[msg F027_SINEN03_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Nihilo's Nightmare System is at
a standstill.
{wait}
---
{F2 08 FF FF}Strange things are happening at
Ikebukuro and the Amala Network.
{wait}
---
{F2 08 FF FF}Now, what's going to happen?
{wait}

[msg F027_SINEN03_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}They've begun...
{wait}
---
{F2 08 FF FF}...Yosuga, that is.
{wait}

[msg F027_SINEN03_04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}...The Manikins have retired from
the race.
{wait}
---
{F2 08 FF FF}Yosuga, Shijima, Musubi...
{wait}
---
{F2 08 FF FF}These three are all competing for
the right of creation.
{wait}
---
{F2 08 FF FF}I don't know who you're for, and I
don't want to know.
{wait}
---
{F2 08 FF FF}But, the time is nearing.
{wait}

[msg F027_SINEN04_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}I heard there was a human girl
hanging around the Mantra's
headquarters when they fell.
{wait}
---
{F2 08 FF FF}She must have some guts.
{wait}

[msg F027_SINEN04_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Something's happening at
Ikebukuro.
{wait}
---
{F2 08 FF FF}Could it be the human girl who
witnessed the fall of the Mantra!?
{wait}
---
{F2 08 FF FF}...Just kidding!!!! Did you fall for
that?
{wait}

[msg F027_SINEN04_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}A demon girl is attacking
Mifunashiro!
{wait}
---
{F2 08 FF FF}...It really was the Ikebukuro girl...
{wait}

[msg F027_SINEN04_04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}Yosuga, was it? The Ikebukuro girl's
Reason.
{wait}
---
{F2 08 FF FF}I like it. I mean, why do I have to live
with all these losers?
{wait}

[msg F027_SINEN05_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Maiden was Nihilo's key to
destroying the Mantra.
{wait}
---
{F2 08 FF FF}What was it? The 'Nightmare
System'?
{wait}

[msg F027_SINEN05_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Nightmare System was put to
a halt by someone.
{wait}
---
{F2 08 FF FF}Isn't this bad for Nihilo?
{wait}

[msg F027_SINEN05_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Yosuga are the ones attacking
Mifunashiro.
{wait}
---
{F2 08 FF FF}They're probably after all
the Magatsuhi the Manikins have
been storing.
{wait}

[msg F027_SINEN05_04 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The Manikins were wiped out...
{wait}
---
{F2 08 FF FF}...I don't like the idea of a world
controlled by power.
{wait}
---
{F2 08 FF FF}Living here, I've realized that
Nihilo's Reason of Shijima is
the best. No more fighting, please.
{wait}

[msg F027_MANE25 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}Futomimi is meditating at
Mifunashiro.
{wait}
---
{F2 08 FF FF}He sees the future by meditating.
{wait}

[msg F027_MANE26 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Why...
{wait}
---
{F2 08 FF FF}Why are we...?
{wait}

[msg F027_MANE27 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}I wonder...
{wait}
---
{F2 08 FF FF}What happened to the human boy at
the Mantra's jail? Did he escape?
{wait}
---
{F2 08 FF FF}...That hat bugs me.
{wait}

[msg F027_MANE28_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}There's evil power at Yoyogi Park,
I hear.
{wait}
---
{F2 08 FF FF}But, we worked together to build
this city.
{wait}
---
{F2 08 FF FF}We'll beat down that evil power!
{wait}

[msg F027_MANE28_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Hmmm...
{wait}
---
{F2 08 FF FF}Was the evil power of Yoyogi really
Sakahagi?
{wait}
---
{F2 08 FF FF}Why doesn't Futomimi say, "The evil
power is gone"? Sakahagi's dead!
{wait}
---
{F2 08 FF FF}Hmmm...
{wait}

[msg F027_MANE29_01 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}'Evil power'...
{wait}
---
{F2 08 FF FF}It's him. Definitely him.
{wait}

[msg F027_MANE29_02 speaker 3] // Female Manikin
{F2 08 FF FF}{speed 6}The evil power of Yoyogi was
Sakahagi.
{wait}
---
{F2 08 FF FF}But, he's dead, so I could care less
now.
{wait}

[msg F027_SINEN06 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The's a temple on the north side of
Ueno.
{wait}
---
{F2 08 FF FF}But, you can't get in, so there's
nothing to see.
{wait}

[msg F027_SINEN07_01 speaker 1] // Soul
{F2 08 FF FF}{speed 6}If you go south from the exit up
ahead, you'll reach Yushima Station.
{wait}
---
{F2 08 FF FF}There's a giant hole there. We call it
the Asakusa Tunnel.
{wait}

[msg F027_SINEN07_02 speaker 1] // Soul
{F2 08 FF FF}{speed 6}It's been real quiet...
{wait}
---
{F2 08 FF FF}Where did the Manikins go?
{wait}

[msg F027_SINEN07_03 speaker 1] // Soul
{F2 08 FF FF}{speed 6}The creation of the world, huh...?
{wait}
---
{F2 08 FF FF}If you lose, you're out. That's pretty
tough...
{wait}

[msg F027_SINEN08_01 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}I saw Sakahagi earlier.
{wait}
---
{F2 08 FF FF}He went down the hall.
{wait}

[msg F027_SINEN08_02 speaker 4] // Male Manikin
{F2 08 FF FF}{speed 6}Huh? Sakahagi's dead?
{wait}

[msg F027_DEVIL03 speaker 8] // Demon
{F2 08 FF FF}{speed 6}I see...
{wait}
---
{F2 08 FF FF}Now that Futomimi's dead,
Asakusa's nothing but a ghost town.
{wait}
---
{F2 08 FF FF}It's just as Lady {firstname 3}
said.
{wait}
---
{F2 08 FF FF}We need to watch Ginza...
...The Assembly of Nihilo.
{wait}

[msg F027_DEVIL03_02 speaker 8] // Demon
{F2 08 FF FF}{speed 6}...Finally, it's time to head for
Kagutsuchi!
{wait}

[msg F027_DEVIL04 speaker 8] // Demon
{F2 08 FF FF}{speed 6}Hmmm... This is one boring town.
No clubs, no bars.
{wait}
---
{F2 08 FF FF}Well, I guess it's a good place to
kick back and relax... There's no
one around, so I can enjoy some
peace and quiet.
{wait}

