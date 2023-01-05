
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   int flag  = REG_EXTENDED | REG_NEWLINE | REG_NOSUB;
   int T = 0;
   Str_init( R )
   Let( R, R_EMAILS );

   T = Regex_compile( R, flag );
   if( T >= 0){
      flag=0;
      printf( "Email valida acm1pt@loc? %s\n", Regex_valid( "acm1pt@loc",T, flag) ? "Si" : "No" );
      printf( "Email valida rm-correo@ab.cd.com? %s\n", Regex_valid( "rm-correo@ab.cd.com",T, flag) ? "Si" : "No" );
      printf( "Email valida rm_correo@ab.com? %s\n", Regex_valid( "rm_correo@ab.com",T, flag) ? "Si" : "No" );
   }else{
      printf("Error en la compilación!\n");
   }
   Free secure R ;
   Free regex  T ;
End
