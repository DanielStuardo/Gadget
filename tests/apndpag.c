
#include <gadget/gadget.h>

LIB_GADGET_START


long * Append_pag_long( long * X, DS_ARRAY * X_data, void * XARR, DS_ARRAY * XARR_data){

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
                Append_ptr(X,long, (long)*(tmp + i) );
            } break;
        }case FLOAT: {
            float * tmp = XARR;
            for( i=0; i < nLimite; i++){
                Append_ptr(X,long, (long)*(tmp + i) );
            } break;
        }case DOUBLE: {
            double * tmp = XARR;
            for( i=0; i < nLimite; i++){
                Append_ptr(X,long, (long)*(tmp + i) );
            } break;
        }case LONG: case ULONG: {
            long * tmp = XARR;
            for( i=0; i < nLimite; i++){
                Append_ptr(X,long, (long)*(tmp + i) );
            } break;
        }case STRING: {
            char ** tmp = XARR;
            for( i=0; i < nLimite; i++){
                Append_ptr(X,long, Str2lng( *(tmp + i) ));
            }
        }
   }
        
   if( X_data->cols > XARR_data->len ){ // hay menos datos de XARR
            for( i=0; i < X_data->cols - XARR_data->len; i++){
                Append_ptr(X,long, 0 );
            }
   }

   ++X_data->rows;

   X_data->dims=2;
   
   return X;
}

Main
   

End


