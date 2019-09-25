using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Language
{

    // Private Variables
    // Lnaguage is the name of the language
    private string language;

    // Dictionary is used to hold the keys and values for translations
    private Dictionary<string, string> languageKeyValue;

    /*
     * createLanguage method
     * This method takes a string which is the name of the language
     * and also creates a dictionary object for the translations 
     */
    public void createLanguage(string lang)
    {
        language = lang;
        languageKeyValue = new Dictionary<string, string>();
    }

    /*
     * getDictionary method
     * This method returns a dictionary containing the translations
     * for a language
     */
    public Dictionary<string, string> getDictionary()
    {
        return languageKeyValue;
    }

    /*
     * getName method
     * This method returns the name of a language
     */
    public string getName()
    {
        return language;
    }

    /*
     * addToDictionary method
     * This method takes a 2 strings (a key and a value)
     * and stores it into the dictionary
     */
    public void addToDictionary(string key, string value)
    {
        languageKeyValue.Add(key, value);
    }

    /*
     * removeKey method
     * This method takes a string key and removes it
     * from the dictionary
     */
    public void removeKey(string key)
    {
        languageKeyValue.Remove(key);
    }
}