using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    public Transform target;

    float bias = 0.9f;

    private void Update()
    {
        if (target != null)
        {
            float x = bias * transform.position.x + (1f - bias) * target.position.x;
            float y = bias * transform.position.y + (1f - bias) * target.position.y;

            transform.position = new Vector3(x, y, transform.position.z);
        }
    }

}