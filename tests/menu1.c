
#include <gadget/gadget.h>

LIB_GADGET_START

#define CLR_FORE   15
#define CLR_BACK   0

void inicia_proceso_apertura();
void cierre_apertura();
void put_a_joke();
GD_VIDEO draw_box ( GD_VIDEO video);
/* Solo son necesarions parámetros MT_CELL porque no cambiará el número de opciones
   de los menús. Si va a cambiar al número de opciones, debe declarar pSDS().
   La otra opción es que declare esos objetos como GLOBALES, y podrá modificarlos
   a su antojo en cualquier parte del programa */
void change_option_menu( int valid[], char *opts2[] );
void Checking_submenu_archivo(MT_CELL * submenu_archivo, int valid[], char *opts2[]);
void Checking_main_menu_archivo(MT_CELL * menu, MT_CELL * submenu_archivo, int valid[], char *opts2[]);

/* variables globales */
int swFinaliza;
int swRefreshMenu;
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
   
   //ctrl_archivo = New_object_mouse(SMD(&ctrl_archivo), BUTTOM_PINBALL, " Archivo ", 5,5, 232,247);// CLR_FORE,CLR_BACK);
   ctrl_archivo = New_object_mouse(SMD(&ctrl_archivo), CONTROL, " Archivo ", 5,6, 232,247);
   //ctrl_salir = New_object_mouse(SMD(&ctrl_salir), BUTTOM_PINBALL, " Salir ", 5,16, 232,247);// CLR_FORE+170,CLR_BACK);
   ctrl_salir = New_object_mouse(SMD(&ctrl_salir), CONTROL, " Salir ", 5,15, 232,247);// CLR_FORE+170,CLR_BACK);
   
   video = draw_box( video );

//   Cls;   
   Refresh(video);
   Put object ctrl_archivo, ctrl_salir;
   
   int c;
   swFinaliza=0;
   swRefreshMenu=0;
   Waiting_some_clic(c) 
   {
       if( Object_mouse( ctrl_archivo ) ){
           Checking_main_menu_archivo(menu, submenu_archivo, valid, opts2);
       }
       
       if( swRefreshMenu ){
           Free object menu, submenu_archivo;
           menu = New_object_mouse(SMD(&menu),CHOICE, SDS(opts), SDS(valid), 6,5);
           submenu_archivo = New_object_mouse(SMD(&submenu_archivo),CHOICE,SDS(opts2),SDS(valid2), 8,23);
           swRefreshMenu=0;
       }

       if(swFinaliza) break;
       if( Object_mouse(ctrl_salir)) break;
       /* puede ser un Refresh(video) y evita el Cls...*/
       //Cls;
       Refresh(video);
       Put object ctrl_archivo, ctrl_salir;
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
End


void Checking_main_menu_archivo(MT_CELL * menu, MT_CELL * submenu_archivo, int valid[], char *opts2[]){
   Put object menu;
   int c1, op=0;
   Waiting_some_clic(c1) 
   {
      op = Object_mouse( menu );
      
      switch ( op ){
          case 1:{  // primera opcion...
              Refresh(video);
              Put object ctrl_archivo, ctrl_salir;
              At 17,15; Print "Opcion 1 del menu"; Flush_out;
              Pause();
              break;
          }
          case 2:{  // segunda opcion inicialmente desactivada...
              Refresh(video);
              Put object ctrl_archivo, ctrl_salir;
              At 17,15; Print "Ahora puedes ver este precioso mensaje!"; Flush_out;
              Pause();
              break;
          }
          case 3:{   // submenu
              Checking_submenu_archivo(submenu_archivo,valid, opts2);
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

void Checking_submenu_archivo(MT_CELL * submenu_archivo, int valid[], char *opts2[] ){
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
               change_option_menu( valid, opts2 );
               swRefreshMenu=1;
               break;
           }
       }
       break; // se sale porque sí
   }
}

GD_VIDEO draw_box ( GD_VIDEO video){

   String barra;
  // Get_fn_let( barra, Replicate(" ",84)); 
   Stack{
       Store ( barra, Multi_copy( barra, "\033[38;5;232m\033[48;5;247m", Replicate(" ",90), "\033[0m", NULL));
   } Stack_off;
   
   Gotoxy(video,4,4);
   Box(video, 25,90, SING_ALL );
  // Gotoxy(video, 6,4); Hline(video,90,SING_ALL);
   Outvid(video,5,5,barra);
  // Reset_text(video);

   Free secure barra;
   return video;
}

void change_option_menu( int valid[], char *opts2[] ){

/* el tamaño del nuevo string debe ser consistente con el
   tamaño declarado inicialmente, porque sino se ve feo. */
   Refresh(video);
   Put object ctrl_archivo, ctrl_salir;

   if ( !valid[1] ){
       valid[1] = 1;
       Let ( opts2[3], " Anular \"Abrir reciente\"  ");
   }else{
       valid[1] = 0;
       Let ( opts2[3], " Activar \"Abrir reciente\" ");
   }
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


