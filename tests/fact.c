
#include <gadget/gadget.h>

LIB_GADGET_START

Main 

   int i;
   for ( i=0; i<=300; i+=50 )
       Print "!%d = %LF\n", i, Fact(i);

End
