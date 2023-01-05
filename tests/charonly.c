
#include <gadget/gadget.h>

LIB_GADGET_START

#define CHAR_TO_PRESERVE  "0123456789abcdefghijklmnopqrstuvwxyz@."

Main
   String w,v="  \t acm$$1pt\033%@cachete\t.com\033\n";

   Print "V= [%s]\n", v;
   Stack{
      Store (w, Char_only(Trim(v),CHAR_TO_PRESERVE));
      Print "W= [%s]\n", w;
   }Stack_off
   
   Free secure v,w;
   
End
