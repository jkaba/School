using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


/// <summary>
/// A class to manage character selection. Based on: 
/// https://www.youtube.com/watch?v=6legBueQHaU
/// </summary>
public class CharacterManager : MonoBehaviour
{
    public int numberOfUsers = 2;

    public List<PlayerBase> playerList = new List<PlayerBase>();
    public List<CharacterBase> characterList = new List<CharacterBase>();

    /// <summary>
    /// Finds and returns the chosen the character using the 
    /// character identifier.
    /// </summary>
    /// <returns>The character with identifier.</returns>
    /// <param name="id">Identifier.</param>
    public CharacterBase ReturnCharacterWithID(string id)
    {
        CharacterBase characterChoice = null;

        for (int i = 0; i < characterList.Count; i++)
        {
            if (string.Equals(characterList[i].characterId, id))
            {
                characterChoice = characterList[i];
                break;
            }
        }

        return characterChoice;
    }

    //a variable to hold the instance of the Character Manager.
    public static CharacterManager instance;

    /// <summary>
    /// Gets Character Manager instance.
    /// </summary>
    /// <returns>The instance.</returns>
    public static CharacterManager GetInstance()
    {
        return instance;
    }

    /// <summary>
    /// Instantiate the Character Manager and ensure it persists.
    /// </summary>
    void Awake()
    {
        instance = this;
        DontDestroyOnLoad(this.gameObject);
    }
}

/// <summary>
/// This class is a helper for managing the different characters
/// that a player can select in the game.
/// </summary>
[System.Serializable]
public class CharacterBase
{
    public string characterId;
    public GameObject prefab;

}

/// <summary>
/// This class is a helper for managing the player information.
/// </summary>
[System.Serializable]
public class PlayerBase
{

    public string playerId;
    public string inputId;
    public bool hasCharacter;
    public PlayerType playerType;
    public GameObject playerPrefab;
    public int score;

    public enum PlayerType
    {
        user, //this is the only actual possibility
        ai,
        simulation
    }
}







