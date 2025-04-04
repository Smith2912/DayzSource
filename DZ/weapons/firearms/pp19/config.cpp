class CfgPatches
{
	class DZ_Weapons_Firearms_PP19
	{
		units[]=
		{
			"PP19"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Firearms"
		};
	};
};
class Mode_Safe;
class Mode_SemiAuto;
class Mode_FullAuto;
class OpticsInfoRifle;
class cfgWeapons
{
	class Rifle_Base;
	class PP19_Base: Rifle_Base
	{
		scope=0;
		displayName="$STR_cfgWeapons_PP19_0";
		descriptionShort="$STR_cfgWeapons_PP19_1";
		model="\dz\weapons\firearms\PP19\PP19.p3d";
		attachments[]=
		{
			"weaponWrap",
			"weaponOpticsAK",
			"pistolMuzzle",
			"weaponButtstockPP19"
		};
		weight=2900;
		itemSize[]={6,3};
		repairableWithKits[]={1};
		repairCosts[]={25};
		WeaponLength=0.66352999;
		barrelArmor=1.35;
		chamberSize=1;
		chamberedRound="";
		chamberableFrom[]=
		{
			"Ammo_380"
		};
		magazines[]=
		{
			"Mag_PP19_64Rnd"
		};
		magazineSwitchTime=0.30000001;
		initSpeedMultiplier=1.25;
		ejectType=1;
		recoilModifier[]={1,1,1};
		swayModifier[]={1.1,1.1,1};
		PPDOFProperties[]={1,0.5,10,130,4,10};
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"dz\weapons\firearms\PP19\data\PP19_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\weapons\firearms\PP19\data\PP_19.rvmat"
		};
		class NoiseShoot
		{
			strength=66;
			type="shot";
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=250;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\PP19\Data\PP_19.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\PP19\Data\PP_19.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\PP19\Data\PP_19_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\PP19\Data\PP_19_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\PP19\Data\PP_19_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		modes[]=
		{
			"SemiAuto",
			"FullAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"Bizon_Shot_SoundSet",
				"Bizon_Tail_SoundSet",
				"Bizon_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"Bizon_silencer_SoundSet",
					"Bizon_silencerTail_SoundSet",
					"Bizon_silencerInteriorTail_SoundSet"
				},
				
				{
					"Bizon_silencerHomeMade_SoundSet",
					"Bizon_silencerHomeMadeTail_SoundSet",
					"Bizon_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.12;
			recoil="recoil_cz61";
			recoilProne="recoil_cz61_prone";
			dispersion=0.003;
			magazineSlot="magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"Bizon_Shot_SoundSet",
				"Bizon_Tail_SoundSet",
				"Bizon_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"Bizon_silencer_SoundSet",
					"Bizon_silencerTail_SoundSet",
					"Bizon_silencerInteriorTail_SoundSet"
				},
				
				{
					"Bizon_silencerHomeMade_SoundSet",
					"Bizon_silencerHomeMadeTail_SoundSet",
					"Bizon_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.097999997;
			recoil="recoil_cz61";
			recoilProne="recoil_cz61_prone";
			dispersion=0.003;
			magazineSlot="magazine";
		};
		class OpticsInfo: OpticsInfoRifle
		{
			memoryPointCamera="eye";
			discreteDistance[]={75,150};
			discreteDistanceInitIndex=0;
			modelOptics="-";
			distanceZoomMin=100;
			distanceZoomMax=100;
		};
		class InventorySlotsOffsets
		{
			class Shoulder
			{
				position[]={-0.059999999,-0.02,0.029999999};
				orientation[]={0,15,0};
			};
			class Melee
			{
				position[]={-0.059999999,-0.02,-0.050000001};
				orientation[]={0,-15,0};
			};
		};
		class Particles
		{
			class OnFire
			{
				class MuzzleFlash
				{
					overrideParticle="weapon_shot_cz61_01";
					ignoreIfSuppressed=1;
					illuminateWorld=1;
				};
				class SmokeCloud
				{
					overrideParticle="weapon_shot_winded_smoke_small";
				};
			};
			class OnOverheating
			{
				shotsToStartOverheating=15;
				maxOverheatingValue=30;
				overheatingDecayInterval=1;
				class SmokingBarrel
				{
					overrideParticle="smoking_barrel_small";
					onlyWithinOverheatLimits[]={0,0.5};
					onlyWithinRainLimits[]={0,0.2};
					ignoreIfSuppressed=1;
				};
				class SmokingBarrelHotSteam
				{
					overrideParticle="smoking_barrel_steam_small";
					positionOffset[]={0.1,0.02,0};
					onlyWithinOverheatLimits[]={0,1};
					onlyWithinRainLimits[]={0.2,1};
				};
				class OpenChamberSmoke
				{
					onlyIfBoltIsOpen=1;
					overrideParticle="smoking_barrel_small";
					overridePoint="Nabojnicestart";
				};
			};
			class OnBulletCasingEject
			{
				class ChamberSmokeRaise
				{
					overrideParticle="weapon_shot_chamber_smoke_raise";
					overridePoint="Nabojnicestart";
				};
			};
		};
		weaponStateAnim="dz\anims\anm\player\reloads\Bizon\w_bizon_states.anm";
	};
	class PP19: PP19_Base
	{
		scope=2;
	};
};
