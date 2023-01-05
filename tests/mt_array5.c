#include <gadget/gadget.h>


LIB_GADGET_START

Main
   /* esto crea un array con posiciones enteras iniciales rellenos con ceros */
    Dim (7,5) as_mt_array(test);
    //New multitype tests;
    
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
    sChg(test,5,0, "fila 5" );
    sChg(test,6,0, "fila 6" );
    
    /* cuerpo */
    
    Range for test [ 1:1:Rows(test), 1:1:Cols(test)];
    int i;
    Iterup(col, test, i){
        Chg(test, float, 1, i, 185.0/(255.0+i));
        //iCell(test, 2, i) = ceil(rand()%100);  /* no tengo que cambiar el tipo inicial de la celda */
        $i-test [2, i] = ceil(rand()%100);
        Chg(test, double,3, i, sin( Radian(30+(i-1)) ) );
        Chg(test, long,  4, i, rand()%100000);
        char potencia[40];
        sprintf(potencia,"1.8213465987073e+%d", i*2);
        sChg(test, 5, i, potencia);
        sprintf(potencia,"1.8213465987073e-%d", i*2);
        sChg(test, 6, i, potencia);
    } 
    
    All range for test;
    DEC_PREC=13; /* para guardar, se debe convertir el numero a string. DEC_PREC establece
                    la precision de los decimales en dicha conversion */
    if ( Save_matrix_mt(SDS(test), "save_matrix.txt" ) ){
        String csys;
        csys = `cat save_matrix.txt`;
        Print "\nEsto se grabó en \"save_matrix.txt\":\n%s\n", csys;
        Free secure csys;
    }
    
    Free_total_array_mt(test);

End

