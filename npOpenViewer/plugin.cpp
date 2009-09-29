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

#include <windows.h>
#include <windowsx.h>

#include "plugin.h"
#include "nsIServiceManager.h"
#include "nsISupportsUtils.h" // some usefule macros are defined here
#include "plstr.h"

//////////////////////////////////////
//
// general initialization and shutdown
//
NPError NS_PluginInitialize()
{
  ViewerInstances::Initialize();
  return NPERR_NO_ERROR;
}

void NS_PluginShutdown()
{
}

/////////////////////////////////////////////////////////////
//
// construction and destruction of our plugin instance object
//
nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
  if(!aCreateDataStruct)
    return NULL;

  nsPluginCreateData* tag = aCreateDataStruct;
  ViewerInstance^ instance = gcnew ViewerInstance();
  bool boolValue;
  int intValue;
  double doubleValue;
  for (int i = 0; i < tag->argc; i++) {
    if (!PL_strcasecmp(tag->argn[i],"AvatarDisappearDistance") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->AvatarDisappearDistance = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"BackgroundColor"))
      instance->BackgroundColor = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"CameraDefaultAngleX") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraDefaultAngleX = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraDefaultAngleY") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraDefaultAngleY = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraFOV") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraFOV = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraKeyWalkingDistance") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraKeyWalkingDistance = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraMaxAngleY") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraMaxAngleY = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraMaxDistance") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraMaxDistance = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraMinAngleY") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraMinAngleY = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraMinDistance") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraMinDistance = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraOffsetY") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraOffsetY = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"CameraStartDistance") && Double::TryParse(gcnew String(tag->argv[i]),doubleValue))
      instance->CameraStartDistance = (float)doubleValue;
    if (!PL_strcasecmp(tag->argn[i],"DHTMLRelationEnable") && Boolean::TryParse(gcnew String(tag->argv[i]),boolValue))
      instance->DHTMLRelationEnable = (bool)boolValue;
    if (!PL_strcasecmp(tag->argn[i],"DrawMenu"))
      instance->DrawMenu = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"DrawSea"))
      instance->DrawSea = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"DrawSky"))
      instance->DrawSky = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"DrawTerrain"))
      instance->DrawTerrain = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"FirstName"))
      instance->FirstName = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"FixDirectionalAmbientColor"))
      instance->FixDirectionalAmbientColor = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"FixDirectionalDiffuseColor"))
      instance->FixDirectionalDiffuseColor = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"FixDirectionalDirection"))
      instance->FixDirectionalDirection = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"InitBackgroundMusicURL"))
      instance->InitBackgroundMusicURL = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"InitBackgroundURL"))
      instance->InitBackgroundURL = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"IsFixDirectional"))
      instance->IsFixDirectional = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"LastName"))
      instance->LastName = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"Locale"))
      instance->Locale = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"LoginBackgroundURL"))
      instance->LoginBackgroundURL = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"LoginLocation"))
      instance->LoginLocation = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"LoginMode"))
      instance->LoginMode = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"Password"))
      instance->Password = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"ProgressColor"))
      instance->ProgressColor = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"RequireVersion"))
      instance->RequireVersion = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"ServerURI"))
      instance->ServerURI = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"SetStandUpIcon") && Boolean::TryParse(gcnew String(tag->argv[i]),boolValue))
      instance->SetStandUpIcon = (bool)boolValue;
    if (!PL_strcasecmp(tag->argn[i],"TickOn"))
      instance->TickOn = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"WindowHeight") && Int32::TryParse(gcnew String(tag->argv[i]),intValue))
      instance->WindowHeight = intValue;
    if (!PL_strcasecmp(tag->argn[i],"WindowWidth") && Int32::TryParse(gcnew String(tag->argv[i]),intValue))
      instance->WindowWidth = intValue;
    if (!PL_strcasecmp(tag->argn[i],"WorldAmbientColor"))
      instance->WorldAmbientColor = gcnew String(tag->argv[i]);
    if (!PL_strcasecmp(tag->argn[i],"WorldTime"))
      instance->WorldTime = gcnew String(tag->argv[i]);
  }
  nsPluginInstance * plugin = new nsPluginInstance(aCreateDataStruct->instance);
  ViewerInstances::Add((unsigned long long)static_cast<nsPluginInstanceBase*>(plugin),instance);
  return plugin;
}

void NS_DestroyPluginInstance(nsPluginInstanceBase * aPlugin)
{
  if(aPlugin)
    delete (nsPluginInstance *)aPlugin;
}

////////////////////////////////////////
//
// nsPluginInstance class implementation
//
nsPluginInstance::nsPluginInstance(NPP aInstance) : nsPluginInstanceBase(),
  mInstance(aInstance),
  mInitialized(FALSE),
  mScriptablePeer(NULL),
  mListener(NULL)
{
  mhWnd = NULL;
}

nsPluginInstance::~nsPluginInstance()
{
  // mScriptablePeer may be also held by the browser 
  // so releasing it here does not guarantee that it is over
  // we should take precaution in case it will be called later
  // and zero its mPlugin member
  mScriptablePeer->SetInstance(NULL);
  NS_IF_RELEASE(mScriptablePeer);
}

static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
static WNDPROC lpOldProc = NULL;

NPBool nsPluginInstance::init(NPWindow* aWindow)
{
  if(aWindow == NULL)
    return FALSE;

  mhWnd = (HWND)aWindow->window;
  if(mhWnd == NULL)
    return FALSE;

  // subclass window so we can intercept window messages and
  // do our drawing to it
  lpOldProc = SubclassWindow(mhWnd, (WNDPROC)PluginWinProc);

  // associate window with our nsPluginInstance object so we can access 
  // it in the window procedure
  SetWindowLong(mhWnd, GWL_USERDATA, (LONG)this);

  //::SetCurrentDirectory("C:\\Program\ Files\\3Di\\OpenViewer");
  ViewerInstance^ instance = ViewerInstances::viewerInstances[(unsigned long long)this];
  Viewer ^viewer = gcnew Viewer();
  IntPtr handle(mhWnd);

  if (instance->AvatarDisappearDistance != 0)
    viewer->AvatarDisappearDistance = instance->AvatarDisappearDistance;
  if (instance->BackgroundColor != nullptr)
    viewer->BackgroundColor = instance->BackgroundColor;
  if (instance->CameraDefaultAngleX != 0)
    { viewer->CamRotationAngleTHETA = instance->CameraDefaultAngleX; viewer->CamDefaultRotationAngleTHETA = instance->CameraDefaultAngleX; }
  if (instance->CameraDefaultAngleY != 0)
    { viewer->CamRotationAnglePHI = instance->CameraDefaultAngleY; viewer->CamDefaultRotationAnglePHI = instance->CameraDefaultAngleY; }
  if (instance->CameraFOV != 0)
    viewer->CameraFOV = instance->CameraFOV;
  if (instance->CameraKeyWalkingDistance != 0)
    viewer->CameraKeyWalkingDistance = instance->CameraKeyWalkingDistance;
  if (instance->CameraMaxAngleY != 0)
    viewer->CameraMaxAngleY = instance->CameraMaxAngleY;
  if (instance->CameraMaxDistance != 0)
    viewer->CameraMaxDistance = instance->CameraMaxDistance;
  if (instance->CameraMinAngleY != 0)
    viewer->CameraMinAngleY = instance->CameraMinAngleY;
  if (instance->CameraMinDistance != 0)
    viewer->CameraMinDistance = instance->CameraMinDistance;
  if (instance->CameraOffsetY != 0)
    viewer->CameraOffsetY = instance->CameraOffsetY;
  if (instance->CameraStartDistance != 0)
    viewer->CameraDistance = instance->CameraStartDistance < 0.1f ? 0.1f : instance->CameraStartDistance;
  viewer->DHTMLRelationEnable = "false";
  if (instance->DrawMenu != nullptr)
    viewer->DrawMenu = instance->DrawMenu;
  if (instance->DrawSea != nullptr)
    viewer->DrawSea = instance->DrawSea;
  if (instance->DrawSky != nullptr)
    viewer->DrawSky = instance->DrawSky;
  if (instance->DrawTerrain != nullptr)
    viewer->DrawTerrain = instance->DrawTerrain;
  if (instance->FirstName != nullptr)
    viewer->FirstName = instance->FirstName;
  if (instance->FixDirectionalAmbientColor != nullptr)
    viewer->FixDirectionalAmbientColor = instance->FixDirectionalAmbientColor;
  if (instance->FixDirectionalDiffuseColor != nullptr)
    viewer->FixDirectionalDiffuseColor = instance->FixDirectionalDiffuseColor;
  if (instance->FixDirectionalDirection != nullptr)
    viewer->FixDirectionalRotation = instance->FixDirectionalDirection;
  if (instance->InitBackgroundMusicURL != nullptr)
    viewer->InitBackgroundMusicURL = instance->InitBackgroundMusicURL;
  if (instance->InitBackgroundURL != nullptr)
    viewer->InitBackgroundURL = instance->InitBackgroundURL;
  if (instance->IsFixDirectional != nullptr)
    viewer->FixDirectional = instance->IsFixDirectional;
  if (instance->LastName != nullptr)
    viewer->LastName = instance->LastName;
  if (instance->Locale != nullptr)
    viewer->Locale = instance->Locale;
  if (instance->LoginBackgroundURL != nullptr)
    viewer->LoginBackgroundURL = instance->LoginBackgroundURL;
  if (instance->LoginLocation != nullptr)
    viewer->LoginLocation = instance->LoginLocation;
  if (instance->LoginMode != nullptr)
    viewer->LoginMode = instance->LoginMode;
  if (instance->Password != nullptr)
    viewer->Password = instance->Password;
  if (instance->ProgressColor != nullptr)
    viewer->ProgressColor = instance->ProgressColor;
  if (instance->ServerURI != nullptr)
    viewer->ServerURI = instance->ServerURI;
  viewer->IsStandUpIcon = instance->SetStandUpIcon;
  if (instance->TickOn != nullptr)
    viewer->TickOn = instance->TickOn;
  if (instance->WindowHeight != 0)
    viewer->Height = instance->WindowHeight;
  if (instance->WindowWidth != 0)
    viewer->Width = instance->WindowWidth;
  if (instance->WorldAmbientColor != nullptr)
    viewer->WorldAmbientColor = instance->WorldAmbientColor;
  if (instance->WorldTime != nullptr)
    viewer->SetWorldTime(instance->WorldTime);
  viewer->Adapter = gcnew Adapter();
  viewer->Adapter->OnDebugMessage += gcnew OpenViewer::TouchToListener(instance,&ViewerInstance::OnDebugMessage);
  viewer->Adapter->OnTouched += gcnew OpenViewer::TouchToListener(instance,&ViewerInstance::OnTouched);
  viewer->Adapter->OnReceiveMessage += gcnew OpenViewer::OnReceiveMessageListener(instance,&ViewerInstance::OnReceiveMessage);
  viewer->Adapter->OnTeleport += gcnew OpenViewer::TeleportToListener(instance,&ViewerInstance::OnTeleport);
  viewer->Adapter->OnTeleported += gcnew OpenViewer::TeleportListener(instance,&ViewerInstance::OnTeleported);
  viewer->Adapter->OnOpenWindow += gcnew OpenViewer::OpenWindowListener(instance,&ViewerInstance::OnOpenWindow);
  viewer->Adapter->OnStateChanged += gcnew OpenViewer::StateChangedListener(instance,&ViewerInstance::OnStateChanged);
  viewer->Adapter->OnAvatarPicked += gcnew OpenViewer::AvatarPickListener(instance,&ViewerInstance::OnAvatarPicked);
  viewer->Adapter->OnDispatch += gcnew OpenViewer::DispatchListener(instance,&ViewerInstance::OnDispatch);
  instance->viewer = viewer;
  instance->boot = gcnew Bootstrap(viewer,handle,instance->WindowWidth,instance->WindowHeight);
  instance->boot->RequireVersion = instance->RequireVersion;
  instance->boot->BackgroundColor = instance->BackgroundColor;
  instance->boot->InitBackgroundURL = instance->InitBackgroundURL;
  instance->boot->Load(gcnew OpenViewer::bootstrap::Bootstrap::OnViewerStartupDelegate(instance,&ViewerInstance::OnStartupCallback));
  mInitialized = TRUE;
  return TRUE;
}

void nsPluginInstance::shut()
{
  if (ViewerInstances::viewerInstances->ContainsKey((unsigned long long)this)) {
    ViewerInstance ^instance = ViewerInstances::viewerInstances[(unsigned long long)this];
    instance->boot->Shutdown();
    if (mListener != 0) mListener->Release();
    ViewerInstances::Remove((unsigned long long)this,instance);
  }
  // subclass it back
  SubclassWindow(mhWnd, lpOldProc);
  mhWnd = NULL;
  mInitialized = FALSE;
}

NPBool nsPluginInstance::isInitialized()
{
  return mInitialized;
}

// ==============================
// ! Scriptability related code !
// ==============================
//
// here the plugin is asked by Mozilla to tell if it is scriptable
// we should return a valid interface id and a pointer to 
// nsScriptablePeer interface which we should have implemented
// and which should be defined in the corressponding *.xpt file
// in the bin/components folder
NPError	nsPluginInstance::GetValue(NPPVariable aVariable, void *aValue)
{
  NPError rv = NPERR_NO_ERROR;

  if (aVariable == NPPVpluginScriptableInstance) {
    // addref happens in getter, so we don't addref here
    nsIScriptablePlugin * scriptablePeer = getScriptablePeer();
    if (scriptablePeer) {
      *(nsISupports **)aValue = scriptablePeer;
    } else
      rv = NPERR_OUT_OF_MEMORY_ERROR;
  }
  else if (aVariable == NPPVpluginScriptableIID) {
    static nsIID scriptableIID = NS_ISCRIPTABLEPLUGIN_IID;
    nsIID* ptr = (nsIID *)NPN_MemAlloc(sizeof(nsIID));
    if (ptr) {
        *ptr = scriptableIID;
        *(nsIID **)aValue = ptr;
    } else
      rv = NPERR_OUT_OF_MEMORY_ERROR;
  }

  return rv;
}

// ==============================
// ! Scriptability related code !
// ==============================
//
// this method will return the scriptable object (and create it if necessary)
nsScriptablePeer* nsPluginInstance::getScriptablePeer()
{
  if (!mScriptablePeer) {
    mScriptablePeer = new nsScriptablePeer(this);
    if(!mScriptablePeer)
      return NULL;

    NS_ADDREF(mScriptablePeer);
  }

  // add reference for the caller requesting the object
  NS_ADDREF(mScriptablePeer);
  return mScriptablePeer;
}

void nsPluginInstance::setEventListener(nsIJavaScriptEventListener* listener)
{
  if (mListener != NULL) {
    mListener->Release();
  }
  mListener = listener;
  listener->AddRef();
}

nsIJavaScriptEventListener* nsPluginInstance::getEventListener()
{
  return mListener;
}

static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg) {
    case WM_PAINT:
      break;
    default:
      break;
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}
