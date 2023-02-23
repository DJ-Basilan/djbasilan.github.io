using System.Collections;
using System.Collections.Generic;
using UnityEngine;


// This behaviour could be seen as the Reversal behaviour as it forces agents that stray to far to move closer
// to their original position relative to the flock.
[CreateAssetMenu(menuName = "Flock/Behaviour/Stay In Radius")]
public class StayInRadiusBehaviour : FlockBehaviour
{
    // Declare the variables unique to this behaviour
    public Vector2 centre;
    public float radius = 15;

    public override Vector2 CalculateMove(FlockAgent agent, List<Transform> context, Flock flock)
    {

        // Calculate the centre offset
        Vector2 centreOffset = centre - (Vector2)agent.transform.position;

        // Creates a value for the centre offset of the flock
        float t = centreOffset.magnitude / radius;

        // Checks the distance between the agent within the radius of its origin point
        if(t < 0.9f)
        {
            // If it is less than 90% away from the radius, carry on
            return Vector2.zero;
        }

        // Otherwise the agent will move back or closer to within the radius
        return centreOffset * t * t;
    }
}
