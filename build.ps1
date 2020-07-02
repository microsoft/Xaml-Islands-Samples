param(
  $project = "WinForms",
  $Configuration="Release",
  $Platform = "x64",
  $BuildAction="ReBuild",
  $Appx_Bundle="Always",
  $Appx_Bundle_Platforms="x64|x86",
  $Appx_Package_Build_Mode="StoreUpload",
  $AppInstallerUri="https://msdn.microsoft.com",
  [switch]$onlyRestore
)

if ($project -eq "WinForms")
{
  $Solution_Name = "WinForms_XAMLIslands_v1.sln"
  #$Wap_Project_Directory="Samples\WinForms\WAP"
  $Wap_Project_Path="Samples\WinForms\WAP\WAP.wapproj"
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
  msbuild $Solution_Name /bl:logfile=restore.$Configuration.$Platform.binlog /t:Restore /p:Configuration=$Configuration /p:Platform=$Platform /p:RuntimeIdentifiers=`"win-x64`;win-x86`;win10-x64-aot`;win10-x86-aot`"
  if (!$onlyRestore.IsPresent)
  {
    msbuild $Wap_Project_Path /bl:logfile=wap.$Configuration.$Platform.binlog /t:$BuildAction /p:Configuration=$Configuration /p:Platform=$Platform /p:UapAppxPackageBuildMode=$Appx_Package_Build_Mode /p:AppxBundle=$Appx_Bundle /p:AppInstallerUri=$AppInstallerUri /p:RuntimeIdentifiers=`"win-x64`;win-x86`;win10-x64-aot`;win10-x86-aot`"
  }
}

build-internal

