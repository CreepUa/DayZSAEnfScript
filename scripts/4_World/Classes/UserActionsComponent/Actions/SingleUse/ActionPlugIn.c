class ActionPlugIn: ActionSingleUseBase
{
	void ActionPlugIn()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
	}
		
	override string GetText()
	{
		return "#plug_in";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		ItemBase target_IB = ItemBase.Cast( target.GetObject() );
		
		if ( target_IB  &&  item )
		{
			if ( item.HasEnergyManager()  &&  !item.GetCompEM().IsPlugged()  &&  target_IB.HasEnergyManager()  &&  target_IB.GetCompEM().CanReceivePlugFrom(item) )
			{
				return true;
			}
			
			ItemBase attached_device = GetAttachedDevice(target_IB);
			
			if (attached_device)
			{
				return true;
			}
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		ItemBase target_IB = ItemBase.Cast( targetObject );
		
		if ( target_IB.HasEnergyManager() )
		{
			ItemBase attached_device = GetAttachedDevice(target_IB);
			
			if (attached_device)
			{
				target_IB = attached_device;
			}
			
			action_data.m_MainItem.GetCompEM().PlugThisInto(target_IB);
		
			if ( !action_data.m_Player.IsPlacingServer() )
			{
				Process(action_data);
			}
		}
	}
	
	void Process( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		ItemBase target_IB = ItemBase.Cast( targetObject );

		target_IB.GetInventory().TakeEntityAsAttachment( InventoryMode.LOCAL, action_data.m_MainItem );
	}
	
	override void OnExecuteClient( ActionData action_data )
	{	
		if ( !action_data.m_Player.IsPlacingLocal() )
		{
			action_data.m_Player.TogglePlacingLocal();
		}
		else
		{
			Process(action_data);
		}
	}
	
	ItemBase GetAttachedDevice(ItemBase parent)
	{
		string parent_type = parent.GetType();
		
		if ( parent.IsInherited(CarBattery)  ||  parent.IsInherited(TruckBattery) )
		{
			ItemBase parent_attachment = ItemBase.Cast( parent.GetAttachmentByType(MetalWire) );
			
			if (!parent_attachment)
			{
				parent_attachment = ItemBase.Cast( parent.GetAttachmentByType(BarbedWire) );
			}
			return parent_attachment;
		}
		
		return NULL;
	}
};