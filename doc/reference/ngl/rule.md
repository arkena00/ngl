# ngl:rule

```
ngl:rule no_zero
{
    ngc:number <value>
    ngl:rule (value != 0)
}
ngl:function divide
{
    ngc:int <x>
    ngc:int <y>
    
    ngl:rule:no_zero<y>

    .result (x / y)
}
```

```
ngl constant
{
    <ngl:data>
    ngl:rule
    {
        ! ngl:edge // refuse all edges
        ngl:edge:read // allow read edge
    }
}

ngl:constant<4> my_int
my_int = 3 // ngl add the edge write from my_int to literal_3
           // ngl:edge<ngl, my_int, literal_3, write>
           // broken rule
an_int = my_int // ngl add the edge read from an_int to my_int
                // ngl:edge<ngl, an_int, my_int, read>
                // ok


ngl:rule // create a rule for the current context (file)
{
    (boolean_expression)
}

ngl:function divide
{
    ngl:int <x>
    ngl:int <y>
    
    ngl:rule
    {
        y != 0
        divide.result != ngl:infinite
        .allow { ngl::parameterization<[x, y]> }
        .deny { ngl::redescription<x> }
    }

    .result (x / y)
}

    ngl:rule no_zero
    {
        .require <value> != 0
    }

ngl:rule<divide, no_zero<divide.y>>
ngl:rule<divide, no_zero<divide.y>, positive<[divide.x, divide.y]>>

```

