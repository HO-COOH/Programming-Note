# Singleton Pattern
## Intro
The singleton pattern is a software design pattern that restricts the instantiation of a class to one **single** instance.
## Implementation
- Scott Meyers' Singleton:  
We define the singleton class such that the only instance can be retrieved by calling ``getInstance()`` method. The consturctor is defined as ``private`` and the class object cannot be copied. In ``C++``, this is achieved by marking the copy constructor and move constructor as ``= delete``.
```cpp
class MySingleton{
private:
    MySingleton();
public:
    MySingleton(MySingleton const&)=delete;
    MySingleton(MySingleton &&)=delete;
    MySingleton& operator=(MySingleton const&)=delete;
    MySingleton& operator=(MySingleton &&)=delete;

    static MySingleton& getInstance()
    {
        static MySingleton obj{};
        return obj;
    }
    void use(){}
};
MySingleton::getInstance().use();   //using the singleton
```
- 
![](./images/1.png)
