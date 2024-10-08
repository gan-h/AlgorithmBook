// 1.1 A first look at function templates
// 1.1.1 Defining the template
#include <iostream>
#include <string>
using std::cout, std::endl;
using std::string;

template <typename T>
T max(T a, T b)
{
    // Type T needs to support <, and also must be copy-able
    return b < a ? a : b;
}

// Note that the compiler can't deduce T using default arguments
// This function can be called as f(1) or f<string>()
template <typename T>
void f(T a = "banana pie")
{
    cout << a << endl;
}

// This allows the compiler to have a default type for T
template <typename T = std::string>
void g(T b)
{
    cout << b << endl;
}

int main()
{
    // :: ensures max is from the global namespace, not std namespace (std::max)
    // Different functions are generated for every type for which the template is used
    // The process of replacing template parameters by concrete types is called instantiation
    // It results in an instance of a template
    // Instantiating a template for a type that doesn't support all operations used within it is a compile-time error
    // Template correctness is checked in two-phases
    // First, for syntax errors, unknown names, static assertions
    // Then, the instantiated template is checked
    // Two-phase instantiation means that when a function template is used in a way that triggers its instantiation,
    // a compiler will need to see that template's definition.
    // With regular functions, in contrast, you can just forward declare the function in your cpp file, then link with the actual definition later.
    // A common approach to requirement that the template-definition is available at compile time, is to define the template in a header file

    cout << ::max(3, 5) << endl;
    cout << ::max(3.0, 3.2) << endl;

    // Type Conversions During Type Deduction
    // When the compiler deduces types for T, type conversion is more limited than we're used to
    // When declaring call parameters by value, only trivial conversions that decay are supported
    // Trivial Conversions that decay include: getting rid of const or volatile, changing references to the referenced type
    // and array types turning into pointers.
    // That is why this double, int stuff throws a compile-time error:
    // cout << ::max(3.0, 3) << endl;
    ::max(static_cast<double>(4), 7.2); // This is okay since its double, double.
    // We can prevent the limited type deduction from happening, by telling the compiler the type
    ::max<double>(4, 7.2); // Since the compiler knows its double, double, it will change the 4 into 4.0

    // Type deduction doesn't work for default call arguments
    // In other words, f(); throws a compile-time error. The compiler will say it can't deduce T.
    // However, if we provide a type, it works: f<string>();
    // We can also pass a value in f("hello there")
    f<string>();
    f("hello there"); // T is deduced as const char *
}
