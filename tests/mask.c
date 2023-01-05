
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v="12779670k",w;
   Print "ORIG: [%s]\n", v;
   
   w = Str_mask(v,"##.###.###-#"," ");
   Print "[%s]\n", w;
   
   Stack { Store( w, Str_mask(Upper(v),"##.###.###-#"," ")) ;
           Print "[%s]\n", w;
           Store( w, Str_mask("45660917","##.###.###-#"," ")) ;
           Print "[%s]\n", w;
         } Stack_off;
   
   Free secure v,w;
End
