
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v="......cadena a reemplazar los laterales%%%%%%%",w;
   Print "ORIG: [%s]\n", v;
   
   w = Lateral_replace(v,'%',' ',RIGHTREPL);
   String t; t = Lateral_replace(w,'.',' ',LEFTREPL);

   Print "[%s]\n", t;
   Free secure t;
   
   Stack { Store( w, Lateral_replace(Lateral_replace(Upper(v),'%','_',RIGHTREPL),'.','_',LEFTREPL)) ;
           Print "[%s]\n", w;
         } Stack_off;
   
   Free secure v,w;
End
