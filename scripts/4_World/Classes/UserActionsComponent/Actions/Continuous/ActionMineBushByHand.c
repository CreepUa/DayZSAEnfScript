class ActionMineBushByHand: ActionMineBush
{
	void ActionMineBushByHand()
	{
		m_CallbackClass = ActionMineBushCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTCursor(1);
		m_ConditionItem = new CCINone;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( GetGame().IsMultiplayer() && GetGame().IsServer() )
				return true;
		
		if (super.ActionCondition(player, target, item))
		{
			if (!item)
				return true;
		}
		return false;
	}
};