using System;
using System.Collections.Generic;
using System.Text;

namespace WPFCore3XamlIslads
{
    public static class Program
    {
        [STAThread]
        public static void Main()
        {
            using (new UWPApplication.App())
            {
                var app = new App();
                app.InitializeComponent();
                app.Run();
            }
        }
    }
}
