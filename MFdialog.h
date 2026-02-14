/*
 * Classe che gestisce una finestra pop up per l'aggiunta o la modifica di un elemento della lista della spesa.
 */

#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <wx/wx.h>
#include "ShoppingItem.h"

//dialogo per creare o modificare un oggetto
class EditDialog : public wxDialog {
private:
    //controlli grafici per l'input dell'utente
    wxTextCtrl* nameInput;
    wxTextCtrl* quantityInput;
    wxTextCtrl* categoryInput;
    wxTextCtrl* priceInput;

    //variabili per i dati inseriti
    wxString name;
    int quantity;
    wxString category;
    double price;

public:
    //costruttore
    EditDialog(wxWindow* parent, const wxString& title,
               const wxString& defaultName = "",
               int defaultQty = 1,
               const wxString& defaultCat = "Generale",
               double defaultPrice = 0.0);

    //getters per i dati inseriti
    wxString getName() const { return name; }
    int getQuantity() const { return quantity; }
    wxString getCategory() const { return category; }
    double getPrice() const { return price; }

    //metodo per gestire l'evento di conferma (OK)
    void OnOK(wxCommandEvent& event);
};

#endif // EDITDIALOG_H