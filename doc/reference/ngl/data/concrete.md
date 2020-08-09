# ngl:data:concrete

__`[description]`__

A concrete is a [ngl:data](../data.md) representing the concretization of a [ngl:concept](concept.md)
in the [ngl:entity] storage space.

__`[edge]`__

- [ngl:storage](../storage.md)

__`[shape]`__
> _ngs:scalar_description_ ngs:concrete


__`[exemple]`__

## Concrete

ngc test
{
    ngc:int <x> = [0]
    ngc:int <y> = [12]
    <ngc:string> = [coucou] ngs:ret [line2]
    ngc:string <test> = __[coucou [test] ]__
}

ngc:point p
p.x = [25]
p.y = [30]

[4] : 1 concept (number)
[four] : 2 concepts (number, string)
ngc:add<[4], [four]> == [8]
ngl:edge<ngl, [four], [4]>


```cpp
// integer array, deduced
[16 51 156]

// digit array
<ngc:digit>[1 6 5 1 1 5 6]

// boolean array
<ngc:boolean>[01101001]

// binary array
<ngc:hexa>[00 22 FF 78]

// string, deduced
[test]

// string, parameterization required, nc can't deduce the concept associated to the shape
<ngc:string>[0123]


// string containing []
[__[ ngs:return begin pattern
ngs:return ]__] end pattern

[__[
use [this] to create "concrete" datas
with multilines
]__]


[[]] // concrete using array of array
[_[]_] // concrete using pattern

[
    [ [123 000] [456 000] ]
    [ [123 000] [456 000] ]
]
``` 

## Concrete manipulation expressions

```cpp
concat ([123 456] [000 111]) = [246 912 000 111]
add ([123 456] + 5) = [246 912]
mul ([123 456] * 2) = [246 912]
cycle ([123 456] ** 2) [123 456 123 456]
split ([123 456] | 1) [[123] [456]]
split ([123 456 000 111 222] | 2) [[123 456] [000 111] [222]]
at ([123 456 789] @ 2) [456]
range (0..5)
range (0..)
range (..5)
range (2..-1)

head = ([123 456 789] @ 0) [123]
tail ([123 456 789] @ 1..) [456 789]
last ([123 456 789] @-1) [789]
init ([123 456 789] @0..-2) [123 456]

slice ([123 456 789 222 000] @2..-2) [789 222]                  // list @x..y : slice of list from x to y
reverse ([123 456 789] -@0..-1) [789 456 123] // reverse index 0 to last
rotate ([123 456 789] @-1..1) [789 123 456] // index last to 1
foreach ([123 456 789 000] $ (+3, *4, /2, -7))
```


## experimental
```
([123 456] + [111 222])
123 + 111
456 + 222

([123 456] <- X [111 222])
123 + 111
123 + 222
456 + 111
456 + 222

([123 456] X -> [111 222])
123 + 111
456 + 111
123 + 222
456 + 222


([ngl::function:add<1, 1> ngl::function:sub<2, 2>] $ ngl::print<?.result>)


([ngf:add ngf:sub] $ ngl::print< ?<1, 1>.result>)

(
    [ngf:add<0, ?p2> ngf:sub<?p1, 1>]
    $ ngl::print< ?<(??p1 | 8), (??p2 | 9)>.result>
)
print add<0, 9>
print sub<8, 1>

(
    [(1, 2) (3, 4)]
    $ [ngf:add ngf:sub]
    $ ngl::print< ?.result>
)
print add<1, 2>
print add<3, 4>
print sub<1, 2>
print sub<3, 4>


```