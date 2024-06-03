#define IMGUI_DEFINE_MATH_OPERATORS
#include "cheat.hpp"
#include <thread>
#include "bytes.h"
#include "Custom.hpp"
#include "anime_Kitttten.hpp"
#include "Peter.h"
#include <map>
#include <direct.h>

#include <D3DX11tex.h>
#pragma comment(lib, "D3DX11.lib")

typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
bool ESP = false;
bool AIMBOT = false;
bool MISC = false;
bool WORLD = false;
bool EXPLOITS = false;
bool ITEMS = false;
namespace TextMenu {
	int Position = 0;
	void CreateTitle(int index, const char* text, ImColor Color)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 10 * index), Color, text);
	}
	void CreateCheckBox(int Index, bool& Value, std::string Text, ImColor Color)
	{
		std::string St;
		if (GetAsyncKeyState(VK_UP) & 0x1)
			Position -= 1;
		if (GetAsyncKeyState(VK_DOWN) & 0x1)
			Position += 1;
		
		if (Index == Position)
		{
			if (GetAsyncKeyState(VK_RIGHT) & 0x1)
				Value = !Value;

			if (Value)
				St = "-> " + Text + " [ON]";
			else
				St = "-> " + Text + " [OFF]";
		}
		else {

			if (Value)
				St = Text + " [ON]";
			else
				St = Text + " [OFF]";
		}
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(10, 10 * Index), Color, Text.c_str());
	}
}
ID3D11ShaderResourceView* Kitten_Texture = nullptr;
ImFont* KittenFont;
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImFontConfig font_config;
	font_config.PixelSnapH = false;
	font_config.FontDataOwnedByAtlas = false;
	font_config.OversampleH = 5;
	font_config.OversampleV = 5;
	font_config.RasterizerMultiply = 1.2f;

	ImGui::StyleColorsDark();

	auto& Style = ImGui::GetStyle();

	Style.WindowPadding = ImVec2(11.000f, 9.000f);
	Style.WindowBorderSize = 0.000f;
	Style.FramePadding = ImVec2(4.000f, 6.000f);
	Style.FrameBorderSize = 1.000f;
	Style.IndentSpacing = 20.000f;
	Style.TabBorderSize = 1.000f;

	Style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.000f, 0.000f, 0.000f, 1.000f);
	Style.Colors[ImGuiCol_WindowBg] = ImVec4(0.083f, 0.083f, 0.083f, 0.940f);
	Style.Colors[ImGuiCol_FrameBg] = ImVec4(0.f, 1.0f, 0.36f, 0.37f);
	Style.Colors[ImGuiCol_Button] = ImVec4(0.137f, 0.398f, 0.291f, 0.400f);
	Style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.000f, 1.000f, 0.390f, 1.000f);
	Style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.000f, 0.515f, 1.000f, 1.000f);

	static const ImWchar ranges[] = {

		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
		0x2DE0, 0x2DFF, // Cyrillic Extended-A
		0xA640, 0xA69F, // Cyrillic Extended-B
		0xE000, 0xE226, // icons
		0,
	};

	font_config.GlyphRanges = ranges;

	//io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\verdana.ttf", 17, &font_config, ranges);
	//io.Fonts->AddFontFromMemoryTTF(icons_binary, sizeof icons_binary, 15, &font_config, ranges);
	D3DX11_IMAGE_LOAD_INFO info;
	ID3DX11ThreadPump* pump{ nullptr };
	if(!Homer_Texture)
		D3DX11CreateShaderResourceViewFromMemory(pDevice, HomeData, sizeof(HomeData), &info, pump, &Homer_Texture, 0);

	if (!Peter_Texture)
		D3DX11CreateShaderResourceViewFromMemory(pDevice, PeterData, sizeof(PeterData), &info, pump, &Peter_Texture, 0);

	
	// Our state
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

Vector4 ImagePlacement;

const char* keys[] =
{
	"None",
	"Mouse 1",
	"Mouse 2",
	"CN",
	"Mouse 3",
	"Mouse 4",
	"Mouse 5",
	"-",
	"Back",
	"Tab",
	"-",
	"-",
	"CLR",
	"Enter",
	"-",
	"-",
	"Shift",
	"CTL",
	"Menu",
	"Pause",
	"Caps",
	"KAN",
	"-",
	"JUN",
	"FIN",
	"KAN",
	"-",
	"Escape",
	"CON",
	"NCO",
	"ACC",
	"MAD",
	"Space",
	"PGU",
	"PGD",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"SEL",
	"PRI",
	"EXE",
	"PRI",
	"INS",
	"Delete",
	"HEL",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"WIN",
	"WIN",
	"APP",
	"-",
	"SLE",
	"Num 0",
	"Num 1",
	"Num 2",
	"Num 3",
	"Num 4",
	"Num 5",
	"Num 6",
	"Num 7",
	"Num 8",
	"Num 9",
	"MUL",
	"ADD",
	"SEP",
	"MIN",
	"Delete",
	"DIV",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
	"F13",
	"F14",
	"F15",
	"F16",
	"F17",
	"F18",
	"F19",
	"F20",
	"F21",
	"F22",
	"F23",
	"F24",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"NUM",
	"SCR",
	"EQU",
	"MAS",
	"TOY",
	"OYA",
	"OYA",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"Shift",
	"Shift",
	"Ctrl",
	"Ctrl",
	"Alt",
	"Alt"
};

namespace colors
{
	 ImVec4 accent_one = ImColor(156, 113, 210);
	 ImVec4 accent_two = ImColor(63, 94, 206);

	 ImVec4 window_background = ImColor(12, 12, 12);
	 ImVec4 window_shadow = ImColor(0, 0, 0);
	 ImVec4 window_label = ImColor(255, 255, 255);
	 ImVec4 window_username = ImColor(90, 90, 90);

	 ImVec4 tab_label = ImColor(255, 255, 255);
	 ImVec4 tab_checkmark = ImColor(24, 24, 24);

	 ImVec4 child_background = ImColor(20, 20, 20);
	 ImVec4 child_outline = ImColor(26, 26, 26);
	 ImVec4 child_label = ImColor(255, 255, 255);

	 ImVec4 scrollbar_rect = ImColor(26, 26, 26);

	 ImVec4 checkbox_label = ImColor(255, 255, 255);
	 ImVec4 checkbox_background = ImColor(26, 26, 26);
	 ImVec4 checkbox_outline = ImColor(36, 36, 36);
	 ImVec4 checkbox_checkmark = ImColor(255, 255, 255);

	 ImVec4 slider_label = ImColor(255, 255, 255);
	 ImVec4 slider_background = ImColor(26, 26, 26);
	 ImVec4 slider_outline = ImColor(36, 36, 36);
	 ImVec4 slider_grab = ImColor(255, 255, 255);
	 ImVec4 slider_value = ImColor(90, 90, 90);

	 ImVec4 combo_label = ImColor(255, 255, 255);
	 ImVec4 combo_background = ImColor(26, 26, 26);
	 ImVec4 combo_outline = ImColor(36, 36, 36);
	 ImVec4 combo_expand = ImColor(255, 255, 255);
	 ImVec4 combo_preview = ImColor(90, 90, 90);
	 ImVec4 combo_window = ImColor(12, 12, 12);

	 ImVec4 selectable_label = ImColor(255, 255, 255);

	 ImVec4 input_label = ImColor(255, 255, 255);
	 ImVec4 input_background = ImColor(26, 26, 26);
	 ImVec4 input_outline = ImColor(36, 36, 36);
	 ImVec4 input_preview = ImColor(90, 90, 90);

	 ImVec4 button_background = ImColor(26, 26, 26);
	 ImVec4 button_outline = ImColor(36, 36, 36);
	 ImVec4 button_label_active = ImColor(255, 255, 255);
	 ImVec4 button_label_inactive = ImColor(90, 90, 90);

	 ImVec4 listbox_background = ImColor(12, 12, 12);
	 ImVec4 listbox_outline = ImColor(36, 36, 36);

	 ImVec4 color_label = ImColor(255, 255, 255);
	 ImVec4 color_background = ImColor(12, 12, 12);
	 ImVec4 color_outline = ImColor(36, 36, 36);

	 ImVec4 key_label = ImColor(255, 255, 255);
	 ImVec4 key_active = ImColor(90, 90, 90);
	 ImVec4 key_background = ImColor(26, 26, 26);
	 ImVec4 key_outline = ImColor(36, 36, 36);
	 ImVec4 key_window = ImColor(12, 12, 12);
}

struct key_state
{
	bool active = false;
	bool hovered = false;
	float alpha = 0.f;
	float size = 0.f;
	ImVec4 outline_col_one = colors::key_outline;
	ImVec4 outline_col_two = colors::key_outline;
	ImVec4 key_color = colors::key_active;
};
bool Keybind(const char* label, int* key, int* mode)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);

	const float width = ImGui::GetWindowWidth() - (g.Style.WindowPadding.x * 2);
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect rect(pos, pos + ImVec2(width, 10));

	ImGui::ItemSize(rect, style.FramePadding.y);
	if (!ImGui::ItemAdd(rect, id))
		return false;

	static std::map<ImGuiID, key_state> anim;
	auto it_anim = anim.find(id);

	if (it_anim == anim.end())
	{
		anim.insert({ id, key_state() });
		it_anim = anim.find(id);
	}

	char buf_display[64] = "None";

	bool value_changed = false;
	int k = *key;

	std::string active_key = "";
	active_key += keys[*key];

	if (*key != 0 && g.ActiveId != id) {
		strcpy_s(buf_display, active_key.c_str());
	}
	else if (g.ActiveId == id) {
		strcpy_s(buf_display, "...");
	}

	const float size = ImGui::CalcTextSize(buf_display).x;

	it_anim->second.size = ImLerp(it_anim->second.size, size, g.IO.DeltaTime * 16.f);
	it_anim->second.outline_col_one = ImLerp(it_anim->second.outline_col_one, g.ActiveId == id ? colors::accent_one : colors::input_outline, g.IO.DeltaTime * 8.f);
	it_anim->second.outline_col_two = ImLerp(it_anim->second.outline_col_two, g.ActiveId == id ? colors::accent_two : colors::input_outline, g.IO.DeltaTime * 8.f);
	it_anim->second.key_color = ImLerp(it_anim->second.key_color, g.ActiveId == id ? colors::key_label : colors::key_active, g.IO.DeltaTime * 8.f);

	const ImRect clickable(pos + ImVec2(width - 10 - it_anim->second.size, -5), pos + ImVec2(width, 15));

	bool hovered = ImGui::ItemHoverable(clickable, id);

	if (hovered && io.MouseClicked[0])
	{
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*key = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					k = 0x01;
					break;
				case 1:
					k = 0x02;
					break;
				case 2:
					k = 0x04;
					break;
				case 3:
					k = 0x05;
					break;
				case 4:
					k = 0x06;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = 0x08; i <= 0xA5; i++) {
				if (io.KeysDown[i]) {
					k = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (ImGui::IsKeyPressedMap(ImGuiKey_Escape)) {
			*key = 0;
			ImGui::ClearActiveID();
		}
		else {
			*key = k;
		}
	}

	if (hovered && g.IO.MouseClicked[1] || it_anim->second.active && (g.IO.MouseClicked[0] || g.IO.MouseClicked[1]) && !it_anim->second.hovered)
		it_anim->second.active = !it_anim->second.active;

	it_anim->second.alpha = ImClamp(it_anim->second.alpha + (8.f * g.IO.DeltaTime * (it_anim->second.active ? 1.f : -1.f)), 0.f, 1.f);

	window->DrawList->AddText( rect.Min - ImVec2(0, 4), ImGui::GetColorU32(colors::key_label), label);
	window->DrawList->AddRectFilled(clickable.Min, clickable.Max, ImGui::GetColorU32(colors::key_background), 3.f);
	const int vtx1 = window->DrawList->VtxBuffer.Size;
	window->DrawList->AddRect(clickable.Min, clickable.Max, ImGui::GetColorU32(ImVec4(1.f, 1.f, 1.f, 1.f)), 3.f);
	const int vtx2 = window->DrawList->VtxBuffer.Size;
	ImGui::ShadeVertsLinearColorGradientKeepAlpha(window->DrawList, vtx1, vtx2, clickable.Min, ImVec2(clickable.Max.x, clickable.Min.y), ImGui::GetColorU32(it_anim->second.outline_col_one), ImGui::GetColorU32(it_anim->second.outline_col_two));

	ImGui::PushStyleColor(ImGuiCol_Text, it_anim->second.key_color);
	ImGui::RenderTextClipped(clickable.Min - ImVec2(0, 2), clickable.Max - ImVec2(0, 2), buf_display, NULL, NULL, ImVec2(0.5f, 0.5f));
	ImGui::PopStyleColor();

	ImGui::SetNextWindowPos(ImVec2(clickable.GetCenter().x - 50, clickable.Max.y + 5));
	ImGui::SetNextWindowSize(ImVec2(101, 84));
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, it_anim->second.alpha);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(3, 8));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 3.f);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, colors::key_window);
	ImGui::PushStyleColor(ImGuiCol_Border, colors::key_outline);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1.f);
	if (it_anim->second.alpha >= 0.01f)
	{
		ImGui::Begin(label, NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove);
		{
			it_anim->second.hovered = ImGui::IsWindowHovered();

			if (ImGui::Selectable("Hold", *mode == 0))
			{
				*mode = 0;
				it_anim->second.active = false;
			}
			if (ImGui::Selectable("Toggle", *mode == 1))
			{
				*mode = 1;
				it_anim->second.active = false;
			}
			if (ImGui::Selectable("Always", *mode == 2))
			{
				*mode = 2;
				it_anim->second.active = false;
			}
		}
		ImGui::End();
	}
	ImGui::PopStyleColor(2);
	ImGui::PopStyleVar(4);

	return value_changed;
}
int m_shot = 0;
std::vector<Vector2> Shot_Pos;

void Batched_BulletTrace() // shitty method universal for all games
{
	if (GetAsyncKeyState(VK_LBUTTON))
		m_shot += 1;

}
bool Checkbox(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const ImRect check_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(label_size.y + style.FramePadding.y * 2, label_size.y + style.FramePadding.y * 2));
	ImGui::ItemSize(check_bb, style.FramePadding.y);

	ImRect total_bb = check_bb;
	if (label_size.x > 0)
		ImGui::SameLine(0, style.ItemInnerSpacing.x);
	const ImRect text_bb(window->DC.CursorPos + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, style.FramePadding.y) + label_size);
	if (label_size.x > 0)
	{
		ImGui::ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
		total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
	}

	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
		*v = !(*v);

	ImGui::RenderFrame(check_bb.Min, check_bb.Max, ImGui::GetColorU32((held && hovered) ? ImGuiCol_FrameBgActive : hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), true, style.FrameRounding);
	if (*v)
	{
		const float check_sz = ImMin(check_bb.GetWidth(), check_bb.GetHeight());
		const float pad = ImMax(1.0f, (float)(int)(check_sz / 6.0f));
		window->DrawList->AddRectFilled(check_bb.Min + ImVec2(pad, pad), check_bb.Max - ImVec2(pad, pad), ImGui::GetColorU32(ImGuiCol_CheckMark), style.FrameRounding);
	}
	ImVec2 Pos = text_bb.GetTL();
	if (g.LogEnabled)
		ImGui::LogRenderedText(&Pos, *v ? "[X]" : "[]");
	if (label_size.x > 0.0f)
		ImGui::RenderText(text_bb.GetTL(), label);

	return pressed;
}
bool Reset = false;
bool DEBUG = false;
bool V1 = false;
bool INit = false;
int Slec = 0;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	/*if (GetAsyncKeyState(VK_INSERT) & 0x1)
		Draw_Menu = !Draw_Menu;*/

	if (GetAsyncKeyState(VK_INSERT) & 0x1)
		NewMenu = !NewMenu;

	if (NewMenu)
	{

			ImGui::SetNextWindowSize(ImVec2(600.000f, 400.000f), ImGuiCond_Once);
			ImGui::Begin("rename me 0", NULL, 27);

			ImVec2 P1, P2;
			ImDrawList* pDrawList;
			const auto& CurrentWindowPos = ImGui::GetWindowPos();
			const auto& pWindowDrawList = ImGui::GetWindowDrawList();
			const auto& pBackgroundDrawList = ImGui::GetBackgroundDrawList();
			const auto& pForegroundDrawList = ImGui::GetForegroundDrawList();

			P1 = ImVec2(5.000f, 5.000f);
			P1.x += CurrentWindowPos.x;
			P1.y += CurrentWindowPos.y;
			P2 = ImVec2(695.000f, 395.000f);
			P2.x += CurrentWindowPos.x;
			P2.y += CurrentWindowPos.y;
			pDrawList = pWindowDrawList;
			pDrawList->AddRectFilledMultiColor(P1, P2,
				ImColor(0.144f, 1.000f, 0.000f, 1.000f),
				ImColor(0.000f, 0.586f, 1.000f, 1.000f),
				ImColor(0.000f, 0.884f, 1.000f, 1.000f),
				ImColor(0.000f, 1.000f, 0.387f, 1.000f));

			P1 = ImVec2(6.000f, 6.000f);
			P1.x += CurrentWindowPos.x;
			P1.y += CurrentWindowPos.y;
			P2 = ImVec2(595.000f, 394.000f);
			P2.x += CurrentWindowPos.x;
			P2.y += CurrentWindowPos.y;
			pDrawList = pWindowDrawList;
			pDrawList->AddRectFilled(P1, P2, ImColor(0.059f, 0.059f, 0.059f, 0.788f), 0.000f);

			P1 = ImVec2(10.000f, 85.000f);
			P1.x += CurrentWindowPos.x;
			P1.y += CurrentWindowPos.y;
			P2 = ImVec2(590.000f, 80.000f);
			P2.x += CurrentWindowPos.x;
			P2.y += CurrentWindowPos.y;
			pDrawList = pWindowDrawList;
			pDrawList->AddRectFilledMultiColor(P1, P2,
				ImColor(0.000f, 1.000f, 0.322f, 0.216f),
				ImColor(0.000f, 0.918f, 1.000f, 0.129f),
				ImColor(0.000f, 0.753f, 1.000f, 0.282f),
				ImColor(0.000f, 1.000f, 0.090f, 0.424f));

			P1 = ImVec2(10.000f, 100.000f);
			P1.x += CurrentWindowPos.x;
			P1.y += CurrentWindowPos.y;
			P2 = ImVec2(590.000f, 390.000f);
			P2.x += CurrentWindowPos.x;
			P2.y += CurrentWindowPos.y;
			pDrawList = pWindowDrawList;
			pDrawList->AddRectFilled(P1, P2, ImColor(0.059f, 0.059f, 0.059f, 0.478f), 0.000f);

			if (ImGui::Button("ESP", ImVec2(138, 70.000f)))
				Slec = 0;

			ImGui::SameLine();
			if(ImGui::Button("Aimbot", ImVec2(138, 70.000f)))
				Slec = 1;
			ImGui::SameLine();
			if (ImGui::Button("Misc", ImVec2(138, 70.000f)))
				Slec = 2;

			ImGui::SameLine();
			if (ImGui::Button("Settings", ImVec2(138, 70.000f)))
				Slec = 3;

			if (Slec == 0)
			{
				
				ImGui::SetCursorPos(ImVec2(20, 125));
				Checkbox("Initialize Cheat", &Reset);
				ImGui::SetCursorPos(ImVec2(20, 150));
				Checkbox("Box", &Box);
				ImGui::SetCursorPos(ImVec2(20, 175));
				Checkbox("Corner Box", &CornerBox);
				ImGui::SetCursorPos(ImVec2(20, 200));
				Checkbox("Lines", &ThreeBox); 
				ImGui::SetCursorPos(ImVec2(20, 225));
				Checkbox("Skeleton", &Skeleon);
				ImGui::SetCursorPos(ImVec2(20, 250));
				Checkbox("LGBTQ Skeleton", &RainbowSkeleton);
				ImGui::SetCursorPos(ImVec2(20, 275));
				Checkbox("Name", &Name);
				ImGui::SetCursorPos(ImVec2(20, 300));
				Checkbox("Homer ESP", &HomerESP);
				ImGui::SetCursorPos(ImVec2(20, 325));
				Checkbox("Peter Greiffen ESP", &Peter_GreiffenEsp);
				ImGui::SetCursorPos(ImVec2(20, 350));
				Checkbox("Distance", &PDistance);
				ImGui::SetCursorPos(ImVec2(250, 125));
				Checkbox("Health Bar", &HealthBar);
				ImGui::SetCursorPos(ImVec2(250, 150));
				Checkbox("Shield Bar", &ShieldBar);
				ImGui::SetCursorPos(ImVec2(250, 175));
				Checkbox("Seer Bar", &SeerHealthBar);
				ImGui::SetCursorPos(ImVec2(250, 200));
				Checkbox("Level", &Level);
				ImGui::SetCursorPos(ImVec2(250, 225));
				Checkbox("Operator", &Operator);
				ImGui::SetCursorPos(ImVec2(250, 250));
				Checkbox("Glow", &Glow);

				//COLORS
				ImGui::SetCursorPos(ImVec2(590, 200));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Box Color", BoxColor);
				ImGui::SetCursorPos(ImVec2(590, 225));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Line Color", LineColor);
				ImGui::SetCursorPos(ImVec2(590, 250));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Skeleton Color", SkeletonColor);
				ImGui::SetCursorPos(ImVec2(590, 275));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Name Color", NameColor);
				ImGui::SetCursorPos(ImVec2(590, 300));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Distance Color", DistanceColor);
				ImGui::SetCursorPos(ImVec2(590, 325));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Operator Color", OperatorColor);
				ImGui::SetCursorPos(ImVec2(590, 350));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Level Color", LevelColor);
				ImGui::SetCursorPos(ImVec2(590, 375));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Glow Color", GlowColor);

				//COLOR NAMES
				ImGui::SetCursorPos(ImVec2(450, 200));
				ImGui::Text("Box Color");
				ImGui::SetCursorPos(ImVec2(450, 225));
				ImGui::Text("Line Color");
				ImGui::SetCursorPos(ImVec2(450, 250));
				ImGui::Text("Skeleton Color");
				ImGui::SetCursorPos(ImVec2(450, 275));
				ImGui::Text("Name Color");
				ImGui::SetCursorPos(ImVec2(450, 300));
				ImGui::Text("Distance Color");
				ImGui::SetCursorPos(ImVec2(450, 325));
				ImGui::Text("Operator Color");
				ImGui::SetCursorPos(ImVec2(450, 350));
				ImGui::Text("Level Color");
				ImGui::SetCursorPos(ImVec2(450, 375));
				ImGui::Text("Glow Color");
				

			}
			else if (Slec == 1)
			{				
				ImGui::SetCursorPos(ImVec2(25, 100));
				Checkbox("Aimbot", &VectorAim);
				ImGui::SetCursorPos(ImVec2(25, 125));
				Checkbox("PSilent", &Psilent);
				ImGui::SetCursorPos(ImVec2(25, 150));
				Checkbox("Target Line", &TargetLine);
				ImGui::SetCursorPos(ImVec2(25, 175));
				Checkbox("Fov Circle", &FovCircle);
				ImGui::SetCursorPos(ImVec2(25, 200));
				Checkbox("Recoil Control", &Rcs);

			
				ImGui::SetCursorPos(ImVec2(10, 235));
				Keybind("PSilent Key", &PsilentKey, 0);
				ImGui::SetCursorPos(ImVec2(10, 250));
				Keybind("Aimbot Key", &AimbotKey, 0);

				ImGui::SetCursorPos(ImVec2(595, 125));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Fov Color", FovColor);
				ImGui::SetCursorPos(ImVec2(595, 150));
				ImGui::SetNextItemWidth(10.0f);
				ImGui::ColorEdit3("Target Line Color", TargetLineColor);
				ImGui::SetCursorPos(ImVec2(450, 125));
				ImGui::Text("Fov Color");
				ImGui::SetCursorPos(ImVec2(450, 150));
				ImGui::Text("Target Line Color");

				ImGui::SetCursorPos(ImVec2(10, 275));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderFloat("Fov Circle Size", &FovSize, 0.0f, 1000.0f);
				ImGui::SetCursorPos(ImVec2(10, 300));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderInt("Smoothing", &smothing, 0, 10);
				ImGui::SetCursorPos(ImVec2(10, 325));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderFloat("Recoil X (1 = Remove, 0 = Recoil)", &pitchSTR, 0.f, 1.f);
				ImGui::SetCursorPos(ImVec2(10, 350));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderFloat("Recoil Y (1 = Remove, 0 = Recoil)", &yawSTR, 0.f, 1.f);
			}
			else if (Slec == 2)
			{
				ImGui::SetCursorPos(ImVec2(20, 125));
				Checkbox("Free Cam", &FreeCam);
				ImGui::SetCursorPos(ImVec2(20, 150));
				Checkbox("Big Map Radar", &BigMapRadar);
				ImGui::SetCursorPos(ImVec2(20, 175));
				Checkbox("Heirloom Changer (Octain)", &HeirloomChanger);
				ImGui::SetCursorPos(ImVec2(20, 200));
				Checkbox("Auto Glide", &Auto_Grapple);
				ImGui::SetCursorPos(ImVec2(20, 225));
				Checkbox("Super Grapple", &Super_Glide);
				ImGui::SetCursorPos(ImVec2(20, 250));
				Checkbox("Fake Fire", &SimulateCMD);
				ImGui::SetCursorPos(ImVec2(20, 275));
				Checkbox("Show FPS", &Show_Fps);
				ImGui::SetCursorPos(ImVec2(20, 300));
				Checkbox("Disable Shadowing", &DisableShadow);
				ImGui::SetCursorPos(ImVec2(20, 325));
				Checkbox("Fov Changer", &FovChanger);
				ImGui::SetCursorPos(ImVec2(20, 350));
				Checkbox("LocalPlayer Teleportation", &Teleportation);
				ImGui::SetCursorPos(ImVec2(250, 125));
				Checkbox("No Jump/Climb Restraints", &NoJumpRestraint);
				ImGui::SetCursorPos(ImVec2(250, 150));
				Checkbox("Quick Melee", &Quick_Melee);
				ImGui::SetCursorPos(ImVec2(250, 175));
				Checkbox("Spin Bot (Server_Side)", &SpinBot);
			}
			else if (Slec == 3)
			{

				
				ImGui::SetCursorPos(ImVec2(10, 110));
				Keybind("Fake Fire Key", &SimulateCMDKey, 0);
				ImGui::SetCursorPos(ImVec2(10, 130));
				Keybind("Free Cam Key", &FreeCamKey, 0);
				ImGui::SetCursorPos(ImVec2(10, 150));
				Keybind("Auto Glide Key", &Auto_GrappleKey, 0);
				ImGui::SetCursorPos(ImVec2(10, 170));
				Keybind("Super Grapple Key", &Super_GlideKey, 0);
				ImGui::SetCursorPos(ImVec2(10, 190));
				Keybind("Teleport Up Key", &UpTpKey, 0);
				ImGui::SetCursorPos(ImVec2(10, 210));
				Keybind("Teleport Down Key", &DownTpKey, 0);

				ImGui::SetCursorPos(ImVec2(10, 230));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderFloat("Max Render Distance", &MaxDistance, 0.0f, 265);
				ImGui::SetCursorPos(ImVec2(10, 255));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderInt("Hightlight ID", &HightlightID, -100, 100);
				ImGui::SetCursorPos(ImVec2(10, 280));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderFloat("Fov", &PlayerFov, 75.0f, 180.f);
				ImGui::SetCursorPos(ImVec2(10, 305));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderFloat("Teleportation X", &TpStrength.x, -100.f, 100.f);
				ImGui::SetCursorPos(ImVec2(10, 330));
				ImGui::SetNextItemWidth(1.0f);
				ImGui::SliderFloat("Teleportation Y", &TpStrength.y, -100.f, 100.f);

			}
			
			ImGui::End();
		

	}
	//if (Draw_Menu)
	//{
	//	c_custom custom;

	//	static bool bools[50]{};
	//	static int ints[50]{};
	//	std::vector < const char* > items = { "Head", "Chest", "Body", "Legs", "Feet" };

	//	static float color[4] = { 1.f, 1.f, 1.f, 1.f };

	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	//	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(510, 380));

	//	ImGui::Begin("Hello, world!", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse); {

	//		auto window = ImGui::GetCurrentWindow();
	//		auto draw = window->DrawList;
	//		auto pos = window->Pos;
	//		auto size = window->Size;
	//		auto style = ImGui::GetStyle();
	//		
	//		ImGui::TextColored(ImColor(255, 0, 0, 255), "Apex Version : v3.0.65.42");
	//			Checkbox("Initialize Cheat", &Reset);
	//			Checkbox("DEBUG Cheat (%CPU%)", &DEBUG);
	//			Checkbox("Box", &Box);
	//			Checkbox("Corner Box", &CornerBox);
	//			Checkbox("Lines", &ThreeBox); 
	//			Checkbox("Skeleton", &Skeleon);
	//			Checkbox("LGBTQ Skeleton", &RainbowSkeleton);
	//			Checkbox("Name", &Name);
	//			Checkbox("Homer ESP", &HomerESP);
	//			Checkbox("Distance", &PDistance);
	//			Checkbox("Health Bar", &HealthBar);
	//			Checkbox("Shield Bar", &ShieldBar);
	//			Checkbox("Seer Bar", &SeerHealthBar);
	//			Checkbox("Level", &Level);
	//			Checkbox("Operator", &Operator);
	//			Checkbox("Glow", &Glow);
	//			ImGui::SliderInt("Hightlight ID", &HightlightID, 1, 100);

	//			
	//			Checkbox("Team Check", &TeamCheck);
	//			Checkbox("Squad Check", &SquadCheck);
	//			ImGui::ColorEdit3("Box Color", BoxColor);
	//			ImGui::ColorEdit3("Line Color", LineColor);
	//			ImGui::ColorEdit3("Skeleton Color", SkeletonColor);
	//			ImGui::ColorEdit3("Name Color", NameColor);
	//			ImGui::ColorEdit3("Distance Color", DistanceColor);
	//			ImGui::ColorEdit3("Operator Color", OperatorColor);
	//			ImGui::ColorEdit3("Level Color", LevelColor);
	//			ImGui::ColorEdit3("Glow Color", GlowColor);
	//			ImGui::SliderFloat("Max Render Distance", &MaxDistance, 0.0f, 1000.0f);
	//			Checkbox("Aimbot", &VectorAim);
	//			Keybind("Aimbot Key", &AimbotKey, 0);
	//			Checkbox("PSilent", &Psilent);
	//			Keybind("PSilent Key", &PsilentKey, 0);
	//			ImGui::SliderInt("Hit Chance ( 0 = 100% || 10 = 0% )", &HitPrecent, 0, 10);
	//			Checkbox("Target Line", &TargetLine);
	//			Checkbox("Fov Circle", &FovCircle);
	//			ImGui::SliderFloat("Fov Circle Size", &FovSize, 0.0f, 1000.0f);
	//			ImGui::ColorEdit3("Fov Color", FovColor);
	//			ImGui::ColorEdit3("Target Line Color", TargetLineColor);
	//			ImGui::SliderInt("Smoothing", &smothing, 0, 10);
	//			Checkbox("Recoil Control", &Rcs);
	//			ImGui::SliderFloat("Recoil X (1 = Remove, 0 = Recoil)", &pitchSTR, 0.f, 1.f);
	//			ImGui::SliderFloat("Recoil Y (1 = Remove, 0 = Recoil)", &yawSTR, 0.f, 1.f);
	//			Checkbox("Free Cam", &FreeCam);
	//			Checkbox("Big Map Radar", &BigMapRadar);
	//			Checkbox("Heirloom Changer (Octain)", &HeirloomChanger);
	//			Checkbox("Auto Glide", &Auto_Grapple);
	//			Checkbox("Super Grapple", &Super_Glide);
	//			Checkbox("Fake Fire", &SimulateCMD);
	//			Checkbox("Show FPS", &Show_Fps);
	//			Checkbox("Disable Shadowing", &DisableShadow);
	//			Checkbox("Fov Changer", &FovChanger);
	//			ImGui::SliderFloat("Fov", &PlayerFov, 75.0f, 180.f);
	//			Checkbox("LocalPlayer Teleportation", &Teleportation);
	//			ImGui::SliderFloat("Teleportation X", &TpStrength.x, -100.f, 100.f);
	//			ImGui::SliderFloat("Teleportation Y", &TpStrength.y, -100.f, 100.f);
	//			Checkbox("No Jump/Climb Restraints", &NoJumpRestraint);
	//			Checkbox("Quick Melee", &Quick_Melee);
	//			Checkbox("Spin Bot (Server_Side)", &SpinBot);
	//			Keybind("Fake Fire Key", &SimulateCMDKey, 0);
	//			ImGui::Spacing();
	//			Keybind("Free Cam Key", &FreeCamKey, 0);
	//			ImGui::Spacing();
	//			Keybind("Auto Glide Key", &Auto_GrappleKey, 0);
	//			ImGui::Spacing();
	//			Keybind("Super Grapple Key", &Super_GlideKey, 0);
	//			ImGui::Spacing();
	//			Keybind("Teleport Up Key", &UpTpKey, 0);
	//			ImGui::Spacing();
	//			Keybind("Teleport Down Key", &DownTpKey, 0);
	//			ImGui::SliderFloat("Image X", &NIglet, -500.0f, 500.0f);

	//	} ImGui::End();
	//	
	//	ImGui::PopStyleVar(2);
	//}
	//retard nigga Shit
	
	if (FovCircle)
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(GetSystemMetrics(0) / 2, GetSystemMetrics(1) / 2), FovSize, ImColor(FovColor[0], FovColor[1], FovColor[2], 255.f));
	
	if (Reset )
	{
		InitPlayer();
	}
	draw_text_outline_font(120, 10, ImColor(255, 155, 0, 255), "{DEV BUILD}");
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(40, 20), ImColor(255, 0, 255, 255), "SCORE");
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(40, 35), ImColor(255, 0, 0, 255), "Pasted Cheat : 1");
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(40, 50), ImColor(255, 0, 0, 255), "Eac : 0");

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}
