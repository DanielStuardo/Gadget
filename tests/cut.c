
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String z="Esta cadena: será cortada : desde aquí", v,w;
   
   v = Cut(z, ':');
   Print "[%s]\n", v;
   w = Cutr(z, ':');
   Print "[%s]\n", w;

  /* aquí no es necesario limpiar las variables "v" y "w", porque
     tanto Store como Let y parecidas limpian la variable destino. */
   Stack{
      Store ( v, Cut(Upper(z), ':'));
      Store ( w, Reverse(Cutr(Reverse(z), ':')));
   } Stack_off;
   
   Print "[%s]\n", v;
   Print "[%s]\n", w;

   Free secure v, w;
   v = First_cut(z,':');
   Print "[%s]\n", v;
   w = Last_cut(z,':');
   Print "[%s]\n", w;

   Stack {
      Store ( v, First_cut(Upper(z), ':'));
      Store ( w, Last_cut(Upper(z), ':'));
      Print "[%s]\n[%s]\n", v,w;
   }
   Free secure z,v,w;
End
