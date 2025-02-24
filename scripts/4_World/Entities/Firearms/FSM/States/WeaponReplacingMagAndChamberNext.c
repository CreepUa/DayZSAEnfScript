/**@class		DetachOldMagazine
 * @brief		detaches old magazine from weapon and stores it in left hand (LH)
 **/
class DetachOldMagazine extends WeaponStateBase
{
	Magazine m_oldMagazine; /// magazine that will be detached

	void DetachOldMagazine (Weapon_Base w = NULL, WeaponStateBase parent = NULL)
	{
		m_oldMagazine = NULL;
	}
	
	override void OnEntry (WeaponEventBase e)
	{
		super.OnEntry(e);
	}

	override void OnAbort (WeaponEventBase e)
	{
		super.OnAbort(e);
		m_oldMagazine = NULL;
	}

	override void OnExit (WeaponEventBase e)
	{
		if (m_oldMagazine )
		{			
			InventoryLocation il = new InventoryLocation;
			e.m_player.GetInventory().FindFreeLocationFor( m_oldMagazine , FindInventoryLocationType.CARGO, il );			
			
			if(!il || !il.IsValid())
			{
				if (DayZPlayerUtils.HandleDropMagazine(e.m_player, m_oldMagazine))
					wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, ok - no inventory space for old magazine - dropped to ground");
				else
					Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, error - cannot drop magazine from left hand after not found inventory space for old magazine");
				
			}
			else
			{
				InventoryLocation oldSrc = new InventoryLocation;
				m_oldMagazine.GetInventory().GetCurrentInventoryLocation(oldSrc);
				
				if (GameInventory.LocationSyncMoveEntity(oldSrc, il))
				{
					wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, ok - old magazine removed from wpn (LHand->inv)");
				}
				else
					Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, error - cannot remove old mag from wpn");
			}
		}
		else
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, error - no magazines configured for replace (m_old=m_oldSrc=NULL)");
				
		m_weapon.HideMagazine();
		m_oldMagazine = NULL;
		super.OnExit(e);
	}
	
	override bool SaveCurrentFSMState (ParamsWriteContext ctx)
	{
		if (!super.SaveCurrentFSMState(ctx))
			return false;

		if (!ctx.Write(m_oldMagazine))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine.SaveCurrentFSMState: cannot write m_oldMagazine for weapon=" + m_weapon);
			return false;
		}

		return true;
	}

	override bool LoadCurrentFSMState (ParamsReadContext ctx, int version)
	{
		if (!super.LoadCurrentFSMState(ctx, version))
			return false;

		if (!ctx.Read(m_oldMagazine))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine.LoadCurrentFSMState: cannot read m_oldMagazine for weapon=" + m_weapon);
			return false;
		}
		return true;
	}
};

/**@class		OldMagazineHide
 * @brief		hides old magazine, but keep it in LH
 * @note		on abort, old magazine is dropped to ground
 **/
class OldMagazineHide : MagazineHide
{
};

/**@class		SwapOldAndNewMagazine
 * @brief		old magazine to inventory, new to left hand
 *
 * stores old magazine in left hand somewhere in inventory (or drop to ground if necessary)
 * and moves new magazine to left hand.
 * on abort new magazine is dropped to ground.
 **/
class SwapOldAndNewMagazine extends WeaponStateBase
{
	Magazine m_newMagazine; /// magazine that will be dropped on abort
	ref InventoryLocation m_newDst;

	override void OnEntry (WeaponEventBase e)
	{
		super.OnEntry(e);
		
		if (!m_newMagazine || !m_newDst || !m_newDst.IsValid())
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " SwapOldAndNewMagazine, error - m_newMagazine(" + m_newMagazine + ") or destination(" + InventoryLocation + ") is not set ");
		}
		else
		{
			m_weapon.ShowMagazine();
			InventoryLocation lhand = new InventoryLocation;
			m_newMagazine.GetInventory().GetCurrentInventoryLocation(lhand);
			
			if (GameInventory.LocationSyncMoveEntity(lhand, m_newDst))
			{
				wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " SwapOldAndNewMagazine, ok - new magazine removed from inv (LHand->Att)");
			}
			else
				Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " SwapOldAndNewMagazine, error - cannot remove new mag from LHand");
		}
	}
	
	override void OnAbort (WeaponEventBase e)
	{
		//m_weapon.HideMagazine();

		m_newMagazine = NULL;
		m_newDst = NULL;

		super.OnAbort(e);
	}

	override void OnExit (WeaponEventBase e)
	{
		m_newMagazine = NULL;
		m_newDst = NULL;

		super.OnExit(e);
	}
	
	override bool SaveCurrentFSMState (ParamsWriteContext ctx)
	{
		if (!super.SaveCurrentFSMState(ctx))
			return false;

		if (!ctx.Write(m_newMagazine))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " SwapOldAndNewMagazine.SaveCurrentFSMState: cannot write m_newMagazine for weapon=" + m_weapon);
			return false;
		}
		
		if (!OptionalLocationWriteToContext(m_newDst, ctx))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " SwapOldAndNewMagazine.SaveCurrentFSMState: cannot write m_newDst for weapon=" + m_weapon);
			return false;
		}

		return true;
	}

	override bool LoadCurrentFSMState (ParamsReadContext ctx, int version)
	{
		if (!super.LoadCurrentFSMState(ctx, version))
			return false;

		if (!ctx.Read(m_newMagazine))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " SwapOldAndNewMagazine.LoadCurrentFSMState: cannot read m_newMagazine for weapon=" + m_weapon);
			return false;
		}
		if (!OptionalLocationReadFromContext(m_newDst, ctx))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " SwapOldAndNewMagazine.LoadCurrentFSMState: cannot read m_newDst for weapon=" + m_weapon);
			return false;
		}

		return true;
	}
};

/**@class		AttachNewMagazine
 * @brief		attach mag in LH into weapon
 **/
class AttachNewMagazine extends WeaponStateBase
{
	Magazine m_newMagazine; /// new magazine from inventory that will be attached
	ref InventoryLocation m_newDst;

	void AttachNewMagazine (Weapon_Base w = NULL, WeaponStateBase parent = NULL)
	{
		m_newMagazine = NULL;
		m_newDst = NULL;
	}
	
	override bool IsWaitingForActionFinish ()
	{
		return true;
	}

	override void OnEntry (WeaponEventBase e)
	{
		super.OnEntry(e);

		if (m_newMagazine && m_newDst)
		{
			InventoryLocation il = new InventoryLocation;
			if (m_newMagazine.GetInventory().GetCurrentInventoryLocation(il))
			{
				InventoryLocation lhand = new InventoryLocation;
				lhand.SetAttachment(e.m_player, m_newMagazine, InventorySlots.LEFTHAND);
				if (GameInventory.LocationSyncMoveEntity(il, m_newDst))
				{
					m_weapon.ShowMagazine();
					wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine, ok - attached new magazine (LHand->dst)");
				}
				else
				{
					wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine, error - cannot attach new magazine!");
				}
			}
			else
				Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine, error - cannot get curr location");
		}
		else
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine, error - no magazines configured for replace (m_new=NULL)");
	}

	override void OnAbort (WeaponEventBase e)
	{
		if (m_newMagazine && m_newDst)
		{
			if (DayZPlayerUtils.HandleDropMagazine(e.m_player, m_newMagazine))
				wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponDetachingMag_Store, ok - aborting, detached magazine dropped to ground");
			else
				Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponDetachingMag_Store, error - cannot abort detaching of magazine");

			m_weapon.HideMagazine(); // force hide on abort
		}
		
		wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine, aborting, but attached new magazine already in place");
		m_newMagazine = NULL;
		m_newDst = NULL;

		super.OnAbort(e);
	}

	override void OnExit (WeaponEventBase e)
	{
		m_newMagazine = NULL;
		m_newDst = NULL;
		super.OnExit(e);
	}

	override bool SaveCurrentFSMState (ParamsWriteContext ctx)
	{
		if (!super.SaveCurrentFSMState(ctx))
			return false;

		if (!ctx.Write(m_newMagazine))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine.SaveCurrentFSMState: cannot write m_newMagazine for weapon=" + m_weapon);
			return false;
		}

		if (!OptionalLocationWriteToContext(m_newDst, ctx))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine.SaveCurrentFSMState: cannot write m_newDst for weapon=" + m_weapon);
			return false;
		}
		return true;
	}

	override bool LoadCurrentFSMState (ParamsReadContext ctx, int version)
	{
		if (!super.LoadCurrentFSMState(ctx, version))
			return false;

		if (!ctx.Read(m_newMagazine))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine.LoadCurrentFSMState: cannot read m_newMagazine for weapon=" + m_weapon);
			return false;
		}
		if (!OptionalLocationReadFromContext(m_newDst, ctx))
		{
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " AttachNewMagazine.LoadCurrentFSMState: cannot read m_newDst for weapon=" + m_weapon);
			return false;
		}
		return true;
	}
};

class AttachNewMagazine_W4T extends WeaponStateBase
{
	override bool IsWaitingForActionFinish () { return true; }
};


/**@class		WeaponReplacingMagAndChamberNext
 * @brief		replace current magazine with new one
 *
 * replace magazine, i.e. eject curr magazine from weapon, attach another (store the old one) 
 * and chamber next bullet from magazine (if possible)
 **/
class WeaponReplacingMagAndChamberNext extends WeaponStateBase
{
	WeaponActions m_action;
	int m_actionType;

	ref WeaponStartAction m_start;
	ref DetachOldMagazine m_detach;
	ref OldMagazineHide m_hideOld;
	ref SwapOldAndNewMagazine m_swapMags;
	ref AttachNewMagazine_W4T m_attach;
	ref WeaponChamberFromAttMag_W4T m_chamber;
	ref WeaponCharging_CK m_onCK;
	ref WeaponEjectCasing m_eject;

	// substates configuration
	Magazine m_oldMagazine; /// magazine that will be detached
	Magazine m_newMagazine; /// magazine that will be attached
	ref InventoryLocation m_newDst;

	void WeaponReplacingMagAndChamberNext (Weapon_Base w = NULL, WeaponStateBase parent = NULL, WeaponActions action = WeaponActions.NONE, int actionType = -1)
	{
		m_action = action;
		m_actionType = actionType;
		m_newMagazine = NULL;

		// setup nested state machine
		m_start = new WeaponStartAction(m_weapon, this, m_action, m_actionType);
		m_eject = new WeaponEjectCasing(m_weapon,this);
		m_detach = new DetachOldMagazine(m_weapon, this);
		m_hideOld = new OldMagazineHide(m_weapon, this);
		m_swapMags = new SwapOldAndNewMagazine(m_weapon, this);
		m_attach = new AttachNewMagazine_W4T(m_weapon, this);
		m_chamber = new WeaponChamberFromAttMag_W4T(m_weapon, this);
		m_onCK = new WeaponCharging_CK(m_weapon, this);

		// events
		WeaponEventBase __so_ = new WeaponEventAnimSliderOpen;
		WeaponEventBase __md_ = new WeaponEventAnimMagazineDetached;
		WeaponEventBase __mh_ = new WeaponEventAnimMagazineHide;
		WeaponEventBase __ms_ = new WeaponEventAnimMagazineShow;
		WeaponEventBase __ma_ = new WeaponEventAnimMagazineAttached;
		WeaponEventBase __ck_ = new WeaponEventAnimCocked;
		WeaponEventBase _fin_ = new WeaponEventHumanCommandActionFinished;

		m_fsm = new WeaponFSM(this); // @NOTE: set owner of the submachine fsm
		m_fsm.AddTransition(new WeaponTransition(   m_start, __md_, m_detach));
		m_fsm.AddTransition(new WeaponTransition(   m_start, __so_, m_eject));
		m_fsm.AddTransition(new WeaponTransition(   m_eject, __md_, m_detach));
		m_fsm.AddTransition(new WeaponTransition(  m_detach, __mh_, m_hideOld));
		m_fsm.AddTransition(new WeaponTransition( m_hideOld, __ms_, m_swapMags));
		m_fsm.AddTransition(new WeaponTransition(m_swapMags, __ma_, m_attach));
		m_fsm.AddTransition(new WeaponTransition(  m_attach, __ck_, m_chamber, NULL, new GuardAnd(new WeaponGuardCurrentChamberEmpty(m_weapon), new WeaponGuardHasAmmo(m_weapon))));
		m_fsm.AddTransition(new WeaponTransition(  m_attach, __ck_, m_onCK));
		m_fsm.AddTransition(new WeaponTransition(  m_attach, _fin_, NULL));
		m_fsm.AddTransition(new WeaponTransition( m_chamber, _fin_, NULL));
		m_fsm.AddTransition(new WeaponTransition(    m_onCK, _fin_, NULL));

		m_fsm.SetInitialState(m_start);
	}
	
	override void OnEntry (WeaponEventBase e)
	{
		int mi = m_weapon.GetCurrentMuzzle();
		m_oldMagazine = m_weapon.GetMagazine(mi);
		m_newMagazine = e.m_magazine;

		wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponReplacingMagAndChamberNext, m_oldMagazine=" + m_oldMagazine + " m_newMagazine=" + m_newMagazine);

		if (m_oldMagazine && m_newMagazine)
		{
			m_newDst = new InventoryLocation;
			
			InventoryLocation oldSrc = new InventoryLocation;
			InventoryLocation newSrc = new InventoryLocation;

			if (!m_newMagazine.GetInventory().GetCurrentInventoryLocation(newSrc))
			{
				Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponReplacingMagAndChamberNext cannot get curr inv loc of NEW mag=" + Object.GetDebugName(m_newMagazine));
			}
			if (!m_oldMagazine.GetInventory().GetCurrentInventoryLocation(oldSrc))
			{
				Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponReplacingMagAndChamberNext cannot get curr inv loc of OLD mag=" + Object.GetDebugName(m_oldMagazine));
			}

			m_newMagazine.GetInventory().GetCurrentInventoryLocation(m_newDst);
			m_newDst.CopyLocationFrom(oldSrc, true);

			// move to LH
			InventoryLocation lhand = new InventoryLocation;
			lhand.SetAttachment(e.m_player, m_newMagazine, InventorySlots.LEFTHAND);
			if (GameInventory.LocationSyncMoveEntity(newSrc, lhand))
			{
				wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " RemoveNewMagazineFromInventory, ok - new magazine removed from inv (inv->LHand)");
			}
			else
				Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " RemoveNewMagazineFromInventory, error - cannot new remove mag from inv");

			m_detach.m_oldMagazine = m_oldMagazine;

			m_swapMags.m_newMagazine = m_newMagazine;

			m_swapMags.m_newDst = m_newDst;
		}
		else
			Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " WeaponReplacingMagAndChamberNext, error - no magazines configured for replace (m_old=m_new=NULL)");

		super.OnEntry(e); // @NOTE: super after submachine init (prevent override from submachine start)
	}
	override void OnExit (WeaponEventBase e)
	{
		m_oldMagazine = NULL;
		m_newMagazine = NULL;
		m_newDst = NULL;
		super.OnExit(e);
	}
	
	override void OnAbort(WeaponEventBase e)
	{
		super.OnAbort(e);
		
		EntityAI leftHandItem = e.m_player.GetInventory().FindAttachment(InventorySlots.LEFTHAND);
		Magazine mag = Magazine.Cast(leftHandItem);
		
		if(mag)
		{
			e.m_player.GetInventory().ClearInventoryReservation( mag , null );
			InventoryLocation il = new InventoryLocation;
			e.m_player.GetInventory().FindFreeLocationFor( mag, FindInventoryLocationType.CARGO, il );
		
			if(!il || !il.IsValid())
			{
				if (DayZPlayerUtils.HandleDropMagazine(e.m_player, mag))
					wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, ok - no inventory space for old magazine - dropped to ground");
				else
					Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, error - cannot drop magazine from left hand after not found inventory space for old magazine");
				
			}
			else
			{
				InventoryLocation oldSrc = new InventoryLocation;
				mag.GetInventory().GetCurrentInventoryLocation(oldSrc);
				
				if (GameInventory.LocationSyncMoveEntity(oldSrc, il))
				{
					wpnDebugPrint("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, ok - old magazine removed from wpn (LHand->inv)");
				}
				else
					Error("[wpnfsm] " + Object.GetDebugName(m_weapon) + " DetachOldMagazine, error - cannot remove old mag from wpn");
			}
		}
	}
};

