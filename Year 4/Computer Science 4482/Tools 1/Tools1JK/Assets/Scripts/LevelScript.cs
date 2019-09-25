using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//This Script is from the Building a custom Inspector Tutorial
public class LevelScript : MonoBehaviour
{
    // experience and level fields
    public int experience;
    public int level
    {
        // The value of level goes up every 750 experience points
        get { return experience / 750; }
    }
}
