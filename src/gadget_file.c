
/************************************************************************
 *
 *   LIBRERIA DE MANIPULACION DE ARCHIVOS
 *
 ************************************************************************/


/*#ifndef _LIB_GADGET_MAIN_

#ifdef GENLIB_GADGET*/
#include "../include/gadget.h"
/*#else
#include <gadget/gadget.h>
#endif

#endif

#include <gadget/gadget_file.h> */

/* establece token para uso global */
extern char * __TOKEN__;

/* SEARCH */
extern long SIZE_SEARCH;

/* STATFILE Y READLINE */
extern int MAX_LENGTH_READ;

/* ACCESO A STACK DE STRING QUE PERMITE ANIDAMIENTO */
extern int PILA_GADGET;
extern int CONTADOR_PILA;
extern char ** pila_de_trabajo;

/* ARCHIVOS */
/* LOAD, SAVE STRING y FUNCIONES UTILITARIAS */

/* Para que sea rápido, generará un array con la posición de inicio y
   término de cada línea. Usar Get_token() para strings pequeños */
int Count_lines( const char * cStringBuff ){

   char * cString = pop_stack_if_null_noLen(cStringBuff, "Count_lines","string");
   if (cString==NULL) { return 0;}

   const char * tb=cString;
   int nLines=0;
   while(*tb!='\0'){
      if(*tb=='\n'){
         ++nLines;
      }
      ++tb;
   }
   if (*tb=='\0') ++nLines;
   free(cString);
   return nLines;
}

/* No devuelve al stack, sino directamente a una variable */
char * Load_string( const char * szFileBuff ){

   char * szFile = pop_stack_if_null_noLen(szFileBuff, "Load_string","filename");
   if (szFile==NULL) { return NULL;}

   FILE *fp;
   if( (fp=fopen(szFile,"rb") ) != NULL ){
      
      fseek(fp, 0L, SEEK_END);
      long int nFinalPos  = ftell( fp ) ;
      
      rewind( fp );
      fseek( fp, 0L, SEEK_CUR) ;

      char * output = NULL; //(char *)calloc(nFinalPos + 2, 1);
      if(PILA_GADGET){  // trabajo directamente sobre la pila.
         malloc_stack_str(nFinalPos + 2);
         output = STK_STR;
      }else{
         output = (char *) calloc( nFinalPos + 2, 1 );
      }
      if( output ){
         long int i=0;
         char ch;
         while ((ch = fgetc(fp)) != EOF){
            output[i++] = ch;
         }
         output[i] = '\0';
      }else{
         Msg_red("Load_string : no hay memoria para CALLOC\n");
      }
      fclose(fp);
      free(szFile);
      if(PILA_GADGET){
         return NULL;
      }
      return output;
   }else{
      Msg_red("Load_string : archivo no existe o nombre de archivo incorrecto\n");
   }
   free(szFile);
   return NULL;
}

int Save_string( const char * cStringBuff, const char * szFileBuff ){

   char * cString = pop_stack_if_null_noLen(cStringBuff, "Save_string","string");
   if (cString==NULL) { return 0;}

   char * szFile = pop_stack_if_null_noLen(szFileBuff, "Save_string","filename");
   if (szFile==NULL) { free(cString);return 0;}
   
   int sw=1;
   FILE *fp;
   if( (fp = fopen(szFile,"w"))!=NULL ){
      const char * tb = cString;
      while(*tb){
         if(*tb!='\0') fputc(*tb,fp);
         tb++;
      }
   }else {
      Msg_red("Save_string : error en la creación del archivo\n");
      sw=0;
   }
   free(cString);free(szFile);
   fclose(fp);

   return sw;
}

int Append_string( const char * cStringBuff, const char * szFileBuff ){

   char * cString = pop_stack_if_null_noLen(cStringBuff, "Append_string","string");
   if (cString==NULL) { return 0;}

   char * szFile = pop_stack_if_null_noLen(szFileBuff, "Append_string","filename");
   if (szFile==NULL) { free(cString);return 0;}

   int sw=1;
   FILE * fp;
   
   if( (fp = fopen(szFile,"a"))!=NULL ){
      const char * tb = cString;
      while(*tb){
         if(*tb!='\0') fputc(*tb,fp);
         tb++;
      }
   }else {
      Msg_red("Append_string : error en la creación|apertura del archivo\n");
      sw=0;
   }
   free(cString);free(szFile);
   fclose(fp);

return sw;
}

int Exist_file( const char * sFileBuff ){

   char * sFile = pop_stack_if_null_noLen(sFileBuff, "Exist_file","filename");
   if (sFile==NULL) { return 0;}
   
   if( access( sFile, F_OK ) == 0 ) {
      free(sFile);
      return 1;
   }else{
      free(sFile);
      return 0;
   }
}

int Exist_dir( const char * sDirBuff ){

   char * sDir = pop_stack_if_null_noLen(sDirBuff, "Exist_dir","filename");
   if (sDir==NULL) { return 0;}

   struct stat sb;
   int retVal = (stat(sDir, &sb) == 0 && S_ISDIR(sb.st_mode) );
   free(sDir);
   return retVal;
}

/* SYSTEM llamada a sistema con devolucion de resultado */

char * Get_sys( const char * execstrBuff ){

   char * execstr = pop_stack_if_null_noLen(execstrBuff, "Get_sys","argument");
   if (execstr==NULL) { return NULL;}

   int sw=1;

   char * retSys=NULL;
   
  // generar nombre de archivo temporal:
   time_t tiempo;
   srand((unsigned) time(&tiempo));
   
   long numrand = 10000 + rand() % (100000001 - 10000);
   char tmpFile[100];
   int ltmpf = sprintf(tmpFile," > /tmp/tmpmacroMurrayfile%ld.tmp",numrand);
   tmpFile[ltmpf]='\0';
  // procesar:

   long nLen = strlen(execstr);
   char * s = (char*) calloc( nLen + 43, 1 );
   memcpy( s, execstr, nLen );
   memcpy( s + nLen, tmpFile, ltmpf );
   const char * t=s;
   
   int ret = system(t);
   if (WIFSIGNALED(ret) &&
      (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)){
      sw=0;
      Msg_red("Get_sys : llamada a sistema devolvió error (execute)\n");
   }
   free(s);
   if(sw){
      FILE *fp;
      char ch;
      ltmpf = sprintf(tmpFile,"/tmp/tmpmacroMurrayfile%ld.tmp",numrand);
      tmpFile[ltmpf]='\0';
      if( (fp=fopen(tmpFile,"r"))!=NULL ){
         fseek(fp, 0L, SEEK_END);
         long int nFinalPos  = ftell( fp ) ;
      
         rewind( fp );
         fseek( fp, 0L, SEEK_CUR) ;

         char * output = (char *)calloc(nFinalPos + 2, 1);      
         if( output ){
            long int i=0;
            while ((ch = fgetc(fp)) != EOF){
               output[i++] = ch;
            }
            output[i] = '\0';
            const char * cbuffer = output;
            
            retSys = NULL;//(char *) calloc( i+1,1);

            if(PILA_GADGET){  // trabajo directamente sobre la pila.
                malloc_stack_str(i+1);
                retSys = STK_STR;
            }else{
                retSys = (char *) calloc( i+1, 1 );
            } 

            if (retSys==NULL) { Msg_red("Get_sys : no hay memoria disponible (devolution)\n"); }
            else { 
                strcpy( retSys, cbuffer );
            }
            free(output);
         }else{
            Msg_red("Get_sys : no hay memoria disponible (calloc)\n");
         }
         fclose(fp);
         // rm file:
         ltmpf = sprintf(tmpFile,"rm /tmp/tmpmacroMurrayfile%ld.tmp",numrand);
         tmpFile[ltmpf]='\0';
         int ret = system(tmpFile);
         if (WIFSIGNALED(ret) &&
            (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)){
            Msg_red("Get_sys : llamada a sistema devolvió error (rm tempfile)\n");
         }
      }else{
         Msg_red("Get_sys : no se pudo crear archivo temporal\n");
      }
   }
   free(execstr);
   if(PILA_GADGET){
      //push_stack_str(retSys); free(retSys); 
      return NULL;
   }
   return retSys;
}

/* realiza busqueda en archivo usando GREP. NO DEVUELVE A UN STACK */
unsigned int ** Search( const char * cFileBuff, const char * cSearchBuff ){
int sw=1;

   long nLenFile = 0;//strlen(cFile);
   long nLenSear = 0;//strlen(cSearch);

   char * cFile = pop_stack_if_null(cFileBuff, &nLenFile, "Search","filename");
   if (cFile==NULL) { return NULL;}

   char * cSearch = pop_stack_if_null(cSearchBuff, &nLenSear, "Search","match");
   if (cSearch==NULL) { free(cFile);return NULL;}

   unsigned int ** pMatch;
   
  // generar nombre de archivo temporal:
   srand(time(NULL));
   long numrand = 10000 + rand() % (100000001 - 10000);
   char tmpFile[100];
   int ltmpf = sprintf(tmpFile," > /tmp/tmpmSeaMurrfile%ld.tmp",numrand);
   tmpFile[ltmpf]='\0';
      
   char * cLine = (char *) calloc(nLenFile + nLenSear + 100, 1);
   memcpy(cLine, "grep -h -n -b ",14);
   memcpy(cLine + 14, cSearch, nLenSear);
   memset(cLine + 14 + nLenSear, ' ', 1 );
   memcpy(cLine + 15 + nLenSear, cFile, nLenFile);

   memcpy(cLine + 15 + nLenSear + nLenFile, tmpFile, ltmpf); 

   const char * t=cLine;

   int ret = system(t);
   if (WIFSIGNALED(ret) &&
      (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)){
      Msg_red("Search : llamada a sistema devolvió error (GREP)\n");
      sw=0;
   }

   free(cLine);
   
   if( sw ){
      FILE *fp;
      
      ltmpf = sprintf(tmpFile,"/tmp/tmpmSeaMurrfile%ld.tmp",numrand);
      tmpFile[ltmpf]='\0';
      if( (fp=fopen(tmpFile,"r"))!=NULL ){
         unsigned int linea=0,noffset=0;
         unsigned int newRow=0;
         char ch;
         short swCreaArray = X_TRUE;
         SIZE_SEARCH = 0;
         while ((ch = fgetc(fp)) != EOF){
            // busca numero de linea
            linea=0; noffset=0;
            while(ch!=':'){
               linea = (linea * 10) + (ch - '0');
               ch = fgetc(fp);    // avanzo un caracter.
            }
            ch = fgetc(fp);  // omite ':'
            // busca desplazamiento
            while(ch!=':'){
               noffset = (noffset * 10) + (ch - '0');
               ch = fgetc(fp);    // avanzo un caracter.
            }
            ch = fgetc(fp);  // omite ':'
            if ( swCreaArray ){
               
               pMatch = (unsigned int **) calloc( 1, sizeof(unsigned int*));
               pMatch[ 0 ] = (unsigned int *) calloc( 2, sizeof(unsigned int) );
               pMatch[ 0 ][0] = linea;
               pMatch[ 0 ][1] = noffset;
               swCreaArray=X_FALSE;
               ++newRow;
            }else{
               
               pMatch = (unsigned int **) realloc( (void *) pMatch, sizeof(unsigned int *)* (newRow+1));
               pMatch[ newRow ] = (unsigned int *) malloc( 2 * sizeof(unsigned int) );
               pMatch[ newRow ][0] = linea;
               pMatch[ newRow ][1] = noffset;
               ++newRow;
            }
            // resto de línea hasta '\n'
            while(ch!='\n') ch = fgetc(fp);
         }
         SIZE_SEARCH = newRow;

         fclose(fp);
        // rm file:
         int ltmpf = sprintf(tmpFile,"rm /tmp/tmpmSeaMurrfile%ld.tmp",numrand);
         tmpFile[ltmpf]='\0';
         int ret = system(tmpFile);
         if (WIFSIGNALED(ret) &&
            (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)){
            Msg_yellow("Search : llamada a sistema devolvió error (rm tempfile)\n");
         }
         if( SIZE_SEARCH ) {
             free(cFile);free(cSearch);
             return pMatch;
         }

      }else{
         Msg_red("Search : no se pudo crear archivo temporal\n");
      }
   }
   free(cFile);free(cSearch);
   return NULL;
}

int File_size(int fd){
  int fsize = Set_EOF(fd);
  Set_BOF(fd);
  return fsize;
}


char * Str_file_error(int nError){
   char * buffer = ( char * ) calloc( 50, 1 );
   switch( nError ){
      case 0:{ memcpy( buffer,"Successful", 10); buffer[10]='\0'; break; }
      case 2:{ memcpy( buffer,"File not found", 14 ); buffer[14]='\0'; break; }
      case 3:{ memcpy( buffer,"Path not found", 14 ); buffer[14]='\0'; break; }
      case 4:{ memcpy( buffer,"Too many files open",19 ); buffer[19]='\0'; break; }
      case 5:{ memcpy( buffer,"Access denied", 13 ); buffer[13]='\0'; break; }
      case 6:{ memcpy( buffer,"Invalid handle", 14 ); buffer[14]='\0'; break; }
      case 8:{ memcpy( buffer,"Insufficient memory", 19 ); buffer[19]='\0'; break; }
      case 15:{ memcpy( buffer,"Invalid drive specified", 23 ); buffer[23]='\0'; break; }
      case 19:{ memcpy( buffer,"Attempted to write to a write-protected disk", 44 ); buffer[44]='\0'; break; }
      case 21:{ memcpy( buffer,"Drive not ready", 15 ); buffer[15]='\0'; break; }
      case 23:{ memcpy( buffer,"Data CRC error", 14 ); buffer[14]='\0'; break; }
      case 29:{ memcpy( buffer,"Write fault", 11 ); buffer[11]='\0'; break; }
      case 30:{ memcpy( buffer,"Read fault", 10 ); buffer[10]='\0'; break; }
      case 32:{ memcpy( buffer,"Sharing violation", 17 ); buffer[17]='\0'; break; }
      case 33:{ memcpy( buffer,"Lock Violation", 14 ); buffer[14]='\0'; break; }
   }
   if(PILA_GADGET){
      push_stack_str(buffer); free(buffer); return NULL;
   }
   return buffer;
}

int Eof( int fhnd ){
   long nSavePos   = lseek( fhnd , 0, 1 ) ;
   long nFinalPos  = lseek( fhnd , 0, 2 ) ;
   int nEof = 0;
   if ( nSavePos >= nFinalPos ) nEof=1;
   nSavePos   = lseek( fhnd , nSavePos, 0 ) ;
   return nEof;
}

int Write_string( int hfnd, const char * toWriteBuff ) {
   int nWriteS=0;
   //long nLen = strlen(toWrite);
   long nLen=0;
   char * toWrite = pop_stack_if_null(toWriteBuff, &nLen, "Write_string","string");
   if (toWrite==NULL) { return 0;}
   
   nWriteS = write( hfnd, toWrite, nLen );
   if(nWriteS<=0){
       Msg_red("Write_string : escritura en archivo, fallida\n");
   }
   free(toWrite);
   return nWriteS;
}

int Write_line( int hfnd, const char * toWriteBuff ) {
   int nWriteS=0;
   long nLen=0;
   
   char * buffer=pop_stack_if_null(toWriteBuff, &nLen, "Write_line","string");
   if (buffer==NULL) { return 0;}
      
   nWriteS = write( hfnd, (const char*)buffer/*toWrite*/, nLen );
   if(nWriteS<=0){
       Msg_red("Write_line : escritura en archivo, fallida\n");
   }
   nWriteS = write( hfnd, "\n", 1 );
   if(nWriteS<=0){
       Msg_red("Write_line : escritura (EOL) en archivo, fallida\n");
   }
   free(buffer);
   return nWriteS;
}

char * Read_string( int fhnd, int nToRead ){
  /* obtener total de caracteres del archivo */
   long nSavePos   = lseek( fhnd , 0, 1 ) ;
   long nFinalPos  = lseek( fhnd , 0, 2 ) ;
        nSavePos   = lseek( fhnd , nSavePos, 0 ) ;
   
   if( nToRead + nSavePos > nFinalPos ) 
      nToRead -= ( nToRead + nSavePos ) - nFinalPos;
   
   if(nSavePos>nFinalPos){
      Msg_red("Read_string : lectura fallida (overflow)\n");
      return NULL;
   }
   char * buffer = ( char * ) calloc( nToRead + 1, 1 ); 
   long nRead;

   nRead = read( fhnd, buffer, nToRead );
   if( nRead == -1 ){
      Msg_red("Read_string : error leyendo el archivo (¿archivo corrupto o sin permisos?)\n");
      free(buffer);
      return NULL;
   }

   long nLen;

   buffer[ nToRead ] = '\0';
   nLen = strlen( buffer );
   // calcula nueva posición.
   nLen++;
   nSavePos = lseek( fhnd , nSavePos + nLen, 0 ) ;
   //if(PILA_GADGET){
   Item_return_release(buffer);
   //}
   return buffer;
}

/* cargar la siguiente linea. se complementa con SEARCH */

char * Read_line( int fhnd ){

  /* obtener total de caracteres del archivo */
   long nSavePos   = lseek( fhnd , 0, 1 ) ;
   long nFinalPos  = lseek( fhnd , 0, 2 ) ;
        nSavePos   = lseek( fhnd , nSavePos, 0 ) ;

   long nToRead = MAX_LENGTH_READ; 
   
   if( nToRead + nSavePos > nFinalPos ) 
      nToRead -= ( nToRead + nSavePos ) - nFinalPos;
   
   if(nSavePos>nFinalPos){
      Msg_red("Read_line : lectura fallida (overflow)\n");
      return NULL;
   }
   char * buffer = ( char * ) calloc( nToRead + 1, 1 ); 
   long nRead=0;

   nRead = read( fhnd, buffer, nToRead );
   if( nRead == -1 ){
      Msg_red("Read_line : error leyendo el archivo (¿archivo corrupto o sin permisos?)\n");
      free(buffer);
      return NULL;
   }
  // ajuste de datos leidos para ajustar LSEEK64 
   long cbuf = 0;
   while( cbuf<=nToRead ){
      if(buffer[cbuf]!='\n') ++cbuf;
      else break;
   }
  //
   long nLen;

   if( cbuf<=nToRead ){  // encontró un '\n'
      buffer[ cbuf ] = '\0';
   }else{     // no encontró '\n'
      buffer[ nToRead ] = '\0';
   }
   nLen = strlen( buffer );
   // calcula nueva posición.
   nLen++;  // se salta '\n' hipotetico.
   nSavePos = lseek( fhnd , nSavePos + nLen, 0 ) ;
   
   //if(PILA_GADGET){
   Item_return_release(buffer);
   //}
   return buffer;
}

F_STAT Stat_file( const char * pFileBuff ){

      F_STAT  dataFile;
      dataFile.total_lines = 0;
      dataFile.size = 0;
      dataFile.max_line_long = 0;
      dataFile.max_tokens_per_line = 0;
      dataFile.is_matrix = 0;
      
      char * pFile = pop_stack_if_null_noLen(pFileBuff, "Stat_file","filename");
      if (pFile==NULL) { return dataFile;}

      const char * pSep = NULL;
      if(__TOKEN__) pSep = __TOKEN__; else pSep=",";
      
      char cSep = pSep[0];
      FILE *fp;
      int nLin=0,nLong=0,noldLong=0;
      long nTotCar=0;
      int sw_Enter=0,sw_Car=0, nTokens=0, maxTokens=0, antChar=0; //, swFirstLine=1;
      char ch;
      short swEsCuadrada=1;

      
      
      fp=fopen(pFile,"r");
      if (fp!=NULL){
         nLin = 0;
         while ((ch = fgetc(fp)) != EOF && swEsCuadrada){
            if (ch == '\n'){
               sw_Enter=1;
               sw_Car=0;
               //swFirstLine=0;
               nLin++;
               if (noldLong < nLong) { // longitud máxima de la línea
                  noldLong = nLong;
               }
               if( antChar != cSep )
                   ++nTokens;
               ///printf(" nTokens = %d, maxTokens = %d\n",nTokens, maxTokens);
               if(nTokens > maxTokens){
                  if(maxTokens > 0) { 
                     Msg_amberf("Stat_file : línea %d tiene más tokens de lo calculado hasta aquí\n",nLin);
                     swEsCuadrada=0;
                  }
                  maxTokens = nTokens;
                  
               }else if(nTokens < maxTokens){
                  Msg_amberf("Stat_file : línea %d tiene menos tokens de lo calculado hasta aquí\n",nLin);
                  Msg_yellow("(Última línea no debe ser '\\n')");
                  swEsCuadrada=0;
               }
               nTokens=0;
              // printf(" ---> NEW maxTokens = %d\n",maxTokens);
               nLong=0;
            }else{
              // if( swFirstLine ) 
               antChar=ch;
               if( cSep == ch ){
                   ++nTokens;
                   if ((ch = fgetc(fp)) != EOF){
                       if( ch == '\n' ){
                           --nTokens;
                       }
                   }
                   ungetc( ch, fp );
               }
               sw_Enter=0;
               sw_Car=1;
               nLong++;
            }
            nTotCar++;
         }
         fclose(fp);
         // suma 1 a nToken, por el último que no leyó:
         //nTokens++;
         //++maxTokens;
         if(sw_Enter==0 && sw_Car==1)
           ++nLin;
         if(nLong > noldLong) noldLong = nLong;
        /* prepare data */
         dataFile.total_lines = nLin;
         dataFile.size = nTotCar;
         dataFile.max_line_long = noldLong;
         dataFile.max_tokens_per_line = maxTokens;
         dataFile.is_matrix = swEsCuadrada;
      }else{
         Msg_red("Stat_file : file open error\n");
         dataFile.total_lines = 0;
         dataFile.size = 0;
         dataFile.max_line_long = 0;
         dataFile.max_tokens_per_line = 0;
         dataFile.is_matrix = 0;
      }
      free(pFile);
      return dataFile;
}

