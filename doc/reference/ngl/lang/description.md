# ngl:lang:description

__`[description]`__

A description add semantic to an identifier

__`[edge]`__

- [scalar_description]
- [vector_description]

---------------------------------------

## scalar_description

__`[path]`__ ngl:lang:description:scalar_description

__`[syntax]`__

>_descriptor_identifier_ _described_identifier_

__`[example]`__

```
ngl:concept matrix
```
matrix is described as a ngl:concept which is a described_identifier

---------------------------------------

## vector_description

__`[syntax]`__

>_descriptor_identifier_ _described_identifier_
{
    _[description]_ `optional,list`
    identifier
    _edge_ `optional,list`
}

__`[example]`__

```
ngl:concept:container matrix
{
    ngl:concept:number rows
    ngl:concept:number columns
    ngl::concept:size // use size as described_identifier

    nge:context ngl:concept:math // use matrix as edge source
}
```

---------------------------------------

## redescription

__`[description]`__
Every described identifier can be redescripted

__`[example]`__

```
ngl:concept:container:matrix float_matrix
{
    ngl::float :ngl:concept:number // redescription of ngl:concept:number in float_matrix context
}
? // parametric redescription version
? ngl::matrix<ngl::float :ngl:concept:number> float_matrix;
```

---------------------------------------

---------------------------------------
[alias]: #alias
[ngl:data]: /doc/reference/ngl/data
[ngl:entity]: /doc/reference/ngl/entity

[description]: #description
[scalar_description]: #scalar_description
[vector_description]: #vector_description