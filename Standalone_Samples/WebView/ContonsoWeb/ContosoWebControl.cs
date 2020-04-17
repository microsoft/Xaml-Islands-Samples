using Microsoft.Toolkit.Forms.UI.Controls;
using System.Windows.Forms;
using Contoso.Interop;

namespace ContosoApp
{
    public partial class ContosoWebControl : UserControl
    {
        private readonly IMainFormInterop mainFormInterop;

        public ContosoWebControl(IMainFormInterop mainFormInterop)
        {
            this.mainFormInterop = mainFormInterop;
            InitializeComponent();
            this.webView.Navigate("http://www.microsoft.com");
        }
    }
}
