#pragma once
#include "pch.h"
#include "BGTask.g.h"

using namespace winrt;
using namespace Windows::ApplicationModel::Background;

namespace winrt::BackgroundTaskComponent::implementation
{
    struct BGTask : BGTaskT<BGTask>
    {
        BGTask() = default;
        
        void Run(IBackgroundTaskInstance taskInstance);
        
        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::BackgroundTaskComponent::factory_implementation
{
    struct BGTask : BGTaskT<BGTask, implementation::BGTask>
    {
    };
}
