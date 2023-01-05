#include <gadget/gadget.h>

LIB_GADGET_START

Main
   Cls;
   Hide_cursor;
      
      /* 
         GET_CHOICE funciona con arrays dinámicos y estaticos. Si es dinámico, debe ser eliminado.
         Las opciones se cuentan desde 0. 
         Si usa arrays dinámicos, tiene la posibilidad de añadir y borrar opciones en tiempo de
         ejecución.
         Necesita un array de opciones, un array de opciones válidas, y un array de condicion.
         El array de condición almacenará la opción elegida, y los datos del despliegue del menú
         de selección, los que serán útiles si se desea poner submenús.
         
         OPCIONES:
         ESCAPE = No escoge nada. Devuelve -1.
         ENTER  = escoge la opcion.
         CTRL-ARROW-UP = va al inicio.
         CTRL-ARROW-DOWN = va al final.
         El ancho de la ventana lo dará el tamaño de las copciones. Cuide de dejar cosas como esta:
         " Abrir archivo "
         " Cerrar        "
         " Preferencias  "
         etc.
         
         Si quiere programar un submenú, USTED DEBE USAR el símbolo "»" en la opción, como se ve en
         el ejemplo, porque Get_choice responderá a ARROW_RIGHT solo si ve ese símbolo en la opción.
         Si no ve ese simbolo, Get_choice reaccionará a ENTER.
      */
      /* este array podría ser dinámico */
      char * opciones[]={" opción  1   "," opción  2   "," opción  3   "," opción  4   "," opción  5   "," opción  6   "," opción  7   ",
                         " opción  8   "," opción  9   "," opción 10   "," opción 11   "," opción 12   "," opción 13   "," opción 14   ",
                         " opción 15   "," opción 16 » "," opción 17   "," opción 18   "," opción 19   "," opción 20   "," opción 21   ",
                         " Salir       "};
      /* este array podría ser dinámico */
      int validos[]={1,1,1,1,1,0,0,1,1,1,1,0,1,0,1,1,1,1,0,1,0,1};
      /* este array NO PUEDE ser dinámico */
      int condiciones[]={0,0,0};

      int opcion=0;
      while( opcion != -1 ){
          fflush(stdin);
          Gotoxy(5,10);
          opcion = Get_choice( opciones, validos, condiciones, sizeof(opciones)/sizeof(char*),
                                /* altura ventana */8, 
                               /*color fore normal*/  1,/*color back normal*/2,
                               /*color highligh fore*/1,/*color hl back*/15 );
      
          if ( opcion == 15 ){
              char * subop[]={" Iniciar proceso apertura ",
                              " Cerrar apertura          ",
                              " Chiste...                "};
              int subval[3]={1,1,1}; 
             /*
              Get_choice() devuelve la posición del cursor correspondiente a la última opción elegida,
              pero lo hace con las variables internas SCREEN_ROW y SCREEN_COL.
              Esto significa que no es necesario posicionar el submenu a continuación.
             */
              int subcond[]={0,0,0};
              int opcion2 = Get_choice( subop, subval, subcond,sizeof(subop)/sizeof(char*), 
                                        3,121,4,1,15);
              Reset_color;
              if( opcion2 == 0 ){
                  At 17,15; Print "( )*( )";Flush_out;
                  usleep(900000);
                  At 17,15; Print "( )O( )";
                  Flush_out;
                  Pause();
              }
              else if( opcion2 == 1 ){
                  At 17,15; Print "( )O( )";Flush_out;
                  usleep(900000);
                  At 17,15; Print "( )*( )";
                  Flush_out;
                  Pause();
              
              }
              else if( opcion2 == 2 ){
                  At 17,15; Print "-- ¿Qué le dijo un pescao a otro pescao?";
                  At 18,15; Print "-- No sé...";
                  At 19,15; Print "-- Le dijo: \"salta pa'lao, pescao\"...¡Espera! ¡No te vayas, no tengo amigos!";
                  Flush_out;
                  Pause();
              }
          }else if (opcion == 21 ){
              break;
          }else{
              Reset_color;
              At 15,5; Print "Opcion elegida = %d\n", opcion; Flush_out;
              Pause();
          }
          Reset_color;
          Cls;
      }
      
      Reset_color;

   Show_cursor;
End
