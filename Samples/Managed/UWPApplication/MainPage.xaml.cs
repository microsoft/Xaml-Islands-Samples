using System;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace Samples.ManagedUWP
{
    public sealed partial class MainPage : UserControl
    {
        public MainPage()
        {
            this.InitializeComponent();

            //try
            //{
            //    this.InitializeComponent();
            //}
            //catch
            //{
            //    this.InitializeComponent();
            //}
            contentFrame.Navigate(typeof(WelcomePage), null);
        }

        private void NavView_ItemInvoked(NavigationView sender, NavigationViewItemInvokedEventArgs args)
        {
            if (args.IsSettingsInvoked)
            {
                contentFrame.Navigate(typeof(SettingsPage));
                return;
            }

            Type pageType = null;
            NavigationViewItem navViewItem = args.InvokedItemContainer as NavigationViewItem;
            if (navViewItem != null)
            {

                switch (navViewItem.Tag)
                {
                    case "WelcomePage":
                        pageType = typeof(WelcomePage);
                        break;
                    case "BasicInputPage":
                        pageType = typeof(BasicInputPage);
                        break;
                    case "CollectionsPage":
                        pageType = typeof(CollectionsPage);
                        break;
                    case "DateAndTimePage":
                        pageType = typeof(DateAndTimePage);
                        break;
                    case "DialogsAndFlyoutsPage":
                        pageType = typeof(DialogsAndFlyoutsPage);
                        break;
                    case "LayoutPage":
                        pageType = typeof(LayoutPage);
                        break;
                    case "MediaPage":
                        pageType = typeof(MediaPage);
                        break;
                    case "MenuToolbarPage":
                        pageType = typeof(MenuToolbarPage);
                        break;
                    case "TextPage":
                        pageType = typeof(TextPage);
                        break;
                    case "RevealPage":
                        pageType = typeof(RevealPage);
                        break;
                    case "AnimationsPage":
                        pageType = typeof(AnimationsPage);
                        break;
                    case "Win32IntegrationPage":
                        pageType = typeof(Win32IntegrationPage);
                        break;

                }
                if (pageType != null)
                {
                    contentFrame.Navigate(pageType);
                }
            }

        }

        private void NavView_BackRequested(NavigationView sender, NavigationViewBackRequestedEventArgs args)
        {
            if (contentFrame.CanGoBack)
                contentFrame.GoBack();
        }
    }
}
