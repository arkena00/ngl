

```
int main()
{
    int a,b,c;
    cout << "Enter value of a: ";
    cin >> a;
    cout << "Enter value of b: ";
    cin >> b;
    c=a;
    a=b;
    b=c;
    cout<<"After swaping a: "<< a << " b: " << b;
    return 0;
}

ngc:function add
{
    ngc:integer {a, b}
    
    ngl:return 
}

ngl:main
{
    ngio:input x
    ngc:constant y = 5
    
    ngc:function:add<x, y>
    
    ngl::loop<container>
    {
        ngl:infinite
    }
}

ngl:program main
{
    ngc:input<ngc:string> age
        
    ngl:function:format<"votre age est {}", age>

    ngl:sprint<> [Votre age est <age>]
}

```