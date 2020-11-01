# 语法基础
CMake中任何的变量、参数都是字符串，如果字符串中包含空格而且要将这个字符串作为一个整体（例如作为一个参数）时，需要将字符串用双引号括起来作为一个参数

定义一个变量使用函数``set(variableName value)``

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
```cmake
function(printSystemInfo)
    message(${CMAKE_SYSTEM_NAME})
    message(${CMAKE_SYSTEM_PROCESSOR})
    message(${CMAKE_SYSTEM_VERSION})
    message(${WIN32})
    message(${MINGW})
endfunction()
```
```
[build] Windows
[build] AMD64
[build] 10.0.19041
[build] 1
[build] 1
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

# Global setup
```cmake
if(MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-W -Wall -Werror)
endif() 
``` 
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