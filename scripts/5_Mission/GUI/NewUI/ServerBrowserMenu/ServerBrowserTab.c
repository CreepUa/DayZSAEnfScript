enum TabType
{
	OFFICIAL,
	COMMUNITY,
	LAN,
	NONE
}

enum SelectedPanel
{
	BROWSER,
	FILTERS,
	MENU
}

class ServerBrowserTab extends ScriptedWidgetEventHandler
{
	protected Widget										m_Root;
	protected ScrollWidget									m_ServerListScroller;
	protected SpacerBaseWidget								m_ServerList;
	
	//protected ref array<ref GetServersResultRow>			m_Entries;
	
	protected ref map<string, ref ServerBrowserEntry>		m_EntryWidgets;

	protected ref ServerBrowserFilterContainer				m_Filters;
	
	protected ServerBrowserMenuNew							m_Menu;
	protected ServerBrowserEntry							m_SelectedServer;
	
	protected TabType										m_TabType;
	protected ESortType										m_SortType;
	protected ESortOrder									m_SortOrder;
	
	protected SelectedPanel									m_SelectedPanel;
	protected bool											m_Initialized;
	protected bool											m_BegunLoading;
	protected bool											m_Loading;
	protected int											m_TotalServers;
	protected int											m_TotalLoadedServers;
	protected int											m_LastLoadedPage;
	protected int											m_TotalPages;
	protected bool											m_LoadingFinished;
	protected int											m_CurrentPageNum;
	
	protected string										m_CurrentSelectedServer;
	protected int											m_CurrentLoadedPage;
	protected ref GetServersInput							m_CurrentFilterInput;
	
	protected Widget										m_ApplyFilter;
	protected Widget										m_RefreshList;
	protected Widget										m_FiltersChanged;
	protected Widget										m_HostSort;
	protected Widget										m_TimeSort;
	protected Widget										m_PopulationSort;
	protected Widget										m_SlotsSort;
	protected Widget										m_PingSort;
	protected TextWidget									m_LoadingText;
	
	protected ref map<ESortType, ref array<ref GetServersResultRow>> m_EntriesSorted;
	protected ref map<ESortType, ESortOrder>				m_SortInverted;
	
	
	void ServerBrowserTab( Widget parent, ServerBrowserMenuNew menu, TabType type )
	{
		Construct(parent, menu, type);
	}
	
	protected void Construct( Widget parent, ServerBrowserMenuNew menu, TabType type )
	{
		m_SortInverted = new map<ESortType, ESortOrder>;
		m_EntriesSorted = new map<ESortType, ref array<ref GetServersResultRow>>;
		
		m_LoadingText			= TextWidget.Cast( m_Root.FindAnyWidget( "loading_servers_info" ) );
	}
	
	void ~ServerBrowserTab()
	{
		if( m_Filters )
			m_Filters.SaveFilters();
		
		if(m_Root)
			delete m_Root;
	}

	ServerBrowserMenuNew GetRootMenu()
	{
		return m_Menu;
	}
	
	bool GetIsServerLoadingFinished()
	{
		return m_LoadingFinished;
	}
	
	override bool OnClick( Widget w, int x, int y, int button )
	{
		
	}
	
	void ScrollToEntry( ServerBrowserEntry entry )
	{
		if( entry )
		{
			float x, y;
			float x_s, y_s;
			float x_l, y_l;
			
			Widget root			= entry.GetRoot();
			Widget first_child	= root.GetParent().GetChildren();
			Widget last_child	= first_child;
			while( last_child )
			{
				if( last_child.GetSibling() )
					last_child = last_child.GetSibling();
				else
					break;
			}
			
			root.GetParent().Update();
			root.Update();
			
			m_ServerListScroller.GetScreenPos( x, y );
			m_ServerListScroller.GetScreenSize( x_s, y_s );
			
			float bottom_pos = y + y_s;
			
			root.GetScreenPos( x_l, y_l );
			root.GetScreenSize( x_s, y_s );
			
			if( root == first_child )
			{
				m_ServerListScroller.VScrollToPos01( 0 );
			}
			else if( root == last_child )
			{
				m_ServerListScroller.VScrollToPos01( 1 );
			}
			else if( y_l + y_s >= bottom_pos )
			{
				m_ServerListScroller.VScrollToPos( m_ServerListScroller.GetVScrollPos() + y_s );
			}
			else if( y_l <= y )
			{
				m_ServerListScroller.VScrollToPos( m_ServerListScroller.GetVScrollPos() - y_s );
			}
		}
	}
	
	void Focus()
	{
		if( m_EntryWidgets.Contains( m_CurrentSelectedServer ) )
		{
			m_EntryWidgets.Get( m_CurrentSelectedServer ).Focus();
			ScrollToEntry( m_EntryWidgets.Get( m_CurrentSelectedServer ) );
		}
	}
	
	void OnFilterFocusLost( Widget w )
	{
		m_SelectedPanel = SelectedPanel.FILTERS;
		m_Menu.FilterFocus( false );
	}
	
	void OnFilterFocus( Widget w )
	{
		m_SelectedPanel = SelectedPanel.FILTERS;
		m_Menu.FilterFocus( true );
	}
	
	void OnFilterChanged()
	{
		
	}
	
	void ServerListFocus( bool focus, bool favorite )
	{
		m_SelectedPanel = SelectedPanel.BROWSER;
		
		if (!m_Menu)
			return;
		
		m_Menu.ServerListFocus( focus, favorite );
	}
	
	override bool OnFocus( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorHighlight( w );
			return true;
		}
		return false;
	}
	
	override bool OnFocusLost( Widget w, int x, int y )
	{
		if( IsFocusable( w ) )
		{
			ColorNormal( w );
			return true;
		}
		return false;
	}
	
	bool IsFocusable( Widget w )
	{
		if( w )
		{
			return ( w == m_ApplyFilter || w == m_RefreshList );
		}
		return false;
	}
	
	void SetPanelFocus()
	{
		
	}
	
	void PressA()
	{
		
	}
	
	void PressX()
	{
		if( m_Menu.GetServersLoadingTab() == TabType.NONE )
			RefreshList();
	}
	
	void PressY(){}
	void PressSholderLeft(){}
	void PressSholderRight(){}
	void Left(){}
	void LeftHold(){}
	void LeftRelease(){}
	void Right(){}
	void RightHold(){}
	void RightRelease(){}
	void Up(){}
	void Down(){}
	
	void GetNextEntry()
	{
		Widget focused = GetFocus();
		if( !focused )
			return;
		Widget sibling = focused.GetSibling();
		if( !sibling )
			return;
		
		if( focused.GetName() == "server_browser_list_entry_root" )
		{
			if( sibling )
				SetFocus( focused.GetSibling() );
			else
				SetFocus( focused.GetParent().GetSibling().GetChildren() );
		}
	}
	
	void GetPrevEntry()
	{
		Widget focused = GetFocus();
		if( focused && focused.GetName() == "server_browser_list_entry_root" )
		{
			Widget sibling = focused.GetParent().GetChildren();
			if( focused == sibling )
				return;
			
			while( sibling )
			{
				if( sibling && sibling.GetSibling() == focused )
				{
					SetFocus( sibling );
				}
				else
				{
					sibling = sibling.GetSibling();
				}
			}
		}
	}
	
	void GetNextFilter()
	{
	
	}
	
	void GetPrevFilter()
	{
	
	}
	
	void SetCurrentPage(int page_num)
	{
		m_CurrentPageNum = page_num;
	}
	
	int GetCurrentPage()
	{
		return m_CurrentPageNum;
	}
	
	bool IsNotInitialized()
	{
		return !m_Initialized;
	}
	
	void ResetFilters()
	{
		m_Filters.ResetFilters();
	}
	
	void ApplyFilters()
	{
	
	}
	
	void AddFavoritesToFilter( ref GetServersInput input )
	{
		m_Menu.AddFavoritesToFilter( input );
	}
	
	void RefreshList()
	{
		m_Menu.SetServersLoadingTab( m_TabType );
		
		m_LoadingFinished = false;
		m_Initialized = true;
		m_BegunLoading = false;
		m_LastLoadedPage = 0;
		m_TotalPages = -1;
		m_TotalServers = 0;
		m_TotalLoadedServers = 0;
		m_CurrentLoadedPage = 0;
		
		//m_Entries.Clear();
		m_EntryWidgets.Clear();

#ifndef PLATFORM_CONSOLE // PLATFORM_WINDOWS
		m_CurrentFilterInput = m_Filters.GetFilterOptionsPC();
		m_CurrentFilterInput.m_Page = 0;
#else
#ifdef PLATFORM_CONSOLE
		m_CurrentFilterInput = m_Filters.GetFilterOptionsConsoles();
		m_CurrentFilterInput.m_SortBy = GetSortOption();
		m_CurrentFilterInput.m_SortOrder = m_SortOrder;
		m_CurrentFilterInput.m_Page = GetCurrentPage();
#endif
#endif
		
		Print("RefreshList Start");
		m_Loading = true;
		switch( m_TabType )
		{
			case TabType.OFFICIAL:
			{
				m_CurrentFilterInput.SetOfficialFilter( true );
				OnlineServices.LoadServers( m_CurrentFilterInput );
				break;
			}
			case TabType.COMMUNITY:
			{
				m_CurrentFilterInput.SetOfficialFilter( false );
				OnlineServices.LoadServers( m_CurrentFilterInput );
				break;
			}
			case TabType.LAN:
			{
				m_CurrentFilterInput.SetLAN();
				OnlineServices.LoadServers( m_CurrentFilterInput );
				break;
			}
		}
		
		Print("RefreshList End");
		//m_ServerListScroller.VScrollToPos01( 0 );
	}
	
	void GetNextPage()
	{
		if( m_TotalPages > 0 && m_LastLoadedPage < m_TotalPages )
		{
			m_CurrentFilterInput.m_Page = m_LastLoadedPage + 1;
			OnlineServices.LoadServers( m_CurrentFilterInput );
		}
	}
	
	void SelectServer( ServerBrowserEntry server )
	{
#ifdef PLATFORM_CONSOLE
		ScrollToEntry( server );
#endif
		
		m_SelectedServer = server;
		
		if (!m_Menu)
			return;
		
		m_Menu.SelectServer( server );
	}
	
	void OnLoadServersAsyncPC( ref GetServersResult result_list, EBiosError error, string response )
	{
		
	}
	
	void OnLoadServersAsyncConsole( GetServersResult result_list, EBiosError error, string response )
	{
		
	}
	
	void SetSort( ESortType type, ESortOrder order )
	{
		m_SortOrder = order;
		m_SortType	= type;
	}
	
	bool IsPingInRange( int ping, string max_ping )
	{
		int max = max_ping.Substring( 1, max_ping.Length() - 1 ).ToInt();
		
		if( ping < max )
			return true;
		return false;
	}
		
	bool PassFilter( GetServersResultRow result )
	{	
		if ( !m_Menu || m_Menu.GetServersLoadingTab() != m_TabType )
		{
			return false;
		}
		
		if( m_Filters.PingIsSet() )
		{
			if ( !IsPingInRange( result.m_Ping, m_Filters.m_PingFilter.GetStringValue() ) )
			{
				return false;
			}
		}
		
		#ifndef PLATFORM_CONSOLE
		if( m_Filters.FavoriteIsSet() )
		{
			bool is_fav = result.m_Favorite;
			
			if ( !is_fav && m_Filters.m_Options["m_FavoritedFilter"] == "#server_browser_show" )
			{
				return false;
			}
			
			if ( is_fav && m_Filters.m_Options["m_FavoritedFilter"] == "#server_browser_hide" )
			{
				return false;
			}
		}
		#endif

		if( m_Filters.PreviouslyIsSet() )
		{
			bool is_visited = g_Game.IsVisited( result.m_HostIp, result.m_HostPort );
			
			if ( !is_visited && m_Filters.m_Options["m_PreviouslyPlayedFilter"] == "#server_browser_show" )
			{
				return false;
			}
			
			if ( is_visited && m_Filters.m_Options["m_PreviouslyPlayedFilter"] == "#server_browser_hide" )
			{
				return false;
			}
		}
		
		return true;
	}
	
	void Connect( ServerBrowserEntry server )
	{
		if( !m_Menu )
			return;
		
		if( m_Menu.GetServersLoadingTab() != TabType.NONE )
			return;
		
		m_SelectedServer = server;
		m_Menu.Connect( server );
	}
	
	string GetSortOption()
	{
		switch( m_SortType )
		{
			case ESortType.HOST:
			{
				return "name";
			}
			case ESortType.TIME:
			{
				return "name";
			}
			case ESortType.POPULATION:
			{
				return "currentNumberPlayers";
			}
			case ESortType.SLOTS:
			{
				return "freeSlots";
			}
			case ESortType.PING:
			{
				return "name";
			}
		}
		return "";
	}
	
	int AddSorted( GetServersResultRow entry )
	{	
		return -1;
	}
	
	void Unfavorite( string uid )
	{
		ServerBrowserEntry entry;
		if( m_EntryWidgets.Find( uid, entry ) )
		{
			entry.SetFavorite( false );
		}
	}
	
	TabType GetTabType()
	{
		return m_TabType;
	}
	
	void ButtonEnable( Widget w )
	{
		w.ClearFlags( WidgetFlags.IGNOREPOINTER );
		ColorNormal(w);
	}
	
	void ButtonDisable( Widget w )
	{
		w.SetFlags( WidgetFlags.IGNOREPOINTER );
		ColorDisable(w);
	}
	
	//Coloring functions (Until WidgetStyles are useful)
	void ColorHighlight( Widget w )
	{
		if( w.IsInherited( ButtonWidget ) )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			button.SetTextColor( ARGB( 255, 200, 0, 0 ) );
		}
		
		w.SetColor( ARGB( 255, 0, 0, 0) );
		
		TextWidget text1	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_text" ) );
		TextWidget text2	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_label" ) );
		TextWidget text3	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_text_1" ) );
		ImageWidget image	= ImageWidget.Cast( w.FindAnyWidget( w.GetName() + "_image" ) );
		Widget option		= Widget.Cast( w.FindAnyWidget( w.GetName() + "_option_wrapper" ) );
		Widget option_label = w.FindAnyWidget( "option_label" );
		
		if( text1 )
		{
			text1.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if( text2 )
		{
			text2.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if( text3 )
		{
			text3.SetColor( ARGB( 255, 255, 0, 0 ) );
			w.SetAlpha(1);
		}
		
		if( image )
		{
			image.SetColor( ARGB( 255, 200, 0, 0 ) );
		}
		
		if ( option )
		{
			option.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if ( option_label )
		{
			option_label.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
	}
	
	void ColorNormal( Widget w )
	{
		//Print("ColorNormal -> "+ w.GetName());
		//DumpStack();
		
		if ( (w.GetFlags() & WidgetFlags.IGNOREPOINTER) == WidgetFlags.IGNOREPOINTER )
		{
			return;
		}
		
		if( w.IsInherited( ButtonWidget ) )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			button.SetTextColor( ARGB( 255, 255, 255, 255 ) );
		}
		
		TextWidget text1	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_text" ) );
		TextWidget text2	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_text_1" ) );
		TextWidget text3	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_label" ) );
		ImageWidget image	= ImageWidget.Cast( w.FindAnyWidget( w.GetName() + "_image" ) );
		Widget option		= w.FindAnyWidget( w.GetName() + "_option_wrapper" );
		Widget option_label = w.FindAnyWidget( "option_label" );
		
		if( text1 )
		{
			text1.SetColor( ARGB( 255, 255, 255, 255 ) );
		}
		
		if( text2 )
		{
			text2.SetColor( ARGB( 255, 255, 255, 255 ) );
		}
		
		if( text3 )
		{
			text3.SetColor( ARGB( 255, 255, 255, 255 ) );
			w.SetAlpha(0);
		}
		
		if( image )
		{
			image.SetColor( ARGB( 255, 255, 255, 255 ) );
		}
		
		if ( option )
		{
			option.SetColor( ARGB( 150, 255, 255, 255 ) );
		}
		
		if ( option_label )
		{
			option_label.SetColor( ARGB( 255, 255, 255, 255 ) );
		}
	}
	
	void ColorDisable( Widget w )
	{
		#ifdef PLATFORM_WINDOWS
		SetFocus( null );
		#endif
		
		if ( w )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			if( button )
			{
				button.SetTextColor( ColorManager.COLOR_DISABLED_TEXT );
			}
		}
	}
}