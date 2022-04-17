#pragma once
#include "pch.h"

using namespace winrt;
using namespace Windows::ApplicationModel::Background;

//#include "BackgroundTaskCPP.g.h"

namespace winrt::BackgroundTaskCPP::implementation
{
    
    struct BackgroundTask : BackgroundTaskT<BackgroundTask>
    {
        BackgroundTask() = default;
        virtual void Run(IBackgroundTaskInstance taskInstance);
        void OnCanceled(IBackgroundTaskInstance taskInstance, BackgroundTaskCancellationReason reason);


    };
}

namespace winrt::BackgroundTaskCPP::factory_implementation
{
    struct BackgroundTask : BackgroundTaskT<BackgroundTask, implementation::BackgroundTask>
    {
    };
}
