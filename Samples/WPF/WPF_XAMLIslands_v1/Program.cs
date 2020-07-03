// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.

using System;

namespace WPF_XAMLIslands_v1
{
    public static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
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