using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameHandler : MonoBehaviour
{
    public Transform playerTransform;

    [SerializeField] private CameraFollow cameraFollow;


    // Start is called before the first frame update
    private void Start()
    {
        // Sets the player character object as the target for the cameraFollow script
        cameraFollow.Setup(() => playerTransform.position);
    }

}
