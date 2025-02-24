#define _ARMA_

//(8 Enums)
enum {
	destructengine = 2,
	destructdefault = 6,
	destructwreck = 7,
	destructtree = 3,
	destructtent = 4,
	destructno = 0,
	destructman = 5,
	destructbuilding = 1
};

class CfgPatches
{
	class DZ_Animals_cervus_elaphus_feminam
	{
		units[] = {"Animal_CervusElaphusF"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Animals"};
	};
};
class CfgVehicles
{
	class AnimalBase;
	class Animal_CervusElaphusF: AnimalBase
	{
		simulation = "dayzanimal";
		scope = 2;
		model = "\DZ\animals\cervus_elaphus_fem\cervus_elaphus_fem.p3d";
		displayName = "$STR_CfgVehicles_Animal_CervusElaphusF0";
		descriptionShort = "$STR_CfgVehicles_Animal_CervusElaphusF1";
		aiAgentTemplate = "Herbivores_CervusElaphusFem";
		injuryLevels[] = {1.0,0.5,0.2,0.0};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 300;
					healthLabels[] = {1.0,0.7,0.5,0.3,0.0};
				};
				class Blood
				{
					hitpoints = 5000;
				};
				class Shock
				{
					hitpoints = 100;
				};
			};
			class DamageZones
			{
				class Zone_Head
				{
					componentNames[] = {"Zone_Head"};
					transferToZonesNames[] = {};
					transferToZonesCoefs[] = {};
					fatalInjuryCoef = 0.15;
					canBleed = 0;
					class Health
					{
						hitpoints = 200;
						transferToGlobalCoef = 1;
					};
					class Blood: Health
					{
						hitpoints = 0;
					};
					class Shock: Health
					{
						hitpoints = 0;
					};
				};
				class Zone_Neck: Zone_Head
				{
					componentNames[] = {"Zone_Neck"};
					transferToZonesNames[] = {"Zone_Chest"};
					transferToZonesCoefs[] = {0.2};
					fatalInjuryCoef = 0.05;
					class Health: Health
					{
						hitpoints = 200;
					};
				};
				class Zone_Chest: Zone_Head
				{
					componentNames[] = {"Zone_Chest"};
					transferToZonesNames[] = {"Zone_Neck","Zone_Belly"};
					transferToZonesCoefs[] = {0.15,0.15};
					fatalInjuryCoef = 0.05;
					class Health: Health
					{
						hitpoints = 200;
					};
				};
				class Zone_Belly: Zone_Head
				{
					componentNames[] = {"Zone_Belly"};
					transferToZonesNames[] = {"Zone_Pelvis","Zone_Chest"};
					transferToZonesCoefs[] = {0.15,0.15};
					fatalInjuryCoef = 0.05;
					class Health: Health
					{
						hitpoints = 300;
					};
				};
				class Zone_Spine: Zone_Head
				{
					componentNames[] = {"Zone_Spine"};
					transferToZonesNames[] = {"Zone_Pelvis","Zone_Belly","Zone_Chest"};
					transferToZonesCoefs[] = {0.1,0.1,0.1};
					fatalInjuryCoef = 0.05;
					class Health: Health
					{
						hitpoints = 200;
					};
				};
				class Zone_Pelvis: Zone_Head
				{
					componentNames[] = {"Zone_Pelvis"};
					transferToZonesNames[] = {"Zone_Spine","Zone_Belly"};
					transferToZonesCoefs[] = {0.15,0.15};
					fatalInjuryCoef = 0.05;
					class Health: Health
					{
						hitpoints = 250;
					};
				};
				class Zone_Legs: Zone_Head
				{
					componentNames[] = {"Zone_Legs"};
					transferToZonesNames[] = {"Zone_Pelvis","Zone_Belly","Zone_Chest"};
					transferToZonesCoefs[] = {0.1,0.1,0.1};
					fatalInjuryCoef = 0.0;
					class Health: Health
					{
						hitpoints = 100;
					};
				};
			};
		};
		class Skinning
		{
			class ObtainedSteaks
			{
				item = "DeerSteakMeat";
				count = 17;
				itemZones[] = {"Zone_Chest","Zone_Belly","Zone_Pelvis"};
				countByZone[] = {7.0,5.0,6.0};
				quantityMinMaxCoef[] = {0.75,1};
			};
			class ObtainedGuts
			{
				item = "Guts";
				count = 3;
				quantityMinMaxCoef[] = {0.5,1};
			};
			class ObtainedPelt
			{
				item = "DeerPelt";
				count = 1;
				quantityCoef = 1;
				transferToolDamageCoef = 1;
			};
			class ObtainedLard
			{
				item = "Lard";
				count = 3;
				quantityMinMaxCoef[] = {0.5,1};
			};
			class ObtainedBones
			{
				item = "Bone";
				count = 3;
				quantityMinMaxCoef[] = {0.8,1};
				transferToolDamageCoef = 1;
			};
		};
		class enfanimsys
		{
			meshObject = "dz\animals\cervus_elaphus_fem\Data\cervus_elaphus_fem_skeleton.xob";
			graphname = "dz\animals\animations\!graph_files\Herbivores\Herbivores_Graph.agr";
			defaultinstance = "dz\animals\animations\!graph_files\Herbivores\DeerFemSkeleton_AnimInstance.asi";
			startnode = "MasterDeers_SM";
			skeletonName = "cervus_elaphus_skeleton.xob";
		};
		class AnimEvents
		{
			class Steps
			{
				class Walk1
				{
					soundLookupTable = "HoofMediumWalk_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 1;
				};
				class Walk2
				{
					soundLookupTable = "HoofMediumWalk_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 2;
				};
				class Walk3
				{
					soundLookupTable = "HoofMediumWalk_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 3;
				};
				class Walk4
				{
					soundLookupTable = "HoofMediumWalk_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 4;
				};
				class Run1
				{
					soundLookupTable = "HoofMediumRun_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 5;
				};
				class Run2
				{
					soundLookupTable = "HoofMediumRun_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 6;
				};
				class Run3
				{
					soundLookupTable = "HoofMediumRun_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 7;
				};
				class Run4
				{
					soundLookupTable = "HoofMediumRun_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 8;
				};
				class Grazing1
				{
					soundLookupTable = "HoofMediumGrazing_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 9;
				};
				class Grazing2
				{
					soundLookupTable = "HoofMediumGrazing_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 10;
				};
				class Bodyfall
				{
					soundLookupTable = "HoofMediumBodyfall_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 11;
				};
				class Settle
				{
					soundLookupTable = "HoofMediumSettle_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 12;
				};
				class Rest2standA
				{
					soundLookupTable = "HoofMediumRest2standA_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 13;
				};
				class Rest2standB
				{
					soundLookupTable = "HoofMediumRest2standB_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 14;
				};
				class Stand2restA
				{
					soundLookupTable = "HoofMediumStand2restA_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 15;
				};
				class Stand2restB
				{
					soundLookupTable = "HoofMediumStand2restB_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 16;
				};
				class Stand2restC
				{
					soundLookupTable = "HoofMediumStand2restC_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 17;
				};
				class Rub1
				{
					soundLookupTable = "HoofMediumRub1_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 18;
				};
				class Rub2
				{
					soundLookupTable = "HoofMediumRub2_LookupTable";
					noise = "DeerStepNoise";
					effectSet[] = {"DeerStepEffect1","DeerStepEffect2"};
					id = 19;
				};
			};
			class Sounds
			{
				class DeerBleat
				{
					soundSet = "DeerBleat_SoundSet";
					noise = "DeerRoarNoise";
					id = 1;
				};
				class DoeBleat
				{
					soundSet = "DoeBleat_SoundSet";
					noise = "DeerRoarNoise";
					id = 2;
				};
				class DeerBreath
				{
					soundSet = "DeerBreath_SoundSet";
					noise = "DeerRoarNoise";
					id = 3;
				};
				class DeerBark
				{
					soundSet = "DeerBark_SoundSet";
					noise = "DeerRoarNoise";
					id = 4;
				};
				class DoeBark
				{
					soundSet = "DoeBark_SoundSet";
					noise = "DeerRoarNoise";
					id = 5;
				};
				class RoeBark
				{
					soundSet = "RoeBark_SoundSet";
					noise = "DeerRoarNoise";
					id = 6;
				};
				class DeerCall
				{
					soundSet = "DeerCall_SoundSet";
					noise = "DeerRoarNoise";
					id = 7;
				};
				class DeerCallFear
				{
					soundSet = "DeerCallFear_SoundSet";
					noise = "DeerRoarNoise";
					id = 8;
				};
				class DeerGrunt
				{
					soundSet = "DeerGrunt_SoundSet";
					noise = "DeerRoarNoise";
					id = 9;
				};
				class DeerRoar
				{
					soundSet = "DeerRoar_SoundSet";
					noise = "DeerRoarNoise";
					id = 10;
				};
				class DeerRoarLong
				{
					soundSet = "DeerRoarLong_SoundSet";
					noise = "DeerRoarNoise";
					id = 11;
				};
				class DeerRoarShort
				{
					soundSet = "DeerRoarShort_SoundSet";
					noise = "DeerRoarNoise";
					id = 12;
				};
				class DeerSnort
				{
					soundSet = "DeerSnort_SoundSet";
					noise = "DeerRoarNoise";
					id = 13;
				};
				class DeerFemRoarX1
				{
					soundSet = "DeerFemRoarX1_SoundSet";
					noise = "DeerRoarNoise";
					id = 14;
				};
				class DeerFemRoarX1_Tail
				{
					soundSet = "DeerFemRoarX1_Tail_SoundSet";
					noise = "DeerRoarNoise";
					id = 15;
				};
				class DeerFemRoarX2
				{
					soundSet = "DeerFemRoarX2_SoundSet";
					noise = "DeerRoarNoise";
					id = 16;
				};
				class DeerFemRoarX2_Tail
				{
					soundSet = "DeerFemRoarX2_Tail_SoundSet";
					noise = "DeerRoarNoise";
					id = 17;
				};
				class DeerFemRoarX3
				{
					soundSet = "DeerFemRoarX3_SoundSet";
					noise = "DeerRoarNoise";
					id = 18;
				};
				class DeerFemRoarX3_Tail
				{
					soundSet = "DeerFemRoarX3_Tail_SoundSet";
					noise = "DeerRoarNoise";
					id = 19;
				};
				class DeerFemRoarX4
				{
					soundSet = "DeerFemRoarX4_SoundSet";
					noise = "DeerRoarNoise";
					id = 20;
				};
				class DeerFemRoarX4_Tail
				{
					soundSet = "DeerFemRoarX4_Tail_SoundSet";
					noise = "DeerRoarNoise";
					id = 21;
				};
				class DeerFemRoarX5
				{
					soundSet = "DeerFemRoarX5_SoundSet";
					noise = "DeerRoarNoise";
					id = 22;
				};
				class DeerFemRoarX5_Tail
				{
					soundSet = "DeerFemRoarX5_Tail_SoundSet";
					noise = "DeerRoarNoise";
					id = 23;
				};
			};
			class Damages
			{
				class Bite
				{
					damage = "DeerBiteDamage";
					id = 1;
				};
			};
		};
		class CommandMoveSettings
		{
			useSpeedMapping = 1;
			movementSpeedMapping[] = {0.0,0.18,0.7,2.8,5.9,15.5};
		};
		class CommandLookAtSettings
		{
			lookAtFilterTimeout = 0.5;
			lookAtFilterSpeed = 1.57;
		};
	};
};
