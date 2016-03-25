#pragma once

#include <wx/wxprec.h>
#include "Map.h"
#include "Field.h"
#include "BestFirstSearch.h"

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class MainFrame;

class A_Star_App :
	public wxApp
{
public:
	A_Star_App();
	~A_Star_App();
	virtual bool OnInit();

private:
	MainFrame *frame;
};

class MainFrame :
	public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	void OnPaint(wxPaintEvent& event);

private:
	void OnFile(wxCommandEvent& event);
	void OnRun(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	wxTextCtrl *debugText;
	wxPanel *panel;

	// AStar Related
	bool loaded;
	DHAStar5000::Map *map;
	DHAStar5000::Field *start;
	DHAlgos::BestFirstSearch *search;

	DHAStar5000::Field *finish;
	std::vector<DHAlgos::Node *> *path;

	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_File = 1,
	ID_Run = 2,
	ID_Debug = 3,
	ID_Output = 4
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_CLOSE(MainFrame::OnClose)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(A_Star_App);
