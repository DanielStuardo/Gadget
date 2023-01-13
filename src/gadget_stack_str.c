
/************************************************************************
 *
 *            LIBRERIA DE AACESO AL STACK DE STRINGS
 *
 ************************************************************************/
 /*
#ifndef _LIB_GADGET_MAIN_

#ifdef GENLIB_GADGET */
#include "../include/gadget.h"

/*#else
#include <gadget/gadget.h>
#endif

#endif

#include <gadget/gadget_stack_str.h>*/

extern int PILA_GADGET;
extern int CONTADOR_PILA;
extern char ** pila_de_trabajo;


/************************************************************************
 *
 *   LIBRERIA DE STACK DE STRING, PARA REALIZAR ANIDAMIENTO DE FUNCIONES
 *   DE CADENA.
 *
 ************************************************************************/


char * pop_stack_if_null_noLen(const char *cBuffer, const char *msg, 
                         const char *sub_msg){
   char * retValue=NULL;
   if( cBuffer ){
       int len = strlen(cBuffer);
       retValue = (char *)calloc( len+1,1);
       memcpy( retValue, cBuffer, len );
       //retValue = (char *)calloc( strlen(cBuffer)+1,1);
       //strcpy( retValue, cBuffer );
   }else{
       if(CONTADOR_PILA>=0){
          int len = strlen( pila_de_trabajo[CONTADOR_PILA]);
          retValue = (char *)calloc( len+1,1);
          memcpy( retValue, pila_de_trabajo[CONTADOR_PILA], len );
          //retValue = (char *)calloc( strlen( pila_de_trabajo[CONTADOR_PILA])+1,1);
          //strcpy( retValue, pila_de_trabajo[CONTADOR_PILA] );
          CONTADOR_PILA--;
       }else{
          if( msg ) {Msg_redf("%s : argumento NULL no esperado '%s'\n",msg,sub_msg);}
          return NULL;
       }
   }
   return retValue;
}

size_t pop_stack_len(const char * cBuffer, const char *msg, const char *sub_msg){
   if(cBuffer){
       return strlen(cBuffer);
   }else{
       if(CONTADOR_PILA>=0){
            size_t retVal = strlen( pila_de_trabajo[CONTADOR_PILA] );
            CONTADOR_PILA--;
            return retVal;
       }else{
            if( msg ) {Msg_redf("%s : argumento NULL no esperado '%s'\n",msg,sub_msg);}
            return 0;
       }
   }
}

char * pop_stack_if_null(const char *cBuffer, long * Len, const char *msg, 
                         const char *sub_msg){
   char * retValue=NULL;
   if( cBuffer ){
       *Len = strlen(cBuffer);
       retValue = (char *)calloc( *Len+1,1);
       //strcpy( retValue, cBuffer );
       memcpy( retValue, cBuffer, *Len );
   }else{
       if(CONTADOR_PILA>=0){
          *Len = strlen( pila_de_trabajo[CONTADOR_PILA] );
          retValue = (char *)calloc( *Len+1,1);
          //strcpy( retValue, pila_de_trabajo[CONTADOR_PILA] );
          memcpy( retValue, pila_de_trabajo[CONTADOR_PILA], *Len );
          CONTADOR_PILA--;
       }else{
          if( msg ) {Msg_redf("%s : argumento NULL no esperado '%s'\n",msg,sub_msg);}
          return NULL;
       }
   }
   return retValue;
}

char * pop_stack_hard(const char *msg, const char *sub_msg){
   char * line=NULL;
   if(CONTADOR_PILA>=0){
       int len = strlen( pila_de_trabajo[CONTADOR_PILA] );
       line = (char *)calloc( len+1,1);
       //strcpy( line, pila_de_trabajo[CONTADOR_PILA] );
       memcpy( line, pila_de_trabajo[CONTADOR_PILA], len );
       CONTADOR_PILA--;
       return line;
   }else{
       Msg_redf("%s : argumento NULL no esperado '%s'\n",msg,sub_msg);
       return NULL;
   }
}

void malloc_stack_str(int nLen){
   if( pila_de_trabajo[++CONTADOR_PILA]) free(pila_de_trabajo[CONTADOR_PILA]);
   pila_de_trabajo[CONTADOR_PILA] = calloc( nLen+1, 1 );
}

void push_stack_str(const char * cString){
   if( pila_de_trabajo[++CONTADOR_PILA]) free(pila_de_trabajo[CONTADOR_PILA]);
   int len = strlen(cString);
   pila_de_trabajo[CONTADOR_PILA] = calloc( len+1, 1 );
   memcpy( pila_de_trabajo[CONTADOR_PILA], (const char *)cString, len );
   //pila_de_trabajo[CONTADOR_PILA] = calloc( strlen(cString)+1, 1 );
   //strcpy( pila_de_trabajo[CONTADOR_PILA], (const char *)cString );
}

