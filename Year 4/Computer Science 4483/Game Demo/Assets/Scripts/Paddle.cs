using UnityEngine;
using System.Collections;

public class Paddle : MonoBehaviour {

    // Variables
	private Ball ball;
	public int speed = 10;
	float timer = 0f;
	bool stunner = false;
	public int type = 0;

	void Start () {
        // Find and set ball
		ball = GameObject.FindObjectOfType<Ball>();
	}
		
	// Update is called once per frame
	void Update ()
    {

        // If stunned don't move
		if (stunner && Time.time < timer) {
		}

        // Else move
		else
        {
			transform.Translate (speed * Time.deltaTime * Input.GetAxis ("Horizontal"), 0, 0);
		}

        // Long paddle constraints
        if (type == 1)
        {
            if (transform.position.x > 10)
            {
                transform.position = new Vector3(10f, transform.position.y, transform.position.z);
            }
            if (transform.position.x < -10)
            {
                transform.position = new Vector3(-10f, transform.position.y, transform.position.z);
            }
        }
        // small paddle constriants
        else
        {
            if (transform.position.x > 11)
            {
                transform.position = new Vector3(11f, transform.position.y, transform.position.z);
            }
            if (transform.position.x < -11)
            {
                transform.position = new Vector3(-11f, transform.position.y, transform.position.z);
            }
        }
	}

    // Stun method, which briefly stuns player if hit
	public void stun()
    {
		if (type == 0 || type == 1)
        {
			timer = Time.time + 0.1f;
			stunner = true;
		}
	}
}
