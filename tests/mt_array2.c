#include <gadget/gadget.h>
////#include "include/gadget_mt_array.h"

LIB_GADGET_START

void imprime_array_mt_3( MT_CELL *array, DS_ARRAY array_data );

Main
   /* esto crea un array con posiciones enteras iniciales rellenos con ceros */
    Dim (5,5) as_mt_array(test);
    
    /* head encabezado */
    sChg(test,0,0, "+" );
    sChg(test,0,1, "head 1" );
    sChg(test,0,2, "head 2" );
    sChg(test,0,3, "head 3" );
    sChg(test,0,4, "head 4" );
    
    /* head lateral */
    sChg(test,1,0, "fila 1" );
    sChg(test,2,0, "fila 2" );
    sChg(test,3,0, "fila 3" );
    sChg(test,4,0, "fila 4" );
    
    /* cuerpo */
    
    Range for test [ 1:1:Rows(test), 1:1:Cols(test)];
    int i;
    Iterup(col, test, i){
        Chg(test, float, 1, i, 185.0/(255.0+i));
        iCell(test, 2, i) = ceil(rand()%100);  /* no tengo que cambiar el tipo inicial de la celda */
        Chg(test, double,3, i, sin( Radian(30+(i-1)) ) );
        Chg(test, long,  4, i, rand()%100000);
    } 
    
    imprime_array_mt_3( SDS(test) );
    /* puedo usar dCell(), porque el espacio de la celda ya está creado y 
       no cambiaré el tipo */
    //dCell(test,3,4) = M_PI;
    $d-test[3,4] = M_PI;
    Prnl;
    imprime_array_mt_3( SDS(test) );
    
    Free_total_array_mt(test);

End

void imprime_array_mt_3( MT_CELL *array, DS_ARRAY array_data ){
   
   All range for array;
   int i,j;
   Iterup ( row, array, i){
       Iterup ( col, array, j){
           Print_Cell( array, i,j ); if (j<Cols(array)-1) Print ",\t";
       }
       Prnl;
   }
}

