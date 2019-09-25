CS4482 App 3
Name: Jameel Kaba
UWO ID: jkaba
Student #: 250796017

Space Invaders Remix

How To Play:

The player can move left and right, and is moved via either the left and right keys or the 'a' and 'd' keys
The player can shoot lasers by pressing the space bar. 
The player can pause the game by pressing 'esc'

Main Menu:
On the Main menu the player is given 3 choices.
- Start 
	- This will begin the process to start the game
- Leaderboard
	- This will display the top 5 scores, the player can return to the main menu from here
- Quit Game
	- Clicking this will close the application

The Main Menu also displays the Lifetime total for points that the player has, this is used to unlock new ships

Starting the game:
By pressing start on the main menu, the player will be asked to enter their name. 
This name can be no more than 9 characters.

After submitting a name the game will proceed to the ship selection screen.
The ship model, as well as it's name, and stats are displayed.
To change ships, press the 'Next Ship' button.
There are 5 ships to choose from, each with a different name, skin, and stats

If you do not have enough lifetime points, then rather than a start button, an error will be displayed.
This error will display how many more points are needed to unlock the ship.

Upon hitting start, the game will load up.
The enemies will not start shooting until you are ready and shoot them first.
These space invaders have no interest in shooting you unless you disturb them.

For every 1000 points, a spaceship will spawn across the top of the screen, and an extra life is given.
If the spaceship is destroyed, a powerup sphere will spawn.

There are 5 possible powerup spheres.
Blue: Enemy Movement is cut in half for 5 seconds
Red: The player gets an extra hit (health + 1)
Green: The ship's shot speed is increased to the next level
White: The ship's shot power is increased to the next level
Yellow: The ship's movement speed is increased to the next level

Powerups stack if the colors are the same
For example, 2 white powerups will increase shot power 2 levels

But, the Green, White, and Yellow powerups are only active until another powerup of a different color other than red is collected.
For example, if you collect 2 green powerups and then a yellow, the shot speed is reverted to it's original stat,
and the movement speed will be in the next level.

This does not apply to Red powerup, as this will just add 1 to health.

Powerup stat Breakdown:
Blue: 	shot speed = original | shot power = original | movement speed = original
Red: 	shot speed = current  | shot power = current  | movement speed = current
Green:	shot speed = +1 level | shot power - original | movement speed = original
White:	shot speed = original | shot power = +1 level | movement speed = original
Yellow:	shot speed = original | shot power = original | movement speed = +1 level

To pause the game press 'esc'.
Pause Menu:
- Restart
	- This restarts the game at the beginning of the stage
- Main Menu
	- returns the player to the main menu
- Quit 
	- Closes the Application

To close the pause menu press 'esc' again

What's displayed during gameplay
- Health: How much health the ship has left
- Score: Current score
- Lives: How many lives the player has left

When the player gets hit, they lose 1 health.
When health reaches 0, the player loses a life.
When the player is out of lives, the game ends.

Upon the game ending the leaderboard is displayed

The leaderboard displays the top 5 scores.
If the players score is in the top 5, then a congratulatory message is displayed
The player can either go back to the main menu, or quit the game from the leaderboard menu

For the purposes of this assignment, the lifetime total is preset to 10000 so that 3 ships are usable.
This can be changed by going to the resources folder, and modifying the first line in the Save.txt file
