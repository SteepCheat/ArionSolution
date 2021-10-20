#pragma once
void WeaponFix(WeaponData* weapon)
{
	int ItemID = 0;
	if (weapon)
		ItemID = weapon->GetItemID();
	if (!ItemID) return;

	for (DWORD64 val : semiautomatic) {
		if (ItemID == val) {
			weapon->NoRecoil();
			weapon->AntiSpread();
			weapon->SetAutomatic();
			weapon->FatBullet();
			return;
		}
	}
	//for (DWORD64 val : meele) {
	//	if (Id == val) {
	//		Weapon->FatHand();
	//		Weapon->LongHand();
	//		Weapon->RunOnHit();
	//		return;
	//	}
	//}
	for (DWORD64 val : sniper) {
		if (ItemID == val) {
			weapon->NoRecoil();
			weapon->AntiSpread();
			weapon->FatBullet();
			return;
		}
	}
	for (DWORD64 val : automatic) {
		if (ItemID == val) {
			weapon->NoRecoil();
			weapon->AntiSpread();
			weapon->FatBullet();
			return;
		}
	}
	//if (Id == bow) {
	//	//Weapon->SuperBow();
	//	return;
	//}
	//if (Id == -75944661)
	//{
	//	Weapon->SuperEoka();
	//	return;
	//}
	//if (Id == 1488979457)
	//{
	//	Weapon->JackhammerBlyat();
	//	return;
	//}
}
