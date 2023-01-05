
#include <gadget/gadget.h>

LIB_GADGET_START

#define CLR_FORE_MENU   232
#define CLR_BACK_MENU   247

void inicia_proceso_apertura();
void cierre_apertura();
void put_a_joke();
GD_VIDEO draw_box ( GD_VIDEO video);
/* Solo son necesarions parámetros MT_CELL porque no cambiará el número de opciones
   de los menús. Si va a cambiar al número de opciones, debe declarar pSDS().
   La otra opción es que declare esos objetos como GLOBALES, y podrá modificarlos
   a su antojo en cualquier parte del programa */
void change_option_menu( MT_CELL * menu, MT_CELL * submenu_archivo );
void Checking_submenu_archivo(MT_CELL * menu, MT_CELL * submenu_archivo );
void Checking_main_menu_archivo(MT_CELL * menu, MT_CELL * submenu_archivo);

/* variables globales */
int swFinaliza;
int cambio_exitoso=1;

GD_VIDEO video;
/* otra forma de declarar los arrays MT y objetos de mouse, globales */
MT_CELL *ctrl_archivo, *ctrl_salir;


Main

   Init_video( &video );
   
   Gpm_Connect conn;

   if ( ! Init_mouse(&conn)){
        perror("No se puede conectar al servidor del ratón\n");
        Stop(1);
   }  
   Enable_raw_mode();
   Hide_cursor;   
   
   /* objetos CTRL... se declaran así porque su declaración es global */
   Define_New_Array(ctrl_archivo);
   ctrl_archivo_data.type = MULTI_TYPE;
   
   Define_New_Array(ctrl_salir);
   ctrl_salir_data.type = MULTI_TYPE;
   
   /* declaracion de objetos locales */
   New object menu, submenu_archivo;
   
   /* opciones para menu. Se usa MT_CELL por si se modifican las opciones en la ejecucion */
   New array opts, opts2 as string;
   Fill array valid, valid2  as int(4) with 1;

   sAppend( opts, " Abrir            ");
   sAppend( opts, " Abrir reciente   ");
   sAppend( opts, " Procesos       » ");
   sAppend( opts, " Cerrar           ");
   sAppend( opts2, " Iniciar proceso apertura ");
   sAppend( opts2, " Cerrar apertura          ");
   sAppend( opts2, " Chiste...                ");
   sAppend( opts2, " Activar \"Abrir reciente\" ");
   
   valid[1] = 0;  // invalido la opción 2. Esto puede cambiar en tiempo de ejecucion
   
   menu = New_object_mouse(SMD(&menu),CHOICE, SDS(opts), SDS(valid), 6,5);
   submenu_archivo = New_object_mouse(SMD(&submenu_archivo),CHOICE,SDS(opts2),SDS(valid2), 8,23);
   
   /* Poner caracteres unicode es problemático. Desistir de eso, aunque se vea bonito */
   ctrl_archivo = New_object_mouse(SMD(&ctrl_archivo), CONTROL," \u2397 Abrir ", 5,6, CLR_FORE_MENU,CLR_BACK_MENU);
   ctrl_salir = New_object_mouse(SMD(&ctrl_salir), CONTROL, " \u2613 Salir ", 5,15, CLR_FORE_MENU,CLR_BACK_MENU);
   
   video = draw_box( video );

//   Cls;   
   Refresh(video);
   Put object ctrl_archivo, ctrl_salir;
   
   int c;
   swFinaliza=0;

   Waiting_some_clic(c) 
   {
       if( Object_mouse( ctrl_archivo ) ){
           Checking_main_menu_archivo(menu, submenu_archivo);
           Assert( cambio_exitoso, falla_cambio );
       }

       if(swFinaliza) break;
       if( Object_mouse(ctrl_salir)) break;
       /* puede ser un Refresh(video) y evita el Cls...*/
       //Cls;
       Refresh(video);
       Put object ctrl_archivo, ctrl_salir;

       Exception( falla_cambio ){
           Msg_amber("Falló el cambio de item del submenu");
           break;
       }

   }

   Disable_raw_mode();

   Close_mouse();
   
/*   At 25,0;
   int i;
   Iterator up i [0:1:menu_data.len]{
       Print_Cell( menu, i); Prnl
   }*/

   Free str array opts, opts2;
   Free array valid, valid2;
   Free video video;
      
   Free objects ctrl_archivo, ctrl_salir, menu, submenu_archivo;
   Show_cursor;
   At 30,1;
/*   char f[10];
   sprintf( f, "\u2397");
   printf( "%s = %ld\n%d,%d,%d", f, strlen(f),f[0],f[1],f[2]);*/
End


void Checking_main_menu_archivo(MT_CELL * menu, MT_CELL * submenu_archivo) {
   Put object menu;
   int c1, op=0;
   Waiting_some_clic(c1) 
   {
      op = Object_mouse( menu );
      if( op!=3 ){
          Refresh(video);
          Put object ctrl_archivo, ctrl_salir;
      }
      switch ( op ){
          case 1:{  // primera opcion...
              //Refresh(video);
              //Put object ctrl_archivo, ctrl_salir;
              At 17,15; Print "Opcion 1 del menu"; Flush_out;
              Pause();
              break;
          }
          case 2:{  // segunda opcion inicialmente desactivada...
              //Refresh(video);
              //Put object ctrl_archivo, ctrl_salir;
              At 17,15; Print "Ahora puedes ver este precioso mensaje!"; Flush_out;
              Pause();
              break;
          }
          case 3:{   // submenu
              Checking_submenu_archivo(menu, submenu_archivo);
              break;
          }
          case 4:{
              swFinaliza=1;
              break;
          }
      }
      break;
   }
}

void Checking_submenu_archivo(MT_CELL * menu, MT_CELL * submenu_archivo ){
   Put object submenu_archivo;
   int c2, op2=0;
   Waiting_some_clic(c2) 
   {
       op2 = Object_mouse( submenu_archivo );
       Refresh(video);
       Put object ctrl_archivo, ctrl_salir;
       switch ( op2 ){
           case 1:{  // primera opcion...
               inicia_proceso_apertura();
               break;
           }
           case 2:{   // 
               cierre_apertura();
               break;
           }
           case 3:{
               put_a_joke();
               break;
           }
           case 4:{
               change_option_menu( menu, submenu_archivo ); 
               break;
           }
       }
       break; // se sale porque sí
   }
}

GD_VIDEO draw_box ( GD_VIDEO video){

   String barra;
  // Get_fn_let( barra, Replicate(" ",84));
   char cColor[50];
   sprintf( cColor, "\033[38;5;%dm\033[48;5;%dm", CLR_FORE_MENU, CLR_BACK_MENU);
   Stack{
       Store ( barra, Multi_copy( barra, cColor, Replicate(" ",90), "\033[0m", NULL));
   } Stack_off;
   
   Gotoxy(video,4,4);
   Box(video, 25,90, SING_ALL );
  // Gotoxy(video, 6,4); Hline(video,90,SING_ALL);
   Outvid(video,5,5,barra);
  // Reset_text(video);

   Free secure barra;
   return video;
}

void change_option_menu( MT_CELL * menu, MT_CELL * submenu_archivo ) {

/* el tamaño del nuevo string debe ser consistente con el
   tamaño declarado inicialmente, porque sino se ve feo. */

   int stItem=0;
   if ( ( stItem = Status_item_menu( menu, 2 ) ) >= 0 ){
       if ( stItem ){
           Disable_item_menu( menu, 2 );
           Change_item_menu( submenu_archivo, " Activar \"Abrir reciente\" ", 4);
       }else{
           Enable_item_menu( menu, 2 );
           Change_item_menu( submenu_archivo, " Anular \"Abrir reciente\"  ", 4);
       }
   }else{
       Pause(); // para ver el mensaje de error.
       cambio_exitoso=0;
   }
   Refresh(video);
   Put object ctrl_archivo, ctrl_salir;

}

void inicia_proceso_apertura(){
   Refresh(video);
   Put object ctrl_archivo, ctrl_salir;
   At 17,15; Print "( )*( )";Flush_out;
   usleep(900000);
   At 17,15; Print "( )O( )";
   Flush_out;
   Pause();
}
void cierre_apertura(){
   Refresh(video);
   Put object ctrl_archivo, ctrl_salir;
   At 17,15; Print "( )O( )";Flush_out;
   usleep(900000);
   At 17,15; Print "( )*( )";
   Flush_out;
   Pause();
}

void put_a_joke(){
   Refresh(video);
   Put object ctrl_archivo, ctrl_salir;
   At 17,15; Print "-- ¿Qué le dijo un pescao a otro pescao?";
   At 18,15; Print "-- No sé...";
   At 19,15; Print "-- Le dijo: \"salta pa'lao, pescao\"...¡Espera! ¡No te vayas, no tengo amigos!";
   Flush_out;
   Pause();
}


