

#include <gadget/gadget.h>

LIB_GADGET_START

void Print_array( RDS(double, array) ){
    Iterup (row, array, k){
       Print "%3.*lf", 0, $array[k];
    } Prnl;
}

void Intercambia_lst( pRDS(double, array), int c1, int c2){
    Swap_lst_ptr(array,double,c1,c2);
}



Main
    Fill array x as double(5) with ceil( rand() % 10 );
    
    All range for x;
    
    Print_array( SDS(x) );
    
    Swap_lst(x,double,0,2); 
    Print_array( SDS(x) );

    Intercambia_lst( pSDS(x), 1,2); Throw( salida );
    Print_array( SDS(x) );
    
 salida:


    Print "Imprime un rango:\n";

    Range for x [2:1:4];
    
    Print_array( SDS(x) );
    
    Free array x;
End
