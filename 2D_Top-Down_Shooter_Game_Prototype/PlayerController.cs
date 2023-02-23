using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    // Instantiated variables
    public float moveSpeed = 3f;
    public Rigidbody2D rb;

    // Used for controlling the movement and aiming
    Vector2 movement;
    Vector2 mousePos;

    public Camera cam;


    // Update is called once per frame
    void Update()
    {
        // Code for moving the player character
        movement.x = Input.GetAxisRaw("Horizontal");
        movement.y = Input.GetAxisRaw("Vertical");

        mousePos = cam.ScreenToWorldPoint(Input.mousePosition);
    }


    private void FixedUpdate()
    {

        rb.MovePosition(rb.position + movement * moveSpeed * Time.fixedDeltaTime);

        // Makes the player character face in the direction of the mouse cursor
        Vector2 lookDir = mousePos - rb.position;
        float angle = Mathf.Atan2(lookDir.y, lookDir.x) * Mathf.Rad2Deg;
        rb.rotation = angle;
    }
}
