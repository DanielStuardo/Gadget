
#include <gadget/gadget.h>

LIB_GADGET_START


void Evaluar_posibilidades(int tiene_auto, int tiene_casa, int quiere, int opcion){
   At 16,5;
   if ( quiere ){
       if ( tiene_auto ){
           if ( tiene_casa ){
               Print "¿Qué espera que no le pone los cuernos?";
               At 17,5; Print "Y dígale que le haga eso que escogió";
           }else{
               Print "Hágale la cochiná en el ring de 4 ruedas";
               At 17,5; 
               if( Is_between(opcion,4,5) ){
                  Print "Y dígale que la haga eso que escogió";
               }else{
                  Print "Pero no va a poder hacer lo que escogió";   
               }
           }
       }else{
           if ( tiene_casa ){
               Print "Lleve a la cochina a la playa en bus y enchúfesela";
           }else{
               Print "Mejor no engañe a su mujer, pasará vergüenza";
               At 17,5; 
               if( opcion==5 ){
                   Print "La opcion escogida es la única hueá que puede hacer";
               }else{
                   Print "Y no se moleste ná en hacer lo que escogió";
               }
           }
       }
   }else{
       if ( tiene_auto ){
           if ( tiene_casa ){
               Print "Usted es un hombre íntegro..."; Flush_out;
               sleep(2);
               At 17,10; Print "íntegramente "; 
               Bold; Print "hueón."; Bold_off;
               Flush_out;
           }else{
               Print "Vaya a sacudirse la nutria a la carretera";
           }
       }else{
           if ( tiene_casa ){
               Print "Lleve a su esposa a la casa, en bus, y enchúfesela";
               At 17,5;
               Print "Y hágale eso que escogió...";
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
   Solid_box_std(17,65,103,25);
   At 22,2; Color_fore(203); Print "Haga clik en los casilleros para seleccionar";
   At 23,2; Print "Haga clik en \"[ Consultar ]\" para ver el consejo";
   Reset_color;
}

Main

   int tiene_auto = 0, tiene_casa = 0, quiere = 1;
   int opcion_rbtn = 0;
   
   Cls;

   Gpm_Connect conn;

   if ( ! Init_mouse(&conn)){
        perror("No se puede conectar al servidor del ratón\n");
        Stop(1);
   }  
   Enable_raw_mode();

   Hide_cursor;
   Imprime_box();

/*   Base_object_mouse(sel1);
   Base_object_mouse(sel2);
   Base_object_mouse(sel3);
   Base_object_mouse(Btn);*/
   New objects sel1, sel2, sel3;     /* items de seleccion multiple */
   New objects Btn, Btn2, Btn3,Btn4; /* botones varios */
   New objects Rbtn;                 /* radio-buttoms*/

   sel1 = New_object_mouse( SMD(&sel1), SELECT, 1, "Usted quiere engañar a su mujer,\n"
                                                   "es vivaracho el hombre.", 7,5, 121,25);
   sel2 = New_object_mouse( SMD(&sel2), SELECT, 0, "Usted tiene auto que no es Maruti", 9,5,121,25);
   sel3 = New_object_mouse( SMD(&sel3), SELECT, 0, "Usted tiene una casa en la playa", 10,5,121,25);
   
   Disable_object(sel1);
   
   Btn = New_object_mouse( SMD(&Btn), BUTTOM, " Consultación ", 12,5, 121,25);
   Btn2 = New_object_mouse( SMD(&Btn2), BUTTOM, " enable all ", 12,23,121,25);
   Btn3 = New_object_mouse( SMD(&Btn3), BUTTOM_EYE, " Náditá ", 13,45,121,25);
   Btn4 = New_object_mouse( SMD(&Btn4), BUTTOM_PINBALL, " Nada ", 14,45,121,25);
  
   Disable_object(Btn3); Disable_object(Btn4);
   
  /* opciones para radio button */ 
   New multitype opciones;
   Append_mt(opciones,int,1); sAppend_mt(opciones,"La paraguaya");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"el vuelo del cóndor");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"el pingüino");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"el \"wena Naty\"");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"la paja arriesgada");
   
   Rbtn = New_object_mouse( SMD(&Rbtn), RADIO_BUTTOM, SDS(opciones), 7,45, 121,25 );

   Color(121,25);
   Put objects sel1, sel2, sel3, Btn, Btn2, Btn3, Btn4;
   Put object Rbtn;

   int c;
   Waiting_some_clic(c) 
   {
       if ( Object_mouse( sel1 ) )   quiere = quiere ? 0 : 1;
       else if ( Object_mouse( sel2 ) )   tiene_auto = tiene_auto ? 0 : 1;
       else if ( Object_mouse( sel3 ) )   tiene_casa = tiene_casa ? 0 : 1;

       if (Object_mouse( Btn)) break;
       if (Object_mouse( Btn2) ) { 
           Enable_object(sel1);
           Enable_object(Btn3);
           Enable_object(Btn4);
       }
       if (Object_mouse( Btn3)|| Object_mouse( Btn4)) ;

       opcion_rbtn = Object_mouse( Rbtn ); /* debe pasar por aquí para chequear la
                                              opcion elegida */

       /*Put_object_mouse(sel1);
       Put_object_mouse(sel2);
       Put_object_mouse(sel3);
       Put_object_mouse(Btn);*/
       Put objects sel1, sel2, sel3, Btn, Btn2, Btn3, Btn4;
       Put object Rbtn;
   }
   
   Color(121,25);
   Evaluar_posibilidades(tiene_auto, tiene_casa, quiere, opcion_rbtn);
   
//   At 19, 5; Print "Escogió la opción de RADIO-BUTTON: %d", opcion_rbtn;
   
   /*Free_object_mouse(sel1);
   Free_object_mouse(sel2);
   Free_object_mouse(sel3);
   Free_object_mouse(Btn);*/
   Free objects sel1, sel2, sel3, Btn2, Btn, Btn3, Btn4;
   Free multitype opciones;

   Free object Rbtn;

   Show_cursor;
   Reset_color;
   Disable_raw_mode();

/*   int i;
   Iterator up i [0:1:Rbtn_data.len]{
       Print_Cell( Rbtn, i); Prnl
   }   
   Free object Rbtn;*/
      
   Close_mouse();
   At 25,0;
End

