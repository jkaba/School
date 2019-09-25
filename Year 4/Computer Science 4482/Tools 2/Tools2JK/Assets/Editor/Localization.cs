using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using UnityEngine.UI;

public class Localization : EditorWindow
{
    // Private Variables

    // Initial setup
    private LanguageManager languageManager;
    private List<Language> languageList;
    private List<string> languageStrings;
    private int selectedLanguage = 0;

    // Variables for creating a new language
    private bool createNewLanguage = false;
    private string createNewLanguageName = "";
    private Dictionary<string, string> tempLanguage = new Dictionary<string, string>();

    // Variables for creating a new translation
    private bool createNewTranslation = false;
    private string createNewTranslationKey = "";
    private string createNewTranslationValue = "";

    // Statement to have the tool be found under the window option
    [MenuItem("Window/Localization")]

    /*
     * Init method
     * This method initializes and opens the window
     */ 
    static void Init()
    {
        EditorWindow.GetWindow(typeof(Localization));
    }

    /*
     * OnEnable method
     * This method sets up the language manager on runtime
     */
    private void OnEnable()
    {
        // Create a new language manager
        languageManager = new LanguageManager();

        // Load the language manager if possible
        languageManager.Load();

        // Load all the languages into the list of languages
        languageStrings = languageManager.getLanguages();

        // Set the selected language to be the current index
        selectedLanguage = languageManager.getCurrentLanguageIndex();
    }

    /*
     * OnGUI method
     * This method creates/runs the GUI
     */ 
    void OnGUI()
    {
        // Get all the language names
        languageStrings = languageManager.getLanguages();
        GUILayout.BeginHorizontal();

        // When not creating a new language
        if (!createNewLanguage)
        { 
            // Select Language Popup
            selectedLanguage = EditorGUILayout.Popup("Select Language", selectedLanguage, languageStrings.ToArray(), GUILayout.Width(Screen.width - 50));
        }

        // When creating a new language / The field for the new language
        else
        { 
            // Enter New Language label and text field
            GUILayout.Label("Enter New Language", GUILayout.Width((Screen.width / 2) - 25));
            createNewLanguageName = EditorGUILayout.TextField(createNewLanguageName, GUILayout.Width((Screen.width / 2) - 25));
        }

        // If the + Button is pressed, then create a new language 
        if (GUILayout.Button("+"))
        { 
            createNewLanguageName = "";
            newLanguage();
            GUIUtility.keyboardControl = 0;
            return;
        }

        // Labelling on the GUI
        GUILayout.EndHorizontal();
        GUILayout.BeginVertical(GUILayout.ExpandWidth(true), GUILayout.ExpandHeight(true));
        GUILayout.BeginHorizontal("box");
        GUILayout.Label("Name/ID/Other");
        GUILayout.Label("Translation");
        GUILayout.EndHorizontal();

        // Get the list of all languages
        languageList = languageManager.getLanguageList();

        // When not creating a new langugae
        if (!createNewLanguage)
        { 
            // Loop through the list of languages
            for (int i = 0; i < languageList.Count; i++)
            {
                // If the language is currently selected then set it as the default
                if (languageList[i].getName() == languageStrings[selectedLanguage])
                { 
                    languageManager.setDefaultLanguage(languageStrings[selectedLanguage]); 
                    List<string> keys = new List<string>(languageList[i].getDictionary().Keys);

                    // For every key (translation)
                    foreach (string key in keys)
                    {
                        // Display the translations
                        GUILayout.BeginVertical();
                        GUILayout.BeginHorizontal("box");
                        GUILayout.Label(key, GUILayout.Width((Screen.width / 2) - 25));
                        languageManager.setValue(i, key, EditorGUILayout.TextField(languageList[i].getDictionary()[key], GUILayout.Width((Screen.width / 2) - 25)));

                        // If the "X" button is pressed then delete the translation
                        if (GUILayout.Button("X"))
                        {
                            removeTranslation(key);
                            return;
                        }
                        GUILayout.EndHorizontal();
                        GUILayout.EndVertical();
                    }
                }
            }
        }
        // When creating a new language
        else
        { 
            // Setup a list of keys (translations)
            List<string> keys = new List<string>(tempLanguage.Keys);

            // For each key (translation) display it
            foreach (string key in keys)
            {
                GUILayout.BeginVertical();
                GUILayout.BeginHorizontal("box");
                GUILayout.Label(key, GUILayout.Width((Screen.width / 2) - 25));
                tempLanguage[key] = EditorGUILayout.TextField(tempLanguage[key], GUILayout.Width((Screen.width / 2) - 25));
                GUILayout.EndHorizontal();
                GUILayout.EndVertical();
            }
        }
        // If creating a new language
        if (createNewLanguage)
        {
            GUILayout.BeginHorizontal();

            // If the create button is clicked, then go to the function
            if (GUILayout.Button("Create", GUILayout.Width(200)))
            {
                createNewLanguageFunction(); 
            }

            // If the cancel button is clicked, then set the create new language variable to false
            if (GUILayout.Button("Cancel", GUILayout.Width(200)))
            {
                createNewLanguage = false;
            }
            GUILayout.EndHorizontal();
        }
        // If the language list is not empty and we are not creating a new language
        if (languageList.Count > 0 && !createNewLanguage)
        {
            // We are not creating a new translation
            if (!createNewTranslation)
            { 
                // If the button for new translation is clicked
                if (GUILayout.Button("New Translation", GUILayout.Width(200)))
                {
                    createNewTranslationKey = "";
                    createNewTranslationValue = "";
                    createNewTranslation = true;
                    GUIUtility.keyboardControl = 0;
                }
            }
            // We are creating a new translation
            else
            { 
                // Set up the text fields for the translation
                GUILayout.BeginHorizontal("box");
                createNewTranslationKey = GUILayout.TextField(createNewTranslationKey);
                createNewTranslationValue = EditorGUILayout.TextField(createNewTranslationValue);
                GUILayout.EndHorizontal();

                // If the save translation button is pressed
                if (GUILayout.Button("Save Translation", GUILayout.Width(200)))
                {
                    // Call the function to create a new translation
                    createNewTranslationFunction();

                    // Set the create new translation variable to false
                    createNewTranslation = false;
                }
                // If the cancel translation button is pressed
                if (GUILayout.Button("Cancel Translation", GUILayout.Width(200)))
                {
                    createNewTranslationKey = "";
                    createNewTranslationValue = "";
                    createNewTranslation = false;
                }
            }
        }
        GUILayout.EndVertical();

        // If there are more than 0 languages and we are not creating a new language
        if (languageList.Count > 0 && !createNewLanguage)
        {
            // If the delete button is pressed
            if (GUILayout.Button("Delete " + languageManager.getCurrentLanguage(), GUILayout.Width(200)))
            {
                // delete the selected language
                deleteLanguage(selectedLanguage);
            }
        }
        // If we are not creating a new language and are not creating a new translation
        if (!createNewLanguage && !createNewTranslation)
        {
            // Save the file
            saveJSON();
        }
        // Update the game
        updateGameObjects(); 
    }

    /*
     * saveJSON method
     * This method calls the saveJSON method of the language manager and saves the file
     */
    public void saveJSON()
    {
        languageManager.saveJSON();
    }

    /*
     * deleteLanguage method
     * This method takes an int parameter that represents the index of the language to be deleted
     * The language at the specified index is deleted
     */
    public void deleteLanguage(int index)
    {
        // Call the remove language methods
        languageManager.removeLanguage(index);
        languageStrings.RemoveAt(index);
        selectedLanguage = 0;

        // If there are more languages left in the language list
        if (languageManager.getLanguageList().Count > 0)
        {
            // Set the default language to be the first language on the list
            languageManager.setDefaultLanguage(languageManager.getLanguageList()[0].getName());
        }
        // Otherwise, set the default language to be nothing
        else
        {
            languageManager.setDefaultLanguage("");
        }
        // Save the file
        languageManager.saveJSON();
    }

    /*
     * newLanguage method
     * This method creates a new language
     */
    public void newLanguage()
    {
        // Set variable to true and create a dictionary for the language
        createNewLanguage = true;
        tempLanguage = new Dictionary<string, string>();

        // If there are more than 0 languages
        if (languageManager.getLanguageList().Count > 0)
        {
            // Create a copy of the keys for the first language's dictionary on the language list
            List<string> keys = new List<string>(languageManager.getLanguageList()[0].getDictionary().Keys);

            // Loop through the keys and add them to the language
            for (int i = 0; i < keys.Count; i++)
            {
                tempLanguage.Add(keys[i], "");
            }
        }
        // If there are no languages, then return
        else
        {
            return;
        }
    }

    /*
     * createNewLanguageFunction
     * This method is used to create a new language in the language manager
     * Also sets variables
     */
    public void createNewLanguageFunction()
    {
        // If the new language name is not empty
        if (createNewLanguageName != "")
        {
            // Call the createNewLanguage method
            languageManager.createNewLanguage(createNewLanguageName, tempLanguage);

            // temp language is set to a new dictionary
            tempLanguage = new Dictionary<string, string>();

            // create new language is set to false
            createNewLanguage = false;
        }
    }

    /*
     * removeTranslation method
     * This method removes a translation that is based on the string given as input
     */
    public void removeTranslation(string keyToRemove)
    { 
        // Loop through the list of languages
        for (int i = 0; i < languageManager.getLanguageList().Count; i++)
        {
            // If the language at index i matches with the one given as input it will be removed
            languageManager.getLanguageList()[i].removeKey(keyToRemove);
        }
        // Save the file
        languageManager.saveJSON();
    }

    /*
     * createNewTranslationFunction method
     * This method is used for creating a new translation
     */ 
    public void createNewTranslationFunction()
    {
        // If the new translation is not empty and does not already exist in the dictionary
        if (createNewTranslationKey != "" && !languageManager.getLanguageList()[selectedLanguage].getDictionary().ContainsKey(createNewTranslationKey))
        {
            // Loop through the language list
            for (int i = 0; i < languageManager.getLanguageList().Count; i++)
            {
                // If the language at index i is the selected language
                if (i == selectedLanguage)
                {
                    // Add the translation to the dictionary
                    languageManager.getLanguageList()[selectedLanguage].addToDictionary(createNewTranslationKey, createNewTranslationValue);
                }
                // If the language at i is not the selected langugae
                else
                {
                    // Add the new key to the dictionary with an empty value
                    languageManager.getLanguageList()[i].addToDictionary(createNewTranslationKey, "");
                }
            }
            // Set the new translation key and value variables to empty
            createNewTranslationKey = "";
            createNewTranslationValue = "";

            // Save the file
            languageManager.saveJSON();
        }
    }

    /*
     * updateGameObjects method
     * This method updates game objects with the appropriate translations
     * based on the currently selected language
     */
    public void updateGameObjects()
    {
        // Get the list of languages and the languages themselves
        languageList = languageManager.getLanguageList();
        languageStrings = languageManager.getLanguages();

        // Loop through the list of languages
        for (int i = 0; i < languageList.Count; i++)
        {
            // If the name of the language on the list at i matches the selected language
            if (languageList[i].getName() == languageStrings[selectedLanguage])
            {
                // Copy the keys onto a list
                List<string> keys = new List<string>(languageList[i].getDictionary().Keys);

                // Go through every key (translation)
                foreach (string key in keys)
                {
                    // Create a gameobject based on the key
                    GameObject go = GameObject.Find(key);

                    // If the key exists
                    if (go != null)
                    {
                        // If the text component is not null
                        if (go.GetComponent<Text>() != null)
                        {
                            // Update the text with the new translation
                            go.GetComponent<Text>().text = languageList[i].getDictionary()[key];
                        }

                        // If the component in children is not null
                        else if (go.GetComponentInChildren<Text>() != null)
                        {
                            // Update the text with the new translation
                            go.GetComponentInChildren<Text>().text = languageList[i].getDictionary()[key];
                        }
                    }
                }
            }
        }
    }
}