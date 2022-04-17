#include "pch.h"
#include "BackgroundClassCPP.h"
//#include "BackgroundClassCPP.g.cpp"

using namespace Windows::ApplicationModel::Background;
using namespace Windows::Storage;
using namespace Windows::UI::Notifications;
using namespace Windows::Data::Xml::Dom;

namespace winrt::BackgroundTaskCPP::implementation
{
    void Debug(hstring message)
    {
        hstring finalMessage = message;
        finalMessage = finalMessage + to_hstring("\r\n");
        OutputDebugString(finalMessage.c_str());
    }


}
