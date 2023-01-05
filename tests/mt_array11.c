#include <gadget/gadget.h>

LIB_GADGET_START

void imprime_array_mt( MT_CELL *array, DS_ARRAY array_data );

Main
    //New_mt_array( test );
    New mt test;
   
    Append_mt(test, int, 15);
    Append_mt(test, double, sqrt(30*3.1415));
    sAppend_mt(test, "María tenía un corderito");
    Append_mt(test, long, 100000000);
    Append_mt(test, float, -3.0/4.0);
    sAppend_mt(test, "su piel era blanca como la nieve");
    Append_mt(test, double, 1.34e-4);
    Append_mt(test, int, 100 );

    Print "Array original:\n";
    imprime_array_mt( SDS(test) );

    test = Delete_lst_mt(pSDS(test), 3);
    test = Delete_lst_mt(pSDS(test), 3);
    
    Print "\nNuevo array:\n";
    imprime_array_mt( SDS(test) );
    
    //Free_total_array_mt(test);
    Free mt test;

End

void imprime_array_mt( MT_CELL *array, DS_ARRAY array_data ){
   
   int i;
   Iterator up i [0: 1: Len(array)]{
       Print_Cell( array, i ); Prnl;
   }
   Prnl;
}


