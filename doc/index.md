# Neuroshok Generic Language

## Introduction

To write a program, we need to describe things. \
ngl will describe any thing as **ngl:data**

To be able to describe things, we need a **ngl:data** able to process logic : an **ngl:entity** \
ngl is an entity who describe things.

To exist, those things need to have a **concrete** support somewhere : in a **ngl:storage**

To act or interact, we need physical or logical rules for each thing : using **ngl:rule** 

Because we have limits, we need to have a maximum and minimum storage : 
- ngl:environment : contains all ngl:data
- ngl:element : an atomic ngl:data

The programmer will write how the ngl entity will work (the compiler)
and how it will work (programs, metaprograms etc ...)

A program is a concept of a programmer, the programmer concretise his concept by writing source code.
The compiler transform the concrete source code to a concept then concretise it to binary code.

## General concepts
- **Data**
    - Concept : a concept is a ngl:data described by an entity stored in the entity storage
    - Concrete : a concrete is a materialisation of a concept
        - Entity : an entity is a data able to process logic

- **Rule** : describe an internal logic or external interactions
      
- **Storage** : store *data* with logic (rules)
    - Environment : a storage containing all the *data* from an entity perspective
    - Element : an atomic ngl:data  from an entity perspective
    
- **Shape** : a shape describe logic between ngl:element
    
- **Edge** : create interactions between *data*

- **Entity** : logical data who can create **ngl:edge** to interact

## Objectives
- simple : easy to read, learn
- generic : write code once, avoid duplicated code
- collaborative : centralise ngl code
- inclusive : allow external code
- customisable : rewrite the language with the language without breaking interop
- compile to anything


## Resources

[Learn](learn/1.getting_started.md)

[Language reference](reference/index.md)