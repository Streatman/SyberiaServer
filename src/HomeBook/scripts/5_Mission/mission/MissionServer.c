modded class MissionServer
{
	override void OnMissionStart()
	{
		super.OnMissionStart();
		
		PluginBuildingSystem buildingPlugin = PluginBuildingSystem.Cast(GetPlugin(PluginBuildingSystem));
		if (buildingPlugin)
		{
			buildingPlugin.LoadLivespaces();
		}
	}
};