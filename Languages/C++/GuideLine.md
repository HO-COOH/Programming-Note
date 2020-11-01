# C++编程核心风格

## 命名
- 首字母大写的类型名
  ``Type`` ``Table`` ``Temperature``
- 变量、对象名不使用大写，多个单词使用下换线 _ 分割
  ``some_variable``
- 注意容易被混淆的数字和字母，如：
  ``0 O o 1 I``
 
## 缩进
### K&R 风格
``` cpp
if(a==b){
    // ...
}
else{
    // ...
}

for(int i=0; i<v.size(); ++i){
    // ...
}

switch(a){
case a:
        // ...
        break;
case b:
        // ...
        break;
default:
        // ...
}

void somefunc()
{
    // ...
}

class Some_class {
public:
        // ...
private:
        // ...
}
```
### 空白
- 通常，在逻辑上明显区分的代码段上加入一个空行  
- 绝对不要在一行上写两个或以上的语句
- 在一个表达式中，当需要强调操作符的运算顺序时用空格  
  ``if(x<0 || max<=x) ``
- 在调用函数时，对于实参，不使用空格隔开，但实参类型（比如函数指针）使用空格隔开  
  ```cpp
  void (*function_pointer)(int, char*, double);
  f(1,'2',3.4);
    ```
- 对于指针，将*紧跟类型后，解释为“某类型的指针”  
  ``int* p``

## 注释
每个文件的开头应该写注释：名字、日期、程序是做什么的

## 声明
- 一行一个声明，大多数情况下在同一行写注释，表明这个变量的作用
- 总是初始化变量，不要在没有一个合适值来初始化之前就声明它
- 不要在循环条件内直接输入一个常数，应该声明一个常量作为循环条件
  ```cpp
    for(int i=1; i<32; ++i) {...} // what is 32?
    //do this
    const int mmax=32;  // explain what is mmax
    for(int i=1; i<mmax; ++i) {...}
  ```


