using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// This class simply prepares a list containing flock agents and their Transform data, which can be
// used to calculate what a given flock agent should do to maintain cohesion and avoidance in certain
// situations.
// E.g. if it should stay close to a nearby flock agent or temprorarily separate from it if an
// obstacle has suddenly appeared in the flock's path.
public abstract class ContextFilter : ScriptableObject
{
    public abstract List<Transform> Filter(FlockAgent agent, List<Transform> original);
}
