/*
    SOSCO, Wheeled Mobile Robot(WMR)
    Copyright (C) 2016  Alireza Hosseini

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BASICUTILS_H
#define BASICUTILS_H

#include <QByteArray>


typedef unsigned char byte;

class Conversions {

public:
    static char* floatToByteArray(float value) {
        union {
            float floatValue;
            char raw8bitData[4];
        }u;
        u.floatValue = value;
    return u.raw8bitData;
}

};

#endif // BASICUTILS_H
