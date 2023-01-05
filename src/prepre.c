

#include <gadget/gadget.h>

/* pre-pre-procesa un archivo C antes de compilar :

   prepre archivo.c > /tmp/nombre_3284384.tmp.c
   if [ ?@ ]
       gcc /tmp/nombre_3284384.tmp.c -o archivo -lmask...
       if[ !]
          error!
*/

LIB_GADGET_START

int retVal=0;
int swHayQueSaltar=0;
int cntNumLine=0;

int Busca_New_Array(int, int);//, char *);
int Busca_Array(int, int, char *, int);
void Busco_String(int, char *);
int Busca_Declare_String(int, int);
int Busca_Free_Secure(int,int,int);
int Busca_Rangos(int,int, int);
int Busca_Cadena_Sys(int, int, char *);
int Busca_At(int,int,int);
int Busca_Print(int,int);
int Busca_For_Items(int,int,int);
int Busca_Iterador_UP(int fd,int numLine);
int Busca_Iterador_DOWN(int fd,int numLine);
int Busca_Cell(int fd,int numLine,int tipo);
int Busca_nombre_all_range_for(int fd, int numLine, int);
int Busca_put_objects(int fd,int numLine,int tipo);
int Busca_array_mt(int fd,int numLine,int tipo);
//int Busca_New_Array_From(int,int,char *);

void Descarta_cometario_linea(int fd, int *numLine, char *buffer){
   char tbuffer[2];
   tbuffer[0] = buffer[0]; 
   tbuffer[1]='\0';
   while( !Eof(fd) && tbuffer[0]!='\n' ){
       read( fd, tbuffer, 1 );
   }
   printf("%s",tbuffer); // imprime el salto de linea
   ++*numLine;
}

void Descarta_comentario_bloque(int fd,int *numLine, char *buffer){

   char asterisc = 0;
   while( !Eof(fd) ){
       read( fd, buffer, 1 );
       if(buffer[0]=='\n'){
          // ++ *numLine;
           ++ cntNumLine;
           swHayQueSaltar=1;
       }else if( buffer[0]=='/' && asterisc == '*' ){
           break;
       }else if(buffer[0]=='*'){
           read( fd, buffer, 1 );
           if(buffer[0]=='/'){
               break;
           }
           asterisc = '*';
       }else{
           asterisc = 0;
       }
   }
}

char * Busca_Nombre(int fd, char *buffer, int numLine){
   Str_init(tipo); tipo=Space(25);
   tipo[0]=buffer[0];
   
   char tbuffer[2];
   tbuffer[0] = buffer[0];
   tbuffer[1] = '\0';
   
   int c=1;
   int swFoundRem = 0;
   while( ! Eof(fd) && c<25 ){
      int nRead = read( fd, buffer, 1 );
      if( nRead > 0 ){
         if( buffer[0]=='/' ){  // cpomentario de bloque, no acepto línea //
             tbuffer[0] = buffer[0]; 
             read( fd, buffer, 1 );
             if(buffer[0]=='*'){
                 Descarta_comentario_bloque(fd, &numLine, buffer);
                 swFoundRem = 1;
                 continue;
             }else if(buffer[0]=='/'){  // 
                 Msg_redf("\nSímbolo:No acepto comentarios de línea en esta parte, en línea %d 😝\n",numLine);
             }else{ // puede ser otra cosa, y es mejor dejarlo pasar
                 tipo[c++] = tbuffer[0];
                 ///tipo[c++] = tbuffer[0];
                 break;
             }
         }
         if ( isalnum(buffer[0]) && buffer[0]!=' ' && buffer[0]!=';'){
            tipo[c++] = buffer[0];
            swFoundRem = 0;
         }else {
            if( !swFoundRem )
                break;
         }
      }else {
         Msg_redf("\nSímbolo:Problemas con la lectura del archivo, en línea %d 😝\n",numLine);
         retVal=1;
         break;
      }
   }
   tipo[c++]=buffer[0];
   tipo[c]='\0';
   Get_fn_let( tipo, __Ltrim__(tipo)); //, strlen(tipo)));
   return tipo;
}

Main
   
   Get_arg_str(file,1); /* 0 = nombre del archivo .c */
///   printf("Archivo: %s\n",file);

   int fd;
   char oldbuffer[2];
   oldbuffer[0]=' ';
   oldbuffer[1] = '\0';
   if( (fd = open( file, O_RDONLY )) ){
      //SetMaxReadLine(1024);
      int numLine=1;
      while( ! Eof(fd) && !retVal ){
         char buffer[2];
         read( fd, buffer, 1 );
         if (buffer[0]==34){ // es un string: debo saltarlo
            Busco_String(fd, buffer);

         }else if( buffer[0]=='/' ){  // puede ser un comentario.
            char tbuffer[2];
            tbuffer[0] = buffer[0];
            tbuffer[1] = '\0';
            read( fd, buffer, 1 );
            if(buffer[0]=='/'){
               Descarta_cometario_linea(fd,&numLine,buffer);
            }else if(buffer[0]=='*'){
              // printf("Numline antes = %d\n",numLine);
               Descarta_comentario_bloque(fd,&numLine,buffer);
              // printf("Numline despu = %d\n",numLine);
            }else{
               printf("%c%c",tbuffer[0],buffer[0]);
            }
         }else if( buffer[0]=='\n' ) {
            if( swHayQueSaltar ){
                Str_init(salta);
                salta = Replicate("\n",cntNumLine);
                printf("%s",salta);
                Free_secure(salta);
                numLine += cntNumLine;
                swHayQueSaltar=0;
                cntNumLine=0;
            }//else{
            ++numLine;
            printf("%c",buffer[0]);
           // }
         }else if( buffer[0]=='N'){  // ver si es "New Array"
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo,"New ")==0 ){
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);
                if( strcmp(tipo1,"array ")==0 ){
                    retVal = Busca_New_Array(fd,numLine);//,buffer);
                
                }else if( strcmp(tipo1,"multitype ")==0 || strcmp(tipo1,"mt ")==0 ){
                    retVal = Busca_array_mt(fd,numLine, 0);
                
                }else if( strcmp(tipo1,"object ")==0 || strcmp(tipo1,"objects ")==0 ||
                          strcmp(tipo1,"objs ")==0 || strcmp(tipo1,"obj ")==0){
                    retVal = Busca_array_mt(fd,numLine, 0);
                    
                }else{
                    printf("%s%s",tipo,tipo1);
                }
                Free_secure(tipo1);
            }else{
               printf("%s",tipo);
            }
            Free_secure(tipo);

         }else if( buffer[0]=='A'){  // ver si es "Array"
            //  Array x,y as int(n); => Dim(n); asArray(f,int);
            if( oldbuffer[0]==' '){
                Str_init(tipo);
                tipo = Busca_Nombre(fd,buffer,numLine);
                ///printf("AT? = %s\n",tipo);
                if( strcmp(tipo,"Array ")==0 ){
                    retVal = Busca_Array(fd,numLine,buffer,0);
                }else if( strcmp(tipo,"At ")==0 ){
                    retVal = Busca_At(fd,numLine,0);
                }else if( strcmp(tipo,"Atrow ")==0 ){
                    retVal = Busca_At(fd,numLine,1);
                }else if( strcmp(tipo,"Atcol ")==0 ){
                    retVal = Busca_At(fd,numLine,2);
                }else if( strcmp(tipo,"All ")==0 ){
                    Str_init(tipo1);
                    tipo1 = Busca_Nombre(fd,buffer,numLine);
                    if( strcmp(tipo1,"range ")==0 ){
                        Str_init(tipo2);
                        tipo2 = Busca_Nombre(fd,buffer,numLine);
                        if( strcmp(tipo2,"for ")==0 ){  // ya está!
                            retVal = Busca_nombre_all_range_for(fd,numLine,1);
                            Free_secure(tipo1);Free_secure(tipo2);//Free_secure(tipo3);
                        }else if( strcmp(tipo2,"ptr ")==0 ){  // ya está!
                            retVal = Busca_nombre_all_range_for(fd,numLine,0);
                            Free_secure(tipo1);Free_secure(tipo2);//Free_secure(tipo3);
                        }else{
                            printf("%s%s%s",tipo,tipo1,tipo2);
                            Free_secure(tipo1);Free_secure(tipo2);
                        }
                    }else{
                        printf("%s%s",tipo,tipo1);
                        Free_secure(tipo1);
                    }
                }else{
                    printf("%s",tipo);
                }
                Free_secure(tipo);
            }else{
                printf("%c",buffer[0]);
            }
         
   /*      }else if( buffer[0]=='R' ){
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo, "ROWS ")==0 ){
                retVal = Busca_Rangos(fd,numLine,0);
            }else{
                printf("%s",tipo);
            }
            Free_secure(tipo);

         }else if( buffer[0]=='C' ){
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo, "COLS ")==0 ){
                retVal = Busca_Rangos(fd,numLine,1);
            }else if( strcmp(tipo, "Clear ")==0 ){
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);

                if( strcmp(tipo1, "Interval;")==0 || strcmp(tipo1, "Interval ")==0){
                    printf("ClearIntv;");
                }
                Free_secure(tipo1);
            }else{
                printf("%s",tipo);
            }
            Free_secure(tipo);
*/
         }else if( buffer[0]=='$' ){
            retVal = Busca_Cell(fd,numLine,1);  // 1=normal
         
         }else if( buffer[0]=='@' ){ 
            retVal = Busca_Cell(fd,numLine,0);  // 0=ptr
            
         }else if( buffer[0]=='I' ){
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo, "Iterator ")==0 ){
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);
                if( strcmp(tipo1, "up ")==0 ){
                    retVal = Busca_Iterador_UP(fd,numLine);
                }else if (strcmp(tipo1, "down ")==0 ){
                    retVal = Busca_Iterador_DOWN(fd,numLine);
                }else{
                    printf("%s%s",tipo,tipo1);
                    Free_secure(tipo1);
                }
            }else{
                printf("%s",tipo);
            }
            Free_secure(tipo);
            
         }else if( buffer[0]=='P' ){
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo, "Put ")==0 ){
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);
                if( strcmp(tipo1, "object ")==0 || strcmp(tipo1, "objects ")==0 ){
                    retVal = Busca_put_objects(fd,numLine,0);
                }else{
                    printf("%s%s",tipo, tipo1);
                    Free_secure(tipo1);
                }
            }else if( strcmp(tipo, "Print ")==0 ){
                retVal = Busca_Print(fd,numLine);
            }else{
                printf("%s",tipo);
            }
            Free_secure(tipo);

       /*  }else if( buffer[0]=='V' ){
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo, "VECT ")==0 ){
                retVal = Busca_Rangos(fd,numLine,3);
            }else{
                printf("%s",tipo);
            }
            Free_secure(tipo);
*/
         }else if( buffer[0]=='F' ){  // FILL, Free, Fxxx
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo,"Fill ") == 0) {
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);
                if( strcmp(tipo1,"array ")==0 ){
                    retVal = Busca_Array(fd,numLine,buffer,1);
                }else{
                    printf("%s",tipo);
                    printf("%s",tipo1);
                }
                Free_secure(tipo1);
                ///retVal = Busca_Array(fd,numLine,buffer,1);

            }else if( strcmp(tipo,"From ") == 0) {  // creacion de array desde otro, cambiando el tipo
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);   // obtiene un array
                Str_init(tipo2);
                tipo2 = Busca_Nombre(fd,buffer,numLine);   // busca "new"
                if( strcmp(tipo2,"new ")==0 ){
                  //  retVal = Busca_New_Array_From(fd,numLine,tipo1);
                }else{
                    printf("%s",tipo);
                    printf("%s",tipo1);
                    printf("%s",tipo2);
                }
                Free_secure(tipo1);
                Free_secure(tipo2);
            }else if( strcmp(tipo,"For ") == 0) {  // Ciclos For especiales:
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);
                if( strcmp(tipo1,"items ")==0 ){   // For Items var in w do => ForItems( _I_, _X_ )
                    retVal = Busca_For_Items(fd,numLine,0);
                }else if( strcmp(tipo1,"each ")==0 ){
                    Str_init(tipo2);
                    tipo2 = Busca_Nombre(fd,buffer,numLine);
                    if( strcmp(tipo2,"item ")==0 ){
                       retVal = Busca_For_Items(fd,numLine,1);
                    }else if( strcmp(tipo2,"token ")==0 ){
                       retVal = Busca_For_Items(fd,numLine,2);

                    }else if( strcmp(tipo2,"founded ")==0 ){
                       retVal = Busca_For_Items(fd,numLine,3);
                    }else if( strcmp(tipo2,"revfounded ")==0 ){
                       retVal = Busca_For_Items(fd,numLine,4);
                    }else if( strcmp(tipo2,"match ")==0 ){
                       retVal = Busca_For_Items(fd,numLine,5);

                    }else{
                       printf("%s",tipo);
                       printf("%s",tipo1);
                       printf("%s",tipo2);
                    }
                    Free_secure(tipo2);
                }else{
                    printf("%s",tipo);
                    printf("%s",tipo1);
                }
                Free_secure(tipo1);

            }else if( strcmp(tipo,"Free ") == 0) {
                // free todo!!
                Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);
                ///printf("PASA: %s\n",tipo1);
                if( strcmp( tipo1,"secure ")==0 ){
                    retVal = Busca_Free_Secure(fd,numLine,0);
                }else if( strcmp( tipo1,"array ")==0 ){
                    
                    retVal = Busca_Free_Secure(fd,numLine,1);
                }else if(  strcmp( tipo1,"multitype ")==0 || strcmp( tipo1,"mt ")==0){
                    retVal = Busca_Free_Secure(fd,numLine,6);
                
                }else if(  strcmp( tipo1,"object ")==0 || strcmp( tipo1,"objects ")==0 ||strcmp( tipo1,"obj ")==0 ){
                    retVal = Busca_Free_Secure(fd,numLine,6);

                }else if(  strcmp( tipo1,"video ")==0 || strcmp( tipo1,"videos ")==0 ){
                    retVal = Busca_Free_Secure(fd,numLine,7);
                }else if(  strcmp( tipo1,"pobject ")==0 || strcmp( tipo1,"pobjects ")==0 ||strcmp( tipo1,"pobj ")==0 ){
                    retVal = Busca_Free_Secure(fd,numLine,8);
                    
                }else if( strcmp( tipo1,"str ")==0 ){
                    Str_init(tipo2);
                    tipo2 = Busca_Nombre(fd,buffer,numLine);
                    if( strcmp(tipo2,"array ")==0 ){
                       retVal = Busca_Free_Secure(fd,numLine,2);
                    }else{
                       printf("%s",tipo);
                       printf("%s",tipo1);
                       printf("%s",tipo2);
                    }
                    Free_secure(tipo2);
                }else if( strcmp( tipo1,"search ")==0 ){  // 2 args
                    retVal = Busca_At(fd,numLine,3);
                }else if( strcmp( tipo1,"stat ")==0 ){   // 1 arg
                    retVal = Busca_Free_Secure(fd,numLine,3);
                }else if( strcmp( tipo1,"tag ")==0 ){   // 1 arg
                    retVal = Busca_Free_Secure(fd,numLine,4);
                }else if( strcmp( tipo1,"match ")==0 ){  // 2 args
                    retVal = Busca_At(fd,numLine,4);
                }else if( strcmp( tipo1,"regex ")==0 ){  // 2 args
                    retVal = Busca_Free_Secure(fd,numLine,5);
                }else{
                    printf("%s",tipo);
                    printf("%s",tipo1);
                }
                Free_secure(tipo1);
            }else{
                printf("%s",tipo);
            }
            Free_secure(tipo);
         
         }else if( buffer[0]=='R'){
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo,"Range ") == 0) {
               Str_init(tipo1);
                tipo1 = Busca_Nombre(fd,buffer,numLine);
                if( strcmp( tipo1,"for ")==0 ){
                    retVal = Busca_Rangos(fd,numLine,1);
                }else if( strcmp( tipo1,"ptr ")==0 ){
                    retVal = Busca_Rangos(fd,numLine,0);
                }else{
                    printf("%s",tipo);
                    printf("%s",tipo1);
                }
                Free_secure(tipo1);
            }else{
                printf("%s",tipo);
            }
            Free_secure(tipo);
                    
         }else if( buffer[0]=='S'){  // busco por String. uede ser Set!
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo,"String ") == 0) {
               retVal = Busca_Declare_String(fd,numLine);
/*            }else if( strcmp( tipo, "Set")==0 ){
               Str_init(tipo1);
               tipo1 = Busca_Nombre(fd,buffer,numLine);
               ///Get_fn_let( tipo, Alltrim(tipo));
               if( strcmp( tipo1,"Multipass;")==0 ){
                  printf("SetMultipass;");
               }else{
                  printf("%s",tipo);
                  printf("%s",tipo1);
               }
               Free_secure(tipo1);*/
            }else{
               /* si no es ninguna de las anteriores, solo imprime */
               printf("%s",tipo);
            }
            Free_secure(tipo);
/*         }else if ( buffer[0]=='U' ){   // Using [x,y,z,w]
            Str_init(tipo);
            tipo = Busca_Nombre(fd,buffer,numLine);
            if( strcmp(tipo,"Using ") == 0) {
               retVal = Busca_Using_Compute_For(fd,numLine);
            }else{
               // si no es ninguna de las anteriores, solo imprime
               printf("%s",tipo);
            }  */
         }else if ( buffer[0]=='`' ){  // GetSys asignable:
            retVal = Busca_Cadena_Sys(fd, numLine,buffer);
         }else{
            printf("%c",buffer[0]);
         }
         oldbuffer[0]=buffer[0];
      }  // while( ! Eof(fd) && !retVal )
      close(fd);
   }else{
      Msg_redf("\nArchivo '%s' no ha podido ser abierto 😝\n", file);
   }
   Free_secure(file);

Return (retVal);

void Busco_String(int fd, char * buffer){
   while( ! Eof(fd) ){
      printf("%c",buffer[0]);
      char buffBefore = buffer[0];
      read( fd, buffer, 1 );
      if ( buffer[0] == 34 ){
          if(buffBefore != '\\') { // es el cierre del string
              printf("%c",buffer[0]);
              break;
          }
      }
   }
}

int Busca_nombre_all_range_for(int fd, int numLine, int tipo){
   int retVal=0;

   char buffer[2];
   buffer[1] = '\0';
   Str_init(vars); 
   if( tipo ){
      Let(vars, "All_range_for(");
   }else{
      Let(vars, "All_range_for_ptr(");
   }
   
      while( ! Eof(fd) ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nAll range for: se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              tbuffer[1] = '\0';
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nAll range for: encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Cat(vars,tbuffer);
                  Cat(vars,buffer);
              }
          }
          
          if( buffer[0]!=';' ) {
              Cat(vars,buffer);
          
          }else {
              Cat(vars,");");
              break;
          }
      }
      printf("%s",vars);
      Free_secure(vars);
      if( Eof(fd) ){
          Msg_redf("\nAll range for: nombre mal formado en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   return retVal;
}
// busca From arraySource new lista,  lista2   as tipo;
// NewArray(nBool,int); nBool=NewFrom(&mat_data,&nBool_data,int);
/*int Busca_New_Array_From(int fd, int numLine, char * aSource){
   int retVal=0;
   Set( cLinea, "NewArray(__NEW__,__TIPO__);__NEW__=NewFrom(&__SOURCE___data,&__NEW___data,__TIPO__);");
   Set( cStrLinea, "NewStrArray(__NEW__);__NEW__=NewFrom(&__SOURCE___data,&__NEW___data,string);");
   // busca lista de arrays:
   char tbuffer[2];
   tbuffer[1]='\0';
   aSource[strlen(aSource)-1]='\0';
   char cItem[128];
   cItem[0]='\0'; int c=0;
   NewStrArray(lista);
   Str_init(tipo);
   int swTipo=1;
   
   while( ! Eof(fd) ){
       read( fd, tbuffer, 1 );

       // check comentarios:
       if( tbuffer[0]=='/' ){  // puede ser un comentario.
           char buffer[2];
           buffer[0] = tbuffer[0];
           buffer[1] = '\0';
           read( fd, tbuffer, 1 );
           if(tbuffer[0]=='*'){
               Descarta_comentario_bloque(fd,&numLine,buffer);
               continue;
           }else{
               Msg_redf("From...Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝",numLine);
               retVal=1;
               break;
           }
       }
       if( tbuffer[0]!=',' && tbuffer[0]!=' '){ 
          cItem[c]=tbuffer[0];
          cItem[++c]='\0';

       }else if(tbuffer[0]==' '){ //
          if( strcmp(cItem,"as")==0 ){
              tipo = Busca_Nombre(fd,tbuffer,numLine);
              Get_fn_let( tipo, Str_tran(tipo,";","") );
              if(strcmp(tipo,"string")==0) swTipo=0;
              break;
          }
          while( ! Eof(fd) ){
             read( fd, tbuffer, 1 );
             // check comentarios:
             if( tbuffer[0]=='/' ){  // puede ser un comentario.
                 char buffer[2];
                 buffer[0] = tbuffer[0];
                 buffer[1] = '\0';
                 read( fd, tbuffer, 1 );
                 if(tbuffer[0]=='*'){
                     Descarta_comentario_bloque(fd,&numLine,buffer);
                     continue;
                 }else{
                     Msg_redf("From...Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝",numLine);
                     retVal=1;
                     break;
                 }
             }
             if(tbuffer[0]==' ') continue;
             else if(tbuffer[0]=='\n' || tbuffer[0]==';') break;
             else {
                 if( cItem[0]!='\0' ){
                     AppendStr(lista, cItem); c=0;
                     cItem[c]='\0';
                 }
                 cItem[0]=tbuffer[0];cItem[1]='\0';c=1;
                 break;
             }
          }
          if( retVal ) break;
       }else if(tbuffer[0]==','){ // encontró un candidato
          if( cItem[0]!='\0' ){
              if( c>1 && cItem[c]!=' ' ){
                  AppendStr(lista, cItem);
              }
              cItem[0]='\0';c=0;
          }
       }

       if( tbuffer[0]==';' || tbuffer[0]=='\n'){
           break;
       }
   }
   if( !retVal && lista_data.len>0 ){
       int i=0;
       while( i < lista_data.len ){
           Str_init(cTmp);
           if (swTipo){
               Let( cTmp, cLinea );
               Get_fn_let( cTmp, Str_tran(cTmp,"__SOURCE__",aSource) );
               Get_fn_let( cTmp, Str_tran(cTmp,"__NEW__",Cell(lista,i)) );
               Get_fn_let( cTmp, Str_tran(cTmp,"__TIPO__",tipo) );
               printf("%s",cTmp);
               Free_secure(cTmp);
           }else{
               Let( cTmp, cStrLinea );
               Get_fn_let( cTmp, Str_tran(cTmp,"__SOURCE__",aSource) );
               Get_fn_let( cTmp, Str_tran(cTmp,"__NEW__",Cell(lista,i)) );
               printf("%s",cTmp);
               Free_secure(cTmp);           
           }
           ++i;
       }
   }
   Free_secure(tipo);
   Free_secure(cLinea);
   Free_secure(cStrLinea);
   FreeStrArray(lista);
   return retVal;
}*/

// para Busca_For_Items:
char * Busca_Cada_Porcion( int fd,/* int *nItems,*/ int numLine){
   Str_init(cItem);
   char tbuffer[2];
   tbuffer[1]='\0';
   int swFirst=1;
   while( ! Eof(fd) ){
       read( fd, tbuffer, 1 );

       // check comentarios:
       if( tbuffer[0]=='/' ){  // puede ser un comentario.
           char buffer[2];
           buffer[0] = tbuffer[0];
           buffer[1] = '\0';
           read( fd, tbuffer, 1 );
           if(tbuffer[0]=='*'){
               Descarta_comentario_bloque(fd,&numLine,buffer);
               continue;
           }else{
               Msg_redf("\nFor(items):Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
               retVal=1;
               break;
           }
       }
 /*      if( tbuffer[0]!='{' ){*/
          if( swFirst ){
             Let( cItem, tbuffer );
             swFirst=0;
          }else{
             Cat( cItem, tbuffer );
          }
         
          if( tbuffer[0]=='\n'){
              break;
          }
/*          if( tbuffer[0]==' ' ) {
              
              ++*nItems;
              break;
          }
       }*/
   }
   if( Eof(fd) || retVal ){
       Msg_redf("\nFor(items):Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
       Free_secure(cItem); // deja NULL
   }
   return cItem;
}

// aqui debo buscar 4 elementos
int Busca_For_Items(int fd, int numLine, int nModo){
   int retVal=0;
   Str_init(Linea);
   switch(nModo){
       case(0) : { Let(Linea,"ForItems(");break; }  //ForItems( _I_, _X_ )
       case(1) : { Let(Linea,"ForEachItem(");break; }  //ForEachItem(_I_,_V_)
       case(2) : { Let(Linea,"For_each_token(");break; }  //ForEachToken( _V_INDEX_, _STR_ )
       case(3) : { Let(Linea,"For_each_founded(");break; }  //ForEachFounded(_X_,_LEN_)
       case(4) : { Let(Linea,"For_each_rev_founded(");break; }  //ForEachRevFounded(_X_,_LEN_)
       case(5) : { Let(Linea,"For_each_match(");break; }  //ForEachMatch(_X_,_LEN_)
   }
//   int nItems=0, 
//   int swFirst=1;
   Str_init(vars);
//   while( nItems < 4 ){
       Str_init(cTemp);
       cTemp = Busca_Cada_Porcion(fd, /*&nItems,*/ numLine);
       if(cTemp){
           //if( swFirst ){
               Let(vars, cTemp);
           /*    swFirst=0;
           }else{
               Cat(vars, cTemp);
           }*/
           Free_secure(cTemp);
       }else{
           Msg_redf("\nFor:Falla proceso de búsqueda de items para 'For' en línea %d 😝\n",numLine);
           retVal=1;// break;
       }
//   }
   if( !retVal /*&& nItems==4*/ ){
       // cambia algunas cosas, según el Modo:
       Get_fn_let(vars, Str_tran(vars," in ",","));
       Get_fn_let(vars, Str_tran(vars," to ",","));
       Get_fn_let(vars, Str_tran(vars," do{","){"));
       Get_fn_let(vars, Str_tran(vars," do ",")"));
       Get_fn_let(vars, Str_tran(vars," do\n",")\n"));
       Cat(Linea, vars);
       printf("%s",Linea);
   }
   Free_secure(Linea); Free_secure(vars);
   return retVal;
}
int Busca_Iterador_DOWN(int fd,int numLine){
   int retVal=0; //, sw_llega_al_fin=0;
   char buffer[2];
   buffer[1] = '\0';
   Str_init(vars); 
   Let(vars,"Iterdown(");

      while( ! Eof(fd) /*&& c<256*/ ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nIterdown: se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              tbuffer[1] = '\0';
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nIterdown: encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Cat(vars,tbuffer);
                  Cat(vars,buffer);
              }
          }
          
          if( buffer[0]==':' || buffer[0]=='[' ) {
              Cat(vars,",");
          }else if( buffer[0]!=']' ) {
              Cat(vars,buffer);
          
          }else {
             //if (!sw_llega_al_fin){
                Cat( vars, ")" ) ;
                if ( Str_at("NONE",vars) ){
                   Get_fn_let( vars, Str_tran(vars,"NONE","0,1,0") );
                }
                break;
                //sw_llega_al_fin=1;
             //}
          }
/*          if(buffer[0]=='{') {
             Cat( vars, "{" ) ;
             break;
          }*/
      }
      printf("%s",vars);
      Free_secure(vars);
      if( Eof(fd) ){
          Msg_redf("\nIterdown: expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   return retVal;    

}

/*
   $V[x,y,...] => Cell(V,x,y,...)
   @V[x,y,...] => pCell(V,x,y,...)
*/
int Busca_Cell(int fd,int numLine,int tipo){
   int retVal=0;
   int swPar=0;
   char buffer[2];
   buffer[1] = '\0';
   Str_init(vars); 
   if( tipo ){
      read( fd, buffer, 1 );
      if( buffer[0]=='1' ){
          Let(vars,"Cell1(");
      }else if(buffer[0]=='2' ){
          Let(vars,"Cell2(");
      }else if(buffer[0]=='3' ){
          Let(vars,"Cell3(");
      }else if(buffer[0]=='4' ){
          Let(vars,"Cell4(");
      }else{
          Let(vars,"Cell(");
          Cat(vars,buffer);
      }
      ///Let(vars,"Cell(");
   }else{
      read( fd, buffer, 1 );
      if( buffer[0]=='1' ){
          Let(vars,"pCell1(");
      }else if(buffer[0]=='2' ){
          Let(vars,"pCell2(");
      }else if(buffer[0]=='3' ){
          Let(vars,"pCell3(");
      }else if(buffer[0]=='4' ){
          Let(vars,"pCell4(");
      }else{
          Let(vars,"pCell(");
          Cat(vars,buffer);
      }
   
     // Let(vars,"pCell(");
   }

      while( ! Eof(fd) ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nCells: se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              tbuffer[1] = '\0';
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nCells: encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Cat(vars,tbuffer);
                  Cat(vars,buffer);
              }
          }
          
          if( buffer[0]=='[' ) {
              Cat(vars,",");
              swPar++;
          }else if( buffer[0]=='$' ) {
              read( fd, buffer, 1 );
              if( buffer[0]=='1' ){
                  Cat(vars,"Cell1(");
              }else if(buffer[0]=='2' ){
                  Cat(vars,"Cell2(");
              }else if(buffer[0]=='3' ){
                  Cat(vars,"Cell3(");
              }else if(buffer[0]=='4' ){
                  Cat(vars,"Cell4(");
              }else{
                  Cat(vars,"Cell(");
                  Cat(vars,buffer);
              }
          }else if( buffer[0]=='@' ) {
              read( fd, buffer, 1 );
              if( buffer[0]=='1' ){
                  Cat(vars,"pCell1(");
              }else if(buffer[0]=='2' ){
                  Cat(vars,"pCell2(");
              }else if(buffer[0]=='3' ){
                  Cat(vars,"pCell3(");
              }else if(buffer[0]=='4' ){
                  Cat(vars,"pCell4(");
              }else{
                  Cat(vars,"pCell(");
                  Cat(vars,buffer);
              }
          
          }else if( buffer[0]!=']' ) {
              Cat(vars,buffer);

          }else {
              Cat( vars, ")" ) ;
              --swPar;
              if( !swPar )
                  break;
          }
      }
      /* verifico si es MT */
      if (tipo){
          if ( Occurs("Cell(d-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "Cell(d-", "dCell(") );
          }
          if ( Occurs("Cell(i-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "Cell(i-", "iCell(") );
          }
          if ( Occurs("Cell(l-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "Cell(l-", "lCell(") );
          }
          if ( Occurs("Cell(f-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "Cell(f-", "fCell(") );
          }
          if ( Occurs("Cell(ui-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "Cell(ui-", "uiCell(") );
          }
          if ( Occurs("Cell(ul-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "Cell(ul-", "ulCell(") );
          }
          if ( Occurs("Cell(s-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "Cell(s-", "sCell(") );
          }

      }else{
          if ( Occurs("pCell(d-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "pCell(d-", "pdCell(") );
          }
          if ( Occurs("pCell(i-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "pCell(i-", "piCell(") );
          }
          if ( Occurs("pCell(l-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "pCell(l-", "plCell(") );
          }
          if ( Occurs("pCell(f-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "pCell(f-", "pfCell(") );
          }
          if ( Occurs("pCell(ui-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "pCell(ui-", "puiCell(") );
          }
          if ( Occurs("pCell(ul-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "pCell(ul-", "pulCell(") );
          }
          if ( Occurs("pCell(s-",vars) ){
              Get_fn_let( vars, Str_tran(vars, "pCell(s-", "psCell(") );
          }

      }
      printf("%s",vars);
      Free_secure(vars);
      if( Eof(fd) ){
          Msg_redf("\nCells: expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }
   

   return retVal;
}

int Busca_Iterador_UP(int fd,int numLine){
   int retVal=0; //, sw_llega_al_fin=0;
   char buffer[2];
   buffer[1] = '\0';
   Str_init(vars); 
   Let(vars,"Iterup(");

      while( ! Eof(fd) /*&& c<256*/ ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nIterup: se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              tbuffer[1] = '\0';
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nIterup: encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Cat(vars,tbuffer);
                  Cat(vars,buffer);
              }
          }
          
          if( buffer[0]==':' || buffer[0]=='[' ) {
              Cat(vars,",");
          }else if( buffer[0]!=']' ) {
              Cat(vars,buffer);
          
          }else {
             //if (!sw_llega_al_fin){
                Cat( vars, ")" ) ;
                if ( Str_at("NONE",vars) ){
                   Get_fn_let( vars, Str_tran(vars,"NONE","0,1,0") );
                }
                break;
                //sw_llega_al_fin=1;
             //}
          }
/*          if(buffer[0]=='{') {
             Cat( vars, "{" ) ;
             break;
          }*/
      }
      printf("%s",vars);
      Free_secure(vars);
      if( Eof(fd) ){
          Msg_redf("\nIterup: expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   return retVal;    
}

int Busca_Print(int fd, int numLine){
   int retVal=0;
   char tbuffer[2];
   tbuffer[1]='\0';
   int swFinallinea=0;
   //Str_init(vars);
   //Let(vars, "printf(");
   printf("printf(");
   
   while( ! Eof(fd) && !retVal ){
       read( fd, tbuffer, 1 );
       if( tbuffer[0]=='\n'){
           if ( !swFinallinea ){
               Msg_redf("\nPrint:Se llegó al final de línea en línea %d 😝\n",numLine);
               retVal=1;
               break;
           }else{
               swFinallinea=0;
           }
       }
       // check comentarios:
       if( tbuffer[0]=='/' ){  // puede ser un comentario.
              char buffer[2];
              buffer[0] = tbuffer[0];
              buffer[1] = '\0';
              read( fd, tbuffer, 1 );
              if(tbuffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nPrint:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(tbuffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  printf("%s%s",buffer,tbuffer);
                  //Cat(vars,buffer);
                  //Cat(vars,tbuffer);
              }
       }
              /* si encontró una variable $ o @, debe derivar hacia esa parte, y regresar */
       if( tbuffer[0]=='$' ){
           retVal = Busca_Cell(fd,numLine,1);
       
       }else if( tbuffer[0]=='@' ){
           retVal = Busca_Cell(fd,numLine,0);
       
       }else if( tbuffer[0]=='"' ){ // es un string
           while( ! Eof(fd) ){
               printf("%c",tbuffer[0]);
               char buffBefore = tbuffer[0];
               read( fd, tbuffer, 1 );
               if ( tbuffer[0] == 34 ){
                   if(buffBefore != '\\') { // es el cierre del string
                       printf("%c",tbuffer[0]);
                       break;
                   }
               }
           }
       }else if( tbuffer[0]=='\\' ){  // sigue en siguiente linea
           swFinallinea=1;
           
       }else if( tbuffer[0]!=';' ) {
           //Cat( vars, tbuffer );
           printf("%s",tbuffer);
      
       }else{
           //Cat( vars, ");" );
           printf(");");
           break;
       }
   }
   if( Eof(fd) ){
       Msg_redf("\nPrint:Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
       retVal=1;
 //  }else{
 //      printf("%s",vars);
   }
 //  Free_secure(vars);
   return retVal;

}

int Busca_Cadena_Sys(int fd, int numLine, char *buffer){
   int retVal=0;
   char tbuffer[2];
   tbuffer[1]='\0';
   Str_init(vars);
   Let(vars, "Get_sys(\"");
   while( ! Eof(fd) ){
       read( fd, tbuffer, 1 );
       if( tbuffer[0]=='\n'){
           Msg_redf("\nSys:Se llegó al final de línea en línea %d 😝\n",numLine);
           retVal=1;
           break;
       }
       if( tbuffer[0]!='`' ) {
           Cat( vars, tbuffer );
       }else{
           Cat( vars, "\");" );
           break;
       }
   }
   if( Eof(fd) ){
       Msg_redf("\nSys:Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
       retVal=1;
   }else{
       printf("%s",vars);
   }
   Free_secure(vars);
   return retVal;
}

int Busca_At(int fd, int numLine, int Modo){
   int retVal=0;
   char tbuffer[2];
   tbuffer[1]='\0';
   Str_init(vars);
   if( Modo == 0){
      Let(vars, "Gotoxy(");
   }else if(Modo==1){
      Let(vars, "Gotox(");
   }else if(Modo==2){
      Let(vars, "Gotoy(");
   }else if(Modo==3){
      Let(vars, "Free_search(");
   }else if(Modo==4){
      Let(vars, "Free_match(");
   }
   while( ! Eof(fd) ){
       read( fd, tbuffer, 1 );
       if( tbuffer[0]=='\n'){
           Msg_redf("\nAt(Locate Cur):Se llegó al final de línea en línea %d 😝\n",numLine);
           retVal=1;
           break;
       }
       
       // check comentarios:
       if( tbuffer[0]=='/' ){  // puede ser un comentario.
              char buffer[2];
              buffer[0] = tbuffer[0];
              buffer[1] = '\0';
              read( fd, tbuffer, 1 );
              if(tbuffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nAt(Locate Cur):Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(tbuffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Cat(vars,buffer);
                  Cat(vars,tbuffer);
              }
       }
          
       if( tbuffer[0]!=';' ) {
           Cat( vars, tbuffer );
       }else{
           Cat( vars, ");" );
           break;
       }
   }
   if( Eof(fd) ){
       Msg_redf("\nAt(Locate Cur):Expresión mal formada en línea %d (palabra demasiado larga 😐)\n",numLine);
       retVal=1;
   }else{
       printf("%s",vars);
   }
   Free_secure(vars);
   return retVal;
}

int Busca_Rangos( int fd, int numLine, int tipo){
   int retVal=0, sw_llega_al_fin=0,swFinalLinea=0;
   char buffer[2];
   buffer[1] = '\0';
   Str_init(vars); //vars=Space(260); int c=8; //, swFirst=1;
   if(tipo){
      Let(vars,"Range_for(");
   }else{
      Let(vars,"Range_for_ptr(");
   }
   
      while( ! Eof(fd) /*&& c<256*/ ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              if ( !swFinalLinea ){
                  Msg_redf("\nRangos:Se llegó al final de línea en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else{
                  Cat(vars,buffer);
                  swFinalLinea=0;
              }
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              tbuffer[1] = '\0';
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nRangos:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Cat(vars,tbuffer);
                  Cat(vars,buffer);
              }
          }
          
          if( buffer[0]=='\\' ){  // sigue abajo
              swFinalLinea=1;
          
          }else if( buffer[0]==':' || buffer[0]=='[' ) {
              Cat(vars,",");
              
          }else if( buffer[0]!=';' && buffer[0]!=']' ) {
              Cat(vars,buffer);
          
          }else {
             if (!sw_llega_al_fin){
                Cat( vars, ");" ) ;
                if ( Str_at("NONE",vars) ){
                   Get_fn_let( vars, Str_tran(vars,"NONE","0,1,0") );
                }
                sw_llega_al_fin=1;
             }
          }
          if(buffer[0]==';') break;
      }
      printf("%s",vars);
      Free_secure(vars);
      if( /*c>=256 ||*/ Eof(fd) ){
          Msg_redf("\nRangos:Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   return retVal; 
}

int Busca_array_mt(int fd, int numLine, int nClear){
   int retVal=0;
      char buffer[2];
      Str_init(tipo); tipo=Space(1024);
      Str_init(vars); vars=Space(260); int c=0, swFirst=1;
      while( ! Eof(fd) && c<256 ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nBusca_array_mt:Se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nBusca_array_mt:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  vars[c++] = tbuffer[0];
                  vars[c++] = buffer[0];
              }
          }
          
          if( buffer[0]!=',' && buffer[0]!=';')
             vars[c++] = buffer[0];
          else {
             vars[c]='\0';c=0;

             if( vars[0] != '\0' ){
                 if( swFirst ){
                      if( nClear==0){
                         Let( tipo,"New_mt_array(" );
                      }
                      swFirst=0;
                 }else{
                      if( nClear==0){
                         Cat( tipo,"New_mt_array(" );
                      }
                 }
                 Cat( tipo,vars );
                 Cat( tipo,");");
             }
          }
          if(buffer[0]==';') break;
      }
      printf("%s",tipo);
      Free_secure(vars);
      if( c>=256 || Eof(fd) ){
          Msg_redf("\nBusca_array_mt: Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   Free_secure(tipo);
   
   return retVal;
}


int Busca_put_objects(int fd, int numLine, int nClear){
   int retVal=0;
      char buffer[2];
      Str_init(tipo); tipo=Space(1024);
      Str_init(vars); vars=Space(260); int c=0, swFirst=1;
      while( ! Eof(fd) && c<256 ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nBusca_put_objects:Se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nBusca_put_objects:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  vars[c++] = tbuffer[0];
                  vars[c++] = buffer[0];
              }
          }
          
          if( buffer[0]!=',' && buffer[0]!=';')
             vars[c++] = buffer[0];
          else {
             vars[c]='\0';c=0;

             if( vars[0] != '\0' ){
                 if( swFirst ){
                      if( nClear==0){
                         Let( tipo,"Put_object_mouse(" );
                      }
                      swFirst=0;
                 }else{
                      if( nClear==0){
                         Cat( tipo,"Put_object_mouse(" );
                      }
                 }
                 Cat( tipo,vars );
                 Cat( tipo,");");
             }
          }
          if(buffer[0]==';') break;
      }
      printf("%s",tipo);
      Free_secure(vars);
      if( c>=256 || Eof(fd) ){
          Msg_redf("\nPut_busca_objects: Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   Free_secure(tipo);
   
   return retVal;
}


int Busca_Free_Secure(int fd, int numLine, int nClear){
   int retVal=0;
      char buffer[2];
      Str_init(tipo); tipo=Space(1024);
      Str_init(vars); vars=Space(260); int c=0, swFirst=1;
      while( ! Eof(fd) && c<256 ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nFree xxx:Se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nFree xxx:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  vars[c++] = tbuffer[0];
                  vars[c++] = buffer[0];
              }
          }
          
          if( buffer[0]!=',' && buffer[0]!=';')
             vars[c++] = buffer[0];
          else {
             vars[c]='\0';c=0;

             if( vars[0] != '\0' ){
                 if( swFirst ){
                      if( nClear==0){
                         Let( tipo,"Free_secure(" );
                      }else if( nClear==1 ){
                         Let( tipo,"Free_array(" );
                      }else if( nClear==2 ){
                         Let( tipo,"Free_str_array(" );
                      }else if( nClear==3 ){
                         Let( tipo,"Free_stat(" );
                      }else if( nClear==4 ){
                         Let( tipo,"Free_tag(" );
                      }else if( nClear==5 ){
                         Let( tipo,"Regex_free(" );
                      }else if( nClear==6 ){
                         Let( tipo,"Free_total_array_mt(" );
                      }else if( nClear==7 ){
                         Let( tipo,"Free_video(" );
                      }else if( nClear==8 ){
                         Let( tipo,"pFree_total_array_mt(" );
                      }
                      swFirst=0;
                 }else{
                      if( nClear==0){
                         Cat( tipo,"Free_secure(" );
                      }else if( nClear==1 ){
                         Cat( tipo,"Free_array(" );
                      }else if( nClear==2 ){
                         Cat( tipo,"Free_str_array(" );
                      }else if( nClear==3 ){
                         Cat( tipo,"Free_stat(" );
                      }else if( nClear==4 ){
                         Cat( tipo,"Free_tag(" );
                      }else if( nClear==5 ){
                         Cat( tipo,"Regex_free(" );
                      }else if( nClear==6 ){
                         Cat( tipo,"Free_total_array_mt(" );
                      }else if( nClear==7 ){
                         Cat( tipo,"Free_video(" );
                      }else if( nClear==8 ){
                         Cat( tipo,"pFree_total_array_mt(" );
                      }
                 }
                 Cat( tipo,vars );
                 Cat( tipo,");");
             }
          }
          if(buffer[0]==';') break;
      }
      printf("%s",tipo);
      Free_secure(vars);
      if( c>=256 || Eof(fd) ){
          Msg_redf("\nFree xxx: Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   Free_secure(tipo);
   
   return retVal;
}

int Busca_Declare_String(int fd, int numLine){
   //String a,b="hola", c=Space(40); => Str_init(a); Set(b,"hola"); Str_init(c);c=Space(40);
   int retVal=0;

      // busco variables:
      char buffer[2];
      Str_init(tipo); tipo=Space(1024);
      Str_init(vars); vars=Space(260); int c=0, swFirst=1;
      while( ! Eof(fd) && c<256 ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nDeclara String:Se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nDeclara String:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  vars[c++] = tbuffer[0];
                  vars[c++] = buffer[0];
              }
          }
          
          if( buffer[0]!=',' && buffer[0]!=';')
             vars[c++] = buffer[0];
          else {
             vars[c]='\0';c=0;

             if( vars[0] != '\0' ){
                 if( Occurs("=",vars) ){
                   //  printf("Veamos Space...\n");
                     if( !Occurs("Space",vars) ){
                      //  printf("Vimos Space!\n");
                        if( swFirst ){
                            Let( tipo,"Set(" ); 
                            swFirst=0;
                        }else{
                            Cat( tipo,"Set(" );
                        }
                        Cat( tipo,vars );
                        Cat( tipo,");");
                        int nPos = Occurs("=",tipo);
                        tipo[nPos-1] = ',';
                     }else{  // es Space!
                        Str_init(var); Str_init(cadena);///var=Space(150);

                        Let(cadena,"Str_init(");
                        
                        Get_fn_let( var, Substr(vars,0,Str_at("=",vars)-1) );
                        Cat(cadena, var);
                        Cat(cadena, ");");
                        Cat(cadena, vars);
                        Cat(cadena, ";");
                        if( swFirst ){
                           Let( tipo, cadena );swFirst=0;
                        }else{
                           Cat( tipo, cadena );
                        }
                        Free_secure(cadena);
                        Free_secure(var);
                     }
                 }else{
                     if(swFirst){
                        Let( tipo,"Str_init(" );
                        swFirst=0;
                     }else{
                        Cat( tipo,"Str_init(" );
                     }
                     Cat( tipo,vars )
                     Cat( tipo,");" );
                 }
                 if( buffer[0]==';' ){  // llega al final de la declaracion
                     printf("%s",tipo);
                     break;
                 }
             }
          }
      }
      Free_secure(vars);
      if( c>=256 || Eof(fd) ){
          Msg_redf("\nDeclara String:Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }

   Free_secure(tipo);
   return retVal;
}

int Busca_Array(int fd, int numLine, char *buffer, int nFill){
   int retVal=0;
   char tipo[1024];
/*   int c;
   if( !nFill ){
      tipo[0]=buffer[0]; c=1;
   }else{
      c=0;
   }
   
   while( ! Eof(fd) && c<=4 ){
       read( fd, buffer, 1 );

       // check comentarios:
       if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("Encontré un comentario de línea donde no debía estar, en línea %d",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Msg_redf("Símbolo no reconocido '%s', en línea %d",tbuffer,numLine);
                  retVal=1;
                  break;
              }
       }       

       tipo[c++] = buffer[0];
   }
   tipo[c]='\0';
   if( strcmp(tipo,"Array") == 0) {*/
      // busco variables:
      char vars[260]; int c=0, swFirst=1;
      while( ! Eof(fd) && c<256 ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
             Msg_redf("\nBusca Array(1):Se llegó al final de línea en línea %d 😝\n",numLine);
             retVal=1;
             break;
          }
          
          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nBusca Array: encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{  // puede ser una division: dejarselo al compilador!
                  Msg_redf("\nBusca Array:Símbolo no reconocido '%s', en línea %d 😝\n",tbuffer,numLine);
                  retVal=1;
                  break;
              }
          }
          
          if( buffer[0]!=',' && buffer[0] != ' ')
             vars[c++] = buffer[0];
          else {
             vars[c]='\0';c=0;
             if( vars[0] != '\0' ){
                 if( strcmp(vars,"as") != 0 ){
                     if( swFirst ){
                         if( !nFill ){
                             strcpy( tipo,"as_array(");
                         }else{
                             strcpy( tipo,"as_fill_array(");
                         }
                         swFirst=0;
                     }else{
                         if( !nFill ){
                             strcat( tipo,"as_array(");
                         }else{
                             strcat( tipo,"as_fill_array(");
                         }
                     }
                     strcat( tipo, vars );
                     strcat( tipo, ",____SUBTIPO____");
                     if( !nFill ){
                         strcat( tipo, ");");
                     }else{
                         strcat( tipo, ",____RELLENO____);");
                     }
                 }else{
                     // busco subtipo: aqui debo ver ()
                     if( !swFirst ){
                         char subtipo[25]; int c=0;
                         while( ! Eof(fd) && c<20 ){
                            read( fd, buffer, 1 );
                            if( buffer[0]=='\n'){
                                Msg_redf("\nBusca Array(2):Se llegó al final de línea en línea %d 😝\n",numLine);
                                retVal=1;
                                break;
                            }
                            
                            // check comentarios:
                            if( buffer[0]=='/' ){  // puede ser un comentario.
                                char tbuffer[2];
                                tbuffer[0] = buffer[0];
                                read( fd, buffer, 1 );
                                if(buffer[0]=='/'){
                                    //Descarta_cometario_linea(fd,buffer);
                                    Msg_redf("\nBusca Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                                    retVal=1;
                                    break;
                                }else if(buffer[0]=='*'){
                                    Descarta_comentario_bloque(fd,&numLine,buffer);
                                    continue; // porque buffer no contendrá datos
                                }else{
                                    Msg_redf("\nBusca Array: símbolo no reconocido '%s', en línea %d 😝\n",tbuffer,numLine);
                                    retVal=1;
                                    break;
                                }
                            }
                            
                            if( buffer[0]==' ') continue;
                            if( buffer[0]!='(' ){  // encontré tipo(
                               subtipo[c++] = buffer[0];
                            }else{
                               break;
                            }
                         }
                         // busco dimensiones:
                         int ctaPar=1;  // no es necesarion que cuente el primer parentesis
                         if( c<20  && !Eof(fd) ){
                            subtipo[c]='\0';
                            char dim[50]; int c=0;
                            dim[c++] = '(';   // porque se añadio aqui
                            while( ! Eof(fd) && c<50 ){
                               read( fd, buffer, 1 );
                               if( buffer[0]=='\n'){
                                   Msg_redf("\nBusca Array(3):Se llegó al final de línea en línea %d 😝\n",numLine);
                                   retVal=1;
                                   break;
                               }

                               // check comentarios:
                               if( buffer[0]=='/' ){  // puede ser un comentario.
                                   char tbuffer[2];
                                   tbuffer[0] = buffer[0];
                                   read( fd, buffer, 1 );
                                   if(buffer[0]=='/'){
                                       //Descarta_cometario_linea(fd,buffer);
                                       Msg_redf("\nBusca Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                                       retVal=1;
                                       break;
                                   }else if(buffer[0]=='*'){
                                       Descarta_comentario_bloque(fd,&numLine,buffer);
                                       continue;
                                   }else{
                                       dim[c++] = tbuffer[0];
                                       
                                      /* Msg_redf("Busca Array:Símbolo no reconocido '%s', en línea %d 😝",tbuffer,numLine);
                                       retVal=1;
                                       break;*/
                                   }
                               }

                               if( buffer[0]==' ') continue;
                               if( buffer[0]=='(') {  // puede ser una expresion matematica
                                  ctaPar++;
                                  ///dim[c++] = buffer[0];
                               }
                               if( buffer[0]!=')' ){  // encontré x,x)
                                  dim[c++] = buffer[0];
                               }else{
                                  if ( !--ctaPar ){  // cuenta el ultimo parentesis
                                      break;
                                  }else{   // pertenece a una expresion
                                      dim[c++] = buffer[0];
                                  }
                               }
                            }
                            dim[c++] = ')';  // aqui añade el ultimo parentesis que encontro
                            dim[c]='\0';
                            // armo cadena:
                            Str_init(w); Let( w, "Dim");
                            Cat(w, dim ); Cat(w,";");
                            Cat(w, tipo );
                            Get_fn_let( w, Str_tran(w,"____SUBTIPO____",subtipo) );
                                
                            if( strcmp(subtipo,"string")==0 ){
                                if( !nFill ){
                                    Get_fn_let( w, Str_tran(w,"as_array","as_str_array") );
                                }else{
                                    Get_fn_let( w, Str_tran(w,"as_fill_array","as_fill_str_array") );
                                }
                                Get_fn_let( w, Str_tran(w,",string","") );
                            }else if( Occurs("unsigned",subtipo) ){
                                if( !nFill ){
                                    Get_fn_let( w, Str_tran(w,"as_array","as_unsigned_array") );
                                }else{
                                    Get_fn_let( w, Str_tran(w,"as_fill_array","as_fill_unsigned_array") );
                                }
                                Get_fn_let( w, Str_tran(w,"unsignedint","int") );
                                Get_fn_let( w, Str_tran(w,"unsignedlong","long") );
                            }
                            if( !nFill )
                                printf("%s",w);
                            else{  // sigue buscando para "with" y cambia W:
                                while( ! Eof(fd) ){  // quito los espacios despues de ")"
                                    read( fd, buffer, 1 );
                                    if(buffer[0]!=' ') break;
                                }
                                char fill[100]; int c=0;
                                fill[c++]=buffer[0];
                                while( ! Eof(fd) && c<=3 ){
                                   read( fd, buffer, 1 );
                                   if( buffer[0]=='\n'){
                                       Msg_redf("\nBusca Array(4):Se llegó al final de línea en línea %d 😝\n",numLine);
                                       retVal=1;
                                       break;
                                   }
                               
                                   // check comentarios:
                                   if( buffer[0]=='/' ){  // puede ser un comentario.
                                       char tbuffer[2];
                                       tbuffer[0] = buffer[0];
                                       read( fd, buffer, 1 );
                                       if(buffer[0]=='/'){
                                           //Descarta_cometario_linea(fd,buffer);
                                           Msg_redf("\nBusca Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                                           retVal=1;
                                           break;
                                       }else if(buffer[0]=='*'){
                                           Descarta_comentario_bloque(fd,&numLine,buffer);
                                       }else{
                                           /*Msg_redf("Busca Array:Símbolo no reconocido '%s', en línea %d 😝",tbuffer,numLine);
                                           retVal=1;
                                           break;*/
                                           fill[c++] = tbuffer[0];
                                           fill[c++] = buffer[0];
                                       }
                                   }else{
                                       fill[c++] = buffer[0];
                                   }
                                }
                                if(!retVal){
                                   fill[c]='\0';
                                   if( strcmp(fill,"with") == 0){
                                      // busco el relleno y lo dejo en fill:
                                      c=0;
                                      while( ! Eof(fd) && c<100 ){
                                         read( fd, buffer, 1 );
                                         if( buffer[0]=='\n'){
                                             Msg_redf("\nBusca Array(5):Se llegó al final de línea en línea %d 😝\n",numLine);
                                             retVal=1;
                                             break;
                                         }

                                         // check comentarios:
                                         if( buffer[0]=='/' ){  // puede ser un comentario.
                                             char tbuffer[2];
                                             tbuffer[0] = buffer[0];
                                             read( fd, buffer, 1 );
                                             if(buffer[0]=='/'){
                                                 //Descarta_cometario_linea(fd,buffer);
                                                 Msg_redf("\nBusca Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                                                 retVal=1;
                                                 break;
                                             }else if(buffer[0]=='*'){
                                                  Descarta_comentario_bloque(fd,&numLine,buffer);
                                                  continue;
                                             }else{
                                                  fill[c++] = tbuffer[0];
                                                  //fill[c++] = buffer[0]; //Se repite abajo????
                                             }
                                         }

                                         if(buffer[0]!=';'){
                                            fill[c++] = buffer[0];
                                         }else break;
                                      }
                                      fill[c]='\0';
                                      // ahora, hago los cambios:
                                      Get_fn_let( w, Str_tran(w,"____RELLENO____",fill) );

                                   }else{
                                      Msg_redf("\nBusca Array:No encuentro cláusula \"with\" en línea %d 😝\n",numLine);
                                      retVal=1;
                                   }
                                   printf("%s",w);
                                }
                            }
                            Free_secure(w);
                         }else{
                             Msg_redf("\nBusca Array:Expresión mal formada en línea %d (falta ';' 😝)\n",numLine);
                             retVal=1;
                         }
                     }else{
                         Msg_redf("\nBusca Array:No ha declarado variables en línea %d 😝\n",numLine);
                         retVal=1;
                     }
                     break;
                 }
             }
          }
      }
      if( c>=256 || Eof(fd) ){
          Msg_redf("\nBusca Array:Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }
/*   }else{
      printf("%s",tipo);
   }*/
   return retVal;
}

int Busca_New_Array(int fd, int numLine){ //, char *buffer){
   int retVal=0;
   char tipo[1024];
//   tipo[0]=buffer[0];
/*   int c=1;
   while( ! Eof(fd) && c<=8 ){
       read( fd, buffer, 1 );

       // check comentarios:
       if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("New Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Msg_redf("New Array:Símbolo no reconocido '%s', en línea %d 😝",tbuffer,numLine);
                  retVal=1;
                  break;
              }
       }

       tipo[c++] = buffer[0];
   }
   tipo[c]='\0';
   if( strcmp(tipo,"New Array") == 0) {*/
      //tipo[0]='\0';
      // busco variables:
      char buffer[2]; buffer[1]='\0';
      char vars[256]; int c=0, swFirst=1;
      while( ! Eof(fd) && c<256 ){
          read( fd, buffer, 1 );
          if( buffer[0]=='\n'){
              Msg_redf("\nNew Array:Se llegó al final de línea en línea %d 😝\n",numLine);
              retVal=1;
              break;
          }

          // check comentarios:
          if( buffer[0]=='/' ){  // puede ser un comentario.
              char tbuffer[2];
              tbuffer[0] = buffer[0];
              read( fd, buffer, 1 );
              if(buffer[0]=='/'){
                  //Descarta_cometario_linea(fd,buffer);
                  Msg_redf("\nNew Array:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                  retVal=1;
                  break;
              }else if(buffer[0]=='*'){
                  Descarta_comentario_bloque(fd,&numLine,buffer);
                  continue;
              }else{
                  Msg_redf("\nNew Array:Símbolo no reconocido '%s', en línea %d 😝\n",tbuffer,numLine);
                  retVal=1;
                  break;
              }
          }

          if( buffer[0]!=',' && buffer[0] != ' ')
             vars[c++] = buffer[0];
          else {
             vars[c]='\0';c=0;
             if( vars[0] != '\0' ){
                if( strcmp(vars,"as") != 0 ){
                    if( swFirst ){
                        strcpy( tipo,"New_array("); swFirst=0;
                    }else{
                        strcat( tipo,"New_array(");
                    }
                    strcat( tipo, vars );
                    strcat( tipo, ",____SUBTIPO____);");
                }else{
                    // busco subtipo: break;
                    if( !swFirst ){
                       char subtipo[20]; int c=0;
                       while( ! Eof(fd) && c<20 ){
                          read( fd, buffer, 1 );
                          if( buffer[0]=='\n'){
                                Msg_redf("\nNew array:Se llegó al final de línea en línea %d 😝\n",numLine);
                                retVal=1;
                                break;
                          }

                          // check comentarios:
                          if( buffer[0]=='/' ){  // puede ser un comentario.
                                char tbuffer[2];
                                tbuffer[0] = buffer[0];
                                read( fd, buffer, 1 );
                                if(buffer[0]=='/'){
                                    //Descarta_cometario_linea(fd,buffer);
                                    Msg_redf("\nNew array:Encontré un comentario de línea donde no debía estar, en línea %d 😝\n",numLine);
                                    retVal=1;
                                    break;
                                }else if(buffer[0]=='*'){
                                    Descarta_comentario_bloque(fd,&numLine,buffer);
                                    continue; // porque buffer no contendrá datos
                                }else{
                                    Msg_redf("\nNew array:Símbolo no reconocido '%s', en línea %d 😝\n",tbuffer,numLine);
                                    retVal=1;
                                    break;
                                }
                          }

                          if( buffer[0]==' ') continue;
                          if( buffer[0]!=';' ){
                             subtipo[c++] = buffer[0];
                          }else{
                             break;
                          }
                       }
                       if( c<20  && !Eof(fd) ){
                          subtipo[c]='\0';
                          // analizar si es unsignedint, sin espacio porque se lo comió.
                          // si es unsigned, enonces, hay que cambiar NewArray por NewUArray
                          Str_init(w); Let(w, tipo );
                          Get_fn_let( w, Str_tran(w,"____SUBTIPO____",subtipo) );
                          if( strcmp(subtipo,"string")==0 ){
                             Get_fn_let( w, Str_tran(w,"New_array","New_str_array") );
                             Get_fn_let( w, Str_tran(w,",string","") );
                          }else if( Occurs("unsigned",subtipo) ){
                             Get_fn_let( w, Str_tran(w,"New_array","New_unsigned_array") );
                             Get_fn_let( w, Str_tran(w,"unsigned","") );
                          }
                          printf("%s",w);
                          Free_secure(w);
                       }else{
                           Msg_redf("\nNew Array:Expresión mal formada en línea %d (falta ';' 😝)\n",numLine);
                           retVal=1;
                       }
                    }else{
                        Msg_redf("\nNew Array:No ha declarado variables en línea %d 😝\n",numLine);
                        retVal=1;
                    }
                    break;
                }
             }
          }
      }
      if( c>=256 || Eof(fd) ){
          Msg_redf("\nNew Array:Expresión mal formada en línea %d (palabra demasiado larga 😝)\n",numLine);
          retVal=1;
      }
/*   }else{
      printf("%s",tipo);
   }*/

   return retVal;
}

/*   MsgRed( "Esta es una prueba de %s",file);
   a = 10*sin(0.350)+|a+|b*sgn(g)||;
   if( a -or- b==2 ) ) { => if( a || b==2 )
   -or- -and-
   
   {a,b,c} = {0,10,-20};
   
   n = {10, ceil(RAND(n))};
   
   SetAllIntv(n);
   MatLet( n, 10 );
   MatLet(s,"");
   
   [int *a, int *b] = fun(x); => do{....
                                     int *a=NULL; int *b=NULL;
                                     do{
                                        int **_retVal_ = fun(x);
                                        if(_retVal_){
                                           *a = _retVal[0,0]; // punteros al primer elemento de _retVal_
                                           *b = _retVal[0,1];
                                        }
                                     }while(0);
   O bien:
   
   int *a = GetColumn(0, retVal);  // obtiene la columna entera del array 2D
   int *b = GetColumn(1, retval);
   
   int *ret = fun(x);
   int a,b,c;
   Store( ret, a,b,c ); =>  Store(_X_,...)  if( _X_ )
   
   Point( ret, *a,*b,*c )   *a = Cell(ret,0,0); *b=Cell(ret,0,1);
   CellP( a, fila )
   
    
   
   
   floar ** pag = GetPage(2, retVal); // obtiene una página del array 3D
   int *c = GetRow(4, retVal);  // obtiene una fila entera de retval.
   int *g = GetInterval( mat );  // obtiene un array 2D con los datos de un intervalo dado.
   PutInterval(g, mat);  // aquí manda el intervalo para guardar los elementos.
   PutRow(c, mat);
   PutColumn(a, mat);
   PutPage(pag, mat);
   AddRow(mat);   // añade espacios al final de un array, según coordenadas 2D. actualiza.
   AddColumn(mat);   
   AddPage(mat);
   
   InsPage, InsColumn, InsRow, DelPage, DelColumn, DelRow

   int ** cloneMat = Clone( mat);  Clone(mat, nuevoMat);
   
   String a,b="hola", c=Space(40); => Str_init(a); Set(b,"hola"); Str_init(c);c=Space(40);

   New Array n,b,c as string; => NewArrayStr(n);NewArrayStr(b);NewArrayStr(c);

   New Array j as int;   =>   NewArray(j,int);

   Array f,h as int(10,10);  =>  Dim(10,10); asArray(f,int); asArray(h,int);
   
   Free Secure file, str1, str2;
   Free Array ...;
   Free Str ... ;

   Dim(x,y,z); redefine array f;
   AddRow(a,b,c,d,e,f,....)
   Not(f)  => f=!f;
   
   char * s[]={"hola","mundo","curioso"};
   AddRow( s, mat );
   AppndList(s, mat );
   IntvRow(); IntvCol();...
   char * bloque = GetCells(mat);
   char * ret = GetCellsFor( i, Cell(mat,i) > 0 );
   int ** range = GetRangeFor( i, Cell(mat,i) == 0); //lo recorre como array 1D, pero devolverá array según dims.
   int * nBool = GetBoolFor( i, Cell(mat,i) > Cell( piv,i));
   int * nBool = GetBoolFor( i, MAT(mat) >= MAT(piv) );
   
   On Error Goto ERROR;  // consulta una variable de error universal.
   ...
ERROR:
   // limpia todo lo que haya que limpiar.

   On Option (opcion, 0,++i, 1,--j, 5,(i+=3; k=0) ) => un switch desde 0 hasta numero de opciones (argumentos);
   
   Initial Conditions: k=1, m=10, k = Cell(mat,0) ;
   ForRange( mat, range ){
   For Range range From mat {
      CellRng(mat) = 10*m++;
   }
   For Each Token v in w
       
   Next (v);
   
End*/
