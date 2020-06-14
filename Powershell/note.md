## 环境
powershell的脚本以``.ps1``作为文件扩展名
开发环境是``Windows Powershell Integrated Scripting Environment (ISE)``

## 命令名
Powershell的命令多使用verb-noun的形式：
+ 使用``Get-Command -Verb Get``列出所有使用``Get``开头的命令
+ 使用``Get-Command -Noun Service``列出所有可以对``Service`` 执行操作的命令

标准参数形式：
Powershell的命令参数以``-``开头，如：
```
Get-Command -Name Clear-Host
```
这个命令中命令是``Get-Command``，参数是``Name Clear-Host``

``?``是标准参数，打印出这条命令的帮助信息

## 命令别名
使用``Get-Alias`` 来打印某个命令别名实际对应的命令
使用``Get-Alias -Definition``来打印某个命令已经定义的命令别名
powershell的标准命令别名：
|Noun or Verb |Abbreviation|
------------- |------------|
Get           | g
Set           | s
Item          | i
Location      | l
Command       | cm
Alias         | al

powershell定义了一些命令别名来简化输入传统cmd和unix中的常见命令：
|cat   |dir     |mount  |rm    |
-------|-----   |-------|-------
| cd   |echo    |move   |rmdir | 
|chdir |erase   |popd   |sleep |
|clear |h       |ps	    |sort  |
|cls   |history	|pushd	|tee   |
|copy  |kill	|pwd	|type  |
|del   |lp	    |r	    |write |
|diff  |ls	    |ren	|

使用``Set-Alias -Name [alias] -Value [Command] ``命令来将``alias`` 作为``Command``的别名

## 帮助信息
使用``Get-Help Command``或``Command -?``获取``Command``命令的帮助信息
``Get-Help``可选参数：
- ``Detailed``
- ``Full``
- ``Examples``
- ``Online``
- ``ShowWindow`` 新建一个窗口来显示

在使用这个命令时，系统首先查找有无直接匹配的命令，如果没找到再查找所有帮助文档中出现了相同单词的命令

使用``Update-Help``命令来更新帮助文档，需要管理员权限

注意：
如果使用``Get-Help`` 来查找相关命令，最好在待查找的命令两头都加上星号``*``，如``Get-Help *process*``，虽然此时powershell会自动加上，所以效果与没加相同，但是如果手动在中间加了星号，则powershell不再会自动给命令两头加星号
## 计时
``Measure-Command {待计时的指令}``

## 其他框架
- WMI (Windows Management Instrumentation)
- CIM (Common Information Model)：所有CIM框架的命令都包含在CimCmdlets模块中，可以通过``Get-Command -Module CimCmdlets``获取全部命令。CIM被设计为同时兼容windows和非windows操作系统


## 脚本基础
### 安全
Windows 10的默认执行策略是Restricted，防止用户执行未知的脚本，Server系统的默认执行策略是RemoteSigned，这个策略才允许执行脚本
- 查看执行策略使用命令``Get-ExecutionPolicy``
- 修改执行策略使用命令``Set-ExecutionPolicy -ExecutionPolicy RemoteSigned``
### 输入输出
- ``Write-Output``输出到一个管道中，这个管道默认是当前终端，不过可以被重定向，也可以作为下一个命令的输入参数
- ``Write-Host``输出到当前终端
- ``Format-List``或``Format-Table``将命令的输出（管道）整理成列表或者表格的形式，注意格式化后的输出不可以作为大多数命令的输入，所以注意通常在一串命令的最后才格式化

### 类型
获取一个对象的类型，使用``$obj.GetType()``

内置类型：
- System.Int32
- System.Int64
- System.Double
- System.Single (需要用(float)强制类型转换才能得到)
- System.Decimal
- System.String
Powershell的String使用16位Unicode编码
由于Powershell的字符串使用双引号或单引号括起来，字符串要包含双引号或单引号可以用如下方法：
```ps
"Embed double quote like this "" or this `" "
->Embed double quote like this " or this "
'Embed single quote like this '' '
->Embed single quote like this '
```
Powershell的双引号字符串可以将变量名替换为它们的值
```ps
$foo = "BAR"
"This is a string in double quotes: $foo"
-> This is a string in double quotes: BAR
```
由于双引号字符串需要额外处理，所以不需要做变量替换时应默认使用单引号字符串提高性能

- System.Collections.IDictionary
- System.Collections.Hashtable

哈希表的形式为``@{keyName = valueName; ...}``，键值对由分号``;``分隔，也可以用空行分隔
正式语法：`` <hashLiteral> = '@{' <keyExpression> '='  <pipeline> [ <separator> <keyExpression> '=' <pipeline> ] * '}' ``

```ps
PS> $user = @{ FirstName = 'John'; LastName = 'Smith';
PhoneNumber = '555-1212' }
PS> $user

Key                            Value
---                            -----
LastName                       Smith
FirstName                      John
PhoneNumber                    555-1212
```
### 变量
``$variable``声明一个变量名叫``variable``  
可以在声明变量时初始化并赋值``$variable = value``, 例如：``$location=Get-Location``  
使用这个变量使用与声明变量相同的语法``$variable``  
可以手动声明变量的类型``[Type]$var = value``

### 成员
使用``$variable | Get-Member``获取变量的成员
### 运算符
- 算术：+-*/%
- 比较：注意比较运算符前要加``-`` eq, ne, gt, ge, lt, le
- 赋值：=, +=, -=, ++, --
- 逻辑：注意逻辑运算符前要加``-`` AND, OR, NOT
- 重定向：``>``将输出重定向到指定的文件或设备
- 匹配：都要加``-``
   + Like：接包含通配符的字符串，如带``*``的字符串
   + NotLike
   + Match：接正则表达式
   + NotMatch
- 集合：都要加``-``
   + Contains
   + NotContains
   + In
   + NotIn
   + Replace，如`` `PowerShell` -replace `Shell`, `Bash` ``
- 范围：``..``，如``1..10``表示1~10的10个数字

注意：以上所有运算符在匹配字符串时都是不区分大小写，要区分大小写在所有运算符名前加字母c

### 语句
1. if
```ps
$x = 30

if($x -eq 10)
{
   write-host("Value of X is 10")
} 
elseif($x -eq 20)
{
   write-host("Value of X is 20")
} 
elseif($x -eq 30)
{
   write-host("Value of X is 30")
} 
else 
{
   write-host("This is else statement")
}
```

2. while
```ps
$array = @("item1", "item2", "item3")
$counter = 0;
while($counter -lt $array.length)
{
   $array[$counter]
   $counter += 1
}
```

3. do...while
```ps
$array = @("item1", "item2", "item3")
$counter = 0;

do {
   $array[$counter]
   $counter += 1
} while($counter -lt $array.length)
```

4. do...until
``until``条件为假时退出循环

5. for
```ps
$arr = @("hello", "world", "you", "bad")
for($i=0; $i -le $arr.length; ++$i)
{ $arr[$i] }
```

6. foreach
```ps
$arr = @("hello", "world", "you", "bad")
foreach($word in $arr)
{ $word }
```
``foreach``循环与``ForEach-Object``终端命令相对应

7. switch
powershell的switch语句需要用花括号将分支括起来，所以不需要``break``结束与其他分支比较
```ps
switch (3)
{
    1 {"It is one."}
    2 {"It is two."}
    3 {"It is three."}
    4 {"It is four."}
}
```

### 注释
- 单行注释用``#``开始
- 多行注释用``<#``开始到``#>``结束

### 数组
使用``,``分隔数组元素
```ps
$arr=1,2,3,4,5
```
数组的类型是元素类型加``[]``，比如整形数组的类型是``[int[]]``

### 函数
```ps
function SomeFunction #函数由function关键字加函数名开始
{
   param($parameterName)   #参数
}
```
函数可以定义返回类型，类型不同的返回值会被强制类型转换

#### 函数的命名
最好遵循powershell的命名约定，由<Verb>-<Prefix><SingularNoun>的形式组成  
可以用命令``Get-Verb``查看所有约定的Verb部分

### 类和对象
Powershell5.0开始支持自定义类
#### 类的声明和定义
- 使用``class``关键字加类名来定义一个新类，使用``[类名]::new()``来创建一个对象  
- 类的数据成员都是对外可见的（public），但是可以用``Hidden``关键字隐藏数据和方法成员，使得在``Get-Member``中不可见，但是在使用``Get-Member -Force``时还会可见
- 类中可以用``static``关键字定义数据成员和方法成员
- 在类的方法中，使用``$this``来指代类的数据成员
- 类的构造函数与类名相同
- 一个类可以有多个构造函数来重载
```ps
class Person 
{
    [string]$fName   #数据成员
    [string]$lName   #数据成员
    static [int]$count=0
    Person($fname, $lname)
    {
        $this.fName=$fname
        $this.lName=$lname
        ++$this.count 
    }
    SayHello()
    {
        Write-Host("Hello $($this.fName), $($this.lName)")
    }
}
#创建一个Person类对象
$me=[Person]::new("Sz","Peter")
$me.SayHello() #调用成员方法
```
#### 继承
要继承一个基类，在类声明后加冒号和基类名``class Derived:Base``  
在派生类的构造函数头后用``base(Argument)``调用基类的构造函数，如果基类可以默认构造则无需显式调用基类的构造函数
```ps
class Base
{
    [int]$a
    Base([int]$num)
    {
        $this.a=$num
    }
}
class Derived
{
    Derived():base(100){}   #调用基类的构造函数
}
```
powershell中的类方法默认都是virtual，所以可以override基类的方法
```ps
class baseClass
{
    [int]foo() {return 100500}
}

class childClass1 : baseClass
{
    [int]foo() {return 200600}
}

[childClass1]::new().foo() # return 200600
```
在派生类中调用基类的方法，先做一个强制类型转换``([Base]$this).SomeMethod()``
#### 接口类 interface
一个类可以继承多个接口，继承接口与继承基类的语法相同，而且继承接口需要重写接口所定义的所有方法，例如继承``System.IComparable``接口。
```ps
class MyComparable:System.IComparable
{
    [int] CompareTo([object]$obj)
    {
        #...
    }
}
```
powershell目前不支持自定义接口类

### 枚举类型
定义一个枚举类型用``enum``关键字加枚举类型名，可以给枚举值提供整数值，powershell中的枚举值只能是整数常量，不能是其他类型
如果没有给枚举值定义数值，将默认从0开始，如果定义了数值，将从那个定义了数值的枚举值向下+1递增
```ps
enum  Color
{
    RED
    GREEN
    BLUE=[int]::MaxValue
}
$color=[Color]::RED
```
由于枚举值是整数，所以枚举值可以与整数做算术运算
```ps
$color2=[Color]::GREEN + 1
Write-Host($color2) # -> 2
```
### 模块
- ``using namespace <NameSpace>``
- ``using module <module>`：引入模块中所有的函数、变量、类
- ``using assembly <assembly-path>``

## 远程管理
单主机远程管理：
1. 要使用powershell进行远程管理，必须先使用命令``Enable-PSRemoting``启用这项功能
2. 获取域管理员权限``$cred=Get-Credential``
3. 建立一个powershell连接``Enter-PSSession -ComputerName name -Credential $cred``
此时如果成功连接，终端会输出新的远程主机名：
```ps
[dc01]: PS C:\Users\Administrator\Documents>
```
4. 结束连接``Exit-PSSession``


可以同时对多个远程计算机执行同一条命令：
```ps
Invoke-Command -ComputerName c1, c2, c2 {SomeCommand} -Credential $cred
```
Invoke-Command实际会返回一个与在本地计算机执行这条命令的结果完全相同的对象，比如：
```ps
Invoke-Command -ComputerName dc01, sql02, web01 {Get-Service -Name W32time} -Credential $Cred | Get-Member
```
终端会返回``TypeName: Deserialized.System.ServiceProcess.ServiceController ...``

多主机远程管理：
1. 创建一个Session对象，同时连接到多个远程主机
```ps
$session = New-Session -ComputerName c1, c2, c3 -Credential $cred
```
2. 使用``Invoke-Command``命令的``-Session``参数发送命令
```ps
Invoke-Command -Session $session {Command}
```
3. 关闭Session对象``Get-PSSession | Remove-PSSession``




``New-CimSession -ComputerName xx -Credential (Get-Credentiall)``

``Get-SimInstance -CimSession $session -ClassName xx``

``Get-CimSession | Remove-CimSession``
