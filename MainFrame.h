#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include "Observer.h"
#include "ShoppingList.h"

//eredita da wxFrame per la finestra principale e da Observer per ricevere notifiche di cambiamento della lista
class MainFrame : public wxFrame, public Observer {
private:
    ShoppingList& list; // Riferimento alla lista logica

    //elementi grafici
    wxListView* listView;
    wxButton* addButton;
    wxButton* removeButton;

    //metodi per gli eventi
    void OnAdd(wxCommandEvent& event);
    void OnRemove(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);

public:
    //costruttore
    MainFrame(const wxString& title, ShoppingList& list);

    //metodo dell'Observer per aggiornare la vista quando la lista cambia
    void update() override;
};

#endif // MAINFRAME_H