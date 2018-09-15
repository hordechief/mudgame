/////////////////////////////////////////////////////////////////////////////
// Name:        SimpleEdit.h
// Author:      XX
// Created:     XX/XX/XX
// Copyright:   
/////////////////////////////////////////////////////////////////////////////

#ifndef __SimpleEdit_H__
#define __SimpleEdit_H__

#if defined(__GNUG__) && !defined(__APPLE__)
    #pragma interface "SimpleEdit.h"
#endif

// Include wxWindows' headers

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "SimpleEdit_wdr.h"
#include "Databases.h"

// WDR: class declarations

//----------------------------------------------------------------------------
// PlayerEditDialog
//----------------------------------------------------------------------------

class PlayerEditDialog: public wxDialog
{
public:
    // constructors and destructors
    PlayerEditDialog( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );
    virtual ~PlayerEditDialog();

    void LoadPlayer( entityid p_id );
    void SavePlayer();
    void Update();
    
    // WDR: method declarations for PlayerEditDialog
    wxTextCtrl* GetPlayerhpregenf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERHPREGENF ); }
    wxTextCtrl* GetPlayerdamageabsorbf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERDAMAGEABSORBF ); }
    wxTextCtrl* GetPlayerstrikedamagef()  { return (wxTextCtrl*) FindWindow( ID_PLAYERSTRIKEDAMAGEF ); }
    wxTextCtrl* GetPlayerdodgingf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERDODGINGF ); }
    wxTextCtrl* GetPlayeraccuracyf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERACCURACYF ); }
    wxTextCtrl* GetPlayermaxhpf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERMAXHPF ); }
    wxTextCtrl* GetPlayeragilityf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERAGILITYF ); }
    wxTextCtrl* GetPlayerhealthf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERHEALTHF ); }
    wxTextCtrl* GetPlayerstrengthf()  { return (wxTextCtrl*) FindWindow( ID_PLAYERSTRENGTHF ); }
    wxTextCtrl* GetPlayerexperience()  { return (wxTextCtrl*) FindWindow( ID_PLAYEREXPERIENCE ); }
    wxTextCtrl* GetPlayerarmortext()  { return (wxTextCtrl*) FindWindow( ID_PLAYERARMORTEXT ); }
    wxTextCtrl* GetPlayerweapontext()  { return (wxTextCtrl*) FindWindow( ID_PLAYERWEAPONTEXT ); }
    wxTextCtrl* GetPlayercurrentitemname()  { return (wxTextCtrl*) FindWindow( ID_PLAYERCURRENTITEMNAME ); }
    wxTextCtrl* GetPlayermoney()  { return (wxTextCtrl*) FindWindow( ID_PLAYERMONEY ); }
    wxSpinCtrl* GetPlayerarmor()  { return (wxSpinCtrl*) FindWindow( ID_PLAYERARMOR ); }
    wxSpinCtrl* GetPlayerweapon()  { return (wxSpinCtrl*) FindWindow( ID_PLAYERWEAPON ); }
    wxTextCtrl* GetPlayercurrentitemid()  { return (wxTextCtrl*) FindWindow( ID_PLAYERCURRENTITEMID ); }
    wxSpinCtrl* GetPlayerinventoryslot()  { return (wxSpinCtrl*) FindWindow( ID_PLAYERINVENTORYSLOT ); }
    wxTextCtrl* GetPlayerhpregen()  { return (wxTextCtrl*) FindWindow( ID_PLAYERHPREGEN ); }
    wxTextCtrl* GetPlayerdamageabsorb()  { return (wxTextCtrl*) FindWindow( ID_PLAYERDAMAGEABSORB ); }
    wxTextCtrl* GetPlayerstrikedamage()  { return (wxTextCtrl*) FindWindow( ID_PLAYERSTRIKEDAMAGE ); }
    wxTextCtrl* GetPlayerdodging()  { return (wxTextCtrl*) FindWindow( ID_PLAYERDODGING ); }
    wxTextCtrl* GetPlayeraccuracy()  { return (wxTextCtrl*) FindWindow( ID_PLAYERACCURACY ); }
    wxTextCtrl* GetPlayermaxhp()  { return (wxTextCtrl*) FindWindow( ID_PLAYERMAXHP ); }
    wxTextCtrl* GetPlayeragility()  { return (wxTextCtrl*) FindWindow( ID_PLAYERAGILITY ); }
    wxTextCtrl* GetPlayerhealth()  { return (wxTextCtrl*) FindWindow( ID_PLAYERHEALTH ); }
    wxTextCtrl* GetPlayerstrength()  { return (wxTextCtrl*) FindWindow( ID_PLAYERSTRENGTH ); }
    wxTextCtrl* GetPlayerattacktime()  { return (wxTextCtrl*) FindWindow( ID_PLAYERATTACKTIME ); }
    wxTextCtrl* GetPlayerhp()  { return (wxTextCtrl*) FindWindow( ID_PLAYERHP ); }
    wxTextCtrl* GetPlayerroom()  { return (wxTextCtrl*) FindWindow( ID_PLAYERROOM ); }
    wxTextCtrl* GetPlayerlevel()  { return (wxTextCtrl*) FindWindow( ID_PLAYERLEVEL ); }
    wxTextCtrl* GetPlayerstatpoints()  { return (wxTextCtrl*) FindWindow( ID_PLAYERSTATPOINTS ); }
    wxComboBox* GetPlayerrank()  { return (wxComboBox*) FindWindow( ID_PLAYERRANK ); }
    wxTextCtrl* GetPlayerpass()  { return (wxTextCtrl*) FindWindow( ID_PLAYERPASS ); }
    wxTextCtrl* GetPlayername()  { return (wxTextCtrl*) FindWindow( ID_PLAYERNAME ); }
    wxSpinCtrl* GetPlayerid()  { return (wxSpinCtrl*) FindWindow( ID_PLAYERID ); }
    
private:
    // WDR: member variable declarations for PlayerEditDialog
    entityid m_lastid;

private:
    // WDR: handler declarations for PlayerEditDialog
    void OnTextHPRegen( wxCommandEvent &event );
    void OnTextDamageAbsorb( wxCommandEvent &event );
    void OnTextStrikeDamage( wxCommandEvent &event );
    void OnTextDodging( wxCommandEvent &event );
    void OnTextAccuracy( wxCommandEvent &event );
    void OnTextMaxHP( wxCommandEvent &event );
    void OnTextAgility( wxCommandEvent &event );
    void OnTextHealth( wxCommandEvent &event );
    void OnTextStrength( wxCommandEvent &event );
    void OnTextLevel( wxCommandEvent &event );
    void OnDelete( wxCommandEvent &event );
    void OnNew( wxCommandEvent &event );
    void OnSave( wxCommandEvent &event );
    void OnInventoryText( wxCommandEvent &event );
    void OnArmorChange( wxCommandEvent &event );
    void OnWeaponChange( wxCommandEvent &event );
    void OnSlotChange( wxCommandEvent &event );
    void OnChangeID( wxCommandEvent &event );

private:
    DECLARE_EVENT_TABLE()
};



//----------------------------------------------------------------------------
// ItemEditDialog
//----------------------------------------------------------------------------

class ItemEditDialog: public wxDialog
{
public:
    // constructors and destructors
    ItemEditDialog( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_DIALOG_STYLE );
    virtual ~ItemEditDialog();
    
    // WDR: method declarations for ItemEditDialog
    wxSpinCtrl* GetItemid()  { return (wxSpinCtrl*) FindWindow( ID_ITEMID ); }
    wxTextCtrl* GetItemhpregen()  { return (wxTextCtrl*) FindWindow( ID_ITEMHPREGEN ); }
    wxTextCtrl* GetItemdamageabsorb()  { return (wxTextCtrl*) FindWindow( ID_ITEMDAMAGEABSORB ); }
    wxTextCtrl* GetItemstrikedamage()  { return (wxTextCtrl*) FindWindow( ID_ITEMSTRIKEDAMAGE ); }
    wxTextCtrl* GetItemdodging()  { return (wxTextCtrl*) FindWindow( ID_ITEMDODGING ); }
    wxTextCtrl* GetItemaccuracy()  { return (wxTextCtrl*) FindWindow( ID_ITEMACCURACY ); }
    wxTextCtrl* GetItemmaxhp()  { return (wxTextCtrl*) FindWindow( ID_ITEMMAXHP ); }
    wxTextCtrl* GetItemagility()  { return (wxTextCtrl*) FindWindow( ID_ITEMAGILITY ); }
    wxTextCtrl* GetItemhealth()  { return (wxTextCtrl*) FindWindow( ID_ITEMHEALTH ); }
    wxTextCtrl* GetItemstrength()  { return (wxTextCtrl*) FindWindow( ID_ITEMSTRENGTH ); }
    wxTextCtrl* GetItemprice()  { return (wxTextCtrl*) FindWindow( ID_ITEMPRICE ); }
    wxTextCtrl* GetItemspeed()  { return (wxTextCtrl*) FindWindow( ID_ITEMSPEED ); }
    wxTextCtrl* GetItemmax()  { return (wxTextCtrl*) FindWindow( ID_ITEMMAX ); }
    wxTextCtrl* GetItemmin()  { return (wxTextCtrl*) FindWindow( ID_ITEMMIN ); }
    wxComboBox* GetItemtype()  { return (wxComboBox*) FindWindow( ID_ITEMTYPE ); }
    wxTextCtrl* GetItemname()  { return (wxTextCtrl*) FindWindow( ID_ITEMNAME ); }
    void LoadItem( entityid p_id );
    void SaveItem();
    
private:
    // WDR: member variable declarations for ItemEditDialog
    entityid m_lastid;
    
private:
    // WDR: handler declarations for ItemEditDialog
    void OnNew( wxCommandEvent &event );
    void OnDelete( wxCommandEvent &event );
    void OnSave( wxCommandEvent &event );
    void OnChangeID( wxCommandEvent &event );

private:
    DECLARE_EVENT_TABLE()
};


//----------------------------------------------------------------------------
// MyFrame
//----------------------------------------------------------------------------

class MyFrame: public wxFrame
{
public:
    // constructors and destructors
    MyFrame( wxWindow *parent, wxWindowID id, const wxString &title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE );
    
private:
    // WDR: method declarations for MyFrame
    void CreateMyMenuBar();
    void CreateMyToolBar();
    
private:
    // WDR: member variable declarations for MyFrame
    
private:
    // WDR: handler declarations for MyFrame
    void PlayerEdit( wxCommandEvent &event );
    void Load( wxCommandEvent &event );
    void Save( wxCommandEvent &event );
    void ItemEdit( wxCommandEvent &event );
    void OnAbout( wxCommandEvent &event );
    void OnQuit( wxCommandEvent &event );
    void OnCloseWindow( wxCloseEvent &event );
    
private:
    DECLARE_EVENT_TABLE()
};

//----------------------------------------------------------------------------
// MyApp
//----------------------------------------------------------------------------

class MyApp: public wxApp
{
public:
    MyApp();
    
    virtual bool OnInit();
    virtual int OnExit();
};

#endif
