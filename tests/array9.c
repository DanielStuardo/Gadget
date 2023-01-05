
#include <gadget/gadget.h>

LIB_GADGET_START


Main
   Seed(1092);
   //Dim (2,3,4) as_fill_array (x, int, ceil(rand()%10));
   Fill array x as int(2,3,4) with ceil(rand()%1000);
   
   int j,k,l;
   
      for( j=0; j<2; j++)  
         for( k=0; k<3; k++) 
            for( l=0; l<4; l++) 
                Print "%d,%d,%d = %d\n", j,k,l, $x [ j, k, l];
   
   Prnl

   Print "Ahora usando las macros de Gadget:\n";

   All range for x;

        For_each_page(x, k){
            Print "  Page: %d\n", k;
            Compute_for( x, l, j,
                Print "    %d,%d,%d = %d\n", l,j,k, $x[ l,j,k]; 
            );
            Prnl;
        }
        Prnl;

   
   DS_MAXMIN maxNode = Max_array( pSDS(x) );
   Print "\nMayor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d\n\n", maxNode.row, maxNode.col, maxNode.pag;
   Print "Elemento en %d,%d,%d = %d\n", maxNode.row, maxNode.col, maxNode.pag,\
                          $x[maxNode.row, maxNode.col, maxNode.pag];
   
// TODO: Get_coor 4D tiene problemas para obtener pagina y libro!!!!
   int fila=0, col=0, pag=0;
   Get_coor( maxNode.local, SMD(&x), &fila, &col, &pag );
   Print "\nGet coord: f: %d, c: %d, p: %d\n", fila,col,pag; 
   
   maxNode = Min_array( pSDS(x) );
   Print "\nMenor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d\n\n", maxNode.row, maxNode.col, maxNode.pag;
   Print "Elemento en %d,%d,%d = %d\n", maxNode.row, maxNode.col, maxNode.pag,\
                          $x[maxNode.row, maxNode.col, maxNode.pag];
   Get_coor(maxNode.local, SMD(&x), &fila, &col, &pag);
   Print "\nGet coord: f: %d, c: %d, p: %d\n", fila,col,pag; 
   Print "\nElemento en 1,2,3 = %d\n", $x[1,2,3];
   Print "Elemento en 1,1,3 = %d\n", $x[1,1,3];
   Free array x;

End


