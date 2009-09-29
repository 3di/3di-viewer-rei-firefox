/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIScriptablePlugin.idl
 */

#ifndef __gen_nsIScriptablePlugin_h__
#define __gen_nsIScriptablePlugin_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIJavaScriptEventListener */
#define NS_IJAVASCRIPTEVENTLISTENER_IID_STR "d912b0be-b1e8-421c-af83-2f46dfe79081"

#define NS_IJAVASCRIPTEVENTLISTENER_IID \
  {0xd912b0be, 0xb1e8, 0x421c, \
    { 0xaf, 0x83, 0x2f, 0x46, 0xdf, 0xe7, 0x90, 0x81 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIJavaScriptEventListener : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IJAVASCRIPTEVENTLISTENER_IID)

  /* void OnDebugMessage (in string message); */
  NS_SCRIPTABLE NS_IMETHOD OnDebugMessage(const char *message) = 0;

  /* void OnTouched (in string uuid); */
  NS_SCRIPTABLE NS_IMETHOD OnTouched(const char *uuid) = 0;

  /* void OnReceivedMessage (in string uuid, in string avatarName, in wstring message); */
  NS_SCRIPTABLE NS_IMETHOD OnReceivedMessage(const char *uuid, const char *avatarName, const PRUnichar *message) = 0;

  /* void OnTeleport (in string regionName, in long x, in long y, in long z); */
  NS_SCRIPTABLE NS_IMETHOD OnTeleport(const char *regionName, PRInt32 x, PRInt32 y, PRInt32 z) = 0;

  /* void OnTeleported (in string uuid, in string avatar, in long x, in long y, in long z); */
  NS_SCRIPTABLE NS_IMETHOD OnTeleported(const char *uuid, const char *avatar, PRInt32 x, PRInt32 y, PRInt32 z) = 0;

  /* void OnOpenWindow (in string target, in string uri); */
  NS_SCRIPTABLE NS_IMETHOD OnOpenWindow(const char *target, const char *uri) = 0;

  /* void OnStateChanged (in long state); */
  NS_SCRIPTABLE NS_IMETHOD OnStateChanged(PRInt32 state) = 0;

  /* void OnAvatarPicked (in string uuid); */
  NS_SCRIPTABLE NS_IMETHOD OnAvatarPicked(const char *uuid) = 0;

  /* void OnDispatch (in string action, in string message); */
  NS_SCRIPTABLE NS_IMETHOD OnDispatch(const char *action, const char *message) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIJavaScriptEventListener, NS_IJAVASCRIPTEVENTLISTENER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIJAVASCRIPTEVENTLISTENER \
  NS_SCRIPTABLE NS_IMETHOD OnDebugMessage(const char *message); \
  NS_SCRIPTABLE NS_IMETHOD OnTouched(const char *uuid); \
  NS_SCRIPTABLE NS_IMETHOD OnReceivedMessage(const char *uuid, const char *avatarName, const PRUnichar *message); \
  NS_SCRIPTABLE NS_IMETHOD OnTeleport(const char *regionName, PRInt32 x, PRInt32 y, PRInt32 z); \
  NS_SCRIPTABLE NS_IMETHOD OnTeleported(const char *uuid, const char *avatar, PRInt32 x, PRInt32 y, PRInt32 z); \
  NS_SCRIPTABLE NS_IMETHOD OnOpenWindow(const char *target, const char *uri); \
  NS_SCRIPTABLE NS_IMETHOD OnStateChanged(PRInt32 state); \
  NS_SCRIPTABLE NS_IMETHOD OnAvatarPicked(const char *uuid); \
  NS_SCRIPTABLE NS_IMETHOD OnDispatch(const char *action, const char *message); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIJAVASCRIPTEVENTLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnDebugMessage(const char *message) { return _to OnDebugMessage(message); } \
  NS_SCRIPTABLE NS_IMETHOD OnTouched(const char *uuid) { return _to OnTouched(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD OnReceivedMessage(const char *uuid, const char *avatarName, const PRUnichar *message) { return _to OnReceivedMessage(uuid, avatarName, message); } \
  NS_SCRIPTABLE NS_IMETHOD OnTeleport(const char *regionName, PRInt32 x, PRInt32 y, PRInt32 z) { return _to OnTeleport(regionName, x, y, z); } \
  NS_SCRIPTABLE NS_IMETHOD OnTeleported(const char *uuid, const char *avatar, PRInt32 x, PRInt32 y, PRInt32 z) { return _to OnTeleported(uuid, avatar, x, y, z); } \
  NS_SCRIPTABLE NS_IMETHOD OnOpenWindow(const char *target, const char *uri) { return _to OnOpenWindow(target, uri); } \
  NS_SCRIPTABLE NS_IMETHOD OnStateChanged(PRInt32 state) { return _to OnStateChanged(state); } \
  NS_SCRIPTABLE NS_IMETHOD OnAvatarPicked(const char *uuid) { return _to OnAvatarPicked(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD OnDispatch(const char *action, const char *message) { return _to OnDispatch(action, message); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIJAVASCRIPTEVENTLISTENER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnDebugMessage(const char *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnDebugMessage(message); } \
  NS_SCRIPTABLE NS_IMETHOD OnTouched(const char *uuid) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnTouched(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD OnReceivedMessage(const char *uuid, const char *avatarName, const PRUnichar *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnReceivedMessage(uuid, avatarName, message); } \
  NS_SCRIPTABLE NS_IMETHOD OnTeleport(const char *regionName, PRInt32 x, PRInt32 y, PRInt32 z) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnTeleport(regionName, x, y, z); } \
  NS_SCRIPTABLE NS_IMETHOD OnTeleported(const char *uuid, const char *avatar, PRInt32 x, PRInt32 y, PRInt32 z) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnTeleported(uuid, avatar, x, y, z); } \
  NS_SCRIPTABLE NS_IMETHOD OnOpenWindow(const char *target, const char *uri) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnOpenWindow(target, uri); } \
  NS_SCRIPTABLE NS_IMETHOD OnStateChanged(PRInt32 state) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnStateChanged(state); } \
  NS_SCRIPTABLE NS_IMETHOD OnAvatarPicked(const char *uuid) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnAvatarPicked(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD OnDispatch(const char *action, const char *message) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnDispatch(action, message); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsJavaScriptEventListener : public nsIJavaScriptEventListener
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIJAVASCRIPTEVENTLISTENER

  nsJavaScriptEventListener();

private:
  ~nsJavaScriptEventListener();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsJavaScriptEventListener, nsIJavaScriptEventListener)

nsJavaScriptEventListener::nsJavaScriptEventListener()
{
  /* member initializers and constructor code */
}

nsJavaScriptEventListener::~nsJavaScriptEventListener()
{
  /* destructor code */
}

/* void OnDebugMessage (in string message); */
NS_IMETHODIMP nsJavaScriptEventListener::OnDebugMessage(const char *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnTouched (in string uuid); */
NS_IMETHODIMP nsJavaScriptEventListener::OnTouched(const char *uuid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnReceivedMessage (in string uuid, in string avatarName, in wstring message); */
NS_IMETHODIMP nsJavaScriptEventListener::OnReceivedMessage(const char *uuid, const char *avatarName, const PRUnichar *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnTeleport (in string regionName, in long x, in long y, in long z); */
NS_IMETHODIMP nsJavaScriptEventListener::OnTeleport(const char *regionName, PRInt32 x, PRInt32 y, PRInt32 z)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnTeleported (in string uuid, in string avatar, in long x, in long y, in long z); */
NS_IMETHODIMP nsJavaScriptEventListener::OnTeleported(const char *uuid, const char *avatar, PRInt32 x, PRInt32 y, PRInt32 z)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnOpenWindow (in string target, in string uri); */
NS_IMETHODIMP nsJavaScriptEventListener::OnOpenWindow(const char *target, const char *uri)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnStateChanged (in long state); */
NS_IMETHODIMP nsJavaScriptEventListener::OnStateChanged(PRInt32 state)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnAvatarPicked (in string uuid); */
NS_IMETHODIMP nsJavaScriptEventListener::OnAvatarPicked(const char *uuid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void OnDispatch (in string action, in string message); */
NS_IMETHODIMP nsJavaScriptEventListener::OnDispatch(const char *action, const char *message)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIScriptablePlugin */
#define NS_ISCRIPTABLEPLUGIN_IID_STR "bc43c2b9-e55b-4e4c-935a-cf1fd98db009"

#define NS_ISCRIPTABLEPLUGIN_IID \
  {0xbc43c2b9, 0xe55b, 0x4e4c, \
    { 0x93, 0x5a, 0xcf, 0x1f, 0xd9, 0x8d, 0xb0, 0x09 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIScriptablePlugin : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISCRIPTABLEPLUGIN_IID)

  /* void SetEventListener (in nsIJavaScriptEventListener listener); */
  NS_SCRIPTABLE NS_IMETHOD SetEventListener(nsIJavaScriptEventListener *listener) = 0;

  /* string GetPluginInfo (); */
  NS_SCRIPTABLE NS_IMETHOD GetPluginInfo(char **_retval) = 0;

  /* void Login (in string firstName, in string lastName, in string password, in string serverURL, in string loginLocation); */
  NS_SCRIPTABLE NS_IMETHOD Login(const char *firstName, const char *lastName, const char *password, const char *serverURL, const char *loginLocation) = 0;

  /* void Logout (); */
  NS_SCRIPTABLE NS_IMETHOD Logout(void) = 0;

  /* void TouchTo (in string uuid); */
  NS_SCRIPTABLE NS_IMETHOD TouchTo(const char *uuid) = 0;

  /* void SitOn (in string uuid); */
  NS_SCRIPTABLE NS_IMETHOD SitOn(const char *uuid) = 0;

  /* void StandUp (); */
  NS_SCRIPTABLE NS_IMETHOD StandUp(void) = 0;

  /* void SendChat (in wstring message, in long range); */
  NS_SCRIPTABLE NS_IMETHOD SendChat(const PRUnichar *message, PRInt32 range) = 0;

  /* wstring GetMessageFromHistory (in long index); */
  NS_SCRIPTABLE NS_IMETHOD GetMessageFromHistory(PRInt32 index, PRUnichar **_retval) = 0;

  /* long GetMessageHistoryLength (); */
  NS_SCRIPTABLE NS_IMETHOD GetMessageHistoryLength(PRInt32 *_retval) = 0;

  /* void TeleportTo (in string region, in long x, in long y, in long z); */
  NS_SCRIPTABLE NS_IMETHOD TeleportTo(const char *region, PRInt32 x, PRInt32 y, PRInt32 z) = 0;

  /* string GetUserAvatarName (); */
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarName(char **_retval) = 0;

  /* string GetUserAvatarPosition (); */
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarPosition(char **_retval) = 0;

  /* string GetUserAvatarUUID (); */
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarUUID(char **_retval) = 0;

  /* string GetUserUUID (); */
  NS_SCRIPTABLE NS_IMETHOD GetUserUUID(char **_retval) = 0;

  /* void UserAvatarUp (); */
  NS_SCRIPTABLE NS_IMETHOD UserAvatarUp(void) = 0;

  /* void UserAvatarDown (); */
  NS_SCRIPTABLE NS_IMETHOD UserAvatarDown(void) = 0;

  /* void UserAvatarLeft (); */
  NS_SCRIPTABLE NS_IMETHOD UserAvatarLeft(void) = 0;

  /* void UserAvatarRight (); */
  NS_SCRIPTABLE NS_IMETHOD UserAvatarRight(void) = 0;

  /* void StartCustomAnimation (in long index); */
  NS_SCRIPTABLE NS_IMETHOD StartCustomAnimation(PRInt32 index) = 0;

  /* string GetFPS (); */
  NS_SCRIPTABLE NS_IMETHOD GetFPS(char **_retval) = 0;

  /* string GetPrimitiveCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetPrimitiveCount(char **_retval) = 0;

  /* string GetTextureCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetTextureCount(char **_retval) = 0;

  /* void CameraLookAt (in float px, in float py, in float pz, in float tx, in float ty, in float tz); */
  NS_SCRIPTABLE NS_IMETHOD CameraLookAt(float px, float py, float pz, float tx, float ty, float tz) = 0;

  /* void SetCameraDistance (in float distance); */
  NS_SCRIPTABLE NS_IMETHOD SetCameraDistance(float distance) = 0;

  /* string GetCameraDistance (); */
  NS_SCRIPTABLE NS_IMETHOD GetCameraDistance(char **_retval) = 0;

  /* string GetCameraPosition (); */
  NS_SCRIPTABLE NS_IMETHOD GetCameraPosition(char **_retval) = 0;

  /* string GetCameraTarget (); */
  NS_SCRIPTABLE NS_IMETHOD GetCameraTarget(char **_retval) = 0;

  /* string GetCameraFOV (); */
  NS_SCRIPTABLE NS_IMETHOD GetCameraFOV(char **_retval) = 0;

  /* void SetCameraFOV (in float fov); */
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOV(float fov) = 0;

  /* void SetCameraFOVDegree (in float fov); */
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOVDegree(float fov) = 0;

  /* string GetCameraOffsetY (); */
  NS_SCRIPTABLE NS_IMETHOD GetCameraOffsetY(char **_retval) = 0;

  /* void SetCameraOffsetY (in float offsetY); */
  NS_SCRIPTABLE NS_IMETHOD SetCameraOffsetY(float offsetY) = 0;

  /* string GetCameraAngleY (); */
  NS_SCRIPTABLE NS_IMETHOD GetCameraAngleY(char **_retval) = 0;

  /* void SetCameraAngleY (in float min, in float max); */
  NS_SCRIPTABLE NS_IMETHOD SetCameraAngleY(float min, float max) = 0;

  /* void SetAvatarDisappearDistance (in float distance); */
  NS_SCRIPTABLE NS_IMETHOD SetAvatarDisappearDistance(float distance) = 0;

  /* string GetAvatarCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetAvatarCount(char **_retval) = 0;

  /* string GetObjectCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetObjectCount(char **_retval) = 0;

  /* string GetRegionName (); */
  NS_SCRIPTABLE NS_IMETHOD GetRegionName(char **_retval) = 0;

  /* string GetWorldTime (); */
  NS_SCRIPTABLE NS_IMETHOD GetWorldTime(char **_retval) = 0;

  /* void SetWorldTime (in string dataTime); */
  NS_SCRIPTABLE NS_IMETHOD SetWorldTime(const char *dataTime) = 0;

  /* void SetTickOn (in string flag); */
  NS_SCRIPTABLE NS_IMETHOD SetTickOn(const char *flag) = 0;

  /* void SetWorldAmbientColor (in string colors); */
  NS_SCRIPTABLE NS_IMETHOD SetWorldAmbientColor(const char *colors) = 0;

  /* void SetFixDirectional (in string flag); */
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectional(const char *flag) = 0;

  /* void SetFixDirectionalRotation (in string radRotation); */
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalRotation(const char *radRotation) = 0;

  /* void SetFixDirectionalDiffuseColor (in string colors); */
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalDiffuseColor(const char *colors) = 0;

  /* void SetFixDirectionalAmbientColor (in string colors); */
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalAmbientColor(const char *colors) = 0;

  /* string Callback (in string action, in string message); */
  NS_SCRIPTABLE NS_IMETHOD Callback(const char *action, const char *message, char **_retval) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIScriptablePlugin, NS_ISCRIPTABLEPLUGIN_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISCRIPTABLEPLUGIN \
  NS_SCRIPTABLE NS_IMETHOD SetEventListener(nsIJavaScriptEventListener *listener); \
  NS_SCRIPTABLE NS_IMETHOD GetPluginInfo(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD Login(const char *firstName, const char *lastName, const char *password, const char *serverURL, const char *loginLocation); \
  NS_SCRIPTABLE NS_IMETHOD Logout(void); \
  NS_SCRIPTABLE NS_IMETHOD TouchTo(const char *uuid); \
  NS_SCRIPTABLE NS_IMETHOD SitOn(const char *uuid); \
  NS_SCRIPTABLE NS_IMETHOD StandUp(void); \
  NS_SCRIPTABLE NS_IMETHOD SendChat(const PRUnichar *message, PRInt32 range); \
  NS_SCRIPTABLE NS_IMETHOD GetMessageFromHistory(PRInt32 index, PRUnichar **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetMessageHistoryLength(PRInt32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD TeleportTo(const char *region, PRInt32 x, PRInt32 y, PRInt32 z); \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarName(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarPosition(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarUUID(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetUserUUID(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarUp(void); \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarDown(void); \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarLeft(void); \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarRight(void); \
  NS_SCRIPTABLE NS_IMETHOD StartCustomAnimation(PRInt32 index); \
  NS_SCRIPTABLE NS_IMETHOD GetFPS(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetPrimitiveCount(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetTextureCount(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD CameraLookAt(float px, float py, float pz, float tx, float ty, float tz); \
  NS_SCRIPTABLE NS_IMETHOD SetCameraDistance(float distance); \
  NS_SCRIPTABLE NS_IMETHOD GetCameraDistance(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetCameraPosition(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetCameraTarget(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetCameraFOV(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOV(float fov); \
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOVDegree(float fov); \
  NS_SCRIPTABLE NS_IMETHOD GetCameraOffsetY(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetCameraOffsetY(float offsetY); \
  NS_SCRIPTABLE NS_IMETHOD GetCameraAngleY(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetCameraAngleY(float min, float max); \
  NS_SCRIPTABLE NS_IMETHOD SetAvatarDisappearDistance(float distance); \
  NS_SCRIPTABLE NS_IMETHOD GetAvatarCount(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetObjectCount(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetRegionName(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetWorldTime(char **_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetWorldTime(const char *dataTime); \
  NS_SCRIPTABLE NS_IMETHOD SetTickOn(const char *flag); \
  NS_SCRIPTABLE NS_IMETHOD SetWorldAmbientColor(const char *colors); \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectional(const char *flag); \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalRotation(const char *radRotation); \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalDiffuseColor(const char *colors); \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalAmbientColor(const char *colors); \
  NS_SCRIPTABLE NS_IMETHOD Callback(const char *action, const char *message, char **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISCRIPTABLEPLUGIN(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetEventListener(nsIJavaScriptEventListener *listener) { return _to SetEventListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD GetPluginInfo(char **_retval) { return _to GetPluginInfo(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD Login(const char *firstName, const char *lastName, const char *password, const char *serverURL, const char *loginLocation) { return _to Login(firstName, lastName, password, serverURL, loginLocation); } \
  NS_SCRIPTABLE NS_IMETHOD Logout(void) { return _to Logout(); } \
  NS_SCRIPTABLE NS_IMETHOD TouchTo(const char *uuid) { return _to TouchTo(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD SitOn(const char *uuid) { return _to SitOn(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD StandUp(void) { return _to StandUp(); } \
  NS_SCRIPTABLE NS_IMETHOD SendChat(const PRUnichar *message, PRInt32 range) { return _to SendChat(message, range); } \
  NS_SCRIPTABLE NS_IMETHOD GetMessageFromHistory(PRInt32 index, PRUnichar **_retval) { return _to GetMessageFromHistory(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetMessageHistoryLength(PRInt32 *_retval) { return _to GetMessageHistoryLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD TeleportTo(const char *region, PRInt32 x, PRInt32 y, PRInt32 z) { return _to TeleportTo(region, x, y, z); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarName(char **_retval) { return _to GetUserAvatarName(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarPosition(char **_retval) { return _to GetUserAvatarPosition(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarUUID(char **_retval) { return _to GetUserAvatarUUID(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserUUID(char **_retval) { return _to GetUserUUID(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarUp(void) { return _to UserAvatarUp(); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarDown(void) { return _to UserAvatarDown(); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarLeft(void) { return _to UserAvatarLeft(); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarRight(void) { return _to UserAvatarRight(); } \
  NS_SCRIPTABLE NS_IMETHOD StartCustomAnimation(PRInt32 index) { return _to StartCustomAnimation(index); } \
  NS_SCRIPTABLE NS_IMETHOD GetFPS(char **_retval) { return _to GetFPS(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetPrimitiveCount(char **_retval) { return _to GetPrimitiveCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTextureCount(char **_retval) { return _to GetTextureCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD CameraLookAt(float px, float py, float pz, float tx, float ty, float tz) { return _to CameraLookAt(px, py, pz, tx, ty, tz); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraDistance(float distance) { return _to SetCameraDistance(distance); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraDistance(char **_retval) { return _to GetCameraDistance(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraPosition(char **_retval) { return _to GetCameraPosition(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraTarget(char **_retval) { return _to GetCameraTarget(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraFOV(char **_retval) { return _to GetCameraFOV(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOV(float fov) { return _to SetCameraFOV(fov); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOVDegree(float fov) { return _to SetCameraFOVDegree(fov); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraOffsetY(char **_retval) { return _to GetCameraOffsetY(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraOffsetY(float offsetY) { return _to SetCameraOffsetY(offsetY); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraAngleY(char **_retval) { return _to GetCameraAngleY(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraAngleY(float min, float max) { return _to SetCameraAngleY(min, max); } \
  NS_SCRIPTABLE NS_IMETHOD SetAvatarDisappearDistance(float distance) { return _to SetAvatarDisappearDistance(distance); } \
  NS_SCRIPTABLE NS_IMETHOD GetAvatarCount(char **_retval) { return _to GetAvatarCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetObjectCount(char **_retval) { return _to GetObjectCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegionName(char **_retval) { return _to GetRegionName(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWorldTime(char **_retval) { return _to GetWorldTime(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetWorldTime(const char *dataTime) { return _to SetWorldTime(dataTime); } \
  NS_SCRIPTABLE NS_IMETHOD SetTickOn(const char *flag) { return _to SetTickOn(flag); } \
  NS_SCRIPTABLE NS_IMETHOD SetWorldAmbientColor(const char *colors) { return _to SetWorldAmbientColor(colors); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectional(const char *flag) { return _to SetFixDirectional(flag); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalRotation(const char *radRotation) { return _to SetFixDirectionalRotation(radRotation); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalDiffuseColor(const char *colors) { return _to SetFixDirectionalDiffuseColor(colors); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalAmbientColor(const char *colors) { return _to SetFixDirectionalAmbientColor(colors); } \
  NS_SCRIPTABLE NS_IMETHOD Callback(const char *action, const char *message, char **_retval) { return _to Callback(action, message, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISCRIPTABLEPLUGIN(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetEventListener(nsIJavaScriptEventListener *listener) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetEventListener(listener); } \
  NS_SCRIPTABLE NS_IMETHOD GetPluginInfo(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPluginInfo(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD Login(const char *firstName, const char *lastName, const char *password, const char *serverURL, const char *loginLocation) { return !_to ? NS_ERROR_NULL_POINTER : _to->Login(firstName, lastName, password, serverURL, loginLocation); } \
  NS_SCRIPTABLE NS_IMETHOD Logout(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->Logout(); } \
  NS_SCRIPTABLE NS_IMETHOD TouchTo(const char *uuid) { return !_to ? NS_ERROR_NULL_POINTER : _to->TouchTo(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD SitOn(const char *uuid) { return !_to ? NS_ERROR_NULL_POINTER : _to->SitOn(uuid); } \
  NS_SCRIPTABLE NS_IMETHOD StandUp(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->StandUp(); } \
  NS_SCRIPTABLE NS_IMETHOD SendChat(const PRUnichar *message, PRInt32 range) { return !_to ? NS_ERROR_NULL_POINTER : _to->SendChat(message, range); } \
  NS_SCRIPTABLE NS_IMETHOD GetMessageFromHistory(PRInt32 index, PRUnichar **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMessageFromHistory(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetMessageHistoryLength(PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMessageHistoryLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD TeleportTo(const char *region, PRInt32 x, PRInt32 y, PRInt32 z) { return !_to ? NS_ERROR_NULL_POINTER : _to->TeleportTo(region, x, y, z); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarName(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUserAvatarName(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarPosition(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUserAvatarPosition(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserAvatarUUID(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUserAvatarUUID(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUserUUID(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUserUUID(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarUp(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->UserAvatarUp(); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarDown(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->UserAvatarDown(); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarLeft(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->UserAvatarLeft(); } \
  NS_SCRIPTABLE NS_IMETHOD UserAvatarRight(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->UserAvatarRight(); } \
  NS_SCRIPTABLE NS_IMETHOD StartCustomAnimation(PRInt32 index) { return !_to ? NS_ERROR_NULL_POINTER : _to->StartCustomAnimation(index); } \
  NS_SCRIPTABLE NS_IMETHOD GetFPS(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetFPS(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetPrimitiveCount(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPrimitiveCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTextureCount(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTextureCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD CameraLookAt(float px, float py, float pz, float tx, float ty, float tz) { return !_to ? NS_ERROR_NULL_POINTER : _to->CameraLookAt(px, py, pz, tx, ty, tz); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraDistance(float distance) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCameraDistance(distance); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraDistance(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCameraDistance(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraPosition(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCameraPosition(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraTarget(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCameraTarget(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraFOV(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCameraFOV(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOV(float fov) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCameraFOV(fov); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraFOVDegree(float fov) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCameraFOVDegree(fov); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraOffsetY(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCameraOffsetY(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraOffsetY(float offsetY) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCameraOffsetY(offsetY); } \
  NS_SCRIPTABLE NS_IMETHOD GetCameraAngleY(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCameraAngleY(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetCameraAngleY(float min, float max) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCameraAngleY(min, max); } \
  NS_SCRIPTABLE NS_IMETHOD SetAvatarDisappearDistance(float distance) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAvatarDisappearDistance(distance); } \
  NS_SCRIPTABLE NS_IMETHOD GetAvatarCount(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAvatarCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetObjectCount(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetObjectCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetRegionName(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetRegionName(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWorldTime(char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWorldTime(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetWorldTime(const char *dataTime) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetWorldTime(dataTime); } \
  NS_SCRIPTABLE NS_IMETHOD SetTickOn(const char *flag) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTickOn(flag); } \
  NS_SCRIPTABLE NS_IMETHOD SetWorldAmbientColor(const char *colors) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetWorldAmbientColor(colors); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectional(const char *flag) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFixDirectional(flag); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalRotation(const char *radRotation) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFixDirectionalRotation(radRotation); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalDiffuseColor(const char *colors) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFixDirectionalDiffuseColor(colors); } \
  NS_SCRIPTABLE NS_IMETHOD SetFixDirectionalAmbientColor(const char *colors) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFixDirectionalAmbientColor(colors); } \
  NS_SCRIPTABLE NS_IMETHOD Callback(const char *action, const char *message, char **_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->Callback(action, message, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsScriptablePlugin : public nsIScriptablePlugin
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISCRIPTABLEPLUGIN

  nsScriptablePlugin();

private:
  ~nsScriptablePlugin();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsScriptablePlugin, nsIScriptablePlugin)

nsScriptablePlugin::nsScriptablePlugin()
{
  /* member initializers and constructor code */
}

nsScriptablePlugin::~nsScriptablePlugin()
{
  /* destructor code */
}

/* void SetEventListener (in nsIJavaScriptEventListener listener); */
NS_IMETHODIMP nsScriptablePlugin::SetEventListener(nsIJavaScriptEventListener *listener)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetPluginInfo (); */
NS_IMETHODIMP nsScriptablePlugin::GetPluginInfo(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Login (in string firstName, in string lastName, in string password, in string serverURL, in string loginLocation); */
NS_IMETHODIMP nsScriptablePlugin::Login(const char *firstName, const char *lastName, const char *password, const char *serverURL, const char *loginLocation)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void Logout (); */
NS_IMETHODIMP nsScriptablePlugin::Logout()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TouchTo (in string uuid); */
NS_IMETHODIMP nsScriptablePlugin::TouchTo(const char *uuid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SitOn (in string uuid); */
NS_IMETHODIMP nsScriptablePlugin::SitOn(const char *uuid)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void StandUp (); */
NS_IMETHODIMP nsScriptablePlugin::StandUp()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SendChat (in wstring message, in long range); */
NS_IMETHODIMP nsScriptablePlugin::SendChat(const PRUnichar *message, PRInt32 range)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring GetMessageFromHistory (in long index); */
NS_IMETHODIMP nsScriptablePlugin::GetMessageFromHistory(PRInt32 index, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetMessageHistoryLength (); */
NS_IMETHODIMP nsScriptablePlugin::GetMessageHistoryLength(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void TeleportTo (in string region, in long x, in long y, in long z); */
NS_IMETHODIMP nsScriptablePlugin::TeleportTo(const char *region, PRInt32 x, PRInt32 y, PRInt32 z)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetUserAvatarName (); */
NS_IMETHODIMP nsScriptablePlugin::GetUserAvatarName(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetUserAvatarPosition (); */
NS_IMETHODIMP nsScriptablePlugin::GetUserAvatarPosition(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetUserAvatarUUID (); */
NS_IMETHODIMP nsScriptablePlugin::GetUserAvatarUUID(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetUserUUID (); */
NS_IMETHODIMP nsScriptablePlugin::GetUserUUID(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UserAvatarUp (); */
NS_IMETHODIMP nsScriptablePlugin::UserAvatarUp()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UserAvatarDown (); */
NS_IMETHODIMP nsScriptablePlugin::UserAvatarDown()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UserAvatarLeft (); */
NS_IMETHODIMP nsScriptablePlugin::UserAvatarLeft()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UserAvatarRight (); */
NS_IMETHODIMP nsScriptablePlugin::UserAvatarRight()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void StartCustomAnimation (in long index); */
NS_IMETHODIMP nsScriptablePlugin::StartCustomAnimation(PRInt32 index)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetFPS (); */
NS_IMETHODIMP nsScriptablePlugin::GetFPS(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetPrimitiveCount (); */
NS_IMETHODIMP nsScriptablePlugin::GetPrimitiveCount(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetTextureCount (); */
NS_IMETHODIMP nsScriptablePlugin::GetTextureCount(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void CameraLookAt (in float px, in float py, in float pz, in float tx, in float ty, in float tz); */
NS_IMETHODIMP nsScriptablePlugin::CameraLookAt(float px, float py, float pz, float tx, float ty, float tz)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCameraDistance (in float distance); */
NS_IMETHODIMP nsScriptablePlugin::SetCameraDistance(float distance)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetCameraDistance (); */
NS_IMETHODIMP nsScriptablePlugin::GetCameraDistance(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetCameraPosition (); */
NS_IMETHODIMP nsScriptablePlugin::GetCameraPosition(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetCameraTarget (); */
NS_IMETHODIMP nsScriptablePlugin::GetCameraTarget(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetCameraFOV (); */
NS_IMETHODIMP nsScriptablePlugin::GetCameraFOV(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCameraFOV (in float fov); */
NS_IMETHODIMP nsScriptablePlugin::SetCameraFOV(float fov)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCameraFOVDegree (in float fov); */
NS_IMETHODIMP nsScriptablePlugin::SetCameraFOVDegree(float fov)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetCameraOffsetY (); */
NS_IMETHODIMP nsScriptablePlugin::GetCameraOffsetY(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCameraOffsetY (in float offsetY); */
NS_IMETHODIMP nsScriptablePlugin::SetCameraOffsetY(float offsetY)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetCameraAngleY (); */
NS_IMETHODIMP nsScriptablePlugin::GetCameraAngleY(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCameraAngleY (in float min, in float max); */
NS_IMETHODIMP nsScriptablePlugin::SetCameraAngleY(float min, float max)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetAvatarDisappearDistance (in float distance); */
NS_IMETHODIMP nsScriptablePlugin::SetAvatarDisappearDistance(float distance)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetAvatarCount (); */
NS_IMETHODIMP nsScriptablePlugin::GetAvatarCount(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetObjectCount (); */
NS_IMETHODIMP nsScriptablePlugin::GetObjectCount(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetRegionName (); */
NS_IMETHODIMP nsScriptablePlugin::GetRegionName(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string GetWorldTime (); */
NS_IMETHODIMP nsScriptablePlugin::GetWorldTime(char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetWorldTime (in string dataTime); */
NS_IMETHODIMP nsScriptablePlugin::SetWorldTime(const char *dataTime)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetTickOn (in string flag); */
NS_IMETHODIMP nsScriptablePlugin::SetTickOn(const char *flag)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetWorldAmbientColor (in string colors); */
NS_IMETHODIMP nsScriptablePlugin::SetWorldAmbientColor(const char *colors)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetFixDirectional (in string flag); */
NS_IMETHODIMP nsScriptablePlugin::SetFixDirectional(const char *flag)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetFixDirectionalRotation (in string radRotation); */
NS_IMETHODIMP nsScriptablePlugin::SetFixDirectionalRotation(const char *radRotation)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetFixDirectionalDiffuseColor (in string colors); */
NS_IMETHODIMP nsScriptablePlugin::SetFixDirectionalDiffuseColor(const char *colors)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetFixDirectionalAmbientColor (in string colors); */
NS_IMETHODIMP nsScriptablePlugin::SetFixDirectionalAmbientColor(const char *colors)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* string Callback (in string action, in string message); */
NS_IMETHODIMP nsScriptablePlugin::Callback(const char *action, const char *message, char **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIScriptablePlugin_h__ */
