using Contoso.Interop;
using System.Linq;
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
            var currentControl = this.Controls.OfType<Control>().Single();
            bool currentContentIsXaml = (currentControl == this.mainUserControl);
            var newControl = currentContentIsXaml ? this.WebControl : this.mainUserControl;

            this.SuspendLayout();
            this.Controls.Remove(currentControl);
            this.Controls.Add(newControl);
            this.ResumeLayout(false);
            this.PerformLayout();
        }
    }
}
