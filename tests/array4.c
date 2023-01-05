
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); 
void incrementa_valor_lista( pRDS(void, lista) );

Main

   Fill array dNum as double(5,5) with rand()%100 / 1.0 ; 

   Fill array lista as double ( (int)(10/2) ) with 100.0;
   
   int i=5;
   while ( i-- ){
      dNum = (double*) Append_col( pSDS(dNum), pSDS(lista));
      incrementa_valor_lista( pSDS(lista) );
   }
   
   New array arreglo_clonado as double;
   arreglo_clonado = (double*)Clone_array( SMD(&arreglo_clonado), pSDS(lista));
   
   lista = (double*)Append_lst( pSDS(lista), pSDS(arreglo_clonado) );
   
   i=5;
   while ( i-- ){
      dNum = (double*) Append_row( pSDS(dNum), pSDS(lista));
      incrementa_valor_lista( pSDS(lista) );
   }

   All range for dNum;
   
   Imprime_el_array( pSDS(dNum), "Imprimiendo todo el array" );
   Prnl;
   Free array dNum, lista, arreglo_clonado;
   
End

void incrementa_valor_lista( pRDS(void, lista) ){
   int i;
   Rescue_DS_ptr( double*, tmp, lista);  // copia puntero array y data set.
   //double * tmp = lista;     // copia solo puntero array
   Iterator up i [ 0: 1: pLen(tmp)]{
       @tmp[i] *= 2;
   }
}

void Imprime_el_array( pRDS( void, X ), const char * msg ){ 
   
   int i,j;
   Print "%s:\n", msg;
   if( pType(X) == DOUBLE ){
       Rescue_DS_ptr( double*, tmp, X);
       pIterup ( row, X, i){
           pIterup ( col, X, j){
              Print "%.*f", 2, @tmp[i, j];
              if ( j < pCols(X)-1 ) 
                  Print ", ";
           }
           Prnl;
       }
   }
}
