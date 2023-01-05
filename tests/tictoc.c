
#include <gadget/gadget.h>

LIB_GADGET_START

Main
  float t1, t2, t3;
  Tic(t1); Tic(t3)
  for( int i=0; i<=100000; ++i ){
     ///printf("I = %d\n",i);
     if( Timer( &t3, 100) ){
        printf("I = %d\t--> CLOCK!\n",i);
     }
  }
  Toc(t1,t2)
  printf("Time = %f\n", t2);
  Str_init(tiempo)
  tiempo = Sec2time(t3);
  if( tiempo ){
     printf("Tiempo = %s\n", tiempo );
     Free_secure( tiempo );
  }
  printf("Time2sec = %ld\n", Time2sec("12:45:22"));
  tiempo = Elaptime("12:45:00","13:45:00:05");
  if(tiempo){
     printf("Tiempo = %s\n", tiempo );
     Free_secure( tiempo );
  }
  printf("Días en el mes de Abril: %d\n", Days_in_month(4, Is_leap_year(2022)));
  printf("Día del año 11 de Abr de 2022: %d\n", Day_of_year("11/04/2022"));
  printf("Día del año 2 de Febrero de 2022: %d\n", Day_of_year("2/2/2022"));
  Str_init(formato)
  formato = Get_date_format(ACTUAL_DATE_FORMAT);
  printf("Actual formato de fecha: %s\n", formato);
  Free_secure(formato);
  printf(" Es válida la fecha 22/1/1987? = %d\n", Is_date_valid("22/1/1987"));
  printf(" Es válida la hora 21:56:09? = %d\n", Is_time_valid("21:56:09"));
  printf(" Es válida la fecha 29/2/2022? = %d\n", Is_date_valid("29/2/2022"));
  printf(" Es válida la hora 28:56:09? = %d\n", Is_time_valid("28:56:09"));
  printf("Es año bisiesto 2016? = %d\n", Is_leap_year(2016));
  printf("Es año bisiesto 2017? = %d\n", Is_leap_year(2017));

  printf("Semana del año 11/04/2022 : %d\n", Week_of_year("11/04/2022"));
  printf("Semana del año 12/1/2022 : %d\n", Week_of_year("12/01/2022"));
  Set_date_format(CHOLIN);
  formato = Get_date_format(ACTUAL_DATE_FORMAT);
  printf("Actual formato de fecha: %s\n", formato);
  Free_secure(formato);

  printf("Semana del año 2022/04/11 : %d\n", Week_of_year("2022/04/11"));
  printf("Semana del año 2022/1/12 : %d\n", Week_of_year("2022/1/12"));


  printf(" Es válida la fecha 2054/12/31? = %d\n", Is_date_valid("2054/12/31"));
  printf(" Es válida la fecha 2054/13/31? = %d\n", Is_date_valid("2054/13/31"));
  Str_init(timeNow)
  timeNow = Get_timestamp();
  printf("HORA Y FECHA ACTUAL (timestamp) = %s\n", timeNow);
  Free_secure(timeNow);
  timeNow = Get_date();
  printf("Fecha actual: %s\n", timeNow);
  printf(" -->Desglosada: %d : %d : %d\n",Get_year(timeNow), Get_month(timeNow), 
                                               Get_day(timeNow));
  Free_secure(timeNow);
  
  Set_date_format(BARBARA);
  formato = Get_date_format(ACTUAL_DATE_FORMAT);
  printf("Actual formato de fecha: %s\n", formato);
  Free_secure(formato);

  timeNow = Get_timestamp();
  printf("HORA Y FECHA ACTUAL (timestamp) = %s\n", timeNow);
  Free_secure(timeNow);

  timeNow = Get_date();
  printf("Fecha actual: %s\n", timeNow);
  printf(" -->Desglosada: %d : %d : %d\n",Get_year(timeNow), Get_month(timeNow), 
                                               Get_day(timeNow));

// probar first monday en otro día de la semana 
  Set_first_monday
  printf("(first monday)       Día de la semana: %d\n", Day_of_week(timeNow));
  Unset_first_monday
  printf("(unset first monday) Día de la semana: %d\n", Day_of_week(timeNow));

  Set_first_monday
  printf("(first monday)       Día de la semana: %d\n", Day_of_week("29/11/2022"));
  Unset_first_monday
  printf("(unset first monday) Día de la semana: %d\n", Day_of_week("29/11/2022"));
  

  Str_init(addDate)
  addDate = Date_add( timeNow, 15 );
  printf("Fecha actual + 15 días : %s\n", addDate);
  Free_secure(addDate);
  addDate = Date_add( timeNow, -15 );
  printf("Fecha actual - 15 días : %s\n", addDate);
  
  Free secure addDate, timeNow;
  
  timeNow = Get_time();
  printf("Hora actual: %s\n", timeNow);
  printf(" Es válida la hora %s? = %d\n", timeNow, Is_time_valid(timeNow));
  printf(" -->Desglosada: %d : %d : %d : %d\n",Get_hour(timeNow), Get_minute(timeNow), 
                                               Get_second(timeNow), Get_millisecond(timeNow));
  Free_secure(timeNow);
  
  
  Str_init(dia1)              Str_init(dia2)
  Let(dia1, "12/02/2022")     Let(dia2, "21/02/2022")
  long dias = Days_diff( dia1, dia2 );
  printf("Días entre %s y %s = %ld\n",dia1,dia2,dias);
  Free secure dia1, dia2;
End

