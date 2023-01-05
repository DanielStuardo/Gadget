
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String w,v="María tenía un corderito";

   Print "V= [%s]\n", v;
   Stack{
      Store (w, Replace(Upper(v),Upper("cocinaba"), Str_at("tenía",v),strlen("tenía")));
      Print "W= [%s]\n", w;
      Free secure w;
   }Stack_off
   
   w = Replace(v,"cocinaba",Str_at("tenía",v),strlen("tenía"));
   Print "W= [%s]\n", w;
   
   Free secure v,w;
   
End
