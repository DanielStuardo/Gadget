
#include <gadget/gadget.h>

LIB_GADGET_START

/*MT_CELL * Add_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int row, int col, ...){
   
   if( !Fld_data->len ){
       pAppend_mt( Fld, int, FIELD);  // tipo del objeto
       pAppend_mt( Fld, int, 1 ); // el primer campo
   }else{
       iCell(Fld, 1) = iCell(Fld, 1) + 1; // incrementa el total de campos
   }
   pAppend_mt( Fld, int, row);
   pAppend_mt( Fld, int, col);
   va_list va;
   va_start( va, col );
   char * cText = va_arg( va, char * );
   if ( cText ){
       psAppend_mt( Fld, cText );
   }else{
       psAppend_mt( Fld, "_" );
   }
   return Fld;
}

MT_CELL *  Replace_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int row, int col, const char * msg){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           int nElem = iCell(Fld,1);  // numero de campos existentes
           int i, pos;
           for (pos=2,i=0; i<nElem; pos+=3, i++){
               if( row == iCell(Fld,pos) && col == iCell(Fld,pos+1) ){
                   Let( sCell(Fld,pos+2), msg );
                   break;
               }
           }
       }else{
           Msg_red("No es un objeto FIELD");
       }
   }else{
       Msg_red("No hay campos declarados para reemplazar");
   }
   return Fld;
}


MT_CELL *  Clear_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int row, int col){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           int nElem = iCell(Fld,1);  // numero de campos existentes
           int i, pos;
           char tBuff[2]; tBuff[0]='\0';
           for (pos=2,i=0; i<nElem; pos+=3, i++){
               if( row == iCell(Fld,pos) && col == iCell(Fld,pos+1) ){
                   Let( sCell(Fld,pos+2), tBuff );
                   break;
               }
           }
       }else{
           Msg_red("No es un objeto FIELD");
       }
   }else{
       Msg_red("No hay campos declarados para limpiar");
   }
   return Fld;
}

MT_CELL *  Clear_all_field(MT_CELL * Fld, DS_ARRAY * Fld_data){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           int nElem = iCell(Fld,1);  // numero de campos existentes
           int i, pos;
           char tBuff[2]; tBuff[0]='\0';
           for (pos=4,i=0; i<nElem; pos+=3, i++){
               Let( sCell(Fld,pos), tBuff );
           }
       }else{
           Msg_red("No es un objeto FIELD");
       }
   }else{
       Msg_red("No hay campos declarados para limpiar");
   }
   return Fld;
}


char * Get_field(MT_CELL * Fld, DS_ARRAY *Fld_data, int posicion){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           int nElem = iCell(Fld,1);  // numero de campos existentes
           if ( posicion <0 || posicion > nElem-1 ){
               return NULL;
           }else{
               return (char*)sCell(Fld, 4 + (3 * posicion));
           }
       }else{
           Msg_red("No es un objeto FIELD");
       }
   }else{
       Msg_red("No hay campos declarados para limpiar");
   }
   return NULL;
}
*/
Main
  /*
     Un campo es una colección de datos string que se imprimirán en la ubicación declarada
     en un prinicipio.
     Si quiere almacenar un dato no-string, conviértalo a string antes de almacenar. GADGET
     tiene muchas funciones que le permitirán convertir cualquier cosa a string.
     Se pueden crear tantas colecciones de campos como se necesite.
     Se declaran como los objetos de MOUSE, pero no pertenecen a este contexto.
     De hecho, los campos son libres de contexto.
     Sirven para interactuar despliegues de datos ingresados o procesados, junto con 
     objetos VIDEO.

   TENGA EN CUENTA:
     Los campos se indexan por posición de acuerdo al orden en que fueron creados.
     
     El objeto FIELD es un objeto tipo MT_CELL, así como los objetos MOUSE, pero no son
     reconocidos por Object_mouse(), porque no es necesario.
  */
  
  /* abre un buffer de video.
     Esto, junto con otras funciones que despliegan caracteres Unicode, son compatibles
     con terminales compatibles con "xterm-256color". */
   Open_buffer;
   
   /* se crea una colección de campos llamada "fld"*/
   New object fld;
   
   /* se añaden dos campos */
   fld = Add_field( pSDS(fld), 10,15,"<campo-de-mensaje>"); /* campo 0 */
   fld = Add_field( pSDS(fld), 16,15,NULL);  /* campo 1 */

   /* imprimimos los campos */
   Put object fld;
      
   Pause();
   /* reemplazamos el contenido de ambos campos. ROW y COL permiten buscar
      el campo a modificar: */
   Cls;
   fld = Replace_field(pSDS(fld), 0 /*10,5*/,"Este es un mensaje");
   fld = Replace_field(pSDS(fld), 1 /*16,12*/,"10/10/2021");

   /* imprimimos los campos */
   Color(121,25);
   Put object fld;
   Reset_color;
   
   /* Get_field() devuelve un puntero al contenido del campo */
   char * v_campo = Get_field( pSDS(fld), 1 );
   if ( v_campo ){
       At 18,12; Print "Campo rescatado(1): %s", v_campo;
   }
   v_campo = Get_field( pSDS(fld), 0 );
   if ( v_campo ){
       At 19,12; Print "Campo rescatado(0): %s", v_campo;
   }
   Pause();

   Cls;
   /* limpia un campo.
      El campo limpiado no modificará el despliegue. Si usa objetos video, debe
      hacer un Refresh(), o Flush(). */
   fld = Clear_field(pSDS(fld), 0 /*10,5*/ );
   /* imprimimos los campos */
   Put object fld;

   Pause();
   
   Cls;
   /* limpia todos los campos.
      Misma consideración que la vista para Clear_field(). */
   fld = Clear_all_field(pSDS(fld));

   /* imprimimos los campos */
   Put object fld;
   
   /* liberamos el objeto "fld" */
   Free object fld;
   
   Pause();
   Close_buffer;
   
End
