# ngl.type.concept

A concept type has to be true for any version of this concept in his generic domain

```
ngc integer
{
    context: ngd.math
}

ngc size
{
    context: ngd.data_processing
    
    ng_require
    {
        ng_value >= 0 && 
        ng_value <= 2 ^ nge.processor.word_size
    }
}

ngc integer
{
    .context: ngd.data_processing
    .entity: computer
    .storage: ngc.stack
    
    size: ngc.size
     
    ngl.require
    {
        size in [nge.processor.char_size .. nge.processor.word_size]
    }
}

ng int
{
    import: ngc.integer
    ngc.integer.size: nge.processor.word_size
}

ng int8
{
    import: ngc.integer
    ngc.integer.size: 8
}

ng array
{
    import ngc.container;
    nga.storage: nge.memory.heap;   
    element_type: ?
}

fn add(ngc.integer a, ngc.integer b) -> ngc.integer
{
    
}

fn size(ng.int t)
{
    return t.size;
}

fn main()
{
    ng.int a; // ngc.stack.add()
    
    ng.int8{ nga.storage: ndb } b; // ndb.add() 
    ng.alias ndb_int8 = ng.int8{ nga.storage: ndb };
    
    ndb: neuroshok.ndb;
    ng.array<ng.int> ar;
    ng.array<element_type: ng.int> ar;
    
    
    //ngl.io.add("coucou" a "c'est " b);
}

ngl:concept web:dom:div;
web:dom:div -> ngc:concept:html

html
{
    head
    {
        title { Exemple }
    }
    body
    {
        
    } 
}




```

