using Microsoft.Toolkit.Forms.UI.XamlHost;

namespace Contoso.App
{
    public partial class MainUserControl : WindowsXamlHost
    {
        public MainUserControl(Interop.IMainFormInterop mainFormInterop)
        {
            InitializeComponent();
            this.Child = new Xaml.MainUserControl(mainFormInterop);
        }
    }
}
