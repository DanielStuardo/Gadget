
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String w,v="María tenía un corderito que tenía hambre";

   Print "V= [%s]\n", v;
   Stack{
      Store (w, Replace(Upper(v),Upper("cocinaba"), Index_at(Upper(v),"TENÍA",2),strlen("TENÍA")));
      Print "W= [%s]\n", w;
      Free secure w;
   }Stack_off
   
   w = Replace(v,"cocinaba",Index_at(v,"tenía",1),strlen("tenía"));
   Print "W= [%s]\n", w;
   
   Free secure v,w;
   
End
