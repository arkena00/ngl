```
ngl data
{
    ngl:storage storage
    // ngl:storage
}

ngl:data concept
{
    .storage
}

ngl::concept container
{
    .storage ngl:storage:heap
    <ngl:data> data_type // data to store
}

ngl:concept:container<data_type> matrix // data_type unknown, has to be define in current context
{
    ngl:concept:number <rows>
    ngl:concept:number <columns>
    ngl::concept:size ( rows * columns )

    <data_type> .data // redescription
}

// meta concept
ngl meta
{
    ngl:concept <concept>
}

// non-intrusive version
ngl:meta<ngc:matrix> meta_matrix
{
    ngl:branch
    {
        (meta.concept.size > 8000) { meta.concept.storage ngl:storage:dynamic }
        (meta.concept.storage ngl:storage:static)
    }
}


// concrete
matrix<4, 4, ngl:float> concrete_matrix;
```
