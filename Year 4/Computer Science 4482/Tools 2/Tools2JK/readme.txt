CS4482 Tools 2
Name: Jameel Kaba
UWO ID: jkaba
Student #: 250796017

Localization Tool Mini-Guide:

The localization tool can be found by opening the language tool under Window --> Language

- You can change the selected language by the dropdown menu
- The Name/ID/Other is the reference associated with the GameObject name and must be unique
- While the game is being played, the GameObjects that match the appropriate name will have
  their text values updated with the translation string

Adding a Language:
- To add a language, click the "+" button located on the top right
	- Enter the name and translations if they already exist

Deleting a Language:
- To delete a language, click the "Delete" button in the bottom left

Adding a Translation:
- To add a translation for a language, click the "New Translation" button
	- Enter the Name/ID/Other and translation and click the "Save Translation" button.
	- This will add the name to all languages; however, the translation will be empty
	  for all languages other than the currently selected language

Deleting a Translation:
- To delete a translation click the "X" button located beside the translation
	- This will delete the translation for ALL languages

Saving:
- All data is saved to the localization.json file located in the Resources folder
- On every GUI call localization.json is loaded and saved to keep data continuous