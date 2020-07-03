using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel.Resources;
using Windows.ApplicationModel.Resources.Core;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace Samples.ManagedUWP
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class WelcomePage : Page
    {
        public WelcomePage()
        {

            this.InitializeComponent();

            //var map = ResourceManager.Current.MainResourceMap.GetSubtree("Managed_WinRT_Comp/Resources");
            //string text = map.GetValue("WelcomeHeader/Text").ValueAsString;
            //Managed_WinRT_Comp.Text = text;

            //var resourceLoader = ResourceLoader.GetForCurrentView("Managed_WinRT_Comp/Resources");
            //string text2 = resourceLoader.GetString("WelcomeHeader/Text");
            //Managed_WinRT_Comp.Text = text2;
            ResourceLoader resourceLoader = null;
            string resourcesPath = "UWPApplication/Resources";
            try
            {
                resourceLoader = ResourceLoader.GetForViewIndependentUse(resourcesPath);
            }
            catch
            {
                Debug.WriteLine($"Resources no found {resourcesPath}");
            }
            if (resourceLoader != null)
            {
                WelcomeDescriptionTB.Text = resourceLoader.GetString("WelcomeDescription/Text");
            }

        }
    }
}
