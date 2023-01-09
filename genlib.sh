#!/bin/bash

# limpio los objetos existentes
function Clear_objects(){
if [ -f "gadget.o" ]; then
   rm gadget.o 
fi
if [ -f "gadget_kbd.o" ]; then
   rm gadget_kbd.o 
fi

if [ -f "gadget_file.o" ]; then
   rm gadget_file.o 
fi

if [ -f "gadget_stack_str.o" ]; then
   rm gadget_stack_str.o 
fi

if [ -f "gadget_numeric.o" ]; then
   rm gadget_numeric.o 
fi

if [ -f "gadget_array.o" ]; then
   rm gadget_array.o 
fi

if [ -f "gadget_datetime.o" ]; then
   rm gadget_datetime.o 
fi

if [ -f "gadget_video.o" ]; then
   rm gadget_video.o 
fi

if [ -f "gadget_mt_array.o" ]; then
   rm gadget_mt_array.o 
fi

if [ -f "gadget_mouse.o" ]; then
   rm gadget_mouse.o 
fi
}

function check_dependences_GPM(){
GPM_MOUSE=`dpkg -l | grep -i libgpm`
if [ "$GPM_MOUSE" != "" ]; then
    return 0;
fi
return 1;
}

function check_dependences_XDOTOOL(){
GPM_XDOTOOL=`dpkg -l | grep -i xdotool`
if [ "$GPM_XDOTOOL" != "" ]; then
    return 0;
fi
return 1;
}

# verificar que existe el directorio "gadget": sino, se crea
Clear_objects

check_dependences_GPM

if [ "$?" != 0 ]; then
   echo "La librería GPM (General Purpose Mouse) no está instalada."
   echo "Instale la librería con el siguiente comando antes de continuar"
   echo "con la instalación de GADGET:"
   echo " "
   echo "       sudo apt install gpm"
   echo " "
   echo "(Quizá sea posible que también necesite libgpm-dev)."
   echo "Generación terminada con fallo."
   exit 1
fi

check_dependences_XDOTOOL

if [ "$?" != 0 ]; then
   echo "XDOTOOL (para simular input de teclado y mouse) no está instalada."
   echo "Instale el programa antes de continuar con la instalación de GADGET:"
   echo " "
   echo "       sudo apt install xdotool"
   echo " "
   echo "Generación terminada con fallo."
   exit 1
fi


         # acceder como #include <gadget/gadget.h>
         if [ ! -d "/usr/include/gadget" ]; then
            sudo mkdir /usr/include/gadget
         fi
         echo "copiando cabeceras a /usr/include/gadget..."
         sudo cp include/gadget.h            /usr/include/gadget/.

echo "generando gadget.o..."
gcc -c -Wall -Werror -fPIC src/gadget.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget.kbd.o..."
gcc -c -Wall -Werror -fPIC src/gadget_kbd.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_file.o..."
gcc -c -Wall -Werror -fPIC src/gadget_file.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_stack_str.o..."
gcc -c -Wall -Werror -fPIC src/gadget_stack_str.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_numeric.o..."
gcc -c -Wall -Werror -fPIC src/gadget_numeric.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_array.o..."
gcc -c -Wall -Werror -fPIC src/gadget_array.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_mt_array.o..."
gcc -c -Wall -Werror -fPIC src/gadget_mt_array.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_datetime.o..."
gcc -c -Wall -Werror -fPIC src/gadget_datetime.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_mouse.o..."
gcc -c -Wall -Werror -fPIC src/gadget_mouse.c
if [ "$?" != 0 ]; then Clear_objects; exit; fi
echo "generando gadget_video.o..."
gcc -c -Wall -Werror -fPIC src/gadget_video.c

if [ "$?" == 0 ]; then
   echo "Generación Ok"
   echo "Generando librería libgadget_shared..."
   gcc -shared -o libgadget_shared_1.0.so gadget.o gadget_kbd.o gadget_mt_array.o gadget_video.o \
                  gadget_file.o gadget_stack_str.o gadget_numeric.o gadget_array.o gadget_datetime.o\
                  gadget_mouse.o
   if [ "$?" == 0 ]; then
      echo "generación Ok"
      echo "Generando librería libgadget_static..."
      
      ar rcs libgadget_static_1.0.a gadget.o  gadget_kbd.o gadget_file.o gadget_mt_array.o gadget_video.o\
                                gadget_stack_str.o gadget_numeric.o gadget_array.o gadget_datetime.o \
                                gadget_mouse.o
      
      if [ "$?" == 0 ]; then
         echo "generación Ok"      
         echo "copiando librerías a /usr/lib..."

         sudo cp libgadget_shared_1.0.so /usr/lib/.
         sudo cp libgadget_static_1.0.a /usr/lib/.
         
         sudo chmod 755 /usr/lib/libgadget_shared_1.0.so
         sudo chmod 755 /usr/lib/libgadget_static_1.0.a
         
         echo "moviendo librerías a lib..."
         if [ ! -d "lib" ]; then
            mkdir lib
         fi
         mv libgadget_shared_1.0.so lib/.
         mv libgadget_static_1.0.a lib/.

         if [ "$?" == 0 ]; then
            echo "Copia Ok"
            echo "Generando Previus Preprocessor de Gadget (PREPRE)..."
            rm gadget.o gadget_kbd.o gadget_file.o gadget_stack_str.o gadget_numeric.o gadget_array.o\
               gadget_datetime.o gadget_video.o gadget_mt_array.o gadget_mouse.o

       # si desea que el programa preprocesador sea estático, descomente esta línea:
       #     gcc -Wall -o gadget_prepre src/prepre.c -lgadget_static_1.0 -lm -lgpm
       # y comente esta otra:
            gcc -Wall -o gadget_prepre_1.0 src/prepre.c -lgadget_shared_1.0  -lm -lgpm
            
            if [ "$?" == 0 ]; then
                echo "PREPRE generado con éxito"
               # echo "copiando gadget_prepre a /usr/bin..."
                sudo cp gadget_prepre_1.0   /usr/bin/.
                
                sudo chmod 755 /usr/bin/gadget_prepre_1.0
                
                echo "moviendo PREPRE a bin..."
                if [ ! -d "bin" ]; then
                   mkdir bin
                fi
                mv gadget_prepre_1.0 bin/.
                echo "Librería creada con éxito."
                echo "-----------------------------------------------------------------------"
                echo "Version del compilador:"
                gcc --version | grep "gcc"

                ./mensaje.sh
            else
                echo "error en la generación de PREPRE"
            fi
         else
            echo "Problemas con la copia (quizá)"
         fi
      else
         echo "Compilación de librería estática fallida"
      fi
   else
      echo "Compilación de librería compartida fallida"
   fi
else
   echo "Compilación fallida"
fi

# borrado de objetos, por si el proceso falla
Clear_objects

exit 0
