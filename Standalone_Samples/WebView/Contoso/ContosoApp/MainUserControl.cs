using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Toolkit.Forms.UI.XamlHost;

namespace ContosoApp
{
    public partial class MainUserControl : WindowsXamlHost
    {
        public MainUserControl()
        {
            InitializeComponent();
            this.Child = new UWPApp.MainUserControl();
        }
    }
}
