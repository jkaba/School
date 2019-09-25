using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

//This script is from the Adding Buttons to a Custom Inspector Tutorial

//Set up Custom inspector
[CustomEditor(typeof(ObjectBuilder))]
public class ObjectBuilderEditor : Editor
{
    public override void OnInspectorGUI()
    {
        //Set up default inspector
        DrawDefaultInspector();

        //variable to hold object builder reference
        ObjectBuilder myScript = (ObjectBuilder)target;

        //Create a Button such that when clicked it calls BuildObject
        if(GUILayout.Button("Build Object"))
        {
            myScript.BuildObject();
        }
    }
}
