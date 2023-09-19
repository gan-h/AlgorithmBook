
/*
  This algorithm takes a number, and turns on the rightmost 0 bit.
  
  How it works:

  When you add 1 to a binary number X, one of two scenarios may happen:
  1. The binary number has 0 for its last digit, and so it turns on.
  2. The binary number has a consecutive sequence of one or more 1s starting from the right.
    i.e. 10010011 has a consecutive sequence of two 1s starting from the right.
  
  Call the size of the sequence of consecutive 1s starting from the right K. 
  Imagine the binary number as an array of 0-indexed bits, that's indexed starting from the right. 
  Then, 

  10010011
       ^
       |
       |- This is equal to K.

  100100
       ^
       |
       |- This is equal to K.
  
  Notice that in both cases, adding 1 turns on the bit at K and changes all the bits to the right to 0.
  
  10010011 + 1 turns into 10010100
  100100 + 1 turns into 100101

  To regain all the 1 digits we lost after the addition, we perform a bitwise OR.
  The digits to the left of K are unaffected, the digit at K is turned on, 
  and the digits to the right of K are all 1s, just as they were before the addition happened. 

  In the most extreme case of the input being the max uint_64_t number (all 1s), this algorithm still works.

*/

#include <cinttypes>
std::uint64_t turnOnRightmostBit(std::uint64_t input) {
  return input | (input + 1);
}