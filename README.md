This is a blackjack game I made during my time off from school. It features a working game loop and working AI. The player starts off with 500 chips and can gain or lose those chips based on their luck and skill.
It uses a time based seed to generate random cards. I'm still working on a way to derive a better RNG engine than a time based one (seeing as how a time based RNG engine is predictable).

Version 0:

This version was generally a conceptual version. It offered prototypes for different AIs as well as the framework for the game itself.

Version 1:

Here we did away with the different AI prototypes. I also implemented a general AI that is designed to react to the player's current hand. A recursive function named hitFunction was also implemented. HitFunction is the game engine, and while buggy, handled a lot of the core blackjack gameplay.

Version 2: 

Version 2 implemented a betting system. Other improvements included the introduction of an exit condtion (where the player reaches <= 0 chips). This version was still buggy and was improved upon in later iterations.

Version 3:

A lot of the indentation and parenteses were ugly to look at, so I went through and updated them to improve readability. I also added pointers to certain varibales (namely the 'chips' variable so that I could better keep track of the chips as they were passed to different functions). The version also altered the flow of the program as a means of fixing certain bugs.

Version 4: 

In progress.
