class PluginZones extends PluginBase
{
	ref PluginZones_Config m_config;
	int m_uniqueId = 1;
	
	override void OnInit()
	{
		MakeDirectory("$profile:Syberia");

		string path = "$profile:Syberia\\ZonesConfig.json";
		if (FileExist(path))
		{
			m_config = new PluginZones_Config;
			JsonFileLoader<ref PluginZones_Config>.JsonLoadFile(path, m_config);
			if (m_config && m_config.m_customZones)
			{
				int i = 0;
				while (i < m_config.m_customZones.Count())
				{
					ref ZoneDefinition zone = m_config.m_customZones.Get(i);
					if (zone.m_id >= m_uniqueId)
					{
						m_uniqueId = zone.m_id + 1;
					}
					
					if (zone.m_spawnChance == 1.0 || Math.RandomFloat01() < zone.m_spawnChance)
					{
						i = i + 1;			
					}
					else
					{
						m_config.m_customZones.Remove(i);						
					}
				}				
			}
		}
	}
	
	int AddObjectiveZone(EntityAI object)
	{
		if (m_config && m_config.m_customZones)
		{
			ref ZoneDefinition zone = new ZoneDefinition();
			zone.m_id = m_uniqueId;
			zone.m_position = object.GetPosition();
			zone.m_radius = object.ConfigGetFloat("radius");
			zone.m_height = object.ConfigGetFloat("height");
			zone.m_enterMessage = object.ConfigGetString("enterMessage");
			zone.m_leaveMessage = object.ConfigGetString("leaveMessage");
			zone.m_leaveTime = object.ConfigGetFloat("leaveTime");
			zone.m_godMode = object.ConfigGetInt("godMode");
			zone.m_inverseDammage = object.ConfigGetInt("inverseDammage");
			zone.m_blockBuildingMode = object.ConfigGetInt("blockBuildingMode");
			zone.m_blockInteractionWithPlayers = object.ConfigGetInt("blockInteractionWithPlayers");
			zone.m_radiation = object.ConfigGetFloat("radiation");
			zone.m_psi = object.ConfigGetFloat("psi");
			zone.m_gas = object.ConfigGetFloat("gas");
			zone.m_spawnChance = 1.0;
			
			m_uniqueId = m_uniqueId + 1;
			m_config.m_customZones.Insert(zone);
			
			return zone.m_id;
		}
		else
		{
			return -1;
		}
	}
	
	void DeleteObjectiveZone(EntityAI object, int id)
	{
		if (m_config && m_config.m_customZones && id > 0)
		{
			for (int i = 0; i < m_config.m_customZones.Count(); i++)
			{
				ref ZoneDefinition zone = m_config.m_customZones.Get(i);
				if (zone.m_id == id)
				{
					m_config.m_customZones.Remove(i);
					
					delete zone;
					return;
				}
			}
		}
	}
	
	void ~PluginZones()
	{
		if (m_config)
			delete m_config;
	}
};

class PluginZones_Config
{
	ref ZoneDefinition m_defaultZone;
	
	ref array<ref ZoneDefinition> m_customZones;
	
	void ~PluginZones_Config()
	{
		if (m_defaultZone)
		{
			delete m_defaultZone;
		}
		
		if (m_customZones)
		{
			foreach (ref ZoneDefinition zone : m_customZones)
			{
				delete zone;
			}
			
			delete m_customZones;
		}
	}
};