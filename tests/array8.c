
#include <gadget/gadget.h>

LIB_GADGET_START


Main
   Seed(1092);
   //Dim (2,2,3,4) as_fill_array (x, int, ceil(rand()%10));
   Fill array x as int(2,2,3,4) with ceil(rand()%1000);
   
   int i,j,k,l;
   
   for( i=0; i<2; i++)  /* fila */
      for( j=0; j<2; j++)  /* columna */
         for( k=0; k<3; k++) /* pagina */
            for( l=0; l<4; l++) /* bloques o libro */
                Print "%d,%d,%d,%d = %d\n", i,j,k,l, $x [ i, j, k, l];
   
   Prnl

   Print "Ahora usando las macros de Gadget:\n";

   All range for x;
   For_each_book(x, l){
        Print "Book: %d\n", l;
        For_each_page(x, k){
            Print "  Page: %d\n", k;
            Compute_for( x, i, j,
                Print "    %d,%d,%d,%d = %d\n", i,j,k,l, $x[ i,j,k,l]; 
            );
            Prnl;
        }
        Prnl;
   }
   
   DS_MAXMIN maxNode = Max_array( pSDS(x) );
   Print "\nMayor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d, book: %d\n\n", maxNode.row, maxNode.col, maxNode.pag, maxNode.book;
   Print "Elemento en %d,%d,%d,%d = %d\n", maxNode.row, maxNode.col, maxNode.pag, maxNode.book,\
                          $x[maxNode.row, maxNode.col, maxNode.pag, maxNode.book];
   
// TODO: Get_coor 4D tiene problemas para obtener pagina y libro!!!!
   int fila=0, col=0, pag=0, blk=0;
   Get_coor( maxNode.local, SMD(&x), &fila, &col, &pag, &blk);
   Print "\nGet coord: f: %d, c: %d, p: %d, b: %d\n", fila,col,pag,blk; 
   
   maxNode = Min_array( pSDS(x) );
   Print "\nMenor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d, book: %d\n\n", maxNode.row, maxNode.col, maxNode.pag, maxNode.book;
   Print "Elemento en %d,%d,%d,%d = %d\n", maxNode.row, maxNode.col, maxNode.pag, maxNode.book,\
                          $x[maxNode.row, maxNode.col, maxNode.pag, maxNode.book];
   Get_coor(maxNode.local, SMD(&x), &fila, &col, &pag, &blk);
   Print "\nGet coord: f: %d, c: %d, p: %d, b: %d\n", fila,col,pag,blk; 
   Print "\nElemento en 1,1,2,3 = %d\n", $x[1,1,2,3];
   Print "Elemento en 1,1,1,3 = %d\n", $x[1,1,1,3];
   Free array x;

End


