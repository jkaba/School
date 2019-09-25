using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;
using LitJson;

public class LanguageManager
{

    // Private Variables

    // current language is the currently selected language
    private string currentLanguage;

    // language list is the list of languages 
    private List<Language> languageList = new List<Language>();

    // json string used for saving
    private string jsonString;

    /*
     * getLanguages method
     * This method gets all languages available
     * 
     */
    public List<string> getLanguages()
    {
        // Create a list to store languages
        List<string> languages = new List<string>();

        // Loop through list of languages adding it to our recently created list
        for(int i = 0; i < languageList.Count; i++)
        {
            languages.Add(languageList[i].getName());
        }

        // Return our new list of languages
        return languages;
    }

    /*
     * getLanguageList method
     * This method returns the list of languages
     */
    public List<Language> getLanguageList()
    {
        return languageList;
    }

    /*
     * getCurrentLanguage method
     * This method gets the currently selected language
     */
    public string getCurrentLanguage()
    {
        return currentLanguage;
    }

    /*
     * getCurrentLanguageIndex method
     * This method returns the location of the current language
     * from inside the language list 
     */
    public int getCurrentLanguageIndex()
    {
        for(int i = 0; i < languageList.Count; i++)
        {
            if(languageList[i].getName() == currentLanguage)
            {
                return i;
            }
        }
        return 0;
    }

    /*
     * setDefaultLanguage method
     * This method takes a string which is the name of a language
     * This string then becomes the default language
     */
    public void setDefaultLanguage(string defaultLanguage)
    {
        currentLanguage = defaultLanguage;
    }

    /*
     * setValue method
     * This method takes an int (index location) and two strings (key and value)
     * The key inside the dictionary at the specified index in the language
     * list is set to be the string represented by value
     */
    public void setValue(int listIndex, string key, string value)
    {
        languageList[listIndex].getDictionary()[key] = value;
    }

    /* 
     * removeLanguage method
     * This method takes an int which represents the 
     * index location for the language to be removed
     */
    public void removeLanguage(int index)
    {
        languageList.RemoveAt(index);
    }

    /*
     * createNewLanguage method
     * This method takes a string and a dictionary and creates a new language
     * This language is stored in the language list and saved
     */
    public void createNewLanguage(string newLanguageName, Dictionary<string, string> tempLanguage)
    {
        // Add a new language in the list
        languageList.Add(new Language());

        // store the language at the end of the list
        languageList[languageList.Count - 1].createLanguage(newLanguageName);

        // create a list of keys based on the dictionary
        List<string> keys = new List<string>(tempLanguage.Keys);

        // Loop through the dictionary and copy it onto the dictionary for the new language
        for(int i = 0; i < keys.Count; i++)
        {
            languageList[languageList.Count - 1].addToDictionary(keys[i], tempLanguage[keys[i]]);
        }

        // Save the file
        saveJSON();
    }

    /*
     * Load method
     * This method loads the json file containing all of the languages and translations
     */
    public void Load()
    {
        // Set up the file to be loaded
        jsonString = File.ReadAllText(Application.dataPath + "/Resources/localization.json");
        JsonReader reader = new JsonReader(jsonString);

        // Set up variables
        string previousHeader = "";
        bool needNextLine = false;
        bool objectStarted = false;

        // While the file is not at the end
        while (reader.Read())
        {
            // Check to see if the file is null
            string type = reader.Value != null ? reader.Value.GetType().ToString() : "";

            // If the File is not null
            if(reader.Value != null)
            {

                // Is the current string "currentLanguage"
                if (reader.Value.ToString() == "currentLanguage")
                {
                    // If so, then set that to the previous header and request for the next line
                    previousHeader = "currentLanguage";
                    needNextLine = true;
                }

                // Is the previous header "currentLanguage" and do we need the next line
                else if (previousHeader == "currentLanguage" && needNextLine)
                {
                    // If so, then set the default language to be the current value, we do not need the next line
                    setDefaultLanguage(reader.Value.ToString());
                    needNextLine = false;
                }

                // Is the Token the property name and has the object not been started
                else if (reader.Token.ToString() == "PropertyName" && !objectStarted)
                {
                    // Add a new language based on the reader value to the list and store it at the end
                    languageList.Add(new Language());
                    languageList[languageList.Count - 1].createLanguage(reader.Value.ToString());

                    // Set objectStarted to true
                    objectStarted = true;
                }

                // If the token is propertyName, the object is started, and we don't need the next line
                else if (reader.Token.ToString() == "PropertyName" && objectStarted && !needNextLine)
                {
                    // Set the previous header to be the value of reader, and we need the next line
                    previousHeader = reader.Value.ToString();
                    needNextLine = true;
                }

                // If the object is started, and we need the next line
                else if(objectStarted && needNextLine)
                {
                    // Add the previous header, and reader value to the last dictionary
                    languageList[languageList.Count - 1].addToDictionary(previousHeader, reader.Value.ToString());

                    // We do not need the next line
                    needNextLine = false;
                }
            }

            // If the reader token is ObjectEnd then set objectStarted to false
            else if(reader.Token.ToString() == "ObjectEnd")
            {
                objectStarted = false;
            }
        }
    }

    /*
     * saveJSON method
     * This method saves the data into a json file
     */
    public void saveJSON()
    {
        // Initial Set up
        StringBuilder sb = new StringBuilder();
        JsonWriter writer = new JsonWriter(sb);

        // Start Writing with the current language and name
        writer.WriteObjectStart();
        writer.WritePropertyName("currentLanguage");
        writer.Write(currentLanguage);

        // Loop through the list of languages and write all translations for each language
        for(int i = 0; i < languageList.Count; i++)
        {
            writer.WritePropertyName(languageList[i].getName());
            writer.WriteObjectStart();
            foreach(KeyValuePair<string, string> entry in languageList[i].getDictionary())
            {
                writer.WritePropertyName(entry.Key);
                writer.Write(entry.Value);
            }
            writer.WriteObjectEnd();
        }

        // Stop Writing
        writer.WriteObjectEnd();

        // Save the file in the resources folder under the name localization.json
        File.WriteAllText(Application.dataPath + "/Resources/localization.json", sb.ToString());
    }
}