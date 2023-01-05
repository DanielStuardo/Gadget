

#include <gadget/gadget.h>

LIB_GADGET_START

#define CLR_FORE   15
#define CLR_BACK   0

Main
   Cls;

/*   GD_VIDEO video;
   Init_video( &video );
 */  
   Gpm_Connect conn;

   if ( ! Init_mouse(&conn)){
        perror("No se puede conectar al servidor del ratón\n");
        Stop(1);
   }  
   Enable_raw_mode();

New objects Rbtn;
New multitype opciones;
   Append_mt(opciones,int,1); sAppend_mt(opciones,"La paraguaya");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"el vuelo del cóndor");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"el pingüino");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"el \"wena Naty\"");
   Append_mt(opciones,int,0); sAppend_mt(opciones,"la paja arriesgada");
   
   Rbtn = New_object_mouse( SMD(&Rbtn), RADIO_BUTTOM, SDS(opciones), 11,45, 121,25 );   
   
   New objects btn, btn2;
   btn = New_object_mouse( SMD(&btn), BUTTOM, " Select ", 5,33, CLR_FORE, CLR_BACK);
   btn2 = New_object_mouse( SMD(&btn2), BUTTOM, " Active ", 9,33, CLR_FORE, CLR_BACK);
   
   Disable_object( btn );
   Disable_object( Rbtn );
   Put object btn, btn2;
   Put object Rbtn;
   int c;
   int opcion_rbtn=1;
   Waiting_some_clic(c) 
   {
       if (Object_mouse( btn2 )){
           Enable_object( btn );
           Enable_object( Rbtn );
       }else if (Object_mouse( btn )){
           break;
       }
       opcion_rbtn = Object_mouse( Rbtn );
       
       Put object btn, btn2;
       Put object Rbtn;
   }
   Reset_color;
   Disable_raw_mode();

   Prnl;
/*   int i;
   Iterator up i [0:1:btn_data.len]{
       Print "POS = %d : ",i; 
       Print_Cell( btn, i); Prnl
       Pause();
   }   */
   
   Free object btn,btn2,Rbtn;
   Free multitype opciones;
   
   Close_mouse();
   
End
