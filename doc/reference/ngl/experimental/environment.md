# ngl:environment

__`[description]`__

An environment contains [ngl:data](data.md). It can be separated in different logical regions.
Many environment can exist but nothing can contain an environment.

//?
It is a [ngl:storage_space](storage.md#space) at the top level /* in the same [ngl:context] */, 
// A storage_space is a region of an environment who contains ngl:data
```
ngl:environment computer
{
    ngl:data processor
    {
        ngl:storage register
        ngl:data word_size
    }

    ngl:concrete_storage
    {
        ngl:data hdd
        ngl:data ram
    }

    ngl:entity os
    {
        ngl:data word_size
        
        ngl:data <architecture>
        ngl:storage filesystem
        ngl:storage stack
        ngl:storage heap
    }
}

// x86-64

```