
#include <gadget/gadget.h>

LIB_GADGET_START

/* esta función está incluida en GADGET
   con el nombre: Get_char_stdin().
   Sólo funciona en modo RAW */
char* get_char_stdin()
{
    int i=0;
    Str_init(c);c=Space(10);
    c[i] = getc(stdin);
    while ( Is_neg(c[i++]) && LEN_TYPED_STRING ) { 
        c[i] = getc(stdin);
        if ( Is_pos( c[i] ) ) { ungetc(c[i], stdin); break; }
        else --LEN_TYPED_STRING; 
    }
    c[i]='\0';
    return c;
}

Main
   Enable_raw_mode();
   int tecla=0;
   int t=0;
   while (tecla!=27 ){
       /* TYPED_STRING se activa cuando se usa Put_kbd_text(), pero esto
          trabaja directamente con STDIN */
       if ( !TYPED_STRING ){
           while ( Kbhit() ){
               tecla = Getch();
               Disable_raw_mode();
               printf("TECLA = %d\n",tecla);
               Enable_raw_mode();
           }
       }else{
           //Disable_raw_mode(); --> no usar: afecta STDIN
           //printf("\nTYPED_STRING = %d\n",TYPED_STRING);
           //printf("LEN_TYPED_STRING = %d\n",LEN_TYPED_STRING);
           //Enable_raw_mode();

           while ( LEN_TYPED_STRING && !feof(stdin) ){
               char* c = Get_char_stdin();
               Print "%s,", c;

               Free secure c;
               --LEN_TYPED_STRING;
               Clamp( LEN_TYPED_STRING, 0, LEN_TYPED_STRING);
           }
           Flush_out;
           Disable_raw_mode(); Prnl; Enable_raw_mode();
               
           TYPED_STRING=0;

       }
       usleep(100);
       ++t;
       if ( t==10000 ){
           system("xdotool key Return");
       }else if( t==11000 ){
          // Mi teclado actual es del MacBook Pro.
          // En otro tipo de teclado, el código puede cambiar.
          // consulte X11/keysymdef.h para más informacion.
           Key_put(KEYP_ENTER);

       }else if( t==12000 ){
           Key_put(KEYP_LEFT);

       }else if( t==13000 ){
           Key_put(KEYP_RIGHT);
           
       }else if( t==14000 ){
           Key_put(KEYP_UP);

       }else if( t==15000 ){
           Key_put(KEYP_DOWN);
           
       }else if( t==16000 ){
           Key_put(KEYP_PAGEUP);
       }else if( t==17000 ){
           Key_put(KEYP_PAGEDOWN);

       }else if( t==18000 ){
           Key_put(KEYP_HOME);
       }else if( t==19000 ){
           Key_put(KEYP_END);
       }else if( t==20000 ){
           Key_put(' ');
       }else if( t==21000 ){
           Key_put(KEYP_BACKSP);
       }else if( t==22000 ){
           Key_put(KEYP_TAB);
       }else if( t==23000 ){
           Key_put(KEYP_DELETE);

       }else if( t==24000 ){
           Key_put_ctrl('a');
       }else if( t==24100 ){
           Key_put_ctrl('b');
       }else if( t==24200 ){
           Key_put_ctrl('w');

       }else if( t==24300 ){
           Key_put_shift('a');

       }else if( t==25000 ){
           Put_kbd_text("Hola mundo[](){Máscara},.:;-_=?$%&/#@! \t<cruel>\n Año 2023");
           
       }else if( t>=28000 ){
           Key_put(KEYP_ESCAPE);
       }
   }

  // Put_kbd_text() reconoce estos caracteres: otros caracteres, el
  // resultado puede ser indefinido.

  /*  Put_kbd_text("Hola mundo[](){},.:;-_=?$%&/#@! \t<cruel>\n Año 2023");
   
     String read;
   // si no se ha puesto nada en el buffer de entrada con Put_kbd_text(),
   // read será NULL:
     read = Read_typed_string();
   
     Disable_raw_mode();
     if ( read){
         printf("\nTEXTO = %s\nChar = %d\n",read, read[strlen(read)-1]);
     }
     free(read);*/
End

