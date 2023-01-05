
/* Calendar : genera calendarios en un array

   modo de uso:
   New Array cal as string;
   cal = Calendar(cal,0);  
       => genera calendario del mes actual
   
   cal = Calendar(cal,n,MES,AÑO) 
       => genera calendario con fecha MES/AÑO, +/- n meses, con 1 <= "n" <= 99. 
       Ejemplo: 
          cal=Calendar(cal,2,5,2022)
       generará un array con 5 calendarios: marzo hasta julio, teniendo como centro
       el mes de mayo (5) del año 2022.
   
   cal = Calendar(cal,N,MES,AÑO) 
       => genera calendario con el MES y AÑO dado, más N meses posteriores, con 100 <= "N" < 200. 
       Si N = 100 o N = 101, es igual a Calendar( cal, 0).
       Ejemplo::
          cal=Calendar(cal,104,5,2022)
       generará un array con 4 calendarios, iniciando con mayo hasta agosto de 2022
   
   NOTA: cada calendario tiene 8 filas y 7 columnas (virtuales), por lo que, para extraer cada mes
   generado por separado, se debe tener en cuenta estas dimensiones.
   
   Los calendarios son generados en modo STRING; por lo que, si desea procesar los días, deberá 
   convertir a numérico dicho día, con int día = Str2Int( Cell(cal,row,col) ); puede usar long, o double,
   o la hueá que quiera, mientras sea numérico.
   
   Si imprime el calendario con "PrintMatrix", puede reemplazar las "," por espacios en blanco, con
   SeTTokSep(' ').

   Mr. Dalien. e-mail: daniel.stuardo@gmail.com.   
*/

#include <gadget/gadget.h>
LIB_GADGET_START

void imprime_calendario( RDS(char*, calendario), int x, int y ){
   All range for calendario; // [0:1:Rows(calendario), 0:1:Cols(calendario)];
   int i,j;
   At x,y;
   Iterup ( row,calendario,i){
      Iterup ( col,calendario,j){
          Print "%*s",4, $calendario[i,j];
      } //Atrow ++x;
      Prnl;
   }
}

Main

   New array cal as string;
   
   //cal = Calendar(cal, 0);  // pide calendario de fecha actual
   //cal = Calendar(cal, 2, 5, 2022);  // pide calendario de mayo de 2022, +/- 2 meses (incluye marzo-abril y junio-julio
   //cal = Calendar(cal, 104, 9, 2022);  // pide calendarios para los meses de mayo hasta agosto
   //cal = Calendar(cal, 103, 2, 2015);
   double t1,t2;
   Cls;
   Tic(t1);
   cal = Calendar(cal, 113, 12, 2022);
   if(cal){
      Cls;
      At 1,2; 
      Print "Len = %d, Dims = %d, Rows = %d, Cols = %d\n", cal_data.len, cal_data.dims,\
                                                           cal_data.rows, cal_data.cols;
      
      Set_token_sep(',');
      imprime_calendario( SDS(cal), 2, 5 );
      
      Toc(t1,t2);
      Msg_greenf("Proceso terminado en %f",t2);
      Free str array cal;
   }
   
   
End
