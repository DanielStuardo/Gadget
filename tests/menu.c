
#include <gadget/gadget.h>

LIB_GADGET_START

#define CLR_FORE   15
#define CLR_BACK   0

Main

   Gpm_Connect conn;

   if ( ! Init_mouse(&conn)){
        perror("No se puede conectar al servidor del ratón\n");
        Stop(1);
   }  
   Enable_raw_mode();
   Hide_cursor;   
   
   New object ctrl_archivo,ctrl_salir, menu, submenu_archivo;
   
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
   
   $valid[1] = 0;  // invalido la opción 2. Esto puede cambiar en tiempo de ejecucion
   
   ctrl_archivo = New_object_mouse(SMD(&ctrl_archivo), BUTTOM_PINBALL, " Archivo ", 5,5, CLR_FORE,CLR_BACK);
   ctrl_salir = New_object_mouse(SMD(&ctrl_salir), BUTTOM_PINBALL, " Salir ", 5,16, CLR_FORE+170,CLR_BACK);
   menu = New_object_mouse(SMD(&menu),CHOICE, SDS(opts), SDS(valid), 6,5);
   submenu_archivo = New_object_mouse(SMD(&submenu_archivo),CHOICE,SDS(opts2),SDS(valid2), 8,23);

   Cls;
   Put object ctrl_archivo, ctrl_salir;
   
   int c;
   int swFinaliza=0;

   Waiting_some_clic(c) 
   {
       if( Object_mouse( ctrl_archivo ) ){
           Put object menu;
           int c1, op=0;
           Waiting_some_clic(c1) 
           {
               if( (op = Object_mouse( menu ) ) ){
                   switch ( op ){
                       case 1:{  // primera opcion...
                           At 17,15; Print "Opcion 1 del menu"; Flush_out;
                           Pause();
                           break;
                       }
                       case 2:{  // primera opcion...
                           break;
                       }
                       case 3:{   // submenu
                           Put object submenu_archivo;
                           int c2, op2=0;
                           Waiting_some_clic(c2) 
                           {
                               if( (op2 = Object_mouse( submenu_archivo )) ){
                                   switch ( op2 ){
                                       case 1:{  // primera opcion...
                                            At 17,15; Print "( )*( )";Flush_out;
                                            usleep(900000);
                                            At 17,15; Print "( )O( )";
                                            Flush_out;
                                            Pause();
                                            break;
                                       }
                                       case 2:{   // 
                                            At 17,15; Print "( )O( )";Flush_out;
                                            usleep(900000);
                                            At 17,15; Print "( )*( )";
                                            Flush_out;
                                            Pause();
                                            break;
                                       }
                                       case 3:{
                                            At 17,15; Print "-- ¿Qué le dijo un pescao a otro pescao?";
                                            At 18,15; Print "-- No sé...";
                                            At 19,15; Print "-- Le dijo: \"salta pa'lao, pescao\"...¡Espera! ¡No te vayas, no tengo amigos!";
                                            Flush_out;
                                            Pause();
                                            break;
                                       }
                                       case 4:{

                                            if ( !$valid[1] ){
                                                $valid[1] = 1;
                                                Let ( opts2[3], " Anular \"Abrir reciente\"  ");
                                            }else{
                                                $valid[1] = 0;
                                                Let ( opts2[3], " Activar \"Abrir reciente\" ");
                                            }
                                            Free object menu, submenu_archivo;
                                            menu = New_object_mouse(SMD(&menu),CHOICE, SDS(opts), SDS(valid), 6,5);
                                            submenu_archivo = New_object_mouse(SMD(&submenu_archivo),CHOICE,SDS(opts2),SDS(valid2), 8,23);
                                            
                                            break;
                                       }
                                   }
                               }
                               break; // se sale porque sí
                           }
                           break;
                       }
                       case 4:{
                           swFinaliza=1;
                           break;
                       }
                   }
               }
               break;
           }
       }

       if(swFinaliza) break;
       if( Object_mouse(ctrl_salir)) break;
       /* puede ser un Refresh(video) y evita el Cls...*/
       Cls;
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
      
   Free objects ctrl_archivo, ctrl_salir, menu, submenu_archivo;
   Show_cursor;
   At 30,1;
End


