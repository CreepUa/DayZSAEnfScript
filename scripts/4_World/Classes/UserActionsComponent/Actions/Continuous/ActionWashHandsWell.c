class ActionWashHandsWellCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(UATimeSpent.WASH_HANDS);
	}
};

class ActionWashHandsWell: ActionContinuousBase
{
	void ActionWashHandsWell()
	{
		m_CallbackClass 	= ActionWashHandsWellCB;
		m_CommandUID		= DayZPlayerConstants.CMD_ACTIONFB_WASHHANDSWELL;
		m_FullBody			= true;
		m_StanceMask		= DayZPlayerConstants.STANCEMASK_CROUCH;
	}

	override string GetText()
	{
		return "#wash_hands";
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( player.HasBloodyHands() && !player.GetItemInHands() )
		{
			if (target.GetObject() && target.GetObject().IsWell() )
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
		module_lifespan.UpdateBloodyHandsVisibility( action_data.m_Player, false );
	}

	/*override void OnCompleteServer( ActionData action_data )
	{
		OnFinishProgressServer(action_data);
	}*/
};