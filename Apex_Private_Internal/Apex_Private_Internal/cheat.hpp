#include "Draw.hpp"
#include "glob.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"// This is messy not for out side eye 
#include "imgui/imgui_impl_win32.h"
#include "kiero/kiero.h"
#include "math.hpp"
#include "memory.hpp"
#include <d3d11.h>
#include <dxgi.h>
#include <string>
#include <string.h>
#include <vector>
#include <Windows.h>
#include <cmath> // hypot
#include <rpcndr.h>
#include <iostream>
#include <cstddef>
#include "Homer.h"
#define LOG std::cout << "[DEBUG] " << 
ID3D11ShaderResourceView* Homer_Texture = nullptr;
ID3D11ShaderResourceView* Peter_Texture = nullptr;

int HightlightID = 1;
 bool Box = false;
 bool CornerBox = false;
 bool ThreeBox = false;
 bool HomerESP = false;
 bool Peter_GreiffenEsp = false;
 bool Name = false;
 bool TeamCheck = false;
 bool SquadCheck = false;
 bool HealthBar = false;
 bool ShieldBar = false;
 bool Operator = false;
 bool Weapon = false;
 bool Skeleon = false;
 bool RainbowSkeleton = false;
 bool Level = false;
 bool TeamID = false;
 bool Glow = false;
 bool PGlow;
 bool Distance = false;
 bool PDistance = false;
 bool SeerHealthBar = false;
 bool FreeCam = false;
 bool SimulateCMD = false;
 float Ticks;
 bool HeirloomChanger;
 bool BigMapRadar;
 int FreeCamKey;
 bool Super_Glide = false;
 int Super_GlideKey;
 bool CanSpin = false;
 bool Psilent;
 int PsilentKey;
 int HitPrecent;
 bool Auto_Grapple = false;
 int Auto_GrappleKey;
 int SimulateCMDKey;
 bool Force_CrossPlay = false;
 bool Show_Fps = false;
 int SkinID;
 bool DisableShadow = false;
 bool FovChanger = false;
 float PlayerFov;
 float MaxDistance = 250.0f;
 bool Teleportation = false;
 int UpTpKey;
 int DownTpKey;
 Vector2 TpStrength;
 bool NoJumpRestraint = false;
bool init = false;
bool Quick_Melee = false;
bool Rcs = false;
bool SpinBot = false;
bool Draw_Menu = false;
bool NewMenu = false;
float BoxColor[4] = { 255,255,255,255 };
float DistanceColor[3] = { 255,255,255 };
float LineColor[3] = { 255,255,255 };
float TargetLineColor[3] = { 255,255,255 };

float OperatorColor[3] = { 255,255,255 };
float LevelColor[3] = { 255,255,255 };
float NameColor[3] = { 255,255,255 };
bool VectorAim;
int AimbotKey;
bool OFFIndicator = false;
bool FovCircle;
bool TargetLine = false;
float FovSize;
bool SnapLine = false;
float FovColor[3] = {255,255,255};
std::uintptr_t LocalPlayer;
std::uintptr_t cl_entitylist;
uintptr_t render;
uintptr_t Matrixa;

void W2S(Vector3 Position, Vector3& Screen, BaseMatrix Matrix)
{
	Vector3 out;
	float _x = Matrix.at[0] * Position.x + Matrix.at[1] * Position.y + Matrix.at[2] * Position.z + Matrix.at[3];
	float _y = Matrix.at[4] * Position.x + Matrix.at[5] * Position.y + Matrix.at[6] * Position.z + Matrix.at[7];
	out.z = Matrix.at[12] * Position.x + Matrix.at[13] * Position.y + Matrix.at[14] * Position.z + Matrix.at[15];

	if (out.z < 0.1f) return;

	_x *= 1.f / out.z;
	_y *= 1.f / out.z;

	out.x = ImGui::GetIO().DisplaySize.x * .5f;
	out.y = ImGui::GetIO().DisplaySize.y * .5f;

	out.x += 0.5f * _x * ImGui::GetIO().DisplaySize.x + 0.5f;
	out.y -= 0.5f * _y * ImGui::GetIO().DisplaySize.y + 0.5f;
	Screen = out;
}


namespace Offsets {
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
void DrawRotatedImageWithBox(ImTextureID textureID, float x, float y, float width, float height)
{
	// Calculate the center point of the rectangle
	ImVec2 center = ImVec2(x + width * 0.5f, y + height * 0.5f);

	// Calculate the rotation angle (180 degrees)
	float angle = 3.14159265359f; // 180 degrees in radians

	// Calculate the transformation matrix for rotation
	ImVec2 rotationMatrix[2] = {
		ImVec2(cos(angle), -sin(angle)), // Adjusted to avoid flipping
		ImVec2(sin(angle), cos(angle))   // Adjusted to avoid flipping
	};

	// Rotate the texture
	ImVec2 rotatedTopLeft = ImVec2(
		center.x + rotationMatrix[0].x * (x - center.x) + rotationMatrix[0].y * (y - center.y),
		center.y + rotationMatrix[1].x * (x - center.x) + rotationMatrix[1].y * (y - center.y)
	);

	ImVec2 rotatedBottomRight = ImVec2(
		center.x + rotationMatrix[0].x * ((x + width) - center.x) + rotationMatrix[0].y * ((y + height) - center.y),
		center.y + rotationMatrix[1].x * ((x + width) - center.x) + rotationMatrix[1].y * ((y + height) - center.y)
	);

	// Draw the rotated image
	ImGui::GetBackgroundDrawList()->AddImage(textureID, rotatedTopLeft, rotatedBottomRight);
}

template<typename T = uintptr_t, typename A>
T ReadMem(A address) {
	auto addresss = *reinterpret_cast<uintptr_t*>(address);
	constexpr uintptr_t min_address = 0x40000;
	constexpr uintptr_t max_address = 0x7FFFFFFF0000;

	if (addresss >= min_address && (addresss + sizeof(T)) < max_address) {
		return *reinterpret_cast<T*>(address);
	}
	else {
		throw std::runtime_error("Invalid memory address or out of bounds.");
	}
}
float GlowColor[3];
inline std::string getName(uintptr_t address)
{
	for (int i = 0; i < 250; i++)
	{
		std::uintptr_t Entity = (*reinterpret_cast<std::uintptr_t*>(((uintptr_t)GetModuleHandleA(NULL) + Offsets::Entity + (i << 5))));

		if (address == Entity)
		{
			uintptr_t nameptr = *reinterpret_cast<uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::NameList + (i - 1) * 0x10);
			if (!nameptr) continue;

			char* name = reinterpret_cast<char*>(nameptr);
			std::string s(name);
			return s;
		}
	}
	return "";
}

inline std::string getModelName(uintptr_t Address)
{
	uintptr_t pMode_Name = *reinterpret_cast<uintptr_t*>(Address + Offsets::m_ModelName);
	char* modelName = reinterpret_cast<char*>(pMode_Name);
	std::string s(modelName);
	return s;
}
inline std::string getSignifierName(uintptr_t Address)
{
	uintptr_t sigAddr = *reinterpret_cast<uintptr_t*>(Address + Offsets::m_iSignifierName);
	if (sigAddr == 0)
		return "";

	char* sig = reinterpret_cast<char*>(sigAddr);
	std::string s = std::string(sig);

	return s;
}
inline int GetPlayerLevel(uintptr_t address)
{
	int m_xp = *reinterpret_cast<int*>(address + Offsets::m_xp); //m_xp
	if (m_xp < 0) return 0;
	if (m_xp < 100) return 1;

	int levels[] = { 2750, 6650, 11400, 17000, 23350, 30450, 38300, 46450, 55050, 64100, 73600, 83550, 93950, 104800, 116100, 127850, 140050, 152400, 164900, 177550, 190350, 203300, 216400, 229650, 243050, 256600, 270300, 284150, 298150, 312300, 326600, 341050, 355650, 370400, 385300, 400350, 415550, 430900, 446400, 462050, 477850, 493800, 509900, 526150, 542550, 559100, 575800, 592650, 609650, 626800, 644100, 661550, 679150, 696900, 714800 };

	int level = 56;
	int arraySize = sizeof(levels) / sizeof(levels[0]);

	for (int i = 0; i < arraySize; i++)
	{
		if (m_xp < levels[i])
		{
			return i + 1;
		}
	}

	return level + ((m_xp - levels[arraySize - 1] + 1) / 18000);
}
bool IsVisable(uintptr_t LittleNiglet)
{
	return 0;
}
inline Vector3 getBonePositionByHitbox(int id, uintptr_t address)
{
	Vector3 origin = *reinterpret_cast<Vector3*>(address + Offsets::M_VecAbsOrigin);

	//BoneByHitBox
	uint64_t Model = *(uint64_t*)(address + 0xff0);

	//get studio hdr
	uint64_t StudioHdr = *reinterpret_cast<uint64_t*>(Model + 0x8);

	//get hitbox array
	uint16_t HitboxCache = *reinterpret_cast<uint16_t*>(StudioHdr + 0x34);
	uint64_t HitBoxsArray = StudioHdr + ((uint16_t)(HitboxCache & 0xFFFE) << (4 * (HitboxCache & 1)));

	uint16_t IndexCache = *reinterpret_cast<uint16_t*>(HitBoxsArray + 0x4);
	int HitboxIndex = ((uint16_t)(IndexCache & 0xFFFE) << (4 * (IndexCache & 1)));

	uint16_t Bone = *reinterpret_cast<uint16_t*>(HitBoxsArray + HitboxIndex + (id * 0x20));

	if (Bone < 0 || Bone > 255)
		return Vector3();

	//hitpos
	uint64_t BoneArray = *(uint64_t*)(address + Offsets::Bones);

	matrix3x4_t Matrix = *reinterpret_cast<matrix3x4_t*>(BoneArray + Bone * sizeof(matrix3x4_t));

	return Vector3(Matrix.m_flMatVal[0][3] + origin.x, Matrix.m_flMatVal[1][3] + origin.y, Matrix.m_flMatVal[2][3] + origin.z);
}
float SkeletonColor[3];
int bloodhoundBones[] = { 0, 1, 2, 4, -5, 1, 6, 7, 19, -5, 1, 8, 9, 10, -5, 4, 11, 12, 13, 14, -5, 4, 15, 16, 17, 18 };
int regualrBones[] = { 0, 1, 3, 4, -5, 1, 6, 7, 8, -5, 1, 9, 10, 11, -5, 4, 12, 13, 14, 15, -5, 4, 16, 17, 18, 19 };
void boneEsp(uintptr_t entity, BaseMatrix Matrix)
{
	for (int i = 1; i < 26; i++)
	{
		auto Script = getModelName(entity);


		if (Script.find("bloodhound") != -1)
		{
			if (bloodhoundBones[i] == -5)
			{
				i++;
				continue;
			}

			Vector3 first = getBonePositionByHitbox(bloodhoundBones[i - 1], entity); //getBonePositionByHitbox(entity, bloodhoundBones[i - 1]);
			Vector3 firstA;
			W2S(first, firstA, Matrix);
			if (firstA.Empty()) continue;

			Vector3 last = getBonePositionByHitbox(bloodhoundBones[i], entity);//getBonePositionByHitbox(entity, bloodhoundBones[i]);
			Vector3 lastA;
			W2S(last, lastA, Matrix);

			//last = ProjectWorldToScreen(last);
			if (lastA.Empty()) continue;

			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x, firstA.y), ImVec2(lastA.x, lastA.y), ImColor(SkeletonColor[0], SkeletonColor[1], SkeletonColor[2]), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x - 1, firstA.y), ImVec2(lastA.x - 1, lastA.y), ImColor(0, 0, 0), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x + 1, firstA.y), ImVec2(lastA.x + 1, lastA.y), ImColor(0, 0, 0), 1);


			Vector3 firstHead = getBonePositionByHitbox(0, entity); //getBonePositionByHitbox(entity, bloodhoundBones[i - 1]);
			Vector3 firstAHead;
			W2S(firstHead, firstAHead, Matrix);
			if (firstAHead.Empty()) continue;

			Vector3 lastHead = getBonePositionByHitbox(1, entity);//getBonePositionByHitbox(entity, bloodhoundBones[i]);
			Vector3 lastAHead;
			W2S(lastHead, lastAHead, Matrix);
			if (lastAHead.Empty()) continue;
			float Radius = std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y);
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y), ImColor(SkeletonColor[0], SkeletonColor[1], SkeletonColor[2], 255.f));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius - 1, ImColor(0, 0, 0, 255));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius + 1, ImColor(0, 0, 0, 255));
		}
		else
		{
			if (regualrBones[i] == -5)
			{
				i++;
				continue;
			}
			Vector3 first = getBonePositionByHitbox(regualrBones[i - 1], entity);
			Vector3 firstA;
			W2S(first, firstA, Matrix);
			if (firstA.Empty()) continue;
			//first = ProjectWorldToScreen(first);

			Vector3 last = getBonePositionByHitbox(regualrBones[i], entity);
			Vector3 lastA;
			W2S(last, lastA, Matrix);
			if (lastA.Empty()) continue;
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x, firstA.y), ImVec2(lastA.x, lastA.y), ImColor(SkeletonColor[0], SkeletonColor[1], SkeletonColor[2]), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x - 1, firstA.y), ImVec2(lastA.x - 1, lastA.y), ImColor(0, 0, 0), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x + 1, firstA.y), ImVec2(lastA.x + 1, lastA.y), ImColor(0, 0, 0), 1);


			Vector3 firstHead = getBonePositionByHitbox(0, entity); //getBonePositionByHitbox(entity, bloodhoundBones[i - 1]);
			Vector3 firstAHead;
			W2S(firstHead, firstAHead, Matrix);
			if (firstAHead.Empty()) continue;

			Vector3 lastHead = getBonePositionByHitbox(1, entity);//getBonePositionByHitbox(entity, bloodhoundBones[i]);
			Vector3 lastAHead;
			W2S(lastHead, lastAHead, Matrix);
			if (lastAHead.Empty()) continue;
			float Radius = std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y);
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y), ImColor(SkeletonColor[0], SkeletonColor[1], SkeletonColor[2], 255.f));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius - 1, ImColor(0, 0, 0, 255));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius + 1, ImColor(0, 0, 0, 255));
		}
	}

}

void RainbowboneEsp(uintptr_t entity, BaseMatrix Matrix)
{
	for (int i = 1; i < 26; i++)
	{
		auto Script = getModelName(entity);

		static int cases = 0;
		static float r = 1.00f, g = 0.00f, b = 1.00f;
		switch (cases)
		{
		case 0: { r -= 0.0001f; if (r <= 0) cases += 1; break; }
		case 1: { g += 0.0001f; b -= 0.0001f; if (g >= 1) cases += 1; break; }
		case 2: { r += 0.0001f; if (r >= 1) cases += 1; break; }
		case 3: { b += 0.0001f; g -= 0.0001f; if (b >= 1) cases = 0; break; }
		default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
		}


		if (Script.find("bloodhound") != -1)
		{
			if (bloodhoundBones[i] == -5)
			{
				i++;
				continue;
			}

			Vector3 first = getBonePositionByHitbox(bloodhoundBones[i - 1], entity); //getBonePositionByHitbox(entity, bloodhoundBones[i - 1]);
			Vector3 firstA;
			W2S(first, firstA, Matrix);
			if (firstA.Empty()) continue;

			Vector3 last = getBonePositionByHitbox(bloodhoundBones[i], entity);//getBonePositionByHitbox(entity, bloodhoundBones[i]);
			Vector3 lastA;
			W2S(last, lastA, Matrix);

			//last = ProjectWorldToScreen(last);
			if (lastA.Empty()) continue;

			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x, firstA.y), ImVec2(lastA.x, lastA.y), ImColor(r,g,b,255.f), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x - 1, firstA.y), ImVec2(lastA.x - 1, lastA.y), ImColor(0, 0, 0), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x + 1, firstA.y), ImVec2(lastA.x + 1, lastA.y), ImColor(0, 0, 0), 1);

			// Do Head
			Vector3 firstHead = getBonePositionByHitbox(0, entity); //getBonePositionByHitbox(entity, bloodhoundBones[i - 1]);
			Vector3 firstAHead;
			W2S(firstHead, firstAHead, Matrix);
			if (firstAHead.Empty()) continue;

			Vector3 lastHead = getBonePositionByHitbox(1, entity);//getBonePositionByHitbox(entity, bloodhoundBones[i]);
			Vector3 lastAHead;
			W2S(lastHead, lastAHead, Matrix);
			if (lastAHead.Empty()) continue;
			float Radius = std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y);
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y), ImColor(r, g, b, 255.f));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius - 1, ImColor(0, 0, 0, 255));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius + 1, ImColor(0, 0, 0, 255));

		}
		else
		{
			if (regualrBones[i] == -5)
			{
				i++;
				continue;
			}
			Vector3 first = getBonePositionByHitbox(regualrBones[i - 1], entity);
			Vector3 firstA;
			W2S(first, firstA, Matrix);
			if (firstA.Empty()) continue;
			//first = ProjectWorldToScreen(first);

			Vector3 last = getBonePositionByHitbox(regualrBones[i], entity);
			Vector3 lastA;
			W2S(last, lastA, Matrix);
			if (lastA.Empty()) continue;
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x, firstA.y), ImVec2(lastA.x, lastA.y), ImColor(r, g, b, 255.f), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x - 1, firstA.y), ImVec2(lastA.x - 1, lastA.y), ImColor(0, 0, 0), 1);
			ImGui::GetForegroundDrawList()->AddLine(ImVec2(firstA.x + 1, firstA.y), ImVec2(lastA.x + 1, lastA.y), ImColor(0, 0, 0), 1);

			// Do Head


			Vector3 firstHead = getBonePositionByHitbox(0, entity); //getBonePositionByHitbox(entity, bloodhoundBones[i - 1]);
			Vector3 firstAHead;
			W2S(firstHead, firstAHead, Matrix);
			if (firstAHead.Empty()) continue;

			Vector3 lastHead = getBonePositionByHitbox(1, entity);//getBonePositionByHitbox(entity, bloodhoundBones[i]);
			Vector3 lastAHead;
			W2S(lastHead, lastAHead, Matrix);
			if (lastAHead.Empty()) continue;
			float Radius = std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y);
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), std::hypot(firstAHead.x - lastAHead.x, firstAHead.y - lastAHead.y), ImColor(r, g, b, 255.f));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius - 1, ImColor(0, 0, 0, 255));
			ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(firstAHead.x, firstAHead.y), Radius + 1, ImColor(0, 0, 0, 255));
		}
	}

}


int id = 1;
int TickCount;
const long highlightSize = 0x34;

float BlacktrackTime;
Vector2  SilentAngles;
bool WasTrue = true;
void SilentBlacktrack()
{
	ULONG64 NetChannel = *reinterpret_cast<ULONG64*>((uintptr_t)GetModuleHandleA(NULL) + 0x16f93a0);
	ULONG64 m_pCommands = *reinterpret_cast<ULONG64*>((uintptr_t)GetModuleHandleA(NULL) + 0x216c070);
	ULONG LastCommand = *reinterpret_cast<ULONG*>((uintptr_t)GetModuleHandleA(NULL) + 0x1712134);
	ULONG64 CurrentCommand = m_pCommands + (0x228 * (LastCommand % 750));

	if (WasTrue)
	{
		printf("Net Channel 0x%lx\n", NetChannel);
		printf("m_pCommands 0x%lx\n", m_pCommands);
		printf("LastC ommand 0x%lx\n", LastCommand);
		printf("Current Command 0x%lx\n", CurrentCommand);
		WasTrue = false;
	}
	//*reinterpret_cast<float*>(CurrentCommand + 0x8) = BlacktrackTime;
	//*reinterpret_cast<Vector2*>(CurrentCommand + 0xC) = SilentAngles;
}

std::vector<uintptr_t> TempList;


/// GLOW
struct GlowMode {
	ULONG BodyStyle, borderStyle, borderWidth, transparency;
};

void SetGlowState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, GlowMode NewGlowMode) {
	 GlowMode oldGlowMode = *reinterpret_cast<GlowMode*>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4);
	 *reinterpret_cast<GlowMode*>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 4) = NewGlowMode;
}

void SetColorState(long HighlightSettingsPointer, long HighlightSize, int HighlightID, Vector3 NewColor) {
	const Vector3 oldColor = *reinterpret_cast<Vector3*>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 8);
	*reinterpret_cast<Vector3*>(HighlightSettingsPointer + (HighlightSize * HighlightID) + 8) = NewColor;
}

void SetGlow(uintptr_t Target, int GlowEnabled, int GlowThroughWall, int HighlightID) {
	*reinterpret_cast<int*>(Target + Offsets::OFF_GLOW_ENABLE) = GlowEnabled;
	*reinterpret_cast<int*>(Target + Offsets::OFF_GLOW_THROUGH_WALL) = GlowThroughWall;
	*reinterpret_cast<int*>(Target + Offsets::OFF_GLOW_FIX) = 2;
	
}

inline Vector3 getBonePos(int id, uintptr_t Address)
{
	Vector3 pos = *reinterpret_cast<Vector3*>(Address + Offsets::M_VecAbsOrigin); //PoopSets::M_VecAbsOrigin
	uintptr_t bones = *reinterpret_cast<uintptr_t*>(Address + Offsets::Bones); //PoopSets::demfuckingBone
	Vector3 bone = {};
	UINT32 boneloc = (id * 0x30);
	bone_t bo = {};
	bo = *reinterpret_cast<bone_t*>(bones + boneloc);

	bone.x = bo.x + pos.x;
	bone.y = bo.y + pos.y;
	bone.z = bo.z + pos.z;
	return bone;
}
std::uintptr_t Aimbot_Target(BaseMatrix M)
{
	std::uintptr_t BestEntity = NULL;
	float Size = 999999.0f;
	for (auto I = 0; I <= 250; I++)
	{
		std::uintptr_t LocalPlayer = (*reinterpret_cast<std::uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::LocalPlayer));
		if (!LocalPlayer) return BestEntity;

		std::uintptr_t Entity = (*reinterpret_cast<std::uintptr_t*>(((uintptr_t)GetModuleHandleA(NULL) + Offsets::Entity + ((I + 1) << 5))));
		if (!Entity) return BestEntity;

		Vector3 Head_Position = getBonePos(BoneList::Head, Entity);
		if (Head_Position.Empty()) return BestEntity;

		Vector3 Screen;
		W2S(Head_Position, Screen, M);
		if (Screen.Empty()) return Entity;
		float Length_To_Center =sqrt(pow((GetSystemMetrics(SM_CXSCREEN) / 2) - Screen.x, 2) + pow((GetSystemMetrics(SM_CYSCREEN) / 2) - Screen.y, 2));
		if (Length_To_Center < Size && Length_To_Center <= (FovSize)) {
			Size = Length_To_Center;
			BestEntity = Entity;

			if (TargetLine)
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Screen.x, Screen.y), ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), ImColor(TargetLineColor[0], TargetLineColor[1], TargetLineColor[2], 255.f));
		}
	}
	return BestEntity;
}

/*Vector3 Head2d = getBonePos(BoneList::Head, Entity);
		Vector3 NewPos;
		W2S(Head2d, NewPos, M);
		if (NewPos.Empty()) return bestEnt;
		float length = sqrt(pow((GetSystemMetrics(SM_CXSCREEN) / 2) - NewPos.x, 2) + pow((GetSystemMetrics(SM_CYSCREEN) / 2) - NewPos.y, 2));

		if (length < closest && length <= (FovSize)) {
			closest = length;
			bestEnt = Entity;
			if (TargetLine)
				ImGui::GetBackgroundDrawList()->AddLine(ImVec2(NewPos.x, NewPos.y), ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), ImColor(TargetLineColor[0], TargetLineColor[1], TargetLineColor[2], 255.f));
		}*/
 int smothing = 1;
 float previousPitch = 0;
 float previousYaw = 0;
 float pitchSTR = 1;
 float yawSTR = 1;
 /*void Read() {
	 Name = Memory::ReadString(OFF_REGION + OFF_LEVEL);
	 IsPlayable = !Name.empty() && Name != "mp_lobby";
	 IsFiringRange = Name == "mp_rr_canyonlands_staging_mu1";
 }*/
 void aimbot(uintptr_t ents, uintptr_t localPlayer, BaseMatrix M) {
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		if (localPlayer != NULL) {
			uintptr_t ent = Aimbot_Target(M);
			if (ent != NULL) {
				Vector3 newAngle = CalcAngle(getBonePositionByHitbox(0,LocalPlayer), getBonePositionByHitbox(0, ent));
				if (newAngle.Empty()) return;
				if (newAngle.x != 0 && newAngle.y != 0)
				{
					/*Vector3 ViewAngle = *reinterpret_cast<Vector3*>(LocalPlayer + Offsets::viewAngles);
					Vector3 delta = newAngle - ViewAngle;

					delta.Normalize();
					float newSmoothing = smothing;
					if (smothing == 1)
					{
						newSmoothing = 1.0f;
					}
					else {
						newSmoothing *= 18;
					}

					delta.y /= newSmoothing;*/
					
					*reinterpret_cast<Vector2*>(LocalPlayer + Offsets::viewAngles) = Vector2(newAngle.x , newAngle.y );
				}
			}
		}
	}
}
 void noRecoil(uintptr_t localPlayer) {
	 if (localPlayer != NULL) {
		 Vector2 angles;
		 angles.y = *reinterpret_cast<float*>(localPlayer + Offsets::viewAngles); //works
		 angles.x = *reinterpret_cast<float*>(localPlayer + Offsets::viewAngles + sizeof(float)); // works
		 Vector2 punch = *reinterpret_cast<Vector2*>(localPlayer + Offsets::PunchAngle);
		 if (punch.y < 0 || punch.x < 0) {
			 angles.x -= (punch.y - previousYaw) * yawSTR;
			 angles.y -= (punch.x - previousPitch) * pitchSTR;
			 //NormalizeAngles(angles);
			 *reinterpret_cast<float*>(localPlayer + Offsets::viewAngles) = angles.y;
			 *reinterpret_cast<float*>(localPlayer + Offsets::viewAngles + sizeof(float)) = angles.x;
			 previousPitch = punch.x;
			 previousYaw = punch.y;
		 }
	 }
 }
 float NIglet = 0.f;
 void InitPlayer() {
	 if ((uintptr_t)GetModuleHandleA(NULL) == NULL) return;

	 LocalPlayer = (*reinterpret_cast<std::uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::LocalPlayer));
	 if (!LocalPlayer)return;
	 cl_entitylist = (*reinterpret_cast<std::uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::Entity));
	 if (!cl_entitylist)return;
	 render = *reinterpret_cast<std::uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::ViewRender);
	 if (!render)return;
	 Matrixa = *reinterpret_cast<std::uintptr_t*>(Offsets::ViewMatrix + render);
	 if (!Matrixa)return;
	 BaseMatrix M = *reinterpret_cast<BaseMatrix*>(Matrixa);

	 Vector3 ViewAngle = *reinterpret_cast<Vector3*>(LocalPlayer + Offsets::viewAngles);
	 std::string View = "[View Angles]   [ X : " + std::to_string(int(ViewAngle.x)) + " ] [ Y : " + std::to_string(int(ViewAngle.y)) + " ] [ Z : " + std::to_string(int(ViewAngle.x)) + " ]";
	 ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 500), ImColor(255, 0, 0, 255), View.c_str());

	 std::string LocalPlayerText = "[Local Player]   [ 0x" + std::to_string(DWORD(LocalPlayer)) + " ]";
	 ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 525), ImColor(255, 0, 0, 255), LocalPlayerText.c_str());

	 std::string cl_entitylistText = "[cl_entitylist]   [ 0x" + std::to_string(DWORD(cl_entitylist)) + " ]";
	 ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 550), ImColor(255, 0, 0, 255), cl_entitylistText.c_str());

	 std::string MatrixaText = "[Matrix]   [ 0x" + std::to_string(DWORD(Matrixa)) + " ]";
	 ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 575), ImColor(255, 0, 0, 255), MatrixaText.c_str());

	 for (auto idx{ 0 }; idx <= 250; idx++)
	 {
		 std::uintptr_t Entity = (*reinterpret_cast<std::uintptr_t*>(((uintptr_t)GetModuleHandleA(NULL) + Offsets::Entity + ((idx + 1) << 5))));
		 if (Entity == LocalPlayer) continue;

		 if (!Entity) continue;

		 auto Ent_Script = getSignifierName(Entity);

		 if (Ent_Script == "player" || Ent_Script == "npc_dummie")
		 {
			 Vector3 Position = (*reinterpret_cast<Vector3*>(Entity + Offsets::M_VecAbsOrigin));
			 if (Position.Empty()) continue;
			 Vector3 LPPosition = (*reinterpret_cast<Vector3*>(LocalPlayer + Offsets::M_VecAbsOrigin));
			 if (LPPosition.Empty()) continue;

			 float DistancAe = calcDist(Position, LPPosition) / 20;
			 if (DistancAe >= MaxDistance) continue;
			 Vector3 Pos1 = Position;
			 Pos1.z += 75;

			 Vector3 Topout;
			 W2S(Position, Topout, M);

			 Vector3 Bottomout;
			 W2S(Pos1, Bottomout, M);



			 Vector3 Pos2 = Position;
			 Pos2.x += HightlightID;

			 Vector3 NewPosHomer;
			 W2S(Pos2, NewPosHomer, M);

			 if (Bottomout.Empty()) continue;

			 if (Topout.Empty()) continue;
			 if (NewPosHomer.Empty()) continue;

			 int Current_Health = (*reinterpret_cast<int*>(Entity + Offsets::m_Health));

			 int Current_Shield = (*reinterpret_cast<int*>(Entity + Offsets::m_Shield));

			 int Max_Shield = (*reinterpret_cast<int*>(Entity + Offsets::m_MaxShield));

			 int Current_Shield_Type = (*reinterpret_cast<int*>(Entity + Offsets::m_Shield_type));

			 int LocalPlayer_Health = (*reinterpret_cast<int*>(Entity + Offsets::m_Health));
																  
			 if (LocalPlayer_Health < 0.1f) continue; // If Dead Skip Entity
			 if (Current_Health < 0.1f) continue; // If i am dead don't pass through

			 float height = Bottomout.y - Topout.y;
			 float width = height / 2.3;
			 if (Peter_GreiffenEsp)
			 {
				 DrawRotatedImageWithBox(Peter_Texture, NewPosHomer.x, NewPosHomer.y, width, height);
			 }
			 if (HomerESP)
			 {
				 DrawRotatedImageWithBox(Homer_Texture, NewPosHomer.x, NewPosHomer.y,width,height);
			 }
			 if (ThreeBox)
				 ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Topout.x, Topout.y), ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), ImColor(LineColor[0], LineColor[1], LineColor[2], 255.f));

			 if (Level)
			 {
				 std::string Text = std::to_string(int(GetPlayerLevel(Entity))) + " Level";
				 ImVec2 Size = ImGui::CalcTextSize(Text.c_str());
				 ImGui::GetBackgroundDrawList()->AddText(ImVec2(Topout.x - (Size.x / 2), Topout.y + 40), ImColor(LevelColor[0], LevelColor[1], LevelColor[2], 255.f), Text.c_str());

			 }
			 if (Box)
			 {
				 DrawBox(ImVec2(Bottomout.x, Bottomout.y), ImVec2(Topout.x, Topout.y), ImColor(0, 0, 0, 255), 1.f);
				 DrawBox(ImVec2(Bottomout.x, Bottomout.y), ImVec2(Topout.x, Topout.y), ImColor(BoxColor[0], BoxColor[1], BoxColor[2], 255.f), .5f);
			 }

			 if (CornerBox)
				 DrawCorneredBox(Topout.x - (height / 4), Topout.y, height / 2, height, ImColor(BoxColor[0], BoxColor[1], BoxColor[2], 255.f), 0.7f);

			 if (HealthBar)
			 {
				 float width = (float(height) / 2) * (float(Current_Health) / 100);
				 ImColor HealthCol;

				 if (Current_Health > 75)
				 {
					 HealthCol = { 0,255,0,255 };
				 }
				 else if (Current_Health > 45)
				 {
					 HealthCol = { 255, 99,0,255 };
				 }
				 else {
					 HealthCol = { 255,0,0,255 };

				 }
				 ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Topout.x - height / 4 - 1, Topout.y + 3 - 1), ImVec2(Topout.x + height / 4 + 1, Topout.y + 9 + 1), ImColor(0, 0, 0)); // black outline
				 ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Topout.x - height / 4, Topout.y + 3), ImVec2(Topout.x + height / 4, Topout.y + 9), ImColor(28, 28, 28)); // grey background
				 ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(Topout.x - height / 4, Topout.y + 3), ImVec2((Topout.x - height / 4) + width, Topout.y + 9), HealthCol); // green health bar
			 }
			 if (ShieldBar)
			 {
				 int shield = Current_Shield;
				 float width = (float(height) / 2) * (float(shield) / 125);
				 bool draw = true;
				 int shieldType = Current_Shield_Type;
				 ImColor color;
				 if (shieldType == 5)
				 {
					 color = ImColor(200, 15, 50);
				 }
				 else if (shieldType == 4)
				 {
					 color = ImColor(205, 195, 50);
				 }
				 else if (shieldType == 3)
				 {
					 color = ImColor(150, 65, 245);
				 }
				 else if (shieldType == 2)
				 {
					 color = ImColor(25, 115, 175);
				 }
				 else if (shieldType == 1)
				 {
					 color = ImColor(215, 215, 215);
				 }
				 else
				 {
					 draw = false;
				 }

				 if (draw)
				 {
					 if (HealthBar == true)
					 {
						 ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Topout.x - height / 4, Topout.y + 12), ImVec2(Topout.x + height / 4, Topout.y + 18), ImColor(28, 28, 28)); // grey background
						 ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Topout.x - height / 4, Topout.y + 12), ImVec2((Topout.x - height / 4) + width, Topout.y + 18), color); // shield bar
						 ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Topout.x - height / 4 - 1, Topout.y + 12 - 1), ImVec2(Topout.x + height / 4 + 1, Topout.y + 18 + 1), ImColor(0, 0, 0)); // black outline
					 }
					 else
					 {
						 ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Topout.x - height / 4, Topout.y + 3), ImVec2(Topout.x + height / 4, Topout.y + 9), ImColor(28, 28, 28)); // grey background
						 ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(Topout.x - height / 4, Topout.y + 3), ImVec2((Topout.x - height / 4) + width, Topout.y + 9), color); // shield bar
						 ImGui::GetBackgroundDrawList()->AddRect(ImVec2(Topout.x - height / 4 - 1, Topout.y + 12 - 1), ImVec2(Topout.x + height / 4 + 1, Topout.y + 18 + 1), ImColor(0, 0, 0)); // black outline
					 }
				 }
			 }
			 if (SeerHealthBar)
			 {
				 if (DistancAe <= 100.0f)
					 SeerHealth(Bottomout.x, Bottomout.y, Current_Shield, Max_Shield, Current_Shield_Type, Current_Health);
			 }
			 if (Name)
			 {
				 auto Text = getName(Entity);
				 ImVec2 Size = ImGui::CalcTextSize(Text.c_str());
				 ImGui::GetBackgroundDrawList()->AddText(ImVec2(Bottomout.x - (Size.x / 2), Bottomout.y - 15), ImColor(NameColor[0], NameColor[1], NameColor[2], 255.f), Text.c_str());
			 }
			 if (PDistance == true)
			 {
				 std::string Text = "" + std::to_string(int(DistancAe)) + "M";
				 ImVec2 Size = ImGui::CalcTextSize(Text.c_str());
				 ImGui::GetBackgroundDrawList()->AddText(ImVec2(Topout.x - (Size.x / 2), Topout.y + 55), ImColor(DistanceColor[0], DistanceColor[1], DistanceColor[2], 255.f), Text.c_str());
			 }

			 if (Skeleon)
				 boneEsp(Entity, M);

			 if (RainbowSkeleton)
				 RainbowboneEsp(Entity, M);

			 if (Operator)
			 {
				 std::string Text = "None";
				 auto Script = getModelName(Entity);
				 if (Script.find("pathfinder") != std::string::npos)
					 Text = "Path Finder";
				 else if (Script.find("octane") != std::string::npos)
					 Text = "Octane";
				 else if (Script.find("bloodhound") != std::string::npos)
					 Text = "BloodHound";
				 else if (Script.find("valkyrie") != std::string::npos)
					 Text = "Valkyrie";
				 else if (Script.find("bangalore") != std::string::npos)
					 Text = "Bangalore";
				 else if (Script.find("fuse") != std::string::npos)
					 Text = "Fuse";
				 else if (Script.find("ash") != std::string::npos)
					 Text = "Ash";
				 else if (Script.find("mad maggie") != std::string::npos)
					 Text = "Mad Maggie";
				 else if (Script.find("ballistic") != std::string::npos)
					 Text = "Ballistic";
				 else if (Script.find("wraith") != std::string::npos)
					 Text = "Wraith";
				 else if (Script.find("revenant") != std::string::npos)
					 Text = "Revenant";
				 else if (Script.find("horizon") != std::string::npos)
					 Text = "Horizon";
				 else if (Script.find("crypto") != std::string::npos)
					 Text = "Crypto";
				 else if (Script.find("seer") != std::string::npos)
					 Text = "Seer";
				 else if (Script.find("vantage") != std::string::npos)
					 Text = "Vantage";
				 else if (Script.find("gibraltar") != std::string::npos)
					 Text = "Gibraltar";
				 else if (Script.find("lifeline") != std::string::npos)
					 Text = "Lifeline";
				 else if (Script.find("mirage") != std::string::npos)
					 Text = "Mirage";
				 else if (Script.find("loba") != std::string::npos)
					 Text = "Loba";
				 else if (Script.find("newcastle") != std::string::npos)
					 Text = "Newcastle";
				 else if (Script.find("conduit") != std::string::npos)
					 Text = "Conduit";
				 else if (Script.find("caustic") != std::string::npos)
					 Text = "caustic";
				 else if (Script.find("wattson") != std::string::npos)
					 Text = "Wattson";
				 else if (Script.find("rampart") != std::string::npos)
					 Text = "Rampart";
				 else if (Script.find("catalyst") != std::string::npos)
					 Text = "Catalyst";
				 else if (Script.find("dummy") != std::string::npos)
					 Text = "Dummy";
				 else
					 Text = "Unkown";
				 ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

				 ImGui::GetBackgroundDrawList()->AddText(ImVec2(Topout.x - (Size.x / 2), Topout.y + 25), ImColor(OperatorColor[0], OperatorColor[1], OperatorColor[2], 255.f), Text.c_str());
			 }

			 if (FreeCam)
			 {
				 if (GetAsyncKeyState(FreeCamKey))
				 {
					 *reinterpret_cast<int*>(LocalPlayer + Offsets::m_iObserverMode) = 7;
					 std::string Text = "[Free Cam]";
					 ImVec2 Size = ImGui::CalcTextSize(Text.c_str());

					 ImGui::GetBackgroundDrawList()->AddText(ImVec2(GetSystemMetrics(0) / 2 - Size.x, GetSystemMetrics(1) / 2 - Size.y), ImColor(255, 0, 0, 255), Text.c_str());
				 }
				 else {
					 *reinterpret_cast<int*>(LocalPlayer + Offsets::m_iObserverMode) = 0;
				 }
			 }
			 if (SimulateCMD)
			 {

				 if (GetAsyncKeyState(SimulateCMDKey))
					 *reinterpret_cast<int*>(LocalPlayer + Offsets::m_lastUCmdSimulationTicks) = 1132396544;

			 }
			 if (Auto_Grapple)
			 {
				 if (GetAsyncKeyState(Auto_GrappleKey))
				 {
					 *reinterpret_cast<int*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::IN_JUMP + 0x8) = 4;

					 auto Gn = *reinterpret_cast<int*>(LocalPlayer + Offsets::m_grapple + 0x0048);
					 if (Gn == 1) {
						 *reinterpret_cast<int*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::IN_JUMP + 0x8) = 5;
					 }
				 }
			 }
			 if (Psilent)
			 {
				 if (GetAsyncKeyState(VK_RBUTTON))
					 int Random = rand() % 10;
				 {
					 uintptr_t ent = Aimbot_Target(M);
					 if (ent != NULL) {
						 Vector3 newAngle = CalcAngle(getBonePositionByHitbox(0, LocalPlayer), getBonePositionByHitbox(0, ent));
						 
							 SilentAngles = { newAngle.x,newAngle.y };
						 BlacktrackTime = 1;
						 SilentBlacktrack();


					 }
				 }
			 }
		 }
		
		 if (Super_Glide)
		 {
			 uintptr_t m_grapple = Offsets::m_grapple;
			 uintptr_t timeBase = Offsets::TimeBase;
			 uintptr_t OFFSET_m_traversalStartTime = Offsets::m_traversalStartTime;
			 uintptr_t OFFSET_m_traversalProgress = Offsets::m_traversalProgress;
			 static float startjumpTime = 0;
			 static bool startSg = false;

			 float	WorldTime = *reinterpret_cast<float*>(LocalPlayer + timeBase);
			 float m_traversalStartTime = *reinterpret_cast<float*>(LocalPlayer + OFFSET_m_traversalStartTime);
			 float m_traversalProgress = *reinterpret_cast<float*>(LocalPlayer + OFFSET_m_traversalProgress);
			 auto HangOnWall = -(m_traversalStartTime - WorldTime);

			 if (GetAsyncKeyState(Super_GlideKey))
			 {
				 if (m_traversalProgress > 0.87f && !startSg && HangOnWall > 0.05f && HangOnWall < 1.5f) {
					 //start SG
					 startjumpTime = WorldTime;
					 startSg = true;
				 }

				 if (startSg) {
					 //press button
					 *reinterpret_cast<int*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::IN_JUMP + 0x8) = 7;
					 if ((WorldTime - startjumpTime) > 0.007) {
						 *reinterpret_cast<int*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::in_duck + 0x8) = 6;
					 }
				 }

				 if ((WorldTime - startjumpTime) > 1.5f && startSg) {
					 //need to release button
					 *reinterpret_cast<int*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::IN_JUMP + 0x8) = 4;
					 *reinterpret_cast<int*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::in_duck + 0x8) = 4;
					 startSg = false;
				 }

			 }

		 }
		 if (VectorAim)
		 {
			 aimbot(Entity, LocalPlayer, M);
		 }
		 if (Glow)
		 {
			/* const long HighlightSettingsPointer = *reinterpret_cast<long*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::OFF_GLOW_HIGHLIGHTS);
			 const long HighlightSize = 0x28;
			 const GlowMode LockedOnMode = { 136, 6, 32, 127 };
			 Vector3 LockedOnColor = { 0, 0.75, 0.75 };
			 LockedOnColor.x = GlowColor[0];
			 LockedOnColor.y = GlowColor[1];
			 LockedOnColor.z = GlowColor[2];
 			 SetGlowState(HighlightSettingsPointer, HighlightSize, 92, LockedOnMode);
			 SetColorState(HighlightSettingsPointer, HighlightSize, 92, LockedOnColor);*/
			 SetGlow(Entity, 1, 2, HightlightID);
		 }
		 if (HeirloomChanger)
		 {
			 auto handle = *reinterpret_cast<uintptr_t*>(LocalPlayer + Offsets::ViewModule);
			 handle &= 0xFFFF;
			 auto ptr = (uint64_t)((uintptr_t)GetModuleHandleA(NULL) + Offsets::Entity + (handle << 5));
			 if (!ptr) return;
			 char modelName[200] = { 0 };
			 auto name_ptr = *reinterpret_cast<uint64_t*>(ptr + Offsets::m_ModelName);
			 std::string model_name = getModelName(ptr);
			 int cur_seq, index;
			 std::cout << "MDL : " << model_name << "\n";
			 if (model_name.find("mdl/weapons/empty_handed/ptpov_emptyhand.rmdl") != std::string::npos)
			 {
				 printf("Found Hand\n");
				 *(const char**)(name_ptr) = "mdl/Weapons/drumstick/ptpov_baton_lifeline.rmdl";
				 *(int*)(ptr + 0x00d8) = 3605;
			 }
			 else if (model_name.find("") != std::string::npos)
			 {
				 cur_seq = (int)(ptr + 0x0e14);
				 index = (int)(ptr + 0x0e08);
				 if (cur_seq == 0 && index == 3605) { *(int*)(ptr + 0x0e14) = 30; }
			 }
		 }
		 if (BigMapRadar)
		 {
			 int LocalPlayer_TeamID = (*reinterpret_cast<int*>(LocalPlayer + 0x0328)); //m_iTeamNum=0x0328
			 if (LocalPlayer_TeamID != 1) {
				 uintptr_t timeBase = Offsets::TimeBase;

				 float curTime = *reinterpret_cast<float*>(Entity + timeBase);
				 double continueTime = 0.2;
				 float endTime = curTime + continueTime;
				 while (curTime < endTime)
				 {
					 *reinterpret_cast<int*>(Entity + 0x0328) = 1;
					 curTime = *reinterpret_cast<float*>(Entity + timeBase);
				 }
				 curTime = *reinterpret_cast<float*>(Entity + timeBase);
				 endTime = curTime + continueTime;
				 while (curTime < endTime)
				 {
					 *reinterpret_cast<int*>(Entity + 0x0328) = LocalPlayer_TeamID;
					 curTime = *reinterpret_cast<float*>(Entity + timeBase);
				 }
			 }
			 for (int i = 1; i <= 32; i++)
			 {
				 int nowtime = GetTickCount();
				 while (GetTickCount() - nowtime < 200) {
					 *reinterpret_cast<int*>(Entity + 0x0328, i);
				 }
			 }
			 *reinterpret_cast<int*>(Entity + 0x0328) = LocalPlayer_TeamID;
		 }

		 if (OFFIndicator)
		 {
			 
		 }

		 //Jump BYpass
		 if (Teleportation)
		 {
			 //m_laserSightColorCustomized=0x256b


			 if (GetAsyncKeyState(UpTpKey))
			 {
				 *reinterpret_cast<bool*>(LocalPlayer + 0x4038) = true; //m_isLungingToPosition=0x4038
				 *reinterpret_cast<bool*>(LocalPlayer + 0x4068) = true; //m_lungeCanFly=0x4068
				 *reinterpret_cast<float*>(LocalPlayer + 0x4074) = 9000.f; //m_lungeMaxTime=0x4074
				 *reinterpret_cast<float*>(LocalPlayer + 0x4078) = 9000.f; //m_lungeMaxEndSpeed=0x4074
				 *reinterpret_cast<Vector3*>(LocalPlayer + 0x403c) = Vector3(TpStrength.x, 0, 0); //m_lungeTargetPosition=0x403c
			 }
			 if (GetAsyncKeyState(DownTpKey))
			 {
				 *reinterpret_cast<bool*>(LocalPlayer + 0x4038) = true; //m_isLungingToPosition=0x4038
				 *reinterpret_cast<bool*>(LocalPlayer + 0x4068) = true; //m_lungeCanFly=0x4068
				 *reinterpret_cast<Vector3*>(LocalPlayer + 0x403c) = Vector3(0, TpStrength.y, 0); //m_lungeTargetPosition=0x403c
			 }

		 }
		 if (Show_Fps) //// works
			 *reinterpret_cast<bool*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::showfps_enabled + 0x6c) = true;
		 else  *reinterpret_cast<bool*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::showfps_enabled + 0x6c) = false;

		 if (DisableShadow) //// works
			 *reinterpret_cast<bool*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::shadow_enable + 0x6c) = false;
		 else  *reinterpret_cast<bool*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::shadow_enable + 0x6c) = true;


		 if (FovChanger) //// works
			 *reinterpret_cast<float*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::ss_viewmodelfov + 0x6c) = PlayerFov;

		 if (Rcs)
		 {
			 noRecoil(LocalPlayer);
		 }
		 if (Quick_Melee)
		 {
			 // m_melee = 0x3190
			 uintptr_t m_melee = *reinterpret_cast<uintptr_t*>(LocalPlayer + 0x3190);
			 if (m_melee)
			 {
				 *reinterpret_cast<bool*>(m_melee + 0x000d) = true; //m_flTimeLastJumped=0x35e0
				 *reinterpret_cast<Vector3*>(m_melee + 0x0028) = Vector3(10, 10, 10); //m_flTimeLastJumped=0x35e0
			 }
		 }
		 if (NoJumpRestraint)
		 {

			 *reinterpret_cast<float*>(LocalPlayer + 0x35c4) = 99999.0f; // m_flTimeLastTouchedWall = 0x35c4

			 *reinterpret_cast<float*>(LocalPlayer + 0x35d0) = 0.01f; //m_flTimeLastJumped=0x35e0

			 *reinterpret_cast<float*>(LocalPlayer + 0x35e0) = 0.01f; //m_flTimeLastLanded=0x35e0

			 *reinterpret_cast<bool*>(LocalPlayer + 0x4608) = false; //m_pushAwayFromTopAcceleration=0x3609

			 *reinterpret_cast<bool*>(LocalPlayer + 0x3609) = false; //m_bDoMultiJumpPenalty=0x3609
			 *reinterpret_cast<bool*>(LocalPlayer + 0x3608) = false; //m_bHasJumpedSinceTouchedGround=0x3608
		 }
		 if (SpinBot)
		 {
			 int LocalPlayer_HealthA = (*reinterpret_cast<int*>(Entity + Offsets::m_Health));
			 uintptr_t ViewModelHandle = *reinterpret_cast<uintptr_t*>(LocalPlayer + 0x2d18) & 0xFFFF;
			 if (!ViewModelHandle) continue;
			 uintptr_t ViewModel = *reinterpret_cast<uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + Offsets::Entity + (ViewModelHandle << 5));
			 if (!ViewModel) continue;

			 if (LocalPlayer_HealthA > 1)
				 CanSpin = true;
			 else
				 CanSpin = false;

			 if (CanSpin) // prevents crashing on kill cam
			 {
				 *reinterpret_cast<int*>(LocalPlayer_HealthA) = 0; // Fake Client Dead To Force Networking Angles
				 *reinterpret_cast<Vector3*>(LocalPlayer + 0x0378) = Vector3(rand() % 100, rand() % -250, rand() % 500); // m_angNetworkAngles server / client
				 *reinterpret_cast<Vector3*>(ViewModel + 0x0378) = Vector3(rand() % 100, rand() % -250, rand() % 500); // m_angNetworkAngles View Module
			 }
			 
		 }
	 }
 }
 

 

 




	

