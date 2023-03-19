# 注册Win10/Win11右键菜单
## 前言
目前国内少有软件做了Windows11的新右键菜单的集成支持，作者目前见到的有且只有[NanaZip](https://github.com/M2Team/NanaZip)。
经过研究源码发现[NanaZip](https://github.com/M2Team/NanaZip)是一个使用专门的打包工程打包的程序，如图

![](images/nanazip.png) 

图中第一个框是Nanazip的打包项目，第二个框是实现Win11右键菜单集成功能的COM组件项目，
而对于简单的单工程WinUI3使用`msix`打包的项目尚没有找到现有项目使用。

## 原理
根据[这篇微软blog](https://blogs.windows.com/windowsdeveloper/2021/07/19/extending-the-context-menu-and-share-dialog-in-windows-11/)，
在新的右键菜单中添加项目，就要实现一个`IExplorerCommand`接口的COM组件，
该接口的定义在[这里](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-iexplorercommand)

## WinUI3使用msix打包项目
1. 首先像平常一样创建一个WinUI3打包的项目如图
![](images/create-project.png)

![](images/winui3-Project.png)

2. 创建一个dll工程
![](images/create-dll-project.png)

3. 在这个dll工程中右键添加Nuget包，搜索并安装`Microsoft.Windows.ImplementationLibrary`如图
![](images/nuget-package.png)

4. 头文件和链接库
```cpp
#include <wrl/module.h>
#include <wrl/implements.h>
#include <wrl/client.h>
#include <shobjidl_core.h>
#include <wil/resource.h>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <Shlwapi.h>

#pragma comment(lib,"runtimeobject")
#pragma comment(lib, "Shlwapi.lib")
```

5. 实现一个主菜单项，并生成一个guid，如果只需要一个简单的菜单项，则只需实现`IExplorerCommand`接口，如果还需要子菜单，则需要额外实现一个`IEnumExplorerCommand`接口，这里以更复杂的带子菜单项为例
```cpp
/*这个类是子菜单项*/
class TestExplorerSubCommand : public RuntimeClass<RuntimeClassFlags<ClassicCom>, IExplorerCommand>
{
public:
    /*
        在这里实现IExplorerCommand的所有方法
        https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-iexplorercommand
        例如:
    */
    HRESULT GetTitle(IShellItemArray* items, PWSTR* name)
    {
        return SHStrDup(L"哈人", name);
    }

    /*
        某些方法如果不需要，返回E_NOTIMPL，并把相应的输出参数的指针置为空
        例如子菜单项通常不需要返回一个迭代器（通常只有菜单入口项才会有子菜单项）
    */
    HRESULT EnumSubCommands(IEnumExplorerCommand** enumCommands)
    {
        *enumCommands = nullptr;
        return E_NOIMPL;
    }
};

/*这个类是主入口项*/
class __declspec(uuid("3282E233-C5D3-4533-9B25-44B8AAAFACFA")) TestExplorerCommandRoot 
    : public RuntimeClass<RuntimeClassFlags<ClassicCom>, IExplorerCommand, IEnumExplorerCommand>
{
public:
    /*
        实现
        https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-iexplorercommand
        https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nn-shobjidl_core-ienumexplorercommand
        的所有方法
    */
};
```

6. 最后加入Dll的样板代码（boiler plate）
```cpp
CoCreatableClass(TestExplorerCommandRoot)                       //修改这里为主入口菜单类，本例中为TestExplorerCommandRoot
CoCreatableClassWrlCreatorMapInclude(TestExplorerCommandRoot)

STDAPI DllGetActivationFactory(_In_ HSTRING activatableClassId, _COM_Outptr_ IActivationFactory** factory)
{
    return Module<ModuleType::InProc>::GetModule().GetActivationFactory(activatableClassId, factory);
}

STDAPI DllCanUnloadNow()
{
    return Module<InProc>::GetModule().GetObjectCount() == 0 ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _COM_Outptr_ void** instance)
{
    return Module<InProc>::GetModule().GetClassObject(rclsid, riid, instance);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

```

7. 右键主项目的`Package.appxmanifest`文件，并使用XML编辑器打开
![](images/package-manifest.png)

修改下面注释的部分
```xml
<?xml version="1.0" encoding="utf-8"?>

<Package
  xmlns="http://schemas.microsoft.com/appx/manifest/foundation/windows10"
  xmlns:uap="http://schemas.microsoft.com/appx/manifest/uap/windows10"
  xmlns:rescap="http://schemas.microsoft.com/appx/manifest/foundation/windows10/restrictedcapabilities"
  xmlns:desktop4="http://schemas.microsoft.com/appx/manifest/desktop/windows10/4"
  xmlns:desktop5="http://schemas.microsoft.com/appx/manifest/desktop/windows10/5"
  xmlns:com="http://schemas.microsoft.com/appx/manifest/com/windows10"
  IgnorableNamespaces="uap rescap">

  <!-- 这里省略 -->

    <Applications>
        <Application Id="App"
        Executable="$targetnametoken$.exe"
        EntryPoint="$targetentrypoint$">
        <uap:VisualElements>
            <!-- 这里省略 -->
        </uap:VisualElements>

            <Extensions>
                <desktop4:Extension Category="windows.fileExplorerContextMenus">
                    <desktop4:FileExplorerContextMenus>
                        <desktop5:ItemType Type="Directory">
                            <!--如果需要在右键文件夹菜单中出现，添加这个项目，其中Clsid为dll代码中的Guid-->
                            <desktop5:Verb Id="Command1" Clsid="3282E233-C5D3-4533-9B25-44B8AAAFACFA" />
                        </desktop5:ItemType>
                        
                        <desktop5:ItemType Type="*">
                            <!--如果需要在任意文件拓展名中出现，添加这个项目，其中Clsid为dll代码中的Guid-->
                            <desktop5:Verb Id="Command1" Clsid="3282E233-C5D3-4533-9B25-44B8AAAFACFA" />
                        </desktop5:ItemType>
                    </desktop4:FileExplorerContextMenus>
                </desktop4:Extension>

                <com:Extension Category="windows.comServer">
                    <com:ComServer>
                        <com:SurrogateServer DisplayName="TestHandler">
                            <!--下面的Path即为dll的地址，如果设置正确，应该是[项目名].dll-->
                            <com:Class Id="3282E233-C5D3-4533-9B25-44B8AAAFACFA" Path="FastCopyShellExtension.dll" ThreadingModel="STA"/>
                        </com:SurrogateServer>
                    </com:ComServer>
                </com:Extension>
            </Extensions>
        </Application>
    </Applications>
    <!-- 这里省略 -->
</Package>

```

8. 把dll项目生成的Release版本dll拖到到主项目中打包，然后修改文件属性中的`Content`字段为`True`，如图
![](images/dll-property.png)

9. 安装`msix`后运行一次，应该就能看到我们自己的程序被添加到右键菜单中了，不需要重新启动`explorer`进程
![](images/result-file.png)

## 该方法同样适应于Win10
Win10安装`msix`后同样适用
![](images/result-win10.png)