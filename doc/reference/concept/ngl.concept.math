```
ngl:concept many


ngl.concept function
{
    ngl.alias: fn
}

ngl:concept integer
{
    ngl.concept.edge.context: integer -> ngl.concept.data_processing
}

ngl:concept integer
{
    ngl.edge.context: integer -> ngl.concept.data_processing
    ngl.entity: computer
    ngl.storage: ngl.concept.memory<.domain: data_processing>.stack
    
    size: ngl.concept.size
     
    ngl.require
    {
        //size in [nge.processor.char_size .. nge.processor.word_size]
    }
}

ngl.concept.type int
{
    <- ngl.concept.integer<.context: ngc.data_processing>
    -> ngl.concept

    ngl.alias: ng
    
    ngc.integer.size: nge.processor.word_size
}

fn main
{
    a: ng.int
    b: ng.int<32>
}
```