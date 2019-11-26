#include "pch.h"
#include "FilePathToBitmapImageConverter.h"
#if __has_include("FilePathToBitmapImageConverter.g.cpp")
#include "FilePathToBitmapImageConverter.g.cpp"
#endif

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media::Imaging;

namespace winrt::MyApp::implementation
{
	Windows::Foundation::IInspectable FilePathToBitmapImageConverter::Convert(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language)
	{
		return BitmapImage{ Uri { unbox_value<hstring>(value) } };
	}
	Windows::Foundation::IInspectable FilePathToBitmapImageConverter::ConvertBack(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language)
	{
		throw hresult_not_implemented();
	}
}
