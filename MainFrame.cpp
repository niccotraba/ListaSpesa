#include "MainFrame.h"
#include <wx/listctrl.h> //per la lista
#include "MFdialog.h" //per il dialogo di inserimento/modifica

MainFrame::MainFrame(const wxString& title, ShoppingList& list)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(600, 450)), list(list) {

    list.addObserver(this);

    //barra menu
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu();

    fileMenu->Append(wxID_SAVE, "&Salva Lista...\tCtrl-S");
    fileMenu->Append(wxID_OPEN, "&Carica Lista...\tCtrl-O");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "&Esci\tAlt-F4");

    menuBar->Append(fileMenu, "&File");
    SetMenuBar(menuBar); //attacca il menu alla finestra

    //layout principale
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    //lista (tabella)
    listView = new wxListView(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
    listView->AppendColumn("Prodotto", wxLIST_FORMAT_LEFT, 150);
    listView->AppendColumn("Quantità", wxLIST_FORMAT_CENTER, 80);
    listView->AppendColumn("Categoria", wxLIST_FORMAT_LEFT, 100);
    listView->AppendColumn("Prezzo", wxLIST_FORMAT_RIGHT, 80);
    listView->AppendColumn("Stato", wxLIST_FORMAT_CENTER, 100);

    //bottoni
    addButton = new wxButton(panel, wxID_ANY, "Aggiungi"); //creazione del bottone "Aggiungi"
    editButton = new wxButton(panel, wxID_ANY, "Modifica"); //creazione del bottone "Modifica"
    toggleButton = new wxButton(panel, wxID_ANY, "Segna Preso"); //creazione del bottone "Segna Preso"
    removeButton = new wxButton(panel, wxID_ANY, "Rimuovi"); //creazione del bottone "Rimuovi"
    wxButton* quitButton = new wxButton(panel, wxID_ANY, "Esci"); //creazione del bottone "Esci"

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(addButton, 0, wxALL, 5);
    buttonSizer->Add(editButton, 0, wxALL, 5);
    buttonSizer->Add(toggleButton, 0, wxALL, 5);
    buttonSizer->Add(removeButton, 0, wxALL, 5);
    buttonSizer->Add(quitButton, 0, wxALL, 5);

    //prezzo totale (in basso a destra)
    totalText = new wxStaticText(panel, wxID_ANY, "Totale: 0.00 €");
    wxFont font = totalText->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD); //grassetto e testo più grande per evidenziare il totale
    font.SetPointSize(12);
    totalText->SetFont(font);

    //layout
    mainSizer->Add(listView, 1, wxEXPAND | wxALL, 10);
    //il totale viene allineato a destra con un margine
    mainSizer->Add(totalText, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 15);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    panel->SetSizer(mainSizer);

    //eventi
    //menu
    Bind(wxEVT_MENU, &MainFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnLoad, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnQuit, this, wxID_EXIT);

    //bottoni
    addButton->Bind(wxEVT_BUTTON, &MainFrame::OnAdd, this);
    editButton->Bind(wxEVT_BUTTON, &MainFrame::OnEdit, this);
    toggleButton->Bind(wxEVT_BUTTON, &MainFrame::OnToggle, this);
    removeButton->Bind(wxEVT_BUTTON, &MainFrame::OnRemove, this);
    quitButton->Bind(wxEVT_BUTTON, &MainFrame::OnQuit, this);

    this->Centre();
    update(); //aggiorna la grafica iniziale con i dati della lista (che è vuota all'inizio)
}

//funzione chiamata quando la lista notifica un cambiamento (tramite notify()) per aggiornare la grafica
void MainFrame::update() {
    //ogni volta che la lista cambia, la grafica vecchia viene eliminata e ricostruita da capo
    //grafica vecchia svuotata
    listView->DeleteAllItems();
    const auto& items = list.getItems();

    //ricostruzione grafica con i dati aggiornati
    for (int i = 0; i < items.size(); ++i) {
        const auto& item = items[i];

        //inserimento dati nella lista grafica
        listView->InsertItem(i, item.getName());
        listView->SetItem(i, 1, std::to_string(item.getQuantity()));
        listView->SetItem(i, 2, item.getCategory());
        listView->SetItem(i, 3, wxString::Format("%.2f €", item.getPrice()));

        //se è comprato, la colonna "Stato" diventa "PRESO" e il testo diventa verde. Altrimenti, "Da prendere" e testo nero
        if (item.isPurchased()) {
            listView->SetItem(i, 4, "PRESO");
            listView->SetItemTextColour(i, *wxLIGHT_GREY); //diventa verde
        } else {
            listView->SetItem(i, 4, "Da prendere");
            listView->SetItemTextColour(i, *wxBLACK);
        }
    }

    //aggiornamento del totale
    double total = list.getTotalCost(); //calcola il totale della lista (tutti gli elementi, anche quelli acquistati)
    totalText->SetLabel(wxString::Format("Totale Lista: %.2f €", total));

    //forzo il ridisegno della finestra per aggiornare la grafica
    totalText->GetParent()->Layout();
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

void MainFrame::OnSave(wxCommandEvent& event) {
    //apre una finestra "Salva con nome"
    wxFileDialog saveFileDialog(this, "Salva lista spesa", "", "spesa.csv",
                                "File CSV (*.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return; //l'utente ha annullato l'operazione

    //recupera il percorso scelto e salva
    if (!list.saveToFile(saveFileDialog.GetPath().ToStdString())) {
        wxLogError("Impossibile salvare il file!");
    }
}

void MainFrame::OnLoad(wxCommandEvent& event) {
    //apre una finestra "Apri file"
    wxFileDialog openFileDialog(this, "Apri lista spesa", "", "",
                                "File CSV (*.csv)|*.csv", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    //carica il file
    if (!list.loadFromFile(openFileDialog.GetPath().ToStdString())) {
        wxLogError("Impossibile caricare il file! Forse il formato è errato.");
    }
}