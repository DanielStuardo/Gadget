
/* MULTI_CAT
   La variable destino debe tener espacio para recibir los datos;
   de lo contrario, habrá un error feo de violación de segmento */

#include <gadget/gadget.h>

LIB_GADGET_START

Main
  String w="cadena", x="sin aporte";

  String v=Space(100);
  
  v = Multi_cat( v, w, " ", x, " aunque no se sabe si es ocultismo", NULL);
  Print "Cadena final: [%s]\n", v;
  
  v[0]='\0';
  Stack{
     Store ( v, Multi_cat(v, Upper(w), " <- ", Reverse(x), " y plop!", NULL ) );
  }
  Print "Cadena final: [%s]\n", v;
  
  Free secure v,w,x;

End
