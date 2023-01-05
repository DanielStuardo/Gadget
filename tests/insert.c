
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String w,v="María tenía un corderito";

   Print "V= [%s]\n", v;
   Stack{
      Store (w, Insert(Upper(v),Upper("mañoso "),Str_at("UN ",Upper(v))+3));
      Print "W= [%s]\n", w;
      Store (w, Insert(v,"dulzón",Str_at("corderito",v)+10));
      Print "W= [%s]\n", w;
   }Stack_off
   
   Free secure v,w;
   
End
