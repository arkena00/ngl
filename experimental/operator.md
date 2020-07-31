ngl:shape ngs:not !
ngl:shape ngs:pow ^

ngl:shape factorial
{
    ngs:expression ngs:not
}

ngl:shape pow
{
    ngs:expression ngs:pow ngs:expression
}

ngl:edge<ngs:pow, ngc:math:exponential>

ngl:edge<ngs:expression, [ngs:not ngs:pow ngs:mul]

a ^ b !
(a ^ b) !

//

ngl:concept:math exponential
{
    ngc:number base
    ngc:number exponent
}