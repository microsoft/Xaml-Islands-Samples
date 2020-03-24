using System;
using System.Collections.Generic;
using System.Text;
using Windows.Graphics.Display;

namespace Samples.ManagedUWP.Helpers
{
    public static class DisplayInformation
    {
        [System.Runtime.InteropServices.DllImport("user32.dll")]
        private static extern uint GetSystemMetrics(int nIndex);

        public static uint ScreenWidthInRawPixels
        {
            get
            {
                return GetSystemMetrics(16 /*SM_CXFULLSCREEN*/);
            }

        }
        public static uint ScreenHeightInRawPixels
        {
            get
            {
                return GetSystemMetrics(17 /*SM_CYFULLSCREEN*/);
            }
        }
        public static DisplayOrientations CurrentOrientation
        {
            get
            {
                if (ScreenWidthInRawPixels > ScreenHeightInRawPixels)
                {
                    return DisplayOrientations.Landscape;
                }
                else
                {
                    return DisplayOrientations.Portrait;
                }

            }
        }

    }
}
