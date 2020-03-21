using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace Samples.ManagedUWP
{

    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class CollectionsPage : Page
    {
        private Deferral RefreshCompletionDeferral
        {
            get;
            set;
        }
        private DispatcherTimer timer = new DispatcherTimer();

        ObservableCollection<string> items = new ObservableCollection<string>();
        public CollectionsPage()
        {
            this.InitializeComponent();

            timer.Interval = new TimeSpan(0, 0, 0, 0, 500);
            timer.Tick += Timer_Tick;

            for (int i = 0; i < 20; i++)
            {
                items.Add(Helpers.WordGenerator.Generate());
            }

            listview.ItemsSource = items;
        }


        private void rc_RefreshRequested(RefreshContainer sender, RefreshRequestedEventArgs args)
        {
            this.RefreshCompletionDeferral = args.GetDeferral();
            timer.Start();

        }
        private void Timer_Tick(object sender, object e)
        {

             Timer_TickImpl();
        }
        private void Timer_TickImpl()
        {
            items.Insert(0, Helpers.WordGenerator.Generate());
            timer.Stop();
            if (this.RefreshCompletionDeferral != null)
            {
                this.RefreshCompletionDeferral.Complete();
                this.RefreshCompletionDeferral.Dispose();
                this.RefreshCompletionDeferral = null;
            }
        }

        private void AddingWordToListBtn(object sender, RoutedEventArgs e)
        {
            items.Insert(0, Helpers.WordGenerator.Generate());
        }
    }
}
