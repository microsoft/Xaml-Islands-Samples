using Windows.UI.Xaml;
using Windows.UI.Xaml.Media;

namespace UILibrary.Controls
{
    /// <summary>
    /// Defines XAML attached properties that are available to Button like elements inside the UI library.
    /// </summary>
    public sealed partial class AttachedProperties : DependencyObject
    {
        private static readonly DependencyProperty _BorderHoverProperty;
        public static DependencyProperty BorderHoverProperty
        {
            get { return _BorderHoverProperty; }
        }


        /// <summary>
        /// Gets the Border brush set for Mouse hover state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetBorderHover(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(BorderHoverProperty);
        }

        /// <summary>
        /// Sets the Border brush set for Mouse hover state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetBorderHover(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(BorderHoverProperty, value);
        }

        internal static readonly DependencyProperty BorderFocusProperty = DependencyProperty.RegisterAttached(
            "BorderFocus", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Border brush set for Key Focus state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetBorderFocus(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(BorderFocusProperty);
        }

        /// <summary>
        /// Sets the Border brush set for Key Focus state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetBorderFocus(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(BorderFocusProperty, value);
        }

        internal static readonly DependencyProperty BorderPressedProperty = DependencyProperty.RegisterAttached(
            "BorderPressed", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Border brush set for Mouse pressed state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetBorderPressed(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(BorderPressedProperty);
        }

        /// <summary>
        /// Sets the Border brush set for Mouse pressed state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetBorderPressed(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(BorderPressedProperty, value);
        }

        internal static readonly DependencyProperty BackgroundHoverProperty = DependencyProperty.RegisterAttached(
            "BackgroundHover", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Background brush set for Mouse hover state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetBackgroundHover(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(BackgroundHoverProperty);
        }

        /// <summary>
        /// Sets the Background brush set for Mouse hover state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetBackgroundHover(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(BackgroundHoverProperty, value);
        }

        internal static readonly DependencyProperty BackgroundPressedProperty = DependencyProperty.RegisterAttached(
            "BackgroundPressed", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Background brush set for Mouse pressed state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetBackgroundPressed(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(BackgroundPressedProperty);
        }

        /// <summary>
        /// Sets the Background brush set for Mouse pressed state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetBackgroundPressed(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(BackgroundPressedProperty, value);
        }

        internal static readonly DependencyProperty ForegroundHoverProperty = DependencyProperty.RegisterAttached(
            "ForegroundHover", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Foreground brush set for Mouse hover state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetForegroundHover(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(ForegroundHoverProperty);
        }

        /// <summary>
        /// Sets the Foreground brush set for Mouse hover state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetForegroundHover(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(ForegroundHoverProperty, value);
        }

        internal static readonly DependencyProperty ForegroundFocusProperty = DependencyProperty.RegisterAttached(
            "ForegroundFocus", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Foreground brush set for KeyFocus state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetForegroundFocus(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(ForegroundFocusProperty);
        }

        /// <summary>
        /// Sets the Foreground brush set for KeyFocus state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetForegroundFocus(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(ForegroundFocusProperty, value);
        }

        internal static readonly DependencyProperty ForegroundPressedProperty = DependencyProperty.RegisterAttached(
            "ForegroundPressed", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Foreground brush set for Mouse pressed state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetForegroundPressed(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(ForegroundPressedProperty);
        }

        /// <summary>
        /// Sets the Foreground brush set for Mouse pressed state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetForegroundPressed(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(ForegroundPressedProperty, value);
        }

        internal static readonly DependencyProperty BorderDisabledProperty = DependencyProperty.RegisterAttached(
            "BorderDisabled", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Border brush set for disabled state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetBorderDisabled(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(BorderDisabledProperty);
        }

        /// <summary>
        /// Sets the Border brush set for disabled state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetBorderDisabled(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(BorderDisabledProperty, value);
        }

        internal static readonly DependencyProperty BackgroundDisabledProperty = DependencyProperty.RegisterAttached(
            "BackgroundDisabled", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Background brush set for disabled state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetBackgroundDisabled(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(BackgroundDisabledProperty);
        }

        /// <summary>
        /// Sets the Background brush set for disabled state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetBackgroundDisabled(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(BackgroundDisabledProperty, value);
        }

        internal static readonly DependencyProperty ForegroundDisabledProperty = DependencyProperty.RegisterAttached(
            "ForegroundDisabled", typeof(SolidColorBrush), typeof(AttachedProperties), null);

        /// <summary>
        /// Gets the Foreground brush set for disabled state.
        /// </summary>
        /// <param name="obj">The element from which the property value is read.</param>
        /// <returns>The brush value of the specified element.</returns>
        public static SolidColorBrush GetForegroundDisabled(DependencyObject obj)
        {
            return (SolidColorBrush)obj.GetValue(ForegroundDisabledProperty);
        }

        /// <summary>
        /// Sets the Foreground brush set for disabled state.
        /// </summary>
        /// <param name="obj">The element to which the property value is written.</param>
        /// <param name="value">The brush value.</param>
        public static void SetForegroundDisabled(DependencyObject obj, SolidColorBrush value)
        {
            obj.SetValue(ForegroundDisabledProperty, value);
        }
    }
}
