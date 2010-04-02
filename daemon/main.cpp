/*
    This file is part of the Cagibi daemon, part of the KDE project.

    Copyright 2009 Friedrich W. H. Kossebau <kossebau@kde.org>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy 
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// program
#include "upnpproxy.h"
// lib
#include "ssdpwatcher.h"
// Qt
#include <QtDBus/QDBusConnection>
#include <QtCore/QCoreApplication>


int main( int argc, char* argv[] )
{
    QCoreApplication programCore( argc, argv );

    Cagibi::SSDPWatcher deviceBrowser;
    deviceBrowser.discover();

    new Cagibi::UPnPProxy();
//     QDBusConnection connection = QDBusConnection::sessionBus();
//     connection.registerObject("/Car", car);
//     connection.registerService( "org.kde.Cagibi" );

    const int result = programCore.exec();

    return result;
}
