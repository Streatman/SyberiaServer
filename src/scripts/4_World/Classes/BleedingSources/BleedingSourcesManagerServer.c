modded class BleedingSourcesManagerServer
{
	protected ref DayZPlayerMeleeFightLogic_LightHeavy	m_MeleeFightLogic;
	
	void SetZVirus(bool value)
	{
		if (value)
		{
			if (m_Player.GetSybStats().m_zombieVirus == 0)
			{
				m_Player.GetSybStats().m_zombieVirus = 1;
			}
			else if (m_Player.GetSybStats().m_zombieVirus == 2)
			{
				m_Player.m_zvirusTimer = m_Player.m_zvirusTimer + GetSyberiaConfig().m_zvirusOnHitIncrementTimer;
			}
		}
		else
		{
			if (m_Player.GetSybStats().m_zombieVirus > 0)
			{
				m_Player.AddExperience(SyberiaSkillType.SYBSKILL_IMMUNITY, GetSyberiaConfig().m_skillsExpImmunityZVirus);
			}
			
			m_Player.GetSybStats().m_zombieVirus = 0;
		}
		m_Player.MarkSybStatsDirty(1000);
	}
		
	void SetBloodInfection(bool value)
	{
		if (value)
		{
			if (m_Player.GetSybStats().m_sepsis == 0)
			{
				m_Player.GetSybStats().m_sepsis = 1;
			}
		}
		else
		{
			if (m_Player.GetSybStats().m_sepsis > 0)
			{
				m_Player.AddExperience(SyberiaSkillType.SYBSKILL_IMMUNITY, GetSyberiaConfig().m_skillsExpImmunitySepsis);
			}
			
			m_Player.GetSybStats().m_sepsis = 0;
		}
		m_Player.MarkSybStatsDirty(1001);
	}
	
	private void ApplyBandageDammageHands()
	{
		ItemBase gloves = m_Player.GetItemOnSlot("Gloves");
		if (gloves)
		{
			gloves.SetCleanness(0);
		}
		else
		{
			m_Player.SetBloodyHands(true);
		}
	}
	
	void ApplyBandage(int level)
	{
		if (m_Player.GetSybStats().m_bulletHits > (m_Player.GetSybStats().m_bulletBandage1 + m_Player.GetSybStats().m_bulletBandage2))
		{
			if (level == 2)
			{
				ApplyBandageDammageHands();
				m_Player.GetSybStats().m_bulletBandage1 = m_Player.GetSybStats().m_bulletBandage1 + 1;
				m_Player.MarkSybStatsDirty(1002);
				return;
			}
			if (level == 3)
			{
				ApplyBandageDammageHands();
				m_Player.GetSybStats().m_bulletBandage2 = m_Player.GetSybStats().m_bulletBandage2 + 1;
				m_Player.MarkSybStatsDirty(1003);
				return;
			}
		}
		
		if (m_Player.GetSybStats().m_knifeHits > (m_Player.GetSybStats().m_knifeBandage1 + m_Player.GetSybStats().m_knifeBandage2))
		{
			if (level == 2)
			{
				ApplyBandageDammageHands();
				m_Player.GetSybStats().m_knifeBandage1 = m_Player.GetSybStats().m_knifeBandage1 + 1;
				m_Player.MarkSybStatsDirty(1004);
				return;
			}
			if (level == 3)
			{
				ApplyBandageDammageHands();
				m_Player.GetSybStats().m_knifeBandage2 = m_Player.GetSybStats().m_knifeBandage2 + 1;
				m_Player.MarkSybStatsDirty(1005);
				return;
			}
		}
		
		if (level > 0)
		{
			RemoveMostSignificantBleedingSource();
			return;
		}
	}
	
	void AddBulletHit()
	{
		m_Player.GetSybStats().m_bulletHits = m_Player.GetSybStats().m_bulletHits + 1;
		SetPainLevel(2);
		m_Player.MarkSybStatsDirty(1006);
	}
	
	void RemoveBulletHit(bool removeBandage)
	{
		if (m_Player.GetSybStats().m_bulletHits > 0)
		{
			m_Player.GetSybStats().m_bulletHits = m_Player.GetSybStats().m_bulletHits - 1;
			if (removeBandage)
			{
				if (m_Player.GetSybStats().m_bulletBandage1 > 0) m_Player.GetSybStats().m_bulletBandage1 = m_Player.GetSybStats().m_bulletBandage1 - 1;
				else if (m_Player.GetSybStats().m_bulletBandage2 > 0) m_Player.GetSybStats().m_bulletBandage2 = m_Player.GetSybStats().m_bulletBandage2 - 1;
			}
			m_Player.MarkSybStatsDirty(1007);
		}
	}
	
	void AddKnifeHit()
	{
		m_Player.GetSybStats().m_knifeHits = m_Player.GetSybStats().m_knifeHits + 1;
		SetPainLevel(2);
		m_Player.MarkSybStatsDirty(1008);
	}
	
	void RemoveKnifeHit(bool removeBandage)
	{
		if (m_Player.GetSybStats().m_knifeHits > 0)
		{
			m_Player.GetSybStats().m_knifeHits = m_Player.GetSybStats().m_knifeHits - 1;
			if (removeBandage)
			{
				if (m_Player.GetSybStats().m_knifeBandage1 > 0) m_Player.GetSybStats().m_knifeBandage1 = m_Player.GetSybStats().m_knifeBandage1 - 1;
				else if (m_Player.GetSybStats().m_knifeBandage2 > 0) m_Player.GetSybStats().m_knifeBandage2 = m_Player.GetSybStats().m_knifeBandage2 - 1;
			}
			m_Player.MarkSybStatsDirty(1009);
		}
	}
	
	void AddHematomaHit()
	{
		if ( Math.RandomFloat01() < m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_IMMUNITY_HEMATOMA_CHANCE, 0, 0) )
			return;
		
		m_Player.GetSybStats().m_hematomaHits = m_Player.GetSybStats().m_hematomaHits + 1;
		
		if (Math.RandomFloat01() < GetSyberiaConfig().m_hematomaPainChance)
		{
			SetPainLevel(1);
		}
		
		m_Player.MarkSybStatsDirty(1010);
	}
	
	void RemoveHematomaHit()
	{
		if (m_Player.GetSybStats().m_hematomaHits > 0)
		{
			m_Player.GetSybStats().m_hematomaHits = m_Player.GetSybStats().m_hematomaHits - 1;
			m_Player.MarkSybStatsDirty(1011);
		}
	}
	
	void AddVisceraHit()
	{
		m_Player.GetSybStats().m_visceraHit = m_Player.GetSybStats().m_visceraHit + 1;
		SetPainLevel(3);
		m_Player.MarkSybStatsDirty(1012);
	}
	
	void RemoveVisceraHit()
	{
		if (m_Player.GetSybStats().m_visceraHit > 0)
		{
			m_Player.GetSybStats().m_visceraHit = m_Player.GetSybStats().m_visceraHit - 1;
			m_Player.MarkSybStatsDirty(1013);
		}
	}
	
	void SetConcussionHit(bool value, bool uncounsion = true)
	{
		m_Player.GetSybStats().m_concussionHit = value;
		if (value)
		{
			if (uncounsion)
			{
				m_Player.m_UnconsciousEndTime = -60;
				m_Player.SetHealth("","Shock",0);
			}
			SetPainLevel(1);
		}
		m_Player.SetSynchDirty();
		m_Player.MarkSybStatsDirty(1014);
	}
	
	int GetPainLevel()
	{
		return m_Player.GetSybStats().m_painLevel;
	}
	
	void SetPainLevel(int value)
	{
		if (m_Player.GetPerkBoolValue(SyberiaPerkType.SYBPERK_IMMUNITY_PAIN_STRONG))
		{
			value = value - 1;
		}
		
		if (value == 1) m_Player.m_painTimer = m_Player.m_painTimer + GetSyberiaConfig().m_painLvl1TimeSec;
		else if (value == 2) m_Player.m_painTimer = m_Player.m_painTimer + GetSyberiaConfig().m_painLvl2TimeSec;
		else if (value == 3) m_Player.m_painTimer = m_Player.m_painTimer + GetSyberiaConfig().m_painLvl3TimeSec;
		
		if (m_Player.GetSybStats().m_painLevel < value)
		{
			m_Player.GetSybStats().m_painLevel = value;
			m_Player.MarkSybStatsDirty(1015);
		}
	}
	
	override bool AttemptAddBleedingSource(int component)
	{
		if ( Math.RandomFloat01() < m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_IMMUNITY_CUTHIT_CHANCE, 0, 0) )
			return false;
		
		return super.AttemptAddBleedingSource(component);
	}
	
	override bool AttemptAddBleedingSourceBySelection(string selection_name)
	{
		if (selection_name == "RightFoot" || selection_name == "LeftFoot")
		{
			if ( Math.RandomFloat01() < m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_SURVIVAL_CUTHIT_LEGS_DEC, 0, 0) )
			{
				return false;
			}
		}
		else if (selection_name == "LeftForeArmRoll" || selection_name == "RightForeArmRoll")
		{
			if ( Math.RandomFloat01() < m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_SURVIVAL_CUTHIT_HANDS_DEC, 0, 0) )
			{
				return false;
			}
			
			m_Player.SetBloodyHands(true);
		}
		
		return super.AttemptAddBleedingSourceBySelection(selection_name);
	}
	
	override void ProcessHit(float damage, EntityAI source, int component, string zone, string ammo, vector modelPos)
	{
		//SybLogSrv("ProcessHit => Damage: " + damage + "; Source: " + source.GetType() + "; Component: " + component + "; zone: " + zone + "; Ammo: " + ammo);
		
		float bleed_threshold = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " DamageApplied " + "bleedThreshold" );		
		string ammoType = GetGame().ConfigGetTextOut( "CfgAmmo " + ammo + " DamageApplied " + "type" );
		bleed_threshold = Math.Clamp(bleed_threshold,0,1);
		
		float HeadProtectionMelee = 0;
		ItemBase helmet = m_Player.GetItemOnSlot("Headgear");
		ItemBase vest = m_Player.GetItemOnSlot("Vest");
		ItemBase top = m_Player.GetItemOnSlot("Body");
		ItemBase pants = m_Player.GetItemOnSlot("Legs");
		if ( helmet )
		{
			HeadProtectionMelee = helmet.ConfigGetFloat("meleeProtection");
			float HeadProtectionProjectile = GetGame().ConfigGetFloat( "CfgVehicles " + helmet.GetType() + " firearmProtection" );
		}
		if ( vest && !vest.IsRuined() )
		{
			float TorsoProtectionInfected = GetGame().ConfigGetFloat( "CfgVehicles " + vest.GetType() + " DamageSystem GlobalArmor Infected Blood damage" );
			float TorsoProtectionMelee = GetGame().ConfigGetFloat( "CfgVehicles " + vest.GetType() + " DamageSystem GlobalArmor Melee Blood damage" );
			float TorsoProtectionProjectile = GetGame().ConfigGetFloat( "CfgVehicles " + vest.GetType() + " bulletProofProtection" );
		}
		if ( top && !top.IsRuined() )
		{
			float ArmProtectionInfected = GetGame().ConfigGetFloat( "CfgVehicles " + top.GetType() + " DamageSystem GlobalArmor Infected Blood damage" );
			float ArmProtectionMelee = GetGame().ConfigGetFloat( "CfgVehicles " + top.GetType() + " DamageSystem GlobalArmor Melee Blood damage" );
			float ArmProtectionProjectile = GetGame().ConfigGetFloat( "CfgVehicles " + top.GetType() + " bulletProofProtection" );
		}
		if ( pants && !pants.IsRuined() )
		{
			float LegProtectionInfected = GetGame().ConfigGetFloat( "CfgVehicles " + pants.GetType() + " DamageSystem GlobalArmor Infected Blood damage" );
			float LegProtectionMelee = GetGame().ConfigGetFloat( "CfgVehicles " + pants.GetType() + " DamageSystem GlobalArmor Melee Blood damage" );
			float LegProtectionProjectile = GetGame().ConfigGetFloat( "CfgVehicles " + pants.GetType() + " bulletProofProtection" );
		}
		
		if (source.IsZombie())
		{
			bool blockZedDamage = false;
			if (zone == "Torso")
			{
				if ( TorsoProtectionInfected < 0.1 || ArmProtectionInfected < 0.1 )
				{
					blockZedDamage = true;
				}
			}
			if (zone == "LeftArm" || zone == "RightArm")
			{
				if ( ArmProtectionInfected < 0.1 )
				{
					blockZedDamage = true;
				}
			}
			if (zone == "LeftLeg" || zone == "RightLeg")
			{
				if ( LegProtectionInfected < 0.1 )
				{
					blockZedDamage = true;
				}
			}
			
			float zvirusInfectionChance = GetSyberiaConfig().m_zvirusZombieHitChance;
			float zedHematomaChance = GetSyberiaConfig().m_hematomaZombieHitChance;
			if (blockZedDamage)
			{
				zedHematomaChance = zedHematomaChance * 0.5;
			}
			
			if (!blockZedDamage && Math.RandomFloat01() < GetSyberiaConfig().m_bleedingZombieHitChance)
			{
				zvirusInfectionChance = zvirusInfectionChance * 1.5;
				
				if ( !m_MeleeFightLogic.IsInBlock() || (m_MeleeFightLogic.IsInBlock() && Math.RandomFloat01() < 0.2) )
				{
					AttemptAddBleedingSource(component);
					if (Math.RandomFloat01() < GetSyberiaConfig().m_sepsisZombieHitChance && m_Player.GetSybStats().m_antibioticsLevel < 3)
					{
						SetBloodInfection(true);
					}
				}
			}
			else if (Math.RandomFloat01() < zedHematomaChance)
			{
				if ( !m_MeleeFightLogic.IsInBlock() || (m_MeleeFightLogic.IsInBlock() && Math.RandomFloat01() < 0.2) )
				{
					AddHematomaHit();
					if (zone == "Head" && Math.RandomFloat01() < 0.3 && Math.RandomFloat01() > HeadProtectionMelee)
					{
						SetConcussionHit(true, false);
					}
					
					if (m_Player.IsFaceBlocked(true))
					{
						zvirusInfectionChance = zvirusInfectionChance * 0.5;
					}
				}
			}
			
			if (Math.RandomFloat01() < zvirusInfectionChance)
			{
				SetZVirus(true);
			}
			
			if (!blockZedDamage && Math.RandomFloat01() < GetSyberiaConfig().m_bleedingKnifehitZombieChance)
			{
				if ( !m_MeleeFightLogic.IsInBlock() || (m_MeleeFightLogic.IsInBlock() && Math.RandomFloat01() < 0.2) )
				{
					AddKnifeHit();
					if (Math.RandomFloat01() < GetSyberiaConfig().m_sepsisZombieHitChance && m_Player.GetSybStats().m_antibioticsLevel < 3)
					{
						SetBloodInfection(true);
					}
				}
			}
			
			if (Math.RandomFloat01() < GetSyberiaConfig().m_concussionZombieHitChance && Math.RandomFloat01() > HeadProtectionMelee)
			{
				if ( !m_MeleeFightLogic.IsInBlock() || (m_MeleeFightLogic.IsInBlock() && Math.RandomFloat01() < 0.2) )
				{
					SetConcussionHit(true, false);
				}
			}
			
			m_Player.AddMindDegradation( GetSyberiaConfig().m_zombieHitDecreaseMind[0], GetSyberiaConfig().m_zombieHitDecreaseMind[1] );
		}
		else if ( ammo.ToType().IsInherited(Nonlethal_Base) )
		{
			AddHematomaHit();
		}
		else if ( ammo == "BearTrapHit" )
		{
			AddKnifeHit();
			if (Math.RandomFloat01() < 0.05 && m_Player.GetSybStats().m_antibioticsLevel < 3)
			{
				SetBloodInfection(true);
			}
		}
		else if ( ammo == "BarbedWireHit" )
		{
			if (Math.RandomFloat01() < 0.2)
			{
				AttemptAddBleedingSource(component);
				if (Math.RandomFloat01() < 0.05 && m_Player.GetSybStats().m_antibioticsLevel < 3)
				{
					SetBloodInfection(true);
				}
			}
		}
		else if ( ammoType == "Melee" )
		{
			bool blockMeleeDamage = false;
			if (zone == "Torso")
			{
				if ( TorsoProtectionMelee < 0.1 || ArmProtectionMelee < 0.1 )
				{
					blockMeleeDamage = true;
				}
			}
			if (zone == "LeftArm" || zone == "RightArm")
			{
				if ( ArmProtectionMelee < 0.1 )
				{
					blockMeleeDamage = true;
				}
			}
			if (zone == "LeftLeg" || zone == "RightLeg")
			{
				if ( LegProtectionMelee < 0.1 )
				{
					blockMeleeDamage = true;
				}
			}
			
			float affectSkeleton = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " affectSkeleton" );
			float bloodDamage = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " DamageApplied Blood" );
			if ( affectSkeleton > 1 && !bloodDamage > 0 )
			{
				if ( !m_MeleeFightLogic.IsInBlock() || (m_MeleeFightLogic.IsInBlock() && Math.RandomFloat01() < 0.5) )
				{
					AddHematomaHit();
					if (zone == "Head" && Math.RandomFloat01() > HeadProtectionMelee)
					{
						SetConcussionHit(true);
					}
				}
			}
			else if (!blockMeleeDamage)
			{
				if (bleed_threshold >= Math.RandomFloat01())
				{
					if ( !source.IsAnimal() && (ammo.Contains("_Heavy") || Math.RandomFloat01() >= 0.4) )
					{
						if ( !m_MeleeFightLogic.IsInBlock() || (m_MeleeFightLogic.IsInBlock() && Math.RandomFloat01() < 0.5) )
						{
							AddKnifeHit();
							if (zone == "Torso" && Math.RandomFloat01() < GetSyberiaConfig().m_visceraKnifehitTorsoChance)
							{
								AddVisceraHit();
							}
						}
					}
					else if (source.IsAnimal() && Math.RandomFloat01() <= 0.25) 
					{
						AddKnifeHit();
					}
					else
					{
						AttemptAddBleedingSource(component);
					}
					
					if (Math.RandomFloat01() < GetSyberiaConfig().m_sepsisKnifeHitChance && m_Player.GetSybStats().m_antibioticsLevel < 3)
					{
						SetBloodInfection(true);
					}
				}
				else
				{
					if (Math.RandomFloat01() < GetSyberiaConfig().m_hematomaPlayerhandsHitChance)
					{
						AddHematomaHit();
					}
				}
			}
		}
		else if ( ammoType == "Projectile" )
		{
			float distanceMod = Math.Clamp(1300 - vector.Distance(source.GetPosition(), m_Player.GetPosition()), 100, 1000) * 0.001;
			float bulletSpeed = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " typicalSpeed" ) * 0.1;
			float bulletCaliber = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " caliber" );
			float bulletWeight = GetGame().ConfigGetFloat( "CfgAmmo " + ammo + " weight" );
			float injectModifier = (bulletSpeed * bulletCaliber * bulletWeight * distanceMod) * GetSyberiaConfig().m_bodyGuardModifier;
			
			if ( zone == "Head" || zone == "Brain" )
			{
				if ( HeadProtectionProjectile < injectModifier )
				{
					SetConcussionHit(true);
				}
			}
			
			bool isBulletStopped = false;
			if ( zone == "Torso" )
			{
				if (TorsoProtectionProjectile > injectModifier || ArmProtectionProjectile > injectModifier )
				{
					isBulletStopped = true;
				}
			}
			if (zone == "LeftArm" || zone == "RightArm")
			{
				if ( ArmProtectionProjectile > injectModifier )
				{
					isBulletStopped = true;
				}
			}
			if (zone == "LeftLeg" || zone == "RightLeg")
			{
				if ( LegProtectionProjectile > injectModifier )
				{
					isBulletStopped = true;
				}
			}
			
			if ( isBulletStopped )
			{
				AddHematomaHit();
			}
			else
			{
				if ( bleed_threshold >= Math.RandomFloat01() )
				{
					if ( ammo.Contains("HuntingBolt") || ammo.Contains("ImprovisedBolt_1") || ammo.Contains("ImprovisedBolt_2") )
					{
						AddKnifeHit();
					}
					else
					{
						AddBulletHit();
					}
					if ( zone == "Torso" && Math.RandomFloat01() < GetSyberiaConfig().m_visceraBullethitTorsoChance )
					{
						AddVisceraHit();
					}
				}
				else
				{
					AttemptAddBleedingSource(component);
				}
				if ( Math.RandomFloat01() < GetSyberiaConfig().m_sepsisBulletHitChance && m_Player.GetSybStats().m_antibioticsLevel < 3 )
				{
					SetBloodInfection(true);
				}
			}
		}
		else if ( ammoType == "FragGrenade" )
		{
			if (!ammo.Contains("FlashGrenade"))
			{
				SetConcussionHit(true);
			}
		}
	};
};
