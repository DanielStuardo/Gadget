
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String r,s,t;
   
   Stack{
       Store ( r, Pad_r (Upper("este mensaje será modificado" ),'.',60) )
       Print "MSG = [%s]\n",r;
       Store ( s, Pad_l (Reverse(Upper("este mensaje será modificado" )),'-',60) )
       Print "MSG = [%s]\n",s;
       //Store ( t, Str_tran(Upper("este mensaje será modificado" ),"MENSAJE","mero") )
       //Store ( t, Str_tran(Upper("este mensaje será modificado" ),"MENSAJE",Upper("mero")) )
       //Store ( t, Str_tran(Upper("este mensaje será modificado" ),Upper("mensaje"),"mero") )
       //Store ( t, Str_tran("este mensaje será modificado",Lower("MENSAJE"),"mero") )
       Store ( t, Pad_c (Str_tran(Upper("este mensaje será modificado" ),Upper("mensaje"),Upper("mero")),' ',60) )
       Print "MSG = [%s]\n",t;
   }Stack_off

   Free secure r,s,t;
   
   Let (r, "mensaje a padear");
   s = Pad_c(r,'|',50);
   Print "MSG = [%s]\n",s;
   Free secure r,s;
End
