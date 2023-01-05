
#include <gadget/gadget.h>

LIB_GADGET_START


/* locales de este test */
void Imprime_el_array( pRDS(void, X), const char* ); //double * dNum, DS_ARRAY * dNum_data );

Main

   //Dim (5,10) as_unsigned_array(dNum, int); <--- esto ------+
   Array dNum as unsigned int(5,10);  // esto convierte a-----+

   int t, i, j;
   All_range_for(dNum);
   Compute_for ( dNum,i,j,
                 if( !Is_even(i) && Is_even(j)) t=100; else t=1;
                 $ dNum [i, j] = ceil(rand()%100) * t; 
               )
/*   int i;
   for (i=0;i<Rows(dNum);i++){
      int j;
      for(j=0;j<Cols(dNum);j++){
         Cell(dNum, i, j) = ceil(rand()%100);
      }
   }*/
   
   // aun tiene los rangos locales declarados.
   Imprime_el_array( pSDS(dNum), "Imprimiendo todo el array" );
   Prnl;
   
   DS_MAXMIN  maxNode = Max_array( pSDS(dNum) );
   Print "\nMayor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d\n\n", maxNode.row, maxNode.col;
   
   Reshape( dNum, 5,2,5);
   All range for dNum;
   int page;
   For_each_page(dNum, page){
         Compute_for( dNum, i,j,
             Print "%d,%d,%d = %d\n", i,j,page, $dNum[i,j,page];
         );
         putchar('\n');
      }
      putchar('\n');

   maxNode = Max_array( pSDS(dNum) );
   Print "\nMayor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d\n\n", maxNode.row, maxNode.col, maxNode.pag;

   maxNode = Min_array( pSDS(dNum) );
   Print "\nMenor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d\n\n", maxNode.row, maxNode.col, maxNode.pag;
   
   Reshape ( dNum,5,10);

   Fill array lista as unsigned int ( (int)(10/2) ) with 100;
   dNum = (unsigned int*)Append_col( pSDS(dNum), pSDS(lista));
   Free array lista;
   
   //Range dNum [0:2:Rows(dNum)] [ 1:2:Cols(dNum)] ;
   Range for dNum [ 1:2:Rows(dNum), 0:2:Cols(dNum)] ;
      
   Imprime_el_array( pSDS(dNum), "Imprimiendo una sección" );

   Print "Copiando la matriz INT a una matriz STRING...\n";

   New array sNum as string; //New_str_array(sNum);
   
   //&sNum := (char **) dNum;
   
   sNum = (char **)Copy_array/*_to_string*/( SMD( &sNum ), pSDS(dNum) );
   /* copio todo, incluso los rangos locales */
   if( sNum){
      Compute_for ( sNum, i,j, 
          Stack{
             Store ( Cell(sNum,i,j), Insert( $sNum[i, j],"Valor = ",1) ); 
          }Stack_off
      );
      Imprime_el_array( pSDS(sNum), "Imprimiendo una sección de la matriz de String:" );
      
      Print "\nAhora será FLOAT, pero no convertirá los valores con strings...\n";
      New array x as float; //New_array(x, float);
      x = (float*)Copy_array/*_to_float*/( SMD( &x ), pSDS(sNum) );
      if(x){
         All range for x;
         Imprime_el_array( pSDS(x), "Imprimiendo la matriz completa:" );
         Free array x ;
      }
      Free str array sNum;

   }else{
      Msg_red("No fue posible hacer la copia...");
   }
   
   // dNum[ :,2] := [];
   dNum = (unsigned int*)Delete_col( pSDS(dNum), 2);
   All_range_for(dNum);
   Imprime_el_array( pSDS(dNum), "Le borré la columna 2" );
   
   // dNum[2, : ] := []
   dNum = (unsigned int*)Delete_row( pSDS(dNum), 2);
   All_range_for(dNum);
   Imprime_el_array( pSDS(dNum), "Le borré la fila 2" );
   
   Free array dNum; //Free_array(dNum);
   
   Array s as string(10); //Dim (10) as_str_array(s);
   
   All_range_for(s);
   Compute_for ( s, i, Let( s[i], "un mensaje cualquiera" ) );

   Imprime_el_array( pSDS( s), "\nImprimiendo el array string");
   
   sAppend(s, "Se añade esto al array");
   sAppend(s, "Se añade esto otro al array");
   sAppend(s, "También se añade esto");
   sAppend(s, "Y esto queda al final");
   
   Print "Len s = %d, Rows s = %d\n", Len(s), Rows(s);
   Rows(s) = Len(s);
   Print "Len s = %d, Rows s = %d\n", Len(s), Rows(s);
   
   Reshape(s,(int)Len(s)/2,2);
   
   if ( Is_ok ) { 
      All_range_for(s);
      char oldTok = Set_new_sep(' ');
      Compute_for (s, i,j, 
             if(rand()%10 >5){
                Stack{
                   Store( $s[i,j], Mod_token( $s[i,j], Upper("profundo"), 3) );
                }Stack_off
             }
      ); Set_token_sep(oldTok);
                        
      Imprime_el_array( pSDS( s), "Imprimiendo el array reshapeado y modificado");
   } else {
      Msg_amber("No puedo continuar porque no pude reshapear el array");
   }
   
   New array arreglo_clonado as string; //New_str_array(arreglo_clonado);
   
   //arreglo_clonado = Clone_array_string( pSDS(s), SMD(&arreglo_clonado));
   arreglo_clonado = (char **)Clone_array( SMD(&arreglo_clonado), pSDS(s));
   
   Imprime_el_array( pSDS( arreglo_clonado ), "Imprimiendo el array clonado");
   
   arreglo_clonado = (char **)Delete_col_string( pSDS(arreglo_clonado), 1 );
   
   All range for arreglo_clonado;
   Imprime_el_array( pSDS( arreglo_clonado ), "Imprimiendo el array modificado (delete)");
   
   Fill array temporal as string( Rows(arreglo_clonado) ) with "insertado";
   arreglo_clonado = (char **)Insert_col_string( pSDS(arreglo_clonado), pSDS(temporal), 0 );
   
   All range for arreglo_clonado;
   Imprime_el_array( pSDS( arreglo_clonado ), "Imprimiendo el array modificado (insert)");
   
   Free str array s, arreglo_clonado, temporal;

   
   Fill array x as int(2,2,3,4) with ceil(rand()%10);//Dim (2,2,3,4) as_fill_array (x, int, ceil(rand()%10));
   
   for(int l=0; l<4; l++)  /* bloques o libro */
      for(int k=0; k<3; k++)  /* pagina */
         for(int i=0; i<2; i++) /* fila */
            for(int j=0; j<2; j++) /* columna */
                Print "%d,%d,%d,%d = %d\n", i,j,k,l, $x [ i, j, k, l];
   
   Prnl
   Print "Ahora usando las macros de Gadget:\n";
   int book;
   All_range_for(x);
   For_each_book(x,book){
      Print "Book: %d\n",book;
      For_each_page(x, page){
         Compute_for( x, i,j,
             Print "%d,%d,%d,%d = %d\n", i,j,page,book, $x[ i,j,page,book]; //Cell(x,i,j,page,book);
         );
         putchar('\n');
      }
      putchar('\n');
   }
   
   
   maxNode = Max_array( pSDS(x) );
   Print "\nMayor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d, book: %d\n\n", maxNode.row, maxNode.col, maxNode.pag, maxNode.book;
   int fila=0, col=0, pag=0, blk=0;
   Get_coor( maxNode.local, SMD(&x), &fila, &col, &pag, &blk);
   Print "Get coord: f: %d, c: %d, p: %d, b: %d\n", fila,col,pag,blk; 
   
   maxNode = Min_array( pSDS(x) );
   Print "\nMenor numero (posicion dura) = %d\n", maxNode.local;
   Print "Posicion fila: %d, col: %d, pag: %d, book: %d\n\n", maxNode.row, maxNode.col, maxNode.pag, maxNode.book;
   Get_coor(maxNode.local, SMD(&x), &fila, &col, &pag, &blk);
   Print "Get coord: f: %d, c: %d, p: %d, b: %d\n", fila,col,pag,blk; 
   
   Get_coor(12, SMD(&x), &fila, &col, &pag, &blk);
   Print "Get coord: f: %d, c: %d, p: %d, b: %d\n", fila,col,pag,blk; 
   
   
   Free_array(x);
   
   New array seq as double;
   seq = Lineal_spaced(SMD(&seq), 1, -1, 10);
   Iterator up i [0: 1: Len(seq) ]{
       Print "%lf, ", seq[i];
   }
   Free array seq;
   Prnl;
   
   seq = Lineal_sequence(SMD(&seq), 1, 0.5, 10);
   Iterup (i, 0, 1, Len(seq)) {
       Print "%lf, ", seq[i];
   }
   
   Free array seq;
   
   Prnl;
   
   String w="María tenía un corderito";
   
   New array aw as string;
   aw = Split( w, ' ', pSDS(aw) );
   if (aw ){
      Iterator up i[ 0:1:Len(aw) ] {
          Print "%s, ", aw[i];
      }
      Free str array aw;

   }else{
      Msg_red("No pude splitear el string...\n");
   }
   
   Prnl;
   
   aw = Split_char( w, pSDS(aw) );
   if (aw ){
      //Iterator up i [0:1:Len(aw)] /*down j [100:1:0]*/ {
      Iterator up i [0:1:Len(aw)] {
          Print "%s, ", aw[i];
      }
      Free str array aw;
   }else{
      Msg_red("No pude splitear el string...\n");
   }
   Free secure w;
   
   F_STAT estado = Stat_file("archivo.txt");
   /* is_matrix me dice si puedo cargar el archivo como una matriz. */
   if (estado.is_matrix){
       //New_str_array(arch);
       //New_array(arch,int);
       New array arch as int;
       
       /* solo cargo la porcion de datos del archivo */
       Range for arch [1: 1: estado.total_lines-1, 1:1 : estado.max_tokens_per_line-1];
       
       arch = Load_matrix( pSDS(arch), "archivo.txt", estado);
       if( arch==NULL ){
           Msg_red("No se ha podido cargar el archivo");
       }else{
           All range for arch;
           Compute_for (arch, i,j, 
                 $arch[i,j] *= sqrt($arch[i,j]);
           );
           
           Imprime_el_array(pSDS( arch ), "\n\nImprimiendo el array cargado");
           //Free str array arch;
           /* guardando TODO el array modificado */
           if (Save_matrix( pSDS(arch), "archivo1.txt")){
               Msg_green("Archivo fue guardado con éxito!");
           }else{
               Msg_amber("Archivo no pudo ser guardado");
           }
           Free array arch;
       }
   }else{ 
       Msg_amber("El archivo no es cuadrado");
   }



   New array nlista as double;
   Append(nlista, double, 5.0);
   Append(nlista, double, 10.0);
   Append(nlista, double, 15.0);

   Append_hlst (nlista,double,10,20,30,40, sqrt(2556),0.345,3.141592,3.141592*2,100 );
   
   Insert_hlst( nlista, double, 7, -1,-2,-3,-4)
   
   Reshape(nlista, 4,4);
   Append_hrow(nlista,double,0.1,0.2,0.3,0.4)
   Append_hcol(nlista,double,10000,20000,30000,40000,50000);
   
   /* prepara datos estáticos para ser usados en funcion Gadget */

/*   double nInsert[]={0,0,0,0,0};
   DS_ARRAY nInsert_data;
   nInsert_data.len=sizeof(nInsert)/sizeof(double);*/
   Array_static( nInsert, double, 0,0,0,0,0 )
   
   nlista = Insert_col_double( pSDS(nlista),pSDS(nInsert),2);
   
   Insert_hrow ( nlista, double, 3, 0.001, 0.002, 0.003, 0.004, 0.005, 0.006);
   Insert_hrow ( nlista, double, Rows(nlista)-1, -0.001, -0.002, -0.003, -0.004, -0.005, -0.006);
   Insert_hrow ( nlista, double, 0, 0, 0, 0, 0, 0, 0);
   
   Insert_hcol ( nlista, double, Cols(nlista)-1, 1,1.0/2.0,1.0/3.0,1.0/4.0,
                                                   1.0/5.0,1.0/6.0,1.0/7.0,1.0/8.0); 
   
   All range for nlista; // no sirve para un array 1D
   //Range for nlista [0: 1: Len(nlista)];

   Print "\nlista con datos añadidos:\n";
   Iterup (row, nlista, i ){
       Iterup (col, nlista, j){
          if( j==5 ){
              Print "%*.*lf, ", 5,5,$nlista[i,j];
          }else{ 
              Print "%*.*lf, ", 8,3,$nlista[i,j];
          }
       }
       Prnl;
   }
   Prnl;
   Free array nlista;
   
   
   New array slista as string;
   slista = (char **) Append_hlst_string(pSDS(slista),"Pablito","clavó","un clavito","oxidao",NULL);
   //Range for nlista [0: 1: Len(slista)];
   Print "\nlista con datos añadidos:\n";
   Iterator up i [0:1:Len(slista)]{
       Print "%s, ", $slista[i];
   }
   Prnl;
   Reshape( slista, 2,2);
   slista = Append_hrow_string(pSDS(slista),"en la cima","de un cerro cortao", NULL);
   All range for slista;
   Imprime_el_array( pSDS(slista),"Imprime el array con fila añadida en duro");

   slista = Append_hcol_string(pSDS(slista),"bis","bis","bis",NULL);

/*   char * tmpp[] = {"verso 1","verso 2","verso 3"};
   DS_ARRAY tmpp_data;
   tmpp_data.len=3;*/
   Array_static( tmpp, char*, "verso 1","verso 2 y un cuarto más","verso 33 1/3")
   
   slista = (char **)Insert_col_string( pSDS(slista), pSDS(tmpp), 0 );
   All range for slista;
   Imprime_el_array( pSDS(slista),"Imprime el array con columna añadida en duro");
   
   Free str array slista;
   
   
   Print "\nPrueba de Iterator down:\n";
   // imprimirá hasta '1', porque es un iterador para arrays.
   Iterator down i [10: (2-3) :0] {
       Print "I=%d, ", i;
   }
   
   Print "\nReplicate....\n";
   String pepe;
   Stack { Store (pepe, Replicate("A",5)); 
           Print "\n[%s]", pepe;
           Store (pepe, Replicate("A",0));
           Print "\n[%s]\n", pepe;
           Free secure pepe;
   }Stack_off
End



/* esta funcion pudo haberse hecho sin punteros ( RDS( void, X ) ) porque
   no se modifica la metadata ( X_data que equivale a dNum_data )*/         
void Imprime_el_array( pRDS( void, X ), const char * msg ){ //double * dNum, DS_ARRAY dNum_data ){
   int i,j;
   Print "%s:\n", msg;
   switch(pType(X)){
      case INTEGER: case UINTEGER:{
          Rescue_DS_ptr( int*, tmp, X);
          //int * tmp = X;
          //DS_ARRAY *tmp_data = X_data;
          if(pDims(X)==1){
             pIterup( row, X, i){
                printf( "%d, ", (int) @tmp[i] );
             }
          }else{ 
             pIterup( row, X, i){
                pIterup( col, X, j){
                   printf( "%d, ",  (unsigned int)@tmp[i, j] );
                }
                putchar('\n');
             }
          }
          break;
      }case FLOAT:{
          Rescue_DS_ptr( float*, tmp, X);
          //int * tmp = X;
          //DS_ARRAY *tmp_data = X_data;
          if(pDims(X)==1){
             pIterup( row, X, i){
                printf( "%f\n", (float) @tmp[i] );
             }
          }else if(pDims(X)==2){
             pIterup( row, X, i){
                pIterup( col, X, j){
                   printf( "%f, ",  (float) @tmp[i, j] );
                }
                putchar('\n');
             }
          }
          break;
      }case STRING:{
          //char ** tmp = X;
          Rescue_DS_ptr( char **, tmp, X);
          if(pDims(X)==1){
             pIterup( row, X, i){
                printf( "%s\n", (char *) @tmp[i] );
             }
          }else if(pDims(X)==2){
             pIterup( row, X, i){
                pIterup( col, X, j){
                    printf( "%s, ", (char *)@tmp[i,j] );
                }
                putchar('\n');
             }
          }
          break;
      }
   }
        
/*   pIterup( row, X, i, 0, 2, Rows_ptr(X) ){
      pIterup( col, X, j, 1,2,Cols_ptr(X) ){*/
          
}

