#include <functional>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

/*

  Lower bound takes as input:

  1. A sorted array
  2. A target value
  3. A comparator: (value, value) -> bool

  It assumes that the comparator was used to sort the array, and that when you call comparator(some value, target)
  on every value in the array, you get:

  [T,T,T,F,F,F,F,F]
         ^

  ... an array of true and false values. The element index after the very last T value 
  (marked in the figure with a carat) is the index that lower_bound will return. 

  When the comparator is the function (a, b) -> (a < b), where a and b are numbers,
  then lower_bound gives the first index where ((element value) < target ) is false, in other words,
  the first index that represents an element greater than or equal to target. 

  Note that if the array is all true values, [T, T, T, T], lower_bound returns the index one past the end,
  since you can sort of define the one-past-the-end index as "containing" an element where comparator(target, value) returns false
*/

template<class T>
int lower_bound_implementation(std::vector<T> v, T target, int start, int endExclusive,  std::function<bool(T, T)> comparator) {
  int loc = -1 + start;
  for(int jump = endExclusive - start + 1; jump != 0; jump /= 2) {
    while(jump + loc < endExclusive && comparator(v[loc + jump], target)) loc += jump;
  }

  return loc + 1;
} 

int main() {
  std::vector<int> v = {1,2,3,4,5,6};
  for(int i = 0; i < 10; i++) {
    int a = lower_bound_implementation<int>(v, i, 0, 6, [](int a, int b){return a < b;});
    int b = std::lower_bound(begin(v), end(v), i) - begin(v);
    assert(a == b);
  }
}