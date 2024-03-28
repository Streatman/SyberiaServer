modded class ActionLightItemOnFire
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		ItemBase target_item = ItemBase.Cast( action_data.m_Target.GetObject() );
		ItemBase item = action_data.m_MainItem;
		
		bool is_ignition_successful = false;
		ItemBase ignited_item;				//item that was lit on fire
		ItemBase fire_source_item;			//item that was the source of fire
		
		if (!target_item || !item)
		{
			return;
		}
	//-------------------
		float chance = GetSyberiaConfig().m_igniteFireplaceBaseSkillcheckChance;
		chance = chance + action_data.m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_SURVIVAL_MAKEFIRE_INC, 0, 0);
		
		if (target_item.IsInherited(BarrelHoles_ColorBase) || target_item.IsInherited(FireplaceIndoor))
			chance = chance + GetSyberiaConfig().m_igniteFireplaceIndoorAdditionalChance;
			
		if (target_item.IsInherited(Roadflare) || item.IsInherited(Blowtorch) || item.IsInherited(Roadflare))
			chance = chance * 2;
		#ifdef Molotov
		if ( item.IsInherited(Molotov) || target_item.IsInherited(FireworksLauncher) )
			chance = 1.0;
		#else
		if ( target_item.IsInherited(FireworksLauncher) )
			chance = 1.0;
		#endif
		
		if ( item.CanIgniteItem( target_item ) )
		{
			is_ignition_successful = target_item.IsThisIgnitionSuccessful( item );
			ignited_item = target_item;
			fire_source_item = item;
		}
		else if ( item.CanBeIgnitedBy( target_item ) )
		{
			is_ignition_successful = target_item.IsTargetIgnitionSuccessful( item );
			ignited_item = item;
			fire_source_item = target_item;
		}
		
		if ( is_ignition_successful && Math.RandomFloat01() < chance) //successfull ignition
		{
			fire_source_item.OnIgnitedTarget( ignited_item );
			ignited_item.OnIgnitedThis( fire_source_item );
			#ifdef Molotov
			if ( item.IsInherited(Molotov) || target_item.IsInherited(FireworksLauncher) )
				action_data.m_Player.AddExperienceOnIgniteFireplace(0);
			else
				action_data.m_Player.AddExperienceOnIgniteFireplace(1);
			#else
			if ( target_item.IsInherited(FireworksLauncher) )
				action_data.m_Player.AddExperienceOnIgniteFireplace(0);
			else
				action_data.m_Player.AddExperienceOnIgniteFireplace(1);
			#endif
		}
		else
		{
			fire_source_item.OnIgnitedTargetFailed( ignited_item );
			ignited_item.OnIgnitedThisFailed( fire_source_item );
			GetSyberiaRPC().SendToClient(SyberiaRPC.SYBRPC_SCREEN_MESSAGE, action_data.m_Player.GetIdentity(), new Param1<string>("#syb_skillcheck_fire"));
			action_data.m_Player.AddExperienceOnIgniteFireplace(-1);
		}
	//-------------------
		if (target_item.IsInherited(FireplaceBase))
		{
			float skillBasedFuelMod = 1.0 - action_data.m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_SURVIVAL_KEEPING_FIRE, 0, 0);
			FireplaceBase.Cast(target_item).SetSkillBasedFuelModifier( skillBasedFuelMod );
		}
		
		if (item.IsInherited(HandDrillKit))
		{
			float value = (float)action_data.m_Player.GetPerkIntValue(SyberiaPerkType.SYBPERK_SURVIVAL_TOOLS_DEGRADATION_DEC, 1);
			item.DecreaseHealth(item.GetMaxHealth("", "") / value);
			
			ItemBase gloves = action_data.m_Player.GetItemOnSlot("Gloves");
			if (gloves && !gloves.IsRuined())
			{
				gloves.DecreaseHealth((gloves.GetMaxHealth("", "") / 10) / value);
			}
			else 
			{
				if (Math.RandomFloat01() > 0.5)
				{
					action_data.m_Player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection("LeftForeArmRoll");
				}
				else
				{
					action_data.m_Player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection("RightForeArmRoll");
				}
			}
		}
	}
};