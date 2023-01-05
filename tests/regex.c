
#include <gadget/gadget.h>

LIB_GADGET_START

char * to_search(){
   String r;
   Letf( r, "Utf%d",8 );

   Item_return_release(r);
}

Main
   String /*r,*/ text;
   
   //Letf( r, "Utf%d",8 )

   if ( Exist_file("/home/dalien/Proyectos/HOPPER/jm/puzzle15.jambo") ){
      text = Load_string("/home/dalien/Proyectos/HOPPER/jm/puzzle15.jambo");
      if( text ){
         int flag = REG_EXTENDED;
         int T;

         Stack { T = Regex_compile( to_search(), flag); }
         if ( Is_regex ( T ) ){
            int numMatches = 1;  // cuántos matches se desea por pasada (granularidad)
            flag = 0;
            RE_MATCH * matches = Regex_match( text, T, numMatches, flag );
            if ( matches /*SIZE_MATCH*/ ){
               int i;
               For each match i, SIZE_MATCH do {
                  printf("Match nº %d:\n--Start = %d\n--End = %d\n--Text = %s\n\n",
                          i, matches[i].start, matches[i].finish, matches[i].match );
               }
               Free match  matches, SIZE_MATCH;
            }else{
               printf("No se encontró nada\n");
            }

         }else{
            printf("Error en la compilación!\n");
         }
         Free regex  T;
         Free secure text;
      }else{
         printf("No se pudo cargar el archivo\n");
      }
   }else{
      printf("No existe el archivo\n");
   }
   //Free secure r ;
End



