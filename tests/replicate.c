
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String w;

   Stack{
       Store( w, Replicate(Upper("xyz"),10 ));
   }Stack_off;

   Print "msg stack : [%s]\n\n", w;
   Free secure w;
   w = Replicate("abc", 5);
   Print "msg normal: %s\n", w;

   Free secure w;
End
