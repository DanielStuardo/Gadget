
#include <gadget/gadget.h>

LIB_GADGET_START

void Print_array( RDS(int, array) ){
    Iterup(row, array, i){
        Iterup(col, array,j){
            Print "%3d,", $array[i,j];
        } Prnl; 
    } Prnl
}

void Intercambia_filas( RDS_ptr(int, array), int f1, int f2){
    Swap_rows_ptr(array,int,f1,f2);
//    return array;
}

Main
    Fill array x as int(5,5) with ceil( rand() % 10 );
    
    All range for x;
    Print_array( SDS(x) );
    
    Swap_rows(x,int,3,5);
    if( Is_ok ){
       Print_array( SDS(x) );
    }
    Swap_rows(x,int,3,4);
    if( Is_ok ){
       Print_array( SDS(x) );
    }
    Intercambia_filas( SDS_ptr(x), 0,1);
    if( Is_ok ){
       Print_array( SDS(x) );
    }
    Free array x;
End
