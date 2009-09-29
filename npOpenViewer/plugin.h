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

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "pluginbase.h"
#include "nsMemory.h"
#include "nsIProxyObjectManager.h"
#include "nsIServiceManager.h"
#include "nsScriptablePeer.h"
#include "nsXPCOMCIDInternal.h"

#using <mscorlib.dll>
#using <System.Windows.Forms.dll>
#using <OpenViewer.dll>
#using <OpenViewer.bootstrap.dll>
#using <Adapter.dll>
#using <Interfaces.dll>

using namespace OpenViewer;
using namespace OpenViewer::bootstrap;
using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Windows::Forms;

ref class OpenViewerEvent
{
public:
  OpenViewerEvent() {}
  ~OpenViewerEvent() {}
};

ref class OpenViewerDebugMessageEvent : OpenViewerEvent
{
public:
  OpenViewerDebugMessageEvent(String^ message) {
    this->message = message;
  }
  ~OpenViewerDebugMessageEvent() {}

  String^ message;
};

ref class OpenViewerTouchedEvent : OpenViewerEvent
{
public:
  OpenViewerTouchedEvent(String^ uuid) {
    this->uuid = uuid;
  }
  ~OpenViewerTouchedEvent() {}

  String^ uuid;
};

ref class OpenViewerReceivedMessageEvent : OpenViewerEvent
{
public:
  OpenViewerReceivedMessageEvent(String^ uuid, String^ avatarName, String^ message) {
    this->uuid = uuid;
    this->avatarName = avatarName;
    this->message = message;
  }
  ~OpenViewerReceivedMessageEvent() {}

  String^ uuid;
  String^ avatarName;
  String^ message;
};

ref class OpenViewerTeleportEvent : OpenViewerEvent
{
public:
  OpenViewerTeleportEvent(String^ regionName, int x, int y, int z) {
    this->regionName = regionName;
    this->x = x;
    this->y = y;
    this->z = z;
  }
  ~OpenViewerTeleportEvent() {}

  String^ regionName;
  int x,y,z;
};

ref class OpenViewerTeleportedEvent : OpenViewerEvent
{
public:
  OpenViewerTeleportedEvent(String^ uuid, String^ avatar, int x, int y, int z) {
    this->uuid = uuid;
    this->avatar = avatar;
    this->x = x;
    this->y = y;
    this->z = z;
  }
  ~OpenViewerTeleportedEvent() {}

  String^ uuid;
  String^ avatar;
  int x,y,z;
};

ref class OpenViewerOpenWindowEvent : OpenViewerEvent
{
public:
  OpenViewerOpenWindowEvent(String^ target, String^ uri) {
    this->target = target;
    this->uri = uri;
  }
  ~OpenViewerOpenWindowEvent() {}

  String^ target;
  String^ uri;
};

ref class OpenViewerStateChangedEvent : OpenViewerEvent
{
public:
  OpenViewerStateChangedEvent(int state) {
    this->state = state;
  }
  ~OpenViewerStateChangedEvent() {}

  int state;
};

ref class OpenViewerAvatarPickedEvent : OpenViewerEvent
{
public:
  OpenViewerAvatarPickedEvent(String^ uuid) {
    this->uuid = uuid;
  }
  ~OpenViewerAvatarPickedEvent() {}

  String^ uuid;
};

ref class OpenViewerDispatchEvent : OpenViewerEvent
{
public:
  OpenViewerDispatchEvent(String^ action, String^ message) {
    this->action = action;
    this->message = message;
  }
  ~OpenViewerDispatchEvent() {}

  String^ action;
  String^ message;
};

ref class ViewerInstance
{
public:
  ViewerInstance();
  ~ViewerInstance();

  Bootstrap^ boot;
  Viewer^ viewer;

  bool IsDHTMLRelationActivated;
  void OnStartupCallback(bool sucess);

  List<IntPtr>^ allocatedInUnmanagedHeap;

  float AvatarDisappearDistance;
  String^ BackgroundColor;
  float CameraDefaultAngleX;
  float CameraDefaultAngleY;
  float CameraFOV;
  float CameraKeyWalkingDistance;
  float CameraMaxAngleY;
  float CameraMaxDistance;
  float CameraMinAngleY;
  float CameraMinDistance;
  float CameraOffsetY;
  float CameraStartDistance;
  bool DHTMLRelationEnable;
  String^ DrawMenu;
  String^ DrawSea;
  String^ DrawSky;
  String^ DrawTerrain;
  String^ FirstName;
  String^ FixDirectionalAmbientColor;
  String^ FixDirectionalDiffuseColor;
  String^ FixDirectionalDirection;
  String^ InitBackgroundMusicURL;
  String^ InitBackgroundURL;
  String^ IsFixDirectional;
  String^ LastName;
  String^ Locale;
  String^ LoginBackgroundURL;
  String^ LoginLocation;
  String^ LoginMode;
  String^ Password;
  String^ ProgressColor;
  String^ RequireVersion;
  String^ ServerURI;
  bool SetStandUpIcon;
  String^ TickOn;
  int WindowHeight;
  int WindowWidth;
  String^ WorldAmbientColor;
  String^ WorldTime;

  void OnDebugMessage(String^ message);
  void OnTouched(String^ message);
  void OnReceiveMessage(String^ uuid, String^ avatarName, String^ message);
  void OnTeleport(String^ regionName, int x, int y, int z);
  void OnTeleported(String^ uuid, String^ avatar, int x, int y, int z);
  void OnOpenWindow(String^ target, String^ uri);
  void OnStateChanged(int state);
  void OnAvatarPicked(String^ uuid);
  void OnDispatch(String^ action, String^ message);

private:
  System::Collections::Queue^ eventQueue;
  void flushEvent(OpenViewerEvent^);
  void flushEvent_unsafe();
};

ref class ViewerInstances
{
public:
  static Object^ singleton;
  static Dictionary<unsigned long long, ViewerInstance^>^ viewerInstances;
  static Dictionary<ViewerInstance^, unsigned long long>^ pluginInstances;

  static void Initialize() {
    singleton = gcnew Object();
    viewerInstances = gcnew Dictionary<unsigned long long, ViewerInstance^>();
    pluginInstances = gcnew Dictionary<ViewerInstance^, unsigned long long>();
  }

  static void Add(unsigned long long plugin, ViewerInstance^ viewer) {
    viewerInstances->Add(plugin,viewer);
    pluginInstances->Add(viewer,plugin);
  }

  static void Remove(unsigned long long plugin, ViewerInstance^ viewer) {
    ViewerInstances::viewerInstances->Remove(plugin);
    ViewerInstances::pluginInstances->Remove(viewer);
  }
};

class nsPluginInstance : public nsPluginInstanceBase
{
public:
  nsPluginInstance(NPP aInstance);
  ~nsPluginInstance();

  NPBool init(NPWindow* aWindow);
  void shut();
  NPBool isInitialized();

  // we need to provide implementation of this method as it will be
  // used by Mozilla to retrieve the scriptable peer
  NPError	GetValue(NPPVariable variable, void *value);

  nsScriptablePeer* getScriptablePeer();
  void setEventListener(nsIJavaScriptEventListener*);
  nsIJavaScriptEventListener* getEventListener();

private:
  NPP mInstance;
  NPBool mInitialized;
  HWND mhWnd;
  nsScriptablePeer* mScriptablePeer;
  nsIJavaScriptEventListener* mListener;
};

#endif // __PLUGIN_H__
