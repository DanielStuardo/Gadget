
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v="este mensaje será utilizado para contar tokens";
   
   Set_token_sep(' ');  // por defecto el separador es ","
   
   Print "El string: \"%s\" tiene: %d tokens\n", v, Count_tokens(v);

   int i=0;
   For each token t, v do
       //Stack{
          if( i % 2 ) {
             //Store( t, Upper(t) );
             Get_fn_let(t, Upper(t));
          }
       //}Stack_off
       Print "Token %d = %s\n", ++i, t;
   Next_token(t);
   
   Free secure v;
End
