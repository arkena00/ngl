```

ngc container
{
    ngc:element
    ngc:size capacity: 4
}

ngc:container:capacity<x>
ngc:container{ capacity: ngc:size<x> }

ngc many
{
    nga.domain: ngd.theory
    nge: computer
    
    element: ?x
    
    ngl.require.algorithm
    {
        // nge native algorithm
        for (auto ?x : v) {}
    }
}

ngc many
{
    nge:has ngx:theory
    ?x element
}

ngc type
{
    type: ?
}

ngc container
{
    value_type: ngc::type

    ngl.compose
    {
        ngc::many<x: value_type>
    }
}

ng array
{
    import ngc.container;
    nga.storage: nge.memory.heap;
    size: ngc::integer
}

ng.array<ng.int, 20>

ng vector
{
    import ngc.container;
}
ng.vector<ng.int>
```