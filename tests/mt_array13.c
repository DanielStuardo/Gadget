#include <gadget/gadget.h>
///#include "include/gadget_mt_array.h"

LIB_GADGET_START

void imprime_array_mt_3( MT_CELL *array, DS_ARRAY array_data );
void Muestra_archivo_original(void);
void imprime_los_tipos(MT_CELL *array, DS_ARRAY array_data);

Main
    if(Exist_file("save_matrix.txt"))
    {
       /* recupero informacion del archivo para su apertura segura */
        F_STAT dataFile = Stat_file("save_matrix.txt");
        if(dataFile.is_matrix)   // tiene forma de matriz???
        {
            //New_mt_array( test );
            New multitype test;
            /* establezco los rangos a leer */
            Range for test [0:1:dataFile.total_lines-1, 0:1:dataFile.max_tokens_per_line-1];
            
            /* cargamos el array todo DOUBLE */
            test = Load_matrix_mt( pSDS(test), "save_matrix.txt", dataFile, DET_LONG);
            Print "\nArchivo cargado (solo área de datos y precision 20 decimales):\n";
            DEC_PREC = 20; /* establece precision decimal para despliegue */
            imprime_array_mt_3( SDS(test) );

           /* seleccionamos la columna 4 (3), todas las filas numéricas */
            int i,j;
            Fix ( col, test, 3);
            Range for test [1:1:Rows(test)];
            Compute_for ( test, i,j, 
                if ( Cell_type(test,i,j) == long_TYPE ){
                    //lCell(test,i,j) = lCell(test,i,j) / lCell(test,i,j) + lCell(test,i,1);
                    $l-test[i,j] = $l-test[i,j] / $l-test[i,j] + $l-test[i,1];
                }else{
                    //dCell(test,i,j) = dCell(test,i,j) / dCell(test,i,j) + dCell(test,i,1);
                    $d-test[i,j] = $d-test[i,j] / $d-test[i,j] + $d-test[i,1];
                }
            );

            Print "\nImprime la nueva tabla (con opcion de doubles -> notacion cientifica):\n";
            DEC_PREC = 0;     /* para que funcione Set_double_notation */
            Set_double_notation;  /* los valores doubles se verán en notacion cientifica */
            imprime_array_mt_3( SDS(test) );
            Unset_notation;    /* desactiva opcion de notacion cientifica */
            
            Print "\nImprime los tipos de la tabla anterior:\n";
            imprime_los_tipos( SDS(test));
            
            //Free_total_array_mt(test); // ahora sí que borro todo el array
            Free multitype test;
            
            Print "\nArchivo original:\n";
            Muestra_archivo_original();
            
        }else{
            Msg_red("El archivo no tiene forma de matriz.\nNo puedo cargarlo");
        }
    }else{
        Msg_red("El archivo \"save_matrix.txt\" debe ser creado con el test \"mt_array5.c\"");
    }

End

void imprime_los_tipos(MT_CELL *array, DS_ARRAY array_data){
   All range for array;
   int i,j;
   Iterup ( row, array, i){
       Iterup ( col, array, j){
           switch( Cell_type(array,i,j)){
               case INTEGER :         {printf("   int"); break;}
               case FLOAT :           {printf(" float"); break;}
               case DOUBLE :          {printf("double"); break;}
               case LONG :            {printf("  long"); break;}
               case UINTEGER :        {printf(" u_int"); break;}
               case ULONG :           {printf("u_long"); break;}
               case STRING:           {printf("char *"); break;}
               case MULTI_TYPE:  break;
           }
           if (j<Cols(array)-1) Print ", ";
       }
       Prnl;
   }   
}

void Muestra_archivo_original(){
    String csys;
    csys = `cat save_matrix.txt`;
    Print "\n%s\n", csys;
    Free secure csys;
}

void imprime_array_mt_3( MT_CELL *array, DS_ARRAY array_data ){
   
   All range for array;
   int i,j;
   Iterup ( row, array, i){
       Iterup ( col, array, j){
           Print_Cell( array, i,j ); if (j<Cols(array)-1) Print ", ";
       }
       Prnl;
   }
}


