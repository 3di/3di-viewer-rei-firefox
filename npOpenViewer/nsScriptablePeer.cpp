/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Copyright (C) 1998, 2009 the Initial Developer and contributors.
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 * Portions Copyright (c) 2009, 3Di, Inc. (http://3di.jp/).
 * All Rights Reserved.
 *
 * ***** END LICENSE BLOCK ***** */

// ==============================
// ! Scriptability related code !
// ==============================

/////////////////////////////////////////////////////
//
// This file implements the nsScriptablePeer object
// The native methods of this class are supposed to
// be callable from JavaScript
//
#include "plugin.h"

static NS_DEFINE_IID(kIScriptableIID, NS_ISCRIPTABLEPLUGIN_IID);
static NS_DEFINE_IID(kIClassInfoIID, NS_ICLASSINFO_IID);
static NS_DEFINE_IID(kISupportsIID, NS_ISUPPORTS_IID);
static NS_DEFINE_IID(kProxyObjectManagerIID, NS_IPROXYOBJECTMANAGER_IID);
static NS_DEFINE_IID(kJavaScriptEventListenerIID, NS_IJAVASCRIPTEVENTLISTENER_IID);

nsScriptablePeer::nsScriptablePeer(nsPluginInstance* aPlugin)
{
  mPlugin = aPlugin;
  mRefCnt = 0;
}

nsScriptablePeer::~nsScriptablePeer()
{
}

// AddRef, Release and QueryInterface are common methods and must 
// be implemented for any interface
NS_IMETHODIMP_(nsrefcnt) nsScriptablePeer::AddRef() 
{ 
  ++mRefCnt; 
  return mRefCnt; 
} 

NS_IMETHODIMP_(nsrefcnt) nsScriptablePeer::Release() 
{ 
  --mRefCnt; 
  if (mRefCnt == 0) { 
    delete this;
    return 0; 
  } 
  return mRefCnt; 
} 

// here nsScriptablePeer should return three interfaces it can be asked for by their iid's
// static casts are necessary to ensure that correct pointer is returned
NS_IMETHODIMP nsScriptablePeer::QueryInterface(const nsIID& aIID, void** aInstancePtr) 
{ 
  if(!aInstancePtr) 
    return NS_ERROR_NULL_POINTER; 

  if(aIID.Equals(kIScriptableIID)) {
    *aInstancePtr = static_cast<nsIScriptablePlugin*>(this);
    AddRef();
    return NS_OK;
  }

  if(aIID.Equals(kIClassInfoIID)) {
    *aInstancePtr = static_cast<nsIClassInfo*>(this); 
    AddRef();
    return NS_OK;
  }

  if(aIID.Equals(kISupportsIID)) {
    *aInstancePtr = static_cast<nsISupports*>(static_cast<nsIScriptablePlugin*>(this)); 
    AddRef();
    return NS_OK;
  }

  return NS_NOINTERFACE; 
}

void nsScriptablePeer::SetInstance(nsPluginInstance* plugin)
{
  if (dynamic_cast<nsPluginInstance*>(plugin))
    mPlugin = plugin;
}

nsPluginInstance* nsScriptablePeer::GetInstance()
{
  return mPlugin;
}

//
// the following methods will be callable from JavaScript
//
ViewerInstance::ViewerInstance()
{
  allocatedInUnmanagedHeap = gcnew List<IntPtr>();
  eventQueue = gcnew System::Collections::Queue();
  DHTMLRelationEnable = true;
  IsDHTMLRelationActivated = false;
}

ViewerInstance::~ViewerInstance()
{
  for each (IntPtr ptr in allocatedInUnmanagedHeap)
    Marshal::FreeHGlobal(ptr);
}

void ViewerInstance::OnStartupCallback(bool success)
{
  if (success && DHTMLRelationEnable) {
    viewer->DHTMLRelationEnable = "true";
    IsDHTMLRelationActivated = true;
  } else {
    viewer->DHTMLRelationEnable = "false";
    IsDHTMLRelationActivated = false;
  }
}

void ViewerInstance::OnDebugMessage(String^ message)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerDebugMessageEvent(message));
}

void ViewerInstance::OnTouched(String^ uuid)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerTouchedEvent(uuid));
}

void ViewerInstance::OnReceiveMessage(String^ uuid, String^ avatarName, String^ message) 
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerReceivedMessageEvent(uuid,avatarName,message));
}

void ViewerInstance::OnTeleport(String^ regionName, int x, int y, int z)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerTeleportEvent(regionName,x,y,z));
}

void ViewerInstance::OnTeleported(String^ uuid, String^ avatar, int x, int y, int z)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerTeleportedEvent(uuid,avatar,x,y,z));
}

void ViewerInstance::OnOpenWindow(String^ target, String^ uri)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerOpenWindowEvent(target,uri));
}

void ViewerInstance::OnStateChanged(int state)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerStateChangedEvent(state));
}

void ViewerInstance::OnAvatarPicked(String^ uuid)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerAvatarPickedEvent(uuid));
}

void ViewerInstance::OnDispatch(String^ action, String^ message)
{
  if (!IsDHTMLRelationActivated) return;
  flushEvent(gcnew OpenViewerDispatchEvent(action, message));
}

void ViewerInstance::flushEvent(OpenViewerEvent^ event)
{
  Monitor::Enter(ViewerInstances::singleton);
  try {
    Monitor::Enter(eventQueue);
    eventQueue->Enqueue(event);
    Monitor::Exit(eventQueue);
    flushEvent_unsafe();
  } finally {
    Monitor::Exit(ViewerInstances::singleton);
  }
}

void ViewerInstance::flushEvent_unsafe()
{
  nsPluginInstance* pluginInstance = (nsPluginInstance*)ViewerInstances::pluginInstances[this];
  nsIJavaScriptEventListener* listener = pluginInstance->getEventListener();
  nsIServiceManager* serviceManager = nsnull;
  nsIProxyObjectManager* proxyManager = nsnull;
  nsIJavaScriptEventListener* proxy = nsnull;
  nsresult rv;

  if (listener == 0) {
    Monitor::Enter(eventQueue);
    eventQueue->Clear();
    Monitor::Exit(eventQueue);
    return;
  }

  rv = NS_GetServiceManager(&serviceManager);
  if(NS_FAILED(rv))
    goto failed;
  rv = serviceManager->GetServiceByContractID(NS_XPCOMPROXY_CONTRACTID,kProxyObjectManagerIID,(void**)&proxyManager);
  if(NS_FAILED(rv))
    goto failed;
  rv = proxyManager->GetProxyForObject(NS_PROXY_TO_MAIN_THREAD,kJavaScriptEventListenerIID,listener,NS_PROXY_ASYNC,(void**)&proxy);
  if(NS_FAILED(rv))
    goto failed;

  int count;
  do {
    OpenViewerEvent^ e = nullptr;
    Monitor::Enter(eventQueue);
    count = eventQueue->Count;
    if (count > 0) {
      e = (OpenViewerEvent^)eventQueue->Dequeue();
    } else {
      e = nullptr;
    }
    Monitor::Exit(eventQueue);

    if (e != nullptr) {
      if (dynamic_cast<OpenViewerDebugMessageEvent^>(e) != nullptr) {
        IntPtr message = Marshal::StringToHGlobalAnsi(dynamic_cast<OpenViewerDebugMessageEvent^>(e)->message);
        proxy->OnDebugMessage((const char*)(void*)message);
        Marshal::FreeHGlobal(message);
      }
      else if (dynamic_cast<OpenViewerTouchedEvent^>(e) != nullptr) {
        IntPtr uuid = Marshal::StringToHGlobalAnsi(dynamic_cast<OpenViewerTouchedEvent^>(e)->uuid);
        proxy->OnTouched((const char*)(void*)uuid);
        Marshal::FreeHGlobal(uuid);
      }
      else if (dynamic_cast<OpenViewerReceivedMessageEvent^>(e) != nullptr) {
        OpenViewerReceivedMessageEvent^ rme = dynamic_cast<OpenViewerReceivedMessageEvent^>(e);
        IntPtr uuid = Marshal::StringToHGlobalAnsi(rme->uuid);
        IntPtr avatarName = Marshal::StringToHGlobalAnsi(rme->avatarName);
        IntPtr message = Marshal::StringToHGlobalUni(rme->message);
        proxy->OnReceivedMessage((const char*)(void*)uuid,(const char*)(void*)avatarName,(const PRUnichar*)(void*)message);
        Marshal::FreeHGlobal(uuid);
        Marshal::FreeHGlobal(avatarName);
        Marshal::FreeHGlobal(message);
      }
      else if (dynamic_cast<OpenViewerTeleportEvent^>(e) != nullptr) {
        OpenViewerTeleportEvent^ tpe = dynamic_cast<OpenViewerTeleportEvent^>(e);
        IntPtr regionName = Marshal::StringToHGlobalAnsi(tpe->regionName);
        proxy->OnTeleport((const char*)(void*)regionName,tpe->x,tpe->y,tpe->z);
        Marshal::FreeHGlobal(regionName);
      }
      else if (dynamic_cast<OpenViewerTeleportedEvent^>(e) != nullptr) {
        OpenViewerTeleportedEvent^ tpe = dynamic_cast<OpenViewerTeleportedEvent^>(e);
        IntPtr uuid = Marshal::StringToHGlobalAnsi(tpe->uuid);
        IntPtr avatar = Marshal::StringToHGlobalAnsi(tpe->avatar);
        proxy->OnTeleported((const char*)(void*)uuid,(const char*)(void*)avatar,tpe->x,tpe->y,tpe->z);
        Marshal::FreeHGlobal(uuid);
        Marshal::FreeHGlobal(avatar);
      }
      else if (dynamic_cast<OpenViewerOpenWindowEvent^>(e) != nullptr) {
        OpenViewerOpenWindowEvent^ owe = dynamic_cast<OpenViewerOpenWindowEvent^>(e);
        IntPtr target = Marshal::StringToHGlobalAnsi(owe->target);
        IntPtr uri = Marshal::StringToHGlobalAnsi(owe->uri);
        proxy->OnOpenWindow((const char*)(void*)target,(const char*)(void*)uri);
        Marshal::FreeHGlobal(target);
        Marshal::FreeHGlobal(uri);
      }
      else if (dynamic_cast<OpenViewerStateChangedEvent^>(e) != nullptr) {
        proxy->OnStateChanged(dynamic_cast<OpenViewerStateChangedEvent^>(e)->state);
      }
      else if (dynamic_cast<OpenViewerAvatarPickedEvent^>(e) != nullptr) {
        OpenViewerAvatarPickedEvent^ ape = dynamic_cast<OpenViewerAvatarPickedEvent^>(e);
        IntPtr uuid = Marshal::StringToHGlobalAnsi(ape->uuid);
        proxy->OnAvatarPicked((const char*)(void*)uuid);
        Marshal::FreeHGlobal(uuid);
      }
      else if (dynamic_cast<OpenViewerDispatchEvent^>(e) != nullptr) {
        OpenViewerDispatchEvent^ dpe = dynamic_cast<OpenViewerDispatchEvent^>(e);
        IntPtr action = Marshal::StringToHGlobalAnsi(dpe->action);
        IntPtr message = Marshal::StringToHGlobalAnsi(dpe->message);
        proxy->OnDispatch((const char*)(void*)action,(const char*)(void*)message);
        Marshal::FreeHGlobal(action);
        Marshal::FreeHGlobal(message);
      }
    }
  } while (false);

failed:
  NS_IF_RELEASE(proxy);
  NS_IF_RELEASE(proxyManager);
  NS_IF_RELEASE(serviceManager);
  return;
}

NS_IMETHODIMP nsScriptablePeer::SetEventListener(nsIJavaScriptEventListener *listener)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->DHTMLRelationEnable) return NS_OK;
  mPlugin->setEventListener(listener);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetPluginInfo(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  Version^ version = OpenViewer::bootstrap::VersionInfo::version;
  String^ _info = String::Format("{{\"Version\":\"{0}\",\"Type\":\"Firefox\"}}",version->ToString());
  if (_info == nullptr)
    _info = gcnew String(String::Empty);
  IntPtr info = Marshal::StringToHGlobalAnsi(_info);
  if (info == IntPtr::Zero) {
    return NS_ERROR_OUT_OF_MEMORY;
  } else {
    try {
      char* infop = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)info)+1));
      if (infop == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(infop,(const char*)(void*)info);
      *_retval = infop;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(info);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::Login(const char *_firstName, const char *_lastName, const char *_password, const char *_serverURL, const char *_loginLocation)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  String^ firstName = gcnew String(_firstName);
  String^ lastName = gcnew String(_lastName);
  String^ password = gcnew String(_password);
  String^ serverURL = gcnew String(_serverURL);
  String^ loginLocation = gcnew String(_loginLocation);
  viewer->Adapter->CallLogin(firstName,lastName,password,serverURL,loginLocation);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Logout()
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallLogout();
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::TouchTo(const char *_uuid)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallTouchTo(gcnew String(_uuid));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SitOn(const char *_uuid)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSitOn(gcnew String(_uuid));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::StandUp()
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallStandUp();
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SendChat(const PRUnichar *message, PRInt32 range)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSendChat(gcnew String(message),range);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetMessageFromHistory(PRInt32 index, PRUnichar **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  String^ _hist = viewer->Adapter->CallGetMessageFromHistory(index);
  if (_hist == nullptr)
    _hist = gcnew String(String::Empty);
  IntPtr hist = Marshal::StringToHGlobalUni(_hist);
  if (hist == IntPtr::Zero) {
    return NS_ERROR_OUT_OF_MEMORY;
  } else {
    try {
      PRUnichar* histp = (PRUnichar*)nsMemory::Alloc(sizeof(PRUnichar)*(::wcslen((PRUnichar*)(void*)hist)+1));
      if (histp == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::wcscpy(histp,(PRUnichar*)(void*)hist);
      *_retval = histp;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(hist);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetMessageHistoryLength(PRInt32 *_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  *_retval = viewer->Adapter->CallGetMessageHistoryLength();
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::TeleportTo(const char *region, PRInt32 x, PRInt32 y, PRInt32 z)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallTeleportTo(gcnew String(region),x,y,z);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetUserAvatarName(char ** _retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr name = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetUserAvatarName());
  if (name == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* namep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)name)+1));
      if (namep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(namep,(char*)(void*)name);
      *_retval = namep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(name);
    }
  }
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetUserAvatarPosition(char ** _retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetUserAvatarPosition());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetUserAvatarUUID(char ** _retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr uuid = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetUserAvatarUUID());
  if (uuid == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* uuidp = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)uuid)+1));
      if (uuidp == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(uuidp,(char*)(void*)uuid);
      *_retval = uuidp;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(uuid);
    }
  }
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetUserUUID(char ** _retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr uuid = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetUserUUID());
  if (uuid == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* uuidp = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)uuid)+1));
      if (uuidp == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(uuidp,(char*)(void*)uuid);
      *_retval = uuidp;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(uuid);
    }
  }
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::UserAvatarUp()
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallUserAvatarUp(true);
  viewer->Adapter->CallUserAvatarDown(false);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::UserAvatarDown()
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallUserAvatarUp(false);
  viewer->Adapter->CallUserAvatarDown(true);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::UserAvatarLeft()
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallUserAvatarLeft();
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::UserAvatarRight()
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallUserAvatarRight();
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::StartCustomAnimation(int index)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallAvatarCustomizeAnimation(index);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetFPS(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(String::Format("{0}",viewer->Adapter->CallGetFPS()));
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetPrimitiveCount(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(String::Format("{0}",viewer->Adapter->CallGetPrimitiveCount()));
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetTextureCount(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(String::Format("{0}",viewer->Adapter->CallGetTextureCount()));
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::CameraLookAt(float px, float py, float pz, float tx, float ty, float tz)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallCameraLookAt(px,py,pz,tx,ty,tz);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetCameraDistance(float distance)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetCameraDistance(distance);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetCameraDistance(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetCameraDistance());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetCameraPosition(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetCameraPosition());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetCameraTarget(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetCameraTarget());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetCameraFOV(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetCameraFOV());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::SetCameraFOV(float fov)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetCameraFOV(fov);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetCameraFOVDegree(float fov)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetCameraFOVDegree(fov);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetCameraOffsetY(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetCameraOffsetY());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::SetCameraOffsetY(float offsetY)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetCameraOffsetY(offsetY);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetCameraAngleY(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetCameraAngleY());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::SetCameraAngleY(float min, float max)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetCameraAngleY(min,max);
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetAvatarDisappearDistance(float distance)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->AvatarDisappearDistance = distance;
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::GetAvatarCount(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetAvatarCount());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetObjectCount(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetObjectCount());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetRegionName(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetRegionName());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::GetWorldTime(char **_retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->CallGetWorldTime());
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
}

NS_IMETHODIMP nsScriptablePeer::SetWorldTime(const char *dataTime)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetWorldTime(gcnew String(dataTime));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetTickOn(const char *flag)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetTickOn(gcnew String(flag));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetWorldAmbientColor(const char *colors)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetWorldAmbientColor(gcnew String(colors));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetFixDirectional(const char *flag)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetFixDirectional(gcnew String(flag));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetFixDirectionalRotation(const char *radRotation)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetFixDirectionalRotation(gcnew String(radRotation));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetFixDirectionalDiffuseColor(const char *colors)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetFixDirectionalDiffuseColor(gcnew String(colors));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::SetFixDirectionalAmbientColor(const char *colors)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  viewer->Adapter->CallSetFixDirectionalAmbientColor(gcnew String(colors));
  return NS_OK;
}

NS_IMETHODIMP nsScriptablePeer::Callback(const char *_action, const char *_message, char** _retval)
{
  ViewerInstance^ viewerInstance = ViewerInstances::viewerInstances[(unsigned long long)mPlugin];
  Viewer^ viewer = viewerInstance->viewer;
  if (!viewerInstance->IsDHTMLRelationActivated) return NS_OK;
  IntPtr value = Marshal::StringToHGlobalAnsi(viewer->Adapter->RunCallback(gcnew String(_action), gcnew String(_message)));
  if (value == IntPtr::Zero)
    return NS_ERROR_OUT_OF_MEMORY;
  else {
    try {
      char* valuep = (char*)nsMemory::Alloc(sizeof(char)*(::strlen((char*)(void*)value)+1));
      if (valuep == 0)
        return NS_ERROR_OUT_OF_MEMORY;
      ::strcpy(valuep,(char*)(void*)value);
      *_retval = valuep;
      return NS_OK;
    } finally {
      Marshal::FreeHGlobal(value);
    }
  }
  return NS_OK;
}
