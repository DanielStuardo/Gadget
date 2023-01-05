#include <gadget/gadget.h>

LIB_GADGET_START

void imprime_array_mt( MT_CELL *array, DS_ARRAY array_data , int x, int y );

Main
    Cls;
    //New_mt_array( test );
    New multitype test;

    Append_mt(test, int, 15);
    Append_mt(test, float, -1.0/4.0);
    Append_mt(test, double, sqrt(30*3.1415));
    Append_mt(test, float, -2.0/4.0);
    sAppend_mt(test, "María tenía un corderito");
    Append_mt(test, float, -3.0/4.0);
    Append_mt(test, long, 100000000);
    Append_mt(test, float, -4.0/4.0);
    sAppend_mt(test, "su piel era blanca como la nieve");
    Append_mt(test, float, -5.0/4.0);
    Append_mt(test, double, 1.34e-4);
    Append_mt(test, float, -6.0/4.0);
    Append_mt(test, int, 100 );

    At 4,2; Print "Array original:";
    At 5,2;
    Solid_box_std(15,35,103,25);    
    imprime_array_mt( SDS(test), 6, 3 );

    Range for test [ 1:2:Len(test) ];
    test = Zap_range_mt(pSDS(test)); // $$test[1:2:Len(test) ] = []; $$test[3]=[]; por ver.
    
    At 4,40; Print "Nuevo Array:";
    At 5,40;
    Solid_box_std(15,35,103,25);    

    imprime_array_mt( SDS(test), 6,41 );
    At 25,0;
    //Free_total_array_mt(test);
    Free multitype test;

End

void imprime_array_mt( MT_CELL *array, DS_ARRAY array_data, int x, int y ){
   
   int i;
   At x, y;
   Iterator up i [0: 1: Len(array)]{
       Atrow x++; Color(121,25); Print_Cell( array, i );
   }
   Reset_color;
}


