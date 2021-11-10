- [语法基础](#语法基础)
- [Generator](#generator)
  - [几个常见的Generator](#几个常见的generator)
    - [Ninja](#ninja)
    - [Unix Makefiles](#unix-makefiles)
- [Project](#project)
- [add_executable](#add_executable)
- [Variables](#variables)
- [Library](#library)
- [Build specification](#build-specification)
- [target_link_libraries](#target_link_libraries)
- [Message](#message)
- [include](#include)
- [GNUInstallDir](#gnuinstalldir)
- [option](#option)
- [CMakePackageConfigHelpers](#cmakepackageconfighelpers)
- [configure_file](#configure_file)
- [Install](#install)
- [list函数](#list函数)
- [find_package](#find_package)
- [Global setup](#global-setup)
  - [FindBoost](#findboost)
  - [Testing](#testing)
    - [CTest](#ctest)
    - [Google Test](#google-test)

# 语法基础
CMake中任何的变量、参数都是字符串，如果字符串中包含空格而且要将这个字符串作为一个整体（例如作为一个参数）时，需要将字符串用双引号括起来作为一个参数

定义一个变量使用函数``set(variableName value)``

给一个变量设置多个值时，就成为了一个list，而list变量实际上是用分号`;`隔开的单个字符串变量，例如下面两个变量设置是完全一样的
```cmake
set(MY_LIST "one" "two")
set(MY_LIST "one;two")
```

要在字符串中要插入变量，使用``${Variable}``

- if
```cmake
if(<cond>)
    <commands>
elseif(<cond>)
    <commands>
else()
    <commands>
endif()
```
    ``cond``为真的情况
    + ON
    + YES
    + TRUE
    + Y
    + 非零数
    + 非0, OFF, NO, FALSE, N, 以及他们的小写的字符串

- while
```cmake
while(<condition>)
  <commands>
endwhile()
```

- foreach
```cmake
foreach(<loop_var> <items>)
  <commands>
endforeach()

# Range
foreach(<loop_var> RANGE <stop>) #loop 0, 1, ..., stop (inclusive)
foreach(<loop_var> RANGE <start> <stop> [<step>])

# List
foreach(<loop_var> IN LISTS <list>)
```
循环一个文件夹中的文件
```cmake
file(GLOB <variable> pattern)
foreach(file <variable>)
  #...
endforeach()
```

- 逻辑运算符
  + ``NOT``
  + ``AND``
  + ``OR``
- 比较运算符
  + ``EQUAL``
  + ``LESS``
  + ``GREATER``
  + ``LESS_EQUAL``
  + ``GREATER_EQUAL``
- 字符串比较
  + ``STREQUAL``
  + ``STRLESS``
  + ``STRGREATER``
  + ``STRLESS_EQUAL``
  + ``STRGREATER_EQUAL``
- 版本比较
  + ``VERSION_EQUAL``
  + ``VERSION_LESS``
  + ``VERSION_LESS_EQUAL``
  + ``VERSION_GREATER``
  + ``VERSION_GREATER_EQUAL``

- function
```cmake
function(<name> [<arg1> ...])
  <commands>
endfunction()
```

- 作用域

  CMake的作用域规不同寻常，当函数体中引用一个全局变量时，这个全局变量的值是在函数调用时计算的
  ```cmake
  function(PrintVar)
      message(${var})
  endfunction()

  set(var 3)
  PrintVar() #3
  ```
  对比
  ```cmake
  set(var 3)
  function(PrintVar)
      message(${var})
  endfunction()

  set(var 4)
  PrintVar() #4
  ```
  在函数调用时，CMake实际上是在函数调用时的全部作用域内变量复制到所调用函数的作用域中，所以在函数中修改这个变量的值不影响原先的变量
  ```cmake
  set(var 3)
  function(PrintVar)
      message(${var}) #4
      set(var 5)
      message(${var}) #5
  endfunction()

  set(var 4)
  PrintVar()
  message(${var}) #4
  ```
  要改变原先变量的值，需要在`set()`调用时加一个`PARENT_SCOPE`参数，加了这个参数以后，set不影响函数作用域内的同名变量的值，这个方法也常用于作为函数的返回值用
  ```cmake
  set(var 3)
  function(PrintVar)
      message(${var}) #4
      set(var 5 PARENT_SCOPE)
      message(${var}) #4
  endfunction()

  set(var 4)
  PrintVar()
  message(${var}) #5
  ```

  ```cmake
  set(var 3)
  function(PrintVar)
      message(${var}) #4
      set(var 5 PARENT_SCOPE)
      set(var 6)
      message(${var}) #6
  endfunction()

  set(var 4)
  PrintVar()
  message(${var}) #5
  ```

  ```cmake
  function(SetVar)
      set(var 5 PARENT_SCOPE)
  endfunction()
      
  SetVar()
  message(${var}) #5，但是这里var显得很突兀，不便于阅读，不推荐这样做
  ```
  更好的做法是使得函数多一个参数只用作返回值
  ```cmake
  function(SetVar result)
      set(result 5 PARENT_SCOPE)
  endfunction()

  SetVar(result)
  message(${result}) #5，这样做使得result的来源更清晰
  ```

- 可变参数函数
  
  可以使用CMake 3.5版本之后的`cmake_parse_arguments()`命令来定义可变参数函数，函数可以有能接收多个值的参数和可选的参数，而且调用函数的参数名可以按任意顺序排列。没有parse到的参数存放在变量`<prefix>_UNPARSED_ARGUMENTS`中，此时往往会产生非预想中的行为，所以应该用`message(WARNING "warning message")`向用户发出警告
  ```cmake
  cmake_parse_arguments
      PARSE_ARGV              #模式
      <N>                     #跳过多少个参数
      <prefix>                #定义变量名的前缀，所以parse后产生的变量名为<prefix>_
      <options>               #可选参数（布尔值）的名称
      <one_value_keywords>    #单值参数
      <multi_value_keywords>  #多值参数
  )
  ```
  在使用这个方法时，通常需要先调用`set()`来定义各个参数名，例如
  ```cmake
  function(Print)
    set(options OPTIONAL)
    set(args ESSENTIAL)
    set(list_args MORE)
    cmake_parse_arguments(
        PARSE_ARGV  #mode
        0           #number of argumets to skip 
        test        #variable prefix
        ${options}
        ${args}        #one-value-keywords
        ${list_args}   #multi-value-keywords
    )   
    
    foreach(arg IN LISTS test_UNPARSED_ARGUMENTS)
        message("Unparsed arguments: ${arg}")        
    endforeach()

    message("ESSENTIAL: ${test_ESSENTIAL}")

    message("OPTIONAL: ${test_OPTIONAL}")

    foreach(item IN LISTS test_MORE)
        message("More: ${item}")
    endforeach()
  endfunction()

  Print(OPTIONAL ESSENTIAL 1 MORE 2 3 4)
  #OPTIONAL -> True, test_ESSENTIAL -> 1, test_MORE -> {2, 3, 4}
  ```

# Generator
CMake generator用来生成原生build system所需的文件，一个project有且只能使用一个generator。使用`cmake --help`可以查看当前平台的默认Generator和可用的Generator。
在windows上的输出：
```
The following generators are available on this platform (* marks default):
* Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 11 2012 [arch] = Generates Visual Studio 2012 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 10 2010 [arch] = Generates Visual Studio 2010 project files.
                                 Optional [arch] can be "Win64" or "IA64".
  Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files.
                                 Optional [arch] can be "Win64" or "IA64".
  Borland Makefiles            = Generates Borland makefiles.
  NMake Makefiles              = Generates NMake makefiles.
  NMake Makefiles JOM          = Generates JOM makefiles.
  MSYS Makefiles               = Generates MSYS makefiles.
  MinGW Makefiles              = Generates a make file for use with
                                 mingw32-make.
  Green Hills MULTI            = Generates Green Hills MULTI files
                                 (experimental, work-in-progress).
  Unix Makefiles               = Generates standard UNIX makefiles.
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  CodeBlocks - MinGW Makefiles = Generates CodeBlocks project files.
  CodeBlocks - NMake Makefiles = Generates CodeBlocks project files.
  CodeBlocks - NMake Makefiles JOM
                               = Generates CodeBlocks project files.
  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  CodeLite - MinGW Makefiles   = Generates CodeLite project files.
  CodeLite - NMake Makefiles   = Generates CodeLite project files.
  CodeLite - Ninja             = Generates CodeLite project files.
  CodeLite - Unix Makefiles    = Generates CodeLite project files.
  Eclipse CDT4 - NMake Makefiles
                               = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - MinGW Makefiles
                               = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
  Kate - MinGW Makefiles       = Generates Kate project files.
  Kate - NMake Makefiles       = Generates Kate project files.
  Kate - Ninja                 = Generates Kate project files.
  Kate - Unix Makefiles        = Generates Kate project files.
  Sublime Text 2 - MinGW Makefiles
                               = Generates Sublime Text 2 project files.
  Sublime Text 2 - NMake Makefiles
                               = Generates Sublime Text 2 project files.
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project files.
```
在Linux上的输出
```
The following generators are available on this platform (* marks default):
  Green Hills MULTI            = Generates Green Hills MULTI files
                                 (experimental, work-in-progress).
* Unix Makefiles               = Generates standard UNIX makefiles.
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  CodeLite - Ninja             = Generates CodeLite project files.
  CodeLite - Unix Makefiles    = Generates CodeLite project files.
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
  Kate - Ninja                 = Generates Kate project files.
  Kate - Unix Makefiles        = Generates Kate project files.
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project files.
```

在调用cmake时加上`-G "<Generator>"` 参数来指定要使用的非默认Generator，注意养成习惯加上双引号，因为多个单词的Generator不加引号会出错，如
```
cmake .. -G "Ninja"
```
## 几个常见的Generator
### Ninja
在`build`目录使用`ninja`构建

### Unix Makefiles
在`build`目录使用`make`构建

`make`读取一个叫`makefile`或`Makefile`（推荐将其命名为`Makefile`因为在使用ls时这个文件会出现在靠前的位置） 的文件，这个文件中定义来一些目标，make根据这些目标所需的文件的修改时间自动判断是否需要重新编译这些文件。
- 命令`make`将构建第一个目标，通常为默认目标，习惯上命名为`default`或`all`
- 命令`make <target>`将构建名为`target`的目标

Makefile的语法：
- 开头通常先定义一些变量，例如编译器、文件名等等，定义的方法是直接使用赋值的语法：变量=值
  ```
  CC=gcc
  CFLAGS=-g -Wall
  ```
  引用变量的值使用$(Name)
- `$(name:string1=string2)`对每个name中的单词，将string1替换为string2
  ```
  SRCS = emitter.c error.c init.c lexer.c main.c symbol.c parser.c
  OBJS = $(SRCS:.c=.o)  #emitter.o error.o init.o ...
  ```
- 用`<target>: <rules>`的语法来定义一个目标的构建方法，其中可以通过列出其他目标来调用构造那些目标的方法
  ```
  all: count  #调用构造count的目标
  count: countwords.o counter.o scanner.o #调用构造countwords.o的目标
      $(CC) $(CFLAGS) -o count countwords.o counter.o scanner.o
  countwords.o: countwords.c
      $(CC) $(CFLAGS) -c countwords.c
  ...
  ```

# Project
```cmake
project(
    <Project-Name>
    [VERSION <major>[.<minor>[.<.patch>[.<tweak>]]]]
    [DESCRIPTION "String"]
    [HOMEPAGE_URL "url"]
    [LANGUAGES [C/CXX/CUDA/OBJC/Fortan/ASM]]
)
```
- ``Project-Name`` 存储在变量``CMAKE_PROJECT_NAME``中
- ``Version``存储在变量
  + ``CMAKE_PROJECT_VERSION``
  + ``CMAKE_PROJECT_VERSION_MAJOR``
  + ``CMAKE_PROJECT_VERSION_MINOR``
  + ``CMAKE_PROJECT_VERSION_PATCH``
  + ``CMAKE_PROJECT_VERSION_TWEAK``
- ``DESCRIPTION``存储在变量``CMAKE_PROJECT_DESCRIPTION``
- ``HOMEPAGE_URL``存储在变量``CMAKE_PROJECT_HOMEPAGE_URL``

# add_executable
有以下3种
- Normal executable
  ```cmake
  add_executable(
      <name>
      [WIN32/MACOSX_BUNDLE] #如果WIN32被指定，则使用WinMain()作为入口点
      [sources...]
  )
  ```
- Imported executables
  ```cmake
  add_executable(
      <name>
      IMPORTED
  )
  ```
- Alias executables
  ```cmake
  add_executable(
      <name>
      ALIAS
      <target>
  )
  ```
  将``name``作为``target``的别名，这个别名可以在接下来的命令中被引用，alias executable不会出现在构建目标中

# Variables
所有cmake自带变量在[here](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html)
- ``CMAKE_CURRENT_SOURCE_DIR`` 返回包含当前这个CMakeLists.txt的文件夹
- ``CMAKE_CURRENT_BINARY_DIR`` 返回包含当前这个CMAKELists.txt所要生成的构建文件的文件夹

```cmake
function(printDir)
    message(${CMAKE_CURRENT_SOURCE_DIR})
    message(${CMAKE_CURRENT_BINARY_DIR})
endfunction()
```
```
[cmake] C:/Users/Peter/Desktop/cmakeTest
[cmake] C:/Users/Peter/Desktop/cmakeTest/build
```
- 系统检测
```
UNIX : is TRUE on all UNIX-like OS's, including Apple OS X and
CygWin

WIN32 : is TRUE on Windows. Prior to 2.8.4 this included CygWin

MSVC: is TRUE on Microsoft Visual C++

APPLE : is TRUE on Apple systems. Note this does not imply the
system is Mac OS X, only that APPLE is #defined in C/C++
header files.

MINGW : is TRUE when using the MinGW compiler in Windows

MSYS : is TRUE when using the MSYS developer environment in Windows

CYGWIN : is TRUE on Windows when using the CygWin version of cmake
```
[cmake_host_system_information](https://cmake.org/cmake/help/latest/command/cmake_host_system_information.html?highlight=cmake_host_system_information)
```cmake
function(printSystemInfo)
    message(${CMAKE_SYSTEM_NAME})
    message(${CMAKE_SYSTEM_PROCESSOR})
    message(${CMAKE_SYSTEM_VERSION})
    cmake_host_system_information(RESULT PhysicalMem QUERY TOTAL_PHYSICAL_MEMORY)
    message(${PhysicalMem})
    message(${WIN32})
    message(${MINGW})
endfunction()
```
```
[build] Windows
[build] AMD64
[build] 10.0.19041
[build] 65488
[build] 1
[build] 1
```
检测编译器的简单方法
```cmake
if(MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-W -Wall -Werror)
endif() 
``` 
- 运行程序

可以在``CMakeLists.txt``中运行其他程序，程序执行的输出到stdout中的结果可以存储到变量中
```cmake
execute_process(COMMAND "vcpkg" "version"
    OUTPUT_VARIABLE result
)
```
``exec_program``在CMake3.0之后的版本后弃用

- 查找程序
```cmake
find_program (
          <VAR> #如果程序存在，则变量存储程序的实际位置，如果不存在，则定义<VAR>-NOTFOUND
          name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
          [HINTS path1 [path2 ... ENV var]]
          [PATHS path1 [path2 ... ENV var]]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
)
```

# Library
有以下5种
- Normal library
  ```cmake
  add_library(
      <name>
      [STATIC/SHARED/MODULE]
      [sources...]
  )
  ```
  + 如果类型没有设置，将被编译成静态或动态库，取决于``BUILD_SHARED_LIBS``变量

- Imported library
  ```cmake
  add_library(
      <name>
      <STATIC/SHARED/MODULE/OBJECT/UNKNOWN> #必须指定一项
      IMPORTED
      [GLOBAL]
  )
  ```

- Alias library
  ```cmake
  add_library(
      <name>
      ALIAS
      <target>
  )
  ```
  将``name``作为``target``库的别名，alias library不会出现在构建目标中
- Interface library
  ```cmake
  add_library(
      <name>
      INTERFACE
      [IMPORTED [GLOBAL]]
  )
  ```
  通常header-only库应该使用这个选项
- Object library
  ```cmake
  add_library(
      <name>
      OBJECT
      <srcs...>
  )
  ```
  生成一个由目标文件（.obj文件）形成的目标文件集合，然后在别的构建目标（比如executable、library目标）中可以通过``name``或者``$<TARGET_OBJECTS:name>``来引用这个目标文件集合，例如
    ```cmake
    #use $<TARGET_OBJECTS:archive>
    add_library(archive OBJECT archive.cpp zip.cpp lzma.cpp)
    add_library(archiveExtras STATIC $<TARGET_OBJECTS:archive> extras.cpp)
    add_executable(test_exe $<TARGET_OBJECTS:archive> test.cpp)
    
    #or use archive
    add_library(archive OBJECT archive.cpp zip.cpp lzma.cpp)
    add_library(archiveExtras STATIC extras.cpp)
    target_link_libraries(archiveExtras PUBLIC archive)
    add_executable(test_exe test.cpp)
    target_link_libraries(test_exe archive)
    ```

# Build specification
- target_include_directories
  ```cmake
    target_include_directories(
        <target> #来源于add_executable()或add_library()，且不能是一个alias
        [SYSTEM] [BEFORE]
        <INTERFACE|PUBLIC|PRIVATE> [items1...]
        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]
    )
  ```
  指定在构建``target``时需要包含的文件夹
- target_compile_definitions
  ```cmake
    target_compile_definitions(
        <target>    #来源于add_executable()或add_library()，且不能是一个alias
        <INTERFACE|PUBLIC|PRIVATE> [items1...]
        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]
    )
  ```
  指定宏定义，在items中，字符串开头的``-D``会被忽略，空字符串也被忽略，例如下面的几条命令是等价的
  ```cmake
    target_compile_definitions(foo PUBLIC FOO)
    target_compile_definitions(foo PUBLIC -DFOO)  # -D removed
    target_compile_definitions(foo PUBLIC "" FOO) # "" ignored
    target_compile_definitions(foo PUBLIC -D FOO) # -D becomes "", then ignored
  ```
- target_compile_options
  ```cmake
    target_compile_options(
        <target>    #来源于add_executable()或add_library()，且不能是一个alias
        [BEFORE]
        <INTERFACE|PUBLIC|PRIVATE> [items1...]
        [<INTERFACE|PUBLIC|PRIVATE> [items2...] ...]
    )
  ```
  指定编译选项

通常来说，在一个库只在内部实现要用到编译选项时，使用``PRIVATE``，在头文件也用到编译选项时，使用``PUBLIC``，只在头文件用到编译选项时，使用``INTERFACE``

- target_compile_features
  ```cmake
    target_compile_features(
        <target>  #来源于add_executable()或add_library()，且不能是一个alias
        <PRIVATE/PUBLIC/INTERFACE> 
        <feature> [...]
    )
  ```

注意使用Visual Studio时不支持在configure time指定构建Release和Debug，必须在build time指定，例如`cmake --build . --config Release`


# target_link_libraries
```cmake
target_link_libraries(
    <targets>...
    <items>...
)
```
``target``必须是来自于``add_executable()``或者``add_library()``，而且不能是一个Alias别名目标

# Message
```cmake
function(printMessage)
    #message(FATAL_ERROR "This is fatal error, will stop cmake processing")
    #message(SEND_ERROR "This is send error. Cmake will continue processing but skip generation")
    message(WARNING "This is warning")
    message(AUTHOR_WARNING "This is cmake warning(dev)")
    message(DEPRECATION "Deprecation only appears if CMAKE_ERROR_DEPRECATED / CMAKE_WARN_DEPRECATED is enabled")
    message(NOTICE "Important message printed to stderr to attract user's attention")
    message(STATUS "The main interesting messages that project users might be interested in. Ideally these should be concise, no more than a single line, but still informative.") 
    # These following message will not be printed
    message(VERBOSE "Detailed informational messages intended for project users. These messages should provide additional details that won’t be of interest in most cases, but which may be useful to those building the project when they want deeper insight into what’s happening.")
    message(DEBUG "Detailed informational messages intended for developers working on the project itself as opposed to users who just want to build it. These messages will not typically be of interest to other users building the project and will often be closely related to internal implementation details.")
    message(TRACE "Fine-grained messages with very low-level implementation details. Messages using this log level would normally only be temporary and would expect to be removed before releasing the project, packaging up the files, etc.")
endfunction()
```

# include
用来运行一个cmake代码文件
```cmake
include(
    <file/module>
    [OPTIONAL]                  #如果设置为OPTIONAL，则当指定文件没找到时不会引起错误
    [RESULT_VARIABLE <var>]     #如果提供了这个参数，则将变量var设置为该文件的路径
)
```
```cmake
include(
    GNUInstallDirs
    RESULT_VARIABLE GNUInstallDirsPath
)
message(${GNUInstallDirsPath})
```
```
C:/msys64/mingw64/share/cmake-3.17/Modules/GNUInstallDirs.cmake
```

# GNUInstallDir
是一个CMake模块，提供了install目标的存储位置

根据GNU标准，文件的安装位置默认如下：
- prefix ``/usr/local``
- exec_prefix 包含机器所需的特殊文件 ``$(prefix)``
- bindir 包含用户所能执行的程序文件 ``/usr/local/bin`` -> ``$(exec_prefix)/bin``
- sbindir 包含用户能在终端中执行的程序文件 ``/usr/local/sbin`` -> ``$(exec_prefix)/sbin``
- libexedir 包含程序文件需要运行的其他文件 ``/usr/local/libexec`` -> ``$(exec_prefix)/libexec``
- datarootdir 包含程序所需的只读且不依赖于具体机器架构的文件 ``/usr/local/share`` -> ``$(prefix)/share``
- sysconfdir 包含程序所需的只读且针对于当前机器的配置文件，通常是ASCII文本文件 ``/usr/local/etc`` -> ``$(prefix)/etc``
- sharedstatedir 包含程序所需读写且不依赖于具体机器架构的文件 ``/usr/local/com`` -> ``$(prefix)/com``
- localstatedir 包含程序所需读写且针对于当前机器的运行时文件，用户不应该修改这些文件 ``/usr/local/var`` -> ``$(prefix)/var``
- runstatedir 包含程序当此执行所需读写且针对于当前机器的运行时文件，这些文件通常在程序执行完毕后就可以销毁 ``/var/run`` -> ``$(localstatedir)/run``
- includedir 用户可以包含的头文件 ``/usr/local/include``，通常只有GCC会查找这个目录
- oldincludedir 除了GCC其他编译器会查找的头文件目录 ``/usr/include``
- docdir 文档文件 ``/usr/local/share/doc/PackageName`` -> ``$(datarootdir)/doc/PackageName``
- infodir 信息文件 ``/usr/local/share/info`` -> ``$(datarootdir)/info``
- htmldir
- dvidir
- psdir 同文档文件，但是可能使用特殊的格式，应该存储到docdir相同的位置
- libdir 目标文件和库文件 ``/usr/local/lib`` -> ``$(exec_prefix/lib)``
- lispdir
- localedir
- mandir ``/usr/local/share/man`` -> ``$(datarootdir)/man``
- man1dir ``$(mandir)/man1``
- man2dir ``$(mandir)/man2``

在cmake中，这个模块定义了2类变量：
- ``CMAKE_INSTALL_<dir>``
- ``CMAKE_INSTALL_FULL_<dir>``

下面是FULL版本在windows上的输出 
```cmake
function(printInstallDir)
    message(${CMAKE_INSTALL_FULL_BINDIR})
    message(${CMAKE_INSTALL_FULL_SBINDIR})
    message(${CMAKE_INSTALL_FULL_LIBEXECDIR})
    message(${CMAKE_INSTALL_FULL_DATAROOTDIR})
    message(${CMAKE_INSTALL_FULL_SYSCONFDIR})
    message(${CMAKE_INSTALL_FULL_SHAREDSTATEDIR})
    message(${CMAKE_INSTALL_FULL_LOCALSTATEDIR})
    message(${CMAKE_INSTALL_FULL_RUNSTATEDIR})
    message(${CMAKE_INSTALL_FULL_INCLUDEDIR})
    message(${CMAKE_INSTALL_FULL_OLDINCLUDEDIR})
    message(${CMAKE_INSTALL_FULL_DOCDIR})
    message(${CMAKE_INSTALL_FULL_MANDIR})
endfunction()
```
```
[cmake] C:/Program Files (x86)/cmakeTest/bin
[cmake] C:/Program Files (x86)/cmakeTest/sbin
[cmake] C:/Program Files (x86)/cmakeTest/libexec
[cmake] C:/Program Files (x86)/cmakeTest/share
[cmake] C:/Program Files (x86)/cmakeTest/etc
[cmake] C:/Program Files (x86)/cmakeTest/com
[cmake] C:/Program Files (x86)/cmakeTest/var
[cmake] C:/Program Files (x86)/cmakeTest/var/run
[cmake] C:/Program Files (x86)/cmakeTest/include
[cmake] /usr/include
[cmake] C:/Program Files (x86)/cmakeTest/share/doc/cmakeTest
[cmake] C:/Program Files (x86)/cmakeTest/share/man
```

# option
```cmake
option(<var> "help text" [ON/OFF])
```
提供一个名叫``var``的选项，可以提供一个默认值，如果没有默认值，将默认为``OFF``，用户可以在cmakecache中选择这个选项，或者在``ccmake``中选择

# CMakePackageConfigHelpers
是一个Cmake模块，用来帮助创建项目的配置文件，以便给其他项目使用本项目

模块中包含2个函数
- configure_package_config_file
```cmake
configure_package_config_file(<input> <output>
  INSTALL_DESTINATION <path>
  [PATH_VARS <var1> <var2> ... <varN>]
  [NO_SET_AND_CHECK_MACRO]
  [NO_CHECK_REQUIRED_COMPONENTS_MACRO]
  [INSTALL_PREFIX <path>]
  )
```
- write_basic_package_version_file
```cmake
write_basic_package_version_file(
    <filename> #应该符合格式：<PackageName>ConfigVersion.cmake
    [VERSION <major.minor.patch>] #通常直接使用${CMAKE_PROJECT_VERSION}
    COMPATIBILITY <
        AnyNewerVersion   #表明可以使用任何比所要求的版本更新的版本，要求满足向后兼容
        |SameMajorVersion #表明使用的版本必须与所要求的版本主版本号一直
        |SameMinorVersion
        |ExactVersion
    >
    [ARCH_INDEPENDENT]  #表明这个项目兼容任何平台，通常只用在header-only库中
)
```

# configure_file
```cmake
configure_file(
    <input> 
    <output>
    [COPYONLY] [ESCAPE_QUOTES] [@ONLY]  #COPYONLY 不能与NEWLINE_STYLE合用
    [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ]
)
```
将``input``文件复制为``output``文件，如果``output``没有指定文件夹，默认复制到``CMAKE_CURRENT_BINARY_DIR``，并将文件中由``#cmakedefine VAR "@value"``宏定义修改为``#define VAR "value"``，其中VAR和value是cmake文件中的同名变量和它的值

# Install
- target
  ```cmake
    install(
        TARGETS targets...
        [EXPORT <export-name>]
        [
          [
             ARCHIVE    #静态库、dll导入库（.lib文件，不是.dll）
            /LIBRARY    #除了dll外的动态库
            /RUNTIME    #可执行文件、dll
            /OBJECTS    #object library，即add_library(<name> OBJECT ...)
            /FRAMEWORK  #macos专属
            /BUNDLE     #macos专属
            /PRIVATE_HEADER
            /PUBLIC_HEADER
            /RESOURCE
          ]
          [DESTINATION <dir>]
          [PERMISSIONS permissions...]
          [CONFIGURATIONS [Debug|Release|...]]
          [COMPONENT <component>]
          [NAMELINK_COMPONENT <component>]
          [OPTIONAL] [EXCLUDE_FROM_ALL]
          [NAMELINK_ONLY|NAMELINK_SKIP]
        ] [...]
        [INCLUDES DESTINATION [<dir> ...]] #当调用install(EXPORT)时，将dir加入到<targets>的INTERFACE_INCLUDE_DIRECTORIES
    )
  ```
- EXPORT
  将名称``<export_name>``与install目标的文件关联起来。要将这些文件实际install，要调用``install(EXPORT)``
- files
```cmake
install(
    <FILES|PROGRAMS> files...
    TYPE <type> | DESTINATION <dir> #选一个
    [PERMISSIONS permissions...]
    [CONFIGURATIONS [Debug|Release|...]]
    [COMPONENT <component>]
    [RENAME <name>] [OPTIONAL] [EXCLUDE_FROM_ALL]
)
```
# list函数
```cmake
Reading
  list(LENGTH <list> <out-var>) # Returns the list's length
  list(GET <list> <element index> [<index> ...] <out-var>) # returns the list of elements specified by indices
  list(JOIN <list> <glue> <out-var>) # 
  list(SUBLIST <list> <begin> <length> <out-var>) # returns a sublist of the given list, if <length> == -1 or the list is smaller than <begin> + <length>, the remaining elements of the list starting at <begin> will be returned 

Search
  list(FIND <list> <value> <out-var>) # returns the index of <value> found in <list> or -1 if not found

Modification
  list(APPEND <list> [<element>...])
  list(FILTER <list> {INCLUDE | EXCLUDE} [REGEX] <regex>)
  list(INSERT <list> <index> [<element>...])
  list(POP_BACK <list> [<out-var>...])
  list(POP_FRONT <list> [<out-var>...])
  list(PREPEND <list> [<element>...])
  list(REMOVE_ITEM <list> <value>...)
  list(REMOVE_AT <list> <index>...)
  list(REMOVE_DUPLICATES <list>) # only the first instance of duplicate element is preserved
  list(
    TRANSFORM 
    <list>
    <
      APPEND/PREPEND/TOUPPER/TOLOWER
      /STRIP        # Remove the leading and trailing spaces from each element of the list
      /GENEX_STRIP  # Strip any generator expressions from each element of the list
      /REPLACE      # Followed with Regex or normal string
    >
    [...]
  ) 

Ordering
  list(REVERSE <list>)    # Reverse the contents of the list in-place
  list(SORT <list> [...]) # 
```

# find_package
``find_package()`` 的查找顺序：

- ``CMAKE_SYSTEM_PREFIX_PATH``
  ```cmake
  foreach(item ${CMAKE_SYSTEM_PREFIX_PATH})
      message(${item})
  endforeach()
  ```

  Windows输出：
  ```
  1> [CMake] C:/Program Files
  1> [CMake] C:/Program Files (x86)
  1> [CMake] C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake
  1> [CMake] C:/Users/Peter/source/repos/CMakeTest/out/install/x64-Debug (default)
  ```

  Linux输出：
  ```
  1> [CMake] /usr/local
  1> [CMake] /usr
  1> [CMake] /
  1> [CMake] /usr
  1> [CMake] /mnt/c/Users/Peter/source/repos/CMakeTest/out/install/WSL-GCC-Debug
  1> [CMake] /usr/X11R6
  1> [CMake] /usr/pkg
  1> [CMake] /opt
  ```


# Global setup

变量``CMAKE_<LANG>_COMPILER_ID``可能的值有
```
Absoft = Absoft Fortran (absoft.com)
ADSP = Analog VisualDSP++ (analog.com)
AppleClang = Apple Clang (apple.com)
ARMCC = ARM Compiler (arm.com)
ARMClang = ARM Compiler based on Clang (arm.com)
Bruce = Bruce C Compiler
CCur = Concurrent Fortran (ccur.com)
Clang = LLVM Clang (clang.llvm.org)
Cray = Cray Compiler (cray.com)
Embarcadero, Borland = Embarcadero (embarcadero.com)
Flang = Flang LLVM Fortran Compiler
G95 = G95 Fortran (g95.org)
GNU = GNU Compiler Collection (gcc.gnu.org)
GHS = Green Hills Software (www.ghs.com)
HP = Hewlett-Packard Compiler (hp.com)
IAR = IAR Systems (iar.com)
Intel = Intel Compiler (intel.com)
MSVC = Microsoft Visual Studio (microsoft.com)
NVIDIA = NVIDIA CUDA Compiler (nvidia.com)
OpenWatcom = Open Watcom (openwatcom.org)
PGI = The Portland Group (pgroup.com)
PathScale = PathScale (pathscale.com)
SDCC = Small Device C Compiler (sdcc.sourceforge.net)
SunPro = Oracle Solaris Studio (oracle.com)
TI = Texas Instruments (ti.com)
TinyCC = Tiny C Compiler (tinycc.org)
XL, VisualAge, zOS = IBM XL (ibm.com)
XLClang = IBM Clang-based XL (ibm.com)
```
变量``CMAKE_CXX_COMPILE_FEATURES``保存了当前编译器所支持的功能列表，可以用一个循环来打印，也可以使用``list()``的相关函数来操作
```cmake
foreach(item ${CMAKE_CXX_COMPILE_FEATURES})
    message(${item})
endforeach()
```

`CMAKE_EXPORT_COMPILE_COMMANDS`可以输出一个`compile_commands.json`文件
包含了所有target生成所需的指令，这个选项仅在使用`Makefile Generator`或`Ninja`生效

## FindBoost
是一个Cmake模块，当调用
```cmake
find_package(Boost
  [version] [EXACT]      # Minimum or EXACT version e.g. 1.67.0
  [REQUIRED]             # Fail with error if Boost is not found
  [COMPONENTS <libs>...] # Boost libraries by their canonical name
                         # e.g. "date_time" for "libboost_date_time"
  [OPTIONAL_COMPONENTS <libs>...]
                         # Optional Boost libraries by their canonical name
)                      # e.g. "date_time" for "libboost_date_time"
```
时会搜索boost库的位置，并定义了几个变量
```
Boost_FOUND            - True if headers and requested libraries were found，当没找到时会定义Boost_NOTFOUND
Boost_INCLUDE_DIRS     - Boost include directories
Boost_LIBRARY_DIRS     - Link directories for Boost libraries
Boost_LIBRARIES        - Boost component libraries to be linked
Boost_<C>_FOUND        - True if component <C> was found (<C> is upper-case)
Boost_<C>_LIBRARY      - Libraries to link for component <C> (may include
                         target_link_libraries debug/optimized keywords)
Boost_VERSION_MACRO    - BOOST_VERSION value from boost/version.hpp
Boost_VERSION_STRING   - Boost version number in x.y.z format
Boost_VERSION          - if CMP0093 NEW => same as Boost_VERSION_STRING
                         if CMP0093 OLD or unset => same as Boost_VERSION_MACRO
Boost_LIB_VERSION      - Version string appended to library filenames
Boost_VERSION_MAJOR    - Boost major version number (X in X.y.z)
                         alias: Boost_MAJOR_VERSION
Boost_VERSION_MINOR    - Boost minor version number (Y in x.Y.z)
                         alias: Boost_MINOR_VERSION
Boost_VERSION_PATCH    - Boost subminor version number (Z in x.y.Z)
                         alias: Boost_SUBMINOR_VERSION
Boost_VERSION_COUNT    - Amount of version components (3)
Boost_LIB_DIAGNOSTIC_DEFINITIONS (Windows)
                       - Pass to add_definitions() to have diagnostic
                         information about Boost's automatic linking
                         displayed during compilation
```
在使用boost库时，还可以用`set()`设置一些选项
```
Boost_USE_DEBUG_LIBS     - Set to ON or OFF to specify whether to search
                           and use the debug libraries.  Default is ON.
Boost_USE_RELEASE_LIBS   - Set to ON or OFF to specify whether to search
                           and use the release libraries.  Default is ON.
Boost_USE_MULTITHREADED  - Set to OFF to use the non-multithreaded
                           libraries ('mt' tag).  Default is ON.
Boost_USE_STATIC_LIBS    - Set to ON to force the use of the static
                           libraries.  Default is OFF.
Boost_USE_STATIC_RUNTIME - Set to ON or OFF to specify whether to use
                           libraries linked statically to the C++ runtime
                           ('s' tag).  Default is platform dependent.
Boost_USE_DEBUG_RUNTIME  - Set to ON or OFF to specify whether to use
                           libraries linked to the MS debug C++ runtime
                           ('g' tag).  Default is ON.
Boost_USE_DEBUG_PYTHON   - Set to ON to use libraries compiled with a
                           debug Python build ('y' tag). Default is OFF.
Boost_USE_STLPORT        - Set to ON to use libraries compiled with
                           STLPort ('p' tag).  Default is OFF.
Boost_USE_STLPORT_DEPRECATED_NATIVE_IOSTREAMS
                         - Set to ON to use libraries compiled with
                           STLPort deprecated "native iostreams"
                           ('n' tag).  Default is OFF.
Boost_COMPILER           - Set to the compiler-specific library suffix
                           (e.g. "-gcc43").  Default is auto-computed
                           for the C++ compiler in use.  A list may be
                           used if multiple compatible suffixes should
                           be tested for, in decreasing order of
                           preference.
Boost_LIB_PREFIX         - Set to the platform-specific library name
                           prefix (e.g. "lib") used by Boost static libs.
                           This is needed only on platforms where CMake
                           does not know the prefix by default.
Boost_ARCHITECTURE       - Set to the architecture-specific library suffix
                           (e.g. "-x64").  Default is auto-computed for the
                           C++ compiler in use.
Boost_THREADAPI          - Suffix for "thread" component library name,
                           such as "pthread" or "win32".  Names with
                           and without this suffix will both be tried.
Boost_NAMESPACE          - Alternate namespace used to build boost with
                           e.g. if set to "myboost", will search for
                           myboost_thread instead of boost_thread.
```
通常的做法是
```cmake
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(<Target> main.cpp)
target_link_libraries(<Target> PRIVATE ${Boost_LIBRARIES})
```

## Testing
### CTest
CTest 是CMake自带的一个工具，通过命令行参数来运行测试用的可执行文件。CTest本身不是一个测试框架，所以通常需要配合其他测试框架例如Google test来使用。通常的做法是使用测试框架来生成一个可执行文件，再由Ctest来运行
### Google Test
`GoogleTest`是一个CMake模块，方便通过CMake来运行相关的单元测试，定义了两个函数
- `gtest_add_tests()`函数通过使用正则表达式并扫描源文件来获取测试项目，当测试代码改变时，通常需要重新运行cmake来配置，由于使用`cmake --build .`时cmake会检测源代码改动，所以，cmake通常会检测到改变并重新生成测试目标，但是如果手动编译，比如使用`make`，此时直接再运行`ctest`就会出问题。注意这个函数在新版cmake中更改了行为，需要`cmake_minimum_required(VERSION 3.10)`，否则会报语法错误
  ```cmake
  gtest_add_tests(
      TARGET target           #测试的可执行文件，通常是一个add_executable()的目标
      [SOURCES src1...]       #当提供了该参数时，只从src1...中获取测试目标，否则从生成target的源文件中获取
      [EXTRA_ARGS arg1...]    #每个测试项目所需的额外参数
      [WORKING_DIRECTORY dir] #指定寻找测试项目的目录，否则使用当前的binary directory
      [TEST_PREFIX prefix]    
      [TEST_SUFFIX suffix]
      [SKIP_DEPENDENCY]
      [TEST_LIST outVar]
  )
  ```
- `gtest_discover_tests()`函数通过扫描生成的可执行文件来获取测试项目，所以当测试代码改变时不需要重新运行cmake
  ```cmake
  gtest_discover_tests(
      target
      [EXTRA_ARGS arg1...]
      [WORKING_DIRECTORY dir]
      [TEST_PREFIX prefix]
      [TEST_SUFFIX suffix]
      [NO_PRETTY_TYPES]
      [NO_PRETTY_VALUES]
      [PROPERTIES name1 value1...]
      [TEST_LIST var]
      [DISCOVERY_TIMEOUT seconds]
      [XML_OUTPUT_DIR dir]
      [DISCOVERY_MODE <POST_BUILD|PRE_TEST>]
  )
  ```