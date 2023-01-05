
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String v="María tenía un corderito\nSu piel era blanca como la nieve\n";
   int nSave=0;
   Stack {
      nSave  = Save_string( Upper(v), "poema25.txt");
      nSave += Append_string( Upper("Crecía en praderas verdes\nY su nombre era Septiembre\n"), "poema25.txt");
      nSave += Append_string(Reverse(Upper("\nY no sabía por qué\npero su mundo estaba al revés")), "poema25.txt");
   } Stack_off
   
   if ( nSave == 3 ){
      String w;
      w = Load_string("poema25.txt");
      //Color_fore(120); Italic; Bold;
      Canvas_terminal; Amber_pencil;
      Print "%s\n", w;
      Reset_color;
      Free secure w;
      
    /* usando stacks */
      Stack{
          Store (w, Lower(Load_string("poema25.txt")));
      }  Stack_off
      Canvas_ocean; White_pencil;
      Print "%s\n", w;
      Reset_color;
      Free secure w;
   }
   
   Free secure v;
End
