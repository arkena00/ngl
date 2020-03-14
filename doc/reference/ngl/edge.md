# ngl:edge

__`[description]`__

An edge is a link between two ngl:data

__`[shape]`__
> : edge
:: auto edge
:<edge_name>: parametric edge
. edge of type has

edge types
- is
- has
- write : modify the ngl:data respecting the rules
- read : access the ngl:data


ngc page
{
    ngc:string name // edge<has, page, name>
}


source:target // logical edge
source::target // logical autoedge
source:<is>:target // parametric autoedge
source:<is>target // parametric edge

source:<is>:target

__`[concrete]`__
```
ngl edge
{
    ngl:entity <origin>
    ngl:data <source>
    ngl:data <target>
    ngl:edge <edge_type>
}

ngl:edge<ngl, my_int, literal_3, write>
ngc:int my_int = "quatre"
ngl:concrete<my_int, 
ng:int z
```

ngl:entity_constant<ngl, 4> my_int

ngl:cluster ads_cluster
{
    .entity = ngl:entity:ads
    my_int = 5 // error
}
my_int = 7 // ok

__`[example]`__



ngl:concept page
{
    nge<is>
}

A-<has>-B-<is>-C-<edge1 && edge2>-D