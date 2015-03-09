//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: clBoostrapWizardBase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef CLBOOSTRAPWIZARDBASE_BASE_CLASSES_H
#define CLBOOSTRAPWIZARDBASE_BASE_CLASSES_H

#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/wizard.h>
#include <vector>
#include <wx/artprov.h>
#include <wx/panel.h>
#include "clBoostrapWizardPage.h"
#include <wx/sizer.h>
#include <wx/bannerwindow.h>
#include <wx/dataview.h>
#include <wx/button.h>
#include <wx/commandlinkbutton.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/stc/stc.h>
#include <wx/radiobox.h>

class clBoostrapWizardBase : public wxWizard
{
protected:
    std::vector<wxWizardPageSimple*> m_pages;

    clBoostrapWizardPageWelcome* m_wizardPageWelcome;
    wxBannerWindow* m_banner81;
    clBoostrapWizardPagePlugins* m_wizardPagePlugins;
    wxBannerWindow* m_banner811;
    wxDataViewListCtrl* m_dvListCtrlPlugins;
    wxButton* m_button99;
    wxButton* m_button101;
    wxButton* m_button103;
    clBoostrapWizardPageCompilers* m_wizardPageCompilers;
    wxBannerWindow* m_banner69;
    wxCommandLinkButton* m_cmdLnkBtnScanForCompilers;
    wxCommandLinkButton* m_cmdLnkBtnDownloadCompiler;
    wxDataViewListCtrl* m_dvListCtrlCompilers;
    clBoostrapWizardPageColours* m_wizardPageColoursAndFonts;
    wxBannerWindow* m_banner71;
    wxChoice* m_choiceTheme;
    wxStyledTextCtrl* m_stc24;
    clBoostrapWizardPageWhitespace* m_wizardPageWhitespace;
    wxBannerWindow* m_banner73;
    wxRadioBox* m_radioBoxSpacesVsTabs;
    wxRadioBox* m_radioBoxWhitespaceVisibility;

protected:
    virtual void OnFinish(wxWizardEvent& event) { event.Skip(); }
    virtual void OnCheckAllPlugins(wxCommandEvent& event) { event.Skip(); }
    virtual void OnCheckAllPluginsUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnUnCheckAllPlugins(wxCommandEvent& event) { event.Skip(); }
    virtual void OnUnCheckAllPluginsUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnToggleCxxPlugins(wxCommandEvent& event) { event.Skip(); }
    virtual void OnScanForCompilers(wxCommandEvent& event) { event.Skip(); }
    virtual void OnInstallCompilerUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnInstallCompiler(wxCommandEvent& event) { event.Skip(); }
    virtual void OnThemeSelected(wxCommandEvent& event) { event.Skip(); }

public:
    wxBannerWindow* GetBanner81() { return m_banner81; }
    clBoostrapWizardPageWelcome* GetWizardPageWelcome() { return m_wizardPageWelcome; }
    wxBannerWindow* GetBanner811() { return m_banner811; }
    wxDataViewListCtrl* GetDvListCtrlPlugins() { return m_dvListCtrlPlugins; }
    wxButton* GetButton99() { return m_button99; }
    wxButton* GetButton101() { return m_button101; }
    wxButton* GetButton103() { return m_button103; }
    clBoostrapWizardPagePlugins* GetWizardPagePlugins() { return m_wizardPagePlugins; }
    wxBannerWindow* GetBanner69() { return m_banner69; }
    wxCommandLinkButton* GetCmdLnkBtnScanForCompilers() { return m_cmdLnkBtnScanForCompilers; }
    wxCommandLinkButton* GetCmdLnkBtnDownloadCompiler() { return m_cmdLnkBtnDownloadCompiler; }
    wxDataViewListCtrl* GetDvListCtrlCompilers() { return m_dvListCtrlCompilers; }
    clBoostrapWizardPageCompilers* GetWizardPageCompilers() { return m_wizardPageCompilers; }
    wxBannerWindow* GetBanner71() { return m_banner71; }
    wxChoice* GetChoiceTheme() { return m_choiceTheme; }
    wxStyledTextCtrl* GetStc24() { return m_stc24; }
    clBoostrapWizardPageColours* GetWizardPageColoursAndFonts() { return m_wizardPageColoursAndFonts; }
    wxBannerWindow* GetBanner73() { return m_banner73; }
    wxRadioBox* GetRadioBoxSpacesVsTabs() { return m_radioBoxSpacesVsTabs; }
    wxRadioBox* GetRadioBoxWhitespaceVisibility() { return m_radioBoxWhitespaceVisibility; }
    clBoostrapWizardPageWhitespace* GetWizardPageWhitespace() { return m_wizardPageWhitespace; }
    clBoostrapWizardBase(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Welcome!"), const wxBitmap& bmp = wxNullBitmap, const wxPoint& pos = wxDefaultPosition, long style = wxDEFAULT_DIALOG_STYLE);
    wxWizardPageSimple* GetFirstPage() const { if(!m_pages.empty()) return m_pages.at(0); return NULL; }
    virtual ~clBoostrapWizardBase();
};

#endif
