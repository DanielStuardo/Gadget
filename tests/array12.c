
#include <gadget/gadget.h>

LIB_GADGET_START


Main
   Fill array nt as int(5,5) with 100;

   nt = Delete_row( pSDS(nt), 0 );
   nt = Delete_row( pSDS(nt), 0 );
   nt = Delete_row( pSDS(nt), 0 );
   nt = Delete_row( pSDS(nt), 0 );
   nt = Delete_row( pSDS(nt), 0 );
   nt = Delete_row( pSDS(nt), 0 ); /* borro uno más de lo que hay*/
   
   Print "SIZE : rows = %d, cols = %d\n", Rows(nt), Cols(nt);
   Assert( Rows(nt) && Cols(nt), excepcion_rango );
   
   All range for nt;
   int i,j;
   Iterator up i[0:1:Rows(nt)]{
       Iterator up j[0:1:Cols(nt)]{
          Print "Valor = %d\n", $nt[i,j];
       } Prnl;
   }
 Exception(excepcion_rango){
      Msg_red("El array está vacío");
   }
   Free array nt;
   
End
