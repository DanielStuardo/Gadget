
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String t;
   For_each_token (t, "palabra1,palabra2, palabra3, palabra4")

       String c;
       //Get_fn_let( c, Trim(t) );
       c = Trim(t);
       Print "Token: %s\n", c;
       Free secure c;
       
   Next_token (t)
   Free secure t;
End
