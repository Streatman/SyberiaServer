modded class SyberiaDatabaseInit
{
	override static void InitIfNot()
	{
		if (!m_initialized)
		{
			TStringArray queries = new TStringArray;
			// Init queries start
			PluginBuildingSystem.InitQueries(queries);
			// Init queries end
		}
		super.InitIfNot();
	}
};