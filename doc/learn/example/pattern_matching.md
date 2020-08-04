# Pattern Matching Example

```
ngc sql_value
{
  (ngc:int | ngc:float | ngc:string)  data
}

ngl branch
{
    ngl:data <element>
}

ngl:branch<v>
{
    (v < 0) (v + 1)
    (0.5) (v * 2.9)
    (ngc:range) ()
    (ngc:range<0, 5>) ()
    ("truc") (v + "test")
    () v
}


// concept_branch on two elements
ngc:sql_value v1
ngc:sql_value v2

ngl:branch<v1.data, v2.data>
{
    (1, 2.5) ( .e1 + .e2 )
    (ngc:int, ngc:int) (v1.data + v2.data)
    (ngc:float, ngl:data) (v1.data * v2.data)
    (ngc:string, ngc:string) (v1.data + v2.data)
    () v
}
// ---

ngc serialisable
ngc encodable


ngl:meta_branch<identifier>
{
    (.name == encodable)
    (.name == serialisable)
    (.has_concept<truc>)
}


ngl:branch<point, color>
{
    (point.x == 0 && point.y == 5)
}

//
ngl:metabranch
```