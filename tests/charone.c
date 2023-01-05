
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String w,v="   EEEssstoo es    un mensaje......\n   y nooo seeeee ná";

   Print "V= [%s]\n", v;
   Stack{
      Store (w, Char_one(Trim(Upper(v))," ESO."));
      Print "W= [%s]\n", w;
      Store (w, Char_one(Trim(Upper(v)),NULL));
      Print "W= [%s]\n", w;
   }Stack_off
   
   Free secure v,w;
   
End
