

/************************************************************************
 *
 *                LIBRERIA DE ACCESO A VIDEO.
 *
 ************************************************************************/

#include "../include/gadget.h"

extern int VID_ACTUAL_ROW, VID_ACTUAL_COL;
extern int ENABLE_RAW_MODE;
extern int SCREEN_ROW, SCREEN_COL;
extern int SIZE_TERM_ROWS, SIZE_TERM_COLS;

extern int PILA_GADGET;
extern int CONTADOR_PILA;
extern char ** pila_de_trabajo;


void Init_video( GD_VIDEO * video /*, int rows, int cols*/){
   
   /* obtiene el tamaño de la terminal */
   Get_size_terminal();
   
   int rows = SIZE_TERM_ROWS;
   int cols = SIZE_TERM_COLS;
   
   video->video_rows = rows;
   video->video_cols = cols;
   /* declaro el doble de espacio, por si lo impreso más los carcateres de escape
      superan el máximo de la pantalla. */
   video->video_mem = (unsigned char *) calloc(rows * cols * 5+1, 1);
   video->count_buffer=0;
/*   video->video_color = ( int **) calloc( rows*cols, sizeof( int*));
   video->video_color[ 0 ] = (unsigned int *) calloc( cols, sizeof(unsigned int) );
   for(int i = 0; i < rows*cols; ++i)
   {
       video->video_color[i] = (int *)calloc(3, sizeof(int));
       video->video_color[i][0] = 0;
       video->video_color[i][1] = 0;
       video->video_color[i][2] = 0;
   }*/
   //video->video_color = (int *) malloc(rows * cols+1);
   //for(int i=0; i< rows*col; i++)
   //    video->video_mem
//   video->count_color=0;
   //memset((void *)video->video_color, 0, rows*cols*3);
   memset((void *)video->video_mem, ' ', rows*cols*5-1);
   video->video_mem[0]='\0';
   
   VID_ACTUAL_ROW=0; VID_ACTUAL_COL=0;

}

void Text_background(GD_VIDEO * video, int nColor){
   char buf_back[70];
   int lnf = sprintf(buf_back,"\x1b[48;5;%dm",nColor);
   const char * pbf = buf_back;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
}

void Text_color(GD_VIDEO * video, int nColor){
   char buf_fore[70];
   int lnf = sprintf(buf_fore,"\x1b[38;5;%dm",nColor);
   const char * pbf = buf_fore;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
}

void _Reset_text_(GD_VIDEO * video){
   memcpy((void *)video->video_mem+video->count_buffer, "\x1b[0m", 4);
   
   video->count_buffer = video->count_buffer + 4;
}

void Printvid_str(GD_VIDEO * video, const char * msg){
   const char *buffer = msg;
   int lnf = strlen(buffer);
   memcpy((void *)video->video_mem+video->count_buffer, buffer, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
}

void Printvid_c(GD_VIDEO * video, const char * msg, int nColor){
   const char *buffer = msg;
   
   char buf_fore[video->video_rows * video->video_cols];
   int lnf = sprintf(buf_fore,"\x1b[38;5;%dm%s",nColor,buffer);
   const char * pbf = buf_fore;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
}

void Printvid_xy(GD_VIDEO * video, int row, int col, const char * msg){
   const char *buffer = msg;
   
   char buf_fore[video->video_rows * video->video_cols];
   int lnf = sprintf(buf_fore,"\x1b[%d;%dH%s",row,col,buffer);
   const char * pbf = buf_fore;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
}

void Printvid_all(GD_VIDEO * video, int row, int col, const char * msg, int nColor){
   const char *buffer = msg;
   
   char buf_fore[video->video_rows * video->video_cols];
   //int lnf = sprintf(buf_fore,"\x1b[%d;%dH\x1b[38;5;%dm%s\x1b[0m",row,col,nColor,buffer);
   int lnf = sprintf(buf_fore,"\x1b[%d;%dH\x1b[38;5;%dm%s",row,col,nColor,buffer);
   const char * pbf = buf_fore;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
}

void _Move_xy_(GD_VIDEO * video, int row, int col){
   char buf_fore[50];
   int lnf = sprintf(buf_fore,"\x1b[%d;%dH",row,col);
   const char * pbf = buf_fore;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
   VID_ACTUAL_ROW=row; VID_ACTUAL_COL=col;
}
void _Move_x_(GD_VIDEO * video, int row){
   char buf_fore[50];
   int lnf = sprintf(buf_fore,"\x1b[%d;%dH",row,VID_ACTUAL_COL);
   const char * pbf = buf_fore;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
   VID_ACTUAL_ROW=row;
}
void _Move_y_(GD_VIDEO * video, int col){
   char buf_fore[50];
   int lnf = sprintf(buf_fore,"\x1b[%d;%dH",VID_ACTUAL_ROW,col);
   const char * pbf = buf_fore;
   memcpy((void *)video->video_mem+video->count_buffer, pbf, lnf);
   
   video->count_buffer = video->count_buffer + lnf;
   VID_ACTUAL_COL=col;
}

/* borra un buffer de video partcular */
void _Delete_video_(GD_VIDEO * video){
   video->count_buffer = 0;
   memset((void *)video->video_mem, ' ', video->video_rows*video->video_cols*5-1);
   video->video_mem[0]='\0';
}

/* imprime el buffer indicado, pero sin borrar la pantalla
   para sobreponer otros buffers sobre un buffer principal.
   Ver si es necesario HOME */
void _Refresh_video_(GD_VIDEO * video){

   video->video_mem[video->count_buffer]='\0';
   //\x1b[2J\x1b[1;1H\x1b[3J
   //\x1b[1;1H
   printf("%s", video->video_mem);fflush(stdout);

}


/* imprime el buffer pero se puede seguir escribiendo en él */
void _Refresh_vid_(GD_VIDEO * video){

   video->video_mem[video->count_buffer]='\0';
   //\x1b[2J\x1b[1;1H\x1b[3J
   //\x1b[1;1H
   printf("\x1b[2J\x1b[1;1H\x1b[3J%s", video->video_mem);fflush(stdout);

}

/* imprime el buffer y lo borra */
void _Flush_vid_(GD_VIDEO * video){

   video->video_mem[video->count_buffer]='\0';
   //\x1b[2J\x1b[1;1H\x1b[3J
   //\x1b[1;1H
   printf("\x1b[2J\x1b[1;1H\x1b[3J%s", video->video_mem);fflush(stdout);
   
   video->count_buffer=0;
}


void Define_box(int tipoBox, char **horiz, char **cornT, char **cornTR, char **cornB, char **cornBR, char **lateral){
  switch( tipoBox ){
     case SING_ALL:{
         Let( *horiz, "─"); Let( *lateral, "│"); Let(*cornT,"┌");
         Let( *cornTR,"┐"); Let( *cornB, "└"); Let( *cornBR,"┘"); break;
     }case DOUB_ALL:{
         Let( *horiz, "═"); Let( *lateral, "║"); Let(*cornT,"╔");
         Let( *cornTR,"╗"); Let( *cornB, "╚"); Let( *cornBR,"╝"); break;
     }case HSING_VDOUB:{
         Let( *horiz, "─"); Let( *lateral, "║"); Let(*cornT,"╓");
         Let( *cornTR,"╖"); Let( *cornB, "╙"); Let( *cornBR,"╜"); break;
     }case HDOUB_VSING:{
         Let( *horiz, "═"); Let( *lateral, "│"); Let(*cornT,"╒");
         Let( *cornTR,"╕"); Let( *cornB, "╘"); Let( *cornBR,"╛"); break;
     }case SOLID_BOX:{
         Let( *horiz, "▄"); /*Let( *lateral, "");*/ Let(*cornT,"▌");
         Let( *cornTR,"▐"); Let( *cornB, "▀");/* Let( *cornBR,"");*/ break;
     }default:{
         Let( *horiz, " "); Let( *lateral, " "); Let(*cornT," ");
         Let( *cornTR," "); Let( *cornB, " "); Let( *cornBR," "); break;
     }
  }
}

/* TODO: falta cruces */
void Define_line(int tipoBox, int dir, char **HL, char **HR, char **B){

  switch( tipoBox ){
     case SING_ALL:{
         if( dir == LINE_HORZ ) {
             Let( *B, "─"); Let( *HL, "├"); Let(*HR,"┤"); break;
         }else{
             Let( *B, "│"); Let( *HL, "┬"); Let(*HR,"┴"); break;
         }
     }case DOUB_ALL:{
         if( dir == LINE_HORZ ) {
             Let( *B, "═"); Let( *HL, "╠"); Let(*HR,"╣"); break;
         }else{
             Let( *B, "║"); Let( *HL, "╦"); Let(*HR,"╩"); break;
         }
     }case HSING_VDOUB:{
         if( dir == LINE_HORZ ) {
             Let( *B, "─"); Let( *HL, "╟"); Let(*HR,"╢"); break;
         }else{
             Let( *B, "║"); Let( *HL, "╥"); Let(*HR,"╨"); break;
         }
     }case HDOUB_VSING:{
         if( dir == LINE_HORZ ) {
             Let( *B, "═"); Let( *HL, "╞"); Let(*HR,"╡"); break;
         }else{
             Let( *B, "│"); Let( *HL, "╤"); Let(*HR,"╧"); break;
         }
     }case SING_DS:{
         if( dir == LINE_HORZ ) {
             Let( *B, "─"); Let( *HL, "╟"); Let(*HR,"┤"); break;
         }else{
             Let( *B, "│"); Let( *HL, "╤"); Let(*HR,"┴"); break;
         }
     }case SING_SD:{
         if( dir == LINE_HORZ ) {
             Let( *B, "─"); Let( *HL, "├"); Let(*HR,"╢"); break;
         }else{
             Let( *B, "│"); Let( *HL, "┬"); Let(*HR,"╧"); break;
         }
     }case DOUB_DS:{
         if( dir == LINE_HORZ ) {
             Let( *B, "═"); Let( *HL, "╠"); Let(*HR,"╡"); break;
         }else{
             Let( *B, "║"); Let( *HL, "╦"); Let(*HR,"╨"); break;
         }
     }case DOUB_SD:{
         if( dir == LINE_HORZ ) {
             Let( *B, "═"); Let( *HL, "╞"); Let(*HR,"╣"); break;
         }else{
             Let( *B, "║"); Let( *HL, "╥"); Let(*HR,"╩"); break;
         }

     }default:{
         if( dir == LINE_HORZ ) {
             Let( *B, "─"); Let( *HL, ""); Let(*HR,""); break;
         }else{
             Let( *B, "│"); Let( *HL, ""); Let(*HR,""); break;
         }    
     }
  }
}

void Horz_line_std(int w, int tipoLine ){
   char * HLline=NULL, * HRline=NULL, * Hline=NULL, * body=NULL; 
   Define_line( tipoLine, LINE_HORZ, &HLline, &HRline, &Hline );
   Stack{
      Store( body,      Multi_copy(body,HLline,Replicate(Hline,w),HRline,NULL)); 
   } Stack_off;
   const char *pB=body;
   printf( "%s", pB);
   free( HLline); free( HRline); free(Hline); free(body);
}

void Vert_line_std(int h, int tipoLine ){
   char * HLline=NULL, *HRline=NULL, *Hline=NULL; 
   Define_line( tipoLine, LINE_VERT, &HLline, &HRline, &Hline );

   const char *pB=Hline;
   printf( "%s", HLline );
   int i;
   for( i=1; i<h-1; i++ ){
      ///At ++SCREEN_ROW, SCREEN_COL; Print "%s", pB;
      printf("\x1b[%d;%dH%s",++SCREEN_ROW, SCREEN_COL,pB );
      ///Printvid_xy(video, VID_ACTUAL_ROW+i, VID_ACTUAL_COL, pB);
   }
   //Printvid_xy(video, VID_ACTUAL_ROW+h-1, VID_ACTUAL_COL, HRline);
   ///At ++SCREEN_ROW, SCREEN_COL; Print "%s", HRline;
   printf("\x1b[%d;%dH%s",++SCREEN_ROW, SCREEN_COL,HRline );

   free( HLline); free( HRline); free(Hline);
}

void Horz_line_vid(GD_VIDEO * video, int w, int tipoLine ){
   char* HLline=NULL, *HRline=NULL,* Hline=NULL, *body=NULL; 
   Define_line( tipoLine, LINE_HORZ, &HLline, &HRline, &Hline );
   Stack{
      Store( body,      Multi_copy(body,HLline,Replicate(Hline,w),HRline,NULL)); 
   } Stack_off;
   const char *pB=body;
   Printvid_str(video, pB);
   ///Free secure HLline, HRline, Hline, body;
   free( HLline); free( HRline); free(Hline); free(body);
}

void Vert_line_vid(GD_VIDEO * video, int h, int tipoLine ){
   char* HLline=NULL, *HRline=NULL, *Hline=NULL; 
   Define_line( tipoLine, LINE_VERT, &HLline, &HRline, &Hline );

   const char *pB=Hline;
   Printvid_str(video, HLline);
   int i;
   for( i=1; i<h-1; i++ ){
      Printvid_xy(video, VID_ACTUAL_ROW+i, VID_ACTUAL_COL, pB);
   }
   Printvid_xy(video, VID_ACTUAL_ROW+h-1, VID_ACTUAL_COL, HRline);
   
   ///Free secure HLline, HRline, Hline;
   free( HLline); free( HRline); free(Hline);
}

/* BOX: top es marcado por Move_xy() */
void Boxvid(GD_VIDEO * video, int h, int w, int tipoBox ){
   
   char* HlineTop=NULL, *HlineBott=NULL, *body=NULL;
   char* horiz=NULL, *cornT=NULL, *cornTR=NULL, *cornB=NULL, *cornBR=NULL, *lateral=NULL;
   Define_box( tipoBox, &horiz, &cornT, &cornTR, &cornB, &cornBR, &lateral );

   Stack { 
       Store( body,      Multi_copy(body,lateral,Replicate(" ",w),lateral,NULL)); 
       Store( HlineTop,  Multi_copy(HlineTop,cornT,Replicate(horiz,w),cornTR,NULL)); 
       Store( HlineBott, Multi_copy(HlineBott,cornB,Replicate(horiz,w),cornBR,NULL));
   } Stack_off;
   
   const char * pbfT = HlineTop, * pbfB = HlineBott;
   Printvid_str(video, pbfT);
   const char * pbb = body;
   int i;
   for( i=1; i<h-1; i++ ){
       Printvid_xy(video, VID_ACTUAL_ROW+i, VID_ACTUAL_COL, pbb);
   }
   Printvid_xy(video, VID_ACTUAL_ROW+h-1, VID_ACTUAL_COL, pbfB);
   
   free(HlineTop); free(HlineBott); free(body);
   //Free secure horiz, cornT, cornTR, cornB, cornBR, lateral;
   free( horiz); free( cornT); free(cornTR); free(cornB); free(cornBR); free(lateral);
   
}

void Box_std(int h, int w, int tipoBox ){
   char * HlineTop=NULL, *HlineBott=NULL, *body=NULL;
   char * horiz=NULL, *cornT=NULL, *cornTR=NULL, *cornB=NULL, *cornBR=NULL, *lateral=NULL;
   Define_box( tipoBox, &horiz, &cornT, &cornTR, &cornB, &cornBR, &lateral );
         
   Stack { 
      Store( body,      Multi_copy(body,lateral,Replicate(" ",w),lateral,NULL)); 
      Store( HlineTop,  Multi_copy(HlineTop,cornT,Replicate(horiz,w),cornTR,NULL)); 
      Store( HlineBott, Multi_copy(HlineBott,cornB,Replicate(horiz,w),cornBR,NULL));
   } Stack_off;
   
   const char * pbfT = HlineTop, * pbfB = HlineBott;
   printf( "%s", pbfT );
   const char * pbb = body;
   int i;
   for( i=1; i<h-1; i++ ){
       //Printvid_xy(video, VID_ACTUAL_ROW+i, VID_ACTUAL_COL, pbb);
       ///Atrow ++SCREEN_ROW; Print "%s", pbb;
       printf("\x1b[%d;%dH%s",++SCREEN_ROW, SCREEN_COL,pbb );
   }
   //Printvid_xy(video, VID_ACTUAL_ROW+h-1, VID_ACTUAL_COL, pbfB);
   ////Atrow ++SCREEN_ROW; Print "%s", pbfB;
   printf("\x1b[%d;%dH%s",++SCREEN_ROW, SCREEN_COL,pbfB );
   
   free(HlineTop); free(HlineBott); free(body);
   ///Free secure horiz, cornT, cornTR, cornB, cornBR, lateral;
   free( horiz); free( cornT); free(cornTR); free(cornB); free(cornBR); free(lateral);

}

void Solid_box_std(int h, int w, int colorF, int colorB){
   char* HlineTop=NULL, *HlineBott=NULL, *body=NULL;
   char* horiz=NULL, *cornT=NULL, *cornTR=NULL, *cornB=NULL;

   Define_box( SOLID_BOX, &horiz, &cornT, &cornTR, &cornB, NULL, NULL );
//         Let( *horiz, "▄"); Let( *lateral, ""); Let(*cornT,"▌");
//         Let( *cornTR,"▐"); Let( *cornB, "▀"); Let( *cornBR,""); break;
   char scolor[40],scolorT[40];
   sprintf(scolor,"\x1b[38;5;%dm\x1b[48;5;%dm",colorF,colorB);
   sprintf(scolorT,"\x1b[38;5;%dm",colorF);

   Stack {
      Store ( body,      Multi_copy(body, scolor, cornT, Replicate(" ",w), scolorT, cornTR, NULL) );
      Store ( HlineTop,  Multi_copy(HlineTop, scolorT, Replicate(horiz,w+2), NULL) );
      Store ( HlineBott, Multi_copy(HlineBott, "\x1b[0m",scolorT, Replicate(cornB,w+2), "\x1b[0m", NULL) );
   } Stack_off;

   const char * pbfT = HlineTop, * pbfB = HlineBott;
   printf( "%s", pbfT);
   const char * pbb = body;
   int i;
   for( i=1; i<h-1; i++ ){
       //Printvid_xy(video, VID_ACTUAL_ROW+i, VID_ACTUAL_COL, pbb);
       //Atrow ++SCREEN_ROW; Print "%s", pbb;
       printf("\x1b[%d;%dH%s",++SCREEN_ROW, SCREEN_COL, pbb );
   }
   //Printvid_xy(video, VID_ACTUAL_ROW+h-1, VID_ACTUAL_COL, pbfB);
   ///Atrow ++SCREEN_ROW; Print "%s", pbfB;
   printf("\x1b[%d;%dH%s",++SCREEN_ROW, SCREEN_COL,pbfB );
   
   free(HlineTop); free(HlineBott); free(body);
   ///Free secure horiz, cornT, cornTR, cornB;
   free( horiz); free( cornT); free(cornTR); free(cornB);

}

void Solid_box_vid(GD_VIDEO * video, int h, int w, int colorF, int colorB){
   char* HlineTop=NULL, *HlineBott=NULL, *body=NULL;
   char* horiz=NULL, * cornT=NULL, *cornTR=NULL, *cornB=NULL;

   Define_box( SOLID_BOX, &horiz, &cornT, &cornTR, &cornB, NULL, NULL );

   char scolor[40],scolorT[40];
   sprintf(scolor,"\x1b[38;5;%dm\x1b[48;5;%dm",colorF,colorB);
   sprintf(scolorT,"\x1b[38;5;%dm",colorF);

   Stack {
      Store ( body,      Multi_copy(body, scolor, cornT, Replicate(" ",w), scolorT, cornTR, NULL) );
      Store ( HlineTop,  Multi_copy(HlineTop, scolorT, Replicate(horiz,w+2), NULL) );
      Store ( HlineBott, Multi_copy(HlineBott, "\x1b[0m",scolorT, Replicate(cornB,w+2), "\x1b[0m", NULL) );
   } Stack_off;

   const char * pbfT = HlineTop, * pbfB = HlineBott;
   Printvid_str(video, pbfT);
   const char * pbb = body;
   int i;
   for( i=1; i<h-1; i++ ){
       Printvid_xy(video, VID_ACTUAL_ROW+i, VID_ACTUAL_COL, pbb);
       //Atrow ++SCREEN_ROW; Print "%s", pbb;
   }
   Printvid_xy(video, VID_ACTUAL_ROW+h-1, VID_ACTUAL_COL, pbfB);
   //Atrow ++SCREEN_ROW; Print "%s", pbfB;
   
   free(HlineTop); free(HlineBott); free(body);
   //Free secure horiz, cornT, cornTR, cornB;
   free( horiz); free( cornT); free(cornTR); free(cornB);

}

int Get_choice( char * menu[], int valid[], int cond[], int len, int hBox, int colorf, int colorb, int hlfore, int hlback ){
   int hl=0, swEnableRaw=0;
   int opcion=0;
   int index=0, botIndex=hBox;

   if(cond[0]) hl = cond[0];
   if(cond[1]) index = cond[1];
   if(cond[2]) botIndex = cond[2];
   
   if (!ENABLE_RAW_MODE){  // no estáhabilitado raw mode??
       Enable_raw_mode();
       swEnableRaw=1;
   }
   int cx=0;
   while( opcion!=ESCAPE && opcion != 13 ){
       int row=SCREEN_ROW+1, col=SCREEN_COL+1;
       int i;
       for ( i=index; i<botIndex && i<len ; i++){
           if( valid[i] ){
               if (i==hl) {
                   //printf( "\x1b[%d;%dH\x1b[38;5;%dm\x1b[48;5;%dm%s", row++,col, hlfore, hlback, menu[i]);
                   cx = row++;
               }else{
                   printf( "\x1b[%d;%dH\x1b[38;5;%dm\x1b[48;5;%dm%s", row++,col, colorf, colorb,menu[i]);
               }
           }else{
               Color_back(colorb);Color_fore(252);printf( "\x1b[%d;%dH%s",row++,col,menu[i]);  // imprimo no valido
               
           }
       }
       printf( "\x1b[%d;%dH\x1b[38;5;%dm\x1b[48;5;%dm%s", cx,col, hlfore, hlback, menu[hl]);
       if ( Kbhit() ){
           opcion = Getch();

           if(opcion == ARROW_UP )   { 
               int i=1;
               while ( hl-i >= 0 ){
                   if ( valid[hl-i] ){
                       hl = hl - i; 
                       break;
                   }
                   i++;
               }
               while (hl < index ) {
                   --index;--botIndex;
               }
               /*--hl; 
               if(hl<0) hl=0;
               if(hl<index){
                   --index;--botIndex;
                   if(index<0) {
                       index=0;
                       botIndex=hBox;
                   }
               }*/
           }
           else if(opcion == ARROW_DOWN ) { 
               int i=1;
               while ( hl+i < len ){
                   if ( valid[hl+i] ){
                       hl = hl + i; 
                       break;
                   }
                   i++;
               }
               while (hl >= botIndex ) {
                   ++index;++botIndex;
               }
               /*++hl;
               if(hl==len) --hl;
               if(hl>=botIndex ) {
                   ++index;++botIndex;
                   if(botIndex>len){
                       --index; --botIndex;
                   }
               }*/
           }
           else if( opcion == ARROW_RIGHT ){
               if ( Occurs("»", menu[hl] ) ){
                   opcion=ENTER;
                   break;
               }
           }
           else if(opcion == CTRL_ARROW_UP || opcion == HOME_KEY){
               hl=0; index=0; botIndex=hBox;
           }
           else if(opcion == CTRL_ARROW_DOWN || opcion == END_KEY){
               hl=len-1; botIndex=hl+1; index=hl-hBox+1;
           }
           else if(opcion == ENTER ){ 
               if (valid[hl]) break;
           }
           else if(opcion== ESCAPE || opcion == Ctrl_key('q') || opcion == Ctrl_key('Q') ) break; 
           opcion=0;
           Flush_inp;
       }
   }
   if (opcion==ENTER) 
   {   
       opcion = hl;
       //SCREEN_ROW = cx-1;SCREEN_COL += strlen(menu[0]);
       Goto_xy( cx-1, SCREEN_COL + strlen(menu[0]) );
       cond[0] = hl; cond[1] = index; cond[2] = botIndex;
   }
   else opcion=-1;
   
   if(swEnableRaw){  // no estaba habilitado: deshabilito
       Disable_raw_mode();
   }
   return opcion;
}


int Get_cursor_raw(int *rows, int *cols) {
  char buf[32];
  unsigned int i = 0;

  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
    if (buf[i] == 'R') break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[') return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

  return 0;
}

int Get_cursor_tty(int *rows, int *cols) {

   int swEnableRaw=0;
   if (!ENABLE_RAW_MODE){  // no estáhabilitado raw mode??
       Enable_raw_mode();
       swEnableRaw=1;
   }
  
   int ret = Get_cursor_raw( rows, cols)  ;

   if(swEnableRaw){  // no estaba habilitado: deshabilito
       Disable_raw_mode();
   }
     
  return ret;
}

