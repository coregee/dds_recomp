// messages of fld/f/f021/f021
[speaker 0] Soul
[speaker 1] Shige
[speaker 2] Shige's voice
[speaker 3] Demon
[speaker 4] Voice

[msg BIG_TERM]
{F2 08 FF FF}{speed 6}This will be a large terminal.
Entry is prohibited because 
it is under construction.
{wait}

[msg SMALL_TERM]
{F2 08 FF FF}{speed 6}This will be a small terminal.
It is under construction, but
it can link to the big terminal.
{wait}
---
{F2 08 FF FF}Do you wish to link it?
{wait}

[sel SMALL_TERM_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F21_AREA1_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Huh?
{wait}
---
{F2 08 FF FF}Since you're in here, does that
mean we can get out now?
{wait}

[msg F21_AREA1_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}If you go through this route, you'll
reach Akasaka and Sannou.
{wait}

[msg F21_AREA1_NPC3 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I hear this Hikawa guy is transferring
Magatsuhi to Akasaka.
{wait}

[msg F21_AREA2_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}It seems that this Hikawa guy is
going to become the leader of
the world. Cool, huh?
{wait}

[msg F21_AREA2_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I don't care who the leader is...
{wait}
---
{F2 08 FF FF}I just wanna see the latest issue of
Ayakashi Monthly!!
{wait}

[msg F21_AREA2_NPC3 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Is it okay to trust this Hikawa guy?
{wait}
---
{F2 08 FF FF}What do you think?
{wait}

[msg SIGE_01 speaker 1] // Shige
{F2 08 FF FF}{speed 6}I'm a prospector that's a lookin' fer
buried treasure 'round these parts.
{wait}
---
{F2 08 FF FF}After years a pokin' around, I finally
located the treasure right here! But...
{wait}
---
{F2 08 FF FF}The earth here's as hard as a rock
turtle with frostbite! So, I can't dig,
ya dig?
{wait}

[msg SIGE_01B speaker 1] // Shige
{F2 08 FF FF}{speed 6}............!!
{wait}
---
{F2 08 FF FF}Ya got demons with ya!?
Hoo-doggie!
{wait}
---
{F2 08 FF FF}Could ya spare one a them demons
a yers? If ya do, I promise ta split
the treasure with ya!
{wait}
---
{F2 08 FF FF}C'mon! Lemme have a demon!
{wait}

[sel SIGE_01_SEL]
{F2 08 FF FF}My demon's your demon.
---
{F2 08 FF FF}Get your own demon.

[msg SIGE_01_NO_01 speaker 1] // Shige
{F2 08 FF FF}{speed 6}Man, guess ya woke up with a snake
in yer boot!
{wait}
---
{F2 08 FF FF}Well, I won't give up!!
{wait}
---
{F2 08 FF FF}Come back if ya change yer mind.
I'll still be here...
{wait}

[msg SIGE_01_YES speaker 1] // Shige
{F2 08 FF FF}{speed 6}Really!? Hoo-doggie! Thanks!
{wait}

[msg SIGE_01C speaker 1] // Shige
{F2 08 FF FF}{speed 6}*whistle*
{wait}
---
{F2 08 FF FF}How about {var 0}?


[sel SIGE_01C_SEL]
{F2 08 FF FF}No, not that one.
---
{F2 08 FF FF}Yeah, go for it.
---
{F2 08 FF FF}Just forget it.

[msg SIGE_01D speaker 1] // Shige
{F2 08 FF FF}{speed 6}Hmmm...
{wait}
---
{F2 08 FF FF}It looks a might weak to me...
Better take in a few winks.
This is gonna take awhile!
{wait}

[msg SIGE_01E speaker 1] // Shige
{F2 08 FF FF}{speed 6}Whoa!
{wait}
---
{F2 08 FF FF}This one's as ornery as a bobcat
with his tail on fire! Look forward to
ma results!
{wait}

[msg SIGE_02 speaker 1] // Shige
{F2 08 FF FF}{speed 6}Hey, it's you!
{wait}
---
{F2 08 FF FF}I'm still gettin' ready. Can you come
back in a while?
{wait}

[msg SIGE_03]
{F2 08 FF FF}{speed 6}> You can hear the sound of rock
being chipped from inside the hole.
{wait}

[msg SIGE_04 speaker 1] // Shige
{F2 08 FF FF}{speed 6}I did it! I did it!
Hoooooo-dooooooggie!!
I finally found the treasure!
{wait}
---
{F2 08 FF FF}I owe ya, lil' buckaroo! We'll split
the treasure, as promised!
{wait}
---
{F2 08 FF FF}There's four chests ahead, so pick
two of 'em.
{wait}

[msg SIGE_05 speaker 2] // Shige's voice
{F2 08 FF FF}{speed 6}Yer not gonna take that one after
all? Hurry up and pick two! I got
a jamboree to go to!
{wait}

[msg SIGE_06 speaker 2] // Shige's voice
{F2 08 FF FF}{speed 6}Alright, one more. Pick any one that
ya like.
{wait}

[msg SIGE_07 speaker 2] // Shige's voice
{F2 08 FF FF}{speed 6}Ya picked two, right? Then the rest
is mine!
{wait}

[msg SIGE_08_01 speaker 1] // Shige
{F2 08 FF FF}{speed 6}Thanks to ya, ma lifelong dream's
been fulfilled.
{wait}
---
{F2 08 FF FF}You're more useful than a terrier in
a backyard fulla prairie dogs!
{wait}

[msg SIGE_08_02 speaker 1] // Shige
{F2 08 FF FF}{speed 6}Thanks to ya, ma lifelong dream's
been fulfilled.
{wait}
---
{F2 08 FF FF}Yer more useful than a cat in
a barnyard fulla mice!
{wait}
---
{F2 08 FF FF}Here's a little somethin' fer ya!
{wait}
---
{F2 08 FF FF}It was in one of ma chests, but
I don't reckon I need it.
{wait}
---
{F2 08 FF FF}Ya might be able to find a use fer it.
{wait}

[msg SIGE_08_03]
{F2 08 FF FF}{speed 6}> You obtained a {color 1}Kimon Ball{color 0}.
{wait}

[msg SIGE_09 speaker 1] // Shige
{F2 08 FF FF}{speed 6}Your demon kicked the bucket.
Sorry 'bout that, partner!
{wait}

[msg SIGE_10 speaker 1] // Shige
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}I knew ya would come!
{wait}
---
{F2 08 FF FF}Have ya decided to gimme
a demon?
{wait}

[msg SIGE_11 speaker 1] // Shige
{F2 08 FF FF}{speed 6}Ya don't need to be as humble as
pie! It's all thanks to ya that I found
the treasure.
{wait}

[msg SIGE_12 speaker 2] // Shige's voice
{F2 08 FF FF}{speed 6}What's wrong, partner? Go ahead
and pick any two treasures.
{wait}

[msg DEBAG_01]
{F2 08 FF FF}{speed 6}> Will you give Shige a strong demon?
{wait}

[sel DEBAG_01_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg DEBAG_01_YES]
{F2 08 FF FF}{speed 6}> The flag "gave strong demon"
has been raised.
{wait}

[msg DEBAG_01_NO]
{F2 08 FF FF}{speed 6}> The flag "gave strong demon"
is still off.
{wait}

[msg DEBAG_02]
{F2 08 FF FF}{speed 6}> Advance the digging event?
{wait}

[sel DEBAG_02_SEL]
{F2 08 FF FF}Advance to step 2.
---
{F2 08 FF FF}Advance to step 3.
---
{F2 08 FF FF}Don't advance.

[msg DEBAG_02_01]
{F2 08 FF FF}{speed 6}> Advancing to step 2.
{wait}

[msg DEBAG_02_02]
{F2 08 FF FF}{speed 6}> Advancing to step 3.
{wait}

[msg DEBAG_02_03]
{F2 08 FF FF}{speed 6}> Event is left as step 1.
{wait}

[msg F21_AREA4_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Watch out for steep slopes!
{wait}
---
{F2 08 FF FF}You'll slide right down to the bottom,
and then... SPLAT.
{wait}

[msg F21_AREA6_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I hear those gods summoned by
Magatsuhi aren't really gods...
{wait}
---
{F2 08 FF FF}Does that mean they're demons?
{wait}

[msg F21_AREA6_NPC2]
{F2 08 FF FF}{speed 6}> There is no answer...
It's just some drunken buffoon.
{wait}

[msg F21_AREA6_NPC3 speaker 3] // Demon
{F2 08 FF FF}{speed 6}Dang! You're pretty tough makin' it
through that tunnel!
{wait}
---
{F2 08 FF FF}But, you're best off not goin' near
the Diet Building.
{wait}
---
{F2 08 FF FF}If you get in the way of Commander
Hikawa... *gulp*
{wait}
---
{F2 08 FF FF}Or, are you here to 'help'
Commander Hikawa?
{wait}

[sel F21_AREA6_NPC3_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F21_AREA6_NPC3_YES speaker 3] // Demon
{F2 08 FF FF}{speed 6}You are, eh?
{wait}
---
{F2 08 FF FF}But, are you good enough!?
{wait}

[msg F21_AREA6_NPC3_NO speaker 3] // Demon
{F2 08 FF FF}{speed 6}Then, Commander Hikawa really will
make you... *gulp*
{wait}

[msg F21_AREA6_NPC3_2ND speaker 3] // Demon
{F2 08 FF FF}{speed 6}Commander Hikawa's god will soon
descend upon us.
{wait}
---
{F2 08 FF FF}The Reason of Shijima shall begin.
{wait}

[msg F21_AREA6_NPC3_SIJIMABUI speaker 3] // Demon
{F2 08 FF FF}{speed 6}Commander Hikawa's god is finally
here.
{wait}
---
{F2 08 FF FF}The final moment of creation has
begun...
{wait}

[msg F21_AREA7_NPC1 speaker 3] // Demon
{F2 08 FF FF}{speed 6}Are you here because you heard
that Commander Hikawa is
summoning a god?
{wait}

[sel F21_AREA7_NPC1_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F21_AREA7_NPC1_YES speaker 3] // Demon
{F2 08 FF FF}{speed 6}I see...
{wait}
---
{F2 08 FF FF}But, there's no need to help.
We have 'their' protection.
{wait}
---
{F2 08 FF FF}I won't tell you to turn back, but
from here on out, I can't guarantee
your safety...
{wait}

[msg F21_AREA7_NPC1_NO speaker 3] // Demon
{F2 08 FF FF}{speed 6}Ha ha ha!
{wait}
---
{F2 08 FF FF}Someone just like you passed by
here a while ago.
{wait}
---
{F2 08 FF FF}The Maiden... calling herself Aradia.
{wait}
---
{F2 08 FF FF}Well, we have 'them' in
the Diet Building.
{wait}
---
{F2 08 FF FF}I won't tell you to turn back, but
from here on out, I can't guarantee
your safety...
{wait}

[msg F21_AREA7_NPC2 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hey, you there.
{wait}
---
{F2 08 FF FF}If you're looking for Hikawa,
you'd better remember this,
or else...
{wait}
---
{F2 08 FF FF}If he's handsome, hook me up!
{wait}

[msg F21_AREA12_DOOR]
{F2 08 FF FF}{speed 6}> It doesn't open from this side.
{wait}

[msg F21_AREA21_NPC1 speaker 0] // Soul
{F2 08 FF FF}{speed 6}You slide down too?
{wait}
---
{F2 08 FF FF}Looks like we got the short end
of the stick.
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

[msg SIPPAI2 speaker 4] // Voice
{F2 08 FF FF}{speed 6}I know you have a candelabrum!
{wait}

[msg SIPPAI_KOTEN speaker 4] // Voice
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

[msg F021_SINEN01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}If you go straight forward, you'll
reach the Diet Building.
{wait}

[msg F021_SINEN02_01 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hey...!
{wait}
---
{F2 08 FF FF}I just saw a human woman!
She was headed for Kasumigaseki.
{wait}
---
{F2 08 FF FF}She was creepy, like she was
possessed by something...
She was hot, though!
{wait}

[msg F021_SINEN02_02 speaker 0] // Soul
{F2 08 FF FF}{speed 6}I think I've finally got it!
{wait}
---
{F2 08 FF FF}The Assembly of Nihilo conceived
their Reason of... Shijima, was it?
'A world of stillness', right...?
{wait}
---
{F2 08 FF FF}Aw, forget it! I'll never understand...
{wait}

[msg F021_SINEN03 speaker 0] // Soul
{F2 08 FF FF}{speed 6}Hey, you. It's dangerous up ahead.
{wait}
---
{F2 08 FF FF}It's a maze in there. Plus,
there are steep slopes.
{wait}
---
{F2 08 FF FF}You'll slide right down to
the bottom!
{wait}
---
{F2 08 FF FF}If you jump in unprepared,
you might die of starvation, or
worse...
{wait}

[msg F021_DEVIL01_01 speaker 3] // Demon
{F2 08 FF FF}{speed 6}You made it through that tunnel?
Wow! You must be tough!
{wait}
---
{F2 08 FF FF}But, even you're not tough enough
to go near the Diet Building.
{wait}
---
{F2 08 FF FF}...If you get in the way of
Commander Hikawa... Well...
It was nice knowing you!
{wait}

[msg F021_DEVIL01_02 speaker 3] // Demon
{F2 08 FF FF}{speed 6}Commander Hikawa's god is
finally here.
{wait}
---
{F2 08 FF FF}The final moment of creation
has begun...
{wait}

[msg F021_DEVIL02 speaker 3] // Demon
{F2 08 FF FF}{speed 6}Are you here because you heard
that Commander Hikawa is
summoning a god?
{wait}

[sel F021_YESNO_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F021_DEVIL02_YES speaker 3] // Demon
{F2 08 FF FF}{speed 6}I see...
{wait}
---
{F2 08 FF FF}But, there's no need to help.
We have 'their' protection.
{wait}
---
{F2 08 FF FF}I won't tell you to turn back, but
from here on out, I can't guarantee
your safety...
{wait}

[msg F021_DEVIL02_NO speaker 3] // Demon
{F2 08 FF FF}{speed 6}Ha ha ha!
{wait}
---
{F2 08 FF FF}Someone just like you passed by
here a while ago.
{wait}
---
{F2 08 FF FF}The Maiden... calling herself Aradia.
{wait}
---
{F2 08 FF FF}Well, we have 'them' in
the Diet Building.
{wait}
---
{F2 08 FF FF}I won't tell you to turn back, but
from here on out, I can't guarantee
your safety...
{wait}

[msg F021_DEVIL02_02 speaker 3] // Demon
{F2 08 FF FF}{speed 6}Commander Hikawa has summoned
the famous god, Ahriman...
{wait}
---
{F2 08 FF FF}Darn! I wanted to see that...
{wait}

