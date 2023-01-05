
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   Fill array x as float(10,5) with ceil(rand()%100);

   Do_it ( Print_if( Equal_arrays(SDS_ptr(x),SDS_ptr(y)),"%s", "Son tablas iguales\n","No son iguales\n");,
           Where ( New array y as float;),
           Then  ( y = Clone_array(SMD(&y), SDS_ptr(x)); ) )  

   Free array x,y;

   Prnl; Prnl;
   Fill array w as string(2,10) with "hola mundo!";
   
   Do_it ( Print_if( sw, "%s", "Son tablas iguales\n", "No son iguales\n" );,
           Where ( New array v as string;
                   int sw = 0; ),
           Then  ( v = Clone_array( SMD( &v ), SDS_ptr(w) );
                   Let( $w[1,1], "distinto" );
                   sw = Equal_arrays( SDS_ptr(w), SDS_ptr(v) ); 
                   Free str array v,w; ))
   
End


