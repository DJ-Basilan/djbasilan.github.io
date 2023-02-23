using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraFollow : MonoBehaviour
{
    // Instantiate Camera object
    private Camera myCamera;

    // Target to follow
    private Func<Vector3> GetCameraFollowPositionFunc;

    // Position of the target
    private Vector3 cameraFollowTargetPosition;


    // Constructor/Setup function to retrieve a target object
    public void Setup(Func<Vector3> GetCameraFollowPositionFunc)
    {
        this.GetCameraFollowPositionFunc = GetCameraFollowPositionFunc;
    }


    // Start is called on the first frame
    private void Start()
    {
        myCamera = transform.GetComponent<Camera>();
    }


    // Update is called once per frame
    void Update()
    {
        Vector3 cameraFollowTargetPosition = GetCameraFollowPositionFunc();
        cameraFollowTargetPosition.z = transform.position.z;      // Sets the Z-axis to be neutral, camera only needs to move along the X- and Y-axes

        // Move in the same direction as the player character
        Vector3 cameraMoveDir = (cameraFollowTargetPosition - transform.position).normalized;
        float distance = Vector3.Distance(cameraFollowTargetPosition, transform.position);
        float cameraMoveSpeed = 2.5f;

        // Keeps the camera aligned with the player character
        if (distance > 0)
        {
            // Calculate the current position of the camera needs
            Vector3 newCameraPosition = transform.position + cameraMoveDir * distance * cameraMoveSpeed * Time.deltaTime;

            // Calculate the distance between the camera's position and its target's position
            float distanceAfterMoving = Vector3.Distance(newCameraPosition, cameraFollowPosition);

            // Overwrites the current camera positon with the follow target's position if the former has overshot it
            // This is necessary because the camera is designed to follow slightly behind its target, not track it dead centre
            if (distanceAfterMoving > distance)
            {
                newCameraPosition = cameraFollowPosition;
            }

            transform.position = newCameraPosition;
        }
    }
}
