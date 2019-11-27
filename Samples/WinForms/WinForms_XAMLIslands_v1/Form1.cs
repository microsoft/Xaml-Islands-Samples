using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinForms_XAMLIslands_v1
{
    public partial class Form1 : Form
    {
        private Microsoft.Toolkit.Forms.UI.XamlHost.WindowsXamlHost windowsXamlHost;

        public Form1()
        {
            InitializeComponent();
            this.windowsXamlHost = new Microsoft.Toolkit.Forms.UI.XamlHost.WindowsXamlHost();
            this.windowsXamlHost.InitialTypeName = "MyClassLibrary.WelcomePage";
        
            this.windowsXamlHost.AutoSizeMode = System.Windows.Forms.AutoSizeMode.GrowOnly;
            this.windowsXamlHost.Location = new System.Drawing.Point(0, 0);
            this.windowsXamlHost.Name = "windowsXamlHost";
            this.windowsXamlHost.Size = new System.Drawing.Size(800, 800);
            this.windowsXamlHost.TabIndex = 0;
            this.windowsXamlHost.Text = "windowsXamlHost";
            this.windowsXamlHost.Dock = System.Windows.Forms.DockStyle.Fill;

            //Adding the WindowsXamlHost to the Form
            this.Controls.Add(this.windowsXamlHost);
            //Setting the title of the Form
            this.Text = "WinForms .Net Core 3 and Xaml Islands";

            this.ResumeLayout(false);

            //this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            //this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            //this.ClientSize = new System.Drawing.Size(800, 600);

            //this.Name = "Form1";
           

        }

    }
}
