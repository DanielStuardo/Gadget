#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String c;
   
   Fn_let( c, Get_sys("pidof aplay"));
   
   Print "[%s]Len = %ld\n", c, strlen(c);
   
   int n=system("pidof aplay"); // verificado in situ
   Print "msg system: %d\n",n;
   
   Free secure c;
   
End
