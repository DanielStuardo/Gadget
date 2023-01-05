
/* MULTI_COPY 
   la variable destino debe ser NULL */

#include <gadget/gadget.h>
LIB_GADGET_START

Main
  String w="cadena", x="sin aporte";

  String v;
  v = Multi_copy( v, w, " ", x, " aunque no se sabe si es ocultismo", NULL);
  Print "Cadena final: [%s]\n", v;
  
  Free secure v;
  Stack{
     Store ( v, Multi_copy(v, Upper(w), " <- ", Reverse(x), " y plop!", NULL ) );
  }
  Print "Cadena final: [%s]\n", v;
  
  Free secure v,w,x;

End
