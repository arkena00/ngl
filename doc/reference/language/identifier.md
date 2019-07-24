# ngl:identifier
__`[description]`__
An identifier is a unique [ngl:data] created by a [ngl:entity] used to describe another [ngl:data].

__`[edge]`__
- [raw_identifier](#raw_identifier)
- _identifier_path_
- _identifier_autopath_
- _descriptor_identifier_
- _described_identifier_
_______________________________________

## raw_identifier
__`[path]`__ [ngl:identifier:description:scalar_description](#scalar_description)
__`[rule]`__
- must match a-z
_______________________________________
## [alias]
An identifier can be aliased
__`[path]`__ [alias]
__`[example]`__
```
? ngl:edge<alias> ngl:concept ngc
ngl:alias<ngl:concept> ngc
```
_______________________________________
## [description]
__`[description]`__
A description add semantic to an identifier
__`[edge]`__
- [scalar_description]
- [vector_description]
_______________________________________
### scalar_description
__`[path]`__ ngl:identifier:description:scalar_description
__`[syntax]`__
_[descriptor_identifier]_ _described_identifier_;
__`[example]`__
```
ngl:concept matrix
```
matrix is described as a ngl:concept which is a described_identifier
_______________________________________
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
_______________________________________
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
_______________________________________
## parametrization
__`[description]`__
Every described identifier can be parameterized
__`[syntax]`__
> _described_identifier_< `(` _described_identifier_ _new_identifier_ `) list(comma separator)` >

### explicitly required
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
_______________________________________
## concretization


_______________________________________
[alias]: #alias
[ngl:data]: /doc/reference/language/data
[ngl:entity]: /doc/reference/language/entity

[description]: #description
[scalar_description]: #scalar_description
[vector_description]: #vector_description