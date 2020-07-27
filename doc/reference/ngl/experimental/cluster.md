# ngl:cluster

__`[description]`__

A cluster is used to regroup ngl:data

__`[example]`__

```
// file1.ngl
ngl:cluster main
{
    .export = false
    ngl:alias<ngl:concept> ngc
}


// file2.ngl
ngl:cluster main

ngl:alias<ngl::integer> int

.export = false
ngl:alias<ngl::double> dbl

// file3.ngl
ngl:cluster zeta
ngl:edge<ngl:cluster:main, ngl:cluster:zeta> // ngl:cluster:import<main>

//
ngc test
int z
dbl d // error
```