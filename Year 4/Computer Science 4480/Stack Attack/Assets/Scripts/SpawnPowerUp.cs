using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Timers;

public class SpawnPowerUp : MonoBehaviour
{

    public GameObject powerUpPrefab;        // The prefab of the power up to be spawned
    public float powerTimer;


    void Start()
    {
        powerTimer = 10f;
    }

    private void Update()
    {
        PowerTimer();
        if(powerTimer <= 0)
        {
            Vector2 spawn = Vector2.zero;
            spawn.y = 10;
            Instantiate(powerUpPrefab, spawn, Quaternion.identity);
            powerTimer = 10f;
        }
    }

    void PowerTimer()
    {
        powerTimer -= Time.deltaTime;

    }
}
