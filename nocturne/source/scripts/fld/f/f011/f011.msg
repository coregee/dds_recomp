// messages of fld/f/f011/f011
[speaker 0] Announcer
[speaker 1] Message
[speaker 2] Employee

[msg ANNOUNCE speaker 0] // Announcer
{F2 08 FF FF}{speed 6}Please do not rush onto the train.
The door is now closing.


[msg ANNOUNCE2 speaker 0] // Announcer
{F2 08 FF FF}{speed 6}Yoyogi Park Station!
Yoyogi Park Station!


[msg MAIL]
{F2 08 FF FF}{speed 6}> You received a message.
{wait}

[msg MAIL2 speaker 1] // Message
{F2 08 FF FF}{speed 6}You're late... You're way late,
{firstname 0} {lastname 0}!
{wait}
---
{F2 08 FF FF}You haven't forgotten that we're
going to visit Ms. {lastname 1},
have you?
{wait}
---
{F2 08 FF FF}Hurry up and get over to
Yoyogi Park. You're wasting
my quality time!
{wait}

[msg MAIL3]
{F2 08 FF FF}{speed 6}> It's from your classmate.
{wait}
---
{F2 08 FF FF}> Enter his name.
{wait}

[msg MAIL4 speaker 1] // Message
{F2 08 FF FF}{speed 6}I don't care if you come or not,
but Ms. {lastname 1}'s nice to me
when you're around...
{wait}
---
{F2 08 FF FF}Oh yeah, you better make sure you
look nice for her.
{wait}
---
{F2 08 FF FF}How about the jacket you bought
the other day... Y'know, the one
with a demon graphic on it?
{wait}
---
{F2 08 FF FF}You're just the mood maker.
Don't forget that.
{wait}

[msg JIHAN]
{F2 08 FF FF}{speed 6}> You see a vending machine!
{wait}
---
{F2 08 FF FF}> You have enough change to buy
a drink.
{wait}
---
{F2 08 FF FF}> Will you buy something?
{wait}

[sel STOKERE_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg STOKERE_YES]
{F2 08 FF FF}{speed 6}> The drink that came out isn't any of
the ones listed.
{wait}
---
{F2 08 FF FF}> You obtained a {color 4}Mysterious Drink{color 0}.
{wait}

[msg STOKERE_NO]
{F2 08 FF FF}{speed 6}> You decided to hurry on ahead.
{wait}

[msg URIKIRE]
{F2 08 FF FF}{speed 6}> The vending machine is sold out.
{wait}

[msg EKIIN_01 speaker 2] // Employee
{F2 08 FF FF}{speed 6}...Huh??? A customer?
{wait}

[msg EKIIN_02 speaker 2] // Employee
{F2 08 FF FF}{speed 6}Are you heading to Yoyogi Park,
too?
{wait}
---
{F2 08 FF FF}After the incident, we've had a lot
of lookee-loos, but not so many
customers.
{wait}
---
{F2 08 FF FF}Man, I've had a lot of free time
on my hands...
{wait}
---
{F2 08 FF FF}...Huh? Are you saying that
you haven't heard the news???
{wait}

[sel EKIIN_02_SEL]
{F2 08 FF FF}What's going on?
---
{F2 08 FF FF}I heard about it.

[msg EKIIN_02_YES speaker 2] // Employee
{F2 08 FF FF}{speed 6}Hmmm... How should I put this?
Yesterday, there was a {color 1}riot{color 0} at
Yoyogi Park.
{wait}
---
{F2 08 FF FF}If you want the details, you can
check the giant screen.
{wait}
---
{F2 08 FF FF}A buncha people were killed.
You could hear the sirens wailing
all night long.
{wait}

[msg EKIIN_02_NO speaker 2] // Employee
{F2 08 FF FF}{speed 6}Who hasn't, right? I mean,
it's all over the news.
{wait}

[msg EKIIN_02_A speaker 2] // Employee
{F2 08 FF FF}{speed 6}I'm sorry about that. I was
so bored! I just needed someone
to talk to.
{wait}

[msg EKIIN_02_B speaker 2] // Employee
{F2 08 FF FF}{speed 6}I'm sorry about that... I shouldn't be
talking on the job, even if I'm not
busy...
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

[msg INFTEST0]
{F2 08 FF FF}{speed 6}> Message Test
Now for the basics...
{wait}

[msg INFTEST1]
{F2 08 FF FF}{speed 6}> Message Test
Next are the choices...
{wait}

[sel INFTEST1_SEL]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg INFTEST1_YES]
{F2 08 FF FF}{speed 6}Yes, you say?
{wait}

[msg INFTEST1_NO]
{F2 08 FF FF}{speed 6}No, you say?
{wait}

