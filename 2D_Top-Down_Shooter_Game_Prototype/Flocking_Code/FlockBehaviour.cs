using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// This script acts as a template for the three flocking behaviours scripts
public abstract class FlockBehaviour : ScriptableObject
{
    public abstract Vector2 CalculateMove(FlockAgent agent, List<Transform> context, Flock flock);
}
