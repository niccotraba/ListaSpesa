#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, ShoppingList& list)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)), list(list) {
    
    // Registriamo questa finestra come osservatore della lista
    list.addObserver(this);

    // Creiamo un pannello di sfondo (obbligatorio su Windows/Linux per i colori giusti)
    wxPanel* panel = new wxPanel(this);

    // Centriamo la finestra nello schermo
    this->Centre();
}

// Implementazione vuota per ora (la riempiremo dopo)
void MainFrame::update() {
    // Qui aggiorneremo la grafica quando i dati cambiano
}

void MainFrame::OnAdd(wxCommandEvent& event) {}
void MainFrame::OnRemove(wxCommandEvent& event) {}
void MainFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}