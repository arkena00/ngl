# ngl:execution:branch
```
ngl::branch
{
    comparison_instruction execution_instruction
}
``` 

Ex:
```
ng::function test;

ngl::branch
{
    
}
``` 

ngl branch
{
    
}

ngl:branch zero_branch
{
    ngl:boolean_expression <bool_expr>
    ngl:execution_block <e>
    
    ngl:concrete
    {
        ngl:instruction:equal<b, 0>
    }
    
    fn:terminate
}

int divide(int a, int b)
{
    if ( b != 0) return a / b;
    else terminate;
}

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

binary_function<ngc:number> divide
{<ngl:parralel>

    zero_branch
    {
        .bool_expr = divide.b
        .block = (.result = .a / .b)
    }
}

dividde<4, 5>