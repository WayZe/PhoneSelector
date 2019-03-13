#ifndef PHONE_H
#define PHONE_H

#include <QString>

class Phone
{
public:
    Phone();

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
};

#endif // PHONE_H
