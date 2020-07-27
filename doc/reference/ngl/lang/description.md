# ngl:lang:description

__`[description]`__

A description add semantic to an identifier

__`[edge]`__

- [scalar_description]
- [vector_description]

---------------------------------------

## scalar_description

__`[shape]`__

>_ngs:identifier_ _ngs:raw_identifier_

__`[shape_alternative]`__
>_path_identifier_

>_path_identifier_ <>

__`[example]`__

```
ngl:concept matrix
```
matrix is described as a ngl:concept which is a described_identifier

```
ngl:concept matrix
{
    ngl:concept:size
    // equivalent to
    // ngl:concept:size size
}
```
matrix is described as a ngl:concept which is a described_identifier

---------------------------------------

## vector_description

__`[shape]`__

>_ngs:identifier_ _ngs:raw_identifier_
{
    `ngc:optional<ngc:many<` _[ngs:description]_ `>>`
    _ngs:identifier_
}

__`[example]`__

```
ngl:concept:container matrix
{
    ngl:concept:number rows
    ngl:concept:number columns
    ngl:concept:size // use size as described_identifier
}
```

---------------------------------------

## redescription

__`[description]`__
Every described identifier can be re-described

__`[example]`__

```
ngl:concept:container matrix
{
    ngl:concept:number rows
    ngl:concept:number columns
    ngl:concept:size (rows * columns) // use size as described_identifier
    ngl:concept type
}

ngl:concept:container:matrix float_matrix
{
    ngl:concept:natural_number .rows // 1
    <ngl:concept> .type // 2
}
```
1. Redescription of matrix.rows as ngl:concept:natural_number
2. Redescription of matrix.type as a parameterized ngl:concept descriptor 

---------------------------------------

---------------------------------------
[alias]: #alias
[ngl:data]: /doc/reference/ngl/data
[ngl:entity]: /doc/reference/ngl/entity

[ngs:description]: #description
[scalar_description]: #scalar_description
[vector_description]: #vector_description