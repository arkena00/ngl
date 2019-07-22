# ngl:lang:execution:function

## function
```
ngl function
{
    ngl:data
}

ngl::function zeta
{
    comparison_instruction execution_instruction
}
``` 

Ex:
```
ngl::function add
{
    ngc::int a
    ngc::int b
    
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