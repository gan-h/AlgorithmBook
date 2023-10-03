#include <functional>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>


/*

Task: Find all unique pairs of numbers in a sorted (ascending) array of numbers that sum to target

*/

struct Pair {
  int first;
  int second;

  bool operator==(const Pair other) {
    return other.first == first && other.second == second;
  }
};

namespace std {
  template<>
  struct hash<Pair> {
    size_t operator()(const Pair a) {
      return std::hash<int>()(a.first) ^ std::hash<int>()(a.second);
    }
  };
}

using namespace std;

vector<Pair> twoPointerMethod(vector<int> input, int target) {
  int start = 0; 
  int end = input.size()-1;
  vector<Pair> ans; 

  while(start < end) {
    if(input[start] + input[end] > target) end--;
    else if(input[start] + input[end] < target) start++;
    else {
      //Equal to target

      ans.push_back({input[start], input[end]});
      if(input[start] == input[end]) break;
      else {
        start = upper_bound(input.begin() + start, input.begin() + end, input[start]) - input.begin();
        auto reverseStart = input.rbegin() + (input.size()-1-end);
        auto reverseEnd = input.rbegin() + (input.size()-1 - start);
        end = (input.size()-1) - (upper_bound(reverseStart, reverseEnd, input[end], [](int a, int b) {return -a < -b;}) - input.rbegin());

      }
    }
  }

  return ans;
}

ostream& operator<<(ostream& o, Pair a) {
  return o << "( " << a.first << ", " << a.second << ") ";
}

int main() {
  unordered_map<int, int> test = {
    {1, true},
    {2, false},
    {3, false}
  };
  for(auto& it : test) {
    it.second = true;
  }

  for(auto it : test) {
    cout << it.second << endl;
  }

  cout << endl;
}