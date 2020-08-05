# ngl:concept:execution:function

__`[description]`__

__`[experimental]`__

```
ngl::execution function
{
    ngl:data result

    ngl:rule 
    {
        !ngl:edge<ngl, ngl:data, ngl:meta:self.result, write>
        ngl:edge<ngl, ngl:meta:self, ngl:meta:self.result, write>
    }
}

ngl:concept concept_of
{
    <ngl:concept>
    ngl:concept <c1>
    ngl:concept <c2>
    ngl:concept result_type

    .result_type ngl:branch<c1, c2>
    {
        (ngc:int, ngc:int) ngc:int
        (ngc:float, ngc:float) ngc:float
        (ngc:float, ngl:data) ngc:float
    }
}

ngl:concept:concept_of<add, ngl:custom, ngc:int>
{
    .result_type ngl:custom
}

ngl::function add
{
    ngc::number <a>
    ngc::number <b>

    <type = ncc:concept_of<a, b>> .result = (a + b)
}

ngl::function:add<5, 6, ngc::double> // 5 + 6 as double

ngc:string<"Hello"> concept_string
ngl:concrete<concept_string, ngl:storage:entity> concrete_string

ngl:data:concrete<[truc]> a



///////




ngl::function zeta
{
    comparison_instruction execution_instruction
}
``` 

Ex:
```
ngl::function add
{
    ngc::number a
    ngc::number b
    
    ngc::int result
}

add<2, 4>




ngc binary_function
{
    ngc::number <a>;
    ngc::number <b>;
    ngc::number <result>;
}

fn divide
{
    zero_branch<.b, (.result = .a / .b)>
}

fn divide
{
    ngc::number < [a b result] >

    ngl:branch
    {
        b == 0 => fn:terminate
        => result = a / b
    }
}

binary_function<ngc:number> divide
{<ngl:parralel>

    zero_branch
    {
        .bool_expr = divide.b
        .block = (.result = .a / .b)
    }
}

dividde<4, 5>

```