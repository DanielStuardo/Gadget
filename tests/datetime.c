
#include <gadget/gadget.h>

LIB_GADGET_START


Main

   char * fecha = Get_date();
   char * hora = Get_time();
   char * fecha_hora = Get_timestamp();
   Print "Fecha actual = %s\nHora actual = %s\nTimestamp = %s\n", fecha, hora, fecha_hora;

   Print "Día = %d, Mes = %d, Año = %d\n", Get_day(fecha), Get_month(fecha), Get_year(fecha);

   Print "Día de la semana = %d (contando \"domingo\" como primer día)\n", Day_of_week(fecha);
   char * dayname = Get_dayname(Day_of_week(fecha));
   Print "Día = %s\n", dayname;   
   Set_first_monday;
   Print "Día de la semana = %d (contando \"lunes\" como primer día)\n", Day_of_week(fecha);
   dayname = Get_dayname(Day_of_week(fecha));
   Print "Día = %s\n", dayname;
   Unset_first_monday;
   
   Print "Is date valid (%s)? = %d\n", fecha,Is_date_valid(fecha);
   Print "Is time valid (%s)? = %d\n", hora, Is_time_valid(hora);
   Print "Es año bisiesto (%d)? = %d\n", Get_year(fecha), Is_leap_year(Get_year(fecha));
   
   Print "\nFechas con cambio de formato:\n";
   int nuevo_formato;
   Iterator up nuevo_formato [DMY:1:YMD_2+1]{
       char * subfecha = Date_format(fecha, nuevo_formato);
       Print "Fecha con formato %d = %s\n", nuevo_formato, subfecha;
       Free secure subfecha;
   }
   
   Print "Pero puede leer la fecha con otro formato:\n";
   Set_date_format( YMD );
   char * misma_fecha = Get_date();
   Print "Fecha con formato YMD(%d) = %s\n", ACTUAL_DATE_FORMAT, misma_fecha;

   Set_date_format( DMY );
   long julian_date = Get_julian_date(Get_year(fecha), Get_month(fecha), Get_day(fecha));
   Print "Fecha codificada: %ld\n", julian_date;
   int Ano=0, Mes=0, Dia=0;
   Decode_julian_date( julian_date, &Ano, &Mes, &Dia );
   Print "Fecha decodificada: %2d/%2d/%4d\n", Dia, Mes, Ano;

   Print "Datos anexos...\n";
   Print "Día del año = %d\n", Day_of_year( fecha );
   Print "Semana del año = %d\n", Week_of_year( fecha );
   Print "Días en este mes = %d\n", Days_in_month( Get_month(fecha), Is_leap_year(Get_year(fecha)) );
   char *nueva_fecha = Date_add(fecha, 10);
   Print "\nSumo 10 días a la fecha actual = %s\n", nueva_fecha;
   Stack{ Store(  nueva_fecha, Date_add(nueva_fecha, -10)) } Stack_off;
   Print "Resto 10 días a la fecha actual = %s\n", nueva_fecha;

   Print "¿Cuántos días hay entre la fecha actual y 01/6/2019? = %ld\n", Days_diff( "1/6/2019", fecha);

   Print "\nDía y mes actual en diferentes idiomas:\n";
   ////Stack{ Store(  fecha, Date_add(fecha, 39)) } Stack_off;
   
   Set_first_monday;
   int i;
   char * languages[]={"Español","Inglés","Francés","Alemán","Italiano"};
   Iterator up i [SP : 1 : IT+1]{
       Set_date_lang(i);
       char *cDia = Get_dayname( Day_of_week(fecha) );
       char *cMes = Get_monthname( Get_month(fecha)-1);
       Print "Día de hoy = %s\tmes actual = %s\tidioma = %s\n", cDia, cMes, languages[i];
   }
   Set_date_lang(SP);  // seteo español
      
   Free secure fecha, fecha_hora, misma_fecha, nueva_fecha; //, dayname;
   
   Print "\nHORAS...\n";
   /* Time2sec y Sec2time no consideran los milisegundos */
   Print "Hora (%s) a segundos = %ld segs\n", hora, Time2sec(hora);
   long segs = Time2sec(hora);
   char * otra_hora = Sec2time(segs);
   Print "Segundos (%ld) a hora = %s\n", segs, otra_hora;
   
   Print "\nDesmembrando la hora:\n";
   Print "Hora         = %d\n", Get_hour( hora);
   Print "Minutos      = %d\n", Get_minute( hora);
   Print "Segundos     = %d\n", Get_second( hora);
   Print "Milisegundos = %d\n", Get_millisecond( hora);

   Print "\nTiempo entre %s y 3:12:47\n", hora;
   char *elap = Elaptime( hora, "3:12:47");
   Print "Transcurre = %s\n", elap;

   Free secure hora, otra_hora,elap;
   
End



