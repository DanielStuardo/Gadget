
#include <gadget/gadget.h>

LIB_GADGET_START
/* comentario  */
Main
    String sbin="00000100101011001011";
    
    Print "Binary : %s, Long = %ld\n", sbin, Bin2lng(sbin);
    
    String shex, soct;
    long otroOctal, otroHexa;
    Stack { Store (shex, Lng2hex(Bin2lng(sbin)) );
            otroHexa = Hex2lng(Lng2hex(Bin2lng(sbin)));
            Store (soct, Lng2oct(Bin2lng(sbin)) );
            otroOctal = Oct2lng(Lng2oct(Bin2lng(sbin)));
          }Stack_off
    Print "Hexadec: %s, \n", shex;
    Print "Octal  : %s, \n", soct;
    Print "Long   : %ld, \n", otroOctal;
    Print "Long   : %ld, \n", otroHexa;
    
    Free secure sbin, shex, soct;
End
