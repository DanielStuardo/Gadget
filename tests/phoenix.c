#include <gadget/gadget.h>

LIB_GADGET_START

#define DIR_LEFT  -1
#define DIR_RIGHT  1
#define TOPE_ACTORES  67

const char* letters[3][36]={{"╭━╮","┏━╮","╭━┓","┏━╮","╭━┓","╭━┓","╭━┓","┳ ┳"," ┳ ","  ┳","┳┏ ","┳  ","╭┳╮","╭━╮","╭━╮","┏━╮","╭━╮","┏╮ ","╭━┓","━┳━","┳ ┳","┳ ┳","┳ ┳","┏┓┳","┳ ┳","┏━┓"," ","╭╮"," ","╭━╮"," "," "," "," ","┏","┓"},  
                            {"┣━┫","┣━┫","┃  ","┃ ┃","┣━ ","┣━ ","┃━┓","┣━┫"," ┃ ","  ┃","┣┻╮","┃  ","┃┃┃","┃ ┃","┃ ┃","┣━╯","┃ ┃","┣┻╮","╰━╮"," ┃ ","┃ ┃","┃┏╯","┃┃┃","╭╋╯","╰┳╯","╭━╯"," ","┣╯"," "," ╭╯"," ","●","━","━","┃","┃"},  
                            {"┻ ┻","┗━╯","╰━┛","┗━╯","╰━┛","┻  ","╰━╯","┻ ┻"," ┻ ","┗━╯","┻ ┻","╰━┛","┻ ┻","┻ ┻","╰━╯","┻  ","╰╋╯","┻ ┻","┗━╯"," ┻ ","╰━╯","┗╯ ","╰┻╯","┻┗┛"," ┻ ","┗━┛"," ","● ","●"," ● ","▛","●","━"," ","┗","┛"}};  

//                 A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, ,!,.,?,,,:,=,-,(,)
int size_letter[]={3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,1,2,1,3,1,1,1,1,1,1};

/*
const char* letters[3][35]={{" ▄ ","█  "," ▄▄","  █","   "," ▄▄"," ▄▄","█  ","▄"," ▀","▟  ","█ ","     ","   ","    "," ▄▄"," ▄▄","   ","  ","▄█▄","   ","    ","     ","   ","  ▄","   "," ","█▛"," ","▄▀▄"," "," ","  ","  ","  "},
                            {" ▄▙","█▄ ","▟  "," ▄█","▟█▀","▟▄ ","▟ ▄","█▄ ","▄"," █","█▄▀","█ ","▟▀▄▀▙","▟▀▙","▄▀▀▄","▟ ▛","▟ █","█▄▀","▄▀"," █ ","█ █","▜▙ ▛","▜ ▄ ▛","▀▄▀","▜▄▛","▀▀█"," ","█ "," "," ▄▀"," ","▄","▄▄","▄▄","▀▄"},
                            {"▀▄▀","▀▄▀","▀▄▄","▀▄▀","▀▄▄","█  "," █▀","█ ▙","█","▄▛","█▀▙","▀▄","█ ▀ █","█ █","▀▄▄▀","█▀ "," ▀█","█  ","▄▀"," ▀▄","▀▄▀"," ▜▛ "," ▜▀▛ ","▄▀▄","▄▛ ","▄█▄"," ","▄ ","▄"," ▄ ","▛","▄","▄▄","  ","▀ "}};
*/
//                 A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, ,!,.,?,,,;,=,-,>
//int size_letter[]={3,3,3,3,3,3,3,3,1,2,3,2,5,3,4,3,3,3,2,3,3,4,5,3,3,3,1,2,1,3,1,1,2,2,2};
/*
const char* letters_C[3][26]={{"▟▀▙","▟▀▙","▟▀▀","█▀▙","▟▀▀","▟▀▀","▟▀▀","█ █","█","  █","█  ","█  ","█▙ ▟█","█▙ █","▟▀▀▙","█▀▙","▟▀▀▙","█▀▙","▟▀▀","▀▀█▀▀","█  █","█  █","█    █","▀▄ ▄▀","▜   ▛","▀▀▀▛"},
                              {"█▄█","█▄▛","█  ","█ █","█▄ ","█▄ ","█ ▄","█▄█","█","  █","█▄▀","█  ","█ ▀ █","█ ▜█","█  █","█▄▛","▜  ▛","█▄▛","▀▀▄","  █  ","█  █","▜  ▛","▜ ▟▙ ▛","  █  "," ▀▄▀ "," ▄▀ "},
                              {"█ █","█▄▛","▜▄▄","█▄▛","▜▄▄","█  ","▜▄▛","█ █","█","▜▄▛","█ █","▜▄▄","█   █","█  █","▜▄▄▛","█  "," ▀▜▙","█ █","▄▄▀","  █  ","▜▄▄▛"," ▜▛ "," ▜▛▜▛ ","▄▀ ▀▄","  █  ","▜▄▄▄"}};

//                   A,B,C,D,E,F, G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z, ,!,. 
int size_letter_C[]={3,3,3,3,3,3, 3,3,1,3,3,3,5,4,4,3,4,3,3,5,4,4,6,5,5,4}; //,1,2,1};
*/

const char *cLedsh[3][10] = {{"┏━┓", " ┓ ", " ━┓", " ━┓","┓ ┓","┏━ ","┏━ "," ━┓","┏━┓","┏━┓"},
                             {"┃ ┃", " ┃ ", "┏━┛", " ━┫","┗━┫","┗━┓","┣━┓","  ┃","┣━┫","┗━┫"},
                             {"┗━┛", " ┻ ", "┗━ ", " ━┛","  ┻"," ━┛","┗━┛","  ┻","┗━┛","  ┻"}};
/*
const char* heroe[4]={"    \x1b[38;5;196m▟^▙ ",
                      " \x1b[38;5;226m▟███████▙ ",
                      " \x1b[38;5;226m▜███████▛ ",
                      "  \x1b[38;5;202m▜=====▛ "};
*/
const char* heroe[4]={"    \x1b[38;5;21m▟┃▙ ",
                      " \x1b[38;5;15m▟ ▟█░█▙ ▙ ",
                      " \x1b[38;5;15m▜███████▛ ",
                      "  \x1b[38;5;196m▜=====▛ "};
                      
const char* heroe_dead[4][3]={{"    ███ ",   "     ▄     ","          "},
                              {" ▟███████▙ ","   ▟███▙   ","    ▄▄    "},
                              {" ▜███████▛ ","   ▜███▛   ","   ████   "},
                              {"  ▜█████▛ ", "    ▀▀▀    ","    ▀▀    "}};
/* se eleva */
const char* heroe_eleva[5][4]={{"    \x1b[38;5;21m▟^▙ ",   "    \x1b[38;5;21m▗█▖   ",   "    \x1b[38;5;21m▗█▖   ", "    \x1b[38;5;21m▗█▖ "},
                               {"  \x1b[38;5;15m▟██░██▙ ", "   \x1b[38;5;15m▟█░█▙  ",   "   \x1b[38;5;15m ▟░▙   ", "   \x1b[38;5;15m ▟░▙ "},
                               {" \x1b[38;5;15m▜███████▛ ","  \x1b[38;5;15m▟██I██▙ ",   "  \x1b[38;5;15m▄█III█▄ ", "  \x1b[38;5;15m▙▟▒▒▒▙▟ "},
                               {"  \x1b[38;5;196m▜=====▛ ", "   \x1b[38;5;196m▜===▛ ",  "   \x1b[38;5;196m▜=▛ ",   "   \x1b[38;5;15m▜III▛ "},
                               {"                        ", "                        ", "                        ","    \x1b[38;5;196m▜●▛ "},
                          };

/*
const char *enemy[4][3]={{"    ┏●┓    ", "  ▄     ▄  "," ▜       ▛ "},
                         {"   ▟█▄█▙   ", "▟▀ █━●━█ ▀▙","  ▀▄   ▄▀  "},
                         {"  ▟     ▙  ", "    ▀▀▀    ","    █▀█    "},
                         {"  ▜     ▛  ", "           ","    ┗●┛    "}
                         };
*/
const char *enemy[5][3]={{"    ┏●┓    ", "  ▄     ▄  "," ▜       ▛ "},
                         {"    ▟▄▙    ", "▟▀ █━●━█ ▀▙","  ▀▄   ▄▀  "},
                         {"   ▟   ▙   ", "    ▀▀▀    ","    █▀█    "},
                         {"   █   █   ", "           ","    ┗●┛    "},
                         {"   ▜   ▛   ", "           ","           "}
                         };

const char *evento_1[5][3]={{"   ▀███    ",   " ██▄   ▄██ ",  "▀█       █▀"},
                            {"   ██▀▀█   ",   "█▀ █████ ▀█",  " ▀█▄   ▄█▀ "},
                            {"  ▄█▀ ▀█▄  ",   "    █▀█▀   ",  " ▀▀█████▀  "},
                            {"  ▀█   █▀  ",   "           ",  "    █▀█▀   "},
                            {"   █   █   ",   "           ",  "           "}
                            };

const char *evento_2[5][3]={{"   █████   ",   " ████  ████",  "███    ▄███"},
                            {"  ████████ ",   "██ █████▀██",  " ███▄  ███ "},
                            {"████    ███",   " █ █████ █ ",  "  ███████  "},
                            {" ███   ████",   "    ▀▀ ▀   ",  "   █████   "},
                            {"  ██   ██  ",   "           ",  "           "}
                            };

/*
const char *evento_1[4][3]={{"    @●@    ",   " /▙     /▙ ",  " ▙       / "},
                            {"   /   ▙   ",   "▛   ▙@●@/ ▙",  "  ▙     ▛  "},
                            {"  |     |  ",   "    * *    ",  "   ▙@●@/   "},
                            {"  |     |  ",   "           ",  "    * *    "}};

const char *evento_2[4][3]={{"    █●@    ",   " ██     /█ ",  " █       █ "},
                            {"   ██  █   ",   "/  █@██/  █",  "  █     █  "},
                            {"  █     |  ",   "    █ *    ",  "   ▙█●@█   "},
                            {"  |     █  ",   "           ",  "    █ *    "}
                            };
*/
const char *evento_3[7][2] = {{"  ▄          ","      .       "},
                              {"    ▄    ▄▙  ","  · * .*   ~  "},
                              {" ▀   ▀█▄██ ▄ ","  : _ *       "},
                              {" /▀█▄███▀ :  ","  / *:-*   . *"},
                              {"    ▀███▄    ","     :^ * .   "},
                              {"▀ *█▀  ▀█    "," * .      *  ."},
                              {" ▄.      ▀  ▄","   l      *   "},
                              };


//aplay -q tests/dataPhoenix/Laser-SoundBible.wav </dev/null >/dev/null 2>&1 &
//aplay -q tests/dataPhoenix/phoenix_blaster.wav </dev/null >/dev/null 2>&1 &
const char* sound[16] = {"aplay -q tests/dataPhoenix/Laser-SoundBible.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/ExplosionHeroe.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_laser_antimateria.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/Laser_01.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/ufo_launch.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/RedAlert.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_inicia_batalla.wav </dev/null >/dev/null 2>&1",
                        "aplay -q tests/dataPhoenix/phoenix_bono.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_transformation.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_minimize.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_show_score.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_mision.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_blaster.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/phoenix_balance.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/condicionRed.wav </dev/null >/dev/null 2>&1 &",
                        "aplay -q tests/dataPhoenix/alive.wav </dev/null >/dev/null 2>&1 &"};

const char*string_fondo[5] = {"ffplay -nodisp -loglevel -8 -loop 9999 tests/dataPhoenix/phoenix_fondo_1.wav </dev/null >/dev/null 2>&1 &",
                              "ffplay -nodisp -loglevel -8 -loop 9999 tests/dataPhoenix/phoenix_fondo_2.wav </dev/null >/dev/null 2>&1 &",
                              "ffplay -nodisp -loglevel -8 -loop 9999 tests/dataPhoenix/phoenix_fondo_4.wav </dev/null >/dev/null 2>&1 &",
                              "ffplay -nodisp -loglevel -8 -loop 9999 tests/dataPhoenix/phoenix_fondo_3.wav </dev/null >/dev/null 2>&1 &",
                              "ffplay -nodisp -loglevel -8 -loop 9999 tests/dataPhoenix/phoenix_modo_nodriza.wav </dev/null >/dev/null 2>&1 &"};
// PATHf<-"ffplay -nodisp -loop 9999 "+PATH

void put_heroe( int x, int y);
//void put_shoot();
int put_shoot();
void verify_shoot_protons();
void verify_shoot_alta_frecuencia();
void verify_shoot_antimateria();

void define_todo(int etapa, int subetapa);
void obtiene_valores();
void put_regenerator(int x, int y, int r);
void put_actor(int x, int y, int r, int c);
void clear_actor(int x, int y);
int put_bomba( int j, int etapa );
void explota_heroe();
void put_explosion(int i);
//void verifica_enemigos_tocados();
///int verifica_disparo(int x, int y, int j, int tipoDisparo );
void put_ready();
void put_big_message(char *msg, int nColorF);
void put_leds(int num, int nColorF);
char * put_sound( int typeSound );
void kill_sound( char * PID_SOUND );
void kill_all_sounds();
void se_eleva_siguiente_mision();
void PEM_bombas();
void show_info();
void show_balance(int heroe_golpeado, int bonus);
void put_score();
void put_hf();
void put_am();
void put_PEM();
int play_win();
void reset_bombas();
void put_life();
void put_game_over();
void presentation(int explanation);
void you_score();
//void put_title();
void blinking(int x, int y, int num);
void put_big_title();


int px,py;
int score=0, heroe_golpeado=0, life=7;

int x,y,e,i,j,k,dx,dy,r,b,sx,sy,sc;
int actores, acabo_con_todos, tope, le_tope, ri_tope, sw_conteo_final;
int shooterx=0, shootery=0, shoot=0;
int swAntimateria, ctaAntimateria=0,swAltaFrecuencia,ctaAltaFrecuencia=0, ctaPulso=0, swprotons;
char tipoDisparo[7], tipoBomba[7];
int dirx[TOPE_ACTORES];
int diry[TOPE_ACTORES];
int posx[TOPE_ACTORES];
int posy[TOPE_ACTORES];
int batir[TOPE_ACTORES];
int estado[TOPE_ACTORES];
int colores[TOPE_ACTORES];
int tarda_explosion[TOPE_ACTORES];
int shotx[TOPE_ACTORES];
int shoty[TOPE_ACTORES];
int bomba[TOPE_ACTORES];
///int bshot[TOPE_ACTORES];

// IMPRIMIR EL VALOR ACTUAL DE LTOPE, PARA SABER CUANDO SE PONE LENTO.
//int lTOPE[20]={25, 20, 20, 15, 13, 10, 9, 8,7, 6,6,6,6,6,6,  5,5,5,5,5};  // original
//int lTOPE[20]={20, 17, 14, 11, 11, 11, 11, 10,10, 9,9,9,9,9,9,  5,5,5,5,5};
int lTOPE[21]=  {75, 50, 35, 30, 25, 20, 15, 13, 11, 10, 10, 10, 10, 10, 10,  8,7,6,  5,5,5}; // probado

int lTOPE_B[21]={50, 30, 20, 13, 10,  9,  8,  7,  6,  6, 5, 5, 5, 5, 5,  4,4,3,3,3,3};
int resucita;

int typewriting;
int swGeometricFly=0;

int tope_resucita, half_resucita, indice_resucita=0; //, indiceTmp;
int limite_fondo[4];
String PIDPILLS;

/* parametros */
#define INCREMENT   30 //25 //18
int swetapa=7;  // 7-1 esto debe ser proporcionado por el programa principal
int hasta_donde=150; //60; //+(6*INCREMENT); //57+(19*6); //+(29*4); //+29*6;  // debe ser proporcionado por el programa principal
int level=1;
int swAbort=0;

/* etapa 2 */
int avance;
char * cfld_force[9];
char * cinta0, * cinta1;
int tinit_color[]={16,17,18,19,20,21,27,33,39,45,51,45,39,33,27,21,20,19,18,17};
int tcolor[]={196,197,198,199,200,201,207,212,213,218,219,218,213,212,207,201,200,199,198,197}, icolor=0, 
    ctcolor[]={22,28,34,40,46,40,34,28,22}, ccolor=0;

void appear_mothership(){

 int i;
 system( sound[9] );
 Iterator up i [0:1:11]{
    Color_fore( tinit_color[i]);

    At avance,  13;  Print "                         ███      ██████▙      ███";
    At avance+1,13;  Print "                         █ ▀▀▀▀▀▀▀███████▀▀▀▀▀▀▀ █";
    At avance+2,13;  Print "                         █▄▄▄▄▄▄▄▄▜█████▛▄▄▄▄▄▄▄▄█";
    At avance+3,13;  Print "                              ██  ▟█████▙██";
    At avance+4,13;  Print "      █ █ █ █ █ █ █ █ █ █ █ █ █ █████████▙█ █ █ █ █ █ █ █ █ █ █ █ █ █";
    At avance+5,13;  Print "     █████████████████████████████████████████████████████████████████";                             
    At avance+6,13;  Print "   █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█";
    At avance+7,13;  Print "  ██                                                                   ██";
    At avance+8,13;  Print " ███                                                                   ███";
    Flush_out;
    usleep(100000);
 }
}

void put_mothership(int ncolor){
 Color_fore(ncolor);
 At avance-1,13;  Print "                                                                         ";
 At avance,  13;  Print "                         ┏━┓      ▟█▀▀▀█▙      ┏━┓";
 At avance+1,13;  Print "                         ┃ ┗┳┳┳┳┳┳█ |=| █┳┳┳┳┳┳┛ ┃";
 At avance+2,13;  Print "                         ┗━━┻┛┃┃┗┛▜█▄=▄█▛┃┃┗┛┗┻━━┛";
 At avance+3,13;  Print "                              ┗┛  ▟█▛O▜█▙┗┛                              ";
 At avance+4,13;  Print "      ┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓▟██ ┻ ██▙┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓ ┏ ┓    ";
 At avance+5,13;  Print "     █▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄███O┫█┣O███▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀█    ";                             
 At avance+6,13;  Print "   █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ┳ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█  ";
 At avance+7,13;  Print "  ▟█                                                                   █▙ ";
 At avance+8,13;  Print " ▟██                                                                   ██▙";
/*
 At 14,13; Print "    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
 At 15,13; Print "     ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
 At 16,13; Print "       ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓";
 At 17,13; Print "         ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
 At 18,13; Print "            ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
 At 19,13; Print "                ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒";
 At 20,13; Print "                     ░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░";
 At 21,13; Print "                          ░░░░░░░░░░░░░░░░░░░░░░░";
 At 22,13; Print "                               ░░░░░░░░░░░░░";
 */
 Flush_out;
// Pause();
}

void put_fldForce(){
   At avance+9,  17; puts(cfld_force[0]);
   At avance+10, 18; puts(cfld_force[1]);
   At avance+11, 20; puts(cfld_force[2]);
   At avance+12, 22; puts(cfld_force[3]);
   At avance+13, 25; puts(cfld_force[4]);
   At avance+14, 29; puts(cfld_force[5]);
   At avance+15, 34; puts(cfld_force[6]);
   At avance+16, 39; puts(cfld_force[7]);
   At avance+17, 44; puts(cfld_force[8]);

}

void put_field_force(){

   icolor++; if (icolor==20) icolor=0;
   Color_fore( tcolor[icolor]);
   put_fldForce();
   Flush_out;
}

void anula_field_force(){
   int i,j,size_field_force[]={67,65,61,57,51,43,33,23,13};
   Iterator up i[0:1:9]{
       for( j=0; j<size_field_force[i]; j++){
           cfld_force[i][j]=' ';
       }
   }
   Reset_color;
   put_fldForce();
}

void put_cinta_force(){ 
   Color_fore(226);Bold;
   At avance+7, 17; puts(cinta0);
   Atrow avance+8;  puts(cinta1);
   Flush_out;
   Reset_color;
}

void rotate_cinta(){ 
   int j;

   char buffer0 = cinta0[66];
   char buffer1 = cinta1[66];
   for( j=66; j>0; j--){
      cinta0[j] = cinta0[j-1];
      cinta1[j] = cinta1[j-1];
   }
   cinta0[0] = buffer0;
   cinta1[0] = buffer1;

}

void put_centro_de_poder(){
   
   Color_fore( ctcolor[ccolor]);
   At avance+5, 50; puts("█");
   Flush_out;
   ccolor++;
   if ( ccolor == 9 ) ccolor = 0;
}

void explota_nave_nodriza(){
   int t, x=avance+5;
   system( sound[1] );
        t=255;
        while ( t>=232 ){
           
              if( t%2 ) 
                   put_mothership(240);
              else
                   put_mothership(15);
              Color_fore ( t ); 

              printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            x-3,45,evento_3[0][0],
                            x-2,45,evento_3[1][0], 
                            x-1,45,evento_3[2][0],
                            x,45,evento_3[3][0],
                            x+1,45,evento_3[4][0],
                            x+2,45,evento_3[5][0],
                            x+3,45,evento_3[6][0]
                             );
              Flush_out;
              usleep(100000);
           
           --t;
        }
        put_mothership(232);

       // Flush_out;
}

int play_mothership(int over_play, int level_ms){
   
   cinta0 = (char*)calloc(68,1);
   cinta1 = (char*)calloc(68,1);
   int j;
   Iterator up j [0:1:67]{
       cinta0[j]='=';
       cinta1[j]='=';
   }
   cinta0[67]='\0';
   cinta1[67]='\0';
   avance=5;
   ccolor=0;
   icolor=0;
   
   String PIDPILLS;
   
   cfld_force[0] = (char *) calloc( 71, 1);
   //strcpy(cfld_force[0], "###################################################################");
   strcpy(cfld_force[0], "===================================================================");

   cfld_force[1] = (char *) calloc( 68, 1);
   strcpy(cfld_force[1], "=================================================================");

   cfld_force[2] = (char *) calloc( 63, 1);
   strcpy(cfld_force[2], "=============================================================");

   cfld_force[3] = (char *) calloc( 59, 1);
   strcpy(cfld_force[3], "=========================================================");

   cfld_force[4] = (char *) calloc( 53, 1);
   strcpy(cfld_force[4], "===================================================");

   cfld_force[5] = (char *) calloc( 45, 1);
   strcpy(cfld_force[5], "===========================================");

   cfld_force[6] = (char *) calloc( 35, 1);
   strcpy(cfld_force[6], "=================================");

   cfld_force[7] = (char *) calloc( 25, 1);
   strcpy(cfld_force[7], "=======================");

   cfld_force[8] = (char *) calloc( 15, 1);
   strcpy(cfld_force[8], "=============");
   strcpy(tipoBomba,"●");
   heroe_golpeado=0;
   
   if (!over_play){
      px=50; py=45;
   }
   int c=0;
   int dir=0;
   int k=0;

   define_todo( 2, 0 );
   int tope = actores;
     
   Get_fn_let( PIDPILLS, put_sound(4) );
   show_info();
   put_heroe( px, py );

   appear_mothership();

   unsigned long tshoot=Tic(), t=Tic(), headms=Tic(), fldforce=Tic(), tcinta=Tic();
   unsigned long bret=Tic();
      
   /*
     TODO: decribir vuelo sinusoidal de ciertos phoenix sobre el héroe.
           Los phoenix que golpeen al tanque deben provocar su destrucción????????
           No. Deben provocar el descontrol del tanque por algunos segundos.
   */ 
   Flush_inp;
   
   while( c!=ESCAPE ){
       if( Timer( &bret, 4L ) ){
           
           if ( k >= tope ) k=-3;
           if ( bomba[ k]==1 ){
               Color_fore(15);
               if( put_bomba( k, 52 /*52*/ ) ){
                   explota_heroe();
                   if ( !life ) break;
               }
           }else{
               if ( rand()%10 >= 8 ){
                   if ( Is_between( posx[ k], py, py+10 ) ){
                       bomba[k]=1;
                       shotx[k] = posx[k];
                       shoty[k] = posy[k]+avance;
                   }
               }
           }
           k+=3;
       }

       if ( Timer( &tshoot, 10L-level_ms ) ){
           if ( shoot>0 ){
               put_shoot();
               if( shooterx == avance+17 ){
                   if( Is_between(shootery, 44,56) ){
                       if ( cfld_force[8][shootery-44] == '=' ){
                           system( sound[12] );
                           cfld_force[8][shootery-44] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>44 ) cfld_force[8][shootery-45] = ' ';
                               if ( shootery<56 ) cfld_force[8][shootery-43] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}
                           
                           --shoot; // = 0;
                           At avance+17, 44; puts(cfld_force[8]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+16 ){
                   if( Is_between(shootery, 39,61) ){
                       if ( cfld_force[7][shootery-39] == '=' ){
                           system( sound[12] );
                           cfld_force[7][shootery-39] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>39 ) cfld_force[7][shootery-40] = ' ';
                               if ( shootery<61 ) cfld_force[7][shootery-38] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}
                           --shoot; // = 0;
                           At avance+16, 39; puts(cfld_force[7]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+15 ){
                   if( Is_between(shootery, 34,66) ){
                       if ( cfld_force[6][shootery-34] == '=' ){
                           system( sound[12] );
                           cfld_force[6][shootery-34] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>34 ) cfld_force[6][shootery-35] = ' ';
                               if ( shootery<66 ) cfld_force[6][shootery-33] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}

                           --shoot; // = 0;
                           At avance+15, 34; puts(cfld_force[6]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+14 ){
                   if( Is_between(shootery, 29,71) ){
                       if ( cfld_force[5][shootery-29] == '=' ){
                           system( sound[12] );
                           cfld_force[5][shootery-29] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>29 ) cfld_force[5][shootery-30] = ' ';
                               if ( shootery<71 ) cfld_force[5][shootery-28] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}
                           --shoot; // = 0;
                           At avance+14, 29; puts(cfld_force[5]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+13 ){
                   if( Is_between(shootery, 25,75) ){
                       if ( cfld_force[4][shootery-25] == '=' ){
                           system( sound[12] );
                           cfld_force[4][shootery-25] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>25 ) cfld_force[4][shootery-26] = ' ';
                               if ( shootery<75 ) cfld_force[4][shootery-24] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}

                           --shoot; // = 0;
                           At avance+13, 25; puts(cfld_force[4]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+12 ){
                   if( Is_between(shootery, 22,78) ){
                       if ( cfld_force[3][shootery-22] == '=' ){
                           system( sound[12] );
                           cfld_force[3][shootery-22] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>22 ) cfld_force[3][shootery-23] = ' ';
                               if ( shootery<78 ) cfld_force[3][shootery-21] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}

                           --shoot; // = 0;
                           At avance+12, 22; puts(cfld_force[3]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+11 ){
                   if( Is_between(shootery, 20,80) ){
                       if ( cfld_force[2][shootery-20] == '=' ){
                           system( sound[12] );
                           cfld_force[2][shootery-20] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>20 ) cfld_force[2][shootery-21] = ' ';
                               if ( shootery<80 ) cfld_force[2][shootery-19] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}
                           --shoot; // = 0;
                           At avance+11, 20; puts(cfld_force[2]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+10 ){
                   if( Is_between(shootery, 18,82) ){
                       if ( cfld_force[1][shootery-18] == '=' ){
                           system( sound[12] );
                           cfld_force[1][shootery-18] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>18 ) cfld_force[1][shootery-19] = ' ';
                               if ( shootery<94 ) cfld_force[1][shootery-17] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}

                           --shoot; // = 0;
                           At avance+10, 18; puts(cfld_force[1]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+9 ){
                   if( Is_between(shootery, 17,83) ){
                       if ( cfld_force[0][shootery-17] == '=' ){
                           system( sound[12] );
                           cfld_force[0][shootery-17] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>17 ) cfld_force[0][shootery-18] = ' ';
                               if ( shootery<96 ) cfld_force[0][shootery-16] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}
                           --shoot; // = 0;
                           At avance+9, 17; puts(cfld_force[0]);
                           score+=50; put_score();
                       }
                   }
               }else if( shooterx == avance+8 ){
                   if( Is_between(shootery, 17,83) ){
                       if ( cinta1[shootery-17] == '=' ){
                           system( sound[12] );
                           cinta1[shootery-17] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>17 ) cinta1[shootery-18] = ' ';
                               if ( shootery<96 ) cinta1[shootery-16] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}
                           --shoot; // = 0;
                           At avance+8, 17; puts(cinta1);
                           score+=100; put_score();
                       }
                   }
               }else if( shooterx == avance+7 ){
                   if( Is_between(shootery, 17,83) ){
                       if ( cinta0[shootery-17] == '=' ){
                           system( sound[12] );
                           cinta0[shootery-17] = ' ';
                           //if( swAntimateria || swAltaFrecuencia ){
                               if ( shootery>17 ) cinta0[shootery-18] = ' ';
                               if ( shootery<96 ) cinta0[shootery-16] = ' ';
                           //    swAltaFrecuencia = swAntimateria = 0;
                           //    score+=90;
                           //}
                           --shoot;// = 0;
                           At avance+7, 17; puts(cinta0);
                           score+=100; put_score();
                       }
                   }
                   
               }else if (shooterx == avance+5 ){
                   if ( shootery == 50 ){
                       reset_bombas();
                       kill_sound(PIDPILLS);
                       Free secure PIDPILLS;
                       anula_field_force();
                       explota_nave_nodriza();
                       acabo_con_todos=1;
                       break;
                   }
               }else if (shooterx == avance+6){
                   if( Is_between(shootery, 17,83) && shootery!=50 ){
                       shoot=0;
                       At shooterx, shootery; puts( " " );
                   }
               }
           }
       }
//       if ( Timer( &tcentro, 250L)) {
// 7          put_centro_de_poder();
//       }
       if ( Timer( &headms, 4000L-(level_ms*500) )){ //5500
           avance++;
           if (avance >= 30){
               system(sound[14]);
           }
           if (avance > 35) {
               reset_bombas();
               kill_sound(PIDPILLS);
               Free secure PIDPILLS;
               life=0;
               explota_heroe();
               break;
           }
       }
       if ( Timer( &fldforce, 100L )){
           put_mothership(15);
           put_field_force();
           put_cinta_force();
           put_centro_de_poder();
       }
       if( Timer( &tcinta, 80L )){
           rotate_cinta();
       }
       
       if( Timer( &t, 40L ) ){
           if ( Kbhit() ){
               c = Getch();
               if(c == ARROW_LEFT )       { dir=DIR_LEFT; }
               else if(c == ARROW_RIGHT ) { dir=DIR_RIGHT;}
               else if(c == ARROW_DOWN )  { dir=0;}
               else if(c==99){      // c=dispara carga de protones
                   if (!shoot){
                       shoot=1;
                       shooterx=px;
                       shootery=py+5;
                       strcpy(tipoDisparo,"┃");//"●"); // ▍
                       system( sound[0] );
                   }
               }
               else if (c==122){    // z= dispara laser antimateria
                   if (!shoot){
                       if (ctaAntimateria){
                           shoot=5-level_ms; //4;
                           shooterx = px;
                           shootery = py+5;
                           //swAntimateria = 1; // no sirve con contra nave nodriza
                           strcpy(tipoDisparo,"█");
                           system( sound[2] );
                           ctaAntimateria--;
                           put_am();
                           
                       }
                   }
               }
               else if (c==118){  // v= pulso PEM debil resetea bombas
                   //if (swetapa<=5){
                       if (ctaPulso){
                           system("aplay -q tests/dataPhoenix/phoenix_PEM.wav </dev/null >/dev/null 2>&1 &");
                           PEM_bombas();
                           --ctaPulso;
                           put_PEM();
                       }
                   //}
               }
               else if (c==120){  // x= dispara laser de alta frecuencia
                   if (!shoot){
                       if (ctaAltaFrecuencia ){
                           shoot=3-(int)(level_ms/2); //2;
                           shooterx = px;
                           shootery = py+5;
                           //swAltaFrecuencia = 1; // no sirve contra nave nodriza
                           strcpy(tipoDisparo,"▓");
                           system( sound[3] );
                           ctaAltaFrecuencia--;
                           put_hf();
                           
                       }
                   }
               }
           }
           py += dir;
           if (py<1) py=1;
           else if (py>87) py=87; //70
           put_heroe( px, py );
       }
       Flush_out;    
   }
   sleep(1);
   Free secure cinta0, cinta1;
   kill_sound(PIDPILLS);
   Free secure PIDPILLS;
   Iterator up k [0:1:9]{
       Free secure cfld_force[k];
   }
   
   if (acabo_con_todos){
       //reset_bombas();
       show_info();
       se_eleva_siguiente_mision();
       sleep(1);
       life++;
       system(sound[7]);
       At 30,39; put_big_message("EXTRA core!",46);
       blinking(51,117,life);
       put_life();
       
       sleep(5);
       Cls; show_info();
       show_balance(heroe_golpeado, 50000);
   }   
   if ( c==ESCAPE ) swAbort=1;
   return acabo_con_todos;
}

void put_intro_mothership(){
   typewriting=0;
   int color[]={88,124,160,196,160,124,88}, i=0, j=0;
   while ( j<4 ){
       At  5,5 ; put_big_message("Warning!", color[i]);
       ++i; if (i==7) {i=0;++j;}
       usleep(100000);
   }
   typewriting=1;
   Reset_color;
   At 12,5 ; put_big_message("located a phoenix battle station!", 34);
   sleep(1);
   At 18,5 ; put_big_message("this station prevents us from",34);
   At 22,5 ; put_big_message("teleporting a regeneration core",34);
   At 26,5 ; put_big_message("for you.",34);
   sleep(1);
   At 32,5 ; put_big_message("you must violate his force field",34);
   At 36,5 ; put_big_message("and destroy the energy baryon",34);
   At 40,5 ; put_big_message("core.",34);
   sleep(1);
   At 46,5 ; put_big_message("good luck, starfighter!",34);
   
   typewriting=0;
   At 52,5 ; put_big_message("end of comunication.",46);
   Pause();
   Cls;
/*   typewriting=1;
   At 10,5 ; put_big_message("if you destroy the battle station,", 34);
   At 14,5 ; put_big_message("it will take time for the phoenix", 34);
   At 18,5 ; put_big_message("to rally, giving us time to send", 34);
   At 22,5 ; put_big_message("you an extra regeneration core.", 34);
   sleep(1);
   At 36,5 ; put_big_message("good luck, starfighter!",34);

   typewriting=0;
   At 50,5 ; put_big_message("Press any key to continue...",46);
   Pause();
   Cls;*/
   sleep(2);
}


/* pulso, alta frec. y antimateria acumulan los no usados */
Main
   //Pause();
   int sw_play_present=1;
   int cnt_mothership = 1;
   int level_ms=0;
   int sw_intro_mothership=1;
   
   if ( Arg_count >= 2 ){
       Get_arg_str( opt_play, 1 );
       if ( Is_equal_str(opt_play,"-nop") ){  // no presentation
            sw_play_present=0;
       }
       Free secure opt_play;
   }
   
   Hide_cursor; 
   Enable_raw_mode();
   Cls;

  /* ffplay tarda en iniciarse, y cuando se inicia por primera vez, malogra put_sound().
     esta línea pretende resolver ese problema. */
   system("ffplay -loglevel -8");

   ///px=50; py=50; show_info(); se_eleva_siguiente_mision();Show_cursor;Stop(1);
   
   ///ctaAltaFrecuencia=20; ctaAntimateria=20; level_ms=4; play_mothership(0, level_ms);Show_cursor;Stop(1);
   
   ///put_intro_mothership();Show_cursor;Stop(1);
   
   //show_balance(0); Show_cursor;Stop(1);
   put_big_title();/// Pause();Show_cursor;Stop(1);
   
   presentation(sw_play_present);// Pause();Show_cursor;Stop(1);


   while( play_win() ){
       
       if ( cnt_mothership % 2 == 0 && cnt_mothership>0 ) {
           Cls;
           if( sw_intro_mothership ){
               put_intro_mothership();
               sw_intro_mothership=0;
           }
           //goto continuar;
           if ( ! play_mothership(0, level_ms) ){
              break;
           }
           ++level_ms;
           if (level_ms > 4 ) level_ms=4; // siempre debe tener este tope!
                                          // de esto depende la etapa de la nave nodriza.
           //continuar:
           //Cls;
       }
    
       --swetapa;
       if (swetapa<0) {swetapa=0;
       }else{
          // if ( swetapa>2 )
               hasta_donde += INCREMENT; //29;
          // if ( hasta_donde == 140 ) hasta_donde=130;
       }
       ++level;
       ++cnt_mothership;
       Cls;
       sleep(1);
       swGeometricFly=0; // prueba.
   }
   kill_all_sounds();
   sleep(1);
   Cls; show_info();
   if ( swAbort ){
       At 7,22 ; put_big_message("mission aborted",196);
       sleep(1);
   }
   show_balance(1, 0);
   put_game_over();
   you_score();
   Show_cursor;
End

int play_win(){
   int c=0;
   int dir=0;
   unsigned long t, refresh, retardo, bret, allkill, tshoot, tmsg, tpicada;
   ///int poneVoz;
//   int tope_resucita, half_resucita, indice_resucita=0; //, indiceTmp;
//   int limite_fondo[4];
//   String PIDPILLS;

   px=50 /*50*/; py=50;
   i=-1; k=-1;
   
   if (swetapa>=4){
       le_tope=-1;
       ri_tope=12;  // {1,5} no solo se limita a la nave, sino a su alrededor
   }else{
       le_tope=2;
       ri_tope=4;
   }
   
   strcpy(tipoBomba,"●"); //
   resucita=0;
   indice_resucita = 0;
   tope_resucita = (int)(hasta_donde/4);
   half_resucita = (int)(hasta_donde/2);
   
   while (indice_resucita<4){
       limite_fondo[ indice_resucita] = tope_resucita;
       tope_resucita += tope_resucita;
       ++indice_resucita;
   }
   ///indiceTmp = 0; 
   indice_resucita = 0;
   
   //ctaPulso = 0;
   //if (swetapa<=4){    // PEM débil
       //ctaPulso=3+ctaPulso;
       ctaPulso=3+(10-swetapa)+ctaPulso;
   //}
    
   swAntimateria=0;
   //ctaAntimateria=1;
   //if (swetapa<5){   // cañon de antimateria
       //ctaAntimateria = 2; //(8-swetapa)+ctaAntimateria;  // incrementara en 1 por cada etapa. inicial=3
   ctaAntimateria = (10-swetapa); //+ctaAntimateria;  // incrementara en 1 por cada etapa. inicial=3
   //}
   swAltaFrecuencia=0;
   //ctaAltaFrecuencia = (10-swetapa)*5 + ctaAltaFrecuencia;  //(1+(5-swetapa)*10)+ctaAltaFrecuencia; // incrementa en 10 cad etapa. inicial=10
   ctaAltaFrecuencia = (10-swetapa)*20 + ctaAltaFrecuencia;
   
   swprotons=0;
   //tipoDisparo[1]='\0';
   define_todo( 1, swetapa );
   tope=1; //4;
   typewriting=0;
   heroe_golpeado=0;
   sw_conteo_final = 0;
   
   show_info();
   put_ready();
   system(sound[6]);
   Cls;
   put_heroe( px, py );

   //level=1;
   //score=0;
   show_info();
   
   Get_fn_let( PIDPILLS, put_sound(indice_resucita) );
   
   t = Tic(); refresh = Tic(); retardo=Tic(); bret = Tic(); allkill = Tic(); tshoot = Tic();tmsg=Tic();
   tpicada=Tic();
   while( c!=ESCAPE ){

       /* refresca el buffer de pantalla.
          al parecer, el buffer se satura en un momento dado, y el juego
          se lagea. Limpiar el buffer parece resolver el problema */
       if ( Timer( &refresh, 2500L-((7-swetapa)*200) ) ){
            Cls;
            show_info();
            ///if ( rand()%10>swetapa ) swGeometricFly=1; else swGeometricFly=0;
       }
       
       //if( Timer( &bret, lTOPE_B[tope-4] ) ){
       if( Timer( &bret, lTOPE_B[tope-1] ) ){
           ++k;
           if ( k == tope ) k=0;
           if ( bomba[ k]==1 ){
               if( put_bomba( k, 52 /*52*/ ) ){
                   explota_heroe();
                   if ( !life ) break;
               }
           }
       }
       if( Timer( &tmsg, 4000L )){
           if (resucita<=half_resucita){
                if( rand()%10<2 ){
                     system (sound[15]); 
                }
           }else{
                if( rand()%10<2 ){
                     system(sound[14]);
                }
           }
           if ( rand()%10>swetapa+2 ) swGeometricFly=1; else swGeometricFly=0;
       }
       
       if( Timer( &tpicada, 15000L )){
           if ( rand()%10>swetapa+2 ) swGeometricFly=1; else swGeometricFly=0;
           //if(swGeometricFly) swGeometricFly=0; else swGeometricFly=1;
       }
       //if( Timer( &retardo, lTOPE[tope-4] )){
       if( Timer( &retardo, lTOPE[tope-1] )){
           ++i;
           if( i==tope ) i=0;
           obtiene_valores();
          
           if( !e ){
               if ( tarda_explosion[ i] ){ //> -1 ){
                   put_explosion( i);
               }    
           }else{  // e>0
               if ( !bomba[ i] ){
                   if ( Is_between (x, (py+le_tope), (py+ri_tope))){
                       if (rand()%10 > 5 /*swetapa*/){  // lanzarán mas bombas conforme avance etapas
                          bomba[ i] = 1;
                          shotx[ i] = x+6; //(x+3)
                          shoty[ i] = y;
                       }
                   }else{
                       if ((rand()%10<3)){
                          bomba[ i] = 1;
                          shotx[ i] = x+6;
                          shoty[ i] = y;
                       }
                   }
               }
               clear_actor( x, y );
               //put_actor( x, y, r, 0 );

               switch( swGeometricFly ){
                  case 0: {
                      if ( /*Is_between (i, 3, 12) && */ rand()%10<=6 ){ 
                          if (y<40){  //28 ){
                              dx = x>py ? -abs(dx): abs(dx); //x>px
                          }else{
                              dy = dy>0 ? -dy: dy; //abs(dy);
                          }
                      }else{
                          if (x<4) {
                              dx = abs(dx);
                          }else if (x>=rand()%87){  //70
                              dx = -dx;
                          }
                          dirx[ i] = dx; //Clamp (dx, 4, 87);
                          if (y<=2) {
                              dy = abs(dy);
                          }else if (y>=rand()%40 ){ // 26
                              dy = -dy;
                          }
                   
                          diry[ i] = dy; //Clamp(dy, 2, 40 );
                      }

                      x = x+dx;
                      y = y+dy;

                      if (y<1) y=1;
                      if (r==2) r = -1;
                      ++r;
                      batir[ i] = r;
                      break;
                  }
                  case 1:{
                      if (r==2) r = -1;
                      ++r;
                      if( dx>0 ){
                          ++x;
                          if( dy>0 ){
                              y+=2; //++y;
                              r=2;
                          }else{
                              y-=2; //--y;
                          }
                          
                      }else{
                          --x;
                          if( dy>0 ){
                              y+=2; //++y;
                              r=2;
                          }else{
                              y-=2; //--y;
                          }
                      }
                      if ( y>=37 ) { dy=-1; y=36; }
                      else if ( y<=1 )  { dy=1; y=2; }
                      if ( x>=87 ) { dx=-2; --x; }
                      else if ( x<=1 )  { dx=2;  ++x; }
                      dirx[ i] = dx;
                      diry[ i] = dy;
                      //x = x+dx;
                      //y = y+dy;
                      
                      batir[ i] = r;
                      break;
                  }
               }
               put_actor( x, y, r, sc );

               posx[ i] = x;
               posy[ i] = y;
               
           }
           
       }

       if ( swprotons) {
           if ( Timer( &tshoot, 10L ) ){
               swprotons = put_shoot();
               verify_shoot_protons();
           }
       }else if ( swAltaFrecuencia ){
           if ( Timer( &tshoot, 5L ) ){
               swAltaFrecuencia = put_shoot();
               verify_shoot_alta_frecuencia();
           }
       }else if ( swAntimateria ){
           if ( Timer( &tshoot, 15L ) ){
               swAntimateria = put_shoot();
               verify_shoot_antimateria();
           }
       }
      

 // se vuelve lento conforme se adentra en la etapa.
       if( Timer( &t, 40L ) ){
           if ( Kbhit() ){
               c = Getch();
               if(c == ARROW_LEFT )       { dir=DIR_LEFT; }
               else if(c == ARROW_RIGHT ) { dir=DIR_RIGHT;}
               else if(c == ARROW_DOWN )  { dir=0;}
               else if(c==99){      // c=dispara carga de protones
                   if (shoot==0){
                       shoot=1;
                       shooterx=px;
                       shootery=py+5;
                       strcpy(tipoDisparo,"┃");//"●"); // ▍
                       system( sound[0] );
                       swprotons=1;
                   }
               }
               else if (c==122){    // z= dispara laser antimateria
                   if (!shoot){
                       if (ctaAntimateria){
                           shoot=1;
                           shooterx = px;
                           shootery = py+5;
                           swAntimateria = 1;
                           strcpy(tipoDisparo,"█");
                           system( sound[2] );
                           ctaAntimateria--;
                           put_am();
                       }
                   }
               }
               else if (c==118){  // v= pulso PEM debil resetea bombas
                   //if (swetapa<=4){
                       if (ctaPulso){
                           system("aplay -q tests/dataPhoenix/phoenix_PEM.wav </dev/null >/dev/null 2>&1 &");
                           PEM_bombas();
                           --ctaPulso;
                           put_PEM();
                       }
                   //}
               }
               else if (c==120){  // x= dispara laser de alta frecuencia
                   if (!shoot){
                       if (ctaAltaFrecuencia ){
                           shoot=1;
                           shooterx = px;
                           shootery = py+5;
                           swAltaFrecuencia = 1;
                           strcpy(tipoDisparo,"▓");
                           system( sound[3] );
                           ctaAltaFrecuencia--;
                           put_hf();
                       }
                   }
               }
               /*else if (c==ARROW_UP){     // verifico si ha terminado todo

                   Break_if( acabo_con_todos );
               }*/
           }
           py += dir;
           if (py<1) py=1;
           else if (py>87) py=87; //70
           put_heroe( px, py );
       }
       
       if( sw_conteo_final ){ ///resucita==hasta_donde){
           if ( Timer (&allkill, 5000L )){ // cada 5 segundos verifica si acabó con todos.
              // if( resucita==hasta_donde ){
                   acabo_con_todos=1; 
                   j=0;
                   do{
                       if (estado[ j] >0 ){
                           acabo_con_todos=0;     // sigue!!
                           break;
                       }
                   }while (++j<tope);
              // }
               Break_if ( acabo_con_todos );
           }
       }
       Flush_out;
   }
   kill_sound(PIDPILLS);
   Free secure PIDPILLS;
   
   if ( c==ESCAPE ) swAbort=1;
   
   //acabo_con_todos=1;
   if (acabo_con_todos){
       reset_bombas();
       se_eleva_siguiente_mision();
       show_balance(heroe_golpeado, 5000);
   }
   if (ctaAntimateria<0) ctaAntimateria=0;
   if (ctaAltaFrecuencia<0) ctaAltaFrecuencia=0;
   if (ctaPulso<0) ctaPulso=0;
   
   return acabo_con_todos;
}

void explanation(){

   At  5,5 ; put_big_message("In the XXII century, Earth", 34);
   At  9,5 ; put_big_message("was invaded by a devastating", 34);
   At 13,5 ; put_big_message("alien force: the Phoenix.",34);

   sleep(1);

   At 19,5 ; put_big_message("The invaders laid waste to",34);
   At 23,5 ; put_big_message("the cities of the united world,",34);
   At 27,5 ; put_big_message("and the survivors managed to",34);
   At 31,5 ; put_big_message("develop an ultimate weapon:",34);
   At 38,5 ; put_big_message("the viking combat ship!",34);
   sleep(1);
   typewriting=0;
   At 50,5 ; put_big_message("Press any key to continue...",46);
   Pause();
   Cls;
   typewriting=1;
   At  5,5 ; put_big_message("You are the best fighter pilot.", 34);
   sleep(1);
   At  11,5 ; put_big_message("You know there are no force field", 34);
   At  15,5 ; put_big_message("to protect us from their black", 34);
   At  19,5 ; put_big_message("hole weapons, but...", 34);
   sleep(1);
   
   At  25,5 ; put_big_message("Our scientists developed a tech", 34);
   At  29,5 ; put_big_message("that mimics the regeneration of", 34);
   At  33,5 ; put_big_message("invaders, but will only allow you", 34);
   At  37,5 ; put_big_message("to be revived seven times.", 34);
   typewriting=0;
   At 50,5 ; put_big_message("Press any key to continue...",46);
   Pause();
   Cls;
   typewriting=1;

   At  5,5 ; put_big_message("Your mission is to kill the", 34);
   At  9,5 ; put_big_message("phoenix hordes and destroy their",34);
   At  13,5 ; put_big_message("motherships.", 34);
   sleep(1);
   At 19,5 ; put_big_message("The world depends on your success.", 34);
   sleep(1);
   At 25,5 ; put_big_message("Now, proceed to study the flight", 34);
   At 29,5 ; put_big_message("manual and combat operations of", 34);
   At 33,5 ; put_big_message("this powerful ship.", 34);
   sleep(2);

   At 40,5 ; put_big_message("-nop: to not see this report again", 196);
   typewriting=0;
   At 50,5 ; put_big_message("Press any key to continue...",46);
   Pause();
   Cls;
   typewriting=1;
}

void big_title(int x,int color){
   
   Color_fore(color);
   At x,35;   Print "███████▙  ██     █  ▟██████▙  ▟██████▙  ██▙     █  ██   ██     ██";
   At x+1,35; Print "██▀▀▀▀▀█  ██     █  ██▀▀▀▀▀█  ██▀▀▀▀▀▀  ███▙    █  ██   ██     ██";
   At x+2,35; Print "██     █  ██     █  ██     █  ██        ████▙   █  ██    ██   ██";
   At x+3,35; Print "██     █  ██     █  ██     █  ██        ██ ▜█▙  █  ██      █▄█";
   At x+4,35; Print "███████▛  ████████  ███    █  ██████    ██  ▜█▙ █  ███     █▀█";
   At x+5,35; Print "███       ███    █  ███    █  ███       ██   ▜█▙█  ███   ██   ██";
   At x+6,35; Print "███       ███    █  ███    █  ███       ███   ▜██  ███  ██     ██";
   At x+7,35; Print "███       ███    █  ▜██████▛  ▜██████▛  ███    ▜█  ███  ██     ██";
   Flush_out;
}
void put_big_title(){
   big_title(10,46);
   typewriting=1;
   At 22,36 ; put_big_message("An epic adventure",46);
   sleep(1);
   At 31,45 ; put_big_message("by mr. dalien",111);
   At 36,60 ; put_leds(2023,111);
   typewriting=0;
   sleep(1);
   At 45,22 ; put_big_message("based on phoenix of tekham",73);
   At 49,33 ; put_big_message("music by starforce",73);
   //sleep(2);
   Pause();
   Cls;
   sleep(1);
}

/*void put_title(){
    Color_fore( 196 );
    At 5,40; Print "       █████  █   █  ███  ████ █   █ ███ █    █";
    At 6,40; Print "        █   █ █   █ █   █ █    ██  █  █   █  █";
    Color_fore( 226 );
    At 7,40; Print "        █   █ █   █ █   █ █    ███ █  █    ██";
    Color_fore( 15);
    At 8,40; Print "        ████   ███  █   █ ███  █ ███  █    ██";
//    Color_fore( 40);
    At 9,40; Print "        █     █   █ █   █ █    █  ██  █   █  █";
    At 10,40;Print "       ███    █   █  ███  ████ █   █ ███ █    █";
    
    Flush_out;
}*/

void presentation(int sw_play_present){
    
    typewriting=1;
    if (sw_play_present){
        system( sound[11]);
        explanation();
    }
    
    //put_title();
    ///big_title(2,34);
    At 7, 15 ; put_big_message("viking starship operations",46);
    
    At 13,15 ; put_big_message("LASERS:",15);
    At 17,22 ; put_big_message(" C ",15);
    At 17,32 ; put_big_message("= Protons",123);
    At 21,22 ; put_big_message(" X ",15);
    At 21,32 ; put_big_message("= high frecuency",123);
    At 25,22 ; put_big_message(" Z ",15);
    At 25,32 ; put_big_message("= Antimater",123);
    At 29,22 ; put_big_message(" V ",15);
    At 29,32 ; put_big_message("= electromagnetic pulse",123);
    At 33,32 ; put_big_message("  (for bombs, and may be...)",123);
    At 39,15 ; put_big_message("lateral arrows = move starship",226);
    ///At 39,71 ; put_big_message("= move starship",226);
    At 43,15 ; put_big_message("arrow down = stop starship",226);
    //At 43,57 ; put_big_message("= stop starship",226);
    
    At 50,15 ; put_big_message("Press any key to begin",46);
    
    typewriting=0;
    Flush_inp;
    Pause();
    Cls;
}

void you_score(){
    Cls;
    system( sound[10]);
    //put_title();
    big_title(5,34);
    
    At 21,30 ; put_big_message("your final score was:",34);
    At 29,55 ; put_leds(score,46);
    
    Flush_inp;
    Pause();
}

void put_game_over(){
   Cls;
   typewriting=1;
   sleep(1);
   At 30,45 ; put_big_message("GAME OVER",196);
   sleep(3);
}
void put_hf(){
   static int sw_hf=1;
   if(ctaAltaFrecuencia){
       At 28,105 ; put_leds(ctaAltaFrecuencia,46); //15);
   }else{
       if( sw_hf ){
           At 24,105 ; put_big_message("Gun HF",240);
           At 28,105 ; put_leds(ctaAltaFrecuencia,240);
           sw_hf=0;
       }
   }
}

void put_am(){
   static int sw_am=1;
   if(ctaAntimateria){
       At 37,105 ; put_leds(ctaAntimateria,46); //15);
   }else{
       if( sw_am ){
           At 33,105 ; put_big_message("Gun AM",240);
           At 37,105 ; put_leds(ctaAntimateria,240); //15);
           sw_am=0;
       }
   }
}

void put_score(){
   At 7,105 ; put_leds(score,46); //15);
   
}

void put_life(){
   At 51,117 ; put_leds(life,226);
}

void put_PEM(){
   static int sw_PEM=1;
   if(ctaPulso){
       At 46,105 ; put_leds(ctaPulso,46); //15);
   }else{
       if( sw_PEM ){
           At 42,105 ; put_big_message("P.E.M.",240);
           At 46,105 ; put_leds(ctaPulso,240); //15);
           sw_PEM=0;
       }
   }
}

void show_info(){
   At 3,105 ; put_big_message("SCORE",34); //159);
   At 7,105 ; put_leds(score,46); //15);
   At 11,105 ; put_big_message("LEVEL",34); //159);
   At 15,105 ; put_leds(level,46); //15);

   if( hasta_donde >= 100 ){
       At 15,114; put_leds(hasta_donde,46);
   }else{
       At 15,117; put_leds(hasta_donde,46);
   }
   put_actor(114,19,2,70);
   //At 15,135; put_leds(swetapa,46);

   if( ctaAltaFrecuencia ){
       At 24,105 ; put_big_message("Gun HF",34); //201);
       At 28,105 ; put_leds(ctaAltaFrecuencia,46); //15);
   }else{
       At 24,105 ; put_big_message("Gun HF",240); //201);
       At 28,105 ; put_leds(ctaAltaFrecuencia,240); //15);
   }
   if( ctaAntimateria ){
       At 33,105 ; put_big_message("Gun AM",34); //201);
       At 37,105 ; put_leds(ctaAntimateria,46); //15);
   }else{
       At 33,105 ; put_big_message("Gun AM",240); //201);
       At 37,105 ; put_leds(ctaAntimateria,240); //15);
   }
   if( ctaPulso ){
       At 42,105 ; put_big_message("P.E.M.",34); //201);
       At 46,105 ; put_leds(ctaPulso,46); //15);
   }else{
       At 42,105 ; put_big_message("P.E.M.",240); //201);
       At 46,105 ; put_leds(ctaPulso,240); //15);
   }
   At 51,105 ; put_big_message("UP",226);
   At 51,117 ; put_leds(life,226);
   put_heroe( 55, 113 );
}

void show_balance(int heroe_golpeado, int bonus_base){

   //char cequis[1024];
   //sprintf( cequis, "\x1b[19;78H█ █\x1b[20;78H █ \x1b[21;78H█ █");
   system( sound[13] );
   typewriting=1;
   At 15,20 ; put_big_message("clear zone:",34);
   sleep(1);
   At 15,62 ; put_leds(bonus_base,226);
   sleep(1);
   At 19,36 ; put_big_message("gun hf:",34);
   sleep(1);
   printf( "\x1b[38;5;34m\x1b[19;78H▄ ▄\x1b[20;78H▄▀▄");
   At 19,82 ; put_leds(100,34);
   At 19,62 ; put_leds(ctaAltaFrecuencia,226);
   sleep(1);
   At 23,36 ; put_big_message("gun AM:",34);
   sleep(1);
   printf( "\x1b[38;5;34m\x1b[24;78H▄ ▄\x1b[25;78H▄▀▄");
   At 23,82 ; put_leds(500,34);
   At 23,62 ; put_leds(ctaAntimateria,226);
   sleep(2);
   At 27,46 ; put_big_message("PEM:",34);
   sleep(1);
   printf( "\x1b[38;5;34m\x1b[28;78H▄ ▄\x1b[29;78H▄▀▄");
   At 27,82 ; put_leds(1000,34);
   At 27,62 ; put_leds(ctaPulso,226);
   sleep(1);
   At 31,38 ; put_big_message("bonus:",34);
   sleep(1);
   int bonus = (heroe_golpeado ? 0 : 20000);
   At 31,62 ; put_leds( bonus,226);
   sleep(3);
   At 36,20 ; put_big_message("total bonus: ",46);
   bonus = bonus_base + bonus + (ctaAltaFrecuencia*100) + (ctaAntimateria*500) + (ctaPulso*1000);
   At 36,64 ; put_leds( bonus,226);
   
   score += bonus;
   blinking(7, 105, score);
   put_score();
   typewriting=0;
   sleep(6);
   //Pause();
}
void blinking(int x, int y, int num){
   int color[]={232,234,236,238,240,242,244,246,248,250,252,254,
                252,250,248,246,244,242,240,238,236,234,232}, i=0, j=0;
   while ( j<3 ){
       At x,y ; put_leds( num,color[i]);
       ++i; if (i==23) {i=0;++j;}
       usleep(30000);
   }

}

void se_eleva_siguiente_mision(){
   char eleva[4096];
   int i=0;
   system(sound[8]);
   while (i<4){
      sprintf( eleva, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            px,py,heroe_eleva[0][i],
                            px+1,py,heroe_eleva[1][i], 
                            px+2,py,heroe_eleva[2][i],
                            px+3,py,heroe_eleva[3][i],
                            px+4,py,heroe_eleva[4][i] );
      puts(eleva);
      usleep(300000);
      ++i;
   }
   usleep(100000);
   system( sound[4] );
   int tx=0;
   while (px>1){
      
      sprintf( eleva, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            px,py,heroe_eleva[0][3],
                            px+1,py,heroe_eleva[1][3], 
                            px+2,py,heroe_eleva[2][3],
                            px+3,py,heroe_eleva[3][3],
                            px+4,py,heroe_eleva[4][3] );
      puts(eleva);
      usleep(80000-( (tx++)*1000) );
      sprintf( eleva, "\x1b[%d;%dH            \x1b[%d;%dH            \x1b[%d;%dH            \x1b[%d;%dH            \x1b[%d;%dH            ",
                            px,py,
                            px+1,py,
                            px+2,py,
                            px+3,py,
                            px+4,py );
      puts(eleva);
      --px;
   }
   sleep(2);
}

//◢ ◣  ◤ ◥
//◥ ◤  ◣ ◢

void PEM_bombas(){

  int j,x,y;
  Color_fore(196);
  printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                      px,py,heroe_dead[0][0],
                      px+1,py,heroe_dead[1][0],
                      px+2,py,heroe_dead[2][0],
                      px+3,py,heroe_dead[3][0]);
            Flush_out;
            
     j=0 ;
     shoot=0;
     At shooterx, shootery;
     puts( " " );
     while (j<=actores){
       if (bomba[ j] == 1){
          bomba[ j]=0;
          x=shotx[ j];
          y=shoty[ j];
          
          Color_fore(255);
          At y-1, x-1; puts ("◢ ◣");
          At y,x;      puts (" ");
          At y+1, x-1; puts ("◥ ◤");
          
          usleep(50000);
          At y-1, x-1; puts ("   ");
          At y+1, x-1; puts ("   ");
          
       }
       if ( estado[ j]>0 ){
          if ( rand()%10 >= 7 )
              estado[ j]=0;
       }
       ++j;
     }
     Flush_out;
}

void put_big_message(char *msg, int nColorF)
{
    //String tmsg;
    //Fn_let( tmsg, Upper( msg ) );
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
        else{ 
            lett = toupper(lett);
            i = lett - 'A';
            /*if( isupper(lett) ){
                sw=1; i = lett - 'A';
            }else{
                i = lett - 'a';
            }*/
            ///i = isupper(lett) ? lett - 'A' : lett - 'a';
        }
        static char letter[1024];
        sprintf( letter,"\x1b[38;5;%dm\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[0m",
                nColorF, row, col, (letters[0][i]),
                row+1,col, (letters[1][i]),
                row+2,col, (letters[2][i]));
//                row+1,col, (sw ? letters_C[1][i]:letters[1][i]),
//                row+2,col, (sw ? letters_C[2][i]:letters[2][i]));
        const char* psimb = letter;
        col = col + (size_letter[i]+1);
        ++ps;
        //Print "%s",psimb; Flush_out;
        puts(psimb);
        if(typewriting) usleep(80000);
    }
    //Free secure tmsg;
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
    //Flush_out;
    Free secure cnum; //, score;
}
void put_ready(){
    At 30,40 ; put_big_message("Ready!",46);
}
  
void put_heroe( int x, int y){
   //char chero[2048];
   //if ( !heroe_golpeado ){
   //sprintf(chero, "\x1b[38;5;15m\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
   //printf( "\x1b[38;5;15m\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
   printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                  x,y,heroe[0],
                  x+1,y,heroe[1],
                  x+2,y,heroe[2],
                  x+3,y,heroe[3]);
/*   }else{
   sprintf(chero, "\x1b[38;5;196m\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                  x,y,heroe[0],
                  x+1,y,heroe[1],
                  x+2,y,heroe[2],
                  x+3,y,heroe[3]);

   }*/
   //puts(chero);
   //Flush_out;
}

int put_shoot(){
   At shooterx, shootery; puts( " " );

   Color_fore(226);
   --shooterx;
   At shooterx, shootery; puts( tipoDisparo );

   if (shooterx==1){   
       shoot=0;
       At shooterx, shootery; puts( " " );
       //swAntimateria = swAltaFrecuencia = 0;
       return 0;
   }
   return 1;
}
/*void put_shoot(){
   At shooterx, shootery; puts( " " );

   Color_fore(226);
   --shooterx;
   At shooterx, shootery; puts( tipoDisparo );

   if (shooterx==1){   
       shoot=0;
       At shooterx, shootery; puts( " " );
       swAntimateria = swAltaFrecuencia = 0;
   }
}*/

void reset_bombas(){
  int j,y;

     j=0;

     shoot=0;
     At shooterx, shootery;
     puts(" ");
     
     while (j<actores){
        if (bomba[j]==1 ){
            bomba[j]=0;
            x=shotx[ j];
            y=shoty[ j];
            At y, x;
            puts( " ");
        }
        ++j;
     }

}
void explota_heroe(){

    reset_bombas();
    int t=0;
    system( sound[9] );
    while ( t<3 ){
        Color_fore ( (!t)? 15: (t==1) ? 39 : 51 );
        printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                  px,py,heroe_dead[0][t],
                  px+1,py,heroe_dead[1][t],
                  px+2,py,heroe_dead[2][t],
                  px+3,py,heroe_dead[3][t]);
        Flush_out;
        ++t;
        usleep(170000);
    }

    heroe_golpeado=1;
    --life;
    put_life();
    if( life ){
        t=2;
        //system( sound[9] );
        while ( t>=0 ){
            Color_fore ( (!t)? 15: (t==1) ? 39 : 51 );
            printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                      px,py,heroe_dead[0][t],
                      px+1,py,heroe_dead[1][t],
                      px+2,py,heroe_dead[2][t],
                      px+3,py,heroe_dead[3][t]);
            Flush_out;
            --t;
            usleep(170000);
        }

        system( sound[5] );
    }else{

        system( sound[1] );
        t=255;
        while ( t>=232 ){
           Color_fore ( t ); //(t==3)? 255: (t==2) ? 245 : (t==1) ? 239: 232 );

           if (t > 235) { //==3){
              //sprintf( evento, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
              printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            px-1,py,evento_3[0][0],
                            px,py,evento_3[1][0], 
                            px+1,py,evento_3[2][0],
                            px+2,py,evento_3[3][0],
                            px+3,py,evento_3[4][0],
                            px+4,py,evento_3[5][0],
                            px+5,py,evento_3[6][0]
                             );
              //puts(evento);
              usleep(100000);

           }else{
              //sprintf( evento, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
              printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            px-1,py,evento_3[0][1],
                            px,py,evento_3[1][1], 
                            px+1,py,evento_3[2][1],
                            px+2,py,evento_3[3][1],
                            px+3,py,evento_3[4][1],
                            px+4,py,evento_3[5][1],
                            px+5,py,evento_3[6][1]
                            );
              //puts(evento);
              usleep(100000);
           }
           Flush_out;
           
           --t;
        }

        //Flush_out;
    }


}

void verify_shoot_protons(){
    int j=0;
    do{
         if ( estado[ j]>0 ){
            if ( Is_between(shootery, (posx[ j]+1), (posx[ j]+10)) ){
                if ( Is_between( shooterx, posy[ j], posy[ j]+2) ){ 
                    shoot = 0;
                    switch( estado[ j] ){
                        case 1:{ --estado[ j]; break; }
                        case 2:{ --estado[ j];
                            colores[ j ] = 196;
                            system("aplay -q tests/dataPhoenix/phoenix_alien_tocado.wav </dev/null >/dev/null 2>&1 &");
                            break; }
                        //case 3:{ --estado[ j];
                        //    colores[ j] = 93; //13;
                        //    break; }
                        //case 4:{ --estado[ j];
                        //    colores[ j] = 93;
                        //    break; }
                    }
                    swprotons=0;
                    break;
                }
            }
         }
    }while(++j<tope);
}

void verify_shoot_alta_frecuencia(){
    int j=0;
    do{
        if ( estado[ j]>0 ){
            if ( Is_between(shootery, (posx[ j]+1), (posx[ j]+10)) ){
                if ( Is_between( shooterx, posy[ j], posy[ j]+2) ){ 
                    shoot=0;
                    estado[ j]=0;
                    swAltaFrecuencia = 0;
                    break;
                }
            }
        }
    }while(++j<tope);
}

void verify_shoot_antimateria(){
    int j=0;
    do{
        if ( estado[ j]>0 ){
            if ( Is_between(shootery, (posx[ j]+1), (posx[ j]+10)) ){
                if ( Is_between( shooterx, posy[ j], posy[ j]+2) ){
                    estado[ j]=0;
                }
            }
        }
    }while(++j<tope);
}


/*void verifica_enemigos_tocados(){
    int j=0;
    if (swAltaFrecuencia){
        do{
            if ( estado[ j]>0 ){
                estado[ j] = verifica_disparo( posx[ j], posy[ j], j, 2);
                if (!shoot) break;
            }
            ++j;
        }while(j<tope);
    }else if (swAntimateria){
        do{
            if ( estado[ j]>0 ){
                estado[ j] = verifica_disparo( posx[ j], posy[ j], j, 3);
            }
            ++j;
        }while(j<tope);
    }else{
        do{
            if ( estado[ j]>0 ){
                estado[ j] = verifica_disparo( posx[ j], posy[ j], j, 1);
                if (!shoot) break;
            }
            ++j;
        }while(j<tope);
    }
}
               
int verifica_disparo(int x, int y, int j, int tipoDisparo ){
  int v;
  v = estado[ j];
  if ( Is_between(shootery, (x+1), (x+10)) ){
     if ( Is_between( shooterx, y, y+2) ){ 
        switch(tipoDisparo){
        ///if (tipoDisparo==1){
        case 1:{
           shoot = 0;
           switch( v ){
               case 1:{ --v; break; }
               case 2:{ --v;
                        colores[ j ] = 196;
                        //if( j>10 )
                            system("aplay -q tests/dataPhoenix/phoenix_alien_tocado.wav </dev/null >/dev/null 2>&1 &");
                        
                        break; }
               case 3:{ --v;
                        colores[ j] = 13;
                        //system("aplay -q tests/dataPhoenix/phoenix_alien_tocado.wav </dev/null >/dev/null 2>&1 &");
                        break; }
               case 4:{ --v;
                        colores[ j] = 93;
                        //system("aplay -q tests/dataPhoenix/phoenix_alien_tocado.wav </dev/null >/dev/null 2>&1 &");
                        break; }
           }
           

           break;
        }case 2:{ //else if (tipoDisparo==2){  // alta frecuencia
           shoot=0;
           v=0;
           swAltaFrecuencia=0;
           break;
        }case 3:{ //else{    // antimateria
           v=0;
        }
        }
     }
  }

     //if (shoterx>=(x+2)) and (shoterx<=(x+4)) 

     return v;
}
*/

void put_explosion(int j){

  int t,x,y,s;
  //char evento[10000];
  
        x = posx[ j];
        y = posy[ j];
        t = tarda_explosion[ j];
        
        if (t==3){
           system("aplay -q tests/dataPhoenix/BombExplosion.wav </dev/null >/dev/null 2>&1 &");
        }

        if (t>4){
           Color_fore( 15);
           s = batir[ j];

           //sprintf( evento, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
           printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            y,x,evento_1[0][s],
                            y+1,x,evento_1[1][s], 
                            y+2,x,evento_1[2][s],
                            y+3,x,evento_1[3][s],
                            y+4,x,evento_1[4][s] );
           //puts(evento);
        }else if (t==4){
           Color_fore( 15);
           s = batir[ j];
           //sprintf( evento, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
           printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            y,x,evento_2[0][s],
                            y+1,x,evento_2[1][s], 
                            y+2,x,evento_2[2][s],
                            y+3,x,evento_2[3][s],
                            y+4,x,evento_2[4][s] );
           //puts(evento);
        
        }else{
           Color_fore ( (t==3)? 255: (t==2) ? 245 : (t==1) ? 239: 232 );

           if (t==3){
              //sprintf( evento, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
              printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            y-1,x,evento_3[0][0],
                            y,x,evento_3[1][0], 
                            y+1,x,evento_3[2][0],
                            y+2,x,evento_3[3][0],
                            y+3,x,evento_3[4][0],
                            y+4,x,evento_3[5][0],
                            y+5,x,evento_3[6][0]
                             );
              //puts(evento);

           }else{
              //sprintf( evento, "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
              printf( "\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                            y-1,x,evento_3[0][1],
                            y,x,evento_3[1][1], 
                            y+1,x,evento_3[2][1],
                            y+2,x,evento_3[3][1],
                            y+3,x,evento_3[4][1],
                            y+4,x,evento_3[5][1],
                            y+5,x,evento_3[6][1]
                             );
              //puts(evento);
           }

        }
       // Flush_out;

        tarda_explosion[ j] = --t;
        if( !t ){
             score+=100;
             put_score();
             
             if(resucita<hasta_donde ){
                   ++resucita;
                   if (tope<actores-1){
                       ++tope; //dtopex;
                       //retardo=Tic();
                       //bret = Tic();
                   }
                   if( resucita == limite_fondo[ indice_resucita] ){
                       ++indice_resucita;
                       kill_sound(PIDPILLS);
                       Free secure PIDPILLS;
                       Get_fn_let( PIDPILLS, put_sound(indice_resucita) );
                   }
                   if( swetapa ){
                       switch( swetapa ){
                           case 0: case 1: estado[j] = (rand()%10 >= 7) ? 1 : 2; break;
                           case 2: case 3: case 4: estado[j] = (rand()%10 >= 7) ? 2 : 1; break;
                           case 5: case 6: case 7: estado[j] = 1; break;
                       }
                   }else{
                       estado[j] = (rand()%10 > 8 ) ? 1 : 2;
                   }

                   tarda_explosion[ j] = 6;
                   switch ( swGeometricFly ){
                       case 0:{
                           posx[ j] = rand()%10>5 ? 87 : 2; //70;
                           posy[ j] = rand()%15;
                           break;
                       }
                       case 1:{
                           posx[ j] = rand()%87; //70;
                           posy[ j] = rand()%15;
                           break;
                       }
                   }
                   colores[ j] = 70; // verde
                   // que aparezca como regenerado 
                   //put_regenerator(x,y,batir[i]);
                   put_regenerator(posx[ j], posy[ j], batir[j]);
             }else{ sw_conteo_final = 1; }
        }
}

int put_bomba( int j, int etapa ){

  int x,y;

  x = shotx[ j];   // estas 2 lineas hacen lo mismo que las lineas
  y = shoty[ j];   // comentadas arriba.

     if (y==etapa ){
        //At y, x;
        printf("\x1b[%d;%dH ",y,x);
        bomba[ j] = 0;
     }else{
        //At y, x;
        printf( "\x1b[%d;%dH ",y,x );
        ++y;
        //At  y, x;
        printf("\x1b[%d;%dH%s", y,x,tipoBomba ); //"O"   
        shoty[ j] = y;
     }
     //Flush_out;
     return ((x>=(py+1) && x<=(py+9)) && ( y>=px)) ? 1 : 0;

}

void put_regenerator(int x, int y, int r){
   
   Color_fore(39);

   printf("\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                         y,x,evento_1[0][r],
                         y+1,x,evento_1[1][r],
                         y+2,x,evento_1[2][r],
                         y+3,x,evento_1[3][r]);

   //Flush_out;
}


void put_actor(int x, int y, int r, int c){
   
   //char actor[2048];
   Color_fore(c);
   //sprintf(actor,"\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
   printf("\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                         y,x,enemy[0][r],
                         y+1,x,enemy[1][r],
                         y+2,x,enemy[2][r],
                         y+3,x,enemy[3][r],
                         y+4,x,enemy[4][r]);
   //puts(actor);
   //Flush_out;
}

void clear_actor(int x, int y){
   //char actor[1024];
   //sprintf(actor,"\x1b[%d;%dH           \x1b[%d;%dH           \x1b[%d;%dH           \x1b[%d;%dH           ",
   printf("\x1b[%d;%dH           \x1b[%d;%dH           \x1b[%d;%dH           \x1b[%d;%dH           \x1b[%d;%dH           ",
          y,x, y+1,x,y+2,x,y+3,x,y+4,x);
   //puts(actor);
   //Flush_out;

}

void obtiene_valores(){
  dx = dirx[ i];    // save direction X of phoenix
  dy = diry[ i];    // save direction Y of phoenix
  x = posx[ i];     // save actual position
  y = posy[ i];     // "
  r = batir[ i];    // position of wind
  e = estado[ i];   // state: 0=dead; 1-4=touch
  b = bomba[ i];    // bomb of phoenix
  sx = shotx[ i];   // position of bomb
  sy = shoty[ i];   // "
  sc = colores[ i]; // colour of phoenix: normal=green(70)
}

void define_todo(int etapa, int subetapa){
  

  actores=20; //14; //más que esto, y se laguea...

  if (etapa==2){ 
       actores=67;
  }
    
  acabo_con_todos=0;

  int i=0;
  do{
      dirx[ i]=0;
      diry[ i]=0;
      posx[ i]=0;
      posy[ i]=0;
      batir[ i]=0;
      estado[ i]=0;
      bomba[ i]=0;
      shotx[ i]=0;
      shoty[ i]=0;
      colores[ i]=0;
  }while( ++i<actores );
  
  i=0;
  while (i<actores){

      if (etapa==1){ 
         //switch(swGeometricFly){
         //   case 0:{
               dirx[i] = ( rand()%10 < 5 ) ? 2: -2;
               diry[i] = ( rand()%10 < 5 ) ? 1: -1;
         /*      break;
            }
            case 1:{
               dirx[i] = ( rand()%10 < 5 ) ? 1: -1;
               diry[i] = ( rand()%10 < 5 ) ? 1: -1;
               break;
            }
         }*/
      }
      if (etapa==1){
         x = rand()%87; //(mth.int (mth.rand 60))
         y = rand()%20; //(mth.int (mth.rand 20))
         y = y<4 ? 4 : y;
      }else{
         x=17+i;
         y=12;  // == avance+7
      }
      
      
      if (etapa==1 ){
         batir[i] = rand()%3;
         if( subetapa ){
             switch(subetapa){
                 case 0: case 1: estado[i] = (rand()%10 >= 7) ? 1 : 2; break;
                 case 2: case 3: case 4: estado[i] = (rand()%10 >= 7) ? 2 : 1; break;
                 case 5: case 6: case 7: estado[i] = 1; break;
             }
         }else{
             estado[i] = (rand()%10 > 8) ? 1 : 2;
         }
/*         if (subetapa==5){
            estado[i] = 1;
         }else if (subetapa==4){
            estado[i] = 2;
         }else if (subetapa==3){
            estado[i] = (rand()%10 >= 7) ? 3 : 2;
         }else if (subetapa==2){
            estado[i] = (rand()%10 >= 2) ? 3 : 2;
         }else {//if (subetapa==1){
            estado[i] = 3; //(rand()%10 >= 7) ? 4 : 2;
         }
*/
         colores[i] = 70;
         tarda_explosion[i] = 6;
      }
      
      posx[i] = x;
      posy[i] = y;
      shotx[i]=0;
      shoty[i]=0;
      bomba[i]=0;
     /// bshot[i]=0;

      ++i;
  }
}

char * put_sound( int typeSound )
{
   String PID_SOUND;
   system( string_fondo[ typeSound ] );
   char ot = Set_new_sep(' ');

   PID_SOUND = `pidof ffplay`;
   
   Fn_let( PID_SOUND, Get_token(PID_SOUND, 1));
   Set_token_sep(ot);
   return PID_SOUND;
}

void kill_sound( char * PID_SOUND )
{
   char strkill[256];
   sprintf( strkill, "kill -9 %s </dev/null >/dev/null 2>&1 &", PID_SOUND);
   system(strkill);
}

void kill_all_sounds()
{
   String PID;
   Fn_let ( PID, Get_sys("pidof ffplay" ));
   if (strlen(PID)>0){
      char cpids[256];
      sprintf(cpids,"kill -9 %s </dev/null >/dev/null 2>&1",PID);
      system(cpids);
   }
   Free secure PID;
}
