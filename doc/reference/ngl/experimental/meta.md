# ngl:meta

multiple level of meta code
```
ngl meta
{
    <ngl:concept>
    <ngl:phase>

    ngl:function add
    ngl:function list
}

ngl:meta<ngc:matrix> meta_matrix
{
    ngl:branch
    {
        (meta.concept.size > 8000) { meta.concept.storage ngl:storage:dynamic }
        (meta.concept.storage ngl:storage:static)
    }
}


ngl:function serialize_fn
{
    <ngl:data>
    ngl:branch<data>
    {
        (ngc:int) .result = enc_int  
        (ngc:string) .result = data
        () .throw
    }
}

// meta meta concept
ngc meta_concept
{
    <ngl:concept>
    <ngl:data<ngc, ngc>> identifier

    ngl:loop<ngl:meta<concept>.datas>
    {
        ngl:meta<concept>.add< identifier<.item, test> >
    }
}

// meta concept
ngc serialisation
{
    <ngl:concept>
    <ngc:serialisation:format> = binary

    + ngc:meta_concept<concept, serialize_fn<ngc, ngc>>
}

ngc movie
{
    -> ngc:serializable
    -> ngc:storable
   
     ngl:edge<ngl, movie, ngc:serialisation<movie>, nge:trait>


    ngl:edge<ngl, movie, ngc:serialisation<movie>, nge:trait>

    ngc:id
    ngc:name
    ngc:duration
}
ngl:program

{
    (ngc:movie + ngc:serialisation) serialisable_movie
    movie.load<>
}

```