
#include <gadget/gadget.h>

LIB_GADGET_START

#define TOPE 100000
Main
   String w="amoroso",z="María tenía un corderito mañoso";
   double t1=0, t2=0;
   
   int i;
   Tic(t1);
   for(i=0;i<TOPE;++i){
      Let( z, "María tenía un corderito mañoso");
      Stack{
         Store( z, Str_tran(Str_tran(z,"mañoso",Reverse(Upper(w))),"corderito","lorito") )
      }Stack_off;
   }
   Toc(t1,t2);
   Print "Z=%s\n", z;
   Print "TIME = %lf\n", t2;
   
   Tic(t1);
   for(i=0;i<TOPE;++i){
      Let( z, "María tenía un corderito mañoso");
      String s;
      s = Upper(w);
      Get_fn_let( z, Str_tran(z,"mañoso",s));
      Free secure s;
      Get_fn_let( z, Str_tran(z,"corderito","lorito"));
   }
   Toc(t1,t2);
   Print "Z=%s\n", z;
   Print "TIME = %lf\n", t2;

   Tic(t1);
   for(i=0;i<TOPE;++i){
      Let( z, "María tenía un corderito mañoso");
      String s,t;
      s = Upper(w);
      t = Str_tran(z,"mañoso",s);
      Free secure s;
      s = Str_tran(t,"corderito","lorito");
      Let ( z, s);
      Free secure s, t;
   }
   Toc(t1,t2);
   Print "Z=%s\n", z;
   Print "TIME = %lf\n", t2;
   
   Free secure z,w;
End

/*
Z=María tenía un lorito AMOROSO
TIME = 1.056897
Z=María tenía un lorito AMOROSO
TIME = 0.953549
Z=María tenía un lorito AMOROSO
TIME = 0.928191

*/
