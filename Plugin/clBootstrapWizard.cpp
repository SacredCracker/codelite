#include "clBootstrapWizard.h"
#include "ColoursAndFontsManager.h"
#include "globals.h"
#include "CompilersDetectorManager.h"
#include "build_settings_config.h"
#include <wx/wupdlock.h>
#include <wx/dcmemory.h>
#include "plugindata.h"
#include <algorithm>
#include "macros.h"

class clBootstrapWizardPluginData : public wxClientData
{
public:
    bool checked;

public:
    clBootstrapWizardPluginData()
        : checked(true)
    {
    }
    virtual ~clBootstrapWizardPluginData() {}
};

const wxString sampleText = "class Demo {\n"
                            "private:\n"
                            "    std::string m_str;\n"
                            "    int m_integer;\n"
                            "    \n"
                            "public:\n"
                            "    /**\n"
                            "     * Creates a new demo.\n"
                            "     * @param o The object\n"
                            "     */\n"
                            "    Demo(const Demo &other) {\n"
                            "        m_str = other.m_str;\n"
                            "        m_integer = other.m_integer;\n"
                            "    }\n"
                            "}";

clBootstrapWizard::clBootstrapWizard(wxWindow* parent)
    : clBoostrapWizardBase(parent)
{
    wxArrayString themes = ColoursAndFontsManager::Get().GetAvailableThemesForLexer("c++");
    m_choiceTheme->Append(themes);
    m_choiceTheme->SetSelection(m_choiceTheme->FindString("Monokai_2"));
    m_stc24->SetText(sampleText);
    LexerConf::Ptr_t lexer = ColoursAndFontsManager::Get().GetLexer("c++", "Monokai_2");
    if(lexer) {
        lexer->Apply(m_stc24, true);
    }
    m_stc24->SetKeyWords(1, "Demo std string");
    m_stc24->SetKeyWords(3, "other");

    ::clRecalculateSTCHScrollBar(m_stc24);
    m_stc24->SetEditable(false);

    clConfig conf("plugins.conf");
    PluginInfoArray plugins;
    conf.ReadItem(&plugins);

    const PluginInfo::PluginMap_t& allPlugins = plugins.GetPlugins();

    wxArrayString pluginsArray;
    std::for_each(allPlugins.begin(), allPlugins.end(), [&](const std::pair<wxString, PluginInfo>& item) {
        wxVector<wxVariant> cols;
        cols.push_back(true);
        cols.push_back(item.first);
        wxString desc = item.second.GetDescription();
        desc.Replace("\n", " ");
        desc.Replace("\r", "");
        cols.push_back(desc);
        m_dvListCtrlPlugins->AppendItem(cols, (wxUIntPtr) new clBootstrapWizardPluginData());
    });
}

clBootstrapWizard::~clBootstrapWizard() {}

void clBootstrapWizard::OnThemeSelected(wxCommandEvent& event)
{
    m_stc24->SetEditable(true);
    wxString selection = m_choiceTheme->GetStringSelection();
    LexerConf::Ptr_t lexer = ColoursAndFontsManager::Get().GetLexer("c++", selection);
    if(lexer) {
        lexer->Apply(m_stc24, true);
    }
    m_stc24->SetKeyWords(1, "Demo std string");
    m_stc24->SetKeyWords(3, "other");
    ::clRecalculateSTCHScrollBar(m_stc24);
    m_stc24->SetEditable(false);
}
void clBootstrapWizard::OnScanForCompilers(wxCommandEvent& event)
{
    wxBusyCursor bc;
    m_compilers.clear();
    wxWindowUpdateLocker locker(m_wizardPageCompilers);

    CompilersDetectorManager detector;
    if(detector.Locate()) {
        m_cmdLnkBtnScanForCompilers->Hide();
        m_cmdLnkBtnDownloadCompiler->Hide();
        m_dvListCtrlCompilers->Show();

        m_compilers = detector.GetCompilersFound();
        for(size_t i = 0; i < m_compilers.size(); ++i) {
            wxVector<wxVariant> cols;
            cols.push_back(m_compilers.at(i)->GetName());
            cols.push_back(m_compilers.at(i)->GetInstallationPath());
            m_dvListCtrlCompilers->AppendItem(cols);
        }

        if(!detector.FoundMinGWCompiler()) {
            CompilersDetectorManager::MSWSuggestToDownloadMinGW(true);
        }

    } else {
        // nothing found on this machine, offer to download
        CompilersDetectorManager::MSWSuggestToDownloadMinGW(true);
    }
    m_wizardPageCompilers->GetSizer()->Layout();
}

wxBitmap clBootstrapWizard::GenerateBitmap(size_t labelIndex)
{
    wxArrayString labels;
    labels.Add("Welcome");
    labels.Add("Plugins");
    labels.Add("Compilers");
    labels.Add("Colours");
    labels.Add("Whitespace");

    wxBitmap bmp(100, 400);
    wxMemoryDC memDC(bmp);
    memDC.SetPen(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    memDC.SetBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE));
    memDC.DrawRectangle(wxRect(bmp.GetSize()));
    wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    wxFont boldFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    boldFont.SetWeight(wxFONTWEIGHT_BOLD);

    wxBitmap arrowRight = wxXmlResource::Get()->LoadBitmap("next-16");
    for(size_t i = 0; i < labels.size(); ++i) {
        wxSize textSize = memDC.GetTextExtent("Tp");
        int rectHeight = textSize.y + 20; // 10 pixels margin x 2
        wxRect rect(0, i * rectHeight, bmp.GetWidth(), rectHeight);

        // Draw the text (align to the right)
        wxCoord textX, textY, bmpX, bmpY;
        memDC.SetFont(font);
        memDC.SetTextForeground(i == labelIndex ? wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT) :
                                                  wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
        memDC.SetFont(i == labelIndex ? boldFont : font);
        textSize = memDC.GetTextExtent(labels.Item(i));
        textX = /*bmp.GetWidth() - textSize.GetWidth() - 16*/ 16;
        textY = ((rect.GetHeight() - textSize.GetHeight()) / 2) + rect.GetY();
        memDC.DrawText(labels.Item(i), textX, textY);

        if(i == labelIndex) {
            bmpX = 0;
            bmpY = ((rect.GetHeight() - arrowRight.GetHeight()) / 2) + rect.GetY();
            memDC.DrawBitmap(arrowRight, bmpX, bmpY);
        }
    }
    memDC.SelectObject(wxNullBitmap);
    return bmp;
}

clBootstrapData clBootstrapWizard::GetData()
{
    clBootstrapData data;
    data.compilers = m_compilers;
    data.selectedTheme = m_choiceTheme->GetStringSelection();
    data.useTabs = (m_radioBoxSpacesVsTabs->GetSelection() == 1);
    data.whitespaceVisibility = m_radioBoxWhitespaceVisibility->GetSelection();
    return data;
}
void clBootstrapWizard::OnInstallCompiler(wxCommandEvent& event)
{
    CompilersDetectorManager::MSWSuggestToDownloadMinGW(false);
}

void clBootstrapWizard::OnInstallCompilerUI(wxUpdateUIEvent& event)
{
#ifdef __WXMSW__
    event.Enable(true);
#else
    event.Enable(false);
#endif
}
void clBootstrapWizard::OnCheckAllPlugins(wxCommandEvent& event)
{
    wxVariant value(true);
    for(int i = 0; i < m_dvListCtrlPlugins->GetItemCount(); ++i) {
        m_dvListCtrlPlugins->SetValue(value, i, 0);
    }
}

void clBootstrapWizard::OnCheckAllPluginsUI(wxUpdateUIEvent& event)
{
    wxArrayString enabledPlugins = GetSelectedPlugins();
    event.Enable((int)enabledPlugins.size() != m_dvListCtrlPlugins->GetItemCount());
}

void clBootstrapWizard::OnToggleCxxPlugins(wxCommandEvent& event) 
{
    static bool enablePlugins = false;
    wxArrayString cxxPlugins;
    cxxPlugins.Add("CMakePlugin");
    cxxPlugins.Add("CScope");
    cxxPlugins.Add("CallGraph");
    cxxPlugins.Add("ContinuousBuild");
    cxxPlugins.Add("CppChecker");
    cxxPlugins.Add("LLDBDebuggerPlugin");
    cxxPlugins.Add("QMakePlugin");
    cxxPlugins.Add("UnitTestPP");
    cxxPlugins.Add("Wizards");
    cxxPlugins.Add("wxFormBuilder");
    cxxPlugins.Add("wxcrafter");
    
    for(int i = 0; i < m_dvListCtrlPlugins->GetItemCount(); ++i) {
        wxVariant newState(enablePlugins);
        wxVariant pluginName;
        m_dvListCtrlPlugins->GetValue(pluginName, i, 1);
        if(cxxPlugins.Index(pluginName.GetString()) != wxNOT_FOUND) {
            m_dvListCtrlPlugins->SetValue(newState, i, 0);
        }
    }
    enablePlugins = !enablePlugins;
}

void clBootstrapWizard::OnUnCheckAllPlugins(wxCommandEvent& event)
{
    wxVariant value(false);
    for(int i = 0; i < m_dvListCtrlPlugins->GetItemCount(); ++i) {
        m_dvListCtrlPlugins->SetValue(value, i, 0);
    }
}

void clBootstrapWizard::OnUnCheckAllPluginsUI(wxUpdateUIEvent& event)
{
    wxArrayString enabledPlugins = GetSelectedPlugins();
    event.Enable(!enabledPlugins.IsEmpty());
}

wxArrayString clBootstrapWizard::GetSelectedPlugins()
{
    wxArrayString enabledPlugins;
    for(int i = 0; i < m_dvListCtrlPlugins->GetItemCount(); ++i) {
        wxVariant value;
        m_dvListCtrlPlugins->GetValue(value, i, 0);
        if(value.GetBool()) {
            wxVariant pluginName;
            m_dvListCtrlPlugins->GetValue(pluginName, i, 1);
            enabledPlugins.Add(pluginName.GetString());
        }
    }
    return enabledPlugins;
}

wxArrayString clBootstrapWizard::GetUnSelectedPlugins()
{
    wxArrayString enabledPlugins;
    for(int i = 0; i < m_dvListCtrlPlugins->GetItemCount(); ++i) {
        wxVariant value;
        m_dvListCtrlPlugins->GetValue(value, i, 0);
        if(!value.GetBool()) {
            wxVariant pluginName;
            m_dvListCtrlPlugins->GetValue(pluginName, i, 1);
            enabledPlugins.Add(pluginName.GetString());
        }
    }
    return enabledPlugins;
}

bool clBootstrapWizard::IsRestartRequired()
{
    return GetSelectedPlugins().GetCount() != (size_t)m_dvListCtrlPlugins->GetItemCount();
}
void clBootstrapWizard::OnFinish(wxWizardEvent& event)
{
    event.Skip();
    if(IsRestartRequired()) {
        // user changed plugins
        clConfig conf("plugins.conf");
        PluginInfoArray plugins;
        conf.ReadItem(&plugins);
        
        plugins.DisablePugins(GetUnSelectedPlugins());
        conf.WriteItem(&plugins);
    }
}
