# ngl:cluster:entity

__`description`__

A **ngl:cluster:entity** describe an entity who can only be used by other entities. It cannot exist alone in the ngl:environment.

__`examples`__

```ngl
// beta.ngl (external source)
ngl:cluster main

ngl:cluster:entity beta
{
    ngl:concept public_concept      // Here public_concept is in the beta
    {                               //   entity cluster, it is public.
        // ...                      //
    }                               //
}

ngl:concept movie                   // Here movie is in the main cluster of
{                                   //   the external sources, it is private to the
    ngc::string <name>              //   library's entity.
    ngc::string <author>            //
    ngc::int <release_date>         //
}                                   //

// Export private concept via the ngl entity to the entity:cluster beta
ngl:edge<ngl, ngl::movie, ngl:entity:cluster:beta, nge::export>


// program.ngl (personal, uses entity clusters)
ngl:cluster main

ngl:edge<ngl, main, ngl:entity:cluster:beta, nge:import>    // import in main cluster
ngl:edge<ads, ngl, ngl:entity:cluster:beta, nge:import>     // import globally

```