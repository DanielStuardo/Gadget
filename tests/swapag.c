

#include <gadget/gadget.h>

LIB_GADGET_START

void Print_array( RDS(double, array) ){
    Iterup(pag, array,k){
      Print "Pagina: %d\n", k;
      Iterup(row, array, i){
        Iterup(col, array,j){
            Print "%3.*lf", 0, $array[i,j,k];
        } Prnl;
      } 
    } Prnl;
}

void Intercambia_pags( RDS_ptr(double, array), int c1, int c2){
    Swap_pags_ptr(array,double,c1,c2);
}



Main
    Fill array x as double(5,5,3) with ceil( rand() % 10 );
    
    All range for x;
    
    Print_array( SDS(x) );
    
    Swap_pags(x,double,0,2); 
    Print_array( SDS(x) );

    Intercambia_pags( SDS_ptr(x), 1,2); Throw( salida );
    Print_array( SDS(x) );
    
 salida:


    Print "Imprime solo la pagina 1:\n";

    Fix(pag, x, 1);
    Print_array( SDS(x) );
    
    Free array x;
    getchar();
End
