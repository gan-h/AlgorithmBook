#include <functional>

/*

Somestime you want to hash your own struct. To do this, use the following code:

*/

struct YourType {
  int strong;
  int beautiful;
  int awesome;
};


//1. namespace std
namespace std {
  //2. template<> declares that you are specializing a template
  template<>
  //3. struct hash<YourType> {}
  struct std::hash<YourType> {
    size_t operator()(const YourType& input) const {
        size_t hashValue = 17;
        hashValue = hashValue * 31 + hash<int>{}(input.strong);
        hashValue = hashValue * 31 + hash<int>{}(input.beautiful);
        hashValue = hashValue * 31 + hash<int>{}(input.awesome);
        return hashValue;
    }
  };
}