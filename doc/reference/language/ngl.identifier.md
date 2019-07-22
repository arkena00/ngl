# ngl:identifier
An identifier is a word composed by ascii chars

Types:
- _identifier_path_
    ```
    source:zeta:alpha:omega
    ```
    
- _identifier_autopath_ \
    Intermediate identifiers can be omitted if a single path exist between the omitted identifiers
    ```
    source::omega
    ```
    
- _descriptor_identifier_
    An identifier previously described
    
- _described_identifier_
    An undescribed identifier 

___

## alias
An identifier can be aliased
```
? ngl:edge<alias> ngl:concept ngc
ngl:alias<ngl:concept> ngc
```

## [description](#description)
A description gives semantic to an identifier

Types:
- scalar_description
- vector_description

### scalar_description
>_descriptor_identifier_ _described_identifier_
```
ngl:concept matrix
```
matrix is described as a ngl:concept which is a described_identifier

### vector_description

>_descriptor_identifier_ _described_identifier_
{
    _[description]_ `optional,list`
    identifier
    _edge_ `optional,list`
}

Example:
```
ngl:concept:container matrix
{
    ngl:concept:number rows
    ngl:concept:number columns
    ngl::concept:size // use size as described_identifier
    
    nge:context ngl:concept:math // use matrix as edge source 
}
```

## redescription
Every described identifier can be redescripted 

```
ngl:concept:container:matrix float_matrix
{
    ngl::float :ngl:concept:number // redescription of ngl:concept:number in float_matrix context
}
? // parametric redescription version
? ngl::matrix<ngl::float :ngl:concept:number> float_matrix;
```

## parametrization
Every described identifier can be parameterized 

> _described_identifier_< (_described_identifier_ _new_identifier_) `list(comma separator)` >

### explicitly required
A parameterised identifier can use the order or explicitly named parameters
```
ngl:concept:container matrix
{
    ngl:concept:number <rows> // 1
    ngl:concept:number <columns> // 2
    ngl::concept:size ( rows * columns )
    
    <data_type> :data // 3, redescribe :data from ngl::container
}

// parameters order
matrix<4, 2, ngl::float> float_matrix;
// named parameters
matrix<data_type ngl::float, rows 4, columns 4> float_matrix4x4;
```

## concretization


___
[description]: #description