// messages of fld/f/f014/f014
[speaker 0] Ghost
[speaker 1] Soul
[speaker 2] Stranded Soul
[speaker 3] Self-Destructing Ghost
[speaker 4] Ghost Patient
[speaker 5] Forneus
[speaker 6] X-ray room
[speaker 7] Door
[speaker 8] Doctor's spirit
[speaker 9] Security System
[speaker 10] Isamu
[speaker 11] Child
[speaker 12] Old Woman
[speaker 13] Chiaki
[speaker 14] {firstname 3}

[msg KAGIKOWARE]
{F2 08 FF FF}{speed 6}> The door has become deformed
and won't open.
{wait}

[msg EREKOWARE]
{F2 08 FF FF}{speed 6}> Nothing happened.
{wait}

[msg JIHAN]
{F2 08 FF FF}{speed 6}> You see a vending machine!
{wait}
---
{F2 08 FF FF}> You have enough change
to buy a drink.
{wait}
---
{F2 08 FF FF}> Will you buy something?
{wait}

[sel STOKERE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg STOKERE_YES]
{F2 08 FF FF}{speed 6}> The drink that came out
isn't any of the ones listed.
{wait}
---
{F2 08 FF FF}> You obtained a {color 4}Mysterious Drink{color 0}.
{wait}

[msg STOKERE_NO]
{F2 08 FF FF}{speed 6}> You decide to hurry on ahead.
{wait}

[msg URIKIRE]
{F2 08 FF FF}{speed 6}> The vending machine is sold-out.
{wait}

[msg DOAKATAI]
{F2 08 FF FF}{speed 6}> The entrance is closed tight.
{wait}

[msg REIKONROB speaker 0] // Ghost
{F2 08 FF FF}{speed 6}Dang!
{wait}
---
{F2 08 FF FF}I came here to sell medicine,
and now I get dragged into
all this rubbish.
{wait}

[msg SINENROB speaker 1] // Soul
{F2 08 FF FF}{speed 6}I saw it!! I saw a human go
underground!!
{wait}
---
{F2 08 FF FF}It's him... This is his doing!!
{wait}

[msg IDCARDGET]
{F2 08 FF FF}{speed 6}> There is an {color 1}Employee ID Card{color 0}.
Will you pick it up?
{wait}

[sel IDCARDGET_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg IDCARDGET_YES]
{F2 08 FF FF}{speed 6}> You obtained an {color 1}Employee ID Card{color 0}.
{wait}

[msg IDCARDGET_NO]
{F2 08 FF FF}{speed 6}> You gave up on
the {color 1}Employee ID Card{color 0}.
{wait}

[msg IDCARDGET_HIKAWA]
{F2 08 FF FF}{speed 6}> You feel like you met {color 1}Hikawa{color 0}.
{wait}

[msg SINEN_ODO speaker 1] // Soul
{F2 08 FF FF}{speed 6}Eh!?
{wait}
---
{F2 08 FF FF}What's goin' on???
{wait}

[msg KAISETU speaker 1] // Soul
{F2 08 FF FF}{speed 6}I saw a demon at the annex...
{wait}
---
{F2 08 FF FF}Wait a minute, demons really
exist!?
{wait}

[msg JIBAKU speaker 2] // Stranded Soul
{F2 08 FF FF}{speed 6}You're still alive, too?
{wait}
---
{F2 08 FF FF}Boy, I sure see a lot of humans
today.
{wait}
---
{F2 08 FF FF}As a matter of fact...
I just saw one go down to
the basement.
{wait}
---
{F2 08 FF FF}I'm envious of you guys!
Being able to walk around and
all... *sigh*
{wait}

[msg BORTEX speaker 3] // Self-Destructing Ghost
{F2 08 FF FF}{speed 6}The Vortex World...
That's what we call this place.
{wait}
---
{F2 08 FF FF}Of course, the world hasn't been
reborn yet.
{wait}
---
{F2 08 FF FF}And I don't know what it's gonna be
like when it does get reborn...


[msg SUICIDE speaker 4] // Ghost Patient
{F2 08 FF FF}{speed 6}If you negotiate well with demons,
they'll join your party.
{wait}
---
{F2 08 FF FF}About negotiating... Well, I dunno
all the details, so I can't tell you
anything specific.
{wait}
---
{F2 08 FF FF}But, don't let that stop you from
trying!
{wait}

[msg NEGO speaker 1] // Soul
{F2 08 FF FF}{speed 6}You're not a human, are you?
Then, let me tell you something
good...
{wait}

[msg NEGONE speaker 1] // Soul
{F2 08 FF FF}{speed 6}Listen up. First, you need to get
demons to join you.
{wait}
---
{F2 08 FF FF}That's right! You need demons on
your side.
{wait}
---
{F2 08 FF FF}If you run into a demon, try starting
a conversation.
{wait}
---
{F2 08 FF FF}I'm sure you'll get a response.
It won't always be a good response,
mind you!
{wait}

[msg ROBAKUMA speaker 1] // Soul
{F2 08 FF FF}{speed 6}You see it too, huh!?
That g-giant demon in the lobby???
{wait}
---
{F2 08 FF FF}We c-can't go near there!
{wait}

[msg MAILGAL speaker 1] // Soul
{F2 08 FF FF}{speed 6}Eeeek! A demon!
There's a demon!!
{wait}
---
{F2 08 FF FF}Demon's are scary, right??
They attack people, right???
{wait}
---
{F2 08 FF FF}EEEEK!! I need to text message
my boyfriend!!
{wait}

[msg UTAGAUHITO speaker 1] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}You're a demon, too???
{wait}

[msg HATEHOS speaker 1] // Soul
{F2 08 FF FF}{speed 6}I hate hospitals. They always
give me an eerie feeling. I'd hate to
die in one!
{wait}
---
{F2 08 FF FF}Wha'? Now's not the time?
Demons have appeared!?
{wait}
---
{F2 08 FF FF}For reals?! ...Eh, just as long as
there are no ghosts. I'm so scared
of ghosts!
{wait}

[msg TATAKAIKATA speaker 1] // Soul
{F2 08 FF FF}{speed 6}When you fight demons, you'll have
a better chance of winning if
you can get more actions in during
your turn.
{wait}
---
{F2 08 FF FF}By using attacks that the enemy is
weak against, you'll be able to
attack more frequently.
{wait}
---
{F2 08 FF FF}But, the enemy will gain the upper
hand if you do the opposite!
{wait}
---
{F2 08 FF FF}So, make sure you use your actions
wisely.
{wait}

[msg BOSSMAE speaker 1] // Soul
{F2 08 FF FF}{speed 6}What!? You're going to defeat
Forneus!?
{wait}

[sel BOSMAE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg BOSSMAE_YES speaker 1] // Soul
{F2 08 FF FF}{speed 6}Hahaha... Yeah, right!
I'll give you all my money
if you can do that.
{wait}

[msg BOSSMAE_NO speaker 1] // Soul
{F2 08 FF FF}{speed 6}I guess I heard wrong...
{wait}

[msg BOSSMAEFNASI speaker 1] // Soul
{F2 08 FF FF}{speed 6}Amazing... You really beat Forneus!!
{wait}

[msg BOSSMAEFARI speaker 1] // Soul
{F2 08 FF FF}{speed 6}............
{wait}
---
{F2 08 FF FF}You really beat him...
{wait}
---
{F2 08 FF FF}Dang! A promise is a promise!!
Take it!!
{wait}
---
{F2 08 FF FF}> You obtained {color 4}100 Macca{color 0}.
{wait}

[msg BOSS speaker 5] // Forneus
{F2 08 FF FF}{speed 6}You wanna get through?
{wait}
---
{F2 08 FF FF}What, you think you can beat me?
{wait}

[sel BOSS_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg BOSS_YES speaker 5] // Forneus
{F2 08 FF FF}{speed 6}Oh yeah...?
{wait}
---
{F2 08 FF FF}Then, bring it on!!!
{wait}

[msg BOSS_NO speaker 5] // Forneus
{F2 08 FF FF}{speed 6}That's a smart decision!
{wait}
---
{F2 08 FF FF}It's best you don't leave this
hospital.
{wait}
---
{F2 08 FF FF}Give it up, loser.
{wait}

[msg IRIGUTI]
{F2 08 FF FF}{speed 6}> You feel the presence of someone
on the roof.
{wait}
---
{F2 08 FF FF}> Enter through the doorway?
{wait}

[sel IRIGUTI_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg IRIGUTI_YES]
{F2 08 FF FF}{speed 6}Entering big map.
{wait}

[msg TORIREI speaker 1] // Soul
{F2 08 FF FF}{speed 6}If I knew this would happen
for reals...
{wait}
---
{F2 08 FF FF}I should've listened to Hikawa.
{wait}

[msg HIDOIUWASA speaker 1] // Soul
{F2 08 FF FF}{speed 6}I don't know the details, but...
{wait}
---
{F2 08 FF FF}I heard that this hospital did
some pretty horrific things!
{wait}

[msg TIKARENGO speaker 6] // X-ray room
{F2 08 FF FF}{speed 6}> For some reason, you cannot
go inside the X-ray room.
{wait}

[msg UTIKAGI speaker 7] // Door
{F2 08 FF FF}{speed 6}> It's locked from the other side.
{wait}

[msg KAIFUKU speaker 8] // Doctor's spirit
{F2 08 FF FF}{speed 6}You're injured... Here, let me
heal you.
{wait}
---
{F2 08 FF FF}There you go. Don't push yourself
too hard.
{wait}
---
{F2 08 FF FF}> Your wounds have healed.
{wait}

[msg RNTODORE_OPEN]
{F2 08 FF FF}{speed 6}The beginning of the
Vortex ends here.
{wait}
---
{F2 08 FF FF}After this event,
the world will become a Vortex.
{wait}
---
{F2 08 FF FF}It will then convert you
into a demonic human.
{wait}
---
{F2 08 FF FF}Then, you will wake up
in room 203.
{wait}

[msg TIKA_DOAUTI]
{F2 08 FF FF}{speed 6}> The door is locked.
Will you unlock it?
{wait}

[sel UTIDOA_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg TIKA_DOAAKI]
{F2 08 FF FF}{speed 6}> You unlocked the door.
{wait}

[msg TIKA_DOAYAME]
{F2 08 FF FF}{speed 6}> The door is still locked.
{wait}

[msg SINSETU speaker 1] // Soul
{F2 08 FF FF}{speed 6}Hey, kid!! This place is dangerous!!
{wait}
---
{F2 08 FF FF}There's demons past here!!
{wait}

[msg DROP2_GET speaker 1] // Soul
{F2 08 FF FF}{speed 6}> You obtained Chakra Drop x 2.
{wait}

[msg HOGYOKU1_GET speaker 1] // Soul
{F2 08 FF FF}{speed 6}> You obtained Magic Bead x 1.
{wait}

[msg CENT1F_EVLEV]
{F2 08 FF FF}{speed 6}> Select a floor.
{wait}

[sel CENT1F_EVLEV_SEL]
{F2 08 FF FF}2F
---
{F2 08 FF FF}B1F
---
{F2 08 FF FF}Quit.

[msg CENT2F_EVLEV]
{F2 08 FF FF}{speed 6}> Select a floor.
{wait}

[sel CENT2F_EVLEV_SEL]
{F2 08 FF FF}1F
---
{F2 08 FF FF}B1F
---
{F2 08 FF FF}Quit.

[msg CENTB1F_EVLEV]
{F2 08 FF FF}{speed 6}> Select a floor.
{wait}

[sel CENTB1F_EVLEV_SEL]
{F2 08 FF FF}1F
---
{F2 08 FF FF}2F
---
{F2 08 FF FF}Quit.

[msg TIKADOA speaker 9] // Security System
{F2 08 FF FF}{speed 6}Insert your {color 1}Annex Gate Pass{color 0}.
{wait}

[msg TIKADOA_NOTLV1 speaker 9] // Security System
{F2 08 FF FF}{speed 6}Insert your {color 1}Annex Gate Pass{color 0}.
{wait}

[msg TIKADOA_NOTLV1_2]
{F2 08 FF FF}> You don't have the right card...
{wait}

[msg SEKYU1 speaker 9] // Security System
{F2 08 FF FF}{speed 6}Insert your {color 1}ID Card{color 0}.
{wait}

[msg SEKYUOPEN speaker 9] // Security System
{F2 08 FF FF}{speed 6}Insert your {color 1}ID Card{color 0}.
{wait}

[msg SEKYUOPEN_2]
{F2 08 FF FF}> You used the {color 1}ID Card{color 0}.
{wait}

[msg SEKYU2A speaker 9] // Security System
{F2 08 FF FF}{speed 6}Insert your {color 1}Annex Gate Pass{color 0}.
{wait}
---
{F2 08 FF FF}> You used the {color 1}Annex Gate Pass{color 0}.
{wait}
---
{F2 08 FF FF}The gate closed!
{wait}

[msg ISA_DENWA]
{F2 08 FF FF}{speed 6}*ring* *ring*
{wait}

[msg ISA_DENWA2 speaker 10] // Isamu
{F2 08 FF FF}Hello? Hello?
{wait}
---
{F2 08 FF FF}Oh, hell!
The elevator stopped
working!!
{wait}
---
{F2 08 FF FF}I'm pressing the emergency
button, but nothing's
happening...
{wait}
---
{F2 08 FF FF}Dammit!
Modern technology my ass!
{wait}

[msg ISA_DENWA3]
{F2 08 FF FF}> You can hear the sound
of Isamu kicking the door.
{wait}

[msg ISA_DENWA4 speaker 10] // Isamu
{F2 08 FF FF}...Anyways, this isn't the time
for Chiaki!
Get someone over here!
{wait}
---
{F2 08 FF FF}Yes, I know who Reiko is...
She's on the second floor!
{wait}
---
{F2 08 FF FF}If Reiko's not there,
anyone'll do...
{wait}
---
{F2 08 FF FF}Any...wa...y...call...som...one...
{wait}

[msg ISA_DENWA5]
{F2 08 FF FF}> The signal is weakening.
{wait}

[msg OKUJOU1]
{F2 08 FF FF}{speed 6}> This door leads to the roof.
{wait}
---
{F2 08 FF FF}> It's locked.
{wait}

[msg DAREMOINAI]
{F2 08 FF FF}{speed 6}> No one is here...
{wait}

[msg HIKAWASARU]
{F2 08 FF FF}{speed 6}> The man left.
{wait}

[msg TAMIKAGI]
{F2 08 FF FF}{speed 6}> The door is locked.
{wait}

[msg LUSSARU]
{F2 08 FF FF}{speed 6}> The child and the old woman
have disappeared...
{wait}

[msg FURI_LUS1]
{F2 08 FF FF}{speed 6}> Someone is up ahead...
{wait}

[msg FURI_LUS2 speaker 11] // Child
{F2 08 FF FF}{speed 6}(no message)
{wait}

[msg FURI_LUS3 speaker 12] // Old Woman
{F2 08 FF FF}{speed 6}What's wrong, my little master?
Are you wondering about that
person over there?
{wait}

[msg FURI_LUS4 speaker 12] // Old Woman
{F2 08 FF FF}{speed 6}I see.
My, my...
{wait}

[msg FURI_LUS5 speaker 12] // Old Woman
{F2 08 FF FF}{speed 6}But, we're busy at the moment.
Let's come back later.
{wait}

[msg FURI_LUS6 speaker 11] // Child
{F2 08 FF FF}{speed 6}Perhaps it is...
an exclusive love
for one's self.
{wait}

[msg FURI_LUS7 speaker 11] // Child
{F2 08 FF FF}{speed 6}Turn your principle into power
and survive the chaos.
{wait}

[msg CHIAKI_1F speaker 13] // Chiaki
{F2 08 FF FF}{speed 6}You're late.
We're ready to go home!
{wait}
---
{F2 08 FF FF}...Just kiddin'.
Look, we've been waiting, 
but we haven't met Yuko.
{wait}
---
{F2 08 FF FF}This hospital's weird.
There's no one around here,
even at the reception area.
{wait}
---
{F2 08 FF FF}I had Isamu look for Yuko,
but he hasn't come back yet.
{wait}
---
{F2 08 FF FF}*sigh*
Maybe I should go home... 
{wait}
---
{F2 08 FF FF}What's that magazine?
{wait}
---
{F2 08 FF FF}Ayakashi Monthly?
Never heard of it.
Is it new?
{wait}
---
{F2 08 FF FF}Do me a favor?
Could you look for Isamu?
I wanna get outta here already.
{wait}
---
{F2 08 FF FF}He's probably somewhere on
the second floor.
{wait}
---
{F2 08 FF FF}I'll be waiting here.
...Whoa, this is one
bizarre-lookin' magazine.
{wait}

[msg CHIAKI_1F2 speaker 14] // {firstname 3}
{F2 08 FF FF}{speed 6}{lipsync}Can you find {firstname 2}?
I see no point in staying here
if we can't find Ms. {lastname 1}.
{wait}
---
{F2 08 FF FF}{lipsync}He should be on the second floor,
where the patients' rooms are.
{wait}

[msg CHIAKI_1F3 speaker 14] // {firstname 3}
{F2 08 FF FF}{speed 6}{lipsync}This magazine is so... bizarre...
{wait}

[msg ISAMU_2F speaker 10] // Isamu
{F2 08 FF FF}{speed 6}Whoa!!!
{wait}
---
{F2 08 FF FF}Oh, it's you.
Dude!
Don't scare me like that!
{wait}
---
{F2 08 FF FF}Still, something's seriously up
with this hospital.
No one was there, huh?
{wait}

[sel ISAMU_2F_SEL]
{F2 08 FF FF}Not a living soul.
---
{F2 08 FF FF}Yeah, there was.

[msg ISAMU_2F2 speaker 10] // Isamu
{F2 08 FF FF}{speed 6}Really?
Something's definitely up!
{wait}

[msg ISAMU_2FNO speaker 10] // Isamu
{F2 08 FF FF}{speed 6}Really?
Oh... you mean Chiaki.
{wait}

[msg ISAMU_2F3 speaker 10] // Isamu
{F2 08 FF FF}{speed 6}*sigh*
I was so looking forward to
hangin' with Yuko.
{wait}
---
{F2 08 FF FF}Man, what is up with
this haunted house of
a hospital?
{wait}
---
{F2 08 FF FF}Seen the basement? Dude! 
It's like they're making 
some sorta monster down there.
{wait}
---
{F2 08 FF FF}Just thinking about it
makes me......!
{wait}
---
{F2 08 FF FF}Hey, man... 
I gotta go take a leak.
{wait}
---
{F2 08 FF FF}Chiaki's in the lobby, right?
Let's meet up there.
Peace out!
{wait}

[msg ISAMU_2F4]
{F2 08 FF FF}{speed 6}> {firstname 2} left.
{wait}

[msg ISAMU_GONE]
{F2 08 FF FF}{speed 6}> {firstname 2} left the room.
{wait}

[msg CHIAKI_GONE]
{F2 08 FF FF}{speed 6}> {firstname 3} isn't in the lobby...
{wait}

[msg RECHIAKI_1F speaker 13] // Chiaki
{F2 08 FF FF}{speed 6}Hey, man,
about this magazine...
{wait}
---
{F2 08 FF FF}There's a special report on
this group called the 'Gaea cult'.
{wait}
---
{F2 08 FF FF}Their leader, Hikawa...
I've seen him before!
{wait}
---
{F2 08 FF FF}It was a while back,
and he was with Yuko.
{wait}
---
{F2 08 FF FF}He's scary. According to the
Scripture of Miroku, the world
'will be swallowed by chaos'.
{wait}
---
{F2 08 FF FF}I highly doubt anything's gonna
happen, but I'm worried about
Yuko and this hospital...
{wait}
---
{F2 08 FF FF}Oh, yeah. When I told Isamu about 
all this, he went to have another
look around.
{wait}
---
{F2 08 FF FF}He gave me this.
Check it out.
{wait}

[msg RECHIAKI_1F2]
{F2 08 FF FF}{speed 6}> You obtained an {color 1}Employee ID Card{color 0}.
{wait}

[msg RECHIAKI_1F3 speaker 14] // {firstname 3}
{F2 08 FF FF}{speed 6}I'll be waiting here.
I wonder if we'll find her...
{wait}

[msg RECHIAKI_1F4 speaker 14] // {firstname 3}
{F2 08 FF FF}{speed 6}I wonder if we'll find her...
{wait}

[msg HIKAROOM_B1F]
{F2 08 FF FF}{speed 6}> You can hear eerie sounds
from inside.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel HIKAROOM_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg LUSI_2F]
{F2 08 FF FF}{speed 6}> Someone is in the other hallway...
{wait}

[msg LUSI_2F2 speaker 11] // Child
{F2 08 FF FF}{speed 6}Shouldn't you hurry?
The countdown's already started.
{wait}

[msg LUSI_2F3 speaker 12] // Old Woman
{F2 08 FF FF}{speed 6}It's almost time.
Chaos will be here...
{wait}

[msg OKUJO]
{F2 08 FF FF}{speed 6}> There is no one here...
{wait}

[msg ISAMU_DAREKA]
{F2 08 FF FF}{speed 6}> Someone is in the other hallway.


[msg ISAMU_TONARI]
{F2 08 FF FF}{speed 6}> You can hear something
in the other room...
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

[msg F014_HIKAWA]
{F2 08 FF FF}{speed 6}> You can hear eerie sounds from
the room.
{wait}
---
{F2 08 FF FF}> Will you enter the room?
{wait}

[sel F014_HIKAWA_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F014_HIKAWA2]
{F2 08 FF FF}{speed 6}> The door is closed tight.
{wait}

[msg F014_GIMIC01]
{F2 08 FF FF}{speed 6}> The door is locked from
the other side.
{wait}

[msg F014_GIMIC02]
{F2 08 FF FF}{speed 6}> The door is closed tight.
{wait}

[msg F014_GIMIC03]
{F2 08 FF FF}{speed 6}> The door will not open.
{wait}

[msg F014_GIMIC04]
{F2 08 FF FF}{speed 6}> The door is locked.
{wait}

[msg F014_GIMIC05]
{F2 08 FF FF}{speed 6}> The door is unlocked.
{wait}
---
{F2 08 FF FF}> Will you enter?
{wait}

[sel F014_GIMIC05_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg F014_GIMIC06]
{F2 08 FF FF}{speed 6}> There is a notice on the information
board.
{wait}
---
{F2 08 FF FF}"This hospital consists of
a {color 1}main building{color 0} and an {color 1}annex{color 0},
connected by a {color 1}passageway{color 0}."
{wait}
---
{F2 08 FF FF}"Only authorized personnel are
allowed in the {color 1}basement{color 0}."
{wait}

