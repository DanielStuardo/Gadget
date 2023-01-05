
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String t;
   
   Stack{

       Store ( t, Pad_c (Str_tran_first(Upper("el as es un as medio asqueroso, pero es as" ),Upper("as"),Upper("burro")),' ',60) )
       Print "MSG = [%s]\n",t;

       Store ( t, Pad_c (Str_tran_last(Upper("el as es un as medio asqueroso, pero es as" ),Upper("as"),Upper("burro")),' ',60) )
       Print "MSG = [%s]\n",t;

       Store ( t, Pad_l (Str_tran_to(Upper("el as es un as medio asqueroso, pero es as" ),Upper("as"),Upper("burro"),2),' ',60) )
       Print "MSG = [%s]\n",t;

       Store ( t, Pad_r (Str_tran_all(Upper("el as es un as medio asqueroso, pero es as" ),Upper("as"),Upper("burro"),2),' ',60) )
       Print "MSG = [%s]\n",t;

       Store ( t, Pad_c (Str_tran_from_to(Upper("el as es un as medio asqueroso, pero es as" ),Upper("as"),Upper("burro"),2,2),' ',60) )
       Print "MSG = [%s]\n",t;

   }Stack_off

   Free secure t;
End
