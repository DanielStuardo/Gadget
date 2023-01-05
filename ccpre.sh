#!/bin/bash

echo "Preprocesando..."
gadget_prepre_1.0 $1.c > tmp_preproceso_mask.tmp.c

if [ "$?" == 0 ]; then
   if [ "$2" == "-E" ]; then
      echo "Generando salida preprocesada..."
      gcc tmp_preproceso_mask.tmp.c -E
      exit 0
   fi
   if [ "$2" == "-static" ]; then
      echo "Compilando librería estática..."
#   gcc -Wall -o $1 tmp_preproceso_mask.tmp.c -lgadget_shared -lpthread -lm
      gcc -Wall -o $1 tmp_preproceso_mask.tmp.c -lgadget_static_1.0 -lm -lgpm
   else
      echo "Compilando librería compartida (por defecto)..."
#   gcc -Wall -o $1 tmp_preproceso_mask.tmp.c -lgadget_shared -lpthread -lm
      #gcc -Wall -v -save-temps -o $1 tmp_preproceso_mask.tmp.c -lgadget_shared_1.0 -lm -lgpm
      gcc -Wall -o $1 tmp_preproceso_mask.tmp.c -lgadget_shared_1.0 -lm -lgpm
   fi
   if [ "$?" == 0 ];then
      if [ "$3" == "-c" ]; then
          valgrind -v --leak-check=full --track-origins=yes --show-reachable=yes ./$1 $4 $5 $6 $7 $8 $9
      fi
   fi
   #rm tmp_preproceso_mask.tmp.o
else
   echo "Preproceso fallido."
   cat tmp_preproceso_mask.tmp.c
   #rm tmp_preproceso_mask.tmp.o
fi
exit 0
