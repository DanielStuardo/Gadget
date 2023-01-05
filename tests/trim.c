
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String r,s,t;
   
   Stack{
       Store ( r, Trim_r (Upper("    este mensaje será modificado    " )) )
       Print "MSG = [%s]\n",r;
       Store ( s, Trim_l (Reverse(Upper("    este mensaje será odasrever    " ))) )
       Print "MSG = [%s]\n",s;
       Store ( t, Trim (Upper("    este mensaje será modificado    " )) )
       Print "MSG = [%s]\n",t;
   }Stack_off

   Free secure r,s,t;
   
   Let( r, "     cadena con espacios     ");
   t = Trim(r);
   s = Upper(t);
   Print "MSG:[%s]\n", s;
   Free secure r,t, s;
End
