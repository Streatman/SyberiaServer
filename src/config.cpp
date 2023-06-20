class CfgPatches
{
	class SyberiaServer
	{
		units[]={};
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"IntenZ_SyberiaClient",
			"IntenZ_Inventory"
		};
	};
};

class CfgMods
{
	class SyberiaServer
	{
		type="mod";
		dependencies[]={"Game","World","Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]={"IntenZ/SyberiaServer/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value="";
				files[]={"IntenZ/SyberiaServer/scripts/4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"IntenZ/SyberiaServer/scripts/5_Mission"};
			};
		};
	};
};

class CfgSyberia
{
	class SleepingSystem
	{
		sleepingDecPerSec=1;
		sleepingUnconsionEnabled=0;
		sleepingIncPerUnconsionBoostValue=5;
		sleepingIncPerUnconsionBoostTime=30;
		sleepingIncPerSleepingLvl1Sec=10;
		sleepingIncPerSleepingLvl2Sec=20;
		sleepingHealPerSec01=0.002;
		sleepingHealInfluenzaChance=0.01;
	};
	
	class MedicineSystem
	{
		sepsisStage1TimeSec=600;
		sepsisStage2TimeSec=2400;
		sepsisDeathTimeSec=1200;
		sepsisHighTemperatureValue=42;
		sepsisZombieHitChance=0.01;
		sepsisKnifeHitChance=0.1;
		sepsisBulletHitChance=0.05;
		sepsisDirtySyringeChance=0.75;
		zvirusStage1TimeSec=600; // 10 min
		zvirusStage2TimeSec=2400; // zvirusStage1TimeSec + 40 min
		zvirusDeathTimeSec=1200;
		zvirusBloodLosePerSec=0.05;
		zvirusHealthLosePerSec=0.01;
		zvirusCuthitSpawnChance=0.003;
		zvirusPainSpawnChance=0.001;
		zvirusVommitSpawnChance=0.0002;
		zvirusBlindnessSpawnChance=0.01;
		zvirusFeverblurSpawnChance=0.01;
		zvirusOnHitIncrementTimer=300;
		zvirusZombieHitChance=0.2;
		zvirusZombieBloodTransferChance=0.1;
		zvirusAntidotBloodDmg01=0.15;
		zvirusAntidotHealthDmg01=0.2;
		painLvl1TimeSec=300;
		painLvl2TimeSec=900;
		painLvl3TimeSec=1800;
		painMaxDurationSec=2400;
		bleedingBullethitHealthlosePerSecond=0.003;
		bleedingBullethitOpenPerSecond=5;
		bleedingBullethitCupd1PerSecond=0.3;
		bleedingBullethitCupd2PerSecond=0.1;
		bleedingBullethitRemoveBandagedTimeSec=-1; // DISABLED
		bleedingKnifehitZombieChance=0.005;
		bleedingKnifehitHealthlosePerSecond=0.003;
		bleedingKnifehitOpenPerSecond=6;
		bleedingKnifehitCupd1PerSecond=0.35;
		bleedingKnifehitCupd2PerSecond=0.1;
		bleedingKnifehitRemoveBandagedTimeSec=3600;
		bleedingVisceraBloodlosePerSecond=3;
		bleedingVisceraHealthlosePerSecond=0.005;
		bleedingHematomaBloodlosePerSecond=0;
		bleedingHematomaHealthlosePerSecond=0.002;
		bleedingZombieHitChance=0.3;
		hematomaPlayerhandsHitChance=0.6;
		hematomaZombieHitChance=0.7;
		hematomaRegenTimerSec=600;
		hematomaRegenTimeBoostOnSalve=8;
		hematomaPainChance=0.5;
		cuthitRegenTimerSec=300;
		visceraKnifehitTorsoChance=0.4;
		visceraBullethitTorsoChance=0.3;
		concussionRegenTimeSec=1800; //30 min
		concussionZombieHitChance=0.05;
		hemostaticEffectModifier=0.3; // 30% of total bloodlose
		hematopoiesisEffectBloodPerSec=2;
		adrenalinEffectShockUpPerSec[]={ 0.01666, 0.03333, 0.2 };
		adrenalinEffectStaminaDepletionMod[]={ 0.5, 0.25, 0.1 };
		adrenalinEffectStaminaRecoveryMod[]={ 1.5, 2.0, 2.5 };
		overdoseDecrementPerSec=0.001;
		overdoseUnconChangePerSec=0.025;
		mindstateHealPerSec=0.005;
		mindstateEmptyDeadtimeSec=600;
		influenzaIncubatePeriodsSec[]={ 300, 1500, 1800 };
		influenzaTemperatureLevels[]={ -1.0, 37.0, 40.0 };
		influenzaSympthomChance[]={ 0.02, 0.04, 0.08 };
		influenzaDeathTime[]={0, 0, 900};
		influenzaApplyOnColdWarnChance=0.001;
		influenzaApplyOnColdCritChance=0.005;
		antibioticsGlobalEffectivityModifier=0.006;
		stomatchpoisonVomitChance[]={ 0.01, 0.02, 0.04 };
		stomatchpoisonWaterDrainFromVomit[]={ 200, 350, 500 };
		stomatchpoisonEnergyDrainFromVomit[]={ 300, 600, 1000 };
		stomatchhealModifier=5;
		stomatchpoisonRawMeat[]={ 1, 400 }; // level, seconds * amount
		stomatchpoisonBurnedMeat[]={ 1, 500 }; // level, seconds * amount
		stomatchpoisonRottenMeat[]={ 2, 600 }; // level, seconds * amount
		stomatchpoisonBurnedFood[]={ 1, 300 }; // level, seconds * amount
		stomatchpoisonRottenFood[]={ 2, 600 }; // level, seconds * amount
		stomatchpoisonDirtyHands[]={ 1, 300 }; // level, seconds * amount
		stomatchpoisonInfection[]={ 1, 500 }; // level, seconds * amount
		stomatchpoisonGasoline[]={ 2, 900 }; // level, seconds * amount
		stomatchpoisonChanceDrinkPond=0.5;
		stomatchpoisonDrinkPond[]={ 2, 200 };
		stomatchpoisonChanceDrinkWell=0.01;
		stomatchpoisonDrinkWell[]={ 1, 100 };
		stomatchpoisonDefaultTimes[]={ 1800, 900, 600 }; // lvl1, lvl2, lvl3
		startSurgeryVisceraChance=0.15;
		startSurgeryBulletChance=0.3;
		startSurgeryKnifeChance=0.5;
		surgerySideEffectBloodLoseCount=500;
		surgerySideEffectHealthLoseCount=20;
		radiationDoseDecrementPerSec[]={ -0.02, -0.08, -0.2, -0.5 };
		radiationLevels[]={ 20, 60, 120 };
		radiationHealthDamage[]={ 0.09, 0.2, 0.8 };
		radiationSleepingDec=3;
		shockDecrementOnLowHealthAndBlood=1.5;
		zombieHitDecreaseMind[]= { 0.4,  5}; // amount, time
		zombieKillDecreaseMind[]={ 0.2, 10}; // amount, time
		playerHitDecreaseMind[]= {0.04,  5}; // amount, time
		playerKillDecreaseMind[]={0.09,300}; // amount, time 
		antidepresantMindInc[]={ 0.1, 0.25, 0.5 };
		disableLaughterSymptom=0;
	};
	
	class AttackSystem
	{
		damageNonWeaponItemInHandsOnAttack=3.0;
		damageGlovesOnHandsOnAttack=2.0;
		damageHandsOnAttackChance=0.20;
		bodyGuardModifier=1;
		zombieAttackDistanceChase=2.2;
		zombieAttackDistanceFight=1.8;
	};
	
	class ZombieSystem
	{
		zombieOpenDoorEnable=1;
		zombieOpenDoorDistance=1.8;
		zombieFindHouseDistance=20.0;
		zombieBloodHandsChanceOnLooting=0.25;
		zombieAttackPlayersInUnconscious=1;
		zombieDetectPlayerVisibilityMultiplier=1;
		zombieDetectPlayerNoiseMultiplier=1;
	};
	
	class AnimalsSystem
	{
		animalsButchingKnifeDamage=100;
	};
	
	class IngameSystem
	{
		bookPagesCountToCut=10;
		gasMaskFilterDegradationInRadZone=-0.2;
		gasMaskFilterDegradationDefault=-0.05;
		igniteFireplaceBaseSkillcheckChance=0.2;
		igniteFireplaceIndoorAdditionalChance=0.3;
		damageClothingInRadiationZone=0.0;
		defaultStaminaDepletionMultiplier=1.0;
		defaultStaminaRecoveryMultiplier=1.0;
		dirtyFruitsSpawnChance=0.25;
		dirtyMushroomsSpawnChance=0.6;
	};
	
	class SkillsExperienceSystem
	{
		skillsExpImmunityPain=50;
		skillsExpImmunityHematoma=10;
		skillsExpImmunityInfluenza=200;
		skillsExpImmunityStomatch=50;
		skillsExpImmunityZVirus=800;
		skillsExpImmunitySepsis=200;
		skillsExpImmunityOverdose=50;
		
		skillsExpAthleticsSprintTime=60;
		skillsExpAthleticsSprintIncrement=80;
		skillsExpAthleticsJogTime=60;
		skillsExpAthleticsJogIncrement=15;
		
		skillsExpStrengthLightAttackValue=30;
		skillsExpStrengthLightAttackChance=0.3;
		skillsExpStrengthHeavyAttackValue=50;
		skillsExpStrengthHeavyAttackChance=0.5;
		skillsExpStrengthMineWoodOrStone=5;
		
		skillsExpMedicineBandage=50;
		skillsExpMedicineTablets=20;
		skillsExpMedicineAmpoule=100;
		skillsExpMedicineInjector=100;
		skillsExpMedicineSurgery=1000;
		
		skillsExpStealthSilentAttackValue=100;
		skillsExpStealthSilentAttackChance=0.5;
		skillsExpStealthCrouchTime=60;
		skillsExpStealthCrouchIncrement=60;
		
		skillsExpHuntingButchSmall=100;
		skillsExpHuntingButchCommon=250;
		skillsExpHuntingButchWolf=500;
		skillsExpHuntingButchBear=3000;
		
		skillsExpSurvivalIgniteFireSuccess=500;
		skillsExpSurvivalIgniteFireFailed=50;
		skillsExpSurvivalCatchFish=150;
		skillsExpSurvivalCraftTool=100;
	};
	
	class WorldSystem
	{
	
	};
	
	class Characters
	{
		class SurvivorM_Mirek
		{
			gender="male";
			ghost="SurvivorM_Mirek_Ghost";
			facelogo="set:faces image:Mirek";
		};
		class SurvivorM_Boris
		{
			gender="male";
			ghost="SurvivorM_Boris_Ghost";
			facelogo="set:faces image:Boris";
		};
		class SurvivorM_Cyril
		{
			gender="male";
			ghost="SurvivorM_Cyril_Ghost";
			facelogo="set:faces image:Cyril";
		};
		class SurvivorM_Denis
		{
			gender="male";
			ghost="SurvivorM_Denis_Ghost";
			facelogo="set:faces image:Denis";
		};
		class SurvivorM_Elias
		{
			gender="male";
			ghost="SurvivorM_Elias_Ghost";
			facelogo="set:faces image:Elias";
		};
		class SurvivorM_Francis
		{
			gender="male";
			ghost="SurvivorM_Francis_Ghost";
			facelogo="set:faces image:Francis";
		};
		class SurvivorM_Guo
		{
			gender="male";
			ghost="SurvivorM_Guo_Ghost";
			facelogo="set:faces image:Guo";
		};
		class SurvivorM_Hassan
		{
			gender="male";
			ghost="SurvivorM_Hassan_Ghost";
			facelogo="set:faces image:Hassan";
		};
		class SurvivorM_Indar
		{
			gender="male";
			ghost="SurvivorM_Indar_Ghost";
			facelogo="set:faces image:Indar";
		};
		class SurvivorM_Jose
		{
			gender="male";
			ghost="SurvivorM_Jose_Ghost";
			facelogo="set:faces image:Jose";
		};
		class SurvivorM_Kaito
		{
			gender="male";
			ghost="SurvivorM_Kaito_Ghost";
			facelogo="set:faces image:Kaito";
		};
		class SurvivorM_Lewis
		{
			gender="male";
			ghost="SurvivorM_Lewis_Ghost";
			facelogo="set:faces image:Lewis";
		};
		class SurvivorM_Manua
		{
			gender="male";
			ghost="SurvivorM_Manua_Ghost";
			facelogo="set:faces image:Manua";
		};
		class SurvivorM_Niki
		{
			gender="male";
			ghost="SurvivorM_Niki_Ghost";
			facelogo="set:faces image:Niki";
		};
		class SurvivorM_Oliver
		{
			gender="male";
			ghost="SurvivorM_Oliver_Ghost";
			facelogo="set:faces image:Oliver";
		};
		class SurvivorM_Peter
		{
			gender="male";
			ghost="SurvivorM_Peter_Ghost";
			facelogo="set:faces image:Peter";
		};
		class SurvivorM_Quinn
		{
			gender="male";
			ghost="SurvivorM_Quinn_Ghost";
			facelogo="set:faces image:Quinn";
		};
		class SurvivorM_Rolf
		{
			gender="male";
			ghost="SurvivorM_Rolf_Ghost";
			facelogo="set:faces image:Rolf";
		};
		class SurvivorM_Seth
		{
			gender="male";
			ghost="SurvivorM_Seth_Ghost";
			facelogo="set:faces image:Seth";
		};
		class SurvivorM_Taiki
		{
			gender="male";
			ghost="SurvivorM_Taiki_Ghost";
			facelogo="set:faces image:Taiki";
		};
		
		class SurvivorF_Eva
		{
			gender="female";
			ghost="SurvivorF_Eva_Ghost";
			facelogo="set:faces image:Eva";
		};
		class SurvivorF_Frida
		{
			gender="female";
			ghost="SurvivorF_Frida_Ghost";
			facelogo="set:faces image:Frida";
		};
		class SurvivorF_Gabi
		{
			gender="female";
			ghost="SurvivorF_Gabi_Ghost";
			facelogo="set:faces image:Gabi";
		};
		class SurvivorF_Helga
		{
			gender="female";
			ghost="SurvivorF_Helga_Ghost";
			facelogo="set:faces image:Helga";
		};
		class SurvivorF_Irena
		{
			gender="female";
			ghost="SurvivorF_Irena_Ghost";
			facelogo="set:faces image:Irena";
		};
		class SurvivorF_Judy
		{
			gender="female";
			ghost="SurvivorF_Judy_Ghost";
			facelogo="set:faces image:Judy";
		};
		class SurvivorF_Keiko
		{
			gender="female";
			ghost="SurvivorF_Keiko_Ghost";
			facelogo="set:faces image:Keiko";
		};class SurvivorF_Linda
		{
			gender="female";
			ghost="SurvivorF_Linda_Ghost";
			facelogo="set:faces image:Linda";
		};
		class SurvivorF_Maria
		{
			gender="female";
			ghost="SurvivorF_Maria_Ghost";
			facelogo="set:faces image:Maria";
		};
		class SurvivorF_Naomi
		{
			gender="female";
			ghost="SurvivorF_Naomi_Ghost";
			facelogo="set:faces image:Naomi";
		};
		class SurvivorF_Baty
		{
			gender="female";
			ghost="SurvivorF_Baty_Ghost";
			facelogo="set:faces image:Baty";
		};
	};
};
