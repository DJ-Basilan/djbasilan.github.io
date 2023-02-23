using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Pathfinding;


public class EnemyAI : MonoBehaviour
{

    // Instantiating Variables
    private enum State
    {
        Patrolling,
        ChaseTarget,
    }

    private State state;

    // Timers
    private float waitTime;             // Time before moving on to the next waypoint
    public float startWaitTime;         // Used to reset the wait timer
    private float chaseTimer = 3.5f;    // Time before NPC gives up chasing

    private Transform target;
    public Transform playerChar;
    public Transform[] patrolPoints;
    private int index;

    private float speed;
    public float nextWaypointDistance = 1.5f;

    Path path;
    int currentWaypoint = 0;
    bool reachedEndOfPath = false;

    Seeker seeker;      // Pathfinding
    Rigidbody2D rb;     // Allows movement and collision


    // When the NPC is active...
    private void Awake()
    {
        seeker = GetComponent<Seeker>();
        rb = GetComponent<Rigidbody2D>();
        state = State.Patrolling;
    }


    // Start is called before the first frame update
    private void Start()
    {
        waitTime = startWaitTime;
        index = 0;
        speed = 180f;

        target = patrolPoints[index];
        InvokeRepeating("UpdatePath", 0f, 0.5f); // Invokes UpdatePath every 0.5 seconds. Useful for when the target is moving.
        
    }


    // Creates and updates the path between the current positions of the NPC and its target.
    private void UpdatePath()
    {
        if (seeker.IsDone())
        seeker.StartPath(rb.position, target.position, OnPathComplete);
    }


    // Required for the UpdatePath method.
    // Checks if the previous path had no errors.
    // Resets the path and the current waypoint for the next path update.
    private void OnPathComplete(Path p)
    {
        if(!p.error)
        {
            path = p;
            currentWaypoint = 0;
        }
    }


    // Fixed Update is only called a certain number frames per second
    private void FixedUpdate()
    {
        // Checks if a path exists
        if (path == null)
            return;

        // Implementation of the Finite State Machine (FSM)
        switch (state)
        {
            default:
            case State.Patrolling: // ***PATROLLING STATE***

                // Checks if the NPC has reached its destination - which in this case would be one of the patrol points
                if (currentWaypoint >= path.vectorPath.Count)
                {
                    reachedEndOfPath = true;

                    // NPC will wait for a certain amount of time before moving on to the next patrol point
                    if (waitTime <= 0)
                    {
                        index++;
                        waitTime = startWaitTime;
                    }
                    else
                    {
                        waitTime -= Time.deltaTime;
                    }

                    return;
                } // if (currentWaypoint >= path.vectorPath.Count)
                else
                {
                    reachedEndOfPath = false;
                }

                // Resets the patrol array when the NPC reaches the final patrol point. Allows for a smooth patrol loop
                if (index == patrolPoints.Length)
                    index = 0;

                target = patrolPoints[index]; // Overwrites the target to the current patrol point

                // Used to add force to the NPC
                Vector2 pDirection = ((Vector2)path.vectorPath[currentWaypoint] - rb.position).normalized;
                Vector2 pForce = pDirection * speed * Time.deltaTime;

                // Used for calculating distance
                float pDistance = Vector2.Distance(rb.position, path.vectorPath[currentWaypoint]);

                // Used to calculate the parameters needed to allow the NPC to face its target
                Vector2 pLookDir = (Vector2)target.position - rb.position;
                float pAngle = Mathf.Atan2(pLookDir.y, pLookDir.x) * Mathf.Rad2Deg - 90f;

                rb.AddForce(pForce); // Gives the NPC movement

                rb.rotation = pAngle; // Makes the NPC face its target while moving

                if (pDistance < nextWaypointDistance)
                {
                    currentWaypoint++;
                }

                // Uses this method to check for the player character - Go to Line 222
                FindTarget();
                break;


            case State.ChaseTarget: // ***CHASE TARGET STATE***

                //*** Many lines of code have been duplicated from the Patrollin State to mitigate a constant "ArgumentOutOfRange" error with the 'index' parameter.***
                //*** For some unknown reason, the error occurs if any of the code below are declared before the entire State change code.***

                // Checks if a path exists
                if (path == null)
                    return;

                // Checks if the NPC has reached the target
                if (currentWaypoint >= path.vectorPath.Count)
                {
                    reachedEndOfPath = true;
                    return;
                }
                else
                {
                    reachedEndOfPath = false;
                }

                // Used to add force to the NPC
                Vector2 direction = ((Vector2)path.vectorPath[currentWaypoint] - rb.position).normalized;
                Vector2 force = direction * speed * Time.deltaTime;

                // Used for calculating distance
                float distance = Vector2.Distance(rb.position, path.vectorPath[currentWaypoint]);

                // Used to calculate the parameters needed to allow the NPC to face its target
                Vector2 lookDir = (Vector2)target.position - rb.position;
                float angle = Mathf.Atan2(lookDir.y, lookDir.x) * Mathf.Rad2Deg - 90f;

                rb.AddForce(force); // Gives the NPC movement

                rb.rotation = angle; // Makes the NPC face its target

                // When the NPC has reached the waypoint, change target to next waypoint
                if (distance < nextWaypointDistance)
                {
                    currentWaypoint++;
                }

                float outOfRange = 11f;

                // Checks if the player character is too far
                if (Vector2.Distance(rb.position, target.position) > outOfRange)
                {

                    // Stops and waits for 3 secs and then returns to the Patrolling State
                    if (chaseTimer <= 0)
                    {

                        // Reverts speed back to normal and reapplies movement
                        speed = 180f;
                        rb.AddForce(force);

                        // Resets the Chase Timer and changes the state accordingly
                        chaseTimer = 3.5f;
                        state = State.Patrolling;
                    }
                    else
                    {
                        rb.Sleep(); // Stops the movement
                        chaseTimer -= Time.deltaTime; // Counting down
                    }
                    
                } // if (Vector2.Distance(rb.position, target.position) > outOfRange)

                break;
        } // switch(state)
    } // FixedUpdate()


    // This method is called when the Player Character is within the NPC's vicinity.
    private void FindTarget()
    {
        float targetRange = 7f;

        if(Vector2.Distance(rb.position, playerChar.position) < targetRange)
        {
            // Changes the target to the Player Character and increases the movement speed
            target = playerChar;
            speed = 330f;

            // Changes to the Chasing State
            state = State.ChaseTarget;
        }
    } // FindTarget()

}
