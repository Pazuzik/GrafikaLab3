#define _USE_ANTIALIASING
#include <wx/wxprec.h>
#include <wx/panel.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/colordlg.h>
#include <wx/textctrl.h>
#include <wx/combobox.h>
#include <wx/frame.h>
#include <wx/dcbuffer.h>
#include <wx/dcgraph.h>
// JUST A TEST CHANGE
class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	MyFrame();
	void letsDraw();
	void Form_Paint(wxPaintEvent& e);
	void Form_Update(wxUpdateUIEvent& e);
	void saveButtonClick(wxCommandEvent& e);
	void checkTheCheck(wxCommandEvent& e);
	void raiseLapka(wxScrollEvent& e);
	void writeText(wxCommandEvent& e);
	void letsPick(wxCommandEvent& e);
	void colorButtonClick(wxCommandEvent& e);

private:
	wxBoxSizer* WxBoxSizer1;
	wxBoxSizer* WxBoxSizer2;
	wxBoxSizer* WxBoxSizer3;
	wxPanel* myPanel;
	wxButton* saveButton;
	wxButton* starButton;
	wxCheckBox* checkTheBanana;
	wxScrollBar* katLapki;
	wxGauge* grafKatLapki;
	wxTextCtrl* tekscik;
	wxString  string = "Tekst";
	wxChoice* pickAChoice;
	int  whichShape;
	wxColour shapeColor;
	wxBitmap Havanana;
	wxBitmap myBuffer;
	wxImage myImage;
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame* frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Demo 11", wxDefaultPosition, wxSize(600, 400))
{
	SetTitle(_("Malpa & banan: love story  Grafika Lab3"));
	SetIcon(wxNullIcon);

	// SETTING UP THE BUTTONS AND SHIT //

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	//this->SetSizer(WxBoxSizer1);
	//this->SetAutoLayout(true);

	myPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	WxBoxSizer1->Add(myPanel, 1, wxEXPAND | wxALL, 5);

	WxBoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxEXPAND, 5);

	WxBoxSizer3 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer3->SetMinSize(wxSize(196, 350));
	WxBoxSizer1->Add(WxBoxSizer3, 0, wxEXPAND, 5);

	saveButton = new wxButton(this, wxID_ANY, _("Zapisz do pliku"), wxPoint(38, 37), wxSize(120, 29), 0, wxDefaultValidator, _("saveButton"));
	WxBoxSizer3->Add(saveButton, 0, wxALIGN_CENTER | wxALL, 5);

	checkTheBanana = new wxCheckBox(this, wxID_ANY, _("Banana:)"), wxPoint(23, 65), wxSize(105, 19), 0, wxDefaultValidator, _("checkTheBanana"));
	WxBoxSizer3->Add(checkTheBanana, 0, wxALIGN_CENTER | wxALL, 5);

	katLapki = new wxScrollBar(this, wxID_ANY, wxPoint(22, 107), wxSize(200, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("katLapki"));
	katLapki->SetScrollbar(0, 1, 100, 1);
	katLapki->Disable();
	WxBoxSizer3->Add(katLapki, 0, wxALIGN_CENTER | wxALL, 5);

	grafKatLapki = new wxGauge(this, wxID_ANY, 99, wxPoint(21, 106), wxSize(200, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("grafKatLapki"));
	WxBoxSizer3->Add(grafKatLapki, 0, wxALIGN_CENTER | wxALL, 5);

	starButton = new wxButton(this, wxID_ANY, _("Kolor gwiazdy"), wxPoint(38, 37), wxSize(120, 29), 0, wxDefaultValidator, _("starButton"));
	WxBoxSizer3->Add(starButton, 0, wxALIGN_CENTER | wxALL, 5);

	tekscik = new wxTextCtrl(this, wxID_ANY, _("Wpisz tekst"), wxPoint(162, 21), wxSize(131, 25), 0, wxDefaultValidator, _("tekscik"));
	WxBoxSizer3->Add(tekscik, 0, wxALIGN_CENTER | wxALL, 5);

	wxArrayString arrayStringFor_WxChoice1;
	pickAChoice = new wxChoice(this, wxID_ANY, wxPoint(447, 21), wxSize(90, 23), arrayStringFor_WxChoice1, 0, wxDefaultValidator, _("letsPick"));
	WxBoxSizer3->Add(pickAChoice, 0, wxALIGN_CENTER | wxALL, 5);
	pickAChoice->Append("gwiazdka");
	pickAChoice->Append("księżyc");
	pickAChoice->Append("słońce");


	SetSizer(WxBoxSizer1);
	Center();
	Layout();
	Centre(wxBOTH);

	Bind(wxEVT_PAINT, &MyFrame::Form_Paint, this);
	Bind(wxEVT_UPDATE_UI, &MyFrame::Form_Update, this);
	saveButton->Bind(wxEVT_BUTTON, &MyFrame::saveButtonClick, this);
	starButton->Bind(wxEVT_BUTTON, &MyFrame::colorButtonClick, this);
	Bind(wxEVT_CHECKBOX, &MyFrame::checkTheCheck, this);
	Bind(wxEVT_SCROLL_THUMBTRACK, &MyFrame::raiseLapka, this);
	Bind(wxEVT_TEXT, &MyFrame::writeText, this);
	Bind(wxEVT_CHOICE, &MyFrame::letsPick, this);

	shapeColor = wxColour(*wxBLACK);

	wxImage bananana = wxImage();
	bananana.AddHandler(new wxPNGHandler);
	bananana.LoadFile("banan.png", wxBITMAP_TYPE_PNG);
	Havanana = wxBitmap(bananana);

}

void MyFrame::letsDraw()
{
	wxPen myOlowek;
	wxClientDC myDC(myPanel);

	myBuffer = wxBitmap(myPanel->GetSize().x, myPanel->GetSize().y);
	wxBufferedDC _myDC(&myDC, myBuffer);

#ifdef _USE_ANTIALIASING
	wxGCDC MyDC(_myDC);
#else
#define MyDC _myDC
#endif

	wxSize XY = myPanel->GetSize();
	int x = (XY.x - 377) / 2;
	int y = (XY.y - 346) / 2;

	MyDC.SetBackground(*wxWHITE_BRUSH);
	MyDC.Clear();


	if (checkTheBanana->IsChecked())
		MyDC.DrawBitmap(Havanana, x+145 - Havanana.GetWidth() / 2, y+190 - 0.38 * grafKatLapki->GetValue() - Havanana.GetHeight() / 2);

	MyDC.DrawCircle(x+180, y+130, 20); // GŁOWA
	MyDC.DrawEllipse(x + 165, y + 120, 12, 6);  // OCZY
	MyDC.DrawEllipse(x + 185, y + 120, 12, 6);
	MyDC.DrawCircle(x + 170, y + 123, 2);
	MyDC.DrawCircle(x + 190, y + 123, 2);
	MyDC.DrawLine(x + 180, y + 150, x + 180, y + 230); // TŁÓW I KOŃCZYNY
	MyDC.DrawLine(x + 180, y + 230, x + 155, y + 270);
	MyDC.DrawLine(x + 180, y + 230, x + 205, y + 270);
	MyDC.DrawLine(x + 180, y + 170, x + 205, y + 200);
	MyDC.DrawLine(x + 180, y + 170, x + 155, y + 200 - 0.38 * grafKatLapki->GetValue()); // RĘKA OD BANANA

	if (checkTheBanana->IsChecked())
	{
		MyDC.DrawEllipticArc(x+170, y+130, 10, 7, -15, -180);
		MyDC.DrawEllipticArc(x+180, y+130, 10, 7, 0, -165); // :3
	}
	else
	{
		MyDC.DrawEllipticArc(x+175, y+130, 10, 15, 0, 180); // :c
	}


	wxString text1(string);
	MyDC.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Cambria Math"));
	MyDC.DrawText(text1, x+140, y+280);
	wxString text2(string);
	MyDC.SetFont(wxFont(30, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false, "Chiller"));
	MyDC.DrawRotatedText(string, x+215, y+270, 90);

	
	if (whichShape == 0)
	{
		MyDC.SetBrush(wxBrush(shapeColor));
		MyDC.SetPen(wxPen(shapeColor));
		wxPoint pointyPoints[5] = 
		{
			wxPoint(x+123, y+80),
			wxPoint(x + 148, y + 128),
			wxPoint(x + 93 , y + 99),
			wxPoint(x + 153, y + 99),
			wxPoint(x + 103, y + 128)
		};
		MyDC.DrawPolygon(5, pointyPoints, 0, 0);
	}
	else if (whichShape == 1)
	{
		MyDC.SetBrush(wxColour(192, 192, 192));
		MyDC.SetPen(wxColour(192, 192, 192));
		MyDC.DrawCircle(x+100, y+75, 25);
		MyDC.SetBrush(wxColour(255, 255, 255));
		MyDC.SetPen(wxColour(255, 255, 255));
		MyDC.DrawCircle(x+90, y+65, 25);
		MyDC.SetBrush(wxColour(0,0,0));
		MyDC.SetPen(wxColour(0, 0, 0));
		MyDC.DrawCircle( x+112, y+77, 2);
		MyDC.DrawLine(x+105, y+86,  x+110,  y+87);
	}
	else if (whichShape == 2)
	{
		MyDC.SetBrush(wxColour(255,255,0));
		MyDC.SetPen(wxColour(255, 255, 0));
		MyDC.DrawCircle(x+100, y+75, 25);
	}


}

void MyFrame::Form_Paint(wxPaintEvent& WXUNUSED(e))
{
	letsDraw();
}

void MyFrame::Form_Update(wxUpdateUIEvent& WXUNUSED(e))
{
	letsDraw();
}

void MyFrame::saveButtonClick(wxCommandEvent& WXUNUSED(e)) {
	wxFileDialog saveFileDialog(this, "Wybierz plik", "", "", "BMP files (*.bmp)|*.bmp|JPG files (*.jpg)|*.jpg|PNG files (*.png)|*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL)
		return;
	myImage = myBuffer.ConvertToImage();
	myImage.AddHandler(new wxJPEGHandler);
	myImage.AddHandler(new wxPNGHandler);
	myImage.SaveFile(saveFileDialog.GetPath());
}

void MyFrame::checkTheCheck(wxCommandEvent& e)
{
	katLapki->Enable(checkTheBanana->IsChecked());
}

void MyFrame::raiseLapka(wxScrollEvent& WXUNUSED(e)) 
{
	grafKatLapki->SetValue(katLapki->GetThumbPosition());
	letsDraw();
}

void MyFrame::writeText(wxCommandEvent& WXUNUSED(e))
{
	string = tekscik->GetValue();
}

void MyFrame::letsPick(wxCommandEvent& WXUNUSED(e))
{
	whichShape = pickAChoice->GetSelection();
}

void MyFrame::colorButtonClick(wxCommandEvent& WXUNUSED(e)) 
{
	wxColourDialog chooseColourDialog(this, nullptr);
	if (chooseColourDialog.ShowModal() == wxID_CANCEL)
		return;
	shapeColor = chooseColourDialog.GetColourData().GetColour();
}