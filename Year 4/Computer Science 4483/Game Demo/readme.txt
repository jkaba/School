CS4483 Game Demo
Invader Breaker

*Important note: this game is made in Unity 2017.3.1f1, so please ensure that you have unity installed on your computer*
*Unity can be downloaded for free at the following link: https://store.unity.com/				       *

How to Start:
- Windows:
	- In the folder there will be a .exe file called "InvaderBreakerDemo.exe"
	- Open this file to start the game
	- Set the display settings to 1280x720 or 1280x800

The game is meant to be played with display settings of 1280x720 or 1280x800
If using any other display settings, the game will still function, though the dialogue part of the story will be displayed wierdly

A MAC port of the demo was planned, but due to unexpected issues, it was not able to be completed at this time.

*In order for the game to function properly, the application must be in the same directory as the Assets folder. *
*This is due to the Assets folder containing a resources folder which stores the save data.			 *

How To Play:

The player can move left and right, and is moved via either the left and right keys or the 'a' and 'd' keys
The player can launch the ball by pressing the space bar.
If the ball has not been launched, the player can pause the game pressing 'esc'
If the ball has been launched, the player can press 'esc' to reset the ball, though there is a penalty for doing so.

Use the mouse to click through the menus
In dialogue, press the space bar to continue the dialogue

Main Menu:
On the Main menu the player is given 3 choices.
- Story
	- This will load up the story mode, for the demo only the first world is available
- Survival
	- This will load up survival mode, here the player can select a power up and start playing right away.
- Quit Game
	- Clicking this will close the application

For the purposes of this demo, everything is unlocked right away.

Starting a story level:
By pressing story on the main menu, the player will be brought to a level select screen.
Here the player can select a chapter to play through.
Upon selecting a chapter, the player will be brought to the pre gameplay dialogue.
Once the dialogue is over, the player is sent to gameplay.
If the player fails the objective, they can either return to one of the menu's or try again.
If the player completes the objective, they are brought to the post gameplay dialogue.
After the dialogue, the player is sent back to the level select screen.

Generally, levels are locked until the previous level is completed.
But, for the purposes of the demo all of chapter 1 is unlocked right away.

Starting Survival mode:
By pressing survival mode on the main menu, the player will be brought to a power up select screen.
Here the player can choose any of the power ups to help aid them during gameplay.

Generally, the power ups are unlocked based on the number of points you have accumulated over time.
But, for the purposes of the demo all power ups are unlocked right away.

Power up Breakdown
- Classic (No power up, standard gameplay)
- Long paddle (Literally, a longer paddle you control)
- Wrecking Ball (All enemies die in 1 hit)
- Tri ball (three balls instead of 1)
- Slo mo (Enemies move at half speed)
- Stun Free (Player will not be stunned upon being hit by a laser)

After selecting a power up, the player needs to enter a name for the leaderboards.
The name can be no more than 9 characters.

After submitting a name, the player is brought into gameplay.
For every 1000 points, a spaceship will spawn across the top of the screen.
For every 10,000 points, an extra life is given.

Upon running out of lives, the game will end and a leaderboard will be displayed.
From the leaderboard, the player can either replay or return to one of the previous menus

Gameplay:
Enemies will spawn and move left and right while firing lasers at the player.
Depending on the level, the enemies may wait for you to make the first move before attacking
If the player is hit by a laser they will be briefly stunned.

The ball is essentially the players lifeline.
If the ball goes beyond the player, they will lose a life.
The ball will bounce off of the boundaries of the level, the player controlled board, and enemies.
If the ball hits an enemy laser, it will destroy the laser.

*In survival mode, enemies will change form based on how much health they have left.

If the player decides they want to reset the current run. They can press 'esc' to bring the ball back to initial position.
However, doing so will cost the player a life.

Credits:

Code used in this game is broken down as followed
- Space Invaders Code: Re-used and modified from an earlier project I had done
- Brick Breaker Code: New Code which I had written for this project

Art Assets are broken down as follows:
Background image, and menu sprites: Unity Samples UI 1.2.1 (downloaded free from Unity Asset Store)
Sprites were drawn by myself with some assets were reused from a project I had done previously.

Music used in this game, is from the Dark Sci-Fi Music Pack by Andrew Isaias.
This was downloaded for free from the Unity Asset Store