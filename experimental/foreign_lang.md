
A ngl:format describe the shape of ngl:data

```
ngl:constant<string, "zeta"> zeta;

ngl convert
{
    ngl:data <input>
    ngl:format <input_format>
    ngl:format <output_format>
    .result = nglc:convert<input, output_format> // use compiler conversion
    // .result = ads:convert<input, output_format> // custom conversion
}

ngl:convert<4 ngc:string>
ngl:convert<"quatre" ngc:integer>
ngl:convert<"4" ngc:integer>


ngl format
{
    ngl:rule <?standard>
    ngc:char| escape_symbol = $
            | delimiter = $

    ngl:rule { // html format check }
}

ngl:format xml
{
    .escape_symbol = $
    .delimiter = $
}

ngl:format:xml html
{
    .standard = ngl:rule:xml:html 
}

html test
{$
    <form>
        <input text = "$ zeta $" />
    </form>
$}

ngc:program
{
    ngl::print<test.form.input.text>
}

ngc test
{
    ngl:rule
    {
        .require |fr-fr| a égal zéro
        |ngl|
        .require a == 0
    } 
}

ngl:shape:html zeta_form
<form>
    <p>test</p>
    <input text = "$ ngc:string <value> $" />
</form>

ngl:format:json zeta_form
{
    "form": {


ngc:int v = 4
ngl:format<v, ngc:string> // "4"
ngl:format<v, ngc:lang:fr> // quatre



```