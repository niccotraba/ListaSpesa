#include "MainFrame.h"
#include <wx/listctrl.h> //per la lista
#include "MFdialog.h" //per il dialogo di inserimento/modifica

MainFrame::MainFrame(const wxString& title, ShoppingList& list)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400)), list(list) {

    //registrazione Observer
    list.addObserver(this);

    //pannello principale (sfondo)
    wxPanel* panel = new wxPanel(this);

    //creazione della Lista (tabella)
    listView = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT); //wxLC_REPORT per la visualizzazione a tabella

    //aggiunta le colonne
    listView->AppendColumn("Prodotto", wxLIST_FORMAT_LEFT, 150);
    listView->AppendColumn("Quantità", wxLIST_FORMAT_CENTER, 80);
    listView->AppendColumn("Categoria", wxLIST_FORMAT_LEFT, 100);
    listView->AppendColumn("Prezzo", wxLIST_FORMAT_RIGHT, 80);
    listView->AppendColumn("Stato", wxLIST_FORMAT_CENTER, 100);

    //creazione bottoni
    addButton = new wxButton(panel, wxID_ANY, "Aggiungi");
    removeButton = new wxButton(panel, wxID_ANY, "Rimuovi");
    editButton = new wxButton(panel, wxID_ANY, "Modifica");
    toggleButton = new wxButton(panel, wxID_ANY, "Preso");
    wxButton* quitButton = new wxButton(panel, wxID_ANY, "Esci");

    //layout con sizer
    //sizer principale verticale (Lista sopra, bottoni sotto)
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    //sizer orizzontale per i bottoni (in riga)
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addButton, 0, wxALL, 5);
    buttonSizer->Add(removeButton, 0, wxALL, 5);
    buttonSizer->Add(editButton, 0, wxALL, 5);
    buttonSizer->Add(toggleButton, 0, wxALL, 5);
    buttonSizer->Add(quitButton, 0, wxALL, 5);

    //aggiunta alla finestra
    mainSizer->Add(listView, 1, wxEXPAND | wxALL, 10); // La lista si espande (1)
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10); // I bottoni no (0)

    panel->SetSizer(mainSizer);

    //collegamento eventi
    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);
    removeButton->Bind(wxEVT_BUTTON, &MainFrame::OnRemove, this);
    editButton->Bind(wxEVT_BUTTON, &MainFrame::OnEdit, this);
    toggleButton->Bind(wxEVT_BUTTON, &MainFrame::OnToggle, this);
    quitButton->Bind(wxEVT_BUTTON, &MainFrame::OnQuit, this);

    this->Centre();

    //chiamata iniziale per popolare la lista con eventuali dati già presenti
    update();
}

//funzione chiamata quando la lista notifica un cambiamento (tramite notify()) per aggiornare la grafica
void MainFrame::update() {
    //ogni volta che la lista cambia, la grafica vecchia viene eliminata e ricostruita da capo
    //grafica vecchia svuotata
    listView->DeleteAllItems();

    //dati aggiornati
    const auto& items = list.getItems();

    //ricostruzione grafica con i dati aggiornati
    for (int i = 0; i < items.size(); ++i) {
        const auto& item = items[i];

        //inserimento nuova riga con il nome del prodotto (colonna 0)
        listView->InsertItem(i, item.getName());

        //inserimento quantità (colonna 1)
        listView->SetItem(i, 1, std::to_string(item.getQuantity()));
        listView->SetItem(i, 2, item.getCategory());

        //inserimento prezzo (colonna 3), formattato con due decimali e simbolo euro
        listView->SetItem(i, 3, wxString::Format("%.2f €", item.getPrice()));

        //stato
        listView->SetItem(i, 4, item.isPurchased() ? "Preso" : "Da prendere");

        //TODO: si potrebbe aggiungere un'icona o un colore diverso per gli elementi acquistati, per renderli più evidenti.
    }
}

//funzioni eventi dei bottoni

//evento delo bottone "aggiungi"
void MainFrame::OnAdd(wxCommandEvent& event) {
    //diaologo vuoto
    EditDialog dialog(this, "Aggiungi Prodotto");

    //se l'utente preme OK, prendo i dati inseriti e creo un nuovo oggetto ShoppingItem, che poi aggiungo alla lista
    if (dialog.ShowModal() == wxID_OK) {
        // Se ha premuto OK, creo l'oggetto con i dati inseriti
        ShoppingItem newItem(
            dialog.getName().ToStdString(),
            dialog.getQuantity(),
            false, // Non comprato
            dialog.getCategory().ToStdString(),
            dialog.getPrice()
        );

        //aggiungo alla lista, che poi notifica la MainFrame per aggiornare la grafica
        list.addItem(newItem);
    }
}

//evento per il bottone "rimuovi"
void MainFrame::OnRemove(wxCommandEvent& event) {
    //indice selezionato dalla lista. -1 se nessun elemento è selezionato
    long itemIndex = -1;
    itemIndex = listView->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex != -1) {
        list.removeItem(itemIndex);
    }
}

//evento per il bottone "esci"
void MainFrame::OnQuit(wxCommandEvent& event) {
    Close(true);
}

//evento per il bottone "modifica"
void MainFrame::OnEdit(wxCommandEvent& event) {
    //prendo l'indice selezionato
    long itemIndex = -1;
    itemIndex = listView->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex == -1) return; // Niente selezionato

    //recupero l'oggetto attuale dalla lista: copiamo i dati per pre-riempire il form
    const auto& item = list.getItems()[itemIndex];

    //il dialogo si apre con i dati vecchi
    EditDialog dialog(this, "Modifica Prodotto",
                      item.getName(),
                      item.getQuantity(),
                      item.getCategory(),
                      item.getPrice());

    //se l'utente preme OK, prendo i dati inseriti e creo un nuovo oggetto ShoppingItem, che poi sostituisco a quello vecchio nella lista
    if (dialog.ShowModal() == wxID_OK) {
        ShoppingItem updatedItem(
            dialog.getName().ToStdString(),
            dialog.getQuantity(),
            item.isPurchased(), // Mantengo lo stato di acquisto vecchio
            dialog.getCategory().ToStdString(),
            dialog.getPrice()
        );

        list.modifyItem(itemIndex, updatedItem);
    }
}

//evento per il bottone "preso" (toggle stato di acquisto)
void MainFrame::OnToggle(wxCommandEvent& event) {
    long itemIndex = -1;
    itemIndex = listView->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (itemIndex != -1) {
        list.togglePurchased(itemIndex);
        // L'observer ridisegnerà la lista aggiornando la scritta "Preso/Da prendere"
    }
}