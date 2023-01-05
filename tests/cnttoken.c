
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v="este mensaje será utilizado para contar tokens";
   
   Set_token_sep(' ');  // por defecto el separador es ","
   
   Print "El string: \"%s\" tiene: %d tokens\n", v, Count_tokens(v);
   Free secure v;
End
