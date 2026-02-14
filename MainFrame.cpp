#include "MainFrame.h"
#include <wx/listctrl.h> // Fondamentale per la lista

MainFrame::MainFrame(const wxString& title, ShoppingList& list)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)), list(list) {

    // 1. Registrazione Observer
    list.addObserver(this);

    // 2. Pannello principale (Sfondo)
    wxPanel* panel = new wxPanel(this);

    // 3. Creazione della Lista (Tabella)
    // wxLC_REPORT significa "modalità dettagli" (colonne)
    listView = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);

    // Aggiungiamo le colonne
    listView->AppendColumn("Prodotto", wxLIST_FORMAT_LEFT, 150);
    listView->AppendColumn("Quantità", wxLIST_FORMAT_CENTER, 80);
    listView->AppendColumn("Categoria", wxLIST_FORMAT_LEFT, 100);
    listView->AppendColumn("Prezzo", wxLIST_FORMAT_RIGHT, 80);
    listView->AppendColumn("Stato", wxLIST_FORMAT_CENTER, 100);

    // 4. Creazione Bottoni
    addButton = new wxButton(panel, wxID_ANY, "Aggiungi");
    removeButton = new wxButton(panel, wxID_ANY, "Rimuovi");
    wxButton* quitButton = new wxButton(panel, wxID_ANY, "Esci");

    // 5. Layout (I Sizers)
    // Sizer principale verticale (Lista sopra, bottoni sotto)
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Sizer orizzontale per i bottoni (li mette in riga)
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addButton, 0, wxALL, 5);
    buttonSizer->Add(removeButton, 0, wxALL, 5);
    buttonSizer->Add(quitButton, 0, wxALL, 5);

    // Assembliamo tutto
    mainSizer->Add(listView, 1, wxEXPAND | wxALL, 10); // La lista si espande (1)
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10); // I bottoni no (0)

    panel->SetSizer(mainSizer);

    // 6. Collegamento Eventi (Click dei bottoni)
    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);
    removeButton->Bind(wxEVT_BUTTON, &MainFrame::OnRemove, this);
    quitButton->Bind(wxEVT_BUTTON, &MainFrame::OnQuit, this);

    this->Centre();

    // Chiamata iniziale per popolare la lista se ci sono già dati
    update();
}

// Questa funzione viene chiamata automaticamente quando la ShoppingList cambia (notify)
void MainFrame::update() {
    // 1. Pulisce la grafica vecchia
    listView->DeleteAllItems();

    // 2. Prende i dati aggiornati
    const auto& items = list.getItems();

    // 3. Riscrive tutto nella tabella
    for (int i = 0; i < items.size(); ++i) {
        const auto& item = items[i];

        // Inserisce la riga (Colonna 0: Nome)
        listView->InsertItem(i, item.getName());

        // Imposta le altre colonne della stessa riga
        listView->SetItem(i, 1, std::to_string(item.getQuantity()));
        listView->SetItem(i, 2, item.getCategory());

        // Formattazione prezzo
        listView->SetItem(i, 3, wxString::Format("%.2f €", item.getPrice()));

        // Stato
        listView->SetItem(i, 4, item.isPurchased() ? "Preso" : "Da prendere");

        // Se è comprato, magari cambiamo colore (opzionale, per ora lasciamo standard)
    }
}

// --- Funzioni eventi (Stub per ora) ---

void MainFrame::OnAdd(wxCommandEvent& event) {
    // Per ora testiamo solo se il bottone funziona aggiungendo un oggetto fisso
    ShoppingItem testItem("Test Prodotto", 1, false, "Test", 9.99);
    list.addItem(testItem);
}

void MainFrame::OnRemove(wxCommandEvent& event) {
    // Prende l'indice selezionato nella grafica
    long itemIndex = -1;
    itemIndex = listView->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex != -1) {
        list.removeItem(itemIndex);
    }
}

void MainFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}