# ngl:rule

```
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
        .require y != 0
        .expect divide.result != ngl:infinite
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

