# ngl:concrete

__`[path]`__ ngl:data:concrete

__`[description]`__

A concrete is a [ngl:data](../data.md) representing the concretization of a [ngl:concept](../concept.md)
in the [ngl:entity] storage space.


``` 
ngl concrete
{
    ngl:concept <concept>
    ngl:access <access> // access = read | write
}

ngl:concrete<ngc:string, read> test { hello world }

ngl:alias< ngl:concrete<ngc:string, read> > ngr_string

ngl:alias< ngl:concrete<ngc:string, <access> > > ngr_string<access>

context : program
concretization_step
concept : source code
concrete : binary 
```