
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v = "MENSAJE MINUSCULIZADO", q;
   q = Space(150);
   Stack{
      Store( q, Multi_cat(q, Lower(v), " -> ", Lower(Reverse(v)), " y plop!", NULL ) );
      Store( v, Reverse(Lower(v)) );
   } Stack_off
   Print "MSG1: %s\n", q;
   Print "MSG2: %s\n", v;
   Free secure v, q;

End
