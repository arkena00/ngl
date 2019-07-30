# ngl:storage

__`[description]`__

A storage is a support for a [ngl:data](data.md) (filesystem, virtual memory, database)
It is a region of a [ngl:environment](environment.md)
Each [ngl:data] has a storage.

__`[edge]`__
- entity_storage // storage in the entity env region

# ngl:storage_space

A storage_space is a delimited region of an [ngl:environment]

__`[example]`__
```
ngl:concept matrix
{
    concept:data:storage ngl:storage:heap
}
```
