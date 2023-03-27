/*************************************************************************/
/*                                                                       */
/*                        CONWAY's GAME OF LIFE                          */
/*                        Author : Vishal Nagda                          */
/*                                                                       */
/*************************************************************************/

// rxvt -g 140x70 -fn "xft:FantasqueSansMono-Regular:pixelsize=3" -e ./gamelife

#include <gadget/gadget.h>

LIB_GADGET_START

#define DIR_LEFT  -1
#define DIR_RIGHT  1
#define size      120
#define sizec     100


const char* heroe[4]={"\x1b[38;5;245m  ▟┃▙ ",
                      "\x1b[38;5;15m ▟█░█▙ ",
                      "\x1b[38;5;15m ▜███▛ ",
                      "\x1b[38;5;245m  ▜█▛ "};

const char* red_point[3] = {"\x1b[38;5;196m▄██▄","\x1b[38;5;196m████","\x1b[38;5;196m▀██▀"};
const char* green_point[3] = {"\x1b[38;5;46m▄██▄","\x1b[38;5;46m████","\x1b[38;5;46m▀██▀"};
const char* blue_point[3] = {"\x1b[38;5;19m▄██▄","\x1b[38;5;19m████","\x1b[38;5;19m▀██▀"};
const char* black_point[3] = {"\x1b[38;5;232m▄██▄","\x1b[38;5;232m████","\x1b[38;5;232m▀██▀"};

const char* letters[3][37]={{"╭━╮","┏━╮","╭━┓","┏━╮","╭━┓","╭━┓","╭━┓","┳ ┳"," ┳ ","  ┳","┳┏ ","┳  ","╭┳╮","╭━╮","╭━╮","┏━╮","╭━╮","┏╮ ","╭━┓","━┳━","┳ ┳","┳ ┳","┳ ┳","┏┓┳","┳ ┳","┏━┓"," ","╭╮"," ","╭━╮"," "," "," "," ","┏","┓","▛"},  
                            {"┣━┫","┣━┫","┃  ","┃ ┃","┣━ ","┣━ ","┃━┓","┣━┫"," ┃ ","  ┃","┣┻╮","┃  ","┃┃┃","┃ ┃","┃ ┃","┣━╯","┃ ┃","┣┻╮","╰━╮"," ┃ ","┃ ┃","┃┏╯","┃┃┃","╭╋╯","╰┳╯","╭━╯"," ","┣╯"," "," ╭╯"," ","●","━","━","┃","┃"," "},  
                            {"┻ ┻","┗━╯","╰━┛","┗━╯","╰━┛","┻  ","╰━╯","┻ ┻"," ┻ ","┗━╯","┻ ┻","╰━┛","┻ ┻","┻ ┻","╰━╯","┻  ","╰╋╯","┻ ┻","┗━╯"," ┻ ","╰━╯","┗╯ ","╰┻╯","┻┗┛"," ┻ ","┗━┛"," ","● ","●"," ● ","▛","●","━"," ","┗","┛"," "}};  

//                 A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, ,!,.,?,,,:,=,-,(,),'
int size_letter[]={3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,2,1,3,1,1,1,1,1,1,1};

const char *cLedsh[3][10] = {{"┏━┓", " ┓ ", " ━┓", " ━┓","┓ ┓","┏━ ","┏━ "," ━┓","┏━┓","┏━┓"},
                             {"┃ ┃", " ┃ ", "┏━┛", " ━┫","┗━┫","┗━┓","┣━┓","  ┃","┣━┫","┗━┫"},
                             {"┗━┛", " ┻ ", "┗━ ", " ━┛","  ┻"," ━┛","┗━┛","  ┻","┗━┛","  ┻"}};

const char* sound[6] = {"aplay -q tests/dataGamelife/dead_bacteria.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_laser_antimateria.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataGamelife/bubble.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataGamelife/gamelife_level.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataGamelife/gamelife_back.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataGamelife/gamelife_cuenta_puntos.wav </dev/null >/dev/null 2>&1 &"
                       };

void put_heroe( int x, int y);
void initialize_grid();
void increment_population( int ncolor);
int put_shoot();
int count_bacteries();
int verify_bacterial_grow();
void put_leds(int num, int nColorF);
void put_big_message(char *msg, int nColorF);
void put_termometer();
void put_temp_bar();
void put_game_over();
void clear_body();
void put_you_win();
void put_score(int score);
void put_life(int life);
void put_red_point(int x, int y);
void put_blue_point(int x, int y);
void put_green_point(int x, int y);
void put_init_play();
void john_is_dead();
void kill_all_sounds();
void bad_message(int type);


//int size = 120, sizec=100;
int shooterx=0, shootery=0, shoot=0;
//int swpenicillumbomb=0, 
int swpenicillumpill=0;
char tipoDisparo[7];
int c,dir=0,steps;
int px,py; // = 123, py = 1;
int grid[size][sizec], cnt_population, totbacteries=0; 
int neighbour_count[size][sizec];
int typewriting=0, time_game=0, level=1, score=0;
int points[]={100,120,77,130,68,127,55,124,50,127,45,130,37,122,34,129,28,127,20,127,7,127};
int icolor=0, bact_colours[]={226,118,118,123,255,207,255,118,226,141,196};
int index_rp=0,game_level=-1, life=3;
// shoot effective versus total shoots:
unsigned int wrong_shoots, total_shoots;

// timers:
unsigned long tbactery = 0L, tnanobot=0L, tshoot = 0L, ttermometer = 0L; //, refresh = 0L;
  
Main

  strcpy(tipoDisparo,"█");

  Hide_cursor; 
  Enable_raw_mode();

  put_init_play();Pause(); 

otra_vez:
  
  Cls;
  ++game_level;
  Assert( game_level < 12, you_win ); 
  ////put_you_win();Pause();Stop(1);

  wrong_shoots=0; total_shoots=0;
  
  put_termometer();
  put_red_point(points[index_rp], points[index_rp+1]+8);Flush_out; //Pause();Stop(1);
  initialize_grid();

  system( sound[2] );
  cnt_population=40; 
  steps=0;
  int k;
  for( k=0; k<=1700; k++){
      increment_population( icolor);
      totbacteries = count_bacteries();
      put_temp_bar();
  }

  px = 123, py = 96; //49;
  put_heroe( px, py );
  
  Flush_inp;
  
  time_game=130-(level*5); //10);

  steps=0;
  cnt_population=40-(level-1)/2; //-level*2; //42-level; 
  put_score(score);
  c=0;
  
  Flush_inp;
  
  system( sound[4] );
  tbactery = Tic(); tnanobot= Tic(); tshoot = Tic(); ttermometer = Tic(); //refresh = Tic();
  
  while( c!=ESCAPE )
  {

    if ( Timer( &tbactery,45L )){ //40
       increment_population( icolor);
    }

    if ( swpenicillumpill ){
       if ( Timer( &tshoot, 1L ) ){
           if (grid[shooterx][shootery]==1){
               printf("\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                      shooterx-1,shootery-1,red_point[0],
                      shooterx,shootery-1,red_point[1],
                      shooterx+1,shootery-1,red_point[2]);
               grid[shooterx][shootery] = 0;
               if(grid[shooterx-1][shootery]==1) grid[shooterx-1][shootery] = 0;
               if(grid[shooterx+1][shootery]==1) grid[shooterx+1][shootery] = 0;
               //if(grid[shooterx-2][shootery]==1) grid[shooterx-2][shootery] = 0;
               //if(grid[shooterx+2][shootery]==1) grid[shooterx+2][shootery] = 0;
               
               if( shootery-1>=0 &&  shootery-1< sizec ){
                   grid[shooterx][shootery-1] = 0;
                   grid[shooterx-1][shootery-1] = 0;
                   grid[shooterx+1][shootery-1] = 0;
               }
               if( shootery+1>=0  &&  shootery-1< sizec ){
                   grid[shooterx][shootery+1] = 0;
                   grid[shooterx-1][shootery+1] = 0;
                   grid[shooterx+1][shootery+1] = 0;
               }
               
               shoot=0;
               swpenicillumpill=0;
               system( sound[0] );
               score += 10;
               put_score(score);
               printf("\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                      shooterx-1,shootery-1,black_point[0],
                      shooterx,shootery-1,black_point[1],
                      shooterx+1,shootery-1,black_point[2]);
           }else{
               shoot = put_shoot();
           }
       }
    }
    
    if( Timer( &ttermometer, 1000L ) ){
        
        totbacteries = count_bacteries();
        --time_game;

        At 135,67 ; put_leds( cnt_population,121);
        At 135,115 ; put_leds( time_game,121);
        put_temp_bar();
        Reset_color;
        if( time_game==0 ) { break; } // pierde
        
    }
    
    if( Timer( &tnanobot, 32L ) ){
        
        if ( Kbhit() ){
            c = Getch();
            if(c == ARROW_LEFT )       { dir=DIR_LEFT; }
            else if(c == ARROW_RIGHT ) { dir=DIR_RIGHT;}
            else if(c == ARROW_DOWN )  { dir=0;}
            else if(c==99){      // c=dispara carga de protones
                 if (!shoot){
                       shoot=1;
                       shooterx=px;
                       shootery=py+3;
                       swpenicillumpill=1;
                       tshoot=0L;
                       system( sound[1] );
                       ++total_shoots;
                 }
            }
            else if(c==SPACE){
                 kill_all_sounds();
                 Pause();
                 system( sound[4] );
            }
            Flush_inp;
        }
        py += dir;
        if (py<1) py=1;
        else if (py>96) py=96; //70
        put_heroe( px, py );
        
    }
  }
  kill_all_sounds();
  At shooterx, shootery; puts( " " );
  Flush_inp;
  sleep(3);
  
  if (totbacteries < 150 && !cnt_population ){
          if (!verify_bacterial_grow()){
              bad_message(0);
              --game_level;
              goto otra_vez;
          }else{
              clear_body();
              ++level;
              if ( level > 4 ) level = 4;
              index_rp+=2;
              ++icolor;
              goto otra_vez;
          }
          
  }else { //if( Is_between( totbacteries, 150, 240 ) ){
          --life;
          put_life(life);
          if( life==0 ){
              john_is_dead();
              put_game_over();
          }else{
              bad_message(1);
              --game_level;
              goto otra_vez;
          }
/*  }else{
          john_is_dead();
          put_game_over();
  */        
  }
  
  Exception( you_win )
  {
      put_you_win();
      put_game_over();    
  }

  Show_cursor;
End

int verify_bacterial_grow()
{
   int nstable=0, newstable=0;
   int i,j;
   //int grid_stable[size][sizec];
   for(i=0; i<size; ++i)
      for( j=0; j<sizec; ++j)
          //grid_stable[i][j] = grid[i][j];
          if (grid[i][j]==1) ++nstable;

   increment_population(0);

   for(i=0; i<size; ++i)
      for( j=0; j<sizec; ++j)
          if (grid[i][j]==1) ++newstable;
    
   return (nstable >= newstable);
}

void put_init_play()
{
   int x=16,i;
   Color_fore(46);
   At x,35;   Print "██▙     ████████████▙    ██▙     ████████████▙";
   At x+1,35; Print "███▙    █    ██▀▀▀▀▀█    ███▙    █    ██▀▀▀▀▀█";
   At x+2,35; Print "████▙   █    ██     █    ████▙   █    ██     █";
   At x+3,35; Print "██ ▜█▙  █    ██     █    ██ ▜█▙  █    ██     █";
   At x+4,35; Print "██  ▜█▙ █    ██     █    ██  ▜█▙ █    ██     █";
   At x+5,35; Print "██   ▜█▙█    ████████    ██   ▜█▙█    ██     █";
   At x+6,35; Print "██    ▜██    ██     █    ██    ▜██    ██     █";
   At x+7,35; Print "██     ▜█    ██     ███████     ▜█    ▜██████▛";
   Flush_out;
   typewriting=1;
   At 30,37 ; put_big_message("life or dead",121);
   Iterator up i[0:2:22]
   {
       put_blue_point(points[i], points[i+1]+8); Flush_out;
       usleep(100000);
   }
   
   
  // Lead the nanobot inside John's body, kill the bacteria and save his life.
   At 44,15 ; put_big_message("Lead the nanobot inside",46);
   At 49,15 ; put_big_message("John's body, kill the",46);
   At 54,15 ; put_big_message("bacteria and save his",46);
   At 59,15 ; put_big_message("life.",46);

   sleep(1);
   typewriting=0;
   At 67,15 ; put_big_message("---------------------------------------------",15);
   At 77,15 ; put_big_message("LASERS:",15);
   At 82,22 ; put_big_message(" C ",15);
   At 82,32 ; put_big_message("= penicillin shoot",123);
   At 90,15 ; put_big_message("lateral arrows = move nano",226);
   At 95,15 ; put_big_message("arrow down = stop nano",226);
   At 105,15 ; put_big_message("---------------------------------------------",15);
   sleep(1);
   typewriting=1;
   At 113,15 ; put_big_message("good luck!",46);
}

void kill_all_sounds()
{
   String PID;
   Fn_let ( PID, Get_sys("pidof aplay" ));
   if (strlen(PID)>0){
      char cpids[1024];
      sprintf(cpids,"kill -9 %s </dev/null >/dev/null 2>&1",PID);
      system(cpids);
   }
   Free secure PID;
}

void put_score(int score)
{
   At 10,137+8 ; put_leds( score,121);
}

void put_life(int life)
{
   At 16,157 ; put_leds( life,121);
}

void put_green_point(int x, int y)
{                                                          
   printf("\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",x,y,green_point[0],x+1,y,green_point[1],x+2,y,green_point[2]);
}

void put_blue_point(int x, int y)
{                                                          
   printf("\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",x,y,blue_point[0],x+1,y,blue_point[1],x+2,y,blue_point[2]);
}

void put_red_point(int x, int y)
{                                                          
   printf("\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",x,y,red_point[0],x+1,y,red_point[1],x+2,y,red_point[2]);
}

void put_you_win(){
   Cls;

   typewriting=1;
   sleep(1);
   At 30,43 ; put_big_message("YOU WIN",46);
   sleep(1);
   At 50,33 ; put_big_message("john is alive!",255);
   sleep(1);
   Seed_by_Time();
   int r = rand()%20;
   if (r <= 6 ){
       At 76,15 ; put_big_message("thanks to you, john will",46);
       At 80,15 ; put_big_message("be able to continue serving",46);
       At 84,15 ; put_big_message("his sentence of three life",46);
       At 88,15 ; put_big_message("sentences for multiple",46);
       At 92,15 ; put_big_message("murder and rape.",46);
   }else if (r >6 && r <= 12){
       At 76,15 ; put_big_message("thanks to you, john will",46);
       At 80,15 ; put_big_message("be able to continue leading",46);
       At 84,15 ; put_big_message("the oxygen monopoly on",46);
       At 88,15 ; put_big_message("the planet.",46);
   }else{
       At 76,15 ; put_big_message("thanks to you, john will be",46);
       At 80,15 ; put_big_message("able to continue exploiting",46);
       At 84,15 ; put_big_message("the forests of the Amazon",46);
       At 88,15 ; put_big_message("and the virgin forests of",46);
       At 92,15 ; put_big_message("Asian continent.",46);
   }
   
   At 110,37 ; put_big_message("final score",46);
   At 116,43; put_leds( score,255);
   Pause();
}

void bad_message(int type)
{
   Cls;
   typewriting=1;
   At 50,15; put_big_message("the bacterial outbreak",208);
   At 55,15; put_big_message("(b.o.) could not be",208);
   At 60,15; put_big_message("controlled...",208);
   
   At 67,15; put_big_message("you will have to return",208);
   At 72,15; put_big_message("to the infected area to",208);
   At 77,15; put_big_message("stop the new bacterial",208);
   At 82,15; put_big_message("outbreak.",208);
   
   if (type){
       At 89,15; put_big_message("but...",196);
       sleep(1);
       At 94,15; put_big_message("you lost one nanobot.",196);
   }
   typewriting=0;
   Pause();
}

void john_is_dead(){
   Cls;

   typewriting=1;
   sleep(1);
   At 40,43 ; put_big_message("john is dead",196);
   sleep(3);
}

void put_game_over(){
   Cls;

   typewriting=1;
   sleep(1);
   At 40,43 ; put_big_message("GAME OVER",196);
   sleep(3);
}

void clear_body(){
   Cls;

   typewriting=1;
   system( sound[3] );
   put_green_point(points[index_rp], points[index_rp+1]+8);Flush_out;

   At 35,43 ; put_big_message("CLEAR BODY!",226);
   sleep(3);
   At 48,15; put_big_message("total shoots:",121);
   At 48,67; put_leds( total_shoots,255);
   At 55,15; put_big_message("Effective shoots:",121);
   unsigned effective_shoots = total_shoots - wrong_shoots;
   if (effective_shoots<0) effective_shoots=1;
   At 55,81; put_leds( effective_shoots,255);
   
   At 62,15; put_big_message("efficiency:       percent",121);
   unsigned efficiency = (unsigned) ((double)effective_shoots/(double)total_shoots*100.0);
   At 62,58; put_leds( efficiency,255);
   
   At 69,15; put_big_message("Bonus: ",121);
   int bonus;
   if(efficiency>=80)         bonus = 10000;
   else if(efficiency>=70)    bonus = 7500;
   else if(efficiency>=60)    bonus = 5000;
   else if(efficiency>=50)    bonus = 2500;
   else if(efficiency>=40)    bonus = 1000;
   else                       bonus = 500;
   
   At 69,38; put_leds( bonus,255);
   
   sleep(1);
   
   At 76,15; put_big_message("score: ",121);
   At 76,38; put_leds( score,255);
   system( sound[5] );
   do{
        score += 10;
        bonus -= 10;
        At 69,38; put_leds( bonus,255);
        At 76,38; put_leds( score,255);
        usleep(10000);
   }while(bonus);
   kill_all_sounds();
   sleep(1);
   Pause();
}

void put_temp_bar()
{
   int nbarra=0, nresto=0, ncolor=0;
   if (totbacteries >= 300 ) {nbarra=90; nresto=10; ncolor=196;}
   else if ( Is_between(totbacteries, 200, 299 )) {nbarra=85; nresto=15; ncolor=208;}
   else if ( Is_between(totbacteries, 150, 199 )) {nbarra=80; nresto=20; ncolor=226;}
   else  {nbarra=75; nresto=25; ncolor=46;}
   String barra1, barra2;
   Fn_let( barra1, Replicate("█", nbarra) );
   Fn_let( barra2, Replicate("█", nresto) );
   Color_fore(ncolor);
   At 128, 2; Print "%s", barra1; Color_fore(245); Print "%s", barra2;
   Reset_color;
   Free secure barra1, barra2;
}

void put_termometer()
{
   int ntemp=0, t=0;
   typewriting=0;
   At 135,2 ; put_big_message("temperature    B.O.      batt. time:",34);
   Color_fore(255);

   Iterator up t [1:10:100]{
       At 130, t; put_leds( ntemp,121);
       ntemp += 5;
   }
   At 4,137+8 ; put_big_message("score",46);
   
   At 16,137+8; put_big_message("up",46);
   put_life(life);
   Reset_color;

}

int put_shoot(){
   At shooterx, shootery; puts( " " );

   Color_fore(226);
   --shooterx;
   At shooterx, shootery; puts( tipoDisparo );

   if (shooterx==1){   
       shoot=0;
       wrong_shoots+=2;
       At shooterx, shootery; puts( " " );
       //swpenicillumbomb=0; 
       swpenicillumpill=0;
       return 0;
   }
   return 1;
}

void put_heroe( int x, int y){
   printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                  x,y,heroe[0],
                  x+1,y,heroe[1],
                  x+2,y,heroe[2],
                  x+3,y,heroe[3]);
   
}

void initialize_grid()
{
  int i,j;
  for(i=0; i<size; ++i)
      for( j=0; j<sizec; ++j){
          grid[i][j]=0;
          neighbour_count[i][j]=0;
      }
  grid[50][49]=1;grid[50][50]=1;grid[50][51]=1;
  grid[49][50]=1;grid[51][51]=1; 
}

int count_bacteries()
{
  int nbacteries=0;
  int i,j;
  for(i=0; i<size; ++i)
      for( j=0; j<sizec; ++j)
          if (grid[i][j]==1) ++nbacteries;
  return nbacteries;
}

#define for_x for ( x = 0; x < sizec; x++)
#define for_y for ( y = 0; y < size; y++)
#define for_xy for_x for_y

void evolve() //void *u, int w, int h)
{
	//unsigned (*univ)[w] = u;
	unsigned new[size][sizec];
        int x,y,x1,y1;

        if( ++steps == 100000 ) steps = 0;
       
        /* este es el foco de infección */
        if ( cnt_population ){
           if ( ! (steps % 50) ){
              if (--cnt_population < 0 ) cnt_population=0;
              if( rand()%10<=4 ){
                  int offset=rand()%45;
                  grid[50+offset][49+offset]=1;
                  grid[50+offset][50+offset]=1;
                  grid[50+offset][51+offset]=1;
                  grid[49+offset][50+offset]=1;
                  grid[51+offset][51+offset]=1;
              }else{
                  int offset=rand()%45;
                  grid[50-offset][49-offset]=1;
                  grid[50-offset][50-offset]=1;
                  grid[50-offset][51-offset]=1;
                  grid[49-offset][50-offset]=1;
                  grid[51-offset][51-offset]=1;
              }
           }
        }
        
	for_y for_x {
		int n = 0;
		for (y1 = y - 1; y1 <= y + 1; y1++)
			for ( x1 = x - 1; x1 <= x + 1; x1++)
				if (grid[(y1 + size) % size][(x1 + sizec) % sizec])
					n++;
 
		if (grid[y][x]) n--;
		new[y][x] = (n == 3 || (n == 2 && grid[y][x]));
	}
	for_y for_x grid[y][x] = new[y][x];
}

void increment_population( int ncolor)
{

	int x,y;
        
	printf("\033[1;1H\x1b[38;5;%dm\x1b[1m", bact_colours[ncolor]);
	for_y {
	        printf("\x1b[%d;1H",y);
		for_x { 
		   if (grid[y][x] == 1)
                      //printf("\x1b[%d;%dHW",y,x);
                      printf("W");
                      //printf("\x1b[%d;%dH\u2588",y,x);
                   else
                      //printf("\x1b[%d;%dH ",y,x);
                      printf(" ");
		
		}
	}
	fflush(stdout);
	evolve();
}

void put_big_message(char *msg, int nColorF)
{
    const char* ps = msg; //tmsg;
    int row = SCREEN_ROW;
    int col = SCREEN_COL;
    while (*ps){
        char lett = *ps;
        int i; //,sw=0;
        if( lett == 32 ) i=26;
        else if ( lett == '!' ) i=27;
        else if ( lett == '.' ) i=28;
        else if ( lett == '?' ) i=29;
        else if ( lett == ',' ) i=30;
        else if ( lett == ':' ) i=31;
        else if ( lett == '=' ) i=32;
        else if ( lett == '-' ) i=33;
        else if ( lett == '(' ) i=34;
        else if ( lett == ')' ) i=35;
        else if ( lett == '\'' ) i=36;
        else{ 
            lett = toupper(lett);
            i = lett - 'A';
        }
        static char letter[1024];
        sprintf( letter,"\x1b[38;5;%dm\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[0m",
                nColorF, row, col, (letters[0][i]),
                row+1,col, (letters[1][i]),
                row+2,col, (letters[2][i]));
        const char* psimb = letter;
        col = col + (size_letter[i]+1);
        ++ps;
        puts(psimb);
        if(typewriting) usleep(80000);
    }
}

void put_leds(int num, int nColorF)
{
    int c, cb=0;
    String cnum;  
    cnum = Int2str(num);
    static char score[40000];
    
    int i; //, sw=0;
    for( i=0;i<strlen(cnum); i++){
        char w = cnum[i];
        c = w - 48;
        int row = SCREEN_ROW;
        int col = SCREEN_COL + (i*3);
        static char digit[512];
        int n = sprintf( digit,"\x1b[38;5;%dm\x1b[%d;%dH%s   \x1b[%d;%dH%s   \x1b[%d;%dH%s\x1b[0m   ",
                nColorF, row, col, cLedsh[0][c],
                row+1,col, cLedsh[1][c],
                row+2,col, cLedsh[2][c]);
        const char* psimb = digit;
        memcpy((void*) score + cb, psimb, n);
        cb += n;
    }
    score[cb]='\0';
    puts(score);
    Free secure cnum; 
}

