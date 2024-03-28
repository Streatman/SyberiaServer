modded class PrepareRabbit
{
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		//-- SYBERIA
		float leg_quantity = 0;
		float meatCountMod = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_MEAT_COUNT, 0, 0);
		float skinningMod = player.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_SKINING, 0, 0);
		float quantityMin, quantityMax;
		float quantityMinCoef, quantityMaxCoef;
		//--
		
		ItemBase deadRabbit = ingredients[0];
		ItemBase resultBones = results[0];
		
		int legCount = 2;//Math.RandomIntInclusive(2,4);
		for (int i=0; i < legCount; i++)
		{
			ItemBase result = ItemBase.Cast(player.SpawnEntityOnGroundOnCursorDir("RabbitLegMeat", DEFAULT_SPAWN_DISTANCE));
			MiscGameplayFunctions.TransferItemProperties(deadRabbit, result);
			
		//	quantityMin = Math.Clamp(quant_min_max_coef.Get(0), 0, quant_min_max_coef.Get(1));
			quantityMin = Math.Clamp(0.5, 0.0, 1);
		//	quantityMax = Math.Clamp(quant_min_max_coef.Get(1), quant_min_max_coef.Get(0), 1);
			quantityMax = Math.Clamp(1.0, 0.5, 1);
			quantityMinCoef = Math.Clamp(quantityMin * 0.2 + meatCountMod, quantityMin * 0.2, quantityMin);
			quantityMaxCoef = Math.Clamp(quantityMax * 0.3 + meatCountMod, quantityMax * 0.3, quantityMax);
			float coef = Math.RandomFloat(quantityMinCoef, quantityMaxCoef);
			leg_quantity = result.GetQuantityMax() * coef;
			leg_quantity = Math.Round(leg_quantity);
			
			result.SetQuantity( leg_quantity, false );
			result.SetTemperature(38);
		}
		
		MiscGameplayFunctions.TransferItemProperties(deadRabbit, resultBones);
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
