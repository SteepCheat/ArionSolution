#pragma once

void Misc(UINT64 TodCycle)
{
	if (Vars::Misc::AlwaysDay)
		safe_write(TodCycle + 0x10, Vars::FloatAntInt::TimeOfDay, float);

	if (Vars::Misc::SpiderMan)
		LocalPlayer.BasePlayer->SpiderMan();

	if (Vars::Misc::FakeAdmin)
		LocalPlayer.BasePlayer->FakeAdmin();

	if (Vars::Misc::SetGravitu)
		LocalPlayer.BasePlayer->GravituMod();

	if (Vars::Misc::InfinityJump)
		LocalPlayer.BasePlayer->InfinityJump();

	/*if (Vars::Misc::CustomFov)
		LocalPlayer.BasePlayer->SetFov();

	if (Vars::Misc::NightModeup)
		LocalPlayer.BasePlayer->todsky();

	if (Vars::Misc::FixAmbient)
		LocalPlayer.BasePlayer->UpdateAmbient();*/

	/*if (Vars::Misc::Zoom)
		LocalPlayer.BasePlayer->Zoom();*/

}