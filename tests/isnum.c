
#include <gadget/gadget.h>
LIB_GADGET_START

Main
   String cnum;
   char * mensaje="Este es un mensaje\n";
   char * tipo[4]={"invalid",NULL,"integer","decimal"};
   
   int n=0;
   Let(cnum,"129.0");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }

   Let(cnum,"129");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }

   Let(cnum,"1");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }

   Let(cnum,"-129");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }
   
   Let(cnum,"0.00003223");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }
   
   Let(cnum,"-129.0");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }
   
   Let(cnum,"-0.000252");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }

   Let(cnum,"-0.0.00252");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %s\n",cnum,tipo[n]); }
   
   Let(cnum,".03233");
   if( (n=Is_number(cnum)) ) Print "%s es un número: %s\n",cnum,tipo[n]; else { Msg_redf("%s no es un número válido aquí %d",cnum,n); }

   Print "%s",mensaje;
   
   Print "Número %f\n", Str2dbl(cnum);
   
   Free secure cnum;
End
