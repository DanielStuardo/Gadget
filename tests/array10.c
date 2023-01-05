
#include <gadget/gadget.h>

LIB_GADGET_START


Main
   Fill array nt as int(5) with 100;

   nt = Delete_lst( pSDS(nt), 0 );
   nt = Delete_lst( pSDS(nt), 0 );
   nt = Delete_lst( pSDS(nt), 0 );
   nt = Delete_lst( pSDS(nt), 0 );
   nt = Delete_lst( pSDS(nt), 0 );
   nt = Delete_lst( pSDS(nt), 0 ); /* borro uno más de lo que hay*/
   
   int i;
   Iterator up i[0:1:nt_data.len]{
       Print "Valor = %d\n", $nt[i];
   }
   Free array nt;
   
End
