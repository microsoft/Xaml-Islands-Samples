using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using UWPApplication;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace Samples.ManagedUWP
{
    public sealed partial class Win32IntegrationPage : Page
    {
        public Win32IntegrationPage()
        {
            this.InitializeComponent();
            UWPApplication.App.OrientationChanged += OnOrientationChanged;
            displayOrientation.Text = Helpers.DisplayInformation.CurrentOrientation.ToString();
        }

        private async void OnOrientationChanged(OrientationChangedEventArgs e)
        {
            if (e.IsLandscape)
            {
                displayOrientation.Text = "Landscape";
            }
            else
            {
                displayOrientation.Text = "Portrait";

            }
        }

    }
}
