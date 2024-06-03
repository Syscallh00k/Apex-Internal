#include "imgui/imgui.h"
#include <string>
#include <Windows.h>

#define M_PI	3.14159265358979323846264338327950288419716939937510


void AddLine(ImVec2 pos, ImVec2 size, ImU32 color, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddLine(pos, size, color, thickness);
}
void DrawCorneredBox(int X, int Y, int W, int H, const ImU32& color, int thickness)
{
	float lineW = (W / 3);
	float lineH = (H / 3);

	////black outlines
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);

	//corners
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}



void DrawBox(float X, float Y, float W, float H, const ImU32 color)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(X + 1, Y + 1), ImVec2(((X + W) - 1), ((Y + H) - 1)), ImGui::GetColorU32(color));
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(X, Y), ImVec2(X + W, Y + H), ImGui::GetColorU32(color));
}
void DrawBox(ImVec2 headPos, ImVec2 pos, const ImU32 color, int thickness) {
	int dist = pos.y - headPos.y;
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(headPos.x - dist / 4, headPos.y), ImVec2(headPos.x + dist / 4, headPos.y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(headPos.x + dist / 4, headPos.y), ImVec2(pos.x + dist / 4, pos.y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x + dist / 4, pos.y), ImVec2(pos.x - dist / 4, pos.y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(pos.x - dist / 4, pos.y), ImVec2(headPos.x - dist / 4, headPos.y), color, thickness);
}
inline void AddHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	ImGui::GetBackgroundDrawList()->PathLineTo(p1);
	ImGui::GetBackgroundDrawList()->PathLineTo(p2);
	ImGui::GetBackgroundDrawList()->PathLineTo(p3);
	ImGui::GetBackgroundDrawList()->PathLineTo(p4);
	ImGui::GetBackgroundDrawList()->PathLineTo(p5);
	ImGui::GetBackgroundDrawList()->PathLineTo(p6);

	ImGui::GetBackgroundDrawList()->PathStroke(col, true, thickness);
}
inline void AddHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
{
	if ((col & IM_COL32_A_MASK) == 0)
		return;

	ImGui::GetBackgroundDrawList()->PathLineTo(p1);
	ImGui::GetBackgroundDrawList()->PathLineTo(p2);
	ImGui::GetBackgroundDrawList()->PathLineTo(p3);
	ImGui::GetBackgroundDrawList()->PathLineTo(p4);
	ImGui::GetBackgroundDrawList()->PathLineTo(p5);
	ImGui::GetBackgroundDrawList()->PathLineTo(p6);
	ImGui::GetBackgroundDrawList()->PathFillConvex(col);
}
inline void DrawQuadFilled(ImVec2 p1, ImVec2 p2, ImVec2 p3, ImVec2 p4, ImColor color) {
	ImGui::GetBackgroundDrawList()->AddQuadFilled(p1, p2, p3, p4, color);
}
inline void DrawHexagon(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col, float thickness)
{
	AddHexagon(p1, p2, p3, p4, p5, p6, col, thickness);
}
inline void DrawHexagonFilled(const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& p5, const ImVec2& p6, ImU32 col)
{
	AddHexagonFilled(p1, p2, p3, p4, p5, p6, col);
}
inline void SeerHealth(float x, float y, int shield, int max_shield, int armorType, int health) {

	int bg_offset = 3;
	int bar_width = 158;
	// 4steps...2*3=6
	// 38*4=152 152+6 = 158
	// 5steps...2*4=8
	// 30*5=150 150+8 = 158
	float max_health = 100.0f;
	float shield_step = 25.0f;

	int shield_25 = 30;
	int steps = 5;

	ImVec2 bg1(x - bar_width / 2 - bg_offset, y);
	ImVec2 bg2(bg1.x - 10, bg1.y - 16);
	ImVec2 bg3(bg2.x + 5, bg2.y - 7);
	ImVec2 bg4(bg3.x + bar_width + bg_offset, bg3.y);
	ImVec2 bg5(bg4.x + 11, bg4.y + 18);
	ImVec2 bg6(x + bar_width / 2 + bg_offset, y);
	DrawHexagonFilled(bg1, bg2, bg3, bg4, bg5, bg6, ImColor(0, 0, 0, 140));

	ImVec2 h1(bg1.x + 3, bg1.y - 4);
	ImVec2 h2(h1.x - 5, h1.y - 8);
	ImVec2 h3(h2.x + (float)health / max_health * bar_width, h2.y);
	ImVec2 h4(h1.x + (float)health / max_health * bar_width, h1.y);
	ImVec2 h3m(h2.x + bar_width, h2.y);
	ImVec2 h4m(h1.x + bar_width, h1.y);
	DrawQuadFilled(h1, h2, h3m, h4m, ImColor(10, 10, 30, 60));
	DrawQuadFilled(h1, h2, h3, h4, ImColor(255, 255, 255, 255));


	ImColor shieldCracked(97, 97, 97);
	ImColor shieldCrackedDark(67, 67, 67);

	ImColor shieldCol;
	ImColor shieldColDark; //not used, but the real seer q has shadow inside
	if (armorType == 1) { //white
		shieldCol = ImColor(247, 247, 247);
		shieldColDark = ImColor(164, 164, 164);
	}
	else if (armorType == 2) { //blue
		shieldCol = ImColor(39, 178, 255);
		shieldColDark = ImColor(27, 120, 210);
	}
	else if (armorType == 3) { //purple
		shieldCol = ImColor(206, 59, 255);
		shieldColDark = ImColor(136, 36, 220);
	}
	else if (armorType == 4) { //gold
		shieldCol = ImColor(255, 255, 79);
		shieldColDark = ImColor(218, 175, 49);
	}
	else if (armorType == 5) { //red
		shieldCol = ImColor(219, 2, 2);
		shieldColDark = ImColor(219, 2, 2);
	}
	else {
		shieldCol = ImColor(247, 247, 247);
		shieldColDark = ImColor(164, 164, 164);
	}
	int shield_tmp = shield;
	int shield1 = 0;
	int shield2 = 0;
	int shield3 = 0;
	int shield4 = 0;
	int shield5 = 0;
	if (shield_tmp > 25) {
		shield1 = 25;
		shield_tmp -= 25;
		if (shield_tmp > 25) {
			shield2 = 25;
			shield_tmp -= 25;
			if (shield_tmp > 25) {
				shield3 = 25;
				shield_tmp -= 25;
				if (shield_tmp > 25) {
					shield4 = 25;
					shield_tmp -= 25;
					shield5 = shield_tmp;
				}
				else {
					shield4 = shield_tmp;
				}
			}
			else {
				shield3 = shield_tmp;
			}
		}
		else {
			shield2 = shield_tmp;
		}
	}
	else {
		shield1 = shield_tmp;
	}
	ImVec2 s1(h2.x - 1, h2.y - 2);
	ImVec2 s2(s1.x - 3, s1.y - 5);
	ImVec2 s3(s2.x + shield1 / shield_step * shield_25, s2.y);
	ImVec2 s4(s1.x + shield1 / shield_step * shield_25, s1.y);
	ImVec2 s3m(s2.x + shield_25, s2.y);
	ImVec2 s4m(s1.x + shield_25, s1.y);

	ImVec2 ss1(s4m.x + 2, s1.y);
	ImVec2 ss2(s3m.x + 2, s2.y);
	ImVec2 ss3(ss2.x + shield2 / shield_step * shield_25, s2.y);
	ImVec2 ss4(ss1.x + shield2 / shield_step * shield_25, s1.y);
	ImVec2 ss3m(ss2.x + shield_25, s2.y);
	ImVec2 ss4m(ss1.x + shield_25, s1.y);

	ImVec2 sss1(ss4m.x + 2, s1.y);
	ImVec2 sss2(ss3m.x + 2, s2.y);
	ImVec2 sss3(sss2.x + shield3 / shield_step * shield_25, s2.y);
	ImVec2 sss4(sss1.x + shield3 / shield_step * shield_25, s1.y);
	ImVec2 sss3m(sss2.x + shield_25, s2.y);
	ImVec2 sss4m(sss1.x + shield_25, s1.y);

	ImVec2 ssss1(sss4m.x + 2, s1.y);
	ImVec2 ssss2(sss3m.x + 2, s2.y);
	ImVec2 ssss3(ssss2.x + shield4 / shield_step * shield_25, s2.y);
	ImVec2 ssss4(ssss1.x + shield4 / shield_step * shield_25, s1.y);
	ImVec2 ssss3m(ssss2.x + shield_25, s2.y);
	ImVec2 ssss4m(ssss1.x + shield_25, s1.y);

	ImVec2 sssss1(ssss4m.x + 2, s1.y);
	ImVec2 sssss2(ssss3m.x + 2, s2.y);
	ImVec2 sssss3(sssss2.x + shield5 / shield_step * shield_25, s2.y);
	ImVec2 sssss4(sssss1.x + shield5 / shield_step * shield_25, s1.y);
	ImVec2 sssss3m(sssss2.x + shield_25, s2.y);
	ImVec2 sssss4m(sssss1.x + shield_25, s1.y);
	if (max_shield == 50) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield != 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
	}
	else if (max_shield == 75) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield < 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
		else if (shield <= 75) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			if (shield < 75) {
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
		}
	}
	else if (max_shield == 100) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield < 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
		else if (shield <= 75) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			if (shield < 75) {
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
		}
		else if (shield <= 100) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			if (shield < 100) {
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
		}
	}
	else if (max_shield == 125) {
		if (shield <= 25) {
			if (shield < 25) {
				DrawQuadFilled(s1, s2, s3m, s4m, shieldCracked);
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(s1, s2, s3, s4, shieldCol);

		}
		else if (shield <= 50) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			if (shield < 50) {
				DrawQuadFilled(ss1, ss2, ss3m, ss4m, shieldCracked);
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
		}
		else if (shield <= 75) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			if (shield < 75) {
				DrawQuadFilled(sss1, sss2, sss3m, sss4m, shieldCracked);
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
		}
		else if (shield <= 100) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			if (shield < 100) {
				DrawQuadFilled(ssss1, ssss2, ssss3m, ssss4m, shieldCracked);
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
		}
		else if (shield <= 125) {
			DrawQuadFilled(s1, s2, s3, s4, shieldCol);
			DrawQuadFilled(ss1, ss2, ss3, ss4, shieldCol);
			DrawQuadFilled(sss1, sss2, sss3, sss4, shieldCol);
			DrawQuadFilled(ssss1, ssss2, ssss3, ssss4, shieldCol);
			if (shield < 125) {
				DrawQuadFilled(sssss1, sssss2, sssss3m, sssss4m, shieldCracked);
			}
			if (shield != 0)
				DrawQuadFilled(sssss1, sssss2, sssss3, sssss4, shieldCol);
		}
	}
}

inline void draw_text_outline_font(float x, float y, ImColor color, const char* string) {
	char buf[512];
	ImVec2 len = ImGui::CalcTextSize(string);

	ImGui::GetForegroundDrawList()->AddText(ImVec2(x - .3 - len.x / 2, y - len.y / 2), ImColor(0.0f, 0.0f, 0.0f, 1.0f), string);
	ImGui::GetForegroundDrawList()->AddText( ImVec2(x + .3 - len.x / 2, y - len.y / 2), ImColor(0.0f, 0.0f, 0.0f, 1.0f), string);
	ImGui::GetForegroundDrawList()->AddText( ImVec2(x - len.x / 2, y - .3 - len.y / 2), ImColor(0.0f, 0.0f, 0.0f, 1.0f), string);
	ImGui::GetForegroundDrawList()->AddText( ImVec2(x - len.x / 2, y + .3 - len.y / 2), ImColor(0.0f, 0.0f, 0.0f, 1.0f), string);

	ImGui::GetForegroundDrawList()->AddText( ImVec2(x - len.x / 2, y - len.y / 2), color, string);
	return;
}
