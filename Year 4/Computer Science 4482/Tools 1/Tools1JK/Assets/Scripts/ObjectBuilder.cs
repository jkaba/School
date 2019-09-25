using System.Collections;
using System.Collections.Generic;
using UnityEngine;


//This script is from the Adding Buttons to a Custom Inspector Tutorial
public class ObjectBuilder : MonoBehaviour
{
    //objects used for tutorial
    public GameObject obj;
    public Vector3 spawnPoint;

    //BuildObject method that is used for when the button is pressed
    public void BuildObject()
    {
        Instantiate(obj, spawnPoint, Quaternion.identity);
    }
}
