class OnlineServices
{
	static ref ScriptInvoker												m_FriendsAsyncInvoker		= new ScriptInvoker();
	static ref ScriptInvoker												m_PermissionsAsyncInvoker	= new ScriptInvoker();
	static ref ScriptInvoker												m_ServersAsyncInvoker		= new ScriptInvoker();
	static ref ScriptInvoker												m_ServerAsyncInvoker		= new ScriptInvoker();
	static ref ScriptInvoker												m_MuteUpdateAsyncInvoker	= new ScriptInvoker();
	static ref ScriptInvoker												m_ServerModLoadAsyncInvoker	= new ScriptInvoker();
	
	static ref BiosClientServices											m_ClientServices;
	static ref TrialService													m_TrialService				= new TrialService;
	
	protected static string													m_InviteServerIP;
	protected static int													m_InviteServerPort;
	protected static string													m_CurrentServerIP;
	protected static int													m_CurrentServerPort;
	protected static ref GetServersResultRow								m_CurrentServerInfo;
	
	
	protected static ref map<string, ref BiosFriendInfo>					m_FriendsList;
	protected static ref map<string, bool>									m_MuteList;
	protected static ref map<string, ref BiosPrivacyPermissionResultArray>	m_PermissionsList;
	
	protected static bool													m_FirstFriendsLoad			= true;
	protected static bool													m_MultiplayState			= false;
	protected static ref array<string>										m_PendingInvites;

	protected static ref BiosUser											m_BiosUser;
	
	static void Init()
	{
		#ifdef PLATFORM_CONSOLE
			#ifndef PLATFORM_WINDOWS // if app is not on Windows with -XBOX parameter
			if( !m_FriendsList )
				m_FriendsList = new map<string, ref BiosFriendInfo>;
			if( !m_MuteList )
				m_MuteList = new map<string, bool>;
			if( !m_PermissionsList )
				m_PermissionsList = new map<string, ref BiosPrivacyPermissionResultArray>;
			
			m_FriendsList.Clear();
			m_PermissionsList.Clear();
			m_MuteList.Clear();
			#endif
		#endif
		
		GetClientServices();
	}
	
	static bool IsInitialized()
	{
		return ( m_ClientServices != null );
	}
	
	static void GetClientServices()
	{
		BiosUserManager user_manager = GetGame().GetUserManager();
		if( user_manager )
		{
			BiosUser selected_user = user_manager.GetSelectedUser();
			if( selected_user )
			{
				m_ClientServices = selected_user.GetClientServices();
			}
			#ifdef PLATFORM_WINDOWS
				array<ref BiosUser> user_list = new array<ref BiosUser>;
				user_manager.GetUserList( user_list );
				if( user_list.Count() > 0 )
				{
					m_ClientServices = user_list.Get( 0 ).GetClientServices();
				}
			#endif
		}
		else
		{
			Error( "BiosClientServices Error: Usermanager does not exist." );
		}
	}
	
	static bool ErrorCaught( EBiosError error )
	{
		switch( error )
		{
			case EBiosError.OK:
			{
				return false;
			}
			case EBiosError.CANCEL:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Operation canceled." );
				return true;
			}
			case EBiosError.BAD_PARAMETER:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Bad parameter." );
				return true;
			}
			case EBiosError.NOT_FOUND:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: User not found." );
				return true;
			}
			case EBiosError.NOT_IMPLEMENTED:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Function not implemented on this platform." );
				return true;
			}
			case EBiosError.PURCHASE_REQUIRED:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Purchase required." );
				return true;
			}
			case EBiosError.NOT_ALLOWED:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Not allowed." );
				return true;
			}
			case EBiosError.BANNED:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Not allowed." );
				return true;
			}
			case EBiosError.LOGICAL:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Logical error." );
				return true;
			}
			case EBiosError.BAD_SCRIPT:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Bad script linking." );
				return true;
			}
			case EBiosError.UPDATE_REQUIRED:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Update required." );
				return true;
			}
			case EBiosError.UPDATE_REQUIRED_AND_DOWNLOADED:
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Mandatory update is ready for install." );
				return true;
			}
		}
		DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Unknown error." );
		return true;
	}
	
	static void LoadServers( notnull GetServersInput inputValues )
	{
		GetClientServices();
		if( m_ClientServices )
		{
			m_ClientServices.GetLobbyService().GetServers( inputValues );
		}
		else
		{
			DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
		}
	}
	
	static void SetServerFavorited(string ipAddress, int port, int steamQueryPort, bool is_favorited )
	{
		GetClientServices();
		if( m_ClientServices )
		{
			if ( is_favorited )
			{
				m_ClientServices.GetLobbyService().AddServerFavorite( ipAddress, port, steamQueryPort );
			}
			else
			{
				m_ClientServices.GetLobbyService().RemoveServerFavorite( ipAddress, port, steamQueryPort );
			}
		}
		else
		{
			DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
		}
	}
	
	static void GetCurrentServerInfo( string ip, int port )
	{
		GetClientServices();
		
		m_CurrentServerIP = ip;
		m_CurrentServerPort = port;
		
		GetServersInput inputValues = new GetServersInput;
		
		inputValues.SetHostIp( ip );
		inputValues.SetHostPort( port );
		inputValues.m_Page = 0;
		inputValues.m_RowsPerPage = 10;
		inputValues.m_Platform = 1;

		#ifdef PLATFORM_XBOX
			inputValues.m_Platform = 2;
		#endif
		#ifdef PLATFORM_PS4
			inputValues.m_Platform = 3;
		#endif
		
		if( m_ClientServices )
		{
			m_ClientServices.GetLobbyService().GetServers( inputValues );
		}
	}
	
	static void ClearCurrentServerInfo()
	{
		m_CurrentServerInfo	= null;
		m_CurrentServerIP	= "";
		m_CurrentServerPort	= 0;
	}
	
	static void SetInviteServerInfo( string ip, int port )
	{
		m_InviteServerIP = ip;
		m_InviteServerPort = port;
	}
	
	static void GetInviteServerInfo( out string ip, out int port )
	{
		ip = m_InviteServerIP;
		port = m_InviteServerPort;
	}
	
	static void OnLoadServersAsync( ref GetServersResult result_list, EBiosError error, string response )
	{
		if( !ErrorCaught( error ) )
		{
			if( m_CurrentServerIP != "" && m_CurrentServerPort > 0 )
			{
				foreach( GetServersResultRow result : result_list.m_Results )
				{
					if( result.m_HostIp == m_CurrentServerIP && result.m_HostPort == m_CurrentServerPort )
					{
						m_CurrentServerInfo	= result;
						m_CurrentServerIP	= "";
						m_CurrentServerPort	= 0;
					}
				}
			}
			
			// todo: remove
			//foreach( GetServersResultRow res : result_list.m_Results )
			//{
			//	Print("OnLoadServersAsync: result id: " + res.m_Id + "modded: " + res.m_Modded);
			//}
			
			// just for example execute the retrieving of extended info for the first server entry in the list
			//if (result_list.m_Results.Count() > 0)
			//{
				//GetServersResultRow re = result_list.m_Results[0];
				//EBiosError er = m_ClientServices.GetLobbyService().GetServerModList(re.m_Id);
				//Print("OnLoadServersAsync GetServerModList returns:" + er);
			//}
			
			m_ServersAsyncInvoker.Invoke( result_list, error, response );
		}
		else
		{
			m_ServersAsyncInvoker.Invoke( null, error, "" );
		}
	}
	
	static GetServersResultRow GetCurrentServerInfo()
	{
		return m_CurrentServerInfo;
	}
	
	static void LoadFriends()
	{
		GetClientServices();
		if( m_ClientServices )
		{
			m_ClientServices.GetSocialService().GetFriendsAsync();
		}
		else
		{
			DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
		}
	}
	
	static void ShowUserProfile( string uid )
	{
		GetClientServices();
		if( m_ClientServices )
		{
			m_ClientServices.GetSocialService().ShowUserProfileAsync( uid );
		}
		else
		{
			DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
		}
	}
	
	static void OnUserProfileAsync(EBiosError error)
	{
		ErrorCaught( error );
	}
	
	static void OnFriendsAsync( ref BiosFriendInfoArray friend_list, EBiosError error )
	{
		if( !ErrorCaught( error ) )
		{
			m_FriendsAsyncInvoker.Invoke( friend_list );
			
			array<string> friends_simple = new array<string>;
			for( int i = 0; i < friend_list.Count(); i++ )
			{
				string uid = friend_list.Get( i ).m_Uid;
				if( m_FriendsList.Get( uid ) )
				{
					if( !BiosFriendInfo.Compare( m_FriendsList.Get( uid ), friend_list.Get( i ) ) )
					{
						friends_simple.Insert( friend_list.Get( i ).m_Uid );
					}
					m_FriendsList.Set( uid, friend_list.Get( i ) );
				}
				else
				{
					m_FriendsList.Insert( uid, friend_list.Get( i ) );
					friends_simple.Insert( friend_list.Get( i ).m_Uid );
				}
			}
			
			if( !m_FirstFriendsLoad )
			{
				if( ClientData.m_LastNewPlayers && ClientData.m_LastNewPlayers.m_PlayerList.Count() > 0 )
				{
					foreach( SyncPlayer player : ClientData.m_LastNewPlayers.m_PlayerList )
					{
						if( m_FriendsList.Contains( player.m_UID ) )
						{
							NotificationSystem.AddNotification( NotificationType.FRIEND_CONNECTED, 6, player.m_PlayerName + " " + "#ps4_invite_has_joined_your_session" );
						}
					}
					ClientData.m_LastNewPlayers.m_PlayerList.Clear();
				}
			}
			m_FirstFriendsLoad = false;
		}
	}
	
	static void LoadPermissions( array<string> player_list )
	{
		GetClientServices();
		if( m_ClientServices )
		{
			array<EBiosPrivacyPermission> perms = new array<EBiosPrivacyPermission>;
			perms.Insert( EBiosPrivacyPermission.COMMUNICATE_VOICE );
			
			ErrorCaught( m_ClientServices.GetPrivacyService().GetPermissionsAsync( player_list, perms ) );
		}
		else
		{
			DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
		}
	}
	
	static void OnPermissionsAsync( ref BiosPrivacyUidResultArray result_list, EBiosError error )
	{
		if( !ErrorCaught( error ) )
		{
			ref BiosPrivacyUidResultArray new_list = new BiosPrivacyUidResultArray;
			ref map<string, bool> mute_list = new map<string, bool>;
			
			for( int i = 0; i < result_list.Count(); i++ )
			{
				string uid = result_list.Get( i ).m_Uid;
				BiosPrivacyPermissionResultArray result_array = m_PermissionsList.Get( uid );
				BiosPrivacyPermissionResultArray result_array2 = result_list.Get( i ).m_Results;
				if( result_array && result_array2 )
				{
					if( !BiosPrivacyPermissionResult.Compare( result_array.Get( 0 ), result_array2.Get( 0 ) ) )
					{
						new_list.Insert( result_list.Get( i ) );
						m_PermissionsList.Set( uid, result_array2 );
						mute_list.Insert( uid, IsPlayerMuted( uid ) );
					}
				}
				else
				{
					m_PermissionsList.Insert( uid, result_array2 );
					new_list.Insert( result_list.Get( i ) );
					mute_list.Insert( uid, IsPlayerMuted( uid ) );
				}
				
				if( !m_MuteList.Contains( uid ) )
				{
					m_MuteList.Insert( uid, !result_array2.Get( 0 ).m_IsAllowed );
				}
			}
			m_PermissionsAsyncInvoker.Invoke( new_list );
			m_MuteUpdateAsyncInvoker.Invoke( mute_list );
		}
	}
	
	static bool IsPlayerMuted( string id )
	{
		BiosPrivacyPermissionResultArray perms = m_PermissionsList.Get( id );
		if( perms )
		{
			for( int i = 0; i < perms.Count(); i++ )
			{
				BiosPrivacyPermissionResult result = perms.Get( i );
				if( result.m_Permission == EBiosPrivacyPermission.COMMUNICATE_VOICE )
				{
					if( !result.m_IsAllowed )
						return true;
				}
			}
		}
		return m_MuteList.Get( id );
	}
	
	static bool MutePlayer( string id, bool mute )
	{
		if( m_MuteList.Contains( id ) )
		{
			m_MuteList.Set( id, mute );
		}
		else
		{
			m_MuteList.Insert( id, mute );
		}
		
		return true;
	}
	
	static map<string, bool> GetMuteList()
	{
		return m_MuteList;
	}
	
	static void ShowInviteScreen()
	{
		#ifdef PLATFORM_CONSOLE
			GetClientServices();
			if( m_ClientServices )
			{
				string addr;
				int port;
				if( GetGame().GetHostAddress( addr, port ) )
				{
					ErrorCaught( m_ClientServices.GetSessionService().ShowInviteToGameplaySessionAsync( addr, port ) );
				}
			}
			else
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
			}
		#endif
	}
	
	static void LoadMPPrivilege()
	{
		#ifdef PLATFORM_CONSOLE
			GetClientServices();
			if( m_ClientServices )
			{
				ErrorCaught( m_ClientServices.GetPrivacyService().GetPrivilegeAsync( EBiosPrivacyPrivilege.MULTIPLAYER_GAMEPLAY, true ) );
			}
			else
			{
				DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
			}
		#else
			OnLoadMPPrivilege( EBiosError.OK );
		#endif
	}
	
	static void LoadVoicePrivilege()
	{
		GetClientServices();
		if( m_ClientServices )
		{
			ErrorCaught( m_ClientServices.GetPrivacyService().GetPrivilegeAsync( EBiosPrivacyPrivilege.COMMUNICATE_VOICE, true ) );
		}
		else
		{
			DebugPrint.LogErrorAndTrace( "BiosClientServices Error: Service reference does not exist." );
		}
	}
	
	static void OnLoadMPPrivilege( EBiosError err )
	{
		if( !ErrorCaught( err ) )
		{
			g_Game.TryConnect();
		}
		else
		{
			if( g_Game.GetGameState() != DayZGameState.MAIN_MENU )
			{
				g_Game.MainMenuLaunch();
			}
			else
			{
				g_Game.SetLoadState( DayZLoadState.MAIN_MENU_START );
				g_Game.GamepadCheck();
			}
		}
	}
	
	static void OnLoadVoicePrivilege( EBiosError err )
	{
		if( g_Game.GetGameState() == DayZGameState.IN_GAME )
		{
			#ifdef PLATFORM_PS4
			GetGame().GetWorld().DisableReceiveVoN( ErrorCaught( err ) );
			#endif
			GetGame().GetWorld().DisableTransmitVoN( ErrorCaught( err ) );
		}
	}
	
	static void SetSessionHandle( string handle )
	{
		GetClientServices();
		if( m_ClientServices )
		{
			m_ClientServices.GetSessionService().m_CurrentHandle = handle;
		}
	}
	
	static string GetSessionHandle()
	{
		GetClientServices();
		if( m_ClientServices )
		{
			return m_ClientServices.GetSessionService().m_CurrentHandle;
		}
		return "";
	}
	
	static void GetSession()
	{
		GetClientServices();
		if( m_ClientServices )
		{
			m_ClientServices.GetSessionService().TryGetSession( GetSessionHandle() );
		}
	}

	static BiosUser GetBiosUser()
	{
		return m_BiosUser;
	}

	static void SetBiosUser(BiosUser user)
	{
		m_BiosUser = user;
	}

	
	static bool GetMultiplayState()
	{
		return m_MultiplayState;
	}
	
	static void SetMultiplayState( bool state )
	{
		m_MultiplayState = state;
		bool is_multiplay;
		if( ClientData.GetSimplePlayerList() )
			is_multiplay = state && ( ClientData.GetSimplePlayerList().Count() > 1 );

		if( m_ClientServices )
			m_ClientServices.GetSessionService().SetMultiplayState(is_multiplay);
	}
	
	static void EnterGameplaySession()
	{
		string addr;
		int port;
		if( GetGame().GetHostAddress( addr, port ) )
		{
			GetClientServices();
			if( m_ClientServices )
			{
				m_ClientServices.GetSessionService().EnterGameplaySessionAsync( addr, port );
				SetMultiplayState(true);
			}
		}
	}
	
	static void LeaveGameplaySession()
	{
		GetClientServices();
		if( m_ClientServices )
		{
			if( m_CurrentServerInfo )
				m_ClientServices.GetSessionService().LeaveGameplaySessionAsync(m_CurrentServerInfo.m_HostIp, m_CurrentServerInfo.m_HostPort);
			else if( m_CurrentServerIP != "" )
				m_ClientServices.GetSessionService().LeaveGameplaySessionAsync(m_CurrentServerIP, m_CurrentServerPort);
				
			SetMultiplayState(false);
			m_FirstFriendsLoad = true;
			
			if( m_FriendsList )
				m_FriendsList.Clear();
		}
	}
	
	static void SetGameplayActivity()
	{
		string addr;
		int port;
		if( GetGame().GetHostAddress( addr, port ) )
		{
			GetClientServices();
			if( m_ClientServices )
			{
				m_ClientServices.GetSessionService().SetGameplayActivityAsync( addr, port );
			}
		}
	}
	
	static void SetPendingInviteList( array<string> invitees )
	{
		string addr;
		int port;
		if( GetGame().GetHostAddress( addr, port ) )
		{
			GetClientServices();
			if( m_ClientServices )
			{
				m_PendingInvites = invitees;
				m_ClientServices.GetSessionService().InviteToGameplaySessionAsync( addr, port, GetPendingInviteList() );
			}
		}
		else
		{
			m_PendingInvites = invitees;
		}
	}
	
	static array<string> GetPendingInviteList()
	{
		array<string> already_on_server = ClientData.GetSimplePlayerList();
		if( already_on_server && m_PendingInvites )
		{
			array<string> new_to_server = new array<string>;
			foreach( string invitee : m_PendingInvites )
			{
				if( already_on_server.Find( invitee ) == -1 )
				{
					new_to_server.Insert( invitee );
				}
			}
			return new_to_server;
		}
		else
		{
			return m_PendingInvites;
		}
	}
	
	static void ClearPendingInviteList( array<string> invitees )
	{
		delete m_PendingInvites;
	}
	
	static int m_AutoConnectTries = 0;
	static void AutoConnectToEmptyServer()
	{
		GetClientServices();
		if( m_ClientServices && m_AutoConnectTries == 0 )
		{
			m_AutoConnectTries = 1;
			ref GetFirstServerWithEmptySlotInput input = new GetFirstServerWithEmptySlotInput;
			input.SetOfficial( true );
			m_ClientServices.GetLobbyService().GetFirstServerWithEmptySlot( input );
		}
	}
	
	static GetServersResultRow GetRandomFreeResult( GetFirstServerWithEmptySlotResult results )
	{
		GetServersResultRow result;
		array<ref GetServersResultRow> results_free = new array<ref GetServersResultRow>;
		
		if( results && results.m_Result && results.m_Result.m_Results && results.m_Result.m_Results.Count() > 0 )
		{
			foreach( GetServersResultRow result_temp : results.m_Result.m_Results )
			{
				if( result_temp.m_FreeSlots > 0 )
				{
					results_free.Insert( result_temp );
				}
			}
		}
		
		return results_free.GetRandomElement();
	}
	
	static void OnAutoConnectToEmptyServer( ref GetFirstServerWithEmptySlotResult result_list, EBiosError error )
	{
		if( !ErrorCaught( error ) )
		{
			GetServersResultRow result = GetRandomFreeResult( result_list );
			if( result )
			{
				g_Game.ConnectFromServerBrowser( result.m_HostIp, result.m_HostPort );
				m_AutoConnectTries = 0;
				return;
			}
			else
			{
				GetGame().GetUIManager().ShowDialog( "#str_xbox_authentification_fail_title", "#str_xbox_authentification_fail", 232, DBT_OK, DBB_NONE, DMT_INFO, GetGame().GetUIManager().GetMenu() );
			}
		}
		
		if( m_AutoConnectTries < 3 )
		{
			m_AutoConnectTries++;
			ref GetFirstServerWithEmptySlotInput input = new GetFirstServerWithEmptySlotInput;
			input.SetOfficial( true );
			m_ClientServices.GetLobbyService().GetFirstServerWithEmptySlot( input );
		}
		else
		{
			GetGame().GetUIManager().ShowDialog( "#str_xbox_authentification_fail_title", "#xbox_authentification_fail", 232, DBT_OK, DBB_NONE, DMT_INFO, GetGame().GetUIManager().GetMenu() );
		}
	}
	
	static void GetServerModList( string server_id )
	{
		GetClientServices();
		if( m_ClientServices )
		{
			m_ClientServices.GetLobbyService().GetServerModList( server_id );
		}
	}
	
	static void OnGetServerModList( ref GetServerModListResult result_list, EBiosError error )
	{
		if( !ErrorCaught( error ) )
		{
			m_ServerModLoadAsyncInvoker.Invoke( result_list );
		}
	}
	
	static bool IsGameTrial( bool sim )
	{
		#ifdef PLATFORM_XBOX
		#ifndef PLATFORM_WINDOWS
		if( m_TrialService )
			return m_TrialService.IsGameTrial( sim );
		#endif
		#endif
		return false;
	}
	
	static bool CheckUpdate()
	{
		GetClientServices();
		if ( m_ClientServices )
		{
			EBiosError error = m_ClientServices.GetPackageService().CheckUpdateAsync();
			
			if ( !error )
			{
				return true;
			}
		}
		
		return false;
	}
	
	static void PromptUpdate()
	{
		GetClientServices();
		if ( m_ClientServices )
		{
			m_ClientServices.GetPackageService().PromptUpdateAsync();
		}
	}
}