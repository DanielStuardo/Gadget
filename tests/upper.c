
#include <gadget/gadget.h>

LIB_GADGET_START

char * Mayusculas( char * msg);

Main
   Str_init( w );
   Setf( msg,"María tenía un corderito\nmañoso y\netérico número %d",2001);
   if (!msg) {
       Msg_red("No hubo memoria para alojar un mensaje");
       Stop(1);
   }
   w = Mayusculas(msg);
   if(w){   
      printf("[%s]\n", w);
      Free_secure(w);
      printf("# Líneas: %d\n", Count_lines(msg));
      Free_secure(msg);
      
      w = Lower("MARÍA TENÍA UN CORDERITO MAÑOSO Y ETÉRICO");
      if( !w ){
         Msg_red("No hubo memoria para alojar un mensaje");
         Stop(1);
      }
      printf("[%s]\n", w);
      Str_init(p)
      p = Reverse( w ); 
      printf("REV:[%s]\n%d\n",p,p[0]);
      Free_secure(w);
      Free_secure(p);
   }else{
      Msg_red("No hubo memoria para alojar un mensaje");
      Free_secure(w);
   }
   
   String v = "mensaje mayusculizado", q;
   q = Space(150);
   Stack{
      Store( q, Multi_cat(q, Upper(v), " -> ", Upper(Reverse(v)), " y plop!", NULL ) );
      Store( v, Reverse(Upper(v)) );
   } Stack_off
   Print "MSG1: %s\n", q;
   Print "MSG2: %s\n", v;
   Free secure v, q;
   
End

char * Mayusculas( char * msg){
   char * buff = Upper(msg);
   return buff;
}
