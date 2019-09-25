using UnityEngine;
using System.Collections;

/* 
 * CameraFollow class 
 * This class handles how the camera operates
 */
public class CameraFollow : MonoBehaviour
{

    public Transform target;
    public float lookSmooth = 0.09f;
    public Vector3 offset = new Vector3(0, 0, -2);
    public float xTilt = 10;
    Vector3 destination = Vector3.zero;
    PlayerMovement player;
    float rotateVel = 0;

    void Start()
    {
        setCameraTarget(target);
    }

    void setCameraTarget(Transform t)
    {
        target = t;
        if(target != null)
        {
            if (target.GetComponent<PlayerMovement>())
            {
                player = target.GetComponent<PlayerMovement>();
            }
        }
    }

    void Update()
    {
        MoveToTarget();
        LookAtTarget();
    }

    void MoveToTarget()
    {
        destination = player.TargetRotation * offset;
        destination += new Vector3(target.localPosition.x, target.localPosition.y + 1, target.localPosition.z);
        transform.position = destination;
    }

    void LookAtTarget()
    {
        float eulerY = Mathf.SmoothDampAngle(transform.eulerAngles.y, target.eulerAngles.y, ref rotateVel, lookSmooth);
        transform.rotation = Quaternion.Euler(transform.eulerAngles.x, eulerY, 0);
    }

    /*
    // Public variables
    public float turnSpeed = 4.0f;

    // Position that camera will be following
    public Transform target;

    // The speed at which the camera will be following
    public float smoothing = 5f;        
    public PlayerMovement player;

    // The initial offset from the target
    Vector3 offset;                     

    void Start()
    {
        // If the game is being played, then calculate the offset
        if (player.pause == false)
        {
            // Calculate the initial offset.
            offset = transform.position - target.position;
        }
    }

    void Update()
    {
        // If game is being played, then allow the rotation of the camera
        if (player.pause == false && player.start == false)
        {
            offset = Quaternion.AngleAxis(Input.GetAxis("Mouse X") * turnSpeed, Vector3.up) * offset;
            transform.position = target.position + offset;
            transform.LookAt(target.position);
        }
    }

    void LateUpdate ()
    {
        // If game is being played, then allow camera update
        if (player.pause == false && player.start == false)
        {
            // Create a postion the camera is aiming for based on the offset from the target.
            Vector3 targetCamPos = target.position + offset;
            // Smoothly interpolate between the camera's current position and it's target position.
            transform.position = Vector3.Lerp(transform.position, targetCamPos, smoothing * Time.deltaTime);
        }
    }*/
}