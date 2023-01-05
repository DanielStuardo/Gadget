
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); 

Main

   //Dim (5,10) as_array(dNum, double); <--- esto ------+
   Array dNum as double(5,10);  // esto convierte a-----+

   int t, i, j;
   All range for dNum; /* establecer rangos para que pueda funcionar "Compute_for" */
   Compute_for ( dNum,i,j,
                 if( !Is_even(i) && Is_even(j)) t=100; else t=1;
                 $ dNum [i, j] = ceil(rand()%100) * t; 
               )
   
   // aun tiene los rangos locales declarados.
   Imprime_el_array( pSDS(dNum), "Imprimiendo todo el array" );
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
