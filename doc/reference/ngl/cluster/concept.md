# ngl:cluster:concept

__`description`__

A **ngl:cluster:concept** is external source code that will be part of the ngl entity.

*To create a concept cluster, you don't have to define a cluster inside the source file.*

__`example`__

*Project architecture*

```bash
$ tree
ngl-project
    ncc
        media.ngl
        algorithm
            ...
        
    program.ngl
    project.ngl
```

*Example using concept clusters*

```ngl
// ncc/media.ngl (external source file)
ngl:concept movie
{
    <ngl::name>                                 // define a ngl::name value, named name 
    <ngl::realisator>                           //          ngl::realisator value, named realisator
    <ngl::date>                                 //          ngl::date value, named date
}


// project.ngl (personal)
ngl:ecosystem project
{
    ...
    ngl:cluster:concept                         // define all the concept clusters used by your ngl entity
    {
        ngl:file ncc/media.ngl                  // include a simple source file
        ngl:folder ncc/algorithm/               // include an entire folder
        ngl:cluster_server ngl://algorithm/     // include from a distant server
    }
}

// program.ngl (personal)
ngl:cluster main

// use directly imported concepts
ngl:concept:movie<name: "Jean Neige - Le Retour", realisator: "Jack Daniel", date: 1998> awesome_movie
```

## Use

__`[description]`__

**ngl:cluster:use** is used to specify a cluster or a concept when conflits occured between two concepts inside differents clusters.

__`[edge]`__

- [ngl:cluster:use](../cluster.md#Use)

__`[example]`__

```sh
$ tree
external-sources/
    ncc/
        programing.ngl
        math.ngl
        math/
            sin.ngl
    ncc_alternative/
        math.ngl

# project that uses external sources
project/
    project.ngl
    program.ngl
```

**ncc**

*ncc/programming.ngl*
```ngl
ngl:cluster programming
ngc integer {}
```

*ncc/math.ngl*
```ngl
ngl:cluster math
ngc integer {}
```

*ncc/math/sin.ngl*
```ngl
ngl:cluster math
ngc sin {}
```

**ncc_alternative**

*ncc_alternative/math.ngl*
```ngl
ngl:cluster math
ngc integer {}
```

**project**
*project/program.ngl*
```ngl
ngc:programming:integer

// duplicated concept clusters, need an explicit use in ngl:cluster:concept via the source code or ngl:ecosystem
ngc:math:integer

// source code
ngl:cluster:concept
{           
    ngl:cluster:use<math, [ncc_alternative/]> // use ncc_alternative cluster
    ngl:cluster:use<math:integer, [ncc_alternative/]> // use ncc_alternative concept
}
```

*project.ngl*
```ngl
ngl:ecosystem project
{
    ngl:cluster:concept
    {           
        ngl:cluster:use<math, [ncc_alternative/]>
    }
}
```