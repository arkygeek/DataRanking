/***************************************************************************
 *   File:  madserialise.h created: 08/01/2014                             *
 *   Class info: MADSerialise                                              *
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


    adapted from code used in Landuse Analyst (C) 2006 by Jason Jorgenson
    and originally contributed by Tim Sutton as per below:

                          LaSerialisable.h  -  description
                             -------------------
    begin                : March 2006
    copyright            : (C) 2003 by Tim Sutton
    email                : tim@linfiniti.com
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MADSERIALISE_H
#define MADSERIALISE_H


class QString;
#include <QFile>

/**
  * An abstract base class for any class that is serialiseable
  */

class MadSerialise
{
public:
  /**
    * @brief MadSerialise Constructor
    */
  MadSerialise();

  /**
    * @brief toXml
    * Write this object to xml and return result as qstring (virtual)
    * @return
    */
  virtual QString toJson()=0;

  /**
    * @brief toJsonFile writes object to Json and return result (virtual qstring)
    * We provide a basic default implementation where given a file name,
    * we will write the serialised json to that file.
    * Internally it uses toJson() method so that must be properly implemented.
    * @see toJson()
    * @param theFileName
    * @return QString (virtual)
    */
  virtual bool toJsonFile(const QString theFileName);

  /**
    * @brief fromXml Read this object from xml
    * @param theXml
    * @return result as true for success, false for failure (virtual)
    */
  virtual bool fromJson(const QString theXml)=0;

  /**
    * @brief fromXmlFile Read this object from xml in a file
    * @see fromXmlFile()
    * Internally it uses fromXml(QString) so that must be properly implemented
    * @param theFileName
    * @return result as true for success, false for failure.
    */
  virtual bool fromJsonFile(const QString theFileName);
};


#endif // MADSERIALISE_H
