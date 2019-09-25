using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossScript : MonoBehaviour {

	public static float enemyMoveSpeed = 0;
	public float changeInterval = 0F;
	private Transform mTransform;
	private Vector3 calc;

	// Material variables
	public Material[] materials;
	public int enemyType;

	// Death variables
	private float killtime = -1;
	private bool killed = false;

	// Parameter variables
	public int health = 100;
	private int playerType;

	void Start()
	{
		mTransform = transform;
	}

	void Update()
	{
		// Calculate movement
		calc = Vector3.back * enemyMoveSpeed * 0 * Time.deltaTime;
		mTransform.Translate(calc);

		// Set material
		this.SetMaterial();
	}

	// Used to set material during movement
	void SetMaterial()
	{
		// Calculate index used for changing the material while moving
		int index = (int)(Time.time / changeInterval);
		index = index % 2;

		// If the enemy is killed, then destroy it
		if (killed)
		{
			if (Time.time > this.killtime)
			{
				Destroy(this.gameObject);
			}
		}
		// Else set the materials
		else
		{
			GetComponent<Renderer>().sharedMaterial = materials[index + enemyType];
		}
	}

	// Used when collision is detected
	public void Dead(int damage)
	{
		// Reduce health by damage taken
		health -= damage;

		// If health is less than or equal to 0 the enemy is dead
		if (health <= 0)
		{
			// Set trigger to false
			GetComponent<Collider2D>().isTrigger = false;

			// Set killed to true and set kill time
			killed = true;
			killtime = Time.time + 0.25f;

			// Material is set to the exploded material
			GetComponent<Renderer>().sharedMaterial = materials[2];
		}
	}
}
