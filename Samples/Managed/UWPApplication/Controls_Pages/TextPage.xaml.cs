using System;
using System.Collections.Generic;
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
    public sealed partial class TextPage : Page
    {
        public TextPage()
        {
            this.InitializeComponent();
            CoreWindow.GetForCurrentThread().CharacterReceived += App_CharacterReceived;
            CoreWindow.GetForCurrentThread().KeyDown += App_KeyDown;
            CoreWindow.GetForCurrentThread().PointerPressed += App_PointerPressed;
        }
        private void App_PointerPressed(CoreWindow sender, PointerEventArgs args)
        {
            System.Diagnostics.Debug.Write($"PR:{args.CurrentPoint.ToString()} ");
        }

        private void App_KeyDown(CoreWindow sender, KeyEventArgs args)
        {
            System.Diagnostics.Debug.Write($"KD:{args.VirtualKey} ");
        }

        private void App_CharacterReceived(CoreWindow sender, CharacterReceivedEventArgs args)
        {
            System.Diagnostics.Debug.Write($"CR:{args.KeyCode} ");
        }

        private void AutoSuggestBox_TextChanged(AutoSuggestBox sender, AutoSuggestBoxTextChangedEventArgs args)
        {
            if (args.Reason == AutoSuggestionBoxTextChangeReason.UserInput)
            {
                List<string> suggestions = new List<string>()
                {
                    sender.Text + "1",
                    sender.Text + "2"
                };
                Control1.ItemsSource = suggestions;
            }
        }

        private void AutoSuggestBox_SuggestionChosen(AutoSuggestBox sender, AutoSuggestBoxSuggestionChosenEventArgs args)
        {
            //SuggestionOutput.Text = args.SelectedItem.ToString();
        }

       
    }
}
