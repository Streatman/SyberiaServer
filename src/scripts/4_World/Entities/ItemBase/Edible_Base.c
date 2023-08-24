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
};