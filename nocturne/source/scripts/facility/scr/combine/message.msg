// messages of facility/scr/combine/message
[speaker 0] Minister

[msg msg_1st speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}This is the Cathedral of Shadows...
What is your bidding?


[msg msg_1st_fullmoon speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}This is the Cathedral of Shadows...
The heavens shine brightly.
What is your bidding?


[msg msg_1st_curse speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}This is the Cathedral of Shadows...
What is your bidding, cursed one?


[msg msg_err_dev_nums speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}You do not have enough demons...
{wait}

[msg msg_sacrifice speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Kagutsuchi is at its brightest...
Will you offer a sacrifice?


[msg msg_confirm speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Are you sure?


[msg msg_err_dev_lev speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}You aren't strong enough
to control it...
{wait}

[msg msg_err_dev_dbl speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}You already have one
in your party...
{wait}

[msg msg_trouble_change speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Hmmm...?
It seems an unexpected demon
was born.
{wait}

[msg msg_trouble_enhance speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Hmmm...?
It seems it is more powerful
than expected.
{wait}

[msg msg_2nd speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}What will you do?


[msg msg_encyc_top speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}What will you do
with the Compendium?


[msg msg_write_err_nobody speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}You do not have anyone who
needs to be registered.
{wait}

[msg msg_see_err_nocontents speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}No one is registered yet.
{wait}

[msg msg_write speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Who will you register?
{wait}

[msg msg_write_updatecheck speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}There is already a record of this
demon. Will you overwrite it?
{wait}

[msg msg_write_updateend speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}{var 1} has been registered.
{wait}

[msg msg_summon_check speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}It will cost {var 2} Macca.
Are you okay with that?
{wait}

[msg msg_summon_check_err speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}It will cost {var 2} Macca...
But, it seems you don't
have enough.
{wait}

[msg msg_talk speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}What do you want to know?


[msg msg_exit speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Come back again.
{wait}

[sel msg_sel01]
{F2 08 FF FF}Yes.
---
{F2 08 FF FF}No.

[msg msg_encyc_regist_top speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}These are the demons that
differ from the records.
Who will you register?


[msg msg_encyc_regist_confirm speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}There is already a record of this
demon. Will you overwrite it?
{wait}

[msg msg_encyc_regist_confirm speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}The record has been updated.
{wait}

[msg msg_encyc_regist_confirm speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Hmmm...
That is everyone.
{wait}

[msg msg_encyc_summon speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}It will cost {color 4}{var 0} Macca{color 0}.
Are you okay with that?


[msg msg_encyc_summon_result speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}I have succeeded in summoning
{var 1}.
{wait}

[msg msg_encyc_summon_error0 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}It will cost {color 4}{var 0} Macca{color 0}...
But, it seems you don't 
have enough.
{wait}

[msg msg_encyc_summon_error1 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}You already have one
in your party...
{wait}

[msg msg_encyc_summon_error2 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Your party is full.
{wait}

[msg msg_encyc_summon_error3 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}You are not strong enough
to control it...
{wait}

[msg msg_encyc_summon_error4 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Even I cannot handle
this man...
{wait}

[msg msg_encyc_registall speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Is it okay to register everyone?


[msg msg_encyc_registall_done speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}I registered everyone.
{wait}

[msg msg_manin_item_follow speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}> The {color 4}{var 5}{color 0}
lost its brilliance...
{wait_nospeaker}{F2 08 FF FF}{wait}

[msg birth_msg_boy speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
Nice ta meetcha, mister.
{wait}

[msg birth_msg_girl speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
You'd better take good care of me.
{wait}

[msg birth_msg_lady speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
A pleasure to meet you.
{wait}

[msg birth_msg_witch speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
Let's have some fun together!
{wait}

[msg birth_msg_heehaw speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of the {color 4}{var 4}{color 0} clan.
Let's go, hee ho!
{wait}

[msg birth_msg_beast speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I AM {color 4}{var 0}{color 0} OF
THE {color 4}{var 4}{color 0} CLAN.
NICE TO MEET YOU. 
{wait}

[msg birth_msg_gentle speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
Charmed, I'm sure...
{wait}

[msg birth_msg_punk speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
I can't wait to kick some ass!
{wait}

[msg birth_msg_oldman speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
Let's take it easy, sonny!
{wait}

[msg birth_msg_oldwoman speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
I'm glad to meet you...
{wait}

[msg birth_msg_lord speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
I am at thy command.
{wait}

[msg birth_msg_manekata speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}You can't fuse a Manikin, fool.
And, they call 'me' a dummy!?
{wait}

[msg birth_msg_heroine speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
At your service!
{wait}

[msg birth_msg_samurai speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am {color 4}{var 0}{color 0} of
the {color 4}{var 4}{color 0} clan.
I place my life in your hands.
{wait}

[msg birth_msg_thing speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}> {color 4}{var 0}{color 0} of the {color 4}{var 4}{color 0} clan
is shaking.
{wait_nospeaker}{F2 08 FF FF}{wait}
---
{F2 08 FF FF}> It seems to have accepted you
as its master.
{wait_nospeaker}{F2 08 FF FF}{wait}

[msg birth_msg_yoju speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}Me {color 4}{var 0}{color 0} the {color 4}{var 4}{color 0}.
Me eat everyone!!
{wait}

[msg birth_msg_devil speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}Kagutsuchi shines
On the path to victory
The sweet scent of blood.
{wait}
---
{F2 08 FF FF}Take me, {color 4}{var 0}{color 0},
with you and we'll raise hell!
{wait}

[msg birth_msg_0xC7 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am the {color 4}{var 4} {var 0}{color 0}!
Victory shall be yours!
Death shall be mine!
{wait}

[msg birth_msg_0xC8 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm the {color 4}{var 4} {var 0}{color 0}.
My anger is hell's blessing...
{wait}

[msg birth_msg_0xC9 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am the {color 4}{var 4} {var 0}{color 0}.
Allow me to hold your funeral...
{wait}

[msg birth_msg_0xC4 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}Haha!
I am the {color 4}{var 4} {var 0}{color 0}!
Behold my overflowing power!
{wait}

[msg birth_msg_0xC5 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am the {color 4}{var 4} {var 0}{color 0}.
Time for another war, eh?
{wait}

[msg birth_msg_0xC6 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}...I am the {color 4}{var 4} {var 0}{color 0}.
My thirst for blood...
...shall never be quenched...
{wait}

[msg birth_msg_0xC3 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am the {color 4}{var 4} {var 0}{color 0}.
I shall be witness to your death.
{wait}

[msg birth_msg_0xCA speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}Hohohoho! Listen carefully!
I am the {color 4}{var 4} {var 0}{color 0}!
Now, entertain me!
{wait}

[msg birth_msg_0xCB speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am the {color 4}{var 4} {var 0}{color 0}.
With the echoes of my trumpet,
your enemies shall perish...
{wait}

[msg birth_msg_0xC2 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am {color 4}{var 0}{color 0} the {color 4}{var 4}{color 0}.
I'll lend the Demi-fiend my power.
{wait}

[msg birth_msg_0xC1 speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am {color 4}{var 0}{color 0} the {color 4}{var 4}{color 0}.
I entrust my wrath to you...
{wait}

[msg birth_msg_0xCC speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I am {color 4}{var 0}{color 0} the {color 4}{var 4}{color 0}.
I have returned from the dead
to help.
{wait}

[msg birth_msg_0xCD speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}I'm {color 4}{var 0}{color 0} the {color 4}{var 4}{color 0}! Hyahaha!
Ya want me to kill some more?
{wait}

[msg birth_msg_0xCF speaker var 0]
{F2 08 FF FF}{speed 6}{style 0}This is the true form of
{color 4}{var 0}{color 0} the {color 4}{var 4}{color 0}.
...Let us hurry, Demi-fiend.
{wait}

[msg talk_msg01 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Fusion is the ritual of fusing two
demons together to form a new one.
{wait}
---
{F2 08 FF FF}You can usually create a demon
with a higher level than the
two you originally fused.
{wait}
---
{F2 08 FF FF}You are essentially trading in 
two demons for one, so you will 
be losing a member.
{wait}
---
{F2 08 FF FF}It is always important that you
keep in mind the ability of
your members before fusing them.
{wait}
---
{F2 08 FF FF}Some demons don't fuse with 
others, like those from
dark and light alliances.
{wait}
---
{F2 08 FF FF}If you want to survive,
be sure not to forget
these basics.
{wait}

[msg talk_msg02 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}I assume that you are already
aware that demons are 
categorized into 'races'...
{wait}
---
{F2 08 FF FF}You should also be aware that the 
races 'Element' and 'Mitama'
are special.
{wait}
---
{F2 08 FF FF}If you use them in a fusion,
the outcome will differ from
that of a normal fusion.
{wait}
---
{F2 08 FF FF}If you fuse a normal demon with an
Element, it will become another
demon of the same race.
{wait}
---
{F2 08 FF FF}If you fuse it with a Mitama,
it will not be reborn, but it
will become more powerful.
{wait}
---
{F2 08 FF FF}It would be wise to remember
that.
{wait}

[msg talk_msg03 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}Kagutsuchi is the source of all
light present in the middle of
the world...
{wait}
---
{F2 08 FF FF}Its light has special powers,
and makes demons go mad.
{wait}
---
{F2 08 FF FF}When it is shining its
brightest, you can use the
light for fusion.
{wait}
---
{F2 08 FF FF}By offering another demon as
a sacrifice, you can use
'sacrificial fusion'.
{wait}
---
{F2 08 FF FF}Sacrificial fusion will allow
you to create demons with
higher stats and more skills.
{wait}
---
{F2 08 FF FF}There are demons that can only
be born from sacrificial fusion.
{wait}
---
{F2 08 FF FF}If you use it right, it will
be of great benefit to you.
{wait}
---
{F2 08 FF FF}Just remember that you can't
offer a sacrifice if you're
fusing with a Mitama.
{wait}
---
{F2 08 FF FF}Also, accidents often occur
when Kagutsuchi is at its 
brightest.
{wait}
---
{F2 08 FF FF}The choice is up to you...
{wait}

[msg talk_msg04 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}As minister, I am always
doing my best when fusing.
{wait}
---
{F2 08 FF FF}...But, nothing is always
definite.
{wait}
---
{F2 08 FF FF}Sometimes there are accidents 
during the ritual.
{wait}
---
{F2 08 FF FF}When that happens, even I
don't know what will be born.
{wait}
---
{F2 08 FF FF}Just remember that there
is always a chance that
something may go wrong...
{wait}

[msg talk_msg05 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}The demons born from fusion
may remember the skills of
the previous demons.
{wait}
---
{F2 08 FF FF}So, if you use it right, you
can have a demon with innate 
skills.
{wait}
---
{F2 08 FF FF}We do not know everything
about it yet, but let me
tell you three things...
{wait}
---
{F2 08 FF FF}First, the skills carried over
change every time you select 
the demons to be fused.
{wait}
---
{F2 08 FF FF}Second, the new demon has 
affinities with certain skills,
making some easier to remember.
{wait}
---
{F2 08 FF FF}Third, the level of the
demons to be fused affects how
many skills are carried over.
{wait}
---
{F2 08 FF FF}So, you see, leveling up the 
demons you already have is 
never a waste.
{wait}
---
{F2 08 FF FF}Remember that.
{wait}

[msg talk_msg06 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}The book that holds all of the
information about demons is known 
as the 'Demonic Compendium'.
{wait}
---
{F2 08 FF FF}If a demon joins your party,
it will automatically be
recorded in the Compendium.
{wait}
---
{F2 08 FF FF}Those recorded can be summoned
to any Cathedral of Shadows.
{wait}
---
{F2 08 FF FF}Also, if you level up a demon
and register it, you will be
able to summon it at that level.
{wait}
---
{F2 08 FF FF}...But, remember that it'll
cost you money to summon
a demon.
{wait}
---
{F2 08 FF FF}The stronger the demon, the
more it'll cost you. 
{wait}

[msg talk_msg07 speaker 0] // Minister
{F2 08 FF FF}{speed 6}{style 0}With the power they have sealed
inside, Magatama can change
humans into demons.
{wait}
---
{F2 08 FF FF}Each Magatama's powers are 
unique, giving their host 
new skills.
{wait}
---
{F2 08 FF FF}There are Magatama that can give
techniques that no other demon
has ever seen or used.
{wait}
---
{F2 08 FF FF}When will it give out new
techniques? Ask the Magatama
itself.
{wait}
---
{F2 08 FF FF}You can tell when the time is
near by its movement.
{wait}
---
{F2 08 FF FF}We help those who use Magatama
in order to fulfill our duty.
{wait}
---
{F2 08 FF FF}When you have collected all the 
Magatama... That will be the
time to carry out our mission.
{wait}
---
{F2 08 FF FF}Come back to the Cathedral
of Shadows once you have
collected all the Magatama.
{wait}

