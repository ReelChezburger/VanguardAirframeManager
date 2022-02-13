#include "cMain.h"
#include <wx/file.h>

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Vanguard Airframe Manager")
{
	this->SetBackgroundColour(wxColor(169, 169, 169));

	// browse panel defenitions
	browsePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 100));
	browsePanel->SetBackgroundColour(wxColor(255, 255, 255));

	browseTitle = new wxStaticText(browsePanel, wxID_ANY, "X-Plane Location", wxDefaultPosition, wxSize(580,20), wxALIGN_CENTRE_HORIZONTAL);
	xPlaneLocationBar = new wxTextCtrl(browsePanel, wxID_ANY, "Set X-Plane Location Here", wxDefaultPosition, wxSize(400, 50));
	browseButton = new wxButton(browsePanel, wxID_ANY, "Browse", wxDefaultPosition, wxSize(100, 50));

	// airframe panel defenitions
	airframePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(295, 300));
	airframePanel->SetBackgroundColour(wxColor(255, 255, 255));

	airframeTitle = new wxStaticText(airframePanel, wxID_ANY, "Zipped Airframes", wxDefaultPosition, wxSize(275, 20), wxALIGN_CENTER_HORIZONTAL);
	airframeList = new wxListBox(airframePanel, wxID_ANY, wxDefaultPosition, wxSize(275, 190));
	airframeListRefresh = new wxButton(airframePanel, wxID_ANY, "Refresh", wxDefaultPosition, wxSize(132, 50));
	airframeOpen = new wxButton(airframePanel, wxID_ANY, "Open", wxDefaultPosition, wxSize(132, 50));

	// import/export panel defenitions
	importExportPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(295, 300));
	importExportPanel->SetBackgroundColour(wxColor(255, 255, 255));

	exportPanel = new wxPanel(importExportPanel, wxID_ANY, wxDefaultPosition, wxSize(275, 180));
	exportPanel->SetBackgroundColour(wxColor(169, 169, 169));
	exportBox = new wxTextCtrl(exportPanel, wxID_ANY, "Airframe to ZIP", wxDefaultPosition, wxSize(255, 75));
	exportButton = new wxButton(exportPanel, wxID_ANY, "Export to ZIP", wxDefaultPosition, wxSize(255, 75));

	importPanel = new wxPanel(importExportPanel, wxID_ANY, wxDefaultPosition, wxSize(275, 90));
	importPanel->SetBackgroundColour(wxColor(169, 169, 169));
	importButton = new wxButton(importPanel, wxID_ANY, "Import from ZIP", wxDefaultPosition, wxSize(255, 70));

	// browse panel sizer
	wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
	verticalSizer->Add(browsePanel, 0, wxEXPAND | wxALL, 10);

	wxBoxSizer* browseVerticalSizer = new wxBoxSizer(wxVERTICAL);
	browseVerticalSizer->Add(browseTitle, 2, wxALIGN_CENTER | wxALL, 10);

	wxBoxSizer* browseHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	browseHorizontalSizer->Add(xPlaneLocationBar, 1, wxEXPAND | wxRIGHT, 10);
	browseHorizontalSizer->Add(browseButton, 0, wxEXPAND);

	browseVerticalSizer->Add(browseHorizontalSizer, 5, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
	browsePanel->SetSizerAndFit(browseVerticalSizer);

	// bottom panels sizer
	wxBoxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	horizontalSizer->Add(airframePanel, 1, wxEXPAND | wxRIGHT, 10);
	horizontalSizer->Add(importExportPanel, 1, wxEXPAND | wxALL, 0);

	//airframe panel sizer
	wxBoxSizer* airframeVerticalSizer = new wxBoxSizer(wxVERTICAL);
	airframeVerticalSizer->Add(airframeTitle, 0, wxEXPAND | wxALL, 10);
	airframeVerticalSizer->Add(airframeList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

	wxBoxSizer* airframeHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	airframeHorizontalSizer->Add(airframeListRefresh, 1, wxEXPAND | wxRIGHT, 10);
	airframeHorizontalSizer->Add(airframeOpen, 1, wxEXPAND | wxALL, 0);

	airframeVerticalSizer->Add(airframeHorizontalSizer, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
	airframePanel->SetSizerAndFit(airframeVerticalSizer);

	// import/export panel sizer
	wxBoxSizer* importExportSizer = new wxBoxSizer(wxVERTICAL);
	importExportSizer->Add(exportPanel, 2, wxEXPAND | wxALL, 10);
	importExportSizer->Add(importPanel, 1, wxEXPAND | wxRIGHT | wxLEFT | wxBOTTOM, 10);

	wxBoxSizer* exportSizer = new wxBoxSizer(wxVERTICAL);
	exportSizer->Add(exportBox, 1, wxEXPAND | wxALL, 10);
	exportSizer->Add(exportButton, 1, wxEXPAND | wxRIGHT | wxLEFT | wxBOTTOM, 10);

	wxBoxSizer* importSizer = new wxBoxSizer(wxVERTICAL);
	importSizer->Add(importButton, 1, wxEXPAND | wxALL, 10);

	exportPanel->SetSizerAndFit(exportSizer);
	importPanel->SetSizerAndFit(importSizer);

	// configures main sizers relative to each-other
	importExportPanel->SetSizerAndFit(importExportSizer);

	verticalSizer->Add(horizontalSizer, 3, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

	this->SetSizerAndFit(verticalSizer);

	//checks config file
	if (!wxFile::Exists("VAM.cfg")) {
		//wxFile::Create("VAM.cfg");
	}
}

cMain::~cMain()
{
}