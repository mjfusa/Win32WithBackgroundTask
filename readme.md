# Sample Win32WithBackgroundTask - WinRT C++

Background Task, Win32 Console App for Background task Registration, Packaging Project, WinRT C++

## Prerequisites

* [Visual Studio 2022 Preview (Preview 3.0+)](https://visualstudio.microsoft.com/vs/preview/)
  * _Select the Universal Windows Platform development workload. In Installation Details > Universal Windows Platform development, check the C++ (v143) Universal Windows Platform tools option(s)._
  ![Visual Studio 2022 Installer](png\install.png)
* [Windows App SDK 22000](https://developer.microsoft.com/en-us/windows/downloads/windows-sdk/)
* Windows Developer Mode: Windows Settings > Update & Security > For developers, choose the Developer mode option.

## Projects in Win32WithBackgroundTask.sln

* **BackgroundTaskComponent**: WinRT C++ Background Task 
* **ConsoleRegisterBackgroundTask**: WinRT C++ Console app that registers the Background Task
* **Win32WithBackgroundTask.Package**: An Windows Application Packaging project. This is needed to deploy the app and register the background task with the OS.
* **UWPHead**: An empty UWP App. This is needed to properly populate the Appxmanifest.xml in the packaging project and ensure the MSIX package contains all of the required assemblies and files - functionally it doesn't do anything. 

```
Note: You will see the UWPHead app is also deployed when debugging from Visual Studio, however it is not included in the app package when distributing the app.
```
## 📝 License

This project is [MIT](./MIT.md) licensed.

