# ngl:cluster:concept

__`description`__

A **ngl:cluster:concept** is external source code that will be part of the ngl entity.

__`examples`__

```ngl
// movie.ngl (external source file)
ngl:concept movie
{
    <ngl::name>
    <ngl::realisator>
    <ngl::date>
}


// project.ngl (personal)
ngl:ecosystem project
{
    ...
    ngl:cluster:concept                         // define all the concept clusters used by your ngl entity
    {
        ngl:file ncc/media.ngl                  // include a simple file
        ngl:folder ncc/algorithm/               // include an entire folder
        ngl:cluster_server ngl://algorithm/     // include from a distant server
    }
}

// program.ngl (personal)
ngl:cluster main

// use directly imported concepts
ngl:concept:movie movie<name: "Jean Neige - Le Retour", realisator: "Jack Daniel", date: 1998>

```