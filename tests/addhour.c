

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
   Assert( Arg_count==2, fail_input );
   Get_arg_str( cTime, 1 );
   int addhour;
///   Print "cTime = [%s]\n", cTime;
   if ( Occurs(":", cTime) ){  // input: hh:mm:ss"
       int sign = 1;
       if ( cTime[0] == '-' ) { 
           sign=-1;
           Fn_let( cTime, Substr( cTime,Str_at("-",cTime)+1,strlen(cTime) ) );
       }
     //  Print "cTime = [%s]\n", cTime;
       Assert ( Is_time_valid( cTime ), fail_time );
      // Print "Es hora valida\n";
       addhour = Time2sec( cTime ) * sign;
       /////addhour *= sign;
   }else if( Occurs(",", cTime) ){  // horas>24 , minutos [0->59]
       long min=0;
       //String cmin;
       Stack{
           addhour = Str2int( Get_token(cTime,1) );
           min = Time2sec( Multi_copy( NULL, "00:", Get_token(cTime,2),NULL) );
       }Stack_off;
       //Free secure cmin;
      // Print "H=%d, M=%ld\n", addhour*60*60, min;
       //int sign = 1;
       if( addhour<0 ) {
           addhour = addhour*60*60 - min;
       }else{
           addhour = addhour*60*60 + min;
       }
       //addhour = Time2sec( cTime );
   }else{
       addhour = Time2sec( cTime );  // asume hora simple
   }
  // Print "Addhour = %d\n", addhour;
   Free secure cTime;
   ///Stop(1);
   Set_date_lang( EN );  // fix english language
   
   char * date = Get_date();
   char * time = Get_time();
   //addhour = Sign( addhour )*addhour;
   int SGN = Sign(addhour);
   
   write_human_date(date, time);
   int adddays=0;
   if( Is_non_neg(addhour) ){
      adddays = ( Time2sec(time) + addhour /**60*60*/ ) / 86400;
      Get_fn_let( time, Sec2time( (Time2sec(time) + addhour /**60*60*/ )) );
      Get_fn_let( date, Date_add( date, adddays ) );
   }else{
      int ts = Time2sec(time), nt = addhour /**60*60 */;
     // Print "TS = %d, ADD = %d\n",ts, nt;
      int subdays = ( Time2sec(time) + SGN*addhour /**60*60*/ ) / 86400;
     /// Print "DAYS- = %d\n", subdays;
      if( SGN*nt > ts ){
          Fn_let( time, Sec2time( 86400*subdays - SGN * (Time2sec(time) + addhour /**60*60*/ )) );
      }else{
          if( SGN*addhour/60/60 <= Get_hour(time) && Is_non_zero(subdays) ) subdays--;
          Fn_let( time, Sec2time( (Time2sec(time) + addhour  /**60*60*/ )) );
      }
      Get_fn_let( date, Date_add( date, SGN*subdays ) );
   }
   write_human_date(date, time);
   
   Free secure date, time;

  Exception( fail_input ){
     Msg_yellow("Use:\n   addhour <[-]nHours|[-]hh:mm[:ss]|[-]hh,mm>\n"
             "e.g.\n addhour 12 (add 12 hours)\n addhour 12:15 (add 12 hours + 15 mins)\n"
             " addhour -04:45 (subtract 4 hours + 45 mins)\n"
             " addhour 72 (add 72 hours)\n addhour -48,3 (subtract 48 hours + 3 mins)\n"
             " addhour 0,-15 (subtract 15 mins = -00:15)");
  }
  Exception( fail_time ){
     Msg_yellowf("Bad format time: %s (valid time: hh:mm[:ss])\n",cTime );
     Free secure cTime;
  }

End
