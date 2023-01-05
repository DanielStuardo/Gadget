
#include <gadget/gadget.h>

LIB_GADGET_START

Main
   String form;
 /*  Get_fn_let( form, Parser( "campo1", "","Campo sin atributos", NORMAL_TAG) );

   String campo_attr;
   Format ( campo_attr, "name = \"%s\" sueldo = %d  cod= '%s'","Empleado Tipo",2000000,"A010-3 POS");
   Get_fn_cat( form, Parser( "campo2", campo_attr,"Pedro Pérez", NORMAL_TAG));
   Free secure campo_attr;*/
   Stack{
       Store ( form, Parser( "campo1", "","Campo sin atributos", NORMAL_TAG) );
       
       char campo_attr[200];
       sprintf(campo_attr,"name = \"%s\" sueldo = %d  cod= '%s'","Empleado Tipo",2000000,"A010-3 POS");
       
       Store_cat ( form, Parser( "campo2", campo_attr,"Pedro Pérez", NORMAL_TAG));
       
       Store_cat ( form, Parse_void( "campo3", "code-field=0") );
       Store_cat ( form, Parser( "campo4", "","", NORMAL_TAG));
       Store_cat ( form, Parser( "fin-campo","","",ONLY_TAG));
       Store ( form, Parser( "registro", "code-reg=9",form, NORMAL_TAG) );
       Store ( form, Str_tran( form, "><", ">\n<" ) );
   } Stack_off;
   
   //Get_fn_cat( form, Parser( "campo2", " name = \"empleado tipo\" sueldo = 2000000   cod= 'A010-3 POS'","Pedro Pérez", NORMAL_TAG));
   //Get_fn_cat( form, Parser( "campo3", "code-field=0","", ONLY_TAG));
/*   Get_fn_cat( form, Parse_void( "campo3", "code-field=0"));
   Get_fn_cat( form, Parser( "campo4", "","", NORMAL_TAG));
   Get_fn_cat( form, Parser( "fin-campo","","",ONLY_TAG));
  // lo anterior queda dentro de un registro:
   Get_fn_let( form, Parser( "registro", "code-reg=9",form, NORMAL_TAG) );
  // añado saltos de línea después de cada campo (opcional): 
   
   Get_fn_let( form, Str_tran( form, "><", ">\n<" ) );
  */    
   printf("Registro:\n%s\n\nAhora extraemos los campos (en desorden)\n\n", form);
   
   // lo devolvemos a la normalidad para que no qede feo pa'la demo:
   Get_fn_let( form, Str_tran( form, ">\n<", "><" ) );

   /* UNPARSER del registro: */
   /* Si extrajera "registro" primero, debería copiar el contenido a "form"
      porque éste, en el ejemplo, quedaría vacío. 
      En "form" queda lo que no fue extraído, y si solo es un registro,
      entonces, para seguir el análisis se debe extraer el campo form al final
      o bien copiar el contenido a "form" con Let() */
  // Init_token(); --> no es necesario, porque se inicializa en "Main"

 /* añado el ejemplo de lo que dije en el comentario, sin alterar el resto del codigo, excepto
    la mencion a "registro" en la cadena a tokenizar */
   ST_GETTAG field = Unparser( &form, "registro");
   if(field.content){
      printf("Contenido del registro:\n%s\n\n",field.content);
      Let( form, field.content);
      Free tag field;

      For each token  v in "campo2,campo3,campo1,campo4,meme,fin-campo" do
         
         ST_GETTAG field = Unparser( &form, v);

         if(field.content){
            Get_fn_let( field.content, Trim(field.content));
            printf("Contenido de (%s) = %s\nLen (%s) = %ld\n", v, field.content,field.content, (long)strlen(field.content));
         }else{
            printf("--> (%s) sin contenido\n",v);
         }
         if(field.attrib){
            printf("Len attrib de (%s)=%d\n",v,field.len);
            int i=0;
            while( i < field.len){
               printf("Attributo del registro (%s): %s\n",field.name[i],field.attrib[i] );
               ++i;
            }
         }else{
            printf("--> (%s) sin atributos\n",v);
         }
         /* liberamos "field"*/
         Free tag field ;

         printf("formulario restante a procesar:\n%s\n",strlen(form) ? form : "<vacío>");
         Prnl;

      Next_token(v)  // aquí se libera cada instanca de "v" y vuelve por otro
      printf("tamaño del formulario al terminar: %ld\n", (long)strlen(form));
   }else{
      Msg_red("el formulario está vacío!");
   }
   Free secure form;   
End
