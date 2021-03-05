using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;

namespace UILibrary.Controls
{
    public sealed partial class AttachedProperties : DependencyObject
    {
        static AttachedProperties()
        {
            _CornerRadiusProperty =
                DependencyProperty.RegisterAttached(
                    "CornerRadius",
                    typeof(CornerRadius),
                    typeof(AttachedProperties), null);

            _BorderHoverProperty =
                DependencyProperty.RegisterAttached(
                    "BorderHover",
                    typeof(Windows.UI.Xaml.Media.SolidColorBrush),
                    typeof(AttachedProperties),
                    null);

        }

        private static readonly DependencyProperty _CornerRadiusProperty;
        public static DependencyProperty CornerRadiusProperty
        {
            get { return _CornerRadiusProperty; }
        }

        /// <summary>
        /// Gets the Corner Radius.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The radius value of the specified element.</returns>
        public static CornerRadius GetCornerRadius(DependencyObject obj)
        {
            return (CornerRadius)obj.GetValue(CornerRadiusProperty);
        }

        /// <summary>
        /// Sets the Corner Radius.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The radius value.</param>
        public static void SetCornerRadius(DependencyObject obj, CornerRadius value)
        {
            obj.SetValue(CornerRadiusProperty, value);
        }
    }
}
