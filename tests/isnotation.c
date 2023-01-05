
#include <gadget/gadget.h>
LIB_GADGET_START

Main
   String cnum;
   
   Let(cnum,"1.343E5");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }
   Print "Número '%s' = %ld\n", cnum,(long)StrE2dbl(cnum);
   Let(cnum,"1.343E-5");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }

   Let(cnum,"-9.343E15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }
   Let(cnum,"9.343e+15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }
   
   Let(cnum,"2E15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }

   Let(cnum,"1e15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }

   Let(cnum,"1.0e15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }

   Let(cnum,"1.0.45e15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }
   
   Let(cnum,"1.87509e15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }
   Print "Número '%s' = %lld\n", cnum,(long long)StrE2dbl(cnum);
   
   Let(cnum,".34e15");
   if( Is_notation(cnum) ) Print "%s es un número notacion\n",cnum; else { Msg_redf("%s no es un número notacion válido aquí",cnum); }


   double num = StrE2dbl(cnum);
   Print "Número '%s' = %f\n", cnum,num;
   Print "Número '2e-4' = %f\n",StrE2dbl("2e-4");
   
   Free secure cnum;
End
