#include <gadget/gadget.h>

LIB_GADGET_START

Main
   
   GD_VIDEO video, video2;
   //Get_size_terminal();
   //Resize_terminal(40,150);
   Cls;
   Init_video( &video ); //, SIZE_TERM_ROWS-4,SIZE_TERM_COLS);
   Init_video( &video2 );

  // printf("rows = %ld, cols=%ld\n", (*video).video_rows, video->video_cols);
  // Free_video (video);
  // exit(1);
   
   int j=10,i; //,i=10;
   int sw_1=0, sw_2=0, sw_3=0, sw_4=0;
   
   Hide_cursor;
   
   //Enable_raw_mode(); // al terminar, se deshabilita raw_mode automáticamente.
   // aunque se puede usar en cualquier momento Disable_raw_mode(). 
   
   while (1){
   
  // 
   Iterator up i [1:1:SIZE_TERM_ROWS/*-4*/] {
   //Iterator down i [SIZE_TERM_ROWS-4:-1:1] {
//\x1b[7m   \x1b[0m
      if( i==6 ) Color_back(video,121);
      else if (i==20 ) Reset_text(video); 
      Outvid(video, i,j, "Este es un mensaje destinado a memoria de video",98+i);
      //Outvid(&video, 3,10, "Este es un mensaje destinadoa memoria de video",121);
      //Outvid(&video, 5,10, "Este es un mensaje destinadoa memoria de video",56);
      
   }
   Reset_text(video);

   if ( !sw_1 ){
      Refresh(video);
      getchar();
      sw_1=1;
   }

   Outvid(video,"\nUn mensaje: no sé dónde saldrá...");

   //Text_background(&video,53);Text_color(&video,11);
   Color_back(video,53); Color_fore(video,11);
   Gotoxy(video, 19,40);  Outvid(video, "   ::   ");
   Gotox (video, 20);     Outvid(video, " $$$$$$ ");
   Gotox (video, 21);     Outvid(video, "   ::   :");
   Reset_text(video);
   
   if ( !sw_2 ){
      Refresh(video);
      getchar();
      sw_2=1;
   }
   
   Color_fore(video, 215);
   Outvid(video, 13,80,"       ");//,219);
   Outvid(video, 14,80," $$$$$$");//,219);
   Outvid(video, 15,80,"     :::::");//,219);

   Outvid(video,"\nUn mensaje: no sé dónde saldrá...");

   
   if ( !sw_3 ){
      Refresh(video);
      getchar();
      sw_3=1;
   }
   //fwrite(video.video_mem,strlen(video.video_mem),1,stdout);
   //getchar(); break;
   if( j < 70 ){
      Gotoxy(video, 15,30);
      Box(video, 10,10, HDOUB_VSING );
      Gotoxy(video, 16,30); Hline(video,10,HDOUB_VSING);
      Gotoxy(video, 19,30); Hline(video,10,HSING_VSING);
   }

   if( j > 70 && j<90 ){
      Gotoxy(video, 7,70);
      Box(video, 10,50, DOUB_ALL );
   }
   
   if ( !sw_4 ){
      Refresh(video);
      getchar();
      sw_4=1;
   }
   
   if( j == 75 ){
      
      Gotoxy(video,20,60); 
      //Color_fore(1);/*Color_back(2);*/
      Box_solid(video, 10,15, /*color fore interior*/1, /*color fondo interior*/ 2);
      Refresh(video);
      
      Gotoxy(20,62);///Color_fore(1);Color_back(2);
      /* 
         GET_CHOICE funciona con arrays dinámicos y estaticos. Si es dinámico, debe ser eliminado.
      */
      char * opciones[]={" opción  1 "," opción  2 "," opción  3 "," opción  4 "," opción  5 "," opción  6 "," opción  7 ",
                         " opción  8 "," opción  9 "," opción 10 "," opción 11 "," opción 12 "," opción 13 "," opción 14 ",
                         " opción 15 "," opción 16 "," opción 17 "," opción 18 "," opción 19 "," opción 20 "," opción 21 "};
      //int validos[21]={1,1,1,1,1,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0};
      Fill array validos as int(21) with 1;
      validos[5]=0; validos[6]=0; validos[11]=0; validos[13]=0; validos[18]=0; validos[20]=0;
      
      int cond[]={0,0,0};
      int opcion = Get_choice( opciones, validos, cond, sizeof(opciones)/sizeof(char*) /*21*/,/* altura ventana */8, 
                               /*color fore normal*/  1,/*color back normal*/2,
                               /*color highligh fore*/1,/*color hl back*/15 );
      Free array validos;
      Reset_color;
      
      Gotoxy(video,10,10); Outvid(video,"OPCION ELEGIDA: ");
      String cOp; Get_fn_let( cOp, Int2str(opcion));
      Gotoy (video,26);    Outvid(video,cOp);
      if( Is_non_neg(opcion) ){
          Gotoy (video,29);    Outvid(video,opciones[opcion]);
      }else{
          Gotoy (video,29);    Outvid(video,"(presionó ESC - no escogió nada)");
      }
      Free secure cOp;
      Refresh(video);
      // esto se imprime en el stdout:
      Gotoxy(13,10);
      Box_solid(10,15,3,10);
      getchar();   // getchar no sirve si está habilitado RAW MODE
      Reset_color;
      
      // ahora, el box_solid anterior queda inserto en el segundo buffer
      Gotoxy(video2,13,10);
      Box_solid(video2,10,15,3,10);
      Reset_text(video2);
   }
   
   if( j> 85){
      #define LONG_BOX  40
      Color_fore(video,255);
      Color_back(video,1);
      Gotoxy(video, 25,80);
      Box(video, 7,LONG_BOX, HSING_VDOUB );
      Gotoxy( video, 25,105); Vline(video, 7, HSING_VDOUB );
      Gotoxy(video, 25,109); Vline(video, 7, HSING_VSING );
      Gotoxy(video, 25,112); Vline(video, 7, HSING_VDOUB );
      /* aprovecha la última columna indicada: 112 */
      Gotox (video, 27); Hline(video, 8, HSING_VDOUB );
      Gotox (video, 29); Hline(video, 8, HDOUB_VDOUB );
      Gotoxy (video, 28,105); Hline(video, 3, DOUB_DS );
      Outvid(video, 28,83,"Mensaje aquí dentro");
      Reset_text(video);
   }
   

 /* Get_cursor solo funciona en RAW MODE 
    
    Esto ejecutado constantemente ralentiza la ejecucion. Ojo!
    */
   if( ENABLE_RAW_MODE ){
      int rows=0, cols=0;
      if( Get_cursor_raw(&rows, &cols) >= 0 ){
          char buff[100];
          if (sprintf(buff,"El cursor está en (%d, %d)",rows,cols) ){
              Outvid(video, 5,5, buff);
          }else{
              Outvid(video, 7,5, "No obtuve la posicion del cursor...");
          }
      }else{
          Outvid(video, 7,5, "No funciona Get_cursor...");
      }
   }else{
      int rows=0, cols=0;
      if (Get_cursor_tty(&rows, &cols)>=0){
          char buff[100];
          if (sprintf(buff,"El cursor está en (%d, %d)",rows,cols) ){
              Outvid(video, 5,5, buff);
          }else{
              Outvid(video, 7,5, "No obtuve la posicion del cursor...");
          }
      }else{
          Outvid(video, 7,5, "No funciona Get_cursor_tty...");
      }
   }
   /* Flush() limpiará la pantalla y desplegará el video */
   Flush(video);
   /* Overlap() y Clear_video() existen por si escribo formularios donde
      se pongan campos sobre una capa dibujada. Se pueden poner cuantas
      capas se desee con estas funciones */
   Overlap(video2);
   

   /* esto está fuera del video: stdout estándar */
   Color_fore(67); Color_back(17);
   At 9,74; Box( 7,30, SING_ALL); /* no necesita "video" porque se imprime en el stdout directamente */
   Atrow 11; Hline(30, HDOUB_VSING);
   At 11,77; Vline( 5, -1 );
   At 11,80; Vline( 5, SING_DS );
   At 11,83; Vline( 5, -1 );
   At 9,97;  Vline( 3, SING_SD);
   At 9,102;  Vline( 3, DOUB_SD);
   At 10,75; Print " Mensaje coloreado ";

   Reset_color;
    
   if( ++j == SIZE_TERM_COLS-48 ) break;
   
   //if( Kbhit() ) break;
   
   //if( --j == 3 ) break;
   usleep((unsigned int)10000);
   
   /* limpia el video para volver a dibujar sobre él. A veces no será necesario hacerlo, porque si
      se reescribe el video completo, lo anterior se perderá. Aquí se reescribe el video, por lo
      que no sería necesario, pero se deja para efectos didácticos. */
   Clear_video(video);
   }
   At SIZE_TERM_ROWS,1 ; // Prnl;
   Show_cursor 
   
   Free_video (video);
   Free_video (video2);
  getchar();
End
