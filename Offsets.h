#pragma once
DWORD64 automatic[]
{
	1545779598, // AK - 47;
	-1758372725, // Томсон
	1796682209, // SMG
	-1812555177,// LR - 300
	1318558775, // MP5
	-2069578888, // M249
};

DWORD64 sniper[]
{
	-778367295, // L96
	1588298435, // Болт
};

DWORD64 semiautomatic[]{
	-904863145, // Берданка 
	818877484, // Пэшка
	-852563019, // берета
	1373971859, // Питон
	649912614, // револьвер
	28201841, // M39
	1953903201, // Гвоздомёт
	-1123473824, // Гранатомёт
};

//DWORD64 meele[]{ 
//	-1978999529, 1602646136, -194509282, -1966748496, 1326180354, 1540934679
//};
//nopatch 884424049(compound), 
//DWORD64 bow = 1802482880;

#define oGameObjectManager 0x17C1F18 // 0x17D69F8
#define oBaseNetworkable   52641824 // BaseNetworkable_c*
//#define oConVar 52633440 //ConVar_Graphics_c*
//#define oTOD_Sky 52651936 //TOD_Sky_c*
#define oBasePlayer 52641640 //BasePlayer_c*


//class BasePlayer
#define oPlayerFlags 0x650 // public BasePlayer.PlayerFlags playerFlags;
#define oPlayerName 0x6B0 // protected string _displayName;
#define oPlayerHealth 0x224 // private float _health;
#define olastSentTickTime 0x624 // private float lastSentTickTime;
#define oClientTeam 0x598 // public PlayerTeam clientTeam;
#define oLifestate 0x21C // public BaseCombatEntity.LifeState lifestate;
#define oSteamID 0x698 // public ulong userID;
#define oPlayerInventory 0x660 // public PlayerInventory inventory;
#define oActiveUID 0x5C8// private uint clActiveItem;
#define oFrozen 0x4C8// public bool Frozen;
#define oWaterBonus 0x728// public float clothingWaterSpeedBonus;
#define oNoBlockAiming 0x720 // public bool clothingBlocksAiming;
#define oSpeedReduction 0x724// public float clothingMoveSpeedReduction;
#define oClothingAccuracyBonus 0x72C //	public float clothingAccuracyBonus;


//EntityRef
#define oHeld 0x98 //private EntityRef heldEntity ..private EntityRef heldEntity; // 0x98 //private EntityRef heldEntity
#define oStancePenalty 0x31C //private float stancePenalty;
#define	oAimconePenalty	0x320 //private float aimconePenalty;
#define	oHipAimCone 0x2EC //public float hipAimCone;
#define	oAimCone 0x6C8 //public float aimCone;			(class BaseProjectile)
#define	oAimconePenaltyPerShot 0x2F0 //public float aimconePenaltyPerShot;
#define oSuccessFraction 0x360 // public float successFraction;
#define oAttackRadius 0x294 //public float attackRadius;
#define oEffectiveRange 0x1FC //public float effectiveRange;
#define oIsAutomatic 0x298 //public bool isAutomatic;
#define oMaxDistance 0x290 //public float maxDistance;			(class BaseMelee)
#define oRepeatDelay 0x1F4 //public float repeatDelay;

//BaseProjectile
#define oAuto 0x288 //public bool automatic;
#define oFastReload 0x2C0 // bool fractionalReload
#define oDistance 0x280 // public float distanceScale
#define oprojectileVelocityScale 0x284 //public float projectileVelocityScale

//BaseMovement
#define oPlayerMovement 0x4E8 // public BaseMovement movement;
#define oGravityMultiplier 0x7C // public float gravityMultiplier;

#define oGroundAngle 0xBC// private float groundAngle;
#define oGroundAngleNew 0xC0 // private float groundAngleNew;

//RecoilProperties
#define oRecoilProperties 0x2D8 //public RecoilProperties recoil;
#define oRecoilMinYaw 0x18 //public float recoilYawMin;
#define oRecoilMaxYaw 0x1C //public float recoilYawMax;
#define oRecoilMinPitch 0x20 //public float recoilPitchMin;
#define oRecoilMaxPitch 0x24 //public float recoilPitchMax;


//PlayerModel
#define oPlayerModel 0x4C0 // public PlayerModel playerModel;
#define oVisible 0x268 // internal bool visible;

//PlayerInput
#define oPlayerInput 0x4E0// public PlayerInput input;
#define oBodyAngles 0x3C // private Vector3 bodyAngles;
#define oRecoilAngles 0x64 // public Vector3 recoilAngles;
#define oHasKeyFocus 0x94 // private bool hasKeyFocus;


#define oArrowBack 0x364 // private float arrowBack;
#define oTriggerReady 0x360 // protected bool attackReady;
#define oItemDefinition 0x20 // public ItemDefinition info;
#define oItemid 0x18 // public int itemid;
