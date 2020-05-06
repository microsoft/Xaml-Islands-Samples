using Helpers;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Forms;
using Windows.ApplicationModel.DataTransfer;

namespace MyWinFormsApp
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            this.windowsXamlHost1.Child = new Samples.ManagedUWP.MainPage();
            this.Load += MainForm_Load;
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            //Using WinRT DataTransferManager in Win32
            IntPtr hwnd = this.Handle;
            var dtm = DataTransferManagerHelper.GetForWindow(hwnd);
            dtm.DataRequested += OnDataRequested;
            UWPApplication.App.ShowShareUIForWindow += ShowShareUI;

            //Detect Orientation
            Microsoft.Win32.SystemEvents.DisplaySettingsChanged += SystemEvents_DisplaySettingsChanged;

        }
        #region Using WinRT DataTransferManager in Win32
        string _text;
        private void ShowShareUI(string text)
        {
            IntPtr hwnd =this.Handle;
            DataTransferManagerHelper.ShowShareUIForWindow(hwnd);
            _text = text;
        }
        async void OnDataRequested(DataTransferManager sender, DataRequestedEventArgs args)
        {
            var deferral = args.Request.GetDeferral();

            try
            {
                DataPackage dp = args.Request.Data;
                dp.Properties.Title = _text;
                dp.SetText(_text);
            }
            finally
            {
                deferral.Complete();
            }
        }
        #endregion

        #region Detect Orientation

        private void SystemEvents_DisplaySettingsChanged(object sender, EventArgs e)
        {
            if (SystemParameters.PrimaryScreenWidth > SystemParameters.PrimaryScreenHeight)
            {
                UWPApplication.App.OrientationChanged(new UWPApplication.OrientationChangedEventArgs() { IsLandscape = true });
            }
            else
            {
                UWPApplication.App.OrientationChanged(new UWPApplication.OrientationChangedEventArgs() { IsLandscape = false });

            }
        }
        #endregion
    }
}
