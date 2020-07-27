# ngl:edge

__`[description]`__

An edge is a parameterized link between two ngl:data

__`[shape]`__
> _ngs:identifier_ `ngc:or<` : :: . `ngc:optional<` :< _ngs:raw_identifier_ > `>` `>` _ngs:identifier_


**Intrinsic edges**
- is
- has
- write : modify the ngl:data respecting the rules
- read : access the ngl:data

**Edge shapes**
- :: auto edge
- :<edge_name> parameterized edge
- . edge of type has

__`[exemple]`__

```
ngc page
{
    ngc:string name // ngl:edge<ngl, ngc:page, name, has>
}

source:target // logical edge
source::target // logical autoedge
source:<is>:target // parametric autoedge
source:<is>target // parametric edge
```