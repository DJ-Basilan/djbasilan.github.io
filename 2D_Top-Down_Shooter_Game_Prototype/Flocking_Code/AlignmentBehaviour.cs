using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// Aligns the flock agent to face the same direction as the heading of the flock
[CreateAssetMenu(menuName = "Flock/Behaviour/Alignment")]
public class AlignmentBehaviour : FlockBehaviour
{

    public override Vector2 CalculateMove(FlockAgent agent, List<Transform> context, Flock flock)
    {
        // If no neighbours, maintain current alignment
        if (context.Count == 0)
            return agent.transform.up;

        // Used to store the actual alignment
        Vector2 alignmentMove = Vector2.zero;


        // Find the average alignment of the neighbouring agents
        foreach (Transform item in context)
        {
            alignmentMove += (Vector2)item.transform.up;
        }

        alignmentMove /= context.Count;

        return alignmentMove;
    }
}
