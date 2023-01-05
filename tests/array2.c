
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); 

Main

   Array dNum as unsigned int (5,10); 

   int t, i, j;
   All range for dNum; /* establecer rangos para que pueda funcionar "Compute_for" */
   Compute_for ( dNum,i,j,
                 if( !Is_even(i) && Is_even(j)) t=100; else t=1;
                 $ dNum [i, j] = ceil(rand()%100) * t; 
               )
   
   // aun tiene los rangos locales declarados.
   Imprime_el_array( pSDS(dNum), "Imprimiendo todo el array" );
   Prnl;

  /* buscamos el valor máximo y el valor mínimo, solo columna por medio partiendo desde posicion 0 */
   Range for dNum [ 0:1:Rows(dNum), 0:2:Cols(dNum) ];
   DS_MAXMIN  maxNode = Max_array( pSDS(dNum) );
   Print "\nMayor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d\n\n", maxNode.row, maxNode.col;

   DS_MAXMIN  minNode = Min_array( pSDS(dNum) );
   Print "\nMenor numero (posicion dura) = %d\n", minNode.local;
   Print "Posicion fila: %d, col: %d\n\n", minNode.row, minNode.col;
   
   Free array dNum;
   
End

void Imprime_el_array( pRDS( void, X ), const char * msg ){ 
   
   int i,j;
   Print "%s:\n", msg;
   if( pType(X) == UINTEGER ){
       Rescue_DS_ptr( unsigned int*, tmp, X);
       pIterup ( row, X, i){
           pIterup ( col, X, j){
              Print "%d", @tmp[i, j];
              if ( j < pCols(X)-1 ) 
                  Print ", ";
           }
           Prnl;
       }
   }
}
