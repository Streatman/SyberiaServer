modded class ActionSkinning
{
	// Spawns the loot according to the Skinning class in the dead agent's config
	override void OnFinishProgressServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		
		//Syberia
		float knifeDmgMultiplier = 1;
		
		// Mark the body as skinned to forbid another skinning action on it
		EntityAI body = EntityAI.Cast(targetObject);
		body.SetAsSkinned();
		
		MiscGameplayFunctions.RemoveAllAttachedChildrenByTypename(body, {Bolt_Base});
		
		HandlePlayerBody(action_data);
		SpawnItems(action_data);
		
		if (body)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(GetGame().ObjectDelete,body);
		}
		
		// clutter cutter removed due to issues with audio it causes when players steps on it.
		//Object cutter = GetGame().CreateObject( "ClutterCutter2x2", body_pos, false ); // clutter cutter to free space on ground for organs.
		
		knifeDmgMultiplier = targetObject.ConfigGetFloat("knifeDamageModifier");
		if (knifeDmgMultiplier <= 0)
		{
			knifeDmgMultiplier = 1;
		}
		
	//	MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, UADamageApplied.SKINNING);
		if (action_data.m_MainItem)
		{
			float skill = 1 - action_data.m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_TOOLS, 0, 0);
			float dmgValue = GetSyberiaConfig().m_animalsButchingKnifeDamage;
			float decreaseHealthValue = skill * dmgValue * knifeDmgMultiplier;
			MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, decreaseHealthValue);
		}
		
		ItemBase gloves = action_data.m_Player.GetItemOnSlot("Gloves");
		if (gloves)
		{
			gloves.SetCleanness(0);
		}
		else
		{
			action_data.m_Player.SetBloodyHands(true);
		}
		
		if (body.IsInherited(Animal_GallusGallusDomesticus))
		{
			action_data.m_Player.AddExperience(SyberiaSkillType.SYBSKILL_HUNTING, GetSyberiaConfig().m_skillsExpHuntingButchSmall);
		}
		else if (body.IsInherited(Animal_CanisLupus))
		{
			action_data.m_Player.AddExperience(SyberiaSkillType.SYBSKILL_HUNTING, GetSyberiaConfig().m_skillsExpHuntingButchWolf);
		}
		else if (body.IsInherited(Animal_UrsusArctos))
		{
			action_data.m_Player.AddExperience(SyberiaSkillType.SYBSKILL_HUNTING, GetSyberiaConfig().m_skillsExpHuntingButchBear);
		}
		else
		{
			action_data.m_Player.AddExperience(SyberiaSkillType.SYBSKILL_HUNTING, GetSyberiaConfig().m_skillsExpHuntingButchCommon);
		}
		
		PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
		module_lifespan.UpdateBloodyHandsVisibility( action_data.m_Player, true );
		
	//	action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
	}
	
//	Spawns an organ defined in the given config
	ItemBase CreateOrgan( PlayerBase player, vector body_pos, string item_to_spawn, string cfg_skinning_organ_class, ItemBase tool)
	{
		// Create item from config
		ItemBase added_item;
		vector pos_rnd = GetRandomPos(body_pos);
		Class.CastTo(added_item,  GetGame().CreateObjectEx( item_to_spawn, pos_rnd, ECE_PLACE_ON_SURFACE ) );
		
		// Check if skinning is configured for this body
		if (!added_item)
			return NULL;
		
		// Set randomized position
		added_item.PlaceOnSurface();
		
		// Set item's quantity from config, if it's defined there.
		float item_quantity = 0;
		float meatCountMod = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_MEAT_COUNT, 0, 0);
		float quantityMin, quantityMax;
		float quantityMinCoef, quantityMaxCoef;
	//	array<float> quant_min_max = new array<float>;
		array<float> quant_min_max_coef = new array<float>;
		
	//	GetGame().ConfigGetFloatArray( cfg_skinning_organ_class + "quantityMinMax", quant_min_max);
		GetGame().ConfigGetFloatArray( cfg_skinning_organ_class + "quantityMinMaxCoef", quant_min_max_coef);
		
		
		// Read config for quantity value
	/*	if (quant_min_max.Count() > 0)
		{
			float soft_skill_manipulated_value = ( quant_min_max.Get(0)+ quant_min_max.Get(1) ) / 2;
			float min_quantity = player.GetSoftSkillsManager().AddSpecialtyBonus( soft_skill_manipulated_value, this.GetSpecialtyWeight() );
			item_quantity = Math.RandomFloat(min_quantity, quant_min_max.Get(1));
		}*/
		
		if (quant_min_max_coef.Count() > 0)		//Steak, Guts, Lard, Bones
		{
			quantityMin = Math.Clamp(quant_min_max_coef.Get(0), 0, quant_min_max_coef.Get(1));
			quantityMax = Math.Clamp(quant_min_max_coef.Get(1), quant_min_max_coef.Get(0), 1);
			quantityMinCoef = Math.Clamp(quantityMin * 0.2 + meatCountMod, quantityMin * 0.2, quantityMin);
			quantityMaxCoef = Math.Clamp(quantityMax * 0.3 + meatCountMod, quantityMax * 0.3, quantityMax);
		//	float coef = Math.RandomFloat(quant_min_max_coef.Get(0), quant_min_max_coef.Get(1));
			float coef = Math.RandomFloat(quantityMinCoef, quantityMaxCoef);
			item_quantity = added_item.GetQuantityMax() * coef;
		}
		
	//	if ( GetGame().ConfigGetFloat( cfg_skinning_organ_class + "quantity" ) > 0 )
	//		item_quantity = g_Game.ConfigGetFloat( cfg_skinning_organ_class + "quantity" );
		
		if ( GetGame().ConfigGetFloat( cfg_skinning_organ_class + "quantityCoef" ) > 0 )	//Pelt
		{
			float coef2 = g_Game.ConfigGetFloat( cfg_skinning_organ_class + "quantityCoef" );
			item_quantity = added_item.GetQuantityMax() * coef2;
		}
		
		if ( item_quantity > 0 )
		{
			item_quantity = Math.Round(item_quantity);
			added_item.SetQuantity( item_quantity, false );
		}
		
		// Transfer tool's damage to the item's condition
		float item_apply_tool_damage_coef = GetGame().ConfigGetFloat( cfg_skinning_organ_class + "transferToolDamageCoef" );
		
		if ( item_apply_tool_damage_coef > 0 )
		{
			float tool_dmg_coef = 1 - tool.GetHealth01();
			float organ_dmg_coef = tool_dmg_coef * item_apply_tool_damage_coef;
			added_item.DecreaseHealthCoef( organ_dmg_coef );
		}
		
	//	added_item.InsertAgent(eAgents.SALMONELLA, 1);
		return added_item;
	}
	
	void SpawnItems(ActionData action_data)
	{
		EntityAI body = EntityAI.Cast(action_data.m_Target.GetObject());
		
		//Syberia
		float meatCountMod = action_data.m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_MEAT_COUNT, 0, 0);
		float skinningMod = action_data.m_Player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_SKINING, 0, 0);
		
		// Get config path to the animal
		string cfg_animal_class_path = "cfgVehicles " + body.GetType() + " " + "Skinning ";
		vector bodyPosition = body.GetPosition();
		
		// Getting item type from the config
		int child_count = g_Game.ConfigGetChildrenCount(cfg_animal_class_path);
		
		string item_to_spawn;
		string cfg_skinning_organ_class;
		// Parsing of the 'Skinning' class in the config of the dead body
		for ( int i1 = 0; i1 < child_count; i1++ )
		{
			// To make configuration as convenient as possible, all classes are parsed and parameters are read
			g_Game.ConfigGetChildName(cfg_animal_class_path, i1, cfg_skinning_organ_class); // out cfg_skinning_organ_class
			cfg_skinning_organ_class = cfg_animal_class_path + cfg_skinning_organ_class + " ";
			g_Game.ConfigGetText(cfg_skinning_organ_class + "item", item_to_spawn); // out item_to_spawn
			
			if ( item_to_spawn != "" ) // Makes sure to ignore incompatible parameters in the Skinning class of the agent
			{
				// Spawning items in action_data.m_Player's inventory
				int item_count = g_Game.ConfigGetInt( cfg_skinning_organ_class + "count" );
				
				array<string> itemZones = new array<string>;
				array<float> itemCount = new array<float>;
				float zoneDmg = 0;
				
				GetGame().ConfigGetTextArray( cfg_skinning_organ_class + "itemZones", itemZones);
				GetGame().ConfigGetFloatArray( cfg_skinning_organ_class + "countByZone", itemCount);
				
				if ( itemCount.Count() > 0 )
				{
					item_count = 0;
					for ( int z = 0; z < itemZones.Count(); z++ )
					{
						zoneDmg = body.GetHealth01(itemZones[z], "Health");
						zoneDmg *= itemCount[z]; //just re-using variable
						item_count += Math.Floor( zoneDmg ) ;
					}
					item_count = Math.Max( (item_count * (meatCountMod + 0.2)) + 1, 1);
				}
				if ( item_to_spawn == "Bone" || item_to_spawn == "ChickenFeather" )
				{
					item_count = Math.Max( (item_count * (meatCountMod + 0.5)), 1);
				}
				
				for ( int i2 = 0; i2 < item_count; i2++ )
				{
					ItemBase spawn_result = CreateOrgan( action_data.m_Player, bodyPosition, item_to_spawn, cfg_skinning_organ_class, action_data.m_MainItem );
					
					//Damage pelts based on the average values on itemZones
					//It only works if the "quantityCoef" in the config is more than 0 
					float qtCoeff = GetGame().ConfigGetFloat( cfg_skinning_organ_class + "quantityCoef");
					if(qtCoeff > 0)
					{
						float avgDmgZones = 0;
						for(int c2 = 0; c2 < itemZones.Count(); c2++ )
						{
							avgDmgZones += body.GetHealth01(itemZones[c2], "Health");
						}
						
						avgDmgZones = avgDmgZones/itemZones.Count(); // Evaluate the average Health
						avgDmgZones = avgDmgZones * skinningMod;
						
						if(spawn_result)
						{
							spawn_result.SetHealth01("","", avgDmgZones);
						}
					}
					
					if ( item_to_spawn == "Bone" || item_to_spawn == "Guts" || item_to_spawn == "SmallGuts" || item_to_spawn == "ChickenFeather" )
					{
						spawn_result.SetHealth01("", "", meatCountMod);
					}
					spawn_result.SetTemperature(38);
					
					// handle fat/guts from human bodies
				/*	if ( ( item_to_spawn == "Lard" ) || ( item_to_spawn == "Guts" ) )
					{
						if ( body.IsKindOf( "SurvivorBase" ) )
						{
							spawn_result.InsertAgent(eAgents.BRAIN, 1);
						}
					}*/
				}
			}
		}
	}
};