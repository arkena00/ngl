# ngl:lang:execution:loop

```

// description
ngl:concept loop
{
    <ngl:data> data
    ngl:execution <execution>
}

// redescription
ngl:concept:loop<ngc:math:number>
{
    .execution ngl:instruction
}

ngl:concept:loop<ngl:concrete:container>
{
    .execution ngl:loop<container.size>
    i
    .element container[i]
}


ngl:loop<array>
{
    ngl:print<.element>
}

ngl:loop< (condition) >
{}

ngl:loop<ngl:infinite>
{}

```