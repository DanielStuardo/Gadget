
#include <gadget/gadget.h>

LIB_GADGET_START


void Evaluar_posibilidades(int tiene_auto, int tiene_casa, int quiere){
   At 15,5;
   if ( quiere ){
       if ( tiene_auto ){
           if ( tiene_casa ){
               Print "¿Qué espera que no le pone los cuernos?";
           }else{
               Print "Hágale la cochiná en el ring de 4 ruedas";
           }
       }else{
           if ( tiene_casa ){
               Print "Lleve a la cochina a la playa en bus y enchúfesela";
           }else{
               Print "Mejor no engañe a su mujer, pasará vergüenza";
           }
       }
   }else{
       if ( tiene_auto ){
           if ( tiene_casa ){
               Print "Usted es un hombre íntegro..."; Flush_out;
               sleep(2);
               At 16,10; Print "íntegramente "; 
               Bold; Print "hueón."; Bold_off;
               Flush_out;
           }else{
               Print "Vaya a correrse una a la carretera";
           }
       }else{
           if ( tiene_casa ){
               Print "Lleve a su esposa a la casa, en bus, y enchúfesela";
           }else{
               Print "Hágase un pan con margarina \"Doña Juanita\"";
           }
       }       
   }
}

void Imprime_box(){
   At 4,2; Color_fore(121); 
   Print "Consejos del Dr. Cariño:";
   At 5,2;
   Solid_box_std(15,60,103,25); 
   At 21,2; Color_fore(203); Print "Haga clik en los casilleros para seleccionar";
   At 22,2; Print "Haga clik en \"[ Consultar ]\" para ver el consejo";
   Reset_color;
}

void Imprime_cuestionario(int ta, int tc, int qe, int nColor){

   char *no_w = " "; //"✘";  // Mayuscula+Ctrl+u => 2718
   char *w = "\u2714"; //"✔";     // Mayuscula+Ctrl+u => 2714
   
   Color(121,nColor);
   At 7,5; Print "❲%s❳ Usted quiere engañar a su mujer ", qe ? w : no_w;
   At 8,5; Print "❲%s❳ Usted tiene auto que no es Maruti ", ta  ? w : no_w;
   At 9,5; Print "❲%s❳ Usted tiene una casa en la playa ", tc ? w : no_w;
   
   At 11,5; Print "╭─────────────╮";
   At 12,5; Print "│ Consultar ✔ │";
   At 13,5; Print "╰─────────────╯";
   
   Flush_out;
}


Main
   
   int tiene_auto = 0, tiene_casa = 0, quiere = 0;

   Cls;

   Gpm_Connect conn;
   
   if ( ! Init_mouse(&conn)){
        perror("No se puede conectar al servidor del ratón\n");
        Stop(1);
   }  
   Enable_raw_mode();

   Hide_cursor;
   Imprime_box();
   Imprime_cuestionario(tiene_auto, tiene_casa, quiere, 25);

   int c;
   Waiting_some_clic(c) 
   {
   
       if ( Is_between( MPOS_COL,5,43 ) ){
           if ( MPOS_ROW == 7 ) quiere = quiere ? 0 : 1;
           else if ( MPOS_ROW == 8 ) tiene_auto = tiene_auto ? 0 : 1;
           else if ( MPOS_ROW == 9 ) tiene_casa = tiene_casa ? 0 : 1;
       }

      if ( Is_range_box(11,5,13,19) ) break;

    /* un poco de efectos especiales innecesarios */
      if ( Is_range_box_excluding(5,2,20,62) ){
           At 5,2;  Solid_box_std(15,60,187,68);
           Imprime_cuestionario(tiene_auto, tiene_casa, quiere, 68);
           usleep(80000); Reset_color;
           At 5,2;  Solid_box_std(15,60,103,25);
      }
      Imprime_cuestionario(tiene_auto, tiene_casa, quiere, 25);
   }
   
   Evaluar_posibilidades(tiene_auto, tiene_casa, quiere);

   Show_cursor;
   Reset_color;
   Disable_raw_mode();
   Close_mouse();
   At 25,0;
End

