modded class PrepareChicken
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		//-- SYBERIA
		float steak_quantity = 0;
		float feathers_quantity = 0;
		float meatCountMod = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_MEAT_COUNT, 0, 0);
		float skinningMod = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_SKINING, 0, 0);
		float quantityMin, quantityMax;
		float quantityMinCoef, quantityMaxCoef;
		//--
		
		ItemBase deadChicken = ingredients[0];
		ItemBase resultBones = results[0];
		
		int steakCount = 2;//Math.RandomIntInclusive(2,4);
		for (int i=0; i < steakCount; i++)
		{
			ItemBase result = ItemBase.Cast(player.SpawnEntityOnGroundOnCursorDir("ChickenBreastMeat", DEFAULT_SPAWN_DISTANCE));
			MiscGameplayFunctions.TransferItemProperties(deadChicken, result);
			
		//	quantityMin = Math.Clamp(quant_min_max_coef.Get(0), 0, quant_min_max_coef.Get(1));
			quantityMin = Math.Clamp(0.5, 0.0, 1);
		//	quantityMax = Math.Clamp(quant_min_max_coef.Get(1), quant_min_max_coef.Get(0), 1);
			quantityMax = Math.Clamp(1.0, 0.5, 1);
			quantityMinCoef = Math.Clamp(quantityMin * 0.2 + meatCountMod, quantityMin * 0.2, quantityMin);
			quantityMaxCoef = Math.Clamp(quantityMax * 0.3 + meatCountMod, quantityMax * 0.3, quantityMax);
			float coef = Math.RandomFloat(quantityMinCoef, quantityMaxCoef);
			steak_quantity = result.GetQuantityMax() * coef;
			steak_quantity = Math.Round(steak_quantity);
			
			result.SetQuantity( steak_quantity, false );
			result.SetTemperature(38);
		}
		
		ItemBase resultFeathers = ItemBase.Cast(player.SpawnEntityOnGroundOnCursorDir("ChickenFeather", DEFAULT_SPAWN_DISTANCE));
		MiscGameplayFunctions.TransferItemProperties(deadChicken, resultFeathers);
		feathers_quantity = Math.Max((Math.RandomIntInclusive(5,15) * (meatCountMod + 0.5)), 1);
		feathers_quantity = Math.Round(feathers_quantity);
		resultFeathers.SetQuantity( feathers_quantity, 1 );
		resultFeathers.SetHealth01("", "", skinningMod);
		
		MiscGameplayFunctions.TransferItemProperties(deadChicken, resultBones);
		resultBones.SetQuantity(Math.Max( (1 * (meatCountMod + 0.5)), 1));
		resultBones.SetHealth01("", "", skinningMod);
		
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
