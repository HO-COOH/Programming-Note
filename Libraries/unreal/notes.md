# 模块
创建一个模块，可以总结为BUILD五个单词
## 构建
在UE中，项目是根据.Target.cs文件和.Build.cs文件来构建的，跟Visual Studio里显示的工程无关，工程只是方便管理文件用的
创建Visual Studio工程可以通过
- GenerateProject.bat
- 右键一个.uproject文件->Generate Visual Studio Project Files

例如要创建一个模块FooBar，在项目文件夹的Source文件夹下新建与模块同名的文件夹FooBar
并在目录下创建一个FooBar.Build.cs，最后的目录应该看起来如下
```
Project Folder
    Source
        FooBar
            FooBar.Build.cs
```
`.Build.cs`文件至少需要包含下面代码
```cs
    using UnrealBuildTool;
    public class FooBar : ModuleRules
    {
        public FooBar(ReadOnlyTargetRules Target) : base(Target)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "Core" });
            //私有依赖使用PrivateDependencyModuleNames.AddRange(new string[]{...});
        }
    }
```
每个uproject都必须至少在私有依赖中依赖Core模块

### 公有依赖public dependency和私有依赖private dependency
- 当别的项目要使用这个模块时，也需要的依赖，需要指定为公有依赖
  
  例如这个模块依赖与某个slate ui控件，需要引入控件的定义
  
  如果把slate定义为私有依赖，会导致无法找到某个slate控件的定义，产生编译错误

- 当别的项目使用这个模块时不需要的依赖，就定义为私有依赖

## 使用
为了让这个模块能被别的模块使用，通常需要把头文件放到Public文件夹中，这样其他模块才可以使用这个模块

实现代码放到Private文件夹中
```
    Project Folder
        Source
            FooBar
                FooBar.Build.cs
                Public
                    MyModuleImpl.h
                Private
                    MyModuleImpl.cpp
```
### 实现
任何的模块都需要一个主类，这个类 类似于单例模式，模块的生命周期即有这个类的生命周期决定
这个主类需要继承自IModuleInterface，并定义两个虚函数
```cpp
    #include "Modules/ModuleInterface.h"
    class FooBarModule : public IModuleInterface
    {
    public:
        virtual void StartupModule() override;
        virtual void ShutdownModule() override;
    };
```
由于`IModuleInterface`来自`Core`模块，所以所有的模块都要至少包含`Core`的依赖

如果其他模块要使用这个模块，可以添加依赖后直接通过`FModuleManager`调用
```cpp
auto foobarModule = FModuleManager::Get().LoadModuleChecked<FooBarModule>();
```
实现一个模块，还需要添加一些注册模块和初始化的代码
习惯上，在Private文件夹下创建一个<模块名>Module.cpp文件，这里创建一个`FooBarModule.cpp`
```
    Project Folder
        Source
            FooBar
                FooBar.Build.cs
                Public
                    MyModuleImpl.h
                Private
                    MyModuleImpl.cpp
                    FooBarModule.cpp
```
在这个文件中，需要把模块的主类暴露给UE，通常使用一个自带的宏
```cpp
IMPLEMENT_GAME_MODULE(FooBarModule, FooBar)
```
`uproject`文件中还要添加对这个模块的描述
```json
    "Modules":
    [
        {
            "Name": "FooBar",
            "Type": "Runtime", //可选的"LoadingPhase": "Default"
        }
    ]
```
关乎`Type`，参考`ModuleDescriptor.h`（`Engine\Source\Runtime\Projects\Public`）中的注释
# 扩展Details Panel
按上面的步骤创建一个Editor模块
## 自定义Struct的呈现形式
```cpp
        class FMyStructCustomization : public IPropertyTypeCustomization
        {
        public:
            static TSharedRef<IPropertyTypeCustomization> MakeInstance()
            {
                return MakeShareable(new FMyStructCustomization);   //其他的初始化操作
            }
            virtual void CustomizeHeader(TSharedRef<IPropertyHandle> structPropertyHandle, class FDetailWidgetRow& headerRow,IPropertyTypeCustomizationUtils& structCustomizationUtils) override
            {
            }
            virtual void CustomizeChildren(TSharedRef<IPropertyHandle> structPropertyHandle, class IDetailChildrenBuilder&structBuilder, IPropertyTypeCustomizationUtils& structCustimizationUtils) override
            {
            }
        };
```
## 自定义整个UObject的呈现形式
```cpp
        class FMyClassCustomization : public IDetailCustomization
        {
        public:
            static TSharedRef<IDetailCustomization> MakeInstance()
            {
                return MakeShareable(new FMyClassCustomization);
            }
            virtual void CustomizationDetails(IDetailLayoutBuilder& builder) override
            {
            }
        };
```
## 注册自定义的类型
在`StartupModule()`中添加
```cpp
        auto& propertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
        //注册一个自定义Struct的呈现形式
        propertyModule.RegisterCustomPropertyTypeLayout(
            <MyStruct>::StaticStruct()->GetFName(),
            FOnGetPropertyTypeCustomizationInstance::CreateStatic(&FMyStructCustomization::MakeInstance) //或任意的函数对象，来构造一IPropertyTypeCustomization
        );
        //注册UObject的呈现形式
        propertyModule.RegisterClassLayout(
            <MyUObject>::StaticClass()->GetFName(),
            FOnGetDetailCustomizationInstance::CreateStatic(&FMyClassCustomization::MakeInstance) //或任意函数对象，来构造一IDetailCustomization
        );
        propertyModule.NotifyCustomizationModuleChanged();
```
在`ShutdownModule()`中添加
```cpp
        if(FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
        {
            auto& propertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
            //注销自定义Struct的呈现
            propertyModule.UnregisterCustomPropertyTypeLayout(<MyStruct>::StaticStruct()->GetFName());
            //注销自定义UObject的呈现
            propertyModule.UnregisterCustomClassLayout(<MyUObject>::StaticClass()->GetFName());
            propertyModule.NotifyCustomizationModuleChanged();
        }
```

# Http 模块
## 发起一个Http请求
```cpp
auto httpRequest = FHttpModule::Get().CreateRequest();
httpRequest->SetURL(TEXT("https://google.com"));
httpRequest->OnProcessRequestComplete().BindStatic(
	+[](FHttpRequestPtr request, FHttpResponsePtr response, bool wasSuccessful)
	{
		auto content = response->GetContentAsString();
		UE_LOG(LogTemp, Warning, TEXT("%s"), *content);
	}
);
httpRequest->ProcessRequest();
```

# Content Browser

# Game
游戏框架

## 角色类
都是Actor的子类
### Pawn
A Pawn is an Actor that can be an "agent" within the world. Pawns can be possessed by a Controller, they are set up to easily accept input, and they can do various and sundry other player-like things. Note that a Pawn is not assumed to be humanoid.
### Character
Pawn的子类。A Character is a humanoid-style Pawn. It comes with a CapsuleComponent for collision and a CharacterMovementComponent by default. It can do basic human-like movement, it can replicate movement smoothly across the network, and it has some animation-related functionality.

## 角色控制类
都是Actor的子类
### Controller
是角色控制类的公共基类，控制一个Pawn
### PlayerController
由玩家控制
### AIController
由电脑控制

## 信息显示类
### HUD
2D的信息显示，通常作为游戏的叠加层
### Camera

## 游戏规则类
### GameMode
`AGameModeBase`类
including things like the game rules and win conditions. It only exists on the server. It typically should not have much data that changes during play, and it definitely should not have transient data that clients need to know about.

真正控制游戏规则的GameMode类的实例只存在于服务器中

一些常用的`AGameModeBase`类方法
- `InitGame()`: 在`AGameModeBase::PreInitializeComponent()`方法调用前被调用
- `PreLogin()` / `PostLogin()`
- `HandleStartingNewPlayer()`
- `RestartPlayer()` / `RestartPlayerAtPlayerStart()` / `RestartPlayerAtTransform()`
- `SpawnDefaultPawnAtTransform()`
- `Logout`

### GameState
The GameState contains the state of the game, which could include things like the list of connected players, the score, where the pieces are in a chess game, or the list of what missions you have completed in an open world game. The GameState exists on the server and all clients and can replicate freely to keep all machines up to date.

GameState应该保存关于游戏进行时本身的信息，而针对于某个玩家的信息应该保存在Player State中

GameState类的实例会存在于服务端和客户端中
一些常用的`AGameStateBase`类方法
- `GetServerWorldTimeSeconds()`
- `PlayerArray` 一个包含所有`APlayerState`对象的数组
- `HasBegunPlay()` 
### PlayerState
表示游戏参与者的状态信息，例如id、当前分数、等级等。AI不会有这样的信息。

## 类与反射
### 类修饰
在声明一个类时，使用Unreal的反射机制可以对类进行修饰，来更改在运行时的行为，例如在蓝图编辑器中是否可见
```cpp
UCLASS(<修饰符>)
class MyClass {...}
```
[所有的修饰符文档](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/GameplayArchitecture/Classes/Specifiers/)

一些常用的修饰符
|修饰符|作用|是否被子类继承
|---|---|---|
|Abstract|表明是个抽象类，防止用户把这个类的对象加到关卡|
|AdvancedClassDisplay|把类的所有属性都放在Advanced栏下，不放到Advanced栏下的属性需要显式的用`SimpleDisplay`修饰
|Blueprintable|可以在蓝图中作为基类使用|*
|NotBlueprintable|不可以在蓝图中作为基类使用（默认值）
|BlueprintType|实例可以在蓝图中作为其他类的属性使用
|ClassGroup="GroupName"|显示在Actor browser中的一个组下面
|Const|类中的所有属性和函数都作为const显示|*
|CustomConstuctor|阻止自动生成构造函数
|Deprecated|标记为弃用，且这个类的实例不会在保存时序列化|*
|HideCategories=(Category1, Category2, ...)|隐藏某个类别的所有属性，要隐藏不属于任何类别的属性，使用这个属性的类名|*
|HideFunctions=(Category1, Category2,...)|隐藏某个Category的全部函数
|HideFunctions=FunctionName|隐藏某个函数

### 函数修饰
`UObject`的方法可以加上函数修饰来引进反射机制
```cpp
UFUNCTION(...)
ReturnType FunctionName(...) {...}
```

[所有的修饰符文档](https://docs.unrealengine.com/4.27/en-US/ProgrammingAndScripting/GameplayArchitecture/Functions/)
一些常用的修饰符
|修饰符|作用
|---|---|
|BlueprintCallable|可以在蓝图中执行
|BlueprintPure|对其所有者（UObject）不做任何修改，而且可以在蓝图中执行
|CallInEditor|在编辑器中显示一个按钮来执行这个函数
|Category="TopCategory\|SubCategory\|..."|属于TopCategory下的SubCategory子分类

### 接口类
为了让一些类拥有共同的接口来，需要继承自一个接口类。UE中要声明一个接口类，实际上要声明两个类：
- 一个以U开头的空类，继承自UInterface类，并添加所需的接口修饰符，这个类的类体只需要一句`GENTERATED_BODY()`宏，不要加任何其他属性或函数，这个类实际不存在，只是为了引入反射机制
- 一个同名，但是以I开头的类，在这个类中添加实际的函数接口声明

接口类中的接口方法可以是：、
- 普通C++虚函数
- BlueprintCallable且BlueprintImplementableEvent（不可以在C++中override，但可以在蓝图中实现）/BlueprintNativeEvent（可以在C++中override一个同名+_Implementation后缀作为函数名的函数，也可以在蓝图实现）二选一的非虚函数
```cpp
UINTERFACE(MinimalAPI, Blueprintable)
class UReactToTriggerInterface : public UInterface //以U开头的空类
{
    GENERATED_BODY()
};

class IReactToTriggerInterface //同名，但以I开头的实际接口类
{    
    GENERATED_BODY()
public:
    /** 接口函数 */
    virtual bool ReactToTrigger(); //普通接口函数，可以在cpp文件中提供一个默认实现

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=Trigger Reaction)
    bool ReactToTriggerCpp(); //可以在子类中override ReactToTriggerCpp_Implementation()，也可以在蓝图中实现

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category=Trigger Reaction)
    bool ReactToTrigger(); //只能在蓝图中实现
};

UCLASS(Blueprintable, Category="MyGame")
class ATrap : public AActor, public IReactToTriggerInstance //实现这个接口的实际类
{
    GENERATED_BODY()
public:
    /*接口override方法*/
}
```
接口修饰符
|修饰符|作用|
|---|---|
|BlueprintType|可以在蓝图中作为变量使用
|DependsOn(Class1, Class2, ...)|在编译这个类之前先编译Class1, Class2...
|MinimalAPI|只导出在这个类的类型信息，不导出它的属性和方法信息，所以实例可以转换到这个类的类型，但不能调用这个类的方法

检查某个实例是否实现了某个接口类
- `bool bIsImplemented = OriginalObject->GetClass()->ImplementsInterface(UReactToTriggerInterface::StaticClass());`
- `bool bIsImplemented = OriginalObject->Implements<UReactToTriggerInterface>();`
- `bool bIsImplemented = (Cast<IReactToTriggerInterface>(originalObject) != nullptr);` 

### 元数据修饰
