#pragma once
#include <wx/wx.h>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	// browse panel
	wxPanel* browsePanel = nullptr;
	wxStaticText* browseTitle = nullptr;
	wxTextCtrl* xPlaneLocationBar = nullptr;
	wxButton* browseButton = nullptr;

	// airframe list
	wxPanel* airframePanel = nullptr;
	wxStaticText* airframeTitle = nullptr;
	wxListBox* airframeList = nullptr;
	wxButton* airframeListRefresh = nullptr;
	wxButton* airframeOpen = nullptr;

	// import/export
	wxPanel* importExportPanel = nullptr;

	//export
	wxPanel* exportPanel = nullptr;
	wxStaticText* exportTitle = nullptr;
	wxTextCtrl* exportBox = nullptr;
	wxButton* exportButton = nullptr;

	//import
	wxPanel* importPanel = nullptr;
	wxStaticText* importTitle = nullptr;
	wxButton* importButton = nullptr;
};

