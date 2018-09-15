/////////////////////////////////////////////////////////////////////////////
// Name:        SimpleEdit.cpp
// Author:      XX
// Created:     XX/XX/XX
// Copyright:   
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
    #pragma implementation "SimpleEdit.h"
#endif

// For compilers that support precompilation
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// Include private headers
#include "SimpleEdit.h"

// WDR: class implementations

//----------------------------------------------------------------------------
// PlayerEditDialog
//----------------------------------------------------------------------------

// WDR: event table for PlayerEditDialog

BEGIN_EVENT_TABLE(PlayerEditDialog,wxDialog)
    EVT_SPINCTRL( ID_PLAYERID, PlayerEditDialog::OnChangeID )
    EVT_SPINCTRL( ID_PLAYERINVENTORYSLOT, PlayerEditDialog::OnSlotChange )
    EVT_SPINCTRL( ID_PLAYERWEAPON, PlayerEditDialog::OnWeaponChange )
    EVT_SPINCTRL( ID_PLAYERARMOR, PlayerEditDialog::OnArmorChange )
    EVT_TEXT( ID_PLAYERCURRENTITEMID, PlayerEditDialog::OnInventoryText )
    EVT_BUTTON( ID_PLAYERSAVE, PlayerEditDialog::OnSave )
    EVT_BUTTON( ID_PLAYERNEW, PlayerEditDialog::OnNew )
    EVT_BUTTON( ID_PLAYERDELETE, PlayerEditDialog::OnDelete )
    EVT_TEXT( ID_PLAYERLEVEL, PlayerEditDialog::OnTextLevel )
    EVT_TEXT( ID_PLAYERSTRENGTH, PlayerEditDialog::OnTextStrength )
    EVT_TEXT( ID_PLAYERHEALTH, PlayerEditDialog::OnTextHealth )
    EVT_TEXT( ID_PLAYERAGILITY, PlayerEditDialog::OnTextAgility )
    EVT_TEXT( ID_PLAYERMAXHP, PlayerEditDialog::OnTextMaxHP )
    EVT_TEXT( ID_PLAYERACCURACY, PlayerEditDialog::OnTextAccuracy )
    EVT_TEXT( ID_PLAYERDODGING, PlayerEditDialog::OnTextDodging )
    EVT_TEXT( ID_PLAYERSTRIKEDAMAGE, PlayerEditDialog::OnTextStrikeDamage )
    EVT_TEXT( ID_PLAYERDAMAGEABSORB, PlayerEditDialog::OnTextDamageAbsorb )
    EVT_TEXT( ID_PLAYERHPREGEN, PlayerEditDialog::OnTextHPRegen )
END_EVENT_TABLE()

PlayerEditDialog::PlayerEditDialog( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    // WDR: dialog function PlayerEdit for PlayerEditDialog
    PlayerEdit( this, TRUE ); 

    m_lastid = 0;
    if( g_players.size() != 0 )
        m_lastid = g_players.begin()->first;
    LoadPlayer( m_lastid );
}

PlayerEditDialog::~PlayerEditDialog()
{
}

// WDR: handler implementations for PlayerEditDialog

void PlayerEditDialog::OnTextHPRegen( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[HPREGEN] = BasicLib::totype<int>( GetPlayerhpregen()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextDamageAbsorb( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[DAMAGEABSORB] = BasicLib::totype<int>( GetPlayerdamageabsorb()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextStrikeDamage( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[STRIKEDAMAGE] = BasicLib::totype<int>( GetPlayerstrikedamage()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextDodging( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[DODGING] = BasicLib::totype<int>( GetPlayerdodging()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextAccuracy( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[ACCURACY] = BasicLib::totype<int>( GetPlayeraccuracy()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextMaxHP( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[MAXHITPOINTS] = BasicLib::totype<int>( GetPlayermaxhp()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextAgility( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[AGILITY] = BasicLib::totype<int>( GetPlayeragility()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextHealth( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[HEALTH] = BasicLib::totype<int>( GetPlayerhealth()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextStrength( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_baseattributes[STRENGTH] = BasicLib::totype<int>( GetPlayerstrength()->GetValue().c_str() );
        Update();
    }
}

void PlayerEditDialog::OnTextLevel( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_level = BasicLib::totype<int>( GetPlayerlevel()->GetValue().c_str() );
        Update();
    }
}



void PlayerEditDialog::OnDelete( wxCommandEvent &event )
{
    if( m_lastid == 0 )
        return;

    wxMessageDialog dialog( this, wxT("Are you sure you want to delete this Player?"),
        wxT("Delete?"), wxYES_NO | wxICON_EXCLAMATION | wxNO_DEFAULT );

    if( dialog.ShowModal() == wxID_YES )
    {
        g_players.erase( g_players.find( m_lastid ) );
        LoadPlayer( m_lastid + 1 );
    }
}

void PlayerEditDialog::OnNew( wxCommandEvent &event )
{
    entityid id = FindOpenID( g_players );
    g_players[id].m_id = id;
    LoadPlayer( id );
}

void PlayerEditDialog::OnSave( wxCommandEvent &event )
{
    SavePlayer();
}

void PlayerEditDialog::OnInventoryText( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        entityid id = 0;
        if( GetPlayercurrentitemid()->GetValue().Length() != 0 )
            id = BasicLib::totype<entityid>( GetPlayercurrentitemid()->GetValue().c_str() );

        int inv = GetPlayerinventoryslot()->GetValue();

        itr->second.m_inventory[inv] = id;
        Update();
    }
}

void PlayerEditDialog::OnArmorChange( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_armor = GetPlayerarmor()->GetValue();
        Update();
    }
}

void PlayerEditDialog::OnWeaponChange( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_weapon = GetPlayerweapon()->GetValue();
        Update();
    }
}

void PlayerEditDialog::OnSlotChange( wxCommandEvent &event )
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        entityid inv = GetPlayerinventoryslot()->GetValue();
        GetPlayercurrentitemid()->SetValue( BasicLib::tostring( itr->second.m_inventory[inv] ).c_str() );
        Update();
    }
}

void PlayerEditDialog::OnChangeID( wxCommandEvent &event )
{
    if( g_players.size() == 0 )
        return;

    wxSpinCtrl* idbox = GetPlayerid();
    entityid id = idbox->GetValue();
    idbox->SetValue( m_lastid );        // reset to previous value for now.

    std::map<entityid, Player>::iterator itr = g_players.find( id );
    if( itr == g_players.end() )
    {
        if( id < g_players.begin()->first )
            id = g_players.rbegin()->first;
        else if( id > g_players.rbegin()->first )
            id = g_players.begin()->first;
        else if( id < m_lastid )
        {
            itr = g_players.lower_bound( id );
            --itr;
            if( itr == g_players.end() )
                return;
            id = itr->first;
        }
        else
        {
            itr = g_players.upper_bound( id );
            if( itr == g_players.end() )
                return;
            id = itr->first;
        }
    }

    // at this point, id should point to the item you want
    SavePlayer();
    LoadPlayer( id );
}

void PlayerEditDialog::LoadPlayer( entityid p_id )
{
    std::map<entityid, Player>::iterator itr = g_players.find( p_id );
    if( itr != g_players.end() )
    {
        GetPlayerid()->SetValue( itr->first );
        m_lastid = p_id;

        GetPlayername()->SetValue( itr->second.m_name.c_str() );
        GetPlayerpass()->SetValue( itr->second.m_pass.c_str() );
        GetPlayerrank()->SetValue( GetRankString( itr->second.m_rank ).c_str() );

        GetPlayerstatpoints()->SetValue( BasicLib::tostring( itr->second.m_statpoints ).c_str() );
        GetPlayerexperience()->SetValue( BasicLib::tostring( itr->second.m_experience ).c_str() );
        GetPlayerlevel()->SetValue( BasicLib::tostring( itr->second.m_level ).c_str() );
        GetPlayerroom()->SetValue( BasicLib::tostring( itr->second.m_room ).c_str() );
        GetPlayerhp()->SetValue( BasicLib::tostring( itr->second.m_hitpoints ).c_str() );
        GetPlayerattacktime()->SetValue( BasicLib::tostring( itr->second.m_nextattacktime ).c_str() );
        GetPlayermoney()->SetValue( BasicLib::tostring( itr->second.m_money ).c_str() );

        GetPlayerstrength()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[STRENGTH] ).c_str() );
        GetPlayerhealth()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[HEALTH] ).c_str() );
        GetPlayeragility()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[AGILITY] ).c_str() );
        GetPlayermaxhp()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[MAXHITPOINTS] ).c_str() );
        GetPlayeraccuracy()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[ACCURACY] ).c_str() );
        GetPlayerdodging()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[DODGING] ).c_str() );
        GetPlayerstrikedamage()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[STRIKEDAMAGE] ).c_str() );
        GetPlayerdamageabsorb()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[DAMAGEABSORB] ).c_str() );
        GetPlayerhpregen()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[HPREGEN] ).c_str() );

        GetPlayerinventoryslot()->SetValue( 0 );
        GetPlayerweapon()->SetValue( itr->second.m_weapon );
        GetPlayerarmor()->SetValue( itr->second.m_armor );
        GetPlayercurrentitemid()->SetValue( BasicLib::tostring( itr->second.m_inventory[0] ).c_str() );
        Update();
    }
}

void PlayerEditDialog::SavePlayer()
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        itr->second.m_name = GetPlayername()->GetValue();
        itr->second.m_pass = GetPlayerpass()->GetValue();
        itr->second.m_rank = GetRank( GetPlayerrank()->GetValue().c_str() );
        itr->second.m_statpoints = BasicLib::totype<int>( GetPlayerstatpoints()->GetValue().c_str() );
        itr->second.m_experience = BasicLib::totype<int>( GetPlayerexperience()->GetValue().c_str() );
        itr->second.m_level = BasicLib::totype<int>( GetPlayerlevel()->GetValue().c_str() );
        itr->second.m_room = BasicLib::totype<int>( GetPlayerroom()->GetValue().c_str() );
        itr->second.m_hitpoints = BasicLib::totype<int>( GetPlayerhp()->GetValue().c_str() );
        itr->second.m_nextattacktime = BasicLib::totype<int>( GetPlayerattacktime()->GetValue().c_str() );
        itr->second.m_money = BasicLib::totype<int>( GetPlayermoney()->GetValue().c_str() );

        itr->second.m_baseattributes[STRENGTH] = BasicLib::totype<int>( GetPlayerstrength()->GetValue().c_str() );
        itr->second.m_baseattributes[HEALTH] = BasicLib::totype<int>( GetPlayerhealth()->GetValue().c_str() );
        itr->second.m_baseattributes[AGILITY] = BasicLib::totype<int>( GetPlayeragility()->GetValue().c_str() );
        itr->second.m_baseattributes[MAXHITPOINTS] = BasicLib::totype<int>( GetPlayermaxhp()->GetValue().c_str() );
        itr->second.m_baseattributes[ACCURACY] = BasicLib::totype<int>( GetPlayeraccuracy()->GetValue().c_str() );
        itr->second.m_baseattributes[DODGING] = BasicLib::totype<int>( GetPlayerdodging()->GetValue().c_str() );
        itr->second.m_baseattributes[STRIKEDAMAGE] = BasicLib::totype<int>( GetPlayerstrikedamage()->GetValue().c_str() );
        itr->second.m_baseattributes[DAMAGEABSORB] = BasicLib::totype<int>( GetPlayerdamageabsorb()->GetValue().c_str() );
        itr->second.m_baseattributes[HPREGEN] = BasicLib::totype<int>( GetPlayerhpregen()->GetValue().c_str() );
    }
}


void PlayerEditDialog::Update()
{
    std::map<entityid, Player>::iterator itr = g_players.find( m_lastid );
    if( itr != g_players.end() )
    {
        entityid inv = GetPlayerinventoryslot()->GetValue();
        if( itr->second.m_inventory[inv] != 0 )
        {
            std::map<entityid, Item>::iterator item = g_items.find( itr->second.m_inventory[inv] );
            if( item != g_items.end() )
                GetPlayercurrentitemname()->SetValue( item->second.m_name.c_str() );
            else
                GetPlayercurrentitemname()->SetValue( "<INVALID ITEM>" );
        }
        else
            GetPlayercurrentitemname()->SetValue( "<EMPTY>" );


        if( itr->second.m_weapon != -1 && itr->second.m_inventory[itr->second.m_weapon] != 0 )
        {
            std::map<entityid, Item>::iterator item = g_items.find( itr->second.m_inventory[itr->second.m_weapon] );
            if( item != g_items.end() )
                GetPlayerweapontext()->SetValue( item->second.m_name.c_str() );
            else
                GetPlayerweapontext()->SetValue( "<INVALID ITEM>" );
        }
        else
            GetPlayerweapontext()->SetValue( "<NONE>" );

        if( itr->second.m_armor != -1 && itr->second.m_inventory[itr->second.m_armor] != 0 )
        {
            std::map<entityid, Item>::iterator item = g_items.find( itr->second.m_inventory[itr->second.m_armor] );
            if( item != g_items.end() )
                GetPlayerarmortext()->SetValue( item->second.m_name.c_str() );
            else
                GetPlayerarmortext()->SetValue( "<INVALID ITEM>" );
        }
        else
            GetPlayerarmortext()->SetValue( "<NONE>" );


        itr->second.RecalculateStats();
        GetPlayerstrengthf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[STRENGTH] + itr->second.m_attributes[STRENGTH]).c_str() );
        GetPlayerhealthf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[HEALTH] + itr->second.m_attributes[HEALTH] ).c_str() );
        GetPlayeragilityf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[AGILITY] + itr->second.m_attributes[AGILITY] ).c_str() );
        GetPlayermaxhpf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[MAXHITPOINTS] + itr->second.m_attributes[MAXHITPOINTS] ).c_str() );
        GetPlayeraccuracyf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[ACCURACY] + itr->second.m_attributes[ACCURACY] ).c_str() );
        GetPlayerdodgingf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[DODGING] + itr->second.m_attributes[DODGING] ).c_str() );
        GetPlayerstrikedamagef()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[STRIKEDAMAGE] + itr->second.m_attributes[STRIKEDAMAGE] ).c_str() );
        GetPlayerdamageabsorbf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[DAMAGEABSORB] + itr->second.m_attributes[DAMAGEABSORB] ).c_str() );
        GetPlayerhpregenf()->SetValue( BasicLib::tostring( itr->second.m_baseattributes[HPREGEN] + itr->second.m_attributes[HPREGEN] ).c_str() );
    }
}


//----------------------------------------------------------------------------
// ItemEditDialog
//----------------------------------------------------------------------------

// WDR: event table for ItemEditDialog

BEGIN_EVENT_TABLE(ItemEditDialog,wxDialog)
    EVT_SPINCTRL( ID_ITEMID, ItemEditDialog::OnChangeID )
    EVT_BUTTON( ID_ITEMSAVE, ItemEditDialog::OnSave )
    EVT_BUTTON( ID_ITEMDELETE, ItemEditDialog::OnDelete )
    EVT_BUTTON( ID_ITEMNEW, ItemEditDialog::OnNew )
END_EVENT_TABLE()


ItemEditDialog::ItemEditDialog( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxDialog( parent, id, title, position, size, style )
{
    // WDR: dialog function ItemEdit for ItemEditDialog
    ItemEdit( this, TRUE );

    m_lastid = 0;
    if( g_items.size() != 0 )
        m_lastid = g_items.begin()->first;
    LoadItem( m_lastid );
}

ItemEditDialog::~ItemEditDialog()
{
    SaveItem();
}

// WDR: handler implementations for ItemEditDialog

void ItemEditDialog::OnNew( wxCommandEvent &event )
{
    entityid id = FindOpenID( g_items );
    g_items[id].m_id = id;
    LoadItem( id );
}

void ItemEditDialog::OnDelete( wxCommandEvent &event )
{
    if( m_lastid == 0 )
        return;

    wxMessageDialog dialog( this, wxT("Are you sure you want to delete this Item?"),
        wxT("Delete?"), wxYES_NO | wxICON_EXCLAMATION | wxNO_DEFAULT );

    if( dialog.ShowModal() == wxID_YES )
    {
        g_items.erase( g_items.find( m_lastid ) );
        LoadItem( m_lastid + 1 );
    }
}

void ItemEditDialog::OnSave( wxCommandEvent &event )
{
    SaveItem();
}


void ItemEditDialog::OnChangeID( wxCommandEvent &event )
{
    if( g_items.size() == 0 )
        return;

    wxSpinCtrl* idbox = GetItemid();
    entityid id = idbox->GetValue();
    idbox->SetValue( m_lastid );        // reset to previous value for now.

    std::map<entityid, Item>::iterator itr = g_items.find( id );
    if( itr == g_items.end() )
    {
        if( id < g_items.begin()->first )
            id = g_items.rbegin()->first;
        else if( id > g_items.rbegin()->first )
            id = g_items.begin()->first;
        else if( id < m_lastid )
        {
            itr = g_items.lower_bound( id );
            --itr;
            if( itr == g_items.end() )
                return;
            id = itr->first;
        }
        else
        {
            itr = g_items.upper_bound( id );
            if( itr == g_items.end() )
                return;
            id = itr->first;
        }
    }

    // at this point, id should point to the item you want
    SaveItem();
    LoadItem( id );
}


void ItemEditDialog::LoadItem( entityid p_id )
{
    std::map<entityid, Item>::iterator itr = g_items.find( p_id );
    if( itr != g_items.end() )
    {
        GetItemid()->SetValue( itr->first );
        m_lastid = p_id;
        
        GetItemname()->SetValue( itr->second.m_name.c_str() );
        GetItemtype()->SetValue( GetItemTypeString( itr->second.m_type ).c_str() );
        GetItemmin()->SetValue( BasicLib::tostring( itr->second.m_min ).c_str() );
        GetItemmax()->SetValue( BasicLib::tostring( itr->second.m_max ).c_str() );
        GetItemspeed()->SetValue( BasicLib::tostring( itr->second.m_speed ).c_str() );
        GetItemprice()->SetValue( BasicLib::tostring( itr->second.m_price ).c_str() );

        GetItemstrength()->SetValue( BasicLib::tostring( itr->second.m_attributes[STRENGTH] ).c_str() );
        GetItemhealth()->SetValue( BasicLib::tostring( itr->second.m_attributes[HEALTH] ).c_str() );
        GetItemagility()->SetValue( BasicLib::tostring( itr->second.m_attributes[AGILITY] ).c_str() );
        GetItemmaxhp()->SetValue( BasicLib::tostring( itr->second.m_attributes[MAXHITPOINTS] ).c_str() );
        GetItemaccuracy()->SetValue( BasicLib::tostring( itr->second.m_attributes[ACCURACY] ).c_str() );
        GetItemdodging()->SetValue( BasicLib::tostring( itr->second.m_attributes[DODGING] ).c_str() );
        GetItemstrikedamage()->SetValue( BasicLib::tostring( itr->second.m_attributes[STRIKEDAMAGE] ).c_str() );
        GetItemdamageabsorb()->SetValue( BasicLib::tostring( itr->second.m_attributes[DAMAGEABSORB] ).c_str() );
        GetItemhpregen()->SetValue( BasicLib::tostring( itr->second.m_attributes[HPREGEN] ).c_str() );
    }
}

void ItemEditDialog::SaveItem()
{
    if( m_lastid == 0 )
        return;

    std::map<entityid, Item>::iterator itr = g_items.find( m_lastid );
    if( itr != g_items.end() )
    {
        itr->second.m_name = GetItemname()->GetValue();
        itr->second.m_type = GetItemType( GetItemtype()->GetValue().c_str() );
        itr->second.m_min = BasicLib::totype<int>( GetItemmin()->GetValue().c_str() );
        itr->second.m_max = BasicLib::totype<int>( GetItemmax()->GetValue().c_str() );
        itr->second.m_speed = BasicLib::totype<int>( GetItemspeed()->GetValue().c_str() );
        itr->second.m_price = BasicLib::totype<int>( GetItemprice()->GetValue().c_str() );

        itr->second.m_attributes[STRENGTH] = BasicLib::totype<int>( GetItemstrength()->GetValue().c_str() );
        itr->second.m_attributes[HEALTH] = BasicLib::totype<int>( GetItemhealth()->GetValue().c_str() );
        itr->second.m_attributes[AGILITY] = BasicLib::totype<int>( GetItemagility()->GetValue().c_str() );
        itr->second.m_attributes[MAXHITPOINTS] = BasicLib::totype<int>( GetItemmaxhp()->GetValue().c_str() );
        itr->second.m_attributes[ACCURACY] = BasicLib::totype<int>( GetItemaccuracy()->GetValue().c_str() );
        itr->second.m_attributes[DODGING] = BasicLib::totype<int>( GetItemdodging()->GetValue().c_str() );
        itr->second.m_attributes[STRIKEDAMAGE] = BasicLib::totype<int>( GetItemstrikedamage()->GetValue().c_str() );
        itr->second.m_attributes[DAMAGEABSORB] = BasicLib::totype<int>( GetItemdamageabsorb()->GetValue().c_str() );
        itr->second.m_attributes[HPREGEN] = BasicLib::totype<int>( GetItemhpregen()->GetValue().c_str() );
    }

}


//------------------------------------------------------------------------------
// MyFrame
//------------------------------------------------------------------------------

// WDR: event table for MyFrame

BEGIN_EVENT_TABLE(MyFrame,wxFrame)
    EVT_MENU(ID_LOAD, MyFrame::Load)
    EVT_MENU(ID_SAVE, MyFrame::Save)
    EVT_MENU(ID_ABOUT, MyFrame::OnAbout)
    EVT_MENU(ID_QUIT, MyFrame::OnQuit)
    EVT_MENU(ID_ITEMEDITOR, MyFrame::ItemEdit)
    EVT_CLOSE(MyFrame::OnCloseWindow)
    EVT_MENU( ID_PLAYEREDITOR, MyFrame::PlayerEdit )
END_EVENT_TABLE()

MyFrame::MyFrame( wxWindow *parent, wxWindowID id, const wxString &title,
    const wxPoint &position, const wxSize& size, long style ) :
    wxFrame( parent, id, title, position, size, style )
{
    CreateMyMenuBar();
    
    CreateMyToolBar();
    
    CreateStatusBar(1);
    SetStatusText( wxT("Welcome!") );
    
     // insert main window here
}

void MyFrame::Load( wxCommandEvent &event )
{
    LoadItems();
    LoadPlayers();
    SetStatusText( wxT("Databases Loaded!") );
}

void MyFrame::Save( wxCommandEvent &event )
{
    SaveItems();
    SavePlayers();
}


void MyFrame::ItemEdit( wxCommandEvent &event )
{
    ItemEditDialog dialog( this, -1, "Item Editor" );
    dialog.ShowModal();
}


void MyFrame::CreateMyMenuBar()
{
#ifdef __WXMAC__
    wxApp::s_macAboutMenuItemId = ID_ABOUT;
#endif

    SetMenuBar( MyMenuBarFunc() );
}

void MyFrame::CreateMyToolBar()
{
    wxToolBar *tb = CreateToolBar( wxTB_HORIZONTAL|wxNO_BORDER /* |wxTB_FLAT */ );
    
    MyToolBarFunc( tb );
}

// WDR: handler implementations for MyFrame

void MyFrame::PlayerEdit( wxCommandEvent &event )
{
    PlayerEditDialog dialog( this, -1, "Player Editor" );
    dialog.ShowModal();
}

void MyFrame::OnAbout( wxCommandEvent &event )
{
    wxMessageDialog dialog( this, wxT("SimpleEdit 1.0\nA datafile editor for SimpleMUD\n(C)2003 Ron Penton"),
        wxT("About SimpleEdit"), wxOK|wxICON_INFORMATION );
    dialog.ShowModal();
}

void MyFrame::OnQuit( wxCommandEvent &event )
{
     Close( TRUE );
}

void MyFrame::OnCloseWindow( wxCloseEvent &event )
{
    // if ! saved changes -> return
    
    Destroy();
}

//------------------------------------------------------------------------------
// MyApp
//------------------------------------------------------------------------------

IMPLEMENT_APP(MyApp)

MyApp::MyApp()
{
}

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( NULL, -1, wxT("SimpleEdit"), wxPoint(100,100), wxSize(500,340) );
    frame->Show( TRUE );
    
    return TRUE;
}

int MyApp::OnExit()
{
    return 0;
}

