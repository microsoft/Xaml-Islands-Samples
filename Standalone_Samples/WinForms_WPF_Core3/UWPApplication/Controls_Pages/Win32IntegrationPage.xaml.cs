using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using UWPApplication;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.ViewManagement;
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

            UWPApplication.App.OrientationChanged += OnWin32OrientationChanged;
            displayOrientationWin32.Text = Helpers.Win32.DisplayInformation.CurrentOrientation.ToString();

            Windows.Graphics.Display.DisplayInformation.GetForCurrentView().OrientationChanged += OnOrientationChanged;
            displayOrientationUWP.Text = Windows.Graphics.Display.DisplayInformation.GetForCurrentView().CurrentOrientation.ToString();
        }

        private void OnOrientationChanged(Windows.Graphics.Display.DisplayInformation sender, object args)
        {
            if (sender.CurrentOrientation == Windows.Graphics.Display.DisplayOrientations.Landscape)
            {
                displayOrientationUWP.Text = "Landscape";
            }
            else if (sender.CurrentOrientation == Windows.Graphics.Display.DisplayOrientations.Portrait)
            {
                displayOrientationUWP.Text = "Portrait";
            }
        }

        private void OnWin32OrientationChanged(OrientationChangedEventArgs e)
        {
            if (e.IsLandscape)
            {
                displayOrientationWin32.Text = "Landscape";
            }
            else
            {
                displayOrientationWin32.Text = "Portrait";
            }
        }
    }
}
