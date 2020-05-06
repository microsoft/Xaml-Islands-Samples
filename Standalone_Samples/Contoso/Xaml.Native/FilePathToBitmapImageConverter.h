#pragma once

#include "FilePathToBitmapImageConverter.g.h"

namespace winrt::MyApp::implementation
{
    struct FilePathToBitmapImageConverter : FilePathToBitmapImageConverterT<FilePathToBitmapImageConverter>
    {
        FilePathToBitmapImageConverter() = default;
		Windows::Foundation::IInspectable Convert(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language);
		Windows::Foundation::IInspectable ConvertBack(Windows::Foundation::IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, Windows::Foundation::IInspectable const& parameter, hstring const& language);
	};
}

namespace winrt::MyApp::factory_implementation
{
    struct FilePathToBitmapImageConverter : FilePathToBitmapImageConverterT<FilePathToBitmapImageConverter, implementation::FilePathToBitmapImageConverter>
    {
    };
}
