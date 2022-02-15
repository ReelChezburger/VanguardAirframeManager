#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, cMain::browseForXPlane)
	EVT_BUTTON(10002, cMain::exportToZIP)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Vanguard Airframe Manager")
{
	this->SetBackgroundColour(wxColor(169, 169, 169));

	// Browse panel defenitions
	browsePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 100));
	browsePanel->SetBackgroundColour(wxColor(255, 255, 255));

	browseTitle = new wxStaticText(browsePanel, wxID_ANY, "X-Plane Location", wxDefaultPosition, wxSize(580,20), wxALIGN_CENTRE_HORIZONTAL);
	xPlaneLocationBar = new wxTextCtrl(browsePanel, wxID_ANY, "Set X-Plane Location With Browse", wxDefaultPosition, wxSize(400, 50), wxTE_READONLY | wxTE_CENTRE | wxTE_BESTWRAP);
	browseButton = new wxButton(browsePanel, 10001, "Browse", wxDefaultPosition, wxSize(100, 50));

	// Airframe panel defenitions
	airframePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(295, 300));
	airframePanel->SetBackgroundColour(wxColor(255, 255, 255));

	airframeTitle = new wxStaticText(airframePanel, wxID_ANY, "Zipped Airframes", wxDefaultPosition, wxSize(275, 20), wxALIGN_CENTER_HORIZONTAL);
	airframeList = new wxListBox(airframePanel, wxID_ANY, wxDefaultPosition, wxSize(275, 190));
	airframeListRefresh = new wxButton(airframePanel, wxID_ANY, "Refresh", wxDefaultPosition, wxSize(132, 50));
	airframeOpen = new wxButton(airframePanel, wxID_ANY, "Open", wxDefaultPosition, wxSize(132, 50));

	// Import/Export panel defenitions
	importExportPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(295, 300));
	importExportPanel->SetBackgroundColour(wxColor(255, 255, 255));

	exportPanel = new wxPanel(importExportPanel, wxID_ANY, wxDefaultPosition, wxSize(275, 180));
	exportPanel->SetBackgroundColour(wxColor(169, 169, 169));
	exportBox = new wxTextCtrl(exportPanel, wxID_ANY, "Airframe to ZIP", wxDefaultPosition, wxSize(255, 75), wxTE_CENTRE | wxTE_BESTWRAP);
	exportButton = new wxButton(exportPanel, 10002, "Export to ZIP", wxDefaultPosition, wxSize(255, 75));

	importPanel = new wxPanel(importExportPanel, wxID_ANY, wxDefaultPosition, wxSize(275, 90));
	importPanel->SetBackgroundColour(wxColor(169, 169, 169));
	importButton = new wxButton(importPanel, 10003, "Import from ZIP", wxDefaultPosition, wxSize(255, 70));

	// Browse panel sizer
	wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);
	verticalSizer->Add(browsePanel, 0, wxEXPAND | wxALL, 10);

	wxBoxSizer* browseVerticalSizer = new wxBoxSizer(wxVERTICAL);
	browseVerticalSizer->Add(browseTitle, 2, wxALIGN_CENTER | wxALL, 10);

	wxBoxSizer* browseHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	browseHorizontalSizer->Add(xPlaneLocationBar, 1, wxEXPAND | wxRIGHT, 10);
	browseHorizontalSizer->Add(browseButton, 0, wxEXPAND);

	browseVerticalSizer->Add(browseHorizontalSizer, 5, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
	browsePanel->SetSizerAndFit(browseVerticalSizer);

	// Bottom panels sizer
	wxBoxSizer* horizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	horizontalSizer->Add(airframePanel, 1, wxEXPAND | wxRIGHT, 10);
	horizontalSizer->Add(importExportPanel, 1, wxEXPAND | wxALL, 0);

	// Airframe panel sizer
	wxBoxSizer* airframeVerticalSizer = new wxBoxSizer(wxVERTICAL);
	airframeVerticalSizer->Add(airframeTitle, 0, wxEXPAND | wxALL, 10);
	airframeVerticalSizer->Add(airframeList, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);

	wxBoxSizer* airframeHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
	airframeHorizontalSizer->Add(airframeListRefresh, 1, wxEXPAND | wxRIGHT, 10);
	airframeHorizontalSizer->Add(airframeOpen, 1, wxEXPAND | wxALL, 0);

	airframeVerticalSizer->Add(airframeHorizontalSizer, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
	airframePanel->SetSizerAndFit(airframeVerticalSizer);

	// Import/export panel sizer
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

	// Configures main sizers relative to each-other
	importExportPanel->SetSizerAndFit(importExportSizer);

	verticalSizer->Add(horizontalSizer, 3, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);

	this->SetSizerAndFit(verticalSizer);
}

cMain::~cMain()
{
}


// Message boxes
void cMain::firstBoot() 
{
	wxMessageBox(wxT("It appears that this is the first time you are running this program.\nPlease set your X-Plane location under the \"X-Plane Location\" window."),
		wxT("First Boot"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
	return;
}

void cMain::pathNotSet()
{
	wxMessageBox(wxT("Please set your X-Plane location under the \"X-Plane Location\" window."),
		wxT("Path Not Set"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
	return;
}

void cMain::pathNotFound()
{
	wxMessageBox(wxT("Your X-Plane location does not appear to be valid.\nPlease check your X-Plane location under the \"X-Plane Location\" window."),
		wxT("Path Not Valid"), wxOK | wxCENTRE | wxSTAY_ON_TOP | wxICON_ERROR, this);
	return;
}

void cMain::airframeNotSet()
{
	wxMessageBox(wxT("Please set which airframe you would like to ZIP in the box above."),
		wxT("Airframe Not Set"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
	return;
}

wxArrayString cMain::splitString(wxString s, wxChar del)
{
	wxArrayString outputArray;
	wxString temp = "";
	for (int i = 0; i < (int)s.size(); i++) 
	{
		if (s[i] != del) 
		{
			temp += s[i];
		}
		else
		{
			outputArray.Add(temp);
			temp = "";
		}
	}
	return outputArray;
}

wxArrayString cMain::splitString(wxString s, wxString del)
{
	wxArrayString outputArray;
	int start = 0;
	int end = s.find(del);
	while (end != -1)
	{
		int substrLen = end - start;
		outputArray.Add(s.substr(start, substrLen));
		start = end + del.size();
		end = s.find(del, start);
	}
	return outputArray;
}

wxString cMain::getAirframeID(wxString airframeToCheck, wxString airframeLine)
{
	wxString airframeID = "";
	if (airframeLine.find("aiframe") != wxString::npos)
	{
		if (airframeLine.find(airframeToCheck) != wxString::npos)
		{
			airframeID = splitString(airframeLine, '/')[1];
		}
	}
	return airframeID;
}

wxString cMain::getAirframeData(wxString airframeID, wxString airframeLine)
{
	if (airframeLine.find("\n") != wxString::npos) {
		airframeLine = splitString(airframeLine, "\n")[0];
	}
	if (airframeLine.find("airframe") != wxString::npos)
	{
		if (airframeID == splitString(airframeLine, '/')[1])
		{
			return airframeLine + "\n";
		}
	}
	return "";
}

// Exports selected airframe from airframe.db to ZIP in output folder
void cMain::exportToZIP(wxCommandEvent& WXUNUSED(event))
{
	// Get the airframe to send from the text box
	wxString airframeToSend;
	airframeToSend = exportBox->GetValue();
	wxMessageBox(airframeToSend,
		wxT("Export Cancelled"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
	if (airframeToSend == "Airframe to ZIP" || airframeToSend == "")
	{
		airframeNotSet();
		return;
	}

	// Scan airframe.db for that airframe and grab the ID
	wxString str;
	wxString idToSend = "";
	wxTextFile airframeDB;
	airframeDB.Open(xPlanePath[1] + wxFileName::GetPathSeparator() + "airframe.db");
	str = airframeDB.GetFirstLine();
	if (getAirframeID(airframeToSend, str) != "") {
		idToSend = getAirframeID(airframeToSend, str);
	}
	while (!airframeDB.Eof() && idToSend == "")
	{
		str = airframeDB.GetNextLine();
		if (getAirframeID(airframeToSend, str) != "") {
			idToSend = getAirframeID(airframeToSend, str);
			break;
		}
	}
	airframeDB.Close();

	if (idToSend == "")
	{
		wxMessageBox(wxT("Airframe not found!"),
			wxT("Airframe Not Found"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
		return;
	}
	else
	{
		wxMessageBox(wxT("Airframe id: " + idToSend),
			wxT("Airframe"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
	}

	// Add all relavent information to a string
	airframeDB.Open(xPlanePath[1] + wxFileName::GetPathSeparator() + "airframe.db");
	str = "";
	wxString airframeData = "";
	wxString airframeUUID = "";
	str = airframeDB.GetFirstLine();
	if (getAirframeData(idToSend, str) != "") {
		airframeData = airframeData + getAirframeData(idToSend, str);
		if (str.find("uuid"))
		{
			airframeUUID = splitString(str, "= ")[1];
		}
	}
	while (!airframeDB.Eof())
	{
		str = airframeDB.GetNextLine();
		if (getAirframeData(idToSend, str) != "") {
			airframeData = airframeData + getAirframeData(idToSend, str);
			if (str.find("uuid"))
			{
				airframeUUID = splitString(str, "= ")[1];
			}
		}
	}
	airframeDB.Close();

	// If nothing was found, notify user
	if (airframeData == "")
	{
		wxMessageBox(wxT("Airframe not found!"),
			wxT("Airframe Not Found"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
		return;
	}
	airframeData.resize(airframeData.size()-2);

	// Check if compressed airframes directory exists
	if (!wxDir::Exists(configDir + wxFileName::GetPathSeparator() + "compressedAirframes"))
	{
		wxFileName::Mkdir(configDir + wxFileName::GetPathSeparator() + "compressedAirframes");
	}

	// Check if a zip for that airframe already exists
	if (wxFile::Exists(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + airframeToSend + ".zip"))
	{
		wxMessageDialog* overWriteDialog = new wxMessageDialog(this, "A .zip for this airframe already exists, would you like to overwrite?", "", wxCANCEL | wxOK | wxCENTRE | wxSTAY_ON_TOP | wxCANCEL_DEFAULT | wxICON_WARNING);
		if (overWriteDialog->ShowModal() == wxID_OK) 
		{
			wxRemoveFile(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + airframeToSend + ".zip");
		}
		else
		{
			wxMessageBox(wxT("Export Cancelled."),
				wxT("Export Cancelled"), wxOK | wxCENTRE | wxSTAY_ON_TOP, this);
			return;
		}
	}

	// Check if temp folder exists
	if (!wxDir::Exists(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + "tmp"))
	{
		wxFileName::Mkdir(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + "tmp");
	}
	else if (wxDir::Exists(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + "tmp" + wxFileName::GetPathSeparator() + airframeToSend))
	{
		wxRemoveFile(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + "tmp" + wxFileName::GetPathSeparator() + airframeToSend);
	}
	wxFileName::Mkdir(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + "tmp" + wxFileName::GetPathSeparator() + airframeToSend);

	// Write airframe data to file
	wxTextFile dataFile;
	dataFile.Open(configDir + wxFileName::GetPathSeparator() + "compressedAirframes" + wxFileName::GetPathSeparator() + "tmp" + wxFileName::GetPathSeparator() + airframeToSend + wxFileName::GetPathSeparator() + "airframe.db.txt");
	dataFile.AddLine(airframeData);
	dataFile.Write();
	dataFile.Close();
	return;
}

void cMain::browseForXPlane(wxCommandEvent& WXUNUSED(event))
{
	wxDirDialog
		openDirDialog(this, _("Open your X-Plane 11 folder"), "", wxDD_DIR_MUST_EXIST);
	if (openDirDialog.ShowModal() == wxID_CANCEL)
		return;     // the user changed idea...

	// proceed loading the file chosen by the user;
	// this can be done with e.g. wxWidgets input streams:
	if (!wxDirExists(openDirDialog.GetPath()))
	{
		pathNotFound();
		return;
	}
	else
	{
		xPlanePath.Add(openDirDialog.GetPath());
		xPlanePath.Add(openDirDialog.GetPath() + wxFileName::GetPathSeparator() + "Output" + wxFileName::GetPathSeparator() + "CL650" + wxFileName::GetPathSeparator() + "airframes");
		xPlaneLocationBar->SetLabel(xPlanePath[0]);
		writeConfig("path", xPlanePath[0]);
	}
	return;
}

void cMain::readConfig()
{
	if (!wxDir::Exists(configDir))
	{
		wxFileName::Mkdir(configDir);
	}
	wxString pathValue;
	wxFileConfig* ConfigINI = new wxFileConfig("Vanguard Airframe Manager", wxEmptyString, configPath);
	if (ConfigINI->wxConfigBase::Read("path", &pathValue))
	{
		if (pathValue == "0") 
		{
			pathNotSet();
		}
		else if (!wxDirExists(pathValue)) 
		{
			pathNotFound();
		}
		else 
		{
			xPlanePath.Add(pathValue);
			xPlanePath.Add(pathValue + wxFileName::GetPathSeparator() + "Output" + wxFileName::GetPathSeparator() + "CL650" + wxFileName::GetPathSeparator() + "airframes");
			xPlaneLocationBar->SetLabel(xPlanePath[0]);
		}
		delete ConfigINI;
	} else
	{
		ConfigINI->Write("path", "0");
		ConfigINI->Flush();
		delete ConfigINI;
		firstBoot();
	}
	return;
}

void cMain::writeConfig(wxString writeKey, wxString writeValue)
{
	wxFileConfig* ConfigINI = new wxFileConfig("Vanguard Airframe Manager", wxEmptyString, configPath);
	ConfigINI->Write(writeKey, writeValue);
	ConfigINI->Flush();
	delete ConfigINI;
	return;
}