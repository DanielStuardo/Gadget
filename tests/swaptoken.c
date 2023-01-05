
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v="este mensaje será utilizado para contar tokens";
   
   Set_token_sep(' ');  // por defecto el separador es ","
   
   Print "El string: \"%s\" tiene: %d tokens\n", v, Count_tokens(v);

   Stack{
       Store( v, Mod_token( Mod_token( Mod_token( v,"Esta", 1), "oración",2 ), "utilizada", 4) );
   }Stack_off

   Print "[%s]\n", v;
   Stack {
       Store ( v, Swap_tokens(Upper(v), 2,7));
       Store ( v, Mod_token( v,"ORACIONES",7));
   }Stack_off
   
   Print "[%s]\n", v;
   
   int i=0;
   For each token t, v do
       if( i % 2 ) {
          //Get_fn_let(t, Lower(t));
          ++i;
          Continue_next_token(t);
       }
       Print "Token %d = %s\n", ++i, t;
   Next_token(t);
   
   Free secure v;
End
