//
// Created by roy on 1/5/19.
//

#ifndef PROJECTPART2_ENTRY_H
#define PROJECTPART2_ENTRY_H

/**
 * Class of matrix entry. has i and j values (coordinates in matrix).
 */
class Entry {
    int iValue, jValue;
public:
    /**
     * Constructor of the entry.
     * @param i row value.
     * @param j column value.
     */
    Entry(int i, int j) {
        this->iValue = i;
        this->jValue = j;
    }

    /**
     * This method returns the row value of the entry.
     * @return row value.
     */
    int getI() {
        return this->iValue;
    }

    /**
     * This method returns the column value of the entry.
     * @return column value.
     */
    int getJ() {
        return this->jValue;
    }

    /**
     * This method checks if a given entry is equal to the entry.
     * @param otherEntry other entry for the check.
     * @return true if equal, else false.
     */
    bool operator==(Entry otherEntry) {
        return this->iValue == otherEntry.getI() && this->jValue == otherEntry.getJ();
    }
};


#endif //PROJECTPART2_ENTRY_H
