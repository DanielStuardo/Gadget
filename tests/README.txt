

COMPILAR UN PROGRAMA

Compilar el programa con el script:

    ccpre.sh
    
Este script compila el programa, enlazando la librería Gadget. Opcionalmente,
lo ejecuta con Valgrind.

Es recomendable que sus programas los ejecute con Valgrind, hastq que esté 
seguro de no tener ningún problema para ser pasado a producción.

Ejemplo:

Si su programa se llama "miPrograma.c", debe compilarlos con el script, sin
poner la extensión:

    ./ccpre.sh miPrograma ( o ./ccpre.sh tests/miPrograma )

Opciones de ccpre.sh:

    ./ccpre.sh miPrograma        compila el programa con la librería compartida,
                                 (por defecto), generando un ejecutable que podrá
                                 ser llamado como:
                              
                                 ./miPrograma
                              
    ./ccpre.sh miPrograma -E     genera un archivo preprocesado de su programa.
                                 La salida será hecha en el stdin.
    
    ./ccpre.sh miPrograma -static
                                 compila el programa usando la librería estática.
                                 Las opciones -static y -E son excluyentes.
    
    ./ccpre.sh miPrograma . -c   compila el programa con la librería compartida,
                                 y a continuación ejecuta Valgrind para chequear
                                 problemas de memoria y otras barbaridades.
    
    ./ccpre.sh miPrograma -static -c
                                 compila el programa con la librería estática,
                                 y a continuación ejecuta Valgrind para chequear
                                 problemas de memoria y otras barbaridades.
    
    El script ccpre.sh invoca al programa "gadget_prepre" que realiza un prepro-
cesamiento de su programa, y genera una única salida llamada:

    tmp_preproceso_mask.tmp.c
    
    Este programa será compilado, pero el ejecutable final tendrá el nombre original
del programa.

    El archivo antes mencionado puede ser usado para ver cómo preprocesan algunas
características de Gadget (atajos sintácticos).

PROGRAMACION

    La característica de GADGET es: "siempre que pidas prestado algo, devuélvelo".

    Esto sugiere que todo en esta librería es memoria dinámica: los strings, los
    arrays simples y los arrays multi-tipo. 
    
    La declaración: 
        
        String var="algo";

    es una declaración dinámica, no estática, y se debe limpiar con "Free secure var". 
    
    Si quiere una declaración estática, como:
       
        char * var = "algo";

    no necesitará limpiarla, pero no podrá modificarla.
    
    Una declaración del tipo:
        
        String var;

    refiere a "char * var=NULL" y su versión macro es "Str_init(var)". 
    
    Puede declarar tantas variables como sean necesarias:
    
        String name="Pepe Pótamos", cMsg, cTmp="   X   ";  // etcétera.
    
    Puede usar la variable declarada de inmediato asignando algo con "Let()":

        Let( cMsg, "hola mundo!");

    o con Get_fn_let():
    
        Get_fn_let(cMsg, Trim( cTmp ));
    
    o usando el Stack (que no depreca a Get_fn_let):
    
        Stack {
            char * tmp = "un mensaje corto";
            Store ( var, Str_tran( Upper( tmp ), "CORTO", "moderado" ) );
        } Stack_off; 

    EXPLICACION.
    
    "Upper(tmp)" toma el contenido de la variable estática, la convierte a mayúsculas,
    y deja el resultado en el STACK. Si usa "Upper" sin STACK, devolverá el resultado
    normalmente.
    La función "Str_tran" tomará el contenido del STACK y reemplazará toda mención a 
    "CORTO" por "moderado", y dejará el resultado en el STACK. Nuevamente, si esta
    función se usara sin STACK, devolvería el resultado normalmente.
    Luego, "Store" tomará el resultado del STACK, y lo dejará en "var".
    
    "Stack_off" verifica si quedó algo remanente en el STACK: si así fue, mandará un
    mensaje de "warning". Luego, limpiará el STACK para seguir cumpliendo su función
    más adelante.
    
    Upper() y Str_tran(), usadas normalmente, se codificarían así:
    
    char * var = Upper( v );
    char * var = Str_tran( v,"algo","por otra cosa");
    
    o bien:
    
    Get_fn_let( var, Upper( v ) );
    Get_fn_let( var, Str_tran( v,"algo","por otra cosa") );
    
OBSERVACIONES.

    El uso de las macros anteriores facilitan el uso de una sola variable, o lo que es
    lo mismo, evita que tenga que declarar tantas variables como llamadas a funciones
    de cadena necesite hacer.
    
    El uso del STACK es de cuidado, porque solo trabaja con las funciones propias
    de la librería. Por supuesto, usted podrá crear sus propias funciones de string
    con las funciones y macros de uso del STACK, y podrá anidar sus propias funciones.
    ¿No es genial?
    
    Una cosa más sobre el STACK: existen dos formas de almacenar resultados:
    
        Store ( v, .... )
    y
        Store_cat( v, .... )
    
    Vea los ejemplos en el directorio "tests" para más información. Creo que es el
    archivo "parser.c", que parsea HTML o XML, lo que usted quiera.

COMENTARIOS FINALES

    Bugs, comentarios y nuevas ideas, por favor hacerlas llegar al correo:
    
    daniel.stuardo@gmail.com
    
    Librería Gadget, noviembre de 2020-2022.
    
    Esta librería es código abierto, y se entrega tal como está. El
    autor no se hace responsable absolutamente de nada malo que surja
    de su aplicación o manipulación.
    
    Vea el archivo LICENCE para que no le quepan dudas sobre lo anterior y para
    obtener una vía de contacto.



