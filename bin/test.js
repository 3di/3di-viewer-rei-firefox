function CalcObject()
{
	margin_top = 0;
	margin_left = 16;
	
	input_height = 48;
	
	
	sy = document.body.scrollTop;
	width = document.body.clientWidth;
	
	js_debug_text_fix.style.width = width - (margin_left * 2);
	js_debug_text_fix.style.left = margin_left;
	js_debug_text_fix.top = sy + margin_top;

	js_object_fix.style.left = margin_left;
	js_object_fix.style.top = sy + margin_top + input_height;
	
	js_cotain_fix.style.top = margin_top + input_height;
	js_cotain_fix.style.left = 800 + (margin_left * 2);
}


//----------------------------------------------------------
// 1. Login / Logout
//----------------------------------------------------------
function Login()
{
	var first = document.getElementById("first");
	var last = document.getElementById("last");
	var password = document.getElementById("password");
	var server = document.getElementById("server");
	var loginLocation = document.getElementById("loginLocation");
       	ctrl.Login(first.value, last.value, password.value, server.value, loginLocation.value);
}

function Logout()
{
	ctrl.Logout();
}

//----------------------------------------------------------
// 2. Touch
//----------------------------------------------------------
function TouchTo()
{
	var touch_res = document.getElementById("touch_res");
	ctrl.TouchTo(touch_res.value);
}

function TouchEventHandler(message)
{
	var touch_res = document.getElementById("touch_res");
	touch_res.value = message;
}

//----------------------------------------------------------
// 3. Sit
//----------------------------------------------------------
function SitOn()
{
	var touch_res = document.getElementById("touch_res");
	ctrl.SitOn(touch_res.value);
}

function StandUp()
{
	ctrl.StandUp();
}

//----------------------------------------------------------
// 4. Text chat
//----------------------------------------------------------
function SendChat()
{
	var chat_message = document.getElementById("chat_message");
	ctrl.SendChat(chat_message.value, 1);
}

function GetChatMessage()
{
    	var chat_history = document.getElementById("chat_history");
	var listNum = chat_history.length;
	var num = ctrl.GetMessageHistoryLength() - listNum;
				
	for (var i=0; i<num; i++)
	{
		var addParam = document.createElement("OPTION");
		addParam.text = ctrl.GetMessageFromHistory(listNum + i);
		addParam.value = listNum + i;
		
		chat_history.add(addParam,null);
	}
}

//----------------------------------------------------------
// 5. Teleport
//----------------------------------------------------------
function Teleport()
{
	var tel_region = document.getElementById("tel_region");
	var tel_x = document.getElementById("tel_x");
	var tel_y = document.getElementById("tel_y");
	var tel_z = document.getElementById("tel_z");
	ctrl.TeleportTo(tel_region.value, tel_x.value, tel_y.value, tel_z.value);
}

//----------------------------------------------------------
// 6.
//----------------------------------------------------------

//----------------------------------------------------------
// 7. Useravatar function
//----------------------------------------------------------
function GetUserAvatarName()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetUserAvatarName();
}

function GetUserAvatarPosition()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetUserAvatarPosition();
}

function UserAvatarUp()
{
	ctrl.UserAvatarUp();
}

function UserAvatarLeft()
{
	ctrl.UserAvatarLeft();
}

function UserAvatarRight()
{
	ctrl.UserAvatarRight();
}

function UserAvatarDown()
{
	ctrl.UserAvatarDown();
}

//----------------------------------------------------------
// 8. Common sample
//----------------------------------------------------------
function GetFPS()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetFPS();
}

function GetPrimitiveCount()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetPrimitiveCount();
}

function GetTextureCount()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetTextureCount();
}

//----------------------------------------------------------
// 9. Camera lookAt
//----------------------------------------------------------
function CameraLookAt()
{
	ctrl.CameraLookAt(64.0, 48.0, 128.0, 128.0, 25.0, 128.0);
}

function GetCameraPosition()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetCameraPosition();
}

function GetCameraTarget()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetCameraTarget();
}

function GetCameraDistance()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetCameraDistance();
}

function SetCameraDistance()
{
	var camera_distance = document.getElementById("camera_distance");
	ctrl.SetCameraDistance(camera_distance.value);
}

function GetCameraFOV()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetCameraFOV();
}

function SetCameraFOV()
{
	var camera_fov = document.getElementById("camera_fov");
	ctrl.SetCameraFOV(camera_fov.value);
}

function SetCameraFOVDegree()
{
	var camera_fov = document.getElementById("camera_fov");
	ctrl.SetCameraFOVDegree(camera_fov.value);
}

function GetCameraOffsetY()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetCameraOffsetY();
}

function SetCameraOffsetY()
{
	var camera_offset_y = document.getElementById("camera_offset_y");
	ctrl.SetCameraOffsetY(camera_offset_y.value);
}

function GetCameraAngleY()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetCameraAngleY();
}

function SetCameraAngleY()
{
	var camera_angle_min_y = document.getElementById("camera_angle_min_y");
	var camera_angle_max_y = document.getElementById("camera_angle_max_y");
	ctrl.SetCameraAngleY(camera_angle_min_y.value, camera_angle_max_y.value);
}

//----------------------------------------------------------
// 10. World
//----------------------------------------------------------
function GetAvatarCount()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetAvatarCount();
}

function GetObjectCount()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetObjectCount();
}

function GetRegionName()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetRegionName();
}

function GetWorldTime()
{
	var debug_info = document.getElementById("js_debug_text_fix");
	debug_info.value = ctrl.GetWorldTime();
}

function SetWorldTime()
{
	var world_time = document.getElementById("world_time");
	ctrl.SetWorldTime(world_time.value);
}

function SetTick(_flag)
{
	ctrl.SetTickOn(_flag);
}

function SetWorldAmbientColor()
{
	var world_ambient_color = document.getElementById("world_ambient_color");
	ctrl.SetWorldAmbientColor(world_ambient_color.value);
}

//----------------------------------------------------------
// 11. Fix directional
//----------------------------------------------------------
function SetFixDirectional(_flag)
{
	ctrl.SetFixDirectional(_flag);
}

function SetFixDirectionalRotation()
{
	var fix_directional_rotation = document.getElementById("fix_directional_rotation");
	ctrl.SetFixDirectionalRotation(fix_directional_rotation.value);
}

function SetFixDirectionalDiffuseColor()
{
	var fix_directional_diffuse = document.getElementById("fix_directional_rotation");
	ctrl.SetFixDirectionalDiffuseColor(fix_directional_diffuse.value);
}

function SetFixDirectionalAmbientColor()
{
	var fix_directional_diffuse = document.getElementById("fix_directional_ambient");
	ctrl.SetFixDirectionalAmbientColor(fix_directional_ambient.value);
}

