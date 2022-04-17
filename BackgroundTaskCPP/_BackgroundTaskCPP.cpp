#include "pch.h"
#include "BackgroundTaskCPP.h"
#include <time.h>

using namespace Windows::ApplicationModel::Background;
using namespace Windows::Storage;
using namespace Windows::UI::Notifications;
using namespace Windows::Data::Xml::Dom;

using namespace BackgroundTaskCPP;

BackgroundTask::BackgroundTask()
{
}

BackgroundTask::~BackgroundTask()
{
}

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

void BackgroundTask::Run(IBackgroundTaskInstance taskInstance)
{

    BackgroundTaskDeferral _deferral = taskInstance.GetDeferral();
    Debug(to_hstring("Background ") + taskInstance.Task().Name() + to_hstring(" Starting..."));

    auto key = taskInstance.Task().Name();

    auto  settings = ApplicationData::Current().LocalSettings();
    //WCHAR buff[100];
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm{ 0 };
    localtime_s(&now_tm, &now_c);

    wcsftime(DateTimeNow, sizeof(DateTimeNow)*sizeof(WCHAR), L":%Y/%m/%d %T", &now_tm);
    settings.Values().Insert(key, box_value(to_hstring(DateTimeNow)));
    
    ShowToast1(to_hstring("Background Task ") + key +  to_hstring(" Triggered!!!"));  
    


}

