# ngl:cluster:foreign

__`description`__

A **ngl:cluster:foreign** is a cluster that contains only **ngl:foreign** descriptions.

__`examples`__

```ngl
// foreign_sfml.ngl (foreign cluster)
ngl:foreign:cluster sfml
{
    ngl:foreign<"init", some, params> init
    ngl:foreign<"cleanup", some, thing, to, give, as, params> cleanup
    ngl:foreign<"wait"> wait

    ngl:foreign<"custom", a, b, c> init
}

// program.ngl
ngl:cluster main

ngl:edge<ngl, main, ngl:cluster:foreign:sfml, nge:import>    // import in main cluster
ngl:edge<ngl, ngl, ngl:cluster:foreign:sfml, nge:import>     // import globally

ngl:foreign:cluster:sfml.init                                // call a foreign function
```