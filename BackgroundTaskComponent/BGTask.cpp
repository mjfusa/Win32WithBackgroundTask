#include "pch.h"
#include "BGTask.h"
#include "BGTask.g.cpp"
#include <cstdint>
#include <time.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Background;
using namespace Windows::Storage;
using namespace Windows::UI::Notifications;
using namespace Windows::Data::Xml::Dom;

namespace winrt::BackgroundTaskComponent::implementation
{
    void Debug(hstring message)
    {
        hstring finalMessage = message;
        finalMessage = finalMessage + to_hstring("\r\n");
        OutputDebugString(finalMessage.c_str());
    }
    
    WCHAR DateTimeNow[100];

    void ShowToast1(hstring msg)
    {
        ToastTemplateType toastTemplate = ToastTemplateType::ToastText02;
        XmlDocument toastXml = ToastNotificationManager::GetTemplateContent(toastTemplate);

        XmlNodeList toastTextElements = toastXml.GetElementsByTagName(to_hstring("text"));
        toastTextElements.GetAt(0).AppendChild(toastXml.CreateTextNode(msg));
        toastTextElements.GetAt(1).AppendChild(toastXml.CreateTextNode(DateTimeNow));

        ToastNotification toast = ToastNotification(toastXml);
        ToastNotificationManager::CreateToastNotifier().Show(toast);
    }
    
    void BGTask::Run(IBackgroundTaskInstance taskInstance)
    {
        BackgroundTaskDeferral _deferral = taskInstance.GetDeferral();
        Debug(to_hstring("Background ") + taskInstance.Task().Name() + to_hstring(" Starting..."));

        auto key = taskInstance.Task().Name();

        auto  settings = ApplicationData::Current().LocalSettings();

        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm now_tm{ 0 };
        localtime_s(&now_tm, &now_c);

        wcsftime(DateTimeNow, sizeof(DateTimeNow) * sizeof(WCHAR), L"%m/%d/%Y %T", &now_tm);
        settings.Values().Insert(key, box_value(to_hstring(DateTimeNow)));

        ShowToast1(to_hstring("Background Task ") + key + to_hstring(" Triggered!!!"));
    }
    
    int32_t BGTask::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void BGTask::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}
