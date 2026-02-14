#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Observer.h"
#include "ShoppingList.h"

//eredita da wxFrame per la finestra principale e da Observer per ricevere notifiche di cambiamento della lista
class MainFrame : public wxFrame, public Observer {
private:
    ShoppingList& list; //riferimento alla lista logica

    //elementi grafici
    wxListView* listView;
    wxButton* addButton;
    wxButton* editButton;
    wxButton* toggleButton;
    wxButton* removeButton;

    wxStaticText* totalText; //testo per visualizzare il totale


    //metodi per gli eventi
    void OnAdd(wxCommandEvent& event); //per aggiungere prodotto
    void OnRemove(wxCommandEvent& event); //per rimuovere prodotto
    void OnEdit(wxCommandEvent& event); //per modificare prodotto
    void OnToggle(wxCommandEvent& event); //per modificare lo stato di acquisto
    void OnQuit(wxCommandEvent& event); //per uscire dall'app
    void OnSave(wxCommandEvent& event); //per salvare la lista su file
    void OnLoad(wxCommandEvent& event); //per caricare la lista da un file

public:
    //costruttore
    MainFrame(const wxString& title, ShoppingList& list);

    //metodo dell'Observer per aggiornare la vista quando la lista cambia
    void update() override;
};

#endif // MAINFRAME_H