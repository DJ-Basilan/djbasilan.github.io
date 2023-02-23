using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Due to the conditions of the Cohesion and Avoidance behaviour scripts, flock agents constantly adjust themselves 
// slightly in order to maintain their relative positions and compensate for the flock's random movement and headings.
// This caused their sprites to become "janky" as they would often rotate sharply and rapidly in various directions
// as they try to maintain their uniformed distancing and alignment.

// This script helps to make the steering/rotation of flock agents more smooth so that it is not affected greatly by
// the adjustments caused by cohesion and avoidance.
[CreateAssetMenu(menuName = "Flock/Behaviour/SteeredCohesion")]
public class SteeredCohesionBehaviour : FlockBehaviour
{

    Vector2 currentVelocity;
    public float agentSmoothTime = 0.5f;


    public override Vector2 CalculateMove(FlockAgent agent, List<Transform> context, Flock flock)
    {

        // If no neighbours, return no adjustments
        if (context.Count == 0)
            return Vector2.zero;

        Vector2 cohesionMove = Vector2.zero;

        // Find the average position of the neighbouring agents
        foreach (Transform item in context)
        {
            cohesionMove += (Vector2)item.position;
        }

        cohesionMove /= context.Count;

        // Create offset from agent's position
        cohesionMove -= (Vector2)agent.transform.position;

        cohesionMove = Vector2.SmoothDamp(agent.transform.up, cohesionMove, ref currentVelocity, agentSmoothTime);

        return cohesionMove;
    }
}
