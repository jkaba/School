using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformMover : MonoBehaviour {

    public static float enemyMoveDir = 1;
    public static float enemyMoveSpeed = 2;
    public float changeInterval = 1F;
    private Transform mTransform;
    private Vector3 calc;

    // Material variables
    public int enemyType;

    // Parameter variables
    private int playerType;

    void Start()
    {
        mTransform = transform;
    }

    void Update()
    {
        if (enemyType == 0)
        {
            calc = new Vector3(0, 0.05f, 0);
            mTransform.Translate(calc);
            if (this.transform.position.y > 7)
            {
                enemyType = 1;
            }
        }
        else if (enemyType == 1)
        {
            // Calculate movement
            calc = new Vector3(0, -0.05f, 0);
            mTransform.Translate(calc);

            if (this.transform.position.y < -3)
            {
                enemyType = 0;
            }

        }
        else if(enemyType == 2)
        {
            calc = new Vector3(0, 0.025f, 0);
            mTransform.Translate(calc);

            if (this.transform.position.y > 12)
            {
                enemyType = 3;
            }
        }
        else if(enemyType == 3)
        {
            calc = new Vector3(0, -0.025f, 0);
            mTransform.Translate(calc);

            if (this.transform.position.y < 5)
            {
                enemyType = 2;
            }
        }
    }
}
