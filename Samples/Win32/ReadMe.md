# Unpackaged native C++/WinRT Win32 Sample

## Overview

This is a complex native C++/WinRT sample to validate several features of XAML Islands v1. 

* [How to use the Keyboard input](#Keyboard)
* [Generatie WinRT resources for Win32 apps](#Resources)
* [How to consume custom third party types](#AppObject)
* [Auto deployment of the Microsoft VC Libs](#VCLib)
* [WinRT free class registration](#WinRT_Registration)

This is how looks like this sample:

![Screenshoot](/1903_Samples/CppWinRT_Win32_App/Screenshoot.PNG)
## Projects in the solution:

* [Main Win32 Windows Application](/1903_Samples/CppWinRT_Win32_App/SampleCppApp/ReadMe.md)
* [UWP Application project](/1903_Samples/CppWinRT_Win32_App//MyApp/ReadMe.md)
* [Sample 3rd party control](/1903_Samples/CppWinRT_Win32_App/SampleUserControl/ReadMe.md)


## <a name="Keyboard"/> How to implement  the Keyboard input </a>

This is an [implementation](/1903_Samples/CppWinRT_Win32_App/SampleCppApp/SampleApp.cpp#L47-L74) of Win32 message loop for an application that contains a set of instances of [DesktopWindowXamlSource](https://docs.microsoft.com/en-us/uwp/api/windows.ui.xaml.hosting.desktopwindowxamlsource)

```C
bool DesktopWindow::NavigateFocus(MSG* msg)
{
    if (const auto nextFocusedIsland = GetNextFocusedIsland(msg))
    {
        WINRT_VERIFY(!nextFocusedIsland.HasFocus());
        const auto previousFocusedWindow = ::GetFocus();
        RECT rect = {};
        WINRT_VERIFY(::GetWindowRect(previousFocusedWindow, &rect));
        const auto nativeIsland = nextFocusedIsland.as<IDesktopWindowXamlSourceNative>();
        HWND islandWnd = nullptr;
        winrt::check_hresult(nativeIsland->get_WindowHandle(&islandWnd));
        POINT pt = { rect.left, rect.top };
        SIZE size = { rect.right - rect.left, rect.bottom - rect.top };
        ::ScreenToClient(islandWnd, &pt);
        const auto hintRect = winrt::Windows::Foundation::Rect({ static_cast<float>(pt.x), static_cast<float>(pt.y), static_cast<float>(size.cx), static_cast<float>(size.cy) });
        const auto reason = GetReasonFromKey(msg->wParam);
        const auto request = winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationRequest(reason, hintRect);
        lastFocusRequestId = request.CorrelationId();
        const auto result = nextFocusedIsland.NavigateFocus(request);
        return result.WasFocusMoved();
    }
    else
    {
        const bool islandIsFocused = GetFocusedIsland() != nullptr;
        byte keyboardState[256] = {};
        WINRT_VERIFY(::GetKeyboardState(keyboardState));
        const bool isMenuModifier = keyboardState[VK_MENU] & 0x80;
        if (islandIsFocused && !isMenuModifier)
        {
            return false;
        }
        const bool isDialogMessage = !!IsDialogMessage(m_hMainWnd, msg);
        return isDialogMessage;
    }
}

int DesktopWindow::MessageLoop(HACCEL hAccelTable)
{
    MSG msg = {};
    HRESULT hr = S_OK;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        const bool xamlSourceProcessedMessage = FilterMessage(&msg);
        if (!xamlSourceProcessedMessage && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            if (!NavigateFocus(&msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    return (int)msg.wParam;
}
```
Dealing with TAB navigation between multiple islands and multiple Win32 elements
```C
void DesktopWindow::OnTakeFocusRequested(winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource const& sender, winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSourceTakeFocusRequestedEventArgs const& args)
{
    if (args.Request().CorrelationId() != lastFocusRequestId)
    {
        const auto reason = args.Request().Reason();
        const BOOL previous =
            (reason == winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::First ||
                reason == winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Down ||
                reason == winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Right) ? false : true;

        const auto nativeXamlSource = sender.as<IDesktopWindowXamlSourceNative>();
        HWND senderHwnd = nullptr;
        winrt::check_hresult(nativeXamlSource->get_WindowHandle(&senderHwnd));

        MSG msg = {};
        msg.hwnd = senderHwnd;
        msg.message = WM_KEYDOWN;
        msg.wParam = GetKeyFromReason(reason);
        if (!NavigateFocus(&msg))
        {
            const auto nextElement = ::GetNextDlgTabItem(m_hMainWnd, senderHwnd, previous);
            ::SetFocus(nextElement);
        }
    }
    else
    {
        const auto request = winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationRequest(winrt::Windows::UI::Xaml::Hosting::XamlSourceFocusNavigationReason::Restore);
        lastFocusRequestId = request.CorrelationId();
        sender.NavigateFocus(request);
    }
}
HWND DesktopWindow::CreateDesktopWindowsXamlSource(DWORD dwStyle, winrt::Windows::UI::Xaml::UIElement content)
{
...
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;
    desktopSource.TakeFocusRequested({ this, &DesktopWindow::OnTakeFocusRequested });
...
}

```

## <a name="Resources"> Generation of WinRT resources for Win32 apps </a>

By default a Windows Store app of a Win32 app that uses 3rd party controls or its own resources requires the generation of a consolidated Resources.pri file.
This is performed by the tool MakePri.exe.
In a UWP App, this only happens when the Appx is generated. However, for Win32 Apps you need to do the following steps:
1. Create a new Blank UWP App
2. Change the output type to be a Dynamic link dll.
3. Change the [AppxPackage](/1903_Samples/CppWinRT_Win32_App/MyApp/Package.appxmanifest#L20) to deploy a dummy exe.
4. Change these [properties](/1903_Samples/CppWinRT_Win32_App/MyApp/MyApp.vcxproj#L18) in your project:
```xml
  <PropertyGroup Label="Globals">
    <WindowsAppContainer>true</WindowsAppContainer>
    <AppxGeneratePriEnabled>true</AppxGeneratePriEnabled>
    <ProjectPriIndexName>App</ProjectPriIndexName>
    <AppxPackage>true</AppxPackage>
  </PropertyGroup>
```
5. In your [main Win32 project](/1903_Samples/CppWinRT_Win32_App/SampleCppApp/SampleCppApp.vcxproj#L248), make sure you deploy the file resources.pri to your output directory:
```xml
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\$(AppProjectName)\resources.pri">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
```
6. Make sure to create a build dependency between your [main Win32 project](/1903_Samples/CppWinRT_Win32_App/SampleCppApp/SampleCppApp.vcxproj) and the [UWP App project](/1903_Samples/CppWinRT_Win32_App/MyApp/MyApp.vcxproj)

## <a name="AppObject"> Use of 3rd party controls </a>

Using 3rd party control objects require:
1. Having a consolidated [resources file](#Resources)
2. A custom application object that:
   1. Registers the Xaml metedata providers.
   2. Initializes Xaml by calling [InitializeForCurrentThread](https://docs.microsoft.com/en-us/uwp/api/windows.ui.xaml.hosting.windowsxamlmanager.initializeforcurrentthread)
   2. Provide [WinRT registration](#WinRT_Registration) of activatable classes.


Make sure to [deploy](/1903_Samples/CppWinRT_Win32_App/SampleCppApp/SampleCppApp.vcxproj#L232-L247) all XAML compiler output from your App in your Win32 app project:
```xml
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\Microsoft.UI.Xaml.Markup\Microsoft.UI.Xaml.Markup.dll">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\SampleUserControl\SampleUserControl.dll">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\$(AppProjectName)\*.xbf">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
    <NativeReferenceFile Include="$(SolutionDir)\bin\$(Platform)\$(Configuration)\$(AppProjectName)\*.dll">
      <DeploymentContent>true</DeploymentContent>
      <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
    </NativeReferenceFile>
```

## <a name="VCLib"> Auto deployment of the Microsoft VC Libs for Win32 applications</a>

The Visual C++ Runtime Libraries are required to execute native applications. In UWP Apps, the Microsoft VC Libs are referenced via Framework packages. The Framework packages are downloaded from the Microsoft Store. Unpackaged Win32 applications are not deployed via Microsoft Store; hence, Framework packages mechanism doesn't work. 

To make it work is needed to deploy the VC Libs to the same folder where the Win32 executable file is deployed.

This is performed using the following [MSBuild code](/1903_Samples/CppWinRT_Win32_App/Microsoft.VCLibs.Win32.targets):
```xml
<?xml version="1.0" encoding="utf-8" ?>
<Project xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
    <PropertyGroup Condition="'$(Configuration)'=='Debug'">
        <VCLibConfig>Debug</VCLibConfig>
        <VCLibConfigName>Debug.</VCLibConfigName>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Configuration)'=='Release'">
        <VCLibConfig>Retail</VCLibConfig>
        <VCLibConfigName></VCLibConfigName>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Platform)'=='Win32'">
        <VCLibPlatform>x86</VCLibPlatform>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Platform)'=='x64'">
        <VCLibPlatform>x64</VCLibPlatform>
    </PropertyGroup>
    <PropertyGroup Condition="'$(Platform)'=='ARM'">
        <VCLibPlatform>ARM</VCLibPlatform>
    </PropertyGroup>
    <PropertyGroup>
        <WindowsKitDir>C:\Program Files (x86)\Microsoft SDKs\Windows Kits\10\</WindowsKitDir>
        <VCLibVersion>14</VCLibVersion>
        <VCLibDir>$(WindowsKitDir)\ExtensionSDKs\Microsoft.VCLibs\$(VCLibVersion).0\Appx\$(VCLibConfig)\$(VCLibPlatform)\</VCLibDir>
        <VCLibName>Microsoft.VCLibs.$(VCLibPlatform).$(VCLibConfigName)$(VCLibVersion).00.appx</VCLibName>
    </PropertyGroup>

    <ItemGroup>
        <VCLibPackage Include="$(VCLibDir)$(VCLibName)" />
    </ItemGroup>

    <Target Name="UnzipVCLibPackage" BeforeTargets="PrepareForBuild">
        <Message Text="Extracting @(VCLibPackage) to $(IntDir)\VCLibs\" />
        <MakeDir Directories="$(IntDir)\VCLibs\" />
        <UnZip SourceFiles="@(VCLibPackage)" DestinationFolder="$(IntDir)\VCLibs\" />
        <CreateItem Include="$(IntDir)\VCLibs\*.dll">
            <Output
                TaskParameter="Include"
                ItemName="VCLibItems"/>
        </CreateItem>
        <Copy SourceFiles="@(VCLibItems)" DestinationFolder="$(OutDir)"/>
    </Target>
</Project>
```
## <a name="WinRT_Registration"> WinRT free registration</a>

In order a 3rd party native type be instanciated by an Win32 executable, the type needs to be registered in the executable manifest.

For example:
```xml
<?xml version="1.0" encoding="utf-8" standalone="yes"?>
<assembly
    xmlns="urn:schemas-microsoft-com:asm.v1"
    xmlns:asmv3="urn:schemas-microsoft-com:asm.v3"
    manifestVersion="1.0">
    <asmv3:file name="MyApp.dll">
        <activatableClass
            name="MyApp.App"
            threadingModel="both"
            xmlns="urn:schemas-microsoft-com:winrt.v1" />
        <activatableClass
            name="MyApp.XamlMetadataProvider"
            threadingModel="both"
            xmlns="urn:schemas-microsoft-com:winrt.v1" />
        <activatableClass
            name="MyApp.MainUserControl"
            threadingModel="both"
            xmlns="urn:schemas-microsoft-com:winrt.v1" />
    </asmv3:file>
</assembly>
```

It is recommended to separate each manifest file per component and have multiple manifest files:

* [MyApp](/1903_Samples/CppWinRT_Win32_App/MyApp/MyApp.manifest)
* [Microsoft UI Xaml](/1903_Samples/CppWinRT_Win32_App/SampleCppApp/Microsoft.UI.Xaml.manifest)
* [Sample User Control](/1903_Samples/CppWinRT_Win32_App/SampleUserControl/SampleUserControl.manifest)

