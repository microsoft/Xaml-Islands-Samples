# MFC XAML Island sample

This sample demonstrates how to use UWP XAML and WinUI 2 controls inside of a MFC MDI app.

### MFCApp 

This project is the MFC MDI app with XamlIsland. It loaded Windows::UI::Controls and WinUI 2 (Windows::UI::Controls) through  a Windows Runtime Component.

It follows the [guide](https://github.com/marb2000/XamlIslands/tree/master/1903_Samples/CppWinRT_Win32_SingleIsland)  to copy xbf, dll, pri files from MyApp and Winows Runtime Components.

### MyApp (Universal Windows)

Both a UWP Blank app and a custom Application object are required to use UWP XAML and WinUI 2 controls. 
To generate a UWP Application, this sample is using the template for a UWP Application in C++. Also, you need to modify the project and do some changes on the classes to use it within XAML Islands v1: 

- It has to compile as a Dynamic Link Library instead of an Executable.

- The XAML Application object has to inherit from Microsoft.UI.Markup.XamlApplication instead of Windows.UI.Xaml.Application. The XamlApplication object comes from Microsoft.Toolkit.Win32.UI.XamlHost Nuget Package. For instance, in the sample the namespace was Toolkit="using:Microsoft.Toolkit.Win32.UI.XamlHost" was added, and the <Application> becomes <Toolkit:XamlApplication>
  
```xml
<Toolkit:XamlApplication
    x:Class="MyApp.App"
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:local="using:MyApp"
    xmlns:Toolkit="using:Microsoft.Toolkit.Win32.UI.XamlHost"
    xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
    xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
    RequestedTheme="Light"
    mc:Ignorable="d">
    <Toolkit:XamlApplication.Resources>
        <XamlControlsResources xmlns="using:Microsoft.UI.Xaml.Controls"/>
    </Toolkit:XamlApplication.Resources>
</Toolkit:XamlApplication>
```
- The build settings have been modified to produced resources.pri and AppxManifest at build time. If your app doesn't have app manifest with the <maxversiontested Id="10.0.18632.0"/>, the build will generate it for you. These MSBuild properties allow you to activate/deactivate this autogeneration. 
```xml
  <PropertyGroup Label="Globals">
    <WindowsAppContainer>true</WindowsAppContainer>
    <AppxGeneratePriEnabled>true</AppxGeneratePriEnabled>
    <ProjectPriIndexName>App</ProjectPriIndexName>
    <AppxPackage>true</AppxPackage>
  </PropertyGroup>
```

### MFCApp.Package
Some Windows 10 APIs require a Package Identity to work, also this MSIX package generates a package manifest that includes the <maxversiontested Id="10.0.18632.0"/> required for XAML Islands.