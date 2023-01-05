
#include <gadget/gadget.h>

LIB_GADGET_START


Main
   Open_buffer;

   At 5,5; Print "Ingresa tu código: ";
   At 5,24;
   String code; //="AC-";
   
   Get_fn_let(code, Input ( code, 30 ) );
   
   At 6,5; Print "\nTexto ingresado: %s, len=%ld\n", code, strlen(code);
   
   At 8,5; Print "Ingresa tu código: ";
   At 8,24;
   Get_fn_let(code, Input ( code, 10 ) );
   At 9,5; Print "\nNuevo texto ingresado: %s, len=%ld\n", code, strlen(code);

  /* con size de buffer = 0, code != NULL*/
   At 11,5; Print "Ingresa tu código: ";
   At 11,24;
   Get_fn_let(code, Input ( code, 1 ) );
   At 12,5; Print "\nNuevo texto ingresado: %s, len=%ld\n", code, strlen(code);

  /* code = NULL y size buffer = 0*/
   Free secure code;
   At 14,5; Print "Ingresa tu código: ";
   At 14,24;
   Get_fn_let(code, Input ( code, 0 ) );
   At 15,5; Print "\nNuevo texto ingresado: %s, len=%ld\n", code, strlen(code);

   Free secure code;
   Close_buffer;
End


