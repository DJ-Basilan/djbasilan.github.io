using System.Collections;
using System.Collections.Generic;
using UnityEngine;


// All behaviours will inherit from this abstract class and only this class will inherit from FlockBehaviour
public abstract class FilteredFlockBehaviour : FlockBehaviour
{
    // Instantiates a Context Filter object
    public ContextFilter filter;
    
}
