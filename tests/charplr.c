
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String w,v="   Esto es un mensaje.....";
   long i = strlen(v);

   Print "V= [%s]\n", v;
   Stack{
      Store (w, Substr(Reverse(v), Char_posl(Reverse(v),'.'), i));
      Store (w, Upper(Substr(w, 0, strlen(w)-(strlen(w)-Char_posr(w,' ')))));
      Print "W= [%s]\n", w;
   }Stack_off
   
   Free secure v,w;
   
End
