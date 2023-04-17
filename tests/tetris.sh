#!/bin/bash

#rxvt -si +sw -lsp 0 +sb -bg 0 -b 0 -w 0 -j -g 28x22  -pixmap "tests/dataTetris/Background_San_Basilio.jpg" -fn "xft:FantasqueSansMono-Regular:pixelsize=26" -e ./tests/tetris $1 $2 $3 $4

# set minimum delay
xset r rate 150 60
#rxvt -si +sw -lsp 0 +sb -bg 0 -b 0 -w 0 -j -g 40x22  -pixmap "tests/dataTetris/Background_San_Basilio_ext.jpg" -fn "xft:FantasqueSansMono-Regular:pixelsize=26" -e ./tests/tetris $1 $2 $3 $4

rxvt -si +sw -lsp 0 +sb -bg 0 -b 0 -w 0 -j -g 40x22  -pixmap "tests/dataTetris/San_Basilio02.jpg" -fn "xft:FantasqueSansMono-Regular:pixelsize=26" -e ./tests/tetris $1 $2 $3 $4
# return to default dalay and rate
xset r rate
