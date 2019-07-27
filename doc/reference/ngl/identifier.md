# ngl:identifier

__`[description]`__

An identifier is a unique [ngl:data] created by a [ngl:entity] used to describe another [ngl:data].

__`[edge]`__

- [raw_identifier](#raw_identifier)
- identifier_path
- identifier_autopath
- descriptor_identifier
- described_identifier

---------------------------------------

## raw_identifier

__`[path]`__ [ngl:identifier:description:scalar_description](#scalar_description)

__`[rule]`__
- must match a-z

---------------------------------------

## [alias]

__`[path]`__ [ngl:alias]

__`[example]`__

```
? ngl:edge<alias> ngl:concept ngc
ngl:alias<ngl:concept> ngc
```

---------------------------------------

## [description]

__`[description]`__
A description add semantic to an identifier

__`[edge]`__

- [scalar_description]
- [vector_description]

---------------------------------------

### scalar_description

__`[path]`__ ngl:identifier:description:scalar_description

__`[syntax]`__

*[descriptor_identifier]* *described_identifier*;

__`[example]`__

```
ngl:concept matrix
```
matrix is described as a ngl:concept which is a described_identifier

---------------------------------------

### vector_description

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

## parametrization

__`[description]`__
Every described identifier can be parameterized

__`[syntax]`__
> *described_identifier*< `(` *described_identifier* *new_identifier* `) list(comma separator)` >

### explicitly required

__`[description]`__
A parameterised identifier can use the order or explicitly named parameters

__`[example]`__

```
ngl:concept:container matrix
{
    ngl:concept:number <rows> // 1
    ngl:concept:number <columns> // 2
    ngl::concept:size ( rows * columns )

    <data_type> .data // 3, redescribe :data from ngl::container
}

// parameters order
matrix<4, 2, ngl::float> float_matrix;
// named parameters
matrix<data_type ngl::float, rows 4, columns 4> float_matrix4x4;
```

---------------------------------------

## concretization


---------------------------------------
[alias]: #alias
[ngl:data]: /doc/reference/ngl/data
[ngl:entity]: /doc/reference/ngl/entity

[description]: #description
[scalar_description]: #scalar_description
[vector_description]: #vector_description