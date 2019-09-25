using UnityEngine;
using System.Collections;

public class Ball : MonoBehaviour {
	
    // Variables
	private Paddle paddle;
	public bool hasStarted = false;
	private Vector3 paddleToBallVector;
	public GameScript gs;
	public StoryGameScript sgs;
	public int type = 0;

	// Use this for initialization
	public void Start ()
    {
        // Find the paddle and set the position of the ball
		paddle = GameObject.FindObjectOfType<Paddle>();
		paddleToBallVector = this.transform.position - paddle.transform.position;
	}
	
	// Update is called once per frame
	void Update ()
    {
        // If not type 2, then survival mode
		if (type != 2)
        {
            // If not paused
			if (gs.pause == false)
            {
                // If not started
				if (!hasStarted)
                {
					// Ball is locked to paddle
					this.transform.position = paddle.transform.position + paddleToBallVector;
			
					// Once space is pressed, then launch
					if (Input.GetKeyDown ("space"))
                    {
						hasStarted = true;
						this.GetComponent<Rigidbody2D> ().velocity = new Vector2 (2f, 10f);
					}
				}
			}
		}
        else
        {
            // Story not paused
			if (sgs.pause == false)
            {
                // Not started
				if (!hasStarted)
                {
					// Ball locked to paddle
					this.transform.position = paddle.transform.position + paddleToBallVector;

					// Press space to launch
					if (Input.GetKeyDown ("space"))
                    {
						hasStarted = true;
						this.GetComponent<Rigidbody2D> ().velocity = new Vector2 (2f, 10f);
					}
				}
			}
		}
	}

	public void dead()
    {
        // Set has started to false and reset ball position
		hasStarted = false;
		Vector3 adder = new Vector3 (0, 10, 0);
		this.transform.position = paddle.transform.position + adder;
	}
	
	void OnCollisionEnter2D (Collision2D collision)
    {
		if (collision.gameObject.tag.Equals("EnemySpaceship"))
		{
			// Run the kill method for enemy space ship
			collision.gameObject.GetComponent<EnemySpaceshipScript>().Kill();

			if (type != 2)
            {
				// Add to the score based on the enemy tag
				gs.AddToScore (collision.gameObject.GetComponent<Collider2D> ().tag);
			}
		}

		else if (collision.gameObject.tag.Contains("Enemy"))
		{
			// create an enemy object based on what was hit
			Enemy enemy = (Enemy)collision.gameObject.GetComponent("Enemy");

            // Based on type, accordingly deal damage to enemies
			if (type == 1 || type == 2)
            {
				// Run the Dead method for the enemy
				enemy.Dead (3);
			} 	
			else
            {
				enemy.Dead (1);
			}

			if (enemy.health == 0)
            { 
				if (type != 2)
                {
					// Add to the score based on the enemy tag
					gs.AddToScore (collision.gameObject.GetComponent<Collider2D> ().tag);
				}
			}
		}
        
		else if (collision.gameObject.tag.Contains("Boss"))
		{
			BossScript boss = (BossScript)collision.gameObject.GetComponent("BossScript");
			boss.Dead (5);
			if (boss.health == 0)
            {
				sgs.complete = true;
			}
		}
	}
}
