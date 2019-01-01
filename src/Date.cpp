#include <cstring>
#include "interface.h"

enum compareResult {
    BIG, SMALL, EQUAL
};

void checkIfTheDateLegal(string date);

/**
 *
 * Constructor for Date Class
 *
 * @param date the string date.
 */
Date::Date(string date) {
    checkIfTheDateLegal(date);
    this->date = date;
}

/**
 * The function check if the date is a legal date.
 *
 * @param date the string date.
 */
void checkIfTheDateLegal(string date) {
    string subS = "";
    string temp = date;
    subS = date.substr(0, 4);
    temp = date.substr(5, date.size());
    bool flag = false;
    if (subS > "9999") {
        flag = true;
    }
    subS = temp.substr(0, 2);
    if (subS > "12") {
        flag = true;
    }
    temp = temp.substr(3, temp.size());
    subS = temp.substr(0, temp.size());
    if (subS > "31") {
        flag = true;
    }
    if (flag) {
        throw "The date are illegal";
    }
}

/**
 * The function compare two date string.
 *
 * @param dateOne date one.
 * @param dateTwo date two.
 * @return compareResult { SMALL , BIG , EQUAL}
 */
compareResult compareDate(string dateOne, string dateTwo) {
    string tempStringOne;
    string tempStringTow;
    tempStringOne = dateOne.substr(0, 4);
    tempStringTow = dateTwo.substr(0, 4);
    int temp = tempStringOne.compare(tempStringTow);
    // Check the year
    if (temp == -1) {
        return SMALL;
    } else if (temp == 1) {
        return BIG;
    }
    // Check the date and the month.
    for (int i = 5; i < 9; i += 3) {
        tempStringOne = dateOne.substr(i, i + 2);
        tempStringTow = dateTwo.substr(i, i + 2);
        temp = tempStringOne.compare(tempStringTow);
        if (temp == -1) {
            return SMALL;
        } else if (temp == 1) {
            return BIG;
        }
    }
    return EQUAL;
}

bool Date::operator<(const Date &d) const {
    int indication = compareDate(this->getDate(), d.getDate());
    if (indication == SMALL) {
        return true;
    }
    return false;
}

bool Date::operator>(const Date &d) const {
    int indication = compareDate(this->getDate(), d.getDate());
    if (indication == BIG) {
        return true;
    }
    return false;
}

bool Date::operator==(const Date &d) const {
    int indication = compareDate(this->getDate(), d.getDate());
    if (indication == EQUAL) {
        return true;
    }
    return false;
}