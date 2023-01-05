
#include <gadget/gadget.h>
LIB_GADGET_START

u_int32_t ReverseBits(u_int32_t x, int bits)
{
    x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1); // Swap _<>_
    x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2); // Swap __<>__
    x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4); // Swap ____<>____
    x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8); // Swap ...
    x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16); // Swap ...
    return x >> (32 - bits);
}
/*Function to left rotate n by d bits*/
long int RotLBit32(long int n, unsigned int d)
{
   /* In n<<d, last d bits are 0. To put first 3 bits of n at 
     last, do bitwise or of n<<d with n >>(INT_BITS - d) */
   return (n << d)|(n >> (32 - d));
}
  
/*Function to right rotate n by d bits*/
long int RotRBit32(long int n, unsigned int d)
{
   /* In n>>d, first d bits are 0. To put last 3 bits of at 
     first, do bitwise or of n>>d with n <<(INT_BITS - d) */
   return (n >> d)|(n << (32 - d));
}
/*Function to left rotate n by d bits*/
long int RotLBit16(long int n, unsigned int d)
{
   /* In n<<d, last d bits are 0. To put first 3 bits of n at 
     last, do bitwise or of n<<d with n >>(INT_BITS - d) */
   return (n << d)|(n >> (16 - d));
}
  
/*Function to right rotate n by d bits*/
long int RotRBit16(long int n, unsigned int d)
{
   /* In n>>d, first d bits are 0. To put last 3 bits of at 
     first, do bitwise or of n>>d with n <<(INT_BITS - d) */
   return (n >> d)|(n << (16 - d));
}

Main
   String w;
   unsigned int i=378;
   unsigned long l=89835;
   unsigned long j=0;

   w = Lng2bin(i);
   if(w){
      Print "%d = %s\n", i, w;
      Free secure w;
   }
   Set_binsize(20)
   w = Lng2bin(l);
   if(w){
      Print "%ld = %s\n", l, w;
      Free secure w;
   }
   Unset_binsize; // necesario paraconvertir
   w = Lng2bin(l);
   if(w){
      printf("%ld = %s\n", l, w);
      j = Bin2lng( w );
      printf("%s = %ld\n", w, j);
      Free_secure(w);
   }
   
   w = Lng2hex(l);
   if(w){
      printf("%ld = %s\n", l, w);
      j = Hex2lng( w );
      printf("%s = %ld\n", w, j);
      Free_secure(w);
   }
   w = Lng2oct(l);
   if(w){
      printf("%ld = %s\n", l, w);
      j = Oct2lng( w );
      printf("%s = %ld\n", w, j);
      Free_secure(w);
   }
   printf("Factorial 25 = %llF\n", Fact(25));
   
   l=235;
   w = Lng2bin( l );
   printf("%s\n", w ); Free secure w;
   printf("BITS...\n");
   w = Lng2bin(Bit(5));
   printf("\tbit 5 = %s\n",w); Free secure w;
   w = Lng2bin( Get_bit(l,3) );
   printf("\tGetbit 3 = %s\n", w ); Free secure w;
   w = Lng2bin( Get_bit(l,2) );
   printf("\tGetbit 2 = %s\n", w ); Free secure w;
   w = Lng2bin( Set_bit(l,2) );
   printf("\tSetbit 2 = %s\n", w ); Free secure w;
   w = Lng2bin( Clear_bit(l,3) );
   printf("\tClearbit 3 = %s\n", w ); Free secure w;
   w = Lng2bin( Toggle_bit(l,3) );
   printf("\tTogglebit 3 = %s\n", w ); Free secure w;
   
   w = Lng2bin( Set_bit_if( 1, l, 3) );
   printf("\tSetbit 3 = %s\n", w ); Free secure w;
   w = Lng2bin( Set_bit_if( 0, l, 3) );
   printf("\tSetbit 3 = %s\n", w ); Free secure w;
   printf("\tIs even? %ld = %d\n", l,Is_even(l));
   printf("\tIs even? 4 = %d\n", Is_even(4));
   
   j=100; l=5;
   printf("\tJ=%ld, L=%ld\n",j,l);
   Swap(j,l); 
   printf("\tswapping...\n");
   printf("\tJ=%ld, L=%ld\n",j,l);
   
   l=17089;
   w = Lng2bin( l );
   printf("%ld = %s\n",l,w);
   Free secure w;
   
   j = ReverseBits(l, 32);
   w = Lng2bin( j );
   printf("Reverse 32 bits: %ld, bin = %s\n", j,w);
   Free secure w;
   
   j = ReverseBits(l, 16);
   w = Lng2bin( j );
   printf("Reverse 16 bits: %ld, bin = %s\n", j,w);
   Free secure w;

   j = ReverseBits(l, 4);
   w = Lng2bin( j );
   printf("Reverse 4 bits: %ld, bin = %s\n", j,w);
   Free secure w;
   
  // #define rotr(x,n)  (x >> n % 32) | (x << (32-n) % 32)
   j = RotLBit16(l, 4);
   w = Lng2bin( j );
   printf("rotate left 4 bits: %ld, bin = %s\n", j,w);
   Free secure w;

   j = RotLBit32(l, 16);
   w = Lng2bin( j );
   printf("rotate left 16 bits: %ld, bin = %s\n", j,w);
   Free secure w;

   j = RotRBit32(l, 8);
   w = Lng2bin( j );
   printf("rotate right 8 bits: %ld, bin = %s\n", j,w);
   Free secure w;

   j = RotLBit16(l, 16);
   w = Lng2bin( j );
   printf("rotate left 16 bits: %ld, bin = %s\n", j,w);
   Free secure w;

   j = RotRBit16(l, 8);
   w = Lng2bin( j );
   printf("rotate right 8 bits: %ld, bin = %s\n", j,w);
   Free secure w;
   
   
End
