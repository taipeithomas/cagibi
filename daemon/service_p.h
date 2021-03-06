/*
    This file is part of the Cagibi daemon.

    Copyright 2009-2010 Friedrich W. H. Kossebau <kossebau@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SERVICE_P_H
#define SERVICE_P_H

// lib
#include "device_p.h"
// Qt
#include <QtCore/QString>
#include <QtCore/QSharedData>


namespace Cagibi
{

class ServicePrivate : public QSharedData
{
  public:
    static const char* const keys[];
    enum { Type=0, ControlUrl, EventSubUrl, SCPDUrl, ServiceId, KeyCount };

    static bool isKey( const QString& key );

  public:
    ServicePrivate();

  public:
    const QString& type() const;
    const QString& id() const;
    const QString& descriptionUrl() const;
    const QString& controlUrl() const;
    const QString& eventSubUrl() const;
    bool isReady() const;
    Device device() const;

  public:
    void setProperty( const QString& key, const QString& value );
    void setReady();
    void setDevicePrivate( DevicePrivate* parentDevicePrivate );

  protected:
    QString mType;
    QString mId;
    QString mDescriptionUrl;
    QString mControlUrl;
    QString mEventSubUrl;

    bool mReady;
    DevicePrivate* mDevicePrivate;
};


inline ServicePrivate::ServicePrivate()
  : mReady( false ),
    mDevicePrivate( 0 )
{
}

inline const QString& ServicePrivate::type()       const { return mType; }
inline const QString& ServicePrivate::id() const { return mId; }
inline const QString& ServicePrivate::descriptionUrl() const { return mDescriptionUrl; }
inline const QString& ServicePrivate::controlUrl() const { return mControlUrl; }
inline const QString& ServicePrivate::eventSubUrl() const { return mEventSubUrl; }
inline bool ServicePrivate::isReady()              const { return mReady; }
inline Device ServicePrivate::device() const
{
    return mDevicePrivate ? Device(mDevicePrivate) : Device();
}

inline void ServicePrivate::setReady() { mReady = true; }

inline void ServicePrivate::setProperty( const QString& key, const QString& value )
{
    if( key == keys[Type] )
        mType = value;
    else if( key == keys[ControlUrl] )
        mControlUrl = value;
    else if( key == keys[EventSubUrl] )
        mEventSubUrl = value;
    else if( key == keys[SCPDUrl] )
        mDescriptionUrl = value;
    else if( key == keys[ServiceId] )
        mId = value;
}
inline void ServicePrivate::setDevicePrivate( DevicePrivate* devicePrivate )
{
    mDevicePrivate = devicePrivate;
}


inline bool ServicePrivate::isKey( const QString& key )
{
    bool result = false;

    for( int i=0; i<KeyCount; ++i )
        if( key == QLatin1String(keys[i]) )
        {
            result = true;
            break;
        }

    return result;
}

}

#endif
