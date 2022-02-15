#pragma once
#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <wx/config.h>
#include <wx/confbase.h>
#include <wx/fileconf.h>
#include <wx/file.h>
#include <wx/dir.h>
#include <wx/filedlg.h>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	// Browse panel
	wxPanel* browsePanel = nullptr;
	wxStaticText* browseTitle = nullptr;
	wxTextCtrl* xPlaneLocationBar = nullptr;
	wxButton* browseButton = nullptr;

	// Airframe list
	wxPanel* airframePanel = nullptr;
	wxStaticText* airframeTitle = nullptr;
	wxListBox* airframeList = nullptr;
	wxButton* airframeListRefresh = nullptr;
	wxButton* airframeOpen = nullptr;

	// Import/Export
	wxPanel* importExportPanel = nullptr;

	// Export
	wxPanel* exportPanel = nullptr;
	wxStaticText* exportTitle = nullptr;
	wxTextCtrl* exportBox = nullptr;
	wxButton* exportButton = nullptr;

	// Import
	wxPanel* importPanel = nullptr;
	wxStaticText* importTitle = nullptr;
	wxButton* importButton = nullptr;

	// Configuration
	wxPathList xPlanePath;

	wxString configDir = wxStandardPaths::Get().GetUserConfigDir() + wxFileName::GetPathSeparator() + "Vanguard Airframe Manager";
	wxString configPath = configDir + wxFileName::GetPathSeparator() + "VAMConfig.ini";

	void firstBoot();
	void pathNotSet();
	void pathNotFound();
	void airframeNotSet();

	wxArrayString splitString(wxString s, wxChar del);
	wxArrayString splitString(wxString s, wxString del);

	void browseForXPlane(wxCommandEvent& event);
	void exportToZIP(wxCommandEvent& event);
	wxString getAirframeID(wxString airframeToCheck, wxString airframeLine);
	wxString getAirframeData(wxString airframeID, wxString airframeLine);

	void readConfig();
	void writeConfig(wxString writeKey, wxString writeValue);

private:
	wxDECLARE_EVENT_TABLE();
};