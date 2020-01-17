�����һ������ģ�壬������Ҫ���ݲ��������Ͳ�ͬ������ͬ���£����Բ���
### 1. ģ����廯������ض���ĳЩ���ͣ����廯һ��ģ�壬��ͨ��ģ������ͬ���£�
### 2. ����ģ�庯�������������ַ�ʽ
1.tag dispatch
	�����Ͼ���ֻ���û��ɼ�һ��ͨ��ģ�壬Ȼ���������ͨ��ģ����ʹ����ͨ�������صķ���ʵ�ʵ��ý��ղ�ͬ��������ͨ����������ģ�庯��
	Ϊ�˵�����ͨ������ģ�庯�������أ�����ʹ��һ��std::conditional<> ��tag
		
		```C++
		
		```
2.SFINAE
		template<typename T>
		bool Equal(T l, T r, enable_if_t<is_floating_point_v<T>>*a=nullptr)
		{
			return true;
		}

		template<typename T>
		bool Equal(T l, T r, enable_if_t<negation_v<is_floating_point<T>>>* a=nullptr)
		{
			return l == r;
		}

# Basic Terminology
- Class Type = ``struct + class + union``
- class = ``struct + class``
- class template: the class is a template, a parameterized description of a family of classes
- template class:
  - synonym for ``class template``
  - refer to classes generated from templates
  - refer to the class types generated from templates
- instantiation: creating a definition for a regular class, type alias, function, member function, variable from a template by substituting concrete arguments for the template parameters
- specialization: the entity resulting from instatiation
  - explicit: programmer specify explicitly a declaration that is tied to a special substitution of template parameters, using ``template<>``
	- partial specialization: specializations that still have template parameters
  - implicit: generated specialization
- primary template: When talking about explicit or partial specializations, the general template is primary template
- declaration: introduce or reintroduce a name into a scope, details are not requried
- definitions: declarations + details, when storage space must be allocated. **For a variable, initialization or no ``extern`` specifier causes a declaration to become a definition**
- One-definition rule (ODR): non-inline functions, member functions, global variables, static data members should be defined only once across the whole program. [Class types](#class-type), templates(including partial specializations but not full specializations), inline functions and variables should be defined at most once per ``cpp`` file, and should be identical.
  

# Function template
## Defining the template
```cpp
template<typename T>
T max(T a, T b)
{
	return b<a? a : b;
}
```
``template<comma-seperated-list-of-parameters>``  
The keyword ``template`` or ``class`` introduces a type parameter. Here, the type parameter is ``T``. In this case, type ``T`` has to support operator ``<``. ``void`` is a valid parameter.
## Instantiation
An attempt to instantiate a template for a type that doesn't support all the operations used within a template will cause a compile-time error.
```cpp
std::complex<float> c1, c2;
max(c1, c2);	//Error!
```
Templates are compiled in **2 phases**:
1. Without instantiation at definition time, the template is checked for correctness ignoring the template paramters:
   - Syntax error
   - Using unknown names(types, functions, ...) that don't depend on template paramters
   - Static assertions that don't depend on template parameters
2. At instantiation time, template code is checked to ensure all code is valid. *Some compilers doesn't perform phase 1 chcks.*
   ```cpp
   template<typename T>
   void func(T t)
   {
	   	T some_var			//first phase error, because of syntax error
	   	some_other_func();	//first phase error if some_other_func() is unknown
	   	static_assert(sizeof(int)>10, "sizeof(int)<=10");	
	   	//first phase error because this doesn't depend on parameters
	   
	   	some_other_func(t);	//second phase error if some_other_func(T) is unknown
		static_assert(sizeof(T)>10, "T too small");	//second phase error because it depends on parameters
   }
## Template Argument deduction
### Type Conversions During Type Deduction
- When declaring template parameters by reference, **No** conversions apply to type deduction. Arguments declared with same template parameter `T` must match.
  ```cpp
	template<typename T>
	T max(T a, T b)		//pass by value
	{
		return b<a? a : b;
	}
	template<typename T>
	T max2(T& a, T& b)	//pass by ref
	{
		return b<a? a : b;
	}
	int const a=3;
	int b=4;
	max(a,b);	//OK, 4
	max2(a,b);	//Error! a->int const&	 b->int&
- When declaring template parameters by value, only trivial conversions that decay are supported:
  - const/volatile ignored
  - T& -> T
  - raw array -> pointer
  - function -> function pointer

## Pass by value vs. Pass by reference
### Pass by value
Since C++11, template can be defined to pass by value, but caller can use ``std::ref`` or ``std::cref`` to pass argument by refernece.
### Pass by reference
- In all cases, there is no copy by passing by reference.
- Arguments never decays.
#### Pass by const reference
- Maybe reloading registers.
- Compiler **cannot** ensure the object passed is not modified. ``const_cast`` may be used.
- Because the parameter is ``const&`` , the type ``T`` itself will not be deduced as ``const``. Thus if a local object is declared as ``T``, it is not ``const``.
```cpp
template<typename T>
void func(T const& arg) { }

std::string const str="Hello";
func(str);		//T -> std::string
func("World");	//T -> char[5]
```
#### Pass by non-const reference
If the argument is a const lvalue, template parameter will be deduced as a ``const`` type. If the argument is a const rvalue, the template parameter will be deduced as a ``const&``, and ``const&`` can be bound to a rvalue, so it can accepts a const rvalue.
```cpp
template<typename T>
void func(T& arg) { }	//We want this template to only deal with non-const reference

std::string const returningConstString() { return std::string const {}; }

std::string const str="Hello";
func(str);		//T -> std::string const
func(returningConstString());	//T -> std::string const
```
In order to deal with it, we can use ``std::enable_if<>`` with ``std::is_const<>``.

#### Pass by forwarding reference
Using a forwarding reference may seems perfect, because it doesn't drop ``const`` qualifier to the referenced object and accepts const lvalue, non-const lvalue, rvalue. **But if the argument is a lvalue (either const or non-const), and the template parameter (deduced as a lvalue reference) is used to declare a local object, it needs a initializer!**
```cpp
template<typename T>
void func(T&& arg) 
{ 
	T x;	//Error if T is lvalue ref and T doesn't have a default initializer!
}

std::string const returningConstString() { return std::string const {}; }
std::string const returningNonConstString() { return std::string  {}; }

std::string non_const_str="Hello";
std::string const const_str="World";
func(non_const_str);	//T -> std::string&				arg-> std::string&
func(const_str);		//T -> std::string const&		arg-> std::string const&
func(returningConstString());//T -> std::string const	arg-> std::string const&&
func(returningNonConstString());//T -> std::string	arg-> std::string&&
```
#### Handling Raw Array & String Literal
If pass by value, raw arrays and string literals decay to pointers, losing the size information.
If pass by reference, raw arrays and string literals do not decay, keeping the size information, but different size are different types.
So the better way is to have partial specialization to handle raw arrays and string literals, so that they are only valid for arrays. Use ``std::decay<>`` to get the element type and use ``std::is_array<>``.
```cpp
template<typename T1, size_t Size1, typename T2, size_t Size2>
void func(T1 (&arg1)[Size1], T2 (&arg2)[Size2]) { }

func("Hello", "world!");	//T1->char	T2->char
```
### Default Function argument
Type of default function argument **does not** work for type deduction. (To use type deduction for default argument, also declare a default template argument for the default function argument)
  
## Multiple Template Parameters
If one of the parameter types is used as the return type, the argument for the other parameter might get converted to this type, regardless of the caller's intention.
```cpp
template<typename T1>
T1 max(T1 a, T2 b){ return b<a? a : b;}
auto m=max(4,7.2);	//int m=7
auto m=max(7.2,4);	//double m=7.2
```
3 ways to solve this problem:
- Introduce another template parameter for the return type
  ```cpp
  template<typename T1, typename T2, typename ReturnType>
  ReturnType max(T1, a, T2 b) {...}
  template<typename ReturnType, typename T1, typename T2>
  ReturnType max2(T1, a, T2 b) {...}
  auto m1=<int, double, double>(4,7.2);	//ReturnType -> double, T1 -> int, T2 -> double
  auto m2=<double>(4,7.2);				//ReturnType -> double, T1 T2 deduced
  ```
  Because all argument types must be specified up to the last one that cannot be determined implicitly (ReturnType here), so in this case, all parameter types needs to be explicitly specified.
- Let compiler find out
  ```cpp
  template<typename T1, typename T2>
  auto max(T1 a, T2 b) { return b<a? a : b; }
  auto m=(4,7.2)	//double m=7.2
  auto m2=(7,1.5)	//double m=7 (because of the ternery operator type)
  ```
  The return type is deduced by the return statement and multiple return statement must match. In this case, if changing the function into if-else, it does not work.
  ```cpp
  template<typename T1, typename T2>
  auto max(T1 a, T2 b)
  {
	  if(a>b)
		return a;
	  else
		return b;
  }
  auto m=(4,7.2)	//Error!
  ```
  In C++11�� only possible way is to use trailing return type
  ```cpp
  template<typename T1, typename T2>
  auto max(T1 a, T2 b) -> decltype(b<a? a : b) { return b<a? a : b;}
  ```
- Declare the return type to be the **common type** of the 2 parameter types
  C++11 provides a means to specify choosing *the more general type*, using std::common_type.
  ```cpp
  #include <type_traits>
  template<typename T1, typename T2>
  std::common_type_t<T1, T2> max(T1 a, T2, b) {return b<a? a : b; }
  ```

## Default Template Arguments
## Overloading Function Templates
Template function can coexist with a non-template function, and can be instantiated with the same type.
1. If implicitly calls a function and there is a perfect match for the non-template function, non-template is called.
2. If no perfect match for non-template function, but there is perfect match for template function or after template type conversions, use template
3. Else, if calls a function with an empty template argument list, only template function will be called.
4. If non-template function is not perfect match, but template function cannot be used by the argument, implicit conversion will be done and call the non-template function. (Because only the nontemplate function allows nontrivial conversions) [Template Type Conversion](#Type-Conversions-During-Type-Deduction)
```cpp
int max(int a, int b) { return b<a? a : b; }

template<typename T>
T max(T a, T b) { return b<a? a : b; }

max(1,2);		//non-template (rule 1)
max(7.0, 42.0);	//template (rule 2)
max<>(1,2);		//template (rule 3)
max(7.0, 42);	//non-template (rule 4)
```

## SFINAE vs Error
SFINAE -> "Substitution failure is not an error" means that only substitution failure will not provide an error if there is one template is suitable. Once a template function is choosed, the argument needs to satisfy all the operation inside the choosed function template, otherwise, an error is occured.
```cpp
template<typename T, unsigned N>
size_t len(T(&)[N])
{
	return N;
}

template<typename T>
size_t len(T const& t)
{
	return t.size();
}

size_t len(...)
{
	return 0;
}

int a[10];
cout<<len(a);	//choose first template (SFINAE the second)
std::vector<int> v;
cout<<len(v);	//choose second template (SFINAE the first)
std::allocator<int> x;
cout << len(x);	//choose second template , Error because no .size() operation
int *p;
cout<<len(p);	//choose third non-template (SFINAE the first and second)
```
In order to get rid of the error of substitution of a tempalte that the argument doesn't satisfy, we can use ``decltype`` to achieve a similar effect of ``std::enable_if<>``, but it applys to the operations inside a template.
```cpp
template<typename T>
auto len(T const& t) -> decltype(t.size(), size_t)	//we require using len function, the argument need to have a .size() member, and the return type of this function template is the last expression of the comma operator
{
	return t.size();
} 

size_t len(...)	//fallback, worst match
{
	return 0;
}
std::allocator<int> x;
cout<<len(x);	//call size_t len(...)
```
# Class Template
## Implementation of A Class Template
```cpp
template<typename T>
class Some_class{};
```
The type of this class is ``Some_class<T>``, with T being a template parameter. **Inside** a class template, using the class name ``Some_class`` is equal to the class with its template parameters as its arguments``Some_class<T>``. Member function implemented inside the template class declaration is called **inline**.
```cpp
template<typename T>
class Some_class
{
public:
	Some_class(Some_class const&);				//copy constructor: Some_class -> Some_class<T>
	Some_class& oeprator=(Some_class const&);	//assignment operator: Some_class -> Some_class<T>
};
```
Outside the class structure, the class template parameter needs to be explicit, thus explicitly specify a member function of a template class is a template.
## Using Class Template
### Partial Usage of Class Template
Until C++17, to use an object of a class template, the template arguments always needs to be specified explicitly. Member functions are **not instantiated** unless they are called. As a result, the template argument type **does not** necessarily provide all possible operations that is used in the class implementation.
```cpp
template<typename T>
class Stack
{
public:
	void print_stack(std::ostream& os) const
	{
		for(T const& element: elems)
			os<<element<<" ";			//T does not need to support std::ostream& operator<<(std::ostream&, T) unless this member function is actually called
	}
}
```
### Concepts
How to know which operations are required for a template to be able to get instantiated? Failures to follow the constraints will lead to terrible error messages. In C++11, you can check for some basic constraints by using ``static_assert`` and ``type_traits``.
```cpp
#include <type_traits>
class Some_class
{
	static_assert(std::is_default_constructible<T>::value, "This class requires default-constructible elements");
};
```
Without the ``static_assert``, the compilation will still fail if the default constructor is required but T does not support it, but the error message will contain the failed assertion to be more readable.
## Warning
If there is reference data member in a class, default assignment operator is **deleted**. Pay special attention when a template parameter is a reference or deduced as a reference. And sometimes, reference non-type template parameter can cause further runtime problems. To disable such possibilities, use ``std::is_reference_v<T>`` with ``static_assert`` or ``SFINAE``.

## Friend
A friend function is **NOT** a class member function. So when defined inside a class, **the class template argument needs to be specified.** 
```cpp
template<typename T>
class Stack
{
public:
	friend std::ostream& operator<<(std::ostream& os, Stack<T> const& s) 
	{
		print_stack(os);
		return os;
	}
}
```
When declare the friend function inside the class and define it afterwards, we have 3 methods:
[A detailed link](https://web.mst.edu/~nmjxv3/articles/templates.html)
- Implicitly declare a new function template, which must use a different template parameter
- Explicitly declare a new function template, which is friend of a template class

## Specialization
### Full Specialization
If you specialize a class template, all member functions needs to be specialized.(Also apply to [Partial Specification](#partial-specialization)) If only some member functions are specialized, you **cannot** speciallize other components of that specialized class. To fully specialize a class template, declare the class with a leading ``template<>`` and a specification of the types for which the class template is specialized.
```cpp
template<>
class Stack<char const*> {
	void some_func();
	// ...
};

template<>
class Stack<int> {
	//Specialized for int Stack
}

void Stack<std::string>::some_func()
{
	//...Specialize some_func for string
}

template<>
class Stack<std::string> {	//ERROR! Cannot re-specialize for Stack<std::string>
}
```
### Partial Specialization
**If you specialize a class template, all member functions needs to be specialized.** Privide special implementation for particular circumstances, but some template parameters can still be defined by the user.
```cpp
template<typename T>
class Stack<T*>
{
	//... Specialized for pointer
}
```
When using partial specialization, be careful of two or more template match the instatiation equally well.
```cpp
template<typename T1, typename T2>
class MyClass { };			//1: the primary template

template<typename T>
class MyClass<T, T> { };	//2: partial specialization when T1==T2

template<typename T>
class MyClass<T, int> { };	//3: partial specialization when T2==int

template<typename T>
class MyClass<T1*, T2*> { };	//4: partial specialization when T1 and T2 are pointers

MyClass<int, int> m;	//match 2 and 3 eqaully well
MyClass<int*, int*>m2;	//match 2 and 4 equally well
```
### Using Partial Specialization

## Type Alias
- ``typedef``
- ``using``
	- ``using`` can create template alias

## Deduction Guide
We can use deduction guide to force the compiler when seeing one particular type, it generate another type we want. Deduction guide start with the template class name and the argument type and an ``->`` to the template class of the type we want. Deduction guide has to be in the same scope (namespace) as the class definition, usually following the class definition. 
``Stack(char const*) -> Stack<std::string>;``

# Nontype Template Parameters
## Restrictions
- Only the following nontype parameters can be used:
  - integral (including enum)
  - pointer
  - lvalue ref to objects/functions
  - std::nullptr_t (type of ``nullptr``)
- String literals (C style string) not allowed
  ```cpp
  template<char const* name>
  class MyClass { };	//Error
  ```
## Nontype Template Argument
Argument for nontype template parameters might be any compile-time expressions.

## Use ``auto`` as template parameter type
Since C++17, you can use ``auto`` as a nontype template parameter to generically accept any type that is allowed for a nontype parameter.
```cpp
template<typename T, auto Maxsize>
class Stack //using Maxsize as the maximum size of the stack
{
public: 
	using size_type=decltype(Maxsize);	//get the type of the nontype template parameter
private:
	size_type maxsize=Maxsize;
	size_type elementNum;
};
```
# Variadic Templates
Variadic template is a template that accpet a variable number of template arguments. A parameter pack is denoted by 3 dots after the keywork ``typename`` before the name of the template parameter name.
```cpp
template<typename T, typename... Types>
void someFunc(T firstArg, Types... args) { }
```
## ``sizeof...()`` operator
C++11 introduced ``sizeof...()`` operator to get the number of elements a parameter pack contains. ``sizeof...()`` operator can be called for both template parameter packs and function parameter packs.
```cpp
template<typename T, typename... Types>
void print(T firstArg, Types... args)
{
	std::cout<<sizeof...(Types)<<'\n';	//print number of remaining types
	std::cout<<sizeof...(args)<<'\n';	//print number of remaining args
}
```
## Fold Expression
A fold expression is a template function that compute the result of using a **binary** operator over all the arguments of a parameter pack with an optional initial value.
```cpp
template<typename... T>
auto foldSum(T... s)
{
	return (...+s);	//compute the sum of ...s
}
```
There are 4 forms of fold expression:
- (...op pack)	->	{[(pack1 op pack2) op pack3]... op packN}
- (pack op ...) ->	{pack1 op [pack2 op ... (packN-1 op packN)]}
- (init op ... op pack)	-> {[(init op pack1) op pack2] op pack3}
- (pack op... op init)	-> {pack1 op [pack2 op ... (packN op init)]}

# Additional Basics
## Zero Initialization
If a local variable is declared without initialization, the value is undefined. When inside a template, because of lack of constructor of built-in primitive types, you need to use a pair of `{}` to zero-initialize a variable.
```cpp
template<typename T>
void someFunc()
{
	T x{};	//x is zero if T is built-in type, or if T is class, uses (explicit) default constrctor
}
```
## Member Function Template
You can define a template member function in a non-template class. And it can be fully specialized or partially specialized. **But member function template is not considered as a special member functions (copy/move constructors, operator=() ) Compiler will still generate the default version.** Constructor is not a special member function, so the constructor can be a template.
```cpp
class Some_class
{
public:
	template<typename T>
	Some_class(T const&)
	{
		std::cout<<"Template copy constructor\n";
	}
};
Some_class x;
Some_class y{x};	//call compiler generated copy constructor!
```
In C++ standard, a copy constructor can never be a template, so delete the compiler generated copy constructor is not a solution. ~~But there is a tricky solution.~~
```cpp
class Some_class
{
public:
	template<typename T>
	Some_class(T const&)
	{
		std::cout<<"Template copy constructor\n";
	}
	Some_class(Some_class const volatile&)=delete;	//delete the volatile const ref version
};
Some_class x;
Some_class y{x};	//call template copy constructor!
```

## Variable Template 
Since C++14, variables can also be parameterized by a specific type. Such a thing is called a variable template.
```cpp
template<typename T>
constexpr T pi{3.14159265358979323845};
```
Variable templates can also have default template arguments. **However, using a variable template with default template argument, the angle brackets still neeeds to be explicitlty specified.**
```cpp
template<typename T=long double>
constexpr T pi{3.14159265358979323845};
std::cout<< pi<> <<'\n';	//std::cout<<pi<<'\n'; is error!
```

## Template Template Parameters
It can be useful to allow a template parameter itself to be a class template, ie. A parameter of a template class is a template.
```cpp
/*Previously, to specify a container for our Stack implementation*/
template<typename T, typename Container>
class Stack
{
	Container elements;
	// ...;
};
Stack<int, std::vector<int>> intStack;	//need to specify std::vector<int>
```
Now we can make the second parameter as a template parameter specifying the internal container of the elements.
```cpp
template<typename T, template <typename Element> typename Container>
class Stack
{
	Container<T> elements;
}
Stack<int, std::vector> intStack;
```
And because the template parameter ``Element`` is not used for ``Container``, it can be omitted.
```cpp
template<typename T, template<typename> typename Container>
class Stack
{
	Container<T> elements;
};
Stack<int, std::vector> intStack;
```
## if constexpr
In C++17, using ``if constexpr()`` makes SFINAE much easier. Different template specialization can be combined into one template and using ``if constexpr()`` to select different operations.

## std::addressof()
When you need to get the pointer of an object that has an overload ``operator&()``, use ``std::addressof()`` instead.

## Callable
Callables can be:
- ordinary functions
- ordinary function pointers
- class types that overload ``operator()()``
- class types that can be converted to a pointer or reference to a function
- lambdas
But calling member functions syntax does not match usual callable syntax using ``()``.
```cpp
class Some_class 
{
public:
	void func();
};
Some_class obj;
obj.func();	//calling member function
Some_class* ptr=&obj;
ptr->func();	//calling member function
```
C++17 introduce ``std::invoke`` that unifies all these cases with ordinary function-call ``()`` syntax.
If the first argument of ``std::invoke`` is a pointer to member function, it uses the second argument as ``this`` object, remaining additional parameters are forwarded to the function. Else, all additional parameters are forwarded to the callable(first argument).
```cpp
std::invoke(&Some_class::func, obj);	//calling member function for obj
```
