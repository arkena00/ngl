# ngl:ecosystem:build

__`[description]`__

Manage ecosystem, project architecture, name, ...

__`[example]`__

```
ngl:environment environment
{
    <<ngc::architecture>> = <<ngl:compiler:architecture>>
    // ngc::architecture = project.architecture
}




ngl:ecosystem project_tree
{
    <ngc:project>
}

ngl:ecosystem project
{
    ngc::string <name>
    ngc::path path
    ngc::string version
    ngc::path root
    ngc:meta:tree<project> project_tree
}

ngl:ecosystem:project nc
{
    .name "ngl compiler"
    
    .project_tree
    {
        ngc:folder bin
        ngc:folder examples
        ngc:folder include
        {
          ngc:folder ngl:meta<nc>.name
        }
    }

    ngl:environment:architecture [x64]
}

// non-intrusive version
ngl:project_tree nc_project_tree
{
    <ngc:project>

    ngc:folder bin
    ngc:folder examples
    ngc:folder include
    {
        ngc:folder ngl:meta<project.name>.name
    }
}

ngl:project_tree<my_project>
{

}
```

nc --make ngl:project