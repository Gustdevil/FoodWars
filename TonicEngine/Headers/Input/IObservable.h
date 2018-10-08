//
// Created by svanr on 10/4/2018.
//

#ifndef PROJECT_SWA_IOBSERVABLE_H
#define PROJECT_SWA_IOBSERVABLE_H

#include <iostream>
#include "IObserver.h"
#include "../Events/IEvent.h"

class IObservable {
public:
    IObservable() {

    }
    virtual void registerObserver(IObserver& iObserver) = 0;
    virtual void notify(IEvent keyEvent) = 0;
};

#endif //PROJECT_SWA_IOBSERVABLE_H
