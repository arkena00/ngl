# ngl:edge

: edge
:: auto edge
:<edge_name>: parametric edge
. edge of type has

ngc page
{
    ngc:string name
}


source:target // logical edge
source::target // logical autoedge
source:<is>:target // parametric autoedge
source:<is>target // parametric edge

source:<is>:target

ngc:page web
{
    // web context // create context
    // ^. access ngc:page context
    .ngc:* // import all concepts from ngc:page
    // 
    
    ^.name
    
    :<is>:ngc:page
    
    web_page :is: page
    
    ngl:edge<is, ngc:page>
    ngc:url url
}

ngc:page web
{
    :<is>page // create edge of type is between page:web and page
    
    ngc:url url
}
// alias web_page

page-<is>-ngc:page:web

ngc:page:web :<is>: ^page