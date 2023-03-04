#!/bin/bash

#rxvt -lsp 0 -j -g 75x103 -pixmap "accion_osada.png" -fn "xft:FantasqueSansMono-Regular:pixelsize=5" -e ./tests/pacman $1 $2 $3 $4
#rxvt -lsp 0 +sb -b 0 -w 0 -j -g 160x103 -pixmap "tests/dataPhoenix/ciudad01.jpg" -fn "xft:FantasqueSansMono-Regular:pixelsize=5" -e ./tests/xwin $1 $2 $3 $4
#rxvt -lsp 0 +sb -bg 0 -b 0 -w 0 -j -g 130x60  -fn "xft:FantasqueSansMono-Regular:pixelsize=8" -e ./tests/playwin $1 $2 $3 $4
rxvt -si +sw -lsp 0 +sb -bg 0 -b 0 -w 0 -j -g 130x60  -pixmap "tests/dataPhoenix/backsky02.jpg" -fn "xft:FantasqueSansMono-Regular:pixelsize=8" -e ./tests/phoenix $1 $2 $3 $4
# -sbg
