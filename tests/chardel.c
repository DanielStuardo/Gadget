
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v="cara$$%%%cter\tes a b\033orrar",w;
   
   w = Char_del(v,"%\t\n\033$");
   Print "[%s]\n", w;
   
   Stack { Store( w, Char_del(Upper(v),"%\t\n\033$")) ;
           Print "[%s]\n", w;
           Store( w, Char_del(Upper(v),NULL)) ;
           Print "[%s]\n", w;
         } Stack_off;
   
   Free secure v,w;
End
