#include "phone.h"

Phone::Phone()
{
    _nextPhones = new QList<Phone *>();
}

Phone::~Phone()
{
    if (_nextPhones)
    {
        foreach (Phone *nextPhone, *_nextPhones)
        {
            delete nextPhone;
            nextPhone = nullptr;
        }
        _nextPhones->clear();
        delete _nextPhones;
        _nextPhones = nullptr;
    }
}

void Phone::AddNextPhone(Phone *nextPhone)
{
    _nextPhones->append(nextPhone);
}
