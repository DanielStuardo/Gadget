/************************************************************************
 *
 *   LIBRERIA DE MANIPULACION DE ARRAYS
 *
 ************************************************************************/


//#ifndef _LIB_GADGET_MAIN_

//#ifdef GENLIB_GADGET
#include "../include/gadget.h"
//#else
//#include <gadget/gadget.h>
//#endif


//#endif

//#include <gadget/gadget_array.h>

/* establece token para uso global */
extern char * __TOKEN__;

/* maxima longitud de buffer de lectura de archivo */
extern int MAX_LENGTH_READ;

/* linspaced y sequence */
extern int SIZE_LINSPACED;
extern int SIZE_SEQUENCE;

/* coordenadas de array globales */
extern int GLOBAL_ARR_ROWS;
extern int GLOBAL_ARR_COLS;
extern int GLOBAL_ARR_PAGS;
extern int GLOBAL_ARR_BOOKS;
extern int GLOBAL_ARR_DIM;

/* para algunas macros que necesitan indicar cómo salió */
extern int Is_ok;


/* comparacion entre arrays */
int  Equal_arrays(void* X, DS_ARRAY *X_data, void*Y, DS_ARRAY *Y_data){

   int _SW_=1;
   if( X_data->len == Y_data->len && X_data->type == Y_data->type){
       switch(X_data->type){
           case INTEGER: {
              int * tmpX = X;
              int * tmpY = Y;
              int i;
              for ( i=0; i< X_data->len; i++) {
                 if( * (tmpX + i) != * (tmpY + i) ){
                    _SW_=0; break;
                 }
              } break;
           }case FLOAT: {
              float * tmpX = X;
              float * tmpY = Y;
              int i;
              for( i=0; i < X_data->len; i++){
                 if( * (tmpX + i) != * (tmpY + i) ){
                    _SW_=0; break;
                 }
              } break;
           }case DOUBLE: {
              double * tmpX = X;
              double * tmpY = Y;
              int i;
              for( i=0; i < X_data->len; i++){
                 if( * (tmpX + i) != * (tmpY + i) ){
                    _SW_=0; break;
                 }
              } break;
           }case LONG: {
              long * tmpX = X;
              long * tmpY = Y;
              int i;
              for( i=0; i < X_data->len; i++){
                 if( * (tmpX + i) != * (tmpY + i) ){
                    _SW_=0; break;
                 }
              } break;
           }case UINTEGER: {
              unsigned int * tmpX = X;
              unsigned int * tmpY = Y;
              int i;
              for ( i=0; i< X_data->len; i++) {
                 if( * (tmpX + i) != * (tmpY + i) ){
                    _SW_=0; break;
                 }
              } break;
           }case ULONG: {
              unsigned long * tmpX = X;
              unsigned long * tmpY = Y;
              int i;
              for(i=0; i < X_data->len; i++){
                 if( * (tmpX + i) != * (tmpY + i) ){
                    _SW_=0; break;
                 }
              } break;
           }case STRING: {
              char ** tmpX = X;
              char ** tmpY = Y;
              int i;
              for( i=0; i < X_data->len; i++){
                 if( strcmp( * (tmpX + i), * (tmpY + i) )!=0 ){
                    _SW_=0; break;
                 }
              } break;
           }
       }
   }else _SW_=0;
   return _SW_;
}


/* GETCOORD */
void Get_coor_2(long nPos, DS_ARRAY * mat_data, int *r, int *c){
   *r = (int)(trunc(nPos/mat_data->cols));
   *c = (int)fmod(nPos,mat_data->cols);
}

void Get_coor_3(long nPos, DS_ARRAY * mat_data, int *r, int *c, int *p ){

   *c = (int)fmod(nPos,mat_data->cols);
   int tf = (int)(trunc(nPos/mat_data->cols));
      
   *p = (int)trunc(tf/mat_data->rows);
   *r = (int)fmod(tf,mat_data->rows);
}

void Get_coor_4(long nPos, DS_ARRAY * mat_data, int *r, int *c, int *p, int *b ){
   // TODO: esto debe ser reescrito a una fórmula.
   
   int n2D = mat_data->rows * mat_data->cols;
   int n3D = mat_data->rows * mat_data->cols * mat_data->pags;

   for ( *b=0; *b<mat_data->books; *b = *b + 1)
       for ( *p=0; *p<mat_data->pags; *p = *p + 1)
           for ( *r=0; *r<mat_data->rows; *r = *r + 1)
               for ( *c=0; *c<mat_data->cols; *c = *c + 1){
                   if ( nPos == (*r * mat_data->cols + *c)+(*p * n2D) + (*b * n3D) ){
                       goto salir_plis;
                   }
               }
   salir_plis:
    ++nPos;
}

/* APPEND_HARD
   añade elementos con datos "en duro". Ejemplo:
    
   array = (char **)Append_hlst_string( SDS_ptr(array), "hola","mundo","hueco",NULL);
   
   esto añadirá a la lista los elementos 10,20,30...60.
   */

char ** Append_hlst_string(char **X, DS_ARRAY * X_data, char * dato,...){
   psAppend(X, dato);
   
   va_list va;
   va_start( va, dato );
   char * tmp = va_arg(va, char *);
   while( tmp ){
       psAppend(X, tmp);
       tmp = va_arg(va, char *);
   }
   va_end( va );
   return X;
}
char ** Append_hrow_string(char ** array, DS_ARRAY * array_data,...){
    
    if(array_data->len>0){  
        if(array_data->rows == 0) array_data->rows=1;
        if(array_data->cols == 0) array_data->cols=array_data->len;
    }  
    
    va_list va;
    va_start( va, array_data );
    int nLen=0;
    char * str = va_arg(va, char *);
    while( str ){
       psAppend(array, str);++nLen;
       str = va_arg(va, char *);
    }
    va_end( va );
    array_data->rows++;
    array_data->cols=nLen;
    array_data->dims=2;
    return array;
}

char ** Append_hcol_string(char ** array, DS_ARRAY * array_data,...){

    if( !array_data->rows && !array_data->cols ){  // array vacio o lista
       if( array_data->len==0 ){ //vacio
          New_str_array(Temp);
          va_list va;
          va_start( va, array_data );

          int nLen=0;
          char * str = va_arg(va, char *);
          while( str ){
             sAppend(Temp, str);++nLen;
             str = va_arg(va, char *);
          }
          va_end( va );
          array_data->rows=Temp_data.len;
          array_data->len=Temp_data.len;
          array_data->cols=1;
          array_data->dims=2;
          return Temp;
       }else{  // lista
          //printf("PASA! dims=%d, len=%d\n",array_data->dims,array_data->len);
          Dim(array_data->len, 2);
          as_str_array(Temp);
          va_list va;
          va_start( va, array_data );
          int i;
          for( i=0; i < array_data->len; i++){
              Let( Cell(Temp,i,0), Cell(array,i) );
          }
          for( i=0; i < Temp_data.rows; i++){
              char * str = va_arg(va, char *);
              if( str ){
                  Let( Cell(Temp,i,1), str );
              } // no es necesario un else
          }
          va_end( va );
          Free_str_ptr_only_array(array);
          array_data->rows=Temp_data.rows;
          array_data->cols=Temp_data.cols;
          array_data->len = Temp_data.len;
          array_data->dims=2;
          return Temp;
       }
    }else {   // significa que tienen rows y cols, porque no existe uno sin el otro

       Dim(array_data->rows, array_data->cols+1);
       as_str_array(Temp);
       va_list va;
       va_start( va, array_data );
       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < array_data->cols; j++){
               Let( Cell(Temp,i,j), pCell(array,i,j) );
           }
           char * str = va_arg(va, char *);
           if( str ){
               Let( Cell(Temp,i,Temp_data.cols-1), str );
           } // no es necesario un else
       }
       va_end( va );
       Free_str_ptr_only_array(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
    }
}

/* INSERT
   inserta elementos en un array, listas, filas y columnas */

/* funciones INSERT_COL */

char **Insert_col_string(char ** array, DS_ARRAY * array_data, 
                         char **APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1);
       as_str_array(Temp);
       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               Let( Cell(Temp,i,j), pCell(array,i,j) );
           }
           Let( Cell(Temp,i,__cToIns__), APND[i] );
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               Let( Cell(Temp,i,jCol), pCell(array,i,j) );
               jCol++;
           }
       }

       Free_str_ptr_only_array(array);
       array_data->rows=Temp_data.rows;
       array_data->cols++;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

unsigned long* Insert_col_ulong(unsigned long* array, DS_ARRAY * array_data, 
                                        unsigned long* APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1);
       as_unsigned_array(Temp, long);
       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           Cell(Temp,i,__cToIns__) = APND[i];
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols++;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

unsigned int* Insert_col_uint(unsigned int* array, DS_ARRAY * array_data, 
                                      unsigned int* APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1);
       as_unsigned_array(Temp, int);

       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           Cell(Temp,i,__cToIns__) = APND[i];
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols++;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

long* Insert_col_long(long* array, DS_ARRAY * array_data, 
                      long* APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1);
       as_array(Temp, long);

       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           Cell(Temp,i,__cToIns__) = APND[i];
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols++;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

int* Insert_col_int(int* array, DS_ARRAY * array_data, 
                    int* APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1);
       as_array(Temp, int);

       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           Cell(Temp,i,__cToIns__) = APND[i];
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols++;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

float* Insert_col_float(float* array, DS_ARRAY * array_data, 
                        float* APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1);
       as_array(Temp, float);

       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           Cell(Temp,i,__cToIns__) = APND[i];
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols++;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

double* Insert_col_double(double* array, DS_ARRAY * array_data, 
                          double* APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1);
       as_array(Temp, double);

       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           Cell(Temp,i,__cToIns__) = APND[i];
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols++;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

/* funcion MASTER */
void * Insert_col(void* array, DS_ARRAY * array_data, void* APND, DS_ARRAY *APND_data, int __pToDel__){
   switch(array_data->type){
       case INTEGER: {
          array = Insert_col_int( (int *) array, array_data, 
                                  (int *) APND, APND_data, __pToDel__ ); break;
       }case FLOAT: {
          array = Insert_col_float( (float *) array, array_data, 
                                    (float *) APND, APND_data, __pToDel__ ); break;
       }case DOUBLE: {
          array = Insert_col_double( (double *) array, array_data, 
                                     (double *) APND, APND_data, __pToDel__ ); break;
       }case LONG: {
          array = Insert_col_long( (long *) array, array_data, 
                                   (long *) APND, APND_data, __pToDel__ ); break;
       }case UINTEGER: {
          array = Insert_col_uint( (unsigned int *) array, array_data, 
                                           (unsigned int *) APND, APND_data, __pToDel__ ); break;
       }case ULONG: {
          array = Insert_col_ulong( (unsigned long *) array, array_data, 
                                            (unsigned long *) APND, APND_data, __pToDel__ ); break;
       }case STRING: {
          array = Insert_col_string( (char **) array, array_data, 
                                     (char **) APND, APND_data, __pToDel__ ); break;
       }
   }
   return array;
}



/* funciones INSERT_ROW */

char **Insert_row_string(char ** array, DS_ARRAY * array_data, 
                         char **APND, DS_ARRAY *APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols);
       as_str_array(Temp);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               Let( Cell(Temp,i,j), pCell(array,i,j) );
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           Let( Cell(Temp,__rToIns__,jCol), APND[i] );
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Let( Cell(Temp,jRow,j), pCell(array,i,j) );
           }
           jRow++;
       }
       Free_str_ptr_only_array(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

unsigned long* Insert_row_ulong(unsigned long* array, DS_ARRAY * array_data, 
                                        unsigned long* APND, DS_ARRAY *APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols);
       as_unsigned_array(Temp, long);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           Cell(Temp,__rToIns__,jCol) = APND[i];
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,jRow,j) = pCell(array,i,j);
           }
           jRow++;
       }
       free(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

unsigned int* Insert_row_uint(unsigned int* array, DS_ARRAY * array_data, 
                                      unsigned int* APND, DS_ARRAY *APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols);
       as_unsigned_array(Temp, int);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           Cell(Temp,__rToIns__,jCol) = APND[i];
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,jRow,j) = pCell(array,i,j);
           }
           jRow++;
       }
       free(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

long* Insert_row_long(long* array, DS_ARRAY * array_data, 
                      long* APND, DS_ARRAY *APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols);
       as_array(Temp, long);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           Cell(Temp,__rToIns__,jCol) = APND[i];
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,jRow,j) = pCell(array,i,j);
           }
           jRow++;
       }
       free(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

int* Insert_row_int(int* array, DS_ARRAY * array_data, 
                    int* APND, DS_ARRAY *APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols);
       as_array(Temp, int);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           Cell(Temp,__rToIns__,jCol) = APND[i];
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,jRow,j) = pCell(array,i,j);
           }
           jRow++;
       }
       free(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

float* Insert_row_float(float* array, DS_ARRAY * array_data, 
                        float* APND, DS_ARRAY *APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols);
       as_array(Temp, float);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           Cell(Temp,__rToIns__,jCol) = APND[i];
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,jRow,j) = pCell(array,i,j);
           }
           jRow++;
       }
       free(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

double* Insert_row_double(double* array, DS_ARRAY * array_data, 
                          double* APND, DS_ARRAY *APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols);
       as_array(Temp, double);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           Cell(Temp,__rToIns__,jCol) = APND[i];
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,jRow,j) = pCell(array,i,j);
           }
           jRow++;
       }
       free(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }
   return array;
}

/* funcion MASTER */
void * Insert_row(void* array, DS_ARRAY * array_data, void* APND, DS_ARRAY *APND_data, int __pToDel__){
   switch(array_data->type){
       case INTEGER: {
          array = Insert_row_int( (int *) array, array_data, 
                                  (int *) APND, APND_data, __pToDel__ ); break;
       }case FLOAT: {
          array = Insert_row_float( (float *) array, array_data, 
                                    (float *) APND, APND_data, __pToDel__ ); break;
       }case DOUBLE: {
          array = Insert_row_double( (double *) array, array_data, 
                                     (double *) APND, APND_data, __pToDel__ ); break;
       }case LONG: {
          array = Insert_row_long( (long *) array, array_data, 
                                   (long *) APND, APND_data, __pToDel__ ); break;
       }case UINTEGER: {
          array = Insert_row_uint( (unsigned int *) array, array_data, 
                                           (unsigned int *) APND, APND_data, __pToDel__ ); break;
       }case ULONG: {
          array = Insert_row_ulong( (unsigned long *) array, array_data, 
                                            (unsigned long *) APND, APND_data, __pToDel__ ); break;
       }case STRING: {
          array = Insert_row_string( (char **) array, array_data, 
                                     (char **) APND, APND_data, __pToDel__ ); break;
       }
   }
   return array;
}

/* funciones INSERT_LST */

unsigned int* Insert_lst_uint(unsigned int* array, DS_ARRAY * array_data, 
                                      unsigned int* APND, DS_ARRAY *APND_data, int __cToIns__){

   if(__cToIns__>=0 && __cToIns__<array_data->len){
      New_unsigned_array(Temp, int);
      int i;
      for( i=0; i < __cToIns__; i++){
          uAppend( Temp, int,pCell(array,i) );
      }
      
      for( i=0; i < APND_data->len; i++){
         uAppend(Temp, int,APND[i]);
      }
      for( i=__cToIns__; i < array_data->len; i++){
         uAppend( Temp, int, pCell(array,i) );
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
   }
   return array;
}

int* Insert_lst_int(int* array, DS_ARRAY * array_data, 
                    int* APND, DS_ARRAY *APND_data, int __cToIns__){

   if(__cToIns__>=0 && __cToIns__<array_data->len){
      New_array(Temp, int);
      int i;
      for( i=0; i < __cToIns__; i++){
          Append( Temp, int,pCell(array,i) );
      }
      
      for( i=0; i < APND_data->len; i++){
         Append(Temp, int,APND[i]);
      }
      for( i=__cToIns__; i < array_data->len; i++){
         Append( Temp, int, pCell(array,i) );
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
   }
   return array;
}

long* Insert_lst_long(long* array, DS_ARRAY * array_data, 
                      long* APND, DS_ARRAY *APND_data, int __cToIns__){

   if(__cToIns__>=0 && __cToIns__<array_data->len){
      New_array(Temp, long);
      int i;
      for( i=0; i < __cToIns__; i++){
          Append( Temp, long,pCell(array,i) );
      }
      
      for( i=0; i < APND_data->len; i++){
         Append(Temp, long,APND[i]);
      }
      for( i=__cToIns__; i < array_data->len; i++){
         Append( Temp, long, pCell(array,i) );
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
   }
   return array;
}

unsigned long* Insert_lst_ulong(unsigned long* array, DS_ARRAY * array_data, 
                                        unsigned long* APND, DS_ARRAY *APND_data, int __cToIns__){

   if(__cToIns__>=0 && __cToIns__<array_data->len){
      New_unsigned_array(Temp, long);
      int i;
      for( i=0; i < __cToIns__; i++){
          uAppend( Temp, long,pCell(array,i) );
      }
      
      for( i=0; i < APND_data->len; i++){
         uAppend(Temp, long,APND[i]);
      }
      for( i=__cToIns__; i < array_data->len; i++){
         uAppend( Temp, long, pCell(array,i) );
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
   }
   return array;
}

float* Insert_lst_float(float* array, DS_ARRAY * array_data, 
                        float* APND, DS_ARRAY *APND_data, int __cToIns__){

   if(__cToIns__>=0 && __cToIns__<array_data->len){
      New_array(Temp, float);
      int i;
      for( i=0; i < __cToIns__; i++){
          Append( Temp, float,pCell(array,i) );
      }
      
      for( i=0; i < APND_data->len; i++){
         Append(Temp, float,APND[i]);
      }
      for( i=__cToIns__; i < array_data->len; i++){
         Append( Temp, float, pCell(array,i) );
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
   }
   return array;
}

double* Insert_lst_double(double* array, DS_ARRAY * array_data, 
                          double* APND, DS_ARRAY *APND_data, int __cToIns__){

   if(__cToIns__>=0 && __cToIns__<array_data->len){
      New_array(Temp, double);
      int i;
      for( i=0; i < __cToIns__; i++){
          Append( Temp, double, pCell(array,i) );
      }
      
      for( i=0; i < APND_data->len; i++){
         Append(Temp, double, APND[i]);
      }
      for( i=__cToIns__; i < array_data->len; i++){
         Append( Temp, double, pCell(array,i) );
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
   }
   return array;
}

char ** Insert_lst_string(char ** array, DS_ARRAY * array_data, char **APND, DS_ARRAY *APND_data,
                          int __cToIns__){

   if(__cToIns__>=0 && __cToIns__<array_data->len){
      New_str_array(Temp);
      int i;
      for( i=0; i < __cToIns__; i++){
          sAppend( Temp, pCell(array,i) );
      }
      
      for( i=0; i < APND_data->len; i++){
         sAppend(Temp, APND[i]);
      }
      for( i=__cToIns__; i < array_data->len; i++){
         sAppend( Temp, pCell(array,i) );
      }
      Free_str_ptr_only_array(array);
      array_data->len=Temp_data.len;
      return Temp;
   }
   return array;
}

/* funcion MASTER */
void * Insert_lst(void* array, DS_ARRAY * array_data, void* APND, DS_ARRAY *APND_data, int __pToDel__){
   switch(array_data->type){
       case INTEGER: {
          array = Insert_lst_int( (int *) array, array_data, 
                                  (int *) APND, APND_data, __pToDel__ ); break;
       }case FLOAT: {
          array = Insert_lst_float( (float *) array, array_data, 
                                    (float *) APND, APND_data, __pToDel__ ); break;
       }case DOUBLE: {
          array = Insert_lst_double( (double *) array, array_data, 
                                     (double *) APND, APND_data, __pToDel__ ); break;
       }case LONG: {
          array = Insert_lst_long( (long *) array, array_data, 
                                   (long *) APND, APND_data, __pToDel__ ); break;
       }case UINTEGER: {
          array = Insert_lst_uint( (unsigned int *) array, array_data, 
                                           (unsigned int *) APND, APND_data, __pToDel__ ); break;
       }case ULONG: {
          array = Insert_lst_ulong( (unsigned long *) array, array_data, 
                                            (unsigned long *) APND, APND_data, __pToDel__ ); break;
       }case STRING: {
          array = Insert_lst_string( (char **) array, array_data, 
                                     (char **) APND, APND_data, __pToDel__ ); break;
       }
   }
   return array;
}



/* DELETE
   borra elementos de un array, listas, filas y columnas */

/* funciones DELETE_LST */

int* Delete_lst_int(int* array, DS_ARRAY * array_data,int __cToDel__){

   if(__cToDel__>=0 && __cToDel__<array_data->len){
      if( array_data->len-1 == 0 ){
          pFree_array(array);
      }else{
      Dim(array_data->len-1);
      as_array(Temp, int);
      int i;
      if( __cToDel__ < array_data->len){
         for( i=0; i < __cToDel__; i++){
             Cell(Temp,i) = pCell(array,i);
         }
         for( i=__cToDel__; i < array_data->len-1; i++){
             Cell(Temp,i) = pCell(array,i+1);
         }
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
      }
   }
   return array;
}

unsigned int* Delete_lst_uint(unsigned int* array, DS_ARRAY * array_data,int __cToDel__){

   if(__cToDel__>=0 && __cToDel__<array_data->len){
      if( array_data->len-1 == 0 ){
          pFree_array(array);
      }else{
      Dim(array_data->len-1);
      as_unsigned_array(Temp, int);
      int i;
      if( __cToDel__ < array_data->len){
         for( i=0; i < __cToDel__; i++){
             Cell(Temp,i) = pCell(array,i);
         }
         for( i=__cToDel__; i < array_data->len-1; i++){
             Cell(Temp,i) = pCell(array,i+1);
         }
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
      }
   }
   return array;
}

float* Delete_lst_float(float* array, DS_ARRAY * array_data,int __cToDel__){

   if(__cToDel__>=0 && __cToDel__<array_data->len){
      if( array_data->len-1 == 0 ){
          pFree_array(array);
      }else{
      Dim(array_data->len-1);
      as_array(Temp, float);
      int i;
      if( __cToDel__ < array_data->len){
         for( i=0; i < __cToDel__; i++){
             Cell(Temp,i) = pCell(array,i);
         }
         for( i=__cToDel__; i < array_data->len-1; i++){
             Cell(Temp,i) = pCell(array,i+1);
         }
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
      }
   }
   return array;
}


double* Delete_lst_double(double* array, DS_ARRAY * array_data,int __cToDel__){

   if(__cToDel__>=0 && __cToDel__<array_data->len){
      if( array_data->len-1 == 0 ){
          pFree_array(array);
      }else{
      Dim(array_data->len-1);
      as_array(Temp, double);
      int i;
      if( __cToDel__ < array_data->len){
         for( i=0; i < __cToDel__; i++){
             Cell(Temp,i) = pCell(array,i);
         }
         for( i=__cToDel__; i < array_data->len-1; i++){
             Cell(Temp,i) = pCell(array,i+1);
         }
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
      }
   }
   return array;
}

long* Delete_lst_long(long* array, DS_ARRAY * array_data,int __cToDel__){

   if(__cToDel__>=0 && __cToDel__<array_data->len){
      if( array_data->len-1 == 0 ){
          pFree_array(array);
      }else{
      Dim(array_data->len-1);
      as_array(Temp, long);
      int i;
      if( __cToDel__ < array_data->len){
         for( i=0; i < __cToDel__; i++){
             Cell(Temp,i) = pCell(array,i);
         }
         for( i=__cToDel__; i < array_data->len-1; i++){
             Cell(Temp,i) = pCell(array,i+1);
         }
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
      }
   }
   return array;
}

unsigned long* Delete_lst_ulong(unsigned long* array, DS_ARRAY * array_data,int __cToDel__){

   if(__cToDel__>=0 && __cToDel__<array_data->len){
      if( array_data->len-1 == 0 ){
          pFree_array(array);
      }else{
      Dim(array_data->len-1);
      as_unsigned_array(Temp, long);
      int i;
      if( __cToDel__ < array_data->len){
         for( i=0; i < __cToDel__; i++){
             Cell(Temp,i) = pCell(array,i);
         }
         for( i=__cToDel__; i < array_data->len-1; i++){
             Cell(Temp,i) = pCell(array,i+1);
         }
      }
      free(array);
      array_data->len=Temp_data.len;
      return Temp;
      }
   }
   return array;
}

char **Delete_lst_string(char ** array, DS_ARRAY * array_data,int __cToDel__){

   if(__cToDel__>=0 && __cToDel__<array_data->len){
      if( array_data->len-1 == 0 ){
          Free_str_ptr_array(array);
      }else{
      Dim(array_data->len-1);
      as_str_array(Temp);
      int i;
      if( __cToDel__ < array_data->len){
         for( i=0; i < __cToDel__; i++){
             Let( Cell(Temp,i), pCell(array,i) );
         }
         for( i=__cToDel__; i < array_data->len-1; i++){
             Let( Cell(Temp,i), pCell(array,i+1) );
         }
      }
      Free_str_ptr_only_array(array);
      array_data->len=Temp_data.len;
      return Temp;
      }
   }
   return array;
}

/* funcion MASTER */
void * Delete_lst(void* array, DS_ARRAY * array_data,int __pToDel__){
   switch(array_data->type){
       case INTEGER: {
          array = Delete_lst_int( (int *) array, array_data, __pToDel__ ); break;
       }case FLOAT: {
          array = Delete_lst_float( (float *) array, array_data, __pToDel__ ); break;
       }case DOUBLE: {
          array = Delete_lst_double( (double *) array, array_data, __pToDel__ ); break;
       }case LONG: {
          array = Delete_lst_long( (long *) array, array_data, __pToDel__ ); break;
       }case UINTEGER: {
          array = Delete_lst_uint( (unsigned int *) array, array_data, __pToDel__ ); break;
       }case ULONG: {
          array = Delete_lst_ulong( (unsigned long *) array, array_data, __pToDel__ ); break;
       }case STRING: {
          array = Delete_lst_string( (char **) array, array_data, __pToDel__ ); break;
       }
   }
   return array;
}

/* funciones DELETE_COL */

unsigned int* Delete_col_uint(unsigned int* array, DS_ARRAY * array_data,int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows, array_data->cols-1);
       as_unsigned_array(Temp, int);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

int* Delete_col_int(int* array, DS_ARRAY * array_data,int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows, array_data->cols-1);
       as_array(Temp, int);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

float* Delete_col_float(float* array, DS_ARRAY * array_data,int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows, array_data->cols-1);
       as_array(Temp, float);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

double* Delete_col_double(double* array, DS_ARRAY * array_data,int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows, array_data->cols-1);
       as_array(Temp, double);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

long* Delete_col_long(long* array, DS_ARRAY * array_data,int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows, array_data->cols-1);
       as_array(Temp, long);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

unsigned long* Delete_col_ulong(unsigned long* array, DS_ARRAY * array_data,int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows, array_data->cols-1);
       as_unsigned_array(Temp, long);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               Cell(Temp,i,jCol) = pCell(array,i,j);
               jCol++;
           }
       }

       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

char **Delete_col_string(char ** array, DS_ARRAY * array_data,int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           psFree_array(array);
       }else{
       Dim(array_data->rows, array_data->cols-1);
       as_str_array(Temp);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               Let( Cell(Temp,i,j), pCell(array,i,j) );
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               Let( Cell(Temp,i,jCol), pCell(array,i,j) );
               jCol++;
           }
       }

       Free_str_ptr_only_array(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

/* funcion MASTER */
void * Delete_col(void* array, DS_ARRAY * array_data,int __cToDel__){
   switch(array_data->type){
       case INTEGER: {
          array = Delete_col_int( (int *) array, array_data, __cToDel__ ); break;
       }case FLOAT: {
          array = Delete_col_float( (float *) array, array_data, __cToDel__ ); break;
       }case DOUBLE: {
          array = Delete_col_double( (double *) array, array_data, __cToDel__ ); break;
       }case LONG: {
          array = Delete_col_long( (long *) array, array_data, __cToDel__ ); break;
       }case UINTEGER: {
          array = Delete_col_uint( (unsigned int *) array, array_data, __cToDel__ ); break;
       }case ULONG: {
          array = Delete_col_ulong( (unsigned long *) array, array_data, __cToDel__ ); break;
       }case STRING: {
          array = Delete_col_string( (char **) array, array_data, __cToDel__ ); break;
       }
   }
   return array;
}

/* DELETE_ROW */

int *Delete_row_int(int* array, DS_ARRAY * array_data,int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows-1, array_data->cols);
       as_array(Temp, int);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,iRow,j) = pCell(array,i,j);
           }
           iRow++;
       }
       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}


unsigned int *Delete_row_uint(unsigned int* array, DS_ARRAY * array_data,int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows-1, array_data->cols);
       as_unsigned_array(Temp, int);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,iRow,j) = pCell(array,i,j);
           }
           iRow++;
       }
       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

float *Delete_row_float(float* array, DS_ARRAY * array_data,int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           pFree_array(array);
       }else{

       Dim(array_data->rows-1, array_data->cols);
       as_array(Temp, float);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,iRow,j) = pCell(array,i,j);
           }
           iRow++;
       }
       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}


double *Delete_row_double(double* array, DS_ARRAY * array_data,int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           pFree_array(array);
       }else{

       Dim(array_data->rows-1, array_data->cols);
       as_array(Temp, double);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,iRow,j) = pCell(array,i,j);
           }
           iRow++;
       }
       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

unsigned long *Delete_row_ulong(unsigned long* array, DS_ARRAY * array_data,int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows-1, array_data->cols);
       as_unsigned_array(Temp, long);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,iRow,j) = pCell(array,i,j);
           }
           iRow++;
       }
       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

long *Delete_row_long(long* array, DS_ARRAY * array_data,int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           pFree_array(array);
       }else{
       Dim(array_data->rows-1, array_data->cols);
       as_array(Temp, long);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,i,j) = pCell(array,i,j);
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Cell(Temp,iRow,j) = pCell(array,i,j);
           }
           iRow++;
       }
       free(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

char **Delete_row_string(char ** array, DS_ARRAY * array_data,int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           psFree_array(array);
       }else{
       Dim(array_data->rows-1, array_data->cols);
       as_str_array(Temp);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               Let( Cell(Temp,i,j), pCell(array,i,j) );
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               Let( Cell(Temp,iRow,j), pCell(array,i,j) );
           }
           iRow++;
       }
       Free_str_ptr_only_array(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       return Temp;
       }
   }
   return array;
}

/* funcion MASTER */
void * Delete_row(void* array, DS_ARRAY * array_data,int __rToDel__){
   switch(array_data->type){
       case INTEGER: {
          array = Delete_row_int( (int *) array, array_data, __rToDel__ ); break;
       }case FLOAT: {
          array = Delete_row_float( (float *) array, array_data, __rToDel__ ); break;
       }case DOUBLE: {
          array = Delete_row_double( (double *) array, array_data, __rToDel__ ); break;
       }case LONG: {
          array = Delete_row_long( (long *) array, array_data, __rToDel__ ); break;
       }case UINTEGER: {
          array = Delete_row_uint( (unsigned int *) array, array_data, __rToDel__ ); break;
       }case ULONG: {
          array = Delete_row_ulong( (unsigned long *) array, array_data, __rToDel__ ); break;
       }case STRING: {
          array = Delete_row_string( (char **) array, array_data, __rToDel__ ); break;
       }
   }
   return array;
}


/* APPEND 
   añade arrays, filas y columnas al final de un array existente */

/* funciones APPEND_LST */

unsigned int * Append_lst_uint(unsigned int *X, DS_ARRAY * X_data, void * XARR, 
                                       DS_ARRAY * XARR_data) {
int i;
switch( XARR_data->type ){
   case INTEGER: {
      int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,int, (unsigned int)*(tmp + i) );
      } break;
   }case FLOAT: {
      float * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,int, (unsigned int)*(tmp + i) );
      } break;
   }case DOUBLE: {
      double * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,int, (unsigned int)*(tmp + i) );
      } break;
   }case LONG: {
      long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,int, (unsigned int)*(tmp + i) );
      } break;
   }case UINTEGER: {
      unsigned int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,int, (unsigned int)*(tmp + i) );
      } break;
   }case ULONG: {
      unsigned long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,int, (unsigned int)*(tmp + i) );
      } break;
   }case STRING: {
      char ** tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,int, Str2int( *(tmp + i) ));
      }
   }
} /* switch */
return X;
}

int * Append_lst_int(int *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data) {
int i;
switch( XARR_data->type ){
   case INTEGER: case UINTEGER: {
      int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,int, (int)*(tmp + i) );
      } break;
   }case FLOAT: {
      float * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,int, (int)*(tmp + i) );
      } break;
   }case DOUBLE: {
      double * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,int, (int)*(tmp + i) );
      } break;
   }case LONG: case ULONG: {
      long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,int, (int)*(tmp + i) );
      } break;
   }case STRING: {
      char ** tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,int, Str2int( *(tmp + i) ));
      }
   }
} /* switch */
return X;
}

float * Append_lst_float(float *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data) {

int i;
switch( XARR_data->type ){
   case INTEGER: case UINTEGER: {
      int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,float, (float)*(tmp + i) );
      } break;
   }case FLOAT: {
      float * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,float, (float)*(tmp + i) );
      } break;
   }case DOUBLE: {
      double * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,float, (float)*(tmp + i) );
      } break;
   }case LONG: case ULONG: {
      long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,float, (float)*(tmp + i) );
      } break;
   }case STRING: {
      char ** tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,float, Str2flt( *(tmp + i) ));
      }
   }
} /* switch */
return X;
}

unsigned long * Append_lst_ulong(unsigned long *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data) {

int i;
switch( XARR_data->type ){
   case INTEGER: {
      int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,long, (unsigned long)*(tmp + i) );
      } break;
   }case FLOAT: {
      float * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,long, (unsigned long)*(tmp + i) );
      } break;
   }case DOUBLE: {
      double * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,long, (unsigned long)*(tmp + i) );
      } break;
   }case LONG: {
      long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,long, (unsigned long)*(tmp + i) );
      } break;
   }case UINTEGER: {
      unsigned int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,long, (unsigned long)*(tmp + i) );
      } break;
   }case ULONG: {
      unsigned long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,long, (unsigned long)*(tmp + i) );
      } break;
   }case STRING: {
      char ** tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         puAppend(X,long, Str2lng( *(tmp + i) ));
      }
   }
} /* switch */
return X;
}

long * Append_lst_long(long *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data) {

int i;
switch( XARR_data->type ){
   case INTEGER: case UINTEGER: {
      int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,long, (long)*(tmp + i) );
      } break;
   }case FLOAT: {
      float * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,long, (long)*(tmp + i) );
      } break;
   }case DOUBLE: {
      double * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,long, (long)*(tmp + i) );
      } break;
   }case LONG: case ULONG: {
      long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,long, (long)*(tmp + i) );
      } break;
   }case STRING: {
      char ** tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,long, Str2lng( *(tmp + i) ));
      }
   }
} /* switch */
return X;
}

double * Append_lst_double(double *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data) {
int i;
switch( XARR_data->type ){
   case INTEGER: case UINTEGER: {
      int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,double, (double)*(tmp + i) );
      } break;
   }case FLOAT: {
      float * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,double, (double)*(tmp + i) );
      } break;
   }case DOUBLE: {
      double * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,double, (double)*(tmp + i) );
      } break;
   }case LONG: case ULONG: {
      long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,double, (double)*(tmp + i) );
      } break;
   }case STRING: {
      char ** tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         pAppend(X,double, Str2dbl( *(tmp + i) ));
      }
   }
} /* switch */
return X;
}

char ** Append_lst_string(char **X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data) {
int i;
switch( XARR_data->type ){
   case INTEGER: case UINTEGER: {
      int * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         char * cNum = Int2str(*(tmp + i) );
         psAppend(X, cNum);
         Free_secure(cNum);
      } break;
   }case FLOAT: {
      float * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         char * cNum = Flt2str(*(tmp + i) );
         psAppend(X, cNum);
         Free_secure(cNum);
      } break;
   }case DOUBLE: {
      double * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         char * cNum = Dbl2str(*(tmp + i) );
         psAppend(X, cNum);
         Free_secure(cNum);
      } break;
   }case LONG: case ULONG: {
      long * tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         char * cNum = Lng2str(*(tmp + i) );
         psAppend(X, cNum);
         Free_secure(cNum);
      } break;
   }case STRING: {
      char ** tmp = XARR;
      for( i=0; i<XARR_data->len; i++){
         psAppend(X, *(tmp + i) );
      }
   }
}
return X;
}

void * Append_lst(void *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){

   switch(X_data->type){
       case INTEGER: {
          X = Append_lst_int( (int *) X, X_data, XARR, XARR_data ); break;
       }case FLOAT: {
          X = Append_lst_float( (float *) X, X_data, XARR, XARR_data ); break;
       }case DOUBLE: {
          X = Append_lst_double( (double *) X, X_data, XARR, XARR_data ); break;
       }case LONG: {
          X = Append_lst_long( (long *) X, X_data, XARR, XARR_data ); break;
       }case UINTEGER: {
          X = Append_lst_uint( (unsigned int *) X, X_data, XARR, XARR_data ); break;
       }case ULONG: {
          X = Append_lst_ulong( (unsigned long *) X, X_data, XARR, XARR_data ); break;
       }case STRING: {
          X = Append_lst_string( (char **) X, X_data, XARR, XARR_data ); break;
       }
   }
   return X;
}

/* funciones APPEND_ROW */

/* AÑADE un array 1d a un array vacio, lista o array 2d, realizando una conversión si es necesario */

unsigned int * Append_row_uint( unsigned int * X, DS_ARRAY * X_data, 
                                        void * XARR, DS_ARRAY * XARR_data){

   int nLimite;
   if(X_data->len>0){  
        if(X_data->rows == 0) X_data->rows=1;
        if(X_data->cols == 0) X_data->cols=X_data->len;
        nLimite = X_data->cols >= XARR_data->len ? XARR_data->len : X_data->cols;
   }else{  // si es 0
        nLimite = XARR_data->len;
        X_data->cols = XARR_data->len;
   }
   int i;
   switch( XARR_data->type ){
        case INTEGER: case UINTEGER: {
            int * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,int, (unsigned int)*(tmp + i) );
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,int, (unsigned int)*(tmp + i) );
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,int, (unsigned int)*(tmp + i) );
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,int, (unsigned int)*(tmp + i) );
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,int, Str2int( *(tmp + i) ));
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
        for( i=0; i < X_data->cols - XARR_data->len; i++){
            puAppend(X,int, 0 );
        }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}

int * Append_row_int( int * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){

   int nLimite;
   if(X_data->len>0){  
        if(X_data->rows == 0) X_data->rows=1;
        if(X_data->cols == 0) X_data->cols=X_data->len;
        nLimite = X_data->cols >= XARR_data->len ? XARR_data->len : X_data->cols;
   }else{  // si es 0
        nLimite = XARR_data->len;
        X_data->cols = XARR_data->len;
   }
   int i;
   switch( XARR_data->type ){
        case INTEGER: case UINTEGER: {
            int * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,int, (int)*(tmp + i) );
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,int, (int)*(tmp + i) );
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,int, (int)*(tmp + i) );
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,int, (int)*(tmp + i) );
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,int, Str2int( *(tmp + i) ));
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
        for( i=0; i < X_data->cols - XARR_data->len; i++){
            pAppend(X,int, 0 );
        }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}

float * Append_row_float( float * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){

   int nLimite;
   if(X_data->len>0){  
        if(X_data->rows == 0) X_data->rows=1;
        if(X_data->cols == 0) X_data->cols=X_data->len;
        nLimite = X_data->cols >= XARR_data->len ? XARR_data->len : X_data->cols;
   }else{  // si es 0
        nLimite = XARR_data->len;
        X_data->cols = XARR_data->len;
   }
   int i;
   switch( XARR_data->type ){
        case INTEGER: case UINTEGER: {
            int * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,float, (float)*(tmp + i) );
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,float, (float)*(tmp + i) );
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,float, (float)*(tmp + i) );
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,float, (float)*(tmp + i) );
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,float, Str2flt( *(tmp + i) ));
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
            for( i=0; i < X_data->cols - XARR_data->len; i++){
                pAppend(X,float, 0.0 );
            }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}

unsigned long * Append_row_ulong( unsigned long * X, DS_ARRAY * X_data, 
                                          void * XARR, DS_ARRAY * XARR_data){

   int nLimite;
   if(X_data->len>0){  
        if(X_data->rows == 0) X_data->rows=1;
        if(X_data->cols == 0) X_data->cols=X_data->len;
        nLimite = X_data->cols >= XARR_data->len ? XARR_data->len : X_data->cols;
   }else{  // si es 0
        nLimite = XARR_data->len;
        X_data->cols = XARR_data->len;
   }
   int i;
   switch( XARR_data->type ){
        case INTEGER: case UINTEGER: {
            int * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,long, (unsigned long)*(tmp + i) );
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,long, (unsigned long)*(tmp + i) );
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,long, (unsigned long)*(tmp + i) );
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,long, (unsigned long)*(tmp + i) );
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                puAppend(X,long, Str2lng( *(tmp + i) ));
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
            for( i=0; i < X_data->cols - XARR_data->len; i++){
                puAppend(X,long, 0 );
            }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}


long * Append_row_long( long * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){

   int nLimite;
   if(X_data->len>0){  
        if(X_data->rows == 0) X_data->rows=1;
        if(X_data->cols == 0) X_data->cols=X_data->len;
        nLimite = X_data->cols >= XARR_data->len ? XARR_data->len : X_data->cols;
   }else{  // si es 0
        nLimite = XARR_data->len;
        X_data->cols = XARR_data->len;
   }
   int i;
   switch( XARR_data->type ){
        case INTEGER: case UINTEGER: {
            int * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,long, (long)*(tmp + i) );
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,long, (long)*(tmp + i) );
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,long, (long)*(tmp + i) );
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,long, (long)*(tmp + i) );
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,long, Str2lng( *(tmp + i) ));
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
            for( i=0; i < X_data->cols - XARR_data->len; i++){
                pAppend(X,long, 0 );
            }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}

double * Append_row_double( double * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){

   int nLimite;
   if(X_data->len>0){  
        if(X_data->rows == 0) X_data->rows=1;
        if(X_data->cols == 0) X_data->cols=X_data->len;
        nLimite = X_data->cols >= XARR_data->len ? XARR_data->len : X_data->cols;
   }else{  // si es 0
        nLimite = XARR_data->len;
        X_data->cols = XARR_data->len;
   }
   int i;
   switch( XARR_data->type ){
        case INTEGER: case UINTEGER: {
            int * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,double, (double)*(tmp + i) );
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,double, (double)*(tmp + i) );
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,double, (double)*(tmp + i) );
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,double, (double)*(tmp + i) );
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                pAppend(X,double, Str2dbl( *(tmp + i) ));
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
            for( i=0; i < X_data->cols - XARR_data->len; i++){
                pAppend(X,double, 0.0 );
            }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}

char ** Append_row_string( char ** X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){

   int nLimite;
   if(X_data->len>0){  
        if(X_data->rows == 0) X_data->rows=1;
        if(X_data->cols == 0) X_data->cols=X_data->len;
        nLimite = X_data->cols >= XARR_data->len ? XARR_data->len : X_data->cols;
   }else{  // si es 0
        nLimite = XARR_data->len;
        X_data->cols = XARR_data->len;
   }
   int i;
   switch( XARR_data->type ){
        case INTEGER: case UINTEGER: {
            int * tmp = XARR;
            for( i=0; i < nLimite; i++){
                char * cNum = Int2str(*(tmp + i) );
                psAppend(X, cNum);
                Free_secure(cNum);
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                char * cNum = Flt2str(*(tmp + i) );
                psAppend(X, cNum);
                Free_secure(cNum);
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                char * cNum = Dbl2str(*(tmp + i) );
                psAppend(X, cNum);
                Free_secure(cNum);
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                char * cNum = Lng2str(*(tmp + i) );
                psAppend(X, cNum);
                Free_secure(cNum);
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                psAppend(X, *(tmp + i) );
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
            for( i=0; i < X_data->cols - XARR_data->len; i++){
                psAppend(X, "" );
            }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}

/* funcion MASTER */
void * Append_row(void *X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){
   switch(X_data->type){
       case INTEGER: {
          X = Append_row_int( (int *) X, X_data, XARR, XARR_data ); break;
       }case FLOAT: {
          X = Append_row_float( (float *) X, X_data, XARR, XARR_data ); break;
       }case DOUBLE: {
          X = Append_row_double( (double *) X, X_data, XARR, XARR_data ); break;
       }case LONG: {
          X = Append_row_long( (long *) X, X_data, XARR, XARR_data ); break;
       }case UINTEGER: {
          X = Append_row_uint( (unsigned int *) X, X_data, XARR, XARR_data ); break;
       }case ULONG: {
          X = Append_row_ulong( (unsigned long *) X, X_data, XARR, XARR_data ); break;
       }case STRING: {
          X = Append_row_string( (char **) X, X_data, XARR, XARR_data ); break;
       }
   }
   return X;
}

/* APPEND PAG */

/* APPEND_COL */

void * Append_col(void * Temp, DS_ARRAY * array_data, void *APND, DS_ARRAY *APND_data){

    if( !array_data->rows && !array_data->cols ){  // array vacio o lista
       if( array_data->len==0 ){ //vacio
          
          int i=0;
          switch(APND_data->type){
              case INTEGER: case UINTEGER: {  // int
                  switch(array_data->type){
                      case INTEGER: case UINTEGER: {   // int -> int
                         Temp = ( int * ) realloc( (void *) Temp, sizeof( int ) * ( APND_data->len ) );
                         memcpy( (void*)Temp, APND, sizeof( int ) * APND_data->len);
                         break;
                      }case FLOAT:{
                         int * tmp = APND;
                         float * array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             pAppend(array, float, (float)*(tmp + i++) );
                         }
                         Temp = (float *)array;
                         break;
                      }case DOUBLE:{
                         int * tmp = APND;
                         double * array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             pAppend(array, double, (double)*(tmp + i++) );
                         }
                         Temp = (double *)array;
                         break;
                      }case LONG: case ULONG:{
                         int * tmp = APND;
                         long * array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             pAppend(array, long, (long)*(tmp + i++) );//int, Str2Int( *(tmp + i++) ));
                         }
                         Temp = (long *)array;
                         break;
                      }case STRING: {  // string
                         int * tmp = APND;
                         char ** array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             char * str = Int2str( *(tmp + i++) );
                             psAppend(array, str);
                             free(str);
                         }
                         Temp = (char **)array;
                         break;
                      }
                  }
                  break;
              }case FLOAT: {  // float -> ....
                  switch(array_data->type){
                      case INTEGER: case UINTEGER: { 
                         float * tmp = APND;
                         int * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, int, (int)*(tmp + i++) );
                         }
                         Temp = (int *)array;
                         break;
                      }case FLOAT:{  // float -> float
                         Temp = ( float * ) realloc( (void *) Temp, sizeof( float ) * ( APND_data->len ) );
                         memcpy( (void*)Temp, APND, sizeof( float ) * APND_data->len);
                         break;
                      }case DOUBLE:{
                         float * tmp = APND;
                         double * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, double, (double)*(tmp + i++) );
                         }
                         Temp = (double *)array;
                         break;
                      }case LONG: case ULONG:{
                         float * tmp = APND;
                         long * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, long, (long)*(tmp + i++) );
                         }
                         Temp = (long *)array;
                         break;
                      }case STRING: {  // float -> string
                         float * tmp = APND;
                         char ** array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             char * str = Flt2str( *(tmp + i++) );
                             psAppend(array, str);
                             free(str);
                         }
                         Temp = (char **)array;
                         break;
                      }
                  }
                  break;
              }case DOUBLE: {  // double -> ...
                  switch(array_data->type){
                      case INTEGER: case UINTEGER: { 
                         double * tmp = APND;
                         int * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, int, (int)*(tmp + i++) );
                         }
                         Temp = (int *)array;
                         break;
                      }case FLOAT:{ 
                         double * tmp = APND;
                         float * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, float, (float)*(tmp + i++) );
                         }
                         Temp = (float *)array;
                         break;
                      }case DOUBLE:{ // double -> double
                         Temp = ( double * ) realloc( (void *)Temp, sizeof(double) * (APND_data->len) );
                         memcpy( (void*)Temp, APND, sizeof( double ) * APND_data->len);
                         break;
                      }case LONG: case ULONG:{
                         double * tmp = APND;
                         long * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, long, (long)*(tmp + i++) );
                         }
                         Temp = (long *)array;
                         break;
                      }case STRING: {  // double -> string
                         double * tmp = APND;
                         char ** array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             char * str = Dbl2str( *(tmp + i++) );
                             psAppend(array, str);
                             free(str);
                         }
                         Temp = (char **)array;
                         break;
                      }
                  }
                  break;
              }case LONG: case ULONG: {  // long -> ...
                  switch(array_data->type){
                      case INTEGER: case UINTEGER: {
                         long * tmp = APND;
                         int * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, int, (int)*(tmp + i++) );
                         }
                         Temp = (int *)array;
                         break;
                      }case FLOAT:{ 
                         long * tmp = APND;
                         float * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, float, (float)*(tmp + i++) );
                         }
                         Temp = (float *)array;
                         break;
                      }case DOUBLE:{ 
                         long * tmp = APND;
                         double * array = Temp;
                         while( i < APND_data->len ){
                             pAppend(array, double, (double)*(tmp + i++) );
                         }
                         Temp = (double *)array;
                         break;
                      }case LONG: case ULONG: {  // long -> long
                         Temp = ( long * ) realloc( (void *) Temp, sizeof( long ) * ( APND_data->len ) );
                         memcpy( (void*)Temp, APND, sizeof( long ) * APND_data->len);
                         break;
                      }case STRING: {  // long -> string
                         long * tmp = APND;
                         char ** array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             char * str = Lng2str( *(tmp + i++) );
                             psAppend(array, str);
                             free(str);
                         }
                         Temp = (char **)array;
                         break;
                      }
                  }
                  break;
                  
              }case STRING: {  // string
                  switch(array_data->type){
                      case INTEGER: case UINTEGER: {
                         char ** tmp = APND;
                         int * array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             pAppend(array, int, Str2int(*(tmp + i++) ));//int, Str2Int( *(tmp + i++) ));
                         }
                         Temp = (int *)array;
                         break;
                      }case FLOAT:{
                         char ** tmp = APND;
                         float * array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             pAppend(array, float, Str2flt(*(tmp + i++) ));
                         }
                         Temp = (float *)array;
                         break;
                      }case DOUBLE:{
                         char ** tmp = APND;
                         double * array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             pAppend(array, double, Str2dbl(*(tmp + i++) ));
                         }
                         Temp = (double *)array;
                         break;
                      }case LONG: case ULONG: {
                         char ** tmp = APND;
                         long * array = Temp;//Temp = array;
                         while( i < APND_data->len ){
                             pAppend(array, long, Str2lng(*(tmp + i++) ));
                         }
                         Temp = (long *)array;
                         break;
                      }case STRING: {  // string
                         char ** tmp = APND;
                         char ** array = Temp;
                         while( i < APND_data->len ){
                             psAppend(array,  *(tmp + i) );
                             ++i;
                         }
                         Temp = (char **)array;
                         break;
                      }
                  }
                  break;
              }
          }
          array_data->rows=APND_data->len; //array_data->len; //Temp_data.len;
          array_data->len=APND_data->len;
          array_data->cols=1;
          array_data->dims=2;
          return Temp;

       }else{  // lista

          Dim(array_data->len, 2);

          Define_Global_Array(Temp1);  // solo declaro la metadata. El array será declarado adentro.
          if( APND_data->len == array_data->len ){
              switch(APND_data->type){
                  case INTEGER: case UINTEGER: {  // int -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // int->int
                              int * array = Temp;
                              int * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // int->float
                              float * array = Temp;
                              int * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // int->double
                              double * array = Temp;
                              int * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG: {  // int->long
                              long * array = Temp;
                              int * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // int->string
                              char ** array = Temp;
                              int * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = (char *)malloc( sizeof(char) * strlen(*(array + i))+1);
                                  Let( Cell(Temp1,i,0), *(array + i) ) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  char * str = Int2str( *(tmp + i) );
                                  Cell(Temp1,i,1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case FLOAT:{  // float -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // float->int
                              int * array = Temp;
                              float * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // float->float
                              float * array = Temp;
                              float * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // float->double
                              double * array = Temp;
                              float * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // float->long
                              long * array = Temp;
                              float * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // float->string
                              char ** array = Temp;
                              float * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = (char *)malloc( sizeof(char) * strlen(*(array + i))+1);
                                  Let( Cell(Temp1,i,0), *(array + i) ) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  char * str = Flt2str( *(tmp + i) );
                                  Cell(Temp1,i,1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case DOUBLE:{  // double -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // double->int
                              int * array = Temp;
                              double * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // double->float
                              float * array = Temp;
                              double * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // double->double
                              double * array = Temp;
                              double * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // double->long
                              long * array = Temp;
                              double * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // double->string
                              char ** array = Temp;
                              double * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = (char *)malloc( sizeof(char) * strlen(*(array + i))+1);
                                  Let( Cell(Temp1,i,0), *(array + i) ) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  char * str = Dbl2str( *(tmp + i) );
                                  Cell(Temp1,i,1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case LONG: case ULONG:{  // long -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // long->int
                              int * array = Temp;
                              long * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // long->float
                              float * array = Temp;
                              long * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // long->double
                              double * array = Temp;
                              long * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // long->long
                              long * array = Temp;
                              long * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // long->string
                              char ** array = Temp;
                              long * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = (char *)malloc( sizeof(char) * strlen(*(array + i))+1);
                                  Let( Cell(Temp1,i,0), *(array + i) ) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  char * str = Lng2str( *(tmp + i) );
                                  Cell(Temp1,i,1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case STRING:{  // string -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // string->int
                              int * array = Temp;
                              char ** tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = Str2int( *(tmp + i) );
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // string->float
                              float * array = Temp;
                              char ** tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = Str2flt(*(tmp + i));
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // string->double
                              double * array = Temp;
                              char ** tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = Str2dbl( *(tmp + i) );
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // string->long
                              long * array = Temp;
                              char ** tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = *(array + i) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = Str2lng( *(tmp + i) );
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // string->string
                              char ** array = Temp;
                              char ** tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->len * 2) );
                              int i;
                              for( i=0; i < array_data->len; i++){
                                  Cell(Temp1,i,0) = (char *)malloc( sizeof(char) * strlen(*(array + i))+1);
                                  Let( Cell(Temp1,i,0), *(array + i) ) ;
                              }
                              for( i=0; i < Temp1_data.rows; i++){
                                  Cell(Temp1,i,1) = (char *)malloc( sizeof(char) * strlen(*(tmp + i))+1);
                                  Let( Cell(Temp1,i,1), *(tmp + i) );
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }
              }

             ///Free_Ptr_StrArray(array);
             array_data->rows=Temp1_data.rows;
             array_data->cols=Temp1_data.cols;
             array_data->len = Temp1_data.len;
             array_data->dims=2;
             return Temp;
          }else{
             return Temp; //array;
          }
       }
    }else {   // significa que tienen rows y cols, porque no existe uno sin el otro

       Dim(array_data->rows, array_data->cols+1);
       Define_Global_Array(Temp1);

       if( APND_data->len == array_data->rows ){
       
              switch(APND_data->type) 
              {
                  case INTEGER: case UINTEGER: {   // int -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {   // int->int
                              int * array = Temp;
                              int * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                              
                          }case FLOAT:{  // int->float
                              float * array = Temp;
                              int * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // int->double
                              double * array = Temp;
                              int * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // int->long
                              long * array = Temp;
                              int * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // int->string
                              char ** array = Temp;
                              int * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = (char *)malloc( sizeof(char) * strlen(pCell(array,i,j))+1);
                                      Let(Cell(Temp1,i,j), pCell(array,i,j) );
                                  }
                                  char *str = Int2str( *(tmp + i) );
                                  Cell(Temp1,i,Temp1_data.cols-1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,Temp1_data.cols-1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case FLOAT:{  // float -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // float->int
                              int * array = Temp;
                              float * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j) ;
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // float->float
                              float * array = Temp;
                              float * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j) ;
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // float->double
                              double * array = Temp;
                              float * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j) ;
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // float->long
                              long * array = Temp;
                              float * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j) ;
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1)= *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // float->string
                              char ** array = Temp;
                              float * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = (char *)malloc( sizeof(char) * strlen(pCell(array,i,j))+1);
                                      Let(Cell(Temp1,i,j), pCell(array,i,j) );
                                  }
                                  char * str = Flt2str( *(tmp + i) );
                                  Cell(Temp1,i,Temp1_data.cols-1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,Temp1_data.cols-1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case DOUBLE:{  // double -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // double->int
                              int * array = Temp;
                              double * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // double->float
                              float * array = Temp;
                              double * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // double->double
                              double * array = Temp;
                              double * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // double->long
                              long * array = Temp;
                              double * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // double->string
                              char ** array = Temp;
                              double * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = (char *)malloc( sizeof(char) * strlen(pCell(array,i,j))+1);
                                      Let(Cell(Temp1,i,j), pCell(array,i,j) );
                                  }
                                  char * str = Dbl2str( *(tmp + i) );
                                  Cell(Temp1,i,Temp1_data.cols-1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,Temp1_data.cols-1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case LONG: case ULONG:{  // long -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // long->int
                              int * array = Temp;
                              long * tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = *(tmp + i);
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // long->float
                              float * array = Temp;
                              long * tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) =  *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // long->double
                              double * array = Temp;
                              long * tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // long->long
                              long * array = Temp;
                              long * tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = *(tmp + i) ;
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // long->string
                              char ** array = Temp;
                              long * tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = (char *)malloc( sizeof(char) * strlen(pCell(array,i,j))+1);
                                      Let( Cell(Temp1,i,j), pCell(array,i,j) );
                                  }
                                  char * str = Lng2str( *(tmp + i) );
                                  Cell(Temp1,i,Temp1_data.cols-1) = (char *)malloc( sizeof(char) * strlen(str)+1);
                                  Let( Cell(Temp1,i,Temp1_data.cols-1), str );
                                  free(str);
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }case STRING:{  // string -> ...
                      switch(array_data->type){
                          case INTEGER: case UINTEGER: {  // string->int
                              int * array = Temp;
                              char ** tmp = APND;
                              int *Temp1 = (int *)malloc( sizeof( int ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j)= pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = Str2int( *(tmp + i) ) ;
                              }
                              free(Temp);
                              Temp = (int*) Temp1;
                              break;
                          }case FLOAT:{  // string->float
                              float * array = Temp;
                              char ** tmp = APND;
                              float *Temp1 = (float *)malloc( sizeof( float ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j)= pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = Str2flt( *(tmp + i) );
                              }
                              free(Temp);
                              Temp = (float*) Temp1;
                              break;
                          }case DOUBLE:{  // string->double
                              double * array = Temp;
                              char ** tmp = APND;
                              double *Temp1 = (double *)malloc( sizeof( double ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = Str2dbl( *(tmp + i) );
                              }
                              free(Temp);
                              Temp = (double*) Temp1;
                              break;
                          }case LONG: case ULONG:{  // string->long
                              long * array = Temp;
                              char ** tmp = APND;
                              long *Temp1 = (long *)malloc( sizeof( long ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = pCell(array,i,j);
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = Str2lng( *(tmp + i) ) ;
                              }
                              free(Temp);
                              Temp = (long*) Temp1;
                              break;
                          }case STRING:{  // string->string
                              char ** array = Temp;
                              char ** tmp = APND;
                              char **Temp1 = (char **)malloc( sizeof( char * ) * (array_data->rows * (array_data->cols+1)) );
                              int i,j;
                              for( i=0; i < array_data->rows; i++){
                                  for( j=0; j < array_data->cols; j++){
                                      Cell(Temp1,i,j) = (char *)malloc( sizeof(char) * strlen(pCell(array,i,j))+1);
                                      Let(Cell(Temp1,i,j), pCell(array,i,j) );
                                  }
                                  Cell(Temp1,i,Temp1_data.cols-1) = (char *)malloc( sizeof(char) * strlen(*(tmp + i))+1);
                                  Let( Cell(Temp1,i,Temp1_data.cols-1), *(tmp + i) );
                              }
                              Free_str_ptr_array(array);
                              Temp = (char **) Temp1;
                              break;
                          }
                      }
                      break;
                  }
              }

          array_data->rows=Temp1_data.rows;
          array_data->cols=Temp1_data.cols;
          array_data->len = Temp1_data.len;
          array_data->dims=2;
          return Temp;
       }else 
          return Temp; //array;
    }
}


/* READTO - lee hasta*/
char * Read_to( int fhnd, char cTok, int * foundNL ){

    char * buffer = NULL;
    buffer = (char*)calloc(MAX_LENGTH_READ,1);
    if( buffer ){
       char * pBuffer = buffer;
       *foundNL=0;
       while( !Eof(fhnd) ){
          char buff[2];
          int nRead = read( fhnd, buff, 1 );
          if( nRead == -1 ){
              * pBuffer='\0';
              break;
          }
          
          if ( buff[0]!=cTok && buff[0]!='\n' ){
             * pBuffer = buff[0]; pBuffer++;
          }else{
             * pBuffer='\0';
             if (buff[0]=='\n') *foundNL=1;
             break;
          }
       }
    }else {Msg_red("Read_to : no hay memoria para CALLOC\n"); }
    
    return buffer;
}

/* LOAD_MATRIX - carga un archivo o una porcion de este. Para cargar una
   porcion del archivo, se deben definir los rangos con Range_for(). Para
   cargar todo el archivo, también. No sirve All_range_for(), porque aún
   no se tiene la matrix. 
   Con:
   Range_for( new_matrix, 0,1,df.total_lines-1, 0,1,df.max_tokens_per_line-1);
   se carga todo el archivo.
   */
int * Load_matrix_int(int * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat ){

      char* tokenizer=NULL;
      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else tokenizer = ",";
      int fdr,fila=0;
      int foundNL=0;
      
      if ( Is_pos( fdr = open( cFile, O_RDONLY )) ){
         int nLen = stat.total_lines * stat.max_tokens_per_line;
         mat_data->dims = 2;
         int i;
         for( i = 0; i < nLen; i++ ){
            char * tmp = Read_to(fdr, tokenizer[0],&foundNL );
            if ( fila >= mat_data->rowi && fila <= mat_data->rowe ){
               if( i >= ( fila * stat.max_tokens_per_line + mat_data->coli ) &&
                  i <= ( fila * stat.max_tokens_per_line + mat_data->cole ) ){
                  int nNum = Str2int( tmp );
                  pAppend( mat, int, nNum ); // cuando DS_ARRAY pasa como puntero, usar pAppend
               }
            }
            Free_secure(tmp);
            fila+=foundNL;
         }
         close(fdr);
         mat_data->rows = (mat_data->rowe - mat_data->rowi)+1;
         mat_data->cols = (mat_data->cole - mat_data->coli)+1;
      }
      else {
         Msg_redf("Load_matrix_int : el archivo '%s' no puede ser abierto",cFile);
      }
   return mat;
}

float * Load_matrix_float(float * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat ){

      char* tokenizer=NULL;
      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else tokenizer = ",";
      int fdr,fila=0;
      int foundNL=0;
      
      if ( Is_pos( fdr = open( cFile, O_RDONLY )) ){
         int nLen = stat.total_lines * stat.max_tokens_per_line;
         mat_data->dims = 2;
         int i;
         for( i = 0; i < nLen; i++ ){
            char * tmp = Read_to(fdr, tokenizer[0],&foundNL );
            if ( fila >= mat_data->rowi && fila <= mat_data->rowe ){
               if( i >= ( fila * stat.max_tokens_per_line + mat_data->coli ) &&
                  i <= ( fila * stat.max_tokens_per_line + mat_data->cole ) ){
                  float nNum = Str2flt( tmp );
                  pAppend( mat, float, nNum ); // cuando DS_ARRAY pasa como puntero, usar pAppend
               }
            }
            Free_secure(tmp);
            fila+=foundNL;
         }
         close(fdr);
         mat_data->rows = (mat_data->rowe - mat_data->rowi)+1;
         mat_data->cols = (mat_data->cole - mat_data->coli)+1;
      }
      else {
         Msg_redf("Load_matrix_float : el archivo '%s' no puede ser abierto",cFile);
      }
   return mat;
}

double * Load_matrix_double(double * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat ){

      char* tokenizer=NULL;
      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else tokenizer = ",";
      int fdr,fila=0;
      int foundNL=0;
      
      if ( Is_pos( fdr = open( cFile, O_RDONLY )) ){
         int nLen = stat.total_lines * stat.max_tokens_per_line;
         mat_data->dims = 2;
         int i;
         for( i = 0; i < nLen; i++ ){
            char * tmp = Read_to(fdr, tokenizer[0],&foundNL );
            if ( fila >= mat_data->rowi && fila <= mat_data->rowe ){
               if( i >= ( fila * stat.max_tokens_per_line + mat_data->coli ) &&
                  i <= ( fila * stat.max_tokens_per_line + mat_data->cole ) ){
                  double nNum = Str2dbl( tmp );
                  pAppend( mat, double, nNum ); // cuando DS_ARRAY pasa como puntero, usar pAppend
               }
            }
            Free_secure(tmp);
            fila+=foundNL;
         }
         close(fdr);
         mat_data->rows = (mat_data->rowe - mat_data->rowi)+1;
         mat_data->cols = (mat_data->cole - mat_data->coli)+1;
      }
      else {
         Msg_redf("Load_matrix_double : el archivo '%s' no puede ser abierto",cFile);
      }
   return mat;
}

long * Load_matrix_long(long * mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat ){

      char* tokenizer=NULL;
      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else tokenizer = ",";
      int fdr,fila=0;
      int foundNL=0;
      
      if ( Is_pos( fdr = open( cFile, O_RDONLY )) ){
         int nLen = stat.total_lines * stat.max_tokens_per_line;
         mat_data->dims = 2;
         int i;
         for( i = 0; i < nLen; i++ ){
            char * tmp = Read_to(fdr, tokenizer[0],&foundNL );
            if ( fila >= mat_data->rowi && fila <= mat_data->rowe ){
               if( i >= ( fila * stat.max_tokens_per_line + mat_data->coli ) &&
                  i <= ( fila * stat.max_tokens_per_line + mat_data->cole ) ){
                  long nNum = Str2lng( tmp );
                  pAppend( mat, long, nNum ); // cuando DS_ARRAY pasa como puntero, usar pAppend
               }
            }
            Free_secure(tmp);
            fila+=foundNL;
         }
         close(fdr);
         mat_data->rows = (mat_data->rowe - mat_data->rowi)+1;
         mat_data->cols = (mat_data->cole - mat_data->coli)+1;
      }
      else {
         Msg_redf("Load_matrix_long : el archivo '%s' no puede ser abierto",cFile);
      }
   return mat;
}

char ** Load_matrix_string(char ** mat, DS_ARRAY * mat_data, const char * cFile, F_STAT stat ){

      char* tokenizer=NULL;
      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else tokenizer = ",";
      int fdr,fila=0;
      int foundNL=0;
      
      if ( Is_pos( fdr = open( cFile, O_RDONLY )) ){
         int nLen = stat.total_lines * stat.max_tokens_per_line;
         mat_data->dims = 2;
         int i;
         for( i = 0; i < nLen; i++ ){
            char * tmp = Read_to(fdr, tokenizer[0],&foundNL );
            if ( fila >= mat_data->rowi && fila <= mat_data->rowe ){
               if( i >= ( fila * stat.max_tokens_per_line + mat_data->coli ) &&
                  i <= ( fila * stat.max_tokens_per_line + mat_data->cole ) ){
                  psAppend( mat, tmp );
               }
            }
            Free_secure(tmp);
            fila+=foundNL;
         }
         close(fdr);
         mat_data->rows = (mat_data->rowe - mat_data->rowi)+1;
         mat_data->cols = (mat_data->cole - mat_data->coli)+1;
      }
      else {
         Msg_redf("Load_matrix_string : el archivo '%s' no puede ser abierto",cFile);
      }
   return mat;
}

void * Load_matrix(void * X, DS_ARRAY * X_data, const char * cFile, F_STAT stat ){

   switch(X_data->type){
       case INTEGER: case UINTEGER: {
          int * retVal;
          retVal = Load_matrix_int( (int*) X, X_data, cFile, stat );
          return retVal;
       }case FLOAT:{
          float * retVal;
          retVal = Load_matrix_float( (float*)X, X_data, cFile, stat );
          return retVal;
       }case DOUBLE:{
          double * retVal;
          retVal = Load_matrix_double( (double *)X, X_data, cFile, stat );
          return retVal;
       }case LONG: case ULONG: {
          long * retVal;
          retVal = Load_matrix_long( (long *)X, X_data, cFile, stat );
          return retVal;
       }case STRING:{
          char ** retVal;
          retVal = Load_matrix_string( (char **)X, X_data, cFile, stat );
          return retVal;
       }
   }
   return X;
}

/* SAVE_MATRIX - se guardan matrices en un archivo. Las matrices numericas
   se convierten a string antes de ser guardadas.
   Solo acepta formas de 2D. Si no tiene esta forma, use Reshape. 
   Necesita Range_for(matrix).
   */
int Save_matrix_int(int *mat, DS_ARRAY * mat_data, const char * cFile ){
   int sw=1;
   if( ( mat_data->rows * mat_data->cols ) == mat_data->len ){
      int fdw;
      if( (fdw = open(cFile, O_RDWR | O_CREAT | O_TRUNC, 0644)) )
      {
          char* tokenizer=NULL;
          if( __TOKEN__ ) tokenizer = __TOKEN__;
          else tokenizer = ",";
          int tlen = strlen(tokenizer);
          char * EOL = "\n";
          int EOLlen = strlen(EOL);
          int i,j;
          pCompute_for( mat, i, j,
                   char * temp = Int2str( pCell(mat,i,j) );
                   if(temp){
                       write(fdw, temp, strlen(temp));
                       Free_secure(temp);
                       if(j < mat_data->cole - mat_data->colinc){
                           write(fdw, tokenizer, tlen);
                       }else{
                           write(fdw, EOL, EOLlen);
                       }
                   }
          );
          close(fdw);
      }else {
          Msg_redf("Save_matrix_int : archivo '%s' no pudo ser creado",cFile);
          sw=0;
      }
   }else{
      Msg_yellow("Save_matrix_int : use 'Reshape' para guardar la matrix (2D).\nMatriz no se ha guardado.");
      sw=0;
   }

   return sw;
}

int Save_matrix_float(float *mat, DS_ARRAY * mat_data, const char * cFile ){
   int sw=1;
   if( ( mat_data->rows * mat_data->cols ) == mat_data->len ){
      int fdw;
      if( (fdw = open(cFile, O_RDWR | O_CREAT | O_TRUNC, 0644)) )
      {
          char* tokenizer=NULL;
          if( __TOKEN__ ) tokenizer = __TOKEN__;
          else tokenizer = ",";
          int tlen = strlen(tokenizer);
          char * EOL = "\n";
          int EOLlen = strlen(EOL);
          int i,j;
          pCompute_for( mat, i, j,
                   char * temp = Flt2str( pCell(mat,i,j) );
                   if(temp){
                       write(fdw, temp, strlen(temp));
                       Free_secure(temp);
                       if(j < mat_data->cole - mat_data->colinc){
                           write(fdw, tokenizer, tlen);
                       }else{
                           write(fdw, EOL, EOLlen);
                       }
                   }
          );
          close(fdw);
      }else {
          Msg_redf("Save_matrix_float : archivo '%s' no pudo ser creado",cFile);
          sw=0;
      }
   }else{
      Msg_yellow("Save_matrix_float : use 'Reshape' para guardar la matrix (2D).\nMatriz no se ha guardado.");
      sw=0;
   }

   return sw;
}

int Save_matrix_double(double *mat, DS_ARRAY * mat_data, const char * cFile ){
   int sw=1;
   if( ( mat_data->rows * mat_data->cols ) == mat_data->len ){
      int fdw;
      if( (fdw = open(cFile, O_RDWR | O_CREAT | O_TRUNC, 0644)) )
      {
          char* tokenizer=NULL;
          if( __TOKEN__ ) tokenizer = __TOKEN__;
          else tokenizer = ",";
          int tlen = strlen(tokenizer);
          char * EOL = "\n";
          int EOLlen = strlen(EOL);
          int i,j;
          pCompute_for( mat, i, j,
                   char * temp = Dbl2str( pCell(mat,i,j) );
                   if(temp){
                       write(fdw, temp, strlen(temp));
                       Free_secure(temp);
                       if(j < mat_data->cole - mat_data->colinc){
                           write(fdw, tokenizer, tlen);
                       }else{
                           write(fdw, EOL, EOLlen);
                       }
                   }
          );
          close(fdw);
      }else {
          Msg_redf("Save_matrix_double : archivo '%s' no pudo ser creado",cFile);
          sw=0;
      }
   }else{
      Msg_yellow("Save_matrix_double : use 'Reshape' para guardar la matrix (2D).\nMatriz no se ha guardado.");
      sw=0;
   }

   return sw;
}

int Save_matrix_long(long *mat, DS_ARRAY * mat_data, const char * cFile ){
   int sw=1;
   if( ( mat_data->rows * mat_data->cols ) == mat_data->len ){
      int fdw;
      if( (fdw = open(cFile, O_RDWR | O_CREAT | O_TRUNC, 0644)) )
      {
          char* tokenizer=NULL;
          if( __TOKEN__ ) tokenizer = __TOKEN__;
          else tokenizer = ",";
          int tlen = strlen(tokenizer);
          char * EOL = "\n";
          int EOLlen = strlen(EOL);
          int i,j;
          pCompute_for( mat, i, j,
                   char * temp = Lng2str( pCell(mat,i,j) );
                   if(temp){
                       write(fdw, temp, strlen(temp));
                       Free_secure(temp);
                       if(j < mat_data->cole - mat_data->colinc){
                           write(fdw, tokenizer, tlen);
                       }else{
                           write(fdw, EOL, EOLlen);
                       }
                   }
          );
          close(fdw);
      }else {
          Msg_redf("Save_matrix_long : archivo '%s' no pudo ser creado",cFile);
          sw=0;
      }
   }else{
      Msg_yellow("Save_matrix_long : use 'Reshape' para guardar la matrix (2D).\nMatriz no se ha guardado.");
      sw=0;
   }

   return sw;
}

int Save_matrix_string(char **mat, DS_ARRAY * mat_data, const char * cFile ){
   int sw=1;
   if( ( mat_data->rows * mat_data->cols ) == mat_data->len ){
      int fdw;
      if( (fdw = open(cFile, O_RDWR | O_CREAT | O_TRUNC, 0644)) )
      {
          char* tokenizer=NULL;
          if( __TOKEN__ ) tokenizer = __TOKEN__;
          else tokenizer = ",";
          int tlen = strlen(tokenizer);
          char * EOL = "\n";
          int EOLlen = strlen(EOL);
          int i,j;
          pCompute_for( mat, i, j,
                write(fdw, pCell(mat,i,j), strlen(pCell(mat,i,j)));
                if(j < mat_data->cole - mat_data->colinc){
                    write(fdw, tokenizer, tlen);
                }else{
                    write(fdw, EOL, EOLlen);
                }
          );
          close(fdw);
      }else {
          Msg_redf("Save_matrix_string : archivo '%s' no pudo ser creado",cFile);
          sw=0;
      }
   }else{
      Msg_yellow("Save_matrix_string : use 'Reshape' para guardar la matrix (2D).\nMatriz no se ha guardado.");
      sw=0;
   }

   return sw;
}

/* SAVER_MATRIX - master */
int Save_matrix(void * X, DS_ARRAY * X_data, const char * cFile ){

   int retVal;
   switch(X_data->type){
       case INTEGER: case UINTEGER: {          
          retVal = Save_matrix_int( (int*) X, X_data, cFile );
          break;
       }case FLOAT:{
          retVal = Save_matrix_float( (float*)X, X_data, cFile );
          break;
       }case DOUBLE:{
          retVal = Save_matrix_double( (double *)X, X_data, cFile );
          break;
       }case LONG: case ULONG: {
          retVal = Save_matrix_long( (long *)X, X_data, cFile );
          break;
       }case STRING:{
          retVal = Save_matrix_string( (char **)X, X_data, cFile );
          break;
       }
   }
   return retVal;
}



/* SPLIT - divide un string en tokens de un array */
char ** Split_char( char * w, char ** q, DS_ARRAY *q_data ){
   const char * v = w;
   if( v ){
      //int cntTok=0;
      while( *v ){  
         char word [6]; int j=0;
         if( *v < 0){
            while ( *v < 0) {word[j++] = *v ; v++;}
            word[j]='\0';
            --v;
         }else{
            word[0] = *v; word[1]='\0'; }
         psAppend( q, word );
         //cntTok++;
         v++;
      }
      //q_data->len = cntTok;
      return q;
   }else return NULL;
}


char ** Split( char * w, char token, char ** t, DS_ARRAY *t_data ){
 
 if( w ){
   char oldt = Set_new_sep(token);
   //int cntTok = 0;
   For_each_token(v, w)
       psAppend(t, v);
       //++cntTok;
   Next_token(v)
   ///t_data->len = cntTok; 
   Set_token_sep(oldt);

   return t;
 }else return NULL;
}

/* Generan secuencias */

double * Lineal_spaced( DS_ARRAY * data, double pDesde, double pHasta, int pTotal ){
   if( pTotal >= 1 ){   
       double inc = (pHasta - pDesde) / ( pTotal - 1);
       long n;

       SIZE_LINSPACED=pTotal;
       
       double * pC=NULL;

       pC = (double *) calloc( pTotal, sizeof(double) );
       pC[0] = pDesde;
       pC[pTotal-1] = pHasta;
   
       for( n=1; n<pTotal-1; n++){
           pC[n] = pC[n-1] + inc;
       }
       data->dims = 1;
       data->len = SIZE_LINSPACED;
       return pC;
   }else{
      Msg_red("Lineal_spaced : número de elementos debe ser mayor que 1\n");
      return NULL;
   }
}

double * Lineal_sequence( DS_ARRAY * data, double pDesde, double pInc, int pTotal ){
   if( pTotal >= 1){
       long n;
       SIZE_SEQUENCE=pTotal;
       
       double * pC=NULL;
       pC = (double *) calloc( pTotal, sizeof(double) );
   
       pC[0] = pDesde;
   
       for( n=1; n<pTotal; n++){
            pC[n] = pC[n-1] + pInc;
       }
       data->dims = 1;
       data->len = SIZE_SEQUENCE;

       return pC;
   }else{
      Msg_red("Lineal_sequence : número de elementos debe ser mayor que 1\n");
      return NULL;
   }
}


/* funcion MAX y MIN de array. busca el valor máximo y el valor mínimo
   de un array D-dim */

/* Se prefiere hacerlo con las coordenadas relativas, dado que se puede
   escoger el rango donde buscar */

void Do_max_array_1D( void * tmp, DS_ARRAY * mat_data, DS_MAXMIN * retVal, int Type, int DIR ){
   
   int nPos = mat_data->rowi;
   switch(Type){
      case INTEGER:{
          int * mat = tmp;
          int maxmin = mat[mat_data->rowi];
          if(DIR){
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] > maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }else{
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] < maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }
          retVal->local=nPos; break;
      }
      case FLOAT:{
          float * mat = tmp;
          float maxmin = mat[mat_data->rowi];
          if(DIR){
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] > maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }else{
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] < maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }
          retVal->local=nPos; break;
      }
      case DOUBLE: {
          double * mat = tmp;
          double maxmin = mat[mat_data->rowi];
          if(DIR){
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] > maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }else{
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] < maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }
          retVal->local=nPos; break;
      }
      case LONG: {
          long * mat = tmp;
          long maxmin = mat[mat_data->rowi];
          if(DIR){
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] > maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }else{
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] < maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }
          retVal->local=nPos; break;
      }
      case UINTEGER:{
          unsigned int * mat = tmp;
          unsigned int maxmin = mat[mat_data->rowi];
          if(DIR){
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] > maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }else{
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] < maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }
          retVal->local=nPos; break;
      }
      case ULONG: {
          unsigned long * mat = tmp;
          unsigned long maxmin = mat[mat_data->rowi];
          if(DIR){
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] > maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }else{
             int i;
             for ( i=mat_data->rowi; i < mat_data->rowe; i+=mat_data->rowinc){
                if( mat[i] < maxmin )  { maxmin = mat[i]; nPos = i; }
             }
          }
          retVal->local=nPos; break;
      }
   }
   //return retVal;
}

void Do_max_array_2D( void * tmp, DS_ARRAY * mat_data, DS_MAXMIN * retVal, int Type, int DIR ){

   switch(Type){
      case INTEGER:{
          int * mat = tmp;
          int maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          int i,j;
          if(DIR){
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) > maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }else{
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) < maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }
          retVal->local = retVal->row * mat_data->cols + retVal->col;
          break;
      }
      case FLOAT:{
          float * mat = tmp;
          float maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          int i,j;
          if(DIR){
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) > maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }else{
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) < maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }
          retVal->local = retVal->row * mat_data->cols + retVal->col;
          break;
      }
      case DOUBLE: {
          double * mat = tmp;
          double maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          int i,j;
          if(DIR){
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) > maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }else{
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) < maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }
          retVal->local = retVal->row * mat_data->cols + retVal->col;
          break;
      }
      case LONG: {
          long * mat = tmp;
          long maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          int i,j;
          if(DIR){
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) > maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }else{
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) < maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }
          retVal->local = retVal->row * mat_data->cols + retVal->col;
          break;
      }
      case UINTEGER:{
          unsigned int * mat = tmp;
          unsigned int maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          int i,j;
          if(DIR){
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) > maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }else{
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) < maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }
          retVal->local = retVal->row * mat_data->cols + retVal->col;
          break;
      }
      case ULONG: {
          unsigned long * mat = tmp;
          unsigned long maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          int i,j;
          if(DIR){
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) > maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }else{
              pCompute_for( mat, i,j,
              if( pCell(mat,i,j) < maxmin )  {
                  maxmin = pCell(mat,i,j); 
                  retVal->row = i; retVal->col = j;
              } )
          }
          retVal->local = retVal->row * mat_data->cols + retVal->col;
          break;
      }
   }
}

void Do_max_array_3D( void * tmp, DS_ARRAY * mat_data, DS_MAXMIN * retVal, int Type, int DIR ){
   switch(Type){
      case INTEGER:{
          int * mat = tmp;
          int maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          int i,j,k;
          if(DIR){
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) > maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }else{
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) < maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) 
                  + retVal->pag * (mat_data->cols*mat_data->rows);
          break;
      }
      case FLOAT:{
          float * mat = tmp;
          float maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          int i,j,k;
          if(DIR){
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) > maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }else{
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) < maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) 
                  + retVal->pag * (mat_data->cols*mat_data->rows);
          break;
      }
      case DOUBLE: {
          double * mat = tmp;
          double maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          int i,j,k;
          if(DIR){
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) > maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }else{
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) < maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) 
                  + retVal->pag * (mat_data->cols*mat_data->rows);
          break;
      }

      case LONG: {
          long * mat = tmp;
          long maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          int i,j,k;
          if(DIR){
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) > maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }else{
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) < maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }

          retVal->local = (retVal->row * mat_data->cols + retVal->col) 
                  + retVal->pag * (mat_data->cols*mat_data->rows);
          break;
      }
      case UINTEGER:{
          unsigned int * mat = tmp;
          unsigned int maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          int i,j,k;
          if(DIR){
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) > maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }else{
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) < maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) 
                  + retVal->pag * (mat_data->cols*mat_data->rows);
          break;
      }
      case ULONG: {
          unsigned long * mat = tmp;
          unsigned long maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          int i,j,k;
          if(DIR){
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) > maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }else{
              pIterup (pag, mat, k){
                  pIterup (row, mat, i){
                      pIterup (col, mat, j){
                          if( pCell(mat,i,j,k) < maxmin )  {
                               maxmin = pCell(mat,i,j,k); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; 
                          }
                      }
                  }
              }
          }

          retVal->local = (retVal->row * mat_data->cols + retVal->col) 
                  + retVal->pag * (mat_data->cols*mat_data->rows);
          break;
      }
   }
}

void Do_max_array_4D( void * tmp, DS_ARRAY * mat_data, DS_MAXMIN * retVal, int Type, int DIR ){

   switch(Type){
      case INTEGER: {
          int * mat = tmp;
          int maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          retVal->book = mat_data->booki;
          int i,j,k,p;
          if (DIR){
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) > maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }else{
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) < maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) + 
                  retVal->pag * (mat_data->cols*mat_data->rows) + 
                  retVal->book * (mat_data->cols*mat_data->rows*mat_data->pags) ;
          break;
      }
      case FLOAT:{
          float * mat = tmp;
          float maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          retVal->book = mat_data->booki;
          int i,j,k,p;
          if (DIR){
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) > maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }else{
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) < maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) + 
                  retVal->pag * (mat_data->cols*mat_data->rows) + 
                  retVal->book * (mat_data->cols*mat_data->rows*mat_data->pags) ;
          break;
      }
      case DOUBLE: {
          double * mat = tmp;
          double maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          retVal->book = mat_data->booki;
          int i,j,k,p;
          if (DIR){
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) > maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }else{
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) < maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) + 
                  retVal->pag * (mat_data->cols*mat_data->rows) + 
                  retVal->book * (mat_data->cols*mat_data->rows*mat_data->pags) ;
          break;
      }
      case LONG: {
          long * mat = tmp;
          long maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          retVal->book = mat_data->booki;
          int i,j,k,p;
          if (DIR){
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) > maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }else{
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) < maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) + 
                  retVal->pag * (mat_data->cols*mat_data->rows) + 
                  retVal->book * (mat_data->cols*mat_data->rows*mat_data->pags) ;
          break;
      }
      case UINTEGER:{
          unsigned int * mat = tmp;
          unsigned int maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          retVal->book = mat_data->booki;
          int i,j,k,p;
          if (DIR){
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) > maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }else{
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) < maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) + 
                  retVal->pag * (mat_data->cols*mat_data->rows) + 
                  retVal->book * (mat_data->cols*mat_data->rows*mat_data->pags) ;
          break;
      }
      case ULONG: {
          unsigned long * mat = tmp;
          unsigned long maxmin = mat[mat_data->rowi];
          retVal->row = mat_data->rowi;
          retVal->col = mat_data->coli;
          retVal->pag = mat_data->pagi;
          retVal->book = mat_data->booki;
          int i,j,k,p;
          if (DIR){
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) > maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }else{
              pIterup (book, mat, p){
                 pIterup (pag, mat, k){
                     pIterup (row, mat, i){
                         pIterup (col, mat, j){
                            if( pCell(mat,i,j,k,p) < maxmin )  {
                               maxmin = pCell(mat,i,j,k,p); 
                               retVal->row = i; retVal->col = j;
                               retVal->pag = k; retVal->book = p;
                            }
                         }
                     }
                 }
              }
          }
          retVal->local = (retVal->row * mat_data->cols + retVal->col) + 
                  retVal->pag * (mat_data->cols*mat_data->rows) + 
                  retVal->book * (mat_data->cols*mat_data->rows*mat_data->pags) ;
          break;
      }
   }
}

DS_MAXMIN Max_array( void * mat, DS_ARRAY * mat_data ){

   DS_MAXMIN retVal;
   retVal.local=-1;
   retVal.row=0;
   retVal.col=0;
   retVal.pag=0;
   retVal.book=0;

   if (mat_data->len ){ // no envía mensaje si es 0

       switch(mat_data->dims){
           case 1: 
               Do_max_array_1D( mat, mat_data, &retVal, mat_data->type, 1 );
               break;
               
           case 2:
               Do_max_array_2D( mat, mat_data, &retVal, mat_data->type, 1 );
               break;
               
           case 3:
               Do_max_array_3D( mat, mat_data, &retVal, mat_data->type, 1 );
               break;

           case 4:
               Do_max_array_4D( mat, mat_data, &retVal, mat_data->type, 1 );
               break;
       
       } // es un array vacío. retorna local=-1
   }
   return retVal;
}

DS_MAXMIN Min_array( void * mat, DS_ARRAY * mat_data ){

   DS_MAXMIN retVal;
   retVal.local=-1;
   retVal.row=0;
   retVal.col=0;
   retVal.pag=0;
   retVal.book=0;

   if (mat_data->len ){ // no envía mensaje si es 0

       switch(mat_data->dims){
           case 1: 
               Do_max_array_1D( mat, mat_data, &retVal, mat_data->type, 0 );
               break;
               
           case 2:
               Do_max_array_2D( mat, mat_data, &retVal, mat_data->type, 0 );
               break;
               
           case 3:
               Do_max_array_3D( mat, mat_data, &retVal, mat_data->type, 0 );
               break;

           case 4:
               Do_max_array_4D( mat, mat_data, &retVal, mat_data->type, 0 );
               break;
       
       } // es un array vacío. retorna local=-1
   }
   return retVal;
}

/* copia el data set de un array en otro para CLONE
   Para usar en otras funciones, añadir metadata
   faltante: LEN y modificar TYPE cuando corresponda */
void Copy_data_set_util(DS_ARRAY * T_data, DS_ARRAY * S_data){
   T_data->rows=S_data->rows;
   T_data->cols=S_data->cols;
   T_data->pags=S_data->pags;
   T_data->books=S_data->books;
   T_data->dims=S_data->dims;
   
   T_data->rowi=S_data->rowi;
   T_data->rowinc=S_data->rowinc;
   T_data->rowe=S_data->rowe;

   T_data->coli=S_data->coli;
   T_data->colinc=S_data->colinc;
   T_data->cole=S_data->cole;

   T_data->pagi=S_data->pagi;
   T_data->paginc=S_data->paginc;
   T_data->page=S_data->page;

   T_data->booki=S_data->booki;
   T_data->bookinc=S_data->bookinc;
   T_data->booke=S_data->booke;
   
   T_data->type = S_data->type;
}

// COPIA arrays, y permite cambiar el tipo de los copiado
char ** Copy_array_to_string( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){
   char ** cpy = NULL;
   Copy_data_set_util(cpy_data, mat_data);
   cpy_data->len = mat_data->len;
   cpy_data->type = string_TYPE;  // cambia el tipo, obvio

   cpy = ( char ** ) calloc( sizeof( char * ) * ( cpy_data->len ), 1 );
   if( cpy == NULL ) {
       Msg_red("Copy_array : no hay memoria para 'Copy_array_to_string' (CALLOC)\n");
       return NULL;
   }
   int i;
   switch(mat_data->type){
       case INTEGER: {
           int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               * (cpy + i ) = NULL;
               Get_fn_let( Cell(cpy,i), Int2str( * (tmp + i) ) );
           }
           break;
       }case FLOAT: {
           float * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               * (cpy + i ) = NULL;
               Get_fn_let( Cell(cpy,i), Flt2str( * (tmp + i) ) );
           }
           break;
       }case DOUBLE: {
           double * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               * (cpy + i ) = NULL;
               Get_fn_let( Cell(cpy,i), Dbl2str( * (tmp + i) ) );
           }
           break;
       }case LONG: {
           long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               * (cpy + i ) = NULL;
               Get_fn_let( Cell(cpy,i), Lng2str(* (tmp + i)) );
           }
           break;
       }case UINTEGER: {
           unsigned int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               * (cpy + i ) = NULL;
               Get_fn_let( Cell(cpy,i), Int2str( * (tmp + i) ) );
           }
           break;
       }case ULONG:{
           unsigned long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               * (cpy + i ) = NULL;
               Get_fn_let( Cell(cpy,i), Lng2str(* (tmp + i)) );
           }
           break;
       }case STRING:{
           char ** tmp = mat;
           for( i=0; i < mat_data->len; i++){
               * (cpy + i ) = NULL;
               Let( Cell(cpy,i), * (tmp + i) );
           }
       }
   }
   
   return cpy;
}

unsigned int * Copy_array_to_uint( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){
   unsigned int * cpy = NULL;
   Copy_data_set_util(cpy_data, mat_data);
   cpy_data->len = mat_data->len;
   cpy_data->type = unsigned_int_TYPE;
   cpy = ( unsigned int * ) malloc( sizeof( unsigned int ) * cpy_data->len );
   if( cpy == NULL ) {
       Msg_red("Copy_array : no hay memoria para 'Copy_array_to_int' (CALLOC)\n");
       return NULL;
   }
   int i;
   switch(mat_data->type){
       case INTEGER: {
           int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case FLOAT: {
           float * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case DOUBLE: {
           double * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case LONG: {
           long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case UINTEGER: {
           unsigned int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case ULONG:{
           unsigned long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case STRING:{
           char ** tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = Str2int( * (tmp + i) ) ;
           }
       }
   }
   return cpy;
}

int * Copy_array_to_int( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){
   int * cpy = NULL;
   Copy_data_set_util(cpy_data, mat_data);
   cpy_data->len = mat_data->len;
   cpy_data->type = int_TYPE;
   cpy = ( int * ) malloc( sizeof( int ) * cpy_data->len );
   if( cpy == NULL ) {
       Msg_red("Copy_array : no hay memoria para 'Copy_array_to_int' (CALLOC)\n");
       return NULL;
   }
   int i;
   switch(mat_data->type){
       case INTEGER: {
           int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case FLOAT: {
           float * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case DOUBLE: {
           double * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case LONG: {
           long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case UINTEGER: {
           unsigned int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case ULONG:{
           unsigned long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case STRING:{
           char ** tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = Str2int( * (tmp + i) ) ;
           }
       }
   }
   return cpy;
}

float * Copy_array_to_float( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){
   float * cpy = NULL;
   Copy_data_set_util(cpy_data, mat_data);
   cpy_data->len = mat_data->len;
   cpy_data->type = float_TYPE;

   cpy = ( float * ) malloc( sizeof( float ) * cpy_data->len );
   if( cpy == NULL ) {
       Msg_red("Copy_array : no hay memoria para 'Copy_array_to_float' (CALLOC)\n");
       return NULL;
   }
   int i;
   switch(mat_data->type){
       case INTEGER: {
           int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case FLOAT: {
           float * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case DOUBLE: {
           double * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case LONG: {
           long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case UINTEGER: {
           unsigned int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case ULONG:{
           unsigned long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case STRING:{
           char ** tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = Str2flt( * (tmp + i) ) ;
           }
       }
   }
   return cpy;
}

unsigned long * Copy_array_to_ulong( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){
   unsigned long * cpy = NULL;
   Copy_data_set_util(cpy_data, mat_data);
   cpy_data->len = mat_data->len;
   cpy_data->type = unsigned_long_TYPE;

   cpy = ( unsigned long * ) malloc( sizeof( unsigned long ) * cpy_data->len );
   if( cpy == NULL ) {
       Msg_red("Copy_array : no hay memoria para 'Copy_array_to_long' (CALLOC)\n");
       return NULL;
   }
   int i;
   switch(mat_data->type){
       case INTEGER: {
           int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case FLOAT: {
           float * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case DOUBLE: {
           double * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case LONG: {
           long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case UINTEGER: {
           unsigned int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case ULONG:{
           unsigned long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case STRING:{
           char ** tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = Str2lng( * (tmp + i) ) ;
           }
       }
   }
   return cpy;
}


long * Copy_array_to_long( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){
   long * cpy = NULL;
   Copy_data_set_util(cpy_data, mat_data);
   cpy_data->len = mat_data->len;
   cpy_data->type = long_TYPE;

   cpy = ( long * ) malloc( sizeof( long ) * cpy_data->len );
   if( cpy == NULL ) {
       Msg_red("Copy_array : no hay memoria para 'Copy_array_to_long' (CALLOC)\n");
       return NULL;
   }
   int i;
   switch(mat_data->type){
       case INTEGER: {
           int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case FLOAT: {
           float * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case DOUBLE: {
           double * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case LONG: {
           long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case UINTEGER: {
           unsigned int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case ULONG:{
           unsigned long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case STRING:{
           char ** tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = Str2lng( * (tmp + i) ) ;
           }
       }
   }
   return cpy;
}

double * Copy_array_to_double( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){
   double * cpy = NULL;
   Copy_data_set_util(cpy_data, mat_data);
   cpy_data->len = mat_data->len;
   cpy_data->type = double_TYPE;

   cpy = ( double * ) malloc( sizeof( double ) * cpy_data->len );
   if( cpy == NULL ) {
       Msg_red("Copy_array : no hay memoria para 'Copy_array_to_double' (CALLOC)\n");
       return NULL;
   }
   int i;
   switch(mat_data->type){
       case INTEGER: {
           int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case FLOAT: {
           float * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case DOUBLE: {
           double * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case LONG:{
           long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case UINTEGER: {
           unsigned int * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case ULONG:{
           unsigned long * tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = * (tmp + i);
           } break;
       }case STRING:{
           char ** tmp = mat;
           for( i=0; i < mat_data->len; i++){
               Cell(cpy,i) = Str2dbl( * (tmp + i) ) ;
           }
       }
   }
   return cpy;
}

/* chequea el tipo de los DS y de ahí invoca a cada funcion.
   Manda el tipo de CPY_DATA, el target */
void * Copy_array( DS_ARRAY *cpy_data, void * mat, DS_ARRAY *mat_data ){

   switch(cpy_data->type){
       case INTEGER: {
           return (int *)Copy_array_to_int( cpy_data, mat, mat_data );
       }case FLOAT: {
           return (float *)Copy_array_to_float( cpy_data, mat, mat_data );
       }case DOUBLE: {
           return (double *)Copy_array_to_double( cpy_data, mat, mat_data );
       }case LONG: {
           return (long *)Copy_array_to_long( cpy_data, mat, mat_data );
       }case UINTEGER: {
           return (unsigned int *)Copy_array_to_uint( cpy_data, mat, mat_data );
       }case ULONG:{
           return (unsigned long *)Copy_array_to_ulong( cpy_data, mat, mat_data );
       }case STRING:{
           return (char **)Copy_array_to_string( cpy_data, mat, mat_data );
       }
   }
   return NULL;
}

// no necesita el array, solo la data:
//   DS_ARRAY T_data;
//   T = CloneArray(S, &S_data, &T_data);
//


void * Clone_array( DS_ARRAY * T_data, void* S, DS_ARRAY * S_data){

   switch( S_data->type){
       case INTEGER: {
          int * T = NULL;
          int*tmp=S;
          Copy_data_set_util(T_data, S_data);
          int i;
          for ( i=0; i < S_data->len; i++){
              pAppend(T, int, pCell(tmp,i));
          }
          return (int *)T;
       }case FLOAT:{
          float * T = NULL;
          float*tmp=S;
          Copy_data_set_util(T_data, S_data);
          int i;
          for ( i=0; i < S_data->len; i++){
              pAppend(T, float, pCell(tmp,i));
          }
          return (float*)T;
       }case DOUBLE:{
          double * T = NULL;
          double*tmp=S;
          Copy_data_set_util(T_data, S_data); 
          int i;  
          for ( i=0; i < S_data->len; i++){
              pAppend(T, double, pCell(tmp,i));
          }
          return (double*)T;
       }case LONG: {
          long * T = NULL;
          long*tmp=S;
          Copy_data_set_util(T_data, S_data);
          int i;
          for ( i=0; i < S_data->len; i++){
              pAppend(T, long, pCell(tmp,i));
          }
          return (long*)T;
       }case UINTEGER:{
          unsigned int * T = NULL;
          unsigned int * tmp=S;
          Copy_data_set_util(T_data, S_data);
          int i;
          for ( i=0; i < S_data->len; i++){
              puAppend(T, int, pCell(tmp,i));
          }
          return (unsigned int *)T;
       }case ULONG:{
          unsigned long * T = NULL;
          unsigned long*tmp=S;
          Copy_data_set_util(T_data, S_data);
          int i;
          for ( i=0; i < S_data->len; i++){
              puAppend(T, long, pCell(tmp,i));
          }
          return (unsigned long*)T;
       }case STRING:{
          char ** T = NULL;
          char ** tmp = S;
          Copy_data_set_util(T_data, S_data);
          int i;
          for ( i=0; i < S_data->len; i++){
              psAppend(T, pCell(tmp,i));
          }
          return (char **)T;
       }
   }
   return NULL;
}

  
int * Clone_array_int( DS_ARRAY * T_data, int* S, DS_ARRAY * S_data ){

   int * T = NULL;
   Copy_data_set_util(T_data, S_data);
   int i;
   for ( i=0; i < S_data->len; i++){
       pAppend(T, int, pCell(S,i));
   }
   return T;
}

unsigned int * Clone_array_uint( DS_ARRAY * T_data, unsigned int* S, DS_ARRAY * S_data ){

   unsigned int * T = NULL;
   Copy_data_set_util(T_data, S_data);
   int i;
   for ( i=0; i < S_data->len; i++){
       puAppend(T, int, pCell(S,i));
   }
   return T;
}

float * Clone_array_float(  DS_ARRAY * T_data, float * S, DS_ARRAY * S_data){

   float * T = NULL;
   Copy_data_set_util(T_data, S_data);
   int i;
   for ( i=0; i < S_data->len; i++){
       pAppend(T, float, pCell(S,i));
   }
   return T;
}

long * Clone_array_long(  DS_ARRAY * T_data, long * S, DS_ARRAY * S_data){

   long * T = NULL;
   Copy_data_set_util(T_data, S_data);
   int i;
   for ( i=0; i < S_data->len; i++){
       pAppend(T, long, pCell(S,i));
   }
   return T;
}

unsigned long * Clone_array_ulong(  DS_ARRAY * T_data, unsigned long * S, DS_ARRAY * S_data){

   unsigned long * T = NULL;
   Copy_data_set_util(T_data, S_data);
   int i;
   for ( i=0; i < S_data->len; i++){
       puAppend(T, long, pCell(S,i));
   }
   return T;
}

double * Clone_array_double( DS_ARRAY * T_data, double * S, DS_ARRAY * S_data ){

   double * T = NULL;
   Copy_data_set_util(T_data, S_data);
   int i;
   for ( i=0; i < S_data->len; i++){
       pAppend(T, double, pCell(S,i));
   }
   return T;
}

char ** Clone_array_string( DS_ARRAY * T_data, char ** S, DS_ARRAY * S_data ){

   char ** T = NULL;
   Copy_data_set_util(T_data, S_data);
   int i;
   for (i=0; i < S_data->len; i++){
       psAppend(T, pCell(S,i));
   }
   return T;
}

