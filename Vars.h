#pragma once

namespace Vars
{
	namespace Other
	{
		int Width = 1920;
		int Height = 1080;
	}
	
	namespace Visuals
	{
		bool IgnoreSliping = false;
	}

	namespace Aim
	{
		bool AimBot = false;
		bool VisibleCheck = false;
		bool IgnoreTeam = false;
		int Range = 300;
		int BoneToAim = 46;//1 - body;
		float Fov = 50.f;

	}
	
	namespace FloatAntInt
	{
		int TimeOfDay = 12;
		float JumpValue = 2;
	}
	
	namespace Misc
	{
	/*	bool Zoom = false;
		int Zoomkey = 0;
		float Zoomvalue = 20.f;*/

		float NightModeup2 = 999.f;
		bool NightModeup = false;
		bool FixAmbient = false;
		bool CustomNight = false;
		float Nighted = 0.f;


		bool CustomFov = false; //Camera
		float GraphicsFov = 90.f;
		bool FatBullet = false;
		bool FakeAdmin = false;
		bool automatic = false;
		bool AlwaysDay = false;
		bool SpiderMan = false;
		bool anti_spread = false;
		bool no_recoil = false;
		bool SetGravitu = false;
		bool InfinityJump = false;
	}
}

