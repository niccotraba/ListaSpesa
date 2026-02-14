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
    bool isUpdating; //flag per evitare aggiornamenti ricorsivi durante la modifica della lista

    //elementi grafici
    wxListView* listView;
    wxButton* addButton;
    wxButton* editButton;
    wxButton* removeButton;

    wxStaticText* totalText; //testo per visualizzare il totale


    //metodi per gli eventi
    void OnAdd(wxCommandEvent& event); //per aggiungere prodotto
    void OnRemove(wxCommandEvent& event); //per rimuovere prodotto
    void OnEdit(wxCommandEvent& event); //per modificare prodotto
    void OnQuit(wxCommandEvent& event); //per uscire dall'app
    void OnSave(wxCommandEvent& event); //per salvare la lista su file
    void OnLoad(wxCommandEvent& event); //per caricare la lista da un file
    void OnListCheck(wxListEvent& event); //per gestire il toggle dello stato di acquisto (preso/da prendere) tramite checkbox nella lista

public:
    //costruttore
    MainFrame(const wxString& title, ShoppingList& list);

    //metodo dell'Observer per aggiornare la vista quando la lista cambia
    void update() override;
};

#endif // MAINFRAME_H