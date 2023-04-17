/*
  TETRIS
  
  Idea original copyright de Alekséi Leonídovich Pázhitnov
  Programado por (c)Dr. Dalien.
  Ejecutar con:
  
  ./tests/tetris.sh [opciones]
*/

#include <gadget/gadget.h>

LIB_GADGET_START

#define ROWS        20
#define COLUMNS     10
#define BACKCOLOR  240
#define VOIDCOLOR  226
#define WHITECOLOR  15

/*elementos del juego */
const char* sound[12] = {"aplay -q tests/dataTetris/tetris_clearline.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_bono.wav </dev/null >/dev/null 2>&1",
                        "aplay -q tests/dataTetris/tetris_levelUp.wav  </dev/null >/dev/null 2>&1",
                        "aplay -q tests/dataTetris/tetris_gameOver.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_title_theme.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/BombExplosion.wav </dev/null >/dev/null 2>&1",
                        "aplay -q tests/dataTetris/hey.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/God_bless_amerika.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_levelUpDance.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/telon_up.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_giro.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_tap.wav </dev/null >/dev/null 2>&1 &"};

const char *music[4] = {"aplay -q tests/dataTetris/tetris_bradinsky_1.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_troika_2.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_loginska_3.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataTetris/tetris_karinka_4.wav </dev/null >/dev/null 2>&1 &"};
/* funciones */

GD_VIDEO Put_field ( GD_VIDEO field, int complexity);
GD_VIDEO Put_next_box(GD_VIDEO next_box);
void Init_array_base();
void Print_blocks(int type, int init);
int  Put_piece(int tetrimino, int active);
int  Down_piece(), Verify_full_lines(long *time);
void Verify_level( int *level, int total_lines);
void Left_moving(), Right_moving(), Put_points(int score, int high, int level, int total_lines);
void Select_piece(), Select_next(), Put_next_piece(), Get_right_rotation(), Get_left_rotation();
void kill_all_sounds(), Put_game_over();
void Presentation(int complexity);
int  Load_high_score();
void Save_score(int score, int high);
void Put_time_bonus(int timeBonus);
void You_win(int type);
void Compute_time(int *timeBonus);
void Change_colors();
void Show_statistics(int score, int high, int level, int total_lines);
void Use_mode(){
    //Color(196,232);
    Color_fore(196);
    //Cls;
    Bold;
    printf("\n TETRIS - by Alekséi\n");
    printf("             Pázhitnov\n"); Bold_off;
    printf("\n Mode use:\n ./tests/tetris.sh\n\n");
    //printf("\n options:\n   [-ns][-1|-2|-3|-4]\n");
    //printf("   [-d1|-d2]\n   [-b1..-b4][-h]\n\n");
    printf(" Options:\n");
    printf(" -ns      disable music.\n");
    printf(" -1..-4   set game mode.\n");
    printf(" -d1,-d2  cosaco dance.\n");
    printf(" -b1..-b5 change blocks.\n");
    printf(" -r       retro screen.\n");
    printf(" -k       kaleidoscope.\n");
    printf(" -h       this help.\n\n");
    
    printf(" Programmed by\n\n\t Mr.Dalien\n\t 2023");
    //printf("for Linux.\n");
    Flush_out;
    Pause();
}
void Name(int wide)
{
    Color(196,232);
    Atcol 5+wide;
    Atrow 3; Print "▄▄▄  ▄▄ ▄▄▄  ▄  ▄  ▄";
    Atrow 4; Print "▀█▀ █▀  ▀█▀ ▀▄█ █ ▀▄" ;
    Atrow 5; Print " ▀   ▀▀  ▀  ▀ ▀ ▀ ▀ ";
    Flush_out;
}

/* variables del sistema */
int tetrimino = 0, next_tetrimino=0;
int state_rotation_r=0, state_rotation_l=0;  /* 0=normal, 1,2,3-->0, según tetriminó */
int sw_play_present=1;  /* enable/disable music */
int complexity = 1;
int cosaco_dance=-1;
int block_type=0; /* bloque por defecto */
int counter_tetromino=0; /* contador de piezas repetidas. Si una pieza se repite más de 3 veces, se escoge otra */
int green_blocks=0;   /* blocks y matriz de juego de color verde con fondo oscuro */
int kaleidoscope=0;   /* kaleidoscopio */
int wide=13;

GD_VIDEO field, next_box;


/* array de campo de juego */
int base[ROWS][COLUMNS];
int tetrimino_T[]={0,5,1,4,1,5,1,6},
    tetrimino_Z[]={0,4,0,5,1,5,1,6},
    tetrimino_J[]={0,4,1,4,1,5,1,6},
    tetrimino_I[]={0,4,0,5,0,6,0,7},
    tetrimino_L[]={0,6,1,4,1,5,1,6},
    tetrimino_S[]={0,5,0,6,1,4,1,5},
    tetrimino_O[]={0,4,0,5,1,4,1,5};

int tetrimino_selected[]={0,0,0,0,0,0,0,0};
int tetrimino_next[]={0,0,0,0,0,0,0,0};
int tetrimino_count[]={0,0,0,0,0,0,0};  /* estadistica de cada tetromino */
int tetrimino_color[]={201,196,21,105,166,46,226,0}; /* colores de base */
int tetrimino_cbak[]={201,196,21,105,166,46,226,0}; /* respaldo de colores original */

/* bloque principal */
Main
    
    if ( Arg_count >= 2 ){
        int i=0;
        while( ++i<Arg_count ){
            Get_arg_str( opt_play, i );
            if ( Is_equal_str(opt_play,"-ns") ){  // no sound
                sw_play_present=0;
            }
            if( Is_equal_str(opt_play,"-1") ){  // normal
                complexity=1;
            }else if( Is_equal_str(opt_play,"-2") ){  // medium
                complexity=2;
            }else if( Is_equal_str(opt_play,"-3") ){  // hard
                complexity=3;
            }else if( Is_equal_str(opt_play,"-4") ){  // rude
                complexity=4;
            }
            if( Is_equal_str(opt_play,"-b1") ){  // tipo de bloque default
                block_type=0;
            }else if( Is_equal_str(opt_play,"-b2") ){  // tipo de bloque alternativo
                block_type=1;
            }else if( Is_equal_str(opt_play,"-b3") ){  // tipo de bloque alternativo
                block_type=2;
            }else if( Is_equal_str(opt_play,"-b4") ){  // tipo de bloque alternativo
                block_type=3;
            }else if( Is_equal_str(opt_play,"-b5") ){  // tipo de bloque alternativo
                block_type=4;
            }
            if( Is_equal_str(opt_play,"-r") ){  // block verde
                green_blocks=1;
                kaleidoscope=0;
            }
            if( Is_equal_str(opt_play,"-k") ){  // block kaleidoscopio: funde retinas.
                kaleidoscope=1;
                green_blocks=0;
            }
            if( Is_equal_str(opt_play,"-h") ){  // help
                Use_mode();
                Free secure opt_play;
                Stop(1);
            }
            if( Is_equal_str(opt_play,"-d1") ){  // cosaco dance 1
                cosaco_dance=0;
            }else if( Is_equal_str(opt_play,"-d2") ){  // cosaco dance 2
                cosaco_dance=1;
            }
            Free secure opt_play;
        }
    }

    Hide_cursor;
    
    if ( Is_non_neg(cosaco_dance) ){
        You_win(cosaco_dance); 
        Stop(1);
    }
    
    if (green_blocks ){
        tetrimino_color[0]=tetrimino_color[3]=tetrimino_color[6]=70; // 34
        tetrimino_color[1]=tetrimino_color[2]=46;
        tetrimino_color[5]=tetrimino_color[4]=255;
    }
    
    Presentation(complexity);
    
    Init_video( &field );
    Init_video( &next_box );
    Init_array_base();

    field = Put_field( field, complexity );
    next_box = Put_next_box( next_box );
    Refresh(field);
    Overlap(next_box);
    
    int high=Load_high_score();
    int score=0, level=1;
    int total_lines=0, local_lines=0; /* lineas totales consumidas y líneas consumidas en una jugada */
    
    Put_points(score, high, level,total_lines);
    
    Enable_raw_mode();

    Seed_by_Time();
    
    int c=0;
    long time_lapse=500; /* retardo de caida */
    
    int indexMusica=0;
    int timeBonus;
    
    Compute_time(&timeBonus);
    Put_time_bonus(timeBonus);
    
    if( sw_play_present )
        system(music[indexMusica]);
    
    while (toupper(c)!='Q'){
        
        Select_piece();
        Select_next();
        if( !Put_piece(tetrimino, 1) ) {
             //if( sw_play_present )
             //    kill_all_sounds();

             //Print_blocks(0,0);
             break;
        }
        Overlap(next_box);
        Put_next_piece();
    
        Print_blocks(1,1);
        usleep(100000);

        unsigned long Tcontrols=0, Tpiece=0, TbonusTime=0; 
        
        Tcontrols=Tic(); Tpiece=Tic(); TbonusTime=Tic();
        
        while ( toupper(c)!='Q' )
        {
            
            if( Timer( &TbonusTime, 1000) ){
                --timeBonus;
                if( timeBonus<0 ) timeBonus=0;
                Put_time_bonus(timeBonus);
            }
            
            if( Timer( &Tpiece, time_lapse ) ){
                if ( !Down_piece() ){
                    break;
                }
                Print_blocks(1,0);
            }
        
            if( Timer( &Tcontrols, 10L ) ){
                if ( Kbhit() ){
                    c = Getch();
                    if(c == ARROW_LEFT || toupper(c) == 'A')        { Left_moving();  }
                    else if(c == ARROW_RIGHT || toupper(c) == 'D' ) { Right_moving(); }
                    else if(c == ENTER || toupper(c) == 'W' )       { while ( Down_piece() ) {
                                                     usleep(10000);
                                                     Print_blocks(1,0);
                                                 }
                                                 break; }
                    else if( toupper(c) == 'K'  || toupper(c) == 'R' ) { if( sw_play_present ) system(sound[10]);
                                                                         Get_right_rotation(); }
                    else if( toupper(c) == 'J'  || toupper(c) == 'E' ) { if( sw_play_present ) system(sound[10]);
                                                                         Get_left_rotation(); }
                    else if( toupper(c) == SPACE ) {
                           if( !Down_piece() ){
                                break;
                           }
                    }
                    else if( toupper(c) == 'P' ) { 
                           if( sw_play_present )
                                kill_all_sounds();
                           Pause();
                           if( sw_play_present )
                                system(music[indexMusica]);
                    }
                }
                Print_blocks(1,0);
            }
        }
        if( sw_play_present )
             system(sound[11]);
             
        local_lines = Verify_full_lines( &time_lapse );
        
        score += local_lines*10; /* 10 puntos por cada línea borrada */

        if ( local_lines ){
             score += timeBonus*5;   /* bono: tiempo remanente * 5 */
             Compute_time(&timeBonus);  /* restaura límite de tiempo según modo de juego */
        }else{   // local_lines es 0, luego, incrementa velocidad por cada 
                 // pieza colocada, hasta que logre borrar una línea.
             if (!timeBonus) --time_lapse;
        }
        
        total_lines += local_lines;
        
        if( local_lines==4 ){  // bono!
             score += 1000;
             Put_points(score, high, level, total_lines);
             if( sw_play_present )
                  system(sound[1]);
        }
        else if( local_lines==3 ) score += 500;
        else if( local_lines==2 ) score += 100;
        
        int tmp_level=level;
        Verify_level( &level, total_lines);
        Put_points(score, high, level, total_lines);
        if( tmp_level < level ){
            
            /*cambia el color de los tetrominós según el cambio de nivel, después del 11to nivel */
            if (!green_blocks)
                //if ( level >= 11 )
                    Change_colors();
            
            /* verifica, si el sonido está activado, si llegó a la mitad o al final virtual */
            if( sw_play_present ){
                kill_all_sounds();
                system( sound[2] );

                if ( ++indexMusica == 4 ){
                    indexMusica=0;
                }
                /* si llegó al nivel 20, ganó! */
                if( level == 21 ) {
                    You_win(1);
                    Reset_color;
                    Cls;
                    Refresh(field);
                    Overlap(next_box);
                    Put_points(score, high, level,total_lines);
                    Put_time_bonus(timeBonus);
                }else if( level == 11 ){   // pasó la mitad del juego. 11
                    You_win(0);
                    Reset_color;
                    Cls;
                    Refresh(field);
                    Overlap(next_box);
                    Put_points(score, high, level,total_lines);
                    Put_time_bonus(timeBonus);
                }
                Seed_by_Time();  //nueva semilla de números aleatorios.
                system(music[indexMusica]);
            }
        }
        
        local_lines = 0;
        
    }
    if( sw_play_present )
        kill_all_sounds();
    Print_blocks(0,0);
    
    Save_score( score, high );
    
    Put_game_over();
    Free video field, next_box;
    
    sleep(2);
    Show_statistics(score, high, level, total_lines);

    Show_cursor;
End

/* funciones del juego */

int Load_high_score()
{
   int high=0;
   String file;
   Let (file, "tests/dataTetris/high");
   
   switch(complexity){
       case 1: { Cat( file, "_normal.txt" ); break; }
       case 2: { Cat( file, "_middle.txt" ); break; }
       case 3: { Cat( file, "_hard.txt" ); break; }
       case 4: { Cat( file, "_rude.txt" ); break; }
   }
   
   if( Exist_file(file)){
       Stack{
           high = Str2int( Load_string(file));
       } Stack_off;
   }
   Free secure file;
   return high;
}

void Save_score(int score, int high)
{
   String file;
   
   Let( file, "tests/dataTetris/high");
   switch(complexity){
       case 1: { Cat( file, "_normal.txt" ); break; }
       case 2: { Cat( file, "_middle.txt" ); break; }
       case 3: { Cat( file, "_hard.txt" ); break; }
       case 4: { Cat( file, "_rude.txt" ); break; }
   }

   if( score > high ){
       Stack{
           Save_string( Int2str(score), file );
       } Stack_off;
   }
   Free secure file;
}

void Compute_time(int *timeBonus)
{
    switch( complexity ){
        case 1: { *timeBonus=90; break; }
        case 2: { *timeBonus=60; break; }
        case 3: { *timeBonus=45; break; }
        case 4: { *timeBonus=30; break; }
    }

}

void Verify_level( int * level, int total_lines)
{
   /* cada 10 líneas borradas, aumenta un nivel */
    *level = (int)(total_lines/10+1);
}

void Change_colors()
{
    static int index_color=0;
    /* rojo, azul, verde, naranjo, morado, celeste, amarillo, */
    int others_color[]={196,21,40,202,165,105,178};
    
    tetrimino_color[0]=tetrimino_color[2]=tetrimino_color[4]=tetrimino_color[6]=others_color[index_color++];
    tetrimino_color[1]=tetrimino_color[3]=tetrimino_color[5]=255;
    if( index_color == 7 ) {
        tetrimino_color[0]=tetrimino_cbak[0];
        tetrimino_color[1]=tetrimino_cbak[1];
        tetrimino_color[2]=tetrimino_cbak[2];
        tetrimino_color[3]=tetrimino_cbak[3];
        tetrimino_color[4]=tetrimino_cbak[4];
        tetrimino_color[5]=tetrimino_cbak[5];
        tetrimino_color[5]=tetrimino_cbak[6];
        index_color=0;
    }
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

void increment_tetrimino_col()
{
    ++tetrimino_selected[1];++tetrimino_selected[3];++tetrimino_selected[5];++tetrimino_selected[7];
}
void increment_tetrimino_row()
{
    ++tetrimino_selected[0];++tetrimino_selected[2];++tetrimino_selected[4];++tetrimino_selected[6];
}

void decrement_tetrimino_col()
{
    --tetrimino_selected[1];--tetrimino_selected[3];--tetrimino_selected[5];--tetrimino_selected[7];
}
void decrement_tetrimino_row()
{
    --tetrimino_selected[0];--tetrimino_selected[2];--tetrimino_selected[4];--tetrimino_selected[6];
}

int verify_bound()
{
    if ( base[ tetrimino_selected[0] ][ tetrimino_selected[1] ] ||
         base[ tetrimino_selected[2] ][ tetrimino_selected[3] ] ||
         base[ tetrimino_selected[4] ][ tetrimino_selected[5] ] ||
         base[ tetrimino_selected[6] ][ tetrimino_selected[7] ] )
         return 0;
    return 1;
}

void Rotate_tetromino(int n,...)
{
    int i;
    va_list va;
    va_start( va, n );
    Iterator up i[0:2:n]{
        int index = va_arg(va, int);
        int value = va_arg(va, int);
        tetrimino_selected[index] += value;
    }
    va_end( va );
}


void Get_right_rotation()
{
    /* simplemente debo cambiar la posición de algún bloque para causar
       el efecto de rotación, y esto depende de tetriminó y de state_rotation_r.
       
       Con este método de ordenamiento de tetrominós, no puedo girar en
       sentido antihorario.
        */
    int sw_borde_l=0, sw_borde_r=0;
    Put_piece(7,0);
    switch ( tetrimino ){
        case 0:{   // T   {0,5,1,4,1,5,1,6}   OK
            switch( state_rotation_r ){
                case 0:{   // normal--> primera rotación
                    Rotate_tetromino( 8,3,1,5,1,6,1,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 8,3,-1,5,-1,6,-1,7,1 );
                    }else{ state_rotation_r++; state_rotation_l=3; }
                    break;
                }case 1:{  // primera-->segunda
                    if(tetrimino_selected[1]==0) {sw_borde_l=1;increment_tetrimino_col();}
                    Rotate_tetromino( 4, 0,1,1,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 4, 0,-1,1,1 );
                         if (sw_borde_l) decrement_tetrimino_col();
                    }else{ state_rotation_r++; state_rotation_l=2; }
                    break;
                }case 2:{  // segunda-->tercera
                    Rotate_tetromino( 8, 0,-1,1,1,3,-1,5,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 8, 0,1,1,-1,3,1,5,1 );
                    }else{ state_rotation_r++; state_rotation_l=1;}
                    break;
                }case 3:{  // tercera-->normal
                    if(tetrimino_selected[7]==9)   {sw_borde_r=1; decrement_tetrimino_col();}
                    Rotate_tetromino( 4, 6,-1,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 4, 6,1,7,-1 );
                         if(sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_r=0; state_rotation_l=0;}
                    break;
                }
            }
            break;
        }case 1:{   //  Z  tetrimino_Z[]={0,4,0,5,1,5,1,6}  OK.
            switch( state_rotation_r ){
                case 0:{   // normal-->primera rotación
                    Rotate_tetromino( 10, 1,2,2,1,5,1,6,1,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,-2,2,-1,5,-1,6,-1,7,1 );
                    }else{ state_rotation_r++; }
                    break;
                }case 1:{
                    if(tetrimino_selected[3]==0)  {sw_borde_l=1;increment_tetrimino_col();}
                    Rotate_tetromino( 10, 1,-2,2,-1,5,-1,6,-1,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,2,2,1,5,1,6,1,7,-1 );
                         if( sw_borde_l) decrement_tetrimino_col();
                    }else{ state_rotation_r=0; }
                    break;
                }
            }
            break;
        }case 2:{  //  tetrimino_J[]={0,4,1,4,1,5,1,6}, OK.
            switch( state_rotation_r ){
                case 0:{
                    Rotate_tetromino( 10, 1,1,2,-1,3,2,6,1,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,-1,2,1,3,-2,6,-1,7,1 );
                    }else{ state_rotation_r++; state_rotation_l=3;}
                    break;
                }case 1:{
                    if(tetrimino_selected[1]==0)  { sw_borde_l=1; increment_tetrimino_col();}
                    
                    Rotate_tetromino( 12, 0,1,1,-1,2,1,3,-1,5,1,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 0,-1,1,1,2,-1,3,1,5,-1,7,-1 );
                         if( sw_borde_l ) decrement_tetrimino_col();
                    }else{ state_rotation_r++; state_rotation_l=2;}
                    break;
                }case 2:{
                    Rotate_tetromino( 10, 0,-1,1,1,4,1,5,-2,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 0,1,1,-1,4,-1,5,2,7,1 );
                    }else{ state_rotation_r++; state_rotation_l=1;}
                    break;
                }case 3:{
                    if(tetrimino_selected[5]==0)  {sw_borde_l=1;increment_tetrimino_col();}
                    else if(tetrimino_selected[1]==9)  {sw_borde_r=1;decrement_tetrimino_col();}

                    Rotate_tetromino( 12, 1,-1,3,-1,4,-1,5,1,6,-1,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 1,1,3,1,4,1,5,-1,6,1,7,-1 );
                         if (sw_borde_l) decrement_tetrimino_col();
                         else if (sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_r=0; state_rotation_l=0;}
                    break;
                }
            }
            break;
        }case 3:{  // tetrimino_I[]={0,4,0,5,0,6,0,7}
            switch( state_rotation_r ){
                case 0:{  // normal-->primera rotación
                    Rotate_tetromino( 12, 1,2,2,1,3,1,4,2,6,3,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 1,-2,2,-1,3,-1,4,-2,6,-3,7,1 );
                    }else{ state_rotation_r++; }
                    break;
                }case 1:{  // primera-->normal
                    if(tetrimino_selected[1]<=1)  {sw_borde_l=1;increment_tetrimino_col();increment_tetrimino_col();}
                    if(tetrimino_selected[7]==9)  {sw_borde_r=1;decrement_tetrimino_col();}

                    Rotate_tetromino( 12, 1,-2,2,-1,3,-1,4,-2,6,-3,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 1,2,2,1,3,1,4,2,6,3,7,-1 );
                         if(sw_borde_l)      {decrement_tetrimino_col();decrement_tetrimino_col();}
                         else if(sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_r=0; }
                    break;
                }
            }
            break;
        }case 4:{   //  tetrimino_L[]={0,6,1,4,1,5,1,6}  OK
            switch( state_rotation_r ){
                case 0:{  // normal-->primera
                    Rotate_tetromino( 8, 1,-1,3,1,4,1,6,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 8, 1,1,3,-1,4,-1,6,-1 );
                    }else{ state_rotation_r++; state_rotation_l=3;}
                    break;
                }case 1:{  // primera-->segunda
                    if(tetrimino_selected[5]==0)  { sw_borde_l=1;increment_tetrimino_col();}

                    Rotate_tetromino( 10, 0,1,1,-1,4,-1,5,1,7,-2);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 0,-1,1,1,4,1,5,-1,7,2);
                         if(sw_borde_l) decrement_tetrimino_col();
                    }else{ state_rotation_r++; state_rotation_l=2;}
                    break;
                }case 2:{  // segunda-->tercera
                    Rotate_tetromino( 8, 0,-1,2,-1,5,-1,7,1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 8, 0,1,2,1,5,1,7,-1);
                    }else{ state_rotation_r++; state_rotation_l=1;}
                    break;
                }case 3:{  // tercera-->normal
                    //if(tetrimino_selected[1]==0)  {sw_borde_l=1;increment_tetrimino_col();}
                    //else 
                    if(tetrimino_selected[3]==9)  {sw_borde_r=1;decrement_tetrimino_col();}
                    Rotate_tetromino( 10, 1,2,2,1,3,-1,6,-1,7,1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,-2,2,-1,3,1,6,1,7,-1);
                         //if(sw_borde_l) decrement_tetrimino_col();
                         //else 
                         if(sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_r=0; state_rotation_l=0;}
                    break;
                }
            }
            break;
        }case 5:{    //  tetrimino_S[]={0,5,0,6,1,4,1,5}  OK
            switch( state_rotation_r ){
                case 0:{   // normal-->primera rotación
                    Rotate_tetromino( 10, 1,-1,2,1,3,-2,5,1,6,1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,1,2,-1,3,2,5,-1,6,-1);
                    }else{ state_rotation_r++; }
                    break;
                }case 1:{  // primera-->normal
                    if(tetrimino_selected[5]==9)  {sw_borde_r=1;decrement_tetrimino_col();}
                    Rotate_tetromino( 10, 1,1,2,-1,3,2,5,-1,6,-1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,-1,2,1,3,-2,5,1,6,1);
                         if(sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_r=0; }
                    break;
                }
            }
            break;
        }
    }
    Put_piece(tetrimino,0);
}

void Get_left_rotation()
{
    int sw_borde_l=0, sw_borde_r=0;
    Put_piece(7,0);
    switch ( tetrimino ){
        case 0:{   // T   {0,5,1,4,1,5,1,6}   OK
            switch( state_rotation_l ){
                case 0:{   // normal--> primera rotación
                    Rotate_tetromino( 4,6,1,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 4,6,-1,7,+1 );
                    }else{ state_rotation_l++; state_rotation_r=3; }
                    break;
                }case 1:{  // primera-->segunda
                    if(tetrimino_selected[1]==9) {sw_borde_r=1;decrement_tetrimino_col();}
                    Rotate_tetromino( 8, 0,1,1,-1,3,1,5,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 8, 0,-1,1,1,3,-1,5,-1 );
                         if (sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_l++; state_rotation_r=2; }
                    break;
                }case 2:{  // segunda-->tercera
                    
                    Rotate_tetromino( 4, 0,-1,1,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 4, 0,1,1,-1 );
                    }else{ state_rotation_l++; state_rotation_r=1;}
                    break;
                }case 3:{  // tercera-->normal
                    if(tetrimino_selected[1]==0)   {sw_borde_l=1; increment_tetrimino_col();}
                    Rotate_tetromino( 8, 3,-1,5,-1,6,-1,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 8, 3,1,5,1,6,1,7,-1 );
                         if(sw_borde_l) decrement_tetrimino_col();
                    }else{ state_rotation_r=0; state_rotation_l=0;}
                    break;
                }
            }
            break;
        }case 1:{   //  Z  tetrimino_Z[]={0,4,0,5,1,5,1,6}  OK.
            switch( state_rotation_r ){
                case 0:{   // normal-->primera rotación
                    Rotate_tetromino( 10, 1,2,2,1,5,1,6,1,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,-2,2,-1,5,-1,6,-1,7,1 );
                    }else{ state_rotation_r++; }
                    break;
                }case 1:{
                    if(tetrimino_selected[3]==0)  {sw_borde_l=1;increment_tetrimino_col();}
                    Rotate_tetromino( 10, 1,-2,2,-1,5,-1,6,-1,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,2,2,1,5,1,6,1,7,-1 );
                         if( sw_borde_l) decrement_tetrimino_col();
                    }else{ state_rotation_r=0; }
                    break;
                }
            }
            break;
        }case 2:{  //  tetrimino_J[]={0,4,1,4,1,5,1,6}, OK.
            switch( state_rotation_l ){
                case 0:{
                    Rotate_tetromino( 12, 1,1,3,1,4,1,5,-1,6,1,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 1,-1,3,-1,4,-1,5,1,6,-1,7,1 );
                    }else{ state_rotation_l++; state_rotation_r=3;}
                    break;
                }case 1:{
                    if(tetrimino_selected[1]==9)  { sw_borde_r=1; decrement_tetrimino_col();}
                    
                    Rotate_tetromino( 10, 0,1,1,-1,4,-1,5,2,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 0,-1,1,1,4,1,5,-2,7,-1 );
                         if( sw_borde_r ) increment_tetrimino_col();
                    }else{ state_rotation_l++; state_rotation_r=2;}
                    break;
                }case 2:{
                    Rotate_tetromino( 12, 0,-1,1,1,2,-1,3,1,5,-1,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 0,1,1,-1,2,1,3,-1,5,1,7,1 );
                    }else{ state_rotation_l++; state_rotation_r=1;}
                    break;
                }case 3:{
                    if(tetrimino_selected[1]==0)  {sw_borde_l=1;increment_tetrimino_col();}

                    Rotate_tetromino( 10, 1,-1,2,1,3,-2,6,-1,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,1,2,-1,3,2,6,1,7,-1 );
                         if (sw_borde_l) decrement_tetrimino_col();
                    }else{ state_rotation_l=0; state_rotation_r=0;}
                    break;
                }
            }
            break;
        }case 3:{  // tetrimino_I[]={0,4,0,5,0,6,0,7} OK.
            switch( state_rotation_r ){
                case 0:{  // normal-->primera rotación
                    Rotate_tetromino( 12, 1,2,2,1,3,1,4,2,6,3,7,-1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 1,-2,2,-1,3,-1,4,-2,6,-3,7,1 );
                    }else{ state_rotation_r++; }
                    break;
                }case 1:{  // primera-->normal
                    if(tetrimino_selected[1]<=1)  {sw_borde_l=1;increment_tetrimino_col();increment_tetrimino_col();}
                    if(tetrimino_selected[7]==9)  {sw_borde_r=1;decrement_tetrimino_col();}

                    Rotate_tetromino( 12, 1,-2,2,-1,3,-1,4,-2,6,-3,7,1 );
                    if( !verify_bound() ){
                         Rotate_tetromino( 12, 1,2,2,1,3,1,4,2,6,3,7,-1 );
                         if(sw_borde_l)      {decrement_tetrimino_col();decrement_tetrimino_col();}
                         else if(sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_r=0; }
                    break;
                }
            }
            break;
        }case 4:{   //  tetrimino_L[]={0,6,1,4,1,5,1,6}  OK
            switch( state_rotation_l ){
                case 0:{  // normal-->primera
                    Rotate_tetromino( 10, 1,-2,2,-1,3,1,6,1,7,-1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,2,2,1,3,-1,6,-1,7,1);
                    }else{ state_rotation_l++; state_rotation_r=3;}
                    break;
                }case 1:{  // primera-->segunda
                    if(tetrimino_selected[3]==9)  { sw_borde_r=1;decrement_tetrimino_col();}

                    Rotate_tetromino( 8, 0,1,2,1,5,1,7,-1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 8, 0,-1,2,-1,5,-1,7,1);
                         if(sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_l++; state_rotation_r=2;}
                    break;
                }case 2:{  // segunda-->tercera
                    Rotate_tetromino( 10, 0,-1,1,1,4,1,5,-1,7,2);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 0,1,1,-1,4,-1,5,1,7,-2);
                    }else{ state_rotation_l++; state_rotation_r=1;}
                    break;
                }case 3:{  // tercera-->normal
                    //if(tetrimino_selected[1]==0)  {sw_borde_l=1;increment_tetrimino_col();}
                    //else 
                    if(tetrimino_selected[1]==0)  {sw_borde_l=1;increment_tetrimino_col();}
                    Rotate_tetromino( 8, 1,1,3,-1,4,-1,6,-1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 8, 1,-1,3,1,4,1,6,1);
                         //if(sw_borde_l) decrement_tetrimino_col();
                         //else 
                         if(sw_borde_l) decrement_tetrimino_col();
                    }else{ state_rotation_l=0; state_rotation_r=0;}
                    break;
                }
            }
            break;
        }case 5:{    //  tetrimino_S[]={0,5,0,6,1,4,1,5}  OK
            switch( state_rotation_r ){
                case 0:{   // normal-->primera rotación
                    Rotate_tetromino( 10, 1,-1,2,1,3,-2,5,1,6,1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,1,2,-1,3,2,5,-1,6,-1);
                    }else{ state_rotation_r++; }
                    break;
                }case 1:{  // primera-->normal
                    if(tetrimino_selected[5]==9)  {sw_borde_r=1;decrement_tetrimino_col();}
                    Rotate_tetromino( 10, 1,1,2,-1,3,2,5,-1,6,-1);
                    if( !verify_bound() ){
                         Rotate_tetromino( 10, 1,-1,2,1,3,-2,5,1,6,1);
                         if(sw_borde_r) increment_tetrimino_col();
                    }else{ state_rotation_r=0; }
                    break;
                }
            }
            break;
        }
    }
    Put_piece(tetrimino,0);
}


void Left_moving()
{
    Put_piece(7,0);
    decrement_tetrimino_col();
    if ( tetrimino_selected[1]<0 || tetrimino_selected[3]<0 || 
         tetrimino_selected[5]<0 || tetrimino_selected[7]<0 ){
        increment_tetrimino_col();
    }else{ // verificar si se topa con alguna pieza
        if( !verify_bound() ){
            increment_tetrimino_col();
        }
    }
    Put_piece(tetrimino,0);
}

void Right_moving()
{
    Put_piece(7,0);
    increment_tetrimino_col();
    if ( tetrimino_selected[1]==10 || tetrimino_selected[3]==10 || 
         tetrimino_selected[5]==10 || tetrimino_selected[7]==10 ){
        decrement_tetrimino_col();
    }else{          // verificar si se topa con alguna pieza
        if( !verify_bound() ){
            decrement_tetrimino_col();
        }
    }
    Put_piece(tetrimino,0);
}

int Down_piece()
{
    int ret=1;
    Put_piece(7,0);
    increment_tetrimino_row();
    if( tetrimino_selected[0]==20 || tetrimino_selected[2]==20 || 
        tetrimino_selected[4]==20 || tetrimino_selected[6]==20 ){
        decrement_tetrimino_row();
        ret=0;
    }else{  // verifica si se topa con alguna pieza
        if( !verify_bound() ){
            decrement_tetrimino_row();
            ret=0;
        }
    }
    Put_piece(tetrimino,0);
    return ret;
}

void Put_statistics()
{
    Color(green_blocks ? 70 : 214,232); // 214
    int i;
    Iterator up i [0:1:7]{
        At 9+(2*i), 10; Print "=%3d", tetrimino_count[i];
    }
    Reset_color;
}

void Select_piece()
{

    static int first=1;
    if( first ){
        tetrimino = rand() % 7; // selecciona tetrimino 0,1,2,3,4,5,6
        int i;

        Iterator up i [ 0:1:8 ]{
            switch( tetrimino ){
                case 0: { tetrimino_selected[i] = tetrimino_T[i]; break; }
                case 1: { tetrimino_selected[i] = tetrimino_Z[i]; break; }
                case 2: { tetrimino_selected[i] = tetrimino_J[i]; break; }
                case 3: { tetrimino_selected[i] = tetrimino_I[i]; break; }
                case 4: { tetrimino_selected[i] = tetrimino_L[i]; break; }
                case 5: { tetrimino_selected[i] = tetrimino_S[i]; break; }
                case 6: { tetrimino_selected[i] = tetrimino_O[i]; break; }
            }
        }
        first=0;
        counter_tetromino++;
        tetrimino_count[tetrimino]++;
    }else{
        int i;

        Iterator up i [ 0:1:8 ]{
            tetrimino_selected[i] = tetrimino_next[i];
        }
        tetrimino = next_tetrimino;
        tetrimino_count[tetrimino]++;
    }
    state_rotation_r=state_rotation_l=0; /* inicia en posición normal */
    Put_statistics();
}

void Select_next()
{
    next_tetrimino = rand() % 7; // selecciona tetrimino 0,1,2,3,4,5,6
    
    /* rutina que evita que se repitan tetrominos más de dos veces */
    if ( next_tetrimino == tetrimino ){
        ++counter_tetromino;
        if (counter_tetromino>2){
             while ( (next_tetrimino = rand() % 7) == tetrimino ) {;}
             counter_tetromino=1;
        }
    }else counter_tetromino=1;
    
    /* selecciona forma del tetromino */
    int i;
    Iterator up i [ 0:1:8 ]{
        switch( next_tetrimino ){
            case 0: { tetrimino_next[i] = tetrimino_T[i]; break; }
            case 1: { tetrimino_next[i] = tetrimino_Z[i]; break; }
            case 2: { tetrimino_next[i] = tetrimino_J[i]; break; }
            case 3: { tetrimino_next[i] = tetrimino_I[i]; break; }
            case 4: { tetrimino_next[i] = tetrimino_L[i]; break; }
            case 5: { tetrimino_next[i] = tetrimino_S[i]; break; }
            case 6: { tetrimino_next[i] = tetrimino_O[i]; break; }
        }
    }
}

int Put_piece(int tetrimino, int active)
{
    if( active ){
        if(base[tetrimino_selected[0]][tetrimino_selected[1]] ||
           base[tetrimino_selected[2]][tetrimino_selected[3]] ||
           base[tetrimino_selected[4]][tetrimino_selected[5]] ||
           base[tetrimino_selected[6]][tetrimino_selected[7]]){
           return 0;
        }
    }
    base[tetrimino_selected[0]][tetrimino_selected[1]] = tetrimino_color[tetrimino];
    base[tetrimino_selected[2]][tetrimino_selected[3]] = tetrimino_color[tetrimino];
    base[tetrimino_selected[4]][tetrimino_selected[5]] = tetrimino_color[tetrimino];
    base[tetrimino_selected[6]][tetrimino_selected[7]] = tetrimino_color[tetrimino];

    return 1;
}

void Put_next_piece()
{
    int i;
    String block; //="\u2B15";▣
    switch( block_type ){
        case 0: { Let ( block, "\u25A3" ); break; }
        case 1: { Let ( block, "\u2B15" ); break; }
        case 2: { Let ( block, "\u2598" ); break; }
        case 3: { Let ( block, "\u2593" ); break; }
        case 4: { Let ( block, "\u2588" ); break; }
    }
    Color(tetrimino_color[next_tetrimino],232);
    Iterator up i [ 0:2:8 ]{
        Gotoxy( tetrimino_next[i]+3, tetrimino_next[i+1]+(next_tetrimino==3 ? 6:7));
        Print "%s",block;
    }
    Flush_out;
    Reset_color;
    Free secure block;
}

void Init_array_base()
{
    int i,j;
    Iterator up i[0:1:ROWS]{
        Iterator up j[0:1:COLUMNS]{
            base[i][j] = 0;
        }
    }
}

int Verify_full_lines(long *time)
{
    int lineasClear=0, i,j, suma;
    String cl = "XXXXXXXXXX";

    i=ROWS-1;
    while( i>=0 ){
        suma=0;
        Iterator up j[0:1:COLUMNS]{
            When( base[i][j] ) ++suma;
        }
        if (suma==COLUMNS){  
            if( sw_play_present )
                system(sound[0]);
            ++lineasClear;

            *time = *time - complexity; // ajusto el tiempo de caída con cada línea borrada.
            if( *time < 80 ) *time = 80;  /* límite de tiempo mínimo */
            
            /* borro línea visualmente */
            int k;
            Iterator down k [ 255:-1:BACKCOLOR]{
                Color_fore (k);
                At i+2, 3+wide; Print "%s", cl; Flush_out;
                usleep(10000);
            }

            /* ajusto la matriz de tetrominos */
            Iterator down k [ i-1 :-1: -1]{
                Iterator up j[ 0:1:COLUMNS]{
                    base[ (k+1)][ j] = base[ k][ j];
                }
            }
            i=ROWS-1;  /* vuelvo a empezar desde el principio, porque la matriz está ajustada */
            Print_blocks(1,0);
        }else --i;
    }
    Free secure cl;
    return lineasClear;
}

void baja_cortina_de_hierro(int from, int increment, int end)
{
    int i;
    sleep(1);
    if( sw_play_present )
        system( sound[3] );
    String cortina_de_hierro;
        
    Get_fn_let( cortina_de_hierro, Replicate("\u2B15",COLUMNS));
    Atcol 3+wide;
    Iterator up i [from :increment: end]{ 
        Atrow i+2;
        Color(239,248); Print "%s", cortina_de_hierro;
        Flush_out;
        usleep(90000);
    }
    Free secure cortina_de_hierro;

}

void Print_blocks(int type, int init)
{
    int i,j;
    String block, back="\u25CB";
    
    switch( block_type ){
        case 0: { Let ( block, "\u25A3" ); break; }
        case 1: { Let ( block, "\u2B15" ); break; }
        case 2: { Let ( block, "\u2598" ); break; }
        case 3: { Let ( block, "\u2593" ); break; }
        case 4: { Let ( block, "\u2588" ); break; }
    }
    
    Iterator up i [0:1:ROWS]{
       Iterator up j [0:1:COLUMNS]{
           At i+2, j+3+wide;
           if ( type == 1 ){
                if ( base[i][j] ){
                    if( kaleidoscope ){
                         Color(rand()%256,232); //Print "%s", block;
                    }else{
                         Color(base[i][j],232);
                    }
                    Print "%s", block;
                    
                }else{
                    Color(BACKCOLOR+2,BACKCOLOR);Print "%s", back;
                }
           }else{ // perdió el juego y muestra todo de un mismo color!
                if ( base[i][j] ){
                    Color(VOIDCOLOR+2,VOIDCOLOR);Print "%s", block;
                    //usleep(1000);
                }else{
                    Color(BACKCOLOR+2,BACKCOLOR);Print "%s", back;
                }
           }
       }
    }
    /* si perdió, baja la cortina de hierro */
    if ( !type ){
        Flush_out;
        baja_cortina_de_hierro(0, 1, ROWS);
    }
    
   /* inicia tetromino jugable como brillante la hueá */
    if ( init ){
       Iterator up i[ BACKCOLOR:1:255]{
           Color(i,i);
           Gotoxy( tetrimino_selected[0]+2, tetrimino_selected[1]+3+wide); Print " ";
           Gotoxy( tetrimino_selected[2]+2, tetrimino_selected[3]+3+wide); Print " ";
           Gotoxy( tetrimino_selected[4]+2, tetrimino_selected[5]+3+wide); Print " ";
           Gotoxy( tetrimino_selected[6]+2, tetrimino_selected[7]+3+wide); Print " ";
           Reset_color;
           Flush_out;
           usleep(10000);
       }
    }

    Flush_out;
    Free secure block, back;
}


/* Dibuja escenario */

void Put_time_bonus(int timeBonus)
{
    Reset_color;
    Color_fore(249); // 28 34 70
    Bold;
    At 2,14+wide; Print "┏TIME┓";
    At 3,14+wide; Print "┃    ┃";
    At 4,14+wide; Print "┗━━━━┛";
    Color_fore(255);  // 46
    At 3,16+wide; Print "%2d", timeBonus;
    
    Bold_off;
    Reset_color;
    Flush_out;
}

void Put_points(int score, int high, int level, int lines)
{
    Color(46,232); Bold;
    At 10,15+wide; Print "%*d",7, score;
    At 13,15+wide; Print "%*d",7, high;
    At 16,16+wide; Print "%3d", level;
    At 19,16+wide; Print "%4d", lines;
                   Bold_off;
    Reset_color;
}

GD_VIDEO Put_next_box(GD_VIDEO next_box)
{
    Gotoxy(next_box,2,10);  Box_solid( next_box, 4,3,232,232);  // 6,4
    Color_fore(next_box,255);
    Color_back(next_box,232);
    Outvid(next_box, 2,10, "\033[1mNEXT\033[22m");
    Reset_text(next_box);
    return next_box;
}


GD_VIDEO Put_field(GD_VIDEO field, int complexity)
{
    //Gotoxy(field,1,2);   Box_solid( field, 22,10,240,BACKCOLOR);
    
    String block="\u25A3", block2="\u25A3\u25A3", bound="\u25c6";
    String block3="\u25A3\u25A3\u25A3",block4="\u25A3\u25A3\u25A3\u25A3";
    int i;
    Color_fore(field, green_blocks ? 22:240);
    Color_back(field, 234);
    Iterator up i [1:1:22]{
        Outvid(field,i,2+wide, bound);
        Outvid(field,i,13+wide, bound);
    }
    Iterator up i[2:1:14]{
        Outvid(field,22,i+wide, bound);
        Outvid(field,1,i+wide, bound);
    }
    Reset_text(field);
    
    Free secure bound;
    
    Color_back(field,green_blocks ? 70 : 196); 
    Color_fore(field,232);
    Outvid(field,6,2,"\033[1m-STATISTICS-\033[22m");
    Reset_text(field);
    
    Color_back(field,232);
    Color_fore(field,tetrimino_color[0]); 
      Outvid(field,8,7,block); Outvid(field,9,6,block3);
    Color_fore(field,tetrimino_color[1]);
      Outvid(field,10,6,block2); Outvid(field,11,7,block2);
    Color_fore(field,tetrimino_color[2]);
      Outvid(field,12,6,block); Outvid(field,13,6,block3);
    Color_fore(field,tetrimino_color[3]);
      Outvid(field,15,5,block4);
    Color_fore(field,tetrimino_color[4]);
      Outvid(field,17,6,block3); Outvid(field,16,8,block);
    Color_fore(field,tetrimino_color[5]);
      Outvid(field,19,6,block2); Outvid(field,18,7,block2);
    Color_fore(field,tetrimino_color[6]);
      Outvid(field,20,7,block2); Outvid(field,21,7,block2);
      
    Free secure block,block2,block3,block4;

    Color_fore(field,green_blocks ? 28 : 196); // 82
    Color_back(field,232);
    
    Outvid(field,9, 14+wide, "\033[1m┏━SCORE━┓");
    Outvid(field,10,14+wide, "┃       ┃");
    Outvid(field,11,14+wide, "┗━━━━━━━┛");

    Outvid(field,12,14+wide, "┏━HIGH━━┓");
    Outvid(field,13,14+wide, "┃       ┃");
    Outvid(field,14,14+wide, "┗━━━━━━━┛");

    Outvid(field,15,14+wide, "┏━LEVEL━┓");
    Outvid(field,16,14+wide, "┃       ┃");
    Outvid(field,17,14+wide, "┗━━━━━━━┛");

    Outvid(field,18,14+wide, "┏━LINES━┓");
    Outvid(field,19,14+wide, "┃       ┃");
    Outvid(field,20,14+wide, "┗━━━━━━━┛\033[22m");
    
    Reset_text(field);
    if (complexity==1){
        Color_fore(field,green_blocks ? 46 : 46);
        Outvid(field, 4,  21+wide, "NORMAL");
    }else if (complexity==2){
        Color_fore(field,green_blocks ? 46 : 226);
        Outvid(field, 4,  21+wide, "MIDDLE");
    }else if (complexity==3){
        Color_fore(field,green_blocks ? 46 : 202);
        Outvid(field, 4,  21+wide, "HARD");
    }else if (complexity==4){
        Color_fore(field,green_blocks ? 46 : 196);
        Outvid(field, 4,  21+wide, "RUDE");
    }

    return field;
}

/* Presentación del juego */

void Title(int wide)
{
    Name(wide);
    Color(232,196);
    //At 8,5;  Bold; Print "FROM RUSIA WITH LOVE"; Bold_off;
    At 8,5+wide;  Bold; Print "THE SOVIET MIND GAME"; Bold_off;
    Flush_out;
    Color(196,232);
    At 12,5+wide; Print "By Alekséi Pázhitnov";
    At 14,9+wide; Print "Programmed by";
    At 16,11+wide; Print "Mr.Dalien";
    At 18,13+wide; Print "2023";
}

void Text_normal(int wide)
{
    Atcol 4+wide;
    Atrow 9;  Print "The speed of the game";
    Atrow 10; Print "increases linearly in";
    Atrow 11; Print "the minimum unit of";
    Atrow 12; Print "time.";
    
    Atrow 14; Print "This game mode is";
    Atrow 15; Print "useful to train your";
    Atrow 16; Print "brain.";
}

void Text_middle(int wide)
{
    Atcol 4+wide;
    Atrow 9;  Print "Game speed increases";
    Atrow 10; Print "by two units of time.";
    
    Atrow 12; Print "This game mode is";
    Atrow 13; Print "useful to train your";
    Atrow 14; Print "brain.";
}

void Text_hard(int wide)
{
    Atcol 4+wide;
    Atrow 9;  Print "Game speed increases";
    Atrow 10; Print "by three units of";
    Atrow 11; Print "time.";
    
    Atrow 13; Print "This game mode is";
    Atrow 14; Print "used to introduce you";
    Atrow 15; Print "to a competition.";

}

void Text_rude(int wide)
{
    Atcol 4+wide;
    Atrow 9;  Bold; Print "Competition mode."; Bold_off;
    Atrow 10; Print "Game speed increases";
    Atrow 11; Print "by four units of";
    Atrow 12; Print "time.";
    
    Atrow 13; Print "If the line erase time";
    Atrow 14; Print "is zero,the game speed";
    Atrow 15; Print "will increase by one";
    Atrow 16; Print "unit of time for each";
    Atrow 17; Print "tetromino placed,until";
    Atrow 18; Print "you erase one line.";    
}

void Show_controls(int wide)
{
    Color(232,196);
    At 3,8+wide;  Bold; Print "GAME CONTROLS"; Bold_off;
    Color(202,232);
    Atcol 3+wide;
    Atrow 5; Print "   A,D = move tetromino";
    Atrow 6; Print "     W = release";
    Atrow 7; Print " Space = speed up";
    Atrow 8; Print "     J = rotate left";
    Atrow 9; Print "     K = rotate right";
    Atrow 10; Print "     Q = quit";
    
    Atrow 12; Print "\x1b[38;5;196m------------------------"; Reset_color;
    Color(202,232);
    Atrow 13; Print " Bonus lines cleared:";
    Atrow 14; Print " 4=1000,3=500,2=100";
    Atrow 15; Print " Special bonus by time";
    
    Atrow 17; Print "\x1b[38;5;196m------------------------"; Reset_color;
    Color(202,232);
    Atcol 4+wide;
    Atrow 18; Print "-Punishment if time";
    Atrow 19; Print " out.";
    Atrow 20; Print "-You win at level 20.";
    Flush_out;
}

void Presentation(int complexity)
{
    GD_VIDEO field;
    Init_video( &field );
    int wide = 6;
    Gotoxy( field, 1,2+wide); Box_solid( field, 22,24,240,232);
    
    Refresh(field);
    Title(wide);
    Reset_color;
    Pause();
    
   /* segunda pantalla */
    Refresh(field);
    
    Color(196,232);
    At 3,3+wide; Print "MODE:";
    if (complexity==1){
        Color_fore(46);
        Atcol 3+wide;
        Atrow 5; Print " ▄   ▄   ▄   ▄ ▄   ▄  ▄ ";
        Atrow 6; Print "█ █ █ █ ▀▄█ █ █ █ █▄█ █ ";
        Atrow 7; Print "▀ ▀  ▀  ▀ ▀ ▀ ▀ ▀ ▀ ▀  ▀";
        Text_normal(wide);

    }else if (complexity==2){
        Color_fore(226);
        Atcol 4+wide;
        Atrow 5; Print " ▄ ▄  ▄ ▄▄  ▄▄  ▄   ▄▄";
        Atrow 6; Print "█ █ █ ▄ █ █ █ █ █  █▀ ";
        Atrow 7; Print "▀ ▀ ▀ ▀ ▀▄▀ ▀▄▀  ▀  ▀▀";
        Text_middle(wide);

    }else if (complexity==3){
        Color_fore(202);
        Atcol 7+wide;
        Atrow 5; Print "▄ ▄  ▄   ▄  ▄▄ ";
        Atrow 6; Print "█▄█ █▄█ ▀▄█ █ █";
        Atrow 7; Print "▀ ▀ ▀ ▀ ▀ ▀ ▀▄▀";
        Text_hard(wide);

    }else if (complexity==4){
        Color_fore(196);
        Atcol 7+wide;
        Atrow 5; Print " ▄  ▄ ▄ ▄▄   ▄▄";
        Atrow 6; Print "▀▄█ █ █ █ █ █▀ ";
        Atrow 7; Print "▀ ▀ ▀▄▀ ▀▄▀  ▀▀";
        Text_rude(wide);
    } 

    Color(232,216);
  //At 20,8; Print "¡Buena suerte!";
    At 20,10+wide; Print "Good luck!";
    Flush_out;
    Reset_color;
    Pause();
    
    Refresh(field);
    Show_controls(wide);
    Reset_color;
    Pause();
    
    Cls;
    Free video field;
}

void Put_game_over()
{
//    if( sw_play_present )
//         system( sound[3] );
    int wide = 6;
    Color(232,196);
    Atcol 5+wide;
    Atrow 9;  Print "  ▄▄  ▄   ▄ ▄   ▄▄ ";
    Atrow 10; Print " █ ▄ █▄█ █ █ █ █▀  ";
    Atrow 11; Print "  ▀▀ ▀ ▀ ▀ ▀ ▀  ▀▀ ";
    Atrow 12; Print "   ▄  ▄ ▄  ▄▄  ▄   ";
    Atrow 13; Print "  █ █ █ █ █▀  ▀▄█  ";
    Atrow 14; Print "   ▀   ▀   ▀▀ ▀ ▀  ";
    Flush_out;
    Reset_color;
}

void Put_you_win(int wide)
{
    Color(46,232);
    Atcol 9+wide;
    Atrow 4; Print " ▄ ▄  ▄  ▄ ▄ ";
    Atrow 5; Print " ▀▄▀ █ █ █ █ ";
    Atrow 6; Print "  ▀   ▀   ▀  ";
    Atrow 7; Print " ▄ ▄ ▄ ▄  ▄  ";
    Atrow 8; Print " █ █ █ ▄ █ █ ";
    Atrow 9; Print "  ▀ ▀  ▀ ▀ ▀ ";
    Flush_out;
}

void Put_mid_game(int wide)
{
    Color(216,232);
    Atcol 6+wide;
    Atrow 4; Print "     ▄ ▄  ▄  ▄  ";
    Atrow 5; Print "    █ █ █ ▄ █ █ ";
    Atrow 6; Print "    ▀ ▀ ▀ ▀ ▀▀  ";    
    Atrow 7; Print "  ▄▄  ▄   ▄ ▄   ▄▄ ";
    Atrow 8; Print " █ ▄ █▄█ █ █ █ █▀  ";
    Atrow 9; Print "  ▀▀ ▀ ▀ ▀ ▀ ▀  ▀▀ ";
    Flush_out;
}

/* el baile del cosaco para medio juego y final virtual */

void Show_cosaco_up(int fila, int columna)
{
   Color_back(232);
   At fila,   columna;  Color_fore(113) ; Print "    ###     ";
   At fila+1, columna;  Color_fore(121) ; Print " ___"; 
   Color_fore(112); Print "(v)"; 
   Color_fore(121); Print "___  ";
   At fila+2, columna;  Color_fore(124) ; Print "    \\╫/     ";
   At fila+3, columna;  Color_fore(124) ; Print "    /^\\     ";
   At fila+4, columna;  Color_fore(121) ; Print "     ║     ";
   At fila+5, columna;  Color_fore(120) ; Print "     ║     ";
   
}

void Show_cosaco_mov1(int fila, int columna)
{
   At fila,   columna;   Color_fore(113) ; Print "    ###     ";
   At fila+1, columna;   Color_fore(121) ; Print "   _";
   Color_fore(112); Print "(\")";
   Color_fore(121); Print "_    ";
   At fila+2, columna;   Color_fore(121); Print "  /_";
   Color_fore(124); Print "\\╫/";
   Color_fore(121); Print "_\\   ";
   At fila+3, columna;   Color_fore(124); Print "    /^\\     ";
   At fila+4, columna;   Color_fore(121); Print "    / \\    ";
   At fila+5, columna;   Color_fore(120); Print "    \\ /    " ;
   Flush_out;
}

void Show_cosaco_mov2(int fila, int columna)
{
   At fila,   columna;   Print "           ";
   At fila+1, columna;   Color_fore(113); Print "    ###    ";
   At fila+2, columna;   Color_fore(121); Print "   _";
   Color_fore(112); Print "(\")";
   Color_fore(121); Print "_    ";
   At fila+3, columna;   Color_fore(121); printf( "   \\");
   Color_fore(124); printf ("\\╫/");
   Color_fore(121); Print "/   ";
   At fila+4, columna;   Color_fore(121); Print "  __";
   Color_fore(124); Print "«^»";
   Color_fore(121); Print "__";
   Color_fore(120); Print "__ " ;
   At fila+5, columna;   Print "  \\        ";
   Flush_out;
}

void Show_cosaco_mov3(int fila, int columna)
{
   At fila,   columna;   Print "           ";
   At fila+1, columna;   Color_fore(113); Print   "    ###       ";
   At fila+2, columna;   Color_fore(121); Print   "   _";
   Color_fore(112); Print "(\")";
   Color_fore(121); Print "_    ";
   At fila+3, columna;   Color_fore(121); Print "  /_";
   Color_fore(124); Print "\\╫/";
   Color_fore(121); Print "_\\   ";
   At fila+4, columna;   Color_fore(120); Print "__";
   Color_fore(121); Print "__";
   Color_fore(124); Print "«^»";
   Color_fore(121); Print "__ "; 
   At fila+5, columna;   Color_fore(120); Print "        /   ";
   Flush_out;
}

void Show_cosaco_mov4(int fila, int columna)
{
   system( sound[6]);
   At fila,   columna;  Color_fore(121); printf( "  \\" );
   Color_fore(113); printf( " ### ");
   Color_fore(121); printf( "/   ");

   Gotoxy (fila+1, columna);  Color_fore(121); printf( "   \\" );
   Color_fore(112); printf ("(^)");
   Color_fore(121); printf ("/    ") ;
   Gotoxy (fila+2, columna);  Color_fore(124); printf( "    \\╫/     ");
   Gotoxy(fila+3, columna);  printf( "    /^\\     ");
   Gotoxy(fila+4, columna);  Color_fore(121); printf ("    / \\    ");
   Gotoxy(fila+5, columna);  Color_fore(120); printf ("   /   \\   ");
   Flush_out;
}

void Show_cosaco_mov5(int fila, int columna)
{
   Gotoxy(fila, columna);     Color_fore(113); printf (  "    ###     "); // "           "
   Gotoxy((fila+1), columna); Color_fore(121); printf (  "   _");
   Color_fore(112); printf ("(\")");
   Color_fore(121); printf ("_   ");
   Gotoxy((fila+2), columna); Color_fore(121);printf (  "  /_");
   Color_fore(124); printf ("\\╫/");
   Color_fore(121); printf ("_\\   " );
   Gotoxy((fila+3), columna); Color_fore(124);printf (  "    /^\\     ");
   Gotoxy((fila+4), columna); Color_fore(121); printf (  "    / \\    ");
   Gotoxy((fila+5), columna); Color_fore(120);printf (  "    \\ /    " );
   Flush_out;
}

void Show_cosaco_mov6(int fila, int columna)
{
   Gotoxy(fila, columna);     Color_fore(113); printf (  "    ###     ");
   Gotoxy((fila+1), columna); Color_fore(121); printf (  "   _");
   Color_fore(112); printf ("(\")");
   Color_fore(121); printf ("_   ");
   Gotoxy((fila+2), columna); Color_fore(121);printf (  "  /_");
   Color_fore(124); printf ("\\╫/");
   Color_fore(121); printf ("_\\   " );
   Gotoxy((fila+3), columna); Color_fore(124);printf (  "    /^\\     ");
   Gotoxy((fila+4), columna); Color_fore(121);printf (   "    | |     ");
   Gotoxy((fila+5), columna); Color_fore(120);printf (   "    | |     ");
   Flush_out;
}

void Show_cosaco_mov7(int fila, int columna)
{
   Gotoxy(fila, columna);     Color_fore(113);printf (   "    ###");
   Color_fore(120); printf (" /   ");
   Gotoxy((fila+1), columna); Color_fore(121);printf (   "   _");
   Color_fore(112); printf ("(^)");
   Color_fore(121); printf ("/    ");
   Gotoxy((fila+2), columna); Color_fore(121);printf (   "  /_");
   Color_fore(124); printf ("\\╫/     ");
   Gotoxy((fila+3), columna); printf (   "    /^\\     ");
   Gotoxy((fila+4), columna); Color_fore(121) ; printf (   "     ║     ");
   Gotoxy((fila+5), columna); Color_fore(120) ; printf (   "     ║     ");
   Flush_out;
}

void Show_cosaco_mov8(int fila, int columna)
{
   Gotoxy(fila, columna);     Color_fore(120); printf (   "  \\");
   Color_fore(113); printf (" ### ");
   Color_fore(120); printf ("/   ");
   Gotoxy((fila+1), columna); Color_fore(121);printf (   "   \\");
   Color_fore(112); printf ("(^)");
   Color_fore(121); printf ("/    "); 
   Gotoxy((fila+2), columna); Color_fore(124);printf (   "    \\╫/     ");
   Gotoxy((fila+3), columna); printf (   "    /^\\     ");
   Gotoxy((fila+4), columna); Color_fore(121) ; printf (   "     ║     ");
   Gotoxy((fila+5), columna); Color_fore(120) ; printf (   "     ║     ");
   Flush_out;
}

void Show_cosaco_love_america(int fila, int columna)
{
   sleep(1);
   Gotoxy((fila+1), columna); Color_fore(121);printf ( "   \\");
   Color_fore(112); printf ("(\")");
   Color_fore(121); printf ("/    ");Flush_out
   usleep(700000);
   Gotoxy((fila+1), columna); Color_fore(121);printf ( "   \\");
   Color_fore(112); printf ("<()");
   Color_fore(121); printf ("/    " );Flush_out
   usleep(500000);
   Gotoxy((fila+1), columna); Color_fore(121);printf ( "   \\");
   Color_fore(112); printf ("()>");
   Color_fore(121); printf ("/    " );Flush_out
   usleep(500000);
}

void Show_cosaco_america_mov1(int fila, int columna)
{
   Gotoxy(fila, columna);     Color_fore(118); printf (   "    ###     ");
   Gotoxy((fila+1), columna); Color_fore(121); printf (   "   _");
   Color_fore(79); printf ("(x)");
   Color_fore(121); printf ("_    ") ;
   Gotoxy((fila+2), columna); Color_fore(121); printf (   "    \\");
   Color_fore(124); printf ("X");
   Color_fore(121); printf ("/     ");
   Gotoxy((fila+3), columna); Color_fore(124); printf (   "    «");
   Color_fore(121); printf ("|");
   Color_fore(124); printf ("»");
   Color_fore(121); printf ("__   ");
   Gotoxy((fila+4), columna); Color_fore(121); printf (   "   /    ");
   Color_fore(120); printf ("/   ");
   Gotoxy((fila+5), columna); Color_fore(120); printf (   "   \\         ");
   Flush_out;
   
}

void Show_cosaco_america_salto(int fila, int columna)
{
   Gotoxy((fila-1), columna); Color_fore(118); printf (    "     ###     ");
   Gotoxy((fila+0), columna); Color_fore(121); printf (    "    _");
   Color_fore(79); printf ( "(x)");
   Color_fore(121); printf ( "_    "); 
   Gotoxy((fila+1), columna); Color_fore(121); printf (    "     \\");
   Color_fore(124); printf ( "X");
   Color_fore(121); printf ( "/     ");
   Gotoxy((fila+2), columna); Color_fore(121); printf (    "   __");
   Color_fore(124); printf ( "«");
   Color_fore(121); printf ( "|");
   Color_fore(124); printf ( "»");
   Color_fore(121); printf ( "__   ");
   Gotoxy((fila+3), columna); Color_fore(120); printf (    "   \\     /   ");
   Gotoxy((fila+4), columna);             printf (    "            ");
   Flush_out;
}

void Show_cosaco_america_mov2(int fila, int columna)
{
   Gotoxy((fila-1), columna); Color_fore(121); printf (   "              ");
   Gotoxy(fila, columna);     Color_fore(118); printf (   "      ###     ");
   Gotoxy((fila+1), columna); Color_fore(121); printf (   "      ");
   Color_fore(79); printf ("(x)");
   Color_fore(121); printf ("_    "); 
   Gotoxy((fila+2), columna); Color_fore(121); printf (   "      \\ ");
   Color_fore(124); printf ("V");
   Color_fore(121); printf ("|     ");
   Gotoxy((fila+3), columna); Color_fore(120); printf (   "  __");
   Color_fore(121); printf ("__");
   Color_fore(124); printf ("«");
   Color_fore(121); printf ("|/     ");
   Gotoxy((fila+4), columna); Color_fore(121); printf (   "       |     ");
   Gotoxy((fila+5), columna); Color_fore(120); printf (   "       |     ");
   Flush_out;
}
   
void Show_cosaco_america_mov3(int fila, int columna)
{
   Gotoxy(fila, columna);     Color_fore(118); printf (    "    ###     ");
   Gotoxy((fila+1), columna); Color_fore(121); printf (    "   _");
   Color_fore(79); printf ( "(x)");
   Color_fore(121); printf ( "_    "); 
   Gotoxy((fila+2), columna); Color_fore(121); printf (    "    \\");
   Color_fore(124); printf ( "X");
   Color_fore(121); printf ( "/     ");
   Gotoxy((fila+3), columna); Color_fore(121); printf (    "  __");
   Color_fore(124); printf ( "«");
   Color_fore(121); printf ( "|");
   Color_fore(124); printf ( "»     ");
   Gotoxy((fila+4), columna); Color_fore(120); printf (    " /     ");
   Color_fore(121); printf ( "\\    ");
   Gotoxy((fila+5), columna); Color_fore(120); printf (    "       /    ");
   Flush_out;
}

void Show_cosaco_america_mov4(int fila, int columna)
{
   Gotoxy((fila-1), columna); Color_fore(121); printf (    "              ");
   Gotoxy(fila, columna);     Color_fore(118); printf (    "  ###       ");
   Gotoxy((fila+1), columna); Color_fore(121); printf (    " _");
   Color_fore(79); printf ( "(x)");
   Color_fore(121); printf ( "      "); 
   Gotoxy((fila+2), columna); Color_fore(121); printf (    " |");
   Color_fore(124); printf ( "V");
   Color_fore(121); printf ( " /       ");
   Gotoxy((fila+3), columna); Color_fore(121); printf (    "  \\|");
   Color_fore(124); printf ( "»");
   Color_fore(121); printf ( "__");
   Color_fore(120); printf ( "__   ");
   Gotoxy((fila+4), columna); Color_fore(121); printf (    "   |         ");
   Gotoxy((fila+5), columna); Color_fore(120); printf (    "   |         ");
   Flush_out;
}

void You_win(int type)
{
    GD_VIDEO field;
    Init_video( &field );
    int wide = 6;
    
    Gotoxy( field, 1,2+wide); Box_solid( field, 22,24,240,232);
    
    Flush(field);
    
    if( type )
        Put_you_win(wide);
    else
        Put_mid_game(wide);
    
    int i;
   /* Arriba el telón! */
   system(sound[9]);
    for( i=1; i<8; i++){
        Show_cosaco_up(15,10+wide);
        Gotoxy( 13,6+wide); Box_solid( 8-i,17,196,196);
        Color(196,232);
        Gotoxy( 20-i, 6+wide); printf( "█▀█▀█▀█▀█▀█▀█▀█▀█▀█" );
        Color(232,232);
        Gotoxy( 21-i, 6+wide); printf( "                   " );
        Flush_out;
        usleep(200000);
    }
    sleep(1);
    
    int time=5, down_telon=20000;
    if (type)
        system(sound[4]);
    else{
        system(sound[8]);
        time = 8;
        down_telon=200000;
    }
    
    Show_cosaco_up(15,10+wide);

   /* Baile */
    for( i=0; i<time; i++){
        Show_cosaco_mov1(15,10+wide); usleep(100000);
        Show_cosaco_mov2(15,10+wide); usleep(300000);
        Show_cosaco_mov1(15,10+wide); usleep(100000);
        Show_cosaco_mov3(15,10+wide); usleep(300000);
        Show_cosaco_mov1(15,10+wide); usleep(100000);
        Show_cosaco_mov2(15,10+wide); usleep(300000);
        Show_cosaco_mov4(15,10+wide); usleep(400000);
    }
   /* cosaco cambia el baile */
   
    if (type){
        Show_cosaco_love_america(15,10+wide);
        system( sound[7]);
        for( i=0; i<7; i++){
            Show_cosaco_america_mov1(15,10+wide);  usleep(60000);
            Show_cosaco_america_salto(15,10+wide); usleep(80000);
            Show_cosaco_america_mov2(15,10+wide);  usleep(200000);
            Show_cosaco_america_mov3(15,10+wide);  usleep(60000);
            Show_cosaco_america_salto(15,10+wide); usleep(80000);
            Show_cosaco_america_mov4(15,10+wide);  usleep(200000);
        }
    }else{
        Show_cosaco_mov5(15,10+wide); usleep(100000);
        system( sound[6]); Show_cosaco_mov6(15,10+wide); usleep(100000);
        Show_cosaco_mov7(15,10+wide); usleep(100000);
        system( sound[6]); Show_cosaco_mov8(15,10+wide); usleep(100000);
    }
   /* Y baja el telón de acero */
    if (!type) system(sound[9]);
    for( i=7; i>0; i--){
        Gotoxy( 13,6+wide); Box_solid( 8-i,17,196,196);
        Color(196,232);
        Gotoxy( 20-i, 6+wide); printf( "█▀█▀█▀█▀█▀█▀█▀█▀█▀█" );
        Color(232,232);
        Gotoxy( 21-i, 6+wide); printf( "                   " );
        Flush_out;
        usleep(down_telon);
    }
    sleep(1);
    
    if (type)
        system( sound[5]);

    Free_video (field);
}

void Show_statistics(int score, int high, int level, int total_lines)
{
    Cls;
    
    Name(-2);
    Reset_color;

    Color ( 232,196);

    Gotoxy(11,9); Bold; printf( "SUMMARY"); Bold_off;
    Flush_out;
    
    Reset_color;
    Color_fore(196);

    Gotoxy( 14, 3); printf( "█▀█▀█▀█▀█▀█▀█▀█▀█▀█" );
    Flush_out;
     
    Show_cosaco_mov5(16,7); usleep(100000);
    system( sound[6]); Show_cosaco_mov6(16,7); usleep(100000);
    Show_cosaco_mov7(16,7); usleep(100000);
    system( sound[6]); Show_cosaco_mov8(16,7); usleep(100000);

    sleep(1);
    system(sound[9]);
    int i;
    for( i=7; i>=0; i--){
        Gotoxy( 14,3); Box_solid( 8-i,17,196,196);
        Color(196,232);
        Gotoxy( 21-i, 3); printf( "█▀█▀█▀█▀█▀█▀█▀█▀█▀█" );
        Color(232,232);
        Gotoxy( 22-i, 3); printf( "                   " );
        Flush_out;
        usleep(200000);
    }
    Reset_color;
    Color(232,196);
    Goto_y(4); Bold;
    Goto_x(16); Print "Score  :%d", score;
    Goto_x(17); Print "Level  :%d", level;
    Goto_x(18); Print "Cleared:%d lins", total_lines;
    Bold_off;
    Flush_out;
    if ( score > high ){
        sleep(1);
        Goto_x(19); Bold; Print "["; Color(196,232); Print "New High Score"; Color(232,196); Print "]";Bold_off;
        Flush_out;
        system( sound[2] );
    }
    
    sleep(1);
    Pause();
    
}
/* EOF */
