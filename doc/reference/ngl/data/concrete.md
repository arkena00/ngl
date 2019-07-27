# ngl:data:concrete
A concrete is a data representing a ngl:concept in the program environment

``` 
ngl concrete
{
    ngl:concept <concept>
    ngl:access <access> // access = read | write
}

ngl:concrete<ngc:string, read> test { hello world }

ngl:alias< ngl:concrete<ngc:string, read> > ngr_string

ngl:alias< ngl:concrete<ngc:string, <access> > > ngr_string<access>
```