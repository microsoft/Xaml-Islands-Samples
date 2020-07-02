param(
  $project,
  $Configuration="Release",
  $Platform = "x64",
  $BuildAction="ReBuild",
  $Appx_Bundle="Always",
  $Appx_Bundle_Platforms="x64|x86",
  $Appx_Package_Build_Mode="StoreUpload",
  $AppInstallerUri="https://msdn.microsoft.com",
  $RunTimeIdentifiers="`"win-x64`;win-x86`;win10-x64-aot`;win10-x86-aot`"",
  [switch]$onlyRestore
)

if ($null -eq $project)
{
  Write-Host "Usage:"
  Write-Host "   >.\build.ps1 [WinForms|WPF|Native] [-Platform [x86|x64]] [-Configuration [Debug|Release]]"
  return
}
elseif ($project -eq "WinForms")
{
  $Solution_Name = "WinForms_XAMLIslands_v1.sln"
  $Wap_Project_Path="Samples\WinForms\WAP\WAP.wapproj"
}
elseif ($project -eq "WPF")
{
  $Solution_Name = "WPF_XAMLIslands_v1.sln"
  $Wap_Project_Path="Samples\WPF\WAP\WAP.wapproj"
}
elseif ($project -eq "Native")
{
  $Solution_Name = "NativeXamlIslands.sln"
  $Wap_Project_Path="Samples\Win32\SampleCppApp.Package\SampleCppApp.Package.wapproj"
}
else
{
   Write-Error "Invalid project name: $project"
   return
}

function build-internal()
{
  msbuild $Solution_Name /bl:logfile=restore.$project.$Configuration.$Platform.binlog /t:Restore /p:Configuration=$Configuration /p:Platform=$Platform /p:RuntimeIdentifiers=$RunTimeIdentifiers
  if (!$onlyRestore.IsPresent)
  {
    $objFolder = ".\Samples\Win32\SampleCppApp\obj\"
    if (test-path $objFolder)
    {
      rmdir $objFolder -Force -Recurse
    }
    msbuild $Wap_Project_Path /bl:logfile=$project.$Configuration.$Platform.binlog /t:$BuildAction /p:Configuration=$Configuration /p:Platform=$Platform /p:UapAppxPackageBuildMode=$Appx_Package_Build_Mode /p:AppxBundle=$Appx_Bundle /p:AppInstallerUri=$AppInstallerUri /p:RuntimeIdentifiers=$RunTimeIdentifiers
  }
}

build-internal

