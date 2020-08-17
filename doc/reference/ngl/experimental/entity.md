# ngl:entity

An entity is a logical [ngl:data] who has concepts and can make ngl:execution:*
It can interact with its environment.

entity
{
    source_code
    internal concepts
    external concepts
}

//



//
an entity can choose where to execute code

```
ngl:function generic_func
{
    ngc:int <a>
    ngc:int <b>
    ...
}

ngl:program program
{
    ngc:begin<shader>

    ngc:write<shader, [a b]>
    ngc:write<shader, [c d]>

    ngc:end<shader>
}

ngl:entity:engine shader
{
    .execution = gpu
    ngc:array <array>

    generic_func<array.get<0>, array.get<1>>
}

```