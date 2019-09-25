using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PlayerMovement : MonoBehaviour
{
    // Lot's of public variables

    public float inputDelay = 0.1f;
    public float forwardVel = 12;
    public float rotateVel = 100;
    Quaternion targetRotation;
    Rigidbody playerRigidbody;
    float forwardInput;
    float turnInput;

    // Movement Variables
    public float speed = 6f;
    Vector3 movement;
    Animator anim;
    int floorMask;
    float camRayLength = 100f;

    // Maze Variables
    public int keyCount = 0;
    public Text keyText;
    public GameObject Door1;
    public GameObject Door2;
    public GameObject Door3;
    public GameObject Door4;
    public GameObject End;

    // End, Pause, And Starting variables
    public bool gameOver;
    public bool pause;
    public bool start;

    // Variables related to LeaderBoard and Scoring
    public Text finalScoreText;
    public float finalScore;
    public string userName;
    public GameManager gm;

    public Quaternion TargetRotation
    {
        get { return targetRotation;  }
    }

    void Awake()
    {
        targetRotation = transform.rotation;
        forwardInput = turnInput = 0;

        // Initial set up
        floorMask = LayerMask.GetMask("Floor");
        anim = GetComponent<Animator>();
        playerRigidbody = GetComponent<Rigidbody>();

        // gameOver and Pause are both false to start
        gameOver = false;
        pause = false;

        // Start set to true to bring up nameEntry screen
        start = true;
    }

    void GetInput()
    {
        forwardInput = Input.GetAxis("Vertical");
        turnInput = Input.GetAxis("Horizontal");
    }

    void Update()
    {
        // If the game is not over, or paused, or at nameEntry
        if (gameOver == false && pause == false && start == false)
        {
            GetInput();
            Turning();
            Animating(turnInput, forwardInput);

            /*
            // Move character
            float h = Input.GetAxisRaw("Horizontal");
            float v = Input.GetAxisRaw("Vertical");

            Move(h, v);
            Turning();
            Animating(h, v);*/

           
        }
       
    }

    void FixedUpdate()
    {
        Move(turnInput, forwardInput);
    }



    void Move(float h, float v)
    {
        // If the game is running then allow movement
        //if (pause == false && gameOver == false)
        //{
            /*if(Mathf.Abs(forwardInput) > inputDelay)
            {
                //move
                playerRigidbody.velocity = transform.forward * forwardInput * forwardVel;
                playerRigidbody.MovePosition(transform.position  playerRigidbody.velocity);
            }
            else
            {
                //zero velocity
                playerRigidbody.velocity = Vector3.zero;
            }*/

            movement.Set(h, 0f, v);
            movement = movement.normalized * speed * Time.deltaTime;
            if (Input.GetKey(KeyCode.UpArrow) == true)
            {
                moveForward(6f);
            }
            if (Input.GetKey(KeyCode.DownArrow) == true)
            {
                moveBack(6f);
            }
            //if (Input.GetKey(KeyCode.RightArrow) == true)
            //{
            //    moveRight(6f);
            //}
            //if (Input.GetKey(KeyCode.LeftArrow) == true)
            //{
            //    moveLeft(6f);
            //}

            playerRigidbody.MovePosition(transform.localPosition);
            

        //}
    }

    private void moveForward(float speed)
    {
        transform.localPosition += transform.forward * speed * Time.deltaTime;
    }

    private void moveBack(float speed)
    {
        transform.localPosition -= transform.forward * speed * Time.deltaTime;
    }

    private void moveRight(float speed)
    {
        transform.localPosition += transform.right * speed * Time.deltaTime;
    }

    private void moveLeft(float speed)
    {
        transform.localPosition -= transform.right * speed * Time.deltaTime;
    }

    void Turning()
    {
        if (Mathf.Abs(turnInput) > inputDelay)
        {
            targetRotation *= Quaternion.AngleAxis(rotateVel * turnInput * Time.deltaTime, Vector3.up);
        }
        transform.rotation = targetRotation;

        /*Ray camRay = Camera.main.ScreenPointToRay (Input.mousePosition);
		RaycastHit floorHit;
		if (Physics.Raycast (camRay, out floorHit, camRayLength, floorMask)) {
			Vector3 playerToMouse = floorHit.point - transform.position;
			playerToMouse.y = 0f;
			Quaternion newRotation = Quaternion.LookRotation (playerToMouse);
			playerRigidbody.MoveRotation (newRotation);
		}*/

    }

    // Animating method, set character animation if char is moving
    void Animating(float h, float v)
    {
        bool walking = h != 0f || v != 0f;
        anim.SetBool("IsWalking", walking);
    }
    
    /*
     * OnTriggerEnter method
     * This method runs when a collision occurs
     * This handles the Maze variables
     */
    private void OnTriggerEnter(Collider collision)
    {
        // If the player collides with a key
        if (collision.gameObject.CompareTag("Key"))
        {
            // Set the key to false, increment key count, update key text
            collision.gameObject.SetActive(false);
            keyCount += 1;
            keyText.text = "Keys Found: " + keyCount.ToString();

            // If collision is with key 1, then open door 1
            if(collision.gameObject.name == "Key1")
            {
                Door1.gameObject.SetActive(false); 
            }

            // If collision is with key 2, then open door 2
            if(collision.gameObject.name == "Key2")
            {
                Door2.gameObject.SetActive(false);
            }

            // If collision is with key 3, then open door 3
            if(collision.gameObject.name == "Key3")
            {
                Door3.gameObject.SetActive(false);
            }

            // If collision is with key 4, then open door 4
            if(collision.gameObject.name == "Key4")
            {
                Destroy(Door4);
            }
        }

        // If collision is with the end panel
        else if(collision.gameObject.CompareTag("Finish"))
        {
            // Set gameOver to true as end was reached 
            gameOver = true;

            // Get the final score (time remaining in seconds)
            finalScore = (int)gm.getTime();

            // Update final score text
            finalScoreText.text = "Final Score: " + finalScore;
        } 
    }
}
