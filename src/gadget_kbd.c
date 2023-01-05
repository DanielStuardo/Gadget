
/************************************************************************
 *
 *            LIBRERIA DE TECLADO RAW MODE, KBHIT Y OTROS.
 *
 ************************************************************************/

/*#ifndef _LIB_GADGET_MAIN_

#ifdef GENLIB_GADGET*/
#include "../include/gadget.h"
/*#else
#include <gadget/gadget.h>
#endif

#endif*/

//#include <gadget/gadget_kbd.h>

/* PARA KBHIT() Y FUNCIONES DE TECLADO */
extern int BYTES_WAITING;
extern int SIZE_TERM_ROWS, SIZE_TERM_COLS;
extern struct termios __ORIGINAL_TERMIOS__;
extern int ENABLE_RAW_MODE;

extern int SCREEN_ROW;
extern int SCREEN_COL;
extern int Is_ok;


/* HABILITACION DE RAW-MODE Y FUNCIONES AD-HOC */

void __Die__(const char *s) {
  write(STDOUT_FILENO, "\x1b[2J", 4);
  write(STDOUT_FILENO, "\x1b[H", 3);

  perror(s);
 // exit(1);
}

/* devuelve el terminal a la normalidad.
   IMPORTANTE! debe pasar por aquí, o el terminal tendrá que ser cerrado.
   Esta función es llamada al final de la ejecución del programa, terminando
   normalmente. También puede ser llamada en cualqioer parte del programa.*/
void Disable_raw_mode() {
  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &__ORIGINAL_TERMIOS__) == -1)
    __Die__("tcsetattr");
  ENABLE_RAW_MODE=0;
}

/* habilita RAW-MODE */
void Enable_raw_mode() {
  if (tcgetattr(STDIN_FILENO, &__ORIGINAL_TERMIOS__) == -1) __Die__("tcgetattr");
  atexit(Disable_raw_mode);

  struct termios raw = __ORIGINAL_TERMIOS__;
  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) __Die__("tcsetattr");

  ENABLE_RAW_MODE=1;
}

/* Uso de teclado en modo RAW */

/* el famoso KBHIT() para Linux */
int Kbhit() {
    static const int STDIN = 0;

    //int bytesWaiting;
    ioctl(STDIN, FIONREAD, &BYTES_WAITING); //&bytesWaiting);
    return BYTES_WAITING; //bytesWaiting;
}


int __ReadKey__() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) { __Die__("read");return '\x1b'; }
  }
       
  if (c == '\x1b') {
    char seq[3];

    if (read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

    //   Gotoxy(19,10); printf("PASA %d\n",seq[0]);
    //   Gotoxy(20,10); printf("PASA %d\n",seq[1]);
    //   FlushOut
       
    if (seq[0] == '[') {    
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (read(STDIN_FILENO, &seq[2], 1) != 1) return '\x1b';
        
        if (seq[2] == '~') {
          switch (seq[1]) {
            case '1': return HOME_KEY;
            case '3': return DEL_KEY;
            case '4': return END_KEY;
            case '5': return PAGE_UP;
            case '6': return PAGE_DOWN;
            case '7': return HOME_KEY;
            case '8': return END_KEY;
          }
        } else if (seq[2]==59){
          switch(seq[1]){
            case(49): {
                char seqEsp[2];

                if (read(STDIN_FILENO, &seqEsp[0], 1) != 1) return '\x1b';
                if (read(STDIN_FILENO, &seqEsp[1], 1) != 1) return '\x1b';

                switch(seqEsp[0]){
                   case(50):{
                      switch( seqEsp[1] ){
                         case('A'): return SHIFT_ARROW_UP;
                         case('B'): return SHIFT_ARROW_DOWN;
                         case('C'): return SHIFT_ARROW_RIGHT;
                         case('D'): return SHIFT_ARROW_LEFT;
                      }
                   }case(51):{
                      switch( seqEsp[1] ){
                         case('A'): return ALT_ARROW_UP;
                         case('B'): return ALT_ARROW_DOWN;
                         case('C'): return ALT_ARROW_RIGHT;
                         case('D'): return ALT_ARROW_LEFT;
                      }                      
                   }case(53):{
                      switch( seqEsp[1] ){
                         case('A'): return CTRL_ARROW_UP;
                         case('B'): return CTRL_ARROW_DOWN;
                         case('C'): return CTRL_ARROW_RIGHT;
                         case('D'): return CTRL_ARROW_LEFT;
                      }
                   }
                }
            }
          }
       }
      } else {
        switch (seq[1]) {
          case 'A': return ARROW_UP;
          case 'B': return ARROW_DOWN;
          case 'C': return ARROW_RIGHT;
          case 'D': return ARROW_LEFT;
          case 'H': return HOME_KEY;
          case 'F': return END_KEY;
          case 'Z': return CTRL_TAB;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;
      }
    }
       
    return '\x1b';
  } else {
    return c;
  }
}

/* ambos deben trabajar con kbhit() */
int Getch(void) {
    int ch = __ReadKey__();
    //char ch = getchar();
    return ch;
}

char * Read_char(void){
   char * cs = calloc(BYTES_WAITING+1,1);
   int i;
   for( i = 0; i<BYTES_WAITING; ++i)
       cs[i] = Getch();
   cs[BYTES_WAITING]='\0';
   return cs;
}


void Get_size_terminal(){
   struct winsize w;
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
   SIZE_TERM_ROWS = (int) w.ws_row;
   SIZE_TERM_COLS = (int) w.ws_col;
}

int Pause(){
   int swEnableRaw=0;
   if (!ENABLE_RAW_MODE){  // no estáhabilitado raw mode??
       Enable_raw_mode();
       swEnableRaw=1;
   }
   
   while( Kbhit() ) Getch();
   int c = Getch();
   
   if(swEnableRaw){  // no estaba habilitado: deshabilito
       Disable_raw_mode();
   }
   return c;
}

void _imprime_input_item_array_(RDS(char *,array)){
   int i;
   for( i=0; i<array_data.len; i++)
      printf("%s",Cell(array,i));
   printf(" \b");
   Flush_out;
}

char * Input( char * cText, int nSpace ){

   int xh = SCREEN_ROW;
   int yh = SCREEN_COL;
   int pos = yh;

   int swEnableRaw=0;
   int /*lBuffer = 0,*/ ipos=0, swSigue=1;

   New_str_array(cBuffer);
   if(cText!=NULL){
      cBuffer = Split_char( cText, pSDS(cBuffer));
      while( nSpace < Len(cBuffer) ){
          cBuffer = Delete_lst( pSDS(cBuffer),nSpace);
          swSigue=0;
      }
      Goto_xy(xh,yh); _imprime_input_item_array_(SDS(cBuffer));
      pos = cBuffer_data.len + yh;
      ipos = cBuffer_data.len;
   }
   if ( nSpace<=0 ){
       nSpace=Len(cBuffer);
   }
   if (nSpace == 0){  // espacio==0 y cText=NULL
       sFree_array(cBuffer);
       char * retVal = Space( 1 );
       retVal[0]='\0';
       return retVal;
   }
   
   
   if (!ENABLE_RAW_MODE){  // no estáhabilitado raw mode??
       Enable_raw_mode();
       swEnableRaw=1;
   }
   Flush_out;

   int ckey=0;
   while( ckey!=ESCAPE && ckey != ENTER ){
       if ( Kbhit() ){
           ckey = Getch();
           ///Gotoxy(2,2); printf("%d,",ckey);
           switch ( ckey ){
               case BACKSPACE:{
                  if(ipos > 0 ){
                      if( ipos < cBuffer_data.len ){ // está entremedio del texto
                          cBuffer = Delete_lst( pSDS(cBuffer),ipos-1);
                          --ipos; --pos;
                          Goto_xy(xh,yh); _imprime_input_item_array_(SDS(cBuffer));
                          Goto_xy(xh,pos);Flush_out;
                          swSigue=1;
                          continue;
                      }
                  }else if( ipos==0 && cBuffer_data.len > 0 ){
                      
                      continue;
                  }
                  if( cBuffer_data.len > 1 ){
                     if( Cell(cBuffer,cBuffer_data.len-1) >= 0){
                         cBuffer = Delete_lst( pSDS(cBuffer),cBuffer_data.len-1);
                     }
                  }else{
                     sFree_array(cBuffer);
                  }
                  swSigue=1;
                  break;

               }case HOME_KEY:{
                  pos = yh; ipos = 0;
                  Goto_xy(xh, pos); Flush_out
                  continue;

               }case END_KEY:{
                  break;

               }case ARROW_LEFT: {
                  if( pos > yh){
                     Goto_xy(xh,--pos);Flush_out;
                     --ipos;
                  }
                  continue;

               }case ARROW_RIGHT: {
                  if (pos < cBuffer_data.len + yh){
                     Goto_xy(xh,++pos);Flush_out;
                     ++ipos;
                  }
                  continue;

               }case DEL_KEY: {
                  //if(ipos >= 0 ){
                      if( ipos < cBuffer_data.len ){ // está entremedio del texto
                          cBuffer = Delete_lst( pSDS(cBuffer),ipos);
                          swSigue=1;
                         // if ( cBuffer != NULL ){
                             Goto_xy(xh,yh); _imprime_input_item_array_(SDS(cBuffer));
                         // }
                          
                          //Goto_xy(10,10); printf("LEN (del_key)= %d  ",cBuffer_data.len);Flush_out;
                          
                          Goto_xy(xh,pos);Flush_out;
                          
                          swSigue=1;
                      }else{
                          //sFree_array(cBuffer);
                          swSigue=1;
                      }
                      continue;
                 // }
                  //break;
               
               }case ENTER: case ESCAPE: case PAGE_UP: case PAGE_DOWN:
                case SHIFT_ARROW_UP: case SHIFT_ARROW_DOWN: case SHIFT_ARROW_RIGHT: case SHIFT_ARROW_LEFT:
                case ALT_ARROW_UP: case ALT_ARROW_DOWN: case ALT_ARROW_RIGHT: case ALT_ARROW_LEFT:
                case CTRL_ARROW_UP: case CTRL_ARROW_DOWN: case CTRL_ARROW_RIGHT: case CTRL_ARROW_LEFT:
                case CTRL_TAB: case Ctrl_key('s'): case Ctrl_key('z'): case Ctrl_key('j'):
                case Ctrl_key('q'):case Ctrl_key('w'):case Ctrl_key('e'):case Ctrl_key('r'):
                case Ctrl_key('t'):case Ctrl_key('i'):case Ctrl_key('h'):case Ctrl_key('k'):case Ctrl_key('l'):
                case ARROW_UP: case ARROW_DOWN: {
                  break;
               }default: {
                  int tkey=0;
                  if( ckey < 0 )  tkey=Getch();
                  if (swSigue){
                      if ( ipos < cBuffer_data.len ) { // inserta
                          char tbuff[10];
                          if( tkey)
                              sprintf(tbuff,"%c%c",ckey,tkey);
                          else
                              sprintf(tbuff,"%c",ckey);
                          New_str_array(tarr);
                          sAppend(tarr,tbuff);
                          cBuffer = Insert_lst( pSDS(cBuffer), pSDS(tarr), ipos);
                          sFree_array(tarr);
                          ++ipos; ++pos;
                          Goto_xy(xh,yh); _imprime_input_item_array_(SDS(cBuffer));
                          Goto_xy(xh,pos);Flush_out;
                          if (cBuffer_data.len >= nSpace-1 ){  // se acaba el ingreso
                              swSigue=0;
                          }else{
                              swSigue=1;
                          }
                          continue;
                      }else{   // añade
                      
                          char tbuff[10];
                          if( tkey)
                              sprintf(tbuff,"%c%c",ckey,tkey);
                          else
                              sprintf(tbuff,"%c",ckey);

                          sAppend(cBuffer, tbuff);
                          if (cBuffer_data.len >= nSpace-1 ){  // se acaba el ingreso
                              swSigue=0;
                          }else{
                              swSigue=1;
                          }
                      }
                  }else continue;
               }
           }
           pos = cBuffer_data.len + yh;
           ipos = cBuffer_data.len;

           Goto_xy(xh,yh); _imprime_input_item_array_(SDS(cBuffer));
           
           //Goto_xy(10,10); printf("LEN (general)= %d  ",cBuffer_data.len);
           Flush_out;
       }
   }
   
   if(swEnableRaw){  // no estaba habilitado: deshabilito
       Disable_raw_mode();
   }
   int i;
   char * retVal = Space( cBuffer_data.len + 1 );
   for(i=0;i<cBuffer_data.len;i++){
       Cat(retVal,Cell(cBuffer,i));
   }
   sFree_array(cBuffer);
   return retVal;
}

