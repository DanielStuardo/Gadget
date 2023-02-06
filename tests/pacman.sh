#!/bin/bash

#rxvt -lsp 0 -j -g 75x103 -pixmap "accion_osada.png" -fn "xft:FantasqueSansMono-Regular:pixelsize=5" -e ./tests/pacman $1 $2 $3 $4
rxvt -lsp 0 +sb -b 0 -w 0 -j -g 75x103 -fn "xft:FantasqueSansMono-Regular:pixelsize=5" -e ./tests/pacman $1 $2 $3 $4


