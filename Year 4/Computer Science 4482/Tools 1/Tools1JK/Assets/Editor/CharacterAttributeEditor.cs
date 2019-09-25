using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

// Custom Tool for Tools 1 Assignment

// Setting up the Custom Editor
[CustomEditor(typeof(CharacterAttributes))]
public class CharacterAttributeEditor : Editor
{
    // Setting the Min and Max values for attributes
    int attributeMax = 100;
    int attributeMin = 0;

    public override void OnInspectorGUI()
    {
        // Create a character reference
        CharacterAttributes character = (CharacterAttributes)target;

        // Popup selection to choose what class
        // Added the assignment to fix the error
        character.classType = (CharacterAttributes.ClassType) EditorGUILayout.EnumPopup("Class", character.classType, EditorStyles.popup);
        

        // Int field to set the value of experience
        character.experience = EditorGUILayout.IntField("Experience", character.experience);

        // Label field to show what the level is based on the amount of exp
        EditorGUILayout.LabelField("Level", character.level.ToString());

        // Attribute label
        EditorGUILayout.PrefixLabel("Attributes:");
        EditorGUI.indentLevel++;

        // Sliders to adjust the values for endurance, speed, and knowledge
        character.endurance = EditorGUILayout.IntSlider(new GUIContent("Endurance"), character.endurance, attributeMin, attributeMax);
        EditorGUILayout.LabelField("HP", character.maxHP.ToString());

        character.knowledge = EditorGUILayout.IntSlider(new GUIContent("Knowledge"), character.knowledge, attributeMin, attributeMax);
        EditorGUILayout.LabelField("MP", character.maxMP.ToString());

        character.speed = EditorGUILayout.IntSlider(new GUIContent("Speed"), character.speed, attributeMin, attributeMax);
        EditorGUILayout.LabelField("Evasion", character.maxEvasion.ToString());

        EditorGUI.indentLevel--;
    }
}