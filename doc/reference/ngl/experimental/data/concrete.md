# ngl:data:concrete

__`[description]`__

A concrete is a [ngl:data](../data.md) representing the concretization of a [ngl:concept](../concept.md)
in the [ngl:entity] storage space.

__`[edge]`__

- [ngl:storage](../storage.md)

``` 
ngl concrete
{
    ngl:concept <concept>
    ngl:storage <storage>
}

ngc:string<"Hello"> concept_string
ngl:concrete<my_string, ngl:storage:entity> concrete_string

ngl:alias< ngl:concrete<ngc:string, read> > ngr_string

ngl:alias< ngl:concrete<ngc:string, <access> > > ngr_string<access>

context : program
concretization_step
concept : source code
concrete : binary 
```