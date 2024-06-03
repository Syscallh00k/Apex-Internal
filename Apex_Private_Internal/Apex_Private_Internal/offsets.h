#pragma once
#include <iostream>
#include <Windows.h>
namespace OffsetsT1 {
	DWORD Entity = 0x1dd45f8; //cl_entitylist0x0216f7b0 
	DWORD LocalPlayer = 0x21830f8;
	DWORD ViewRender = 0x73f1978;
	DWORD viewAngles = 0x2534 - 0x14;
	DWORD in_duck = 0x073f2df8;
	DWORD PunchAngle = 0x2438;
	DWORD OFF_GLOW_ENABLE = 0x028c;                       //Script_Highlight_GetCurrentContext
	DWORD OFF_GLOW_THROUGH_WALL = 0x26c;                 //Script_Highlight_SetVisibilityType
	DWORD OFF_GLOW_FIX = 0x270;
	DWORD OFF_GLOW_HIGHLIGHT_ID = 0x298;                 //[DT_HighlightSettings].m_highlightServerActiveStates    
	DWORD OFF_GLOW_HIGHLIGHTS = 0xbb247d0;      //HighlightSettings

	DWORD showfps_enabled = 0x01787190;
	DWORD Bones = 0x0da0 + 0x48;
	DWORD m_grapple = 0x1da8;
	DWORD shadow_enable = 0x016292d0;
	DWORD CPlayer_camera_origin = 0x1ed0;
	DWORD ViewModule = 0x2d18;
	DWORD IN_JUMP = 0x073f2d00;
	DWORD TimeBase = 0x2088;
	DWORD m_traversalProgress = 0x2aec;
	DWORD m_traversalStartTime = 0x2af0;
	DWORD ss_viewmodelfov = 0x0215f4e0;
	DWORD m_iObserverMode = 0x34a4;
	DWORD m_xp = 0x3694;
	DWORD m_iSignifierName = 0x0468;
	DWORD m_ModelName = 0x0030;
	DWORD NameList = 0xc5ff080;
	DWORD ViewMatrix = 0x11a350;
	DWORD M_VecAbsOrigin = 0x017c;
	DWORD m_localOrigin = 0x0188;
	DWORD m_localAngles = 0x0194;
	DWORD m_Health = 0x0318;
	DWORD m_Shield = 0x01a0;
	DWORD m_MaxShield = 0x01a4;
	DWORD m_Shield_type = 0x462c;
	DWORD m_lastUCmdSimulationTicks = 0x1c54;
	DWORD m_lastUCmdSimulationRemainderTime = 0x1c58;
}
