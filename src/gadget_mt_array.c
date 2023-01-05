
/*********************************************************************************************

                            DEFINICIONES PARA ARRAYS MULTITIPO

 *********************************************************************************************/

#include "../include/gadget.h"

/* establece token para uso global */
extern char * __TOKEN__;

/* precision decimal a imprimir */
extern int DEC_PREC;
/* macros de impresion imprimen valores doubles como notacion cientifica */
extern int SET_DBL_NOT;

extern int Is_ok;
/* maxima longitud de buffer de lectura de archivo */
extern int MAX_LENGTH_READ;

/* coordenadas de array globales */
extern int GLOBAL_ARR_ROWS;
extern int GLOBAL_ARR_COLS;
extern int GLOBAL_ARR_PAGS;
extern int GLOBAL_ARR_BOOKS;
extern int GLOBAL_ARR_DIM;


/* funciones */


MT_CELL *Load_matrix_mt(MT_CELL * array, DS_ARRAY * array_data, char * cFile, F_STAT _ST_, int DetectLong)
{
      char* tokenizer=NULL;
      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else tokenizer = ",";
      
      int fdr,fila=0;
      int foundNL=0;
      array_data->dims = 2;
      if ( Is_pos( fdr = open( cFile, O_RDONLY )) ){
         int nLen = _ST_.total_lines * _ST_.max_tokens_per_line;
         for( int i = 0; i < nLen; i++ ){
            char * tmp = Read_to(fdr, tokenizer[0],&foundNL );
            if ( fila >= array_data->rowi /* INIT_ROW_INTV*/ && fila <= array_data->rowe/*END_ROW_INTV*/ ){
               if( i >= ( fila * _ST_.max_tokens_per_line + array_data->coli /*INIT_COL_INTV*/ ) &&
                  i <= ( fila * _ST_.max_tokens_per_line + array_data->cole /*END_COL_INTV*/ ) ){
                  int lNumber = Is_number(tmp);
                  
                  if( lNumber==2 && DetectLong ){ // es un numero sin punto decimal
                      long nNum = Str2lng( tmp );
                      pAppend_mt( array, long, nNum );
                  }else if( lNumber ){  // todo es double en una matrix MT
                      double nNum = Str2dbl( tmp );
                      pAppend_mt( array, double, nNum );
                  }else{  // lo toma como string
                      if( Is_notation(tmp) ){  // es notacion cientifica??
                          double nNum = StrE2dbl( tmp );
                          pAppend_mt( array, double, nNum );
                      }else{
                          psAppend_mt(array, tmp);
                      }
                  }
               }
            }
            Free_secure(tmp);
            fila+=foundNL;
         }
         close(fdr);
         array_data->rows = (array_data->rowe - array_data->rowi)+1;
         array_data->cols = (array_data->cole - array_data->coli)+1;
      }
      else {
         Msg_redf("Load_matrix_mt : el archivo '%s' no puede ser abierto\revise sus permisos", cFile);
      }
      return array;
}

int Save_matrix_mt(MT_CELL * array, DS_ARRAY array_data, char * cFile ){

int sw=1;
   if( ( array_data.rows * array_data.cols ) == array_data.len ){
      int fdw;
      if( (fdw = open(cFile, O_RDWR | O_CREAT | O_TRUNC, 0644)) )
      {
          char* tokenizer=NULL;
          if( __TOKEN__ ) tokenizer = __TOKEN__;
          else tokenizer = ",";
          
          int tlen = strlen(tokenizer);
          char * EOL = "\n";
          int EOLlen = strlen(EOL);

          Str_init(tmp);
          int i,j;
          Iterup(row, array, i){
             Iterup(col, array, j){
                if(j < array_data.cole-1 ){

                   switch( Cell_type(array,i,j)) {
                      case int_TYPE :    {Get_fn_let(tmp, Int2str(iCell(array,i,j) )); break;}
                      case float_TYPE :  {Get_fn_let(tmp, Flt2str(fCell(array,i,j) )); break;}
                      case double_TYPE : {Get_fn_let(tmp, Dbl2str(dCell(array,i,j) )); break;}
                      case long_TYPE :   {Get_fn_let(tmp, Lng2str(lCell(array,i,j) )); break;}
                      case unsigned_int_TYPE :    {Get_fn_let(tmp, Int2str(uiCell(array,i,j) )); break;}
                      case unsigned_long_TYPE :   {Get_fn_let(tmp, Lng2str(ulCell(array,i,j) )); break;}
                      case string_TYPE:  {Let(tmp, sCell(array,i,j)); break;}
                      case MULTI_TYPE:  break;
                   }
                   write(fdw, tmp, strlen(tmp));
                   write(fdw, tokenizer, tlen);

                }
             }

             switch( Cell_type(array,i, array_data.cole-1 )){
                case int_TYPE :    {Get_fn_let(tmp, Int2str(iCell(array,i,array_data.cole-1) )); break;}
                case float_TYPE :  {Get_fn_let(tmp, Flt2str(fCell(array,i,array_data.cole-1) )); break;}
                case double_TYPE : {Get_fn_let(tmp, Dbl2str(dCell(array,i,array_data.cole-1) )); break;}
                case long_TYPE :   {Get_fn_let(tmp, Lng2str(lCell(array,i,array_data.cole-1) )); break;}
                case unsigned_int_TYPE :    {Get_fn_let(tmp, Int2str(uiCell(array,i,array_data.cole-1) )); break;}
                case unsigned_long_TYPE :   {Get_fn_let(tmp, Lng2str(ulCell(array,i,array_data.cole-1) )); break;}
                case string_TYPE:  {Let(tmp, sCell(array,i,array_data.cole-1)); break;}
                case MULTI_TYPE:  break;
             }

             write(fdw, tmp, strlen(tmp));
             write(fdw, EOL, EOLlen);

          }
          Free_secure(tmp);
          close(fdw);
      }else {
          Msg_red("Save_matrix_mt : archivo destino no pudo ser creado");
          sw=0;
      }
   }else{
      Msg_yellow("Save_matrix_mt : use 'Reshape' o 'rangos' para guardar la matriz.\nMatriz no se ha guardado.");
      sw=0;
   }

return sw;
}


MT_CELL * Append_lst_mt(MT_CELL * array, DS_ARRAY * array_data, MT_CELL * APND, DS_ARRAY APND_data){

    int i=0;
    do{
       switch( Cell_type(APND,i)) {
           case int_TYPE :    {pAppend_mt(array, int, iCell(APND,i) ); break;}
           case float_TYPE :  {pAppend_mt(array, float, fCell(APND,i) ); break;}
           case double_TYPE : {pAppend_mt(array, double, dCell(APND,i) ); break;}
           case long_TYPE :   {pAppend_mt(array, long, lCell(APND,i) ); break;}
           case unsigned_int_TYPE :    {puAppend_mt(array, int, uiCell(APND,i) ); break;}
           case unsigned_long_TYPE :   {puAppend_mt(array, long, ulCell(APND,i) ); break;}
           case string_TYPE:  {psAppend_mt(array, sCell(APND,i) ); break;}
           case MULTI_TYPE:  {break;}
       }

    }while( ++i < APND_data.len );
    return array;
}

MT_CELL * Append_col_mt(MT_CELL * array, DS_ARRAY * array_data, MT_CELL * APND, DS_ARRAY APND_data){

    if( !array_data->rows && !array_data->cols ){  // array vacio o lista
       if( array_data->len==0 ){ //vacio
          New_mt_array(Temp);

          int i=0;
          do{
              switch( Cell_type(APND,i)) {
                  case int_TYPE :    {Append_mt(Temp, int, iCell(APND,i) ); break;}
                  case float_TYPE :  {Append_mt(Temp, float, fCell(APND,i) ); break;}
                  case double_TYPE : {Append_mt(Temp, double, dCell(APND,i) ); break;}
                  case long_TYPE :   {Append_mt(Temp, long, lCell(APND,i) ); break;}
                  case unsigned_int_TYPE :    {uAppend_mt(Temp, int, uiCell(APND,i) ); break;}
                  case unsigned_long_TYPE :   {uAppend_mt(Temp, long, ulCell(APND,i) ); break;}
                  case string_TYPE:  {sAppend_mt(Temp, sCell(APND,i) ); break;}
                  case MULTI_TYPE:  {break;}
              }

          }while( ++i < APND_data.len );
          array_data->rows=Temp_data.len;
          array_data->len=Temp_data.len;
          array_data->cols=1;
          array_data->dims=2;
          return Temp;
       }else{  // lista
          //printf("PASA! dims=%d, len=%d\n",array_data->dims,array_data->len);
          Dim(array_data->len, 2) as_mt_array(Temp);

          if( APND_data.len == array_data->rows ){
              for( int i=0; i < array_data->len; i++){
                 
                 switch( Cell_type(array,i)) {
                    case int_TYPE :    {Chg(Temp,int,i,0,iCell(array,i)); break;}
                    case float_TYPE :  {Chg(Temp,float,i,0,fCell(array,i)); break;}
                    case double_TYPE : {Chg(Temp,double,i,0,dCell(array,i)); break;}
                    case long_TYPE :   {Chg(Temp,long,i,0,lCell(array,i)); break;}
                    case unsigned_int_TYPE :    {Chg(Temp,int,i,0,uiCell(array,i)); break;}
                    case unsigned_long_TYPE :   {Chg(Temp,long,i,0,ulCell(array,i)); break;}
                    case string_TYPE:  {sChg(Temp,i,0, sCell(array,i) ); break;}
                    case MULTI_TYPE:  {break;}
                 }
              }
              for( int i=0; i < Temp_data.rows; i++){
                 switch( Cell_type(APND,i)) {
                    case int_TYPE :    {Chg(Temp,int,i,1,iCell(APND,i)); break;}
                    case float_TYPE :  {Chg(Temp,float,i,1,fCell(APND,i)); break;}
                    case double_TYPE : {Chg(Temp,double,i,1,dCell(APND,i)); break;}
                    case long_TYPE :   {Chg(Temp,long,i,1,lCell(APND,i)); break;}
                    case unsigned_int_TYPE :    {Chg(Temp,int,i,1,uiCell(APND,i)); break;}
                    case unsigned_long_TYPE :   {Chg(Temp,long,i,1,ulCell(APND,i)); break;}
                    case string_TYPE:  {sChg(Temp,i,1, sCell(APND,i) ); break;}
                    case MULTI_TYPE:  {break;}
                 }
              }
             pFree_total_array_mt(array);
             array_data->rows = Temp_data.rows;
             array_data->cols = Temp_data.cols;
             array_data->len  = Temp_data.len;
             array_data->dims=2;
             return Temp;
          }else{
             Msg_red("Append_col_mt : No coinciden las longitudes de los arrays");
             return array;
          }
       }
    }else {   // significa que tienen rows y cols, porque no existe uno sin el otro

       Dim(array_data->rows, array_data->cols+1) as_mt_array(Temp);

       if( APND_data.len == array_data->rows ){
          for( int i=0; i < array_data->rows; i++){
              for( int j=0; j < array_data->cols; j++){
                 switch( pCell_type(array,i,j)) {
                    case int_TYPE :    {Chg(Temp,int,i,j,piCell(array,i,j)); break;}
                    case float_TYPE :  {Chg(Temp,float,i,j,pfCell(array,i,j)); break;}
                    case double_TYPE : {Chg(Temp,double,i,j,pdCell(array,i,j)); break;}
                    case long_TYPE :   {Chg(Temp,long,i,j,plCell(array,i,j)); break;}
                    case unsigned_int_TYPE :    {Chg(Temp,int,i,j,puiCell(array,i,j)); break;}
                    case unsigned_long_TYPE :   {Chg(Temp,long,i,j,pulCell(array,i,j)); break;}
                    case string_TYPE:  {sChg(Temp,i,j, psCell(array,i,j) ); break;}
                    case MULTI_TYPE:  {break;}
                 }
              }
              switch( Cell_type(APND,i)) {
                  case int_TYPE :    {Chg(Temp,int,i,Temp_data.cols-1,iCell(APND,i)); break;}
                  case float_TYPE :  {Chg(Temp,float,i,Temp_data.cols-1,fCell(APND,i)); break;}
                  case double_TYPE : {Chg(Temp,double,i,Temp_data.cols-1,dCell(APND,i)); break;}
                  case long_TYPE :   {Chg(Temp,long,i,Temp_data.cols-1,lCell(APND,i)); break;}
                  case unsigned_int_TYPE :    {Chg(Temp,int,i,Temp_data.cols-1,uiCell(APND,i)); break;}
                  case unsigned_long_TYPE :   {Chg(Temp,long,i,Temp_data.cols-1,ulCell(APND,i)); break;}
                  case string_TYPE:  {sChg(Temp,i,Temp_data.cols-1, sCell(APND,i) ); break;}
                  case MULTI_TYPE:  {break;}
              }

          }

          pFree_total_array_mt(array);
          array_data->rows=Temp_data.rows;
          array_data->cols=Temp_data.cols;
          array_data->len = Temp_data.len;
          array_data->dims=2;
          return Temp;
       }else 
          return array;
    }
}


MT_CELL * Append_row_mt(MT_CELL * array, DS_ARRAY * array_data, MT_CELL * APND, DS_ARRAY APND_data){
    int i=0;
    do{
       switch( Cell_type(APND,i)) {
          case int_TYPE :    {pAppend_mt(array, int, iCell(APND,i) ); break;}
          case float_TYPE :  {pAppend_mt(array, float, fCell(APND,i) ); break;}
          case double_TYPE : {pAppend_mt(array, double, dCell(APND,i) ); break;}
          case long_TYPE :   {pAppend_mt(array, long, lCell(APND,i) ); break;}
          case unsigned_int_TYPE :    {puAppend_mt(array, int, uiCell(APND,i) ); break;}
          case unsigned_long_TYPE :   {puAppend_mt(array, long, ulCell(APND,i) ); break;}
          case string_TYPE:  {psAppend_mt(array, sCell(APND,i) ); break;}
          case MULTI_TYPE:  {break;}
       }
    }while( ++i < APND_data.len );
    if(array_data->rows==0) array_data->rows=1;
    array_data->rows++;
    array_data->cols=APND_data.len;
    array_data->dims=2;
    return array;
}

MT_CELL * Zap_range_mt(MT_CELL * array, DS_ARRAY * array_data){
    
    int __rToDel__=array_data->rowi;
    
    if(array_data->rowe<=array_data->len){
        New_mt_array(Temp);
        int i;
        for ( i=0; i<array_data->len; i++){
            if( i != __rToDel__ ){
                switch( Cell_type(array,i)) {
                    case int_TYPE :    {Append_mt(Temp, int, iCell(array,i) ); break;}
                    case float_TYPE :  {Append_mt(Temp, float, fCell(array,i) ); break;}
                    case double_TYPE : {Append_mt(Temp, double, dCell(array,i) ); break;}
                    case long_TYPE :   {Append_mt(Temp, long, lCell(array,i) ); break;}
                    case unsigned_int_TYPE :    {uAppend_mt(Temp, int, uiCell(array,i) ); break;}
                    case unsigned_long_TYPE :   {uAppend_mt(Temp, long, ulCell(array,i) ); break;}
                    case string_TYPE:  {sAppend_mt(Temp, sCell(array,i) ); break;}
                    case MULTI_TYPE:  {break;}
                }
            }else{
                __rToDel__ += __rToDel__ > array_data->rowe ? -1 : array_data->rowinc;
            }
        }

        pFree_total_array_mt(array);
        array_data->len = Temp_data.len;
        array_data->dims=1;
        return Temp;
    }else{
       Msg_red("Zap_range_mt : rango a borrar fuera de sí mismo");
    }
    return array;
}

MT_CELL * Delete_lst_mt(MT_CELL * array, DS_ARRAY * array_data, int __rToDel__){
    if(__rToDel__>=0 && __rToDel__<array_data->len){
        if ( array_data->len-1 == 0 ){
            pFree_total_array_mt(array);
        }else{
        Dim( array_data->len-1 ) as_mt_array(Temp);
        int i,j=0;
        for ( j=0,i=0; i<array_data->len; i++){
            if( i != __rToDel__ ){
                switch( Cell_type(array,i)) {
                    case int_TYPE :    {Chg(Temp, int, j, iCell(array,i) ); break;}
                    case float_TYPE :  {Chg(Temp, float, j, fCell(array,i) ); break;}
                    case double_TYPE : {Chg(Temp, double, j, dCell(array,i) ); break;}
                    case long_TYPE :   {Chg(Temp, long, j, lCell(array,i) ); break;}
                    case unsigned_int_TYPE :    {Chg(Temp, int, j, uiCell(array,i) ); break;}
                    case unsigned_long_TYPE :   {Chg(Temp, long, j, ulCell(array,i) ); break;}
                    case string_TYPE:  {sChg(Temp, j, sCell(array,i) ); break;}
                    case MULTI_TYPE:  {break;}
                }
                j++;
            }
        }

        pFree_total_array_mt(array);
        array_data->len = Temp_data.len;
        array_data->dims=1;
        return Temp;
        }
    }else{
       Msg_red("Delete_lst_mt : posición a borrar fuera de rango");
    }
    return array;
}


MT_CELL * Insert_lst_mt(MT_CELL * array, DS_ARRAY * array_data, 
                        MT_CELL * APND,  DS_ARRAY * APND_data, int __rToIns__){
    if(__rToIns__>=0 && __rToIns__<array_data->len){ 
        Dim( array_data->len + APND_data->len ) as_mt_array(Temp);
        int i;
        for ( i=0; i<__rToIns__; i++){
            switch( Cell_type(array,i)) {
                case int_TYPE :    {Chg(Temp, int, i, iCell(array,i) ); break;}
                case float_TYPE :  {Chg(Temp, float, i, fCell(array,i) ); break;}
                case double_TYPE : {Chg(Temp, double, i, dCell(array,i) ); break;}
                case long_TYPE :   {Chg(Temp, long, i, lCell(array,i) ); break;}
                case unsigned_int_TYPE :    {Chg(Temp, int, i, uiCell(array,i) ); break;}
                case unsigned_long_TYPE :   {Chg(Temp, long, i, ulCell(array,i) ); break;}
                case string_TYPE:  {sChg(Temp, i, sCell(array,i) ); break;}
                case MULTI_TYPE:  {break;}
            }
        }
        int jPos=__rToIns__;
        for( i=0; i < APND_data->len; i++){
            switch( Cell_type(APND,i)) {
                case int_TYPE :    {Chg(Temp, int, jPos, iCell(APND,i) ); break;}
                case float_TYPE :  {Chg(Temp, float, jPos, fCell(APND,i) ); break;}
                case double_TYPE : {Chg(Temp, double, jPos, dCell(APND,i) ); break;}
                case long_TYPE :   {Chg(Temp, long, jPos, lCell(APND,i) ); break;}
                case unsigned_int_TYPE :    {Chg(Temp, int, jPos, uiCell(APND,i) ); break;}
                case unsigned_long_TYPE :   {Chg(Temp, long, jPos, ulCell(APND,i) ); break;}
                case string_TYPE:  {sChg(Temp, jPos, sCell(APND,i) ); break;}
                case MULTI_TYPE:  {break;}
            }
            jPos++;
        }
        for ( i=__rToIns__; i<array_data->len; i++){
            switch( Cell_type(array,i)) {
                case int_TYPE :    {Chg(Temp, int, jPos, iCell(array,i) ); break;}
                case float_TYPE :  {Chg(Temp, float, jPos, fCell(array,i) ); break;}
                case double_TYPE : {Chg(Temp, double, jPos, dCell(array,i) ); break;}
                case long_TYPE :   {Chg(Temp, long, jPos, lCell(array,i) ); break;}
                case unsigned_int_TYPE :    {Chg(Temp, int, jPos, uiCell(array,i) ); break;}
                case unsigned_long_TYPE :   {Chg(Temp, long, jPos, ulCell(array,i) ); break;}
                case string_TYPE:  {sChg(Temp, jPos, sCell(array,i) ); break;}
                case MULTI_TYPE:  {break;}
            }
            jPos++;
        }
        pFree_total_array_mt(array);
        array_data->len = Temp_data.len;
        array_data->dims=1;
        return Temp;
    }else{
       Msg_red("Insert_lst_mt : posición a insertar fuera de rango");
    }
    return array;
}


MT_CELL * Insert_row_mt(MT_CELL * array, DS_ARRAY * array_data, 
                        MT_CELL * APND,  DS_ARRAY * APND_data, int __rToIns__){

   if(array_data->rows == 0) array_data->rows=1;
   if(array_data->cols == 0) array_data->cols=array_data->len;

   if(__rToIns__>=0 && __rToIns__<array_data->rows){

       Dim(array_data->rows+1, array_data->cols) as_mt_array(Temp);
       int i,j;
       for( i=0; i < __rToIns__; i++){
           for( j=0; j < array_data->cols; j++){
               //Let( Cell(Temp,i,j), pCell(array,i,j) );
               switch( pCell_type(array,i,j)) {
                    case int_TYPE :    {Chg(Temp, int, i,j, piCell(array,i,j) ); break;}
                    case float_TYPE :  {Chg(Temp, float, i,j, pfCell(array,i,j) ); break;}
                    case double_TYPE : {Chg(Temp, double, i,j, pdCell(array,i,j) ); break;}
                    case long_TYPE :   {Chg(Temp, long, i,j, plCell(array,i,j) ); break;}
                    case unsigned_int_TYPE :    {Chg(Temp, int, i,j, puiCell(array,i,j) ); break;}
                    case unsigned_long_TYPE :   {Chg(Temp, long, i,j, pulCell(array,i,j) ); break;}
                    case string_TYPE:  {sChg(Temp, i,j, psCell(array,i,j) ); break;}
                    case MULTI_TYPE:  {break;}
               }
           }
       }
       int jCol=0;
       for( i=0; i < APND_data->len; i++){
           //Let( Cell(Temp,__rToIns__,jCol), APND[i] );
           switch( Cell_type(APND,i)) {
                case int_TYPE :    {Chg(Temp, int, __rToIns__,jCol, iCell(APND,i) ); break;}
                case float_TYPE :  {Chg(Temp, float, __rToIns__,jCol, fCell(APND,i) ); break;}
                case double_TYPE : {Chg(Temp, double, __rToIns__,jCol, dCell(APND,i) ); break;}
                case long_TYPE :   {Chg(Temp, long, __rToIns__,jCol, lCell(APND,i) ); break;}
                case unsigned_int_TYPE :    {Chg(Temp, int, __rToIns__,jCol, uiCell(APND,i) ); break;}
                case unsigned_long_TYPE :   {Chg(Temp, long, __rToIns__,jCol, ulCell(APND,i) ); break;}
                case string_TYPE:  {sChg(Temp, __rToIns__,jCol, sCell(APND,i) ); break;}
                case MULTI_TYPE:  {break;}
           }
           jCol++;
       }
       int jRow=__rToIns__+1;
       for( i=__rToIns__; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               //Let( Cell(Temp,jRow,j), pCell(array,i,j) );
               switch( pCell_type(array,i,j)) {
                   case int_TYPE :    {Chg(Temp, int, jRow,j, piCell(array,i,j) ); break;}
                   case float_TYPE :  {Chg(Temp, float, jRow,j, pfCell(array,i,j) ); break;}
                   case double_TYPE : {Chg(Temp, double, jRow,j, pdCell(array,i,j) ); break;}
                   case long_TYPE :   {Chg(Temp, long, jRow,j, plCell(array,i,j) ); break;}
                   case unsigned_int_TYPE :    {Chg(Temp, int, jRow,j, puiCell(array,i,j) ); break;}
                   case unsigned_long_TYPE :   {Chg(Temp, long, jRow,j, pulCell(array,i,j) ); break;}
                   case string_TYPE:  {sChg(Temp, jRow,j, psCell(array,i,j) ); break;}
                   case MULTI_TYPE:  {break;}
               }
           }
           jRow++;
       }
       pFree_total_array_mt(array);
       
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }else{
       Msg_red("Insert_row_mt : fila a insertar fuera de rango");
   }
   return array;
}

MT_CELL * Insert_col_mt(MT_CELL * array, DS_ARRAY * array_data, 
                        MT_CELL * APND, DS_ARRAY *APND_data, int __cToIns__){
   
   if(array_data->rows == 0) array_data->rows=array_data->len;
   if(array_data->cols == 0) array_data->cols=1;
   
   if(__cToIns__>=0 && __cToIns__<array_data->cols && APND_data->len == array_data->rows){
       Dim(array_data->rows, array_data->cols+1) as_mt_array(Temp);
       int i;
       for( i=0; i < array_data->rows; i++){
           int j;
           for( j=0; j < __cToIns__; j++){
               //Let( Cell(Temp,i,j), pCell(array,i,j) );
               switch( pCell_type(array,i,j)) {
                   case int_TYPE :    {Chg(Temp, int, i,j, piCell(array,i,j) ); break;}
                   case float_TYPE :  {Chg(Temp, float, i,j, pfCell(array,i,j) ); break;}
                   case double_TYPE : {Chg(Temp, double, i,j, pdCell(array,i,j) ); break;}
                   case long_TYPE :   {Chg(Temp, long, i,j, plCell(array,i,j) ); break;}
                   case unsigned_int_TYPE :    {Chg(Temp, int, i,j, puiCell(array,i,j) ); break;}
                   case unsigned_long_TYPE :   {Chg(Temp, long, i,j, pulCell(array,i,j) ); break;}
                   case string_TYPE:  {sChg(Temp, i,j, psCell(array,i,j) ); break;}
                   case MULTI_TYPE:  {break;}
               }
           }
           //Let( Cell(Temp,i,__cToIns__), APND[i] );
           switch( Cell_type(APND,i)) {
                case int_TYPE :    {Chg(Temp, int, i,__cToIns__, iCell(APND,i) ); break;}
                case float_TYPE :  {Chg(Temp, float, i,__cToIns__, fCell(APND,i) ); break;}
                case double_TYPE : {Chg(Temp, double, i,__cToIns__, dCell(APND,i) ); break;}
                case long_TYPE :   {Chg(Temp, long, i,__cToIns__, lCell(APND,i) ); break;}
                case unsigned_int_TYPE :    {Chg(Temp, int, i,__cToIns__, uiCell(APND,i) ); break;}
                case unsigned_long_TYPE :   {Chg(Temp, long, i,__cToIns__, ulCell(APND,i) ); break;}
                case string_TYPE:  {sChg(Temp, i,__cToIns__, sCell(APND,i) ); break;}
                case MULTI_TYPE:  {break;}
           }
           
           int jCol=__cToIns__+1;
           for( j=__cToIns__; j < array_data->cols; j++){
               //Let( Cell(Temp,i,jCol), pCell(array,i,j) );
               switch( pCell_type(array,i,j)) {
                   case int_TYPE :    {Chg(Temp, int, i,jCol, piCell(array,i,j) ); break;}
                   case float_TYPE :  {Chg(Temp, float, i,jCol, pfCell(array,i,j) ); break;}
                   case double_TYPE : {Chg(Temp, double, i,jCol, pdCell(array,i,j) ); break;}
                   case long_TYPE :   {Chg(Temp, long, i,jCol, plCell(array,i,j) ); break;}
                   case unsigned_int_TYPE :    {Chg(Temp, int, i,jCol, puiCell(array,i,j) ); break;}
                   case unsigned_long_TYPE :   {Chg(Temp, long, i,jCol, pulCell(array,i,j) ); break;}
                   case string_TYPE:  {sChg(Temp, i,jCol, psCell(array,i,j) ); break;}
                   case MULTI_TYPE:  {break;}
               }
               jCol++;
           }
       }

       pFree_total_array_mt(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
   }else{
       Msg_red("Insert_col_mt : columna a insertar fuera de rango");
   }
   return array;
}

MT_CELL * Delete_row_mt(MT_CELL * array, DS_ARRAY * array_data, int __rToDel__){
   if(__rToDel__>=0 && __rToDel__ < array_data->rows){
       if( array_data->rows-1 == 0 ){
           pFree_total_array_mt(array);
       }else{
       Dim(array_data->rows-1, array_data->cols)  as_mt_array(Temp);
       int i,j;
       for( i=0; i < __rToDel__; i++){
           for( j=0; j < array_data->cols; j++){
               //Cell(Temp,i,j) = pCell(array,i,j);
               switch( pCell_type(array,i,j)) {
                   case int_TYPE :    {Chg(Temp, int, i,j, piCell(array,i,j) ); break;}
                   case float_TYPE :  {Chg(Temp, float, i,j, pfCell(array,i,j) ); break;}
                   case double_TYPE : {Chg(Temp, double, i,j, pdCell(array,i,j) ); break;}
                   case long_TYPE :   {Chg(Temp, long, i,j, plCell(array,i,j) ); break;}
                   case unsigned_int_TYPE :    {Chg(Temp, int, i,j, puiCell(array,i,j) ); break;}
                   case unsigned_long_TYPE :   {Chg(Temp, long, i,j, pulCell(array,i,j) ); break;}
                   case string_TYPE:  {sChg(Temp, i,j, psCell(array,i,j) ); break;}
                   case MULTI_TYPE:  {break;}
               }
           }
       }
       int iRow=__rToDel__;
       for( i=__rToDel__+1; i < array_data->rows; i++){
           for( j=0; j < array_data->cols; j++){
               //Cell(Temp,iRow,j) = pCell(array,i,j);
               switch( pCell_type(array,i,j)) {
                   case int_TYPE :    {Chg(Temp, int, iRow,j, piCell(array,i,j) ); break;}
                   case float_TYPE :  {Chg(Temp, float, iRow,j, pfCell(array,i,j) ); break;}
                   case double_TYPE : {Chg(Temp, double, iRow,j, pdCell(array,i,j) ); break;}
                   case long_TYPE :   {Chg(Temp, long, iRow,j, plCell(array,i,j) ); break;}
                   case unsigned_int_TYPE :    {Chg(Temp, int, iRow,j, puiCell(array,i,j) ); break;}
                   case unsigned_long_TYPE :   {Chg(Temp, long, iRow,j, pulCell(array,i,j) ); break;}
                   case string_TYPE:  {sChg(Temp, iRow,j, psCell(array,i,j) ); break;}
                   case MULTI_TYPE:  {break;}
               }
           }
           iRow++;
       }
       pFree_total_array_mt(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
       }
   }else{
       Msg_red("Delete_row_mt : fila a borrar fuera de rango");
   }
   return array;
}

MT_CELL * Delete_col_mt(MT_CELL * array, DS_ARRAY * array_data, int __cToDel__){
   if(__cToDel__>=0 && __cToDel__ < array_data->cols){
       if( array_data->cols-1 == 0 ){
           pFree_total_array_mt(array);
       }else{
       Dim(array_data->rows, array_data->cols-1) as_mt_array(Temp);
       int i,j;
       for( i=0; i < array_data->rows; i++){
           for( j=0; j < __cToDel__; j++){
               //Cell(Temp,i,j) = pCell(array,i,j);
               switch( pCell_type(array,i,j)) {
                   case int_TYPE :    {Chg(Temp, int, i,j, piCell(array,i,j) ); break;}
                   case float_TYPE :  {Chg(Temp, float, i,j, pfCell(array,i,j) ); break;}
                   case double_TYPE : {Chg(Temp, double, i,j, pdCell(array,i,j) ); break;}
                   case long_TYPE :   {Chg(Temp, long, i,j, plCell(array,i,j) ); break;}
                   case unsigned_int_TYPE :    {Chg(Temp, int, i,j, puiCell(array,i,j) ); break;}
                   case unsigned_long_TYPE :   {Chg(Temp, long, i,j, pulCell(array,i,j) ); break;}
                   case string_TYPE:  {sChg(Temp, i,j, psCell(array,i,j) ); break;}
                   case MULTI_TYPE:  {break;}
               }
           }
           int jCol=__cToDel__;
           for( j=__cToDel__+1; j < array_data->cols; j++){
               //Cell(Temp,i,jCol) = pCell(array,i,j);
               switch( pCell_type(array,i,j)) {
                   case int_TYPE :    {Chg(Temp, int, i,jCol, piCell(array,i,j) ); break;}
                   case float_TYPE :  {Chg(Temp, float, i,jCol, pfCell(array,i,j) ); break;}
                   case double_TYPE : {Chg(Temp, double, i,jCol, pdCell(array,i,j) ); break;}
                   case long_TYPE :   {Chg(Temp, long, i,jCol, plCell(array,i,j) ); break;}
                   case unsigned_int_TYPE :    {Chg(Temp, int, i,jCol, puiCell(array,i,j) ); break;}
                   case unsigned_long_TYPE :   {Chg(Temp, long, i,jCol, pulCell(array,i,j) ); break;}
                   case string_TYPE:  {sChg(Temp, i,jCol, psCell(array,i,j) ); break;}
                   case MULTI_TYPE:  {break;}
               }
               jCol++;
           }
       }

       pFree_total_array_mt(array);
       array_data->rows=Temp_data.rows;
       array_data->cols=Temp_data.cols;
       array_data->len = Temp_data.len;
       array_data->dims=2;
       return Temp;
       }
   }else{
       Msg_red("Delete_col_mt : columna a borrar fuera de rango");
   }
   return array;
}


