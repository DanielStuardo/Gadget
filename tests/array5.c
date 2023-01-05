
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); 

Main

   Fill array dNum as double(5,5) with rand()%100 / 1.0 ; 

   All range for dNum;
   Imprime_el_array( pSDS(dNum), "Imprimiendo todo el array" );
   Prnl;
   
   dNum = (double*)Delete_col( pSDS(dNum), 2);
   
   All range for dNum;
   Imprime_el_array( pSDS(dNum), "Le borré la columna 2" );
   Prnl;
   
   dNum = (double*)Delete_row( pSDS(dNum), 2);
   
   All range for dNum;
   Imprime_el_array( pSDS(dNum), "Le borré la fila 2" );
   Prnl;
   
   Free array dNum;
   
End

void Imprime_el_array( pRDS( void, X ), const char * msg ){ 
   
   int i,j;
   Print "%s:\n", msg;
   if( pType(X) == DOUBLE ){
       Rescue_DS_ptr( double*, tmp, X);
       pIterup ( row, X, i){
           pIterup ( col, X, j){
              Print "%.*f", 2, @tmp[i, j];
              if ( j < pCols(X)-1 ) 
                  Print ", ";
           }
           Prnl;
       }
   }
}
