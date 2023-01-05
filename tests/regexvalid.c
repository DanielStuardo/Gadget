
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   int flag  = REG_EXTENDED | REG_NEWLINE | REG_NOSUB;
   int T = 0;
   String R;
 //  Let( R, "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
   Let( R, R_IPS );

   T = Regex_compile( R, flag );
   if( T >= 0){
      flag=0;
      printf( "IP valida 255.255.0.0? %s\n", Regex_valid( "255.255.0.0",T, flag) ? "Si" : "No" );
      printf( "IP valida 256.255.0.0? %s\n", Regex_valid( "256.255.0.0",T, flag) ? "Si" : "No" );
   }else{
      printf("Error en la compilación!\n");
   }
   Free secure R;
   Free regex T;
End
