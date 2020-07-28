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



//




cluster A
ngc movie
{
    ngc:string name
    ngc:string director_name
}


cluster B
ngc movie
{
    ngc:string title
    ngc:name date

    fn display()
}

ngc:movie
{
    display() {}
}

fiability
quality
version 1 2 3 4


//
cluster main

ngc movie
{
    ngc:string title
    ngc:string director
}

ngc:movie movie;
std::cout << movie.name;

ngl:concept_shape<movie_A>
!=
ngl:concept_shape<movie_B>

nglc -import cluster_main concepts
> clusterA found
