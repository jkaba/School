using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;


//This Script is from the Building a Custom Inspector Tutorial

//Setting up the custom editor
[CustomEditor(typeof(LevelScript))]
public class LevelScriptEditor : Editor
{
    public override void OnInspectorGUI()
    {
        LevelScript myTarget = (LevelScript)target;

        //Setting up an int field to adjust the experience value
        myTarget.experience = EditorGUILayout.IntField("Experience", myTarget.experience);

        //The level is shown in a label field and is determined by experience/750
        EditorGUILayout.LabelField("Level", myTarget.level.ToString());
    }
}
