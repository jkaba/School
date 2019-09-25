using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveCube : MonoBehaviour {

    public float moveSpeed;
    public float rotationSpeed;
    public float jumpHeight;

	// Update is called once per frame
	void Update () {
        if (Input.GetKey(KeyCode.RightArrow))
        {
            //transform.Translate(moveSpeed*Time.deltaTime, 0f, 0f, Space.World);
            GetComponent<Rigidbody>().velocity = new Vector3(moveSpeed, GetComponent<Rigidbody>().velocity.y, GetComponent<Rigidbody>().velocity.z);
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            //transform.Translate(-1*moveSpeed*Time.deltaTime, 0f, 0f, Space.World);
            GetComponent<Rigidbody>().velocity = new Vector3(-1*moveSpeed, GetComponent<Rigidbody>().velocity.y, GetComponent<Rigidbody>().velocity.z);
        }
        if (Input.GetKey(KeyCode.UpArrow))
        {
            //transform.Translate(0f, 0f, moveSpeed*Time.deltaTime, Space.World);
            GetComponent<Rigidbody>().velocity = new Vector3(GetComponent<Rigidbody>().velocity.x, GetComponent<Rigidbody>().velocity.y, moveSpeed);
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            //transform.Translate(0f, 0f, -1*moveSpeed*Time.deltaTime, Space.World);
            GetComponent<Rigidbody>().velocity = new Vector3(GetComponent<Rigidbody>().velocity.x, GetComponent<Rigidbody>().velocity.y, -1*moveSpeed);
        }
        if (Input.GetKey(KeyCode.PageUp))
        {
            transform.RotateAround(transform.position, new Vector3(0f, 1f, 0f), rotationSpeed*Time.deltaTime);
        }
        if (Input.GetKey(KeyCode.PageDown))
        {
            transform.RotateAround(transform.position, new Vector3(0f, 1f, 0f), -1*rotationSpeed*Time.deltaTime);
        }
        if (Input.GetKeyDown(KeyCode.Space))
        {
            //StartCoroutine(JumpCo(20f));
            GetComponent<Rigidbody>().velocity = new Vector3(GetComponent<Rigidbody>().velocity.x, jumpHeight, GetComponent<Rigidbody>().velocity.z);
        }
    }



    IEnumerator JumpCo(float speed)
    {
        
        while (speed > 0)
        {
            transform.Translate(Vector3.up * speed * Time.deltaTime, Space.World);
            speed -= (9.81f / 5);
            yield return null;
        } 
    }
}
