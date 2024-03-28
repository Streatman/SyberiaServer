class CfgPatches
{
	class SyberiaServer_HomeBook
	{
		units[]={};
		requiredAddons[]=
		{
			"SyberiaServer"
		};
	};
};

class CfgMods
{
	class IntenZ_SyberiaServer_HomeBook
	{
		type="mod";
		
		dependencies[]={"World","Mission"};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]={"IntenZ\SyberiaServer\HomeBook\Scripts\4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"IntenZ\SyberiaServer\HomeBook\Scripts\5_Mission"};
			};
		};
	};
};
