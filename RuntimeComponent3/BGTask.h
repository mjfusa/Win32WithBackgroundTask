#pragma once
#include "pch.h"
#include "BGTask.g.h"

using namespace winrt;
using namespace Windows::ApplicationModel::Background;

namespace winrt::RuntimeComponent3::implementation
{
    struct BGTask : BGTaskT<BGTask>
    {
        BGTask() = default;
        
        void Run(IBackgroundTaskInstance taskInstance);
        
        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::RuntimeComponent3::factory_implementation
{
    struct BGTask : BGTaskT<BGTask, implementation::BGTask>
    {
    };
}
