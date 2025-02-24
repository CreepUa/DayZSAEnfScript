enum SurfaceAnimationBone
{
	LeftFrontLimb = 0,
	RightFrontLimb,
	LeftBackLimb,
	RightBackLimb
}

enum PlantType
{
	TREE_HARD		= 1000,
	TREE_SOFT		= 1001,
	BUSH_HARD		= 1002,	
	BUSH_SOFT		= 1003,
}

class EntityAI extends Entity
{
	bool 					m_DeathSyncSent;
	bool 					m_KilledByHeadshot;
	ref KillerData 			m_KillerData;
	
	ref array<EntityAI> 	m_AttachmentsWithCargo;
	ref array<EntityAI> 	m_AttachmentsWithAttachments;
	ref InventoryLocation 	m_OldLocation;
	
	float					m_Weight;
	
	//Called on item attached to this item (EntityAI item, string slot, EntityAI parent)
	protected ref ScriptInvoker		m_OnItemAttached;
	//Called on item detached from this item (EntityAI item, string slot, EntityAI parent)
	protected ref ScriptInvoker		m_OnItemDetached;
	//Called when an item is added to the cargo of this item (EntityAI item, EntityAI parent)
	protected ref ScriptInvoker		m_OnItemAddedIntoCargo;
	//Called when an item is removed from the cargo of this item (EntityAI item, EntityAI parent)
	protected ref ScriptInvoker		m_OnItemRemovedFromCargo;
	//Called when an item is moved around in the cargo of this item (EntityAI item, EntityAI parent)
	protected ref ScriptInvoker		m_OnItemMovedInCargo;
	//Called when an item is flipped around in cargo (bool flip)
	protected ref ScriptInvoker		m_OnItemFlipped;
	//Called when an items view index is changed 
	protected ref ScriptInvoker		m_OnViewIndexChanged;
	//Called when an location in this item is reserved (EntityAI item) - cargo
	protected ref ScriptInvoker		m_OnSetLock;
	//Called when this item is unreserved (EntityAI item) - cargo
	protected ref ScriptInvoker		m_OnReleaseLock;
	//Called when an location in this item is reserved (EntityAI item) - attachment
	protected ref ScriptInvoker		m_OnAttachmentSetLock;
	//Called when this item is unreserved (EntityAI item) - attachment
	protected ref ScriptInvoker		m_OnAttachmentReleaseLock;
	
	void EntityAI ()
	{
		// Set up the Energy Manager
		string type = GetType();
		string param_access_energy_sys = "CfgVehicles " + type + " EnergyManager ";
		bool is_electic_device = GetGame().ConfigIsExisting(param_access_energy_sys);

		if (is_electic_device) // TO DO: Check if this instance is a hologram (advanced placement). If Yes, then do not create Energy Manager component.
		{
			CreateComponent(COMP_TYPE_ENERGY_MANAGER);
			m_EM = ComponentEnergyManager.Cast(  CreateComponent(COMP_TYPE_ENERGY_MANAGER));
			RegisterNetSyncVariableBool("m_EM.m_IsSwichedOn");
			RegisterNetSyncVariableBool("m_EM.m_CanWork");
			RegisterNetSyncVariableBool("m_EM.m_IsPlugged");
			RegisterNetSyncVariableInt ("m_EM.m_EnergySourceNetworkIDLow");
			RegisterNetSyncVariableInt ("m_EM.m_EnergySourceNetworkIDHigh");
		}
		
		// Item preview index
		RegisterNetSyncVariableInt( "m_ViewIndex", 0, 99 );
		
		m_AttachmentsWithCargo			= new array<EntityAI>;
		m_AttachmentsWithAttachments	= new array<EntityAI>;
		//m_NewLocation 					= new InventoryLocation;
		//m_OldLocation 					= new InventoryLocation;
	}
	
	void ~EntityAI()
	{
		
	}

	private ref ComponentsBank m_ComponentsBank;
	ComponentEnergyManager m_EM; // This reference is necesarry due to synchronization, since it's impossible to synchronize values from a component :(

	//! CreateComponent
	Component CreateComponent(int comp_type, string extended_class_name="")
	{
		return GetComponent(comp_type, extended_class_name);
	}

	//! GetComponent
	Component GetComponent(int comp_type, string extended_class_name="")
	{
		if ( m_ComponentsBank == NULL )
			m_ComponentsBank = new ComponentsBank(this);
		
		return m_ComponentsBank.GetComponent(comp_type, extended_class_name);
	}

	//! DeleteComponent
	bool DeleteComponent(int comp_type)
	{
		return m_ComponentsBank.DeleteComponent(comp_type);
	}
	
	//! IsComponentExist
	bool HasComponent(int comp_type)
	{
		if ( m_ComponentsBank )
			return m_ComponentsBank.IsComponentAlreadyExist(comp_type);
		
		return false;
	}

	//! Log
	void Log(string msg, string fnc_name = "n/a")
	{
		Debug.Log(msg, "Object", "n/a", fnc_name, this.GetType());
	}

	//! LogWarning
	void LogWarning(string msg, string fnc_name = "n/a")
	{
		Debug.LogWarning(msg, "Object", "n/a", fnc_name, this.GetType());
	}

	//! LogError
	void LogError(string msg, string fnc_name = "n/a")
	{
		Debug.LogError(msg, "Object", "n/a", fnc_name, this.GetType());
	}

	///@{ Skinning
	bool IsSkinned()
	{
		return GetCompBS() && GetCompBS().IsSkinned();
	}

	void SetAsSkinned()
	{
		if (GetCompBS())
			GetCompBS().SetAsSkinned();
	}

	bool CanBeSkinnedWith(EntityAI tool)
	{
		if ( !IsSkinned()  &&  tool )
			if ( !IsAlive()  &&  tool.ConfigGetBool("canSkinBodies") )
				return true;
		return false;
	}
	///@} Skinning

	// ITEM TO ITEM FIRE DISTRIBUTION
	//! Override this method to return TRUE when this item has or can provide fire. Evaluated on server and client.
	bool HasFlammableMaterial()
	{
		return false;
	}
	
	//! Override this method so it checks whenever this item can be ignited right now or not. Evaluated on Server and Client.
	bool CanBeIgnitedBy(EntityAI igniter = NULL)
	{
		return false;
	}
	
	//! Override this method and check if the given item can be ignited right now by this one. Evaluated on Server and Client.
	bool CanIgniteItem(EntityAI ignite_target = NULL)
	{
		return false;
	}
	
	//! Override this method and make it so it returns whenever this item is on fire right now or not. Evaluated on Server and Client.
	bool IsIgnited()
	{
		if ( HasEnergyManager() )
			return GetCompEM().IsWorking(); // This code is optional, it's just what's most likely to be used in your items.
		
		return false;
	}
	
	//! Executed on Server when this item ignites some target item
	void OnIgnitedTarget( EntityAI target_item)
	{
		
	}
	
	//! Executed on Server when some item ignited this one
	void OnIgnitedThis( EntityAI fire_source)
	{
		
	}
	
	//! Executed on Server when this item failed to ignite target item
	void OnIgnitedTargetFailed( EntityAI target_item)
	{
		
	}
	
	//! Executed on Server when some item failed to ignite this one
	void OnIgnitedThisFailed( EntityAI fire_source)
	{
		
	}
	
	//! Final evaluation just before the target item is actually ignited. Evaluated on Server.
	bool IsTargetIgnitionSuccessful(EntityAI item_target)
	{
		return true;
	}
	
	//! Final evaluation just before this item is actually ignited from fire source. Evaluated on Server.
	bool IsThisIgnitionSuccessful(EntityAI item_source = NULL)
	{
		return true;
	}
	// End of fire distribution ^
	
	// ADVANCED PLACEMENT EVENTS
	void OnPlacementStarted( Man player ) { }
		
	void OnHologramBeingPlaced( Man player ) { }
	
	void OnPlacementComplete( Man player ) { }

	void OnPlacementCancelled( Man player )
	{
		if ( HasEnergyManager() )
		{
			Man attached_to = Man.Cast( GetHierarchyParent() );
			if (!attached_to  ||  attached_to == player )// Check for exception with attaching a cable reel to an electric fence
				GetCompEM().UnplugThis();
		}
	}
	
	bool CanBePlaced( Man player, vector position ) { return true; }

	//! Method which returns message why object can't be placed at given position
	string CanBePlacedFailMessage( Man player, vector position )
	{
		return "";
	}	
	
	//! is this container empty or not, checks both cargo and attachments
	bool IsEmpty()
	{
		return (!HasAnyCargo() && GetInventory().AttachmentCount() == 0);
	}

	//! is this container empty or not, checks only cargo
	bool HasAnyCargo()
	{
		CargoBase cargo = GetInventory().GetCargo();
		
		if(!cargo) return false;//this is not a cargo container
		
		if( cargo.GetItemCount() > 0 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	array<EntityAI> GetAttachmentsWithCargo()
	{
		return m_AttachmentsWithCargo;
	}
	
	array<EntityAI> GetAttachmentsWithAttachments()
	{
		return m_AttachmentsWithAttachments;
	}

	int GetAgents() { return 0; }
	void RemoveAgent(int agent_id);
	void RemoveAllAgents();
	void RemoveAllAgentsExcept(int agent_to_keep);
	void InsertAgent(int agent, float count = 1);

	override bool IsEntityAI() { return true; }
	
	bool IsInventoryVisible()
	{
		return !( GetParent() || GetHierarchyParent() );
	}
	
	bool IsPlayer()
	{
		return false;
	}
	
	bool IsAnimal()
	{
		return false;
	}
	
	bool IsZombie()
	{
		return false;
	}
	
	bool IsZombieMilitary()
	{
		return false;
	}

	/**@brief Delete this object in next frame
	 * @return \p void
	 *
	 * @code
	 *			ItemBase item = GetGame().GetPlayer().CreateInInventory("GrenadeRGD5");
	 *			item.Delete();
	 * @endcode
	**/
	void Delete()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(GetGame().ObjectDelete, this);
	}
	void DeleteOnClient()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call(GetGame().ObjectDeleteOnClient, this);
	}
	
	//! Returns root of current hierarchy (for example: if this entity is in Backpack on gnd, returns Backpack)
	proto native EntityAI GetHierarchyRoot();

	//! Returns root of current hierarchy cast to Man
	proto native Man GetHierarchyRootPlayer();
	
	//! Returns direct parent of current entity
	proto native EntityAI GetHierarchyParent();

	//! Get economy item profile (if assigned, otherwise null)
	proto native CEItemProfile GetEconomyProfile();

	//! Called upon object creation
	void EEInit()
	{
		if (GetInventory())
		{
			GetInventory().EEInit();
			m_AttachmentsWithCargo.Clear();
			m_AttachmentsWithAttachments.Clear();
			for( int i = 0; i < GetInventory().AttachmentCount(); i++ )
			{
				EntityAI attachment = GetInventory().GetAttachmentFromIndex( i );
				if( attachment )
				{
					if( attachment.GetInventory().GetCargo() )
					{
						m_AttachmentsWithCargo.Insert( attachment );
					}
					
					if( attachment.GetInventory().GetAttachmentSlotsCount() > 0 )
					{
						m_AttachmentsWithAttachments.Insert( attachment );
					}
				}
			}
			UpdateWeight();
		}
	}
	
	//! Called right before object deleting
	void EEDelete(EntityAI parent)
	{
		GetInventory().EEDelete(parent);
		
		if ( HasEnergyManager() )
			GetCompEM().OnDeviceDestroyed();
	}
	
	void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner) { }
	
	void OnItemAttachmentSlotChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc) {}
	
	void EEItemLocationChanged (notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
		EntityAI old_owner = oldLoc.GetParent();
		EntityAI new_owner = newLoc.GetParent();
		OnItemLocationChanged(old_owner, new_owner);
		
		if (oldLoc.GetType() == InventoryLocationType.ATTACHMENT && newLoc.GetType() == InventoryLocationType.ATTACHMENT)
		{
			OnItemAttachmentSlotChanged(oldLoc,newLoc);
		}
		
		if (oldLoc.GetType() == InventoryLocationType.ATTACHMENT)
		{
			if (old_owner)
				OnWasDetached(old_owner, oldLoc.GetSlot());
			else
				Error("EntityAI::EEItemLocationChanged - detached, but old_owner is null");
		}
		
		if (newLoc.GetType() == InventoryLocationType.ATTACHMENT)
		{
			if (new_owner)
				OnWasAttached(newLoc.GetParent(), newLoc.GetSlot());
			else
				Error("EntityAI::EEItemLocationChanged - attached, but new_owner is null");
		}
	}
	
	void EEInventoryIn (Man newParentMan, EntityAI diz, EntityAI newParent)
	{
	}
	void EEInventoryOut (Man oldParentMan, EntityAI diz, EntityAI newParent)
	{
		if (GetInventory() && newParent == null)
		{
			GetInventory().ResetFlipCargo();
		}
	}

	void EEAmmoChanged()
	{
		
	}

	void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		// Notify potential parent that this item was ruined
		EntityAI parent = GetHierarchyParent();
		
		if (parent)
		{
			parent.OnAttachmentRuined(this);
		}
	}

	void EEKilled(Object killer)
	{
		//analytics
		GetGame().GetAnalyticsServer().OnEntityKilled( killer, this );
	}
	
	//! Called when some attachment of this parent is ruined. Called on server and client side.
	void OnAttachmentRuined(EntityAI attachment)
	{
		// ...
	}
	
	void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		//Print("EEHitByRemote: damageType: "+ damageType +"; source: "+ source +"; component: "+ component +"; dmgZone: "+ dmgZone +"; ammo: "+ ammo +"; modelPos: "+ modelPos);
	}
	
	// called only on the client who caused the hit
	void EEHitByRemote(int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos)
	{
		
	}
	
	// !Called on PARENT when a child is attached to it.
	void EEItemAttached(EntityAI item, string slot_name)
	{
		UpdateWeight();
		
		//Print (slot_name);
		if ( m_ComponentsBank != NULL )
		{
			for ( int comp_key = 0; comp_key < COMP_TYPE_COUNT; ++comp_key )
			{
				if ( m_ComponentsBank.IsComponentAlreadyExist(comp_key) )
				{
					m_ComponentsBank.GetComponent(comp_key).Event_OnItemAttached(item, slot_name);
				}
			}
		}
		
		
		
		// Energy Manager
		if ( this.HasEnergyManager()  &&  item.HasEnergyManager() )
		{
			GetCompEM().OnAttachmentAdded(item); // Inner code is meant to be executed client and server side to avoid unnecesarry network synchronization
		}
		
		if( item.GetInventory().GetCargo() )
		{
			m_AttachmentsWithCargo.Insert( item );
		}
		
		if( item.GetInventory().GetAttachmentSlotsCount() > 0 )
		{
			m_AttachmentsWithAttachments.Insert( item );
		}
		
		if( m_OnItemAttached )
			m_OnItemAttached.Invoke( item, slot_name, this );
		//SwitchItemSelectionTexture(item, slot_name);
	}
	
	// !switches materials and/or textures of cloting items on player
	void SwitchItemSelectionTexture(EntityAI item, string slot_name)
	{
	}
	
	// !Called on PARENT when a child is detached from it.
	void EEItemDetached(EntityAI item, string slot_name)
	{
		UpdateWeight();
		
		if ( m_ComponentsBank != NULL )
		{
			for ( int comp_key = 0; comp_key < COMP_TYPE_COUNT; ++comp_key )
			{
				if ( m_ComponentsBank.IsComponentAlreadyExist(comp_key) )
				{
					m_ComponentsBank.GetComponent(comp_key).Event_OnItemDetached(item, slot_name);
				}
			}
		}
		
		// Energy Manager
		if ( this.HasEnergyManager()  &&  item.HasEnergyManager() )
		{
			GetCompEM().OnAttachmentRemoved(item);
		}
		
		if( m_AttachmentsWithCargo.Find( item ) > -1 )
		{
			m_AttachmentsWithCargo.RemoveItem( item );
		}
		
		if( m_AttachmentsWithAttachments.Find( item ) > -1 )
		{
			m_AttachmentsWithAttachments.RemoveItem( item );
		}
		
		
		
		if( m_OnItemDetached )
			m_OnItemDetached.Invoke( item, slot_name, this );
		//SwitchItemSelectionTexture(item, slot_name);
	}

	void EECargoIn(EntityAI item)
	{
		UpdateWeight();
		
		if( m_OnItemAddedIntoCargo )
			m_OnItemAddedIntoCargo.Invoke( item, this );
		item.OnMovedInsideCargo(this);
	}

	void EECargoOut(EntityAI item)
	{
		UpdateWeight();
		
		if( m_OnItemRemovedFromCargo )
			m_OnItemRemovedFromCargo.Invoke( item, this );
		item.OnRemovedFromCargo(this);
	}

	void EECargoMove(EntityAI item)
	{
		if( m_OnItemMovedInCargo )
			m_OnItemMovedInCargo.Invoke( item, this );
		item.OnMovedWithinCargo(this);
	}
	
	ScriptInvoker GetOnItemAttached()
	{
		if( !m_OnItemAttached )
			m_OnItemAttached = new ScriptInvoker;
		return m_OnItemAttached;
	}
	
	ScriptInvoker GetOnItemDetached()
	{
		if( !m_OnItemDetached )
			m_OnItemDetached = new ScriptInvoker;
		return m_OnItemDetached;
	}
	
	ScriptInvoker GetOnItemAddedIntoCargo()
	{
		if( !m_OnItemAddedIntoCargo )
			m_OnItemAddedIntoCargo = new ScriptInvoker;
		return m_OnItemAddedIntoCargo;
	}
	
	ScriptInvoker GetOnItemRemovedFromCargo()
	{
		if( !m_OnItemRemovedFromCargo )
			m_OnItemRemovedFromCargo = new ScriptInvoker;
		return m_OnItemRemovedFromCargo;
	}
	
	ScriptInvoker GetOnItemMovedInCargo()
	{
		if( !m_OnItemMovedInCargo )
			m_OnItemMovedInCargo = new ScriptInvoker;
		return m_OnItemMovedInCargo;
	}
	
	ScriptInvoker GetOnItemFlipped()
	{
		if( !m_OnItemFlipped )
			m_OnItemFlipped = new ScriptInvoker;
		return m_OnItemFlipped;
	}
	
	ScriptInvoker GetOnViewIndexChanged()
	{
		if( !m_OnViewIndexChanged )
			m_OnViewIndexChanged = new ScriptInvoker;
		return m_OnViewIndexChanged;
	}
	
	ScriptInvoker GetOnSetLock()
	{
		if( !m_OnSetLock )
			m_OnSetLock = new ScriptInvoker;
		return m_OnSetLock;
	}
	
	ScriptInvoker GetOnReleaseLock()
	{
		if( !m_OnReleaseLock )
			m_OnReleaseLock = new ScriptInvoker;
		return m_OnReleaseLock;
	}
	
	ScriptInvoker GetOnAttachmentSetLock()
	{
		if( !m_OnAttachmentSetLock )
			m_OnAttachmentSetLock = new ScriptInvoker;
		return m_OnAttachmentSetLock;
	}
	
	ScriptInvoker GetOnAttachmentReleaseLock()
	{
		if( !m_OnAttachmentReleaseLock )
			m_OnAttachmentReleaseLock = new ScriptInvoker;
		return m_OnAttachmentReleaseLock;
	}
	
	
	//! Called when this item enters cargo of some container
	void OnMovedInsideCargo(EntityAI container)
	{
		if ( HasEnergyManager() )
		{
			GetCompEM().HandleMoveInsideCargo(container);
		}
	}
	
	//! Called when this item exits cargo of some container
	void OnRemovedFromCargo(EntityAI container)
	{
	
	}
	
	//! Called when this item moves within cargo of some container
	void OnMovedWithinCargo(EntityAI container)
	{
	
	}
	
	//! Called when entity is part of "connected system" and being restored after load
	void EEOnAfterLoad()
	{
		// ENERGY MANAGER
		// Restore connections between devices which were connected before server restart
		if ( HasEnergyManager()  &&  GetCompEM().GetRestorePlugState() )
		{
			int b1 = GetCompEM().GetEnergySourceStorageIDb1();
			int b2 = GetCompEM().GetEnergySourceStorageIDb2();
			int b3 = GetCompEM().GetEnergySourceStorageIDb3();
			int b4 = GetCompEM().GetEnergySourceStorageIDb4();

			// get pointer to EntityAI based on this ID
			EntityAI potential_energy_source = GetGame().GetEntityByPersitentID(b1, b2, b3, b4); // This function is available only in this event!
			
			// IMPORTANT!
			// Object IDs acquired here become INVALID when electric devices are transfered to another server while in plugged state (like Flashlight plugged into its attachment 9V battery)
			// To avoid issues, these items must be excluded from this system of restoring plug state so they don't unintentionally plug to incorrect devices through these invalid IDs.
			// Therefore their plug state is being restored withing the EEItemAttached() event while being excluded by the following 'if' conditions...
			
			bool is_attachment = false;
			
			if (potential_energy_source)
				is_attachment = GetInventory().HasAttachment(potential_energy_source);
			
			if ( !is_attachment	&&	potential_energy_source )
				is_attachment = potential_energy_source.GetInventory().HasAttachment(this);
			
			if ( potential_energy_source  &&  potential_energy_source.GetCompEM()  &&  potential_energy_source.HasEnergyManager()  &&  !is_attachment )
			{
				GetCompEM().PlugThisInto(potential_energy_source); // restore connection
			}
		}
	}
	
	//! Called when entity is being created as new by CE/ Debug
	void EEOnCECreate()
	{
	}

	//! Called when entity is being loaded from DB or Storage (after all children loaded)
	void AfterStoreLoad()
	{
	}

	//! Checks if this instance is of type DayZCreature
	bool IsDayZCreature()
	{
		return false;
	}
	
	//! Sets all animation values to 1, making them INVISIBLE if they are configured in models.cfg in such way. These selections must also be defined in the entity's config class in 'AnimationSources'. 
	void HideAllSelections()
	{
		string cfg_path = "cfgVehicles " + GetType() + " AnimationSources";
		
		if ( GetGame().ConfigIsExisting(cfg_path) )
		{
			int	selections = GetGame().ConfigGetChildrenCount(cfg_path);
			
			for (int i = 0; i < selections; i++)
			{
				string selection_name;
				GetGame().ConfigGetChildName(cfg_path, i, selection_name);
				HideSelection(selection_name);
			}
		}
	}
	
	//! Sets all animation values to 0, making them VISIBLE if they are configured in models.cfg in such way. These selections must also be defined in the entity's config class in 'AnimationSources'. 
	void ShowAllSelections()
	{
		string cfg_path = "cfgVehicles " + GetType() + " AnimationSources";
		
		if ( GetGame().ConfigIsExisting(cfg_path) )
		{
			int	selections = GetGame().ConfigGetChildrenCount(cfg_path);
			
			for (int i = 0; i < selections; i++)
			{
				string selection_name;
				GetGame().ConfigGetChildName(cfg_path, i, selection_name);
				ShowSelection(selection_name);
			}
		}
	}
	
	/**@fn		CanReceiveAttachment
	 * @brief calls this->CanReceiveAttachment(attachment)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, attachment, "CanReceiveAttachment");
	 **/
	bool CanReceiveAttachment (EntityAI attachment, int slotId)
	{
		return true;
	}

	/**@fn		CanPutAsAttachment
	 * @brief	calls this->CanPutAsAttachment(parent)
	 * @param[in] child	\p	item to be put as attachment of a parent
	 * @return	true if action allowed
	 *
	 * @note: engine code is scriptConditionExecute(this, parent, "CanPutAsAttachment")
	 **/
	bool CanPutAsAttachment (EntityAI parent)
	{
		return !IsHologram();
	}
	/**@fn		CanReleaseAttachment
	 * @brief calls this->CanReleaseAttachment(attachment)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, attachment, "CanReleaseAttachment");
	 **/
	bool CanReleaseAttachment (EntityAI attachment)
	{
		if( attachment && attachment.GetInventory() && GetInventory() )
		{
			InventoryLocation il = new InventoryLocation;
			attachment.GetInventory().GetCurrentInventoryLocation( il );
			if( il.IsValid() )
			{
				int slot = il.GetSlot();
				return !GetInventory().GetSlotLock( slot );
			}
		}
		return true;
	}
	/**@fn		CanDetachAttachment
	 * @brief	calls this->CanDetachAttachment(parent)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, parent, "CanDetachAttachment");
	 **/
	bool CanDetachAttachment (EntityAI parent)
	{
		return true;
	}

	/**@fn		CanReceiveItemIntoCargo
	 * @brief	calls this->CanReceiveItemIntoCargo(cargo)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, cargo, "CanReceiveItemIntoCargo");
	 **/
	bool CanReceiveItemIntoCargo (EntityAI cargo)
	{
		if (GetInventory() && GetInventory().GetCargo())
			return GetInventory().GetCargo().CanReceiveItemIntoCargo(cargo));
		
		return true;
	}
	/**@fn		CanPutInCargo
	 * @brief	calls this->CanPutInCargo(parent)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, parent, "CanPutInCargo");
	 **/
	bool CanPutInCargo (EntityAI parent)
	{
		return !IsHologram();
	}

	/**@fn		CanSwapItemInCargo
	 * @brief	calls this->CanSwapItemInCargo(child_entity, new_entity)
	 * @return	true if action allowed
	 *
	 * @note: return ScriptConditionExecute(GetOwner(), child_entity, "CanSwapItemInCargo", new_entity);
	 **/
	bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{
		if (GetInventory() && GetInventory().GetCargo())
			return GetInventory().GetCargo().CanSwapItemInCargo(child_entity, new_entity));
		
		return true;
	}

	/**@fn		CanReleaseCargo
	 * @brief	calls this->CanReleaseCargo(cargo)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, cargo, "CanReleaseCargo");
	 **/
	bool CanReleaseCargo (EntityAI cargo)
	{
		return true;
	}

	/**@fn		CanRemoveFromCargo
	 * @brief	calls this->CanRemoveFromCargo(parent)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, parent, "CanRemoveFromCargo");
	 **/
	bool CanRemoveFromCargo (EntityAI parent)
	{
		return true;
	}
	
	/**@fn		CanReceiveItemIntoInventory
	 * @brief calls this->CanReceiveItemIntoInventory(item)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, , "CanReceiveItemIntoInventory");
	 **/
	/*bool CanReceiveItemIntoInventory (EntityAI entity_ai)
	{
		return true;
	}*/

	/**@fn		CanPutInInventory
	 * @brief calls this->CanPutInInventory(parent)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, parent, "ConditionIntoInventory");
	 **/
	/*bool CanPutInInventory (EntityAI parent)
	{
		return true;
	}*/

	/**@fn		CanReceiveItemIntoHands
	 * @brief	calls this->CanReceiveItemIntoHands(item_to_hands)
	 * @return	true if action allowed
	 *
	 * @note: scriptConditionExecute(this, item_to_hands, "CanReceiveItemIntoHands");
	 **/
	bool CanReceiveItemIntoHands (EntityAI item_to_hands)
	{
		return true;
	}
	
	bool IsBeingPlaced()
	{
		return false;
	}
	
	bool IsHologram()
	{
		return false;
	}
	
	bool CanSaveItemInHands (EntityAI item_in_hands)
	{
		return true;
	}

	/**@fn		CanPutIntoHands
	 * @brief calls this->CanPutIntoHands(parent)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, parent, "CanPutIntoHands");
	 **/
	bool CanPutIntoHands (EntityAI parent)
	{
		return !IsHologram();
	}

	/**@fn		CanReleaseFromHands
	 * @brief calls this->CanReleaseFromHands(handheld)
	 * @return	true if action allowed
	 *
	 * @note: scriptConditionExecute(this, handheld, "CanReleaseFromHands");
	 **/
	bool CanReleaseFromHands (EntityAI handheld)
	{
		return true;
	}

	/**@fn		CanRemoveFromHands
	 * @brief	calls this->CanRemoveFromHands(parent)
	 * @return	true if action allowed
	 *
	 * @note: return scriptConditionExecute(this, parent, "CanRemoveFromHands");
	 **/
	bool CanRemoveFromHands (EntityAI parent)
	{
		return true;
	}

	/**@fn		CanDisplayAttachmentSlot
	 * @param	slot_name->name of the attachment slot that will or won't be displayed
	 * @return	true if attachment icon can be displayed in UI (inventory)
	 **/	
	bool CanDisplayAttachmentSlot( string slot_name )
	{
		return true;
	}

	/**@fn		CanDisplayAttachmentCategory
	 * @param	category_name->name of the attachment category that will or won't be displayed
	 * @return	true if attachment icon can be displayed in UI (inventory)
	 **/		
	bool CanDisplayAttachmentCategory( string category_name )
	{
		return true;
	}
	
	/**@fn		CanDisplayCargo
	 * @return	true if cargo can be displayed in UI (inventory)
	 **/		
	bool CanDisplayCargo()
	{
		return true;
	}	
	
	/**@fn		IgnoreOutOfReachCondition
	 * @return	if true, attachment condition for out of reach (inventory) will be ignored
	 **/		
	bool IgnoreOutOfReachCondition()
	{
		return GetHierarchyRootPlayer() == GetGame().GetPlayer();
	}	

	// !Called on CHILD when it's attached to parent.
	void OnWasAttached( EntityAI parent, int slot_id ) { }
		
	// !Called on CHILD when it's detached from parent.
	void OnWasDetached( EntityAI parent, int slot_id ) { }
	
	proto native GameInventory GetInventory ();
	proto native void CreateAndInitInventory ();
	proto native void DestroyInventory ();
		
	int GetSlotsCountCorrect()
	{
		if( GetInventory() )
			return GetInventory().GetAttachmentSlotsCount();
		else
			return -1;
	}

	EntityAI FindAttachmentBySlotName(string slot_name)
	{
		if ( GetGame() )
		{
			int slot_id = InventorySlots.GetSlotIdFromString(slot_name);
			if (slot_id != InventorySlots.INVALID)
				return GetInventory().FindAttachment(slot_id); 
		}
		return null;
	}

	/**@fn		IsLockedInSlot
	 * @return	true if entity is locked in attachment slot
	 **/	
	bool IsLockedInSlot()
	{
		EntityAI parent = GetHierarchyParent();
		if ( parent )
		{
			InventoryLocation inventory_location = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( inventory_location );
			
			return parent.GetInventory().GetSlotLock( inventory_location.GetSlot() );
		}
		
		return false;
	}
	
	/**
	\brief Put item anywhere into this entity (as attachment or into cargo, recursively)
	*/
	bool PredictiveTakeEntityToInventory (FindInventoryLocationType flags, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToInventory(InventoryMode.PREDICTIVE, flags, item);
	}
	bool LocalTakeEntityToInventory (FindInventoryLocationType flags, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToInventory(InventoryMode.LOCAL, flags, item);
	}
	bool ServerTakeEntityToInventory (FindInventoryLocationType flags, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToInventory(InventoryMode.SERVER, flags, item);
	}
	bool PredictiveTakeEntityToTargetInventory (notnull EntityAI target, FindInventoryLocationType flags, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToTargetInventory(InventoryMode.PREDICTIVE, target, flags, item);
	}
	bool LocalTakeEntityToTargetInventory (notnull EntityAI target, FindInventoryLocationType flags, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToTargetInventory(InventoryMode.LOCAL, target, flags, item);
	}
	bool ServerTakeEntityToTargetInventory (notnull EntityAI target, FindInventoryLocationType flags, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToTargetInventory(InventoryMode.SERVER, target, flags, item);
	}
	/**
	\brief Put item into into cargo
	*/
	bool PredictiveTakeEntityToCargo (notnull EntityAI item)
	{
		return GetInventory().TakeEntityToCargo(InventoryMode.PREDICTIVE, item);
	}
	bool LocalTakeEntityToCargo (notnull EntityAI item)
	{
		return GetInventory().TakeEntityToCargo(InventoryMode.LOCAL, item);
	}
	bool ServerTakeEntityToCargo (notnull EntityAI item)
	{
		return GetInventory().TakeEntityToCargo(InventoryMode.SERVER, item);
	}

	bool PredictiveTakeEntityToTargetCargo (notnull EntityAI target, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToTargetCargo(InventoryMode.PREDICTIVE, target, item);
	}
	bool LocalTakeEntityToTargetCargo (notnull EntityAI target, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToTargetCargo(InventoryMode.LOCAL, target, item);
	}
	bool ServerTakeEntityToTargetCargo (notnull EntityAI target, notnull EntityAI item)
	{
		return GetInventory().TakeEntityToTargetCargo(InventoryMode.SERVER, target, item);
	}
	/**
	\brief Put item into into cargo on specific cargo location
	*/
	bool PredictiveTakeEntityToCargoEx (notnull EntityAI item, int idx, int row, int col)
	{
		return GetInventory().TakeEntityToCargoEx(InventoryMode.PREDICTIVE, item, idx, row, col);
	}
	bool LocalTakeEntityToCargoEx (notnull EntityAI item, int idx, int row, int col)
	{
		return GetInventory().TakeEntityToCargoEx(InventoryMode.LOCAL, item, idx, row, col);
	}

	bool PredictiveTakeEntityToTargetCargoEx (notnull CargoBase cargo, notnull EntityAI item, int row, int col)
	{
		return GetInventory().TakeEntityToTargetCargoEx(InventoryMode.PREDICTIVE, cargo, item, row, col);
	}
	bool LocalTakeEntityToTargetCargoEx (notnull CargoBase cargo, notnull EntityAI item, int row, int col)
	{
		return GetInventory().TakeEntityToTargetCargoEx(InventoryMode.LOCAL, cargo, item, row, col);
	}
	bool ServerTakeEntityToTargetCargoEx (notnull CargoBase cargo, notnull EntityAI item, int row, int col)
	{
		return GetInventory().TakeEntityToTargetCargoEx(InventoryMode.SERVER, cargo, item, row, col);
	}
	/**
	\brief Returns if item can be added as attachment on specific slot. Note that slot index IS NOT slot ID! Slot ID is defined in DZ/data/config.cpp
	*/
	bool PredictiveTakeEntityAsAttachmentEx (notnull EntityAI item, int slot)
	{
		return GetInventory().TakeEntityAsAttachmentEx(InventoryMode.PREDICTIVE, item, slot);
	}
	bool LocalTakeEntityAsAttachmentEx (notnull EntityAI item, int slot)
	{
		return GetInventory().TakeEntityAsAttachmentEx(InventoryMode.LOCAL, item, slot);
	}
	bool ServerTakeEntityAsAttachmentEx (notnull EntityAI item, int slot)
	{
		return GetInventory().TakeEntityAsAttachmentEx(InventoryMode.SERVER, item, slot);
	}

	bool PredictiveTakeEntityToTargetAttachmentEx (notnull EntityAI target, notnull EntityAI item, int slot)
	{
		return GetInventory().TakeEntityAsTargetAttachmentEx(InventoryMode.PREDICTIVE, target, item, slot);
	}
	bool LocalTakeEntityToTargetAttachmentEx (notnull EntityAI target, notnull EntityAI item, int slot)
	{
		return GetInventory().TakeEntityAsTargetAttachmentEx(InventoryMode.LOCAL, target, item, slot);
	}
	bool ServerTakeEntityToTargetAttachmentEx (notnull EntityAI target, notnull EntityAI item, int slot)
	{
		return GetInventory().TakeEntityAsTargetAttachmentEx(InventoryMode.SERVER, target, item, slot);
	}

	bool PredictiveTakeEntityToTargetAttachment (notnull EntityAI target, notnull EntityAI item)
	{
		return GetInventory().TakeEntityAsTargetAttachment(InventoryMode.PREDICTIVE, target, item);
	}
	bool LocalTakeEntityToTargetAttachment (notnull EntityAI target, notnull EntityAI item)
	{
		return GetInventory().TakeEntityAsTargetAttachment(InventoryMode.LOCAL, target, item);
	}
	bool ServerTakeEntityToTargetAttachment (notnull EntityAI target, notnull EntityAI item)
	{
		return GetInventory().TakeEntityAsTargetAttachment(InventoryMode.SERVER, target, item);
	}

	bool PredictiveTakeToDst (notnull InventoryLocation src, notnull InventoryLocation dst)
	{
		return GetInventory().TakeToDst(InventoryMode.PREDICTIVE, src, dst);
	}
	bool LocalTakeToDst (notnull InventoryLocation src, notnull InventoryLocation dst)
	{
		return GetInventory().TakeToDst(InventoryMode.LOCAL, src, dst);
	}
	bool ServerTakeToDst (notnull InventoryLocation src, notnull InventoryLocation dst)
	{
		return GetInventory().TakeToDst(InventoryMode.SERVER, src, dst);
	}

	/**
	\brief Put item into as attachment
	*/
	bool PredictiveTakeEntityAsAttachment (notnull EntityAI item)
	{
		return GetInventory().TakeEntityAsAttachment(InventoryMode.PREDICTIVE, item);
	}
	bool LocalTakeEntityAsAttachment (notnull EntityAI item)
	{
		return GetInventory().TakeEntityAsAttachment(InventoryMode.LOCAL, item);
	}
	bool ServerTakeEntityAsAttachment (notnull EntityAI item)
	{
		return GetInventory().TakeEntityAsAttachment(InventoryMode.SERVER, item);
	}

	bool PredictiveDropEntity (notnull EntityAI item) { return false; }
	bool LocalDropEntity (notnull EntityAI item) { return false; }
	bool ServerDropEntity (notnull EntityAI item) { return false; }

	/**
	\brief Get attached entity by type
	*/
	EntityAI GetAttachmentByType(typename type)
	{
		for ( int i = 0; i < GetInventory().AttachmentCount(); i++ )
		{
			EntityAI attachment = GetInventory().GetAttachmentFromIndex ( i );
			if ( attachment && attachment.IsInherited ( type ) )
				return attachment;
			}
		return NULL;
	}

	/**
	\brief Get attached entity by config type name
	*/
	EntityAI GetAttachmentByConfigTypeName(string type)
	{
		for ( int i = 0; i < GetInventory().AttachmentCount(); i++ )
		{
			EntityAI attachment = GetInventory().GetAttachmentFromIndex ( i );
			if ( attachment.IsKindOf ( type ) )
				return attachment;
			}
		return NULL;
	}
	/**
	\brief Returns if item can be dropped out from this entity
	*/
	bool CanDropEntity (notnull EntityAI item) { return true; }

	/**
	 **/
	EntityAI SpawnEntityOnGroundPos (string object_name, vector pos)
	{
		InventoryLocation il = new InventoryLocation;
		vector mat[4];
		Math3D.MatrixIdentity4(mat);
		mat[3] = pos;
		il.SetGround(NULL, mat);
		return SpawnEntity(object_name, il,ECE_PLACE_ON_SURFACE,RF_DEFAULT);
	}
	/**
	 **/
	EntityAI SpawnEntityOnGround (string object_name, vector mat[4])
	{
		InventoryLocation il = new InventoryLocation;
		il.SetGround(NULL, mat);
		return SpawnEntity(object_name, il,ECE_PLACE_ON_SURFACE,RF_DEFAULT);
	}

	// Returns wetness value. This is just a necesarry forward declaration for Energy Manager which works with EntityAI. This function itself works in ItemBase where its overwritten.
	float GetWet()
	{
		return 0; // Only ItemBase objects have wetness!
	}
	
	//! Returns index of the string found in cfg array 'hiddenSelections'. If it's not found then it returns -1.
	int GetHiddenSelectionIndex( string selection )
	{
		array<string> config_selections	= new array<string>;
		string cfg_hidden_selections = "CfgVehicles" + " " + GetType() + " " + "hiddenSelections";
		GetGame().ConfigGetTextArray ( cfg_hidden_selections, config_selections );
		
		for (int i = 0; i < config_selections.Count(); ++i)
		{
			if ( config_selections.Get ( i ) == selection )
			{
				return i;
			}
		}
		
		return -1;
	}

	/**
	 * @fn		RegisterNetSyncVariableBool
	 * @brief	registers bool variable synchronized over network
	 *
	 * @param[in]	variableName	\p		which variable should be synchronized
	 **/	
	proto native void RegisterNetSyncVariableBool(string variableName);
	
	/**
	 * @fn		RegisterNetSyncVariableInt
	 * @brief	registers int variable synchronized over network
	 *
	 * @param[in]	variableName	\p		which variable should be synchronized
	 * @param[in]	minValue		\p		minimal value used for quantization (when minValue == maxValue, no quatization is done)
	 * @param[in]	maxValue		\p		maximal value used for quantization (when minValue == maxValue, no quatization is done)
	 **/	
	proto native void RegisterNetSyncVariableInt(string variableName, int minValue = 0, int maxValue = 0);
	
	/**
	 * @fn		RegisterNetSyncVariableFloat
	 * @brief	registers float variable synchronized over network
	 *
	 * @param[in]	variableName	\p		which variable should be synchronized
	 * @param[in]	minValue		\p		minimal value used for quantization (when minValue == maxValue, no quatization is done)
	 * @param[in]	maxValue		\p		maximal value used for quantization (when minValue == maxValue, no quatization is done)
	 * @param[in]	precision		\p		precision in number of digits after decimal point
	 **/	
	proto native void RegisterNetSyncVariableFloat(string variableName, float minValue = 0, float maxValue = 0, int precision = 1);

	proto native void SwitchLight(bool isOn);

	//! Simple hidden selection state; 0 == hidden
	proto native void SetSimpleHiddenSelectionState(int index, bool state);
	
	//! Change texture in hiddenSelections
	proto native void SetObjectTexture(int index, string texture_name);
	//! Change material in hiddenSelections
	proto native void SetObjectMaterial(int index, string mat_name);
		
	proto native bool	IsPilotLight();
	proto native void SetPilotLight(bool isOn);

	/**
	\brief Engine calls this function to collect data from entity to store for persistence (on server side).
	@code
	void OnStoreSave(ParamsWriteContext ctx)
	{
		// dont forget to propagate this call trough class hierarchy!
		super.OnStoreSave(ctx);

		// write any data (using params) you want to store
		int   a = 5;
		float b = 6.0;

		ctx.Write(a);
		ctx.Write(b);
	}
	@endcode
	*/
	void OnStoreSave(ParamsWriteContext ctx)
	{
		// Saving of energy related states
		if ( HasEnergyManager() )
		{
			// Save energy amount
			ctx.Write( GetCompEM().GetEnergy() );
			
			// Save passive/active state
			ctx.Write( GetCompEM().IsPassive() );
			
			// Save ON/OFF state
			ctx.Write( GetCompEM().IsSwitchedOn() );
			
			// Save plugged/unplugged state
			ctx.Write( GetCompEM().IsPlugged() );
			
			// ENERGY SOURCE
			// Save energy source IDs
			EntityAI energy_source = GetCompEM().GetEnergySource();
			int b1 = 0;
			int b2 = 0;
			int b3 = 0;
			int b4 = 0;

			if (energy_source)
			{
				energy_source.GetPersistentID(b1, b2, b3, b4);
			}

			ctx.Write( b1 ); // Save energy source block 1
			ctx.Write( b2 ); // Save energy source block 2
			ctx.Write( b3 ); // Save energy source block 3
			ctx.Write( b4 ); // Save energy source block 4
		}
	}
	
	/**
	\brief Called when data is loaded from persistence (on server side).
	@code
	void OnStoreLoad(ParamsReadContext ctx, int version)
	{
		// dont forget to propagate this call trough class hierarchy!
		if ( !super.OnStoreLoad(ctx, version) )
			return false;

		// read data loaded from game database (format and order of reading must be the same as writing!)
		int a;
		if ( !ctx.Read(a) )
			return false;

		float b;
		if ( !ctx.Read(b) )
			return false;

		return true;
	}
	@endcode
	*/
	bool OnStoreLoad (ParamsReadContext ctx, int version)
	{
		// Restoring of energy related states
		if ( HasEnergyManager() )
		{
			// Load energy amount
			float f_energy = 0;
			if ( !ctx.Read( f_energy ) )
				f_energy = 0;
			GetCompEM().SetEnergy(f_energy);
			
			// Load passive/active state
			bool b_is_passive = false;
			if ( !ctx.Read( b_is_passive ) )
				return false;
			GetCompEM().SetPassiveState(b_is_passive);
			
			// Load ON/OFF state
			bool b_is_on = false;
			if ( !ctx.Read( b_is_on ) )
			{
				GetCompEM().SwitchOn();
				return false;
			}
			
			// Load plugged/unplugged state
			bool b_is_plugged = false;
			if ( !ctx.Read( b_is_plugged ) )
				return false;
			
			// ENERGY SOURCE
			if ( version <= 103 )
			{
				// Load energy source ID low
				int i_energy_source_ID_low = 0; // Even 0 can be valid ID!
				if ( !ctx.Read( i_energy_source_ID_low ) )
					return false;
				
				// Load energy source ID high
				int i_energy_source_ID_high = 0; // Even 0 can be valid ID!
				if ( !ctx.Read( i_energy_source_ID_high ) )
					return false;
			}
			else
			{
				int b1 = 0;
				int b2 = 0;
				int b3 = 0;
				int b4 = 0;

				if ( !ctx.Read(b1) ) return false;
				if ( !ctx.Read(b2) ) return false;
				if ( !ctx.Read(b3) ) return false;
				if ( !ctx.Read(b4) ) return false;

				if ( b_is_plugged )
				{
					// Because function GetEntityByPersitentID() cannot be called here, ID values must be stored and used later.
					GetCompEM().StoreEnergySourceIDs( b1, b2, b3, b4 );
					GetCompEM().RestorePlugState(true);
				}
			}

			if (b_is_on)
			{
				GetCompEM().SwitchOn();
			}
		}
		return true;
	}

	//! Sets object synchronization dirty flag, which signalize that object wants to be synchronized (take effect only in MP on server side)
	proto native void SetSynchDirty();

	/**
	\brief Called on clients after receiving synchronization data from server.
	*/
	void OnVariablesSynchronized()
	{
		if ( HasEnergyManager() )
		{
			if ( GetGame().IsMultiplayer() )
			{
				bool is_on = GetCompEM().IsSwitchedOn();
				
				if (is_on != GetCompEM().GetPreviousSwitchState())
				{
					if (is_on)
						GetCompEM().SwitchOn();
					else
						GetCompEM().SwitchOff();
					;
				}
				
				int id_low = GetCompEM().GetEnergySourceNetworkIDLow();
				int id_High = GetCompEM().GetEnergySourceNetworkIDHigh();
				
				EntityAI energy_source = EntityAI.Cast( GetGame().GetObjectByNetworkId(id_low, id_High) );
				
				if (energy_source)
				{
					// Boris: The following prints are here to help fix DAYZ-37406. They will be removed when I find out what is causing the issue.
					Print(energy_source);
					Print(id_low);
					Print(id_High);
					Print(energy_source.GetCompEM());
					Print(this);
					
					if ( !energy_source.GetCompEM() )
					{
						string object = energy_source.GetType();
						Error("Synchronization error! Object " + object + " has no instance of the Energy Manager component!");
					}
					
					GetCompEM().PlugThisInto(energy_source);
					
				}
				else
				{
					GetCompEM().UnplugThis();
				}
				
				GetCompEM().DeviceUpdate();
				GetCompEM().StartUpdates();
			}
		}
	}

	proto native void SetAITargetCallbacks(AbstractAITargetCallbacks callbacks);

	override void EOnFrame(IEntity other, float timeSlice)
	{
		if ( m_ComponentsBank != NULL )
		{
			for ( int comp_key = 0; comp_key < COMP_TYPE_COUNT; ++comp_key )
			{
				if ( m_ComponentsBank.IsComponentAlreadyExist(comp_key) )
				{
					m_ComponentsBank.GetComponent(comp_key).Event_OnFrame(other, timeSlice);
				}
			}
		}
	}
	
	Shape DebugBBoxDraw()
	{
		return GetComponent(COMP_TYPE_ETITY_DEBUG).DebugBBoxDraw();
	}

	void DebugBBoxSetColor(int color)
	{
		GetComponent(COMP_TYPE_ETITY_DEBUG).DebugBBoxSetColor(color);
	}

	void DebugBBoxDelete()
	{
		GetComponent(COMP_TYPE_ETITY_DEBUG).DebugBBoxDelete();
	}

	Shape DebugDirectionDraw(float distance = 1)
	{
		return GetComponent(COMP_TYPE_ETITY_DEBUG).DebugDirectionDraw(distance);
	}

	void DebugDirectionSetColor(int color)
	{
		GetComponent(COMP_TYPE_ETITY_DEBUG).DebugDirectionSetColor(color);
	}

	void DebugDirectionDelete()
	{
		GetComponent(COMP_TYPE_ETITY_DEBUG).DebugDirectionDelete();
	}

	//! Hides selection of the given name. Must be configed in config.hpp and models.cfg
	void HideSelection( string selection_name )
	{
		if ( !ToDelete() )
		{
			SetAnimationPhase ( selection_name, 1 ); // 1 = hide, 0 = unhide!
		}
	}

	//! Shows selection of the given name. Must be configed in config.hpp and models.cfg
	void ShowSelection( string selection_name )
	{
		if ( !ToDelete() )
		{
			SetAnimationPhase ( selection_name, 0 ); // 1 = hide, 0 = unhide!
		}
	}

	//! Returns blocks of bits of persistence id of this entity.
	//! This id stays the same even after server restart.
	proto void GetPersistentID( out int b1, out int b2, out int b3, out int b4 );

	//! Set (override) remaining economy lifetime (seconds)
	proto native void SetLifetime( float fLifeTime );
	//! Get remaining economy lifetime (seconds)
	proto native float GetLifetime();
	//! Reset economy lifetime to default (seconds)
	proto native void IncreaseLifetime();

	// BODY STAGING
	//! Use this to access Body Staging component on dead character. Returns NULL if the given object lacks such component.
	ComponentBodyStaging GetCompBS()
	{
		if ( HasComponent(COMP_TYPE_BODY_STAGING) )
			return ComponentBodyStaging.Cast( GetComponent(COMP_TYPE_BODY_STAGING) );
		return NULL;
	}

	///@{ energy manager
	//! ENERGY MANAGER:Documentation: Confluence >> Camping & Squatting >> Electricity >> Energy Manager functionalities
	//! Use this to access Energy Manager component on your device. Returns NULL if the given object lacks such component.
	ComponentEnergyManager GetCompEM()
	{
		if ( HasComponent(COMP_TYPE_ENERGY_MANAGER) )
			return ComponentEnergyManager.Cast( GetComponent(COMP_TYPE_ENERGY_MANAGER) );
		return NULL;
	}

	//! If this item has class EnergyManager in its config then it returns true. Otherwise returns false.
	bool HasEnergyManager()
	{
		return HasComponent(COMP_TYPE_ENERGY_MANAGER);
	}

	// ------ Public Events for Energy manager component. Overwrite these and put your own functionality into them. ------

	//! Energy manager event: Called only once when this device starts doing its work
	void OnWorkStart() {}

	//! Energy manager event: Called every device update if its supposed to do some work. The update can be every second or at random, depending on its manipulation.
	void OnWork( float consumed_energy ) {}

	//! Energy manager event: Called when the device stops working (was switched OFF or ran out of energy)
	void OnWorkStop() {}

	//! Energy manager event: Called when the device is switched on
	void OnSwitchOn() {}

	//! Energy manager event: Called when the device is switched OFF
	void OnSwitchOff() {}

	//! Energy manager event: Called when this device is plugged into some energy source
	void OnIsPlugged(EntityAI source_device) {}

	//! Energy manager event: Called when this device is UNPLUGGED from the energy source
	void OnIsUnplugged( EntityAI last_energy_source ) {}

	//! Energy manager event: When something is plugged into this device
	void OnOwnSocketTaken( EntityAI device ) {}

	//! Energy manager event: When something is UNPLUGGED from this device
	void OnOwnSocketReleased( EntityAI device ) {}

	//! Energy manager event: Object's initialization. Energy Manager is fully initialized by this point.
	void OnInitEnergy() {}

	//! Energy manager event: Called when energy was consumed on this device. ALWAYS CALL super.OnEnergyConsumed() !!!
	void OnEnergyConsumed() {}

	//! Energy manager event: Called when energy was added on this device. ALWAYS CALL super.OnEnergyAdded() !!!
	void OnEnergyAdded() {}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		if ( GetGame().IsClient() )
		{
			switch(rpc_type)
			{
				// BODY STAGING - server => client synchronization of skinned state.
				case ERPCs.RPC_BS_SKINNED_STATE:
				{
					ref Param1<bool> p_skinned_state= new Param1<bool>(false);
					if (ctx.Read(p_skinned_state))
					{
						float state = p_skinned_state.param1;
						if (state && GetCompBS())
							GetCompBS().SetAsSkinnedClient();
					}
					break;
				}
				
				case ERPCs.RPC_EXPLODE_EVENT:
				{
					OnExplodeClient();
					
					break;
				}
			}
		}
	}
	///@} energy manager
	
	//calculates total weight of item
	int GetWeight()
	{
		return m_Weight;
	}
	
	void UpdateWeight();
	
	///@{ view index
	//! Item view index is used to setup which camera will be used in item view widget in inventory.
	//! With this index you can setup various camera angles for different item states (e.g. fireplace, weapons).
	int m_ViewIndex = 0;
	
	//! Sets item preview index
	void SetViewIndex( int index )
	{
		m_ViewIndex = index;
		
		if( GetGame().IsServer() ) 
		{
			SetSynchDirty();
		}
	}
	
	//! Returns item preview index !!!! IF OVERRIDING with more dynamic events call GetOnViewIndexChanged() in constructor on client !!!!
	int GetViewIndex()
	{
		if( MemoryPointExists( "invView2" ) )
		{
			#ifdef PLATFORM_WINDOWS
			InventoryLocation il = new InventoryLocation;
			GetInventory().GetCurrentInventoryLocation( il );
			InventoryLocationType type = il.GetType();
			switch( type )
			{
				case InventoryLocationType.CARGO:
				{
					return 0;
				}
				case InventoryLocationType.ATTACHMENT:
				{
					return 1;
				}
				case InventoryLocationType.HANDS:
				{
					return 0;
				}
				case InventoryLocationType.GROUND:
				{
					return 1;
				}
				case InventoryLocationType.PROXYCARGO:
				{
					return 0;
				}
				default:
				{
					return 0;
				}
			}
			#ifdef PLATFORM_CONSOLE
			return 1;
			#endif
			#endif
		}
		return 0;
	}
	///@} view index
	
	//! Returns hit component for the Entity (overriden for each Type - PlayerBase, DayZInfected, DayZAnimal, etc.)
	string GetHitComponentForAI()
	{
		Debug.LogError("EntityAI: HitComponentForAI not set properly for that entity (" + GetType() + ")");
		//! returns Global so it is obvious you need to configure that properly on entity
		return "";
	}

	//! returns default hit component for the Entity (overriden for each Type - PlayerBase, DayZInfected, DayZAnimal, etc.)
	string GetDefaultHitComponent()
	{
		Debug.LogError("EntityAI: DefaultHitComponent not set properly for that entity (" + GetType() + ")");
		//! returns Global so it is obvious you need to configure that properly on entity
		return "";
	}
	
	//! returns default hit position component name for the Entity (overriden by type if needed - used mainly as support for impact particles)
	string GetDefaultHitPositionComponent()
	{
		Debug.LogError("EntityAI: DefaultHitPositionComponent not set for that entity (" + GetType() + ")");
		return "";
	}
	
	array<string> GetSuitableFinisherHitComponents()
	{
		Debug.LogError("EntityAI: SuitableFinisherHitComponents not set for that entity (" + GetType() + ")");
		return null;
	}
	
	vector GetDefaultHitPosition()
	{
		Debug.LogError("EntityAI: DefaultHitPosition not set for that entity (" + GetType() + ")");
		return vector.Zero;
	}
	
	//! value is related to EMeleeTargetType
	int GetMeleeTargetType()
	{
		return EMeleeTargetType.ALIGNABLE;
	}
	
	//! returns sound type of attachment (used for clothing and weapons on DayZPlayerImplement, paired with Anim*Type enum from DayZAnimEvents)
	string GetAttachmentSoundType()
	{
		return "None";
	}
	
	//! returns item behaviour of item (more in ItemBase)
	bool IsHeavyBehaviour()
	{
		return false;
	}
	
	//! returns item behaviour of item (more in ItemBase)
	bool IsOneHandedBehaviour()
	{
		return false;
	}
	
	//! returns item behaviour of item (more in ItemBase)
	bool IsTwoHandedBehaviour()
	{
		return false;
	}
	
	string ChangeIntoOnAttach(string slot) {}
	string ChangeIntoOnDetach() {}
	
	void OnDebugSpawn() 
	{
		array<string> slots = new array<string>;
		ConfigGetTextArray("Attachments", slots);
		
		array<string> mags = new array<string>;
		ConfigGetTextArray("magazines", mags);
		
		//-------
		
		TStringArray all_paths = new TStringArray;
		
		all_paths.Insert(CFG_VEHICLESPATH);
		all_paths.Insert(CFG_MAGAZINESPATH);
		all_paths.Insert(CFG_WEAPONSPATH);
		
		string config_path;
		string child_name;
		int scope;
		string path;
		int consumable_count;
		
		for(int i = 0; i < all_paths.Count(); i++)
		{
			config_path = all_paths.Get(i);
			int children_count = GetGame().ConfigGetChildrenCount(config_path);
			
			for(int x = 0; x < children_count; x++)
			{
				GetGame().ConfigGetChildName(config_path, x, child_name);
				path = config_path + " " + child_name;
				scope = GetGame().ConfigGetInt( config_path + " " + child_name + " scope" );
				bool should_check = 1;
				if( config_path == "CfgVehicles" && scope == 0)
				{
					should_check = 0;
				}
				
				if ( should_check )
				{
					string inv_slot;
					GetGame().ConfigGetText( config_path + " " + child_name + " inventorySlot",inv_slot );
					for(int z = 0; z < slots.Count(); z++)
					{
						if(slots.Get(z) == inv_slot)
						{
							this.GetInventory().CreateInInventory( child_name );
							continue;
							//Print("matching attachment: " + child_name + " for inv. slot name:" +inv_slot);
						}
					}
				}
			}
		}
	};
	
	override EntityAI ProcessMeleeItemDamage(int mode = 0)
	{
		if ((GetGame().IsServer() || !GetGame().IsMultiplayer()))
			AddHealth("","Health",-MELEE_ITEM_DAMAGE);
		return this;
	}

	void SetBayonetAttached(bool pState, int slot_idx = -1) {};
	bool HasBayonetAttached() {};
	int GetBayonetAttachmentIdx() {};
	
	void SetButtstockAttached(bool pState, int slot_idx = -1) {};
	bool HasButtstockAttached() {};
	int GetButtstockAttachmentIdx() {};
	
	void SetInvisibleRecursive(bool invisible, EntityAI parent = null, array<int> attachments = null)
	{
		array<int> childrenAtt = new array<int>;
		array<int> attachmentsArray = new array<int>;
		if (attachments)
			attachmentsArray.Copy(attachments);
		else
		{
			for (int i = 0; i < GetInventory().GetAttachmentSlotsCount(); i++)
			{
				attachmentsArray.Insert(GetInventory().GetAttachmentSlotId(i));
			}
		}
		
		EntityAI item;
		
		foreach( int slot : attachmentsArray )
		{
			if( parent )
				item = parent.GetInventory().FindAttachment(slot);
			else
				item = this;//GetInventory().FindAttachment(slot);
			
			if( item )
			{
				if( item.GetInventory().AttachmentCount() > 0 )
				{
					for(i = 0; i < item.GetInventory().GetAttachmentSlotsCount(); i++)
					{
						childrenAtt.Insert(item.GetInventory().GetAttachmentSlotId(i));
					}
					
					SetInvisibleRecursive(invisible,item,childrenAtt);
				}
				
				item.SetInvisible(invisible);
			}
		}
	}
	
	void SoundHardTreeFallingPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "hardTreeFall_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
		
	void SoundSoftTreeFallingPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "softTreeFall_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
		
	void SoundHardBushFallingPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "hardBushFall_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
		
	void SoundSoftBushFallingPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "softBushFall_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
};
