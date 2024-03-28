modded class CAContinuousQuantityLiquidTransfer
{
	protected float		m_QuantityFilled;
	
	override void CalcAndSetQuantity( ActionData action_data )
	{
		m_QuantityFilled += m_QuantityUsedPerSecond * action_data.m_Player.GetDeltaT();
		ItemBase target_item = ItemBase.Cast(action_data.m_Target.GetObject());
		float temperature = action_data.m_MainItem.GetTemperature();
		float target_temperature = target_item.GetTemperature();
		float m_ReplenishedQuantity = Math.InverseLerp(action_data.m_MainItem.GetQuantityMin(), action_data.m_MainItem.GetQuantityMax(), m_QuantityFilled);
		float target_ReplenishedQuantity = Math.InverseLerp(target_item.GetQuantityMin(), target_item.GetQuantityMax(), m_QuantityFilled);
		float m_addedTemperature;
		
		if ( m_TendencyDrain )
		{
			m_addedTemperature = Math.Lerp(0, target_temperature - temperature, m_ReplenishedQuantity);
			action_data.m_MainItem.AddTemperature(m_addedTemperature);
		}
		else
		{
			m_addedTemperature = Math.Lerp(0, temperature - target_temperature, target_ReplenishedQuantity);
			target_item.AddTemperature(m_addedTemperature);
		}
		
		super.CalcAndSetQuantity( action_data );
	}
};
