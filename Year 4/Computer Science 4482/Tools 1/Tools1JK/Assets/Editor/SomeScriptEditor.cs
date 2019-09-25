using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

//This script is from the DrawDefaultInspector tutorial

//Set up custom inspector
[CustomEditor(typeof(SomeScript))]
public class SomeScriptEditor : Editor
{
    public override void OnInspectorGUI()
    {
        //Default inspector settings are put in the custom inspector
        DrawDefaultInspector();

        //Adding a help box
        EditorGUILayout.HelpBox("This is a help box", MessageType.Info);
    }
}
