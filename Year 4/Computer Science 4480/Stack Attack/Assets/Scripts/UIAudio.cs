using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIAudio : MonoBehaviour {

    public AudioClip btnHighlightedSound;
    public AudioClip btnPressedSound;

    public AudioSource source;

    public void BtnHighlight()
    {
        source.clip = btnHighlightedSound;
        source.Play();
    }

    public void BtnPress()
    {
        source.clip = btnPressedSound;
        source.Play();
    }

}
