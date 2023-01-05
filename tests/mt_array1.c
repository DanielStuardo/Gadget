#include <gadget/gadget.h>
///#include "include/gadget_mt_array.h"

LIB_GADGET_START

void imprime_array_mt( MT_CELL *array, DS_ARRAY *array_data );
void imprime_array_mt_2( MT_CELL *array, DS_ARRAY array_data );
void imprime_array_mt_3( MT_CELL *array, DS_ARRAY array_data );

MT_CELL * Cambia_array_mt(MT_CELL *array, DS_ARRAY *array_data );

Main
   //New_mt_array( test );
   New multitype test;
   
   Append_mt(test, int, 15);
   Append_mt(test, double, sqrt(30*3.1415));
   sAppend_mt(test, "María tenía un corderito");
   Append_mt(test, long, 100000000);
   Append_mt(test, float, -3.0/4.0);
   
   imprime_array_mt( pSDS(test) ); // solo para probar puntero a metadata
   
   fCell(test,4) = 1.0/2.0;
   Print "\nNuevo valor para posicion 4 = %f", fCell(test,4);
   
   /* cambio el tipo de celda 3 desde numerico a string */
   sChg(test, 3, "Su piel era blanca como la nieve");
   Print "\nNuevo valor y tipo para posicion 3 = %s\n", (char *)sCell(test,3);
   
   Print "Añadiendo más valores...\n";
   Append_mt(test,double, 0.25*sin(180*3.14+1));
   sAppend_mt(test,"esto será cambiado más adelante");
   uAppend_mt(test,int, 7829*2 );  /* unsigned int = tipo 5 */
   
   Print "\nCambio a María por Juanita...\n";
   Let( sCell(test,2), "Juanita vestía un corsé ajustado");

   Print "\nNuevo array multitipo:\n";
   imprime_array_mt_2( SDS(test) ); // sin puntero a metadata

   /* aquí se cambia el tipo de celda de string a numerico */
   sChg_type(test,6,long);
   lCell(test,6) = 9000000;
      
   Print "\nNuevo array multitipo:\n";
   imprime_array_mt_2( SDS(test) ); // sin puntero a metadata
   
   
   Print "\nAhora borramos el array y añadimos nuevos valores--todos float!...\n";
   /* elimino el array y lo cambio por otro: */
   test = Cambia_array_mt( pSDS(test) );
   
   Print "\nAquí en la posicion 0 nos quedó algo raro... %f\nLo cambiamos con \"Chg()...\"\n", fCell(test,0);
   /* cambio el tipo de celda 0, de float a double  y asigno valor*/
   Chg(test,double,0, fCell(test,4)*10);

   /* solo cambio el tipo de la celda de float a double */
   Chg_type(test,3,float,double);
   
   Print "\nNuevo array:\n";
   imprime_array_mt_2( SDS(test) );
   
   Reshape( test, 2,5);
   Print "\nCambiando la forma del array:\n";
   imprime_array_mt_3( SDS(test) );
   
   Print "\nEl valor en la celda 0,4 = %f\n\n", fCell(test,0,4);
   
   Free_total_array_mt(test); // elimina el array totalmente.
End

MT_CELL * Cambia_array_mt(MT_CELL *array, DS_ARRAY *array_data ){

  /* elimina el cuerpo del array */
   pFree_array_mt(array);
   int i;
   for( i=0; i<10; i++){
      pAppend_mt(array, float, 1.0/i); // añade en modo puntero "p"+"Append"
   }
   return array;
}

void imprime_array_mt( MT_CELL *array, DS_ARRAY *array_data ){
   int i;
   Iterator up i [0: 1: array_data->len]{
       Print "Valor %d = ", i;
       Print_Cell( array, i );
       Print "\t\tTipo = %d", Cell_type(array,i);
       Prnl;
   }
}

void imprime_array_mt_2( MT_CELL *array, DS_ARRAY array_data ){
   int i;
   Iterator up i [0: 1: array_data.len]{
       Print "Valor %d = ", i;
       Print_Cell( array, i );
       Print "\t\tTipo = %d", Cell_type(array,i);
       Prnl;
   }
}

void imprime_array_mt_3( MT_CELL *array, DS_ARRAY array_data ){
   
   All range for array;
   int i,j;
   Iterup ( row, array, i){
       Iterup ( col, array, j){
           Print_Cell( array, i,j ); if (j<Cols(array)-1) Print ",\t";
       }
       Prnl;
   }
}


