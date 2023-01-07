
#include <gadget/gadget.h>

LIB_GADGET_START


Main
  int num[]={-5,-4,-3, 0,4,6,7,9,10,14,18,19,20,21,99,100,101};
  
  int found=0;
  /* un BUG en gadget_prepre hace que sizeof(num)/sizeof(int) falle.*/
  Print "Size = %ld\n",sizeof(num) / sizeof(int);
  bScan( num, found, -3, 0, sizeof(num)/sizeof(int) );
  if ( Is_pos(found) ){
     Print "Pos = %d\n", found;
  }

End
