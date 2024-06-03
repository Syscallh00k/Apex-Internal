
#include "math.hpp"
#include "offsets.h"
#include <vector>

class C_Entity {
public:
	std::vector<C_Entity> TempList;
	class LocalPlayer {
	public:
		LocalPlayer* Get_LocalPlayer() {
			return reinterpret_cast<LocalPlayer*>((uintptr_t)GetModuleHandleA(NULL) + OffsetsT1::LocalPlayer);
		}
		int Get_Current_health()
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return 0;
			return *reinterpret_cast<int*>(Address + OffsetsT1::m_Health);

		}
		Vector3 Get_Position()
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return { 0,0,0 };
			Vector3 Pos = *reinterpret_cast<Vector3*>(Address + OffsetsT1::M_VecAbsOrigin);
			if (Pos.Empty()) return { 0,0,0 };
			return Pos;
		}
		std::string getName()
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return "";

			for (int i = 0; i < 250; i++)
			{
				std::uintptr_t Entity = (*reinterpret_cast<std::uintptr_t*>(((uintptr_t)GetModuleHandleA(NULL) + OffsetsT1::Entity + (i << 5))));

				if (Address == Entity)
				{
					uintptr_t nameptr = *reinterpret_cast<uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + OffsetsT1::NameList + (i - 1) * 0x10);
					if (!nameptr) continue;

					char* name = reinterpret_cast<char*>(nameptr);
					std::string s(name);
					return s;
				}
			}
			return "";
		}
		std::string getModelName()
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return "";
			uintptr_t pMode_Name = *reinterpret_cast<uintptr_t*>(Address + OffsetsT1::m_ModelName);
			char* modelName = reinterpret_cast<char*>(pMode_Name);
			std::string s(modelName);
			return s;
		}
		std::string getSignifierName()
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return "";
			uintptr_t sigAddr = *reinterpret_cast<uintptr_t*>(Address + OffsetsT1::m_iSignifierName);
			if (sigAddr == 0)
				return "";

			char* sig = reinterpret_cast<char*>(sigAddr);
			std::string s = std::string(sig);

			return s;
		}
		int GetPlayerLevel()
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return 0;
			int m_xp = *reinterpret_cast<int*>(Address + OffsetsT1::m_xp); //m_xp
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
		bool IsPlayer()
		{
			std::string name = getSignifierName();
			if (name == "player")
				return true;
			else
				return false;
		}
		bool IsDummy()
		{
			std::string name = getSignifierName();
			if (name == "npc_dummie")
				return true;
			else
				return false;
		}
		bool IsValid()
		{
			uint64_t Address = ((uint64_t)this);
			if (Address)
				return true;
			else
				return false;
		}
		Vector3 getBonePos(int id)
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return { 0,0,0 };
			Vector3 pos = *reinterpret_cast<Vector3*>(Address + OffsetsT1::M_VecAbsOrigin); //PoopSets::M_VecAbsOrigin
			uintptr_t bones = *reinterpret_cast<uintptr_t*>(Address + OffsetsT1::Bones); //PoopSets::demfuckingBone
			Vector3 bone = {};
			UINT32 boneloc = (id * 0x30);
			bone_t bo = {};
			bo = *reinterpret_cast<bone_t*>(bones + boneloc);

			bone.x = bo.x + pos.x;
			bone.y = bo.y + pos.y;
			bone.z = bo.z + pos.z;
			return bone;
		}
		Vector3 getBonePositionByHitbox(int id)
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return { 0,0,0 };
			Vector3 origin = *reinterpret_cast<Vector3*>(Address + OffsetsT1::M_VecAbsOrigin);

			//BoneByHitBox
			uint64_t Model = *(uint64_t*)(Address + 0xff0);

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
			uint64_t BoneArray = *(uint64_t*)(Address + OffsetsT1::Bones);

			matrix3x4_t Matrix = *reinterpret_cast<matrix3x4_t*>(BoneArray + Bone * sizeof(matrix3x4_t));

			return Vector3(Matrix.m_flMatVal[0][3] + origin.x, Matrix.m_flMatVal[1][3] + origin.y, Matrix.m_flMatVal[2][3] + origin.z);
		}
		uint64_t Get_Address()
		{
			uint64_t Address = ((uint64_t)this);
			if (!Address) return 0;
			else return Address;
		}
	};
	int Get_Current_health()
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return 0;
		return *reinterpret_cast<int*>(Address + OffsetsT1::m_Health);

	}
	Vector3 Get_Position()
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return {0,0,0};
		Vector3 Pos = *reinterpret_cast<Vector3*>(Address + OffsetsT1::M_VecAbsOrigin);
		if (Pos.Empty()) return { 0,0,0 };
		return Pos;
	}
	std::string getName()
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return "";

		for (int i = 0; i < 250; i++)
		{
			std::uintptr_t Entity = (*reinterpret_cast<std::uintptr_t*>(((uintptr_t)GetModuleHandleA(NULL) + OffsetsT1::Entity + (i << 5))));

			if (Address == Entity)
			{
				uintptr_t nameptr = *reinterpret_cast<uintptr_t*>((uintptr_t)GetModuleHandleA(NULL) + OffsetsT1::NameList + (i - 1) * 0x10);
				if (!nameptr) continue;

				char* name = reinterpret_cast<char*>(nameptr);
				std::string s(name);
				return s;
			}
		}
		return "";
	}
	std::string getModelName()
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return "";
		uintptr_t pMode_Name = *reinterpret_cast<uintptr_t*>(Address + OffsetsT1::m_ModelName);
		char* modelName = reinterpret_cast<char*>(pMode_Name);
		std::string s(modelName);
		return s;
	}
	std::string getSignifierName()
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return "";
		uintptr_t sigAddr = *reinterpret_cast<uintptr_t*>(Address + OffsetsT1::m_iSignifierName);
		if (sigAddr == 0)
			return "";

		char* sig = reinterpret_cast<char*>(sigAddr);
		std::string s = std::string(sig);

		return s;
	}
	int GetPlayerLevel()
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return 0;
		int m_xp = *reinterpret_cast<int*>(Address + OffsetsT1::m_xp); //m_xp
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
	bool IsPlayer()
	{
		std::string name = getSignifierName();
		if (name == "player")
			return true;
		else
			return false;
	}
	bool IsDummy()
	{
		std::string name = getSignifierName();
		if (name == "npc_dummie")
			return true;
		else
			return false;
	}
	bool IsValid()
	{
		uint64_t Address = ((uint64_t)this);
		if (Address)
			return true;
		else 
			return false;
	}
	Vector3 getBonePos(int id)
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return { 0,0,0 };
		Vector3 pos = *reinterpret_cast<Vector3*>(Address + OffsetsT1::M_VecAbsOrigin); //PoopSets::M_VecAbsOrigin
		uintptr_t bones = *reinterpret_cast<uintptr_t*>(Address + OffsetsT1::Bones); //PoopSets::demfuckingBone
		Vector3 bone = {};
		UINT32 boneloc = (id * 0x30);
		bone_t bo = {};
		bo = *reinterpret_cast<bone_t*>(bones + boneloc);

		bone.x = bo.x + pos.x;
		bone.y = bo.y + pos.y;
		bone.z = bo.z + pos.z;
		return bone;
	}
	Vector3 getBonePositionByHitbox(int id)
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return { 0,0,0 };
		Vector3 origin = *reinterpret_cast<Vector3*>(Address + OffsetsT1::M_VecAbsOrigin);

		//BoneByHitBox
		uint64_t Model = *(uint64_t*)(Address + 0xff0);

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
		uint64_t BoneArray = *(uint64_t*)(Address + OffsetsT1::Bones);

		matrix3x4_t Matrix = *reinterpret_cast<matrix3x4_t*>(BoneArray + Bone * sizeof(matrix3x4_t));

		return Vector3(Matrix.m_flMatVal[0][3] + origin.x, Matrix.m_flMatVal[1][3] + origin.y, Matrix.m_flMatVal[2][3] + origin.z);
	}
	uint64_t Get_Address()
	{
		uint64_t Address = ((uint64_t)this);
		if (!Address) return 0;
		else return Address;
	}
};
void Nig()
{
	for (auto I = 0; I <= 1000; I++)
	{
		C_Entity* Entity = (reinterpret_cast<C_Entity*>((uintptr_t)GetModuleHandleA(NULL) + OffsetsT1::Entity));
		C_Entity::LocalPlayer* LocalPlayer = LocalPlayer->Get_LocalPlayer();

		if (Entity->Get_Address() == LocalPlayer->Get_Address()) continue;
		if (!Entity->IsValid()) continue;
		if (!LocalPlayer->IsValid()) continue;
		if (!Entity->IsPlayer()) continue;
		if (Entity->Get_Current_health() < .1f) continue;
		if (LocalPlayer->Get_Current_health() < .1f) continue;
		//Entity->TempList.push_back(Entity);
		Vector3 Screen_Head;
		Vector3 HeadPosition = Entity->getBonePos(BoneList::Head);
		if (HeadPosition.Empty()) continue;

		Vector3 Screen_Base;
		Vector3 BasePosition = Entity->Get_Position();
		if (BasePosition.Empty()) continue;

		ProjW2s(HeadPosition, Screen_Head);
		ProjW2s(BasePosition, Screen_Base);
		if (Screen_Head.Empty()) continue;
		if (Screen_Base.Empty()) continue;


		



	}
}