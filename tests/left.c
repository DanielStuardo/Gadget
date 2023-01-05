
#include <gadget/gadget.h>
LIB_GADGET_START

Main

   String f, t;
   Let(f,"mañana encontraré vida extraterrestre");
   Print "Original : %s\n", f;
   
   t = Left( f, Str_at("vida", f)-1 );
   Cat(t, "un amor");
   printf("Modificado : %s\n", t);
   Free secure f,t;
End
