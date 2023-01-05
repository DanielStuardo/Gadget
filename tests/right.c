
#include <gadget/gadget.h>
LIB_GADGET_START

Main
   
   String f,t;
   Let(f,"mañana encontraré vida extraterrestre");
   Print "Original : %s\n", f;
   
   t = Right( f, Index_at(f,"vida",1));
   printf("modificado : %s\n", t);
   Free secure f,t;

End
