using System.Linq;
using System.Windows.Forms;

namespace Contoso.App
{
    public partial class MainForm : Form, Interop.IMainFormInterop
    {
        private Web.ContosoWebControl webControl;

        public MainForm()
        {
            InitializeComponent();
        }

        private Web.ContosoWebControl WebControl
        {
            get
            {
                if (this.webControl == null)
                {
                    this.webControl = new Web.ContosoWebControl(this)
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

        public ulong WindowHandle
        {
            get
            {
                return (ulong)this.Handle.ToInt64();
            }
        }

    }
}
