
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String t;
   t = `ls -lstar *.c `;

   if( t ){
      Print "resultado de LS xSYS:\n%s\nLen=%ld\n", t, strlen(t);
   
         Set_token_sep ('\n');
    
         // v se inicializa dentro de la macro.
         //For each token  v in  t do  
         For_each_token ( v, t )
            Print "Token: %s\n", v;

            Set_token_sep (' ');
      
            //For each token  w in v do
            For_each_token ( w, v )
            
               Print "---Sub token: %s\n",w;
            Next_token(w)
     
            Set_token_sep ('\n');
         Next_token(v)
   
      Free secure t;
   }else{
       Msg_red("no se pudo ejecutar la línea");
   }
   
  /* dentro del stack */
   Stack{
      Store ( t, Str_tran( Str_tran(Upper(Get_sys("ls -lstar *.txt")),"XU","ROOT"), "NOV","NOVEMBER"));
   } Stack_off
   Print "\nSistema devuelve:\n%s\n",t;
   Free secure t;
   
End
