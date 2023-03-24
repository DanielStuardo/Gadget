#!/bin/bash

rxvt -si +sw -lsp 0 +sb -bg 0 -b 0 -w 0 -j -g 170x139  -pixmap "tests/dataGamelife/body02.png" -fn "xft:FantasqueSansMono-Regular:pixelsize=3" -e ./tests/gamelife
#rxvt -si +sw -lsp 0 +sb -bg 0 -b 0 -w 0 -j -g 110x139 -fn "xft:FantasqueSansMono-Regular:pixelsize=3" -e ./tests/gamelife $1 $2 $3 $4
