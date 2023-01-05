
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); 

Main
 
   //Dim (10) as_str_array(s);
   Array s as string(10); 
   
   int i,j;
   
   All range for s ;
   Compute_for ( s, i, Let( s[i], "un mensaje cualquiera" ) );

   Imprime_el_array( pSDS( s), "\nImprimiendo el array string");
   
   sAppend(s, "Se añade esto al array");       Throw ( Error_append );
   sAppend(s, "Se añade esto otro al array");  Throw ( Error_append );
   sAppend(s, "También se añade esto");        Throw ( Error_append );
   sAppend(s, "Y esto queda al final");        Throw ( Error_append );
   
   Print "\nAppend no actualiza ROW ni COL, solo LEN...\nLen s = %d, Rows s = %d\n", Len(s), Rows(s);
   Rows(s) = Len(s);
   Print "\nROW actualizado (aunque no sirve de nada aquí)!\nLen s = %d, Rows s = %d\n", Len(s), Rows(s);
   
   Reshape(s,(int)Len(s)/2,2); Throw ( Error );
   
   All range for s;
   char oldTok = Set_new_sep(' ');
   Compute_for (s, i,j, 
             if(rand()%10 >5){
                Stack{
                   Store( $s[i,j], Mod_token( $s[i,j], Upper("profundo"), 3) );
                }Stack_off
             }
   ); Set_token_sep(oldTok);
                        
   Imprime_el_array( pSDS( s), "\nImprimiendo el array reshapeado y modificado");
   Prnl;
   
/* area de excepciones */
   Exception( Error ){
      Msg_amber("No puedo continuar porque no pude reshapear el array");
   }
   Exception( Error_append ){
      Msg_amber("Hubo un problema añadiendo datos al array");
   }
   
   Free str array s;
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
