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

ngl:storage register
ngl:storage stack
ngl:storage heap
ngl:storage filesystem
ngl:storage database
ngl:storage garbage_collector // ngl:data without edges are deleted
ngl:storage entity // ngl:data stored in the program binary
```

# ngc:location

ngl:location<ngl:env, 1, 0> register
ngl:location<ngl:env, 1, 1> heap

ngl:location<heap, 1, >

```

ngl:program
{
    ngc:array<ngc:byte> stack_array
    
    # ngl:data:storage:heap
    ngc:int a
    ngc:int b
    ngc:int c
    
    # ngl:data:storage = stack
    
    
    ngc:array<ngc:byte> heap_array
}

ngl:location
{
    ngc:number <dimension>
    ngl:env:storage origin
    ngl:coordinate<dimension> position
}
```

///////////////////////////////////////////////////////////////////////////////////////
entity, storage

ngc point
{
    ngc:number <x> = [0]
    ngc:number <y> = [0]
}

ngl:program
{
    ngc:point<.storage = register> p
    ngc:point<.storage = heap> p
}


ngl:entity E
ngl:storage S

ngl:edge<ngl, ngc:movie, ngl:storage:database, write>

[00 00 00 00 00]
[00 22 11 45 78]


// storage:register
r0 [00000000]
r1 [00000000]

// storage:stack

// storage::heap
[000000000000000000000000000000000000]

// storage:database
T0 T1 T2

ngc coordinate
{
    ngc::array<ngc:number> <points>
}

ngc location
{
    ngl:storage <origin>
    ngl:coordinate<ngc:array> position
    // data_dimension = origin.data_dimension
}

ngl storage
{
    ngc:number <dimension>
    ngl:location<dimension> <origin>
}

ngl:environment
{
    :<is> ngl:storage

    ngl:entity os
    {
        ngl:storage<2, ngl:location<environment, [0]>> register // 2D storage, location environment, index 0
        ngl:storage<1, ngl:location<environment, [1]>> heap // 1D storage, location environment, index 1
    }
}

ngl:storage<2, ngl:location<ngl:storage:heap, [0xFF0023]>> db // 2D storage, location memory, index 0xFF0023(address)

ngc:point<5, 5> p

ngc:write<db, p> // insert into point_table VALUES(5, 5)
ngc:write<os:register, p>

ngc:read<ngl:location<os:register, [1 32]> // read in the register storage, register 1, bit 32 
