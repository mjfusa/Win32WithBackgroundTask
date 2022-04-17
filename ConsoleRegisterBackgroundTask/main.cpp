// ConsoleRegisterBackgroundTask.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Background;
using namespace Windows::Storage;

IAsyncOperation<IBackgroundTaskRegistration> RegisterBackgroundTask(winrt::hstring triggerName, IBackgroundTrigger trigger)
{
    // Check if the task is already registered
    BackgroundAccessStatus abs = co_await BackgroundExecutionManager::RequestAccessAsync();
    std::cout << "BackgroundExecutionManager::RequestAccessAsync returns: " << magic_enum::enum_name(abs) << "\n";
    if ((abs == BackgroundAccessStatus::Unspecified) ||
        (abs == BackgroundAccessStatus::Denied) ||
        (abs == BackgroundAccessStatus::DeniedBySystemPolicy) ||
        (abs == BackgroundAccessStatus::DeniedByUser)
        )
    {
        std::cout << "Access request denied.\n";
        co_return NULL;
    }

    auto allTasks{ BackgroundTaskRegistration::AllTasks() };
    bool taskRegistered{ false };
    for (auto const& task : allTasks)
    {
        if (task.Value().Name() == triggerName)
        {
            taskRegistered = true;
            std::wcout << triggerName.c_str() << L" already registered.\n";
            co_return NULL;
        }
    }

    BackgroundTaskBuilder builder = BackgroundTaskBuilder();
    builder.Name(triggerName);
    builder.SetTrigger(trigger);
    builder.TaskEntryPoint(to_hstring("RuntimeComponent3.BGTask"));
    co_return builder.Register();
}

void UnregisterBackgroundTask(hstring triggerName) 
{
    auto allTasks{ BackgroundTaskRegistration::AllTasks() };
    bool taskRegistered{ false };
    for (auto const& task : allTasks)
    {
        if (task.Value().Name() == triggerName)
        {
            task.Value().Unregister(true);
        }
    }
}

IAsyncOperation<IBackgroundTaskRegistration> RegisterMyBackgroundTask()
{
    UnregisterBackgroundTask(to_hstring("TimeZoneTrigger"));
    auto taskRegistration = co_await  RegisterBackgroundTask(to_hstring("TimeZoneTrigger"), SystemTrigger(SystemTriggerType::TimeZoneChange, false));
    co_return taskRegistration;
}


int main()
{
    // App must run packaged. ApplicationModel::Package will throw an expection if not. See Windows Application Packaging Project
    auto p = winrt::Windows::ApplicationModel::Package::Current();
    auto pv = p.Id().Version();
    std::cout << "Version: " << pv.Major << "." << pv.Minor << "." << pv.Build << "." << pv.Revision << "\n";

    auto rbgt{ RegisterMyBackgroundTask() };
    auto result = rbgt.get();
    if (NULL != result) {
        std::cout << "Registration completed for Time Zone change system event. Change the time zone to trigger the background task.";
    }
    else {
        std::cout << "Registration not completed for Time Zone change system event. ";
    }

    auto settings = ApplicationData::Current().LocalSettings();

}



