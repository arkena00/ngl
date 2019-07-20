
```
ngc matrix
{
    ngc:size rows
    ngc:size columns
    ngl::concept:size // use size as identifier
    
    nge:context ngl:concept:math // use matrix as edge source 
}

ngc:matrix matrix4x4
{
    ngc:usize .ngc:size
    
    .rows ngc:number
    .columns ngc:number
   

    .rows 4
    .columns 4
}

ngc matrix4x4
{
    nge:is matrix
    
    
}

ng:matrix<ngc::dynamic>
```
