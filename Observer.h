/*
* Interfaccia dell'osservatore. Il soggetto (Subject) notifica l'osservatore (Observer) quando si verificano eventi di interesse, consentendo all'osservatore di reagire di conseguenza.
 */

#ifndef LISTASPESA_OBSERVER_H
#define LISTASPESA_OBSERVER_H

class Observer {
public:
 //distruttore virtuale per garantire la corretta distruzione degli oggetti derivati
 virtual ~Observer() = default;

 //metodo chiamato quando il Subject notifica l'osservatore di un evento. Da implementare nelle classi concrete che ereditano da Observer
 virtual void update() = 0;
};

#endif //LISTASPESA_OBSERVER_H