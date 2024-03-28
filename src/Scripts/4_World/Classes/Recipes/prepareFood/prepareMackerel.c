modded class PrepareMackerel
{
	override void Init()
	{
		m_Name = "#STR_gutandprepare0";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 1.5;//animation length in relative time units
		m_Specialty = 0.02;// value > 0 for roughness, value < 0 for precision
		
		
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0,"Mackerel");//you can insert multiple ingredients this way

		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;// 0 = do nothing
		m_IngredientDestroy[0] = true;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"Sickle");//you can insert multiple ingredients this way
		InsertIngredient(1,"KukriKnife");
		InsertIngredient(1,"FangeKnife");
		InsertIngredient(1,"Hacksaw");
		InsertIngredient(1,"HandSaw");
		InsertIngredient(1,"KitchenKnife");
		InsertIngredient(1,"SteakKnife");
		InsertIngredient(1,"StoneKnife");
		InsertIngredient(1,"Cleaver");
		InsertIngredient(1,"CombatKnife");
		InsertIngredient(1,"HuntingKnife");
		InsertIngredient(1,"Machete");
		InsertIngredient(1,"CrudeMachete");
		InsertIngredient(1,"OrientalMachete");
		InsertIngredient(1,"WoodAxe");
		InsertIngredient(1,"Hatchet");
		InsertIngredient(1,"FirefighterAxe");
		InsertIngredient(1,"Sword");
		InsertIngredient(1,"AK_Bayonet");
		InsertIngredient(1,"M9A1_Bayonet");
		InsertIngredient(1,"SKS_Bayonet");
		InsertIngredient(1,"BoneKnife");
		InsertIngredient(1,"Screwdriver");
		
		m_IngredientAddHealth[1] = -12;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = true;// set 'true' to allow modification of the values by softskills on this ingredient
	}
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		//-- SYBERIA
		float fillet_quantity = 0;
		float meatCountMod = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_MEAT_COUNT, 0, 0);
		float skinningMod = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_SKINING, 0, 0);
		float quantityMin, quantityMax;
		float quantityMinCoef, quantityMaxCoef;
		//--
		
		ItemBase deadMackerel = ingredients[0];
		
		int filletCount = 2;
		for (int i=0; i < filletCount; i++)
		{
			ItemBase result = ItemBase.Cast(player.SpawnEntityOnGroundOnCursorDir("MackerelFilletMeat", DEFAULT_SPAWN_DISTANCE));
			MiscGameplayFunctions.TransferItemProperties(deadMackerel, result);
			
		//	quantityMin = Math.Clamp(quant_min_max_coef.Get(0), 0, quant_min_max_coef.Get(1));
			quantityMin = Math.Clamp(0.5, 0.0, 1);
		//	quantityMax = Math.Clamp(quant_min_max_coef.Get(1), quant_min_max_coef.Get(0), 1);
			quantityMax = Math.Clamp(1.0, 0.5, 1);
			quantityMinCoef = Math.Clamp(quantityMin * 0.2 + meatCountMod, quantityMin * 0.2, quantityMin);
			quantityMaxCoef = Math.Clamp(quantityMax * 0.3 + meatCountMod, quantityMax * 0.3, quantityMax);
			float coef = Math.RandomFloat(quantityMinCoef, quantityMaxCoef);
			fillet_quantity = result.GetQuantityMax() * coef;
			fillet_quantity = Math.Round(fillet_quantity);
			
			result.SetQuantity( fillet_quantity, false );
			result.SetTemperature(10);
		}
		
		//-- SYBERIA
		ItemBase gloves = player.GetItemOnSlot("Gloves");
		if (gloves)
		{
			gloves.SetCleanness(0);
		}
		else
		{
			player.SetBloodyHands(true);
		}
		
		player.AddExperience(SyberiaSkillType.SYBSKILL_HUNTING, GetSyberiaConfig().m_skillsExpHuntingButchSmall);
		
		//--
		PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
		module_lifespan.UpdateBloodyHandsVisibility( player, true );
	}
	override void ApplyModificationsIngredients(ItemBase sorted[], PlayerBase player)
	{
		//---------------------- ingredients ----------------------
		for(int i = 0; i < MAX_NUMBER_OF_INGREDIENTS; i++)
		{
			ItemBase ingredient = sorted[i];
			
			if( m_IngredientDestroy[i] == 1 )//<------m_IngredientDestroy
			{
				if( ingredient ) m_IngredientsToBeDeleted.Insert(ingredient);
			}
			else
			{
				float skill = 1 - player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_TOOLS, 0, 0);
				float dmgValue = GetSyberiaConfig().m_animalsButchingKnifeDamage;
				float decreaseHealthValue = skill * dmgValue * 0.25;
				MiscGameplayFunctions.DealAbsoluteDmg(ingredient, decreaseHealthValue);
			}
		}
	}
	
/*	override float GetLengthInSecs()
	{
		float skinTime = 15;
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		float skillModifier = 1 - player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_BUTCH_SPEED, 0, 0);
		
		skinTime = Math.Max(1, skinTime * skillModifier);
		
		return skinTime;//m_AnimationLength * CRAFTING_TIME_UNIT_SIZE;
	}*/
};
