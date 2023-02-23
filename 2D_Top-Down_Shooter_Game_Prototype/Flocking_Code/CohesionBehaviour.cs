using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Maintains a set distance between a flock agent and its neighbours so that few to no collisions occur within
// the flock as it roams the map.
[CreateAssetMenu(menuName = "Flock/Behaviour/Cohesion")]
public class CohesionBehaviour : FilteredFlockBehaviour
{

    public override Vector2 CalculateMove(FlockAgent agent, List<Transform> context, Flock flock)
    {
        
        // If no neighbours, return no adjustments
        if (context.Count == 0)
            return Vector2.zero;
        

        // Find the average position of the neighbouring agents
        Vector2 cohesionMove = Vector2.zero;

        // Used to integrate the filter objects and behaviours into the Flocking behaviour
        List<Transform> filteredContext = (filter == null) ? context : filter.Filter(agent, context);

        foreach (Transform item in filteredContext)
        {
            cohesionMove += (Vector2)item.position;
        }

        cohesionMove /= context.Count;

        // Create offset from agent's position
        cohesionMove -= (Vector2)agent.transform.position;

        return cohesionMove;
    }
}
