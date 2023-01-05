
#include <gadget/gadget.h>

LIB_GADGET_START
#define FILENAME   "archivo.txt"
Main
   
   F_STAT data = Stat_file(FILENAME);
   if( data.total_lines ){
      Print "File: "FILENAME"\n";
      Print "Total lines         = %d\n",  data.total_lines;
      Print "Size                = %ld\n", data.size;
      Print "Max. long line      = %d\n",  data.max_line_long;
      Print "Max. token per line = %d\n",  data.max_tokens_per_line;
      Print "Is matrix shape ?   = %s\n",  data.is_matrix ? "Yes":"Nope"; 
   }

End
