//
// Created by roy on 1/5/19.
//

#ifndef PROJECTPART2_ENTRY_H
#define PROJECTPART2_ENTRY_H

class Entry {
    int iValue, jValue;
public:
    Entry(int i, int j) {
        this->iValue = i;
        this->jValue = j;
    }

    int getI() {
        return this->iValue;
    }
    int getJ() {
        return this->jValue;
    }
};


#endif //PROJECTPART2_ENTRY_H
