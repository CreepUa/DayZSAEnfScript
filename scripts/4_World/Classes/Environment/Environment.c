class Environment
{
	const float RAIN_LIMIT_LOW		= 0.05;

	const float WATER_LEVEL_HIGH	= 1.5;
	const float WATER_LEVEL_MID 	= 1.2;
	const float WATER_LEVEL_LOW 	= 0.5;
	const float WATER_LEVEL_NONE	= 0.15;

	protected float	   				m_DayTemp;
	protected float  				m_NightTemp;
	
	protected float					m_WetDryTick; //ticks passed since last clothing wetting or drying
	protected float					m_ItemsWetnessMax; //! keeps wetness of most wet item in player's possesion
	protected float					m_RoofCheckTimer; // keeps info about tick time

	//player
	protected PlayerBase 			m_Player;
	protected float					m_PlayerHeightPos; // y position of player above water level (meters)
	protected float 				m_PlayerSpeed; // 1-3 speed of player movement
	protected float 				m_PlayerTemperature; //34-44
	protected float 				m_PlayerHeat; //3-9 heatcomfort generated by entites movement
	protected float					m_HeatComfort;  //delta that changes entitys temperature				

	//environment
	protected float 				m_Rain = 0; // 0-1 amount of rain 
	protected float 				m_Wind = 0; // strength of wind
	protected float 				m_Fog = 0; // 0-1 how foggy it is
	protected float 				m_DayOrNight = 0; // 0-1 day(1) or night(0)
	protected float 				m_Clouds = 0; // 0-1 how cloudy it is
	protected float 				m_EnvironmentTemperature = 0; //temperature of environment player is in
	protected float					m_Time = 0;
	
	//
	protected float					m_WaterLevel;
	protected bool 					m_IsUnderRoof;
	protected bool 					m_IsInWater;
	protected bool					m_IsTempSet;
	
	//
	protected float 				m_HeatSourceTemp;
	
	ref protected array<int> 		m_SlotIdsComplete;
	ref protected array<int> 		m_SlotIdsUpper;
	ref protected array<int> 		m_SlotIdsBottom;
	ref protected array<int> 		m_SlotIdsLower;
	
	ref protected array<int>		m_HeadParts;
	ref protected array<int>		m_BodyParts;
	ref protected array<int>		m_FeetParts;
		
	void Environment(PlayerBase pPlayer)
	{
		Init(pPlayer);
	}
	
	void Init(PlayerBase pPlayer)
	{
		m_Player 				= pPlayer;
		m_PlayerSpeed			= 0.0;
		m_WetDryTick			= 0.0;
		m_RoofCheckTimer		= 0.0;
		m_WaterLevel			= 0.0;
		m_HeatComfort			= 0.0;
		
		m_IsUnderRoof			= false;
		m_IsInWater				= false;

		//! load temperatures (from server config)
		if (GetGame().GetMission().GetWorldData())
		{
			m_DayTemp = g_Game.GetMission().GetWorldData().GetDayTemperature();
			m_NightTemp = g_Game.GetMission().GetWorldData().GetNightTemperature();
		}
		m_HeatSourceTemp		= 0.0;

		//! whole body slots		
		m_SlotIdsComplete 		= new array<int>;		
		m_SlotIdsComplete 		= {
			InventorySlots.HEADGEAR,
			InventorySlots.MASK,
			InventorySlots.EYEWEAR,
			InventorySlots.GLOVES,
			InventorySlots.ARMBAND,
			InventorySlots.BODY,
			InventorySlots.VEST,
			InventorySlots.BACK,
			InventorySlots.LEGS,
			InventorySlots.FEET,
		};
		//! upper body part slots
		m_SlotIdsUpper 			= new array<int>;
		m_SlotIdsUpper 			= {
			InventorySlots.GLOVES,
			InventorySlots.ARMBAND,
			InventorySlots.BODY,
			InventorySlots.VEST,
			InventorySlots.BACK,
			InventorySlots.LEGS,
			InventorySlots.FEET,
		};
		//! bottom body part slots
		m_SlotIdsBottom 		= new array<int>;
		m_SlotIdsBottom			= {
			InventorySlots.LEGS,
			InventorySlots.FEET,
		};
		//! lower body part slots
		m_SlotIdsLower 			= new array<int>;
		m_SlotIdsLower			= {
			InventorySlots.FEET,
		};

		//! --------------------------
		//! heat comfort related slots
		m_HeadParts				= new array<int>;
		m_HeadParts				= {
			InventorySlots.HEADGEAR,
			InventorySlots.MASK,
		};
		
		m_BodyParts				= new array<int>;
		m_BodyParts				= {
			InventorySlots.GLOVES,
			InventorySlots.ARMBAND,
			InventorySlots.BODY,
			InventorySlots.VEST,
		};
		
		m_FeetParts				= new array<int>;
		m_FeetParts				= {
			InventorySlots.LEGS,
			InventorySlots.FEET,
		};
	}

	
	// Calculates heatisolation of clothing, process its wetness, collects heat from heated items and calculates player's heat comfort
	void Update(float pDelta)
	{
		if (m_Player)
		{
			m_RoofCheckTimer += pDelta;
			//! check if player is under roof (only if the Building check is false)
			if (m_RoofCheckTimer >= GameConstants.ENVIRO_TICK_ROOF_RC_CHECK && !IsInsideBuilding())
			{
				CheckUnderRoof();
				m_RoofCheckTimer = 0;
			}

			m_Time += pDelta;
			if ( m_Time >= GameConstants.ENVIRO_TICK_RATE )
			{
				m_Time = 0;
				m_WetDryTick++; // Sets whether it is time to add wetness to items and clothing
				
				//Print(IsInsideBuilding().ToString());

				//! Updates data
				CheckWaterContact(m_WaterLevel);
				CollectAndSetPlayerData();
				CollectAndSetEnvironmentData();
				
				//! Process temperature
				ProcessItemsHeat();

				//! Process item wetness/dryness
				if ( m_WetDryTick >= GameConstants.ENVIRO_TICKS_TO_WETNESS_CALCULATION )
				{
					if( IsWaterContact() )
					{
						ProcessWetnessByWaterLevel(m_WaterLevel);
					}
					else if( IsRaining() && !IsInsideBuilding() && !IsUnderRoof() && !IsInsideVehicle() )
					{
						ProcessWetnessByRain();
					}
					else
					{
						ProcessItemsDryness();
					}

					//! setting of wetness/dryiness of player
					if( m_ItemsWetnessMax < GameConstants.STATE_DRENCHED && m_Player.GetStatWet().Get() == 1 )
					{
						m_Player.GetStatWet().Set(0);
					}
					else if( m_ItemsWetnessMax >= GameConstants.STATE_DRENCHED && m_Player.GetStatWet().Get() == 0 )
					{
						m_Player.GetStatWet().Set(1);
					}

					m_WetDryTick = 0;
					m_ItemsWetnessMax = 0; //! reset item wetness counter;
				}
				
				m_HeatSourceTemp = 0.0;
			}
		}
	}
	
	bool IsTemperatureSet()
	{
		return m_IsTempSet;
	}
	
	void AddToEnvironmentTemperature(float pTemperature)
	{
		m_HeatSourceTemp = pTemperature;
	}
	
	//! Returns heat player generated based on player's movement speed (for now)
	protected float GetPlayerHeat()
	{
		float heat = Math.Max(m_PlayerSpeed * GameConstants.ENVIRO_DEFAULT_ENTITY_HEAT, GameConstants.ENVIRO_DEFAULT_ENTITY_HEAT);
		return heat;
	}
	
	protected bool IsUnderRoof()
	{
		return m_IsUnderRoof;
	}
	
	protected bool IsWaterContact()
	{
		return m_IsInWater;
	}
	
	protected bool IsInsideBuilding()
	{
		return m_Player && m_Player.IsSoundInsideBuilding();
	}

	protected bool IsInsideVehicle()
	{
		return m_Player && m_Player.IsInVehicle();
	}
	
	protected bool IsRaining()
	{
		return m_Rain > RAIN_LIMIT_LOW;
	}
	
	//! Checks whether Player is sheltered
	protected void CheckUnderRoof()
	{
		float hitFraction;
		vector hitPosition, hitNormal;
		vector from = m_Player.GetPosition();
		vector to = from + "0 25 0";
		Object hitObject;
		PhxInteractionLayers collisionLayerMask = PhxInteractionLayers.ITEM_LARGE|PhxInteractionLayers.BUILDING|PhxInteractionLayers.VEHICLE;
		
		m_IsUnderRoof = DayZPhysics.RayCastBullet(from, to, collisionLayerMask, null, hitObject, hitPosition, hitNormal, hitFraction);
	}
	
	protected void CheckWaterContact(out float pWaterLevel)
	{
		string surfType;
		int liquidType;

		g_Game.SurfaceUnderObject(m_Player, surfType, liquidType);

		switch ( liquidType )
		{
			case 0: // sea
			case LIQUID_WATER:
				vector wl = HumanCommandSwim.WaterLevelCheck(m_Player, m_Player.GetPosition());
				pWaterLevel = wl[0];
				m_IsInWater = true;
			break;
			
			default:
				pWaterLevel = 0;
				m_IsInWater = false;
			break;
		}

		//! sync info about water contact to player
		m_Player.SetInWater(m_IsInWater);
	}
	
	// Calculates item heat isolation based on its wetness
	float GetCurrentItemHeatIsolation(ItemBase pItem)
	{
		float wetFactor;
		float healthFactor;

		float heatIsolation = pItem.GetHeatIsolation(); 	//! item heat isolation (from cfg)
		float itemHealthLabel = pItem.GetHealthLevel();		//! item health (state)
		float itemWetness = pItem.GetWet();					//! item wetness
		
		//! wet factor selection
		if ( itemWetness >= GameConstants.STATE_DRY && itemWetness < GameConstants.STATE_DAMP )
		{
			wetFactor = GameConstants.ENVIRO_ISOLATION_WETFACTOR_DRY;
		}
		else if ( itemWetness >= GameConstants.STATE_DAMP && itemWetness < GameConstants.STATE_WET )
		{
			wetFactor = GameConstants.ENVIRO_ISOLATION_WETFACTOR_DAMP;
		}
		else if ( itemWetness >= GameConstants.STATE_WET && itemWetness < GameConstants.STATE_SOAKING_WET )
		{
			wetFactor = GameConstants.ENVIRO_ISOLATION_WETFACTOR_WET;
		}
		else if ( itemWetness >= GameConstants.STATE_SOAKING_WET && itemWetness < GameConstants.STATE_DRENCHED )
		{
			wetFactor = GameConstants.ENVIRO_ISOLATION_WETFACTOR_SOAKED;
		}
		else if ( itemWetness >= GameConstants.STATE_DRENCHED )
		{
			wetFactor = GameConstants.ENVIRO_ISOLATION_WETFACTOR_DRENCHED;
		}
		
		//! health factor selection
		switch (itemHealthLabel)
		{
		case GameConstants.STATE_PRISTINE:
			healthFactor = GameConstants.ENVIRO_ISOLATION_HEALTHFACTOR_PRISTINE;
		break;
		case GameConstants.STATE_WORN:
			healthFactor = GameConstants.ENVIRO_ISOLATION_HEALTHFACTOR_WORN;
		break;
		case GameConstants.STATE_DAMAGED:
			healthFactor = GameConstants.ENVIRO_ISOLATION_HEALTHFACTOR_DAMAGED;
		break;
		case GameConstants.STATE_BADLY_DAMAGED:
			healthFactor = GameConstants.ENVIRO_ISOLATION_HEALTHFACTOR_B_DAMAGED;
		break;
		case GameConstants.STATE_RUINED:
			healthFactor = GameConstants.ENVIRO_ISOLATION_HEALTHFACTOR_RUINED;
		break;
		}
		
		//! apply fatctors
		heatIsolation *= healthFactor;
		heatIsolation *= wetFactor;

		return heatIsolation;
	}

	protected float GetCurrentItemWetAbsorbency(ItemBase pItem)
	{
		float healthFactor;
		float absorbency = pItem.GetAbsorbency();			//! item absorbency from config
		float itemHealthLabel = pItem.GetHealthLevel();		//! item health (state)

		if( absorbency == 0 )
		{
			return 0;
		}

		//! health factor selection
		switch (itemHealthLabel)
		{
		case GameConstants.STATE_PRISTINE:
			healthFactor = GameConstants.ENVIRO_ABSORBENCY_HEALTHFACTOR_PRISTINE;
		break;
		case GameConstants.STATE_WORN:
			healthFactor = GameConstants.ENVIRO_ABSORBENCY_HEALTHFACTOR_WORN;
		break;
		case GameConstants.STATE_DAMAGED:
			healthFactor = GameConstants.ENVIRO_ABSORBENCY_HEALTHFACTOR_DAMAGED;
		break;
		case GameConstants.STATE_BADLY_DAMAGED:
			healthFactor = GameConstants.ENVIRO_ABSORBENCY_HEALTHFACTOR_B_DAMAGED;
		break;
		case GameConstants.STATE_RUINED:
			healthFactor = GameConstants.ENVIRO_ABSORBENCY_HEALTHFACTOR_RUINED;
		break;
		}

		//! takes into account health of item
		absorbency = absorbency + (1 - healthFactor);

		return Math.Min(1, absorbency);
	}
	
	//ENVIRONTMENT
	// Returns amount of ?C air temperature should be lowered by, based on player's height above water level
	protected float GetTemperatureHeightCorrection()
	{
		float temperature_reduction = Math.Max(0, (m_PlayerHeightPos * GameConstants.ENVIRO_TEMPERATURE_HEIGHT_REDUCTION));
		return temperature_reduction;
	}
	
	float GetTemperature()
	{
		return m_EnvironmentTemperature;
	}
	
	// Calculates and return temperature of environment
	protected float GetEnvironmentTemperature()
	{
		float temperature;

		//! day or night
		if( m_NightTemp < m_DayTemp )
		{
			temperature = m_NightTemp + ((m_DayTemp - m_NightTemp) * m_DayOrNight);
		}
		else
		{
			temperature = m_DayTemp + ((m_NightTemp - m_DayTemp) * m_DayOrNight);
		}
		
		if( IsWaterContact() ) 
		{
			temperature = temperature * GameConstants.ENVIRO_WATER_TEMPERATURE_COEF;
		}
		
		if( IsInsideBuilding() )
		{
			temperature = temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_COEF;
		}
		
		if( IsUnderRoof() )
		{
			temperature = temperature * GameConstants.ENVIRO_TEMPERATURE_UNDERROOF_COEF;
		}

		float fog_effect  = m_Fog * GameConstants.ENVIRO_FOG_TEMP_EFFECT;
		float clouds_effect = m_Clouds * GameConstants.ENVIRO_CLOUDS_TEMP_EFFECT;
		//float wind_effect = m_Wind * 0.01;
		//float combined_effect = clouds_effect + fog_effect + wind_effect;
		float combined_effect = clouds_effect + fog_effect;
		if ( combined_effect > 0 )
		{
			temperature = temperature * (1 - combined_effect);
		}
		
		if (m_HeatSourceTemp > temperature)
		{
			temperature = temperature + m_HeatSourceTemp;
		}
		temperature -= GetTemperatureHeightCorrection();
		return temperature;
	}	
		
	// Calculats wet/drying delta based on player's location and weather
	protected float GetWetDelta()
	{
		float wet_delta = 0;
		if ( IsWaterContact() )
		{
			//! player is getting wet by movement/swimming in water (+differentiate wet_delta by water level)
			if (m_WaterLevel >= WATER_LEVEL_HIGH)
			{
				wet_delta = 1;
			}
			else if (m_WaterLevel >= WATER_LEVEL_MID && m_WaterLevel < WATER_LEVEL_HIGH)
			{
				wet_delta = 0.66;
			}
			else if (m_WaterLevel >= WATER_LEVEL_LOW && m_WaterLevel < WATER_LEVEL_MID)
			{
				wet_delta = 0.66;
			}
			else if (m_WaterLevel >= WATER_LEVEL_NONE && m_WaterLevel < WATER_LEVEL_LOW)
			{
				wet_delta = 0.33;
			}
		}
		else if ( IsRaining() && !IsInsideBuilding() && !IsUnderRoof() )
		{
			//! player is getting wet from rain
			wet_delta = GameConstants.ENVIRO_WET_INCREMENT * GameConstants.ENVIRO_TICKS_TO_WETNESS_CALCULATION * ( 4 * GameConstants.ENVIRO_WIND_EFFECT * m_Wind ) * ( m_Rain );
		}
		else
		{
			//! player is drying
			float sun_effect = ( GameConstants.ENVIRO_SUN_INCREMENT * m_DayOrNight * ( 1 - m_Fog ) ) * ( 1 - ( m_Clouds * GameConstants.ENVIRO_CLOUD_DRY_EFFECT ) );
			float temp_effect = m_PlayerHeat + Math.Max( GetEnvironmentTemperature(), 0.0 );
			//! Coef should be higher than 0 (Sqrt is none for x < 0)
			if ( temp_effect <= 0 ) { temp_effect = 1; }

			wet_delta = -( GameConstants.ENVIRO_DRY_INCREMENT * ( temp_effect + sun_effect ) );
			if ( !IsInsideBuilding() )
				wet_delta *= ( 1 + ( GameConstants.ENVIRO_WIND_EFFECT * m_Wind ) );
		}

		return wet_delta;
	}
	

	// EXPOSURE
	// Each tick updates current entity member variables
	protected void CollectAndSetPlayerData()
	{
		vector playerPos = m_Player.GetPosition();
		m_PlayerHeightPos = playerPos[1];

		HumanCommandMove hcm = m_Player.GetCommand_Move();
		if(hcm)
			m_PlayerSpeed = hcm.GetCurrentMovementSpeed();
		//m_PlayerTemperature = m_Player.GetStatTemperature().Get(); //can be current entity temeprature in future
		m_PlayerHeat = GetPlayerHeat();
	}
	
	// Each tick updates current environment member variables
	protected void CollectAndSetEnvironmentData()
	{
		Weather weather = g_Game.GetWeather();

		m_Rain = weather.GetRain().GetActual();
		m_DayOrNight = (-1 * Math.AbsFloat( ( 1 - ( g_Game.GetDayTime() / GameConstants.ENVIRO_HIGH_NOON ) ) ) ) + 1;
		m_Fog = weather.GetFog().GetActual();
		m_Clouds =	weather.GetOvercast().GetActual();
		m_Wind = weather.GetWindSpeed();
		SetEnvironmentTemperature();
	}
	
	void SetEnvironmentTemperature()
	{
		m_IsTempSet = true;
		m_EnvironmentTemperature = GetEnvironmentTemperature();
	}

	protected void ProcessWetnessByRain()
	{
		ProcessItemsWetness(m_SlotIdsComplete);
	}

	protected void ProcessWetnessByWaterLevel(float pWaterLevel)
	{
		ref array<int> slotIds = new array<int>;
	
		// process attachments by water depth
		if (pWaterLevel >= WATER_LEVEL_HIGH)
		{
			//! complete
			ProcessItemsWetness(m_SlotIdsComplete);
		}
		else if (pWaterLevel >= WATER_LEVEL_MID && pWaterLevel < WATER_LEVEL_HIGH)
		{
			//! upper part
			ProcessItemsWetness(m_SlotIdsUpper);
		}
		else if (pWaterLevel >= WATER_LEVEL_LOW && pWaterLevel < WATER_LEVEL_MID)
		{
			//! bottom part
			ProcessItemsWetness(m_SlotIdsBottom);
		}
		else if (pWaterLevel >= WATER_LEVEL_NONE && pWaterLevel < WATER_LEVEL_LOW)
		{
			//! feet
			ProcessItemsWetness(m_SlotIdsLower);
		}
	}

	// Wets or dry items once in given time
	protected void ProcessItemsWetness(array<int> pSlotIds)
	{
		EntityAI attachment;
		ItemBase item;
		
		int attCount = m_Player.GetInventory().AttachmentCount();
		
		for (int attIdx = 0; attIdx < attCount; attIdx++)
		{
			attachment = m_Player.GetInventory().GetAttachmentFromIndex(attIdx);
			if ( attachment.IsItemBase() )
			{
				item = ItemBase.Cast(attachment);
				int attachmentSlot = attachment.GetInventory().GetSlotId(0);

				for (int i = 0; i < pSlotIds.Count(); i++)
				{
					if (attachmentSlot == pSlotIds.Get(i))
					{
						ApplyWetnessToItem(item);
					}
				}
			}
		}
		
		if (m_Player.GetItemInHands())
		{
			ApplyWetnessToItem(m_Player.GetItemInHands());
		}

		//! force recalc of player's load (for stamina)
		m_Player.UpdateWeight();
		m_Player.SetPlayerLoad( m_Player.GetWeight() );
	}

	protected void ProcessItemsDryness()
	{
		EntityAI attachment;
		ItemBase item;
		
		int attCount = m_Player.GetInventory().AttachmentCount();
		
		for (int attIdx = 0; attIdx < attCount; attIdx++)
		{
			attachment = m_Player.GetInventory().GetAttachmentFromIndex(attIdx);
			if ( attachment && attachment.IsItemBase() )
			{
				item = ItemBase.Cast(attachment);
				ApplyDrynessToItem(item);
			}
		}

		if (m_Player.GetItemInHands())
		{
			ApplyDrynessToItem(m_Player.GetItemInHands());
		}

		//! force recalc of player's load (for stamina)		
		m_Player.UpdateWeight();
		m_Player.SetPlayerLoad( m_Player.GetWeight() );
	}
	
	
	protected void ApplyWetnessToItem(ItemBase pItem)
	{
		if (pItem && GetCurrentItemWetAbsorbency(pItem) > 0)
		{
			pItem.AddWet(GetWetDelta() * GetCurrentItemWetAbsorbency(pItem));
			if (pItem.GetWet() > m_ItemsWetnessMax)
				m_ItemsWetnessMax = pItem.GetWet();
			//Print("processing wetness for " + pItem.GetDisplayName());
	
			if ( pItem.GetInventory().GetCargo() )
			{
				int inItemCount = pItem.GetInventory().GetCargo().GetItemCount();
	
				for (int i = 0; i < inItemCount; i++)
				{
					ItemBase inItem;
					if ( Class.CastTo(inItem, pItem.GetInventory().GetCargo().GetItem(i)) )
					{
						inItem.AddWet(GetWetDelta() * GetCurrentItemWetAbsorbency(inItem) * GameConstants.ENVIRO_WET_PASSTHROUGH_COEF);
						//Print("processing wetness for (inside)" + inItem.GetDisplayName());
					}
				}
			}
		}
	}
	
	protected void ApplyDrynessToItem(ItemBase pItem)
	{
		if (pItem)
		{
			if (pItem.GetWet() > pItem.GetWetMin())
			{
				pItem.AddWet(GetWetDelta());
				if (pItem.GetWet() > m_ItemsWetnessMax)
					m_ItemsWetnessMax = pItem.GetWet();
				//Print("drying for " + pItem.GetDisplayName());
			}
	
			if ( pItem.GetInventory().GetCargo() )
			{
				int inItemCount = pItem.GetInventory().GetCargo().GetItemCount();
	
				for (int i = 0; i < inItemCount; i++)
				{
					ItemBase inItem;
					if ( Class.CastTo(inItem, pItem.GetInventory().GetCargo().GetItem(i)) )
					{
						if (inItem.GetWet() > inItem.GetWetMin())
						{
							inItem.AddWet(GetWetDelta() * GameConstants.ENVIRO_WET_PASSTHROUGH_COEF);
							//Print("drying for (inside)" + inItem.GetDisplayName());
						}
					}
				}
			}
		}
	}

	// HEAT COMFORT
	//! Calculates and process temperature of items
	protected void ProcessItemsHeat()
	{
		float hcHead, hcBody, hcFeet;	//! Heat Comfort
		float hHead, hBody, hFeet;		//! Heat (from items);
		
		float heatComfortAvg;
		float heatAvg;

		BodyPartHeatProperties(m_HeadParts, GameConstants.ENVIRO_HEATCOMFORT_HEADPARTS_WEIGHT, hcHead, hHead);
		BodyPartHeatProperties(m_BodyParts, GameConstants.ENVIRO_HEATCOMFORT_BODYPARTS_WEIGHT, hcBody, hBody);
		BodyPartHeatProperties(m_FeetParts, GameConstants.ENVIRO_HEATCOMFORT_FEETPARTS_WEIGHT, hcFeet, hFeet);

		heatComfortAvg = (hcHead + hcBody + hcFeet) / 3;
		heatAvg = (hHead + hBody + hFeet) / 3;
		
		heatAvg = heatAvg * GameConstants.ENVIRO_ITEM_HEAT_TRANSFER_COEF;
		float overridenHeatComfort = 0.0;
		if( OverridenHeatComfort(overridenHeatComfort) )
		{
			m_HeatComfort = overridenHeatComfort;
		}
		else
		{
			m_HeatComfort = (heatComfortAvg + heatAvg + (GetPlayerHeat()/100)) + EnvTempToCoef(m_EnvironmentTemperature);
			m_HeatComfort = Math.Clamp(m_HeatComfort, m_Player.GetStatHeatComfort().GetMin(), m_Player.GetStatHeatComfort().GetMax());
		}
		
		m_Player.GetStatHeatComfort().Set(m_HeatComfort);

		/*		
		if (!GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			DbgUI.BeginCleanupScope();
			DbgUI.Begin("New HeatComfort debug", 300, 100);
			DbgUI.Text("Heat comfort: " + m_Heat.ToString());
			DbgUI.Text("HeatComfort raw (avg): " + heatComfortAvg.ToString());
			DbgUI.Text("Heat raw (avg): " + heatAvg.ToString());
			DbgUI.Text("TempToCoef: " + EnvTempToCoef(m_EnvironmentTemperature).ToString());
			DbgUI.End();
			DbgUI.EndCleanupScope();
		}
		*/
	}
	
	protected bool OverridenHeatComfort(out float value)
	{
		if( IsInsideVehicle() )
		{
			if( m_Player.GetCommand_Vehicle() )
			{
				CarScript cs = CarScript.Cast(m_Player.GetCommand_Vehicle().GetTransport());
				if( cs )
				{
					value = cs.GetEnviroHeatComfortOverride();
				}
			
				return true;
			}
		}
		
		return false;
	}
	
	protected float EnvTempToCoef(float pTemp)
	{
		if (pTemp >= GameConstants.ENVIRO_HIGH_TEMP_LIMIT)
			return 1;
		
		if (pTemp <= GameConstants.ENVIRO_LOW_TEMP_LIMIT)
			return -1;
		
		float result = (pTemp - GameConstants.ENVIRO_PLAYER_COMFORT_TEMP) / 100;
		
		return result;
	}
	
	//! returns weighted avg heat comfort for bodypart
	protected void BodyPartHeatProperties(array<int> pBodyPartIds, float pCoef, out float pHeatComfort, out float pHeat)
	{
		int attCount;
		
		EntityAI attachment;
		ItemBase item;
		
		pHeatComfort = -1;
		attCount = m_Player.GetInventory().AttachmentCount();
		
		for (int attIdx = 0; attIdx < attCount; attIdx++)
		{
			attachment = m_Player.GetInventory().GetAttachmentFromIndex(attIdx);
			if ( attachment.IsClothing() )
			{
				item = ItemBase.Cast(attachment);
				int attachmentSlot = attachment.GetInventory().GetSlotId(0);

				//! go through all body parts we've defined for that zone (ex.: head, body, feet)
				for (int i = 0; i < pBodyPartIds.Count(); i++)
				{
					if (attachmentSlot == pBodyPartIds.Get(i))
					{
						pHeatComfort += GetCurrentItemHeatIsolation(item);
						
						//! traverse cargo of the item and adds cargo item temperature into account
						if (item.HasAnyCargo())
						{
							CargoBase cargoBase;
							int cargoCount;
							
							cargoBase = item.GetInventory().GetCargo();
							cargoCount = cargoBase.GetItemCount();
							for (int c = 0; c < cargoCount; c++)
							{
								ItemBase cargoItemIB;
								if ( Class.CastTo(cargoItemIB, cargoBase.GetItem(c)) && cargoItemIB.IsItemBase() )
								{
									pHeat += cargoItemIB.GetTemperature();
								}
							}
						}
					}
				}
			}
		}

		pHeatComfort = (pHeatComfort / pBodyPartIds.Count()) * pCoef;
		pHeat = (pHeat / pBodyPartIds.Count()) * pCoef;
	}

	//! debug
#ifdef DEVELOPER
	void ShowEnvDebugPlayerInfo(bool enabled)
	{
		int windowPosX = 10;
		int windowPosY = 200;

		Object obj;

		DbgUI.Begin("Player stats", windowPosX, windowPosY);
		if( enabled )
		{
			//DbgUI.Text("Temperature: " + m_PlayerTemperature.ToString());
			DbgUI.Text("Heat comfort: " + m_HeatComfort.ToString());
			DbgUI.Text("Inside: " + IsInsideBuilding().ToString() + " ("+m_Player.GetSurfaceType()+")");
			DbgUI.Text("Under roof: " + m_IsUnderRoof.ToString());
			if( IsWaterContact() && m_WaterLevel > WATER_LEVEL_NONE )
			{
				DbgUI.Text("Water Level: " + m_WaterLevel);
			}
			
		}
		DbgUI.End();
		
		DbgUI.Begin("Weather stats:", windowPosX, windowPosY + 200);
		if( enabled )
		{
			DbgUI.Text("Env temperature: " +  m_EnvironmentTemperature.ToString());
			DbgUI.Text("Wind: " +  m_Wind.ToString());
			DbgUI.Text("Rain: " + m_Rain.ToString());
			DbgUI.Text("Day/Night (1/0): " + m_DayOrNight.ToString());
			DbgUI.Text("Fog: " + m_Fog.ToString());
			DbgUI.Text("Clouds: " + m_Clouds.ToString());
			DbgUI.Text("Height: " + GetTemperatureHeightCorrection().ToString());
			DbgUI.Text("Wet delta: " + GetWetDelta().ToString());
		}
		DbgUI.End();
	}
#endif
};