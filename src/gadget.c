
//#ifdef GENLIB_GADGET
#include "../include/gadget.h"
/*#else
#include <gadget/gadget.h>
#endif */

/* establece token para uso global */
extern char * __TOKEN__;

/* MONEY */
extern int DECIMAL_POINT;
extern int SEPARATOR_MILLARS;

/* CONTROL-POSICION EN PANTALLA */
extern int SCREEN_ROW, SCREEN_COL;

/* REGEX */
extern int SIZE_MATCH; // se satura cuando hay búsquedas exitosas con regex_match
extern int __aIndexREGEX__;
extern regex_t __aREGEX__[20];
extern int __validREGEX__[20];

/* INDEX_AT y COUNT_AT */
extern int MULTIPASS;

/* SEARCH */
extern long SIZE_SEARCH;

/* STATFILE Y READLINE */
extern int MAX_LENGTH_READ;

/* ACCESO A STACK DE STRING QUE PERMITE ANIDAMIENTO */
extern int PILA_GADGET;
extern int CONTADOR_PILA;
extern char ** pila_de_trabajo;

extern int Is_ok;

/************************************************************************
 *
 *                     LIBRERIA DE FUNCIONES DE STRING
 *
 ************************************************************************/

/* TOKENS */

/* IMPORTANTE! declarar antes del trabajo con TOKENS */
/* establece separador inicial de token por defecto: coma */
void Init_token(){
   if( __TOKEN__ ) free(__TOKEN__);
   __TOKEN__ = (char*)calloc(2,1);
   __TOKEN__[0]=',';
   __TOKEN__[1]='\0';
}

/* IMPORTANTE! declarar después del trabajo con TOKENS */
/* libera __TOKEN__ de memoria */
void End_token(){
   if(__TOKEN__) free(__TOKEN__);
   __TOKEN__=NULL;
}

/* establece un nuevo separador de token */
void Set_token_sep(char nuevoToken){
   __TOKEN__[0]=nuevoToken;
}

/* establece nuevo separador y devuelve el anterior */
char Set_new_sep(char nuevoToken){
   char oldToken = __TOKEN__[0];
   __TOKEN__[0]=nuevoToken;
   return oldToken;
}

/* obtiene el separador de token activo */
char Get_token_sep(){
   return (__TOKEN__ ? __TOKEN__[0] : '\0');
}

/* obtiene el total de tokens en un string clásico */
int Count_tokens( char * cTXTBuff ){

      const char* tokenizer=NULL;

      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else { Msg_red("Count_tokens: no se ha inicializado «InitTokens»\n"); return -1; }
      
      long nLen = 0; //strlen(cTXT);
      char * cTXT=pop_stack_if_null(cTXTBuff, &nLen, "Count_tokens","target");
      if ( cTXT == NULL ) return -1;
      
      char *cTexto = (char *)calloc( nLen + 1, 1 );
      memcpy( cTexto, cTXT, nLen );
      char* token; 

      int nTok=0;
      token = strtok(cTexto, tokenizer);
      if( !token ){
         Msg_red("Count_tokens: error interno (strtok) - fin prematuro de busqueda\n");
         nTok=-1;
      }else{
         while( token ){
            token = strtok(0, tokenizer);
            ++nTok;
         }  
      }
      free(cTexto);
      free(cTXT);
return nTok;
}

/* obtiene el token indicado */
char * Get_token( char * cTXTBuff, int nToken ){
   
      const char* tokenizer=NULL;

      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else { Msg_red("Get_token: no se ha inicializado «InitTokens»\n"); return NULL; }
      
      long nLen = 0;//strlen(cTXT);
      char * cTXT=pop_stack_if_null(cTXTBuff, &nLen, "Get_token","target");
      if ( cTXT == NULL ) return NULL;

      
      char *cTexto = (char *)calloc( nLen + 1, 1 );
      memcpy( cTexto, cTXT, nLen );
      char* token=NULL; 

      int nTok=1;
      token = strtok(cTexto, tokenizer);
      char * ret = NULL;
      if( !token ){
         Msg_yellow("Get_token: error interno (strtok) - fin prematuro de busqueda\n");
      }else{
         if( nToken > 1 ){
            while( token ){
               token = strtok(0, tokenizer);
               ++nTok;
               if( nTok==nToken) break;
            }
         }
      }
      ret = (char *)calloc( strlen(token) + 1, 1 );
      strcpy(ret,token);
      free(cTexto);
      free(cTXT);
      if(PILA_GADGET){
          push_stack_str(ret);
          free(ret);
          return NULL;
      }
return ( ret );
}

/* modifica un token */
char * Mod_token( char * cTXTBuff, const char * cTOKBuff, int nToken ){   
   
   long nLen = 0;//strlen(cTXT);
   char * cTXT=pop_stack_if_null(cTXTBuff, &nLen, "Mod_token","token");
   if ( cTXT == NULL ) return NULL;
      
   if( nLen ){
      long rLen = 0;//strlen(cTOK);
      char * cTOK=pop_stack_if_null(cTOKBuff, &rLen, "Get_token","target");
      if ( cTOK == NULL ) {free(cTXT);return NULL;}
      
      const char* tokenizer=NULL;

      if( __TOKEN__ ) tokenizer = __TOKEN__;
      else { Msg_red("Mod_token: no se ha inicializado «Init_tokens»\n"); return cTXT; }
      
      char * ret=NULL;
      
      char *cTexto = (char *)calloc( nLen + 100, 1 );
      char *cFinal = (char *)calloc( nLen + rLen + 100, 1 );
      memcpy( cTexto, cTXT, nLen );
      char* token=NULL; 

      int nTok=1;
      token = strtok(cTexto, tokenizer);
      if( !token ){
         Msg_yellow("Mod_token: error interno (strtok) - fin prematuro de busqueda\n");
      }else{
         while( token ){
            if( nTok == nToken ){ // guardo el reemplazo
               if( nTok>1 ){
                  strncat(cFinal, tokenizer,1 );
               }
               if( cTOK!=NULL ) {
                  strcat(cFinal, cTOK );
               }
            }else{  // guardo el token leido
               if(nTok>1) {
                  strncat(cFinal, tokenizer,1 );
               }
               strcat(cFinal, token );
            }  
            token = strtok(0, tokenizer);
            ++nTok;
         }
      }
      if( *cFinal ){
         int nLen = strlen(cFinal)-1;
         if(cFinal[ nLen ]==*tokenizer){
            cFinal[ nLen ]='\0';
         }
         const char * pFinal = cFinal;
         if(*pFinal==*tokenizer){
            ++pFinal;
         }

         ret = (char *)calloc( strlen(pFinal) + 1, 1 );
         strcpy(ret, pFinal);
         
      } /* no hace nada */
      free(cTexto);
      free(cFinal);
      free(cTXT); free(cTOK);
      if(PILA_GADGET){
         push_stack_str(ret); free(ret);return NULL;
      }
      return ( ret );
      
   } else { // no hace nada?
      if(PILA_GADGET){
         push_stack_str(cTXT); free(cTXT);return NULL;
      }
      return ( cTXT );
   }
}

/* swap de tokens */
char * Swap_tokens(char * cTXTBuff, int nToken1, int nToken2){
   
   char * cTXT=pop_stack_if_null_noLen(cTXTBuff, "Swap_tokens","token");
   if ( cTXT == NULL ) return NULL;
   
   char * token1 = (char *) Get_token(cTXT,nToken1);
   if ( token1 == NULL){
       token1 = pop_stack_hard("Swap_tokens","get_token");
   }
   char * token2 = (char *) Get_token(cTXT,nToken2);
   if ( token2 == NULL){
       token2 = pop_stack_hard("Swap_tokens","get_token");
   }
   
   char * nuevo1 = (char *) Mod_token(cTXT, token2, nToken1);
   if ( nuevo1 == NULL){
       nuevo1 = pop_stack_hard("Swap_tokens","get_token");
   }

   char * nuevo2 = (char *) Mod_token(nuevo1, token1, nToken2);
   if ( nuevo2 == NULL){
       nuevo2 = pop_stack_hard("Swap_tokens","get_token");
   }
   free(nuevo1);
   free(token1);
   free(token2);
   free(cTXT);
   if(PILA_GADGET){
       push_stack_str(nuevo2); free(nuevo2);return NULL;
   }
   return (nuevo2);
}

/* FIRST_HALF LAST_HALF - cortan el string en la primera aparición del caracter pCh */
char * First_cut( char * pStringBuff, char pCh ){
  
  char * pString=pop_stack_if_null_noLen(pStringBuff, "First_cut","target");
  if ( pString == NULL ) return NULL;
   
  const char * Base = index(pString, pCh);
  if( Base ){
     Str_init(retVal);
     size_t l = Base - pString;
     pString[l] = '\0';
     Copy( retVal, pString );
     free(pString);
     if(PILA_GADGET){
        push_stack_str(retVal);
        free(retVal);
        return NULL;
     }
     return retVal;
  }
  free(pString);
  return NULL;
}

char * Last_cut( char * pStringBuff, char pCh ){

  char * pString=pop_stack_if_null_noLen(pStringBuff, "Last_cut","target");
  if ( pString == NULL ) return NULL;

  const char * Base = rindex(pString, pCh);
  if( Base ){
     Str_init(retVal);
     Base++;
     Copy( retVal, Base );
     free(pString);
     if(PILA_GADGET){
        push_stack_str(retVal);
        free(retVal);
        return NULL;
     }
     return retVal;
  }
  free(pString);
  return NULL;
}


/* CUT y RCUT - cortan el string en la primera aparición del caracter pCh */
char * Cut( char * pStringBuff, char pCh ){
  
  char * pString=pop_stack_if_null_noLen(pStringBuff, "Cut","target");
  if ( pString == NULL ) return NULL;
   
  const char * Base = index(pString, pCh);
  if( Base ){
     Str_init(retVal);
     Copy( retVal, Base );
     free(pString);
     if(PILA_GADGET){
        push_stack_str(retVal);
        free(retVal);
        return NULL;
     }
     return retVal;
  }
  free(pString);
  return NULL;
}

char * Cutr( char * pStringBuff, char pCh ){

  char * pString=pop_stack_if_null_noLen(pStringBuff, "Cutr","target");
  if ( pString == NULL ) return NULL;

  const char * Base = rindex(pString, pCh);
  if( Base ){
     Str_init(retVal);
     Copy( retVal, Base );
     free(pString);
     if(PILA_GADGET){
        push_stack_str(retVal);
        free(retVal);
        return NULL;
     }
     return retVal;
  }
  free(pString);
  return NULL;
}

/* MULTICAT Y MULTICOPY */
/* Necesita que la variable target tenga espacio */
char * Multi_cat( char * szDest, const char * szSrc, ... )
{
   char * szResult = szDest;
   va_list va;

   while( *szDest )
      szDest++;

   va_start( va, szSrc );
   if(PILA_GADGET){
      while( CONTADOR_PILA >= 0 )
      {
         if( szSrc ){
            while( *szSrc )
               *szDest++ = *szSrc++;
         }else{
            char *szSrcBuff = pop_stack_hard("Multi_cat", "multi_cat");
            const char * pText = szSrcBuff;
            while( *pText )
               *szDest++ = *pText++;
            free(szSrcBuff);
         }
         szSrc = va_arg( va, char * );
      }
      /* verificar si no quedan más variables */
   }
   while( szSrc )
   {
      while( *szSrc )
         *szDest++ = *szSrc++;
      szSrc = va_arg( va, char * );
   }

   *szDest = '\0';
   va_end( va );

   if(PILA_GADGET){
      push_stack_str(szResult);
      return NULL;
   }
   return szResult;
}

char * Multi_copy( char * szDest, const char * szSrc, ... )
{
   char * szResult;
   va_list va;

   if( szDest == NULL )
   {
      long nSize = 1;
      const char * szSrcPtr = szSrc;
      va_start( va, szSrc );
      long nRecup = 0;
      if(PILA_GADGET){
         while( CONTADOR_PILA >= 0 )
         {
             if ( szSrcPtr ){
                 nSize += strlen( szSrcPtr );
             }else{
                 char *szSrcBuff = pop_stack_hard("Multi_copy", "multi_copy");
                 const char * pText = szSrcBuff;
                 if( pText )
                     nSize += strlen( pText );
                 free(szSrcBuff);
                 ++nRecup;
             }
             szSrcPtr = va_arg( va, char * );
         }
         CONTADOR_PILA += nRecup;
      }
      while( szSrcPtr )
      {
         nSize += strlen( szSrcPtr );
         szSrcPtr = va_arg( va, char * );
      }
      va_end( va );
  /*    
      const char * szSrcPtr = szSrc;
      long nSize = 1;

      va_start( va, szSrc );
      
      while( szSrcPtr )
      {
         nSize += strlen( szSrcPtr );
         szSrcPtr = va_arg( va, char * );
      }
      va_end( va );
*/
     /* aqui no puedo usar directamente el stack, porque los elementos
        aun deben ser usados */
      szDest = Space( nSize );
      
   }else { 
      Msg_yellow("Multi_copy : variable TARGET debe ser NULL\n");
      return szDest;
   }
   szResult = szDest;

   va_start( va, szSrc );
   
   if(PILA_GADGET){
      while( CONTADOR_PILA >= 0 )
      {
         if( szSrc ){
            while( *szSrc )
               *szDest++ = *szSrc++;
         }else{
            char *szSrcBuff = pop_stack_hard("Multi_copy", "multi_copy");
            const char * pText = szSrcBuff;
            while( *pText )
               *szDest++ = *pText++;
            free(szSrcBuff);
         }
         szSrc = va_arg( va, char * );
      }
      /* verificar si no quedan más variables */
   }

   
   while( szSrc )
   {
      while( *szSrc )
         *szDest++ = *szSrc++;
      szSrc = va_arg( va, char * );
   }
   *szDest = '\0';
   va_end( va );

  /* esto debe estar aqui, tal cual */
   if(PILA_GADGET){
      push_stack_str(szResult);
      free(szResult);
      return NULL;
   }

   return szResult;
}

/*  UPPER */
char * Upper( const char * cText ){

   long nLen = 0;//strlen(cText);
   
   char * buffer=pop_stack_if_null(cText, &nLen,"Upper","target");
   if ( buffer == NULL ) return NULL;
   
   
   char * newStr = NULL;
   if(PILA_GADGET){  // trabajo directamente sobre la pila.
      malloc_stack_str(nLen+10);
      newStr = STK_STR;
   }else{
      newStr = (char *) calloc( nLen+10, 1 );
   }
   if ( newStr ){
      int i=0;
      const char * pText = buffer; //cText;
      while( *pText ) {
          if( *pText == -61 ){
             newStr[i++] = *pText;
             pText++;
             newStr[i++] = *pText - 32;
          }else{
             newStr[i++] = toupper((unsigned char) *pText);
          }
          pText++; 
      }
   }
   free(buffer);
   if(PILA_GADGET){
      // push_stack_str(newStr);
      // free(newStr);
       return NULL;
   }
   
   return newStr;
}

/*  LOWER */
char * Lower( const char * cText ){

   long nLen = 0;//strlen(cText);

   char * buffer=pop_stack_if_null(cText, &nLen,"Lower","target");
   if ( buffer == NULL ) return NULL;

   char * newStr = NULL;
   //newStr = (char *) calloc( nLen+10, 1 );
   if(PILA_GADGET){  // trabajo directamente sobre la pila.
      malloc_stack_str(nLen+10);
      newStr = STK_STR;
   }else{
      newStr = (char *) calloc( nLen+10, 1 );
   }
   if ( newStr ){
      int i=0;
      const char * pText = buffer; //cText;
      while( *pText ) {
          if( *pText == -61 ){
             newStr[i++] = *pText;
             pText++;
             newStr[i++] = *pText + 32;
          }else{
             newStr[i++] = tolower((unsigned char) *pText);
          }
          pText++; 
      }
   }
   
   free(buffer);
   if(PILA_GADGET){
       //push_stack_str(newStr);
       //free(newStr);
       return NULL;
   }

   return newStr;
}

/* REVERSE STRING */
char * Reverse( const char* cString ){
   
   long nLen = 0;//strlen(cString);

   char * buffer=pop_stack_if_null(cString, &nLen,"Reverse","target");
   if ( buffer == NULL ) return NULL;

   char *str = NULL; //(char*)calloc( nLen+10,1);
   
   if(PILA_GADGET){  // trabajo directamente sobre la pila.
      malloc_stack_str(nLen+10);
      str = STK_STR;
   }else{
      str = (char *) calloc( nLen+10, 1 );
   }
   
   memcpy(str, (const char *) buffer, nLen);
   
   char *p1, *p2;

   if (! str || ! *str){
      if( buffer ) free(buffer);
      return NULL;
   }else{
      long nLenStr = strlen(str);
      for (p1 = str, p2 = str + nLenStr - 1; p2 > p1; ++p1, --p2)
      {
         *p1 ^= *p2;
         *p2 ^= *p1;
         *p1 ^= *p2;
      }
      /* ajuste para letras en español que quedaron invertidas */
      char pt[1];
      for ( p1 = str, p2 = str; *p1 != '\0' ; ++p1, ++p2 ){
         if( *p1 < 0 ){
            pt[0] = *p1; ++p2;
            *p1 = *p2;
            *p2 = pt[0];
            p1+=2; ++p2;
         }
      }
      
      free(buffer);
      if(PILA_GADGET){
          //push_stack_str(str);
          //free(str);
          return NULL;
      }
      
      return str;
   }
}


/*  PARSER UNPARSER */
/* PARSER Y UNPARSER DE EXPRESIONES HTML */

// msg = Parser( "campo", "a=0 b='algo'", "", ONLY_TAG(0)|NORMAL_TAG(1));
// Cat( html, msg);
// free(msg);
// esto puede ser encerrado en una macro o función.

char * Parser( const char* cNameBuff, const char* cAttribsBuff, const char* cContentBuff, int nUnicoTag ){

      long nLenAttr = 0;//strlen(cAttribs);
      long nLen = 0;//strlen(cContent);
      long nLenName = 0;//strlen(cName); 

      char * cName=pop_stack_if_null(cNameBuff, &nLenName,"Parser","field");
      if ( cName == NULL ) return NULL;
      
      char * cAttribs=pop_stack_if_null(cAttribsBuff, &nLenAttr,"Parser","attribs");
      if ( cAttribs == NULL ) { free(cName);return NULL;}
      
      char * cContent=pop_stack_if_null(cContentBuff, &nLen,"Parser","content");
      if ( cContent == NULL ) { free(cName);free(cAttribs);return NULL;}

      char* cTemp = (char*)calloc( nLenAttr + nLenName + nLenName + nLen + 50, 1);
      if (cTemp==NULL){
          free(cName);free(cAttribs);free(cContent);
          Msg_red("No hay memoria para 'Parser'\n");
          Is_ok=0;
          return NULL;
      }
      memset(cTemp,0,nLenAttr + nLenName + nLenName + nLen + 50);  // relleno con 0.
      memcpy(cTemp,"<",1);

      memcpy(cTemp + 1,cName,nLenName);
      
      int spc = 1;
      if( nLenAttr > 0 ){  // hay atributos
         memcpy(cTemp + 1 + nLenName," ",1);
         spc=2;
      }
      memcpy(cTemp + nLenName + spc,cAttribs,nLenAttr);
      
     // verificar si es un unico tag y añadieron contenido:
      if(nLen && nUnicoTag) nLen=0;  // anula el contenido
       
      if(!nLen){      // es etiqueta vacía, sin contenido?
         if(nUnicoTag){        // del tipo <nombre [attrib]/>
            memcpy(cTemp + nLenName + spc + nLenAttr,"/>",2);
            cTemp[nLenName + spc + 2 + nLenAttr]='\0';
         }else{           // del tipo <nombre [attrib]>
            memcpy(cTemp + nLenName + spc + nLenAttr,">",1);
         }
      }else{                                // tiene contenidos
         memcpy(cTemp + nLenName + spc + nLenAttr,">",1);
         memcpy(cTemp + nLenName + spc + 1 + nLenAttr,cContent,nLen);
      }
      if(!nUnicoTag){  // añado cierre de tag
         memcpy(cTemp + nLenName + spc + 1 + nLenAttr + nLen,"</",2);
         memcpy(cTemp + nLenName + spc + 3 + nLenAttr + nLen,cName,nLenName);
         memcpy(cTemp + nLenName + spc + 3 + nLenAttr + nLen + nLenName,">",1);
         cTemp[nLenName + spc + 4 + nLenAttr + nLen + nLenName]='\0';
      }

   free(cName);free(cAttribs);free(cContent);
   if(PILA_GADGET){
       push_stack_str(cTemp);
       free(cTemp);
       return NULL;
   }

return cTemp;
}

/* NO PUEDE SER STACKIZADO */
ST_GETTAG Unparser( char **cVarStr, char* cName ){

      long nLenName = strlen(cName);
      long nLenVar = strlen(*cVarStr);
     //
      int sw=1; // variable de control
      char* cField = (char*)calloc(nLenName + 100,1); // campo a buscar. Podría incluir lista de atributos
      /*if(cField==NULL){
          Msg_red("No hay memoria para Unparser (get fields)\n");
          return retVal;
      }*/
      memset(cField,0,nLenName + 100);
      memcpy(cField,"<",1);                // armamos el campo a buscar en cVarStr
      memcpy(cField + 1,cName,nLenName);
      memcpy(cField + 1 + nLenName,">",1);
      cField[nLenName + 2]='\0';       // "<field>"
      ///printf("FIELD : [%s]\n", cField);
      int es_vacio=0;
      int tieneAtrib=0;
      char* iniF = strstr(*cVarStr,cField);  // primera ocurrencia del campo
      char* atributos=(char*)calloc(100,1);   // por si encuentra atributos más adelante.
      /*if(atributos==NULL){
          Msg_red("No hay memoria para Unparser (get attribs)\n");
          free(cField);
          return retVal;
      }*/
      int ctaAtrib=0;        // para saber cuántos atributos hay en el campo, de existir.

      ST_GETTAG retVal;  // inicializo estructura de retorno.
      retVal.content=NULL;
      retVal.attrib=NULL;
      retVal.name=NULL;
      retVal.len=0;
      ///retVal.status=0;

            
      if (iniF==NULL)
      {  // no lo encontró. Puede ser un campo solitario.
         cField[nLenName + 1]='/';cField[nLenName + 2]='>';cField[nLenName + 3]='\0';  // "<field/>"
         //printf("FIELD2 : [%s]\nTEXT : \n%s\n", cField, *cVarStr);
         iniF = strstr(*cVarStr,cField);   // busco otra vez.
         if(iniF==NULL)
         {  // no lo encontró. Podría ser un tag con atributos...
            cField[nLenName + 1]=' ';cField[nLenName + 2]='\0';  // "<field "
            //printf("FIELD3 : [%s]\n", cField);
            iniF = strstr(*cVarStr,cField);   // busco otra vez.
            if(iniF==NULL)
            {
               sw=0;
               Msg_amberf("Unparser : no se ha encontrado el campo indicado: '%s'\n",cName);
               Is_ok=0;
            }
            else
            {  // tiene atributos
               tieneAtrib=1;
               // debo completar el campo, para incluir los atributos, y luego, obtenerlos afuera
               char* tiniF = iniF + strlen(cField);
               int i = nLenName + 2;
               int j=0;
               do
               {  // busca por el final del tag
                  cField[i] = *tiniF;
                  if(*tiniF!='/' && *tiniF!='>')   // solo necesito el contenido, no el campo completo.
                  {
                     atributos[j] = *tiniF; j++;
                  }
                  if(*tiniF=='=') ctaAtrib++;
                  tiniF++; i++;
               }
               while(*tiniF!='>');

               atributos[j]='\0';  // aqui solo debería tener la lista de atributos.

               if(*tiniF=='>') {cField[i] = *tiniF; i++;} // el rezagado.
               cField[i]='\0';
             //  printf("\nCFIELD = %s, i=%d,cfield[i-2]=%c\n",cField,i,cField[i-2]);
               if(cField[i-2]=='/')
               {  // es un tag unico.
                  es_vacio=1;
                  retVal.content = NULL;  // devuelve nulo como contenido
               }
            }
         }
         else
         {
            es_vacio=1;
            retVal.content = NULL;  // devuelve nulo como contenido
         }
      }
      // procesar la salida.
      if(sw)
      {
         if(!es_vacio)
         {  // obtengo el contenido
            char* tiniF = iniF;   // rescato posicion original del campo.
            tiniF += strlen(cField); // ubico en el inicio del contenido
            // armo el final del campo:
            char* cFieldEnd = (char*)calloc(nLenName + 100,1); // campo a buscar
   /*         if (cFieldEnd==NULL){
                Msg_red("No hay memoria para Unparser (get fields)");
                free(cField);
                return retVal;
            }*/
            memset(cFieldEnd,0,nLenName + 100);
            memcpy(cFieldEnd,"</",2);
            memcpy(cFieldEnd + 2,cName,nLenName);
            memcpy(cFieldEnd + 2 + nLenName,">",1);
            cFieldEnd[nLenName + 3]='\0';
            //busco campo final! Primera ocurrencia.
            char* iniFE = strstr(*cVarStr,cFieldEnd);
            int porcion = iniFE - tiniF;
            //armo string de contenido y guardo en Stack
          //  printf("\nPORCION=%d\n",porcion);
            if(porcion>0){
               char* cFieldContent = (char*)calloc(porcion + 1,1);
               /*if(cFieldContent==NULL){
                   Msg_red("No hay memoria para Unparser (get contents)");
                   free(cField);free(cFieldEnd);
                   return retVal;
               }*/
               memset(cFieldContent,0,porcion + 1);
               memcpy(cFieldContent,tiniF,porcion);
               cFieldContent[porcion]='\0';

             //  printf("\nBUFFER=%s\n",cBuffer);
               retVal.content = (char *)calloc( strlen(cFieldContent)+5,1);
               if(retVal.content){
                   strcpy(retVal.content, cFieldContent);
               }
               free(cFieldContent);
            }else{
               retVal.content = NULL;
            }
            //borro "porcion" de la variable cVarStr:
         //   printf("\nPASO!\nENTRA A PREPARAR VARIABLE");
            char* cNewVar = (char*)calloc(nLenVar + 10, 1); // preparo nueva variable
            memset(cNewVar,0,nLenVar+10);
            char * temporal = *cVarStr;
            porcion = iniF-temporal;
            int i=0;
            while(porcion--)
            {
               cNewVar[i] = temporal[i];i++;
            }
            char* final = iniFE + strlen(cFieldEnd);
            while(*final)
            {
               cNewVar[i] = *final; final++;i++;
            }
            cNewVar[i]='\0';
           // printf("\n-----variable temporal: %s\n\n",cNewVar);
            free(*cVarStr);
            
            *cVarStr = (char *)calloc( strlen(cNewVar)+5,1);
            if(*cVarStr){
                strcpy(*cVarStr, cNewVar);
            }
           // printf("\n-----1 quedó: %s\n",*cVarStr);
            free(cNewVar);
            free(cFieldEnd);
         //   printf("\nPASO!\nSALE!");
         }
         else
         {
            //borro "porcion" de la variable cVarStr:
            char* cNewVar = (char*)calloc(nLenVar + 10, 1);
            memset(cNewVar,0,nLenVar+10);
            char * temporal = *cVarStr;
            int porcion = iniF-temporal;
            int tp = porcion;
            int i=0;
            while(porcion--)
            {
               cNewVar[i] = temporal[i];i++;
            }
            const char* final = temporal + ( tp + strlen(cField));
            while(*final)
            {
               cNewVar[i] = *final; final++;i++;
            }
            cNewVar[i]='\0';
           // printf("\n-----variable temporal: %s\n\n",cNewVar);
            free(*cVarStr);
            *cVarStr = (char *)calloc( strlen(cNewVar)+5,1);
            if(*cVarStr){
                strcpy( *cVarStr, cNewVar);
            }
           // printf("\n-----2 quedó: %s\n",*cVarStr);
            free(cNewVar);
         }
      }
      free(cField);
      // procesar lista de atributos.
      if(tieneAtrib)
      {  // obtiene los atributos y guardo en array, y el resto del proceso queda igual
         if(ctaAtrib)
         {  // puede que se escribió: <field >, o <field />: debe dejar pasar como campo normal.

           // inicializo array de atributos
            retVal.attrib = ( char ** ) calloc( sizeof( char * ) * ( ctaAtrib ), 1 );
            retVal.name = ( char ** ) calloc( sizeof( char * ) * ( ctaAtrib ), 1 );
            
            int i=0;
            int indArray=0;
          //  printf("\nENTRA A ATRIBUTOS DESDE: %s",atributos);
            while(atributos[i]!='\0')
            {
               if(atributos[i]==' ') {i++;continue;}  // salte los espacios en blanco.
               //saco el nombre del atributo:
               char* cNameAttrib = (char*)calloc(100, 1);
               int j=0;
               while(atributos[i]!='='){
                   if(atributos[i]==' ') {i++;continue;}
                   cNameAttrib[j] = atributos[i];
                   ++j;
                   ++i;
               }
               // guardo nombre de atributo:
               * (retVal.name + indArray ) = (char*)calloc(strlen( cNameAttrib )+1,1);
               strcpy(* (retVal.name + indArray ), cNameAttrib);
               free(cNameAttrib);
               
               if(atributos[i]=='=')  // encontré un valor.
               {
                  i++;  // avanzo, y veo qué tiene: numero, string, u otra cosa.
               //   printf("\nENTRA A GUARDAR VALOR");
                  while(atributos[i]!='\0' && atributos[i]==' ') i++;   // quita espacios en blanco.
                  int j=0;
                  char* cValor = (char*)calloc(100, 1);
                  if(atributos[i]==34 || atributos[i]==39)  // hay un string.
                  {
                     i++;    // no guarda comillas.
                     do{
                        cValor[j] = atributos[i];  // guardo todo lo que hay dentro de la cadena.
                        i++; j++;
                     }while(atributos[i]!='\0' && atributos[i]!=34 && atributos[i]!=39);
                  }else{   // es otra cosa. Termina con espacio en blanco.
                     do{
                        cValor[j] = atributos[i];  // guardo todo lo que hay hasta espacio en blanco.
                        i++; j++;
                     }while(atributos[i]!='\0' && atributos[i]!=' ');
                  }
                  cValor[j]='\0';
              //    printf("\nVALOR OBTENIDO: %s",cValor);
                  // guarda en array:
                  
                  * (retVal.attrib + indArray ) = (char*)calloc(strlen( cValor )+1,1);
                  strcpy(* (retVal.attrib + indArray++ ), cValor);

                  free(cValor);
               }
               i++;
            }
            retVal.len = indArray;  // total de atributos leidos

         }
      }
      free(atributos);
      return retVal;
}

/* TRIMS */
                                   
char * __Rtrim__(const char *sbuffer) {

   long size = 0;
   char * linea=pop_stack_if_null(sbuffer, &size,"Trim_r","target");
   if ( linea == NULL ) return NULL;

   if(size>0) size--;   // me salto el '\0'
   char * r, *buffer=NULL;
   const char * pLinea = linea;
   const char * t;
   long tsize;

   t = pLinea;
   t += size;
   while( X_ISSPACE( *t ) )
   {
      t--;
      size--;
      if (size==0 && *t==' ') {--t;break;}
   }
   tsize = t - pLinea + 1;

   ///buffer = (char *) calloc(tsize+1,1);
   if(PILA_GADGET){  // trabajo directamente sobre la pila.
      malloc_stack_str(tsize+1);
      buffer = STK_STR;
   }else{
      buffer = (char *) calloc( tsize+1, 1 );
   }
   
   if (buffer==NULL) { if(linea) free(linea); return NULL; }
   r = buffer;
   memcpy(r,pLinea,tsize);
   r[tsize]='\0';

   free(linea);
   if(PILA_GADGET){
       //push_stack_str(buffer);
       //free(buffer);
       return NULL;
   }

   return buffer;
}

char * __Ltrim__(const char *sbuffer) {

   long nLen = 0;
   char * linea=pop_stack_if_null(sbuffer, &nLen,"Trim_l","target");
   if ( linea == NULL ) return NULL;

   const char *t=linea;
   
   while( nLen && X_ISSPACE( *t ) )
   {
      t++;
      nLen--;
   }
   char *r, *buffer=NULL;
   //buffer = (char *) calloc(nLen+1,1);
   if(PILA_GADGET){  // trabajo directamente sobre la pila.
      malloc_stack_str(nLen+1);
      buffer = STK_STR;
   }else{
      buffer = (char *) calloc( nLen+1, 1 );
   }
   
   if (buffer==NULL) { if(linea) free(linea); return NULL; }
   
   r = buffer;
   memcpy(r,t,nLen); 
   r[nLen]='\0';

   free(linea);
   if(PILA_GADGET){
       //push_stack_str(buffer);
       //free(buffer);
       return NULL;
   }

   return buffer;
}

char * __Alltrim__( const char *sbuffer) {

   long size = 0;
   char * linea=pop_stack_if_null(sbuffer, &size,"Trim","target");
   if ( linea == NULL ) return NULL;

   const char *t=linea;
   char *l = __Ltrim__(t); //,size);
   if (l==NULL){ // es posible que venga desde una pila:
       l = pop_stack_hard("Trim","Trim_l");
       if ( l == NULL ){
          free(linea);
          return NULL;
       }
   }
   char *r = __Rtrim__(l); //,strlen(l));
   if (r==NULL){ // es posible que venga desde una pila:
       r = pop_stack_hard("Trim","Trim_r");
       if ( r == NULL ){
          free(linea);free(l);
          return NULL;
       }
   }
   
   
   long nLen = strlen(r);
   char *u, *buffer=NULL;
  // buffer = (char *) calloc(nLen+1,1);
   if(PILA_GADGET){  // trabajo directamente sobre la pila.
      malloc_stack_str(nLen+1);
      buffer = STK_STR;
   }else{
      buffer = (char *) calloc( nLen+1, 1 );
   }
   
   if (buffer==NULL) { if(linea) free(linea); free(l);free(r); return NULL; }
   
   u = buffer;
   memcpy(u,r,nLen); 
   free(r);free(l);
   u[nLen]='\0';

   free(linea);
   if(PILA_GADGET){
       //push_stack_str(buffer);
       //free(buffer);
       return NULL;
   }

   return buffer;
}

/* Capitalize */
char * Capital( const char* sBuffer ){
    char * buffer = pop_stack_if_null_noLen(sBuffer, "Capital","target");
    if ( buffer == NULL ) return NULL;

    buffer[0] = toupper(buffer[0]);
    Item_return_release( buffer );
}

/* PAD */
char * __Pad__( char * sbuffer, char cPad, int nLen, int tCompare ){

   long nSize = 0;
   char * cTXT=pop_stack_if_null(sbuffer, &nSize,tCompare==0? "Pad_c": tCompare==1? "Pad_r":"Pad_l","target");
   if ( cTXT == NULL ) return NULL;

   const char * cText = cTXT;

   if( nSize < nLen ){
      char * szResult = NULL; //( char * ) calloc( nLen + 1, 1 );
      if(PILA_GADGET){  // trabajo directamente sobre la pila.
         malloc_stack_str(nLen+1);
         szResult = STK_STR;
      }else{
         szResult = (char *) calloc( nLen+1, 1 );
      }
      
      switch( tCompare){
         case 0: {   // X_PADC 
            long nPad = ( ( long ) nLen - nSize ) >> 1;
            memset( szResult, cPad, nPad );
            memcpy( szResult + nPad, cText, nSize );
            memset( szResult + nPad + nSize, cPad, ( long ) nLen - nSize - nPad );
            break;
         }case 1: {  // X_PADR
            memcpy( szResult, cText, nSize );
            memset( szResult + nSize, cPad, ( long ) nLen - nSize );
            break;
         }case 2: {  // X_PADL
            memset( szResult, cPad, ( long ) nLen - nSize );
            memcpy( szResult + ( long ) nLen - nSize, cText, nSize );
            break;
         }
      }
      free(cTXT);
      if(PILA_GADGET){
          //push_stack_str(szResult);
          //free(szResult);
          return NULL;
      }

      return ( szResult );
   }else{
      
      if(PILA_GADGET){
          push_stack_str(cTXT);
          free(cTXT);
          return NULL;
      }

      return ( cTXT );
   }
}

/* REPLICATE */
char * Replicate( char * szText, int nTimes) {

   long nLen = 0;//strlen(szText);

   char * ds_buffer=pop_stack_if_null(szText, &nLen,"Replicate","target");
   if ( ds_buffer == NULL ) return NULL;

   long nTotalLen = ( nLen * nTimes );
   char * szResult = NULL; //(char *) calloc(( nTotalLen + 1),1);
   if(PILA_GADGET){  // trabajo directamente sobre la pila.
      malloc_stack_str(nTotalLen + 1);
      szResult = STK_STR;
   }else{
      szResult = (char *) calloc( nTotalLen + 1, 1 );
   }
   
   if ( szResult == NULL ) { free(ds_buffer); return NULL;}
     
   char * szPtr = szResult;

   while(nTimes)
   {
      int j=nLen;
      while(j--) szPtr[j] = ds_buffer[j]; //szText[j];
      szPtr += nLen;
      --nTimes;
   }
   szResult[ nTotalLen ] = '\0';
   
   free(ds_buffer);
   if(PILA_GADGET){
      //push_stack_str(szResult);
      //free(szResult);
      return NULL;
   }
   
   return szResult;
}

/* SUBSTR */
char * Substr( char * TextoBuff, long nPos, long nLen ){

      long nSize = 0; //strlen(Texto);      

      char * ds_buffer=pop_stack_if_null(TextoBuff, &nSize,"Substr","target");
      if ( ds_buffer == NULL ) return NULL;

      if( nPos < 0 ){
         nPos += nSize;
         if( nPos < 0 )
            nPos = 0;
      }
      else if( nPos ){
         nPos--;
      }

      if( nPos < nSize ){
         if ( nLen > 0 ) {
            if( nLen > nSize - nPos )
               nLen = nSize - nPos;
         }else{
            nLen = nSize - nPos;
         }
         
         if( nLen > 0 ){
            if( nLen == nSize ){
               if(PILA_GADGET){
                  push_stack_str(ds_buffer);
                  free(ds_buffer);
                  return NULL;
               }
               return ds_buffer; //Texto;
            }else{
               const char * Text = ds_buffer; //Texto;
               
               char * szResult = ( char * ) calloc( nLen + 10, 1 );

               if ( szResult != NULL ){
                   Text = Text + nPos;
                   memcpy( szResult, Text, nLen );
                   szResult[ nLen ] = '\0';

                   free(ds_buffer);
                   if(PILA_GADGET){
                       push_stack_str(szResult);
                       free(szResult);
                       return NULL;
                   }
                   return szResult;
               }else{
                   //printf("No hubo espacio para resultado\n");
                   free(ds_buffer);
                   return NULL;
               }
            }
         }else{
            //printf("nLen (%ld) <= 0 \n",nLen);
            free(ds_buffer);
            return NULL;
         }
      }else{
         //printf("nPos (%ld) < nSize (%ld)\n",nPos,nSize);
         free(ds_buffer);
         return NULL;
      }
}

char * Left( char * cTXT, long nLen ){
      return Substr( (char *) cTXT, 1, (long) nLen );
}

char * Right( char * cTXT, long nPos ){
      return Substr( (char *) cTXT, (long) nPos, 0 );
}

/* DEVUELVEN UN RESULTADO NUMERICO - POSICION */

/*
 * Harbour Project source code:
 * STUFF() function
 *
 * Copyright 1999 Antonio Linares <alinares@fivetech.com>
 * www - http://harbour-project.org*/
 
 
/* ------------------------------------------------ */
/* search for exact substring in backward direction */
/* ------------------------------------------------ */
const char *ct_at_exact_backward( const char * pcString, long sStrLen,
                                  const char * pcMatch, long sMatchLen, long * psMatchStrLen )
{

   long sIndex;
   const char * pcRet;

   if( ( sMatchLen == 0 ) || ( sStrLen < sMatchLen ) )
      return NULL;

   for( pcRet = pcString + sStrLen - sMatchLen; pcRet >= pcString; pcRet-- )
   {
      for( sIndex = 0; sIndex < sMatchLen; sIndex++ )
         if( *( pcRet + sIndex ) != *( pcMatch + sIndex ) )
            break;
      if( sIndex == sMatchLen )
      {
         /* last match found */
         if( psMatchStrLen != NULL )
            *psMatchStrLen = sMatchLen;
         return pcRet;
      }
   }

   return NULL;
}


const char *ct_at_exact_forward( const char * pcString, long sStrLen,
                                 const char * pcMatch, long sMatchLen, long * psMatchStrLen )
{

   long sPos;

   if( ( sMatchLen == 0 ) || ( sStrLen < sMatchLen ) )
      return NULL;

   sPos = __Strat__( pcMatch, sMatchLen, pcString, sStrLen, 1/*, 0*/ );
   if( sPos == 0 )
   {
      return NULL;
   }
   else
   {
      if( psMatchStrLen != NULL )
         *psMatchStrLen = sMatchLen;
      return pcString + sPos - 1;
   }
}

/* STRAT encuentra un substring dentro de otro. Acepta caracteres españoles */
long __Strat__( const char * szSub, long nSubLen, const char * szText, long nLen, short tCompare )
{

   if( nSubLen > 0 && nLen >= nSubLen )
   {
      long nPos = 0;
      nLen -= nSubLen;

      if( tCompare ){  // 1 = compare case sensitive
         do
         {
            if( szText[ nPos ] == *szSub )
            {  
               long nSubPos = nSubLen;
               do
               {
                  if( --nSubPos == 0 )
                         return nPos + 1;
               }
               while( szText[ nPos + nSubPos ] == szSub[ nSubPos ] );
            }
         }
         while( nPos++ < nLen );
      }else{   // 0 = compare case insensitive
         do
         {
            if( X_TOUPPER(szText[ nPos ]) == X_TOUPPER(*szSub) )
            {  
               long nSubPos = nSubLen;
               do
               {
                  if( --nSubPos == 0 ){
                      return nPos + 1;
                  }
               }
               while( szText[ nPos + nSubPos ] == szSub[ nSubPos ] );
            }
         }
         while( nPos++ < nLen );      
      }
   }

   return 0;
}

/* Case-sensitive */
long Str_at( const char * szSubBuff, const char * cTXTBuff )
{
   long nSubLen = 0;//strlen(szSub);
   long nLen = 0;//strlen(cTXT);
   
   char * szSub = pop_stack_if_null(szSubBuff, &nSubLen,"Str_at","to search");
   if ( szSub ==NULL ) return 0L;

   char * cTXT = pop_stack_if_null(cTXTBuff, &nLen,"Str_at","target");
   if ( cTXT ==NULL ) {free(szSub);return 0L;}
         
   long retVal = __Strat__( szSub, nSubLen, cTXT, nLen, 1 );
   free(szSub);free(cTXT);
   return ( retVal );
   
}
/* Case insensitive */
long Str_iat( const char * szSubBuff, const char * cTXTBuff )
{
   long nSubLen = 0;//strlen(szSub);
   long nLen = 0;//strlen(cTXT);

   char * szSub = pop_stack_if_null(szSubBuff, &nSubLen,"Str_iat","to search");
   if ( szSub ==NULL ) return 0L;

   char * cTXT = pop_stack_if_null(cTXTBuff, &nLen,"Str_iat","target");
   if ( cTXT ==NULL ) {free(szSub);return 0L;}

   long retVal = __Strat__( szSub, nSubLen, cTXT, nLen, 0 );
   free(szSub);free(cTXT);
   return ( retVal );
}

int Index_at( const char * pcStringBuff, const char * pcStringToMatchBuff, long nCounter ){

   long sStrToMatchLen = 0;//strlen(pcStringToMatch);
   long sStrLen = 0;//strlen(pcString);

   char * pcString = pop_stack_if_null(pcStringBuff, &sStrLen,"Index_at","target");
   if ( pcString ==NULL ) return 0L;

   char * pcStringToMatch = pop_stack_if_null(pcStringToMatchBuff, &sStrToMatchLen,"Index_at","to search");
   if ( pcStringToMatch ==NULL ) {free(pcString);return 0L;}


   long sIgnore=0, sMatchStrLen = 0;
   const char *pc = NULL;

   /* nth match or last match ? */
   if( nCounter != 0 ){
      /* find the <nCounter>th match */
      const char *pcSubStr;
      long sSubStrLen;
      long nMatchCounter = 0;

      pcSubStr = pcString;
      sSubStrLen = sStrLen;
      
      if( nCounter > 0 ){
         while( nMatchCounter < nCounter ){
            pc = ct_at_exact_forward( pcSubStr, sSubStrLen, pcStringToMatch,
                                               sStrToMatchLen, &sMatchStrLen );
            if( pc == NULL ){
               /* no match found; if this happens at this point,
                  there are no <nCounter> matches, so return an empty string */
               free(pcString);free(pcStringToMatch);
               return 0;
            }
            nMatchCounter++;

            if( MULTIPASS )
               pcSubStr = pc + 1;
            else
               pcSubStr = pc + sMatchStrLen;
            sSubStrLen = sStrLen - ( pcSubStr - pcString );
         }
      }else{  // busca igual como si no existiera el último
         pc = ct_at_exact_backward( pcString, sStrLen, pcStringToMatch,
                                          sStrToMatchLen, &sMatchStrLen );
         if( pc == NULL ){
            /* ATNUM */
           free(pcString);free(pcStringToMatch);
           return 0;
         } 
      }
   }else{
      pc = ct_at_exact_backward( pcString, sStrLen, pcStringToMatch,
                                          sStrToMatchLen, &sMatchStrLen );
      if( pc == NULL ){
         /* ATNUM */
         free(pcString);free(pcStringToMatch);
         return 0;
      }
   }
   int retVal = ( pc - ( (const char *)pcString - sIgnore ) + 1 );
   free(pcString);free(pcStringToMatch);
   return retVal;
}


/* STUFF*/
/*
 * $Id: stuff.c 16043 2011-01-13 09:44:53Z druzus $
 */

/*
   reemplazar: nDel > 0
   insert: nDel=0
   delete:  nDel>0

*/
char * __stuff_item__( char * pString2, const char * pString1, long nPos, long nDel ){
   long nText = strlen(pString2);
   long nInsert = strlen(pString1);
      
   long nTotalLen;
   if( nPos ){
      if( nPos < 1 || nPos > nText ){
         nPos = nText;
      }else{
         nPos--;
      }
   }

   if( nDel ){
      if( nDel < 1 || nDel > nText - nPos )  nDel = nText - nPos;
   }

   if( ( nTotalLen = nText + nInsert - nDel ) > 0 ){
      char * szResult = ( char * ) calloc( nTotalLen + 1, 1 );
      if( szResult != NULL ) {
         memcpy( szResult, pString2, nPos );
         memcpy( szResult + nPos, pString1, nInsert );
         memcpy( szResult + nPos + nInsert, pString2 + nPos + nDel, nText - ( nPos + nDel ) );
         szResult[ nTotalLen ] = '\0';
      }
      //free(pString1);free(pString2);
      if(PILA_GADGET){
         push_stack_str(szResult);
         free(szResult);
         return NULL;
      }
      return szResult;
   }
   else{
      //free(pString1);
      if(PILA_GADGET){
         push_stack_str(pString2);
         //free(pString2);
         return NULL;
      }
      return pString2;
   }
}

char * Insert( const char * pString1Buff, const char * pString2Buff, long nPos ){
   char * pString1 = pop_stack_if_null_noLen(pString1Buff,"Insert","target");
   if ( pString1 == NULL ) return NULL;
   
   char * pString2 = pop_stack_if_null_noLen(pString2Buff,"Insert","source");
   if ( pString2 == NULL ) {free(pString1);return NULL;}

   char * retVal = __stuff_item__( pString1, pString2, nPos, 0L );
   free(pString1);free(pString2);
   return retVal;
}
char * Delete( const char * pString1Buff, long nPos, long nDel ){
   char * pString1 = pop_stack_if_null_noLen(pString1Buff,"Delete","target");
   if ( pString1 == NULL ) return NULL;

   char * retVal = __stuff_item__( pString1, "", nPos, nDel );
   free(pString1);
   return retVal;
}
char * Replace( const char * pString1Buff, const char * pString2Buff, long nPos, long nDel ){
   char * pString1 = pop_stack_if_null_noLen(pString1Buff,"Replace","target");
   if ( pString1 == NULL ) return NULL;
   
   char * pString2 = pop_stack_if_null_noLen(pString2Buff,"Replace","source");
   if ( pString2 == NULL ) {free(pString1);return NULL;}

   char * retVal = __stuff_item__( pString1, pString2, nPos, nDel );
   free(pString1);free(pString2);
   return retVal;
}

int Str_count_at( const char * pcStringBuffer, const char * pcStringToMatchBuffer, long sIgnore ){

   long sStrToMatchLen = 0; //strlen(pcStringToMatch);
   long sStrLen = 0 ;//strlen(pcString);

   char * pcString = pop_stack_if_null(pcStringBuffer, &sStrLen, "Str_count_at","target");
   if ( pcString ==NULL ) return 0;

   char * pcStringToMatch = pop_stack_if_null(pcStringToMatchBuffer, &sStrToMatchLen, "Str_count_at","match");
   if ( pcStringToMatch ==NULL ) { free(pcString);return 0; }
      
      long sMatchStrLen = 0, sSubStrLen;
      int nCounter;
      const char *pc, *pcSubStr;

      /* eventually ignore some characters if sIgnore>0 */

      if( sIgnore >= sStrLen ){
         return 0;
      }else{
         pcString += sIgnore;
         sStrLen -= sIgnore;
      }

      nCounter = 0;
      pcSubStr = pcString;
      sSubStrLen = sStrLen;

      do{
         pc = ct_at_exact_forward( pcSubStr, sSubStrLen, pcStringToMatch,
                                   sStrToMatchLen, &sMatchStrLen );
         nCounter++;
         if( MULTIPASS ){
            pcSubStr = pc + 1;
         }else{
            pcSubStr = pc + sMatchStrLen;
         }
         sSubStrLen = sStrLen - ( pcSubStr - pcString );
         ///printf("Sub found: [%s]\n",pcSubStr);
      }while( pc != NULL );
      
      free(pcStringToMatch);free(pcString);
      return ( nCounter - 1 );
}

//char * __strtran_item__( const char * szText, const char * szSeek, const char * szReplace, long nInicio, long nCuenta ){
char * __strtran_item__( const char * TextReplace, const char * SeekReplace, const char * bufferReplace, long nInicio, long nCuenta ){

   long nText = 0;
   long nSeek = 0;
   long nReplace = 0;

   char * szText = pop_stack_if_null(TextReplace, &nText, "Stra_tran","target");
   if ( szText ==NULL ) return NULL;
   
   char * szSeek = pop_stack_if_null(SeekReplace, &nSeek, "Stra_tran","to search");
   if ( szSeek == NULL ) {free(szText); return NULL;};

   char * szReplace = pop_stack_if_null(bufferReplace, &nReplace, "Stra_tran","to replace");
   if ( szReplace == NULL ) {free(szText); free(szSeek); return NULL;};

   long nStart = nInicio <= 0 ?  1 : nInicio;
   long nCount = nCuenta <= 0 ? -1 : nCuenta;

   if( nSeek && nSeek <= nText && nStart > 0 ) {
      long nFound = 0;
      long nReplaced = 0;
      long nT = 0;
      long nS = 0;

      while( nT < nText && nText - nT >= nSeek - nS ) {
         if( szText[ nT ] == szSeek[ nS ] ){
            ++nT;
            if( ++nS == nSeek ){
               if( ++nFound >= nStart ){
                  nReplaced++;
                  if( --nCount == 0 )
                     nT = nText;
               }
               nS = 0;
            }
         }else if( nS ){
            nT -= nS - 1;
            nS = 0;
         }else
            ++nT;
      }

      if( nReplaced ){
         long nLength = nText;

         if( nSeek > nReplace )
            nLength -= ( nSeek - nReplace ) * nReplaced;
         else
            nLength += ( nReplace - nSeek ) * nReplaced;

         if( nLength ){
            char * szResult = ( char * ) calloc( nLength + 1, 1 );
            if ( szResult != NULL ){
               char * szPtr = szResult;

               nFound -= nReplaced;
               nT = nS = 0;
               do{
                  if( nReplaced && szText[ nT ] == szSeek[ nS ] ){
                     ++nT;
                     if( ++nS == nSeek ){
                        const char * szCopy;
   
                        if( nFound ){
                           nFound--;
                           szCopy = szSeek;
                        }else{
                           nReplaced--;
                           szCopy = szReplace;
                           nS = nReplace;
                        }
                        while( nS ){
                           *szPtr++ = *szCopy++;
                           --nS;
                        }
                     }
                  }else{
                     if( nS ){
                        nT -= nS;
                        nS = 0;
                     }
                     *szPtr++ = szText[ nT++ ];
                  }
               }while( nT < nText );
            }
            free(szReplace); free(szSeek); free(szText);
            if(PILA_GADGET){
               push_stack_str(szResult);
               free(szResult);
               return NULL;
            }
            return szResult; // si no hay memoria, retorna NULL
         }else{
            free(szReplace); free(szSeek);
            if(PILA_GADGET){
               push_stack_str(szText);
               free(szText);
               return NULL;
            }
            return szText;
         }
      }else{
         free(szReplace); free(szSeek);// free(szText);
         if(PILA_GADGET){
            push_stack_str(szText);
            free(szText);
            return NULL;
         }
         
         return szText;
      }
   }else{
      free(szReplace); free(szSeek); ///free(szText);
      if(PILA_GADGET){
         push_stack_str(szText);
         free(szText);
         return NULL;
      }

      return szText;
   }
}

// funciones que llaman a la de arriba:
char * Str_tran( const char * szText, const char * szSeek, const char * szReplace ){
    char *  retVal = __strtran_item__( szText, szSeek, szReplace, 0L, 0L );
    return retVal;
}

char * Str_tran_first( const char * szText, const char * szSeek, const char * szReplace ){
    char *  retVal = __strtran_item__( szText, szSeek, szReplace, 1L, 1L );
    return retVal;
}
/*#defn    TRAN-LAST(_S_,_R_,_X_)              #RAND;___VTRNL___#RNDV=0;___REPL_TXT_=0;#ATOM#CMPLX;mov(___REPL_TXT_);\
                                             ___FIND_LAST_=0;#ATOM#CMPLX;mov(___FIND_LAST_);___AT_LAST_=0;\
                                             {___FIND_LAST_};#ATOM#CMPLX;cpy(___VTRNL___#RNDV);countat;mov(___AT_LAST_);\
                                             {___AT_LAST_}{___REPL_TXT_}{___FIND_LAST_}{___VTRNL___#RNDV}transform;%RAND;*/
char * Str_tran_last( const char * pcStringBuffer, const char * pcStringToMatchBuffer, const char * szReplace ){
    /* poner los datos en el stack, porque se van con Str_count_at() */
    
    char * pcString = pop_stack_if_null_noLen(pcStringBuffer, "Stra_tran_last(Str_count_at)","target");
    if ( pcString==NULL){ return NULL; }

    char * pcStringToMatch = pop_stack_if_null_noLen(pcStringToMatchBuffer, "Stra_tran_last(Str_count_at)","match");
    if ( pcStringToMatch==NULL){ free(pcString); return NULL; }
    
    int AtLast = Str_count_at( pcString, pcStringToMatch, 0L );
    char * retVal = __strtran_item__( pcString, pcStringToMatch, szReplace, (long)AtLast, 1L );
    
    /* no devuelvo a pila, porque eso ya se resuelve en str_tran_last */     
    free(pcStringToMatch);free(pcString);
    return retVal;
}

char * Str_tran_to( const char * szText, const char * szSeek, const char * szReplace, long nInicio ){
    char *  retVal = __strtran_item__( szText, szSeek, szReplace, nInicio, 1L );
    return retVal;
}

char * Str_tran_all( const char * szText, const char * szSeek, const char * szReplace, long nInicio ){
    char *  retVal = __strtran_item__( szText, szSeek, szReplace, nInicio, 0L );
    return retVal;
}

char * Str_tran_from_to( const char * szText, const char * szSeek, const char * szReplace, long nInicio, long nCuenta ){
    char *  retVal = __strtran_item__( szText, szSeek, szReplace, nInicio, nCuenta );
    return retVal;
}

/* GESTION DE CARACTERES EN UN STRING */
// al inicio o al final, devuelve la posición donde cambia un caracter
int Char_posl( const char * cStringBuffer, char cCar ){
   int pos = 0;
   
   char * cString = pop_stack_if_null_noLen(cStringBuffer, "Char_posl","source");
   if ( cString == NULL ) return 0;

   const char * b = cString;
   while ( cCar == *b ) ++b;
   pos = (b - cString) + 1;

   free(cString);

   return pos;
}

int Char_posr( const char * cStringBuffer, char cCar ){
   int pos = 0;

   long i = 0; //(int)strlen(cString)-1;
   char * cString = pop_stack_if_null(cStringBuffer, &i, "Char_posr","source");
   if ( cString == NULL ) return 0;
   --i;

   while( cCar == cString[i] ) --i;
   pos = (int)i+1;

   free(cString);
   return pos;
}

// reduce los carcateres dupicados adyacentes en un solo string.
char * Char_one( const char * pcStringBuffer, const char * pcDeleteSetBuffer ){
   
   long sDeleteSetLen = 0;
   long sStrLen = 0;//strlen( pcString );
   
   char * cString = pop_stack_if_null(pcStringBuffer, &sStrLen, "Char_one","source");
   const char * pcString = cString;
   
   char * pcDeleteSet = pop_stack_if_null(pcDeleteSetBuffer, &sDeleteSetLen, NULL,NULL);

   if( pcDeleteSet == NULL ){
        sDeleteSetLen = 0;
   }

   Str_init(retVal);

   if( sStrLen > 1 )
   {
      const char *pcSub;
      char *pcRet;
      long sRetStrLen = 0;
      char cCurrent = *pcString;

      pcRet = ( char * ) calloc( sStrLen + 10, 1 );
      /// copy first char
      pcRet[sRetStrLen++] = cCurrent;
      for( pcSub = pcString + 1; pcSub < pcString + sStrLen; pcSub++ )
      {
         if( *pcSub != cCurrent )
         {
            cCurrent = *pcSub;
            pcRet[sRetStrLen++] = cCurrent;
         }
         else if( pcDeleteSet != NULL &&
                           !ct_at_exact_forward( pcDeleteSet, sDeleteSetLen,
                                                 pcSub, 1, NULL ) )
         {
            pcRet[sRetStrLen++] = cCurrent;
         }
      }
      Copy( retVal, pcRet );
      free(pcRet);
   }
   else
   {
      // algorithm does nothing to 1-char-strings
      Copy( retVal, pcString );
   }

   free(cString); if(pcDeleteSet != NULL) free(pcDeleteSet);
   if(PILA_GADGET){
      push_stack_str(retVal);
      free(retVal);
      return NULL;
   }

   return retVal;
}

// borra todos los carcateres de STR1 que no estén incluidos en STR2
char * Char_only( const char *pcStringBuffer, const char *pcOnlySetBuffer ){
   long sStrLen = 0;//strlen(pcString);
   long sOnlySetLen = 0;//strlen(pcOnlySet);

   char * pcString = pop_stack_if_null(pcStringBuffer, &sStrLen, "Char_only","source");
   if (pcString==NULL) { return NULL;}
   
   char * pcOnlySet = pop_stack_if_null(pcOnlySetBuffer, &sOnlySetLen, "Char_only","set_data_only");
   if (pcOnlySet==NULL) { free(pcString); return NULL;}

   char *pcRet;
   long sRetStrLen = 0;
   int iShift, iBool;
   const char *pcSub, *pc;

   Str_init(retVal);
      if( sStrLen == 0 || sOnlySetLen == 0 ){
         Let( retVal, "");
         free(pcString);free(pcOnlySet);
         if(PILA_GADGET){
            push_stack_str(retVal);
            free(retVal);
            return NULL;
         }
         
         return retVal;
      }

      iShift = 1;
      
      pcRet = ( char * ) calloc( sStrLen + 10, 1 );

      for( pcSub = pcString; pcSub < pcString + sStrLen + 1 - iShift; pcSub += iShift )
      {
         pc = ct_at_exact_forward( pcOnlySet, sOnlySetLen, pcSub, iShift, NULL );
         iBool = ( ( pc != NULL ) && ( ( ( pc - pcOnlySet ) % iShift ) == 0 ) );

         if( iBool )
         {
            for( pc = pcSub; pc < pcSub + iShift; pc++ )
               pcRet[sRetStrLen++] = *pc;
         }
      }
      // copy last character if string len is odd 
      if( iShift == 2 && sStrLen % 2 == 1 )
      {
         pcRet[sRetStrLen++] = pcString[sStrLen - 1];
      }
      Let( retVal, pcRet );
      free(pcRet);
      free(pcString);free(pcOnlySet);
      if(PILA_GADGET){
          push_stack_str(retVal);
          free(retVal);
          return NULL;
      }

      return retVal;
}

// remueve caracteres desde STR1 indicados en STR2
char * Char_del( const char *pcStringBuff, const char *pcOnlySetBuff ){

   long sStrLen = 0;//strlen(pcString);
   long sOnlySetLen = 0;//strlen(pcOnlySet);

   char * pcString = pop_stack_if_null(pcStringBuff, &sStrLen, "Char_del","source");
   if (pcString==NULL) { return NULL;}

   char * pcOnlySet = pop_stack_if_null(pcOnlySetBuff, &sOnlySetLen, NULL,NULL);
   
   char *pcRet;
   long sRetStrLen = 0;
   int iShift, iBool;
   const char *pcSub, *pc;

   Str_init(retVal);
   
      if( sStrLen == 0 ){
         Let( retVal, "");
         free(pcString); if(pcOnlySet) free(pcOnlySet);
         if(PILA_GADGET){
             push_stack_str(retVal); free(retVal); return NULL;
         }
         return retVal;
      }
      if( sOnlySetLen == 0 ){
         Let( retVal, pcString);
         free(pcString); if(pcOnlySet) free(pcOnlySet);
         if(PILA_GADGET){
             push_stack_str(retVal); free(retVal); return NULL;
         }
         return retVal;
      }
      iShift = 1;

      pcRet = ( char * ) calloc( sStrLen + 10, 1 );

      for( pcSub = pcString; pcSub < pcString + sStrLen + 1 - iShift; pcSub += iShift )
      {
         pc = ct_at_exact_forward( pcOnlySet, sOnlySetLen, pcSub, iShift, NULL );
         iBool = ( ( pc != NULL ) && ( ( ( pc - pcOnlySet ) % iShift ) == 0 ) );

         if( !iBool )
         {
            for( pc = pcSub; pc < pcSub + iShift; pc++ )
               pcRet[sRetStrLen++] = *pc;
         }
      }
      // copy last character if string len is odd
      if( iShift == 2 && sStrLen % 2 == 1 )
      {
         pcRet[sRetStrLen++] = pcString[sStrLen - 1];
      }
      Let( retVal, pcRet);
      free( pcRet );
      free(pcString); if(pcOnlySet) free(pcOnlySet);
      if(PILA_GADGET){
          push_stack_str(retVal); free(retVal); return NULL;
      }
      return retVal;
}

char * Lateral_replace( const char * pcStringBuff, char cSearch, char cReplace, int iSwitch ){

   long sStrLen = 0;//strlen(pcString);
   char * pcString = pop_stack_if_null(pcStringBuff, &sStrLen, "Lateral_replace","source");
   if (pcString==NULL) { return NULL;}
   
   char *pcRet, *pc;
   
   pcRet = ( char * ) calloc( sStrLen + 10, 1 );
   memcpy( pcRet, pcString, sStrLen );

   if( iSwitch != RIGHTREPL )
   {
      pc = pcRet;
      while( *pc == cSearch && pc < pcRet + sStrLen )
      {
         *pc = cReplace;
         pc++;
      }
   }

   if( iSwitch != LEFTREPL )
   {
      pc = pcRet + sStrLen - 1;
      while( *pc == cSearch && pc >= pcRet )
      {
         *pc = cReplace;
         pc--;
      }
   }
   free(pcString);
   if(PILA_GADGET){
      push_stack_str(pcRet); free(pcRet); return NULL;
   }
   return pcRet;
}

size_t Str_len( const char * Buff ){
   return pop_stack_len(Buff, "Str_len","source");
}

/* MASK Y MONEY */
char * Str_mask( const char * numeroBuff, const char * formatoBuff, char * carBuff ) {
   
   long ln = 0;//strlen(numero);
   long lf = 0;//strlen(formato);
   
   char * numero = pop_stack_if_null(numeroBuff, &ln, "Str_mask","source");
   if (numero==NULL) { return NULL;}
   
   char * formato = pop_stack_if_null(formatoBuff, &lf, "Str_mask","format");
   if (formato==NULL) { free(numero);return NULL;}
   
   char * car = pop_stack_if_null_noLen(carBuff, NULL,NULL);
   
   char *buffer, *pBuf;

   pBuf = (char *)calloc(lf+5,1);
   if (pBuf==NULL) return NULL;

   buffer = pBuf;
   int16_t i=lf, k=lf; 

   char c; 
   --lf; --ln; --k;
   while (lf>=0 && ln>=0) {
      c = formato[lf];
      if (c=='#') buffer[k] = numero[ln--]; 
      else buffer[k] = c;
      --k;
      --lf;
   }
   while (lf>=0) {
      c = formato[lf];
      if (*car) {
         if (c=='#') buffer[k] = *car;
         else buffer[k] = c;
      } else {
         buffer[k] = ' ';
      }
      --lf;
      --k;
   }
   buffer[i]='\0';
   
   free(numero);free(formato);if(car) free(car);
   if(PILA_GADGET){
      push_stack_str(buffer); free(buffer); return NULL;
   }
return buffer;
}

/* STRMONEY y FORMATMONEY */
char * Str_money(long double numero, int decimales ){

   char *buffer = (char *)calloc (1024,1); 
   if (buffer==NULL) return NULL;
   char *num = (char *)calloc (1024,1); 
   if (num==NULL) return NULL;
   
   char *buf = buffer;

   int i=0,j=0,swNeg=0;
   if( numero < 0 ) {
      swNeg=1;
      numero *= -1;
   }
   
   int size = sprintf(buf,"%.*Lf",decimales, numero);
   int intSize=size;
   if( decimales>0 ){
      intSize=size-decimales-1;  // longitud entero
   }

   if( swNeg ){  
      num[0] = '-';//'.';
      ++i;
   }
   num[i] = buf[0];
   ++j;++i;
   --intSize;
   
   while( intSize ){
/*      if( buf[j]=='.' ) {
         num[i++] = ',';//DECIMAL_POINT; //buf[j];
         printf("\nPASA 1\n");
         break;
      }else{*/
         if( fmod(intSize,3) )
            num[i++] = buf[j];
         else{
            num[i++] = SEPARATOR_MILLARS;//','; //( char ) SEPARATOR_MILLARS;//',';//;
         //   printf("\nPASA 2\n");
            num[i++] = buf[j];
         }
 //     }
      ++j;
      --intSize;
      --size;
   }
   while( size ){
      if( buf[j]=='.' )
         num[i++] = DECIMAL_POINT;
      else
         num[i++] = buf[j];
      --size;
      ++j;
   }
   free(buffer);
 // completar signo, moneda y pad.  
   num[i]='\0';

   if(PILA_GADGET){
      push_stack_str(num); free(num); return NULL;
   }
   return num;
}

char * Format_money( long double numero, int decimales, int nPad, char relleno, const char * sufijoBuff ){
   
   char * sufijo = pop_stack_if_null_noLen(sufijoBuff, NULL,NULL);
 //  if ( sufijo ){
      char * money = Str_money( numero, decimales );
      if (money==NULL){
          money = pop_stack_hard("Format_money","money");
      }
      if ( money ){
         char * padMoney = __Pad__( money, relleno, nPad, PADL );
         if ( padMoney == NULL ){
            padMoney = pop_stack_hard("Format_money","pad money");
         }
         if ( padMoney ){
            Str_init( retVal )
            
            if( sufijo != NULL ){
               Let(retVal, sufijo );
               Cat(retVal, padMoney );
            }else{
               Let(retVal, padMoney );
            }
            free(money);
            free(padMoney);if(sufijo) free(sufijo);
            if(PILA_GADGET){
               push_stack_str(retVal); free(retVal); return NULL;
            }
            return retVal;
         }else{
            Msg_red("Pad devolvió NULL en Format_money");
         }
      }else{
         Msg_red("No hay memoria para Format_money");
      }
 //  }
   return NULL;
}


/* REGEX - EXPRESIONES REGULARES */

int Regex_compile( const char* cPatternBuff, int nFlags ){
     int error;

     long nLenPat = 0;//strlen( cPattern );
     char * cPattern = pop_stack_if_null(cPatternBuff, &nLenPat, "Regex_compile","pattern");
     if (cPattern==NULL) { return -1;}

     if ( nLenPat ){
        ++__aIndexREGEX__;
        if(__aIndexREGEX__>=TOPE_REGEX){  // buscar alguno que haya sido eliminado
           int i;
           for(i=0;i<TOPE_REGEX;i++){
              if(!__validREGEX__[i]){
                 __aIndexREGEX__=i;
                 break;
              }
           }
        }
        if(__aIndexREGEX__>=0 && __aIndexREGEX__<TOPE_REGEX){
           __validREGEX__[__aIndexREGEX__]=1;
           error = regcomp(&(__aREGEX__[__aIndexREGEX__]), cPattern, nFlags);

           if (error==0) {  // compiló bien. Ahora, a validar!
              free(cPattern);
              return __aIndexREGEX__;

           }else{
              __validREGEX__[__aIndexREGEX__]=0;
              char error_message[MAX_ERROR_MSG];
              char* ERROR = (char*)calloc(MAX_ERROR_MSG,1); 
              regerror (error, &(__aREGEX__[__aIndexREGEX__]), error_message, MAX_ERROR_MSG);
              memcpy(ERROR,"Regex_compile: error en compilacion: ",36);
              memcpy(ERROR + 36,error_message,strlen(error_message));
              Msg_red(ERROR);
              free(ERROR);
           }
        }else{
           Msg_red("Regex_compile : límite de stack de expresiones regulares sobrepasado\n");
        }
     }else{
        Msg_red("Regex_compile : patrón no debe ser nulo\n");
     }
     free(cPattern);
     return -1;
}

void Regex_free( int nIndex ){
   if( (nIndex >= 0 && nIndex < TOPE_REGEX) ){
      if(__validREGEX__[nIndex]){
         regfree(&__aREGEX__[nIndex]);
         __validREGEX__[nIndex]=0;
      }  // no hace nada.
   }else{
      Msg_red("Regex_free : error en índice de compilación\n");
   }
}

int Regex_valid( const char* test_patternBuff, int nIndex, int nFlags ){

      char * test_pattern = pop_stack_if_null_noLen(test_patternBuff, "Regex_valid","source");
      if (test_pattern==NULL) { return -1;}
     
      if( nIndex>=0 && nIndex<=__aIndexREGEX__ ){
      /// verificar indice
         if(__validREGEX__[nIndex]){

            int   error = regexec(&__aREGEX__[nIndex], test_pattern, (size_t) 0, NULL, nFlags);
            if (error == 0) {
                  free(test_pattern);
                  return 1;
            } else if (error == REG_NOMATCH) {
                  free(test_pattern);
                  return 0;
            } else {
                  free(test_pattern);
                  return 0;
            }
         }else{
            Msg_red("Regex_valid : no existe la compilación aludida\n");
         }
      }else{
         Msg_red("Regex_valid : límite de stack de expresiones regulares sobrepasado\n");
      }
      free(test_pattern);
      return -1;
}


RE_MATCH * Regex_match( const char* to_matchBuff, int nIndex, int n_matches, int nFlags ){
      SIZE_MATCH=0;
      char * to_match = pop_stack_if_null_noLen(to_matchBuff, "Regex_match","match");
      if (to_match==NULL) { return NULL;}
      
      if( nIndex>=0 && nIndex<=__aIndexREGEX__ ){
      /// verificar indice
         if(__validREGEX__[nIndex]){

            RE_MATCH * pMatch;
            int swCreaArray=X_TRUE;
            unsigned int newRow=0;
            
            regmatch_t m[n_matches]; // esta estructura es poco manejable.
            
            const char * p = to_match;

            int swBucle=1;
            while (swBucle) {
               int i = 0;
               int nomatch = regexec (&__aREGEX__[nIndex], p, n_matches, m, nFlags);
               //printf("pasa por aqui: %d\n",nomatch);
               if (nomatch) {
                  free(to_match);
                  return pMatch;  // si no encuentra nada, retorna lo que encontró
               }else{
                  for (i = 0; i < n_matches; i++) {
                     //printf("---FOR---pasa por aqui: %d\n",i);
                     
                     int start;
                     int finish;
                     if (m[i].rm_so == -1) {
                        //if(i==0) swBucle=0;
                        break;
                     }
                     start = m[i].rm_so + (p - to_match);
                     finish = m[i].rm_eo + (p - to_match);
                     ///printf("start=%d, finish=%d\n",start,finish);
                     if(finish && start){                        

                        char* buffer = (char*)calloc((finish - start) + 1, 1);
                        sprintf(buffer, "%.*s",(finish - start),to_match + start);
                        
                        if ( swCreaArray ){
                            pMatch = (RE_MATCH *) calloc( 1, sizeof(RE_MATCH));
                            pMatch[0].start  = start+1;
                            pMatch[0].finish = finish;
                            pMatch[0].match  = strdup(buffer);
                            swCreaArray=X_FALSE;
                            ++newRow;
                        }else{
                            pMatch = (RE_MATCH *) realloc( (void *) pMatch, sizeof(RE_MATCH) * (newRow+1));
                            pMatch[ newRow ].start  = start+1;
                            pMatch[ newRow ].finish = finish;
                            pMatch[ newRow ].match  = strdup(buffer);
                            ++newRow;
                        }
                        free(buffer);
                        SIZE_MATCH=newRow;
                     }else{
                        swBucle=0;
                        break;
                     }
                  } /* for */
               }
               p += m[0].rm_eo;
            }  /* while */
            free(to_match);
            if ( SIZE_MATCH ) return pMatch;
            return NULL;
         }else{
            Msg_red("Regex_match : no existe la compilación aludida\n");
         }
      }else{
         Msg_red("Regex_match : límite de stack de expresiones regulares sobrepasado\n");
      }
      free(to_match);
return NULL;
}


