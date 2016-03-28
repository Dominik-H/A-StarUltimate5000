#include "A_Star_App.h"

A_Star_App::A_Star_App()
{
}


A_Star_App::~A_Star_App()
{
}

bool A_Star_App::OnInit() 
{
	frame = new MainFrame("A-Star Ultimate 5000", wxPoint(50, 50), wxSize(460, 600));
	frame->Show(true);
	return true;
}

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(NULL, wxID_ANY, title, pos, size, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)),
	map(0), start(0), search(0), finish(0), path(0)
{
	loaded = false;

	SetIcon(wxICON(frame_icon));

	panel = new wxPanel(this, wxID_ANY);
	panel->SetBackgroundColour(wxColour(53, 53, 53));

	wxButton *button_file = new wxButton(panel, ID_File, wxT("Choose File"), wxPoint(10, 300), wxSize(205, 30));
	Connect(ID_File, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnFile));

	wxButton *button_run = new wxButton(panel, ID_Run, wxT("Run"), wxPoint(230, 300), wxSize(205, 30));
	Connect(ID_Run, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnRun));

	button_file->SetFocus();

	debugText = new wxTextCtrl(panel, ID_Debug, wxT(""), wxPoint(10, 340), wxSize(425, 215), wxTE_READONLY | wxTE_RICH | wxTE_MULTILINE | wxBORDER_NONE);
	debugText->SetBackgroundColour(wxColour(35, 35, 35));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(230, 230, 230), wxColour(35, 35, 35)));
	debugText->AppendText(wxT("***WELCOME to my A-Star-Ultimate-5000 App!***\nThis App is created as a school asignment by Dominik Horňák. All Rights Reserved!\n"));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(255, 0, 0)));
	debugText->AppendText(wxT("The START field is RED\n"));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(0, 0, 255)));
	debugText->AppendText(wxT("The FINISH field is BLUE\n"));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(0, 255, 0)));
	debugText->AppendText(wxT("The PATH is GREEN\n"));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(204, 204, 0)));
	debugText->AppendText(wxT("The WALL is YELLOW\n"));

	debugText->SetDefaultStyle(wxTextAttr(wxColour(230, 230, 230)));
	debugText->AppendText(wxT("ONLY RESULT IS DRAWN! Other data are only writen bellow.\n"));

	Connect(wxEVT_PAINT, wxPaintEventHandler(MainFrame::OnPaint));
}

void MainFrame::OnFile(wxCommandEvent& event)
{
	if (loaded) {
		if (path) {
			path->clear();
			delete path;
		}

		delete search;
		start->deleteKids();
		delete start;
		delete map;
		loaded = false;
	}

	wxFileDialog *openFileDialog = new wxFileDialog(this);

	if (openFileDialog->ShowModal() == wxID_OK) {
		std::string path = openFileDialog->GetPath();
		map = new DHAStar5000::Map(path);
		start = new DHAStar5000::Field(nullptr, map, 0, 0);
		search = new DHAlgos::BestFirstSearch(start);
		loaded = true;

		debugText->SetDefaultStyle(wxTextAttr(*wxRED));
		debugText->AppendText("Data Loaded Succesfuly!\n");
	}

	delete openFileDialog;
}

void MainFrame::OnRun(wxCommandEvent& event)
{
	if (loaded) {
		wxClientDC dc(panel);
		dc.SetPen(wxPen(wxColour(53, 53, 53)));
		dc.SetBrush(wxBrush(wxColour(53, 53, 53)));
		dc.DrawRectangle(10, 10, 425, 280);

		debugText->SetDefaultStyle(wxTextAttr(*wxGREEN));

		finish = dynamic_cast<DHAStar5000::Field *>(search->search());
		if (!finish) {
			debugText->AppendText(wxT("There is no path!\n"));
			return;
		}

		wxColour yellow(204, 204, 0);

		path = finish->getPathToStart();

		std::vector<DHAlgos::Node *> debug = search->getDebugData();
		for (uint32 i = 0; i < debug.size(); ++i) {
			wxString out = wxT("X: ");
			int dimension = dynamic_cast<DHAStar5000::Field *>(debug.at(i))->getY();
			out += wxString::Format(wxT("%d"), dimension);
			out += wxT(" Y: ");
			dimension = dynamic_cast<DHAStar5000::Field *>(debug.at(i))->getX();
			out += wxString::Format(wxT("%d"), dimension);
			out += wxT("\n");
			debugText->AppendText(out);
		}

		wxString out = wxT("X: ");
		int dimension = finish->getY();
		out += wxString::Format(wxT("%d"), dimension);
		out += wxT(" Y: ");
		dimension = finish->getX();
		out += wxString::Format(wxT("%d"), dimension);
		out += wxT("\n");
		debugText->AppendText(out);

		uint32 height = map->getWidth();
		uint32 width = map->getHeight();

		uint32 w = (425 / width) - 1;
		uint32 h = (280 / height) - 1;

		for (uint32 i = 0; i < height; ++i) {
			for (uint32 j = 0; j < width; ++j) {
				switch (map->getFieldType(i, j)) {
				case DHAStar5000::FieldType::WALL:
					dc.SetPen(wxPen(yellow));
					dc.SetBrush(wxBrush(yellow));
					break;
				case DHAStar5000::FieldType::START:
					dc.SetPen(wxPen(*wxRED));
					dc.SetBrush(wxBrush(*wxRED));
					break;
				case DHAStar5000::FieldType::FINISH:
					dc.SetPen(wxPen(*wxBLUE));
					dc.SetBrush(wxBrush(*wxBLUE));
					break;
				default:
					dc.SetPen(wxPen(wxColour(35, 35, 35)));
					dc.SetBrush(wxBrush(wxColour(35, 35, 35)));
				}

				dc.DrawRectangle(10 + (j * (w + 1)), 10 + (i * (h + 1)), w, h);
			}
		}

		dc.SetPen(wxPen(*wxGREEN));
		dc.SetBrush(wxBrush(*wxGREEN));

		for (uint32 i = 1; i < path->size(); ++i) {
			uint32 x = dynamic_cast<DHAStar5000::Field *>(path->at(i))->getY();
			uint32 y = dynamic_cast<DHAStar5000::Field *>(path->at(i))->getX();

			dc.DrawRectangle(10 + (x * (w + 1)), 10 + (y * (h + 1)), w, h);
		}
	}
}

void MainFrame::OnPaint(wxPaintEvent& event) 
{
}

void MainFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MainFrame::OnClose(wxCloseEvent& event) 
{
	if (loaded) {
		if (path) {
			path->clear();
			delete path;
		}

		delete search;
		start->deleteKids();
		delete start;
		delete map;
		loaded = false;
	}

	Destroy();
}
