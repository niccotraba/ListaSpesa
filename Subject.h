/*
 * Interfaccia dei Subjects.
 * Gestisce i soggetti osservati dagli oberver fornendo i metodi per aggiungere, rimuovere e notificare gli osservatori.
 */


#ifndef LISTASPESA_SUBJECT_H
#define LISTASPESA_SUBJECT_H

#include "Observer.h"
#include <vector>
#include <algorithm> //per std::remove

class Subject {
    protected:
        std::vector <Observer*> observers_;
    public:
    //distrutture virtuale
    virtual ~Subject() = default;

    //metodo per registrare un nuovo osservatore
    void addObserver (Observer* observer) {
        if (observer != nullptr) {
            //controllo per evitare duplicati
            auto it = std::find(observers_.begin(), observers_.end(), observer);
            if (it == observers_.end()) {
                observers_.push_back(observer);
            }
        }
    }

    //metodo per rimuovere un osservatore dalla lista degli osservatori: utilizzo dell'idioma "erase-remove"
    void removeObserver (Observer* observer) {
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
    }

    //metodo per notificare gli osservatore. E' protetto perché solo le classi derivate devono poterlo chiamare.
    //Il metodo è chiamato dalle classi derivate ogni volta che lo stato interno cambia.
protected:
    void notify() {
        for (Observer* observer : observers_) {
            if (observer != nullptr) {
                observer->update();
            }
        }
    }
};
#endif //LISTASPESA_SUBJECT_H