/*
  GADGET.H
  
  Headers sobre tratamiento de cadenas y de arrays.

*/

//#ifndef _LIB_GADGET_MAIN_

//#define _LIB_GADGET_MAIN_

#ifndef _STDIO_H
#   include <stdio.h>
#endif


#ifndef _STDLIB_H
#   include <stdlib.h>
#endif

#ifndef _UNISTD_H
#   include <unistd.h>
#endif

#ifndef _MATH_H
#   include <math.h>
#endif

#ifndef _STRING_H
#   include <string.h>
#endif

#ifndef _TIME_H
#   include <time.h>
#endif

#ifndef _MALLOC_H
#   include <malloc.h>
#endif

#ifndef _SIGNAL_H
#   include <signal.h>
#endif

#ifndef _STDARG_H
#   include <stdarg.h>
#endif

#ifndef _LIBC_LIMITS_H_
#   include <limits.h>
#endif

#ifndef _TERMIOS_H
#   include <termios.h>
#endif


#ifndef _SYS_IOCTL_H
#   include <sys/ioctl.h>
#endif

#ifndef _SYS_TYPES_H
#   include <sys/types.h>
#endif

#ifndef _SYS_STAT_H
#   include <sys/stat.h>
#endif

#ifndef _SYS_TIME_H
#   include <sys/time.h>
#endif

#ifndef _FCNTL_H
#   include <fcntl.h>
#endif

#ifndef _ERRNO_H
#   include <errno.h>
#endif

#ifndef _REGEX_H
#   include <regex.h>
#endif

#ifndef _SETJMP_H
#   include <setjmp.h>
#endif

#ifndef _CTYPE_H
#   include <ctype.h>
#endif

#ifndef _GPM_H_
#   include <gpm.h>
#endif


#define  HB_OS_UNIX
#define  GNU_SOURCE

/* estructura para PARSER/UNPARSER */
typedef struct _retrieve_tag_{
   char * content;
   ////int status;  // 3=contiene todo; 1=contiene solo contenido; 2= contiene solo attrb;
   int len;    // longitud en filas de array de atributos
   char ** attrib;   // array de valores de atributos
   char ** name;    // array de nombre de atributo
}ST_GETTAG;

/* estructura de datos para STAT_FILE*/
typedef struct _info_file_stat_{
    int   total_lines;
    long  size;
    int   max_line_long;
    int   max_tokens_per_line;
    short is_matrix;
}F_STAT;

/* estructura que recibirá los resultados de REGEXMATCH */

typedef struct __REGEX_ITEM__ {
  int     start;
  int     finish;
  char  * match;
} RE_MATCH;

typedef signed long long   LONGLONG;
typedef unsigned int **    F_SEARCH;

/* MODO RAW */
enum editKey {
  BACKSPACE = 127,
  ENTER = 13,
  ESCAPE = 27,
  SPACE = 32,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN,
  SHIFT_ARROW_UP,
  SHIFT_ARROW_DOWN,
  SHIFT_ARROW_RIGHT,
  SHIFT_ARROW_LEFT,
  ALT_ARROW_UP,
  ALT_ARROW_DOWN,
  ALT_ARROW_RIGHT,
  ALT_ARROW_LEFT,
  CTRL_ARROW_UP,
  CTRL_ARROW_DOWN,
  CTRL_ARROW_RIGHT,
  CTRL_ARROW_LEFT,
  CTRL_TAB
};

/* definiciones para manejo de arrays */

typedef struct _single_arr_{
    int len;                /* longitud total del array */
    int rows, cols, pags, books;   /* rangos del array */
    int dims;               /* dimension del array */
    int rowi, rowinc, rowe; /* rangos de acceso local a arrays */
    int coli, colinc, cole;
    int pagi, paginc, page;
    int booki, bookinc, booke;
    int * sparse;           /* coordenadas sparse */
    int Is_sparse;          /* 1=es sparse; 0=no lo es */
    short type;             /* tipo del array (valores en _data_types_) */
} DS_ARRAY;


/* MIN y MAX de una lista */
typedef struct __data_max_min__ {
  int  local;
  int  row;
  int  col;
  int  pag;
  int  book;
} DS_MAXMIN;

/* los arrays simples solo admiten estos tipos de datos numéricos: */
enum _data_types_{
   int_TYPE = 1,
   float_TYPE,
   double_TYPE,
   long_TYPE,
   unsigned_int_TYPE,
   unsigned_long_TYPE=6,
   string_TYPE=10,
   MULTI_TYPE
};

/* clon de _data_type_, para uso del usuario */
enum _data_user_types_{
   INTEGER = 1,
   FLOAT,
   DOUBLE,
   LONG,
   UINTEGER,
   ULONG,
   STRING=10
};


/* estructura de datos simple para arrays multitipo */
typedef enum _data_types_  ElementType;

typedef struct __Element__ {
  ElementType type;
  void        *value;
}MT_CELL;


/* estructura para acceso a buffer de video personal */
typedef struct __video_mem__{
   unsigned char *video_mem; //, *color_mem;
   unsigned int count_buffer;
//   int **video_color;
   size_t video_rows, video_cols;
//   int count_color;
} GD_VIDEO;

/* límite de stack de strings.
   Las funciones de string aquí usan una modalidad doble: pueden recibir y devolver datos
   desde y hacia un stack. Esto posibilita que puedan ser anidadas.
   Las funciones string de C no pueden hacer esto: si desea que puedan hacer esto, deberá
   escribir una versión propia de ellas. */
#define  LIMITE_STACK_STR   32

/* MENSAJES SIMPLES */

#define  Msg_red(_X_)     printf("\033[38;5;9m%s\033[0m\n",_X_);fflush(stdout);

#define  Msg_yellow(_X_)  printf("\033[38;5;11m%s\033[0m\n",_X_);fflush(stdout);

#define  Msg_green(_X_)   printf("\033[38;5;10m%s\033[0m\n",_X_);fflush(stdout);

#define  Msg_pink(_X_)    printf("\033[38;5;13m%s\033[0m\n",_X_);fflush(stdout);

#define  Msg_amber(_X_)  printf("\033[38;5;208m%s\033[0m\n",_X_);fflush(stdout);

#define  Msg_cyan(_X_)   printf("\033[38;5;14m%s\033[0m\n",_X_);fflush(stdout);

/* MENSAJES CON ARGUMENTOS */
#define  Msg_redf(_X_, ...) \
         printf ("\033[38;5;9m");printf( _X_,##__VA_ARGS__); printf("\033[0m\n");fflush(stdout);
         
#define  Msg_yellowf(_X_,...)    \
         printf ("\033[38;5;11m");printf( _X_,##__VA_ARGS__); printf("\033[0m\n");fflush(stdout);

#define  Msg_greenf(_X_,...)     \
         printf ("\033[38;5;10m");printf( _X_,##__VA_ARGS__); printf("\033[0m\n");  fflush(stdout);

#define  Msg_pinkf(_X_,...)      \
         printf ("\033[38;5;13m");printf( _X_,##__VA_ARGS__); printf("\033[0m\n");fflush(stdout);

#define  Msg_amberf(_X_,...)     \
         printf ("\033[38;5;208m");printf( _X_,##__VA_ARGS__); printf("\033[0m\n");fflush(stdout);

#define  Msg_cyanf(_X_,...)      \
         printf ("\033[38;5;14m");printf( _X_,##__VA_ARGS__); printf("\033[0m\n");fflush(stdout);

/* macros útiles */

#define  Break_if(_X_)        if( _X_ ) break;
#define  Continue_if(_X_)     if( _X_ ) continue;

#define  When(_X_)            if( _X_ )


/* stack para funciones GADGET de string */

/* inicia el trabajo con el stack */
#define  Stack       if( (PILA_GADGET = 1) )

/* finaliza el trabajo con el stack. La pila debe quedar en "0" */
#define  Stack_off   PILA_GADGET = 0; if(CONTADOR_PILA>=0){ Msg_red("Proceso termina con stack ocupado: borro sobrante\n");\
                                         CONTADOR_PILA=-1; }

/* la idea es revisar el argumento: si es NULL, debo revisar el stack 
   Si el stack es null, entonces, error. 
   STORE almacena el valor en la variable indicada, obtenido desde el
   stack. */
 
#define Store(_X_,_Y_)   \
 do{\
   _Y_;\
   if(PILA_GADGET){\
       if( CONTADOR_PILA>=0 ){\
           Let(_X_, pila_de_trabajo[CONTADOR_PILA]);CONTADOR_PILA--;\
       }\
   }else{ Msg_amber("Store: No hay datos en la pila");}\
 }while(0);

#define  Item_return_release(_X_) \
   if(PILA_GADGET){\
   push_stack_str(_X_);free(_X_);return NULL;\
   } return _X_;
   
#define  Item_return(_X_) \
   if(PILA_GADGET){\
   push_stack_str(_X_);return NULL;\
   } return _X_;

#define  Get_fn_or_stack(_X_,_Y_,_MSG_,_SUBMSG_)  \
     _X_ = _Y_;\
     if( _X_==NULL){\
         _X_ = pop_stack_hard(_MSG_,_SUBMSG_);\
     }


#define  Store_cat(_X_,_Y_) \
 do{\
   _Y_;\
   if(PILA_GADGET){\
       if( CONTADOR_PILA>=0 ){\
           _X_ = (char*)realloc( (void *)_X_,strlen(_X_) + strlen(pila_de_trabajo[CONTADOR_PILA]) + 1);\
           if(_X_) { strcat(_X_, pila_de_trabajo[CONTADOR_PILA]); }\
           else { Msg_red("Cat: No hay memoria para <"#_X_">(REALLOC)\n"); }\
           CONTADOR_PILA--;\
       }\
   }else{ Msg_amber("Store: No hay datos en la pila");}\
 }while(0);

/* define un stack de 16 posiciones */
#define  Init_stack \
   do{\
       pila_de_trabajo = ( char ** ) calloc( sizeof( char * ) * LIMITE_STACK_STR, 1 ); \
       if( pila_de_trabajo ) {\
          int i;\
          for( i=0 ; i < LIMITE_STACK_STR; i++){\
               * (pila_de_trabajo + i ) = (char *)calloc(2,1);\
               strcpy( * (pila_de_trabajo + i ), "" );\
          }\
       }else {\
          Msg_red("Init_stack : no hay memoria para stack de strings (CALLOC)\n");\
          exit(1);\
       }\
   }while(0);

/* TRY CATCH FYNALLY ENDTRY */

// NECESITA: #include <setjmp.h>
/*  Copyright (C) 2009-2015 Francesco Nidito */
/*#define Try              do{ jmp_buf ex_buf__; switch( setjmp(ex_buf__) ){ case 0: while(1){
#define Catch(_X_)       break; case _X_:
#define Finally          break; } default: {
#define End_try           break; } } }while(0);
#define Throw(_E_,_X_)   if( ( _E_ ) ) longjmp(ex_buf__, _X_ );
#define Raise(_X_)       longjmp(ex_buf__, _X_ );

// estas son definidas por el usuario:
#define NOT_ENOUGH_MEMORY (1)
// .... etc.
*/
/* STRINGS */

#define  Str_init(_V_)       char * _V_=NULL;
#define  Space(_N_)         (char*)calloc(( _N_+1 ), 1);

#define  New_char(_N_)         (char*)calloc(( _N_+1 ), 1);
#define  New_int(_N_)         (int*)calloc(( _N_+1 ), sizeof(int));

#define  Free_secure(_X_)    if(_X_) { free(_X_); _X_=NULL; }

#define  Let(_X_,_Y_)       if(_X_) free(_X_);\
                            _X_ = (char*)calloc( strlen(_Y_) + 1, 1);\
                            if(_X_) { strcpy(_X_, _Y_); }\
                            else { perror("\033[38;5;196mLet: No hay memoria para <"#_X_">(CALLOC)\n\033[0m"); }

#define  Copy(_X_,_Y_)      Let(_X_,_Y_)


#define  Set(_X_,_Y_)       char *_X_ = (char*)calloc( strlen(_Y_) + 1, 1);\
                            if(_X_) { strcpy(_X_, _Y_); }\
                            else { perror("\033[38;5;196mSet: No hay memoria para <"#_X_">(CALLOC)\n\033[0m"); }

#define  Cat(_X_,_Y_)       _X_ = (char*)realloc( (void *)_X_,strlen(_X_) + strlen(_Y_) + 1);\
                            if(_X_) { strcat(_X_, _Y_); }\
                            else { perror("\033[38;5;196mCat: No hay memoria para <"#_X_">(REALLOC)\n\033[0m"); }

/************************** SEARCH *****************************/
/* macros para obtener linea y desplazamiento de resuatdos SEARCH */
#define  Found_numline(_X_,_Y_)      _X_[_Y_][0]
#define  Found_offset(_X_,_Y_)       _X_[_Y_][1]

/*  int lenFounded = SIZE_SEARCH;
    ...
    FreeSearch( search, lenFounded ); */
#define  Free_search(_X_,_LEN_) \
   do{\
      int i;\
      for( i=0; i < _LEN_; ++i )\
          free(_X_[i]);\
      free(_X_);\
   }while(0);

#define  Search_lines(_X_)             Search(_X_,"-r $'\n'");

#define  For_each_founded(_X_,_LEN_)       for( _X_=0; _X_ < _LEN_; ++_X_ )
#define  For_each_rev_founded(_X_,_LEN_)   for( _X_=_LEN_-1; _X_ >=0 ; --_X_ )

/* posicionamiento de puntero de archivos */
#define  Get_pos(_X_)              lseek(_X_,0,SEEK_CUR);
//  SetPos devuelve un dato al stack: debe ser asignado:
#define  Set_pos(_X_,_P_)         lseek(_X_,_P_,SEEK_SET);
#define  Seek(_X_,_P_,_S_)        lseek(_X_,_P_,_S_);
#define  Set_max_readline(_X_)    MAX_LENGTH_READ=_X_;

// posicionan puntero de lectura-escritura en archivo abierto: no deben ser asignados
#define  Set_BOF(_FD_)            lseek(_FD_,0,SEEK_SET);
#define  Set_EOF(_FD_)            lseek(_FD_,0,SEEK_END);

/************************** REGEX ******************************/

// tope de compilaciones al hilo que se pueden hacer.
#define  TOPE_REGEX     20
#define  MAX_ERROR_MSG  0x1000

#define  R_NUMBERS    "^[+-]?([1-9][0-9]*\\.?[0-9]*([Ee][+-]?[0-9]+)|([0-9]+([.][0-9]*)?|[.][0-9]+))?$"
#define  R_EMAILS     "^[^@]+@[^@]+\\.[a-zA-Z]{2,}$"
#define  R_IPS        "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
#define  R_DATES      "^([0-2][0-9]|3[0-1])(\\/|-)(0[1-9]|1[0-2])\\2(\\d{4})$"
#define  R_TIMES      "^([01]?[0-9]|2[0-3]):[0-5][0-9](:[0-5][0-9])?$"
#define  R_URLS       "^(http|https|ftp|ftps)\\:\\/\\/[a-zA-Z0-9\\-\\.]+\\.[a-zA-Z]{2,3}(\\/\\S*)$"

/* cuando compila un regex, devuelve un entero. Si fue exitosa, el entero es positivo */
#define  Is_regex(_X_)    ( _X_ >= 0 )

/*  RE_MATCH match = ....
    int lenMatch = SIZE_MATCH;
    ....
    Free_match(match, lenMatch )*/
#define  Free_match(_X_,_LEN_) \
do{\
   int i; for( i=0; i < _LEN_; ++i )\
       free(_X_[i].match);\
   free(_X_);\
}while(0);

/* Ciclo for para recorrer los match encontrados por regex_match.
   _LEN_ == SIZE_MATCH 
   int j;
   For_each_match( j, SIZE_MATCH ) { ... } */
#define  For_each_match(_X_,_LEN_)   for( _X_=0; _X_ < (_LEN_); ++_X_ )
#define  For_each_reverse_match(_X_,_LEN_)   for( _X_=(_LEN_)-1; _X_ >= 0; --_X_ )

/**************************************************************/

/**************** TOKEN **********************/

/* iteracion por tokens */
#define  For_each_token( _V_INDEX_, _STR_ )  do{\
                                               char * _V_INDEX_;\
                                               int _V_INDEX_##_TT_ = Count_tokens( _STR_ ), _V_INDEX_##_I_;\
                                               for(_V_INDEX_##_I_=1; _V_INDEX_##_I_<=_V_INDEX_##_TT_;++_V_INDEX_##_I_){\
                                                   _V_INDEX_ = (char *) Get_token( _STR_, (int) _V_INDEX_##_I_ );

#define  Continue_next_token(_V_INDEX_)        free(_V_INDEX_);continue;
#define  Break_token(_V_INDEX_)                free(_V_INDEX_);break;
#define  Next_token(_V_INDEX_)                 free(_V_INDEX_); }} while(0);

/*********************************************/
/******************** STATFILE *******************/
#define  Free_stat(_X_)       free(_X_);

/********************* PARSER ***************************/
#define ONLY_TAG  1
#define NORMAL_TAG 0

#define  Free_tag(_X_) \
  do{\
     if(_X_.content) free(_X_.content);\
     int i;\
     for(i=0; i<_X_.len;i++) {\
         if(_X_.attrib[i]) free(_X_.attrib[i]);\
         if(_X_.name[i])   free(_X_.name[i]);\
     }\
     if(_X_.attrib) free(_X_.attrib);\
     if(_X_.name)  free(_X_.name);\
  }while(0);

#define Parse_void(_X_,_A_)     Parser( _X_,_A_,"",ONLY_TAG)

/********** FUNCIONES CON FORMATO *****************/
#define  Letf(_X_,format,...) \
               do{\
                 Is_ok=1;\
                 char * formato = (char *)calloc(1024,1);\
                 if(formato) {\
                     sprintf( formato, format,##__VA_ARGS__);\
                     if(_X_) free(_X_);\
                     _X_ = (char*)calloc( strlen(formato) + 1, 1);\
                     if(_X_) { strcpy(_X_, formato); Free_secure(formato); }\
                        else { Msg_red("Letf : No hay memoria para <"#_X_">(calloc)\n");\
                               _X_ = NULL; Is_ok=0; }\
                 }else {Msg_red("Letf : No hay memoria para 'calloc'\n"); Is_ok=0;}\
               }while(0);

#define  Setf(_X_,format,...)   \
               char *_X_ = NULL;\
               do{\
                   Is_ok=1;\
                   char * formato = (char *)calloc(1024,1);\
                   if(formato) {\
                       sprintf( formato, format,##__VA_ARGS__);\
                       _X_ = (char*)calloc( strlen(formato) + 1, 1);\
                       if(_X_) { strcpy(_X_, formato); Free_secure(formato); }\
                          else { Msg_red("Setf : No hay memoria para <"#_X_">(calloc)\n"); Is_ok=0;}\
                   }else {Msg_red("Setf : No hay memoria para 'calloc'\n");Is_ok=0;}\
               }while(0);

#define  Catf(_X_,format,...) \
               do{\
                 Is_ok=1;\
                 char * formato = (char *)calloc(1024,1);\
                 if(formato) {\
                     sprintf( formato, format,##__VA_ARGS__);\
                     _X_ = (char*)realloc( (void *)_X_,strlen(_X_) + strlen(formato) + 1);\
                     if(_X_) { strcat(_X_, formato); Free_secure(formato); }\
                     else {Msg_red("Catf : No hay memoria para (CALLOC)\n"); Is_ok=0;}\
                 }else { Msg_red("Catf : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0;}\
               }while(0);

/* GET_SYS con formato */
#define  Get_sysf(_X_,format,...)\
              do{\
                 char * ___formato___ = (char *)calloc(1024,1);\
                 if(___formato___) {\
                     sprintf( ___formato___, format,##__VA_ARGS__);\
                     if(_X_) free(_X_); _X_=NULL;\
                     _X_ = Get_sys(___formato___);Free_secure(___formato___);\
                 } else { Msg_red("Get_sysf : No hay memoria para 'calloc'\n"); }\
              }while(0);

/* semejante a SPRINTF, solo que no hay que declarar variable temporal para format */
#define  Format(_X_, ... ) \
              do{\
                  char *tmp=NULL;\
                  if( ( tmp=(char *)calloc(MAX_LENGTH_READ,1) ) ){\
                      sprintf(tmp, ##__VA_ARGS__);\
                      Let( _X_, tmp); free(tmp);\
                  }else{ Let( _X_, "<ERROR-FORMAT>");\
                         Msg_red("Format : no hay memoria para <" #_X_ ">\n");}\
              }while(0);
                                     
/* ASIGNAR/CONCATENAR EL RESULTADO DE UNA FUNCION STRING A UNA VARIABLE */
#define   Fn_cat( _X_, _Y_ )    Get_fn_cat( _X_, _Y_ )
#define   Get_fn_cat( _X_, _Y_ ) \
               do{\
                   char * __tmp__=NULL;\
                   __tmp__ = _Y_;\
                   if(__tmp__){ Cat( _X_, __tmp__ ); free(__tmp__);}\
               }while(0);

#define   Fn_let(_X_,_Y_)   Get_fn_let( _X_, _Y_ )
#define   Get_fn_let( _X_, _Y_ ) \
               do{\
                   char * __tmp__=NULL;\
                   __tmp__ = _Y_;\
                   if(__tmp__){ Let( _X_, __tmp__ ); free(__tmp__);}\
               }while(0);

/**************************************************/
/* STRAT */
// sacado de Harbour project:
/* Some common character constants */

#define X_CHAR_NUL             '\0'    /*   0 - NUL */
#define X_CHAR_EOS             X_CHAR_NUL
#define X_CHAR_BEL             '\a'    /*   7 - Bell */
#define X_CHAR_BS              '\b'    /*   8 - Backspace */
#define X_CHAR_HT              '\t'    /*   9 - Tab horizontal */
#define X_CHAR_LF              '\n'    /*  10 - Linefeed */
#define X_CHAR_VT              '\v'    /*  11 - Tab vertical */
#define X_CHAR_FF              '\f'    /*  12 - Formfeed */
#define X_CHAR_CR              '\r'    /*  13 - Carriage return */
#define X_CHAR_EOF             '\x1A'  /*  26 - End of file marker */

/* Harbour specific character constants */

#define X_CHAR_HARD1           X_CHAR_CR
#define X_CHAR_HARD2           X_CHAR_LF

#define X_CHAR_SOFT1           '\x8D'  /* 141 */
#define X_CHAR_SOFT2           X_CHAR_LF

#define X_ISUPPER( c )         ( ( c ) >= 'A' && ( c ) <= 'Z' )
#define X_ISLOWER( c )         ( ( c ) >= 'a' && ( c ) <= 'z' )
#define X_TOUPPER( c )         ( ( c ) >= 'a' && ( c ) <= 'z' ? ( c ) - ( 'a' - 'A' ) : ( c ) )
#define X_TOLOWER( c )         ( ( c ) >= 'A' && ( c ) <= 'Z' ? ( c ) + ( 'a' - 'A' ) : ( c ) )
#define X_ISDIGIT( c )         ( ( c ) >= '0' && ( c ) <= '9' )
#define X_ISALPHA( c )         ( X_ISUPPER( c ) || X_ISLOWER( c ) )
#define X_ISALNUM( c )         ( X_ISALPHA( c ) || X_ISDIGIT( c ) )
#define X_ISXDIGIT( c )        ( X_ISDIGIT(c) || \
                                  ( (c) >= 'A' && (c) <= 'F' ) || \
                                  ( (c) >= 'a' && (c) <= 'f' ) )
#define X_ISSPACE( c )         ( ( c ) == ' ' || \
                                  ( c ) == X_CHAR_HT || \
                                  ( c ) == X_CHAR_LF || \
                                  ( c ) == X_CHAR_CR )
/* conversiones */
#define X_DEFAULT_WIDTH      255
#define X_FALSE              0
#define X_TRUE               1
#define X_DBL_LENGTH( d )    ( ( (d) > 9999999999.0 || (d) < -999999999.0 ) ? 20 : 10 )
#define X_LONG_LENGTH( l )   ( ( (l) < -999999999 ) ? 20 : 10 )

/* set lenguaje para calendario */
#define SP     0
#define EN     1
#define FR     2
#define GR     3
#define IT     4


/***************** DECLARACIONES DE MAIN Y FUNCIONES ********************/

#define  LIB_GADGET_START   \
        struct termios __ORIGINAL_TERMIOS__;\
        char * __TOKEN__;\
        int SIZE_TERM_ROWS=20, SIZE_TERM_COLS=80;\
        int VID_ACTUAL_ROW=0, VID_ACTUAL_COL=0;\
        int __aIndexREGEX__=-1;\
        regex_t __aREGEX__[20];\
        int __validREGEX__[20];\
        int MULTIPASS=0;\
        int SIZE_MATCH=0;\
        int ACTIVE_TAB=0;\
        int ACTIVE_OPT=0;\
        long SIZE_SEARCH=0;\
        int ACTUAL_LANG_DATE=0;\
        int FIRST_MONDAY=0;\
        int ACTUAL_DATE_FORMAT=0;\
        int DEC_PREC=0;\
        int SET_DBL_NOT=0;\
        int SIZE_BINARY=0;\
        int DECIMAL_POINT=46;\
        int MAX_LENGTH_READ=512;\
        int TYPED_STRING=0;\
        int LEN_TYPED_STRING=0;\
        int SEPARATOR_MILLARS=44;\
        int PILA_GADGET=0,CONTADOR_PILA=-1;\
        int SCREEN_ROW=1, SCREEN_COL=1;\
        int MOUSE_EVENT=0,MPOS_ROW=0, MPOS_COL=0;\
        int ENABLE_MOUSE_DRIVER=0;\
        int BYTES_WAITING=0;\
        int SIZE_LINSPACED;\
        int SIZE_SEQUENCE;\
        int ENABLE_RAW_MODE=0;\
        int GLOBAL_ARR_ROWS=0, GLOBAL_ARR_COLS=0,GLOBAL_ARR_PAGS=0,GLOBAL_ARR_BOOKS=0,GLOBAL_ARR_DIM=0;\
        int Is_ok=1;\
        char ** pila_de_trabajo;   

#define Main  \
        int main(int argc, char* argv[]){\
            __TOKEN__=NULL;\
            Init_token();\
            Init_stack;

/* OBTIENE ARGUMENTOS DESDE EL COMMAND LINE */
#define Get_arg_str(_X_,_N_)   Str_init(_X_); if( argc > (_N_) ) { Let(_X_,argv[(_N_)]) } else{\
                               Msg_red("Get_arg_str : no se ha recibido el argumento esperado para <"#_X_">"); Stop(1);}
#define Get_arg_int(_X_,_N_)   int _X_; if( argc > (_N_) ) { _X_ = Str2int(argv[(_N_)]); } else{\
                               Msg_red("Get_arg_int : no se ha recibido el argumento esperado para <"#_X_">"); Stop(1);}
#define Get_arg_long(_X_,_N_)   long _X_; if( argc > (_N_) ) { _X_ = Str2lng(argv[(_N_)]); } else{\
                                Msg_red("Get_arg_int : no se ha recibido el argumento esperado para <"#_X_">"); Stop(1);}
#define Get_arg_float(_X_,_N_)    float _X_; if( argc > (_N_) ) { _X_ = Str2flt(argv[(_N_)]); } else{\
                                  Msg_red("Get_arg_float : no se ha recibido el argumento esperado para <"#_X_">"); Stop(1);}
#define Get_arg_double(_X_,_N_)   double _X_; if( argc > (_N_) ) { _X_ = Str2dbl(argv[(_N_)]); } else{\
                                  Msg_red("Get_arg_double : no se ha recibido el argumento esperado para <"#_X_">"); Stop(1);}

#define Arg_count            argc

/* salto simple de línea */
#define  Prnl                   putchar('\n');

#define  Free_stack_str \
                         if( pila_de_trabajo ){\
                         do{ \
                             int i; \
                             for(i=0; i<LIMITE_STACK_STR;i++){\
                                if(pila_de_trabajo[ i ] )\
                                   free( pila_de_trabajo[ i ] ); \
                             }\
                             free( pila_de_trabajo );\
                         }while(0);\
                         }

#define  Reinit_stack \
     Free_stack_str;\
     Init_stack;

/* DETENERSE EN CUALQUIER PARTE DEL PROGRAMA */
#define Stop(_N_)        End_token(); Free_stack_str; \
                         exit(_N_);

/* SALIDA NORMAL */
#define End              End_token(); \
                         Free_stack_str;\
                         return(0); }

/* SALIDA CON UN VALOR DE RETORNO */
#define Return(_N_)      End_token(); \
                         Free_stack_str;\
                         return(_N_); }

/********************** FUNCIONES STRING BASICAS **********************/
#define   Trim(_X_)           __Alltrim__(_X_) //,strlen(_X_))
#define   Trim_r(_X_)         __Rtrim__(_X_) //,strlen(_X_))
#define   Trim_l(_X_)         __Ltrim__(_X_) //,strlen(_X_))
#define   Adjust(_X_,_N_)     Get_fn_let(_X_, Sub_str(_X_,1,_N_));

/* PAD */
/* definiciones para PAD */
#define   PADC    0
#define   PADR    1
#define   PADL    2

#define   Pad_c(_V_,_R_,_L_)   __Pad__(_V_,_R_,_L_,PADC)
#define   Pad_r(_V_,_R_,_L_)   __Pad__(_V_,_R_,_L_,PADR)
#define   Pad_l(_V_,_R_,_L_)   __Pad__(_V_,_R_,_L_,PADL)

/* Lateral_replace */
#define   LEFTREPL     54
#define   RIGHTREPL    55
#define   Lateral_replace_r(_V_,_W_,_X_)  Lateral_replace(_V_,_W_,_X_,RIGHTREPL)
#define   Lateral_replace_l(_V_,_W_,_X_)  Lateral_replace(_V_,_W_,_X_,LEFTREPL)

/* ve si un substring está contenido en otro */
#define   Exact_occurs(_X_,_Y_)     __Strat__( _X_, strlen(_X_), _Y_, strlen(_Y_), 1 )
#define   Occurs(_X_,_Y_)           __Strat__( _X_, strlen(_X_), _Y_, strlen(_Y_), 0 )

/* define COUNT_AT */
#define   Set_multipass    MULTIPASS=1;
#define   Unset_multipass  MULTIPASS=0;

/* definicion para finalizar MULTICAT y MULTILET */
#define   ENDCAT       NULL
#define   ENDCPY       NULL

/* Conversion string -> numeros xx_MONEY */
#define   Decimal_point(_X_)      DECIMAL_POINT=( int ) _X_;
#define   Separator_millars(_X_)  SEPARATOR_MILLARS=( int ) _X_;

/* Otras macros útiles*/
#define   Is_equal_str(_X_,_Y_)   ( ( *_X_ ) && ( strcmp(_X_,_Y_)==0 ) )

/* establece decimales para conversión:
   Int2str, Lng2str, Flt2str y Dbl2str */
#define   Set_decimal(_X_)        DEC_PREC=_X_;

/* ALGUNAS MACROS SEMANTICAS breves */
#define Out_uint(_F_)   unsigned int  ___TempValue___ = _F_,___swOut___=0;
#define Out_int(_F_)   int  ___TempValue___ = _F_,___swOut___=0;
#define Out_flt(_F_)   float  ___TempValue___ = _F_,___swOut___=0;
#define Out_ulng(_F_)   unsigned long  ___TempValue___ = _F_,___swOut___=0;
#define Out_lng(_F_)   long  ___TempValue___ = _F_,___swOut___=0;
#define Out_dbl(_F_)   double  ___TempValue___ = _F_,___swOut___=0;
#define Out_str(_F_)   char * ___TempValue___ = _F_,___swOut___=1;

#define Block( _X_, _E_) \
   do{\
      _E_\
      if( !___swOut___ ) {_X_ =  ___TempValue___;}\
      else {Msg_red("Block: se devuelve un tipo no esperado");}\
   }while(0);

#define sBlock(_X_, _E_)     Block_string( _X_, _E_)
#define Block_string( _X_, _E_) \
   do{\
      _E_\
      if( ___swOut___ ) {\
          Let(_X_,___TempValue___);Free_secure(___TempValue___);\
      }else{Msg_red("Block_string: se devuelve un tipo no esperado");}\
   }while(0);
   
#define Where(_X_)  _X_
#define Then(_X_)   _X_
#define Do_it(_X_,_Y_,_Z_)  _Y_;\
                            _Z_;\
                            _X_;

#define Throw(_X_)       if( !Is_ok ) { goto _X_; }
#define Exception(_H_)   _H_: if( !Is_ok++ )
#define Assert(_X_,_Y_)  if( !(_X_) ) { Is_ok=0; goto _Y_; }

#define STK_STR   pila_de_trabajo[CONTADOR_PILA]

/*******************************************************************************/




/* IMPORTANTE! declarar antes del trabajo con TOKENS */
/* establece separador inicial de token por defecto: coma */
void Init_token();

/* IMPORTANTE! declarar después del trabajo con TOKENS */
/* libera __TOKEN__ de memoria */
void End_token();

/* establece un nuevo separador de token */
void Set_token_sep(char);
/* establece nuevo separador y devuelve el anterior */
char Set_new_sep(char);

/* obtiene el separador de token activo */
char Get_token_sep();

/* obtiene el total de tokens en un string clásico */
int Count_tokens( char *);

/* obtiene el token indicado */
char * Get_token( char * cTXT, int nToken );
/* modifica un token: devuelve la nueva cadena con el token modificado 
   Ejemplo:
    char * cadena=NULL;
    Let(cadena, "María tenía un corderito blanco")
    char * nuevo = (char *) ModToken(cadena, "negro", 5);
    Let(cadena, nuevo );
    puts( cadena );
    free(nuevo);
    free(cadena);
        
    Salida: "María tenía un corderito negro"
   
   */
char * Mod_token( char * cTXT, const char * cTOK, int nToken );

/* swap de tokens */
char * Swap_tokens(char * cTXT, int nToken1, int nToken2);

/* igual que CUT y CUTR, pero omiten el caracter */
char * First_cut( char * pStringBuff, char pCh );
char * Last_cut( char * pStringBuff, char pCh );

/* CUT y RCUT */
char * Cut( char * pString, char pCh );
char * Cutr( char * pString, char pCh );

/* MULTI CAT w = MultiCat(w,b,c,d...,NULL) */
/*
AJ: 2004-02-23
Concatenates multiple strings into a single result.
Eg. hb_xstrcat (buffer, "A", "B", NULL) stores "AB" in buffer.
*/
char * Multi_cat( char * szDest, const char * szSrc, ... );
/* COPY w = MultiCopy(w,"hola","mundo",NULL) */
char * Multi_copy( char * szDest, const char * szSrc, ... );

/*  UPPER */
char * Upper( const char * cText );

/*  LOWER */
char * Lower( const char * cText );

/* REVERSE STRING */
char * Reverse( const char* cString );

/*  PARSER UNPARSER 
    Necesita NORMAL_TAG o ONLY_TAG en int
    Se definen Free_tag() para liberar resultado de Unparser()
    y Parse_void() para generar campo vacío */
char * Parser( const char*, const char*, const char* , int );
ST_GETTAG Unparser( char **, char* );

/* TRIMS */                                   
char * __Rtrim__(const char *linea);
char * __Ltrim__(const char *linea);
char * __Alltrim__( const char *linea);


/* Capitalize an string */
char * Capital( const char* sBuffer );

/* PAD 
   tCompare es un valor entre 0 y 2 que indica orientación del relleno:
   char * v = Pad( v, ' ', 100, 0 )
*/
char * __Pad__( char * cTXT, char cPad, int nLen, int tCompare );

/* REPLICATE un string */
char * Replicate( char * szText, int nTimes);

/* SUBSTR */
char * Substr( char * Texto, long nPos, long nLen );
char * Left( char * cTXT, long nLen );
char * Right( char * cTXT, long nPos );

/* DEVUELVEN UN RESULTADO NUMERICO - POSICION */

size_t Str_len( const char * cString );

/* Harbour Project source code:
 *   internal and switch functions for CT3 string functions
 *
 * Copyright 2001 IntTec GmbH, Neunlindenstr 32, 79106 Freiburg, Germany
 *        Author: Martin Vogel <vogel@inttec.de>
 */
 
/* STRAT encuentra un substring dentro de otro. Acepta caracteres españoles */
long __Strat__( const char * szSub, long nSubLen, const char * szText, long nLen, short tCompare );
long Str_at( const char * szSub, const char * cTXT );
long Str_iat( const char * szSub, const char * cTXT );

/* STRTRAN */

/* -------------------------- */
/* search for exact substring */
/* -------------------------- */

/* ------------------------------------------------ */
/* search for exact substring in backward direction */
/* ------------------------------------------------ */
const char *ct_at_exact_backward( const char * pcString, long sStrLen,
                                  const char * pcMatch, long sMatchLen, long * psMatchStrLen );

const char *ct_at_exact_forward( const char * pcString, long sStrLen,
                                 const char * pcMatch, long sMatchLen, long * psMatchStrLen );

/* STUFF*/
/*
 * $Id: stuff.c 16043 2011-01-13 09:44:53Z druzus $
 */

/*
 * Harbour Project source code:
 * STUFF() function
 *
 * Copyright 1999 Antonio Linares <alinares@fivetech.com>
 * www - http://harbour-project.org*/
/*
   reemplazar: nDel > 0
   insert: nDel=0
   delete:  nDel>0
   index_at

*/
char * __stuff_item__( char * pString2, const char * pString1, long nPos, long nDel );
char * Insert( const char * pString1, const char * pString2, long nPos );
char * Delete( const char * pString1, long nPos, long nDel );
char * Replace( const char * pString1, const char * pString2, long nPos, long nDel );

/* devuelve la posicion de un substring. nCounter > 0 indica desde donde debe considerar
   lo buscado; nCounter==0 busca desde atrás */
int Index_at( const char * pcString, const char * pcStringToMatch, long nCounter );

/* cuenta cuántas ocurrencias existen del substring */
int Str_count_at( const char * pcString, const char * pcStringToMatch, long sIgnore );

/* transforma el texto */
char * __strtran_item__( const char * szText, const char * szSeek, const char * szReplace, long nInicio, long nCuenta );
// funciones que llaman a la de arriba:
char * Str_tran( const char * szText, const char * szSeek, const char * szReplace );
char * Str_tran_first( const char * szText, const char * szSeek, const char * szReplace );
/*#defn    TRAN-LAST(_S_,_R_,_X_)              #RAND;___VTRNL___#RNDV=0;___REPL_TXT_=0;#ATOM#CMPLX;mov(___REPL_TXT_);\
                                             ___FIND_LAST_=0;#ATOM#CMPLX;mov(___FIND_LAST_);___AT_LAST_=0;\
                                             {___FIND_LAST_};#ATOM#CMPLX;cpy(___VTRNL___#RNDV);countat;mov(___AT_LAST_);\
                                             {___AT_LAST_}{___REPL_TXT_}{___FIND_LAST_}{___VTRNL___#RNDV}transform;%RAND;*/
char * Str_tran_last( const char * szText, const char * szSeek, const char * szReplace );
char * Str_tran_to( const char * szText, const char * szSeek, const char * szReplace, long nInicio );
char * Str_tran_all( const char * szText, const char * szSeek, const char * szReplace, long nInicio );
char * Str_tran_from_to( const char * szText, const char * szSeek, const char * szReplace, long nInicio, long nCuenta );

/* GESTION DE CARACTERES EN UN STRING */
// al inicio o al final, devuelve la posición donde cambia un caracter
//int __PosChar__( const char * cString, char cCar, int Direccion );
int Char_posl( const char * cString, char cCar );
int Char_posr( const char * cString, char cCar );

/* * Copyright 2001 IntTec GmbH, Neunlindenstr 32, 79106 Freiburg, Germany
   *        Author: Martin Vogel <vogel@inttec.de> funciones CHAR
   */
// reduce los carcateres dupicados adyacentes en un solo string.
char * Char_one( const char * pcString, const char * pcDeleteSet );

// borra todos los carcateres de STR1 que no estén incluidos en STR2
char * Char_only( const char *pcString, const char *pcOnlySet );

// remueve caracteres desde STR1 indicados en STR2
char * Char_del( const char *pcString, const char *pcOnlySet );

/* reemplaza caracteres de los laterales */
char * Lateral_replace( const char * pcString, char cSearch, char cReplace, int iSwitch );

/* MASK Y MONEY */
char * Str_mask( const char * numero, const char * formato, char * car );

/* STRMONEY y FORMATMONEY */
char * Str_money(long double numero, int decimales );
char * Format_money( long double numero, int decimales, int nPad, char relleno, const char * sufijo );

/* REGEX - EXPRESIONES REGULARES */
int Regex_compile( const char* cPattern, int nFlags );
void Regex_free( int nIndex );
int Regex_valid( const char* test_pattern, int nIndex, int nFlags );
RE_MATCH * Regex_match( const char* to_match, int nIndex, int n_matches, int nFlags );


/*******************************************************************************************

                 ARRAYS
 *******************************************************************************************/

/* argumentos variables en preprocesador 

   René Nyffenegger, 2018 */
#define ELEVENTH_ARGUMENT(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define COUNT_ARGUMENTS(...) ELEVENTH_ARGUMENT(dummy, ## __VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define CONCAT(a, b)  a##b
#define CONCAT2(a, b) CONCAT(a, b)

/* acceso a celdas con puntero 
   Si se van a anidar, no use "$var[]" ni "Cell" ni "pCell", sino "Cell1", "pCell2", etc., directamente,
   porque el proceso CONCAT2 no permite que el preprocesador de C detecte el anidamiento */

#define pCell(_X_, ...) CONCAT2(pCell, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell1(_X_,ARG1)              _X_[ ( ARG1 ) ]
#define pCell2(_X_,ARG1,ARG2)         _X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ]
#define pCell3(_X_,ARG1,ARG2,ARG3)    _X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + ( ARG3 ) * ( (_X_##_data->cols) * (_X_##_data->rows) ) ]
#define pCell4(_X_,ARG1,ARG2,ARG3,ARG4) \
        _X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + (( ARG3 ) * ( (_X_##_data->cols) * (_X_##_data->rows) )) + (( ARG4 ) * ( (_X_##_data->cols) * (_X_##_data->rows) * _X_##_data->pags)) ]

/* acceso a celdas sin puntero */
#define Cell(_X_, ...) CONCAT2(Cell, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell1(_X_,ARG1)              _X_[ ( ARG1 ) ]
#define Cell2(_X_,ARG1,ARG2)         _X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ]
#define Cell3(_X_,ARG1,ARG2,ARG3)    _X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + ( ARG3 ) * ( (_X_##_data.cols) * (_X_##_data.rows) ) ]

#define Cell4(_X_,ARG1,ARG2,ARG3,ARG4) \
        _X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + (( ARG3 ) * ( (_X_##_data.cols) * (_X_##_data.rows) )) + (( ARG4 ) * ( (_X_##_data.cols) * (_X_##_data.rows) * _X_##_data.pags )) ]

/*
#define Cell5(_X_,ARG1,ARG2,ARG3,ARG4,ARG5) \
        _X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + (( ARG3 ) * ( (_X_##_data.cols) * (_X_##_data.rows) )) + (( ARG4 ) * ( (_X_##_data.cols) * (_X_##_data.rows) )) + (( ARG5 ) * ( (_X_##_data.cols) * (_X_##_data.rows) )) ]

// Etcétera...
*/
/* acceso a celdas sin puntero */
#define Node(_X_, ...) CONCAT2(Node, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Node2(_X_,_I_,_J_)   ( _I_ ) * ( _X_##_data.cols ) + ( _J_ )
#define Node3(_X_,_I_,_J_,_K_)   ( ( _I_ ) * ( _X_##_data.cols ) + ( _J_ ) ) + ( _K_ ) * ( (_X_##_data.cols) * (_X_##_data.rows) )
#define Node4(_X_,_I_,_J_,_K_,_L_) \
        ( ( _I_ ) * ( _X_##_data.cols ) + ( _J_ ) ) + (( _K_ ) * ( (_X_##_data.cols) * (_X_##_data.rows) )) + (( _L_ ) * ( (_X_##_data.cols) * (_X_##_data.rows) * _X_##_data.pags ))

/* acceso a celdas con puntero */
#define pNode(_X_, ...) CONCAT2(pNode, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pNode2(_X_,_I_,_J_)   ( _I_ ) * ( _X_##_data->cols ) + ( _J_ )
#define pNode3(_X_,_I_,_J_,_K_)   ( ( _I_ ) * ( _X_##_data->cols ) + ( _J_ ) ) + ( _K_ ) * ( (_X_##_data->cols) * (_X_##_data->rows) )
#define pNode4(_X_,_I_,_J_,_K_,_L_) \
        ( ( _I_ ) * ( _X_##_data->cols ) + ( _J_ ) ) + (( _K_ ) * ( (_X_##_data->cols) * (_X_##_data->rows) )) + (( _L_ ) * ( (_X_##_data->cols) * (_X_##_data->rows) * _X_##_data->pags ))


/* RANGOS para acceso iterado */
#define Range_for(_X_, ...)  CONCAT2(Range_for, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

/* para un array 1D */
#define Range_for3(_X_,A1,A2,A3)  \
        _X_##_data.rowi=A1;_X_##_data.rowinc=A2;_X_##_data.rowe=A3;

/* para un array 2D */
#define Range_for6(_X_,A1,A2,A3,B1,B2,B3) \
        _X_##_data.rowi=A1;_X_##_data.rowinc=A2;_X_##_data.rowe=A3; \
        _X_##_data.coli=B1;_X_##_data.colinc=B2;_X_##_data.cole=B3; 

/* para un array 3D */
#define Range_for9(_X_,A1,A2,A3,B1,B2,B3,C1,C2,C3) \
        _X_##_data.rowi=A1;_X_##_data.rowinc=A2;_X_##_data.rowe=A3; \
        _X_##_data.coli=B1;_X_##_data.colinc=B2;_X_##_data.cole=B3; \
        _X_##_data.pagi=C1;_X_##_data.paginc=C2;_X_##_data.page=C3;

/* para un array 4D */
#define Range_book_for(_X_,A1,A2,A3) \
        _X_##_data.booki=A1;_X_##_data.bookinc=A2;_X_##_data.booke=A3; 

/* establece como rango local los rangos completos del array */
#define All_range_for(_X_) \
        Is_ok=1;\
        switch (_X_##_data.dims){\
           case 1: _X_##_data.rowi=0;_X_##_data.rowinc=1;_X_##_data.rowe=_X_##_data.rows; break; \
           case 2: _X_##_data.rowi=0;_X_##_data.rowinc=1;_X_##_data.rowe=_X_##_data.rows; \
                   _X_##_data.coli=0;_X_##_data.colinc=1;_X_##_data.cole=_X_##_data.cols; break; \
           case 3: _X_##_data.rowi=0;_X_##_data.rowinc=1;_X_##_data.rowe=_X_##_data.rows; \
                   _X_##_data.coli=0;_X_##_data.colinc=1;_X_##_data.cole=_X_##_data.cols; \
                   _X_##_data.pagi=0;_X_##_data.paginc=1;_X_##_data.page=_X_##_data.pags; break; \
           case 4: _X_##_data.rowi=0;_X_##_data.rowinc=1;_X_##_data.rowe=_X_##_data.rows; \
                   _X_##_data.coli=0;_X_##_data.colinc=1;_X_##_data.cole=_X_##_data.cols; \
                   _X_##_data.pagi=0;_X_##_data.paginc=1;_X_##_data.page=_X_##_data.pags; \
                   _X_##_data.booki=0;_X_##_data.bookinc=1;_X_##_data.booke=_X_##_data.books; break; \
           default: {\
                   Msg_red("All_range_for : Dimensión fuera de rango.\n");\
                   Msg_red("Si lo desea, añada una nueva dimensión\n");\
                   Is_ok=0;\
           }\
        }

/* RANGOS para acceso iterado cuando se está usando paso por referencia */
#define Range_for_ptr(_X_, ...)  CONCAT2(Range_for_ptr, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

/* para un array 1D */
#define Range_for_ptr3(_X_,A1,A2,A3)  \
        _X_##_data->rowi=A1;_X_##_data->rowinc=A2;_X_##_data->rowe=A3;

/* para un array 2D */
#define Range_for_ptr6(_X_,A1,A2,A3,B1,B2,B3) \
        _X_##_data->rowi=A1;_X_##_data->rowinc=A2;_X_##_data->rowe=A3; \
        _X_##_data->coli=B1;_X_##_data->colinc=B2;_X_##_data->cole=B3; 

/* para un array 3D */
#define Range_for_ptr9(_X_,A1,A2,A3,B1,B2,B3,C1,C2,C3) \
        _X_##_data->rowi=A1;_X_##_data->rowinc=A2;_X_##_data->rowe=A3; \
        _X_##_data->coli=B1;_X_##_data->colinc=B2;_X_##_data->cole=B3; \
        _X_##_data->pagi=C1;_X_##_data->paginc=C2;_X_##_data->page=C3;

/* para un array 4D */
#define Range_book_for_ptr(_X_,A1,A2,A3) \
        _X_##_data->booki=A1;_X_##_data->bookinc=A2;_X_##_data->booke=A3; 

/* establece como rango local los rangos completos del array */
#define All_range_for_ptr(_X_) \
        Is_ok=1;\
        switch (_X_##_data.dims){\
           case 1: _X_##_data->rowi=0;_X_##_data->rowinc=1;_X_##_data->rowe=_X_##_data->rows; break; \
           case 2: _X_##_data->rowi=0;_X_##_data->rowinc=1;_X_##_data->rowe=_X_##_data->rows; \
                   _X_##_data->coli=0;_X_##_data->colinc=1;_X_##_data->cole=_X_##_data->cols; break; \
           case 3: _X_##_data->rowi=0;_X_##_data->rowinc=1;_X_##_data->rowe=_X_##_data->rows; \
                   _X_##_data->coli=0;_X_##_data->colinc=1;_X_##_data->cole=_X_##_data->cols; \
                   _X_##_data->pagi=0;_X_##_data->paginc=1;_X_##_data->page=_X_##_data->pags; break; \
           case 4: _X_##_data->rowi=0;_X_##_data->rowinc=1;_X_##_data->rowe=_X_##_data->rows; \
                   _X_##_data->coli=0;_X_##_data->colinc=1;_X_##_data->cole=_X_##_data->cols; \
                   _X_##_data->pagi=0;_X_##_data->paginc=1;_X_##_data->page=_X_##_data->pags; \
                   _X_##_data->booki=0;_X_##_data->bookinc=1;_X_##_data->booke=_X_##_data->books; break; \
           default: {\
                   Msg_red("All_range_for_ptr : Dimensión fuera de rango.");\
                   Msg_red("\nSi lo desea, añada una nueva dimensión\n");\
                   Is_ok=0;\
           }\
        }

/*********************************************
             ARRAYS DIMENSIONADOS
 *********************************************/

/* Se usan las macros ya hechas para arrays simples.
   Se puede liberar con FreeArray() y FreeStrArray() */
#define int_INIT_VAL        0
#define long_INIT_VAL      0L
#define float_INIT_VAL     0.0
#define double_INIT_VAL    0.0
#define nan_INIT_VAL       nan

/* establece las dimensiones del nuevo array */
#define Dim( ... ) CONCAT2(Dim, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__)

#define Dim1(ARG1)            GLOBAL_ARR_ROWS=ARG1; GLOBAL_ARR_COLS=0; GLOBAL_ARR_PAGS=0;\
                              GLOBAL_ARR_BOOKS=0; GLOBAL_ARR_DIM=1;
#define Dim2(ARG1,ARG2)       GLOBAL_ARR_ROWS=ARG1; GLOBAL_ARR_COLS=ARG2; GLOBAL_ARR_PAGS=0;\
                              GLOBAL_ARR_BOOKS=0; GLOBAL_ARR_DIM=2;
#define Dim3(ARG1,ARG2,ARG3)  GLOBAL_ARR_ROWS=ARG1; GLOBAL_ARR_COLS=ARG2; GLOBAL_ARR_PAGS=ARG3;\
                              GLOBAL_ARR_BOOKS=0; GLOBAL_ARR_DIM=3;
#define Dim4(ARG1,ARG2,ARG3,ARG4) \
                              GLOBAL_ARR_ROWS=ARG1; GLOBAL_ARR_COLS=ARG2; GLOBAL_ARR_PAGS=ARG3;\
                              GLOBAL_ARR_BOOKS=ARG4; GLOBAL_ARR_DIM=4;
                              
/* macros de definici{on del array con metadata DS_ARRAY */
#define Define_Global_Array(_X_) \
        DS_ARRAY  _X_##_data;\
        _X_##_data.rows = GLOBAL_ARR_ROWS ;\
        _X_##_data.cols = GLOBAL_ARR_COLS ;\
        _X_##_data.pags = GLOBAL_ARR_PAGS ;\
        _X_##_data.books = GLOBAL_ARR_BOOKS ;\
        _X_##_data.dims = GLOBAL_ARR_DIM;\
        _X_##_data.len = ( GLOBAL_ARR_ROWS ? GLOBAL_ARR_ROWS : 1 )\
                             * ( GLOBAL_ARR_COLS ? GLOBAL_ARR_COLS : 1 )\
                             * ( GLOBAL_ARR_PAGS ? GLOBAL_ARR_PAGS : 1 )\
                             * ( GLOBAL_ARR_BOOKS ? GLOBAL_ARR_BOOKS : 1 );\
        _X_##_data.rowi=0; _X_##_data.rowinc=0; _X_##_data.rowe=0;\
        _X_##_data.coli=0; _X_##_data.colinc=0; _X_##_data.cole=0;\
        _X_##_data.pagi=0; _X_##_data.paginc=0; _X_##_data.page=0;\
        _X_##_data.booki=0; _X_##_data.bookinc=0; _X_##_data.booke=0;

#define Init_Global_Array(_X_,_TIPO_)\
        do{\
          Is_ok=1;\
          _X_ = ( _TIPO_ * ) malloc( sizeof( _TIPO_ ) * _X_##_data.len );\
          if( _X_ == NULL ) {\
              Msg_red("as_array : no hay memoria para <"#_X_">(MALLOC)");\
              Is_ok=0;break;\
          }\
        }while(0);

#define Init_Global_Unsigned_Array(_X_,_TIPO_)\
        do{\
          Is_ok=1;\
          _X_ = ( unsigned _TIPO_ * ) malloc( sizeof( unsigned _TIPO_ ) * _X_##_data.len );\
          if( _X_==NULL ) {\
              Msg_red("as_unsigned_array : no hay memoria para <"#_X_">(MALLOC)");\
              Is_ok=0;break; \
          }\
        }while(0);

#define Init_Global_Str_Array(_X_)\
        do{\
          Is_ok=1;\
          _X_ = ( char ** ) calloc( sizeof( char * ) * _X_##_data.len, 1 );\
          if( _X_ == NULL ) {\
              Msg_red("as_str_array : no hay memoria para <"#_X_">(CALLOC)\n");\
              Is_ok=0;break;\
          }\
        }while(0);

#define Init_Global_Fill_Array(_X_,_TIPO_,_F_)\
        do{\
          Is_ok=1;\
          _X_ = ( _TIPO_ * ) malloc( sizeof( _TIPO_ ) * _X_##_data.len );\
          if( _X_ ) {\
             int i;\
             for( i=0; i < _X_##_data.len; i++){\
                 * (_X_ + i ) = ( _TIPO_ ) ( _F_ );\
             }\
          }else { Msg_red("as_fill_array : no hay memoria para <"#_X_">(MALLOC)\n");\
                  Is_ok=0;break; }\
        }while(0);

#define Init_Global_Fill_Unsigned_Array(_X_,_TIPO_,_F_)\
        do{\
          Is_ok=1;\
          _X_ = ( unsigned _TIPO_ * ) malloc( sizeof( unsigned _TIPO_ ) * _X_##_data.len );\
          if( _X_ ) {\
             int i;\
             for( i=0; i < _X_##_data.len; i++){\
                * (_X_ + i ) = ( unsigned _TIPO_ ) ( _F_ );\
             }\
          }else { Msg_red("as_fill_unsigned_array : no hay memoria para <"#_X_">(MALLOC)\n");\
                  Is_ok=0;break; }\
        }while(0);

#define Init_Global_Fill_Str_Array(_X_,_F_) \
        do{\
          Is_ok=1;\
          _X_ = ( char ** ) calloc( sizeof( char * ) * ( _X_##_data.len ), 1 );\
          if( _X_ ) {\
             int i;\
             for( i=0 ; i < _X_##_data.len; i++){\
                * (_X_ + i ) = (char *)calloc(strlen(_F_)+1,1);\
                strcpy( * (_X_ + i ), _F_ );\
             }\
          }else {Msg_red("as_fill_str_array : no hay memoria para <" #_X_ "> (CALLOC)\n");\
                 Is_ok=0;break;}\
        }while(0);


/* define un array de tipo _TIPO_ (ver _data_types_), menos el tipo STRING, que
   se debe definir aparte */
#define as_array(_X_,_TIPO_)\
        _TIPO_ * _X_ = NULL;\
        Define_Global_Array(_X_)\
        _X_##_data.type = _TIPO_##_TYPE;\
        Init_Global_Array(_X_,_TIPO_ )

#define as_unsigned_array(_X_,_TIPO_) \
        unsigned _TIPO_ * _X_ = NULL;\
        Define_Global_Array(_X_)\
        _X_##_data.type = unsigned_##_TIPO_##_TYPE;\
        Init_Global_Unsigned_Array(_X_,_TIPO_)

#define as_str_array(_X_) \
        char ** _X_ = NULL;\
        Define_Global_Array(_X_)\
        _X_##_data.type = string_TYPE;\
        Init_Global_Str_Array(_X_)

/* creacion de arrays con un valor de relleno */
#define as_fill_array(_X_,_TIPO_,_F_) \
        _TIPO_ * _X_ = NULL;\
        Define_Global_Array(_X_)\
        _X_##_data.type = _TIPO_##_TYPE;\
        Init_Global_Fill_Array(_X_,_TIPO_,_F_)

#define as_fill_unsigned_array(_X_,_TIPO_,_F_) \
        unsigned _TIPO_ * _X_ = NULL;\
        Define_Global_Array(_X_)\
        _X_##_data.type = unsigned_##_TIPO_##_TYPE;\
        Init_Global_Fill_Unsigned_Array(_X_,_TIPO_,_F_)

#define as_fill_str_array(_X_,_F_)\
        char ** _X_ = NULL;\
        Define_Global_Array(_X_)\
        _X_##_data.type = string_TYPE;\
        Init_Global_Fill_Str_Array(_X_,_F_)

/* ARRAYS NUEVOS, SIN DIMENSION */

#define Set_zeros_metadata_new_array(_X_) \
        _X_##_data.rows = 0 ;\
        _X_##_data.cols = 0 ;\
        _X_##_data.pags = 0 ;\
        _X_##_data.books = 0 ;\
        _X_##_data.dims = 1;\
        _X_##_data.len = 0;\
        _X_##_data.rowi=0; _X_##_data.rowinc=0; _X_##_data.rowe=0;\
        _X_##_data.coli=0; _X_##_data.colinc=0; _X_##_data.cole=0;\
        _X_##_data.pagi=0; _X_##_data.paginc=0; _X_##_data.page=0;\
        _X_##_data.booki=0; _X_##_data.bookinc=0; _X_##_data.booke=0;

#define Set_zeros_metadata_delete_array_ptr(_X_) \
        _X_##_data->rows = 0 ;\
        _X_##_data->cols = 0 ;\
        _X_##_data->pags = 0 ;\
        _X_##_data->books = 0 ;\
        _X_##_data->dims = 0;\
        _X_##_data->len = 0;\
        _X_##_data->rowi=0; _X_##_data->rowinc=0; _X_##_data->rowe=0;\
        _X_##_data->coli=0; _X_##_data->colinc=0; _X_##_data->cole=0;\
        _X_##_data->pagi=0; _X_##_data->paginc=0; _X_##_data->page=0;\
        _X_##_data->booki=0; _X_##_data->bookinc=0; _X_##_data->booke=0;

#define Set_zeros_metadata_delete_array(_X_) \
        _X_##_data.rows = 0 ;\
        _X_##_data.cols = 0 ;\
        _X_##_data.pags = 0 ;\
        _X_##_data.books = 0 ;\
        _X_##_data.dims = 0;\
        _X_##_data.len = 0;\
        _X_##_data.rowi=0; _X_##_data.rowinc=0; _X_##_data.rowe=0;\
        _X_##_data.coli=0; _X_##_data.colinc=0; _X_##_data.cole=0;\
        _X_##_data.pagi=0; _X_##_data.paginc=0; _X_##_data.page=0;\
        _X_##_data.booki=0; _X_##_data.bookinc=0; _X_##_data.booke=0;

#define Define_New_Array(_X_) \
        DS_ARRAY  _X_##_data;\
        Set_zeros_metadata_new_array(_X_);

#define New_unsigned_array(_X_,_TIPO_) \
        unsigned _TIPO_ * _X_ = NULL;\
        Define_New_Array(_X_)\
        _X_##_data.type = unsigned_##_TIPO_##_TYPE;

#define New_array(_X_,_TIPO_)\
        _TIPO_ * _X_ = NULL;\
        Define_New_Array(_X_)\
        _X_##_data.type = _TIPO_##_TYPE;

#define New_str_array(_X_) \
        char ** _X_ = NULL;\
        Define_New_Array(_X_)\
        _X_##_data.type = string_TYPE;

/* APPEND elementos a un array, sea nuevo o existente */

#define puAppend(_X_, _TIPO_, _V_) \
        Is_ok=1;\
        _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ )\
               * ( ++_X_##_data->len ) );\
        if( _X_ ) {\
           * (_X_ + _X_##_data->len - 1 ) = ( unsigned _TIPO_ )( ( _V_ ) );\
        }else {Msg_red("puAppend : no hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0;}

#define pAppend(_X_, _TIPO_, _V_) \
        Is_ok=1;\
        _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * ( ++_X_##_data->len ) );\
        if( _X_ ) {\
           * (_X_ + _X_##_data->len - 1 ) = ( _TIPO_ )( ( _V_ ) );\
        }else {Msg_red("pAppend : no hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0;}

#define uAppend(_X_, _TIPO_, _V_) \
        Is_ok=1;\
        _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) \
              * ( ++_X_##_data.len ) );\
        if( _X_ ) {\
           * (_X_ + _X_##_data.len - 1 ) = ( unsigned _TIPO_ )( ( _V_ ) );\
        }else {Msg_red("uAppend : no hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0;}

#define Append(_X_, _TIPO_, _V_) \
        Is_ok=1;\
        _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * ( ++_X_##_data.len ) );\
        if( _X_ ) {\
           * (_X_ + _X_##_data.len - 1 ) = ( _TIPO_ )( ( _V_ ) );\
        }else {Msg_red("Append : no hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0;}


#define sAppend(_X_,_V_) \
        Is_ok=1;\
        _X_ = ( char ** ) realloc( (void *) _X_, sizeof( char * ) * ( ++_X_##_data.len ) );\
        if( _X_ ) {\
           * (_X_ + _X_##_data.len - 1 ) = (char *)calloc(strlen(_V_)+1,1);\
           strcpy(* (_X_ + _X_##_data.len - 1 ),  _V_ );\
        }else {Msg_red("sAppend : no hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0;}

#define psAppend(_X_,_V_) \
        Is_ok=1;\
        _X_ = ( char ** ) realloc( (void *) _X_, sizeof( char * ) * ( ++_X_##_data->len ) );\
        if( _X_ ) {\
           * (_X_ + _X_##_data->len - 1 ) = (char *)calloc(strlen(_V_)+1,1);\
           strcpy( * (_X_ + _X_##_data->len - 1 ), _V_ );\
        }else {Msg_red("psAppend : no hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0;}


/* libera un array numérico */

#define Free_only_array(_X_)       free(_X_); _X_=NULL;

// 
#define Free_array(_X_)  free(_X_); _X_=NULL; Set_zeros_metadata_delete_array(_X_)

#define pFree_array(_X_)    Free_ptr_array(_X_)
#define Free_ptr_array(_X_)  free(_X_); _X_=NULL; Set_zeros_metadata_delete_array_ptr(_X_)

/* libera array de string */
#define sFree_only_array(_X_)     Free_str_only_array(_X_)
#define Free_str_only_array(_X_)   \
        do{\
           int i; for( i=0; i < _X_##_data.len; i++)\
              if(_X_[ i ]) free(_X_[ i ]); \
           free(_X_);_X_=NULL;\
        }while(0);

#define sFree_array(_X_)     Free_str_array(_X_)
#define Free_str_array(_X_)  \
        do{\
           int i;for( i=0; i < _X_##_data.len; i++)\
              if(_X_[ i ]) free(_X_[ i ]); \
           free(_X_);_X_=NULL; Set_zeros_metadata_delete_array(_X_)\
        }while(0);

#define psFree_only_array(_X_)     Free_str_ptr_only_array(_X_)
#define Free_str_ptr_only_array(_X_)  \
        do{\
           int i; for( i=0; i < _X_##_data->len; i++) \
               if(_X_[ i ]) free(_X_[ i ]); \
           free(_X_);_X_=NULL;\
        }while(0);

#define psFree_array(_X_)        Free_str_ptr_array(_X_)
#define Free_str_ptr_array(_X_)  \
        do{\
           int i; for( i=0; i < _X_##_data->len; i++) \
               if(_X_[ i ]) free(_X_[ i ]); \
           free(_X_);_X_=NULL; Set_zeros_metadata_delete_array_ptr(_X_)\
        }while(0);

/* obtiene los datos de la metadata del array */
#define pDims(_X_)        _X_##_data->dims
#define Dims(_X_)            _X_##_data.dims
#define pRows(_X_)        _X_##_data->rows
#define Rows(_X_)            _X_##_data.rows
#define pCols(_X_)        _X_##_data->cols
#define Cols(_X_)            _X_##_data.cols
#define pPags(_X_)        _X_##_data->pags
#define Pags(_X_)            _X_##_data.pags
#define pBooks(_X_)        _X_##_data->books
#define Books(_X_)            _X_##_data.books
#define pLen(_X_)         _X_##_data->len
#define Len(_X_)             _X_##_data.len

/* devuelve el tipo */
#define Type(_X_)          _X_##_data.type
#define pType(_X_)      _X_##_data->type

/* RESHAPE de matrices */
#define Reshape(_X_, ...) CONCAT2(Reshape, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)
#define pReshape(_X_, ...) CONCAT2(Reshape_ptr, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Reshape4(_X_,ARG1,ARG2,ARG3,ARG4) \
        Is_ok=1;\
        if( ( ( ARG1 ) * ( ARG2 ) * ( ARG3 ) * ( ARG4 ) ) == _X_##_data.len ){\
           _X_##_data.rows=ARG1; _X_##_data.cols=ARG2; _X_##_data.pags=ARG3; \
           _X_##_data.books=ARG4; _X_##_data.dims=4;\
        }else {Msg_red("Reshape : nuevas dimensiones fuera de rango para <"#_X_">\n");\
              Is_ok=0;}

#define Reshape3(_X_,ARG1,ARG2,ARG3) \
        Is_ok=1;\
        if( ( ( ARG1 ) * ( ARG2 ) * ( ARG3 ) ) == _X_##_data.len ){\
           _X_##_data.rows=ARG1; _X_##_data.cols=ARG2; _X_##_data.pags=ARG3;\
           _X_##_data.books=0; _X_##_data.dims=3;\
        }else {Msg_red("Reshape : nuevas dimensiones fuera de rango para <"#_X_">\n");\
              Is_ok=0;}

#define Reshape2(_X_,ARG1,ARG2) \
        Is_ok=1;\
        if( ( ( ARG1 ) * ( ARG2 ) ) == _X_##_data.len ){\
           _X_##_data.rows=ARG1; _X_##_data.cols=ARG2;_X_##_data.pags=0;\
           _X_##_data.books=0;_X_##_data.dims=2;\
        }else {Msg_red("Reshape : nuevas dimensiones fuera de rango para <"#_X_">\n");\
              Is_ok=0;}

#define Reshape1(_X_,ARG1) \
        Is_ok=1;\
        if( ( ARG1 ) == _X_##_data.len ){\
           _X_##_data.rows=ARG1; _X_##_data.cols=0; _X_##_data.pags=0;\
           _X_##_data.books=0; _X_##_data.dims=1;\
        }else {Msg_red("Reshape : nueva dimensión fuera de rango para <"#_X_">\n");\
              Is_ok=0;}

#define Reshape_ptr4(_X_,ARG1,ARG2,ARG3,ARG4) \
        Is_ok=1;\
        if( ( ( ARG1 ) * ( ARG2 ) * ( ARG3 ) * ( ARG4 ) ) == _X_##_data->len ){\
           _X_##_data->rows=ARG1; _X_##_data->cols=ARG2; _X_##_data->pags=ARG3;\
           _X_##_data->books=ARG4; _X_##_data->dims=4;\
        }else {Msg_red("Reshape_ptr : nuevas dimensiones fuera de rango para <"#_X_">\n");\
              Is_ok=0;}

#define Reshape_ptr3(_X_,ARG1,ARG2,ARG3) \
        Is_ok=1;\
        if( ( ( ARG1 ) * ( ARG2 ) * ( ARG3 ) ) == _X_##_data->len ){\
           _X_##_data->rows=ARG1; _X_##_data->cols=ARG2; _X_##_data->pags=ARG3;\
           _X_##_data.books=0; _X_##_data->dims=3;\
        }else {Msg_red("Reshape_ptr : nuevas dimensiones fuera de rango para <"#_X_">\n");\
              Is_ok=0;}

#define Reshape_ptr2(_X_,ARG1,ARG2) \
        Is_ok=1;\
        if( ( ( ARG1 ) * ( ARG2 ) ) == _X_##_data->len ){\
           _X_##_data->rows=ARG1; _X_##_data->cols=ARG2;_X_##_data->pags=0;\
           _X_##_data.books=0;_X_##_data->dims=2;\
        }else {Msg_red("Reshape_ptr : nuevas dimensiones fuera de rango para <"#_X_">\n");\
              Is_ok=0;}

#define Reshape_ptr1(_X_,ARG1) \
        Is_ok=1;\
        if( ( ARG1 ) == _X_##_data->len ){\
           _X_##_data->rows=ARG1; _X_##_data->cols=0; _X_##_data->pags=0;\
           _X_##_data.books=0; _X_##_data->dims=1;\
        }else {Msg_red("Reshape_ptr : nuevas dimensiones fuera de rango para <"#_X_">\n");\
              Is_ok=0;}


/* Iteraciones sobre rangos directos de array */

/* for down */
#define Iterdown(_R_, ...) CONCAT2(Iterdown, COUNT_ARGUMENTS(__VA_ARGS__))(_R_, ##__VA_ARGS__)

#define Iterdown2(_R_,_O_,_V_) \
        for( _V_=_O_##_data._R_##i; _V_> _O_##_data._R_##e; _V_+=_O_##_data._R_##inc)

#define Iterdown3(_R_,_I_,_INC_,_FIN_)  \
        for( _R_=_I_; _R_> _FIN_; _R_+=_INC_)
        
/* iteración con intervalos genéricos */
#define Iterdown5(_R_,_O_,_V_,_I_,_INC_,_END_) \
        _O_##_data._R_##i=_I_;_O_##_data._R_##inc=_INC_;_O_##_data._R_##e=_END_;\
        for( _V_=_O_##_data._R_##i; _V_> _O_##_data._R_##e; _V_+=_O_##_data._R_##inc)

/* for down ptr */
#define pIterdown(_R_, ...) CONCAT2(Iterdown_ptr, COUNT_ARGUMENTS(__VA_ARGS__))(_R_, ##__VA_ARGS__)

#define Iterdown_ptr2(_R_,_O_,_V_)  \
        for( _V_=_O_##_data->_R_##i; _V_< _O_##_data->_R_##e; _V_+=_O_##_data->_R_##inc)

#define Iterdown_ptr5(_R_,_O_,_V_,_I_,_INC_,_END_) \
        _O_##_data->_R_##i=_I_;_O_##_data->_R_##inc=_INC_;_O_##_data->_R_##e=_END_;\
        for( _V_=_O_##_data->_R_##i; _V_> _O_##_data->_R_##e; _V_+=_O_##_data->_R_##inc)

/* for up */
#define Iterup(_R_, ...) CONCAT2(Iterup, COUNT_ARGUMENTS(__VA_ARGS__))(_R_, ##__VA_ARGS__)

#define Iterup2(_R_,_O_,_V_)  \
        for( _V_=_O_##_data._R_##i; _V_< _O_##_data._R_##e; _V_+=_O_##_data._R_##inc)

#define Iterup3(_R_,_I_,_INC_,_FIN_)  \
        for( _R_=_I_; _R_< _FIN_; _R_+=_INC_)


#define Iterup5(_R_,_O_,_V_,_I_,_INC_,_END_) \
        _O_##_data._R_##i=_I_;_O_##_data._R_##inc=_INC_;_O_##_data._R_##e=_END_;\
        for( _V_=_O_##_data._R_##i; _V_< _O_##_data._R_##e; _V_+=_O_##_data._R_##inc)


/* for up ptr */
#define pIterup(_R_, ...) CONCAT2(Iterup_ptr, COUNT_ARGUMENTS(__VA_ARGS__))(_R_, ##__VA_ARGS__)

#define Iterup_ptr2(_R_,_O_,_V_) \
        for( _V_=_O_##_data->_R_##i; _V_< _O_##_data->_R_##e; _V_+=_O_##_data->_R_##inc)

#define Iterup_ptr5(_R_,_O_,_V_,_I_,_INC_,_END_) \
        _O_##_data->_R_##i=_I_;_O_##_data->_R_##inc=_INC_;_O_##_data->_R_##e=_END_;\
        for( _V_=_O_##_data->_R_##i; _V_< _O_##_data->_R_##e; _V_+=_O_##_data->_R_##inc)

/* FIX 
   Se pueden fijar filas, columnas, paginas o libros para trabajr sobre ellos y no tener que definir
   cosas como [pagina: 1: pagina] */
   
#define pFix(_R_,_O_,_N_)   _O_##_data->_R_##i=_N_;_O_##_data->_R_##inc=1;_O_##_data->_R_##e=_N_+1;
#define Fix(_R_,_O_,_N_)   _O_##_data._R_##i=_N_;_O_##_data._R_##inc=1;_O_##_data._R_##e=_N_+1;


/* MACROS COMPUTE 
   sirven para efectuar operaciones sobre una o varias matrices con el mismo intervalo.
   Los intervalos pueden ser declarados con All_range_for() y con Range_for().
   ATENCION! Solo sirven rangos en ascenso */

/* compute por valor */
#define Compute_for(_V_, ...) CONCAT2(COMPUTE, COUNT_ARGUMENTS(__VA_ARGS__))(_V_, ##__VA_ARGS__)

#define  COMPUTE2(_V_,_I_,_E_)\
         for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
            _E_;\
         }

#define  COMPUTE3(_V_,_I_,_J_,_E_)\
         for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
            for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
               _E_;\
            }\
         }

#define  COMPUTE4(_V_,_I_,_J_,_K_,_E_)\
         for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
            for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
               for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                  _E_;\
               }\
            }\
         }

#define  COMPUTE5(_V_,_I_,_J_,_K_,_L_,_E_)\
         for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
            for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
               for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                  for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                     _E_;\
                  }\
               }\
            }\
         }

/* ACCESO A ARRAYS 3D Y 4D POR ORDEN SEMANTICO */

#define  For_each_page(_V_,_K_)\
         for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc)

#define  For_each_book(_V_,_L_) \
         for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc)


/* compute por referencia */

#define  pCompute_for(_V_, ...) CONCAT2(COMPUTE_ptr, COUNT_ARGUMENTS(__VA_ARGS__))(_V_, ##__VA_ARGS__)

#define  COMPUTE_ptr2(_V_,_I_,_E_)\
         for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
            _E_;\
         }

#define  COMPUTE_ptr3(_V_,_I_,_J_,_E_)\
         for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
            for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
               _E_;\
            }\
         }

#define  COMPUTE_ptr4(_V_,_I_,_J_,_K_,_E_)\
         for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
            for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
               for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                  _E_;\
               }\
            }\
         }

#define  COMPUTE_ptr5(_V_,_I_,_J_,_K_,_L_,_E_)\
         for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
            for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
               for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                  for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                     _E_;\
                  }\
               }\
            }\
         }

/* ACCESO A ARRAYS 3D Y 4D POR ORDEN SEMANTICO */

#define  For_each_page_ptr(_V_,_K_)\
         for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc)

#define  For_each_book_ptr(_V_,_L_) \
         for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc)


/* argumntos de funciones: SEND */
// si modifica el data set
#define pSDS(_X_)     _X_, &_X_##_data
// si no  modifica el data set
#define SDS(_X_)         _X_, _X_##_data
// solo envia la metadata. puede ser SMD( &v )
#define SMD(_X_)         _X_##_data

/* argumento de funciones: RECEIVER */
// solo data set. puede ser MD( *v ) para puntero a data set
#define RMD(_X_)         DS_ARRAY _X_##_data

/* si modifica el data set */
#define pRDS(_TIPO_,_X_)     _TIPO_ *_X_, DS_ARRAY *_X_##_data
/* puede ser si no modifica el Data Set */
#define RDS(_TIPO_, _X_)      _TIPO_ *_X_, DS_ARRAY _X_##_data

/* COPIA LA INFO PARA FUNCIONES QUE RECIBEN void* (cualquier tipo de array) */
#define Rescue_DS_ptr(_TIPO_,_DEST_,_SOURCE_) \
     _TIPO_ _DEST_ = _SOURCE_;\
     DS_ARRAY *_DEST_##_data = _SOURCE_##_data;

#define Rescue_DS(_TIPO_,_DEST_,_SOURCE_) \
     _TIPO_ _DEST_ = _SOURCE_;\
     DS_ARRAY _DEST_##_data = _SOURCE_##_data;


/* MACROS DE MANEJO DE ARRAYS */

/*
   Las siguientes macros añaden e insertan elementos "en duro" en los arrays.
   Solo funcionan para arrays num{ericos. Para arrays de string, existen
   funciones.
*/

/* DECISION 
   Existen macros en la primera prueba para resolver otras cosas con arrays.
   ¿Las incluyo, o trato de transformarlas a funcion? */


/* Prepara array estático para que pueda ser usado con funciones gadget como
   array utilitario */
#define Array_static(_V_,_TIPO_,...) \
   _TIPO_ _V_[]={__VA_ARGS__};\
   DS_ARRAY _V_##_data;\
   _V_##_data.len=sizeof(_V_)/sizeof(_TIPO_);

/* MACROS APPEND HARD */

/* AÑADE datos numéricos simples al arreglo */

#define  Append_hlst(_X_,_TIPO_,_D1_,...)  \
do{\
   _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      Append(_X_,_TIPO_,xTemp[i]);\
   }\
}while(0);

/* añade datos "unsigned" al arreglo */
#define  uAppend_hlst(_X_,_TIPO_,_D1_,...)  \
do{\
   unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      uAppend(_X_,_TIPO_,xTemp[i]);\
   }\
}while(0);

/* añade datos numericos cuando la metadata se ha pasado a funcion como puntero */
#define  pAppend_hlst(_X_,_TIPO_,_D1_,...)  \
do{\
   _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      pAppend(_X_,_TIPO_,xTemp[i]);\
   }\
}while(0);

/* añade datos numericos "unsigned" cuando la metadata se ha pasado a funcion como puntero */
#define  puAppend_hlst(_X_,_TIPO_,_D1_,...)  \
do{\
   unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      puAppend(_X_,_TIPO_,xTemp[i]);\
   }\
}while(0);

/* añade filas en una matriz numerica */
#define  Append_hrow(_X_,_TIPO_,_D1_,...)  \
do{\
   _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      Append(_X_,_TIPO_,xTemp[i]);\
   }\
   _X_##_data.rows++;\
   _X_##_data.cols=nLen;\
   _X_##_data.dims=2;\
}while(0);

#define  uAppend_hrow(_X_,_TIPO_,_D1_,...)  \
do{\
   unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      uAppend(_X_,_TIPO_,xTemp[i]);\
   }\
   _X_##_data.rows++;\
   _X_##_data.cols=nLen;\
   _X_##_data.dims=2;\
}while(0);

/* añade filas en una matriz numerica puntero */
#define  pAppend_hrow(_X_,_TIPO_,_D1_,...)  \
do{\
   _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      pAppend(_X_,_TIPO_,xTemp[i]);\
   }\
   _X_##_data->rows++;\
   _X_##_data->cols=nLen;\
   _X_##_data->dims=2;\
}while(0);

/* añade filas en una matriz numerica puntero unsigned */
#define  puAppend_hrow(_X_,_TIPO_,_D1_,...)  \
do{\
   unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   int nLen = sizeof(xTemp)/sizeof(_TIPO_);\
   int i;\
   for( i=0; i<nLen; i++) {\
      puAppend(_X_,_TIPO_,xTemp[i]);\
   }\
   _X_##_data->rows++;\
   _X_##_data->cols=nLen;\
   _X_##_data->dims=2;\
}while(0);

/* añade columnas a un array numerico 2D*/
#define Append_hcol(_X_,_TIPO_,_D1_,...)  \
do{\
   Is_ok=1;\
   _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   if( !_X_##_data.rows && !_X_##_data.cols ){\
      if( _X_##_data.len==0 ){\
         int nSize = sizeof(xTemp)/sizeof(_TIPO_);\
         int i;\
         for( i=0; i<nSize; i++){\
             Append(_X_, _TIPO_, xTemp[i]);\
         }\
         _X_##_data.rows=nSize;_X_##_data.len=nSize;_X_##_data.cols=1;_X_##_data.dims=2;\
      }else{\
         int nLen=0;\
         _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * ( nLen = (_X_##_data.len * 2 ) ) );\
         if(_X_){\
             int nInter=nLen-1,j;\
             for( j=_X_##_data.len-1; j>=0; j-- ){\
                 Cell(_X_,nInter) = xTemp[j];\
                 Cell(_X_,nInter-1) = Cell(_X_,j);\
                 nInter-=2;\
             }\
             _X_##_data.rows=_X_##_data.len;_X_##_data.len=nLen;_X_##_data.cols=2;_X_##_data.dims=2;\
         }else{\
            Msg_red("Append_hcol : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0; \
         }\
      }\
   }else{\
      int nLen=0;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * ( nLen = (_X_##_data.len + _X_##_data.rows ) ) );\
      if(_X_){\
         int __cToIns__=_X_##_data.cols,i,j;\
         for( i=0; i<_X_##_data.rows; i++){\
             for( j=_X_##_data.len-1; j>=__cToIns__; j--){\
                 Cell(_X_,j+1) = Cell(_X_,j);\
             }\
             Cell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data.len++;\
             __cToIns__ += _X_##_data.cols+1;\
         }\
         _X_##_data.cols++;_X_##_data.len=nLen;\
      }else { Msg_red("Append_hcol : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0; }\
   }\
}while(0);

/* añade columnas a un array numerico unsigned 2D */
#define uAppend_hcol(_X_,_TIPO_,_D1_,...)  \
do{\
   Is_ok=1;\
   unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   if( !_X_##_data.rows && !_X_##_data.cols ){\
      if( _X_##_data.len==0 ){\
         int nSize = sizeof(xTemp)/sizeof(_TIPO_), i;\
         for( i=0; i<nSize; i++){\
             uAppend(_X_, _TIPO_, xTemp[i]);\
         }\
         _X_##_data.rows=nSize;_X_##_data.len=nSize;_X_##_data.cols=1;_X_##_data.dims=2;\
      }else{\
         int nLen=0;\
         _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) \
                 * ( nLen = (_X_##_data.len * 2 ) ) );\
         if(_X_){\
             int nInter=nLen-1, j;\
             for( j=_X_##_data.len-1; j>=0; j-- ){\
                 Cell(_X_,nInter) = xTemp[j];\
                 Cell(_X_,nInter-1) = Cell(_X_,j);\
                 nInter-=2;\
             }\
             _X_##_data.rows=_X_##_data.len;_X_##_data.len=nLen;_X_##_data.cols=2;_X_##_data.dims=2;\
         }else{\
            Msg_red("Append_hcol_unsigned : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0; \
         }\
      }\
   }else{\
      int nLen=0;\
      _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ )\
              * ( nLen = (_X_##_data.len + _X_##_data.rows ) ) );\
      if(_X_){\
         int __cToIns__=_X_##_data.cols, i, j;\
         for( i=0; i<_X_##_data.rows; i++){\
             for( j=_X_##_data.len-1; j>=__cToIns__; j--){\
                 Cell(_X_,j+1) = Cell(_X_,j);\
             }\
             Cell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data.len++;\
             __cToIns__ += _X_##_data.cols+1;\
         }\
         _X_##_data.cols++;_X_##_data.len=nLen;\
      }else { Msg_red("Append_hcol_unsigned : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0; }\
   }\
}while(0);

/* añade columnas a un array numerico 2D puntero */
#define pAppend_hcol(_X_,_TIPO_,_D1_,...)  \
do{\
   Is_ok=1;\
   _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   if( !_X_##_data->rows && !_X_##_data->cols ){\
      if( _X_##_data->len==0 ){\
         int nSize = sizeof(xTemp)/sizeof(_TIPO_), i;\
         for( i=0; i<nSize; i++){\
             pAppend(_X_, _TIPO_, xTemp[i]);\
         }\
         _X_##_data->rows=nSize;_X_##_data->len=nSize;_X_##_data->cols=1;_X_##_data->dims=2;\
      }else{\
         int nLen=0;\
         _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * ( nLen = (_X_##_data.len * 2 ) ) );\
         if(_X_){\
             int nInter=nLen-1, j;\
             for( j=_X_##_data->len-1; j>=0; j-- ){\
                 pCell(_X_,nInter) = xTemp[j];\
                 pCell(_X_,nInter-1) = pCell(_X_,j);\
                 nInter-=2;\
             }\
             _X_##_data->rows=_X_##_data->len;_X_##_data->len=nLen;_X_##_data->cols=2;_X_##_data->dims=2;\
         }else{\
            Msg_red("Append_hcol_ptr : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; \
         }\
      }\
   }else{\
      int nLen=0;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * ( nLen = (_X_##_data.len + _X_##_data.rows ) ) );\
      if(_X_){\
         int __cToIns__=_X_##_data->cols, i, j;\
         for( i=0; i<_X_##_data->rows; i++){\
             for( j=_X_##_data->len-1; j>=__cToIns__; j--){\
                 pCell(_X_,j+1) = pCell(_X_,j);\
             }\
             pCell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data->len++;\
             __cToIns__ += _X_##_data->cols+1;\
         }\
         _X_##_data->cols++;_X_##_data->len=nLen;\
      }else { Msg_red("Append_hcol_ptr : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; }\
   }\
}while(0);

/* añade columnas a un array numerico 2D puntero unsigned */
#define puAppend_hcol(_X_,_TIPO_,_D1_,...)  \
do{\
   Is_ok=1;\
   unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
   if( !_X_##_data->rows && !_X_##_data->cols ){\
      if( _X_##_data->len==0 ){\
         int nSize = sizeof(xTemp)/sizeof(_TIPO_), i;\
         for( i=0; i<nSize; i++){\
             puAppend(_X_, _TIPO_, xTemp[i]);\
         }\
         _X_##_data->rows=nSize;_X_##_data->len=nSize;_X_##_data->cols=1;_X_##_data->dims=2;\
      }else{\
         int nLen=0;\
         _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) \
                  * ( nLen = (_X_##_data.len * 2 ) ) );\
         if(_X_){\
             int nInter=nLen-1, j;\
             for( j=_X_##_data->len-1; j>=0; j-- ){\
                 pCell(_X_,nInter) = xTemp[j];\
                 pCell(_X_,nInter-1) = pCell(_X_,j);\
                 nInter-=2;\
             }\
             _X_##_data->rows=_X_##_data->len;_X_##_data->len=nLen;_X_##_data->cols=2;_X_##_data->dims=2;\
         }else{\
            Msg_red("Append_hcol_uptr : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; \
         }\
      }\
   }else{\
      int nLen=0;\
      _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) \
             * ( nLen = (_X_##_data.len + _X_##_data.rows ) ) );\
      if(_X_){\
         int __cToIns__=_X_##_data->cols, i, j;\
         for( i=0; i<_X_##_data->rows; i++){\
             for( j=_X_##_data->len-1; j>=__cToIns__; j--){\
                 pCell(_X_,j+1) = pCell(_X_,j);\
             }\
             pCell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data->len++;\
             __cToIns__ += _X_##_data->cols+1;\
         }\
         _X_##_data->cols++;_X_##_data->len=nLen;\
      }else { Msg_red("Append_hcol_uptr : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; }\
   }\
}while(0);

/* MACROS INSERT HARD */

/* INSERT HARD LST */

#define Insert_hlst( _X_,_TIPO_,_POS_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_POS_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data.len){\
      _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nSize = sizeof(xTemp)/sizeof(_TIPO_);\
      int nLen = 0, ntLen=0,it=0;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * \
            ( nLen = (_X_##_data.len + nSize ) ) );\
      if(_X_){\
         ntLen = nLen-1,i;\
         for( i=_X_##_data.len-1; i>=__cToIns__; i--) {\
            Cell(_X_,ntLen) = Cell(_X_,i);\
            ntLen--;\
         }\
         for( i=__cToIns__; i<__cToIns__+nSize; i++) {\
            Cell(_X_,i) = xTemp[it++];\
         }\
         _X_##_data.len=nLen;\
      }\
   }else {Msg_red("Insert_hlst : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

/* insercion de datos unsigned */
#define uInsert_hlst( _X_,_TIPO_,_POS_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_POS_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data.len){\
      unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nSize = sizeof(xTemp)/sizeof(_TIPO_);\
      int nLen = 0, ntLen=0,it=0;\
      _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) * \
            ( nLen = (_X_##_data.len + nSize ) ) );\
      if(_X_){\
         ntLen = nLen-1, i;\
         for( i=_X_##_data.len-1; i>=__cToIns__; i--) {\
            Cell(_X_,ntLen) = Cell(_X_,i);\
            ntLen--;\
         }\
         for( i=__cToIns__; i<__cToIns__+nSize; i++) {\
            Cell(_X_,i) = xTemp[it++];\
         }\
         _X_##_data.len=nLen;\
      }\
   }else {Msg_red("Insert_hlst_unsigned : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

/* insercion de datos con Data Set puntero */
#define pInsert_hlst( _X_,_TIPO_,_POS_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_POS_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data->len){\
      _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nSize = sizeof(xTemp)/sizeof(_TIPO_);\
      int nLen = 0, ntLen=0,it=0;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) * \
            ( nLen = (_X_##_data->len + nSize ) ) );\
      if(_X_){\
         ntLen = nLen-1, i;\
         for( i=_X_##_data->len-1; i>=__cToIns__; i--) {\
            pCell(_X_,ntLen) = pCell(_X_,i);\
            ntLen--;\
         }\
         for( i=__cToIns__; i<__cToIns__+nSize; i++) {\
            pCell(_X_,i) = xTemp[it++];\
         }\
         _X_##_data->len=nLen;\
      }\
   }else {Msg_red("Insert_hlst_ptr : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

/* insercion de datos unsigned con DS puntero */
#define puInsert_hlst( _X_,_TIPO_,_POS_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_POS_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data->len){\
      unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nSize = sizeof(xTemp)/sizeof(_TIPO_);\
      int nLen = 0, ntLen=0,it=0;\
      _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) * \
            ( nLen = (_X_##_data->len + nSize ) ) );\
      if(_X_){\
         ntLen = nLen-1, i;\
         for( i=_X_##_data->len-1; i>=__cToIns__; i--) {\
            pCell(_X_,ntLen) = pCell(_X_,i);\
            ntLen--;\
         }\
         for( i=__cToIns__; i<__cToIns__+nSize; i++) {\
            pCell(_X_,i) = xTemp[it++];\
         }\
         _X_##_data->len=nLen;\
      }\
   }else {Msg_red("Insert_hlst_uptr : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

/* INSERT HARD ROW */

#define Insert_hrow( _X_,_TIPO_,_ROW_,_D1_,...) \
do{\
   Is_ok=1;\
   int __rToIns__=(_ROW_);\
   if(__rToIns__>=0 && __rToIns__<_X_##_data.rows){\
      _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) \
             * ( nLen = (_X_##_data.len + _X_##_data.cols ) ) );\
      if(_X_){\
         Iterdown(row,_X_, i, _X_##_data.rows-1, -1, __rToIns__-1 ){\
             Iterup( col, _X_, j, 0, 1, _X_##_data.cols ){\
                 Cell(_X_,i+1,j) = Cell(_X_,i,j); }}\
         Iterup(col, _X_, j){ Cell(_X_,__rToIns__,j) = xTemp[j]; }\
         _X_##_data.rows++;\
         _X_##_data.len=nLen;\
      }else { Msg_red("Insert_hrow : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0;}\
   }else{ Msg_red("Insert_hrow : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

#define uInsert_hrow( _X_,_TIPO_,_ROW_,_D1_,...) \
do{\
   Is_ok=1;\
   int __rToIns__=(_ROW_);\
   if(__rToIns__>=0 && __rToIns__<_X_##_data.rows){\
      unsinged _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0;\
      _X_ = ( unsinged _TIPO_ * ) realloc( (void *) _X_, sizeof( unsinged _TIPO_ ) \
             * ( nLen = (_X_##_data.len + _X_##_data.cols ) ) );\
      if(_X_){\
         Iterdown(row,_X_, i, _X_##_data.rows-1, -1, __rToIns__-1 ){\
             Iterup( col, _X_, j, 0, 1, _X_##_data.cols ){\
                 Cell(_X_,i+1,j) = Cell(_X_,i,j); }}\
         Iterup(col, _X_, j){ Cell(_X_,__rToIns__,j) = xTemp[j]; }\
         _X_##_data.rows++;\
         _X_##_data.len=nLen;\
      }else { Msg_red("Insert_hrow_unsigned : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0;}\
   }else{ Msg_red("Insert_hrow_unsigned : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

#define pInsert_hrow( _X_,_TIPO_,_ROW_,_D1_,...) \
do{\
   Is_ok=1;\
   int __rToIns__=(_ROW_);\
   if(__rToIns__>=0 && __rToIns__<_X_##_data->rows){\
      _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) \
             * ( nLen = (_X_##_data->len + _X_##_data->cols ) ) );\
      if(_X_){\
         pIterdown(row,_X_, i, _X_##_data->rows-1, -1, __rToIns__-1 ){\
             pIterup( col, _X_, j, 0, 1, _X_##_data->cols ){\
                 pCell(_X_,i+1,j) = pCell(_X_,i,j); }}\
         pIterup(col, _X_, j){ pCell(_X_,__rToIns__,j) = xTemp[j]; }\
         _X_##_data->rows++;\
         _X_##_data->len=nLen;\
      }else { Msg_red("Insert_hrow_ptr : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0;}\
   }else{ Msg_red("Insert_hrow_ptr : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

#define puInsert_hrow( _X_,_TIPO_,_ROW_,_D1_,...) \
do{\
   Is_ok=1;\
   int __rToIns__=(_ROW_);\
   if(__rToIns__>=0 && __rToIns__<_X_##_data->rows){\
      unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0;\
      _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) \
             * ( nLen = (_X_##_data->len + _X_##_data->cols ) ) );\
      if(_X_){\
         pIterdown(row,_X_, i, _X_##_data->rows-1, -1, __rToIns__-1 ){\
             pIterup( col, _X_, j, 0, 1, _X_##_data->cols ){\
                 pCell(_X_,i+1,j) = pCell(_X_,i,j); }}\
         pIterup(col, _X_, j){ pCell(_X_,__rToIns__,j) = xTemp[j]; }\
         _X_##_data->rows++;\
         _X_##_data->len=nLen;\
      }else { Msg_red("Insert_hrow_uptr : No hay memoria para <"#_X_">(REALLOC)\n"); Is_ok=0;}\
   }else{ Msg_red("Insert_hrow_uptr : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

/* INSERT HARD COLUMN */

#define Insert_hcol( _X_,_TIPO_,_COL_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_COL_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data.cols){\
      _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0, i, j;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) \
              * ( nLen = (_X_##_data.len + _X_##_data.rows ) ) );\
      if(_X_){\
         for( i=0; i<_X_##_data.rows; i++){\
             for( j=_X_##_data.len-1; j>=__cToIns__; j--){\
                 Cell(_X_,j+1) = Cell(_X_,j);\
             }\
             Cell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data.len++;\
             __cToIns__ += _X_##_data.cols+1;\
         }\
         _X_##_data.cols++; _X_##_data.len=nLen;\
      }else { Msg_red("Insert_hcol : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; }\
   }else{ Msg_red("Insert_hcol : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

#define uInsert_hcol( _X_,_TIPO_,_COL_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_COL_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data.cols){\
      unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0, i, j;\
      _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) \
              * ( nLen = (_X_##_data.len + _X_##_data.rows ) ) );\
      if(_X_){\
         for( i=0; i<_X_##_data.rows; i++){\
             for( j=_X_##_data.len-1; j>=__cToIns__; j--){\
                 Cell(_X_,j+1) = Cell(_X_,j);\
             }\
             Cell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data.len++;\
             __cToIns__ += _X_##_data.cols+1;\
         }\
         _X_##_data.cols++; _X_##_data.len=nLen;\
      }else { Msg_red("Insert_hcol_unsigned : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; }\
   }else{ Msg_red("Insert_hcol_unsigned : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);


#define pInsert_hcol( _X_,_TIPO_,_COL_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_COL_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data->cols){\
      _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0, i, j;\
      _X_ = ( _TIPO_ * ) realloc( (void *) _X_, sizeof( _TIPO_ ) \
              * ( nLen = (_X_##_data->len + _X_##_data->rows ) ) );\
      if(_X_){\
         for( i=0; i<_X_##_data->rows; i++){\
             for( j=_X_##_data->len-1; j>=__cToIns__; j--){\
                 pCell(_X_,j+1) = pCell(_X_,j);\
             }\
             pCell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data->len++;\
             __cToIns__ += _X_##_data->cols+1;\
         }\
         _X_##_data->cols++; _X_##_data->len=nLen;\
      }else { Msg_red("Insert_hcol_ptr : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; }\
   }else{ Msg_red("Insert_hcol_ptr : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

#define puInsert_hcol( _X_,_TIPO_,_COL_,_D1_,...) \
do{\
   Is_ok=1;\
   int __cToIns__=(_COL_);\
   if(__cToIns__>=0 && __cToIns__<_X_##_data->cols){\
      unsigned _TIPO_ xTemp[]={ _D1_,##__VA_ARGS__ };\
      int nLen=0, i, j;\
      _X_ = ( unsigned _TIPO_ * ) realloc( (void *) _X_, sizeof( unsigned _TIPO_ ) \
              * ( nLen = (_X_##_data->len + _X_##_data->rows ) ) );\
      if(_X_){\
         for( i=0; i<_X_##_data->rows; i++){\
             for( j=_X_##_data->len-1; j>=__cToIns__; j--){\
                 pCell(_X_,j+1) = pCell(_X_,j);\
             }\
             pCell(_X_,__cToIns__) = xTemp[i];\
             _X_##_data->len++;\
             __cToIns__ += _X_##_data->cols+1;\
         }\
         _X_##_data->cols++; _X_##_data->len=nLen;\
      }else { Msg_red("Insert_hcol_uptr : No hay memoria para <"#_X_">(REALLOC)\n");Is_ok=0; }\
   }else{ Msg_red("Insert_hcol_uptr : Posición a insertar no es válida\n"); Is_ok=0;}\
}while(0);

/* SWAPS */

/* SWAP-ROWS PTR */

#define  pSwap_rows(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __R1__=(_R_), __R2__=(_S_);\
   if(__R1__<0 || __R1__>_X_##_data->rows-1){\
      Msg_red("Swap_rows_ptr : fila "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__R2__<0 || __R2__>_X_##_data->rows-1){\
      Msg_red("Swap_rows_ptr : fila "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      pIterup( col, _X_, j, 0, 1, _X_##_data->cols ){\
          _TIPO_ dato = pCell(_X_,__R1__,j);\
          pCell(_X_,__R1__,j) = pCell(_X_,__R2__,j);\
          pCell(_X_,__R2__,j) = dato; }}\
}while(0);

/* SWAP-ROWS */
#define  Swap_rows(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __R1__=(_R_), __R2__=(_S_);\
   if(__R1__<0 || __R1__>_X_##_data.rows-1){\
      Msg_red("Swap_rows : fila "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__R2__<0 || __R2__>_X_##_data.rows-1){\
      Msg_red("Swap_rows : fila "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      Iterup( col, _X_, j, 0, 1, _X_##_data.cols ){\
          _TIPO_ dato = Cell(_X_,__R1__,j);\
          Cell(_X_,__R1__,j) = Cell(_X_,__R2__,j);\
          Cell(_X_,__R2__,j) = dato; }}\
}while(0);

/* SWAP-COLS */
#define  pSwap_cols(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __C1__=(_R_), __C2__=(_S_);\
   if(__C1__<0 || __C1__>_X_##_data->cols-1){\
      Msg_red("Swap_cols_ptr : columna "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__C2__<0 || __C2__>_X_##_data->cols-1){\
      Msg_red("Swap_cols_ptr : columna "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      pIterup( row, _X_, i, 0, 1, _X_##_data->rows ){\
          _TIPO_ dato = pCell(_X_,i,__C1__);\
          pCell(_X_,i,__C1__) = pCell(_X_,i,__C2__);\
          pCell(_X_,i,__C2__) = dato; }}\
}while(0);

#define  Swap_cols(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __C1__=(_R_), __C2__=(_S_);\
   if(__C1__<0 || __C1__>_X_##_data.cols-1){\
      Msg_red("Swap_cols : columna "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__C2__<0 || __C2__>_X_##_data.cols-1){\
      Msg_red("Swap_cols : columna "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      Iterup( row, _X_, i, 0, 1, _X_##_data.rows ){\
          _TIPO_ dato = Cell(_X_,i,__C1__);\
          Cell(_X_,i,__C1__) = Cell(_X_,i,__C2__);\
          Cell(_X_,i,__C2__) = dato; }}\
}while(0);

/* SWAP-PAGS */

#define  pSwap_pags(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __P1__=(_R_), __P2__=(_S_);\
   if(__P1__<0 || __P1__>_X_##_data->pags-1){\
      Msg_red("Swap_pags_ptr : página "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__P2__<0 || __P2__>_X_##_data->pags-1){\
      Msg_red("Swap_pags_ptr : página "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      pIterup( row, _X_, i, 0, 1, _X_##_data->rows ){\
          pIterup( col, _X_, j, 0, 1, _X_##_data->cols ){\
          _TIPO_ dato = pCell(_X_,i,j,__P1__);\
          pCell(_X_,i,j,__P1__) = pCell(_X_,i,j,__P2__);\
          pCell(_X_,i,j,__P2__) = dato; }}}\
}while(0);

#define  Swap_pags(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __P1__=(_R_), __P2__=(_S_);\
   if(__P1__<0 || __P1__>_X_##_data.pags-1){\
      Msg_red("Swap_pags : página "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__P2__<0 || __P2__>_X_##_data.pags-1){\
      Msg_red("Swap_pags : página "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      Iterup( row, _X_, i, 0, 1, _X_##_data.rows ){\
          Iterup( col, _X_, j, 0, 1, _X_##_data.cols ){\
          _TIPO_ dato = Cell(_X_,i,j,__P1__);\
          Cell(_X_,i,j,__P1__) = Cell(_X_,i,j,__P2__);\
          Cell(_X_,i,j,__P2__) = dato; }}}\
}while(0);

/* SWAP-LST */

#define  pSwap_lst(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __P1__=(_R_), __P2__=(_S_);\
   if(__P1__<0 || __P1__>_X_##_data->len-1){\
      Msg_red("Swap_lst_ptr : posición "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__P2__<0 || __P2__>_X_##_data->len-1){\
      Msg_red("Swap_lst_ptr : posición "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      _TIPO_ dato = pCell(_X_,__P1__);\
      pCell(_X_,__P1__) = pCell(_X_,__P2__);\
      pCell(_X_,__P2__) = dato; }\
}while(0);

#define  Swap_lst(_X_,_TIPO_,_R_,_S_) \
do{\
   Is_ok=1;\
   int __P1__=(_R_), __P2__=(_S_);\
   if(__P1__<0 || __P1__>_X_##_data.len-1){\
      Msg_red("Swap_lst : posición "#_R_" fuera de rango\n"); Is_ok=0;}\
   else if (__P2__<0 || __P2__>_X_##_data.len-1){\
      Msg_red("Swap_lst : posición "#_S_" fuera de rango\n"); Is_ok=0;}\
   else{\
      _TIPO_ dato = Cell(_X_,__P1__);\
      Cell(_X_,__P1__) = Cell(_X_,__P2__);\
      Cell(_X_,__P2__) = dato; }\
}while(0);

/* obtiene coordenadas virtuales de arrays n-dimensionales */
#define Get_coor(_X_, _M_,...) CONCAT2(Get_coor_, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, _M_, ##__VA_ARGS__)


/* SCAN simple ascendete y descendente */

#define Rev_scan(_X_, _V_, _D_, _LOW_, _HIGH_)     __Scan_Array__(_X_, _V_, _D_, _LOW_, _HIGH_,>, --)
#define Scan(_X_, _V_, _D_, _LOW_, _HIGH_)     __Scan_Array__(_X_, _V_, _D_, _LOW_, _HIGH_,<, ++)
#define __Scan_Array__(_X_, _V_, _D_, _LOW_, _HIGH_,_OP_,_OP1_)\
do{\
   int i;\
   _V_=-1;\
   for(i=(_LOW_); i _OP_ (_HIGH_); i _OP1_ ){\
       if ( _X_[i] == _D_ ){\
           _V_ = i;break;\
       }\
   }\
}while(0);

/* SCAN simple para strings */
#define sRev_scan(_X_, _V_, _D_, _LOW_, _HIGH_)     __Scan_Str_Array__(_X_, _V_, _D_, _LOW_, _HIGH_,>, --)
#define sScan(_X_, _V_, _D_, _LOW_, _HIGH_)     __Scan_Str_Array__(_X_, _V_, _D_, _LOW_, _HIGH_,<, ++)
#define __Scan_Str_Array__(_X_, _V_, _D_, _LOW_, _HIGH_,_OP_,_OP1_)\
do{\
   int i;\
   _V_=-1;\
   for(i=(_LOW_); i _OP_ (_HIGH_); i _OP1_ ){\
       if ( strcmp( _X_[i], _D_ ) == 0 ){\
           _V_ = i;break;\
       }\
   }\
}while(0);

/* BINARY SCAN simple para numeros */
#define bScan(_X_, _V_, _D_, _LOW_, _HIGH_) \
do{\
  int mid=0,swFound=0;\
  int low = (_LOW_);\
  int high = (_HIGH_);\
  while (low <= high) {\
    mid = low + (high - low) / 2;\
    if (_X_[mid] == _D_) { swFound=1; break; }\
    if (_X_[mid] < _D_)  low = mid + 1;\
    else  high = mid - 1;\
  }\
  _V_ = swFound ? mid : -1;\
}while(0);

/**********************************************************************/


/* FUNCIONES DE MANEJO DE ARRAYS */

/* devuelve 1 o 0 */
int  Equal_arrays(void* X, DS_ARRAY *X_data, void*Y, DS_ARRAY *Y_data);

/* la funcion anterior es la MASTER, y llama a las que vienen aquí, que
   pueden ser usadas por separado */
char ** Copy_array_to_string(DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data );
float * Copy_array_to_float(DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data );
int * Copy_array_to_int( DS_ARRAY *cpy, void * mat, DS_ARRAY *mat_data );
unsigned int * Copy_array_to_uint( DS_ARRAY *cpy, void * mat, DS_ARRAY *mat_data );
long * Copy_array_long( DS_ARRAY *cpy, void * mat, DS_ARRAY *mat_data );
unsigned long * Copy_array_ulong( DS_ARRAY *cpy, void * mat, DS_ARRAY *mat_data );
double * Copy_array_to_double( DS_ARRAY *cpy, void * mat, DS_ARRAY *mat_data );


/* la funcion anterior es la MASTER, y llama a las que vienen aquí, que
   pueden ser usadas por separado */
int * Clone_array_int( DS_ARRAY * T_data, int* S, DS_ARRAY * S_data );
unsigned int * Clone_array_uint( DS_ARRAY * T_data, unsigned int* S, DS_ARRAY * S_data );
float * Clone_array_float( DS_ARRAY * T_data, float* S, DS_ARRAY * S_data );
long * Clone_array_long( DS_ARRAY * T_data, long * S, DS_ARRAY * S_data );
unsigned long * Clone_array_ulong( DS_ARRAY * T_data, unsigned long * S, DS_ARRAY * S_data );
double * Clone_array_double( DS_ARRAY * T_data, double * S, DS_ARRAY * S_data );
char ** Clone_array_string( DS_ARRAY * T_data, char ** S, DS_ARRAY * S_data );

/* MAX y MIN */
DS_MAXMIN Max_array( void * mat, DS_ARRAY * mat_data );
DS_MAXMIN Min_array( void * mat, DS_ARRAY * mat_data );

/* secuencias */
double * Lineal_spaced( DS_ARRAY * data, double pDesde, double pHasta, int pTotal );
double * Lineal_sequence( DS_ARRAY * data, double pDesde, double pInc, int pTotal );

/* SPLIT y SPLIT_CHAR */
char ** Split( char * w, char token, char ** t, DS_ARRAY *t_data );
/* falso SPLIT_CHAR: regresa array de caracter string (por los acentos y eso),
   no de chars: para esto, el string ya es un array de char. */
char ** Split_char( char * w, char ** q, DS_ARRAY *q_data );

/* LOAD_MATRIX 
   carga un archivo en una matriz, y se puede especificar una porción de archivo a
   cargar. */

/* funcion utilitaria que lee e indica si encontró un "\n", para contar las filas leídas */
char * Read_to( int fhnd, char cTok, int *foundNL );

/* ahora sí: load_matrix por tipo leído */
int * Load_matrix_int(int * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat );
float * Load_matrix_float(float * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat );
long * Load_matrix_long(long * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat );
double * Load_matrix_double(double * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat );
char ** Load_matrix_string(char ** strMat, DS_ARRAY * strMat_data, const char * cFile, F_STAT stat );

/* SAVE_MATRIX 
   guardará toda la matriz en un archivo. Se realiza una conversión a STRING cuando
   sea necesario. */
int Save_matrix_int(int *mat, DS_ARRAY * mat_data, const char * cFile );
int Save_matrix_float(float *mat, DS_ARRAY * mat_data, const char * cFile );
int Save_matrix_long(long *mat, DS_ARRAY * mat_data, const char * cFile );
int Save_matrix_double(double *mat, DS_ARRAY * mat_data, const char * cFile );
int Save_matrix_string(char **mat, DS_ARRAY * mat_data, const char * cFile );

/* APPEND - tareas comunes con arrays. añaden datos a un array existente */
/* APPEND_LST - añade un array al array */
int * Append_lst_int(int *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
unsigned int * Append_lst_uint(unsigned int *X, DS_ARRAY * X_data, 
                                       void * XARR, DS_ARRAY * XARR_data);
float * Append_lst_float(float *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
long * Append_lst_long(long *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
unsigned long * Append_lst_ulong(unsigned long *X, DS_ARRAY * X_data, 
                                         void * XARR, DS_ARRAY * XARR_data);
double * Append_lst_double(double *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
char ** Append_lst_string(char **X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);

/* Añade columnas a un array 2D */
// ya está integrado en la mega-funcion-basura del master

/* añade un array a otro aray, en forma de fila, 2D */
int * Append_row_int( int * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
unsigned int * Append_row_uint( unsigned int * X, DS_ARRAY * X_data, 
                                        void * XARR, DS_ARRAY * XARR_data);
float * Append_row_float( float * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
long * Append_row_long( long * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
unsigned long * Append_row_ulong( unsigned long * X, DS_ARRAY * X_data, 
                                          void * XARR, DS_ARRAY * XARR_data);
double * Append_row_double( double * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
char ** Append_row_string( char ** X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);


/* Borra elementos de un array */
char **Delete_col_string(char ** array, DS_ARRAY * array_data,int __cToDel__);
unsigned long* Delete_col_ulong(unsigned long* array, DS_ARRAY * array_data,int __cToDel__);
long* Delete_col_long(long* array, DS_ARRAY * array_data,int __cToDel__);
double* Delete_col_double(double* array, DS_ARRAY * array_data,int __cToDel__);
float* Delete_col_float(float* array, DS_ARRAY * array_data,int __cToDel__);
int* Delete_col_int(int* array, DS_ARRAY * array_data,int __cToDel__);
unsigned int* Delete_col_uint(unsigned int* array, DS_ARRAY * array_data,int __cToDel__);

char **Delete_row_string(char ** array, DS_ARRAY * array_data,int __rToDel__);
unsigned long* Delete_row_ulong(unsigned long* array, DS_ARRAY * array_data,int __rToDel__);
long* Delete_row_long(long* array, DS_ARRAY * array_data,int __rToDel__);
double* Delete_row_double(double* array, DS_ARRAY * array_data,int __rToDel__);
float* Delete_row_float(float* array, DS_ARRAY * array_data,int __rToDel__);
int* Delete_row_int(int* array, DS_ARRAY * array_data,int __rToDel__);
unsigned int* Delete_row_uint(unsigned int* array, DS_ARRAY * array_data,int __rToDel__);

char **Delete_lst_string(char ** array, DS_ARRAY * array_data,int __pToDel__);
unsigned long* Delete_lst_ulong(unsigned long* array, DS_ARRAY * array_data,int __pToDel__);
long* Delete_lst_long(long* array, DS_ARRAY * array_data,int __pToDel__);
double* Delete_lst_double(double* array, DS_ARRAY * array_data,int __pToDel__);
float* Delete_lst_float(float* array, DS_ARRAY * array_data,int __pToDel__);
int* Delete_lst_int(int* array, DS_ARRAY * array_data,int __pToDel__);
unsigned int* Delete_lst_uint(unsigned int* array, DS_ARRAY * array_data,int __pToDel__);

/* INSERT */
unsigned int* Insert_lst_uint(unsigned int* array, DS_ARRAY * array_data, 
                                      unsigned int* APND, DS_ARRAY *APND_data, int __cToIns__);
int* Insert_lst_int(int* array, DS_ARRAY * array_data, 
                    int* APND, DS_ARRAY *APND_data, int __cToIns__);
long* Insert_lst_long(long* array, DS_ARRAY * array_data, 
                      long* APND, DS_ARRAY *APND_data, int __cToIns__);
unsigned long* Insert_lst_ulong(unsigned long* array, DS_ARRAY * array_data, 
                                        unsigned long* APND, DS_ARRAY *APND_data, int __cToIns__);
float* Insert_lst_float(float* array, DS_ARRAY * array_data, 
                        float* APND, DS_ARRAY *APND_data, int __cToIns__);
double* Insert_lst_double(double* array, DS_ARRAY * array_data, 
                          double* APND, DS_ARRAY *APND_data, int __cToIns__);
char ** Insert_lst_string(char ** array, DS_ARRAY * array_data, char **APND, DS_ARRAY *APND_data,
                          int __cToIns__);

char **Insert_row_string(char ** array, DS_ARRAY * array_data, 
                         char **APND, DS_ARRAY *APND_data, int __rToIns__);
unsigned long* Insert_row_ulong(unsigned long* array, DS_ARRAY * array_data, 
                                        unsigned long* APND, DS_ARRAY *APND_data, int __rToIns__);
unsigned int* Insert_row_uint(unsigned int* array, DS_ARRAY * array_data, 
                                      unsigned int* APND, DS_ARRAY *APND_data, int __rToIns__);
long* Insert_row_long(long* array, DS_ARRAY * array_data, 
                      long* APND, DS_ARRAY *APND_data, int __rToIns__);
int* Insert_row_int(int* array, DS_ARRAY * array_data, 
                    int* APND, DS_ARRAY *APND_data, int __rToIns__);
float* Insert_row_float(float* array, DS_ARRAY * array_data, 
                        float* APND, DS_ARRAY *APND_data, int __rToIns__);
double* Insert_row_double(double* array, DS_ARRAY * array_data, 
                          double* APND, DS_ARRAY *APND_data, int __rToIns__);

char **Insert_col_string(char ** array, DS_ARRAY * array_data, 
                         char **APND, DS_ARRAY *APND_data, int __cToIns__);
unsigned long* Insert_col_ulong(unsigned long* array, DS_ARRAY * array_data, 
                                        unsigned long* APND, DS_ARRAY *APND_data, int __cToIns__);
unsigned int* Insert_col_uint(unsigned int* array, DS_ARRAY * array_data, 
                                      unsigned int* APND, DS_ARRAY *APND_data, int __cToIns__);
long* Insert_col_long(long* array, DS_ARRAY * array_data, 
                      long* APND, DS_ARRAY *APND_data, int __cToIns__);
int* Insert_col_int(int* array, DS_ARRAY * array_data, 
                    int* APND, DS_ARRAY *APND_data, int __cToIns__);
float* Insert_col_float(float* array, DS_ARRAY * array_data, 
                        float* APND, DS_ARRAY *APND_data, int __cToIns__);
double* Insert_col_double(double* array, DS_ARRAY * array_data, 
                          double* APND, DS_ARRAY *APND_data, int __cToIns__);

/* matrics con elementos string añadidos EN DURO "hlst= hard lst"*/
char ** Append_hlst_string(char **X, DS_ARRAY * X_data, char * dato,...);
char ** Append_hrow_string(char ** array, DS_ARRAY * array_data,...);
char ** Append_hcol_string(char ** array, DS_ARRAY * array_data,...);

/* MASTERS */

int Save_matrix(void * X, DS_ARRAY * X_data, const char * cFile );
void * Load_matrix(void * strMat, DS_ARRAY * strMat_data, const char * cFile, F_STAT stat );

void * Clone_array( DS_ARRAY * T_data, void* S, DS_ARRAY * S_data);
void * Copy_array(DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data );

void * Append_lst(void *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
void * Append_row(void *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data);
void * Append_col(void *array, DS_ARRAY * array_data, void *APND, DS_ARRAY *APND_data);

///void * Append_hard_lst(void *X, DS_ARRAY * X_data, ...);

void * Delete_lst(void* array, DS_ARRAY * array_data,int __cToDel__);
void * Delete_col(void* array, DS_ARRAY * array_data,int __cToDel__);
void * Delete_row(void* array, DS_ARRAY * array_data,int __rToDel__);

void * Insert_lst(void* array, DS_ARRAY * array_data, void* APND, DS_ARRAY *APND_data, int __pToDel__);
void * Insert_row(void* array, DS_ARRAY * array_data, void* APND, DS_ARRAY *APND_data, int __pToDel__);
void * Insert_col(void* array, DS_ARRAY * array_data, void* APND, DS_ARRAY *APND_data, int __pToDel__);

/* obtiene coordenadas cartesianas de una posicion fisica del array */
/* GETCOORD */
void Get_coor_2(long nPos, DS_ARRAY * mat_data, int *r, int *c);
void Get_coor_3(long nPos, DS_ARRAY * mat_data, int *r, int *c, int *p );
void Get_coor_4(long nPos, DS_ARRAY * mat_data, int *r, int *c, int *p, int *b );


/********************************************************************************

                  FUNCIONES PARA FECHAS Y HORAS

 ********************************************************************************/
 
/* TIEMPO, CONTROL DE FECHAS Y HORAS */

// identificación de formatos de fecha
#define  DMY        0   // DD/MM/YYYY
#define  MDY        1   // MM/DD/YYYY
#define  YMD        2   // YYYY/MM/DD
#define  DMY_1      3   // DD-MM-YYYY
#define  MDY_1      4   // MM-DD-YYYY
#define  YMD_1      5   // YYYY-MM-DD
#define  DMY_2      6   // DD.MM.YYYY
#define  MDY_2      7   // MM.DD.YYYY
#define  YMD_2      8   // YYYY.MM.DD

/* clock_t X, Y;  */
#define  Tic(_X_)            _X_ = clock();
#define  Toc(_X_,_Y_)        _Y_ = ( clock() - (_X_) ) / CLOCKS_PER_SEC;
#define  Is_leap_year(_X_)     ( _X_ % 4 == 0 && _X_ % 100 != 0 ) || ( _X_ % 400 == 0 )
#define  Is_time_valid(_D_)    hb_timeValid( _D_, strlen(_D_), NULL )
#define  Is_date_valid(_D_)    hb_dateValid( _D_, strlen(_D_))

#define  X_STR_DATE_BASE      1721060     /* 0000/01/01 */
#define  X_DATE_YEAR_LIMIT    9999

/* codifica fechas en formato DMY */
#define Get_julian_date(_Y_,_M_,_D_)  x_dateEncode( _Y_, _M_, _D_ )
#define Decode_julian_date(_LJulian_, _Y_, _M_, _D_)    x_dateDecode( _LJulian_, _Y_, _M_, _D_)

#define Show_calendar(_AC_,_DS_C_, _ROW_, _COL_, _DAY_ACTUAL_) \
        _imprime_item_calendario_( _AC_,_DS_C_, _ROW_, _COL_, _DAY_ACTUAL_ )

#define  Set_first_monday       FIRST_MONDAY=1;
#define  Unset_first_monday      FIRST_MONDAY=0;

#define  Set_date_format(_X_)   ACTUAL_DATE_FORMAT=( _X_ >= DMY && _X_ <= YMD_1 ) ? _X_ : DMY ;

#define  Set_date_lang(_X_)     ACTUAL_LANG_DATE=( _X_ >= SP && _X_ <= IT ) ? _X_ : SP ;

#define  Calendar(_X_, _CODE_,...)   GET_CALENDAR( &_X_##_data, _CODE_, ##__VA_ARGS__ )

/* TIEMPO, CONTROL DE FECHAS Y HORAS */

/* STRTONUM */
double __numPow10__( int nPrecision );

/* funcion str2number obtenida del proyecto Harbour */
int __str2number__( int fPCode, const char * szNum, long nLen, long * lVal, double * dVal, int * piDec, int * piWidth );

/* funciones fecha obtenida desde el Proyecto Harbour*/
double x_strVal( const char *, long );

/*
 * Additional date functions
 *
 * Copyright 1999 Jose Lalin <dezac@corevia.com>
 */

/* este se invoca */
char * Get_date_format(int nType);

/* USO INTERNO */
char * x_GetDateFormat(int nType);

char * Sec2time( long lTime );
long Time2sec( const char * pszTime );
void x_timeStampGetLocal( int * piYear, int * piMonth, int * piDay,
                           int * piHour, int * piMinutes,
                           int * piSeconds, int * piMSec );

long x_dateEncode( int iYear, int iMonth, int iDay );
void x_dateDecode( long lJulian, int *piYear, int *piMonth, int *piDay );

char * x_dateFormat( const char * szDate, char * szFormattedDate, const char * szDateFormat );
int x_dateUnformatRaw( const char * szDate, const char * szDateFormat, long * plDate );
long x_dateUnformat( const char * szDate, const char * szDateFormat );
// resta horas en formato hh:MM:ss:mm
char * Elaptime( const char * cStart, const char * cEnd );

int ct_doy( long lDate );
int Day_of_year( const char * cDate );
int x_dateDOW( int iYear, int iMonth, int iDay );
int Week_of_year( const char * cDateF );
int Days_in_month( int iMonth, int bLeap );
int x_dateJulianDOW( long lJulian );

int Day_of_week( const char * cDateF );
int hb_timeValid( const char * szTime, long nLen, int * piDecode );

int hb_dateValid( const char * cDate, long nLen );

char * Get_timestamp();

char * Get_date();

char * Get_time();

/* cambia el formato de fecha. Ver #defines para mas informacion */
char * Date_format( char * cDate, int cFormato);

// devuelve día, mes y año por separado, en formato numérico
int Get_hour( const char * sTime );
int Get_minute( const char *sTime );
int Get_second( const char *sTime );
int Get_millisecond( const char *sTime );
int Get_year( const char *cDateF );
int Get_day( const char *cDateF );
int Get_month( const char *cDateF );
int Timer( float * nVarTimer, float nTimeMillisec );

void x_dateStrPut( char * szDate, int iYear, int iMonth, int iDay );

char * x_dateDecStr( char * szDate, long lJulian );
char * Date_add( const char * cDate, long lEnd );
long Days_diff( const char * cDate1, const char * cDate2 );

/* 0=domingo, 1=lunes,..., 7=domingo */
char * Get_dayname(int nDay);

/* 0=enero, 1=febrero...*/
char * Get_monthname(int nMonth);

char ** GET_CALENDAR( DS_ARRAY *, int, ... );

/* imprime calendario para seleccionar una fecha */
void _imprime_item_calendario_( RDS(char*, calendario), int x, int y, int actual_day );
void _show_item_calendar_dalien_( RDS(char *,cal), int nColorF, int nColorB, int actual_day );
long Select_date_from_calendar(char * date, int nColorF, int nColorB,int last_day_next_month);


/*************************************************************************************************

                       ARCHIVOS
 ****************************************************************************************************/
 
/* ARCHIVOS */
int Count_lines( const char * cString );
char * Load_string( const char * szFile );
int Save_string( const char * cString, const char * szFile );
int Append_string( const char * cString, const char * szFile );
int Exist_file( const char * sFile );
int Exist_dir( const char * sDir );

/* obtiene un string de una llamada a sistema */
char * Get_sys( const char * execstr );

/* realiza busquedas en un archivo, con GREP interno 
   Internamente, usa las opciones de base: -h -n -b */
unsigned int ** Search( const char *, const char * );
/* archivos complementarios de SEARCH 
   Usar open() y close(), no fopen() */
char * Str_file_error(int nError);
int File_size(int fd);
int Eof( int );
int Write_line( int, const char * );
char * Read_line( int );
int Write_string( int, const char * );
char * Read_string( int, int );
F_STAT Stat_file( const char * );

/***************************************************************************
                   
                            KEYBOARD Y TERMIOS 
                   
 ***************************************************************************/

// define macro para detectar CTRL+<KEY>. CtrlKey('h') => ctrl+h
#define  Ctrl_key(k)        ((k) & 0x1f)
#define Flush_out     fflush(stdout);
#define Flush_inp     fflush(stdin);while( Kbhit() ) Getch();

/* imprime array simple en la ubicacion del cursor */
#define Print_array(_X_,_DX_)   _imprime_input_item_array_(_X_,_DX_)

/* definiciones TEMPORALES para el uso de las funciones Key_put_xxx() 
   Deberá cambiarlas si su teclado es de otro tipo, distinto al mío.
   Consulte X11/keysymdef.h para más información */
#define KEYP_ENTER                   0xff8d  /* Enter */
#define KEYP_HOME                    0xff50
#define KEYP_LEFT                    0xff51  /* Move left, left arrow */
#define KEYP_UP                      0xff52  /* Move up, up arrow */
#define KEYP_RIGHT                   0xff53  /* Move right, right arrow */
#define KEYP_DOWN                    0xff54  /* Move down, down arrow */
#define KEYP_PRIOR                   0xff55  /* Prior, previous */
#define KEYP_PAGEUP                  0xff55
#define KEYP_NEXT                    0xff56  /* Next */
#define KEYP_PAGEDOWN                0xff56
#define KEYP_END                     0xff57  /* EOL */
#define KEYP_BEGIN                   0xff58  /* BOL */
#define KEYP_ESCAPE                  0xff1b 
#define KEYP_DELETE                  0xffff  /* Delete, rubout */
#define KEYP_BACKSP                  0xff08  /* Back space, back char */
#define KEYP_TAB                     0xff09

/* HABILITACION DE RAW-MODE Y FUNCIONES AD-HOC */

void __Die__(const char *s);
/* devuelve el terminal a la normalidad.
   IMPORTANTE! debe pasar por aquí, o el terminal tendrá que ser cerrado.
   Esta función es llamada al final de la ejecución del programa, terminando
   normalmente. También puede ser llamada en cualqioer parte del programa.*/
void Disable_raw_mode();
/* habilita RAW-MODE */
void Enable_raw_mode();
/* Uso de teclado en modo RAW */

/* obtiene la posicion del cursor en RAW MODE */
//int Get_cursor_raw(int *rows, int *cols);

/* el famoso KBHIT() para Linux */
int Kbhit();

int __ReadKey__();

/* ambos deben trabajar con kbhit() */
int Getch(void);
char * Read_char(void);

/* obtiene el tamaño del terminal */
void Get_size_terminal(void);

int Pause();

/* entrada de datos desde teclado */
void _imprime_input_item_array_(RDS(char *,array));
char * Input( char * cText, int nSpace );

/* simulacion de input */
void Key_put(unsigned int nKey);
void Key_put_ctrl(unsigned int nKey);
void Key_put_shift(unsigned int nKey);
void Key_put_alt(unsigned int nKey);

/* pone un texto en el buffer del teclado STDIN */
void Put_kbd_text(const char* cKey);

/* recibe un string-char desde stdin cuando se usa Put_kbd_text() */
char* Get_char_stdin();

/* lee el texto puesto en el STDIN */
char * Read_typed_string();

/************************************************************************
 *
 *                LIBRERIA BASICA DE MAPEO DE ARRAYS.
 *
 ************************************************************************/


/* mapea un array, cambiando el valor de sus elementos debido a condiciones */

/* 1D */
#define Map( _V_, _I_, ...) CONCAT2(Map_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_, ##__VA_ARGS__) 

#define Map_2(_V_, _I_,ARG1,ARG2) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
    }

#define Map_3(_V_, _I_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else { ARG3; }\
    }
    
#define Map_4(_V_, _I_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
    }

#define Map_5(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else { ARG5; }\
    }

#define Map_6(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
    }

#define Map_7(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else { ARG7; }\
    }

#define Map_8(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
    }

#define Map_9(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
        else { ARG9; }\
    }

#define Map_10(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
        else if( ARG10 ) { ARG9; }\
    }

#define Map_11(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
        else if( ARG10 ) { ARG9; }\
        else { ARG11; }\
    }



/* 2D */
#define Map2( _V_, _I_,_J_, ...) CONCAT2(Map2_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_,_J_, ##__VA_ARGS__) 

#define Map2_2(_V_, _I_,_J_,ARG1,ARG2) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
        }\
    }

#define Map2_3(_V_, _I_,_J_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else { ARG3; }\
        }\
    }
    
#define Map2_4(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
        }\
    }

#define Map2_5(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else { ARG5; }\
        }\
    }

#define Map2_6(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
        }\
    }

#define Map2_7(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else { ARG7; }\
        }\
    }

#define Map2_8(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
        }\
    }

#define Map2_9(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
            else { ARG9; }\
        }\
    }

#define Map2_10(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
            else if( ARG10 ) { ARG9; }\
        }\
    }

#define Map2_11(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
            else if( ARG10 ) { ARG9; }\
            else { ARG11; }\
        }\
    }

/* 3D */
#define Map3( _V_, _I_,_J_,_K_, ...) CONCAT2(Map3_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_,_J_,_K_, ##__VA_ARGS__) 

#define Map3_2(_V_, _I_,_J_,_K_,ARG1,ARG2) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
            }\
        }\
    }

#define Map3_3(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else { ARG3; }\
            }\
        }\
    }
    
#define Map3_4(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
            }\
        }\
    }

#define Map3_5(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else { ARG5; }\
            }\
        }\
    }

#define Map3_6(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
            }\
        }\
    }

#define Map3_7(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else { ARG7; }\
            }\
        }\
    }

#define Map3_8(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
            }\
        }\
    }

#define Map3_9(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
                else { ARG9; }\
            }\
        }\
    }

#define Map3_10(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
                else if( ARG10 ) { ARG9; }\
            }\
        }\
    }

#define Map3_11(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
                else if( ARG10 ) { ARG9; }\
                else { ARG11; }\
            }\
        }\
    }

/* 4D */
#define Map4( _V_, _I_,_J_,_K_,_L_, ...) CONCAT2(Map4_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_,_J_,_K_,_L_, ##__VA_ARGS__) 

#define Map4_2(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                }\
            }\
        }\
    }

#define Map4_3(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else { ARG3; }\
                }\
            }\
        }\
    }
    
#define Map4_4(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                }\
            }\
        }\
    }

#define Map4_5(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else { ARG5; }\
                }\
            }\
        }\
    }

#define Map4_6(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                }\
            }\
        }\
    }

#define Map4_7(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else { ARG7; }\
                }\
            }\
        }\
    }

#define Map4_8(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                }\
            }\
        }\
    }

#define Map4_9(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                    else { ARG9; }\
                }\
            }\
        }\
    }

#define Map4_10(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                    else if( ARG10 ) { ARG9; }\
                }\
            }\
        }\
    }

#define Map4_11(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data.rowi;_I_<_V_##_data.rowe; _I_+=_V_##_data.rowinc){\
        for( _J_=_V_##_data.coli;_J_<_V_##_data.cole; _J_+=_V_##_data.colinc){\
            for( _K_=_V_##_data.pagi;_K_<_V_##_data.page; _K_+=_V_##_data.paginc){\
                for( _L_=_V_##_data.booki;_L_<_V_##_data.booke; _L_+=_V_##_data.bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                    else if( ARG10 ) { ARG9; }\
                    else { ARG11; }\
                }\
            }\
        }\
    }


/************************ MAPPING PTR *****************************/

/* 1D */
#define pMap( _V_, _I_, ...) CONCAT2(Map_ptr_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_, ##__VA_ARGS__) 

#define Map_ptr_2(_V_, _I_,ARG1,ARG2) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
    }

#define Map_ptr_3(_V_, _I_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else { ARG3; }\
    }
    
#define Map_ptr_4(_V_, _I_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
    }

#define Map_ptr_5(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else { ARG5; }\
    }

#define Map_ptr_6(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
    }

#define Map_ptr_7(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else { ARG7; }\
    }

#define Map_ptr_8(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
    }

#define Map_ptr_9(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
        else { ARG9; }\
    }

#define Map_ptr_10(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
        else if( ARG10 ) { ARG9; }\
    }

#define Map_ptr_11(_V_, _I_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        if( ARG2 ) { ARG1; }\
        else if( ARG4 ) { ARG3; }\
        else if( ARG6 ) { ARG5; }\
        else if( ARG8 ) { ARG7; }\
        else if( ARG10 ) { ARG9; }\
        else { ARG11; }\
    }



/* 2D */
#define pMap2( _V_, _I_,_J_, ...) CONCAT2(Map2_ptr_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_,_J_, ##__VA_ARGS__) 

#define Map2_ptr_2(_V_, _I_,_J_,ARG1,ARG2) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
        }\
    }

#define Map2_ptr_3(_V_, _I_,_J_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else { ARG3; }\
        }\
    }
    
#define Map2_ptr_4(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
        }\
    }

#define Map2_ptr_5(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else { ARG5; }\
        }\
    }

#define Map2_ptr_6(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
        }\
    }

#define Map2_ptr_7(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else { ARG7; }\
        }\
    }

#define Map2_ptr_8(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
        }\
    }

#define Map2_ptr_9(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
            else { ARG9; }\
        }\
    }

#define Map2_ptr_10(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
            else if( ARG10 ) { ARG9; }\
        }\
    }

#define Map2_ptr_11(_V_, _I_,_J_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            if( ARG2 ) { ARG1; }\
            else if( ARG4 ) { ARG3; }\
            else if( ARG6 ) { ARG5; }\
            else if( ARG8 ) { ARG7; }\
            else if( ARG10 ) { ARG9; }\
            else { ARG11; }\
        }\
    }

/* 3D */
#define pMap3( _V_, _I_,_J_,_K_, ...) CONCAT2(Map3_ptr_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_,_J_,_K_, ##__VA_ARGS__) 

#define Map3_ptr_2(_V_, _I_,_J_,_K_,ARG1,ARG2) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
            }\
        }\
    }

#define Map3_ptr_3(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else { ARG3; }\
            }\
        }\
    }
    
#define Map3_ptr_4(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
            }\
        }\
    }

#define Map3_ptr_5(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else { ARG5; }\
            }\
        }\
    }

#define Map3_ptr_6(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
            }\
        }\
    }

#define Map3_ptr_7(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else { ARG7; }\
            }\
        }\
    }

#define Map3_ptr_8(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
            }\
        }\
    }

#define Map3_ptr_9(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
                else { ARG9; }\
            }\
        }\
    }

#define Map3_ptr_10(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
                else if( ARG10 ) { ARG9; }\
            }\
        }\
    }

#define Map3_ptr_11(_V_, _I_,_J_,_K_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                if( ARG2 ) { ARG1; }\
                else if( ARG4 ) { ARG3; }\
                else if( ARG6 ) { ARG5; }\
                else if( ARG8 ) { ARG7; }\
                else if( ARG10 ) { ARG9; }\
                else { ARG11; }\
            }\
        }\
    }

/* 4D */
#define pMap4( _V_, _I_,_J_,_K_,_L_, ...) CONCAT2(Map4_ptr_, COUNT_ARGUMENTS(__VA_ARGS__))(_V_,_I_,_J_,_K_,_L_, ##__VA_ARGS__) 

#define Map4_ptr_2(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                }\
            }\
        }\
    }

#define Map4_ptr_3(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else { ARG3; }\
                }\
            }\
        }\
    }
    
#define Map4_ptr_4(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                }\
            }\
        }\
    }

#define Map4_ptr_5(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else { ARG5; }\
                }\
            }\
        }\
    }

#define Map4_ptr_6(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                }\
            }\
        }\
    }

#define Map4_ptr_7(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else { ARG7; }\
                }\
            }\
        }\
    }

#define Map4_ptr_8(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                }\
            }\
        }\
    }

#define Map4_ptr_9(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                    else { ARG9; }\
                }\
            }\
        }\
    }

#define Map4_ptr_10(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                    else if( ARG10 ) { ARG9; }\
                }\
            }\
        }\
    }

#define Map4_ptr_11(_V_, _I_,_J_,_K_,_L_,ARG1,ARG2,ARG3,ARG4,ARG5,ARG6,ARG7,ARG8,ARG9,ARG10,ARG11) \
    for( _I_=_V_##_data->rowi;_I_<_V_##_data->rowe; _I_+=_V_##_data->rowinc){\
        for( _J_=_V_##_data->coli;_J_<_V_##_data->cole; _J_+=_V_##_data->colinc){\
            for( _K_=_V_##_data->pagi;_K_<_V_##_data->page; _K_+=_V_##_data->paginc){\
                for( _L_=_V_##_data->booki;_L_<_V_##_data->booke; _L_+=_V_##_data->bookinc){\
                    if( ARG2 ) { ARG1; }\
                    else if( ARG4 ) { ARG3; }\
                    else if( ARG6 ) { ARG5; }\
                    else if( ARG8 ) { ARG7; }\
                    else if( ARG10 ) { ARG9; }\
                    else { ARG11; }\
                }\
            }\
        }\
    }


/************************************************************************
 *
 *                    MACROS Y FUNCIONES NUMÉRICAS
 *
 ************************************************************************/
 
#define   Is_pos(_X_)    ( ( _X_ ) > 0 )
#define   Is_neg(_X_)    ( ( _X_ ) < 0 )
#define   Is_zero(_X_)        ( ( _X_ ) == 0 )
#define   Is_non_neg(_X_)     ( ( _X_ ) >= 0 )
#define   Is_non_pos(_X_)     ( ( _X_ ) <= 0 )
#define   Is_non_zero(_X_)     ( ( _X_ ) != 0 )
#define   Is_between(_V_,_X_,_Y_)   ( (_V_) >= (_X_) && (_V_) <= (_Y_) )

#define   Not(_X_)           _X_ = _X_ ? 0 : 1;
#define   Max(_X_,_Y_)   ((_X_) < (_Y_) ? (_Y_) : (_X_))
#define   Min(_X_,_Y_)   ((_X_) > (_Y_) ? (_Y_) : (_X_))

#define   Clamp(_V_,_I_,_F_)     ( _V_ > _F_ ) ? _F_ : ( _V_ < _I_ ) ? _I_ : _V_ 
#define   Len_int(_V_)        (int)ceil(log10( ( _V_ ) ))
#define   Degree(_V_)      ( (_V_) * 180.0 / 3.14159265358979323846 )
#define   Radian(_V_)      ( (_V_) * 3.14159265358979323846 / 180.0 )
#define   Seed_by_Time()    do{ time_t tiempo;\
                            srand((unsigned) time(&tiempo)); }while(0);
#define   Seed(_N_)        srand((unsigned int) (_N_));

/* bits mediante macros */
// Bit(x) regresa el bit x puesto a uno y los demas bits en cero, ej. Bit(3) regresa 00001000
#define   Bit(_X_)         ( ( unsigned long ) 1 << ( ( unsigned long )_X_ ))

// GetBit(x,b) regresa el bit b-esimo de x ej. GetBit(n,3)
#define   Get_bit(_X_,_B_)   (( ( unsigned long ) _X_ ) & Bit( _B_ ))

// SetBit(x,b) establece en '1' el bit b de x ej. SetBit(PORTD,4)
#define   Set_bit(_X_,_B_)   (( _X_ ) |= Bit( _B_ ))

// ClearBit(x,b) establece a '0' el bit b de x
#define   Clear_bit(_X_,_B_) (( _X_ ) &= ~Bit( _B_ ))

// ToggleBit(x,b) invierte el valor del bit b de x a su complemento,
#define   Toggle_bit(_X_,_B_)  ((_X_) ^= Bit(_B_))

// SetBitIf(x,b,v) establece el bit b en 1 si valor 'v' es TRUE; sino, establece en 0
#define   Set_bit_if(_V_,_X_,_B_) (( _V_ )? Set_bit(_X_,_B_) : Clear_bit( _X_, _B_ ))
 
// ES_PAR(x) regresa 0 cuando x no es par y algo diferente de 0 cuando es par
#define   Is_even(_X_)   (!Get_bit(_X_,0))

// Y gracias a la magia del XOR, podemos intercambiar el valor de 2 variables
// tipo int o char sin la necesidad de una variable temporal
#define   Swap(_X_,_Y_)  (_X_ = _X_ ^ _Y_ ,  _Y_ = _X_ ^ _Y_ ,  _X_ = _X_ ^ _Y_ )

#define  Set_binsize(_N_)   SIZE_BINARY = ( _N_ );
#define  Unset_binsize      SIZE_BINARY = 0;

// medicion de tiempo
#define   Tic(_X_)            _X_ = clock();
#define   Toc(_X_,_Y_)        _Y_ = ( clock() - (_X_) ) / CLOCKS_PER_SEC;

// año bisiesto 
#define   Is_leap_year(_X_)     ( _X_ % 4 == 0 && _X_ % 100 != 0 ) || ( _X_ % 400 == 0 )

/************************************************************************
 *
 *   LIBRERIA DE MANIPULACION DE NUMEROS
 *
 ************************************************************************/

/* NUMEROS A STRING Y VICEVERSA 
   Esto es usado por MAIN para obtener argumentos únicos desde línea de comandos */

/* STRTONUM */
double __numPow10__( int nPrecision );

/* precision */
double Dbl_prec(double dNum, int Dec);
float Flt_prec(float dNum, int Dec);

/* funcion str2number obtenida del proyecto Harbour */
int __str2number__( int fPCode, const char * szNum, long nLen, long * lVal, double * dVal, int * piDec, int * piWidth );

double Str2dbl( const char* szNum );
float Str2flt( const char* szNum );
long Str2lng( const char* szText );
int Str2int( const char* szText );

int Is_number(const char *);
//long StrE2lng( const char *);
//long long StrE2llng( const char * lineaBuff );
double StrE2dbl( const char *);
long double StrE2ldbl( const char * lineaBuff );
int Is_notation(const char *);

/* NUM2STR */

char * Int2str( int );
char * Lng2str( long );
char * Flt2str( float );
char * Dbl2str( double );

char * Num2notation( double );

/* MATEMATICA */

long double Fact( int );
long Bin2lng( const char * );
long Hex2lng( const char * );
long Oct2lng( const char * );
char * Lng2hex( unsigned long );

char * Lng2bin( unsigned long );
char * Lng2oct( unsigned long );

/************************************************************************
 *
 *   LIBRERIA DE STACK DE STRING, PARA REALIZAR ANIDAMIENTO DE FUNCIONES
 *   DE CADENA.
 *
 ************************************************************************/

/* Funciones de acceso al stack de string. 
   Están disponibles para el usuario, en caso de que quiera definir
   sus propias funciones que usen este stack, y que trabajen con
   strings */

/* saca un string desde el stack, si cBuffer es NULL. cBuffer corresponde
   al argumento de la función, y puede ser tantos argumentos como se
   necesitem */
char * pop_stack_if_null(const char *cBuffer, long * Len, const char *msg, 
                         const char *sub_msg);
/* saca un string desde el stack, pero no devuelve su tamaño */
char * pop_stack_if_null_noLen(const char *cBuffer, const char *msg, 
                         const char *sub_msg);

/* obtiene longitud del string, desde stack o de la variable */
size_t pop_stack_len(const char * cBuffer, const char *msg, const char *sub_msg);

/* saca un string desde el stack */
char * pop_stack_hard(const char *msg, const char *sub_msg);

/* crea espacio en el stack para trabajar sobre él */
void malloc_stack_str(int nLen);

/* mete un string en el stack. */
void push_stack_str(const char * cString);


/************************************************************************
 *
 *                           MACROS DE TERMINAL
 *
 ************************************************************************/


#define  Prnl              putchar('\n');
#define  Flush_key         char r; while( (r = getchar()) != '\n') ;
#define  FlushOut          fflush(stdout);

// macros de inhabilitación de CTRL+C y CTRL+Z:
#define Break_off     signal(SIGINT, SIG_IGN);\
                      signal(SIGTSTP, SIG_IGN);
// habilitación de CTRL+C y CTRL+Z:
#define Break_on      signal(SIGINT, SIG_DFL);\
                      signal(SIGTSTP, SIG_DFL);


#define  Hide_cursor             printf("\033[?25l");FlushOut;
#define  Show_cursor             printf("\033[?25h");FlushOut;
// borra hacia abajo (0), hacia arriba(1), todo(2)
#define  Clr_scr(_X_)            printf("\033[%dJ",_X_);FlushOut;
// borra hacia derecha (0), hacia izquierda(1), toda la linea(2)
#define  Clr_line(_X_)           printf("\033[%dK",_X_);FlushOut;
//clear && printf("\e[3J")
#define  Cls                    printf("\033[2J\033[1;1H\033[3J");FlushOut;
#define  Home                   printf("\033[1;1H");FlushOut;

#define  Print_if(_E_,fmt,_O1_,_O2_)    printf( fmt, (_E_) ? ( _O1_ ) : ( _O2_ ) );

#define  Gotoxy(...) CONCAT2(Gotoxy, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 

#define  Gotoxy2(ARG1,ARG2)       Goto_xy(ARG1,ARG2)
#define  Gotoxy3(ARG1,ARG2,ARG3)  _Move_xy_(&ARG1,ARG2,ARG3)

#define  Goto_xy( _nPosx_, _nPosy_ ) \
 do{\
   int _X_ROW_ = _nPosx_, _X_COL_ = _nPosy_;\
   printf("\033[%d;%dH",_X_ROW_, _X_COL_);\
   SCREEN_ROW = _X_ROW_;\
   SCREEN_COL = _X_COL_;\
 }while(0);

#define  Gotoy(...) CONCAT2(Gotoy, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 

#define  Gotoy1(ARG1)       Goto_y(ARG1)
#define  Gotoy2(ARG1,ARG2)  _Move_y_(&ARG1,ARG2)

#define  Goto_y( _nPosy_ ) \
 do{\
   int _X_COL_ = _nPosy_;\
   printf("\033[%d;%dH",SCREEN_ROW,_X_COL_);\
   SCREEN_COL = _X_COL_;\
 }while(0);

#define  Gotox(...) CONCAT2(Gotox, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 

#define  Gotox1(ARG1)       Goto_x(ARG1)
#define  Gotox2(ARG1,ARG2)  _Move_x_(&ARG1,ARG2)

#define  Goto_x( _nPosx_ ) \
 do{\
   int _X_ROW_ = _nPosx_;\
   printf("\033[%d;%dH",_X_ROW_,SCREEN_COL);\
   SCREEN_ROW = _X_ROW_;\
 }while(0);

//#define  Color_fore(_X_)            printf("\033[38;5;%dm",_X_);
//#define  Color_back(_X_)           printf("\033[48;5;%dm",_X_);

#define  Color_fore(...) CONCAT2(Color_text, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 
#define  Color_text1(_ARG_)          printf("\033[38;5;%dm",_ARG_)
#define  Color_text2(_ARG1_,_ARG2_)  Text_color(&_ARG1_, _ARG2_)

#define  Color_back(...) CONCAT2(Color_back, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 
#define  Color_back1(_ARG_)          printf("\033[48;5;%dm",_ARG_)
#define  Color_back2(_ARG1_,_ARG2_)  Text_background(&_ARG1_, _ARG2_)

#define  Color(_X_,_Y_)           printf("\033[38;5;%dm\033[48;5;%dm",_X_,_Y_)
#define  Color_fore_off             printf("\033[27m");
#define  Reset_color              printf("\033[0m");FlushOut;

#define  Inverse_off            printf("\033[27m");
#define  Inverse                printf("\033[7m");
#define  Underline_off          printf("\033[24m");
#define  Underline              printf("\033[4m");
#define  Italic_off             printf("\033[23m");
#define  Italic                 printf("\033[3m");
#define  Bold_off               printf("\033[22m");
#define  Bold                   printf("\033[1m");

#define  Resize_terminal(_X_,_Y_)    printf("\033[8;%d;%dt",_X_,_Y_);FlushOut;\
                                     Get_size_terminal();
#define  Open_buffer             printf("\033[?1049h\033[H");
#define  Close_buffer            printf("\033[?1049l");

#define  RGB_fore(_X_,_Y_,_Z_)      printf("\033[38;2;%d;%d;%dm",_X_,_Y_,_Z_);
#define  RGB_back(_X_,_Y_,_Z_)     printf("\033[48;2;%d;%d;%dm",_X_,_Y_,_Z_);

#define  Canvas_paper           RGB_back(227,216,181)
#define  Canvas_terminal        RGB_back(7,27,4)
#define  Canvas_old             RGB_back(60,6,19)
#define  Canvas_ocean           RGB_back(72,136,216)
#define  White_pencil           RGB_fore(255,255,255)
#define  Black_pencil           RGB_fore(30,27,10)
#define  Amber_pencil           RGB_fore(243,135,13)
#define  Green_pencil           RGB_fore(121,192,35)


/************************************************************************
 *
 *                LIBRERIA DE ACCESO A VIDEO.
 *
 ************************************************************************/

#define Free_video(_X_)\
   free(_X_.video_mem);


#define Box(...) CONCAT2(Box_multi, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 

#define Box_multi3(ARG1,ARG2,ARG3)       Box_std(ARG1,ARG2,ARG3)
#define Box_multi4(ARG1,ARG2,ARG3,ARG4)  Boxvid(&ARG1,ARG2,ARG3,ARG4)

#define Box_solid(...) CONCAT2(SolidBox, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 

#define SolidBox4(ARG1,ARG2,ARG3,ARG4)       Solid_box_std(ARG1,ARG2,ARG3,ARG4)
#define SolidBox5(ARG1,ARG2,ARG3,ARG4,ARG5)  Solid_box_vid(&ARG1,ARG2,ARG3,ARG4,ARG5)

#define Overlap(_X_)              _Refresh_video_(&_X_)
#define Clear_video(_X_)          _Delete_video_(&_X_)


#define Outvid(_VID_,...) CONCAT2(Print_vid, COUNT_ARGUMENTS(__VA_ARGS__))(_VID_, ##__VA_ARGS__) 

/* solo un string en las coordenadas previstas */
#define Print_vid1(_VID_,_STR_)  Printvid_str(&_VID_,_STR_);

/* string en coordenadas y con color */
#define Print_vid2(_VID_,_STR_,_COLOR_)  Printvid_c(&_VID_,_STR_,_COLOR_);

/* string en coordenadas y con color */
#define Print_vid3(_VID_,_FIL_,_COL_,_STR_)  Printvid_xy(&_VID_,_FIL_,_COL_,_STR_);

/* string en coordenadas y con color */
#define Print_vid4(_VID_,_FIL_,_COL_,_STR_,_COLOR_)  Printvid_all(&_VID_,_FIL_,_COL_,_STR_,_COLOR_);

/* refresco */
#define Refresh(_X_)      _Refresh_vid_(&_X_)
#define Flush(_X_)        _Flush_vid_(&_X_)

#define Vline(...) CONCAT2(v_line, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 
#define v_line2(_W_,_T_)       Vert_line_std( _W_, _T_ )
#define v_line3(_V_,_W_,_T_)   Vert_line_vid(&_V_, _W_, _T_ )

#define Hline(...) CONCAT2(h_line, COUNT_ARGUMENTS(__VA_ARGS__))(__VA_ARGS__) 
#define h_line2(_W_,_T_)        Horz_line_std( _W_, _T_ )
#define h_line3(_V_,_W_,_T_)    Horz_line_vid(&_V_, _W_, _T_ )

#define Reset_text(_X_)    _Reset_text_(&_X_)


/* cajas */
#define  DOUB_ALL       0  /*  ╔═══╗
                               ╚═══╝  */
#define  SING_ALL       1  /*  ┌───┐
                               └───┘  */ 
#define  HDOUB_VDOUB    0      
#define  HSING_VSING    1

#define  HSING_VDOUB    2  /*  ╓───╖
                               ╙───╜  */
#define  HDOUB_VSING    3  /*  ╒═══╕
                               ╘═══╛  */
#define  SOLID_BOX      4

/* lineas */
#define  SING_DS        4  /*  ╤    
                               ┴  ╟──┤ */

#define  SING_SD        5  /*  ┬
                               ╧  ├──╢ */

#define  DOUB_DS        6  /*  ╦
                               ╨  ╠══╡ */
#define  DOUB_SD        7  /*  ╥
                               ╩  ╞══╣ */


#define  LINE_VERT      0
#define  LINE_HORZ      1


void Init_video( GD_VIDEO * video);

void Text_background(GD_VIDEO * video, int nColor);
void Text_color(GD_VIDEO * video, int nColor);
void _Reset_text_(GD_VIDEO * video);

void Printvid_str(GD_VIDEO * video, const char * msg);
void Printvid_c(GD_VIDEO * video, const char * msg, int nColor);
void Printvid_xy(GD_VIDEO * video, int row, int col, const char * msg);
void Printvid_all(GD_VIDEO * video, int row, int col, const char * msg, int nColor);

void _Move_xy_(GD_VIDEO * video, int row, int col);
void _Move_x_(GD_VIDEO * video, int row);
void _Move_y_(GD_VIDEO * video, int col);

void _Delete_video_(GD_VIDEO * video);
void _Refresh_video_(GD_VIDEO * video);
void _Refresh_vid_(GD_VIDEO * video);
void _Flush_vid_(GD_VIDEO * video);

void Define_box(int tipoBox, char **horiz, char **cornT, char **cornTR, char **cornB, char **cornBR, char **lateral);
void Define_line(int tipoBox, int dir, char **HL, char **HR, char **B);

void Horz_line_std(int w, int tipoLine );
void Vert_line_std(int h, int tipoLine );
void Horz_line_vid(GD_VIDEO * video, int w, int tipoLine );
void Vert_line_vid(GD_VIDEO * video, int h, int tipoLine );

void Boxvid(GD_VIDEO * video, int h, int w, int tipoBox );
void Box_std(int h, int w, int tipoBox );
void Solid_box_std(int h, int w, int colorF, int colorB);
void Solid_box_vid(GD_VIDEO * video, int h, int w, int colorF, int colorB);

int Get_choice( char * menu[], int valid[], int condicion[], int len, int hBox, 
                int colorf, int colorb, int hlfore, int hlback );

int Get_cursor_raw(int *rows, int *cols);
int Get_cursor_tty(int *rows, int *cols);

/*********************************************************************************************

                            DEFINICIONES PARA USO BASICO DE MOUSE

 *********************************************************************************************/
#define PRESS_RIGHT   40000
#define PRESS_LEFT    10000
#define PRESS_MIDDLE  20000

#define SELECT   0
#define BUTTOM   1
#define BUTTOM_EYE    2
#define BUTTOM_PINBALL    3
#define RADIO_BUTTOM    4
#define TABS   5
#define FIELD   6
#define CHOICE   7
#define CONTROL   8


#define Free_object_mouse(_X_)    Free_total_array_mt(_X_)
#define Base_object_mouse(_X_)    New_mt_array(_X_)


#define  Is_range_mouse(_FILA_,_COLI_,_COLF_) \
   Is_between( MPOS_COL, (_COLI_), (_COLF_) ) && MPOS_ROW == (_FILA_) 

#define  Is_range_box(_FILAI_,_COLI_,_FILAF_,_COLF_) \
   Is_between( MPOS_COL, (_COLI_), (_COLF_) ) && \
   Is_between( MPOS_ROW, (_FILAI_), (_FILAF_) )

#define  Is_range_box_excluding(_FILAI_,_COLI_,_FILAF_,_COLF_) \
   ( !Is_between( MPOS_COL, (_COLI_), (_COLF_) ) && \
      Is_between( MPOS_ROW, (_FILAI_), (_FILAF_) ) ) || \
   (  Is_between( MPOS_COL, (_COLI_), (_COLF_) ) && \
     !Is_between( MPOS_ROW, (_FILAI_), (_FILAF_) ) ) || \
   ( !Is_between( MPOS_COL, (_COLI_), (_COLF_) ) && \
     !Is_between( MPOS_ROW, (_FILAI_), (_FILAF_) ) )

#define  Waiting_some_clic(_X_) \
   while((_X_ = Get_event_mouse()) != EOF)

void Clear_box(int row, int col, int alto, int ancho);

/* campos */
MT_CELL * Add_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int row, int col, ...);
MT_CELL *  Replace_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int pos /*int row, int col*/, const char * msg);
char * Get_field(MT_CELL * Fld, DS_ARRAY *Fld_data, int posicion);
MT_CELL *  Clear_field(MT_CELL * Fld, DS_ARRAY * Fld_data, int pos /*int row, int col*/);
MT_CELL *  Clear_all_field(MT_CELL * Fld, DS_ARRAY * Fld_data);

/* objetos mouse */
int Status_object( MT_CELL* mObj );
int Disable_object( MT_CELL* mObj );
int Enable_object( MT_CELL* mObj );

int Status_item_menu(  MT_CELL* mObj, int item );
int Enable_item_menu( MT_CELL* mObj, int item );
int Disable_item_menu( MT_CELL* mObj, int item );
int Change_item_menu( MT_CELL* mObj, const char *nuevo_item, int item );

MT_CELL * New_object_mouse( DS_ARRAY * array_data, int typeObject, ... );
int Object_mouse( MT_CELL* mObj );
void Put_object_mouse( MT_CELL * mObj );

int __Universal_mouse_handler__(Gpm_Event *event, void *data);
int Init_mouse(Gpm_Connect * conn);
int Get_event_mouse();
void Close_mouse();


/*********************************************************************************************

                            DEFINICIONES PARA ARRAYS MULTITIPO

 *********************************************************************************************/

/* definiciones arrays multitipo */

#define __Init_Global_MT_Array__(_X_)\
  do{\
     Is_ok=1;\
     _X_ = ( MT_CELL * ) malloc( sizeof( MT_CELL ) * _X_##_data.len );\
     if( _X_ ) { int i;\
         for( i=0; i < _X_##_data.len; i++){\
            _X_[i].type = int_TYPE;\
            _X_[i].value = malloc(sizeof(int));\
            *( (int *) (_X_[i].value )) = ( int ) ( 0 );\
         }\
     }else{\
         Msg_red("as_mt_array : no hay memoria para <"#_X_">(MALLOC)"); Is_ok=0;break;\
     }\
  }while(0);

/* inicialmente, declara el espacio del array de acuerdo con DIM */
#define as_mt_array(_X_) \
    MT_CELL * _X_ = NULL;\
    Define_Global_Array(_X_)\
    _X_##_data.type = MULTI_TYPE;\
    __Init_Global_MT_Array__(_X_)

/* declara un array vacío */                     
#define New_mt_array(_X_)  \
    MT_CELL *_X_ = NULL;\
    Define_New_Array(_X_)\
    _X_##_data.type = MULTI_TYPE;

/* añade un valor numerico signado al array */
#define Append_mt(_X_, _TIPO_, _V_) \
    Is_ok=1;\
    _X_ = ( MT_CELL * ) realloc( (void *) _X_, sizeof( MT_CELL ) * ( ++_X_##_data.len ) );\
    if( _X_ ) {\
        _X_[_X_##_data.len - 1].type = _TIPO_##_TYPE;\
        _X_[_X_##_data.len - 1].value = malloc(sizeof(_TIPO_));\
        *( (_TIPO_ *) (_X_[_X_##_data.len - 1].value )) = ( _TIPO_ ) ( _V_ );\
    }else {Msg_red("Append_mt : no hay memoria para <"#_X_">(REALLOC)");Is_ok=0;}

/* añade un valor numerico unsigned al array */
#define uAppend_mt(_X_, _TIPO_, _V_) \
    Is_ok=1;\
    _X_ = ( MT_CELL * ) realloc( (void *) _X_, sizeof( MT_CELL ) * ( ++_X_##_data.len ) );\
    if( _X_ ) {\
        _X_[_X_##_data.len - 1].type = unsigned_##_TIPO_##_TYPE;\
        _X_[_X_##_data.len - 1].value = malloc(sizeof(unsigned _TIPO_));\
        *( (unsigned _TIPO_ *) (_X_[_X_##_data.len - 1].value )) = ( unsigned _TIPO_ ) ( _V_ );\
    }else {Msg_red("uAppend_mt : no hay memoria para <"#_X_">(REALLOC)");Is_ok=0;}

/* añade un valor numerico signado al array con metadata apuntada */
#define pAppend_mt(_X_, _TIPO_, _V_) \
    Is_ok=1;\
    _X_ = ( MT_CELL * ) realloc( (void *) _X_, sizeof( MT_CELL ) * ( ++_X_##_data->len ) );\
    if( _X_ ) {\
        _X_[_X_##_data->len - 1].type = _TIPO_##_TYPE;\
        _X_[_X_##_data->len - 1].value = malloc(sizeof(_TIPO_));\
        *( (_TIPO_ *) (_X_[_X_##_data->len - 1].value )) = ( _TIPO_ ) ( _V_ );\
    }else {Msg_red("pAppend_mt : no hay memoria para <"#_X_">(REALLOC)");Is_ok=0;}

/* añade un valor numerico unsigned al array con metadata apuntada */
#define puAppend_mt(_X_, _TIPO_, _V_) \
    Is_ok=1;\
    _X_ = ( MT_CELL * ) realloc( (void *) _X_, sizeof( MT_CELL ) * ( ++_X_##_data->len ) );\
    if( _X_ ) {\
        _X_[_X_##_data->len - 1].type = unsigned_##_TIPO_##_TYPE;\
        _X_[_X_##_data->len - 1].value = malloc(sizeof(_TIPO_));\
        *( (unsigned _TIPO_ *) (_X_[_X_##_data->len - 1].value )) = ( unsigned _TIPO_ ) ( _V_ );\
    }else {Msg_red("puAppend_mt : no hay memoria para <"#_X_">(REALLOC)");Is_ok=0;}

/* añade un valor string a un array MT */
#define sAppend_mt(_X_,_V_) \
    Is_ok=1;\
    _X_ = ( MT_CELL * ) realloc( (void *) _X_, sizeof( MT_CELL ) * ( ++_X_##_data.len ) );\
    if( _X_ ) {\
        _X_[_X_##_data.len - 1].type = string_TYPE;\
        _X_[_X_##_data.len - 1].value = calloc(strlen(_V_)+1,1);\
        strcpy( (char *) (_X_[_X_##_data.len - 1].value ),  _V_ );\
    }else { Msg_red("Append_mt_str : no hay memoria para <"#_X_">(REALLOC)"); Is_ok=0;}

/* añade un valor string a un array MT apuntado */
#define psAppend_mt(_X_,_V_) \
    Is_ok=1;\
    _X_ = ( MT_CELL * ) realloc( (void *) _X_, sizeof( MT_CELL ) * ( ++_X_##_data->len ) );\
    if( _X_ ) {\
        _X_[_X_##_data->len - 1].type = string_TYPE;\
        _X_[_X_##_data->len - 1].value = calloc(strlen(_V_)+1,1);\
        strcpy( (char *) (_X_[_X_##_data->len - 1].value ),  _V_ );\
    }else { Msg_red("pAppend_mt_str : no hay memoria para <"#_X_">(REALLOC)"); Is_ok=0;}

/* liberación del cuerpo del array, pero puede seguir añadiéndose elementos en el */
#define pFree_array_mt(_X_)  \
   do{\
      int i;\
      for ( i = 0; i < _X_##_data->len; i++){ free(_X_[i].value);} \
      Set_zeros_metadata_delete_array_ptr(_X_)\
   }while(0);

#define Free_array_mt(_X_)  \
   do{\
      int i;\
      for ( i = 0; i < _X_##_data.len; i++){ free(_X_[i].value);} \
      Set_zeros_metadata_delete_array(_X_)\
   }while(0);


#define pFree_only_array_mt(_X_)  \
   do{\
      int i;\
      for ( i = 0; i < _X_##_data->len; i++){ free(_X_[i].value);} \
   }while(0);

#define Free_only_array_mt(_X_)  \
   do{\
      int i;\
      for ( i = 0; i < _X_##_data.len; i++){ free(_X_[i].value);} \
   }while(0);


/* liberación del array completo */
#define pFree_total_array_mt(_X_)  \
   do{\
      int i;\
      for ( i = 0; i < _X_##_data->len; i++){ free(_X_[i].value);} free(_X_);\
      Set_zeros_metadata_delete_array_ptr(_X_)\
   }while(0);

#define Free_total_array_mt(_X_)  \
   do{\
      int i;\
      for ( i = 0; i < _X_##_data.len; i++){ free(_X_[i].value);} free(_X_);\
      Set_zeros_metadata_delete_array(_X_)\
   }while(0);


/* libera elementos del array MT */

#define pFree_mt(_X_, ...) CONCAT2(pFree_mt, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pFree_mt2(_X_,ARG1,ARG2)  \
   do{\
      int __Index__ = ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 );\
      if(_X_[ __Index__ ].value) \
         { free(_X_[ __Index__ ].value); \
           _X_[ __Index__ ].value=NULL; \
           _X_[ __Index__ ].type=0;\
         }\
   }while(0);

#define pFree_mt3(_X_,ARG1,ARG2,ARG3)  \
   do{\
      int __Index__ = ( ( ARG1 ) * _X_##_data->cols + ( ARG2 ) ) + ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows );\
      if(_X_[ __Index__ ].value)\
         { free(_X_[ __Index__ ].value); \
           _X_[ __Index__ ].value=NULL; \
           _X_[ __Index__ ].type=0;\
         }\
   }while(0);

#define Free_mt(_X_, ...) CONCAT2(Free_mt, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)
 
#define Free_mt1(_X_,ARG1)  \
   if(_X_[ARG1].value)\
      { free(_X_[ARG1].value); _X_[ARG1].value=NULL; _X_[ARG1].type=0;}

#define Free_mt2(_X_,ARG1,ARG2)  \
   do{\
      int __Index__ = ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 );\
      if(_X_[ __Index__ ].value) \
         { free(_X_[ __Index__ ].value);\
           _X_[ __Index__ ].value=NULL; \
           _X_[ __Index__ ].type=0;\
         }\
   }while(0);

#define Free_mt3(_X_,ARG1,ARG2,ARG3) \
   do{\
      int __Index__ = ( ( ARG1 ) * _X_##_data.cols + ( ARG2 ) ) + ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows );\
      if(_X_[ __Index__ ].value) \
         { free(_X_[ __Index__ ].value);\
           _X_[ __Index__ ].value=NULL; \
           _X_[ __Index__ ].type=0;\
         }\
   }while(0);

/* acceso a celdas MT */

#define iCell(_X_,...) CONCAT2(Cell_mtint, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell_mtint1(_X_,ARG1)             *((int *)(_X_[ ARG1 ].value))
#define Cell_mtint2(_X_,ARG1,ARG2)        *((int *)(_X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].value))
#define Cell_mtint3(_X_,ARG1,ARG2,ARG3)   *((int *)(_X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].value))

#define fCell(_X_,...) CONCAT2(Cell_mtflt, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell_mtflt1(_X_,ARG1)             *((float *)(_X_[ ARG1 ].value))
#define Cell_mtflt2(_X_,ARG1,ARG2)        *((float *)(_X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].value))
#define Cell_mtflt3(_X_,ARG1,ARG2,ARG3)   *((float *)(_X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].value))

#define dCell(_X_,...) CONCAT2(Cell_mtdbl, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell_mtdbl1(_X_,ARG1)              *((double *)(_X_[ ARG1 ].value))
#define Cell_mtdbl2(_X_,ARG1,ARG2)         *((double *)(_X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].value))
#define Cell_mtdbl3(_X_,ARG1,ARG2,ARG3)    *((double *)(_X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].value))

#define lCell(_X_,...) CONCAT2(Cell_mtlng, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell_mtlng1(_X_,ARG1)              *((long *)(_X_[ ARG1 ].value))
#define Cell_mtlng2(_X_,ARG1,ARG2)         *((long *)(_X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].value))
#define Cell_mtlng3(_X_,ARG1,ARG2,ARG3)    *((long *)(_X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].value))

#define uiCell(_X_,...) CONCAT2(Cell_mtuint, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell_mtuint1(_X_,ARG1)             *((unsigned int *)(_X_[ ARG1 ].value))
#define Cell_mtuint2(_X_,ARG1,ARG2)        *((unsigned int *)(_X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].value))
#define Cell_mtuint3(_X_,ARG1,ARG2,ARG3)   *((unsigned int *)(_X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + \
                                            ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].value))

#define ulCell(_X_,...) CONCAT2(Cell_mtulng, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell_mtulng1(_X_,ARG1)             *((unsigned long *)(_X_[ ARG1 ].value))
#define Cell_mtulng2(_X_,ARG1,ARG2)        *((unsigned long *)(_X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].value))
#define Cell_mtulng3(_X_,ARG1,ARG2,ARG3)   *((unsigned long *)(_X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + \
                                            ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].value))

#define sCell(_X_,...) CONCAT2(Cell_mtstr, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define Cell_mtstr1(_X_,ARG1)              (_X_[ ARG1 ].value)
#define Cell_mtstr2(_X_,ARG1,ARG2)         (_X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].value)
#define Cell_mtstr3(_X_,ARG1,ARG2,ARG3)    (_X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].value)

/* acceso con apuntadores */
#define piCell(_X_,...) CONCAT2(pCell_mtint, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell_mtint2(_X_,ARG1,ARG2)        *((int *)(_X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].value))
#define pCell_mtint3(_X_,ARG1,ARG2,ARG3)   *((int *)(_X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows ) ].value))

#define pfCell(_X_,...) CONCAT2(pCell_mtflt, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell_mtflt2(_X_,ARG1,ARG2)        *((float *)(_X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].value))
#define pCell_mtflt3(_X_,ARG1,ARG2,ARG3)   *((float *)(_X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows ) ].value))

#define pdCell(_X_,...) CONCAT2(pCell_mtdbl, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell_mtdbl2(_X_,ARG1,ARG2)        *((double *)(_X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].value))
#define pCell_mtdbl3(_X_,ARG1,ARG2,ARG3)   *((double *)(_X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows ) ].value))

#define plCell(_X_,...) CONCAT2(pCell_mtlng, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell_mtlng2(_X_,ARG1,ARG2)        *((long *)(_X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].value))
#define pCell_mtlng3(_X_,ARG1,ARG2,ARG3)   *((long *)(_X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows ) ].value))

#define puiCell(_X_,...) CONCAT2(pCell_mtuint, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell_mtuint2(_X_,ARG1,ARG2)        *((unsigned int *)(_X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].value))
#define pCell_mtuint3(_X_,ARG1,ARG2,ARG3)   *((unsigned int *)(_X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + \
                                            ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows ) ].value))

#define pulCell(_X_,...) CONCAT2(pCell_mtulng, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell_mtulng2(_X_,ARG1,ARG2)        *((unsigned long *)(_X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].value))
#define pCell_mtulng3(_X_,ARG1,ARG2,ARG3)   *((unsigned long *)(_X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + \
                                            ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows ) ].value))

#define psCell(_X_,...) CONCAT2(pCell_mtstr, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pCell_mtstr2(_X_,ARG1,ARG2)        (_X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].value)
#define pCell_mtstr3(_X_,ARG1,ARG2,ARG3)   (_X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + \
                                           ( ARG3 ) * ( _X_##_data->cols * _X_##_data->rows ) ].value)


/* tipo de cada elemento del MT array. sirve para obtener el tipo, y para asignar un tipo nuevo */
#define Cell_type(_X_, ...) CONCAT2(MTType, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define MTType1(_X_,ARG1)              _X_[ ARG1 ].type
#define MTType2(_X_,ARG1,ARG2)         _X_[ ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ].type
#define MTType3(_X_,ARG1,ARG2,ARG3)    _X_[ ( ( ARG1 ) * ( _X_##_data.cols ) + ( ARG2 ) ) + ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].type

#define pCell_type(_X_, ...) CONCAT2(pMTType, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define pMTType2(_X_,ARG1,ARG2)         _X_[ ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ].type
#define pMTType3(_X_,ARG1,ARG2,ARG3)    _X_[ ( ( ARG1 ) * ( _X_##_data->cols ) + ( ARG2 ) ) + ( ARG3 ) * ( _X_##_data.cols * _X_##_data.rows ) ].type


/* Para asignar un valor a un elemento, si este valor es del mismo tipo, se puede hacer una asignacion
   simple o usar Let en el caso de un string.
   Para cambiar el tipo de la celda según el valor asignado, se deben usar las siguientes macros */


#define Chg(_X_,_TIPO_,...) CONCAT2(MTChg, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,_TIPO_,##__VA_ARGS__)

#define MTChg2(_X_,_TIPO_,_I_,_V_)   \
    do{\
        Free_mt(_X_,_I_);\
        int __Index__ = (_I_);\
        _X_[ __Index__ ].type = _TIPO_##_TYPE;\
        _X_[ __Index__ ].value = malloc(sizeof(_TIPO_));\
        *( (_TIPO_ *) (_X_[ __Index__ ].value )) = ( _TIPO_ ) ( _V_ );\
    }while(0);

#define MTChg3(_X_,_TIPO_,_I_,_J_,_V_)   \
    do{\
        int __Index__ = (_I_)*_X_##_data.cols + (_J_);\
        Free_mt(_X_,_I_,_J_);\
        _X_[ __Index__ ].type = _TIPO_##_TYPE;\
        _X_[ __Index__ ].value = (_TIPO_*) malloc(sizeof(_TIPO_));\
        *( (_TIPO_ *) (_X_[ __Index__ ].value )) = ( _TIPO_ ) ( _V_ );\
    }while(0);

#define MTChg4(_X_,_TIPO_,_I_,_J_,_K_,_V_)   \
    do{\
        int __Index__ = ((_I_)*_X_##_data.cols + (_J_))+(_K_)*(_X_##_data.cols*_X_##_data.rows);\
        Free_mt(_X_,_I_,_J_,_K_);\
        _X_[ __Index__ ].type = _TIPO_##_TYPE;\
        _X_[ __Index__ ].value = malloc(sizeof(_TIPO_));\
        *( (_TIPO_ *) (_X_[ __Index__ ].value )) = ( _TIPO_ ) ( _V_ );\
    }while(0);

#define sChg(_X_,...) CONCAT2(MTChgstr, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,##__VA_ARGS__)

#define MTChgstr2(_X_,_I_,_V_)   \
    do{\
        int __long__ = strlen(_V_);\
        Free_mt(_X_,_I_);\
        _X_[ _I_ ].type = string_TYPE;\
        _X_[ _I_ ].value = (char*)calloc( __long__ + 1, 1);\
        memcpy((char *)(_X_[(_I_)].value), _V_, __long__);\
    }while(0);

#define MTChgstr3(_X_,_I_,_J_,_V_)   \
    do{\
        int __Index__ = (_I_)*_X_##_data.cols + (_J_);\
        int __long__ = strlen(_V_);\
        Free_mt(_X_,_I_,_J_);\
        _X_[ __Index__ ].type = string_TYPE;\
        _X_[ __Index__ ].value = (char*)calloc( __long__ + 1, 1);\
        memcpy((char *)(_X_[ __Index__ ].value), _V_, __long__);\
    }while(0);

#define MTChgstr4(_X_,_I_,_J_,_K_,_V_)   \
    do{\
        int __long__ = strlen(_V_);\
        int __Index__ = ((_I_)*_X_##_data.cols + (_J_))+(_K_)*(_X_##_data.cols*_X_##_data.rows);\
        Free_mt(_X_,_I_,_J_,_K_);\
        _X_[ __Index__ ].type = string_TYPE;\
        _X_[ __Index__ ].value = (char*)calloc( __long__ + 1, 1);\
        memcpy((char *)(_X_[ __Index__ ].value), _V_, __long__);\
    }while(0);


/* Chg con punteros en metdata */
#define pChg(_X_,_TIPO_,...) CONCAT2(MTpChg, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,_TIPO_,##__VA_ARGS__)

#define MTpChg3(_X_,_TIPO_,_I_,_J_,_V_)   \
    do{\
        int __Index__ = (_I_)*_X_##_data->cols + (_J_);\
        Free_mt(_X_,_I_,_J_);\
        _X_[ __Index__ ].type = _TIPO_##_TYPE;\
        _X_[ __Index__ ].value = malloc(sizeof(_TIPO_));\
        *( (_TIPO_ *) (_X_[ __Index__ ].value )) = ( _TIPO_ ) ( _V_ );\
    }while(0);

#define MTpChg4(_X_,_TIPO_,_I_,_J_,_K_,_V_)   \
    do{\
        int __Index__ = ((_I_)*_X_##_data->cols + (_J_))+(_K_)*(_X_##_data->cols*_X_##_data->rows);\
        Free_mt(_X_,_I_,_J_,_K_);\
        _X_[ __Index__ ].type = _TIPO_##_TYPE;\
        _X_[ __Index__ ].value = malloc(sizeof(_TIPO_));\
        *( (_TIPO_ *) (_X_[ __Index__ ].value )) = ( _TIPO_ ) ( _V_ );\
    }while(0);

#define psChg(_X_,...) CONCAT2(MTpChgstr, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,##__VA_ARGS__)

#define MTpChgstr2(_X_,_I_,_V_)   \
    do{\
        int __Index__ = (_I_);\
        int __long__ = strlen(_V_);\
        Free_mt(_X_,_I_);\
        _X_[ __Index__ ].type = string_TYPE;\
        _X_[ __Index__ ].value = (char*)calloc( __long__ + 1, 1);\
        memcpy((char *)(_X_[ __Index__ ].value), _V_, __long__);\
    }while(0);
    
#define MTpChgstr3(_X_,_I_,_J_,_V_)   \
    do{\
        int __Index__ = (_I_)*_X_##_data->cols + (_J_);\
        int __long__ = strlen(_V_);\
        Free_mt(_X_,_I_,_J_);\
        _X_[ __Index__ ].type = string_TYPE;\
        _X_[ __Index__ ].value = (char*)calloc( __long__ + 1, 1);\
        memcpy((char *)(_X_[ __Index__ ].value), _V_, __long__);\
    }while(0);

#define MTpChgstr4(_X_,_I_,_J_,_K_,_V_)   \
    do{\
        int __long__ = strlen(_V_);\
        int __Index__ = ((_I_)*_X_##_data->cols + (_J_))+(_K_)*(_X_##_data->cols*_X_##_data->rows);\
        Free_mt(_X_,_I_,_J_,_K_);\
        _X_[ __Index__ ].type = string_TYPE;\
        _X_[ __Index__ ].value = (char*)calloc( __long__ + 1, 1);\
        memcpy((char *)(_X_[ __Index__ ].value), _V_, __long__);\
    }while(0);


/* Cambia el tipo de una celda numérica */

#define Chg_type(_X_,...) CONCAT2(MTChgType, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,##__VA_ARGS__)

#define MTChgType3(_X_,_I_,_TIPO_ORIG_,_TIPO_DEST_)\
    do{\
        int __Index__ = (_I_);\
        _TIPO_DEST_ var = (_TIPO_DEST_ ) *((_TIPO_ORIG_ *) (_X_[(__Index__)].value));\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
        *((_TIPO_DEST_ *) (_X_[__Index__].value)) = (_TIPO_DEST_) var;\
    }while(0);

#define MTChgType4(_X_,_I_,_J_,_TIPO_ORIG_,_TIPO_DEST_)\
    do{\
        int __Index__ = (_I_)*_X_##_data.cols + (_J_);\
        _TIPO_DEST_ var = (_TIPO_DEST_ ) *((_TIPO_ORIG_ *) (_X_[(__Index__)].value));\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
        *((_TIPO_DEST_ *) (_X_[__Index__].value)) = (_TIPO_DEST_) var;\
    }while(0);

#define MTChgType5(_X_,_I_,_J_,_K_,_TIPO_ORIG_,_TIPO_DEST_)\
    do{\
        int __Index__ = ((_I_)*_X_##_data.cols + (_J_))+(_K_)*(_X_##_data.cols*_X_##_data.rows);\
        _TIPO_DEST_ var = (_TIPO_DEST_ ) *((_TIPO_ORIG_ *) (_X_[(__Index__)].value));\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
        *((_TIPO_DEST_ *) (_X_[__Index__].value)) = (_TIPO_DEST_) var;\
    }while(0);

/* CHT_type on punteros */

#define pChg_type(_X_,...) CONCAT2(MTpChgType, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,##__VA_ARGS__)

#define MTpChgType4(_X_,_I_,_J_,_TIPO_ORIG_,_TIPO_DEST_)\
    do{\
        int __Index__ = (_I_)*_X_##_data->cols + (_J_);\
        _TIPO_DEST_ var = (_TIPO_DEST_ ) *((_TIPO_ORIG_ *) (_X_[(__Index__)].value));\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
        *((_TIPO_DEST_ *) (_X_[__Index__].value)) = (_TIPO_DEST_) var;\
    }while(0);

#define MTpChgType5(_X_,_I_,_J_,_K_,_TIPO_ORIG_,_TIPO_DEST_)\
    do{\
        int __Index__ = ((_I_)*_X_##_data->cols + (_J_))+(_K_)*(_X_##_data->cols*_X_##_data->rows);\
        _TIPO_DEST_ var = (_TIPO_DEST_ ) *((_TIPO_ORIG_ *) (_X_[(__Index__)].value));\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
        *((_TIPO_DEST_ *) (_X_[__Index__].value)) = (_TIPO_DEST_) var;\
    }while(0);

/* Cambia el tipo de celda de string a numérico. El valor desaparece */

#define sChg_type(_X_,...) CONCAT2(MTsChgType, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,##__VA_ARGS__)

#define MTsChgType2(_X_,_I_,_TIPO_DEST_)\
    do{\
        int __Index__ = (_I_);\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
    }while(0);

#define MTsChgType3(_X_,_I_,_J_,_TIPO_DEST_)\
    do{\
        int __Index__ = (_I_)*_X_##_data.cols + (_J_);\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
    }while(0);

#define MTsChgType4(_X_,_I_,_J_,_K_,_TIPO_DEST_)\
    do{\
        int __Index__ = ((_I_)*_X_##_data.cols + (_J_))+(_K_)*(_X_##_data.cols*_X_##_data.rows);\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
    }while(0);

/* Cambia el tipo de celda string a numerico con punteros */
#define psChg_type(_X_,...) CONCAT2(MTpsChgType, COUNT_ARGUMENTS(__VA_ARGS__))(_X_,##__VA_ARGS__)

#define MTpsChgType3(_X_,_I_,_J_,_TIPO_DEST_)\
    do{\
        int __Index__ = (_I_)*_X_##_data->cols + (_J_);\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
    }while(0);

#define MTpsChgType4(_X_,_I_,_J_,_K_,_TIPO_DEST_)\
    do{\
        int __Index__ = ((_I_)*_X_##_data->cols + (_J_))+(_K_)*(_X_##_data->cols*_X_##_data->rows);\
        Free_mt(_X_, __Index__);\
        _X_[__Index__].value = malloc(sizeof(_TIPO_DEST_));\
        _X_[__Index__].type = _TIPO_DEST_##_TYPE;\
    }while(0);



/* Imprime una celda de array MT */

#define Print_Cell(_X_,...) CONCAT2(PrintMTByTypeRaw, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define PrintMTByTypeRaw1(_X_,_I_) \
    do{\
        int __Type_Cell__ = Cell_type(_X_,_I_);\
        switch( __Type_Cell__ ) {\
            case int_TYPE :           {printf( "%d",iCell(_X_,_I_) ); break;}\
            case float_TYPE :         {if(DEC_PREC) printf( "%.*f", DEC_PREC, fCell(_X_,_I_) ); \
                                       else if(SET_DBL_NOT) printf( "%g", fCell(_X_,_I_) ); \
                                       else         printf( "%f", fCell(_X_,_I_) ); \
                                       break;}\
            case double_TYPE :        {if(DEC_PREC) printf( "%.*lf",DEC_PREC, dCell(_X_,_I_) ); \
                                       else if(SET_DBL_NOT) printf( "%g", dCell(_X_,_I_) ); \
                                       else         printf( "%lf", dCell(_X_,_I_) ); \
                                       break;}\
            case long_TYPE :          {printf( "%ld", lCell(_X_,_I_) ); break;}\
            case unsigned_int_TYPE :  {printf( "%d", uiCell(_X_,_I_) ); break;}\
            case unsigned_long_TYPE : {printf( "%ld", ulCell(_X_,_I_) ); break;}\
            case string_TYPE:         {printf( "%s", (char*)sCell(_X_,_I_) ); break;}\
            case MULTI_TYPE:             {printf( "<matrix-MT>" ); break;}\
        }\
    }while(0);

#define PrintMTByTypeRaw2(_X_,_I_,_J_) \
    do{\
        int __Type_Cell__ = Cell_type(_X_,_I_,_J_);\
        switch( __Type_Cell__ ) {\
            case int_TYPE :           {printf( "%d", iCell(_X_,_I_,_J_) ); break;}\
            case float_TYPE :         {if(DEC_PREC) printf( "%.*f", DEC_PREC,fCell(_X_,_I_,_J_) ); \
                                       else if(SET_DBL_NOT) printf( "%g", fCell(_X_,_I_,_J_) ); \
                                       else         printf( "%f", fCell(_X_,_I_,_J_) ); \
                                       break;}\
            case double_TYPE :        {if(DEC_PREC) printf( "%.*lf", DEC_PREC, dCell(_X_,_I_,_J_) ); \
                                       else if(SET_DBL_NOT) printf( "%g", dCell(_X_,_I_,_J_) ); \
                                       else         printf( "%lf", dCell(_X_,_I_,_J_) );\
                                       break;}\
            case long_TYPE :          {printf( "%ld", lCell(_X_,_I_,_J_) ); break;}\
            case unsigned_int_TYPE :  {printf( "%d", uiCell(_X_,_I_,_J_) ); break;}\
            case unsigned_long_TYPE : {printf( "%ld", ulCell(_X_,_I_,_J_) ); break;}\
            case string_TYPE:         {printf( "%s", (char*)sCell(_X_,_I_,_J_) ); break;}\
            case MULTI_TYPE:             {printf( "<matrix-MT>" ); break;}\
        }\
    }while(0);

#define PrintMTByTypeRaw3(_X_,_I_,_J_,_K_) \
    do{\
        int __Type_Cell__ = Cell_type(_X_,_I_,_J_,_K_);\
        switch( __Type_Cell__ ) {\
            case int_TYPE :           {printf( "%d", iCell(_X_,_I_,_J_,_K_) ); break;}\
            case float_TYPE :         {if(DEC_PREC) printf( "%.*f", DEC_PREC,fCell(_X_,_I_,_J_,_K_) ); \
                                       else if(SET_DBL_NOT) printf( "%g", fCell(_X_,_I_,_J_,_K_) ); \
                                       else         printf( "%f", fCell(_X_,_I_,_J_,_K_) ); \
                                       break;}\
            case double_TYPE :        {if(DEC_PREC) printf( "%.*lf", DEC_PREC,dCell(_X_,_I_,_J_,_K_) );\
                                       else if(SET_DBL_NOT) printf( "%g", dCell(_X_,_I_,_J_,_K_) ); \
                                       else         printf( "%lf", dCell(_X_,_I_,_J_,_K_) );\
                                       break;}\
            case long_TYPE :          {printf( "%ld", lCell(_X_,_I_,_J_,_K_) ); break;}\
            case unsigned_int_TYPE :  {printf( "%d", uiCell(_X_,_I_,_J_,_K_) ); break;}\
            case unsigned_long_TYPE : {printf( "%ld", ulCell(_X_,_I_,_J_,_K_) ); break;}\
            case string_TYPE:         {printf( "%s", (char*)sCell(_X_,_I_,_J_,_K_) ); break;}\
            case MULTI_TYPE:             {printf( "<matrix-MT>" ); break;}\
        }\
    }while(0);

/* imprime una celda con punteros */
#define pPrint_Cell(_X_,...) CONCAT2(PrintMTpByTypeRaw, COUNT_ARGUMENTS(__VA_ARGS__))(_X_, ##__VA_ARGS__)

#define PrintMTpByTypeRaw2(_X_,_I_,_J_) \
    do{\
        int __Type_Cell__ = Cell_type(_X_,_I_,_J_);\
        switch( __Type_Cell__ ) {\
            case int_TYPE :           {printf( "%d", piCell(_X_,_I_,_J_) ); break;}\
            case float_TYPE :         {if(DEC_PREC) printf( "%.*f", DEC_PREC,pfCell(_X_,_I_,_J_) );\
                                       else if(SET_DBL_NOT) printf( "%g", fCell(_X_,_I_,_J_) ); \
                                       else         printf( "%f", pfCell(_X_,_I_,_J_) );\
                                       break;}\
            case double_TYPE :        {if(DEC_PREC) printf( "%.*lf", DEC_PREC, pdCell(_X_,_I_,_J_) );\
                                       else if(SET_DBL_NOT) printf( "%g", fCell(_X_,_I_,_J_) ); \
                                       else         printf( "%lf", pdCell(_X_,_I_,_J_) );\
                                       break;}\
            case long_TYPE :          {printf( "%ld", plCell(_X_,_I_,_J_) ); break;}\
            case unsigned_int_TYPE :  {printf( "%d", puiCell(_X_,_I_,_J_) ); break;}\
            case unsigned_long_TYPE : {printf( "%ld", pulCell(_X_,_I_,_J_) ); break;}\
            case string_TYPE:         {printf( "%s", (char*)psCell(_X_,_I_,_J_) ); break;}\
            case MULTI_TYPE:             {printf( "<matrix-MT>" ); break;}\
        }\
    }while(0);

#define PrintMTpByTypeRaw3(_X_,_I_,_J_,_K_) \
    do{\
        int __Type_Cell__ = Cell_type(_X_,_I_,_J_,_K_);\
        switch( __Type_Cell__ ) {\
            case int_TYPE :           {printf( "%d", piCell(_X_,_I_,_J_,_K_) ); break;}\
            case float_TYPE :         {if(DEC_PREC) printf( "%.*f", DEC_PREC,pfCell(_X_,_I_,_J_,_K_) ); \
                                       else if(SET_DBL_NOT) printf( "%g", fCell(_X_,_I_,_J_,_K_) ); \
                                       else         printf( "%f",pfCell(_X_,_I_,_J_,_K_) ); \
                                       break;}\
            case double_TYPE :        {if(DEC_PREC) printf( "%.*lf", DEC_PREC,pdCell(_X_,_I_,_J_,_K_) ); \
                                       else if(SET_DBL_NOT) printf( "%g", dCell(_X_,_I_,_J_,_K_) ); \
                                       else         printf( "%lf",pdCell(_X_,_I_,_J_,_K_) ); \
                                       break;}\
            case long_TYPE :          {printf( "%ld", plCell(_X_,_I_,_J_,_K_) ); break;}\
            case unsigned_int_TYPE :  {printf( "%d", puiCell(_X_,_I_,_J_,_K_) ); break;}\
            case unsigned_long_TYPE : {printf( "%ld", pulCell(_X_,_I_,_J_,_K_) ); break;}\
            case string_TYPE:         {printf( "%s", (char*)psCell(_X_,_I_,_J_,_K_) ); break;}\
            case MULTI_TYPE:             {printf( "<matrix-MT>" ); break;}\
        }\
    }while(0);

/* otras definiciones */

// para cargar un archivo en una matriz MT:
#define DET_LONG     1
#define ALL_DOUBLE   0

/* para macros de impresion de celdas MT */
#define Set_double_notation     SET_DBL_NOT=1;
#define Unset_notation          SET_DBL_NOT=0;

MT_CELL *Load_matrix_mt(MT_CELL * array, DS_ARRAY * array_data, char * cFile, F_STAT _ST_, int DetectLong);
int Save_matrix_mt(MT_CELL * array, DS_ARRAY array_data, char * cFile );

MT_CELL * Append_lst_mt(MT_CELL * array, DS_ARRAY * array_data, MT_CELL * APND, DS_ARRAY APND_data);
MT_CELL * Append_col_mt(MT_CELL * array, DS_ARRAY * array_data, MT_CELL * APND, DS_ARRAY APND_data);
MT_CELL * Append_row_mt(MT_CELL * array, DS_ARRAY * array_data, MT_CELL * APND, DS_ARRAY APND_data);

MT_CELL * Insert_lst_mt(MT_CELL * array, DS_ARRAY * array_data, 
                        MT_CELL * APND,  DS_ARRAY * APND_data, int __rToIns__);
MT_CELL * Insert_row_mt(MT_CELL * array, DS_ARRAY * array_data, 
                        MT_CELL * APND,  DS_ARRAY * APND_data, int __rToIns__);
MT_CELL * Insert_col_mt(MT_CELL * array, DS_ARRAY * array_data, 
                        MT_CELL * APND, DS_ARRAY *APND_data, int __cToIns__);

MT_CELL * Delete_lst_mt(MT_CELL * array, DS_ARRAY * array_data, int __rToDel__);
MT_CELL * Delete_row_mt(MT_CELL * array, DS_ARRAY * array_data, int __rToDel__);
MT_CELL * Delete_col_mt(MT_CELL * array, DS_ARRAY * array_data, int __cToDel__);

MT_CELL * Zap_range_mt(MT_CELL * array, DS_ARRAY * array_data);

/* EOF */

