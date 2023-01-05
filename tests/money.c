
#include <gadget/gadget.h>

LIB_GADGET_START

#define DECIMALS   2
Main
   double v=1298323.478;
   Print "ORIG: [%lf]\n", v;
   
   String w;
   w = Str_money(v,DECIMALS);
   Print "[%s]\n", w;
   
   Free secure w;
   Stack { Store( w, Multi_copy(w,"Sueldo: $ ",Str_money(v*10,DECIMALS-DECIMALS),NULL)) ;
           Print "[%s]\n", w;
         } Stack_off;
   
   Free secure w;
End
