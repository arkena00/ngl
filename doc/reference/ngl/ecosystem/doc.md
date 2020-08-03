# ngl:ecosystem:doc

__`[description]`__

Implement a documentation by adding a **ngl:ecosystem:doc** to your code targetting your **ngl:data**.

__`[example]`__

```
// Description of ngl::doc
ngl:ecosystem:doc
{
    ngl:data <data>
    ngl::string <content>

    ngc::string title = ngl:meta<data>.name
    ngc::string descriptors
    
    ngl:loop<ngl:meta<data.description>>
    {
        // concat string
        descriptors.append<.item.descriptor.name>
        descriptors.append<.item.described.name>
    }
}

// Description of a matrix
ngc:container matrix
{
    ngc:number <rows>
    ngc:number <columns>
    
    ngc:array<ngc::number, (rows * columns)> data
}

// Documentation of the matrix container
ngl:ecosystem:doc<matrix>
{
  .title "truc"
  .content "custom matrix content"
}
```