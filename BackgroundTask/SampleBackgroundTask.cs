//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

using System;
using Windows.UI.Notifications;
using Windows.Data.Xml.Dom;
using Windows.ApplicationModel.Background;
using System.Diagnostics;
using Windows.Storage;
using Windows.UI.Core;
using Microsoft.Toolkit.Uwp.Notifications;

namespace BackgroundTask
{
    /// <summary>
    /// A background task always implements the IBackgroundTask interface.
    /// </summary>
    public sealed class BackgroundTaskSample : IBackgroundTask
    {
        private BackgroundTaskDeferral _deferral;

        /// <summary>
        /// The Run method is the entry point of a background task.
        /// </summary>
        public void Run(IBackgroundTaskInstance taskInstance)
        {
            _deferral = taskInstance.GetDeferral();
            Debug.WriteLine("Background " + taskInstance.Task.Name + " Starting...");


            var key = taskInstance.Task.Name;

            //
            // Record that this background task ran.
            //
            var settings = ApplicationData.Current.LocalSettings;
            settings.Values[key] = DateTime.Now.ToString();


            ShowToast1($"Background Task {key} Triggered!!!");

            _deferral.Complete();
        }

        /// <summary>
        /// Show toast notification
        /// </summary>
        private void ShowToast1(string msg)
        {
            ToastTemplateType toastTemplate = ToastTemplateType.ToastText02;
            XmlDocument toastXml = ToastNotificationManager.GetTemplateContent(toastTemplate);

            XmlNodeList toastTextElements = toastXml.GetElementsByTagName("text");
            toastTextElements[0].AppendChild(toastXml.CreateTextNode(msg));
            toastTextElements[1].AppendChild(toastXml.CreateTextNode(DateTime.Now.ToString()));

            ToastNotification toast = new ToastNotification(toastXml);
            ToastNotificationManager.CreateToastNotifier().Show(toast);
        }

        private void ShowToast(string msg)
        {
            new ToastContentBuilder()
            .AddArgument("action", "viewConversation")
            .AddArgument("conversationId", 9813)
            .AddText(msg)
            .Show();
        }

        /// <summary>
        /// Update the live tile
        /// </summary>
        private void UpdateTile(string msg)
        {
            XmlDocument tileXml = TileUpdateManager.GetTemplateContent(TileTemplateType.TileSquare150x150Text01);

            XmlNodeList textNodes = tileXml.GetElementsByTagName("text");
            textNodes[0].InnerText = msg;
            textNodes[1].InnerText = DateTime.Now.ToString("HH:mm:ss");

            TileNotification tileNotification = new TileNotification(tileXml);
            TileUpdateManager.CreateTileUpdaterForApplication().Update(tileNotification);
        }
    }
}