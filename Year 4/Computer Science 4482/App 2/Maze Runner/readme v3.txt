CS4482 App 2 
Name: Jameel Kaba
UWO ID: jkaba
Student #: 250796017

Maze Runner

Upon Starting you are given the main menu with the following 3 options
- Play Game
	- Starts the game
- LeaderBoard
	- Shows you the top 5 rankings
	- If this is your first time playing, the rankings have default values
- Quit Game
	- Quit the game and close the application

Upon Starting the game, you are given screen asking you to enter a 3 character name
- If the name is < or > 3 char you will be given an error message
- If the name is 3 char, then upon pressing submit you will begin the game

You control a character at the outside of the maze
- up and down arrow keys are used to move the character back and forward
- left and right arrow keys are used to rotate the camera
	
- To pause the game, you press the 'esc' key
	- Pause menu options
		- Restart
			- Restarts the game to the start of the maze
		- Main Menu
			- Brings you back to the main menu
		- Quit
			- Closes the app
- To close the pause menu, press the 'esc' key once more

You are given 5 minutes, to go through the maze
- The maze is broken into 4 parts
- To advance to the next part you must find the key for that part
	- Once you have collected the key, the door will auto open

Upon reaching the end of the maze or running out of time, the game over animation will play

After about 5 seconds, the LeaderBoard will pop up
- If you rank in the top 5, you get a congratulations message
- If not, you can still see the top 5
- Press the Main Menu button to return to the main menu
- Press the Quit button to close the application

The maze was built using Unity Primitives

Scripts from Tutorials
- Survival Shooter Tutorial
	- CameraFollow
	- Player Movement
	- The code from these scripts were used as a base, and have been modified
- Making a Main Menu Tutorial
	- LoadSceneOnClicked
	- QuitOnClicked

Assets Used
- Survival Shooter Tutorial
	- Player Model
	- Player Animation
	- Player Textures
	- Player Material
	- player prefab
- From Asset Store
	- Handpainted keys 1.0 by RoboCG
		- key model
		- key texture
	- Doors Free - A Powerful Door Script 2.3 by Murakami
		- door model
		- door texture
		- door materials