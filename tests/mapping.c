#include <gadget/gadget.h>

LIB_GADGET_START

Main
    Fill array x as int(10,10) with ceil( rand() % 10 );

    All range for x;
    Map2( x, i,j,
          $x[i,j]=0,  $x[i,j]<3,
          $x[i,j]=-1, $x[i,j]>7,
          $x[i,j]=5 /* para todo lo demás */ )
    
    Iterup(row,x, i){
        Iterup(col,x,j){
            Print "%3d,", $x[i,j];
        } Prnl; 
    } Prnl

    Free array x;
End
