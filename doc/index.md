# Neuroshok Generic Language

## Introduction

To write a program, we need to describe things. \
ngl will describe everything as **ngl:data**

To be able to describe things, we need a **ngl:data** able to process logic : an **ngl:entity** \
ngl is an entity who describe things.

To exist, those things need to have a **physical** support somewhere : in a **ngl:storage**

To act or interact, we need physical or logical rules for each thing : using **ngl:rule** 

The programmer will write how the ngl entity will work (the compiler)
and how it will work (programs, metaprograms etc ...)

### Architecture   
- **Data**
    - Physical
        - Constant : an immutable data
        - Mutable : a mutable data
    - Logical
        - Entity : a data able to process logic
    
    - ? Specific
        - logical_constant : a mutable data following a specific logic but not mutable by an external entity
        - logical_mutable : a mutable data following a specific logic, it can be immutable for some entities

- **Rule** : describe an internal logic or external interactions
      
- **Storage** : store *data* with logic (rules)
    - Environment : a storage containing all the *data* from an entity perspective
    
- **Edges** : create interactions between *data*

- **Concept** : a concept is a ngl:data described by an entity stored in the entity storage

## Resources

[Learn](learn/1.getting started.md)

[Language reference](reference/index.md)