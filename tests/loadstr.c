
#include <gadget/gadget.h>

LIB_GADGET_START

     
char * get_line( char * tBuff, int nLine ){
     
     char * t = pop_stack_if_null_noLen(tBuff, "get_line","string");
     if (t==NULL) { return NULL;}
     
     String line; 
     char old_token = Get_token_sep();
     Set_token_sep('\n');
     
     /* Get_token ya está "stackificado" */
     Get_fn_or_stack ( line, Get_token(t, nLine), "get_line","get_token" );
/*     line = Get_token(t, nLine);
     if( line==NULL){
         line = pop_stack_hard("get_line","get_token");
     }*/
     free(t);
     Set_token_sep(old_token);
     Item_return_release(line);
}

Main
if( Exist_file("lista.txt") ) {
   String str;
   str = Load_string("lista.txt");
   if( str ){
      printf("String:\n%s\nLen=%d\n", str, strlen(str));
      printf("# lines : %d\n", Count_lines(str));

      Str_init(newStr);
      Stack { Store (newStr, Char_one( str, " " )); } Stack_off
      Reinit_stack;  // libera el stack
      
      printf("String:\n%s\nLen=%d\n", newStr, strlen(newStr));
      printf("# lines : %d\n", Count_lines(newStr));      
      
      String linea;
      Stack{
           Store (linea, Upper(get_line(newStr, 2)));
       } Stack_off
       
      Print "Línea #2 = %s\n", linea; 
      
      Free secure str, newStr, linea; 
   }
   
}else { Msg_red("No existe el archivo"); }
End
