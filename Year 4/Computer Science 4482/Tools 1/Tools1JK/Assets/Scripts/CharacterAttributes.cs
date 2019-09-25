using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// 4 types of class types to choose from
public class CharacterAttributes : MonoBehaviour
{
    //Attributes script used for assigning attributes to characters
    // This is what was causing the error
    public enum ClassType { Paladin, Monk, BlackMage, WhiteMage }

    // reference variables
    public ClassType classType;
    public int experience;

    // level variable
    public int level
    {
        // levels are earned for every 1000 experience points
        get { return experience / 1000;  }
    }

    public static explicit operator CharacterAttributes(Enum v)
    {
        throw new NotImplementedException();
    }

    // Three parameters used to determine HP, MP, and Evasion for characters
    public int endurance;
    public int speed;
    public int knowledge;

    // A Characters max HP is determined by how much endurance they have
    public int maxHP
    {
        get { return endurance * 15; }
    }

    // A Characters max MP is determined by how much knowledge they have
    public int maxMP
    {
        get { return knowledge * 10; }
    }

    // A Characters evasion stat is determined by their speed 
    public int maxEvasion
    {
        get { return speed * 5; }
    }
}