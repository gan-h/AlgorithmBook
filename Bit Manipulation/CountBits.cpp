//This algorithm counts the number of bits turned on

/*
  How it works:
  
  Every time we subtract one from a non-zero binary number, the rightmost 1 turns to zero, and all the digits further
  to the right change to 1.
  
  For example:
  1001000 - 1 = 1000111. 
     ^              ^^^
     |                |--> notice how all these digits turned to 1
     |
     |--> this is the rightmost 1.

  10101 - 1 = 10100
      ^           ^
      |           |--> the rightmost 1 changed to zero. There are no digits to the right of it (if there were, they would be equal to 1)
      |
      |--> this is the rightmost 1

  
  Let's call the position of the rightmost 1, K, to make thinking about what "input = input & (input - 1)" does easier.
  Every digit to the left of K in both (input) and (input - 1) is the same. 
  In (input), the digit at K is 1, whereas in (input-1), the digit at K is 0
  Every digit to the right of K in (input) is 0, whereas each digit to the right of (input-1) is 1. 
  
  Thus, input & (input - 1) changes the digit at K to zero and everything to the right of K to zero.
  
  The while loop makes sure that this is done as many times as long as a rightmost 1 in the input exists. 
  If we keep track of the number of iterations it takes for the number to have no 1s at all (input == 0),
  then we get our answer. 
*/

#include <cinttypes>

int countBits(uint64_t input) {
  int count = 0;

  while(input != 0) {
    input = turnOffRightMostBit(input);
    count++;
  }

  return count;
}

inline uint64_t turnOffRightMostBit(uint64_t input) {
  return input & (input - 1);
}