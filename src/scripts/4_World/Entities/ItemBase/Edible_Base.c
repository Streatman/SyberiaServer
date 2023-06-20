modded class Edible_Base
{
	override void EEOnCECreate()
	{
		super.EEOnCECreate();
		if (IsFruit() && Math.RandomFloat01() < GetSyberiaConfig().m_dirtyFruitsSpawnChance)
		{
			InsertAgent(eAgents.FOOD_POISON, 1);
		}
		else if (IsMushroom() && Math.RandomFloat01() < GetSyberiaConfig().m_dirtyMushroomsSpawnChance)
		{
			InsertAgent(eAgents.FOOD_POISON, 1);
		}
	}
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
	
		ctx.Write( m_alreadySkinned );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
	
		if ( !ctx.Read( m_alreadySkinned ) )
		{
			m_alreadySkinned = false;
			return false;
		}
		
		return true;
	}
	
	void DoSkinning(PlayerBase butcher, ItemBase tool)
	{
		if (m_alreadySkinned)
			return;
		
		vector body_pos = GetPosition();
		
		ItemBase added_item;
		float meatCountMod = butcher.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_MEAT_COUNT, 0, 0);
		float skinningMod = butcher.GetPerkFloatValue(SyberiaPerkType.SYBPERK_HUNTING_SKINING, 0, 0);
		string skinningCfg = CFG_VEHICLESPATH + " " + GetType() + " Skinning";
		int skinningChildsCount = GetGame().ConfigGetChildrenCount(skinningCfg);
		string itemName;
		float count;
		float quantityMin, quantityMax;
		string skinningChildName;
		
		for (int childId = 0; childId < skinningChildsCount; childId++)
		{
			if (GetGame().ConfigGetChildName(skinningCfg, childId, skinningChildName))
			{
				itemName = GetGame().ConfigGetTextOut(skinningCfg + " " + skinningChildName + " item");
				count = GetGame().ConfigGetFloat(skinningCfg + " " + skinningChildName + " count");
				
				vector pos_rnd = body_pos + Vector(Math.RandomFloat01() - 0.5, 0, Math.RandomFloat01() - 0.5);
				
				if (skinningChildName == "ObtainedSteaks")
				{
					if (count > 0) 
					{
						count = Math.Max((count * (meatCountMod + 0.2)) + 1, 1);
						quantityMin = Math.Clamp(0.2 + meatCountMod, 0.2, 0.9);
						quantityMax = Math.Clamp(0.3 + meatCountMod, 0.3, 1.0);
						
						while (count > 0)
						{
							count = count - 1.0;
							added_item = ItemBase.Cast(GetGame().CreateObjectEx( itemName, pos_rnd, ECE_PLACE_ON_SURFACE ));
							if (added_item)
							{
								added_item.SetQuantity(Math.Round(Math.RandomFloat(quantityMin, quantityMax) * added_item.GetQuantityMax()), false);
								added_item.InsertAgent(eAgents.SALMONELLA, 1);
								added_item.SetTemperature(38);
							}
						}
					}
				}
				else if (skinningChildName == "ObtainedBones")
				{
					if (count > 0) 
					{
						count = Math.Max((count * (meatCountMod + 0.5)), 1);
						quantityMin = Math.Clamp(0.2 + meatCountMod, 0.2, 0.9);
						quantityMax = Math.Clamp(0.3 + meatCountMod, 0.3, 1.0);
						
						while (count > 0)
						{
							count = count - 1.0;
							added_item = ItemBase.Cast(GetGame().CreateObjectEx( itemName, pos_rnd, ECE_PLACE_ON_SURFACE ));
							if (added_item)
							{
								added_item.SetQuantity(Math.Round(Math.RandomFloat(quantityMin, quantityMax) * added_item.GetQuantityMax()), false);
								added_item.InsertAgent(eAgents.SALMONELLA, 1);
								added_item.SetTemperature(38);
								added_item.SetHealth01("", "", meatCountMod);
							}
						}
					}
				}
				else if (skinningChildName == "ObtainedGuts")
				{
					if (count > 0) 
					{
						quantityMin = Math.Clamp(0.2 + meatCountMod, 0.2, 0.9);
						quantityMax = Math.Clamp(0.3 + meatCountMod, 0.3, 1.0);
						
						while (count > 0)
						{
							count = count - 1.0;
							added_item = ItemBase.Cast(GetGame().CreateObjectEx( itemName, pos_rnd, ECE_PLACE_ON_SURFACE ));
							if (added_item) {
								added_item.SetQuantity(Math.Round(Math.RandomFloat(quantityMin, quantityMax) * added_item.GetQuantityMax()), false);
								added_item.InsertAgent(eAgents.SALMONELLA, 1);
								added_item.SetTemperature(38);
								added_item.SetHealth01("", "", meatCountMod);
							}
						}
					}
				}
				else if (skinningChildName == "ObtainedPelt")
				{
					added_item = ItemBase.Cast(GetGame().CreateObjectEx( itemName, pos_rnd, ECE_PLACE_ON_SURFACE ));
					if (added_item)
					{
						added_item.SetTemperature(38);
						added_item.SetHealth01("", "", skinningMod);
					}
				}
				else if (skinningChildName == "ObtainedFeathers")
				{
					if (count > 0) 
					{
						count = Math.Max((count * (meatCountMod + 0.5)), 1);
					//	quantityMin = Math.Clamp(0.2 + meatCountMod, 0.2, 0.9);
					//	quantityMax = Math.Clamp(0.3 + meatCountMod, 0.3, 1.0);
						
						while (count > 0)
						{
							count = count - 1.0;
							added_item = ItemBase.Cast(GetGame().CreateObjectEx( itemName, pos_rnd, ECE_PLACE_ON_SURFACE ));
							if (added_item)
							{
								added_item.SetHealth01("", "", skinningMod);
							}
						}
					}
				}
				else
				{
					while (count > 0)
					{
						count = count - 1.0;
						ItemBase.Cast(GetGame().CreateObjectEx( itemName, pos_rnd, ECE_PLACE_ON_SURFACE ));
					}
				}
			}
		}
		
		m_alreadySkinned = true;
		butcher.AddExperience(SyberiaSkillType.SYBSKILL_HUNTING, GetSyberiaConfig().m_skillsExpHuntingButchSmall);
		SetHealth01("", "", 0);
		SetSynchDirty();
		
		ItemBase gloves = butcher.GetItemOnSlot("Gloves");
		if (gloves)
		{
			gloves.SetCleanness(0);
		}
		else
		{
			butcher.SetBloodyHands(true);
		}
	}
};