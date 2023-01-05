
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   
   /* use combinado con ReadLine */
   if( Exist_file("lista.txt") ) {
      // file exists
      
      F_SEARCH lista = Search( "lista.txt", "Juanito");
      int encontrados = SIZE_SEARCH; // no hace falta si solo se usa un SEARCH.
      
      if (lista){ // puede preguntar por SIZE_SEARCH
         int fdr,fdw;
         fdr = open( "lista.txt", O_RDONLY );
         fdw = open("prueba.txt", O_RDWR | O_CREAT, 0644);
         if ( Is_pos(fdw) && Is_pos(fdr) ){
            
            printf("Tamaño del archivo: %d\n",File_size(fdr));
            
            Set_max_readline(1024);
            
            int i;
            
            For_each_founded( i, encontrados ){
               printf("Linea: %d, offset: %d\n",Found_numline(lista,i),Found_offset(lista,i));
               Set_pos(fdr, Found_offset(lista,i));
               
               //Str_init(w);
               // debe asignar un tamaño máximo de linea posible a leer; por
               // defecto, es 512. Para cambiarlo, use SetMaxReadLine(n), con "n"
               // el nuevo tamaño máximo posible de linea a leer.
               /*w = Read_line(fdr);
                   Write_line( fdw, w );
*/
               Stack { 
                   Write_line( fdw, Upper( Read_line(fdr) ) );
               } Stack_off;
               //free(w);
            }
            
            /* liberar memoria */
            Free search lista, encontrados;
            close(fdr);
            close(fdw);
         }else{
            Str_init(msg_error); msg_error = Str_file_error(errno);
            Msg_redf("Error en la apertura o creación del archivo: %s\n",msg_error);
            Free_secure(msg_error);
            if (lista){
               Free search lista, encontrados;
            }
         }
      } else{
          Msg_amber("No matches!!\n");
      }
   } else {
    // file doesn't exist
       Msg_red("No existe el archivo\n");
   }
   if ( Exist_dir("../fl") ){
       Msg_green("Existe el direcotorio\n");
   }else{
       Msg_red("No existe el directorio\n");
   }    
       
End
