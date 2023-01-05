
#include <gadget/gadget.h>

LIB_GADGET_START

Main 

   String sn="1.4538e+100";
   
   Print "sn   = %s\n", sn;
   Print "Dbl  = %lf\n", StrE2dbl(sn);
   
   String h;
   h = Dbl2str(StrE2dbl(sn));
   Print "to Str = %s\n",h;
   Free secure h;
   h = Num2notation(StrE2dbl(sn));
   Print "to Notat = %s\n",h;
   Free secure h;
   
   Print "Long = %lld\n", StrE2llng(sn); 
   
   Free secure sn;
   
   double n=5789347957945734501342.2323;
   sn = Num2notation(n);
   Print "N = %lf\nNotation = %s\n",n, sn;
   Print "StrE2ldbl = %Lf\n", StrE2ldbl(sn);
   Free secure sn;
End
