# ngl:storage

__`[description]`__


__`[edge]`__




```

ngc array
{
    <ngl:data> concept
    ngc:number <size> 
}

ngc zeta
{
    <ngc:array> array // 1
    ngc:array<?, 2> <array> // 2 // autoparametrization ?

    // 3
    <ngc> concept
    ngc:array<concept, size> array
}

ngc:zeta<ngc:array<ngc:int, 2>> // 1

ngc:zeta<ngc:int> // 3

ngc size
{
    ngc:number <n>
}

ngc array
{
    <ngl:concept> concept
    ngc:number <size> 
}

ngc zeta
{
    ngl:concept <T>
    ngc:number <S>

    ngc:array<T, ngc:size<S>> data

    ngc:array< <ngl:concept>, ngc:size< <ngc:number> >> data
}

ngc:zeta alpha
{
    <ngc> .data // redescription
}

zeta<ngc:int, 2>


template<class T, int Size>
{

    std::array<T, Size>   
}
```




