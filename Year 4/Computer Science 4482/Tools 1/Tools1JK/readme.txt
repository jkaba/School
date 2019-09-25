CS4482 Tools 1
Name: Jameel Kaba
UWO ID: jkaba
Student #: 250796017

Editor Tutorials done:
- Building a Custom Inspector
	- Files associated:
		- LevelScriptEditor.cs
		- LevelScript.cs
- Adding Buttons to a Custom Inspector
	- Files associated:
		- ObjectBuilderEditor.cs
		- ObjectBuilder.cs
- The DrawDefaultInspector Function
	- Files associated:
		- SomeScriptEditor.cs
		- SomeScript.cs

Created MonoBehaviour Asset: CharacterAttribute.cs 
It helps create a character with the following attributes
- class type (character can be one of four classes)
- exp points 
- level (calculated based on the amount of exp)
- endurance 
- hp (calculated based on endurance)
- knowledge stat 
- mp (calculated based on knowledge)
- speed stat
- evasion (calculated based on speed)

differences between The default editor and custom editor: 
- the default editor did not show the following fields:
	- level	
	- hp
	- mp
	- evasion
- endurance, knowledge, and speed stats are set using a slider in the custom editor

The TestScene just contains a cube on a light blue background.
The cube has the character attribute assigned to it
