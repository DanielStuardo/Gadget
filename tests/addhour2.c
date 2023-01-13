

#include <gadget/gadget.h>

LIB_GADGET_START

void write_human_date( const char* date, const char * time )
{
    //char * cMonth = Get_monthname( Get_month( date )-1 ); 
    // model => March 7 2009 7:30pm EST
    Print "%s %d %d %d:%d%s EST\n", Get_monthname( Get_month( date )-1 ),\
                                    Get_day( date ), Get_year( date ), \
                                    Get_hour(time),Get_minute(time), \
                                    Get_hour(time)>=12 ? "pm" : "am" ;
}

Main

   Set_date_lang( EN );  // fix english language
   
   char * date = Get_date();
   char * time = Get_time();

   write_human_date(date, time);

  /* resultados quedan en la pila (forzado). No obstante, Add_time2date()
     puede ser usada fuera del Stack, como se muestra en el ejemplo.
     Es una manera de hacer que una función string devuelva más
     de un resultado. Hasta ahora, Add_time2date() es la única funcion
     del conjunto de Gadget que hace esto. */
   Add_time2date(date, time, 0, -5); 
   Stack{
       Pop_stack( date );    
       Pop_stack( time );
       Print "date = %s, time = %s\n", date, time;
   }Stack_off;
   
   write_human_date(date, time);
   
   /* Add_time puede alternar su uso con o sin stack */
   Fn_let( time, Add_time( time, 5,15 ) );
   Print "Aquí solo se alteró la hora, no la fecha:\n";
   write_human_date(date, time);
   
   Stack{
      Store ( time, Add_time( time, 5,15 ) );
   }Stack_off;
   write_human_date(date, time);
   
   Free secure date, time;
End
