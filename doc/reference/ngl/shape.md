# ngl:shape

__`[description]`__

A **ngl:shape** describes the concrete shape of **ngl:data**

It's described using intrinsic concepts.

The shape of ngl itself is read during the ngl:phase:shape

__`[shape]`__

> ngl:shape { `ngc:many<` _ngs:identifier_ `>` }

__`[example]`__


```
ngl:shape digit
{
    ngc:range<0 9>
}

ngl:shape integer
{
     ngc:sequence<
        ngc:and< ngc:not<0> ngc:digit>
        ngc:many<ngc:digit>
     >
}

ngl:shape binary_number
{
    ngc:many< ngc:or<0 1> >
}
```

## shape conceptualisation

__`[description]`__

To conceptualise a shape, it requires an edge with a concept

__`[example]`__

````
// math.ngl
ngl:shape add
{
     ngc:sequence< ngs:identifier ngs:plus ngs:identifier >
}

ngl:cluster math
ngl:concept sum
{
    ngc:math:number n1
    ngc:math:number n2

    ngc:math:number .result
}

ngl:edge<ngl, ngl:shape:add, ngl:concept:math:sum>
// ngs:identifier[0] -> n1
// ngs:identifier[1] -> n2
````

