#include <gadget/gadget.h>

LIB_GADGET_START

Main
   int l=0;
   Msg_yellow("¿Está la palabra \"juan\" en la frase \"La Juanita está linda\"?")
   
   if( (l=Occurs("juan", "La Juanita está linda" )) ){
       Msg_green("claro que está!");
       Print "En la posición: %d\n", l;
   }else{
       Msg_red("No encontró un match");
   }
   
   Msg_yellow("Pero, ¿está exactamente?");
   if( (l=Exact_occurs("juan", "La Junita está linda" )) ){
       Msg_green("encontró un match!");
       Print "posición: %d\n", l ;
   }else{
       Msg_red("No, no está exactamente");
       Msg_pink("Entonces, ¡no me venga con tonterías!")
   }
   
End
