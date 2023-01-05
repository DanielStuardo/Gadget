
#include <gadget/gadget.h>

LIB_GADGET_START

char * get_url_own(){
   String r;
   Let( r, "http://www.google.cl");
   if(PILA_GADGET){
      Item_return_release(r);
   }
   return r;
}

Main
   Cls
   int flag  = REG_EXTENDED | REG_NEWLINE | REG_NOSUB;
   int T = 0;
   Str_init( R );
   Let( R, R_URLS );

   T = Regex_compile( R, flag );
   if( Is_regex(T) ){
      flag=0;
      Stack { 
         printf( "Url valida https://www.google.cl? %s\n", Regex_valid( get_url_own(),T, flag) ? "Si" : "No" );
      }Stack_off;
      
      printf( "Url valida https://www.google.cl/? %s\n", Regex_valid( "http://www.google.cl/",T, flag) ? "Si" : "No" );
      printf( "Url valida http://www.acm1pt.cl/index.aspx? %s\n", Regex_valid( "http://www.acm1pt.cl/index.aspx",T, flag) ? "Si" : "No" );
      printf( "Url valida ftps://anonomo.com.ar? %s\n", Regex_valid( "ftps://anonomo.com.ar",T, flag) ? "Si" : "No" );
      printf( "Url valida ftps://anonomo.com.ar/? %s\n", Regex_valid( "ftps://anonomo.com.ar/",T, flag) ? "Si" : "No" );
      printf( "Url valida https://www.com? %s\n", Regex_valid( "https://www.com",T, flag) ? "Si" : "No" );
      printf( "Url valida https://www.tata.com/index.html? %s\n", Regex_valid( "https://www.tata.com/index.html",T, flag) ? "Si" : "No" );
      printf( "Url valida https://www.com/index.html? %s\n", Regex_valid( "https://www.com/index.html",T, flag) ? "Si" : "No" );
   }else{
      printf("Error en la compilación!\n");
   }
   Free_secure( R );
   Regex_free( T );
End
