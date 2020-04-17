using Contoso.Interop;

namespace UWPApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainUserControl
    {
        private readonly IMainFormInterop mainFormInterop;

        public MainUserControl(IMainFormInterop mainFormInterop)
        {
            this.mainFormInterop = mainFormInterop;
            this.InitializeComponent();
        }

        private void OnGotoWeb(object sender, Windows.UI.Xaml.RoutedEventArgs e)
        {
            this.mainFormInterop.SwitchUI();
        }
    }
}
