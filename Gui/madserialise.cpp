/***************************************************************************
 *   File:  madserialise.cpp created: 08/01/2014                                    *
 *   Class info: MADSerialise                                               *
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

                          LaSerialisable.cpp  -  description
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

//Local includes
#include "MadSerialise.h"

//Qt includes
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDebug>

MadSerialise::MadSerialise()
{
}

bool MadSerialise::toJsonFile(const QString theFileName)
{
  bool myResult = false;
  QFile myFile( theFileName );
  if ( myFile.open( QIODevice::WriteOnly ) )
  {
    QTextStream myQTextStream( &myFile );
    myQTextStream << this->toJson();
    myFile.close();
    myResult=true;
  }
  else
  {
    //@TODO Error handler!
    myResult=false;
  }
  return myResult ;
}

bool MadSerialise::fromJsonFile(const QString theFileName)
{
  bool myResult = false;
  QFile myFile( theFileName );
  if ( myFile.open( QIODevice::ReadOnly ) )
  {
    myResult=this->fromJson(myFile.readAll());
    myFile.close();
  }
  else
  {
    //@TODO Error handler!
    myResult=false;
  }
  return myResult ;
}


