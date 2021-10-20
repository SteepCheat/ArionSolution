float GetBulletSpeed()
{
	switch (LocalPlayer.BasePlayer->GetActiveWeapon()->GetItemID())
	{
	case 1796682209: //smg
		return 240.f;
	case 1588298435: //bolt
		return 656.25f;
	case -778367295: //l96
		return 1125.f;
	case 28201841: //m39
		return 469.f;
	case 1953903201: //nailgun
		return 50.f;
	case 649912614: //revolver
		return 300.f;
	case 818877484: //p250
		return 300.f;
	case -1367281941: //waterpipe, 250-green ammo, 100-other
		return 100.f;
	case -765183617: //double barrel, 250-green ammo, 100-other
		return 100.f;
	case -1812555177: //lr300
		return 375.f;
	case -852563019: //m92
		return 300.f;
	case -1123473824: //grenade launcher, shotgun - 250, other - 100
		return 100.f;
	case 442886268: //rocket launcher, unknown
		return 250.f;
	case -904863145: //semiautomatic rifle
		return 375.f;
	case -41440462: //spas12, 250-green ammo, 100-other
		return 100.f;
	case 1545779598: //ak47
		return 375.f;
	case 1443579727: //bow, 80-high speed arrow, 40 - fire arrow, 50 - normal
		return 50.f;
	case -75944661: //eoka, 250-green ammo, 100-other
		return 100.f;
	case 1318558775: //mp5a4
		return 240.f;
	case 795371088: //pomp shotgun, 250-green ammo, 100-other
		return 100.f;
	case 1965232394: //crossbow, 75 - normal, 120-high velocity, 60 - fire
		return 75.f;
	case -2069578888:
		return 488.f;
	case 1373971859: //python
		return 300.f;
	case -1758372725: //tompson
		return 300.f;
	default:
		return 250.f;
	}
}

float AimFov(BasePlayer* Entity)
{
	Vector2 ScreenPos;
	if (!LocalPlayer.WorldToScreen(Entity->GetBoneByID(), ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(Vars::Other::Width / 2, Vars::Other::Height / 2), ScreenPos);

	//return Math::Calc2D_Dist(Vector2(Vars::Other::Width / 2, Vars::Other::Height / 2), ScreenPos);
}

Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone)
{
	Vector3 BonePos = Player->GetBoneByID();
	float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

	if (Dist > 0.001f) {
		float BulletTime = Dist / GetBulletSpeed();
		Vector3 vel = Player->GetVelocity();
		Vector3 PredictVel = vel * BulletTime * 0.75f;
		BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
	} return BonePos;
}

void Normalize(float& Yaw, float& Pitch) {
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}

void AimBotTarget(BasePlayer* player)
{
	Vector3 Local = LocalPlayer.BasePlayer->GetBoneByID();
	Vector3 PlayerPos = player->GetBoneByID();
	PlayerPos = Prediction(Local, player, BoneList(neck));
	//std::cout << "target predicted " << PlayerPos.x << " " << PlayerPos.y << " " << PlayerPos.z << std::endl;
	Vector2 AngleToAim = Math::CalcAngle(Local, PlayerPos);
	Normalize(AngleToAim.y, AngleToAim.x);
	if (isnan(AngleToAim.x) || isnan(AngleToAim.y))
		return;
	LocalPlayer.BasePlayer->SetVA(AngleToAim);


	/*std::cout << "Gototarget " << "x: " << AngleToAim.x << " " << AngleToAim.y << " Distance: " << Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(), player->GetBoneByID()) << " Fov: " << AimFov(player) << std::endl;*/

	Normalize(AngleToAim.y, AngleToAim.x);
	LocalPlayer.BasePlayer->SetVA(AngleToAim);
}

void Aim(BasePlayer* player)
{
	if (Vars::Aim::AimBot)
	{
		if (GetAsyncKeyState(0x58)) {
			//std::cout << "Target " << player->GetSteamID() << std::endl;
			WeaponData* ActWeapon = LocalPlayer.BasePlayer->GetActiveWeapon();
			AimBotTarget(player);
		}
	}
}
