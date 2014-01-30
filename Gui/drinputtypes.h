/***************************************************************************
 *   File:  drinputtypes.h created: 22/01/2014                                    *
 *   Class info: DrInputTypes                                               *
 *   Copyright (C) 2013 by: Jason S. Jorgenson                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef DRINPUTTYPES_H
#define DRINPUTTYPES_H

class DrInputTypes
{
public:
  DrInputTypes();
  ~DrInputTypes();

  // accessors
  bool minData() const;
  int weight() const;
  //double
  //mutators
  void setMinData(bool theMinDataBool);
  void setWeight(int theWeightInt);

private:
  bool mMinData;
  int mWeight;
};

#endif // DRINPUTTYPES_H
