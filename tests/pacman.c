
/*
     ██████▄▄     ▟▙         ▄▟██▄▄    █▙        ▟█       ▟▙       █▙     ███
     █████████▄  ▟██▙     ▟█████████▄  ██▙      ▟██      ▟██▙      ██▙    ███
     █████████▀ ▟████▙   ▄█████▀▀▀     ███▙    ▟███     ▟████▙     ███▙   ███
     ██████▀▀  ▟██████▙  ▀█████▄▄▄     ████▙  ▟████    ▟██████▙    ████▙  ███
     ███      ▟███ ▄███▙  ▀█████████▀  █████▙▟███ █   ▟███ ▄███▙   █████▙▄█ █
     ███     ▟██████████▙    ▀▀██▀▀    ███████▄▄▄▄█  ▟██████████▙  ████████▄█


     Created by Mr. Dalien.
     
     Compile:
     
     ./ccpre.sh tests/Pacman/pacman -static 
     
     This program MUST BE EXECUTED WHIT:
     
     rxvt -g 75x103 -insecure -fn "xft:FantasqueSansMono-Regular:pixelsize=5" -e ./tests/pacman
     
     test:
     
     rxvt -hold -g 75x103 -fn "xft:FantasqueSansMono-Regular:pixelsize=5" -e valgrind ./tests/pacman
     
     o
     
     rxvt -hold -g 75x103 -fn "xft:FantasqueSansMono-Regular:pixelsize=5" -e valgrind --show-leak-kinds=all ./tests/pacman


     Enjoy!
     
     Con amor
     Mr. Dalien
*/

#include <gadget/gadget.h>
#include "tests/pacman.h"

LIB_GADGET_START

 
Main

 int sw_play_acts=0, sw_continue_play=0, init_level=-1;
 if ( Arg_count >= 2 ){
     int i=0;
     while( ++i<Arg_count ){
         Get_arg_str( opt_play, i );
         if ( Is_equal_str(opt_play,"-a") ){  // pacman -a
            sw_play_acts=1;
            break;
         }
         if( Is_equal_str(opt_play, "-c") ){  // pacman -c : continuar el juego
            sw_continue_play=1;
         }
         if(  Is_equal_str(opt_play,"-l") ){ // pacman -l <1-5> : elegir el nivel para iniciar
            Get_arg_int( nlevel, ++i );
            if ( Is_between( nlevel, 1, 5 ) ){
                switch( nlevel ){
                    case 1: init_level = -1; break;
                    case 2: init_level = 1; break;
                    case 3: init_level = 4; break;
                    case 4: init_level = 7; break;
                    case 5: init_level = 10; break;
                    default: init_level = -1; break;
                }
            }
         }
         if( Is_equal_str(opt_play,"-mr") ){  // sonidos Mr. pacman
            sw_sound_p=1;
         }
         if( Is_equal_str(opt_play,"-mrs") ){  // sonidos Mrs. pacman
            sw_sound_p=0;
         }
         Free secure opt_play;
     }
 } 

 DEC_PREC=0;
    
 int vidas = 3;
 int x=0, y=0, tx=0, ty=0;  // 77, 36
 int score = 0;
 int level = init_level;
 int last_level_rand=0;
 int level_fruit=-1;
 int sw_dead=0;
 int sw_random=0;
 int cnt_status_pills=0;
 unsigned long PLUS=0L;  // cuando acabe con una partida, al volver, el juego aumenará su velocidad
 ///int extra_life=0;
 int sw_plus_prob=0;
 int sw_extra_life_active=2;
 int sw_inicio=1; /* para que ponga la musica de entrada */
 int status_pills[4] = {1,1,1,1};
 int color_level[14] = {LAB_LEVEL1,LAB_LEVEL1,
                        LAB_LEVEL2,LAB_LEVEL2,LAB_LEVEL2,
                        LAB_LEVEL3,LAB_LEVEL3,LAB_LEVEL3,
                        LAB_LEVEL4,LAB_LEVEL4,LAB_LEVEL4,
                        LAB_LEVEL5,LAB_LEVEL5,LAB_LEVEL5}; // agregar más colores.
 int flash_level[14] = {LAB_FLASH1,LAB_FLASH1,
                        LAB_FLASH2,LAB_FLASH2,LAB_FLASH2,
                        LAB_FLASH3,LAB_FLASH3,LAB_FLASH3,
                        LAB_FLASH4,LAB_FLASH4,LAB_FLASH4,
                        LAB_FLASH5,LAB_FLASH5,LAB_FLASH5}; 
 int level_file[14] =  {0, 0, 1, 1, 1, 2,  2,  2,  3,  3,  3,  4, 4, 4};
 int pillx[4]={0,0,0,0};  // ubicación de pills.
 int pilly[4]={0,0,0,0};
 int ghostx[4]={0,0,0,0};
 int ghosty[4]={0,0,0,0};
    
 Hide_cursor;
    
 Enable_raw_mode();

 //play_Act(4);
 //Show_cursor;
 //Stop(1);
 
 Seed_by_Time(); // nueva semilla para el generador rand

 Assert( !sw_play_acts, show_acts );

 initial_screen();
 

 int high;
 high = load_high_score();
 
 
 
 String lab;

 while ( vidas > 0 ){
    
    Color_back(BACKGROUND);
    Cls;
    /* area de carga de laberintos y pantalla */
    if ( !sw_dead ){
        ++level;
        if( !sw_random ){
            if( level == 14 ) {
                while ( (level = rand()%14) == last_level_rand ); 
                last_level_rand = level;
                init_level=-10;
                sw_random=1;
            }
        }else{
            while ( (level = rand()%14) == last_level_rand ); 
            last_level_rand = level;
        }
        
        /* intermission */
        
        if( level == 2 ) {if( init_level == -1 ){ play_Act(1); } /*++PLUS;*/}
        else if(level == 5 ) {if( init_level == -1 ){play_Act(2);} /*++PLUS*/;}
        else if(level == 8 ) {if( init_level == -1 ){play_Act(3);} /*++PLUS;*/}
        else if(level == 11 ) {if( init_level == -1 ){play_Act(4);} /*++PLUS;*/}
        ++PLUS;
        PLUS=Clamp(PLUS,0,8);
        
        ++level_fruit;
        if( level_fruit == 8 ) level_fruit=7; 
        
           /* primero */ 
        
        New array tdots,tpdots as int; //
    
        lab = Load_string(laberinth_files[level_file[level]]);
        
        F_STAT dotsLab = Stat_file(laberinth_dots[level_file[level]]);
        if ( !dotsLab.is_matrix ){
            Msg_red("archivo de puntos no es matriciable");
            Free secure lab;
            Show_cursor;
            Stop(1);
        }
        /* preparo el laberinto para imprimirlo sin deshabilitar modo raw */
        Fn_let(lab, prepare_lab_string( lab, high /*, color_level[level]*/ ));
        
        Range for tdots [ 0:1:dotsLab.total_lines-1, 0:1:dotsLab.max_tokens_per_line-1 ];
        tdots = Load_matrix( pSDS(tdots), laberinth_dots[level_file[level]], dotsLab);
        
        /* traspasamos a array estático por rendimiento? */
        int j,k;
        Iterator up j [0:1:Rows(tdots)]{
            Iterator up k[0:1:Cols(tdots)]{
                dots[j][k] = $tdots[j,k];
            }
        }
        Free array tdots;
        
        /* obtener la posicion de los power pills */
        get_loc_power_pills( /*pSDS(dots),*/ pillx, pilly, &tx, &ty );
        
        Range for tpdots [ 0:1:dotsLab.total_lines-1, 0:1:dotsLab.max_tokens_per_line-1 ];
        tpdots = Load_matrix( pSDS(tpdots), laberinth_ghost_dots[level_file[level]], dotsLab);
        
        /* traspasamos a array estático por rendimiento? */
        Iterator up j [0:1:Rows(tpdots)]{
            Iterator up k[0:1:Cols(tpdots)]{
                pdots[j][k] = $tpdots[j,k];
            }
        }
        Free array tpdots;
        
        /* obtener la posiciond e los fantasmas 40,41,42,43*/
        get_loc_ghost_pos( /*pSDS(pdots),*/ ghostx, ghosty );

        /* regenera el stado de los power pills */
        status_pills[0]=1;status_pills[1]=1;status_pills[2]=1;status_pills[3]=1;
    }
   /* ubicación de pacman */ 
    x=tx, y=ty;
   
   /* aumento de probabilidad de detección de pacman solo se hará una vez dentro
      de un nivel */ 
    sw_plus_prob = sw_dead ? 0 : 1;
    cnt_status_pills= !sw_dead ? 3 : cnt_status_pills;  // verifica si pill está activo en tiempo de ejecucion.
    
    sw_dead=0; // resetea vida

   /* cuando haga la funcion multidimensional, estas declaraciones
      deberán estar afuera de este ciclo. Se dejarán solo las asignaciones
      que deberán sustraerse de una estructura de datos */
   /* data del pacman*/ 
    int c=0, dir=0, tdir=0, olddir=0, boca=0;
    int color_pacman=COLOR_PACMAN, index_shadow=0;
    
   /* waka-waka */
    int sw_waka=0;
    int cnt_void_waka=0; // numero de wakas que no se hacen (que no come)
    String PIDWAKA, PIDPILLS, PIDEATGHOST, PIDSIREN;
   
   /* datos del laberinto */ 
    int sw_escape=0;  /* si preisona ESC, no pregunta si quiere continuar el juego */
    int sw_predice=0; /* si presiona una tecla antes de una esquina o cruce */
    int sw_tunnel=0;  /* si entra al tunel, debe disminuir la velocidad */
    int sw_level_clear=0;  // indica si se ha superado el nivel.
    
   /* obtener el total de puntos del laberinto */
    //All range for dots;
    int total_dots = get_total_dots();// SDS(dots) );
    int cnt_dots = 0;  // cuenta el número de puntos que deben ser comidos.


   /* fruta */
    int sw_fruit=0;
    int sw_appear_fruit=1; // !sw_dead ? 1 : 0;
    
    unsigned long tfruit=0L, tdisp_fruit=0L;
    unsigned long tpost_eat_fruit=0L;

   /* datos de pastillas titilantes */
    
    unsigned long tpills=0L; //[4]={0.0,0.0,0.0,0.0};
    int sw_power_pills=1; // controla movimiento de power pills
    
    int sw_pill_active=0; // indica si está activo el power para comer fantasmas
    int punctuation[]={400,800,1200,1600}; // puntos por cada phantom comido
    int cnt_eat=0;
    unsigned long teating=0L, teating2=0L;
    int ScaryColor=21, sw_time_scary=0, sw_titile=1, sw_eat_first=0;
    unsigned long tscary=0L;
   
   /* datos de los phantoms */
    unsigned long t=0L, time_limit=VEL_PACMAN-PLUS;
    unsigned long tp[4]={0L,0L,0L,0L};
    unsigned long time_limitp[4]={VEL_RED-PLUS,VEL_PINK-PLUS,VEL_BLUE-PLUS,VEL_YELLOW-PLUS};
    unsigned long old_time_limitp[]={0L,0L,0L,0L};
    int sw_tunnelp[] = {0,0,0,0};
    int sw_eating_mode[]={0,0,0,0};
    
    pdir[0]=DIR_DOWN; pdir[1]=DIR_LEFT; pdir[2]=DIR_RIGHT; pdir[3]=DIR_UP;
    pdiri[0]=DIR_DOWN; pdiri[1]=DIR_LEFT; pdiri[2]=DIR_RIGHT; pdiri[3]=DIR_UP;
    int pprob[]={8,7,5,4};  // probabilidad de que tomará la dirección del pacman
    
    unsigned long timer_dots=0L;

    //int pix[]={45,45,55,55}; // posicion inicial phantoms pix[0] = ghostx[0];
    //int piy[]={31,41,31,41};
    int pix[4]={ghostx[0],ghostx[1],ghostx[2],ghostx[3]};
    int piy[4]={ghosty[0],ghosty[1],ghosty[2],ghosty[3]};
    int px[4]={pix[0],pix[1],pix[2],pix[3]};  // posicion relativa, varia en el juego.
    int py[4]={piy[0],piy[1],piy[2],piy[3]};
    //int pColor[]={196,93,45,172};
    int pColor[]={196,201,45,172};

    //unsigned long timer_dots=0L;
    
    //Color_back(0); Color_fore( color_level[level] );//119);
    //At 1,1; 
    Color(color_level[level],BACKGROUND); Print "%s",lab; Flush_out;
    
    Reset_color;

    pone_score(score, &sw_extra_life_active, &vidas, level_fruit);

    pone_ready(vidas, sw_inicio, level_fruit, /*pacman, phantoms,*/ px, py, x, y);
    //print_dots( COLOR_DOTS,BACKGROUND );//, status_pills, sw_power_pills );
    //print_tunnel();

    sw_inicio = 0;
   /*
    ▄  ▄  ▄   ▄   ▄                             
   ▀▄ █  █ █ █▄▀ █▀                             
   ▀   ▀  ▀  ▀ ▀  ▀
   */
    
    //Enable_raw_mode();
    
    Fn_let( PIDSIREN, put_sound(SND_SIREN)); //pone_siren());
        
    int i=0;
    int sw_phantom_trace=1;
    int sw_pre_eat_fruit=1;
    unsigned long t_point_fruit=0L;
    Flush_inp;

    t=Tic();    // timer para PAcman

    tp[0] = Tic();tp[1]=Tic();tp[2]=Tic();tp[3]=Tic();  // timer for phantoms
    tpills=Tic();
    timer_dots=Tic(); 

    while(c!=ESCAPE ) 
    {
        /* analiza si está en modo comer */
        if( sw_pill_active ){
            if( sw_eat_first ){
            
                if( Timer( &teating, 5000L-(level_fruit*300) ) ){
                    sw_time_scary=1;
                    tscary=0L; tscary = Tic();
                    teating2=0L; teating2=Tic();
                    sw_eat_first=0;
                }
            }else{
                if( Timer( &teating2, 4000L-(level_fruit*300) ) ){
                    sw_eating_mode[0]=0;sw_eating_mode[1]=0;sw_eating_mode[2]=0;sw_eating_mode[3]=0;
                    sw_pill_active=0;
                    teating2=0L; teating=0L; sw_time_scary=0; sw_titile=1;ScaryColor=21;
                    if( PIDPILLS ){
                        //kill_pills(PIDPILLS);
                        kill_sound( PIDPILLS );
                        Free secure PIDPILLS;
                    }
                    
                    //At 61, 62; Put_leds(1000,0,0);
                    Fn_let( PIDSIREN, put_sound(SND_SIREN)); //pone_siren());
                }
            }
            if( sw_time_scary ){
                if( Timer( &tscary, 120L )){
                    if ( sw_titile ) {
                        ScaryColor=21; sw_titile=0;
                    }else{
                        ScaryColor=255;sw_titile=1;
                    }
                }
            }
        }
        /* analiza posicion de phantoms */
        // Iterator up i [0: 1: 4]{
        if(sw_phantom_trace){
             if ( Timer( &tp[i], time_limitp[i] )){
             
                 At px[i],py[i]; draw_ascii_phantoms(BACKGROUND,BACKGROUND,i);

                // if( $dots[px[i]+1, py[i]+1] == 1 || $dots[px[i]+1, py[i]+1] == 2  ){
                     switch(pdir[i]){
                         case DIR_LEFT:{ --py[i]; break; }
                         case DIR_DOWN:{ ++px[i]; break; }
                         case DIR_UP:  { --px[i]; break; }
                         case DIR_RIGHT:{ ++py[i]; break; }
                     }
                     
                // }
                 if ( ghost_direction_is( DIR_LEFT ) ) {
                     if ( pdots[px[i]+1][py[i]+1] == TUNNEL_R ){ // busco salida en la misma linea
                         int k;
                         for( k=py[i]+1; k>0; k--){
                             if( pdots[px[i]+1][k] == TUNNEL_L ){
                                 py[i] = k; break;
                             }
                         }
                     }else{
                         py[i] = analize_for_left_direction( x,y,px[i], py[i], pprob[i], i );
                     }

                 }else if ( ghost_direction_is( DIR_DOWN ) ) { 
                     px[i] = analize_for_down_direction( x,y,px[i], py[i], pprob[i], i );

                 }else if ( ghost_direction_is( DIR_UP ) ) {
                     px[i] = analize_for_up_direction( x,y,px[i], py[i], pprob[i], i );

                 }else if ( pdir[i] == DIR_RIGHT ){
                     if ( pdots[px[i]+1][py[i]+1] == TUNNEL_L ){ // busco salida en la misma linea
                         int k;
                         for( k=py[i]+1; k<76; k++){
                             if( pdots[px[i]+1][k] == TUNNEL_R ){
                                 py[i] = k; break;
                             }
                         }
                     }else{
                         py[i] = analize_for_right_direction( x,y,px[i], py[i], pprob[i], i );
                     }
                     
                 }
                 /* verifica si entró al tunel */
                 if (pdots[px[i]+1][py[i]+1] == 20) {
                     if (!sw_tunnelp[i]){
                         old_time_limitp[i] = time_limitp[i];
                         time_limitp[i] = 85.0; sw_tunnelp[i]=1;
                         tp[i]=0;
                         tp[i]=Tic();
                         if ( pdir[i] == DIR_LEFT )  {--py[i];}
                         else  {++py[i];}
                     }else{
                         time_limitp[i] = old_time_limitp[i]; sw_tunnelp[i]=0;
                         tp[i]=0;
                         tp[i]=Tic();
                         if ( pdir[i] == DIR_LEFT )  { --py[i];}
                         else { ++py[i];}
                     }
                 }else if( pdots[px[i]+1][py[i]+1] == 30 ){  // se va al otro lado
                     if ( pdir[i] == DIR_LEFT ) {py[i] = 70;}
                     else   {py[i] = 2;}
                 }
                 
                 
                 if (!sw_pill_active || !sw_eating_mode[i]){
                     At px[i],py[i]; draw_ascii_phantoms(pColor[i],BACKGROUND,i);
                     if ( Is_between( px[i], x-1, x+1) && Is_between(py[i],y-1, y+1) ){
                         sw_dead=1;
                        // break; // sale de Iterator
                     }
                 }else{ /* se lo comió? */
                     
                     if ( Is_between( px[i], x-1, x+1) && Is_between(py[i],y-1, y+1) ){
                         if (sw_waka){
                              //kill_waka(&sw_waka, PIDWAKA);
                              kill_sound( PIDWAKA );sw_waka=0;
                              Free secure PIDWAKA;
                              cnt_void_waka=0; 
                         }
                         if(PIDEATGHOST){
                              //kill_eat_ghost(PIDEATGHOST);
                              kill_sound( PIDEATGHOST );
                              Free secure PIDEATGHOST;
                         }
                         Fn_let( PIDEATGHOST, put_sound(SND_EATGHOST)); //pone_eat_phantom());

                         //At x,y; draw_ascii_pacman(255,BACKGROUND,0,0);
                         score += punctuation[cnt_eat];
                         show_point(x, y, punctuation[cnt_eat]);
                         Color(color_level[level],BACKGROUND); Print "%s",lab; Flush_out;
                         print_dots( COLOR_DOTS,BACKGROUND );

                        // sleep(1);
                         /* devuelve al fantasma a su guarida */
                         px[i] = pix[i];
                         py[i] = piy[i];
                         pdir[i] = pdiri[i];
                         if( sw_tunnelp[i] ){
                             time_limitp[i] = old_time_limitp[i]; sw_tunnelp[i]=0;
                         }
                         sw_eating_mode[i]=0;
                         pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                         ///At px[i],py[i]; draw_ascii_phantoms(pColor[i],0,i);
                         cnt_eat++;
                         if( cnt_eat==4 ) {
                             sw_pill_active=0;
                             sw_time_scary=0;
                             ScaryColor=21;
                             if( PIDPILLS ){
                                 //kill_pills(PIDPILLS);
                                 kill_sound( PIDPILLS );
                                 Free secure PIDPILLS;
                                 //At 61, 62; Put_leds(1000,0,0);
                             }
                             Fn_let( PIDSIREN, put_sound(SND_SIREN)); //pone_siren());
                         } 
                         Free secure PIDEATGHOST;
                     }
                     At px[i],py[i]; draw_ascii_phantoms(ScaryColor,BACKGROUND,i);
                 }

             }
         } // iterator ghost
         ++i;
         if(i==4) i=0;
         
         
         /* verifica la fruta */
         if ( sw_fruit ){
             if( sw_pre_eat_fruit ){
                 if ( Timer( &tdisp_fruit, 30L ) ){
                     pone_fruit(level_fruit);
                 }

                 if ( Timer( &tfruit, 10000L ) ){
                     sw_fruit=0;
                     quita_fruit();
                     tfruit=0L;tdisp_fruit=0L;
                     dots[62][37] = 1; // vuelve a la normalidad.
                 }
             }else{  // show message loco!!
                 
                 if( Timer( &t_point_fruit, 30L ) ){
                     At 62, 34;Put_leds(point_fruit[level_fruit],46,BACKGROUND);
                 }
                 if ( Timer( &tpost_eat_fruit, 2000L )) {
                     sw_pre_eat_fruit=1;
                     sw_fruit=0;
                     At 62, 34;Put_leds(point_fruit[level_fruit],BACKGROUND,BACKGROUND);
                 }
             }
         }

        /* verifica si murió el pacman */ 
         if( sw_dead ){
            /* if (sw_waka){
                  kill_waka(&sw_waka, PIDWAKA);
                  Free secure PIDWAKA;
                  cnt_void_waka=0;
             }
             if( PIDPILLS ){
                  kill_pills(PIDPILLS);
                  Free secure PIDPILLS;
             }
             if(PIDEATGHOST){
                  kill_eat_ghost(PIDEATGHOST);
                  Free secure PIDEATGHOST;
             }*/
             kill_all_sounds();
             Free secure PIDEATGHOST, PIDWAKA, PIDPILLS,PIDSIREN;
             cnt_void_waka=0;
             sw_waka=0;
             sw_fruit=0;
             dots[62][37] = 1; // vuelve a la normalidad.
             sleep(1);
             --vidas;
             
             //Disable_raw_mode();
             //Color_back(0); Color_fore( color_level[level]  );//119);
             //At 1,1; 
             Color(color_level[level],BACKGROUND); Print "%s",lab; Flush_out;
             refresh_score(score);
             //Enable_raw_mode();
             
             Reset_color;

             print_dots( COLOR_DOTS,BACKGROUND);//, status_pills,sw_power_pills );
             //print_tunnel();
             death_pacman(x,y,pacman);
             break;
         }
         
        /* analiza posicion de pacman*/
         if( Timer( &t, time_limit ) ){
             At x,y; draw_ascii_pacman(BACKGROUND,BACKGROUND,dir,boca);
             
           //  At x+5,y+20; draw_ascii(pacman,2,0,0,dir);          

             if (sw_predice ){
                 if ( tdir == DIR_LEFT ){
                     --y;
                     if ( dots[x+1][y+1]!=1 ) ++y;
                     else { dir = tdir; /*++y;*/olddir=0; sw_predice=0; }
                 }else if( tdir == DIR_DOWN ){
                     ++x;
                     if ( dots[x+1][y+1]!=1 ) --x;
                     else { dir = tdir; /*--x;*/olddir=0; sw_predice=0; }

                 }else if( tdir == DIR_UP ){
                     --x;
                     if ( dots[x+1][y+1]!=1 ) ++x;
                     else { dir = tdir; /*++x;*/olddir=0; sw_predice=0; }

                 }else if( tdir == DIR_RIGHT ){
                     ++y;
                     if ( dots[x+1][y+1]!=1 ) --y;
                     else { dir = tdir; /*--y;*/olddir=0; sw_predice=0; }

                 }
             }
             
             if ( Kbhit() ){

                 c = Getch();
//             At x,y; draw_ascii(pacman,2,0,0,boca);
//             At x+5,y+10; draw_ascii(pacman,2,0,0,boca);
                 olddir= dir;
                 
                 if(c == ARROW_LEFT || c == 'j' ) { dir=DIR_LEFT; tdir=DIR_LEFT;}
                 else if(c == ARROW_RIGHT || c == 'l' ) {dir=DIR_RIGHT;tdir=DIR_RIGHT;}
                 else if(c == ARROW_UP  || c == 'i' )   {dir=DIR_UP; tdir=DIR_UP;}
                 else if(c == ARROW_DOWN  || c == 'k' ) { dir=DIR_DOWN; tdir=DIR_DOWN;}
/*                 else if(c == 'p' )  { kill_all_sounds();
                                       Free secure PIDEATGHOST, PIDPILLS, PIDPILLS,PIDSIREN;
                                         cnt_void_waka=0;
                                         sw_waka=0;
                                       Pause();
                                       Fn_let( PIDSIREN, put_sound(SND_SIREN));
                                      } */
                 else if(c == ESCAPE ) { vidas=0;
                                         /*if(sw_waka){
                                             kill_waka(&sw_waka, PIDWAKA); 
                                             Free secure PIDWAKA;
                                             cnt_void_waka=0;
                                         }
                                         if( PIDPILLS ){
                                             kill_pills(PIDPILLS);
                                             Free secure PIDPILLS;
                                         }
                                         if(PIDEATGHOST){
                                              kill_eat_ghost(PIDEATGHOST);
                                             Free secure PIDEATGHOST;
                                         }*/
                                         kill_all_sounds();
                                         Free secure PIDEATGHOST, PIDWAKA, PIDPILLS,PIDSIREN;
                                         cnt_void_waka=0;
                                         sw_waka=0;
                                         sw_escape=1;
                                         continue; }

//             At x,y; draw_ascii(pacman,2,121,0,boca);
//             At x+5,y+20; draw_ascii(pacman,2,119,0,boca);
             }
             
             
             /* hay un desfase con el array de puntos, porque comienza en 0, y las
                coordenadas del mono comienzan en 1 */
             
             
             if(dir==DIR_LEFT) {   //{ y-= y>3 ? 1 : 0; if( y==3 ) dir=tdir=0; }
                 --y;
                 int location = dots[x+1][y+1];
                 if( location == TUNNEL_R ) {
                      do{
                         --y;
                      }while( dots[x+1][y] != TUNNEL_L) ;
                      --y;
                      index_shadow=1;
                 }
                 else if ( location>2 && location!=20 && location!=30
                                       && location!=100 ) {
                      if( location==3 && (olddir==DIR_UP || olddir==DIR_DOWN) ){
                           ++y; dir=olddir; sw_predice=1;
                      }else{
                           ++y; dir=tdir=0; 
                           if( sw_waka ){
                              //kill_waka(&sw_waka,PIDWAKA);
                              kill_sound( PIDWAKA );sw_waka=0;
                              Free secure PIDWAKA;
                              cnt_void_waka=0;
                           }
                      }
                     /* }else{
                         ++y; dir=olddir; sw_predice=1;
                      }*/
                 }
                 else if ( location==0 ) {
                      ++y; dir=olddir; sw_predice=1;
                 }
                 else if ( location==2 /* || $dots[x+1,y+1]==1*/ ) {
                     score += 10;
                     ++cnt_dots;
                     dots[x+1][y+1]=1;
                     pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                     if(!sw_waka){
                         Free secure PIDWAKA;
                         Fn_let( PIDWAKA, put_sound(SND_WAKA)); //pone_waka());
                         sw_waka=1;
                     }
                     cnt_void_waka=0;
                 }else if ( location==100 ){  // fruit!!
                        score += point_fruit[level_fruit];
                        //system("aplay -q tests/dataPacman/pacman_eatfruit.wav </dev/null >/dev/null 2>&1 &");
                        system(EAT_FRUIT);
                        quita_fruit();
                        At 62, 34;Put_leds(point_fruit[level_fruit],15,BACKGROUND);
                        
                        pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                        //sw_fruit=1;
                        
                        tfruit=0L;tdisp_fruit=0L;
                        dots[x+1][y+1] = 1;
                        sw_pre_eat_fruit=0;
                        tpost_eat_fruit=Tic();
                        t_point_fruit=Tic();
                 }else{
                     if( sw_waka ){
                         cnt_void_waka++;
                         if( cnt_void_waka > 3 ) {
                             //kill_waka(&sw_waka,PIDWAKA);
                             kill_sound( PIDWAKA );sw_waka=0;
                             Free secure PIDWAKA;
                             cnt_void_waka=0;
                         }
                     }
                 }
                 /* verifica si entró al tunel */
                 if (location==20) {
                     if (!sw_tunnel) {sw_tunnel=1; color_pacman=244;index_shadow=-1;--y;}
                     else {sw_tunnel=0; color_pacman=COLOR_PACMAN; index_shadow=0; --y;}
                 }else if( location == 30 ){  // se va al otro lado
                     index_shadow=1;
                     y = 70;
                 }
                 /* verifica si ha comido todos los puntos para terminar la partida */
                 if( cnt_dots == total_dots ){
                     sw_level_clear=1;
                     break;
                 }else{
                     if (sw_appear_fruit){
                         if(cnt_dots == (int) (total_dots/3)) { // comió 1/3 de los puntos
                             sw_fruit=1;
                             tfruit=0L;
                             dots[62][37] = 100;
                             tfruit=Tic();
                             pone_fruit(level_fruit);
                             tdisp_fruit=0L;
                             tdisp_fruit=Tic();
                             sw_appear_fruit=0;
                             // aumenta probabiidad de los más lerdos para detectar a pacman
                             if (sw_plus_prob){
                                 pprob[2] = pprob[2]+1;
                                 pprob[3] = pprob[3]+1;
                                 sw_plus_prob=0;
                             }
                         }
                     }
                 }
             }
             else if(dir==DIR_DOWN) {//{ x += x<93 ? 1 : 0; if( x==93 ) dir=tdir=0;}
                 ++x;
                 int location = dots[x+1][y+1];
                 if ( location>2 && Is_not(location,20, 30, 50,51,52,53) ) {
                      if( location==3 && (olddir==DIR_LEFT || olddir==DIR_RIGHT) ){
                           --x; dir=olddir; sw_predice=1;
                      }else{
                           --x; dir=tdir=0; 
                           if( sw_waka ){
                                //kill_waka(&sw_waka,PIDWAKA);
                                kill_sound( PIDWAKA );sw_waka=0;
                                Free secure PIDWAKA;
                                cnt_void_waka=0;
                           }
                      }
                     /* }else{
                         --x; dir=olddir; sw_predice=1; 
                      }*/
                 }
                 else if ( location==0 ) {
                      --x; dir=olddir; sw_predice=1; 
                 }
                 else if ( location==2/* || $dots[x+1,y+1]==1 */) {
                     score += 10;
                     ++cnt_dots;
                     dots[x+1][y+1]=1;
                     pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                     if(!sw_waka){
                         Free secure PIDWAKA;
                         Fn_let( PIDWAKA, put_sound(SND_WAKA)); //pone_waka());
                         sw_waka=1;
                     }
                     cnt_void_waka=0;
                 }else if ( location>=50 && location<=53 ) { // power pills!
                     if(sw_waka){
                         //kill_waka(&sw_waka,PIDWAKA);
                         kill_sound( PIDWAKA );sw_waka=0;
                         Free secure PIDWAKA;
                         cnt_void_waka=0;
                     }
                     if (PIDPILLS){
                         //kill_pills(PIDPILLS);
                         kill_sound( PIDPILLS );
                         Free secure PIDPILLS;
                     }
                     if( PIDSIREN){
                         //kill_siren( PIDSIREN );
                         kill_sound( PIDSIREN );
                         Free secure PIDSIREN;
                     }
                     Color( flash_level[level], BACKGROUND); Print "%s",lab;
                     print_dots( 255,BACKGROUND);
                     Flush_out;
                     Fn_let( PIDPILLS, put_sound(SND_PILLS)); //pone_pills());
                     usleep(20000);
                     Color( color_level[level], BACKGROUND); Print "%s",lab;
                     Flush_out;

                     status_pills[ location-50 ]=0;
                     --cnt_status_pills;
                     dots[x+1][y+1]=1;
                     score += 50;
                     sw_time_scary=0;
                     ++cnt_dots;
                     pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                     sw_eating_mode[0]=1;sw_eating_mode[1]=1;sw_eating_mode[2]=1;sw_eating_mode[3]=1;
                     cnt_eat=0;
                     sw_pill_active=1; /* activa power: fantasmas puedens er comidos */
                     sw_eat_first=1;
                     ScaryColor=21;
                     teating=0L;
                     teating=Tic(); // pone timer para duracion de estado vulnerable de phantoms
                 }else{
                     if( sw_waka ){
                         cnt_void_waka++;
                         if( cnt_void_waka > 3 ) {
                             //kill_waka(&sw_waka,PIDWAKA);
                             kill_sound( PIDWAKA );sw_waka=0;
                             Free secure PIDWAKA;
                             cnt_void_waka=0;
                         }
                     }
                 }
                 
                 /* verifica si ha comido todos los puntos para terminar la partida */
                 
                 if( cnt_dots == total_dots ){
                     sw_level_clear=1;
                     break;
                 }else{
                     if (sw_appear_fruit){
                         if(cnt_dots == (int) (total_dots/3)) { // comió 1/3 de los puntos
                             sw_fruit=1;
                             tfruit=0L;
                             dots[62][37] = 100;
                             tfruit=Tic();
                             pone_fruit(level_fruit);
                             tdisp_fruit=0L;
                             tdisp_fruit=Tic();
                             sw_appear_fruit=0;
                            // aumenta probabiidad de los más lerdos para detectar a pacman
                             if (sw_plus_prob){
                                 pprob[2] = pprob[2]+1;
                                 pprob[3] = pprob[3]+1;
                                 sw_plus_prob=0;
                             }
                         }
                     }
                 }

             }
             else if(dir==DIR_UP) {//{ x -= x>3 ? 1 : 0; if( x==3 ) dir=tdir=0;}
                 --x;
                 int location = dots[x+1][y+1];
                 if ( location>2 && Is_not(location,20, 30, 50,51,52,53 ) ) {
                      if( location==3 && (olddir==DIR_LEFT || olddir==DIR_RIGHT) ){
                           ++x; dir=olddir; sw_predice=1;
                      }else{
                           ++x; dir=tdir=0; 
                           if( sw_waka ){
                               //kill_waka(&sw_waka,PIDWAKA);
                               kill_sound( PIDWAKA );sw_waka=0;
                               Free secure PIDWAKA;
                               cnt_void_waka=0;
                           }
                      }
                     /* }else{
                         ++x; dir=olddir; sw_predice=1; 
                      }*/
                 }
                 else if ( location==0 ) {
                      ++x; dir=olddir; sw_predice=1; 
                 }
                 else if (location==2 /*|| $dots[x+1,y+1]==1*/ ) {
                     score += 10;
                     ++cnt_dots;
                     dots[x+1][y+1]=1;
                     pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                     if(!sw_waka){
                         Free secure PIDWAKA;
                         Fn_let( PIDWAKA, put_sound(SND_WAKA)); //pone_waka());
                         sw_waka=1;
                     }
                     cnt_void_waka=0;

                 }else if ( location>=50 && location<=53 ) { // power pills!
                     if(sw_waka){
                         //kill_waka(&sw_waka,PIDWAKA);
                         kill_sound( PIDWAKA );sw_waka=0;
                         Free secure PIDWAKA;
                         cnt_void_waka=0;
                     }
                     if (PIDPILLS){
                         //kill_pills(PIDPILLS);
                         kill_sound( PIDPILLS );
                         Free secure PIDPILLS;
                     }
                     if( PIDSIREN){
                         //kill_siren( PIDSIREN );
                         kill_sound( PIDSIREN );
                         Free secure PIDSIREN;
                     }
                     Color( flash_level[level], BACKGROUND); Print "%s",lab;
                     print_dots( 255,BACKGROUND);
                     Flush_out;
                     Fn_let( PIDPILLS, put_sound(SND_PILLS)); //pone_pills());
                     usleep(20000);
                     Color( color_level[level], BACKGROUND); Print "%s",lab;
                     Flush_out;
                     
                     status_pills[ dots[x+1][y+1]-50 ]=0;
                     --cnt_status_pills;
                     dots[x+1][y+1]=1;
                     score += 50;
                     sw_time_scary=0;
                     ++cnt_dots;
                     pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                     sw_eating_mode[0]=1;sw_eating_mode[1]=1;sw_eating_mode[2]=1;sw_eating_mode[3]=1;
                     cnt_eat=0;
                     sw_pill_active=1; /* activa power: fantasmas puedens er comidos */
                     sw_eat_first=1;
                     ScaryColor=21;
                     teating=0;
                     teating =Tic();
                 }else{
                     if( sw_waka ){
                         cnt_void_waka++;
                         if( cnt_void_waka > 3 ) {
                             //kill_waka(&sw_waka,PIDWAKA);
                             kill_sound( PIDWAKA );sw_waka=0;
                             Free secure PIDWAKA;
                             cnt_void_waka=0;
                         }
                     }

                 }
                 /* verifica si ha comido todos los puntos para terminar la partida */
                 if( cnt_dots == total_dots ){
                     sw_level_clear=1;
                     break;
                 }else{
                     if (sw_appear_fruit){
                         if(cnt_dots == (int) (total_dots/3)) { // comió 1/3 de los puntos
                             sw_fruit=1;
                             tfruit=0L;
                             dots[62][37] = 100;
                             tfruit=Tic();
                             pone_fruit(level_fruit);
                             tdisp_fruit=0L;
                             tdisp_fruit=Tic();
                             sw_appear_fruit=0;
                             // aumenta probabiidad de los más lerdos para detectar a pacman
                             if (sw_plus_prob){
                                 pprob[2] = pprob[2]+1;
                                 pprob[3] = pprob[3]+1;
                                 sw_plus_prob=0;
                             }
                         }
                     }
                 }

             }
             else if(dir==DIR_RIGHT) { //{ y += y<69 ? 1 : 0; if( y==69 ) dir=tdir=0;}
                 ++y;
                 int location = dots[x+1][y+1];
                 if( location == TUNNEL_L ) {
                      do{
                         ++y;
                      }while( dots[x+1][y] != TUNNEL_R) ;
                      ++y;
                      index_shadow=1;

                 }else if ( location>2 && location!=20 && location!=30
                                       && location!=100 ) {
                      if( location==3 && (olddir==DIR_UP || olddir==DIR_DOWN) ){
                           --y; dir=olddir; sw_predice=1;
                      }else{
                           --y; dir=tdir=0; 
                           if( sw_waka ){
                               //kill_waka(&sw_waka,PIDWAKA);
                               kill_sound( PIDWAKA );sw_waka=0;
                               Free secure PIDWAKA;
                               cnt_void_waka=0;
                           }
                      }
                      /*}else{
                         --y; dir=olddir; sw_predice=1;
                      }*/
                 }
                 else if ( location==0 ) { 
                     --y; dir=olddir; sw_predice=1; 
                /* }else if ($dots[x+1,y+1]==3 ) {
                     if( sw_waka ){
                         kill_waka(&sw_waka,PIDWAKA);
                         Free secure PIDWAKA;
                         cnt_void_waka=0;
                     }
                 }*/
                 }else if ( location==2 /*|| $dots[x+1,y+1]==1*/ ) {
                     score += 10;
                     ++cnt_dots;
                     dots[x+1][y+1]=1;
                     pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                     if(!sw_waka){
                         Free secure PIDWAKA;
                         Fn_let( PIDWAKA, put_sound(SND_WAKA)); //pone_waka());
                         sw_waka=1;
                     }
                     cnt_void_waka=0;
                 }else if ( location==100 ){  // fruit!!
                        score += point_fruit[level_fruit];
                        //system("aplay -q tests/dataPacman/pacman_eatfruit.wav </dev/null >/dev/null 2>&1 &");
                        system(EAT_FRUIT);
                        quita_fruit();
                        At 62, 34;Put_leds(point_fruit[level_fruit],15,BACKGROUND);
                        
                        pone_score(score, &sw_extra_life_active, &vidas, level_fruit);
                        //sw_fruit=0;
                        
                        tfruit=0L;tdisp_fruit=0L;
                        dots[x+1][y+1] = 1; 
                        sw_pre_eat_fruit=0;
                        tpost_eat_fruit=Tic();
                        t_point_fruit=Tic();
                 }else{
                     if( sw_waka ){
                         cnt_void_waka++;
                         if( cnt_void_waka > 3 ) {
                             //kill_waka(&sw_waka,PIDWAKA);
                             kill_sound( PIDWAKA );sw_waka=0;
                             Free secure PIDWAKA;
                             cnt_void_waka=0;
                         }
                     }
                 }
                 /* verifica si entró al tunel */
                 if (location==20) {
                     if (!sw_tunnel) {sw_tunnel=1; color_pacman=244;index_shadow=-1;++y;}
                     else {sw_tunnel=0; color_pacman=COLOR_PACMAN; index_shadow=0; ++y;}
                     /*if (!sw_tunnel){
                         time_limit = 70L; sw_tunnel=1;
                         ++y; // para que no regrese de inmediato y colapse todo!
                     }else{
                         time_limit = 40L; sw_tunnel=0;
                         ++y;
                     }
                     t=0;Tic(t);*/
                 }else if( location == 30 ){  // se va al otro lado
                     index_shadow=1;
                     y = 2;
                 }
                 /* verifica si ha comido todos los puntos para terminar la partida */
                 if( cnt_dots == total_dots ){
                     sw_level_clear=1;
                     break;
                 }else{
                     if (sw_appear_fruit){
                         if(cnt_dots == (int) (total_dots/3)) { // comió 1/3 de los puntos
                             sw_fruit=1;
                             tfruit=0L;
                             dots[62][37] = 100;
                             tfruit=Tic();
                             pone_fruit(level_fruit);
                             tdisp_fruit=0L;
                             tdisp_fruit=Tic();
                             sw_appear_fruit=0;
                             // aumenta probabiidad de los más lerdos para detectar a pacman
                             if (sw_plus_prob){
                                 pprob[2] = pprob[2]+1;
                                 pprob[3] = pprob[3]+1;
                                 sw_plus_prob=0;
                             }
                         }
                     }
                 }

             }

             //if ( (x == 2 || x == 93 || y == 2 || y == 70) && dir ) dir=tdir=0;
             Flush_inp;
             if( sw_tunnel ){
                 color_pacman += index_shadow ;
                 color_pacman = Clamp( color_pacman, 232, 244 );
             }
             At x,y; draw_ascii_pacman(color_pacman,BACKGROUND,dir,boca);
             //print_dots( SDS( dots), 226,BACKGROUND);//, status_pills, sw_power_pills );
             //print_tunnel();
            
            /* timer para poner los power pills */
            /* if ( Timer( &tpills, 120L ) ){
                 sw_power_pills = sw_power_pills ? 0 : 1;
                 print_power_pills(status_pills, sw_power_pills, pillx, pilly);
             }*/
             /* actualiza estado si abre la boca o la cierra*/
             boca = boca ? 0 : 1;
         }

         /* timer para poner los power pills */
         if( Is_non_neg(cnt_status_pills) ){
             if ( Timer( &tpills, 220L ) ){
                 sw_power_pills = sw_power_pills ? 0 : 1;
                 print_power_pills(status_pills, sw_power_pills, pillx, pilly);
             }
         }
         if  (Timer (&timer_dots, 30L)){
             print_dots( COLOR_DOTS,BACKGROUND);
         }

         /* timer para poner los power pills */
       /*  if(status_pills[cnt_status_pills]){
             if ( Timer( &tpills[cnt_status_pills], 20L ) ){
                 sw_power_pills = sw_power_pills ? 0 : 1;
                 //print_power_pills(status_pills, sw_power_pills, pillx, pilly);
                 print_power_pills( sw_power_pills, pillx[cnt_status_pills], pilly[cnt_status_pills]);
             }
             ++cnt_status_pills; if (cnt_status_pills==4) cnt_status_pills=0;
         }*/
         
         
    } /* PLAY WHILE */
    
    if ( sw_level_clear ){
             kill_all_sounds();
             Free secure PIDEATGHOST, PIDWAKA, PIDPILLS,PIDSIREN;
             At x,y; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,0,1);
             sleep(1);
             cnt_void_waka=0;
             sw_waka=0;
             sw_dead=0;
             //Disable_raw_mode();
             int i, sw_color=0 ;
             Iterator up i[0:1:5]{
                 //Color_back(0); Color_fore( sw_color ? 69 : 226 );//119);
                 //At 1,1; 
                 Color( (sw_color ? color_level[level] : COLOR_PACMAN), BACKGROUND); Print "%s",lab;
                 Flush_out;
                 usleep(550000);
                 sw_color = sw_color ? 0 : 1;
                 Reset_color;
             }
             /* borra laberinto y sus puntos, para cargar uno nuevo */
             //Free array pdots;
             Free secure lab;
    }else{
    
        Free secure PIDWAKA, PIDPILLS,PIDEATGHOST, PIDSIREN;
        //Disable_raw_mode();
    }

    if ( !vidas && sw_continue_play && !sw_escape ){
        At 52,23 ; put_big_message("Continue?",202,BACKGROUND);
        char ans[2]; // debe declarar así para usar Get_option()
        Get_option(ans, "YySsNn");

        if( Occurs( ans,"YySs") ){
            score=0;
            vidas=3;
            Free secure PIDWAKA, PIDPILLS,PIDEATGHOST, PIDSIREN;
        }
    }
 } /* MAIN WHILE */


 Disable_raw_mode();
 //Color_back(0); Color_fore( color_level[level] );
 //At 1,1; 
 Color(241,BACKGROUND); Print "%s",lab;Flush_out;
    
 Reset_color;
 game_over();

/* Exception( fail_dots_file ){
    Msg_red("Archivo de puntos no es matriciable");
 }*/
 /* aqui se libera todo, dado que siempre el jugador va a perder */
 Free secure lab;
 
 save_score( score, high );
 
 Exception( show_acts ){
    Color(BACKGROUND,BACKGROUND);
    Cls;
    //Pause();
    sleep(1);
    play_Act(1);
    sleep(2);
    play_Act(2);
    sleep(2);
    play_Act(3);
    sleep(2);
    play_Act(4);
    sleep(2);
    //Pause();
 }
 Show_cursor;
 //
End

/* funciones y procedimientos */

void show_point(int x, int y, int points/*, char *lab, int px[], int py[]*/)
{

   if( y<30 ){
       At x+1, y; Put_leds(points,46,BACKGROUND);
   }else{
       At x+1, y-6; Put_leds(points,46,BACKGROUND);
   }
   sleep(1);
   Reset_color;
}

int analize_for_left_direction( int x, int y, int px, int py, int pprob, int i )
{
     if ( ghost_found( TOP_LEFT ) ){
                         ghost_go( DIR_DOWN ); 
                         ++py;
                         
     }else if ( ghost_found( BOTT_LEFT ) ){ 
                         ghost_go( DIR_UP );
                         ++py;
     }else if ( ghost_found( EXIT_HOME ) ){ // sale de la casa
                         // añadir probabilidad para que salga
                         if ( rand()%10 <= 3 )
                             ghost_go( DIR_UP );
                         
     }else if ( ghost_found(TOP_CRUX) ) {
                         //int prob = rand()%10;
                         if ( pacman_is_down ) {
                             if ( pacman_is_to_the_left ) { 
                                 ghost_go( DIR_LEFT );
                             }else{ 
                                 ghost_go( DIR_DOWN );
                             }

                         }else if ( pacman_is_up ){
                             if( pacman_is_to_the_left ) { 
                                 ghost_go( DIR_LEFT ); 
                             }else{ 
                                 ghost_go( DIR_DOWN ); 
                             } // aplicar prob.

                         }else{
                             ghost_go( DIR_LEFT ); 
                         }

     }else if ( ghost_found( BOTT_CRUX ) ){
                         //int prob = rand()%10;
                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left ){
                                 ghost_go( DIR_LEFT );
                             }else{
                                 ghost_go( DIR_UP );
                             } // aplicar prob.
                         }else if( pacman_is_up ){
                             if( pacman_is_to_the_left ) {
                                 ghost_go( DIR_UP );
                             }else { 
                                 ghost_go( DIR_LEFT );
                             } // aplicar prob.
                         }else{  // misma fila
                             ghost_go( DIR_LEFT );  // solo sigue, porque no es natural devolverse.
                         }

     }else if ( ghost_found( LEFT_CRUX ) ){
                         if ( pacman_is_down ) {
                             ghost_go( DIR_DOWN );
                         }else  {
                             if ( rand()%10 <= pprob ) {
                                 ghost_go( DIR_UP );
                             }else{
                                 ghost_go( DIR_DOWN );
                             }
                         }
                     
     }else if ( ghost_found( CRUX ) ){

                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_DOWN );
                                 }else{
                                     ghost_go( DIR_LEFT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_DOWN );
                                 }else{
                                     ghost_go( DIR_LEFT );
                                 }
                             }else{  // está en la mismo pasillo
                                 if ( rand()%10 <= pprob ){
                                      ghost_go( DIR_DOWN );
                                 }else{
                                      ghost_go( DIR_LEFT );
                                 }
                             }
                             
                         }else if( pacman_is_up ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_UP );
                                 }else{
                                     ghost_go( DIR_LEFT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_UP );
                                 }else{
                                     ghost_go( DIR_LEFT );
                                 }
                             }else{  // está en la mismo pasillo
                                 if ( rand()%10 <= pprob ){
                                     ghost_go( DIR_UP );
                                 }else{
                                     ghost_go( DIR_LEFT );
                                 }
                             }

                         }else{   // tiene que ser igual
                             if( pacman_is_to_the_left ){ 
                                 ghost_go( DIR_LEFT );
                             }else{
                                 if ( rand()%10 <= pprob ) {
                                     ghost_go( DIR_DOWN );
                                 }else{
                                     ghost_go( DIR_UP );
                                 }
                             }
                         }
                         //++py[i];
                   /*  }else if ( ghost_found( END_WAY ) ){ // no creo que esto se vaya a ejecutar algun dia
                         // añadir probabilidad para que salga
                         if( rand()%10 <= pprob[i] ) {
                             if ( pacman_is_down || x == px[i] ) {
                                 ghost_go( DIR_DOWN );
                             }else {
                                 ghost_go( DIR_UP ); 
                             }
                         }else {
                             if( rand()%10 < pprob[i] ) {
                                 ghost_go( DIR_DOWN );
                             }else {
                                 ghost_go( DIR_UP );
                             }
                         }
                         ++py[i];*/
    }
    return py;
}

int analize_for_down_direction( int x, int y, int px, int py, int pprob, int i )
{
    if ( ghost_found( BOTT_LEFT )){
                         ghost_go( DIR_RIGHT ); 
                         --px;
    }else if ( ghost_found( BOTT_RIGHT )){
                         ghost_go( DIR_LEFT ); 
                         --px;
  /*  }else if ( ghost_found( END_WAY )){ // tiene que ir izq o derecha
                         // añadir probabilidad para que salga
                         if( rand()%10 <= pprob ) {
                             if ( pacman_is_to_the_right ) {
                                 ghost_go( DIR_RIGHT );
                             }else {
                                 ghost_go( DIR_LEFT ); 
                             }
                         }else {
                             if( rand()%10 < pprob ) {
                                 ghost_go( DIR_RIGHT );
                             }else {
                                 ghost_go( DIR_LEFT );
                             }
                         }
                         --px;*/

    }else if ( ghost_found( LEFT_CRUX )){
                         if ( pacman_is_down )     { 
                             if( rand()%10 < pprob ) {
                                  ghost_go( DIR_DOWN );
                             }else{ 
                                  ghost_go( DIR_RIGHT );
                             }
                         }
                         else{
                             if( rand()%10 < pprob ) {
                                  ghost_go( DIR_RIGHT );
                             }else{
                                  ghost_go( DIR_DOWN );
                             }
                         }

    }else if (ghost_found( RIGHT_CRUX )){
                         if ( pacman_is_down ) { 
                             if( rand()%10 < pprob ) {
                                  ghost_go( DIR_LEFT );
                             }else{ 
                                  ghost_go( DIR_DOWN );
                             }
                         }
                         else{
                            if( rand()%10 < pprob ) {
                                  ghost_go( DIR_DOWN );
                             }else{
                                  ghost_go( DIR_LEFT );
                             }
                         }
                     
    }else if ( ghost_found( BOTT_CRUX )){
                         //int prob = rand()%10;
                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left )  {
                                 ghost_go( DIR_LEFT );
                             }else{
                                 ghost_go( DIR_RIGHT );
                             } // aplicar prob.
                         }else if ( pacman_is_up ){
                             if( pacman_is_to_the_left )  {
                                 ghost_go( DIR_LEFT );
                             }else {
                                 ghost_go( DIR_RIGHT );
                             } // aplicar prob.
                         }else{
                             if ( pacman_is_to_the_left )  {
                                 ghost_go( DIR_LEFT );
                             }else{
                                 ghost_go( DIR_RIGHT );
                             }
                         }

    }else if ( ghost_found( CRUX )){
                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_DOWN );
                                 }else{
                                     ghost_go( DIR_LEFT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_RIGHT );
                                 }else{
                                     ghost_go( DIR_DOWN );
                                 }
                             }else{  // está en la mismo pasillo
                                 ghost_go( DIR_DOWN );
                             }
                         }else if( pacman_is_up ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_LEFT );
                                 }else{
                                     ghost_go( DIR_RIGHT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){
                                     ghost_go( DIR_RIGHT );
                                 }else{
                                     ghost_go( DIR_UP );
                                 }
                             }else{  // está en la mismo pasillo
                                 ghost_go( DIR_UP );
                             }
                         }else{   // tiene que ser igual
                             if( pacman_is_to_the_left ){  
                                 ghost_go( DIR_LEFT );
                             }else{ 
                                 ghost_go( DIR_RIGHT );
                             }
                         }
                     }
    return px;
}

int analize_for_up_direction( int x, int y, int px, int py, int pprob, int i )
{
    if ( ghost_found( TOP_RIGHT )){
                         ghost_go( DIR_LEFT ); 
                         ++px;
    }else if ( ghost_found( TOP_LEFT )){
                         ghost_go( DIR_RIGHT ); 
                         ++px;

    }else if ( ghost_found( END_WAY ) ||
               ghost_found( TOP_HOME )){ // tiene que ir izq o derech
                         // añadir probabilidad para que salga
                         if( rand()%10 <= pprob ) {
                             if ( pacman_is_to_the_right ) {
                                 ghost_go( DIR_RIGHT );
                             }else {
                                 ghost_go( DIR_LEFT ); 
                             }
                         }else {
                             if( rand()%10 < pprob ) {
                                 ghost_go( DIR_RIGHT );
                             }else {
                                 ghost_go( DIR_LEFT );
                             }
                         }
                         ++px;

    }else if ( ghost_found( RIGHT_CRUX )){
                         if ( pacman_is_down ) {
                             ghost_go( DIR_LEFT );
                         }else {
                             if( rand()%10 < pprob ) {
                                 ghost_go( DIR_UP );
                             }else  {
                                 ghost_go( DIR_LEFT );
                             }
                         }
                         
    }else if ( ghost_found( LEFT_CRUX )){
                         if ( pacman_is_down )  {
                             if( rand()%10 < pprob ) {
                                  ghost_go( DIR_RIGHT ); 
                             }else{ 
                                  ghost_go( DIR_UP ); 
                             }
                         }else {
                             if( rand()%10 < pprob ) {
                                  ghost_go( DIR_UP );
                             }else{
                                  ghost_go( DIR_RIGHT );
                             }
                         }
                         
    }else if ( ghost_found( TOP_CRUX )){
                         //int prob = rand()%10;
                         if( pacman_is_to_the_left ) { 
                             ghost_go( DIR_LEFT );
                         }else{ 
                             ghost_go( DIR_RIGHT ); 
                         }// aplicar prob.

    }else if ( ghost_found( CRUX )){
                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ) { 
                                     ghost_go( DIR_LEFT );
                                 }else{ 
                                     ghost_go( DIR_RIGHT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){ 
                                     ghost_go( DIR_RIGHT );
                                 }else{ 
                                     ghost_go( DIR_LEFT );
                                 }
                             }else{  // está en la mismo pasillo
                                 if ( rand()%10 <= pprob ) {
                                     ghost_go( DIR_LEFT );
                                 }else{  
                                     ghost_go( DIR_RIGHT );
                                 }
                             }
                         }else if( pacman_is_up ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ){ 
                                     ghost_go( DIR_UP );
                                 }else{
                                     ghost_go( DIR_LEFT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){ 
                                     ghost_go( DIR_UP );
                                 }else{ 
                                     ghost_go( DIR_RIGHT );
                                 }
                             }else{  // está en la mismo pasillo
                                 ghost_go( DIR_UP );
                             }
                         }else{   // tiene que ser igual
                             if( pacman_is_to_the_left ) {
                                 ghost_go( DIR_LEFT );
                             }else{
                                 ghost_go( DIR_RIGHT );
                             }
                         }
    }
    return px;
}

int analize_for_right_direction( int x, int y, int px, int py, int pprob, int i )
{
    if ( ghost_found( BOTT_RIGHT )){
                         ghost_go( DIR_UP ); 
                         --py;
    
    }else if ( ghost_found( TOP_RIGHT )){
                         ghost_go( DIR_DOWN ); 
                         --py;
    
   /* }else if ( ghost_found( END_WAY )){ // tiene que ir arriba o abajo
                         // añadir probabilidad para que salga
                         if( rand()%10 <= pprob ) {
                             if ( pacman_is_down ) { 
                                  pdir[i] = DIR_DOWN; 
                             }else{
                                  pdir[i] = DIR_UP; 
                             }
                         }else {
                             if( rand()%10 < 5 ) {
                                  pdir[i] = DIR_DOWN;
                             }else{
                                  pdir[i] = DIR_UP;
                             }
                         }
                         --py[i];*/
    }else if ( ghost_found( TOP_CRUX )){
                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left ) { 
                                 ghost_go( DIR_DOWN );
                             }else{
                                 if( rand()%10 <= pprob ){
                                      ghost_go( DIR_RIGHT ); // aplicar prob.
                                 }else{
                                      ghost_go( DIR_DOWN ); 
                                 }// aplicar prob.
                             }
                         }else if( pacman_is_up ){
                             if( pacman_is_to_the_left ) { 
                                 ghost_go( DIR_RIGHT );
                             }else {
                                 if( rand()%10 <= pprob ){
                                      ghost_go( DIR_DOWN ); // aplicar prob.
                                 }else{
                                      ghost_go( DIR_RIGHT );
                                 } // aplicar prob.
                             }
                         }else{
                             if( pacman_is_to_the_left ) {
                                 ghost_go( DIR_RIGHT );
                             }else{
                                 ghost_go( DIR_DOWN );
                             }
                         }

    }else if ( ghost_found( RIGHT_CRUX )){
                         if ( pacman_is_down ) {
                             if( rand()%10 <= pprob ) {
                                   ghost_go( DIR_DOWN );
                             }else{
                                   ghost_go( DIR_UP );
                             }
                         }else {
                             if( rand()%10 < pprob ) {
                                   ghost_go( DIR_UP );
                             }else{
                                   ghost_go( DIR_DOWN );
                             }
                         }
                         
    }else if ( ghost_found( BOTT_CRUX )){
                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left ) { 
                                  ghost_go( DIR_RIGHT );
                             }else {
                                 if( rand()%10 <= pprob ){
                                      ghost_go( DIR_RIGHT );
                                 }else{
                                      ghost_go( DIR_UP );
                                 } // aplicar prob.
                             }
                         }else if( pacman_is_up ){
                             if( pacman_is_to_the_left ) { 
                                  ghost_go( DIR_UP ); 
                             }else {
                                 if( rand()%10 <= pprob ){
                                     ghost_go( DIR_UP ); // aplicar prob.
                                 }else {
                                     ghost_go( DIR_RIGHT );
                                 } // aplicar prob.
                             }
                         }else{
                             ghost_go( DIR_RIGHT );
                         }

    }else if ( ghost_found( CRUX )){
                         if ( pacman_is_down ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ){
                                      ghost_go( DIR_DOWN );
                                 }else{
                                      ghost_go( DIR_RIGHT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){
                                      ghost_go( DIR_RIGHT );
                                 }else{
                                      ghost_go( DIR_DOWN );
                                 }
                             }else{  // está en la mismo pasillo
                                 ghost_go( DIR_DOWN );
                             }
                         }else if( pacman_is_up ){
                             if( pacman_is_to_the_left ){    
                                 if( rand()%10 < pprob ){
                                      ghost_go( DIR_UP );
                                 }else{
                                      ghost_go( DIR_RIGHT );
                                 }
                             }else if( pacman_is_to_the_right ){
                                 if( rand()%10 < pprob ){
                                      ghost_go( DIR_RIGHT );
                                 }else{
                                      ghost_go( DIR_UP );
                                 }
                             }else{  // está en la mismo pasillo
                                 ghost_go( DIR_UP );
                             }
                         }else{   // tiene que ser igual
                             if( pacman_is_to_the_left ){ 
                                 ghost_go( DIR_LEFT );
                             }else if( pacman_is_to_the_right ){ 
                                 if( rand()%10 <=pprob ){
                                     ghost_go( DIR_UP );
                                 }else{
                                     ghost_go( DIR_DOWN );
                                 }
                             }
                         }
    }

    return py;
}


void draw_ascii_pacman( int color, int bcolor,int pos, int boca )
{
    int i, cntbuff=0;
    //char * vid = (char*)calloc(1024,1);
    static char vid[4096];
    //pos = boca ? pos : pos;
    for (i=0; i<5; i++){
        static char psimb[ 512 ];
        int n = sprintf( psimb, "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[0m",
                         color,bcolor,(SCREEN_ROW+i), SCREEN_COL, pacman[i][ (boca ? 0 : pos) ]);
        const char* pf = psimb;
        memcpy((void *) vid + cntbuff, pf, n );
        cntbuff = cntbuff + n;
    }
    vid[cntbuff]='\0';
    printf("%s",vid); Flush_out;
    //Free_secure(vid);
}

void draw_ascii_junior( int color, int bcolor, int dir, int boca )
{
    int i, cntbuff=0;
    //char * vid = (char*)calloc(1024,1);
    static char vid[4096];
    
    for (i=0; i<5; i++){
        static char psimb[ 512 ];
        int n;
        if ( dir == 0 ){ // corre a la izquierda
            n = sprintf( psimb, "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[0m",
                         color,bcolor,(SCREEN_ROW+i), SCREEN_COL, junior[i][ boca ? 0 : 1 ]);
        }else{
            n = sprintf( psimb, "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[0m",
                         color,bcolor,(SCREEN_ROW+i), SCREEN_COL, junior[i][ boca ? 2 : 3 ]);
        }
        const char* pf = psimb;
        memcpy((void *) vid + cntbuff, pf, n );
        cntbuff = cntbuff + n;
    }
    vid[cntbuff]='\0';
    printf("%s",vid); Flush_out;
    //Free_secure(vid);
}

void death_mr_pacman(int color, int bcolor,int pos )
{
    int i, cntbuff=0;
    //char * vid = (char*)calloc(1024,1);
    static char vid[4096];
    
    for (i=0; i<5; i++){
        static char psimb[ 512 ];
        int n = sprintf( psimb, "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[0m",
                         color,bcolor,(SCREEN_ROW+i), SCREEN_COL, mrpacman_death[i][pos]);
        const char* pf = psimb;
        memcpy((void *) vid + cntbuff, pf, n );
        cntbuff = cntbuff + n;
    }
    vid[cntbuff]='\0';
    printf("%s",vid); Flush_out;
}

void draw_ascii_phantoms( int color, int bcolor,int pos )
{
    int i, cntbuff=0;
    //char * vid = (char*)calloc(1024,1);
    static char vid[4096];
    
    for (i=0; i<5; i++){
        static char psimb[ 512 ];
        int n = sprintf( psimb, "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[0m",
                         color,bcolor,(SCREEN_ROW+i), SCREEN_COL, phantoms[i][pos]);
        const char* pf = psimb;
        memcpy((void *) vid + cntbuff, pf, n );
        cntbuff = cntbuff + n;
    }
    vid[cntbuff]='\0';
    printf("%s",vid); Flush_out;
    //Free_secure(vid);
}
void Put_leds(int num, int nColorF, int nColorB)
{
    int c, cb=0;

    //Str_init(cnum);
    String cnum;  
    cnum = Int2str(num); //Fn_let( cnum, Int2str(num));    
    //char* score=Space(2048);
    static char score[4096];
    
    int i; //, sw=0;
    for( i=0;i<strlen(cnum); i++){
        char w = cnum[i];
        c = w - 48;
        int row = SCREEN_ROW;
        int col = SCREEN_COL + (i*3);
        static char digit[512];
        int n = sprintf( digit,"\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[0m",
                nColorF, nColorB, row, col, cLedsh[0][c],
                row+1,col, cLedsh[1][c],
                row+2,col, cLedsh[2][c]);
        const char* psimb = digit;
        memcpy((void*) score + cb, psimb, n);
        cb += n;
/*        printf( "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[0m",
                nColorF, nColorB, row, col, cLedsh[0][c],
                row+1,col, cLedsh[1][c],
                row+2,col, cLedsh[2][c]);*/
    }
    score[cb]='\0';
    Print "%s", score;
    Flush_out;
    Free secure cnum; //, score;
}

char* Get_leds(int num, int x, int y)
{
    int c, cb=0;

    //Str_init(cnum);
    String cnum;  
    cnum = Int2str(num); //Fn_let( cnum, Int2str(num));    
    char* score=Space(4096);
    
    int i; //, sw=0;
    for( i=0;i<strlen(cnum); i++){
        char w = cnum[i];
        c = w - 48;
        int row = x;
        int col = y + (i*3);
        static char digit[512];
        int n = sprintf( digit,"\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s",
                row, col, cLedsh[0][c],
                row+1,col, cLedsh[1][c],
                row+2,col, cLedsh[2][c]);
        const char* psimb = digit;
        memcpy((void*) score + cb, psimb, n);
        cb += n;
    }
    score[cb]='\0';
    Free secure cnum; //, score;
    return score;
}

/*void print_power_pills( int sw_power_pills, int px, int py )
{
    if (sw_power_pills){
        Print "\x1b[1m\x1b[38;5;255m\x1b[48;5;0m\x1b[%d;%dH%s"\
              "\x1b[%d;%dH%s",px,py, pills[0],px+1,py,pills[1];
                //Color(255,0);
                //At px, py; Print "%s", pills[0];
                //Atrow px+1  ; Print "%s", pills[1];
    }else{
        Print "\x1b[1m\x1b[38;5;255m\x1b[48;5;0m\x1b[%d;%dH   "\
              "\x1b[%d;%dH   ",px,py,px+1,py;

                //Color(0,0);
                //At px, py; Print "   ";
                //Atrow px+1  ; Print "   ";
    }
}*/
void print_power_pills(int stpills[], int sw_power_pills, int px[], int py[])
{
    int i;

    Iterator up i [0:1:4]{
        if( stpills[i] ){
            if (sw_power_pills){
                /*Color(255,0);
                At px[i], py[i]; Print "%s", pills[0];
                Atrow px[i]+1  ; Print "%s", pills[1];*/
                Print "\x1b[38;5;255m\x1b[48;5;%dm\x1b[%d;%dH%s"\
                    "\x1b[%d;%dH%s"\
                    "\x1b[%d;%dH%s\x1b[0m"\
                    ,BACKGROUND,px[i],py[i], pills[0],px[i]+1,py[i],pills[1]\
                    ,px[i]+2,py[i],pills[2];
            }else{
                /*Color(0,0);
                At px[i], py[i]; Print "   ";
                Atrow px[i]+1  ; Print "   ";*/
                Print "\x1b[38;5;255m\x1b[48;5;%dm\x1b[%d;%dH   "\
                    "\x1b[%d;%dH   "\
                    "\x1b[%d;%dH   \x1b[0m",\
                    BACKGROUND,px[i],py[i],px[i]+1,py[i],px[i]+2,py[i];
            }
        }
    }
    Flush_out;
}

void print_dots( int colorF, int colorB ) 
{
    int i,j, cb=0,n; //,j ;//, cb=0;
   // At 12,1; //
   //int cx=Cols(dots); //, rx=Rows(dots);
   //Reshape( dots, rx*cx);
   //Color(colorF, colorB);
   //char *points = Space(25000);
   static char points[300000];
   
   Iterator up i [0:1:101]{
      Iterator up j [0:1:76]{
      if( dots[i][j] == 2 ){
          //int r = (int)(trunc(i/cx));
          //int c = (int)fmod(i,cx);
          //printf("\x1b[%d;%dH\u25cf",r+1,c+1);
          static char local_point[100];
          //n = sprintf(local_point,"\x1b[%d;%dH\u25cf",i+1,j+1);
          n = sprintf(local_point,"\x1b[%d;%dH@",i+1,j+1);
          memcpy((void*) points + cb, local_point, n);
          cb+=n;
      } 
      }
   }
   points[cb]='\0';
   Print "\x1b[38;5;%dm\x1b[48;5;%dm%s", colorF, colorB,points;
   //points[0]='\0';
   //Free secure points;
   
   //Reshape(dots,rx,cx);
/*    Iterator up i [11:1:Rows(dots)]{
        Iterator up j [0:1:Cols(dots)]{
             if( $dots[i,j]==2 ){
                 //printf("\x1b[1m\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH\u25cf",colorF,colorB,i+1,j+1);
                 printf("\x1b[%d;%dH\u25cf",i+1,j+1);
           //      char point[50];
           //      int n = sprintf(point,"\x1b[%d;%dH\u25cf",i+1,j+1);
           //      memcpy( (void*)points + cb, point, n) ;
           //      cb += n;
             }
        }
    }*/
  //  points[cb]='\0';
  //  Print "%s", points;
  //  Free secure points;
    Flush_out;
    Reset_color;
}

/*void print_tunnel()
{
    int i;
    At 51,1; Color(0,0);
    Iterator up i [51 : 1: 57]{
        Print "███████";
        Atcol 68; Print "███████";
        At i,1;
    }
    Reset_color;
}*/

/* considerar esta posicion en los diseños de los laberintos, simepre
   debajo de la casa de los fantasmas */
void pone_fruit(int level_fruit)
{
   Print "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s"\
         "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s"\
         "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s",\
         color_fruit[0][level_fruit],BACKGROUND,62,36,fruits[0][level_fruit],\
         color_fruit[1][level_fruit],BACKGROUND,63,36,fruits[1][level_fruit],\
         color_fruit[1][level_fruit],BACKGROUND,64,36,fruits[2][level_fruit];
//   Color(color_fruit[0][level_fruit],0); At 62,36; Print "%s", fruits[0][level_fruit];
//   Color(color_fruit[1][level_fruit],0); Atrow 63; Print "%s", fruits[1][level_fruit];
//   Color(color_fruit[1][level_fruit],0); Atrow 64; Print "%s", fruits[2][level_fruit];
   Flush_out;
   Reset_color;
}

void quita_fruit()
{
   Print "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH     "\
         "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH     "\
         "\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH     ",\
         BACKGROUND,BACKGROUND,62,36,\
         BACKGROUND,BACKGROUND,63,36,\
         BACKGROUND,BACKGROUND,64,36;
/*   Color(BACKGROUND,BACKGROUND);
   At 62,36; Print "     ";
   Atrow 63; Print "     ";
   Atrow 64; Print "     ";*/
   Flush_out;
   Reset_color;
}


void pone_miniaturas( int vidas, int level_fruit )
{
   int i, col=3;
   
   Iterator up i [0:1:5]{
       if( i<vidas ){
           Color (COLOR_PACMAN,BACKGROUND);
           At 99, col; Print " ▄ ";
           At 100,col; Print "███";
           At 101,col; Print " ▀ ";
       }else{
           Color (BACKGROUND,BACKGROUND);
           At 99, col; Print "   ";
           At 100,col; Print "   ";
           At 101,col; Print "   ";
       }
       Flush_out;
       col += 4;
   }
   col+=2;
   Iterator up i[0:1:level_fruit+1]{
       Color(color_fruit[0][i],BACKGROUND); At 99,col; Print "%s", fruits[0][i];
       Color(color_fruit[1][i],BACKGROUND); Atrow 100; Print "%s", fruits[1][i];
       Color(color_fruit[1][i],BACKGROUND); Atrow 101; Print "%s", fruits[2][i];
       Flush_out;
       col += 6;
   }
   Reset_color;
}

void save_score(int score, int high)
{
   if( score > high ){
       Stack{
           Save_string( Int2str(score), "tests/dataPacman/high.txt" );
       }
   }
}

int load_high_score()
{
   int high=0;
   if( Exist_file("tests/dataPacman/high.txt")){
       Stack{
           high = Str2int( Load_string("tests/dataPacman/high.txt"));
       } Stack_off;
   }
   return high;
}

void refresh_score(int score)
{
   int ls = !score ? 0 : floor(log10( ( score ) ))+1;
   At 6, 55-ls;Put_leds(score,15,BACKGROUND); Flush_out; //37
}

void pone_score(int score, int *sw_extra_active, int * vidas, int level_fruit )
{
   int ls = !score ? 0 : floor(log10( ( score ) ))+1;
   At 6, 55-ls;Put_leds(score,15,BACKGROUND); Flush_out; //37
   if( sw_extra_active ){
       if ( score >= 20000 && *sw_extra_active==1 ){
           
           system( PAC_EXTRA );
           *vidas = *vidas + 1;
           *sw_extra_active=0;
           pone_miniaturas(*vidas-1, level_fruit);
       }else if ( score >= 10000 && *sw_extra_active == 2){
           //const char *PAC_EXTRA = "aplay tests/dataPacman/mspacman_extrapac.wav </dev/null >/dev/null 2>&1 &";
           system( PAC_EXTRA );
           *vidas = *vidas + 1;
           *sw_extra_active=*sw_extra_active-1;
           pone_miniaturas(*vidas-1, level_fruit);
       }
   }
}

/* PID 's
   El último PID que entra a la cola de proceso, es el primero de la
   lista de "pidof". Siempre debo sacar le primero, para no eliminar
   el sonido equivocado */
   
char * put_sound( int typeSound )
{
   String PID_SOUND;
   if( !sw_sound_p )
       system( sound[ typeSound ] );
   else
       system( mrsound[ typeSound ] );
       
   PID_SOUND = `pidof aplay`;
   char ot = Set_new_sep(' ');
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

/*
char* pone_waka()
{
   String PIDWAKA;
   char *PAC_EAT_GHOST = "aplay tests/dataPacman/mspacman_waca2.wav </dev/null >/dev/null 2>&1 &";
   system( PAC_EAT_GHOST );
   PIDWAKA = `pidof aplay`;
   char ot = Set_new_sep(' ');
   Fn_let( PIDWAKA, Get_token(PIDWAKA, 1));
   Set_token_sep(ot);
   return PIDWAKA;
}

char* pone_pills()
{
   String PIDPILLS;
   char *PAC_PILLS = "aplay tests/dataPacman/mspacman-pills.wav </dev/null >/dev/null 2>&1 &";
   system( PAC_PILLS );
   PIDPILLS = `pidof aplay`;
   char ot = Set_new_sep(' ');
   Fn_let( PIDPILLS, Get_token(PIDPILLS, 1));
   Set_token_sep(ot);
   return PIDPILLS;
}
char* pone_eat_phantom()
{
   String PIDEATGHOST;
   char *PAC_EAT_GHOST = "aplay tests/dataPacman/mspacman_eatghost.wav </dev/null >/dev/null 2>&1 &";
   system( PAC_EAT_GHOST );   
   PIDEATGHOST = `pidof aplay`;
   char ot = Set_new_sep(' ');
   Fn_let( PIDEATGHOST, Get_token(PIDEATGHOST, 1));
   Set_token_sep(ot);
   return PIDEATGHOST;
}

char* pone_siren()
{
   String PIDSIREN;
   char *PAC_SIREN = "aplay tests/dataPacman/mspacman_siren.wav </dev/null >/dev/null 2>&1 &";
   system( PAC_SIREN );   
   PIDSIREN = `pidof aplay`;
   char ot = Set_new_sep(' ');
   Fn_let( PIDSIREN, Get_token(PIDSIREN, 1));
   Set_token_sep(ot);
   return PIDSIREN;
}
*/
/*void kill_siren( char *PIDSIREN)
{
   char strkill[100];
   sprintf( strkill, "kill -9 %s </dev/null >/dev/null 2>&1 &", PIDSIREN);
   system(strkill);
}

void kill_waka( int *sw_waka, char *PIDWAKA)
{
   char strkill[100];
   sprintf( strkill, "kill -9 %s </dev/null >/dev/null 2>&1 &", PIDWAKA);
   system(strkill);

   *sw_waka=0;
}

void kill_pills( char *PIDPILLS)
{
   char strkill[100];
   sprintf( strkill, "kill -9 %s </dev/null >/dev/null 2>&1 &", PIDPILLS);
   system(strkill);
}

void kill_eat_ghost(char* PIDEATGHOST)
{
   char strkill[100];
   sprintf( strkill, "kill -9 %s </dev/null >/dev/null 2>&1 &", PIDEATGHOST);
   system(strkill);
}*/

void kill_all_sounds()
{
   String PID;
   //Stack { Store ( PID, Char_only( Get_sys("pidof aplay"), "0123456789" )); } Stack_off;
   Fn_let ( PID, Get_sys("pidof aplay" ));
   if (strlen(PID)>0){
      char cpids[256];
      sprintf(cpids,"kill -9 %s </dev/null >/dev/null 2>&1",PID);
      system(cpids);
   }
   Free secure PID;
}

void death_pacman(int x, int y,const char*pacman[5][5])
{
   //static char *PAC_EAT = "aplay tests/dataPacman/mspacman_death.wav </dev/null >/dev/null 2>&1 &";
   if( !sw_sound_p){
       system( MSPAC_EAT );
       int desvanece[] = {255,245,238,BACKGROUND};
       int i;
       for (i = 0; i<4; i++){
           At x,y; draw_ascii_pacman(desvanece [i],BACKGROUND,1,0);
           usleep(100000-i*1000);
           At x,y; draw_ascii_pacman(desvanece [i],BACKGROUND,2,0);
           usleep(100000-i*1000);
           At x,y; draw_ascii_pacman(desvanece [i],BACKGROUND,3,0);
           usleep(100000-i*1000);
           At x,y; draw_ascii_pacman(desvanece [i],BACKGROUND,4,0);
           usleep(100000-i*1000);
       }
   }else{
       system( MRPAC_EAT );
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,0);
       usleep(150000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,1);
       usleep(150000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,2);
       usleep(150000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,3);
       usleep(150000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,4);
       usleep(150000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,5);
       usleep(150000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,6);
       usleep(400000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,7);
       usleep(100000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,8);
       usleep(100000);
       At x,y; death_mr_pacman(COLOR_PACMAN,BACKGROUND,9);
       usleep(400000);
       At x,y; death_mr_pacman(BACKGROUND,BACKGROUND,9);
   }   
   sleep(1);
   Reset_color;
}

int get_total_dots() // RDS(int, dots) )
{
   int i,j;
   int cnt_dots=0;
   Iterator up i[0:1:101]{
       Iterator up j[0:1:76]{
            if ( dots[i][j] == 2 || dots[i][j] == 50 || dots[i][j] == 51 ||
                 dots[i][j] == 52 || dots[i][j] == 53 )
                 ++cnt_dots;
       }
   }
   return cnt_dots;

}

void get_loc_power_pills( /*pRDS(int, dots),*/ int pillx[], int pilly[], int *tx, int *ty )
{
    int i,j, x=0;
    Iterator up i[0:1:101]
    {
        Iterator up j[0:1:76]
        {
            if( dots[i][j] >= 50 && dots[i][j] < 60 ){ // obtengo ubicacion absoluta de cada power pills
                 pillx[x] = i;
                 pilly[x] = j;
                 x++;
            }else if( dots[i][j] == 10 ){
                 *tx = i-1;  // ubicación en pantalla de pacman
                 *ty = j-1;
                 dots[i][j] = 1; //@v[] accede al puntero del array pasado por parametro
            }
        }
    }
}

void get_loc_ghost_pos( int ghostx[], int ghosty[] )
{
    int i,j, x=0;
    Iterator up i[0:1:101] //pRows(pdots)]
    {
        Iterator up j[0:1:76] //pCols(pdots)]
        {
            if( pdots[i][j] >= 40 && pdots[i][j] < 60 ){
                //if( pdots[i][j] < TUNNEL_L ){
                    ghostx[x] = i-1;
                    ghosty[x] = j-1;
                    pdots[i][j] = 1;
                    x++;
                /*}else{
                    if(pdots[i][j] == TUNNEL_L ){
                        topT = topT + 1;
                        tleft[ topT ] = j-1;
                    }else{  // debe ser TUNNEL_R
                        tright[ topT ] = j-1;
                    }
                }*/
            }
        }
    }
}

char * prepare_lab_string( char* lab, int high /*, int colorF*/ )
{
    int i, nlines;
    String new_lab;
    char oldsep = Set_new_sep('\n');
    
    nlines = Count_tokens( lab );
    
    //char header[100];
    //sprintf( header, "\x1b[38;5;%dm\x1b[48;5;0m\x1b[1;1H", colorF ); 
    //Let( new_lab, header ); 

    Let( new_lab, "\x1b[1;1H" ); 
    Fn_cat( new_lab, Get_token(lab, 1) );
    
    Iterator up i [2:1:nlines]
    {
        String cline;
        char buffer[2048];
        Fn_let( cline, Get_token(lab, i) );
        
        sprintf( buffer, "\x1b[%d;1H%s",i, cline );
        Cat ( new_lab, buffer );
        Free secure cline;
    }
    Set_token_sep(oldsep);
    /* pone el high */
    int ls = !high ? 0 : floor(log10( ( high ) ))+1;
    //char * shigh = Get_leds(high, 6, 18-ls);
    
    Fn_cat( new_lab, Get_leds(high, 6, 18-ls) );
    
    //Free secure shigh;
    return new_lab;
}


void put_big_message(char *msg, int nColorF, int nColorB)
{
    //String tmsg;
    //Fn_let( tmsg, Upper( msg ) );
    const char* ps = msg; //tmsg;
    int row = SCREEN_ROW;
    int col = SCREEN_COL;
    while (*ps){
        char lett = *ps;
        int i,sw=0;
        if( lett == 32 ) i=26;
        else if ( lett == '!' ) i=27;
        else if ( lett == '.' ) i=28;
        else if ( lett == '?' ) i=29;
        else if ( lett == ',' ) i=30;
        else{ 
            if( isupper(lett) ){
                sw=1; i = lett - 'A';
            }else{
                i = lett - 'a';
            }
            ///i = isupper(lett) ? lett - 'A' : lett - 'a';
        }
        char letter[1024];
        sprintf( letter,"\x1b[38;5;%dm\x1b[48;5;%dm\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[%d;%dH%s\x1b[0m",
                nColorF, nColorB, row, col, (sw ? letters_C[0][i]:letters[0][i]),
                row+1,col, (sw ? letters_C[1][i]:letters[1][i]),
                row+2,col, (sw ? letters_C[2][i]:letters[2][i]));
        const char* psimb = letter;
        col = col + (sw ? size_letter_C[i]+1 : size_letter[i]+1);
        ++ps;
        Print "%s",psimb; Flush_out;
    }
    //Free secure tmsg;
}

/* Esta presentación es mala... pero es míiiiiiiiiaaaaaaa */
void initial_screen()
{
     const char* nameGhost[3][4] = {
     {" ▄  ▄  ▄  ▄  ▄   ▄ ▄"," ▄  ▄  ▄  ▄   ▄ ▄","▄  ▄  ▄   ▄ ▄"," ▄▄ ▄  ▄ ▄ ▄▄   ▄▄"},
     {"█▄▀ █  ▄ █ █ █▄▀ ▀▄▀","█▄█ ▄ █ █ █▄▀ ▀▄▀","▄ █ █ █▄▀ ▀▄▀","█   █  ▀▄▀ █ █ █▀ "},
     {"▀▄▀  ▀ ▀ ▀ ▀ ▀ ▀  ▀ ","▀   ▀ ▀ ▀ ▀ ▀  ▀ ","▀ ▀ ▀ ▀ ▀  ▀ "," ▀▀  ▀  ▀  ▀▄▀  ▀▀"}};
       
     Color (BACKGROUND,BACKGROUND); Cls;
     //Color(240,BACKGROUND);
     At 94,40 ; put_big_message("Mr. Dalien",240,BACKGROUND);
     //At 94, 45; Print "█▙ ▟█  ▄  █▀▙ ▟▀▙ █  ▀ ██ █▙ █";
     //At 95, 45; Print "█ ▀ █ █   █▄▛ █▀█ █▄ █ █▄ █ ▙█";

     Color(COLOR_PACMAN,BACKGROUND);
     At 10,1; Print "  ██████▄▄     ▟▙         ▄▟██▄▄    █▙        ▟█       ▟▙       █▙     ███";
     At 11,1; Print "  █████████▄  ▟██▙     ▟█████████▄  ██▙      ▟██      ▟██▙      ██▙    ███";
     At 12,1; Print "  █████████▀ ▟████▙   ▄█████▀▀▀     ███▙    ▟███     ▟████▙     ███▙   ███";
     At 13,1; Print "  ██████▀▀  ▟██████▙  ▀█████▄▄▄     ████▙  ▟████    ▟██████▙    ████▙  ███";
     At 14,1; Print "  ███      ▟███ ▄███▙  ▀█████████▀  █████▙▟███ █   ▟███ ▄███▙   █████▙▄█ █";
     At 15,1; Print "  ███     ▟██████████▙    ▀▀██▀▀    ███████▄▄▄▄█  ▟██████████▙  ████████▄█";
     
     
     system("aplay -q tests/dataPacman/mspacman_Coin_Credit.wav </dev/null >/dev/null 2>&1 &");
     
     int pColor[]={196,201,45,172}, i;
     Iterator up i[0:1:4]{
       At 30+(i*6), 20; draw_ascii_phantoms(pColor[i],BACKGROUND,i);
       Color (255,BACKGROUND);
       At 32+(i*6), 28; Print "▀▀";
       At 33+(i*6), 28; Print "▀▀";
       Color( pColor[i],BACKGROUND );
       At 31+(i*6), 32; Print "%s", nameGhost[0][i];
       At 32+(i*6), 32; Print "%s", nameGhost[1][i];
       At 33+(i*6), 32; Print "%s", nameGhost[2][i];
       Reset_color;
     }

     Flush_out;
     int col=6, sw=1;
     Iterator up i[0:1:8]{
       Color(color_fruit[0][i],BACKGROUND); At 75,col; Print "%s", fruits[0][i];
       Color(color_fruit[1][i],BACKGROUND); Atrow 76; Print "%s", fruits[1][i];
       Color(color_fruit[1][i],BACKGROUND); Atrow 77; Print "%s", fruits[2][i];
       
       if( sw ) { At 70, col;} //-2; }
       else     { At 80, col;} //-2; }
       sw = sw ? 0 : 1;
       Put_leds(point_fruit[i],166,BACKGROUND);
       Flush_out;
       col += 8;
     }
     Flush_out;
     Reset_color;
     
     Color( 255,BACKGROUND );
     At 60, 28; Print "▀▀              \u25cf    ▀▀";
     At 61, 28; Print "▀▀                   ▀▀";
     At 60, 33; Put_leds(50,255,BACKGROUND);  
     At 60, 53; Put_leds(10,255,BACKGROUND);
     
   //  Enable_raw_mode();
     int boca = 1, sw_power_pills=1;
     unsigned long t=0L,tp=0L;
     t = Tic(); tp = Tic();
     while ( !Kbhit() ){
         When ( Timer( &t, 80L ) ){
             At 22,36; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_LEFT,boca);
             boca = boca ? 0 : 1;
         }
         When ( Timer( &tp, 220L ) ){
            if (sw_power_pills){
                Color(255,BACKGROUND);
                At 60, 20; Print "%s", pills[0];
                Atrow 61 ; Print "%s", pills[1];
                Atrow 62 ; Print "%s", pills[2];
            }else{
                Color(BACKGROUND,BACKGROUND);
                At 60, 20; Print "   ";
                Atrow 61 ; Print "   ";
                Atrow 62 ; Print "   ";
            }
            sw_power_pills = sw_power_pills ? 0 : 1;
         }
     }
   //  Disable_raw_mode();

}


/* animations!! */
void play_Act(int nAct)
{
    if (nAct==1)
    {
        Color(BACKGROUND,BACKGROUND);
        Cls;
        At 5,22 ; put_big_message("They meet",121,0);
        system("aplay -q tests/dataPacman/mspacman_They_Meet_Act_1.wav </dev/null >/dev/null 2>&1 &");
        unsigned long t = Tic(), tg=Tic();
        int y=1, yg=1, boca=0, swp=1,swg=0;
        int yb=71, ygb=71;
        while ( swp || swg){
           if (swp ){
              When ( Timer( &t, 50L ) ){
                 At 22,y-1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                 At 22,y++; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_RIGHT,boca);
                 
                 At 32,yb+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                 At 32,yb--; draw_ascii_pacman(225,BACKGROUND,DIR_LEFT,boca);
                 boca = boca ? 0 : 1;
              }
              When( y == 71 ){
                 At 22,y-1;  draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                 At 32,yb+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                 swp=0;
              }
           }
           
           if ( y>=25 ) swg=1;
           When( swg ){
              if( yg==71 ){
                  At 22, yg-1; draw_ascii_phantoms(BACKGROUND,BACKGROUND,0);
                  At 32, ygb+1; draw_ascii_phantoms(BACKGROUND,BACKGROUND,0);
                  swg=0;
              }else{
                  When( Timer( &tg, 37L ) ){
                      At 22, yg-1; draw_ascii_phantoms(BACKGROUND,BACKGROUND,1);
                      At 22, yg++; draw_ascii_phantoms(196,BACKGROUND,1);
                      
                      At 32, ygb+1; draw_ascii_phantoms(BACKGROUND,BACKGROUND,2);
                      At 32, ygb--; draw_ascii_phantoms(45,BACKGROUND,2);
                  }
              }
           }
        }
        usleep(500000);
        String PIDPILLS, PIDEATGHOST;
        Fn_let( PIDPILLS, put_sound(SND_PILLS));
        //sleep(1);
        usleep(500000);
        
        Fn_let( PIDEATGHOST, put_sound(SND_EATGHOST)); 
        usleep(500000);
        kill_sound(PIDEATGHOST); Free secure PIDEATGHOST;
        Fn_let( PIDEATGHOST, put_sound(SND_EATGHOST)); 
        usleep(500000);
        kill_sound(PIDEATGHOST);
        kill_sound(PIDPILLS); 
        usleep(500000);
        Free secure PIDPILLS, PIDEATGHOST;
        
        y=1, yg=1, boca=0, swp=1,swg=0;
        yb=71, ygb=71;
        while ( swp || swg){
           if (swp ){
              When ( Timer( &t, 50L ) ){
                 At 32,y-1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                 At 32,y++; draw_ascii_pacman(225,BACKGROUND,DIR_RIGHT,boca);
                 
                 At 32,yb+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                 At 32,yb--; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_LEFT,boca);
                 boca = boca ? 0 : 1;
              }
              When( y == 34 ){
                 //At 32,y-1;  draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                 //At 32,yb+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                 swp=0;
              }
           }
        }
        usleep(500000);
           Print "\x1b[38;5;196m\x1b[48;5;232m\x1b[23;36H%s"\
                 "\x1b[38;5;196m\x1b[48;5;232m\x1b[24;36H%s"\
                 "\x1b[38;5;196m\x1b[48;5;232m\x1b[25;36H%s",\
                 fruits[0][6],\
                 fruits[1][6],\
                 fruits[2][6];
           Flush_out;
           Reset_color;
        sleep(2);
        //Pause();
    }else if( nAct==2)
    {
        Color(BACKGROUND,BACKGROUND);
        Cls;
        At 5,18 ; put_big_message("The craving",121,0);

        system("aplay -q tests/dataPacman/mspacman_The_Chase_Act_2.wav </dev/null >/dev/null 2>&1 &");
        sleep(2);
        int sw=1, swp=1, y=1, yb=71, boca=0, x=22;
        int cnt=0, tope=71;
        Seed_by_Time();
        unsigned long t=Tic();
        while(swp){
            When ( Timer( &t, 35L) ){
              if (sw){
                 At x,y-1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                 At x,y++; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_RIGHT,boca);

                 When( y == tope ){
                    At x,y-1;  draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                    yb=71;
                    sw=0;
                    cnt++;
                    if( cnt == 3 ) { swp=0; continue; }
                    else x = rand()%80;
                    if (x<20) x=20;
                    sleep(1);
                 }
                 boca = boca ? 0 : 1;
                 //sleep(1);
              }else{
//              When ( Timer( &t, 35L-cnt ) ){
                 At x,yb+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                 At x,yb--; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_LEFT,boca);
                 
                 When( yb== 1 ){
                    At x,yb+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                    y=1;
                    sw=1;
                    x = rand()%80;
                    if (x<20) x=20;
                    sleep(1);
                    //cnt++;
                    if( cnt == 2 ) {
                        x = 40;
                        Print "\x1b[38;5;82m\x1b[48;5;232m\x1b[%d;46H%s"\
                              "\x1b[38;5;196m\x1b[48;5;232m\x1b[%d;46H%s"\
                              "\x1b[38;5;196m\x1b[48;5;232m\x1b[%d;46H%s",\
                              x+1,fruits[0][5],\
                              x+2,fruits[1][5],\
                              x+3,fruits[2][5];
                        Flush_out;
                        Reset_color;
                        tope=46;
                        //swp=0;
                    }
                 }
                 boca = boca ? 0 : 1;
                 //sleep(1);
                 
              }
           }
        }
        //system("aplay -q tests/dataPacman/pacman_eatfruit.wav </dev/null >/dev/null 2>&1 &");
        system(EAT_FRUIT);
        At x,y-1;  draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_RIGHT,0);
        swp=1;
        while(swp){
            When ( Timer( &t, 20L) ){
                At x,y+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                At x,y--; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_LEFT,boca);
                 
                When( y == 1 ){
                    At x,y+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                    swp=0;
                }
                boca = boca ? 0 : 1;
            }
        }
        swp=1; y=71;
        At x,30; draw_ascii_pacman(225,BACKGROUND,DIR_RIGHT,1);
        while(swp){
            When ( Timer( &t, 40L) ){
                At x,y+1; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_LEFT,boca);
                At x,y--; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_LEFT,boca);
                 
                When( y == 41 ){
                    At x,y+1; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_LEFT,0);
                    swp=0;
                }
                boca = boca ? 0 : 1;
            }
        }
        
        Print "\x1b[38;5;82m\x1b[48;5;232m\x1b[%d;37H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[%d;37H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[%d;37H%s",\
              x+1,fruits[0][5],\
              x+2,fruits[1][5],\
              x+3,fruits[2][5];
              Flush_out;
              Reset_color;
        usleep(500000);
        At x,30; draw_ascii_pacman(225,BACKGROUND,DIR_RIGHT,0);
        usleep(500000);
        Print "\x1b[38;5;196m\x1b[48;5;232m\x1b[%d;30H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[%d;30H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[%d;30H%s",\
              x-4,fruits[0][6],\
              x-3,fruits[1][6],\
              x-2,fruits[2][6];
           Flush_out;
           Reset_color;
        sleep(2);
    }else if(nAct==3)
    {
                              
        Color(BACKGROUND,BACKGROUND);
        Cls;
        At 5,27 ; put_big_message("Junior",121,0);
        At 60,10; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_RIGHT,1);
        At 60,16; draw_ascii_pacman(225,BACKGROUND,DIR_RIGHT,1);
        
        system("aplay -q tests/dataPacman/mspacman_Junior_Act_3.wav </dev/null >/dev/null 2>&1 &");
        int swf=1, cnt=0, x=31, y=55, yb=0, swjr=0 ; 

        while(swf){

                 Color(15,0);
                 At 30, y; Print "      ▟▙      ▄▟▛   ";
                 At 31, y; Print "  \x1b[38;5;166m▀▀▀▀▀█▙\x1b[38;5;15m  ▄▟██▀    ";
                 At 32, y; Print "        ▜▟█████▛▀   ";
                 At 33, y; Print "          ▀▀▀▀      ";
                 At 34, y; Print "                    ";
                 At 35, y; Print "                    "; Flush_out;
                 
                 if( !swjr ){
                 if( x!=62 && cnt > 2 ) {
                     Color(0,0);
                     At x+1, y; Print " ▟   ";
                     At x+2, y; Print "▟█▙  ";
                     At x+3, y; Print "▜█▛  "; Flush_out;
                     x+=2;
                     if ( x>=61 ) {x=61; swjr=1;yb=y;}
                 }
                 Color(69,0);
                 At x+1, y; Print " ▟";
                 At x+2, y; Print "▟█▙";
                 At x+3, y; Print "▜█▛"; Flush_out;
                 }
                // --y;
                 //sw=0;
                 usleep(80000);
                 Color(0,0);
                 At 30, y; Print "      ▟▙      ▄▟▛   ";
                 At 31, y; Print "  ▀▀▀▀▀█▙  ▄▟██▀    ";
                 At 32, y; Print "        ▜▟█████▛▀   ";
                 At 33, y; Print "          ▀▀▀▀      ";
                 At 34, y; Print "                    ";
                 At 35, y; Print "                    ";Flush_out;
                 y-=2;

                 Color(15,0);
                 At 30, y; Print "      ▟▙           ";
                 At 31, y; Print "  \x1b[38;5;166m▀▀▀▀▀█▙\x1b[38;5;15m          ";
                 At 32, y; Print "        ▜▟████▛▀   ";
                 At 33, y; Print "          ▀▀▜██    ";
                 At 34, y; Print "              ▜█   ";
                 At 35, y; Print "               ▜   "; 
                 At 31, Flush_out;
                 if( !swjr ){
                 if( x!=62 && cnt > 2 ) {
                     Color(0,0);
                     At x+1, y+2; Print " ▟   ";
                     At x+2, y+2; Print "▟█▙  ";
                     At x+3, y+2; Print "▜█▛  "; Flush_out;
                     x+=2;
                     if ( x>=61 ) {x=61; swjr=1;yb=y;}
                 }

                 Color(69,0);
                 At x+1, y; Print " ▟";
                 At x+2, y; Print "▟█▙";
                 At x+3, y; Print "▜█▛"; Flush_out;
                 }
                 usleep(80000);
                 Color(0,0);
                 At 30, y; Print "      ▟▙           ";
                 At 31, y; Print "  ▀▀▀▀▀█▙          ";
                 At 32, y; Print "        ▜▟████▛▀   ";
                 At 33, y; Print "          ▀▀▜██    ";
                 At 34, y; Print "              ▜█   ";
                 At 35, y; Print "               ▜   "; Flush_out;

                 --y;

                 cnt++;

           if ( y <= 1 ) swf=0;
        }
        sleep(1);
        Color(COLOR_PACMAN,232);
        At x+1, yb; Print "  ┳";
        At x+2, yb; Print " ▜▙";
        At x+3, yb; Print " ▟▛"; Flush_out;
        usleep(400000);
        At 60,10; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_RIGHT,0);
        At 60,16; draw_ascii_pacman(225,BACKGROUND,DIR_RIGHT,0);

        Print "\x1b[38;5;196m\x1b[48;5;232m\x1b[56;14H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[57;14H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[58;14H%s",\
              fruits[0][6],\
              fruits[1][6],\
              fruits[2][6];
           Flush_out;
           Reset_color;   
        sleep(2);
    }
    else if( nAct==4 ){
        Color(BACKGROUND,BACKGROUND);
        Cls;
        At 5,18 ; put_big_message("Run son, run!",121,0);
        system("aplay -q tests/dataPacman/pacman_intermission.wav </dev/null >/dev/null 2>&1 &");
        int swp=1, swg=0, y=71, yg=71, boca=1;
        unsigned long t = Tic(), tg=Tic();
        while ( swp || swg ){
           if (swp ){
              When ( Timer( &t, 60L ) ){
                 At 22,y--; draw_ascii_junior(COLOR_PACMAN,BACKGROUND,0,boca);
                 boca = boca ? 0 : 1;
              }
              When( y == 1 ){
                 At 22,y;  draw_ascii_junior(BACKGROUND,BACKGROUND,0,boca);
                 swp=0;
              }
           }
           if ( y<=48 ) swg=1;
           When( swg ){
              if( yg==1 ){
                  At 22, yg; draw_ascii_phantoms(BACKGROUND,BACKGROUND,0);
                  swg=0;
              }else{
                  When( Timer( &tg, 45L ) ){
                      At 22, yg--; draw_ascii_phantoms(BACKGROUND,BACKGROUND,0);
                      At 22, yg; draw_ascii_phantoms(196,BACKGROUND,0);
                  }
              }
           }
        }

        //usleep(900000);
        String PIDPILLS;
        Fn_let( PIDPILLS, put_sound(SND_PILLS));
        usleep(900000);
        system("aplay -q tests/dataPacman/pacman_intermission.wav </dev/null >/dev/null 2>&1 &");
        
        swp=0; swg=1; y=1; yg=1;
        int swl=0, yl=1, bocal=0, bocajr=0, yjr=1, swjr=0;
        unsigned long tl = Tic(), tjr=Tic();
        while ( swp || swg || swl || swjr ){
           if (swjr ){
              When ( Timer( &tjr, 40L ) ){
                 At 22,yjr; draw_ascii_junior(BACKGROUND,BACKGROUND,1,bocajr);
                 At 22,++yjr; draw_ascii_junior(COLOR_PACMAN,BACKGROUND,1,boca);
                 bocajr = bocajr ? 0 : 1;
              }
              When( yjr >= 35 ){
                 //At 22,yl;  draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,bocal);
                 At 22,++yjr; draw_ascii_junior(COLOR_PACMAN,BACKGROUND,1,0);
                 swjr=0;
              }
           }
           if (swl ){
              When ( Timer( &tl, 40L ) ){
                 At 22,yl; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,bocal);
                 At 22,++yl; draw_ascii_pacman(225,BACKGROUND,DIR_RIGHT,bocal);
                 bocal = bocal ? 0 : 1;
              }
              When( yl >= 71 ){
                 At 22,yl;  draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,bocal);
                 swl=0;
              }
           }
           if (swp ){
              When ( Timer( &t, 40L ) ){
                 At 22,y; draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                 At 22,++y; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,DIR_RIGHT,boca);
                 boca = boca ? 0 : 1;
              }
              When( y >= 71 ){
                 At 22,y;  draw_ascii_pacman(BACKGROUND,BACKGROUND,DIR_RIGHT,boca);
                 swp=0;
              }
           }
           if ( yg==20 ) swp=1;
           if ( yg==26 ) swl=1;
           if ( yg==50 ) swjr=1;
           When( swg ){
              if( yg==71 ){
                  At 22, yg; draw_ascii_phantoms(BACKGROUND,BACKGROUND,0);
                  swg=0;
              }else{
                  When( Timer( &tg, 50L ) ){
                      At 22, yg++; draw_ascii_phantoms(BACKGROUND,BACKGROUND,0);
                      At 22, yg; draw_ascii_phantoms(21,BACKGROUND,0);
                  }
              }
           }
        }
        
        //sleep(6);
        kill_sound(PIDPILLS); 
        
        Free secure PIDPILLS;
        String PIDEATGHOST;
        Fn_let( PIDEATGHOST, put_sound(SND_EATGHOST));
        usleep(500000);
        //kill_sound(PIDEATGHOST); 
        Free secure PIDEATGHOST;
        
        Print "\x1b[38;5;196m\x1b[48;5;232m\x1b[17;35H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[18;35H%s"\
              "\x1b[38;5;196m\x1b[48;5;232m\x1b[19;35H%s",\
              fruits[0][6],\
              fruits[1][6],\
              fruits[2][6];
           Flush_out;
           Reset_color; 
        
        sleep(2);
    }
}

void  pone_ready( int vidas,int inicio, int level_fruit, //const char*pacman[5][5], const char*phantoms[5][5],
                  int px[], int py[], int x, int y )
{
   int i=1;
   int color=121;
   if (inicio){
      //char *PAC_INIT = "aplay tests/dataPacman/mspacman_beginning.wav </dev/null >/dev/null 2>&1 &";
      if (!sw_sound_p)
          system( MSPAC_INIT );
      else
          system( MRPAC_INIT );
       
   }
   print_dots( COLOR_DOTS,BACKGROUND );
   pone_miniaturas(vidas, level_fruit);
   
   //Color(121,BACKGROUND);
   while ( i<=2 ){
      /*At 62, 28; Print " ▄   ▄▄  ▄  ▄▄  ▄ ▄ ▄▄ ";
      At 63, 28; Print "█▄▀ █▀  █▄█ █ █ ▀▄▀ █▛ ";
      At 64, 28; Print "▀ ▀  ▀▀ ▀ ▀ ▀▄▀  ▀  ▄  ";*/
      At 62,28 ; put_big_message("Ready!",color,BACKGROUND);
      Flush_out;
      if ( i==1 ) sleep(2);
   
      //Color(BACKGROUND,BACKGROUND);
      color=BACKGROUND;
      ++i;
   }
   pone_miniaturas(vidas-1, level_fruit);
   At x,y; draw_ascii_pacman(COLOR_PACMAN,BACKGROUND,0,0); // 77,36
   Iterator up i[0:1:4]{
       At px[i],py[i]; draw_ascii_phantoms(15,BACKGROUND,i);
   }
   if (inicio) sleep(2);
   
}

void game_over()
{
    Color( COLOR_PACMAN,BACKGROUND );
    int colx = 28;
    At 49, colx; Print "                     ";
    At 50, colx; Print "   ▄▄  ▄   ▄ ▄   ▄▄  ";
    At 51, colx; Print "  █ ▄ █▄█ █ █ █ █▀   ";
    At 52, colx; Print "   ▀▀ ▀ ▀ ▀ ▀ ▀  ▀▀  ";
    At 53, colx; Print "    ▄  ▄ ▄  ▄▄  ▄    ";
    At 54, colx; Print "   █ █ █ █ █▀  █▄▀   ";
    At 55, colx; Print "    ▀   ▀   ▀▀ ▀ ▀   ";
    At 56, colx; Print "                     ";
    Flush_out;
    sleep(3);
    Reset_color;
}

