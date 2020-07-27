# ngl:storage

__`[description]`__

A storage is a support for a [ngl:data](data.md) (filesystem, virtual memory, database)
It is a region of a [ngl:environment](environment.md)
Each [ngl:data] has a storage.

__`[edge]`__

__`[concrete]`__

```
ngl storage
{
    ngl:function add
    ngl:function remove
}

ngl:storage stack
ngl:storage heap
ngl:storage filesystem
ngl:storage database
ngl:storage garbage_collector // ngl:data without edges are deleted
ngl:storage entity // ngl:data stored in the program binary
```


# ngl:storage_space

A storage_space is a delimited region of an [ngl:environment]

__`[example]`__
```
ngl:concept matrix
{
    concept:data:storage ngl:storage:heap
}
```
