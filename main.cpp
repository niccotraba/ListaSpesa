// codice cpp per una semplice applicazione wxWidgets che crea una finestra vuota, prova

#include <wx/wx.h>

// Definizione dell'applicazione
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

// Definizione della finestra principale
class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

wxIMPLEMENT_APP(MyApp);

// Avvio dell'app
bool MyApp::OnInit() {
    MyFrame *frame = new MyFrame("Lista della Spesa", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    return true;
}

// Costruttore della finestra
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {
}