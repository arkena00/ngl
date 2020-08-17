# compilation
nc /home/project

project/
    ngl.ngl
    
    
///////////////////////////////////////////////////////////////////////////////////////
# enum
enum class color {red blue}

ngc color
{
    ngc:name = ngl:meta:self.name
    <ngc:value>
}

ngc:color <spe> red<[FF0000]> // color desribe red as a specialization of color // red is color
ngc:color blue<[0000FF]>

ngc:color:red

///////////////////////////////////////////////////////////////////////////////////////
# ngl sections
#storage:heap

#ngo

#ngs:html

///////////////////////////////////////////////////////////////////////////////////////
ngl:cluster main

ngl:program
{
    ngl:edge<os:console.input, main.input>
    ngv:os:console.input -> main.input
    
    nio:console -> [Enter your name]
    ngc:string input <- nio:console
}

ngl:function input
{
    <ngc:string> data
    ngc:write<data, ngv:os:console>
}



///////////////////////////////////////////////////////////////////////////////////////
execution

ngl:cluster main

ngl:program
{
    ngc:number n
    
    -> producer<n> // ngl:edge<ngl, program, producer, parallel>
    -> consumer<n>
}

    ngl:entity:engine producer
    {
        ngc:number <n>
        ngc:add<n, 1>
    }
    
    ngl:entity:engine consumer
    {
        ngc:number <n>
        ngc:sub<n, 1>
    }

ngl:program2
{
    ngc:number n2
    
    -> producer<n2>
    -> consumer<n2>
}

// chain
-> program -> program2
// or
-> F1
--> F2
--> P2
---> F3
---> P3

// parallel
-> program
-> program2

// 2 process 2 threads
-> init -> process1 -> program
                    -> program2
                    
-> init2 -> process2 -> program
                     -> program2
                     
// pipeline
ngl:entity:engine pipeline
{
    ngc::array <datas>
    data -> op1 -> op2
}

fn pipeline:add
{
    ngc:array <data>
    pipeline.data
}


pipeline.add<data>
pipeline.add<data>


ngl:data data

data:f1:f2<?, 7>:parallel<f3 & f4>
