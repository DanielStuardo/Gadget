
#include <gadget/gadget.h>

LIB_GADGET_START

Main    
  int tecla=0;
  int x = 10, y = 1;
//  int max_y = 0, max_x = 0;
  int next_y = 0;
  int direction = 1;
  int DELAY=30000;

//    OpenBuffer

    Cls

    Gotoxy(1,1);printf ("Pulse cualquier tecla: \n"); Getch();

    /* Recibir teclas en modo sin buferes (es decir, sin esperar a que se
     * pulse ENTER) */

    Get_size_terminal(); //getmaxyx(stdscr, max_y, max_x);
    Hide_cursor;

    Enable_raw_mode();
 while(tecla!='.' && tecla!=13) {
    Cls
    Gotoxy(x,y) ; printf("o"); Flush_out;
    
    if ( Kbhit() ){
       tecla = Getch();
       printf("TECLA = %d\n",tecla);
       if(tecla == ARROW_LEFT ) DELAY+=100;
       if(tecla == ARROW_RIGHT ) DELAY-=100;
       if(tecla == ARROW_UP )   --x;
       if(tecla == ARROW_DOWN ) ++x; 
       Flush_in;
    }
    usleep(DELAY);

    next_y = y + direction;

    if (next_y >= SIZE_TERM_COLS || next_y < 0) {
       direction*= -1;
    } else {
       y+= direction;
    }
 }
 Show_cursor;
 Cls;
// DisableRawMode();
 
// Gotoxy(20,5);   printf ("Pulse cualquier tecla para finalizar"); fflush(stdout);
// Getch();
// CloseBuffer
End
