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


ngl:concept:io write
{

}

ngl:concrete<ngl, ngl:shape:assignment, ngl:concept:assign>

//
ngl:lang:parameterised_scalar_description
{
    <ngs:identifier>
    <ngs:identifier>
    <ngs:parameterised_identifier> = "generalise"
}

A:D
A::D
A:<is>D
A::<is>D

A:<nge:any>D

ngc:animal <> cat
ngc:animal <generalise> dog

? namespace, contenance, héritage

ngc:machin ads:bidule

ngc:truc <has> bidule
{

}


ngc:animal <- (dog, cat, truc)

ngc:animal:dog
{

}


ngc:animal:cat
ngc:animal:<

ngl:concept ads:animal
{
    poils
}
animal:poils

ngl:concept:animal cat
{
    john-<friend_with>-jack
    john--B
}