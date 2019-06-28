# ngl::identifier
An identifier is a word composed by ascii chars \
`zeta` 
It is determined by the entity describing

## [identifier:path]
An identifier can have a path \
`source:zeta:alpha:omega`

## [identifier:auto_path]
Intermediate identifiers can be omitted if a single path exist between the omitted identifiers \
`source::omega`

## [optional<identifier>]
An identifier can be optional

## [alias<identifier>]
An identifier can be aliased \
`nge:alias ngl:concept ngc` 

## [identifier:described]
An identifier can be described \
`ngl:concept matrix` \
matrix is described as a ngl:concept which is a described identifier

Described identifiers can be connected to other identifiers
```
[identifier:described] [optional:identifier]
{
    [list:identifier]
    [optional:[list:edge]]
}
```
Connect a [list:identifier] from [identifier:described] to [list:identifier] using ngl:edge:has

```
ngl:concept:container matrix
{
    ngl:concept rows
    ngl:concept columns
    ngl::concept:size // use size as identifier
    
    nge:context ngl:concept:math // use matrix as edge source 
}
```

ngl:concept:container matrix
{
    ngl:concept rows
    ngl:concept columns
    ngl::concept:size // use size as identifier

    <
        if ()
    >
    ngc:bool dynamic
    
    .storage = ?dynamic   
}

ngc:matrix<rows: 4, columns:4> matrix4x4

## [identifier:parameterized]
Every described identifier can be parameterized 

ngc:matrix
<
    ?dynamic

    if (ngl:true) rows: 4
    columns:4
> matrix4x4

## [identifier:concretized]
ng:matrix<ngc::dynamic>

Use the ngc:matrix and concretise it

