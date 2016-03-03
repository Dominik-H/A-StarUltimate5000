#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

class A_Star_App :
	public wxApp
{
public:
	A_Star_App();
	~A_Star_App();
	virtual bool OnInit();
};

class MainFrame :
	public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_Hello = 1
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(ID_Hello, MainFrame::OnHello)
	EVT_MENU(wxID_EXIT, MainFrame::OnExit)
	EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(A_Star_App);
