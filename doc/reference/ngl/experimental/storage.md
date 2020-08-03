# ngl:storage

__`[description]`__

A storage is a support for a [ngl:data](data.md) (filesystem, virtual memory, database)
It is a region of a [ngl:environment](environment.md)
Each [ngl:data] is on a storage.

ngl:storage have rules

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


program entity storage 
[3                       ]

garbage collected storage
[                        ]

dynamic storage
[                        ]

database  storage
[                        ]

stack storage
[                        ]

proc register storage
[                        ]


ngc:int x
test<x>