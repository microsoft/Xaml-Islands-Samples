// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace SampleLibraryCS
{
    public sealed partial class CustomUserControl : UserControl
    {
        public static DependencyProperty LabelProperty { get; private set; }

        static CustomUserControl()
        {
            LabelProperty = DependencyProperty.Register(
                nameof(Label),
                typeof(string),
                typeof(CustomUserControl),
                new PropertyMetadata(default(string)
                ));
        }

        public string Label
        {
            get
            {
                return (string)GetValue(LabelProperty);
            }
            set
            {
                SetValue(LabelProperty, value);
            }
        }

        public CustomUserControl()
        {
            this.InitializeComponent();
        }
    }
}
