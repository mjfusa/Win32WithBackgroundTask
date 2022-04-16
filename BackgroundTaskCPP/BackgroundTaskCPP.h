#pragma once

#include "pch.h"

using namespace winrt;
using namespace Windows::ApplicationModel::Background;

namespace BackgroundTaskCPP
{
    class BackgroundTask : public IBackgroundTask
    {
    public:
        BackgroundTask();


        virtual void Run(IBackgroundTaskInstance taskInstance);
        void OnCanceled(IBackgroundTaskInstance taskInstance, BackgroundTaskCancellationReason reason);

    private:
        ~BackgroundTask();
    };
}
