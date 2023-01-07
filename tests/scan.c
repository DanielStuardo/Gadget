

#include <gadget/gadget.h>

LIB_GADGET_START


Main
   Fill array num as int(10,10) with ceil(rand()%10);
   
   int found=0, init=0;
   
   Print "Scan ascendente:\n";
   do{
       Scan( num, found, 5, init, Len(num));
       if( Is_pos(found) ){
           int x=0, y=0;
           Get_coor( found, &num_data, &x, &y);
           Print "Pos = %d, Pos 2D = (%d, %d)\n", found, x, y;
           init = found+1;
       }
   }while( Is_pos(found) );

   Print "\nScan descendente:\n";
   init=Len(num)-1;
   do{
       Rev_scan( num, found, 5, init, -1);
       if( Is_pos(found) ){
           int x=0, y=0;
           Get_coor( found, &num_data, &x, &y);
           Print "Pos = %d, Pos 2D = (%d, %d)\n", found, x, y;
           init = found-1;
       }
   }while( Is_pos(found) );

   Prnl;
   
   All range for num;
   int i,j;
   Iterup( row, num, i){
       Iterup( col, num, j){
           Print "%d, ",$num[i,j];
       }
       Prnl;
   }

   Free array num;
End
