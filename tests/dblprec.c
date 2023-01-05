
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   /** argumento 0 es el nombre de archivo */
   if( Arg_count == 2 ){
       Get_arg_double(nDbl,1);
       Print "Argumento: %lf\n", nDbl;
   }
   double v=89049.27887340987765;
   int i;
   Print "Numero sin precision: %.*lf\n", 11,v;
   for (i=0;i<16;i++){
      Print "Precision %2d : %.*lf\n", i, 15, Dbl_prec(v,i);
   }
   String sv="9083.8763632844";
   v = Str2dbl(sv);
   Print "Double = %.*lf\n", 10,v;
   Free secure sv;
End
