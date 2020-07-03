using Microsoft.Toolkit.Win32.UI.XamlHost;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace UWPApplication
{
    sealed partial class App : XamlApplication
    {
        public static Action<string> ShowShareUIForWindow;
        public static Action<OrientationChangedEventArgs> OrientationChanged;

        IntPtr windowHandle;
        public IntPtr WindowHandle
        {
            get
            {
                return windowHandle;
            }
            set
            {
                windowHandle = value;
            }
        }


        public App()
        {
            this.Initialize();
        }
    }

    public class OrientationChangedEventArgs
    {
        public bool IsLandscape { get; set; }
    }
}
