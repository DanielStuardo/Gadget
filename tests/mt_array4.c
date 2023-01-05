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
        //iCell(test, 2, i) = ceil(rand()%100);  /* no tengo que cambiar el tipo inicial de la celda */
        $i-test [2, i] = ceil(rand()%100);
        Chg(test, double,3, i, sin( Radian(30+(i-1)) ) );
        Chg(test, long,  4, i, rand()%100000);
    } 
    
    imprime_array_mt_3( SDS(test) );

    /* añado una columna al final */
    New_mt_array(nueva_col);
    sAppend_mt(nueva_col,"head 5");
    Append_mt(nueva_col,float,0.0);
    Append_mt(nueva_col,int,0);
    Append_mt(nueva_col,double,0.0);
    Append_mt(nueva_col,long, 0L);

    test = Append_col_mt(pSDS(test), SDS(nueva_col));
    Prnl;
    imprime_array_mt_3( SDS(test) );
    
    /* añado más columnas al final */
    char head[10];
    for (i=6; i<10;i++){
        sprintf(head,"head %d",i);
        //Let ( sCell(nueva_col, 0), head );
        Let ( $s-nueva_col[ 0 ], head );
        test = Append_col_mt(pSDS(test), SDS(nueva_col));
    }
    Prnl;
    imprime_array_mt_3( SDS(test) );
    
    Free_total_array_mt(nueva_col);
    
    Free_total_array_mt(test);

End

void imprime_array_mt_3( MT_CELL *array, DS_ARRAY array_data ){
   
   All range for array;
   int i,j;
   Iterup ( row, array, i){
       Iterup ( col, array, j){
           Print_Cell( array, i,j ); if (j<Cols(array)-1) Print ", ";
       }
       Prnl;
   }
}

