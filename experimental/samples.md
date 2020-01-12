struct Matrix<T: Copy + Display> {

        rows: usize,
        columns: usize,
        data: Vec<T>,
}

impl<T: Copy + Display> Matrix<T> {

    fn new(rows: usize, columns: usize) -> Self {

        Self {

            rows: rows,
            columns: columns,
            data: Vec::with_capacity(rows*columns),

        }

    }
}

ngc matrix
{
    <- ngc:container:capacity<rows * columns>
    .storage<nge:storage:heap>

    ngc:size rows
    ngc:size columns 
    ngc:many<ngc:data> 
}

ngc many
{
    ngl:data <data>
    <ngl:data>
}

ngc array
{
    ngc:many<int>;
}

ng matrix
{
    ngc:size ng:int
    ngc:many ng:vector
}

ng:matrix{ rows = 2, cols = 2 }

ng:matrix<2, 2, ngc:float> m;

ngc integer
{
    
}