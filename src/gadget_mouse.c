
/*********************************************************************************************

                            DEFINICIONES PARA USO BASICO DE MOUSE

 *********************************************************************************************/

#include "../include/gadget.h"

extern int MOUSE_EVENT;
extern int MPOS_ROW;
extern int MPOS_COL;
extern int ENABLE_MOUSE_DRIVER;

extern int Is_ok;
extern int SCREEN_ROW;
extern int SCREEN_COL;

extern int ACTIVE_TAB;
extern int ACTIVE_OPT;

void Clear_box(int row, int col, int alto, int ancho){
   int Hfill = ancho - col;
   int Vfill = alto + row;

   char *cfill = NULL;//Space( Hfill + 1 );
   Get_fn_let( cfill, Replicate(" ", Hfill) );

   char buffer[ Hfill * Vfill];
   int i, count_buffer=0;
   for ( i=row; i<Vfill; i++){
       char buf_fore[ Hfill * 2];
       int lnf = sprintf(buf_fore,"\x1b[%d;%dH%s",i,col,cfill);
       const char * pbf = buf_fore;
       memcpy((void *)buffer+count_buffer, pbf, lnf);
       count_buffer = count_buffer + lnf;
   }
   buffer[count_buffer]='\0';
   Free_secure(cfill);
   printf("%s",buffer);
}

MT_CELL * Add_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int row, int col, ...){
   
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
       char buffer[ strlen(cText) + 20 ];
       sprintf( buffer, "\033[38;5;239m%s\033[0m", cText );
       psAppend_mt( Fld, buffer ); //cText );
   }else{
       psAppend_mt( Fld, "_" );
   }
   return Fld;
}

MT_CELL *  Replace_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int posicion /*int row, int col*/, const char * msg){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           /*int nElem = iCell(Fld,1);  // numero de campos existentes
           int i, pos;
           for (pos=2,i=0; i<nElem; pos+=3, i++){
               if( row == iCell(Fld,pos) && col == iCell(Fld,pos+1) ){
                   Let( sCell(Fld,pos+2), msg );
                   break;
               }
           }*/
           if ( posicion <0 || posicion > iCell(Fld,1)-1 ){
               Msg_red("Replace_field: posición fuera de rango");
               return Fld;
           }else{
               Let( sCell(Fld, 4 + (3 * posicion)), msg );
               //return (char*)sCell(Fld, 4 + (3 * posicion));
           }
       }else{
           Msg_red("Replace_field: No es un objeto FIELD");
       }
   }else{
       Msg_red("Replace_field: No hay campos declarados para reemplazar");
   }
   return Fld;
}

char * Get_field(MT_CELL * Fld, DS_ARRAY *Fld_data, int posicion){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           int nElem = iCell(Fld,1);  // numero de campos existentes
           if ( posicion <0 || posicion > nElem-1 ){
               Msg_red("Get_field: posición fuera de rango");
               return NULL;
           }else{
               return (char*)sCell(Fld, 4 + (3 * posicion));
           }
       }else{
           Msg_red("Get_field: No es un objeto FIELD");
       }
   }else{
       Msg_red("Get_field: No hay campos declarados de donde obtener el dato");
   }
   return NULL;
}

MT_CELL *  Clear_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int posicion /*int row, int col*/){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           /*int nElem = iCell(Fld,1);  // numero de campos existentes
           int i, pos;
           char tBuff[2]; tBuff[0]='\0';
           for (pos=2,i=0; i<nElem; pos+=3, i++){
               if( row == iCell(Fld,pos) && col == iCell(Fld,pos+1) ){
                   Let( sCell(Fld,pos+2), tBuff );
                   break;
               }
           }*/
           if ( posicion <0 || posicion > iCell(Fld,1)-1 ){
               Msg_red("Clear_field: posición fuera de rango");
               return Fld;
           }else{
               char tBuff[2]; tBuff[0]='_'; tBuff[1]='\0';
               Let( sCell(Fld, 4 + (3 * posicion)), tBuff );
               //return (char*)sCell(Fld, 4 + (3 * posicion));
           }
       }else{
           Msg_red("Clear_field: No es un objeto FIELD");
       }
   }else{
       Msg_red("Clear_field: No hay campos declarados para limpiar");
   }
   return Fld;
}

MT_CELL *  Clear_all_field(MT_CELL * Fld, DS_ARRAY * Fld_data){
   if ( Fld_data->len ){
       if( iCell(Fld,0) == FIELD ){
           int nElem = iCell(Fld,1);  // numero de campos existentes
           int i, pos;
           char tBuff[2]; tBuff[0]='_'; tBuff[1]='\0';
           for (pos=4,i=0; i<nElem; pos+=3, i++){
               Let( sCell(Fld,pos), tBuff );
           }
       }else{
           Msg_red("Clear_all_field: No es un objeto FIELD");
       }
   }else{
       Msg_red("Clear_all_field: No hay campos declarados para limpiar");
   }
   return Fld;
}

MT_CELL * New_object_mouse( DS_ARRAY * array_data, int typeObject, ... ){

   New_mt_array(mObj);
   
   switch( typeObject ){
       case SELECT:{
           va_list va;
           va_start( va, typeObject );
           int selInit  = va_arg( va, int ); // extrae seleccion inicial
           char * cText = va_arg( va, char * ); // texto de la seleccion
           int row      = va_arg( va, int ); // posicion fila
           int col      = va_arg( va, int ); // posicion columna
           int nColorF  = va_arg( va, int ); // color texto
           int nColorB  = va_arg( va, int ); // color fondo
           va_end( va );

           Str_init(SD);  // enable
           Str_init(NI);  // disable
           Let( SD, cText);
           Let( NI, cText);
           
           int trow = row, nAtSelectArea=0;
           while ( Occurs("\n", SD ) ){
               if ( !nAtSelectArea ){  // busco asta donde puedo hacer clic si hay "\n"
                   nAtSelectArea = Str_at( "\n", SD );
               }
               char tmp[250];
               // enable
               sprintf(tmp,"\033[0m\033[%d;%dH\x1b[38;5;%dm\x1b[48;5;%dm",++trow, col+4, nColorF,nColorB);
               Get_fn_let(SD, Str_tran_first( SD, "\n", tmp ));
               // disable
               sprintf(tmp,"\033[0m\033[%d;%dH\x1b[38;5;247m\x1b[48;5;%dm",trow, col+4,nColorB);
               Get_fn_let(NI, Str_tran_first( NI, "\n", tmp ));
           }
           
           Append_mt(mObj, int, SELECT);
           Append_mt(mObj, int, selInit);
           sAppend_mt(mObj, SD);
           
           Append_mt(mObj, int, nAtSelectArea ? nAtSelectArea+7 : strlen(cText)+7 );
           Append_mt(mObj, int, row);
           Append_mt(mObj, int, col);
           sAppend_mt(mObj, NI);     // disable. 
           Append_mt(mObj, int, 1);  // habilitado
           Append_mt(mObj, int, nColorF);  // colorf
           Append_mt(mObj, int, nColorB);  // colorb

           Free_secure(SD);Free_secure(NI);
           array_data->len = mObj_data.len;
           array_data->dims = 1;
           break;
       }case BUTTOM:{

           va_list va;
           va_start( va, typeObject );
           char * cText = va_arg( va, char * ); // texto del boton
           int row      = va_arg( va, int ); // posicion fila
           int col      = va_arg( va, int ); // posicion columna
           int nColorF  = va_arg( va, int ); // color texto
           int nColorB  = va_arg( va, int ); // color fondo
           
           va_end( va );
           int lenText  = strlen(cText);
           
           Append_mt(mObj, int, BUTTOM);

          // Verifico hasta donde dejo area de clic:
          /* int toAreaClic = 0;
           const char * pText = cText;
           while ( *pText ){
              if ( *pText == '\n' ) break;
              ++pText; ++toAreaClic;
           }*/ 
         

           char tmp[50];
           sprintf(tmp,"\033[%d;%dH",row+1, col);
           
           char cColor[50];
           sprintf(cColor,"\x1b[38;5;%dm\x1b[48;5;%dm",nColorF,nColorB);
           char cReset[10];
           sprintf(cReset,"\033[0m");
           char cDisable[50];
           sprintf(cDisable,"\x1b[38;5;247m\x1b[48;5;%dm",nColorB);
           
         /* elabora boton principal */           
           Str_init(cBody);
           cBody = Multi_copy( cBody, tmp,cColor,"\u2502",cText,"\u2502",cReset,NULL);

           Str_init(updown);
           Str_init(SL); 
           SL = Space(2048);
           
           int cntUTF8=0;
           const char * p = cText;
           while ( *p ){
               if ( *p < 0 ) ++cntUTF8;
               ++p;
           }
           
           Get_fn_let( updown, Replicate("\u2500", (lenText - (int)(cntUTF8/2))/*lenText*/ ));
           //SL = Multi_copy( SL, tmp,"\u256d",updown,"\u256e",NULL); 
           //SD = Multi_copy( SD, tmp,"\u2570",updown,"\u256f",NULL);
           
           sprintf(tmp,"\033[%d;%dH",row, col);
           SL = Multi_cat( SL, tmp,cColor,"\u256d",updown,"\u256e",cReset,NULL);
           SL = Multi_cat( SL, cBody, NULL);
           sprintf(tmp,"\033[%d;%dH",row+2, col);
           SL = Multi_cat( SL, tmp,cColor,"\u2570",updown,"\u256f",cReset,NULL);
           
           //sAppend_mt(mObj, cBody);
           sAppend_mt(mObj, SL);

         /* elabora boton tocado */
           Free_secure( cBody );
           Free_secure( updown); Free_secure(SL);
           
           sprintf(tmp,"\033[%d;%dH",row+1, col);

           cBody = Multi_copy( cBody, tmp,cColor,"\033[1m\u2503",cText,"\u2503\033[22m",cReset,NULL);

           SL = Space(2048);
           
           Get_fn_let( updown, Replicate("\u2501", (lenText - (int)(cntUTF8/2)) /*lenText*/ ));
           
           sprintf(tmp,"\033[%d;%dH",row, col);
           SL = Multi_cat( SL, tmp,cColor,"\033[1m\u250f",updown,"\u2513\033[22m",cReset,NULL);
           SL = Multi_cat( SL, cBody, NULL);
           sprintf(tmp,"\033[%d;%dH",row+2, col);
           SL = Multi_cat( SL, tmp,cColor,"\033[1m\u2517",updown,"\u251B\033[22m",cReset,NULL);

           sAppend_mt(mObj, SL);
           
           /* elabora boton inactivo */
           Free_secure( cBody );
           Free_secure( updown); Free_secure(SL);
           
           sprintf(tmp,"\033[%d;%dH",row+1, col);

           cBody = Multi_copy( cBody, tmp,cDisable,"\u2502",cText,"\u2502",cReset,NULL);

           SL = Space(2048);
           
           Get_fn_let( updown, Replicate("\u2500", (lenText - (int)(cntUTF8/2)) ));
           
           sprintf(tmp,"\033[%d;%dH",row, col);
           SL = Multi_cat( SL, tmp,cDisable,"\u256d",updown,"\u256e",cReset,NULL);
           SL = Multi_cat( SL, cBody, NULL);
           sprintf(tmp,"\033[%d;%dH",row+2, col);
           SL = Multi_cat( SL, tmp,cDisable,"\u2570",updown,"\u256f",cReset,NULL);

           sAppend_mt(mObj, SL);
           //sAppend_mt(mObj, cBody );
           //Append_mt(mObj, int, 0);  // borrar

          /* resto de datos */
           Append_mt(mObj, int, (lenText - (int)(cntUTF8/2))/*lenText*/);
           Append_mt(mObj, int, row);
           Append_mt(mObj, int, col);
           Append_mt(mObj, int, row + 2);
           Append_mt(mObj, int, col + (lenText - (int)(cntUTF8/2))/*lenText*/ + 2);

           //sAppend_mt(mObj, SL);
           //sAppend_mt(mObj, SD);
           Append_mt(mObj, int, 1);   // habilitado

           Free_secure( updown); Free_secure(SL); // Free_secure(SD);
           Free_secure( cBody );
           
           
           array_data->len = mObj_data.len;
           array_data->dims = 1;
           
           break;
       }case BUTTOM_EYE: case BUTTOM_PINBALL: {
           va_list va;
           va_start( va, typeObject );
           char * cText = va_arg( va, char * ); // texto del boton
           int row      = va_arg( va, int ); // posicion fila
           int col      = va_arg( va, int ); // posicion columna
           int nColorF  = va_arg( va, int ); // color texto
           int nColorB  = va_arg( va, int ); // color fondo
           
           va_end( va );
           int lenText  = strlen(cText);
           if (typeObject==BUTTOM_EYE){
               Append_mt(mObj, int, BUTTOM_EYE);
           }else{
               Append_mt(mObj, int, BUTTOM_PINBALL);
           }

         /* elabora boton principal */
           char tmp[50];
           sprintf(tmp,"\033[%d;%dH",row, col);
           
           char cColor[50];
           sprintf(cColor,"\x1b[38;5;%dm\x1b[48;5;%dm",nColorF,nColorB);
           char cReset[10];
           sprintf(cReset,"\033[0m");
           char cDisable[50];
           sprintf(cDisable,"\x1b[38;5;247m\x1b[48;5;%dm",nColorB);
           
           int cntUTF8=0;
           const char * p = cText;
           while ( *p ){
               if ( *p < 0 ) ++cntUTF8;
               ++p;
           }
           
           Str_init(cBody);Str_init(cDisableBody);
           if (typeObject==BUTTOM_EYE){
               cBody = Multi_copy( cBody, tmp,cColor,"(",cText,")",cReset,NULL);
               cDisableBody = Multi_copy( cDisableBody, tmp,cDisable,"(",cText,")",cReset,NULL);
           }else{
               cBody = Multi_copy( cBody, tmp,cColor,"\u2308",cText,"\u2309",cReset,NULL);
               cDisableBody = Multi_copy( cDisableBody, tmp,cDisable,"\u2308",cText,"\u2309",cReset,NULL);
           }
           sAppend_mt(mObj, cBody);

         /* elabora boton tocado */  
           Free_secure( cBody );
           
           sprintf(tmp,"\033[%d;%dH",row, col);
           Str_init(updown);
           
           if (typeObject==BUTTOM_EYE){
               Get_fn_let( updown, Replicate("─", (lenText - (int)(cntUTF8/2)) /*lenText*/ ));
               cBody = Multi_copy( cBody, tmp,cColor,"\033[1m─",updown,"─\033[22m",cReset,NULL);
           }else{
               Get_fn_let( updown, Replicate("_", (lenText - (int)(cntUTF8/2)) /*lenText*/ ));
               cBody = Multi_copy( cBody, tmp,cColor,"\033[1m_",updown,"_\033[22m",cReset,NULL);
           }
           sAppend_mt(mObj, cBody);
           
           Free_secure(updown);Free_secure( cBody );
           
           Append_mt(mObj, int, (lenText - (int)(cntUTF8/2)) /*lenText*/ );
           Append_mt(mObj, int, row);
           Append_mt(mObj, int, col);
           Append_mt(mObj, int, col + (lenText - (int)(cntUTF8/2)) /*lenText*/ +1 );
           
           // enable:
           Append_mt(mObj, int, 1);
           sAppend_mt(mObj, cDisableBody);
           
           Free_secure( cDisableBody );
           
           array_data->len = mObj_data.len;
           array_data->dims = 1;
           
           break;
       }case RADIO_BUTTOM: {
           va_list va;
           va_start( va, typeObject );
           MT_CELL * arr = va_arg( va, MT_CELL * ); // array mt
           DS_ARRAY arr_data = va_arg( va, DS_ARRAY ); // metadata.
           int row      = va_arg( va, int ); // posicion fila
           int col      = va_arg( va, int ); // posicion columna
           int nColorF  = va_arg( va, int ); // color texto
           int nColorB  = va_arg( va, int ); // color fondo
           
           va_end( va );
           
           Append_mt(mObj, int, RADIO_BUTTOM);
           if ( arr_data.len % 2 ) {
               Msg_red("Opciones de RADIO_BUTTOM incompletas");
               return mObj;
           }
           
           Append_mt(mObj, int, (int)arr_data.len/2); // total opciones.
           /* hablitado/no habilitado*/
           Append_mt(mObj, int, 1 );
           /* colores */
           Append_mt(mObj, int, nColorF );
           Append_mt(mObj, int, nColorB );
           
           int i,j;
           for (j=0,i = 0; i<arr_data.len; j++,i+=2){
               Append_mt(mObj, int, row+j);
               Append_mt(mObj, int, col);
               Append_mt(mObj, int, col + strlen((char *)sCell(arr,i+1)));
               Append_mt(mObj, int, iCell(arr,i)); // estado de la opcion
               sAppend_mt(mObj, (char *)sCell(arr,i+1)); // mensaje de la opcion
           }
           array_data->len = mObj_data.len;
           array_data->dims = 1;
           break;
       }case TABS: {
           va_list va;
           va_start( va, typeObject );
           int row      = va_arg( va, int ); // posicion fila
           int col      = va_arg( va, int ); // posicion columna
           int alto     = va_arg( va, int ); // alto del tab
           int ancho    = va_arg( va, int ); // ancho del tab
           
           Append_mt(mObj, int, TABS);
           Append_mt(mObj, int, row);  // este valor indica posicion de las etiquetas. Caja = row+1.
           Append_mt(mObj, int, col);
           Append_mt(mObj, int, alto);
           Append_mt(mObj, int, ancho);
           Append_mt(mObj, int, 0);  // número de tabs: llenar a continuación
           
           int cntTabs=0;
           char * tabName=NULL;
           int lenTabName=0, tCol=col;
           tabName = va_arg( va, char * );
           while( tabName )
           {
              ++cntTabs;
              int cntUTF8=0;
              const char * p = tabName;
              while ( *p ){
                  if ( *p < 0 ) ++cntUTF8;
                  ++p;
              }
              
      //        Append_mt (mObj, int, row );
              Append_mt (mObj, int, tCol + 2 );
              lenTabName = strlen( tabName );
              Append_mt (mObj, int, tCol + 1 + (lenTabName - (int)(cntUTF8/2)) );
              sAppend_mt(mObj, tabName );
              tCol = tCol + /*lenTabName*/ (lenTabName - (int)(cntUTF8/2)) + 2;
              tabName = va_arg( va, char * );
           }
           va_end( va );
           iCell(mObj,5) = cntTabs; // actualizo la cantidad de tabs.
           /* ajusto ancho por si me quedo corto */
           if ( ancho < tCol-col ){
               iCell(mObj,4) = tCol;
           }
           
           array_data->len = mObj_data.len;
           array_data->dims = 1;
           break;

     }case CHOICE:{
           va_list va;
           va_start( va, typeObject );
           char ** cText = va_arg( va, char ** ); // array mt
           DS_ARRAY cText_data = va_arg( va, DS_ARRAY ); // metadata.
           int * valid  = va_arg( va, int* );  // validos
           DS_ARRAY valid_data = va_arg( va, DS_ARRAY ); 
           int row      = va_arg( va, int ); // posicion fila
           int col      = va_arg( va, int ); // posicion columna
           va_end( va );
           
           if( cText_data.len == valid_data.len ){
           
               Append_mt(mObj, int, CHOICE);
//               Append_mt(mObj, int, row);
//               Append_mt(mObj, int, col);
               Append_mt(mObj, int, cText_data.len); // numero de elementos del array de opciones
           
               int i;
               for(i = 0; i< cText_data.len; i++){
                   Append_mt(mObj, int, row+i);
                   Append_mt(mObj, int, col);
                   Append_mt(mObj, int, col + strlen(cText[i]) );
                   Append_mt(mObj, int, valid[i] );
                   sAppend_mt(mObj, cText[i] );
               }
           }else{
               Msg_red("Arrays de opciones de CHOICE son de tamaño diferente");
               return mObj;
           }
           array_data->len = mObj_data.len;
           array_data->dims = 1;
           break;
       }case CONTROL:{
           va_list va;
           va_start( va, typeObject );
           char * cText = va_arg( va, char * ); // texto de la seleccion
           int row      = va_arg( va, int ); // posicion fila
           int col      = va_arg( va, int ); // posicion columna
           int nColorF  = va_arg( va, int ); // color texto
           int nColorB  = va_arg( va, int ); // color fondo
           va_end( va );
           
           Append_mt(mObj, int, CONTROL);
                      
           char tmp[50];
           sprintf(tmp,"\033[%d;%dH",row, col);
           char cColor[50];
           sprintf(cColor,"\x1b[38;5;%dm\x1b[48;5;%dm",nColorF,nColorB);
           char cReset[10];
           sprintf(cReset,"\033[0m");
           char cDisable[50];
           sprintf(cDisable,"\x1b[38;5;247m\x1b[48;5;%dm",nColorB);

           int cntUTF8=0;
           const char * p = cText;
           while ( *p ){
              if ( *p < 0 ) ++cntUTF8;
              ++p;
           }
           
           Append_mt(mObj, int, 1);   // activo.
           Append_mt(mObj, int, row);
           Append_mt(mObj, int, col);
           Append_mt(mObj, int, col + strlen(cText) - ceil((double)cntUTF8/2.0));
           
           // control normal
           Str_init(SD);
           SD = Multi_copy( SD, tmp, cColor, cText, cReset, NULL);
           sAppend_mt(mObj, SD);
           Free_secure(SD);

           // control tocado 1m 22m, 7m, 27m
           SD = Multi_copy( SD, tmp, cColor,"\033[1m\033[7m", cText, "\033[27m\033[22m",cReset, NULL);
           sAppend_mt(mObj, SD);
           Free_secure(SD);
           
           // control inactivo
           SD = Multi_copy( SD, tmp, cDisable, cText, cReset, NULL);
           sAppend_mt(mObj, SD);
           Free_secure(SD);
           
           array_data->len = mObj_data.len;
           array_data->dims = 1;
           
           break;
       }
   }
   return mObj;
}

//Enable_object(menu,n); // segundo argumento ...
//Disable_object(menu,n);
//Change_text(submenu_archivo,n,"...");

int Status_object( MT_CELL* mObj ){
   int retVal=1;
   switch( iCell(mObj,0) ){
       case SELECT:{
           retVal = iCell(mObj,7);
           break;
       }
       case BUTTOM:{
           retVal = iCell(mObj,9);
           break;
       }
       case BUTTOM_EYE: case BUTTOM_PINBALL:{
           retVal = iCell(mObj,7);
           break;
       }
       case RADIO_BUTTOM:{
           retVal = iCell(mObj,2);
           break;
       }
       case CONTROL:{
           retVal = iCell(mObj,1);
           break;
       }
   }   
   return retVal;
}

int Disable_object( MT_CELL* mObj ){
   int retVal=1;
   switch( iCell(mObj,0) ){
       case SELECT:{
           iCell(mObj,7) = 0;
           break;
       }
       case BUTTOM:{
           iCell(mObj,9) = 0;
           break;
       }
       case BUTTOM_EYE: case BUTTOM_PINBALL:{
           iCell(mObj,7) = 0;
           break;
       }
       case RADIO_BUTTOM:{
           iCell(mObj,2) = 0;
           break;
       }
       case CONTROL:{
           iCell(mObj,1) = 0;
           break;
       }
   }
   return retVal;
}

int Enable_object( MT_CELL* mObj ){
   int retVal=1;
   switch( iCell(mObj,0) ){
       case SELECT:{
           iCell(mObj,7) = 1;
           break;
       }
       case BUTTOM:{
           iCell(mObj,9) = 1;
           break;
       }
       case BUTTOM_EYE: case BUTTOM_PINBALL:{
           iCell(mObj,7) = 1;
           break;
       }
       case RADIO_BUTTOM:{
           iCell(mObj,2) = 1;
           break;
       }
       case CONTROL:{
           iCell(mObj,1) = 1;
           break;
       }

   }
   return retVal;
}

int Status_item_menu(  MT_CELL* mObj, int item ){
   int retVal=0;
   --item;
   if( iCell(mObj, 0 ) == CHOICE ){
      if ( item >= 0 && item < iCell(mObj, 1) ){
         retVal = iCell(mObj, 5 + (item*5) );
      }else{
         char items[20];
         sprintf(items,"(%d - %d)",1,iCell(mObj, 1) );
         Msg_redf("Status_item_menu: item fuera de rango %s",items);
         retVal=-1;
      }
   }else{
      Msg_red("Status_item_menu: no es un menu CHOICE");
      retVal=-1;
   }
   return retVal;
}

int Enable_item_menu( MT_CELL* mObj, int item ){
   int retVal=1;
   --item;
   if( iCell(mObj, 0 ) == CHOICE ){
      if ( item >= 0 && item < iCell(mObj, 1) ){
         iCell(mObj, 5 + (item*5) ) = 1;
      }else{
         char items[20];
         sprintf(items,"(%d - %d)",1,iCell(mObj, 1) );
         Msg_redf("Enable_item_menu: item fuera de rango %s",items);
         retVal=-1;
      }
   }else{
      Msg_red("Enable_item_menu: no es un menu CHOICE");
      retVal=0;
   }
   return retVal;
}

int Disable_item_menu( MT_CELL* mObj, int item ){
   int retVal=1;
   --item;
   if( iCell(mObj, 0 ) == CHOICE ){
      if ( item >= 0 && item < iCell(mObj, 1) ){
         iCell(mObj, 5 + (item*5) ) = 0;
      }else{
         char items[20];
         sprintf(items,"(%d - %d)",1,iCell(mObj, 1) );
         Msg_redf("Disable_item_menu: item fuera de rango %s",items);
         retVal=-1;
      }
   }else{
      Msg_red("Disable_item_menu: no es un menu CHOICE");
      retVal=0;
   }
   return retVal;
}

int Change_item_menu( MT_CELL* mObj, const char *nuevo_item, int item ){
   int retVal=1;
   --item;
   if( iCell(mObj, 0 ) == CHOICE ){
      if ( item >= 0 && item < iCell(mObj, 1) ){
         Let( sCell(mObj, 6 + (item*5) ), nuevo_item ) ;
      }else{
         char items[20];
         sprintf(items,"(%d - %d)",1,iCell(mObj, 1) );
         Msg_redf("Change_item_menu: item fuera de rango %s",items);
         retVal=-1;
      }
   }else{
      Msg_red("Change_item_menu: no es un menu CHOICE");
      retVal=0;
   }   
   return retVal;
}

int Object_mouse( MT_CELL* mObj ){
   int retVal=0;
   switch( iCell(mObj,0) ){
       case SELECT: {
          if ( iCell(mObj,7) ){
              if ( Is_between( MPOS_COL, iCell(mObj,5),iCell(mObj,3) ) ){
                  if ( MPOS_ROW == iCell(mObj,4) ) {
                      iCell(mObj, 1) = iCell(mObj, 1) ? 0 : 1;
                      retVal = 1;
                  }
              }
          }
          break;
       }case BUTTOM: {
          if ( iCell(mObj,9) ){
              if ( Is_range_box(iCell(mObj,5),iCell(mObj,6),iCell(mObj,7),iCell(mObj,8)) ){
                  printf("%s", (char *)sCell(mObj,2)); Flush_out;
                  usleep(100000);
                  printf("%s", (char *)sCell(mObj,1)); Flush_out;
                  retVal = 1;
              }
          }
          break;
       }case BUTTOM_EYE: case BUTTOM_PINBALL: {
          if ( iCell(mObj,7) ){
              if ( Is_range_mouse(iCell(mObj,4),iCell(mObj,5),iCell(mObj,6)) ){
                  printf("%s", (char *)sCell(mObj,2)); Flush_out;
                  usleep(100000);
                  printf("%s", (char *)sCell(mObj,1)); Flush_out;
                  retVal = 1;
              }
          }
          break;
       }case RADIO_BUTTOM: {
          
          int enable=iCell(mObj,2);
          
          int totOptions = iCell(mObj,1);
          
          int optSel = 0;
          int i,j;
          if (enable){
              for( j=5, i=1; i<=totOptions; j+=5,i++ ){
                  if ( Is_range_mouse( iCell(mObj,j), iCell(mObj,j+1), iCell(mObj,j+2) ) ){
                      iCell(mObj,j+3) = -1;
                      retVal=i; //iCell(mObj, i);
                      optSel = j+3;
                      break;
                  }
              }
          }
          if( optSel && enable ){
              /* cambia las otras opciones a deseleccioado */
               for( j=8, i=1; i<=totOptions; j+=5,i++ ){
                   if ( iCell(mObj,j) > 0 ){
                       iCell(mObj,j) = 0;
                   }
               }
               iCell(mObj,optSel) = 1;
          }else{  // devuelve la opcion ya escogida
               for( j=8, i=1; i<=totOptions; j+=5,i++ ){
                   if ( iCell(mObj,j) ){
                       retVal = i; ///iCell(mObj,j);
                       break;
                   }
               }
          }
//          }
          break;
       }case TABS:{
          int i, tcol;
          for (tcol=6,i=0; i< iCell(mObj,5) /*nTabs*/; tcol+=3, i++){
              //if ( Is_range_mouse( iCell(mObj,1)+1, iCell(mObj,tcol), iCell(mObj,tcol+1) ) ){
              if ( Is_range_box( iCell(mObj,1), iCell(mObj,tcol), iCell(mObj,1)+1, iCell(mObj,tcol+1) ) ){
                  if ( ACTIVE_TAB != i ){
                      ACTIVE_TAB=i;
                      retVal = ACTIVE_TAB;
                      Put_object_mouse(mObj);
                      break;
                  }
              }
          }
          
          break;
       }case CHOICE:{
          int i;
          for(i=0; i< iCell(mObj, 1); i++){
              if( iCell(mObj, 5 + (i*5) ) ){
                  if( Is_range_mouse( iCell(mObj, 2 + (i*5) ), iCell(mObj, 3 + (i*5) ), iCell(mObj, 4 + (i*5) )) ){
                      ACTIVE_OPT = i+1;
                      retVal = ACTIVE_OPT;
                      printf( "\x1b[%d;%dH\x1b[38;5;0m\x1b[48;5;15m%s", iCell(mObj, 2 + (i*5) ),
                      iCell(mObj, 3 + (i*5) ), (char*) sCell(mObj, 6 + (i*5) ));
                      Flush_out;
                      usleep(200000);
                      break;
                  }
              }
          }
          Reset_color;
          break;
       }case CONTROL:{
          if ( iCell(mObj,1) ){
              if ( Is_range_mouse(iCell(mObj,2),iCell(mObj,3),iCell(mObj,4)) ){
                  printf("%s", (char *)sCell(mObj,6)); Flush_out;
                  //usleep(100000);
                  //printf("%s", (char *)sCell(mObj,5)); Flush_out;
                  retVal = 1;
              }
          }
          break;
       }
   }
   return retVal;
}

void Put_object_mouse( MT_CELL * mObj ){
   switch( iCell( mObj, 0 ) ){
       case SELECT:{
           Goto_xy( iCell(mObj,4), iCell(mObj,5));
           if ( iCell(mObj,7) ){
               printf("\x1b[38;5;%dm\x1b[48;5;%dm❲%s❳ %s\033[0m", iCell(mObj,8),iCell(mObj,9),
                      (iCell(mObj,1) ? "\u2714":" "), (char *)sCell(mObj,2) );
           }else{
               printf("\x1b[38;5;247m\x1b[48;5;%dm❲%s❳ %s\033[0m", iCell(mObj,9),
                      (iCell(mObj,1) ? "\u2714":" "), (char *)sCell(mObj,6) );
           }
           Flush_out;
           break; 
       }
       case BUTTOM: {
           if ( iCell(mObj,9) ){
               printf("%s", (char *)sCell(mObj,1)); Flush_out;
           }else{
               printf("%s", (char *)sCell(mObj,3)); Flush_out;
           }
           break;
       }
       case BUTTOM_EYE: case BUTTOM_PINBALL:{
           if ( iCell(mObj,7) ){
               printf("%s", (char *)sCell(mObj,1)); Flush_out;
           }else{
               printf("%s", (char *)sCell(mObj,8)); Flush_out;
           }
           break;
       }

       case RADIO_BUTTOM:{
           int totOptions = iCell(mObj,1);
           int i,j;
           char  cursor[40];
           Str_init(buffer);
           buffer=Space(512);
           int enable=iCell(mObj,2);
           Color_fore( enable ? iCell(mObj,3) : 247);
           Color_back( iCell(mObj,4) );

           for( j=5, i=0; i<totOptions; j+=5,i++ ){
               //Goto_xy( iCell(mObj,j), iCell(mObj,j+1));
               sprintf(cursor,"\033[%d;%dH%s ",iCell(mObj,j), iCell(mObj,j+1),(iCell(mObj,j+3) ? "\u25c9" : "\u25cb"));
               buffer = Multi_cat( buffer, cursor, (char *)sCell(mObj,j+4), NULL);
               //sprintf(buffer,"%s%s%s",buffer, (iCell(mObj,j+3) ? "\u25c9" : "\u25cb"), (char *)sCell(mObj,i+4));
           }
           printf("%s\033[0m", buffer); Flush_out;
           //Reset_color;
           Free_secure(buffer);
           
           break;
       }
       case TABS:{
           int row = iCell(mObj,1);
           /*int col = iCell(mObj,2);
           int alto = iCell(mObj,3);
           int ancho = iCell(mObj,4);
           int nTabs = iCell(mObj,5);
           Clear_box(row, col, alto, ancho );
           Goto_xy(row+1,col); Box_std(alto, ancho, SING_ALL);*/
           Clear_box(row, iCell(mObj,2), iCell(mObj,3), iCell(mObj,4) );
           Goto_xy(row+1,iCell(mObj,2)); Box_std(iCell(mObj,3), iCell(mObj,4), SING_ALL);

           int i;
           int tcol = 6;
           for (i=0; i< iCell(mObj,5) /*nTabs*/; i++){
               printf("\033[%d;%dH╒%s╕",row,iCell(mObj,tcol)-1,(char*)sCell(mObj,tcol+2));
               printf("\033[%d;%dH┴\033[%d;%dH┴",row+1,iCell(mObj,tcol)-1,row+1,iCell(mObj,tcol+1)+1);
               tcol += 3;
           }
           /* ver tab activo y modificar box */
           int blanco = 6 + (3 * ACTIVE_TAB);
           int rango = iCell(mObj,blanco+1) - iCell(mObj,blanco) + 1;
           char *borra = Space(rango*2 +1);
           //memset((void *)borra, 32, rango);
           Get_fn_let(borra, Replicate("═",rango));
           printf("\033[%d;%dH%s\033[%d;%dH┘\033[1m%s\033[22m└",row, iCell(mObj,blanco), borra, 
                                                 row+1,iCell(mObj,blanco)-1, (char*)sCell(mObj,blanco+2));
           Flush_out;
           Free_secure(borra);
           break;
       }
       case FIELD:{
           int nElem = iCell(mObj,1);
           int i,j;
           char  cursor[40];
           Str_init(buffer);
           buffer=Space(2048);
           for( j=2, i=0; i<nElem; j+=3,i++ ){
               sprintf(cursor,"\033[%d;%dH",iCell(mObj,j), iCell(mObj,j+1));
               buffer = Multi_cat( buffer, cursor, (char *)sCell(mObj,j+2), NULL);
           }
           printf("%s", buffer); Flush_out;
           Free_secure(buffer);
           break;
       }
       case CHOICE:{
           int i;
           for(i=0; i< iCell(mObj, 1); i++){
               if( iCell(mObj, 5 + (i*5) ) ){
                   printf( "\x1b[%d;%dH\x1b[38;5;232m\x1b[48;5;247m%s", iCell(mObj, 2 + (i*5) ),
                       iCell(mObj, 3 + (i*5) ), (char*) sCell(mObj, 6 + (i*5) ));
               }else{
                   printf( "\x1b[%d;%dH\x1b[38;5;240m\x1b[48;5;247m%s", iCell(mObj, 2 + (i*5) ),
                       iCell(mObj, 3 + (i*5) ), (char*) sCell(mObj, 6 + (i*5) ));
               }
               Reset_color;
               Flush_out;
           }
           break;
       }
       case CONTROL:{
          if ( iCell(mObj,1) ){
              printf("%s", (char *)sCell(mObj,5)); Flush_out;
          }else{
              printf("%s", (char *)sCell(mObj,7)); Flush_out;
          }
           break;
       }
   }
   
}

int __Universal_mouse_handler__(Gpm_Event *event, void *data){
   int nEvent=0;
   if(event->type & GPM_DOWN){
       if(event->buttons & GPM_B_LEFT){
            nEvent=event->buttons & GPM_B_LEFT;
       }
       if(event->buttons & GPM_B_RIGHT){
            nEvent=event->buttons & GPM_B_RIGHT;
       } 
       if(event->buttons & GPM_B_MIDDLE){
            nEvent=event->buttons & GPM_B_MIDDLE;
       }
       MPOS_ROW=event->y;
       MPOS_COL=event->x;
       MOUSE_EVENT = nEvent*10000;
       return MOUSE_EVENT;
   }
   return 0;
}

int Init_mouse(Gpm_Connect * conn){
    if (!ENABLE_MOUSE_DRIVER){
        conn->eventMask = ~0; /* Want to know about all the events */
        conn->defaultMask = 0; /* don't handle anything by default */
        conn->minMod = 0; /* want everything */ 
        conn->maxMod = ~0;

        if(Gpm_Open(conn, 0) == -1) return 0;
        
        gpm_handler = __Universal_mouse_handler__;

        ENABLE_MOUSE_DRIVER=1;
    }
    return 1;
}

int Get_event_mouse(){
    return Gpm_Getc(stdin);
}

void Close_mouse(){
    Gpm_Close();
}

