/************************************************************************
 *
 *   LIBRERIA DE MANIPULACION DE NUMEROS
 *
 ************************************************************************/


/*#ifndef _LIB_GADGET_MAIN_

#ifdef GENLIB_GADGET*/
#include "../include/gadget.h"
/*#else
#include <gadget/gadget.h>
#endif


#endif

#include <gadget/gadget_numeric.h> */

/* acceso al stack str */
extern int PILA_GADGET;
extern int CONTADOR_PILA;
extern char ** pila_de_trabajo;


/* PRECISION GLOBAL */
extern int DEC_PREC;
extern int SIZE_INT;

// tamaño del binario a convertir con BIN
extern int SIZE_BINARY;

/* STRING - NUMBERS */
/* NUMEROS A STRING Y VICEVERSA */

/* STRTONUM */
double __numPow10__( int nPrecision )
{
   static const double s_dPow10[ 17 ] = {                1.0,   /*  0 */
                                                        10.0,   /*  1 */
                                                       100.0,   /*  2 */
                                                      1000.0,   /*  3 */
                                                     10000.0,   /*  4 */
                                                    100000.0,   /*  5 */
                                                   1000000.0,   /*  6 */
                                                  10000000.0,   /*  7 */
                                                 100000000.0,   /*  8 */
                                                1000000000.0,   /*  9 */
                                               10000000000.0,   /* 10 */
                                              100000000000.0,   /* 11 */
                                             1000000000000.0,   /* 12 */
                                            10000000000000.0,   /* 13 */
                                           100000000000000.0,   /* 14 */
                                          1000000000000000.0,   /* 15 */
                                         10000000000000000.0 }; /* 16 */
   if( nPrecision < 17 )
   {
      if( nPrecision >= 0 )
         return s_dPow10[ nPrecision ];
      else if( nPrecision > -17 )
         return 1.0 / s_dPow10[ ( unsigned int ) -nPrecision ];
   }

   return pow( 10.0, ( double ) nPrecision );
}

static const double gadget_factor_Precision[17] = {1,10,100,1000,10000,100000,1e+06,1e+07,1e+08,1e+09,1e+10,
                             1e+11,1e+12,1e+13,1e+14,1e+15,1e+16};

double Dbl_prec(double dNum, int Dec){
  return round(dNum * gadget_factor_Precision[Dec])/gadget_factor_Precision[Dec];
}

float Flt_prec(float dNum, int Dec){
  return round(dNum * gadget_factor_Precision[Dec])/gadget_factor_Precision[Dec];
}

int __str2number__( int fPCode, const char * szNum, long nLen, long * lVal, double * dVal, int * piDec, int * piWidth )
{
   int fDbl = X_FALSE, fDec = X_FALSE, fNeg, fHex = X_FALSE;
   int iLen, iPos = 0;
   int c, iWidth, iDec = 0, iDecR = 0;

   iLen = ( int ) nLen;

   while( iPos < iLen && X_ISSPACE( szNum[ iPos ] ) )
      iPos++;

   if( iPos >= iLen )
   {
      fNeg = X_FALSE;
   }
   else if( szNum[ iPos ] == '-' )
   {
      fNeg = X_TRUE;
      iPos++;
   }
   else
   {
      fNeg = X_FALSE;
      if( szNum[ iPos ] == '+' )
         iPos++;
   }

   *dVal = 0;
   *lVal = 0;

   /* Hex Number */
   if( fPCode && iPos + 1 < iLen && szNum[ iPos ] == '0' &&
       ( szNum[ iPos + 1 ] == 'X' || szNum[ iPos + 1 ] == 'x' ) )
   {
      iPos += 2;
      iWidth = X_DEFAULT_WIDTH;
      fHex = X_TRUE;
      for( ; iPos < iLen; iPos++ )
      {
         c = szNum[ iPos ];
         if( c >= '0' && c <= '9' )
            c -= '0';
         else if( c >= 'A' && c <= 'F' )
            c -= 'A' - 10;
         else if( c >= 'a' && c <= 'f' )
            c -= 'a' - 10;
         else
            break;
         *lVal = ( *lVal << 4 ) + c;
      }
   }
   else
   {
      long lLimV;
      int iLimC;

      lLimV = LONG_MAX / 10;
      iLimC = ( int ) ( LONG_MAX % 10 );

      iWidth = iPos;

      for( ; iPos < iLen; iPos++ )
      {
         c = szNum[ iPos ];
         if( c >= '0' && c <= '9' )
         {
            if( fDbl )
            {
               *dVal = *dVal * 10.0 + ( c - '0' );
            }
            else if( *lVal < lLimV || ( *lVal <= lLimV && ( ( int ) ( c - '0' ) ) <= iLimC ) )
            {
               *lVal = *lVal * 10 + ( c - '0' );
            }
            else
            {
               *dVal = ( double ) *lVal * 10.0 + ( c - '0' );
               fDbl = X_TRUE;
            }
            if( fDec )
               iDec++;
            else
               iWidth++;
         }
         else if( c == '.' && !fDec )
         {
            fDec = X_TRUE;
         }
         else
         {
            while( !fDec && iPos < iLen )
            {
               if( szNum[ iPos++ ] == '.' )
                  fDec = X_TRUE;
               else
                  iWidth++;
            }
            if( fDec )
               iDecR = iLen - iPos;
            break;
         }
      }
   }

   if( fNeg )
   {
      if( fDbl )
         *dVal = -*dVal;
      else
         *lVal = -*lVal;
   }
   if( !fDbl && (
/*#if defined( PCODE_LONG_LIM )
        ( fPCode && !fHex && !PCODE_LONG_LIM( *lVal ) ) ||
#endif*/
        fDec ) )
   {
      *dVal = ( double ) *lVal;
      fDbl = X_TRUE;
   }
   if( iDec )
   {
#if defined( __XCC__ ) || defined( __POCC__ )
      if( iDec < 16 )
         *dVal /= ( LONGLONG ) __numPow10__( iDec );
      else
#endif
         *dVal /= __numPow10__( iDec );
   }

   if( piDec )
      *piDec = iDec + iDecR;
   if( piWidth )
   {
      if( fHex )
         *piWidth = iWidth;
      else
      {
         if( fPCode )
         {
            if( iWidth < 10 || fNeg )
               *piWidth = fDbl ? X_DBL_LENGTH( *dVal ) : X_LONG_LENGTH( *lVal );
            else
               *piWidth = iWidth + ( iDec == 0 ? 1 : 0 );
         }
         else if( iWidth > 10 )
         {
            *piWidth = fDbl ? X_DBL_LENGTH( *dVal ) : X_LONG_LENGTH( *lVal );
         }
         else
         {
            if( iDec + iDecR == 0 )
               *piWidth = iLen;
            else if( iWidth == 0 )
               *piWidth = 1;
            else if( fNeg && iWidth == 1 && *dVal != 0 )
               *piWidth = 2;
            else
               *piWidth = iWidth;
         }
      }
   }

   return fDbl;
}

double Str2dbl( const char* szNumBuff ){
   long lVal;
   double dVal;  
   
   char * szNum = pop_stack_if_null_noLen(szNumBuff, "Str2dbl","str-number");
   if (szNum==NULL) { return 0.0;}

   if( ! __str2number__( X_FALSE, szNum, strlen( szNum ), &lVal, &dVal, NULL, NULL ) ){
      free(szNum);
      return (double) lVal;
   }else{
      free(szNum);
      return dVal;
   }
}
float Str2flt( const char* szNumBuff ){
   long lVal;
   double fVal;  

   char * szNum = pop_stack_if_null_noLen(szNumBuff, "Str2flt","str-number");
   if (szNum==NULL) { return 0.0;}

   if( ! __str2number__( X_FALSE, szNum, strlen( szNum ), &lVal, &fVal, NULL, NULL ) ){
      free(szNum);
      return (float) lVal;
   }else{
      free(szNum);
      return (float)fVal;
   }
}

long Str2lng( const char* szNumBuff ){
   long lVal;
   double dVal;

   char * szNum = pop_stack_if_null_noLen(szNumBuff, "Str2lng","str-number");
   if (szNum==NULL) { return 0L;}

   if( __str2number__( X_FALSE, szNum, strlen( szNum ), &lVal, &dVal, NULL, NULL ) )
   {
      free(szNum);
      return (long)dVal;
   }
   free(szNum);
   return lVal;
}


int Str2int( const char* szNumBuff ){
   long iVal;
   double dVal;

   char * szNum = pop_stack_if_null_noLen(szNumBuff, "Str2int","str-number");
   if (szNum==NULL) { return 0;}

   if( __str2number__( X_FALSE, szNum, strlen( szNum ), &iVal, &dVal, NULL, NULL ) )
   {
      free(szNum);
      return (int)dVal;
   }
   free(szNum);
   return (int) iVal;
}


/* OTRAS CONVERSIONES RELACIONADAS CON NUMEROS Y STRINGS */

/* Chequea si string en numero, y si es notacion cientifica */
int Is_number(const char * AXBuff){
  
  char * sAX = pop_stack_if_null_noLen(AXBuff, "Is_number","str-number");
   if (sAX==NULL) { return 0;}
   
  int DX;
  short int SW_M=0,SW_N=0,SW_P=0;
  short int retorne;
  const char* AX = sAX;
  
  retorne = AX[0]!='\0' ? 1 : 0;
  
  while( (DX=*AX)!='\0'){
    if(DX=='-'){
       if (SW_N || SW_P || SW_M) {retorne=0;break;}
       SW_M=1;
    }else if (DX=='.'){
       if( SW_P) {retorne=0;break;}
       ///if (!SW_N || SW_P) {retorne=0;break;}
       SW_P=1;
    }else if (isdigit(DX)) {SW_N=1;
    }else {retorne=0;break;}
    ++AX;
  }
  if (retorne==0) { SW_P = SW_N = SW_M = 0;}
  retorne=retorne<<1;
  retorne|=SW_P;     // 1=es decimal; 0=entero
  free(sAX);
  return (retorne);
}

/*long long StrE2llng( const char * lineaBuff ){
   
   char * linea = pop_stack_if_null_noLen(lineaBuff, "StrE2lng","str-number");
   if (linea==NULL) { return 0;}
   
   const char *buf;
   char *sMant;
   long long nMant;
   int nExp,mant=0,signo;
   buf=linea;

   while(*buf!='E' && *buf!='e') {
      mant++;
      ++buf;
   }
   nExp = atoi(++buf);
   sMant = (char *)calloc(mant+10,1);
   strncpy(sMant,linea,mant);
   sMant[mant]='\0';

   if (sMant[0]=='-') {
      signo=(-1); 
      //sMant++;
      sMant[0]='0';
   } else signo=1;

   nMant = atoll(sMant);
   free ( sMant );
//   printf("\n--> %f, %d, %d\n%f\n",nMant,nExp,signo, nMant * pow( (double)10, (double)nExp)*signo);
   //return ((double) nMant * (double)pow( (double)10, (double)nExp)*(double)signo );
   free(linea);
   return (nMant * (long double)powl( 10.0, (long double)nExp)*signo );
}

long StrE2lng( const char * lineaBuff ){
   
   char * linea = pop_stack_if_null_noLen(lineaBuff, "StrE2lng","str-number");
   if (linea==NULL) { return 0;}
   
   const char *buf;
   char *sMant;
   long nMant;
   int nExp,mant=0,signo;
   buf=linea;

   while(*buf!='E' && *buf!='e') {
      mant++;
      ++buf;
   }
   nExp = atoi(++buf);
   sMant = (char *)calloc(mant+10,1);
   strncpy(sMant,linea,mant);
   sMant[mant]='\0';

   if (sMant[0]=='-') {
      signo=(-1); 
      //sMant++;
      sMant[0]='0';
   } else signo=1;

   nMant = atol(sMant);
   free ( sMant );
//   printf("\n--> %f, %d, %d\n%f\n",nMant,nExp,signo, nMant * pow( (double)10, (double)nExp)*signo);
   //return ((double) nMant * (double)pow( (double)10, (double)nExp)*(double)signo );
   free(linea);
   return (nMant * (long)pow( 10.0, (long)nExp)*signo );
}
*/
double StrE2dbl( const char * lineaBuff ){
   
   char * linea = pop_stack_if_null_noLen(lineaBuff, "StrE2dbl","str-number");
   if (linea==NULL) { return 0.0;}

   const char *buf;
   char *sMant;
   double nMant;
   int nExp,mant=0,signo;
   buf=linea;

   while(*buf!='E' && *buf!='e') {
      mant++;
      ++buf;
   }
   nExp = atoi(++buf);
   sMant = (char *)calloc(mant+10,1);
   strncpy(sMant,linea,mant);
   sMant[mant]='\0';

   if (sMant[0]=='-') {
      signo=(-1); 
      //sMant++;
      sMant[0]='0';
   } else signo=1;

   nMant = atof(sMant);
   free ( sMant );
//   printf("\n--> %f, %d, %d\n%f\n",nMant,nExp,signo, nMant * pow( (double)10, (double)nExp)*signo);
   //return ((double) nMant * (double)pow( (double)10, (double)nExp)*(double)signo );
   free(linea);
   return (nMant * pow( 10.0, (double)nExp)*signo );
}

long double StrE2ldbl( const char * lineaBuff ){
   
   char * linea = pop_stack_if_null_noLen(lineaBuff, "StrE2ldbl","str-number");
   if (linea==NULL) { return 0.0;}

   const char *buf;
   char *sMant;
   long double nMant;
   int nExp,mant=0,signo;
   buf=linea;

   while(*buf!='E' && *buf!='e') {
      mant++;
      ++buf;
   }
   nExp = atoi(++buf);
   sMant = (char *)calloc(mant+10,1);
   strncpy(sMant,linea,mant);
   sMant[mant]='\0';

   if (sMant[0]=='-') {
      signo=(-1); 
      //sMant++;
      sMant[0]='0';
   } else signo=1;

   nMant = atof(sMant);
   free ( sMant );
//   printf("\n--> %f, %d, %d\n%f\n",nMant,nExp,signo, nMant * pow( (double)10, (double)nExp)*signo);
   //return ((double) nMant * (double)pow( (double)10, (double)nExp)*(double)signo );
   free(linea);
   return (nMant * powl( 10.0, (long double)nExp)*signo );
}


int Is_notation(const char * AXBuff){
  
  char * AX = pop_stack_if_null_noLen(AXBuff, "Is_notation","str-number");
  if (AX==NULL) { return 0;}

  int retorne=1;
  int swE=0;
  int swP=0;
  int swS=0;
  int swD=0;
  
  const char *t=AX;
  if( *t=='.' ) { swP=1; ++t; }
  if(isdigit(*t) || *t=='-' || *t=='+'){
     ++t;
     while(*t!='\0'){
        if(isdigit(*t)) {
           ++t;
        }else if(*t=='.'){
           if(swP){
              //printf("hay mas de un punto = %c\n",*t);
              retorne=0; break;
           } else {
              swP=1;
           }
           ++t;
        }else if(isalpha(*t)){
           if(*t!='e' && *t!='E'){ 
               //printf("debo encontrar un E aqui = %c\n",*t);
               retorne=0;
               break;
           }else{
               if(swE) {
                  //printf("se repite E = %c\n",*t);
                  retorne=0; break;
               } else { 
                  swE=1; 
               }
               ++t;
               if(*t!='\0'){
                   if(!isdigit(*t) && (*t!='-' && *t!='+')) {
                      //printf("despues de E debe ser un digito o + o - = %c\n",*t);
                      retorne=0;
                      break;
                   }else if(*t=='-' || *t=='+'){
                      if(swS){ 
                         //printf("encontre mas de un signo luego de E = %c\n",*t);
                         retorne=0;break;
                      } else {
                         swS=1;
                         ++t;
                         if(isdigit(*t)){
                            //printf("Activa swD\n");
                            swD=1;
                         }else{
                            //printf("no encontre un digito luego de E+- = %c\n",*t);
                            retorne=0;break;
                         }
                      }
                   }else if(isdigit(*t)){
                      //printf("Activa swD\n");
                      swD=1;
                   }else{
                      //printf("Algo raro detecta = %c\n",*t);
                      retorne=0;break;
                   }
                   ++t;
               }else{
                   //printf("encontre fin de cadena antes de completar E\n");
                   retorne=0;break;
               }
           }
        }else{
           //printf("encontre algo distinto a digito, E y . = %c\n",*t);
           retorne=0;
           break;
        }
     }
  }else{
     //printf("no encontre signo ni digito al empezar = %c\n",*t);
     retorne=0;
  }
  if( retorne && !swD){
//     if(!swE)
     //printf("retorne = 1 pero !swD\n");
     retorne=0;
  }
  free(AX);
  return retorne;
}

/* NUM2STR */

char * Int2str( int dNum ){
   char * buffer = (char *)calloc(120,1);
   int n=0;
/*   if (DEC_PREC)
      n=sprintf(buffer,"%.*d",DEC_PREC, dNum);
   else*/
   n=sprintf(buffer,"%d",dNum);
   buffer[n]='\0';
   
   Item_return_release(buffer);
   
   ///return buffer;
}

char * Lng2str( long dNum ){
   char * buffer = (char *)calloc(120,1);
   int n=0;
/*   if (DEC_PREC)
      n=sprintf(buffer,"%.*ld",DEC_PREC, dNum);
   else*/
   n=sprintf(buffer,"%ld",dNum);
   buffer[n]='\0';
   
   Item_return_release(buffer);
   //return buffer;
}

char * Flt2str( float dNum ){
   char * buffer = (char *)calloc(120,1);
   int n=0;
   if (DEC_PREC)
      n=sprintf(buffer,"%.*f",DEC_PREC, dNum);
   else
      n=sprintf(buffer,"%f",dNum);
   buffer[n]='\0';
   
   Item_return_release(buffer);
   //return buffer;
}

char * Dbl2str( double dNum ){
   char * buffer = (char *)calloc(120,1);
   int n=0;
   if (DEC_PREC)
      n=sprintf(buffer,"%.*lf",DEC_PREC, dNum);
   else
      n=sprintf(buffer,"%lf",dNum);
   buffer[n]='\0';
   
   Item_return_release(buffer);
   //return buffer;
}

char * Num2notation( double dNum ){
   char * buffer = (char *)calloc(120,1);
   int n=0;
   n=sprintf(buffer,"%e",dNum);
   buffer[n]='\0';
   
   Item_return_release(buffer);
   //return buffer;
}

/* MATEMATICA */

long double Fact( int param){
  long double f=1;
  int i;
  static double tablaf[21]={1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,6227020800,
                            87178291200,1307674368000,20922789888000,355687428096000,6402373705728000,
                            121645100408832000,2432902008176640000};
  int x = param;

    if (x<=20){
       f=tablaf[x];
    }else{
       f=tablaf[20];
       i=21;
       do{
         f=f*i;
       }while(++i<=x);
    }
  return f;
}

long Bin2lng( const char * binBuff ){

    char * binf = pop_stack_if_null_noLen(binBuff, "Bin2lng","str-number");
    if (binf==NULL) { return 0L;}
  
    const char * bin = binf;
    
    while(*bin!='1')
       bin++;

    long nLen = strlen(bin);

    long decimal=0;
    int i = 0;

    nLen--;

    while(nLen>=0) {
        ///printf("=> [%d],",bin[nLen]);fflush(stdout);
        
        if(bin[nLen] == '0' || bin[nLen] == '1')
           decimal += pow(2, i) * ( bin[nLen] - 48 );
        else{
            decimal=0;
            Msg_red("Bin2lng : hay dígitos que no son ni '0' ni '1'\n");
            break;
        }
        nLen--; i++;
    }
    free(binf);
    return decimal;

}
long Hex2lng( const char * hexBuff ){

   long nLen = 0;//strlen(hex);
   char * hex = pop_stack_if_null(hexBuff, &nLen, "Hex2lng","str-number");
    if (hex==NULL) { return 0L;}

   long decimal;
    int i = 0, val;

    decimal = 0;
    nLen--;

    for(i=0; hex[i]!='\0'; i++)
    {
        /* Find the decimal representation of hex[i] */
        if(hex[i]>='0' && hex[i]<='9')
        {
            val = hex[i] - 48;
        }
        else if(hex[i]>='a' && hex[i]<='f')
        {
            val = hex[i] - 97 + 10;
        }
        else if(hex[i]>='A' && hex[i]<='F')
        {
            val = hex[i] - 65 + 10;
        }
        else
        {
            decimal=0;
            Msg_red("Hex2lng : hay dígitos que no son hexadecimales\n");
            break;
        }

        decimal += val * pow(16, nLen);
        nLen--;
    }
    free(hex);
   return decimal;
}


long Oct2lng( const char * octBuff ){

   char * oct = pop_stack_if_null_noLen(octBuff, "Oct2lng","str-number");
    if (oct==NULL) { return 0L;}

   long octal = Str2lng( oct );
/*   if( octal==NULL){
       octal = pop_stack_hard("Oct2lng","Str2lng");
   }*/

   long decimal=0;
   int i=0;
   while (octal != 0){
        decimal =  decimal +(octal % 10)* pow(8, i++);
        octal = octal / 10;
   }
   free(oct);
   return decimal;
}

char * Lng2hex( unsigned long pLong ){
    char * buf = (char *)calloc(64,1);
    sprintf(buf,"%lX", pLong);
    
    Item_return_release(buf);
    //return buf;
}

char * Lng2bin( unsigned long nNum ){
    long k, c;
    int size=63;
    if(SIZE_BINARY>0) size = SIZE_BINARY;
    char * buffer = (char *)calloc(size+2,1);
    for (c = size; c >= 0; c--){
        k = nNum >> c;
        if (k & 1)
            buffer[size-c] = '1';
        else
            buffer[size-c] = '0';
    }
    buffer[size+1] = '\0';
    const char * pString = buffer;
    if(!SIZE_BINARY){  // quita los ceros de más
        while(*pString != '\0' && *pString!='1')
           pString++;
        if( ! *pString ) pString--;
    }
    char * retVal = Space( strlen(pString) + 1 );
    strcpy(retVal, pString);
    free(buffer);
    
    Item_return_release(retVal);
    //return retVal;
}

char * Lng2oct( unsigned long decimal ){

    long octal=0;
    int i=1;
    while (decimal != 0){
       octal += (decimal % 8) * i;
       decimal /= 8;
       i *= 10;
    }
    char * sOctal = Lng2str( octal );
    if( sOctal == NULL){
       sOctal = pop_stack_hard("Lng2oct","Lng2str");
    }
    
    Item_return_release(sOctal);
    //return sOctal;
}



