using UnityEngine;
using System.Collections;

public class LoseCollider : MonoBehaviour {

    // variables
	public GameScript gs;
	public StoryGameScript sgs;
	public int type = 0;
	
    // If ball hits lose collider, then activate method in game script
	void OnTriggerEnter2D (Collider2D collision)
    {
		if (collision.gameObject.tag.Equals ("Ball"))
        {
			if (type == 0)
            {
				gs.Killed ();
			}
            else
            {
				sgs.Killed ();
			}
		}
	}
}
