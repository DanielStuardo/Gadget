
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); 

Main
 
   //Dim (10) as_str_array(s);
   Array s as string(10); 
   
   int i;
   
   All range for s ;
   Compute_for ( s, i, Let( s[i], "un mensaje cualquiera" ) );

   sAppend(s, "Se añade esto al array");       Throw ( Error_append );
   sAppend(s, "Se añade esto otro al array");  Throw ( Error_append );
   sAppend(s, "También se añade esto");        Throw ( Error_append );
   sAppend(s, "Y esto queda al final");        Throw ( Error_append );
   
   Reshape(s,(int)Len(s)/2,2); Throw ( Error );

   All range for s ;
   Imprime_el_array( pSDS( s), "\nImprimiendo el array reshapeado y modificado");
   Prnl;
   
   New array arreglo_clonado as string;
   
   arreglo_clonado = (char **)Clone_array( SMD(&arreglo_clonado), pSDS(s));
   
   Imprime_el_array( pSDS( arreglo_clonado ), "\nImprimiendo el array clonado");
   
   arreglo_clonado = (char **)Delete_col( pSDS(arreglo_clonado), 1 );
   
   All range for arreglo_clonado;
   Imprime_el_array( pSDS( arreglo_clonado ), "\nImprimiendo el array modificado (delete)");
   
   Fill array temporal as string( Rows(arreglo_clonado) ) with "insertado";
   arreglo_clonado = (char **)Insert_col( pSDS(arreglo_clonado), pSDS(temporal), 0 );
   
   All range for arreglo_clonado;
   Imprime_el_array( pSDS( arreglo_clonado ), "\nImprimiendo el array modificado (insert)");

   
/* area de excepciones */
   Exception( Error ){
      Msg_amber("No puedo continuar porque no pude reshapear el array");
   }
   Exception( Error_append ){
      Msg_amber("Hubo un problema añadiendo datos al array");
   }
   
   Free str array s, arreglo_clonado, temporal;

End

void Imprime_el_array( pRDS( void, X ), const char * msg ){ 
   
   int i,j;
   Print "%s:\n", msg;
   if( pType(X) == STRING ){
       Rescue_DS_ptr( char**, tmp, X);
       if ( tmp_data->dims == 1 ){
           pIterup ( row, tmp, i){
               Print "%s\n", @tmp[i];
           }

       }else if ( tmp_data->dims == 2 ){
           pIterup ( row, tmp, i){
               pIterup ( col, tmp, j){
                  Print "%s", @tmp[i, j];
                  if ( j < pCols(tmp)-1 ) 
                      Print ", ";
               }
               Prnl;
           }
       }
   }
}
