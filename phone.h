#ifndef PHONE_H
#define PHONE_H

#include <QString>
#include <QList>

class Phone
{
public:
    Phone();
    ~Phone();

    void AddNextPhone(Phone * nextPhone);

private:
    QString *_name = nullptr;

    /* 1*/ bool _os; // true - IOS, false - android
    /* 2*/ bool _year;
    /* 3*/ bool _cores;
    /* 4*/ bool _cameras; // true - double, false - single
    /* 5*/ bool _cameraMegapixels;
    /* 6*/ bool _sims;
    /* 7*/ bool _memoryCard;
    /* 8*/ bool _waterproof;
    /* 9*/ bool _nfc;
    /*10*/ bool _fastCharge;

    QList<Phone *> *_nextPhones = nullptr;
};

#endif // PHONE_H
