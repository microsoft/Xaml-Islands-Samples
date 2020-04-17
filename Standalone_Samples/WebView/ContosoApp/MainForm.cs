using Contoso.Interop;
using System.Windows.Forms;

namespace ContosoApp
{
    public partial class MainForm : Form, IMainFormInterop
    {
        private ContosoWebControl webControl;

        public MainForm()
        {
            InitializeComponent();
        }

        private ContosoWebControl WebControl
        {
            get
            {
                if (this.webControl == null)
                {
                    this.webControl = new ContosoWebControl(this)
                    {
                        Dock = System.Windows.Forms.DockStyle.Fill,
                        Location = new System.Drawing.Point(0, 0),
                        Name = "Contoso Web Control",
                        Size = new System.Drawing.Size(1194, 474),
                        TabIndex = 0,
                        TabStop = false,
                    };
                }
                return this.webControl;
            }
        }

        public void SwitchUI()
        {
            throw new System.NotImplementedException();
        }
    }
}
