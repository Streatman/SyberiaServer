modded class CAContinuousFill
{
	protected float		m_QuantityFilled;
	
	override void CalcAndSetQuantity( ActionData action_data )
	{
		m_QuantityFilled += m_QuantityFilledPerSecond * action_data.m_Player.GetDeltaT();
		float m_temperature = action_data.m_MainItem.GetTemperature();
		float m_ReplenishedQuantity = Math.InverseLerp(action_data.m_MainItem.GetQuantityMin(), action_data.m_MainItem.GetQuantityMax(), m_QuantityFilled);
		float m_addedTemperature;
		
		if (action_data.m_Target.GetObject() && (action_data.m_Target.GetObject().GetWaterSourceObjectType() == EWaterSourceObjectType.WELL || action_data.m_Target.GetObject().IsWell()))
		{
			float m_TemperatureWell = 4;
			m_addedTemperature = Math.Lerp(0, m_TemperatureWell - m_temperature, m_ReplenishedQuantity);
			action_data.m_MainItem.AddTemperature(m_addedTemperature);
		}
		else
		{
			float m_TemperaturePond = GetSyberiaConfig().m_temperatureFillWaterBottleTotal;
			m_addedTemperature = Math.Lerp(0, m_TemperaturePond - m_temperature, m_ReplenishedQuantity);
			action_data.m_MainItem.AddTemperature(m_addedTemperature);
		}
		
		super.CalcAndSetQuantity( action_data );
	}
};
