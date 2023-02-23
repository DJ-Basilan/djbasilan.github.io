using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// When it has encountered an obstacle, the flock agent will avoid it by temporarily separating from its group or
// moving in the same direction as a nearby flock member and breaking the relative distancing between them to
// compensate for maintaining a set distance between itself and the obstacle.
[CreateAssetMenu(menuName = "Flock/Behaviour/Avoidance")]
public class AvoidanceBehaviour : FilteredFlockBehaviour
{

    public override Vector2 CalculateMove(FlockAgent agent, List<Transform> context, Flock flock)
    {

        // If no neighbours, return no adjustments
        if (context.Count == 0)
            return Vector2.zero;


        // Find the average position of the neighbouring agents
        Vector2 avoidanceMove = Vector2.zero;

        int nAvoid = 0;

        // Used to integrate the filter objects and behaviours into the Flocking behaviour
        List<Transform> filteredContext = (filter == null) ? context : filter.Filter(agent, context);

        foreach (Transform item in filteredContext)
        {
            if(Vector2.SqrMagnitude(item.position - agent.transform.position) < flock.SquareAvoidanceRadius)
            {
                nAvoid++;
                avoidanceMove += (Vector2)(agent.transform.position - item.position); // Calculates the offset position for avoidance
            }
            
        }

        // Finds the average
        if (nAvoid > 0)
            avoidanceMove /= nAvoid;

        return avoidanceMove;
    }
}
