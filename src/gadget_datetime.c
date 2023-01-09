
/************************************************************************
 *
 *                LIBRERIA BASICA DE MANEJO DE FECHAS/HORAS.
 *
 ************************************************************************/
 
 
// #ifndef _LIB_GADGET_MAIN_

//#ifdef GENLIB_GADGET
#include "../include/gadget.h"
//#else
//#include <gadget/gadget.h>
//#endif

//#endif

///#include <gadget/gadget_datetime.h>

extern int FIRST_MONDAY;
extern int ACTUAL_DATE_FORMAT;

/* establece token para uso global */
extern char * __TOKEN__;

/* establece el lenguaje de días y meses */
extern int ACTUAL_LANG_DATE;

/* coordenadas de array globales */
extern int GLOBAL_ARR_ROWS;
extern int GLOBAL_ARR_COLS;
extern int GLOBAL_ARR_PAGS;
extern int GLOBAL_ARR_BOOKS;
extern int GLOBAL_ARR_DIM;

/* para algunas macros que necesitan indicar cómo salió */
extern int Is_ok;

/* ACCESO A STACK DE STRING QUE PERMITE ANIDAMIENTO */
extern int PILA_GADGET;
extern int CONTADOR_PILA;
extern char ** pila_de_trabajo;

extern int SCREEN_ROW;
extern int SCREEN_COL;


/* TIEMPO, CONTROL DE FECHAS Y HORAS */


/* función obtenida desde el Proyecto Harbour*/
double x_strVal( const char * szText, long nLen )
{
   long lVal;
   double dVal;

   if( ! __str2number__( X_FALSE, szText, nLen, &lVal, &dVal, NULL, NULL ) )
      dVal = ( double ) lVal;
   return dVal;
}

/*
 * Additional date functions
 *
 * Copyright 1999 Jose Lalin <dezac@corevia.com>
 */

/* este se invoca */
char * Get_date_format(int nType){
   char * RetVal = calloc(11,1);
   switch(nType){
      case(0): { strcpy(RetVal, "DD/MM/YYYY"); break; }
      case(1): { strcpy(RetVal, "MM/DD/YYYY"); break; }
      case(2): { strcpy(RetVal, "YYYY/MM/DD"); break; }
      case(3): { strcpy(RetVal, "DD-MM-YYYY"); break; }
      case(4): { strcpy(RetVal, "MM-DD-YYYY"); break; }
      case(5): { strcpy(RetVal, "YYYY-MM-DD"); break; }
      case(6): { strcpy(RetVal, "DD.MM.YYYY"); break; }
      case(7): { strcpy(RetVal, "MM.DD.YYYY"); break; }
      case(8): { strcpy(RetVal, "YYYY.MM.DD"); break; }
      default: { strcpy(RetVal, "DD/MM/YYYY"); break; }
   }
   if(PILA_GADGET){
      push_stack_str(RetVal); free(RetVal); return NULL;
   }
   return RetVal;
}

/* USO INTERNO */
char * x_GetDateFormat(int nType){
   switch(nType){
      case(0): return "DD/MM/YYYY";
      case(1): return "MM/DD/YYYY";
      case(2): return "YYYY/MM/DD";
      case(3): return "DD-MM-YYYY";
      case(4): return "MM-DD-YYYY";
      case(5): return "YYYY-MM-DD";
      case(6): return "DD.MM.YYYY";
      case(7): return "MM.DD.YYYY";
      case(8): return "YYYY.MM.DD";
      default: return "DD/MM/YYYY";
   }
}


char * Sec2time( long lTime )
{
   int iValue;
   char * pszTime = (char *)calloc(9,1);
   if( pszTime ){
      iValue = ( int ) ( ( lTime / 3600 ) % 24 );
      pszTime[ 0 ] = ( char ) ( iValue / 10 ) + '0';
      pszTime[ 1 ] = ( char ) ( iValue % 10 ) + '0';
      pszTime[ 2 ] = ':';
      iValue = ( int ) ( ( lTime / 60 ) % 60 );
      pszTime[ 3 ] = ( char ) ( iValue / 10 ) + '0';
      pszTime[ 4 ] = ( char ) ( iValue % 10 ) + '0';
      pszTime[ 5 ] = ':';
      iValue = ( int ) ( lTime % 60 );
      pszTime[ 6 ] = ( char ) ( iValue / 10 ) + '0';
      pszTime[ 7 ] = ( char ) ( iValue % 10 ) + '0';
      pszTime[ 8 ] = '\0';
   }
   if(PILA_GADGET){
      push_stack_str(pszTime); free(pszTime); return NULL;
   }
   return pszTime;
}

long Time2sec( const char * pszTimeBuff )
{
   ///long nLen;
   long lTime = 0;

   long nLen = 0;//strlen( pszTime );
   char * pszTime = pop_stack_if_null(pszTimeBuff, &nLen, "Time2sec","time-string");
   if (pszTime==NULL) { return -1;}

   if( nLen >= 1 )
      lTime += ( long ) x_strVal( pszTime, nLen ) * 3600;

   if( nLen >= 4 )
      lTime += ( long ) x_strVal( pszTime + 3, nLen - 3 ) * 60;

   if( nLen >= 7 )
      lTime += ( long ) x_strVal( pszTime + 6, nLen - 6 );

   free(pszTime);
   return lTime;
}


void x_timeStampGetLocal( int * piYear, int * piMonth, int * piDay,
                           int * piHour, int * piMinutes,
                           int * piSeconds, int * piMSec )
{

#if defined( HB_OS_WIN )
   {
      SYSTEMTIME st;

      GetLocalTime( &st );

      *piYear    = st.wYear;
      *piMonth   = st.wMonth;
      *piDay     = st.wDay;
      *piHour    = st.wHour;
      *piMinutes = st.wMinute;
      *piSeconds = st.wSecond;
      *piMSec    = st.wMilliseconds;
   }
#else
   {
      struct tm st;
      time_t seconds, millisecs;

#  if defined( HB_OS_UNIX ) || defined( HB_OS_OS2 )
      struct timeval tv;
      gettimeofday( &tv, NULL );
      seconds = tv.tv_sec;
      millisecs = tv.tv_usec / 1000;
#  else
      struct timeb tb;
      ftime( &tb );
      seconds = tb.time;
      millisecs = tb.millitm;
#  endif

#  if defined( HB_HAS_LOCALTIME_R )
      localtime_r( &seconds, &st );
#  else
      st = *localtime( &seconds );
#  endif

      *piYear    = st.tm_year + 1900;
      *piMonth   = st.tm_mon + 1;
      *piDay     = st.tm_mday;
      *piHour    = st.tm_hour;
      *piMinutes = st.tm_min;
      *piSeconds = st.tm_sec;
      *piMSec    = millisecs;
   }
#endif
}

long x_dateEncode( int iYear, int iMonth, int iDay )
{
   /* Perform date validation */
   if( iYear >= 0 && iYear <= X_DATE_YEAR_LIMIT &&
       iMonth >= 1 && iMonth <= 12 &&
       iDay >= 1 )
   {
      /* Month, year, and lower day limits are simple,
         but upper day limit is dependent upon month and leap year */
      static const int auiDayLimit[ 12 ] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

      if( iDay <= auiDayLimit[ iMonth - 1 ] ||
          ( iDay == 29 && iMonth == 2 &&
            ( iYear & 3 ) == 0 && ( iYear % 100 != 0 || iYear % 400 == 0 ) ) )
      {
         int iFactor = ( iMonth < 3 ) ? -1 : 0;

         return ( ( long )( iFactor + 4800 + iYear ) * 1461 / 4 ) +
                ( ( long )( iMonth - 2 - ( iFactor * 12 ) ) * 367 ) / 12 -
                ( ( long )( ( iFactor + 4900 + iYear ) / 100 ) * 3 / 4 ) +
                ( long ) iDay - 32075;
      }
   }

   return 0;
}

void x_dateDecode( long lJulian, int *piYear, int *piMonth, int *piDay )
{
   if( lJulian >= X_STR_DATE_BASE )
   {
      long U, V, W, X;

      lJulian += 68569;
      W = ( lJulian * 4 ) / 146097;
      lJulian -= ( ( 146097 * W ) + 3 ) / 4;
      X = 4000 * ( lJulian + 1 ) / 1461001;
      lJulian -= ( ( 1461 * X ) / 4 ) - 31;
      V = 80 * lJulian / 2447;
      U = V / 11;

      *piYear  = ( int ) ( X + U + ( W - 49 ) * 100 );
      *piMonth = ( int ) ( V + 2 - ( U * 12 ) );
      *piDay   = ( int ) ( lJulian - ( 2447 * V / 80 ) );
   }
   else
   {
      *piYear  =
      *piMonth =
      *piDay   = 0;
   }
}

char * x_dateFormat( const char * szDate, char * szFormattedDate, const char * szDateFormat )
{
   /*
    * NOTE: szFormattedDate must point to a buffer of at least 11 bytes.
    *       szDateFormat must point to a buffer holding the date format to use.
    */
   int format_count, digit_count, size;

   /*
    * Determine the maximum size of the formatted date string
    */
   size = ( int ) strlen( szDateFormat );
   if( size > 10 )
      size = 10;

   if( szDate && strlen( szDate ) == 8 ) /* A valid date is always 8 characters */
   {
      const char * szPtr;
      int digit;
      int used_d, used_m, used_y;

      format_count = 0;
      used_d = used_m = used_y = X_FALSE;
      szPtr = szDateFormat;

      while( format_count < size )
      {
         digit = X_TOUPPER( ( unsigned char ) *szPtr );
         szPtr++;
         digit_count = 1;
         while( X_TOUPPER( ( unsigned char ) *szPtr ) == digit && format_count < size )
         {
            szPtr++;
            if( format_count + digit_count < size )
               digit_count++;
         }
         switch( digit )
         {
            case 'D':
               switch( digit_count )
               {
                  case 4:
                     if( ! used_d && format_count < size )
                     {
                        /* szFormattedDate[ format_count++ ] = '0'; */
                        szFormattedDate[ format_count++ ] = szDate[ 6 ];
                        digit_count--;
                     }
                  case 3:
                     if( ! used_d && format_count < size )
                     {
                        /* szFormattedDate[ format_count++ ] = '0'; */
                        szFormattedDate[ format_count++ ] = szDate[ 6 ];
                        digit_count--;
                     }
                  case 2:
                     if( ! used_d && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 6 ];
                        digit_count--;
                     }
                  default:
                     if( ! used_d && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 7 ];
                        digit_count--;
                     }
                     while( digit_count-- > 0 && format_count < size )
                        szFormattedDate[ format_count++ ] = ( char ) digit;
               }
               used_d = X_TRUE;
               break;

            case 'M':
               switch( digit_count )
               {
                  case 4:
                     if( ! used_m && format_count < size )
                     {
                        /* szFormattedDate[ format_count++ ] = '0'; */
                        szFormattedDate[ format_count++ ] = szDate[ 4 ];
                        digit_count--;
                     }
                  case 3:
                     if( ! used_m && format_count < size )
                     {
                        /* szFormattedDate[ format_count++ ] = '0'; */
                        szFormattedDate[ format_count++ ] = szDate[ 4 ];
                        digit_count--;
                     }
                  case 2:
                     if( ! used_m && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 4 ];
                        digit_count--;
                     }
                  default:
                     if( ! used_m && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 5 ];
                        digit_count--;
                     }
                     while( digit_count-- > 0 && format_count < size )
                        szFormattedDate[ format_count++ ] = ( char ) digit;
               }
               used_m = X_TRUE;
               break;

            case 'Y':
               switch( digit_count )
               {
                  case 4:
                     if( ! used_y && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 0 ];
                        digit_count--;
                     }

                  case 3:
                     if( ! used_y && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 1 ];
                        digit_count--;
                     }

                  case 2:
                     if( ! used_y && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 2 ];
                        digit_count--;
                     }

                  default:
                     if( ! used_y && format_count < size )
                     {
                        szFormattedDate[ format_count++ ] = szDate[ 3 ];
                        digit_count--;
                     }
                     while( digit_count-- > 0 && format_count < size )
                        szFormattedDate[ format_count++ ] = ( char ) digit;
               }
               used_y = X_TRUE;
               break;

            default:
               while( digit_count-- > 0 && format_count < size )
                  szFormattedDate[ format_count++ ] = ( char ) digit;
         }
      }
   }
   else
   {
      /* Not a valid date string, so return a blank date with separators */
      format_count = size; /* size is either 8 or 10 */
      strncpy( szFormattedDate, szDateFormat, size );

      for( digit_count = 0; digit_count < size; digit_count++ )
      {
         switch( szFormattedDate[ digit_count ] )
         {
            case 'D':
            case 'd':
            case 'M':
            case 'm':
            case 'Y':
            case 'y':
               szFormattedDate[ digit_count ] = ' ';
         }
      }
   }

   szFormattedDate[ format_count ] = '\0';

   return szFormattedDate;
}

int x_dateUnformatRaw( const char * szDate, const char * szDateFormat, long * plDate )
{
   int d_value = 0, m_value = 0, y_value = 0;
   int iSize = 0;

   if( szDate )
   {
      int d_pos = 0, m_pos = 0, y_pos = 0;
      int count, digit, non_digit, size, used;

     // if( ! szDateFormat )
     //    szDateFormat = hb_setGetDateFormat();
      size = ( int ) strlen( szDateFormat );

      for( count = used = 0; count < size && used < 3; count++ )
      {
         switch( szDateFormat[ count ] )
         {
            case 'D':
            case 'd':
               if( d_pos == 0 )
               {
                  ++used;
                  if( m_pos == 0 && y_pos == 0 )
                     d_pos = 1;
                  else if( m_pos == 0 || y_pos == 0 )
                     d_pos = 2;
                  else
                     d_pos = 3;
               }
               break;
            case 'M':
            case 'm':
               if( m_pos == 0 )
               {
                  ++used;
                  if( d_pos == 0 && y_pos == 0 )
                     m_pos = 1;
                  else if( d_pos == 0 || y_pos == 0 )
                     m_pos = 2;
                  else
                     m_pos = 3;
               }
               break;
            case 'Y':
            case 'y':
               if( y_pos == 0 )
               {
                  ++used;
                  if( m_pos == 0 && d_pos == 0 )
                     y_pos = 1;
                  else if( m_pos == 0 || d_pos == 0 )
                     y_pos = 2;
                  else
                     y_pos = 3;
               }
         }
      }

      /* If there are non-digits at the start of the date field,
         they are not to be treated as date field separators */
      non_digit = 1;
      size = ( int ) strlen( szDate );
      for( count = used = 0; count < size; count++ )
      {
         digit = szDate[ count ];
         if( X_ISDIGIT( digit ) )
         {
            /* Process the digit for the current date field */
            if( d_pos == 1 )
               d_value = ( d_value * 10 ) + digit - '0';
            else if( m_pos == 1 )
               m_value = ( m_value * 10 ) + digit - '0';
            else if( y_pos == 1 )
               y_value = ( y_value * 10 ) + digit - '0';
            /* Treat the next non-digit as a date field separator */
            non_digit = 0;
         }
         else
         {
            /* Process the non-digit */
            if( non_digit == 0 )
            {
               /* Only move to the next date field on the first
                  consecutive non-digit that is encountered */
               non_digit = 1;
               d_pos--;
               m_pos--;
               y_pos--;
               if( ++used >= 3 )
                  break;
            }
         }
      }
      iSize = count;

      if( y_value >= 0 && y_value < 100 )
      {
         count = 1900; ///hb_setGetEpoch();
         digit = count / 100;
         count %= 100;

         if( y_value >= count )
            y_value += ( digit * 100 );
         else
            y_value += ( ( digit * 100 ) + 100 );
      }
   }

   *plDate = x_dateEncode( y_value, m_value, d_value );

   return iSize;
}

long x_dateUnformat( const char * szDate, const char * szDateFormat )
{
   long lDate;

   x_dateUnformatRaw( szDate, szDateFormat, &lDate );

   return lDate;
}

// resta horas en formato hh:MM:ss:mm
char * Elaptime( const char * cStartBuff, const char * cEndBuff ){

   char * cStart = pop_stack_if_null_noLen(cStartBuff, "Elaptime","initial date-string");
   if (cStart==NULL) { return NULL;}

   char * cEnd = pop_stack_if_null_noLen(cEndBuff, "Elaptime","end date-string");
   if (cEnd==NULL) { free(cStart); return NULL;}
   
   long lStart = Time2sec( cStart );
   long lEnd =   Time2sec( cEnd );
   char * szTime=NULL;
   szTime = Sec2time( ( lEnd < lStart ? 86400 : 0 ) + lEnd - lStart );
   
   free(cStart);free(cEnd);
   if(PILA_GADGET){
      push_stack_str(szTime); free(szTime); return NULL;
   }
   
   return szTime;
}

int ct_doy( long lDate )
{
   int iYear, iMonth, iDay;
   long lFirst;

   x_dateDecode( lDate, &iYear, &iMonth, &iDay );
   lFirst = x_dateEncode( iYear, 1, 1 );
   return ( int ) ( lDate - lFirst + 1 );
}

int Day_of_year( const char * cDateBuff )
{
   char * cDate = pop_stack_if_null_noLen(cDateBuff, "Day_of_year","date-string");
   if (cDate==NULL) { return -1;}
   
   int retVal = ct_doy( x_dateUnformat( cDate, x_GetDateFormat(ACTUAL_DATE_FORMAT) ) );
   free(cDate);
   return retVal;
}

int x_dateDOW( int iYear, int iMonth, int iDay )
{
   if( iMonth < 3 )
   {
      iMonth += 13;
      iYear--;
   }
   else
      iMonth++;

   return ( iDay + 26 * iMonth / 10 +
            iYear + iYear / 4 - iYear / 100 + iYear / 400 + 6 ) % 7 + 1;
}

int Week_of_year( const char * cDateFBuff )
{
   char * cDateF = pop_stack_if_null_noLen(cDateFBuff, "Week_of_year","date-string");
   if (cDateF==NULL) { return -1;}

   long lDate2;
   char pszTime[ 11 ];
   int iYear, iMonth, iDay;
   x_dateDecode( x_dateUnformat( cDateF, x_GetDateFormat(ACTUAL_DATE_FORMAT) ), 
                                  &iYear, &iMonth, &iDay );
   snprintf( pszTime, 11, "%02d/%02d/%4d", iDay, iMonth, iYear);
 //  printf("\033[38;5;196mWeekOfYear : %s\n\033[0m",pszTime);
   const char *cDate = pszTime;
   long lDate = x_dateUnformat( cDate, x_GetDateFormat(0) );
//   if( hb_setGetCPtr( HB_SET_DATEFORMAT ) && ( hb_setGetCPtr( HB_SET_DATEFORMAT )[ 0 ] == 'd' ||
//                                               hb_setGetCPtr( HB_SET_DATEFORMAT )[ 0 ] == 'D' ) )
//   if( x_GetDateFormat(ACTUAL_DATE_FORMAT)[0] == 'D' )
       lDate2 = lDate + 3 - ( x_dateDOW( iYear, iMonth, iDay ) + 5 ) % 7;
//   else
//       lDate2 = lDate + 4 - x_dateDOW( iYear, iMonth, iDay );
   
   free(cDateF);
   return ( ct_doy( lDate2 ) - 1 ) / 7 + 1 ;
}

int Days_in_month( int iMonth, int bLeap )
{
   if( iMonth == 2 )
      return bLeap ? 29 : 28;
   else if( iMonth == 4 || iMonth == 6 || iMonth == 9 || iMonth == 11 )
      return 30;
   else
      return 31;
}

int x_dateJulianDOW( long lJulian )
{
   if( lJulian >= X_STR_DATE_BASE )
      return ( int ) ( ( lJulian + 1 ) % 7 ) + 1 - FIRST_MONDAY;
   else
      return 0;
}

int Day_of_week( const char * cDateFBuff ){

   char * cDateF = pop_stack_if_null_noLen(cDateFBuff, "Day_of_week","date-string");
   if (cDateF==NULL) { return -1;}

   char pszTime[ 11 ];
   int iYear, iMonth, iDay;
   x_dateDecode( x_dateUnformat( cDateF, x_GetDateFormat(ACTUAL_DATE_FORMAT) ), 
                                  &iYear, &iMonth, &iDay );
   snprintf( pszTime, 11, "%02d/%02d/%4d", iDay, iMonth, iYear);

   const char *cDate = pszTime;
   int nDow = x_dateJulianDOW( x_dateUnformat( cDate, x_GetDateFormat(ACTUAL_DATE_FORMAT) ) );
   if(nDow==0) nDow=7;
   
   free(cDateF);
   return nDow;
}

int hb_timeValid( const char * szTimeBuff, long nLen, int * piDecode )
{
   char * szTime = pop_stack_if_null_noLen(szTimeBuff, "Is_time_valid","time-string");
   if (szTime==NULL) { return -1;}

   int fValid = X_FALSE;

   if( nLen == 2 || nLen == 5 || nLen == 8 || nLen == 11 )
   {
      static const int sc_iMax[] = { 23, 59, 59, 99 };
      int     i, iVal;
      long ul;

      fValid = X_TRUE;
      for( ul = 0; fValid && ul < nLen; ++ul )
      {
         fValid = ul % 3 == 2 ? szTime[ ul ] == ':' :
                  ( szTime[ ul ] >= '0' && szTime[ ul ] <= '9' );
      }
      for( ul = 0, i = 0; fValid && ul < nLen; ul += 3, ++i )
      {
         iVal   = 10 * ( szTime[ ul ] - '0' ) + ( szTime[ ul + 1 ] - '0' );
         fValid = iVal <= sc_iMax[ i ];
         if( piDecode )
            piDecode[ i ] = iVal;
      }
   }
   
   free(szTime);
   return fValid;
}

int hb_dateValid( const char * cDateBuff, long nLen ){

   char * cDate = pop_stack_if_null_noLen(cDateBuff, "Is_date_valid","date-string");
   if (cDate==NULL) { return -1;}

   int fecha_correcta = 0;
   int dia_maximo=0;
   
   int iYear, iMonth, iDay;
   x_dateDecode( x_dateUnformat( cDate, x_GetDateFormat(ACTUAL_DATE_FORMAT) ), 
                                  &iYear, &iMonth, &iDay );

   if ( iMonth >= 1 && iMonth <= 12 ){
       switch ( iMonth ){
           case  1 : case  3 : case  5 : case  7 : case  8 : case 10 :
           case 12 : dia_maximo = 31;
                     break;
           case  4 : case  6 : case  9 :
           case 11 : dia_maximo = 30;
                     break;
           case  2 : if ( ( iYear % 4 == 0 && iYear % 100 != 0 ) || iYear % 400 == 0 )
                        dia_maximo = 29;
                     else
                        dia_maximo = 28;
       }

       if ( iDay >= 1 && iDay <= dia_maximo )
           fecha_correcta = 1;
   }
   free(cDate);
   return fecha_correcta;
}

char * Get_timestamp(){
   
   char * pszTime=NULL;
   int iYear, iMonth, iDay, iHour, iMinute, iSeconds, iMillisec;
   x_timeStampGetLocal( &iYear, &iMonth, &iDay,
                         &iHour, &iMinute, &iSeconds, &iMillisec );
   pszTime = (char *)calloc(26,1);

   switch(ACTUAL_DATE_FORMAT){
      case(0): {
          snprintf( pszTime, 25, "%02d/%02d/%4d,%02d:%02d:%02d:%02d", iDay,iMonth,iYear, iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(1): {
          snprintf( pszTime, 25, "%02d/%02d/%4d,%02d:%02d:%02d:%02d", iMonth,iDay, iYear,iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(2): {
          snprintf( pszTime, 25, "%04d/%02d/%2d,%02d:%02d:%02d:%02d", iYear,iMonth,iDay, iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(3): {
          snprintf( pszTime, 25, "%02d-%02d-%4d,%02d:%02d:%02d:%02d", iDay,iMonth,iYear, iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(4): {
          snprintf( pszTime, 25, "%02d-%02d-%4d,%02d:%02d:%02d:%02d", iMonth,iDay,iYear, iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(5): {
          snprintf( pszTime, 25, "%04d-%02d-%2d,%02d:%02d:%02d:%02d", iYear,iMonth,iDay, iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }default: {
          snprintf( pszTime, 25, "%02d/%02d/%4d,%02d:%02d:%02d:%02d", iDay,iMonth,iYear, iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }
   }
   if(PILA_GADGET){
      push_stack_str(pszTime); free(pszTime); return NULL;
   }
   return pszTime;
}

char * Get_date(){
   char * pszTime=NULL;
   int iYear, iMonth, iDay, iHour, iMinute, iSeconds, iMillisec;
   x_timeStampGetLocal( &iYear, &iMonth, &iDay,
                         &iHour, &iMinute, &iSeconds, &iMillisec );
   pszTime = (char *)calloc(26,1);

   switch(ACTUAL_DATE_FORMAT){
      case(0): {
          snprintf( pszTime, 11, "%02d/%02d/%4d", iDay,iMonth,iYear );
          break;
     }case(1): {
          snprintf( pszTime, 11, "%02d/%02d/%4d", iMonth,iDay, iYear );
          break;
     }case(2): {
          snprintf( pszTime, 11, "%04d/%02d/%2d", iYear,iMonth,iDay );
          break;
     }case(3): {
          snprintf( pszTime, 11, "%02d-%02d-%4d", iDay,iMonth,iYear );
          break;
     }case(4): {
          snprintf( pszTime, 11, "%02d-%02d-%4d", iMonth,iDay,iYear );
          break;
     }case(5): {
          snprintf( pszTime, 11, "%04d-%02d-%2d", iYear,iMonth,iDay );
          break;
     }default: {
          snprintf( pszTime, 11, "%02d/%02d/%4d", iDay,iMonth,iYear );
          break;
     }
   }
   if(PILA_GADGET){
      push_stack_str(pszTime); free(pszTime); return NULL;
   }
   return pszTime;
}

char * Get_time(){
   char * pszTime=NULL;
   int iYear, iMonth, iDay, iHour, iMinute, iSeconds, iMillisec;
   x_timeStampGetLocal( &iYear, &iMonth, &iDay,
                         &iHour, &iMinute, &iSeconds, &iMillisec );
   pszTime = (char *)calloc(26,1);

   switch(ACTUAL_DATE_FORMAT){
      case(0): {
          snprintf( pszTime, 12, "%02d:%02d:%02d:%02d", iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(1): {
          snprintf( pszTime, 12, "%02d:%02d:%02d:%02d", iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(2): {
          snprintf( pszTime, 12, "%02d:%02d:%02d:%02d", iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(3): {
          snprintf( pszTime, 12, "%02d:%02d:%02d:%02d", iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(4): {
          snprintf( pszTime, 12, "%02d:%02d:%02d:%02d", iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }case(5): {
          snprintf( pszTime, 12, "%02d:%02d:%02d:%02d", iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }default: {
          snprintf( pszTime, 12, "%02d:%02d:%02d:%02d", iHour,iMinute,iSeconds, iMillisec/10 );
          break;
     }
   }
   if(PILA_GADGET){
      push_stack_str(pszTime); free(pszTime); return NULL;
   }
   return pszTime;
}
// devuelve día, mes y año por separado, en formato numérico

int Get_hour( const char * sTimeBuff ){
   int iHour;
   long nLen = 0;//strlen( sTime );
   char * sTime = pop_stack_if_null(sTimeBuff, &nLen, "Get_hour","time-string");
   if (sTime==NULL) { return -1;}
   
   if( nLen >= 8 ){
      iHour    = 10 * ( sTime[ 0 ] - '0' ) + ( sTime[ 1 ] - '0' );
   }else{
      iHour = 0;
   }
   free(sTime);
   return iHour;
}

int Get_minute( const char *sTimeBuff ){
   int iMinute;
   long nLen = 0;//strlen( sTime );
   char * sTime = pop_stack_if_null(sTimeBuff, &nLen, "Get_minute","time-string");
   if (sTime==NULL) { return -1;}
   
   if( nLen >= 8 ){
      iMinute  = 10 * ( sTime[ 3 ] - '0' ) + ( sTime[ 4 ] - '0' );
   }else{
      iMinute = 0;
   }
   free(sTime);
   return iMinute;
}

int Get_second( const char *sTimeBuff ){
   int iSeconds;
   long nLen = 0;//strlen( sTime );
   char * sTime = pop_stack_if_null(sTimeBuff, &nLen, "Get_second","time-string");
   if (sTime==NULL) { return -1;}
   
   if( nLen >= 8 ){
      iSeconds = 10 * ( sTime[ 6 ] - '0' ) + ( sTime[ 7 ] - '0' );
   }else{
      iSeconds = 0;
   }
   free(sTime);
   return iSeconds;
}

int Get_millisecond( const char *sTimeBuff ){
   int iMillisec;
   long nLen = 0;//strlen( sTime );
   char * sTime = pop_stack_if_null(sTimeBuff, &nLen, "Get_millisecond","time-string");
   if (sTime==NULL) { return -1;}
   
   if( nLen == 11 ){
      iMillisec = 10 * ( sTime[ 9 ] - '0' ) + ( sTime[ 10 ] - '0' );
   }else{
      iMillisec = 0;
   }
   free(sTime);
   return iMillisec;
}

int Get_year( const char *cDateFBuff ){

   char * cDateF = pop_stack_if_null_noLen(cDateFBuff, "Get_year","date-string");
   if (cDateF==NULL) { return -1;}
   
   int iYear, iMonth, iDay;
   x_dateDecode( x_dateUnformat( cDateF, x_GetDateFormat(ACTUAL_DATE_FORMAT) ), 
                                  &iYear, &iMonth, &iDay );
   free(cDateF);
   return iYear;
}
int Get_day( const char *cDateFBuff ){

   char * cDateF = pop_stack_if_null_noLen(cDateFBuff, "Get_day","date-string");
   if (cDateF==NULL) { return -1;}

   int iYear, iMonth, iDay;
   x_dateDecode( x_dateUnformat( cDateF, x_GetDateFormat(ACTUAL_DATE_FORMAT) ), 
                                  &iYear, &iMonth, &iDay );
   free(cDateF);
   return iDay;
}
int Get_month( const char *cDateFBuff ){

   char * cDateF = pop_stack_if_null_noLen(cDateFBuff, "Get_month","date-string");
   if (cDateF==NULL) { return -1;}

   int iYear, iMonth, iDay;
   x_dateDecode( x_dateUnformat( cDateF, x_GetDateFormat(ACTUAL_DATE_FORMAT) ), 
                                  &iYear, &iMonth, &iDay );
   free(cDateF);
   return iMonth;
}

int Timer( float * nVarTimer, float nTimeMillisec ){   // trabaja con clock().

  if( ( clock() - * nVarTimer ) * 1000 / CLOCKS_PER_SEC >= nTimeMillisec ){
      * nVarTimer = clock();
      return 1;
   }else{
      return 0;
   }
}

void x_dateStrPut( char * szDate, int iYear, int iMonth, int iDay )
{

   if( iYear >= 0 && iMonth > 0 && iDay > 0 )
   {
      szDate[ 0 ] = ( char ) ( ( ( iYear / 1000 ) % 10 ) + '0' );
      szDate[ 1 ] = ( char ) ( ( ( iYear / 100 ) % 10 ) + '0' );
      szDate[ 2 ] = ( char ) ( ( ( iYear / 10 ) % 10 ) + '0' );
      szDate[ 3 ] = ( char ) ( ( iYear % 10 ) + '0' );

      szDate[ 4 ] = ( char ) ( ( iMonth / 10 ) + '0' );
      szDate[ 5 ] = ( char ) ( ( iMonth % 10 ) + '0' );

      szDate[ 6 ] = ( char ) ( ( iDay / 10 ) + '0' );
      szDate[ 7 ] = ( char ) ( ( iDay % 10 ) + '0' );
   }
   else
   {
      memset( szDate, '0', 8 );
   }
}

char * x_dateDecStr( char * szDate, long lJulian )
{
   int iYear, iMonth, iDay;

   if( lJulian <= 0 )
   {
      memset( szDate, ' ', 8 );
   }
   else
   {
      x_dateDecode( lJulian, &iYear, &iMonth, &iDay );
      x_dateStrPut( szDate, iYear, iMonth, iDay );
   }
   szDate[ 8 ] = '\0';

   return szDate;
}

char * Date_add( const char * cDateBuff, long lEnd ){

   char * cDate = pop_stack_if_null_noLen(cDateBuff, "Date_add","date-string");
   if (cDate==NULL) { return NULL;}

   long lStart = x_dateUnformat( cDate, x_GetDateFormat(ACTUAL_DATE_FORMAT) );
   char szDate[ 9 ];
   char * szFormatted = calloc(11,1); //[ 11 ];
   //char szFormatted[ 11 ];
   
   char * retVal =  x_dateFormat( x_dateDecStr( szDate, lStart + lEnd ),
                    szFormatted, x_GetDateFormat(ACTUAL_DATE_FORMAT) );
//   free(szFormatted);
   free(cDate);
   if(PILA_GADGET){
      push_stack_str(retVal); free(retVal); return NULL;
   }
   return retVal;
}

long Days_diff( const char * cDate1Buff, const char * cDate2Buff ){
   char * cDate1 = pop_stack_if_null_noLen(cDate1Buff, "Date_diff","initial date-string");
   if (cDate1==NULL) { return -1;}
   
   char * cDate2 = pop_stack_if_null_noLen(cDate2Buff, "Date_add","end date-string");
   if (cDate2==NULL) { return -1;}
   
   long lStart = x_dateUnformat( cDate2, x_GetDateFormat(ACTUAL_DATE_FORMAT) );
   long lEnd = x_dateUnformat( cDate1, x_GetDateFormat(ACTUAL_DATE_FORMAT) );
   free(cDate1);free(cDate2);
return lStart - lEnd;
}

/* cambia el formato de una fecha */
char * Date_format( char * cDateBuff, int formato){
   char * cDate = pop_stack_if_null_noLen(cDateBuff, "Date_format","initial date-string");
   if (cDate==NULL) { return NULL;}
   
   char *subfecha = Space(12);
   char *formato_actual = Get_date_format(ACTUAL_DATE_FORMAT);
   char *nuevo_formato = Get_date_format(formato);
   long lStart = x_dateUnformat( cDate, formato_actual );
   char szDate[ 9 ];
   char * retVal =  x_dateFormat( x_dateDecStr( szDate, lStart ),
                    subfecha, nuevo_formato );
   
   free(formato_actual); free( nuevo_formato );
   free(cDate);
   Item_return_release(retVal);
}

/* CALENDAR */
#define ISO_CAL 0

////const char *line = "";

static unsigned __MONTHS_TO_DAYS__(unsigned month)
{
   return (month * 3057 - 3007) / 100;
}

static long __YEARS_TO_DAYS__(unsigned yr)
{
   return yr * 365L + yr / 4 - yr / 100 + yr / 400;
}

long __YMD_TO_SCALAR__ (unsigned yr, unsigned mo, unsigned day)
{
   long scalar;
   scalar = day + __MONTHS_TO_DAYS__(mo);
   if ( mo > 2 )                         /* adjust if past February */
      scalar -= Is_leap_year(yr) ? 1 : 2;
   yr--;
   scalar += __YEARS_TO_DAYS__(yr);
   return scalar;
}

/* obtiene nombres de día y meses, segíun ACTUAL_LANG_DATE */
char * Get_dayname(int nDay){
   static char *_DAY_NAMES_CL_[8] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado", "domingo"};
   static char *_DAY_NAMES_GR_[8] = {"sonntag", "montag", "dienstag", "mittwoch", "donnerstag", "freitag", "samstag", "sonntag"};
   static char *_DAY_NAMES_EN_[8] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"};
   static char *_DAY_NAMES_FR_[8] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi", "dimanche"};
   static char *_DAY_NAMES_IT_[8] = {"domenica", "lunedi", "martedi", "mercoledi", "giovedi", "venerdi", "sabato", "domenica"};
   char * retVal = NULL;
   switch(ACTUAL_LANG_DATE){
       case SP: { retVal = _DAY_NAMES_CL_[nDay] ; break; }
       case EN: { retVal = _DAY_NAMES_EN_[nDay] ; break; }
       case FR: { retVal = _DAY_NAMES_FR_[nDay] ; break; }
       case GR: { retVal = _DAY_NAMES_GR_[nDay] ; break; }
       case IT: { retVal = _DAY_NAMES_IT_[nDay] ; break; }
       default: { retVal = _DAY_NAMES_CL_[nDay] ; break; }
   }
   if(PILA_GADGET){
      push_stack_str(retVal); return NULL;
   }
   return retVal;
}

char * Get_monthname(int nMonth){
   static char *_S_MONTH_CL_[12] = {"enero", "febrero", "marzo", "abril", "mayo", "junio",
                   "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
   static char *_S_MONTH_EN_[12] = {"january","february","march","april","may","june","july","august","september",
                   "october","november","december"};
   static char *_S_MONTH_FR_[12] = {"janvier","février","mars","avril","mai","juin","juillet","août","septembre",
                   "octobre","novembre","décembre"};
   static char *_S_MONTH_IT_[12] = {"gennaio","febbraio","marzo","aprile","maggio","giugno","luglio","agosto","settembre",
                   "ottobre","novembre","dicembre"};
   static char *_S_MONTH_GR_[12] = {"januar","februar","märz","april","mai","juni","july","august","september",
                   "oktober","november","dezember"};
   char * retVal = NULL;
   switch(ACTUAL_LANG_DATE){
       case SP:{ retVal = _S_MONTH_CL_[nMonth] ; break; }
       case EN:{ retVal = _S_MONTH_EN_[nMonth] ; break; }
       case FR:{ retVal = _S_MONTH_FR_[nMonth] ; break; }
       case GR:{ retVal = _S_MONTH_GR_[nMonth] ; break; }
       case IT:{ retVal = _S_MONTH_IT_[nMonth] ; break; }
       default: { retVal = _S_MONTH_CL_[nMonth] ; break; }
   }
   if(PILA_GADGET){
      push_stack_str(retVal); return NULL;
   }
   return retVal;
}

/*
  nCode = codigo de funcion: 0=hoy; 1-99=+/- meses antes y despues del mes
*/
char ** GET_CALENDAR( DS_ARRAY * cal_data, int nCode, ... ){

   static int  _DAYS_[12]    = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  /* meses del año en diferentes idiomas, seteados con ACTUAL_LANG_DATE */
   static char *_SMONTH_CL_[12] = {"ENE", "FEB", "MAR", "ABR", "MAY", "JUN",
                   "JUL", "AGO", "SEP", "OCT", "NOV", "DIC"};
   static char *_SMONTH_EN_[12] = {"JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP",
                   "OCT","NOV","DEC"};
   static char *_SMONTH_FR_[12] = {"JAN","FéV","MAR","AVR","MAI","JUN","JUL","AOû","SEP",
                   "OCT","NOV","DéC"};
   static char *_SMONTH_IT_[12] = {"GEN","FEB","MAR","APR","MAG","GIU","LUG","AGO","SET",
                   "OTT","NOV","DIC"};
   static char *_SMONTH_GR_[12] = {"JAN","FEB","MäR","APR","MAI","JUN","JUL","AUG","SEP",
                   "OKT","NOV","DEZ"};
                   
   static char *_DAYNAMES_CL_[8] = {"Do", "Lu", "Ma", "Mi", "Ju", "Vi", "Sa", "Do"};
   static char *_DAYNAMES_GR_[8] = {"So", "Mo", "Di", "Mi", "Do", "Fr", "Sa", "So"};
   static char *_DAYNAMES_EN_[8] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
   static char *_DAYNAMES_FR_[8] = {"Di", "Lu", "Ma", "Me", "Je", "Ve", "Sa", "Di"};
   static char *_DAYNAMES_IT_[8] = {"Do", "Lu", "Ma", "Me", "Gi", "Ve", "Sa", "Do"};

   int day, day_1, numdays, i, j;
   int mo; int yr;

   if( nCode == 0 ){  // today! no pide nada a stack    calendar(TODAY)
      int iDay, iHour, iMinute, iSeconds, iMillisec;  // no usado.
      x_timeStampGetLocal( &yr, &mo, &iDay,
                            &iHour, &iMinute, &iSeconds, &iMillisec );
      
   }else if( nCode >0 && nCode <=99 ){   // +/- meses antes y después de fecha indicada en stack. calendar(BETWEEN+n)
         va_list va;
         va_start( va, nCode );
         mo = va_arg(va, int);
         yr = va_arg(va, int);
         va_end( va );
         for (i = nCode; i > 0; --i){  // ajusto el mes de inicio, aplicando time machine.
            --mo;
            if (!mo){
                  mo = 12;
                  --yr;
            }
         }
         nCode *= 2 ;  // duplica los meses, para incluir el segundo bloque después de la fecha indicada.
         if( fmod(nCode,2) == 0) ++nCode;
         va_end( va );

   }else if( nCode>=100 && nCode<200){   // añade meses a la fecha del stack.  calendar(ADDMONTH+n)
         nCode = (int)(nCode-100);   // ajuste para los meses a incluir después de la fecha.
         va_list va;
         va_start( va, nCode );
         mo = va_arg(va, int);
         yr = va_arg(va, int);
         va_end( va );
      
   }else{   // meses después de la fecha indicada en stack
      Msg_red("Calendar : el código no se ajusta a lo esperado\n");
      return NULL;
   }

   // Quiere solo despliegue (0 o nada) o array (1)?

      if (!mo || 12 < mo){
         Msg_red("Calendar : argumento \"Mes\" fuera de rango\n");
         return NULL;
      }

      if (100 > yr){
            yr += 1900;
      }
      if (3000 < yr || 1800 > yr){
         Msg_red("Calendar : rango de años esperado: 1800 < año < 3000\n");
         return NULL;
      }

      if(nCode==0) nCode=1;
      
      Dim( nCode * 8, 7 );
      as_fill_str_array( pRows,"   " );

      int nPos = 0; //1;
      int factor=1;
      int nCol;
      //_____________________

      for(i = 0; i < nCode; i++, mo++){

            if (12 < mo){
                  mo = 1;
                  ++yr;
            }
            numdays = _DAYS_[mo - 1];
            if (2 == mo && (Is_leap_year(yr))){
                  ++numdays;
            }
            day_1 = (int)((__YMD_TO_SCALAR__(yr, mo, 1) - (long)ISO_CAL) % 7L);
            
            switch(ACTUAL_LANG_DATE){
                case SP:{ Let( Cell(pRows, nPos, 0), _SMONTH_CL_[mo - 1] ); break; }
                case EN:{ Let( Cell(pRows, nPos, 0), _SMONTH_EN_[mo - 1] ); break; }
                case FR:{ Let( Cell(pRows, nPos, 0), _SMONTH_FR_[mo - 1] ); break; }
                case GR:{ Let( Cell(pRows, nPos, 0), _SMONTH_GR_[mo - 1] ); break; }
                case IT:{ Let( Cell(pRows, nPos, 0), _SMONTH_IT_[mo - 1] ); break; }
                default:{ Let( Cell(pRows, nPos, 0), _SMONTH_CL_[mo - 1] ); break; }
            }
            int h;
            for( h=1;h<6;h++){
                Let( Cell(pRows, nPos, h), "   " );
            }
            char *cAnio = (char *)calloc(11,1);
            sprintf(cAnio,"%4d",yr);
            Let( Cell(pRows, nPos, 6), cAnio );
            free(cAnio);
            ++nPos;
            
               nCol=0;
               for (j = 0; j < 7; ++j){
                   switch(ACTUAL_LANG_DATE){
                       case SP: {Let( Cell( pRows, nPos, nCol), _DAYNAMES_CL_[ISO_CAL + j] ); break; }
                       case EN: {Let( Cell( pRows, nPos, nCol), _DAYNAMES_EN_[ISO_CAL + j] ); break; }
                       case FR: {Let( Cell( pRows, nPos, nCol), _DAYNAMES_FR_[ISO_CAL + j] ); break; }
                       case GR: {Let( Cell( pRows, nPos, nCol), _DAYNAMES_GR_[ISO_CAL + j] ); break; }
                       case IT: {Let( Cell( pRows, nPos, nCol), _DAYNAMES_IT_[ISO_CAL + j] ); break; }
                       default: {Let( Cell( pRows, nPos, nCol), _DAYNAMES_CL_[ISO_CAL + j] ); break; }
                   }
                   ++nCol;
               }
               ++nPos;

               for( h=0;h<7;h++){  // rellena con esapcio, ue después será ocupado en parte
                   Let( Cell(pRows, nPos, h), "   " );
               }

               nCol=0;
               
               int nday=1;
               for (day = 0; /*day < 7*/; ++day){
                  if(day < day_1){
                      Let( Cell(pRows, nPos, nCol), "   " );
                      ++nCol;

                  }else{
                     char *cDia = (char *)calloc(11,1);
                     sprintf(cDia,"%3d",nday);
                     Let( Cell(pRows, nPos, nCol), cDia );
                     ++nCol;

                     free(cDia);
                     nday++;
                     ++day_1; day_1 %= 7;
                     if(!day_1 && 1 != day) break;
                  }
               }
               ++nPos;

               int iniDay = nday;

               ++day_1;

              //________________________
               while (day <= numdays){
                  int h;
                  for( h=0;h<7;h++){  // rellena con esapcio, ue después será ocupado en parte
                      Let( Cell(pRows, nPos, h), "   " );
                  }

                  int nCol=0;

                  for (day = iniDay; day <= numdays; ++day, ++day_1, day_1 %= 7){
                     if (!day_1 && 1 != day){
                        char *cTerminal = (char *)calloc(11,1);

                        sprintf(cTerminal,"%3d",day);
                        Let( Cell( pRows, nPos, nCol), cTerminal); 
                        ++nCol;

                        free(cTerminal);
                        ++day;
                        iniDay=day;
                        
                        ++day_1;
                        day_1 %= 7;
                        break;
                     }
                     char *cDiaI = (char *)calloc(11,1);
                     sprintf(cDiaI,"%3d",day);
                     Let( Cell( pRows, nPos, nCol), cDiaI ); 
                     ++nCol;

                     free(cDiaI);
                  }
                  ++nPos;
               }
               
               nPos = nPos + ((8*factor++)-nPos);

      }

    cal_data->rows = pRows_data.rows;
    cal_data->cols = pRows_data.cols;
    cal_data->pags = pRows_data.pags;
    cal_data->dims = pRows_data.dims;
    cal_data->len  = pRows_data.len;
    cal_data->type = 10;

   return pRows;
}

void _imprime_item_calendario_( RDS(char*, calendario), int x, int y, int actual_day ){

   int i,j;

   Str_init(day_sel);
   
   All_range_for(calendario);
   Goto_xy( x,y );

   Iterup ( row,calendario,i){
      Iterup ( col,calendario,j){ //
          if ( Str2int( Cell(calendario,i,j) ) == actual_day ){
              Get_fn_let( day_sel, Trim( Cell(calendario,i,j)));
              printf( "  " ); Inverse; 
              if( actual_day>=10) printf( "%s", day_sel); 
              else printf( " %s", day_sel); 
              Inverse_off;
          }else{
              if( j==0 || j==6) Bold;
              printf ("%*s",4, Cell(calendario,i,j));
              if( j==0 || j==6) Bold_off;
          }
      } Goto_x( ++x );
   }
   Free_secure (day_sel);
}

void _show_item_calendar_dalien_( RDS(char *,cal), int nColorF, int nColorB, int actual_day ){
   
   int oldx = SCREEN_ROW, oldy = SCREEN_COL;
   //Color_fore(67); Color_back(17);
   Color_fore(nColorF); Color_back(nColorB); 
   Goto_xy( oldx, oldy); //5,24;  
   Box( 10,30, SING_ALL);
   //imprime_calendario( SDS( cal ), 6, 25, actual_day );
   //SCREEN_ROW = oldx; SCREEN_COL = oldy;
   _imprime_item_calendario_( SDS( cal ), oldx+1, oldy+1, actual_day );
   SCREEN_ROW = oldx; SCREEN_COL = oldy;
   Reset_color;

}

long Select_date_from_calendar(char * date, int nColorF, int nColorB,int last_day_next_month){
   //New array cal as string;
   New_str_array(cal);
   Set_date_lang(EN);

   //char * date = Get_date();
   int actual_day = Get_day( date );
   int actual_month = Get_month( date );
   int actual_year = Get_year( date );
   int days_in_month = Days_in_month( actual_month, Is_leap_year(actual_year) );

   cal = Calendar(cal, 100, actual_month, actual_year); // calendario de la fecha actual

   //Disable_raw_mode(); /* para que se detenga en getch() */
   char oldSep = Get_token_sep(' ');
  // char newDate[11];

   _show_item_calendar_dalien_( SDS(cal), nColorF, nColorB, actual_day );           
           
   Flush_inp;
   
   int tecla=0, swModDate=0;
   while( tecla != ENTER && tecla != ESCAPE)
   {
       tecla = Getch();
       if(tecla == ARROW_LEFT ) {
           actual_day--;
           if ( !actual_day ){
               if (last_day_next_month ){
                   actual_month--;
                   if( actual_month < 1 ){
                       actual_year--; actual_month=12;
                   }
                   swModDate=2;  // debe cambiar a ultimo día del mes
                   goto new_calendar;
               }else{
                   actual_day = days_in_month;
               }
           }
           _show_item_calendar_dalien_( SDS(cal), nColorF, nColorB,actual_day );
       }
       else if(tecla == ARROW_RIGHT ) {
           actual_day++;
           if(actual_day>days_in_month) {
               if ( last_day_next_month ){
                   actual_month++;
                   if( actual_month > 12 ){
                       actual_year++; actual_month=1;
                   }
                   actual_day=1;
                   swModDate=1;
                   goto new_calendar;
               }else{
                   actual_day=1;
               }
           }
           _show_item_calendar_dalien_( SDS(cal), nColorF, nColorB,actual_day );
       }
       else if(tecla == ARROW_UP ) {
           actual_day-=7;
           if( actual_day<=0 ) actual_day+=7;
           _show_item_calendar_dalien_( SDS(cal), nColorF, nColorB,actual_day );
       }
       else if(tecla == ARROW_DOWN ) {
           actual_day+=7;
           if( actual_day>days_in_month ) actual_day-=7;
           _show_item_calendar_dalien_( SDS(cal), nColorF, nColorB,actual_day );
       }
     /* salta meses */
       else if(tecla == CTRL_ARROW_LEFT ) {
           actual_month--;
           if( actual_month < 1 ){
               actual_year--; actual_month=12;
           }
           swModDate=1;
       }
       else if(tecla == CTRL_ARROW_RIGHT ) {
           actual_month++;
           if( actual_month > 12 ){
               actual_year++; actual_month=1;
           }
           swModDate=1;
       }
     /* salta años */
       else if(tecla == SHIFT_ARROW_RIGHT ) {
           actual_year++;
           if(actual_year>2999) actual_year=2999;
           swModDate=1;
       }
       else if(tecla == SHIFT_ARROW_LEFT ) {
           actual_year--;
           if(actual_year<1800) actual_year=1800;
           swModDate=1;
       }
     /* salta décadas */
       else if(tecla == ALT_ARROW_RIGHT ) {
           actual_year+=10;
           if(actual_year>2999) actual_year=2999;
           swModDate=1;
       }
       else if(tecla == ALT_ARROW_LEFT ) {
           actual_year-=10;
           if(actual_year<1800) actual_year=1800;
           swModDate=1;
       }

    new_calendar:   
     /* prepara nuevo calendario */  
       if( swModDate ){
           sFree_array (cal);
           days_in_month=Days_in_month( actual_month, Is_leap_year(actual_year) );
           if ( swModDate == 1 ){
               if( actual_day>days_in_month) actual_day=days_in_month;
           }else{
               actual_day = days_in_month;
           }
           cal = Calendar(cal, 100, actual_month, actual_year);

           _show_item_calendar_dalien_( SDS(cal), nColorF, nColorB,actual_day );
           swModDate=0;
       }
       Flush_inp;
   }
   long julian_date=0;
   if (tecla == ENTER ){
       julian_date = Get_julian_date(actual_year, actual_month, actual_day);
   }
   //getchar();
   Set_token_sep(oldSep);
   // Enable_raw_mode(); /* para que siga el mouse */
   Flush_inp;

   sFree_array( cal);
 ///  Free_secure (date);
   return julian_date;
}

