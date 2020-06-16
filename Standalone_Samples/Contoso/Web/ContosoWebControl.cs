using System.Windows.Forms;

namespace Contoso.Web
{
    public partial class ContosoWebControl : UserControl
    {
        private readonly Interop.IMainFormInterop mainFormInterop;

        public ContosoWebControl(Interop.IMainFormInterop mainFormInterop)
        {
            this.mainFormInterop = mainFormInterop;
            InitializeComponent();
            this.webView.Navigate("http://www.microsoft.com");
        }

        private void OnGoBackButtonClick(object sender, System.EventArgs e)
        {
            this.mainFormInterop.SwitchUI();
        }
    }
}
