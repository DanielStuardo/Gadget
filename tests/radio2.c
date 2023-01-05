
#include <gadget/gadget.h>

LIB_GADGET_START

GD_VIDEO draw_box ( GD_VIDEO video){
   Gotoxy(video, 3,10);
   Color_fore(video,167);
   Box(video, 15,20, HDOUB_VSING );
   Gotoxy(video, 9,10); Hline(video,20,HDOUB_VSING);
   Gotoxy(video, 14,10); Hline(video,20,HDOUB_VSING);
   Reset_text(video);
   
   Color_fore(video, 80);
   Outvid(video, 10,12,"Seleccione un ítem");
   Outvid(video, 11,12,"solo para ver si");
   Outvid(video, 12,12,"esto funciona.");
   Color_fore(video,111);
   Outvid(video, 13,15,"Mr. Dalien");
   Outvid(video, 15,12, "Fecha seleccionada:");
   
   //Outvid(video, 16,12, 
   Reset_text(video);
   return video;
}

MT_CELL * pone_campos( MT_CELL * arrayF, DS_ARRAY * arrayF_data){

  /* No se necesota pSDS() si el objeto entra como pSDS() a esta funcion.
     Además, si no desea poner un mensaje informativo ("<date>" o lo que sea),
     debe poner NULL:
           arrayF = Add_field( SDS(arrayF),16,12,NULL);
         */
   arrayF = Add_field( SDS(arrayF),16,12,"<date>");
   return arrayF;
}

#define CLR_FORE   15
#define CLR_BACK   0

Main
   Cls;

   GD_VIDEO video;
   Init_video( &video );
   
   Gpm_Connect conn;

   if ( ! Init_mouse(&conn)){
        perror("No se puede conectar al servidor del ratón\n");
        Stop(1);
   }  
   Enable_raw_mode();
   Hide_cursor;

   New objects Rbtn, Btn_select, Btn_ena, Btn_calendar, Fields;
   
   int option_rbtn=1;
   
   /* prepara objetos de mouse */
   New multitype opciones;
   Append_mt(opciones,int,1); sAppend_mt(opciones,"daily");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"weekly");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"monthly");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"yearly");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"millenialy");
   
   Rbtn = New_object_mouse( SMD(&Rbtn), RADIO_BUTTOM, SDS(opciones), 4,12, CLR_FORE, CLR_BACK );
   Btn_select = New_object_mouse( SMD(&Btn_select), BUTTOM, " Select ", 5,33, CLR_FORE, CLR_BACK);
   Btn_calendar = New_object_mouse( SMD(&Btn_calendar), BUTTOM, " Show calendar ", 8,33, CLR_FORE, CLR_BACK);
   
   Btn_ena = New_object_mouse( SMD(&Btn_ena), BUTTOM, " enable|disable Radio-B ", 11,33, CLR_FORE, CLR_BACK);

   
 //  Disable_object(Rbtn);
   // prepara fondo de pantalla 
   video = draw_box ( video );
   //   añade campos.
   //   Un campo es independiente del contexto, aparecerá donde se coloque a voluntad 
   //Fields = Add_field( pSDS(Fields),16,12);
   Fields = pone_campos( pSDS(Fields));
   
   // pone todo 
   Refresh(video);
   Put object Rbtn, Btn_select, Btn_ena, Btn_calendar, Fields;

// *********** cuerpo del programa *************
   int c;
   char fecha_elegida[11];
   Waiting_some_clic(c) 
   {
       if (Object_mouse( Btn_calendar)) {
           char * date = Get_date();
           At 5,24;  // locate calendar
           // devuelve 0 si no selecciona nada.
           //   devuelve fecha codificada si hubo selección.
           //   67 = color fore
           //   17 = back color
           //   Tercer parámetro:
           //   1 = si llega al primer día, se pasa al mes anterior; si
           //       llega al último día, se pasa al siguiente. 
           //   0 = se queda en el mismo mes, no cambia el mes si va más
           //       allá del primer día o del último. 
           long date_select = Select_date_from_calendar(date, 67, 17, 0);
           if ( date_select ){
               int Ano=0, Mes=0, Dia=0;
               Decode_julian_date( date_select, &Ano, &Mes, &Dia );
               sprintf( fecha_elegida,"%02d/%02d/%04d", Dia, Mes, Ano);
               //Outvid(video,16,12,fecha_elegida);
               Fields = Replace_field( pSDS(Fields),0,fecha_elegida);
           }
           Free secure date;
       }else if (Object_mouse( Btn_ena )){
           if (Status_object( Rbtn ) ){
               Disable_object( Rbtn );
           }else{
               Enable_object( Rbtn );
           }
       }
       
       option_rbtn = Object_mouse( Rbtn ); // debe pasar por aquí para chequear la
                                           //   opcion elegida 
                   
       if (Object_mouse( Btn_select)) break;
       
       Refresh(video);
       Put object Rbtn, Btn_select, Btn_ena, Btn_calendar,Fields;
   }
   At 19,10; Print "Option selected: %d (\"%s\")\n", option_rbtn, (char*)$s-opciones[option_rbtn*2-1];


   Reset_color;
   Disable_raw_mode();
   Close_mouse();
   Show_cursor;
   
   Free object Rbtn, Btn_select, Btn_ena,Btn_calendar, Fields;
   Free video video;
   Free multitype opciones;
/*********************************************/

/*   int i;
   Iterator up i [0:1:Rbtn_data.len]{
       Print_Cell( Rbtn, i); Prnl
   }   
   Free object Rbtn;*/
      
   
   At 25,0;
   
End
