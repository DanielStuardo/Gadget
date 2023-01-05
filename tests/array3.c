
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); 

Main

   Array dNum as int (5,10); 

   int t, i, j;
   All range for dNum; /* establecer rangos para que pueda funcionar "Compute_for" */
   Compute_for ( dNum,i,j,
                 if( !Is_even(i) && Is_even(j)) t=100; else t=1;
                 $ dNum [i, j] = ceil(rand()%100) * t; 
               )
   Imprime_el_array( pSDS(dNum), "Imprimiendo todo el array original" );
   
   Print "\nCopiando la matriz INT a una matriz STRING...\n";

   New array sNum as string;
   
   /* copio todo, incluso los rangos locales */
   sNum = (char **)Copy_array( SMD( &sNum ), pSDS(dNum) );
   
   Range for sNum [ 1:2:Rows(sNum), 0:2:Cols(sNum)] ;
   
   if( sNum){
      Compute_for ( sNum, i,j, 
          Stack{
             Store ( Cell(sNum,i,j), Insert( $sNum[i, j],"Valor = ",1) ); 
          }Stack_off
      );
      
      Imprime_el_array( pSDS(sNum), "\nImprimiendo una sección de la matriz de String:" );
      
      Print "\nAhora será FLOAT, pero no convertirá los valores con strings...\n";
      New array x as float; 
      x = (float*)Copy_array( SMD( &x ), pSDS(sNum) );
      if(x){
         All range for x;
         Imprime_el_array( pSDS(x), "\nImprimiendo la matriz completa" );
         Free array x ;
      }
      Free str array sNum;

   }else{
      Msg_red("No fue posible hacer la copia...");
   }

   Free array dNum;
   
End

void Imprime_el_array( pRDS( void, X ), const char * msg ){ 
   
   int i,j;
   Print "%s:\n", msg;
   if( pType(X) == INTEGER ){
       Rescue_DS_ptr( int*, tmp, X);
       pIterup ( row, X, i){
           pIterup ( col, X, j){
              Print "%d", @tmp[i, j];
              if ( j < pCols(X)-1 ) 
                  Print ", ";
           }
           Prnl;
       }
   }else if( pType(X) == STRING ){
       Rescue_DS_ptr( char**, tmp, X);
       pIterup ( row, X, i){
           pIterup ( col, X, j){
              Print "%s", @tmp[i, j];
              if ( j < pCols(X)-1 ) 
                  Print ", ";
           }
           Prnl;
       }
   }else if( pType(X) == FLOAT ){
       Rescue_DS_ptr( float*, tmp, X);
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
