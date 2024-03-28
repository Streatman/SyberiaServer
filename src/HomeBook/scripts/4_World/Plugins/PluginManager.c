modded class PluginManager
{
	override void Init()
	{
		if (GetGame().IsServer())
		{
			RegisterPlugin("PluginBuildingSystem", false, true);
		}
	
		super.Init();
	}
}