#pragma once

class WeaponData
{
public:

	/*Weapons info*/
	
		int GetItemID()
		{
			UINT64 Info = safe_read((const uintptr_t)this + oItemDefinition, UINT64);
			return safe_read(Info + oItemid, int);
		}

	int GetUID()
	{
		return safe_read((const uintptr_t)this + 0x28, int);
	}

	/*Functions for weapons*/
	
	void SetAutomatic()
	{
		if (Vars::Misc::automatic)
		{
			UINT64 Held = safe_read((const uintptr_t)(const uintptr_t)this + oHeld, UINT64);
			safe_write((const uintptr_t)Held + oAuto, 1, bool);
		}
	}

	void FatBullet()
	{
		if (Vars::Misc::FatBullet)
		{
			DWORD64 Held = safe_read((const uintptr_t)this + oHeld, DWORD64);
			DWORD64 List = safe_read(Held + 0x358, DWORD64); //private List<Projectile> createdProjectiles;
			int size = safe_read(List + 0x18, DWORD64);
			List = safe_read(List + 0x10, DWORD64);

			{
				for (int i = 0; i < size; ++i)
				{
					UINT64 Item = safe_read(List + 0x20 + (i * 0x8), UINT64);
					safe_write(Item + 0x2C, 3.0f, float);
				}
			}

		}
	}
	
	void AntiSpread()
	{
		if (Vars::Misc::anti_spread)
		{
			DWORD64 Held = safe_read((const uintptr_t)this + oHeld, DWORD64);
			safe_write(Held + oStancePenalty, 0.f, float);
			safe_write(Held + oAimconePenalty, 0.f, float);
			safe_write(Held + oAimCone, 0.f, float);
			safe_write(Held + oHipAimCone, 0.f, float);
			safe_write(Held + oAimconePenaltyPerShot, 0.f, float);
			//Работает
		}
	}

	void NoRecoil()
	{
		if (Vars::Misc::no_recoil)
		{
			DWORD64 Held = safe_read((const uintptr_t)this + oHeld, DWORD64);
			DWORD64 recoil = safe_read(Held + oRecoilProperties, DWORD64);
			safe_write(recoil + oRecoilMinYaw, 0.f, float);
			safe_write(recoil + oRecoilMaxYaw, 0.f, float);
			safe_write(recoil + oRecoilMinPitch, 0.f, float);
			safe_write(recoil + oRecoilMaxPitch, 0.f, float);
			//safe_write(recoil + 0x30, 0.f, float); //public float ADSScale; 
			//safe_write(recoil + 0x34, 0.f, float); //public float movementPenalty; 		
			//Работает
		}
	}
	
private:
};
