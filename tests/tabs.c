
#include <gadget/gadget.h>

LIB_GADGET_START

#define CLR_FORE   15
#define CLR_BACK   0

Main
   Open_buffer;

   Gpm_Connect conn;

   if ( ! Init_mouse(&conn)){
        perror("No se puede conectar al servidor del ratón\n");
        Stop(1);
   }  
   Enable_raw_mode();
   Hide_cursor;
   
//   GD_VIDEO video_tab0, video_tab1, video_tab2;
   New object tab, btn, btn_tab_final, btn_tab_siguiente, btn_tab_anterior;

 /* al crear el objeto TAB, por defult ACTIVE_TAB=0.
    Si el "ancho" del tab es menor al tamaño sumado de los encabezados, el tamaño del
    tab se ajustará. */
   tab = New_object_mouse( SMD(&tab),TABS,/*fila*/ 2, /*columna*/ 2,/*alto*/ 20, /*ancho*/ 60,
                                          /*headers*/ " Tab 1 "," Segundo tab "," Tercero ", " Último ",
                                          " Penútimo "," Feliz final ", NULL);

   btn = New_object_mouse( SMD(&btn), BUTTOM, " Terminación ", 23,45, CLR_FORE,CLR_BACK);
   btn_tab_final = New_object_mouse( SMD(&btn_tab_final), BUTTOM, " Terminación anormal ", 10,25, CLR_FORE,CLR_BACK);
   btn_tab_siguiente = New_object_mouse( SMD(&btn_tab_siguiente), BUTTOM, " Siguiente ", 15,40, CLR_FORE,CLR_BACK);
   btn_tab_anterior = New_object_mouse( SMD(&btn_tab_anterior), BUTTOM, " Anterior ", 15,10, CLR_FORE,CLR_BACK);
   
   /* añadir pantallas de cada tab */
/*   video_tab0 = draw_video_tab0( video_tab0 );
   video_tab1 = draw_video_tab1( video_tab1 );
   video_tab2 = draw_video_tab2( video_tab2 );
*/   

   Put object tab, btn;  // muestra el tab activo. Se puede elegir entre todos los creados con ACTIVE_TAB=n;

//   Refresh( video_tab0 );  // muestra el video asociado al tab 0.


   /*imprime los objetos asociados*/

   int c;
   int swFinaliza=0;
   Waiting_some_clic(c) 
   {
       switch( Object_mouse (tab) )  // aquí borra el espacio del tab. Imprime los objetos de cada tab.
       {
           case 0:
           {
                //Refresh(video_tab0);  // imprime en todo el terminal, no hay problema.
                // put objetos asociados al tab.
                //Put object btn_tab_siguiente;
                break;
           }
           case 1:
           {
                //Refresh(video_tab1);
                // put objetos asociados al tab.
                //Put object btn_tab_siguiente;
                break;
           }
           case 2:
           {
                At 9,5; Print "No es conveniente usar este método de \"anterior\" y \"siguiente\"...";
                At 10,5; Print "porque habría que imprimir todo el contenido del tab destino.";
                At 11,5; Print "Mejor clikear en los labels de los tabs.\nEs su decisión.";
                Put object btn_tab_siguiente, btn_tab_anterior;
                break;
           }
           case 3:{
                //Put object btn_tab_siguiente;
                break;
           }
           case 4:{
                Put object btn_tab_siguiente;
                break;
           }
           case 5:{
                At 5,5; Print "Tab Activo = %d",ACTIVE_TAB;
                At 7,5; Print "(Esto no aparecerá si llega aquí con \"siguiente\").";
                Put object btn_tab_final; 
                break;
           }
       }
       //   analiza cada objeto y se ejecuta 
       //   Get_active_tab 
       //   macro que consulta ACTIVE_TAB

       switch( ACTIVE_TAB ){
           case 0:{
                   
               break;
           }
           case 1:{

               break;
           }
           case 2:{

               if (Object_mouse( btn_tab_siguiente )) {
                   ACTIVE_TAB++;
                   Put object tab;
               }else if(Object_mouse( btn_tab_anterior )) {
                   ACTIVE_TAB--;
                   Put object tab;
               }

               break;
           }
           case 3:{

               break;
           }
           case 4:{
               if (Object_mouse( btn_tab_siguiente )) {
                   ACTIVE_TAB++;
                   Put object tab,btn_tab_final;
               }

               break;
           }
           case 5:{
               if (Object_mouse( btn_tab_final )) 
                   swFinaliza = 1;
               break;
           }
       }
       if (Object_mouse( btn)) break;
       if (swFinaliza) break;
   }

/*********************************************/

   Reset_color;
   Disable_raw_mode();

   Close_mouse();
   Show_cursor;

/*   At 25,0;
   int i;
   Iterator up i [0:1:tab_data.len]{
       Print_Cell( tab, i); Prnl
   }*/
   //Free object Rbtn;

//   Free videos video_tab0, video_tab1, video_tab2;
   Free object tab, btn, btn_tab_final, btn_tab_siguiente, btn_tab_anterior;
   
   Close_buffer;
   At 30,0;
End

