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
	class DZ_Weapons_Projectiles
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};
class CfgAmmo
{
	class ShotgunCore;
	class DefaultAmmo;
	class BulletCore;
	class Bullet_Base: BulletCore
	{
		scope = 0;
		hit = 8;
		indirectHit = 0;
		indirectHitRange = 0;
		model = "\dz\weapons\projectiles\empty.p3d";
		soundFly[] = {"",9.999997e-09,1};
		soundDefault1[] = {"dz\sounds\weapons\hits\bullet\soft_ground_1",0.5,1,40};
		soundDefault2[] = {"dz\sounds\weapons\hits\bullet\soft_ground_2",0.5,1,40};
		soundDefault3[] = {"dz\sounds\weapons\hits\bullet\soft_ground_3",0.5,1,40};
		soundDefault4[] = {"dz\sounds\weapons\hits\bullet\soft_ground_4",0.5,1,40};
		soundDefault5[] = {"dz\sounds\weapons\hits\bullet\soft_ground_5",0.5,1,40};
		soundDefault6[] = {"dz\sounds\weapons\hits\bullet\soft_ground_6",0.5,1,40};
		soundDefault7[] = {"dz\sounds\weapons\hits\bullet\soft_ground_7",0.5,1,40};
		soundDefault8[] = {"dz\sounds\weapons\hits\bullet\soft_ground_8",0.5,1,40};
		soundGroundSoft1[] = {"dz\sounds\weapons\hits\bullet\soft_ground_1",0.5,1,40};
		soundGroundSoft2[] = {"dz\sounds\weapons\hits\bullet\soft_ground_2",0.5,1,40};
		soundGroundSoft3[] = {"dz\sounds\weapons\hits\bullet\soft_ground_3",0.5,1,40};
		soundGroundSoft4[] = {"dz\sounds\weapons\hits\bullet\soft_ground_4",0.5,1,40};
		soundGroundSoft5[] = {"dz\sounds\weapons\hits\bullet\soft_ground_5",0.5,1,40};
		soundGroundSoft6[] = {"dz\sounds\weapons\hits\bullet\soft_ground_6",0.5,1,40};
		soundGroundSoft7[] = {"dz\sounds\weapons\hits\bullet\soft_ground_7",0.5,1,40};
		soundGroundSoft8[] = {"dz\sounds\weapons\hits\bullet\soft_ground_8",0.5,1,40};
		soundGroundHard1[] = {"dz\sounds\weapons\hits\bullet\hard_ground_1",0.5,1,40};
		soundGroundHard2[] = {"dz\sounds\weapons\hits\bullet\hard_ground_2",0.5,1,40};
		soundGroundHard3[] = {"dz\sounds\weapons\hits\bullet\hard_ground_3",0.5,1,40};
		soundGroundHard4[] = {"dz\sounds\weapons\hits\bullet\hard_ground_4",0.5,1,40};
		soundGroundHard5[] = {"dz\sounds\weapons\hits\bullet\hard_ground_5",0.5,1,40};
		soundGroundHard6[] = {"dz\sounds\weapons\hits\bullet\hard_ground_6",0.5,1,40};
		soundGroundHard7[] = {"dz\sounds\weapons\hits\bullet\hard_ground_7",0.5,1,40};
		soundGroundHard8[] = {"dz\sounds\weapons\hits\bullet\hard_ground_8",0.5,1,40};
		soundMetal1[] = {"dz\sounds\weapons\hits\bullet\metal_1",0.5,1,40};
		soundMetal2[] = {"dz\sounds\weapons\hits\bullet\metal_2",0.5,1,40};
		soundMetal3[] = {"dz\sounds\weapons\hits\bullet\metal_3",0.5,1,40};
		soundMetal4[] = {"dz\sounds\weapons\hits\bullet\metal_4",0.5,1,40};
		soundMetal5[] = {"dz\sounds\weapons\hits\bullet\metal_5",0.5,1,40};
		soundMetal6[] = {"dz\sounds\weapons\hits\bullet\metal_6",0.5,1,40};
		soundMetal7[] = {"dz\sounds\weapons\hits\bullet\metal_7",0.5,1,40};
		soundMetal8[] = {"dz\sounds\weapons\hits\bullet\metal_8",0.5,1,40};
		soundGlass1[] = {"dz\sounds\weapons\hits\bullet\glass_1",0.5,1,40};
		soundGlass2[] = {"dz\sounds\weapons\hits\bullet\glass_2",0.5,1,40};
		soundGlass3[] = {"dz\sounds\weapons\hits\bullet\glass_3",0.5,1,40};
		soundGlass4[] = {"dz\sounds\weapons\hits\bullet\glass_4",0.5,1,40};
		soundGlass5[] = {"dz\sounds\weapons\hits\bullet\glass_5",0.5,1,40};
		soundGlass6[] = {"dz\sounds\weapons\hits\bullet\glass_6",0.5,1,40};
		soundGlass7[] = {"dz\sounds\weapons\hits\bullet\glass_7",0.5,1,40};
		soundGlass8[] = {"dz\sounds\weapons\hits\bullet\glass_8",0.5,1,40};
		soundGlassArmored1[] = {"dz\sounds\weapons\hits\bullet\glass_arm_1",0.5,1,40};
		soundGlassArmored2[] = {"dz\sounds\weapons\hits\bullet\glass_arm_2",0.5,1,40};
		soundGlassArmored3[] = {"dz\sounds\weapons\hits\bullet\glass_arm_3",0.5,1,40};
		soundGlassArmored4[] = {"dz\sounds\weapons\hits\bullet\glass_arm_4",0.5,1,40};
		soundGlassArmored5[] = {"dz\sounds\weapons\hits\bullet\glass_arm_5",0.5,1,40};
		soundGlassArmored6[] = {"dz\sounds\weapons\hits\bullet\glass_arm_6",0.5,1,40};
		soundGlassArmored7[] = {"dz\sounds\weapons\hits\bullet\glass_arm_7",0.5,1,40};
		soundGlassArmored8[] = {"dz\sounds\weapons\hits\bullet\glass_arm_8",0.5,1,40};
		soundVehiclePlate1[] = {"dz\sounds\weapons\hits\bullet\metal_plate_1",0.5,1,40};
		soundVehiclePlate2[] = {"dz\sounds\weapons\hits\bullet\metal_plate_2",0.5,1,40};
		soundVehiclePlate3[] = {"dz\sounds\weapons\hits\bullet\metal_plate_3",0.5,1,40};
		soundVehiclePlate4[] = {"dz\sounds\weapons\hits\bullet\metal_plate_4",0.5,1,40};
		soundVehiclePlate5[] = {"dz\sounds\weapons\hits\bullet\metal_plate_5",0.5,1,40};
		soundVehiclePlate6[] = {"dz\sounds\weapons\hits\bullet\metal_plate_6",0.5,1,40};
		soundVehiclePlate7[] = {"dz\sounds\weapons\hits\bullet\metal_plate_7",0.5,1,40};
		soundVehiclePlate8[] = {"dz\sounds\weapons\hits\bullet\metal_plate_8",0.5,1,40};
		soundWood1[] = {"dz\sounds\weapons\hits\bullet\wood_1",0.5,1,40};
		soundWood2[] = {"dz\sounds\weapons\hits\bullet\wood_2",0.5,1,40};
		soundWood3[] = {"dz\sounds\weapons\hits\bullet\wood_3",0.5,1,40};
		soundWood4[] = {"dz\sounds\weapons\hits\bullet\wood_4",0.5,1,40};
		soundWood5[] = {"dz\sounds\weapons\hits\bullet\wood_5",0.5,1,40};
		soundWood6[] = {"dz\sounds\weapons\hits\bullet\wood_6",0.5,1,40};
		soundWood7[] = {"dz\sounds\weapons\hits\bullet\wood_7",0.5,1,40};
		soundWood8[] = {"dz\sounds\weapons\hits\bullet\wood_8",0.5,1,40};
		soundHitBody1[] = {"dz\sounds\weapons\hits\bullet\body_1",1,1,20};
		soundHitBody2[] = {"dz\sounds\weapons\hits\bullet\body_2",1,1,20};
		soundHitBody3[] = {"dz\sounds\weapons\hits\bullet\body_3",1,1,20};
		soundHitBody4[] = {"dz\sounds\weapons\hits\bullet\body_4",1,1,20};
		soundHitBody5[] = {"dz\sounds\weapons\hits\bullet\body_5",1,1,20};
		soundHitBody6[] = {"dz\sounds\weapons\hits\bullet\body_6",1,1,20};
		soundHitBody7[] = {"dz\sounds\weapons\hits\bullet\body_7",1,1,20};
		soundHitBody8[] = {"dz\sounds\weapons\hits\bullet\body_8",1,1,20};
		soundHitBuilding1[] = {"dz\sounds\weapons\hits\bullet\building_1",0.5,1,40};
		soundHitBuilding2[] = {"dz\sounds\weapons\hits\bullet\building_2",0.5,1,40};
		soundHitBuilding3[] = {"dz\sounds\weapons\hits\bullet\building_3",0.5,1,40};
		soundHitBuilding4[] = {"dz\sounds\weapons\hits\bullet\building_4",0.5,1,40};
		soundHitBuilding5[] = {"dz\sounds\weapons\hits\bullet\building_5",0.5,1,40};
		soundHitBuilding6[] = {"dz\sounds\weapons\hits\bullet\building_6",0.5,1,40};
		soundHitBuilding7[] = {"dz\sounds\weapons\hits\bullet\building_7",0.5,1,40};
		soundHitBuilding8[] = {"dz\sounds\weapons\hits\bullet\building_8",0.5,1,40};
		soundHitFoliage1[] = {"dz\sounds\weapons\hits\bullet\foliage_1",1,1,20};
		soundHitFoliage2[] = {"dz\sounds\weapons\hits\bullet\foliage_2",1,1,20};
		soundHitFoliage3[] = {"dz\sounds\weapons\hits\bullet\foliage_3",1,1,20};
		soundHitFoliage4[] = {"dz\sounds\weapons\hits\bullet\foliage_4",1,1,20};
		soundHitFoliage5[] = {"dz\sounds\weapons\hits\bullet\foliage_5",1,1,20};
		soundHitFoliage6[] = {"dz\sounds\weapons\hits\bullet\foliage_6",1,1,20};
		soundHitFoliage7[] = {"dz\sounds\weapons\hits\bullet\foliage_7",1,1,20};
		soundHitFoliage8[] = {"dz\sounds\weapons\hits\bullet\foliage_8",1,1,20};
		soundPlastic1[] = {"dz\sounds\weapons\hits\bullet\plastic_1",0.5,1,40};
		soundPlastic2[] = {"dz\sounds\weapons\hits\bullet\plastic_2",0.5,1,40};
		soundPlastic3[] = {"dz\sounds\weapons\hits\bullet\plastic_3",0.5,1,40};
		soundPlastic4[] = {"dz\sounds\weapons\hits\bullet\plastic_4",0.5,1,40};
		soundPlastic5[] = {"dz\sounds\weapons\hits\bullet\plastic_5",0.5,1,40};
		soundPlastic6[] = {"dz\sounds\weapons\hits\bullet\plastic_6",0.5,1,40};
		soundPlastic7[] = {"dz\sounds\weapons\hits\bullet\plastic_7",0.5,1,40};
		soundPlastic8[] = {"dz\sounds\weapons\hits\bullet\plastic_8",0.5,1,40};
		soundConcrete1[] = {"dz\sounds\weapons\hits\bullet\concrete_1",0.5,1,40};
		soundConcrete2[] = {"dz\sounds\weapons\hits\bullet\concrete_2",0.5,1,40};
		soundConcrete3[] = {"dz\sounds\weapons\hits\bullet\concrete_3",0.5,1,40};
		soundConcrete4[] = {"dz\sounds\weapons\hits\bullet\concrete_4",0.5,1,40};
		soundConcrete5[] = {"dz\sounds\weapons\hits\bullet\concrete_5",0.5,1,40};
		soundConcrete6[] = {"dz\sounds\weapons\hits\bullet\concrete_6",0.5,1,40};
		soundConcrete7[] = {"dz\sounds\weapons\hits\bullet\concrete_7",0.5,1,40};
		soundConcrete8[] = {"dz\sounds\weapons\hits\bullet\concrete_8",0.5,1,40};
		soundRubber1[] = {"dz\sounds\weapons\hits\bullet\tyre_1",0.5,1,40};
		soundRubber2[] = {"dz\sounds\weapons\hits\bullet\tyre_2",0.5,1,40};
		soundRubber3[] = {"dz\sounds\weapons\hits\bullet\tyre_3",0.5,1,40};
		soundRubber4[] = {"dz\sounds\weapons\hits\bullet\tyre_4",0.5,1,40};
		soundRubber5[] = {"dz\sounds\weapons\hits\bullet\tyre_5",0.5,1,40};
		soundRubber6[] = {"dz\sounds\weapons\hits\bullet\tyre_6",0.5,1,40};
		soundRubber7[] = {"dz\sounds\weapons\hits\bullet\tyre_7",0.5,1,40};
		soundRubber8[] = {"dz\sounds\weapons\hits\bullet\tyre_8",0.5,1,40};
		soundWater1[] = {"dz\sounds\weapons\hits\bullet\water_1",0.5,1,40};
		soundWater2[] = {"dz\sounds\weapons\hits\bullet\water_2",0.5,1,40};
		soundWater3[] = {"dz\sounds\weapons\hits\bullet\water_3",0.5,1,40};
		soundWater4[] = {"dz\sounds\weapons\hits\bullet\water_4",0.5,1,40};
		soundWater5[] = {"dz\sounds\weapons\hits\bullet\water_5",0.5,1,40};
		soundWater6[] = {"dz\sounds\weapons\hits\bullet\water_6",0.5,1,40};
		soundWater7[] = {"dz\sounds\weapons\hits\bullet\water_7",0.5,1,40};
		soundWater8[] = {"dz\sounds\weapons\hits\bullet\water_8",0.5,1,40};
		hitGroundSoft[] = {"soundGroundSoft1",0.125,"soundGroundSoft2",0.125,"soundGroundSoft3",0.125,"soundGroundSoft4",0.125,"soundGroundSoft5",0.125,"soundGroundSoft6",0.125,"soundGroundSoft7",0.125,"soundGroundSoft8",0.125};
		hitGroundHard[] = {"soundGroundHard1",0.125,"soundGroundHard2",0.125,"soundGroundHard3",0.125,"soundGroundHard4",0.125,"soundGroundHard5",0.125,"soundGroundHard6",0.125,"soundGroundHard7",0.125,"soundGroundHard8",0.125};
		hitMan[] = {"soundHitBody1",0.125,"soundHitBody2",0.125,"soundHitBody3",0.125,"soundHitBody4",0.125,"soundHitBody5",0.125,"soundHitBody6",0.125,"soundHitBody7",0.125,"soundHitBody8",0.125};
		hitArmor[] = {"soundVehiclePlate1",0.125,"soundVehiclePlate2",0.125,"soundVehiclePlate3",0.125,"soundVehiclePlate4",0.125,"soundVehiclePlate5",0.125,"soundVehiclePlate6",0.125,"soundVehiclePlate7",0.125,"soundVehiclePlate8",0.125};
		hitBuilding[] = {"soundHitBuilding1",0.125,"soundHitBuilding2",0.125,"soundHitBuilding3",0.125,"soundHitBuilding4",0.125,"soundHitBuilding5",0.125,"soundHitBuilding6",0.125,"soundHitBuilding7",0.125,"soundHitBuilding8",0.125};
		hitFoliage[] = {"soundHitFoliage1",0.125,"soundHitFoliage2",0.125,"soundHitFoliage3",0.125,"soundHitFoliage4",0.125,"soundHitFoliage5",0.125,"soundHitFoliage6",0.125,"soundHitFoliage7",0.125,"soundHitFoliage8",0.125};
		hitWood[] = {"soundWood1",0.125,"soundWood2",0.125,"soundWood3",0.125,"soundWood4",0.125,"soundWood5",0.125,"soundWood6",0.125,"soundWood7",0.125,"soundWood8",0.125};
		hitGlass[] = {"soundGlass1",0.125,"soundGlass2",0.125,"soundGlass3",0.125,"soundGlass4",0.125,"soundGlass5",0.125,"soundGlass6",0.125,"soundGlass7",0.125,"soundGlass8",0.125};
		hitGlassArmored[] = {"soundGlassArmored1",0.125,"soundGlassArmored2",0.125,"soundGlassArmored3",0.125,"soundGlassArmored4",0.125,"soundGlassArmored5",0.125,"soundGlassArmored6",0.125,"soundGlassArmored7",0.125,"soundGlassArmored8",0.125};
		hitConcrete[] = {"soundConcrete1",0.125,"soundConcrete2",0.125,"soundConcrete3",0.125,"soundConcrete4",0.125,"soundConcrete5",0.125,"soundConcrete6",0.125,"soundConcrete7",0.125,"soundConcrete8",0.125};
		hitRubber[] = {"soundRubber1",0.25,"soundRubber2",0.25,"soundRubber3",0.25,"soundRubber4",0.25};
		hitPlastic[] = {"soundPlastic1",0.125,"soundPlastic2",0.125,"soundPlastic3",0.125,"soundPlastic4",0.125,"soundPlastic5",0.125,"soundPlastic6",0.125,"soundPlastic7",0.125,"soundPlastic8",0.125};
		hitDefault[] = {"soundDefault1",0.125,"soundDefault2",0.125,"soundDefault3",0.125,"soundDefault4",0.125,"soundDefault5",0.125,"soundDefault6",0.125,"soundDefault7",0.125,"soundDefault8",0.125};
		hitMetal[] = {"soundMetal1",0.125,"soundMetal2",0.125,"soundMetal3",0.125,"soundMetal4",0.125,"soundMetal5",0.125,"soundMetal6",0.125,"soundMetal7",0.125,"soundMetal8",0.125};
		hitMetalplate[] = {"soundVehiclePlate1",0.125,"soundVehiclePlate2",0.125,"soundVehiclePlate3",0.125,"soundVehiclePlate4",0.125,"soundVehiclePlate5",0.125,"soundVehiclePlate6",0.125,"soundVehiclePlate7",0.125,"soundVehiclePlate8",0.125};
		hitWater[] = {"soundWater1",0.125,"soundWater2",0.125,"soundWater3",0.125,"soundWater4",0.125,"soundWater5",0.125,"soundWater6",0.125,"soundWater7",0.125,"soundWater8",0.125};
		soundSetBulletFly[] = {"bulletFlyBy_SoundSet"};
		soundSetSuperSonic[] = {"SuperSonicCrack_SoundSet","SuperSonicCrackTail_SoundSet"};
		class SoundSetsGroundHits
		{
			default[] = {"Shell_39mm_default_SoundSet"};
			asphalt_ext[] = {"Shell_39mm_default_SoundSet"};
			asphalt_destroyed_ext[] = {"Shell_39mm_default_SoundSet"};
			asphalt_int[] = {"Shell_39mm_default_int_SoundSet"};
			asphalt_destroyed_int[] = {"Shell_39mm_default_int_SoundSet"};
			asphalt_felt[] = {"Shell_39mm_default_SoundSet"};
			asphalt_felt_int[] = {"Shell_39mm_default_int_SoundSet"};
			cp_broadleaf_dense1[] = {"Shell_39mm_leaves_SoundSet"};
			cp_broadleaf_dense2[] = {"Shell_39mm_leaves_SoundSet"};
			cp_broadleaf_sparse1[] = {"Shell_39mm_leaves_SoundSet"};
			cp_broadleaf_sparse2[] = {"Shell_39mm_leaves_SoundSet"};
			cp_conifer_common1[] = {"Shell_39mm_leaves_SoundSet"};
			cp_conifer_common2[] = {"Shell_39mm_leaves_SoundSet"};
			cp_conifer_moss1[] = {"Shell_39mm_leaves_SoundSet"};
			cp_conifer_moss2[] = {"Shell_39mm_leaves_SoundSet"};
			cp_concrete1[] = {"Shell_39mm_default_SoundSet"};
			cp_concrete2[] = {"Shell_39mm_default_SoundSet"};
			concrete_ext[] = {"Shell_39mm_default_SoundSet"};
			concrete_stairs_ext[] = {"Shell_39mm_default_SoundSet"};
			concrete_int[] = {"Shell_39mm_default_int_SoundSet"};
			concrete_stairs[] = {"Shell_39mm_default_SoundSet"};
			ceramic_tiles_ext[] = {"Shell_39mm_default_SoundSet"};
			ceramic_tiles_int[] = {"Shell_39mm_default_int_SoundSet"};
			ceramic_tiles_roof_ext[] = {"Shell_39mm_default_SoundSet"};
			ceramic_tiles_roof_int[] = {"Shell_39mm_default_int_SoundSet"};
			cp_dirt[] = {"Shell_39mm_dirt_SoundSet"};
			dirt_ext[] = {"Shell_39mm_dirt_SoundSet"};
			dirt_int[] = {"Shell_39mm_dirt_int_SoundSet"};
			cp_grass[] = {"Shell_39mm_grass_SoundSet"};
			grass_dry_ext[] = {"Shell_39mm_grass_SoundSet"};
			grass_dry_int[] = {"Shell_39mm_grass_int_SoundSet"};
			cp_grass_tall[] = {"Shell_39mm_grass_SoundSet"};
			cp_gravel[] = {"Shell_39mm_gravel_SoundSet"};
			gravel_small_ext[] = {"Shell_39mm_gravel_SoundSet"};
			gravel_small_int[] = {"Shell_39mm_gravel_int_SoundSet"};
			gravel_large_ext[] = {"Shell_39mm_gravel_SoundSet"};
			gravel_large_int[] = {"Shell_39mm_gravel_int_SoundSet"};
			lino_ext[] = {"Shell_39mm_default_SoundSet"};
			lino_int[] = {"Shell_39mm_default_int_SoundSet"};
			metal_thick_ext[] = {"Shell_39mm_metal_SoundSet"};
			metal_stairs_ext[] = {"Shell_39mm_metal_SoundSet"};
			metal_thick_int[] = {"Shell_39mm_metal_int_SoundSet"};
			metal_thin_ext[] = {"Shell_39mm_metal_SoundSet"};
			metal_thin_int[] = {"Shell_39mm_metal_int_SoundSet"};
			metal_thin_mesh_ext[] = {"Shell_39mm_metal_SoundSet"};
			metal_thin_mesh_int[] = {"Shell_39mm_metal_int_SoundSet"};
			cp_rock[] = {"Shell_39mm_default_SoundSet"};
			rubble_large_ext[] = {"Shell_39mm_gravel_SoundSet"};
			rubble_large_int[] = {"Shell_39mm_gravel_int_SoundSet"};
			rubble_small_ext[] = {"Shell_39mm_gravel_SoundSet"};
			rubble_small_int[] = {"Shell_39mm_gravel_int_SoundSet"};
			sand_ext[] = {"Shell_39mm_sand_SoundSet"};
			sand_int[] = {"Shell_39mm_sand_int_SoundSet"};
			stone_ext[] = {"Shell_39mm_sand_SoundSet"};
			stone_int[] = {"Shell_39mm_sand_int_SoundSet"};
			textile_carpet_ext[] = {"Shell_39mm_carpet_SoundSet"};
			textile_carpet_int[] = {"Shell_39mm_carpet_int_SoundSet"};
			trash_ext[] = {"Shell_39mm_default_SoundSet"};
			trash_int[] = {"Shell_39mm_default_int_SoundSet"};
			wood_parquet_ext[] = {"Shell_39mm_wood_SoundSet"};
			wood_parquet_int[] = {"Shell_39mm_wood_int_SoundSet"};
			wood_planks_ext[] = {"Shell_39mm_wood_SoundSet"};
			wood_planks_stairs_ext[] = {"Shell_39mm_wood_SoundSet"};
			wood_planks_int[] = {"Shell_39mm_wood_int_SoundSet"};
			wood_planks_stairs_int[] = {"Shell_39mm_wood_int_SoundSet"};
			fresh_water_ext[] = {"Shell_39mm_water_SoundSet"};
			fresh_water_int[] = {"Shell_39mm_water_int_SoundSet"};
			water[] = {"Shell_39mm_water_SoundSet"};
		};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		casing = "FxCartridge_556";
		round = "FxRound_556";
		timeToLive = 6;
		deflecting = 10;
		tracerStartTime = -1;
		muzzleEffect = "BIS_Effects_Rifle";
		maxLeadSpeed = 23;
		typicalSpeed = 900;
		initSpeed = 900;
		weight = 0.015;
		impactBehaviour = 0;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 99;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class Shotgun_Base: ShotgunCore
	{
		scope = 0;
		model = "\dz\weapons\projectiles\empty.p3d";
		waterEffectOffset = -0.8;
		soundDefault1[] = {"dz\sounds\weapons\hits\bullet\soft_ground_1",0.5,1,40};
		soundDefault2[] = {"dz\sounds\weapons\hits\bullet\soft_ground_2",0.5,1,40};
		soundDefault3[] = {"dz\sounds\weapons\hits\bullet\soft_ground_3",0.5,1,40};
		soundDefault4[] = {"dz\sounds\weapons\hits\bullet\soft_ground_4",0.5,1,40};
		soundDefault5[] = {"dz\sounds\weapons\hits\bullet\soft_ground_5",0.5,1,40};
		soundDefault6[] = {"dz\sounds\weapons\hits\bullet\soft_ground_6",0.5,1,40};
		soundDefault7[] = {"dz\sounds\weapons\hits\bullet\soft_ground_7",0.5,1,40};
		soundDefault8[] = {"dz\sounds\weapons\hits\bullet\soft_ground_8",0.5,1,40};
		soundGroundSoft1[] = {"dz\sounds\weapons\hits\bullet\soft_ground_1",0.5,1,40};
		soundGroundSoft2[] = {"dz\sounds\weapons\hits\bullet\soft_ground_2",0.5,1,40};
		soundGroundSoft3[] = {"dz\sounds\weapons\hits\bullet\soft_ground_3",0.5,1,40};
		soundGroundSoft4[] = {"dz\sounds\weapons\hits\bullet\soft_ground_4",0.5,1,40};
		soundGroundSoft5[] = {"dz\sounds\weapons\hits\bullet\soft_ground_5",0.5,1,40};
		soundGroundSoft6[] = {"dz\sounds\weapons\hits\bullet\soft_ground_6",0.5,1,40};
		soundGroundSoft7[] = {"dz\sounds\weapons\hits\bullet\soft_ground_7",0.5,1,40};
		soundGroundSoft8[] = {"dz\sounds\weapons\hits\bullet\soft_ground_8",0.5,1,40};
		soundGroundHard1[] = {"dz\sounds\weapons\hits\bullet\hard_ground_1",0.5,1,40};
		soundGroundHard2[] = {"dz\sounds\weapons\hits\bullet\hard_ground_2",0.5,1,40};
		soundGroundHard3[] = {"dz\sounds\weapons\hits\bullet\hard_ground_3",0.5,1,40};
		soundGroundHard4[] = {"dz\sounds\weapons\hits\bullet\hard_ground_4",0.5,1,40};
		soundGroundHard5[] = {"dz\sounds\weapons\hits\bullet\hard_ground_5",0.5,1,40};
		soundGroundHard6[] = {"dz\sounds\weapons\hits\bullet\hard_ground_6",0.5,1,40};
		soundGroundHard7[] = {"dz\sounds\weapons\hits\bullet\hard_ground_7",0.5,1,40};
		soundGroundHard8[] = {"dz\sounds\weapons\hits\bullet\hard_ground_8",0.5,1,40};
		soundMetal1[] = {"dz\sounds\weapons\hits\bullet\metal_1",0.5,1,40};
		soundMetal2[] = {"dz\sounds\weapons\hits\bullet\metal_2",0.5,1,40};
		soundMetal3[] = {"dz\sounds\weapons\hits\bullet\metal_3",0.5,1,40};
		soundMetal4[] = {"dz\sounds\weapons\hits\bullet\metal_4",0.5,1,40};
		soundMetal5[] = {"dz\sounds\weapons\hits\bullet\metal_5",0.5,1,40};
		soundMetal6[] = {"dz\sounds\weapons\hits\bullet\metal_6",0.5,1,40};
		soundMetal7[] = {"dz\sounds\weapons\hits\bullet\metal_7",0.5,1,40};
		soundMetal8[] = {"dz\sounds\weapons\hits\bullet\metal_8",0.5,1,40};
		soundGlass1[] = {"dz\sounds\weapons\hits\bullet\glass_1",0.5,1,40};
		soundGlass2[] = {"dz\sounds\weapons\hits\bullet\glass_2",0.5,1,40};
		soundGlass3[] = {"dz\sounds\weapons\hits\bullet\glass_3",0.5,1,40};
		soundGlass4[] = {"dz\sounds\weapons\hits\bullet\glass_4",0.5,1,40};
		soundGlass5[] = {"dz\sounds\weapons\hits\bullet\glass_5",0.5,1,40};
		soundGlass6[] = {"dz\sounds\weapons\hits\bullet\glass_6",0.5,1,40};
		soundGlass7[] = {"dz\sounds\weapons\hits\bullet\glass_7",0.5,1,40};
		soundGlass8[] = {"dz\sounds\weapons\hits\bullet\glass_8",0.5,1,40};
		soundGlassArmored1[] = {"dz\sounds\weapons\hits\bullet\glass_arm_1",0.5,1,40};
		soundGlassArmored2[] = {"dz\sounds\weapons\hits\bullet\glass_arm_2",0.5,1,40};
		soundGlassArmored3[] = {"dz\sounds\weapons\hits\bullet\glass_arm_3",0.5,1,40};
		soundGlassArmored4[] = {"dz\sounds\weapons\hits\bullet\glass_arm_4",0.5,1,40};
		soundGlassArmored5[] = {"dz\sounds\weapons\hits\bullet\glass_arm_5",0.5,1,40};
		soundGlassArmored6[] = {"dz\sounds\weapons\hits\bullet\glass_arm_6",0.5,1,40};
		soundGlassArmored7[] = {"dz\sounds\weapons\hits\bullet\glass_arm_7",0.5,1,40};
		soundGlassArmored8[] = {"dz\sounds\weapons\hits\bullet\glass_arm_8",0.5,1,40};
		soundVehiclePlate1[] = {"dz\sounds\weapons\hits\bullet\metal_plate_1",0.5,1,40};
		soundVehiclePlate2[] = {"dz\sounds\weapons\hits\bullet\metal_plate_2",0.5,1,40};
		soundVehiclePlate3[] = {"dz\sounds\weapons\hits\bullet\metal_plate_3",0.5,1,40};
		soundVehiclePlate4[] = {"dz\sounds\weapons\hits\bullet\metal_plate_4",0.5,1,40};
		soundVehiclePlate5[] = {"dz\sounds\weapons\hits\bullet\metal_plate_5",0.5,1,40};
		soundVehiclePlate6[] = {"dz\sounds\weapons\hits\bullet\metal_plate_6",0.5,1,40};
		soundVehiclePlate7[] = {"dz\sounds\weapons\hits\bullet\metal_plate_7",0.5,1,40};
		soundVehiclePlate8[] = {"dz\sounds\weapons\hits\bullet\metal_plate_8",0.5,1,40};
		soundWood1[] = {"dz\sounds\weapons\hits\bullet\wood_1",0.5,1,40};
		soundWood2[] = {"dz\sounds\weapons\hits\bullet\wood_2",0.5,1,40};
		soundWood3[] = {"dz\sounds\weapons\hits\bullet\wood_3",0.5,1,40};
		soundWood4[] = {"dz\sounds\weapons\hits\bullet\wood_4",0.5,1,40};
		soundWood5[] = {"dz\sounds\weapons\hits\bullet\wood_5",0.5,1,40};
		soundWood6[] = {"dz\sounds\weapons\hits\bullet\wood_6",0.5,1,40};
		soundWood7[] = {"dz\sounds\weapons\hits\bullet\wood_7",0.5,1,40};
		soundWood8[] = {"dz\sounds\weapons\hits\bullet\wood_8",0.5,1,40};
		soundHitBody1[] = {"dz\sounds\weapons\hits\bullet\body_1",1,1,20};
		soundHitBody2[] = {"dz\sounds\weapons\hits\bullet\body_2",1,1,20};
		soundHitBody3[] = {"dz\sounds\weapons\hits\bullet\body_3",1,1,20};
		soundHitBody4[] = {"dz\sounds\weapons\hits\bullet\body_4",1,1,20};
		soundHitBody5[] = {"dz\sounds\weapons\hits\bullet\body_5",1,1,20};
		soundHitBody6[] = {"dz\sounds\weapons\hits\bullet\body_6",1,1,20};
		soundHitBody7[] = {"dz\sounds\weapons\hits\bullet\body_7",1,1,20};
		soundHitBody8[] = {"dz\sounds\weapons\hits\bullet\body_8",1,1,20};
		soundHitBuilding1[] = {"dz\sounds\weapons\hits\bullet\building_1",0.5,1,40};
		soundHitBuilding2[] = {"dz\sounds\weapons\hits\bullet\building_2",0.5,1,40};
		soundHitBuilding3[] = {"dz\sounds\weapons\hits\bullet\building_3",0.5,1,40};
		soundHitBuilding4[] = {"dz\sounds\weapons\hits\bullet\building_4",0.5,1,40};
		soundHitBuilding5[] = {"dz\sounds\weapons\hits\bullet\building_5",0.5,1,40};
		soundHitBuilding6[] = {"dz\sounds\weapons\hits\bullet\building_6",0.5,1,40};
		soundHitBuilding7[] = {"dz\sounds\weapons\hits\bullet\building_7",0.5,1,40};
		soundHitBuilding8[] = {"dz\sounds\weapons\hits\bullet\building_8",0.5,1,40};
		soundHitFoliage1[] = {"dz\sounds\weapons\hits\bullet\foliage_1",1,1,20};
		soundHitFoliage2[] = {"dz\sounds\weapons\hits\bullet\foliage_2",1,1,20};
		soundHitFoliage3[] = {"dz\sounds\weapons\hits\bullet\foliage_3",1,1,20};
		soundHitFoliage4[] = {"dz\sounds\weapons\hits\bullet\foliage_4",1,1,20};
		soundHitFoliage5[] = {"dz\sounds\weapons\hits\bullet\foliage_5",1,1,20};
		soundHitFoliage6[] = {"dz\sounds\weapons\hits\bullet\foliage_6",1,1,20};
		soundHitFoliage7[] = {"dz\sounds\weapons\hits\bullet\foliage_7",1,1,20};
		soundHitFoliage8[] = {"dz\sounds\weapons\hits\bullet\foliage_8",1,1,20};
		soundPlastic1[] = {"dz\sounds\weapons\hits\bullet\plastic_1",0.5,1,40};
		soundPlastic2[] = {"dz\sounds\weapons\hits\bullet\plastic_2",0.5,1,40};
		soundPlastic3[] = {"dz\sounds\weapons\hits\bullet\plastic_3",0.5,1,40};
		soundPlastic4[] = {"dz\sounds\weapons\hits\bullet\plastic_4",0.5,1,40};
		soundPlastic5[] = {"dz\sounds\weapons\hits\bullet\plastic_5",0.5,1,40};
		soundPlastic6[] = {"dz\sounds\weapons\hits\bullet\plastic_6",0.5,1,40};
		soundPlastic7[] = {"dz\sounds\weapons\hits\bullet\plastic_7",0.5,1,40};
		soundPlastic8[] = {"dz\sounds\weapons\hits\bullet\plastic_8",0.5,1,40};
		soundConcrete1[] = {"dz\sounds\weapons\hits\bullet\concrete_1",0.5,1,40};
		soundConcrete2[] = {"dz\sounds\weapons\hits\bullet\concrete_2",0.5,1,40};
		soundConcrete3[] = {"dz\sounds\weapons\hits\bullet\concrete_3",0.5,1,40};
		soundConcrete4[] = {"dz\sounds\weapons\hits\bullet\concrete_4",0.5,1,40};
		soundConcrete5[] = {"dz\sounds\weapons\hits\bullet\concrete_5",0.5,1,40};
		soundConcrete6[] = {"dz\sounds\weapons\hits\bullet\concrete_6",0.5,1,40};
		soundConcrete7[] = {"dz\sounds\weapons\hits\bullet\concrete_7",0.5,1,40};
		soundConcrete8[] = {"dz\sounds\weapons\hits\bullet\concrete_8",0.5,1,40};
		soundRubber1[] = {"dz\sounds\weapons\hits\bullet\tyre_1",0.5,1,40};
		soundRubber2[] = {"dz\sounds\weapons\hits\bullet\tyre_2",0.5,1,40};
		soundRubber3[] = {"dz\sounds\weapons\hits\bullet\tyre_3",0.5,1,40};
		soundRubber4[] = {"dz\sounds\weapons\hits\bullet\tyre_4",0.5,1,40};
		soundRubber5[] = {"dz\sounds\weapons\hits\bullet\tyre_5",0.5,1,40};
		soundRubber6[] = {"dz\sounds\weapons\hits\bullet\tyre_6",0.5,1,40};
		soundRubber7[] = {"dz\sounds\weapons\hits\bullet\tyre_7",0.5,1,40};
		soundRubber8[] = {"dz\sounds\weapons\hits\bullet\tyre_8",0.5,1,40};
		soundWater1[] = {"dz\sounds\weapons\hits\bullet\water_1",0.5,1,40};
		soundWater2[] = {"dz\sounds\weapons\hits\bullet\water_2",0.5,1,40};
		soundWater3[] = {"dz\sounds\weapons\hits\bullet\water_3",0.5,1,40};
		soundWater4[] = {"dz\sounds\weapons\hits\bullet\water_4",0.5,1,40};
		soundWater5[] = {"dz\sounds\weapons\hits\bullet\water_5",0.5,1,40};
		soundWater6[] = {"dz\sounds\weapons\hits\bullet\water_6",0.5,1,40};
		soundWater7[] = {"dz\sounds\weapons\hits\bullet\water_7",0.5,1,40};
		soundWater8[] = {"dz\sounds\weapons\hits\bullet\water_8",0.5,1,40};
		hitGroundSoft[] = {"soundGroundSoft1",0.125,"soundGroundSoft2",0.125,"soundGroundSoft3",0.125,"soundGroundSoft4",0.125,"soundGroundSoft5",0.125,"soundGroundSoft6",0.125,"soundGroundSoft7",0.125,"soundGroundSoft8",0.125};
		hitGroundHard[] = {"soundGroundHard1",0.125,"soundGroundHard2",0.125,"soundGroundHard3",0.125,"soundGroundHard4",0.125,"soundGroundHard5",0.125,"soundGroundHard6",0.125,"soundGroundHard7",0.125,"soundGroundHard8",0.125};
		hitMan[] = {"soundHitBody1",0.125,"soundHitBody2",0.125,"soundHitBody3",0.125,"soundHitBody4",0.125,"soundHitBody5",0.125,"soundHitBody6",0.125,"soundHitBody7",0.125,"soundHitBody8",0.125};
		hitArmor[] = {"soundVehiclePlate1",0.125,"soundVehiclePlate2",0.125,"soundVehiclePlate3",0.125,"soundVehiclePlate4",0.125,"soundVehiclePlate5",0.125,"soundVehiclePlate6",0.125,"soundVehiclePlate7",0.125,"soundVehiclePlate8",0.125};
		hitBuilding[] = {"soundHitBuilding1",0.125,"soundHitBuilding2",0.125,"soundHitBuilding3",0.125,"soundHitBuilding4",0.125,"soundHitBuilding5",0.125,"soundHitBuilding6",0.125,"soundHitBuilding7",0.125,"soundHitBuilding8",0.125};
		hitFoliage[] = {"soundHitFoliage1",0.125,"soundHitFoliage2",0.125,"soundHitFoliage3",0.125,"soundHitFoliage4",0.125,"soundHitFoliage5",0.125,"soundHitFoliage6",0.125,"soundHitFoliage7",0.125,"soundHitFoliage8",0.125};
		hitWood[] = {"soundWood1",0.125,"soundWood2",0.125,"soundWood3",0.125,"soundWood4",0.125,"soundWood5",0.125,"soundWood6",0.125,"soundWood7",0.125,"soundWood8",0.125};
		hitGlass[] = {"soundGlass1",0.125,"soundGlass2",0.125,"soundGlass3",0.125,"soundGlass4",0.125,"soundGlass5",0.125,"soundGlass6",0.125,"soundGlass7",0.125,"soundGlass8",0.125};
		hitGlassArmored[] = {"soundGlassArmored1",0.125,"soundGlassArmored2",0.125,"soundGlassArmored3",0.125,"soundGlassArmored4",0.125,"soundGlassArmored5",0.125,"soundGlassArmored6",0.125,"soundGlassArmored7",0.125,"soundGlassArmored8",0.125};
		hitConcrete[] = {"soundConcrete1",0.125,"soundConcrete2",0.125,"soundConcrete3",0.125,"soundConcrete4",0.125,"soundConcrete5",0.125,"soundConcrete6",0.125,"soundConcrete7",0.125,"soundConcrete8",0.125};
		hitRubber[] = {"soundRubber1",0.25,"soundRubber2",0.25,"soundRubber3",0.25,"soundRubber4",0.25};
		hitPlastic[] = {"soundPlastic1",0.125,"soundPlastic2",0.125,"soundPlastic3",0.125,"soundPlastic4",0.125,"soundPlastic5",0.125,"soundPlastic6",0.125,"soundPlastic7",0.125,"soundPlastic8",0.125};
		hitDefault[] = {"soundDefault1",0.125,"soundDefault2",0.125,"soundDefault3",0.125,"soundDefault4",0.125,"soundDefault5",0.125,"soundDefault6",0.125,"soundDefault7",0.125,"soundDefault8",0.125};
		hitMetal[] = {"soundMetal1",0.125,"soundMetal2",0.125,"soundMetal3",0.125,"soundMetal4",0.125,"soundMetal5",0.125,"soundMetal6",0.125,"soundMetal7",0.125,"soundMetal8",0.125};
		hitMetalplate[] = {"soundVehiclePlate1",0.125,"soundVehiclePlate2",0.125,"soundVehiclePlate3",0.125,"soundVehiclePlate4",0.125,"soundVehiclePlate5",0.125,"soundVehiclePlate6",0.125,"soundVehiclePlate7",0.125,"soundVehiclePlate8",0.125};
		hitWater[] = {"soundWater1",0.125,"soundWater2",0.125,"soundWater3",0.125,"soundWater4",0.125,"soundWater5",0.125,"soundWater6",0.125,"soundWater7",0.125,"soundWater8",0.125};
		soundSetBulletFly[] = {"bulletFlyBy_SoundSet"};
		impactBehaviour = 1;
		class SoundSetsGroundHits
		{
			default[] = {"Shell_12ga_default_SoundSet"};
			asphalt_ext[] = {"Shell_12ga_default_SoundSet"};
			asphalt_destroyed_ext[] = {"Shell_12ga_default_SoundSet"};
			asphalt_int[] = {"Shell_12ga_default_int_SoundSet"};
			asphalt_destroyed_int[] = {"Shell_12ga_default_int_SoundSet"};
			asphalt_felt[] = {"Shell_12ga_default_SoundSet"};
			asphalt_felt_int[] = {"Shell_12ga_default_int_SoundSet"};
			cp_broadleaf_dense1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_broadleaf_dense2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_broadleaf_sparse1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_broadleaf_sparse2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_common1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_common2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_moss1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_moss2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_concrete1[] = {"Shell_12ga_default_SoundSet"};
			cp_concrete2[] = {"Shell_12ga_default_SoundSet"};
			concrete_ext[] = {"Shell_12ga_default_SoundSet"};
			concrete_stairs_ext[] = {"Shell_12ga_default_SoundSet"};
			concrete_int[] = {"Shell_12ga_default_int_SoundSet"};
			concrete_stairs[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_ext[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_int[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_roof_ext[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_roof_int[] = {"Shell_12ga_default_SoundSet"};
			cp_dirt[] = {"Shell_12ga_dirt_SoundSet"};
			dirt_ext[] = {"Shell_12ga_dirt_SoundSet"};
			dirt_int[] = {"Shell_12ga_dirt_int_SoundSet"};
			cp_grass[] = {"Shell_12ga_grass_SoundSet"};
			grass_dry_ext[] = {"Shell_12ga_grass_SoundSet"};
			grass_dry_int[] = {"Shell_12ga_grass_int_SoundSet"};
			cp_grass_tall[] = {"Shell_12ga_grass_SoundSet"};
			cp_gravel[] = {"Shell_12ga_gravel_SoundSet"};
			gravel_small_ext[] = {"Shell_12ga_gravel_SoundSet"};
			gravel_small_int[] = {"Shell_12ga_gravel_int_SoundSet"};
			gravel_large_ext[] = {"Shell_12ga_gravel_SoundSet"};
			gravel_large_int[] = {"Shell_12ga_gravel_int_SoundSet"};
			lino_ext[] = {"Shell_12ga_default_SoundSet"};
			lino_int[] = {"Shell_12ga_default_SoundSet"};
			metal_thick_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_stairs_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_thick_int[] = {"Shell_12ga_metal_int_SoundSet"};
			metal_thin_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_thin_int[] = {"Shell_12ga_metal_int_SoundSet"};
			metal_thin_mesh_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_thin_mesh_int[] = {"Shell_12ga_metal_int_SoundSet"};
			cp_rock[] = {"Shell_12ga_default_SoundSet"};
			rubble_large_ext[] = {"Shell_12ga_gravel_SoundSet"};
			rubble_large_int[] = {"Shell_12ga_gravel_SoundSet"};
			rubble_small_ext[] = {"Shell_12ga_gravel_SoundSet"};
			rubble_small_int[] = {"Shell_12ga_gravel_SoundSet"};
			sand_ext[] = {"Shell_12ga_sand_SoundSet"};
			sand_int[] = {"Shell_12ga_sand_int_SoundSet"};
			stone_ext[] = {"Shell_12ga_sand_SoundSet"};
			stone_int[] = {"Shell_12ga_sand_int_SoundSet"};
			textile_carpet_ext[] = {"Shell_12ga_carpet_SoundSet"};
			textile_carpet_int[] = {"Shell_12ga_carpet_int_SoundSet"};
			trash_ext[] = {"Shell_12ga_default_SoundSet"};
			trash_int[] = {"Shell_12ga_default_SoundSet"};
			wood_parquet_ext[] = {"Shell_12ga_wood_SoundSet"};
			wood_parquet_int[] = {"Shell_12ga_wood_int_SoundSet"};
			wood_planks_ext[] = {"Shell_12ga_wood_SoundSet"};
			wood_planks_stairs_ext[] = {"Shell_12ga_wood_SoundSet"};
			wood_planks_int[] = {"Shell_12ga_wood_int_SoundSet"};
			wood_planks_stairs_int[] = {"Shell_12ga_wood_int_SoundSet"};
			fresh_water_ext[] = {"Shell_12ga_water_SoundSet"};
			fresh_water_int[] = {"Shell_12ga_water_int_SoundSet"};
			water_int[] = {"Shell_12ga_water_int_SoundSet"};
			water[] = {"Shell_12ga_water_int_SoundSet"};
		};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 99;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
				};
			};
		};
	};
	class Bullet_12GaugePellets: Shotgun_Base
	{
		scope = 2;
		proxyShape = "\dz\weapons\projectiles\shotgunshell_pellets.p3d";
		casing = "FxCartridge_12Pellet";
		round = "FxRound_12Pellet";
		spawnPileType = "Ammo_12gaPellets";
		hit = 6;
		indirectHit = 0;
		indirectHitRange = 0;
		hitShockHead = 20000;
		hitShock = 400;
		hitBlood = -200;
		hitHealth = -200;
		bleedChance = 2;
		initSpeed = 370;
		typicalSpeed = 370;
		airFriction = -0.00675;
		caliber = 0.5;
		deflecting = 0;
		dispersion = 0.05;
		projectilesCount = 8;
		weight = 0.005;
		impactBehaviour = 1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 34;
				armorDamage = 0.5;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 33;
			};
		};
		class NoiseHit
		{
			strength = 2;
			type = "shot";
		};
	};
	class Bullet_12GaugeSlug: Bullet_Base
	{
		scope = 2;
		proxyShape = "\dz\weapons\projectiles\shotgunshell_slug.p3d";
		casing = "FxCartridge_12Slug";
		round = "FxRound_12Slug";
		spawnPileType = "Ammo_12gaSlug";
		hit = 11;
		indirectHit = 0;
		indirectHitRange = 0;
		initSpeed = 420;
		typicalSpeed = 420;
		airFriction = -0.006;
		caliber = 1;
		deflecting = 0;
		weight = 0.028;
		impactBehaviour = 1;
		class SoundSetsGroundHits
		{
			default[] = {"Shell_12ga_default_SoundSet"};
			asphalt_ext[] = {"Shell_12ga_default_SoundSet"};
			asphalt_destroyed_ext[] = {"Shell_12ga_default_SoundSet"};
			asphalt_int[] = {"Shell_12ga_default_int_SoundSet"};
			asphalt_destroyed_int[] = {"Shell_12ga_default_int_SoundSet"};
			asphalt_felt[] = {"Shell_12ga_default_SoundSet"};
			asphalt_felt_int[] = {"Shell_12ga_default_int_SoundSet"};
			cp_broadleaf_dense1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_broadleaf_dense2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_broadleaf_sparse1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_broadleaf_sparse2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_common1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_common2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_moss1[] = {"Shell_12ga_leaves_SoundSet"};
			cp_conifer_moss2[] = {"Shell_12ga_leaves_SoundSet"};
			cp_concrete1[] = {"Shell_12ga_default_SoundSet"};
			cp_concrete2[] = {"Shell_12ga_default_SoundSet"};
			concrete_ext[] = {"Shell_12ga_default_SoundSet"};
			concrete_stairs_ext[] = {"Shell_12ga_default_SoundSet"};
			concrete_int[] = {"Shell_12ga_default_int_SoundSet"};
			concrete_stairs[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_ext[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_int[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_roof_ext[] = {"Shell_12ga_default_SoundSet"};
			ceramic_tiles_roof_int[] = {"Shell_12ga_default_SoundSet"};
			cp_dirt[] = {"Shell_12ga_dirt_SoundSet"};
			dirt_ext[] = {"Shell_12ga_dirt_SoundSet"};
			dirt_int[] = {"Shell_12ga_dirt_int_SoundSet"};
			cp_grass[] = {"Shell_12ga_grass_SoundSet"};
			grass_dry_ext[] = {"Shell_12ga_grass_SoundSet"};
			grass_dry_int[] = {"Shell_12ga_grass_int_SoundSet"};
			cp_grass_tall[] = {"Shell_12ga_grass_SoundSet"};
			cp_gravel[] = {"Shell_12ga_gravel_SoundSet"};
			gravel_small_ext[] = {"Shell_12ga_gravel_SoundSet"};
			gravel_small_int[] = {"Shell_12ga_gravel_int_SoundSet"};
			gravel_large_ext[] = {"Shell_12ga_gravel_SoundSet"};
			gravel_large_int[] = {"Shell_12ga_gravel_int_SoundSet"};
			lino_ext[] = {"Shell_12ga_default_SoundSet"};
			lino_int[] = {"Shell_12ga_default_SoundSet"};
			metal_thick_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_stairs_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_thick_int[] = {"Shell_12ga_metal_int_SoundSet"};
			metal_thin_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_thin_int[] = {"Shell_12ga_metal_int_SoundSet"};
			metal_thin_mesh_ext[] = {"Shell_12ga_metal_SoundSet"};
			metal_thin_mesh_int[] = {"Shell_12ga_metal_int_SoundSet"};
			cp_rock[] = {"Shell_12ga_default_SoundSet"};
			rubble_large_ext[] = {"Shell_12ga_gravel_SoundSet"};
			rubble_large_int[] = {"Shell_12ga_gravel_SoundSet"};
			rubble_small_ext[] = {"Shell_12ga_gravel_SoundSet"};
			rubble_small_int[] = {"Shell_12ga_gravel_SoundSet"};
			sand_ext[] = {"Shell_12ga_sand_SoundSet"};
			sand_int[] = {"Shell_12ga_sand_int_SoundSet"};
			stone_ext[] = {"Shell_12ga_sand_SoundSet"};
			stone_int[] = {"Shell_12ga_sand_int_SoundSet"};
			textile_carpet_ext[] = {"Shell_12ga_carpet_SoundSet"};
			textile_carpet_int[] = {"Shell_12ga_carpet_int_SoundSet"};
			trash_ext[] = {"Shell_12ga_default_SoundSet"};
			trash_int[] = {"Shell_12ga_default_SoundSet"};
			wood_parquet_ext[] = {"Shell_12ga_wood_SoundSet"};
			wood_parquet_int[] = {"Shell_12ga_wood_int_SoundSet"};
			wood_planks_ext[] = {"Shell_12ga_wood_SoundSet"};
			wood_planks_stairs_ext[] = {"Shell_12ga_wood_SoundSet"};
			wood_planks_int[] = {"Shell_12ga_wood_int_SoundSet"};
			wood_planks_stairs_int[] = {"Shell_12ga_wood_int_SoundSet"};
			fresh_water_ext[] = {"Shell_12ga_water_SoundSet"};
			fresh_water_int[] = {"Shell_12ga_water_int_SoundSet"};
			water_int[] = {"Shell_12ga_water_int_SoundSet"};
			water[] = {"Shell_12ga_water_int_SoundSet"};
		};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 110;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 100;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_556x45: Bullet_Base
	{
		scope = 2;
		muzzleFlashParticle = "weapon_shot_m4a1_01";
		spawnPileType = "Ammo_556x45";
		casing = "FxCartridge_556";
		round = "FxRound_556";
		hit = 8;
		indirectHit = 0;
		indirectHitRange = 0;
		initSpeed = 1000;
		typicalSpeed = 1000;
		airFriction = -0.00105;
		caliber = 0.9;
		deflecting = 10;
		tracerScale = 1;
		tracerStartTime = -1;
		tracerEndTime = 1;
		nvgOnly = 1;
		damageBarrel = 3;
		damageBarrelDestroyed = 30;
		weight = 0.00356;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 55;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 66;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_556x45Tracer: Bullet_556x45
	{
		scope = 2;
		model = "\dz\weapons\projectiles\tracer_red.p3d";
		spawnPileType = "Ammo_556x45Tracer";
		tracerScale = 1.2;
		tracerStartTime = 0.075;
		tracerEndTime = 3;
	};
	class Bullet_545x39: Bullet_Base
	{
		scope = 2;
		spawnPileType = "Ammo_545x39";
		casing = "FxCartridge_556";
		round = "FxRound_556";
		hit = 7.2;
		airFriction = -0.00027;
		typicalSpeed = 880;
		initSpeed = 880;
		caliber = 0.9;
		deflecting = 10;
		weight = 0.00343;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 55;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 66;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_545x39Tracer: Bullet_545x39
	{
		scope = 2;
		model = "\dz\weapons\projectiles\tracer_green.p3d";
		spawnPileType = "Ammo_545x39Tracer";
		tracerScale = 1.2;
		tracerStartTime = 0.075;
		tracerEndTime = 3;
	};
	class Bullet_762x54: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_762";
		round = "FxRound_762";
		spawnPileType = "Ammo_762x54";
		muzzleFlashParticle = "weapon_shot_mp5k_02_boris";
		hit = 12;
		indirectHit = 0;
		indirectHitRange = 0;
		airLock = 1;
		initSpeed = 790;
		typicalSpeed = 790;
		airFriction = -0.0008;
		caliber = 1;
		deflecting = 10;
		damageBarrel = 6;
		damageBarrelDestroyed = 60;
		weight = 0.01;
		impactBehaviour = 1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 110;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 100;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_762x54Tracer: Bullet_762x54
	{
		scope = 2;
		model = "\dz\weapons\projectiles\tracer_green.p3d";
		spawnPileType = "Ammo_762x54Tracer";
		tracerScale = 1.2;
		tracerStartTime = 0.075;
		tracerEndTime = 3;
	};
	class Bullet_308Win: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_762";
		round = "FxRound_308Win";
		spawnPileType = "Ammo_308Win";
		hit = 12;
		indirectHit = 0;
		indirectHitRange = 0;
		airLock = 1;
		typicalSpeed = 740;
		tracerScale = 1.2;
		tracerStartTime = -1;
		tracerEndTime = 1;
		airFriction = -0.00085;
		caliber = 1;
		deflecting = 10;
		damageBarrel = 6;
		damageBarrelDestroyed = 60;
		initSpeed = 740;
		weight = 0.01;
		impactBehaviour = 1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 110;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 100;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_308WinTracer: Bullet_308Win
	{
		scope = 2;
		model = "\dz\weapons\projectiles\tracer_red.p3d";
		spawnPileType = "Ammo_308WinTracer";
		tracerScale = 1.2;
		tracerStartTime = 0.075;
		tracerEndTime = 3;
	};
	class Bullet_762x39: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_762x39";
		round = "FxRound_762x39";
		spawnPileType = "Ammo_762x39";
		hit = 9.5;
		indirectHit = 0;
		indirectHitRange = 0;
		airLock = 1;
		initSpeed = 740;
		typicalSpeed = 740;
		airFriction = -0.00143;
		caliber = 0.9;
		deflecting = 10;
		damageBarrel = 3;
		damageBarrelDestroyed = 30;
		weight = 0.008;
		muzzleFlashParticle = "weapon_shot_akm_01";
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 55;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 66;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_762x39Tracer: Bullet_762x39
	{
		scope = 2;
		model = "\dz\weapons\projectiles\tracer_green.p3d";
		spawnPileType = "Ammo_762x39Tracer";
		tracerScale = 1.2;
		tracerStartTime = 0.075;
		tracerEndTime = 3;
	};
	class Bullet_45ACP: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_9mm";
		round = "FxRound_9mm";
		spawnPileType = "Ammo_45ACP";
		muzzleFlashParticle = "weapon_shot_mp5k_02_boris";
		hit = 0;
		indirectHit = 0;
		indirectHitRange = 0;
		tracerScale = 1;
		caliber = 0.9;
		deflecting = 30;
		initSpeed = 260;
		typicalSpeed = 260;
		airFriction = -0.00145;
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		weight = 0.0149;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 34;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 33;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_357: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_9mm";
		round = "FxRound_9mm";
		spawnPileType = "Ammo_357";
		hit = 9;
		indirectHit = 0;
		indirectHitRange = 0;
		tracerScale = 1;
		caliber = 0.9;
		deflecting = 30;
		airFriction = -0.000599;
		typicalSpeed = 440;
		initSpeed = 440;
		weight = 0.008;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 80;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_9x19: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_9mm";
		round = "FxRound_9mm";
		spawnPileType = "Ammo_9x19";
		hit = 7;
		indirectHit = 0;
		indirectHitRange = 0;
		tracerScale = 1;
		caliber = 0.8;
		deflecting = 30;
		initSpeed = 360;
		typicalSpeed = 360;
		airFriction = -0.003;
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		muzzleFlashParticle = "weapon_shot_mp5k_01";
		weight = 0.0084;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 26;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 33;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_380: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_9mm";
		round = "FxRound_9mm";
		spawnPileType = "Ammo_380";
		hit = 5.5;
		indirectHit = 0;
		indirectHitRange = 0;
		tracerScale = 1;
		muzzleFlashParticle = "weapon_shot_mp5k_02_boris";
		caliber = 0.8;
		deflecting = 30;
		initSpeed = 290;
		typicalSpeed = 290;
		airFriction = -0.0016;
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		weight = 0.006;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 21;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 33;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_22: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_22";
		round = "FxRound_22";
		spawnPileType = "Ammo_22";
		hit = 4.5;
		indirectHit = 0;
		indirectHitRange = 0;
		tracerScale = 0.6;
		tracerStartTime = -1;
		tracerEndTime = 1;
		deflecting = 30;
		caliber = 0.7;
		airFriction = -0.000769;
		typicalSpeed = 380;
		initSpeed = 380;
		weight = 0.0025;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 18;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 25;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_9x39AP: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_762x39";
		round = "FxRound_762x39";
		spawnPileType = "Ammo_9x39AP";
		hit = 11;
		indirectHit = 0;
		indirectHitRange = 0;
		tracerScale = 1;
		caliber = 1;
		deflecting = 15;
		typicalSpeed = 320;
		airFriction = -0.00055;
		initSpeed = 320;
		weight = 0.0168;
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 55;
				armorDamage = 3;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 66;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Bullet_9x39: Bullet_Base
	{
		scope = 2;
		casing = "FxCartridge_762x39";
		round = "FxRound_762x39";
		spawnPileType = "Ammo_9x39";
		hit = 11;
		indirectHit = 0;
		indirectHitRange = 0;
		tracerScale = 1;
		caliber = 0.9;
		deflecting = 20;
		typicalSpeed = 320;
		airFriction = -0.00055;
		initSpeed = 320;
		weight = 0.0168;
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 55;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 66;
			};
		};
		class NoiseHit
		{
			strength = 10;
			type = "shot";
		};
	};
	class Arrow_Composite: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_composite_flying.p3d";
		spawnPileType = "Ammo_ArrowComposite";
		proxyShape = "\dz\weapons\projectiles\arrow_composite.p3d";
		hit = 12;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "FxRound_arrow_composite";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00215;
		typicalSpeed = 90;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 90;
		weight = 0.025;
		tracerScale = 1;
		tracerStartTime = 1e-05;
		tracerEndTime = -1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 50;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Arrow_Target: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_target.p3d";
		proxyShape = "\dz\weapons\projectiles\arrow_target.p3d";
		hit = 7;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00215;
		typicalSpeed = 100;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 30;
		weight = 0.025;
		tracerScale = 1;
		tracerStartTime = 1e-05;
		tracerEndTime = -1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 50;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Arrow_Hunting: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_hunting.p3d";
		proxyShape = "\dz\weapons\projectiles\arrow_hunting.p3d";
		hit = 7;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00215;
		typicalSpeed = 100;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 30;
		weight = 0.025;
		tracerScale = 1;
		tracerStartTime = 1e-05;
		tracerEndTime = -1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 50;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Arrow_Bolt: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_hunting_flying.p3d";
		spawnPileType = "Ammo_ArrowBolt";
		proxyShape = "\dz\weapons\projectiles\arrow_hunting.p3d";
		hit = 14;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "";
		deflecting = 0;
		caliber = 0.55;
		airFriction = -0.00215;
		typicalSpeed = 100;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 100;
		weight = 0.025;
		tracerScale = 1;
		tracerStartTime = 1e-05;
		tracerEndTime = -1;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 50;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Arrow_Boned: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_hunting_flying.p3d";
		spawnPileType = "Ammo_ArrowBoned";
		proxyShape = "\dz\weapons\projectiles\arrow_crafted_advanced.p3d";
		hit = 11;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00215;
		typicalSpeed = 80;
		initSpeed = 80;
		weight = 0.025;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 50;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Arrow_Primitive: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_hunting_flying.p3d";
		spawnPileType = "Ammo_ArrowPrimitive";
		proxyShape = "\dz\weapons\projectiles\arrow_crafted_simple.p3d";
		hit = 10;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00215;
		typicalSpeed = 70;
		initSpeed = 70;
		weight = 0.025;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 50;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Arrow_Crude: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\arrow_hunting_flying.p3d";
		spawnPileType = "Ammo_SharpStick";
		proxyShape = "\dz\weapons\projectiles\arrow_crude_simple.p3d";
		hit = 8;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00255;
		typicalSpeed = 50;
		initSpeed = 50;
		weight = 0.025;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 50;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Dart_Syringe: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\dart_syringe.p3d";
		spawnPileType = "Ammo_DartSyringe";
		hit = 9;
		indirectHit = 0;
		indirectHitRange = 0;
		casing = "";
		round = "";
		deflecting = 20;
		caliber = 0.5;
		airFriction = -0.00215;
		typicalSpeed = 100;
		weight = 0.025;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		initSpeed = 30;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 1.0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 35;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Bullet_Flare: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\projectiles\tracer_red.p3d";
		spawnPileType = "Ammo_Flare";
		casing = "-";
		round = "-";
		caliber = 1;
		airFriction = -0.00215;
		typicalSpeed = 180;
		initSpeed = 180;
		weight = 0.025;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		hit = 5;
		indirectHit = 2;
		indirectHitRange = 0.2;
		simulation = "shotIlluminating";
		simulationStep = 0.05;
		explosive = 0;
		soundHit[] = {"",0,1};
		deflecting = 90;
		timeToLive = 40;
		explosionTime = 40;
		radius = 300;
		soundEngine[] = {"dz\sounds\effects\crafting\fire\flare_1",0.099999994,1,100};
		class PointLight
		{
			color[] = {1,0.4,0.3,1.0};
			brightness = 1.0;
			radius = 100;
			dayLight = 1;
			position = "";
			hitpoint = "";
			selection = "";
			heatHazeRadius = 0.2;
			heatHazePower = 0.01;
			fireEffect = 1;
			fireEffectOctaves = 4;
			fireEffectPersistence = 0.99;
			fireEffectFract = 0.33;
		};
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 0;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 10;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class GrenadeM4: Bullet_Base
	{
		scope = 2;
		simulation = "shotShell";
		simulationStep = 0.05;
		soundFly[] = {"dz\sounds\weapons\effects\bullet_crack_mid",9.999997e-09,1};
		model = "\dz\weapons\ammunition\rocket_rpg7_inflight.p3d";
		proxyShape = "\dz\weapons\projectiles\rocket_rpg7_inflight.p3d";
		spawnPileType = "Ammo_GrenadeM4";
		hit = 60;
		indirectHit = 28;
		indirectHitRange = 7;
		explosive = 1;
		typicalSpeed = 3;
		initSpeed = 3;
		weight = 0.2;
		fuseDistance = 5;
		soundHit[] = {"",10.0,1};
		soundEngine[] = {"",9.999998e-05,4};
		timeToLive = 20;
		deflecting = 60;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 0.75;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 99;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Rocket_RPG7_Base: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\ammunition\rocket_rpg7_inflight.p3d";
		proxyShape = "\dz\weapons\projectiles\rocket_rpg7_inflight.p3d";
		casing = "-";
		round = "-";
		caliber = 0.2;
		airFriction = -0.00215;
		typicalSpeed = 180;
		initSpeed = 180;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		simulationStep = 0.05;
		soundHit[] = {"",0,1};
		soundEngine[] = {"dz\sounds\effects\crafting\fire\flare_1",0.099999994,1,100};
		explosive = 1;
		hit = 500;
		indirectHit = 150;
		indirectHitRange = 2;
		maxSpeed = 1;
		initTime = 0;
		thrustTime = 0.2;
		thrust = 2000;
		timeToLive = 20;
		explosionTime = 20;
		maneuvrability = 0;
		maxControlRange = 0;
		deflecting = 5;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 0.8;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 150;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Rocket_RPG7_HE: Rocket_RPG7_Base
	{
		hit = 208;
		indirectHit = 20;
		indirectHitRange = 2;
		model = "\dz\weapons\ammunition\rocket_rpg7_inflight.p3d";
		spawnPileType = "Ammo_RPG7_HE";
		initTime = 0.1;
		thrust = 280;
		thrustTime = 1;
		maxSpeed = 295;
		sideAirFriction = 0.5;
		timeToLive = 4.5;
		fuseDistance = 5;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 0.8;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 150;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Rocket_RPG7_AP: Rocket_RPG7_Base
	{
		hit = 128;
		indirectHit = 80;
		indirectHitRange = 30;
		model = "\dz\weapons\ammunition\rocket_rpg7_inflight.p3d";
		spawnPileType = "Ammo_RPG7_AP";
		initTime = 0.1;
		thrust = 280;
		thrustTime = 1;
		maxSpeed = 295;
		sideAirFriction = 0.5;
		timeToLive = 4.5;
		fuseDistance = 5;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 0.8;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 150;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Rocket_LAW_Base: Bullet_Base
	{
		scope = 2;
		model = "\dz\weapons\ammunition\rocket_rpg7_inflight.p3d";
		proxyShape = "\dz\weapons\projectiles\rocket_rpg7_inflight.p3d";
		casing = "-";
		round = "-";
		caliber = 0.2;
		airFriction = -0.00215;
		typicalSpeed = 145;
		initSpeed = 145;
		soundFly[] = {};
		supersonicCrackNear[] = {};
		supersonicCrackFar[] = {};
		simulationStep = 0.05;
		soundHit[] = {"",0,1};
		soundEngine[] = {"dz\sounds\effects\crafting\fire\flare_1",0.099999994,1,100};
		explosive = 1;
		hit = 500;
		indirectHit = 150;
		indirectHitRange = 2;
		maxSpeed = 1;
		initTime = 0;
		thrustTime = 0.2;
		thrust = 2000;
		timeToLive = 20;
		explosionTime = 20;
		maneuvrability = 0;
		maxControlRange = 0;
		deflecting = 5;
		explosionEffects = "VehicleExplosionEffects";
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 0.8;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 150;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
	class Rocket_LAW_HE: Rocket_LAW_Base
	{
		hit = 208;
		indirectHit = 20;
		indirectHitRange = 2;
		model = "\dz\weapons\ammunition\rocket_rpg7_inflight.p3d";
		spawnPileType = "Ammo_LAW_HE";
		initTime = 0.1;
		thrust = 280;
		thrustTime = 1;
		maxSpeed = 295;
		sideAirFriction = 0.5;
		timeToLive = 4.5;
		fuseDistance = 5;
		class DamageApplied
		{
			type = "Projectile";
			dispersion = 0.0;
			bleedThreshold = 0.8;
			defaultDamageOverride[] = {{0.5,1.0}};
			class Health
			{
				damage = 150;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 0;
			};
		};
	};
};
class CfgVehicles
{
	class All;
	class Strategic;
	class ThingEffect;
	class FxCartridge: ThingEffect
	{
		model = "\dz\weapons\projectiles\nabojnice_556.p3d";
		displayName = "";
		submerged = 0;
		submergeSpeed = 0;
		timeToLive = 5;
		disappearAtContact = 1;
		airRotation = 1.5;
	};
	class FxCartridge_Small: ThingEffect
	{
		model = "\dz\weapons\projectiles\nabojnice_small.p3d";
		displayName = "";
		submerged = 0;
		submergeSpeed = 0;
		timeToLive = 5;
		disappearAtContact = 1;
		airRotation = 1.5;
	};
	class FxCartridge_9mm: FxCartridge_Small{};
	class FxCartridge_556: FxCartridge{};
	class FxCartridge_762: FxCartridge
	{
		model = "\dz\weapons\projectiles\nabojnice_762.p3d";
	};
	class FxCartridge_762x39: FxCartridge
	{
		model = "\dz\weapons\projectiles\nabojnice_762x39.p3d";
	};
	class FxCartridge_12Pellet: FxCartridge
	{
		model = "\dz\weapons\projectiles\shotgunshell_pellets.p3d";
	};
	class FxCartridge_12Slug: FxCartridge
	{
		model = "\dz\weapons\projectiles\shotgunshell_slug.p3d";
	};
	class FxCartridge_22: FxCartridge
	{
		model = "\dz\weapons\projectiles\nabojnice_22.p3d";
	};
	class FxRound: FxCartridge
	{
		model = "\dz\weapons\projectiles\556_SingleRound.p3d";
		displayName = "";
		submerged = 0;
		submergeSpeed = 0;
		timeToLive = 5;
		disappearAtContact = 1;
		airRotation = 1.0;
	};
	class FxRound_9mm: FxRound
	{
		model = "\dz\weapons\projectiles\9mm_SingleRound.p3d";
	};
	class FxRound_556: FxRound
	{
		model = "\dz\weapons\projectiles\556_SingleRound.p3d";
	};
	class FxRound_762: FxRound
	{
		model = "\dz\weapons\projectiles\762_SingleRound.p3d";
	};
	class FxRound_762x39: FxRound
	{
		model = "\dz\weapons\projectiles\762x39_SingleRound.p3d";
	};
	class FxRound_12Pellet: FxRound
	{
		model = "\dz\weapons\projectiles\shotgunshell_pellets.p3d";
	};
	class FxRound_12Slug: FxRound
	{
		model = "\dz\weapons\projectiles\shotgunshell_slug.p3d";
	};
	class FxRound_22: FxRound
	{
		model = "\dz\weapons\projectiles\22_SingleRound.p3d";
	};
	class FxRound_308Win: FxRound
	{
		model = "\dz\weapons\projectiles\308Win_SingleRound.p3d";
	};
	class FxRound_arrow_composite: FxRound
	{
		model = "\dz\weapons\projectiles\arrow_composite.p3d";
	};
};
