/*
 * Implementazione della classe MFdialog, che rappresenta la finestra di dialogo per la gestione della lista della spesa
 * La classe fornisce un'interfaccia per inserire o modificare i dettagli di un elemento della lista, come nome, quantità, categoria e prezzo.
 */

#include "MFdialog.h"

EditDialog::EditDialog(wxWindow* parent, const wxString& title,
                       const wxString& defaultName, int defaultQty,
                       const wxString& defaultCat, double defaultPrice)
    : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(300, 250)) {

    //sizer principale verticale
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    //griglia per i campi di input (2 colonne: etichetta + campo di input)
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 5, 5); // 2 col, 5px gap

    //nome
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Nome:"), 0, wxALIGN_CENTER_VERTICAL);
    nameInput = new wxTextCtrl(this, wxID_ANY, defaultName);
    gridSizer->Add(nameInput, 1, wxEXPAND);

    //quantità
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Quantità:"), 0, wxALIGN_CENTER_VERTICAL);
    quantityInput = new wxTextCtrl(this, wxID_ANY, wxString::Format("%d", defaultQty));
    gridSizer->Add(quantityInput, 1, wxEXPAND);

    //categoria
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Categoria:"), 0, wxALIGN_CENTER_VERTICAL);
    categoryInput = new wxTextCtrl(this, wxID_ANY, defaultCat);
    gridSizer->Add(categoryInput, 1, wxEXPAND);

    //prezzo
    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Prezzo (€):"), 0, wxALIGN_CENTER_VERTICAL);
    priceInput = new wxTextCtrl(this, wxID_ANY, wxString::Format("%.2f", defaultPrice));
    gridSizer->Add(priceInput, 1, wxEXPAND);

    //aggiunta griglia al main
    gridSizer->AddGrowableCol(1, 1); //la seconda colonna (input) si espande
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxALL, 15);

    //bottoni OK/Annulla standard
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    //binding manuale del tasto OK per validare i dati
    Bind(wxEVT_BUTTON, &EditDialog::OnOK, this, wxID_OK);

    SetSizer(mainSizer);
}

void EditDialog::OnOK(wxCommandEvent& event) {
    //validazione nome
    if (nameInput->GetValue().IsEmpty()) {
        wxMessageBox("Il nome non può essere vuoto!", "Errore", wxOK | wxICON_ERROR);
        return;
    }

    //conversione e salvataggoio dati
    name = nameInput->GetValue();
    category = categoryInput->GetValue();

    //gestione errori numerici
    long q;
    if (!quantityInput->GetValue().ToLong(&q) || q <= 0) {
        wxMessageBox("Quantità non valida!", "Errore", wxOK | wxICON_ERROR);
        return;
    }
    quantity = (int)q;

    if (!priceInput->GetValue().ToDouble(&price) || price < 0) {
        wxMessageBox("Prezzo non valido!", "Errore", wxOK | wxICON_ERROR);
        return;
    }

    //se tutto valido, chiudi il dialogo con OK
    EndModal(wxID_OK);
}