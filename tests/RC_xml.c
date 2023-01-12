
#include <gadget/gadget.h>

LIB_GADGET_START

Main
    Assert( Arg_count == 2, end_input );
    Get_arg_str( xml_file, 1 );
    Assert( Exist_file(xml_file), file_not_exist );
    //String xml;
    char* xml = Load_string(xml_file);
    //Print "%s\n", xml;
    
    /* delete '\n'*/
    //Get_fn_let( xml, Str_tran( xml, ">\n<", "><" ) );
    //Print "%s\n", xml;
    ST_GETTAG field = Unparser( &xml, "Students");
    Assert ( field.content, fail_content );
    //Print "Content:\n%s\n", field.content;
   // Get_fn_let( field.content, Trim(field.content));
    while ( Occurs ("Student",field.content ) )
    {
        ST_GETTAG sub_field = Unparser( &field.content, "Student");
        //Print "\n%s\n",sub_field.content;
        //Get_fn_let( sub_field.content, Trim(sub_field.content));
        if(sub_field.attrib){
            //printf("Len attrib de (Student)=%d\n",sub_field.len);
            
            int i=0;
            Iterator up i [ 0: 1: sub_field.len ]{
            //while( i < sub_field.len){
               if ( strcmp(sub_field.name[i], "Name" )==0 ){
                   Get_fn_let( sub_field.attrib[i], Str_tran( sub_field.attrib[i], "&#x00C9;","É" ) );
                   /* OK... I must write the function that change this diabolic characters :D */
                   Print "%s\n",sub_field.attrib[i];
                   break;
               }
               //printf("Attributo del registro (%s): %s\n",sub_field.name[i],sub_field.attrib[i] );
              // ++i;
            }
       // }else{
       //     printf("--> (Student) sin atributos\n");
        }
        
        Free tag sub_field;
    }
    
    Free tag field;
  
  /* Exceptions areas */  
    Exception( fail_content ){
       Msg_red("Not content for \"Students\" field\n");
    }
    Free secure xml;
    
    Exception( file_not_exist ){
       Msg_redf("File \"%s\" not found\n", xml_file);
    }
    Free secure xml_file;
    
    Exception( end_input ){
       Msg_yellow("Use:\n   RC_xml <xml_file.xml>");
    }
    
End
