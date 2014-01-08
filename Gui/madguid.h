/***************************************************************************
 *   File:  madguid.h created: 08/01/2014                                    *
 *   Class info: MADGuid                                               *
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

#ifndef MADGUID_H
#define MADGUID_H
#include <QString>
/**
  * An abstract base class for any class that has a globally unique
  * identifier (GUID) to represent a unique instance.
  * original @author: Tim Sutton
  * adapted by @author: Jason Jorgenson
  */

class MADGuid
{
public:
  /** Constructor . */
  MADGuid();

  /** Destructor . */
  virtual ~MADGuid();

  /** Retrieve the globally unique identifier */
  QString guid() const;

  /** Set the globally unique identifier for this object.
   *  If no Parameter is passed a guid will be self assigned
   *  @param theGuid - a guid for this dataset ranking form
   */
  void setGuid(QString theGuid="");

private:
  /** A globally unique identifier for this dataset ranking form*/
  QString mGuid;
};


#endif // MADGUID_H
