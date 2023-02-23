using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// This script is used to allow flock agents to acknowledge the obstacles and characters on the map.
// Without this, the flock agents may:
// - Treat the "ground" as an obstacle and get stuck on it
// - Phase through objects that should have collision physics
// - Crash into obstacles as it attempts to traverse on or through the space occupied by it instead
//   of applying the Avoidance Behaviour
areas on the map occupied by a static object
[CreateAssetMenu(menuName = "Flock/Filter/Physics Layer")]
public class PhysicsLayerFilter : ContextFilter
{
    // Used to access the physics layers from the inspector - in this case it will access the Obstacles layer
    public LayerMask mask;

    public override List<Transform> Filter(FlockAgent agent, List<Transform> original)
    {
        List<Transform> filtered = new List<Transform>();
        foreach(Transform item in original)
        {

            // Checks if the layer of the game is the same as the one instantiated above
            if(mask == (mask | (1 << item.gameObject.layer)))
                filtered.Add(item);
        }

        return filtered;
    }
}
