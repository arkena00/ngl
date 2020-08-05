# ngl:lang:execution:branch
>ngl:branch
{
    (_branch_expression_) _concrete_expression_ `list` 
}

Example:
```
ngl:function divide
{
    ngc::number <a>
    ngc::number <b>
    
    ngl:branch
    {
        (a != 0) .result = a / b
        () ngl:terminate 
    }
}
```



# experimental
``` 
ngl:function menu
{
    ngc::number <index>
    
    ngl:branch<index, ngl:instruction:equal>
    {
        index == 0 action1
        index == 1 action2
        () action_error
    }
    
    //
    ngl:match<index>
    {
        0 action1
        1 action2
        () action_error
    }
}



ngl branch
{
    ngl:lang:boolean_expression
    ngl:lang:executable_expression
}
    
ngl:meta<ngl:branch> match
{    
    ngl:data <value>

    // pseudo code
    for auto item : .boolean_expression
    {
        if (!is_literal<item>) ngl:compiler.error(errc:wrong_type)
        ngl:meta:print
        {
            .boolean_expression == value .executable_expression
         }
    }
}
//
ngl:match<index>
{
    0 action1
    1 action2
    () action_error
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


ngx:function add
{
    ngc::number <a>
    ngc::number <b>

    ngx:branch<ngl:phase>
    {
        (ngl:phase:compilation)
        {
            .result = 0
        }
        (ngl:phase:execution)
        {
            .result = (a + b)
        }
    }
}