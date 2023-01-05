
#include <gadget/gadget.h>
LIB_GADGET_START

char * cambia( char * var ){

   String retVal;
   Let(retVal, var);
   char * timenow = Get_time();
   Catf( retVal, " ha cambiado a las %s!", timenow);
   Free secure timenow;
   return retVal;

}

void otroCambio( char **var ){

   char * timenow = Get_time();
   Catf( *var, ", y ha cambiado otra vez a las %s!", timenow);
   Free secure timenow;

}

Main
   String msgFormato;

   Set( name, "Juanito Pérez" );

   Format( msgFormato, "Mensaje a [%*s], domiciliado en [%*s]",10,name,10,"Calle 7 S/N");
   if( 1 ){ Cat( msgFormato,", además, va con adjunto"); }
   printf( "%s\n",msgFormato);
   
   printf("Name = %s\n",name);

   Get_fn_let( name, cambia(name));
   printf("Name = %s\n",name);

   otroCambio( &name);
   printf("Name = %s\n",name);

   Setf( ultima_cadena, "Es muy lento: %d,%d",10,20);
   printf("len [%s] = %d\n", ultima_cadena, strlen(ultima_cadena));
   Free secure ultima_cadena, name, msgFormato ;
End
