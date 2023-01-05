
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String w,v="María tenía un corderito";

   Print "V= [%s]\n", v;
   Stack{
      Store (w, Delete(Upper(v),Str_at("tenía ",v),strlen("tenía ")));
      Print "W= [%s]\n", w;
      Free secure w;
   }Stack_off
   
   w = Delete(v,Str_at("tenía ",v),strlen("tenía "));
   Print "W= [%s]\n", w;
   
   Free secure v,w;
   
End
