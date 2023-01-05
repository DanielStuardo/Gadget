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
            New_mt_array( test );
            /* establezco los rangos a leer */
            Range for test [0:1:dataFile.total_lines-1, 0:1:dataFile.max_tokens_per_line-1];
            
            /* cargo el archivo con todos los números de tipo double*/
            test = Load_matrix_mt( pSDS(test), "save_matrix.txt", dataFile, ALL_DOUBLE);
            
            /* imprimo la matrix */
            Print "Archivo cargado (todo double):\n";
            imprime_array_mt_3( SDS(test) );
            
            /* veré que cargó en el último double, que se ve solo 0.00000 */
            char * sNotat = Num2notation( dCell(test,6,4) );
            Print "\nLa celda 6,4 tiene    = %s\n", sNotat;
            Print "Número sin conversión   = %g\n", dCell(test,6,4);
            Print "Número sin conversión 2 = %.*lf\n", 30, dCell(test,6,4);
            Free secure sNotat;
            
            Print "\nImprime los tipos de la tabla anterior:\n";
            imprime_los_tipos( SDS(test));
            
            Free_array_mt(test); // no borro completamente el array, solo el cuerpo, para reutilizarlo
            
            /* al hacer free, borré los rangos establecidos anteriormente. debo volver a declararlos,
               pero ahora solo cargaré el área de datos */
            Range for test [1:1:dataFile.total_lines-1, 1:1:dataFile.max_tokens_per_line-1];
            
            /* ahora cargamos el array detectando long para números sin punto decimal */
            test = Load_matrix_mt( pSDS(test), "save_matrix.txt", dataFile, DET_LONG);
            Print "\nArchivo cargado con LONG detection (solo área de datos y precision 20 decimales):\n";
            DEC_PREC = 20; /* establece precision decimal para despliegue */
            imprime_array_mt_3( SDS(test) );
            
            Print "\nImprime los tipos de la tabla anterior:\n";
            imprime_los_tipos( SDS(test));
            
            Free_total_array_mt(test); // ahora sí que borro todo el array
            
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
               case int_TYPE :             {printf("   int"); break;}
               case float_TYPE :           {printf(" float"); break;}
               case double_TYPE :          {printf("double"); break;}
               case long_TYPE :            {printf("  long"); break;}
               case unsigned_int_TYPE :    {printf(" u_int"); break;}
               case unsigned_long_TYPE :   {printf("u_long"); break;}
               case string_TYPE:           {printf("char *"); break;}
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


