

#include <gadget/gadget.h>

LIB_GADGET_START

void Print_array( RDS(double, array) ){

    Iterup(row, array, i){
        Iterup(col, array,j){
            Print "%3.*lf", 0, $array[i,j];
        } Prnl; 
    } Prnl;
}

void Intercambia_cols( RDS_ptr(double, array), int c1, int c2){
    Swap_cols_ptr(array,double,c1,c2);
}



Main
    Fill array x as double(5,5) with ceil( rand() % 10 );
    
    All range for x;
    
    Print_array( SDS(x) );
    
    Swap_cols(x,double,0,2); 
    Print_array( SDS(x) );

    Intercambia_cols( SDS_ptr(x), 1,2); Throw( salida );
    Print_array( SDS(x) );
    
 salida:


    Print "Imprime solo la columna 4:\n";

    Fix(col, x, 4);
    Print_array( SDS(x) );
    
    Free array x;
End
