
/*
   Todos los arrays en GADGET son de una dimensión, y se calculan sus posiciones 
   según la dimensión "virtual" con que fueron creados.
   Una manera de evitar hacer el cálculo de posiciones de manera repetida, es
   usar Node(), y así podemos tratar al array como lo que es, una sucia colección
   de elementos de una sola dimensión.
   
   int index = NODE(array,row[,col[,pag[,book]]]) hace este trabajo.
   
*/

#include <gadget/gadget.h>

LIB_GADGET_START

Main
    Fill array prueba as double(5,5) with (double)(rand()%1000);
    
    
    
    int i,j, in;
    Iterator up i [0:1:Rows(prueba)]{
       Iterator up j [0:1:Cols(prueba)]{
           Print "%*.*f, ",8,2,$prueba[i,j];
       }
       Prnl;
    }
    
    //All range for prueba;
    Range for prueba [0:2:Rows(prueba), 0:2:Cols(prueba)];
    Compute_for( prueba, i,j,
        in = Node(prueba,i,j);
        prueba[in] = sqrt(prueba[in]/0.5);
    );
    Prnl;
    
    Iterator up i [0:1:Rows(prueba)]{
       Iterator up j [0:1:Cols(prueba)]{
           if ( Is_even(i) && Is_even(j) ) Color_fore(121);
           Print "%*.*f\033[0m, ",8,2,$prueba[i,j];
       }
       Prnl;
    }
    
    Free array prueba;

End
