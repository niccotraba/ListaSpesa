#include <wx/wx.h>
#include "MainFrame.h"
#include "ShoppingList.h"

//classe che rappresenta il programma intero, gestisce l'inizializzazione e la creazione della finestra principale
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

//macro per implementare l'applicazione wxWidgets
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    //creazione la lista della spesa (il Modello)
    //'new' perché deve sopravvivere per tutta la durata dell'app
    ShoppingList* shoppingList = new ShoppingList("La Mia Spesa");

    //creazione finestra principale (la Vista)
    MainFrame* frame = new MainFrame("Lista Spesa C++", *shoppingList);

    //display della finestra
    frame->Show(true);

    return true;
}