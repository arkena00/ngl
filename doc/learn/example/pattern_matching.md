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


ngl:more_than_branch<i>
{
    (0) i > 0
    (5) i > 5
}

//
ngl:metabranch

// shape matching
ngl:branch<url>
{
    ("http://" ngs:word "." ngs:domain) .result url
    (ngs:word "." ngs:domain) .result ("http://" url)
}

ngs ip
{
    ngs:ip_number "." ngs:ip_number "." ngs:ip_number "." ngs:ip_number
}

ngs:ip my_ip
ngl:branch<my_ip>
{
    (my_ip.ip_number[0] == 127) // is_local
    (my_ip.ip_number[0] == 0) // error
}

ngl:branch<bitset>
{
    ([111] ..) 11100010
    ([00] .. [11]) 00100011
    ([0001] [?] [011]) 00010011 | 00011011
}

// sugar
(127.?.?.?)
(!127.?.?.?)

if (a == 1)
{
    if (b == 2)
        if (c == 3)
}

ngl:nested_branch<a, b, c>
{
    (1) {
        print<n1>
        print<n11>
        }
     -> (2) print<n2>
     --> (3) print<n3>

     > 
}

```