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

#ifndef DEVICE_P_H
#define DEVICE_P_H

// lib
#include "icon.h"
#include "service.h"
#include "device.h"
// Qt
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QSharedData>


namespace Cagibi
{

class DevicePrivate : public QSharedData
{
  friend const QDBusArgument& ::operator>>( const QDBusArgument& argument,
                                            Cagibi::Device& device );

  public:
    static const char* const keys[];
    enum { Type=0, FriendlyName, Manufacturer, ModelDescription, ModelName, ModelNumber, SerialNumber, UDN, PresentationUrl, KeyCount };

    static bool isKey( const QString& key );

  public:
    DevicePrivate();

  public:
    const QString& type() const;
    const QString& friendlyName() const;
    const QString& manufacturerName() const;
//     const QString& manufacturerUrl() const;
    const QString& modelDescription() const;
    const QString& modelName() const;
    const QString& modelNumber() const;
    const QString& serialNumber() const;
    const QString& udn() const;
//     const QString upc() const;
    const QString& presentationUrl() const;

    const QList<Icon>& icons() const;
    const QList<Service>& services() const;
    const QList<Device>& devices() const;

    bool hasParentDevice() const;
    Device parentDevice() const;

    RootDevice* rootDevice() const;

  public:
    void setProperty( const QString& key, const QString& value );
    void setParentDevicePrivate( DevicePrivate* parentDevicePrivate );
    void setRootDevice( RootDevice* rootDevice );

    void addDevice( const Device& device );
    void addService( const Service& service );
    void addIcon( const Icon& icon );

  protected:
    QString mType;
    /// short user-friendly title
    QString mFriendlyName;
    QString mManufacturerName;
//     QString mManufacturerUrl;
    /// long user-friendly title
    QString mModelDescription;
    QString mModelName;
    QString mModelNumber;
    QString mSerialNumber;
    QString mUdn;
//     QString mUpc; Universal Product Code;
    QString mPresentationUrl;

    QList<Icon> mIcons;
    QList<Service> mServices;
    QList<Device> mDevices;

    DevicePrivate* mParentDevicePrivate;
    RootDevice* mRootDevice;
};


inline DevicePrivate::DevicePrivate() : mParentDevicePrivate( 0 ), mRootDevice( 0 ) {}
inline const QString& DevicePrivate::type() const { return mType; }
inline const QString& DevicePrivate::friendlyName() const { return mFriendlyName; }
inline const QString& DevicePrivate::manufacturerName() const { return mManufacturerName; }
inline const QString& DevicePrivate::modelDescription() const { return mModelDescription; }
inline const QString& DevicePrivate::modelName() const { return mModelName; }
inline const QString& DevicePrivate::modelNumber() const { return mModelNumber; }
inline const QString& DevicePrivate::serialNumber() const { return mSerialNumber; }
inline const QString& DevicePrivate::udn() const { return mUdn; }
inline const QString& DevicePrivate::presentationUrl() const { return mPresentationUrl; }
inline const QList<Icon>& DevicePrivate::icons() const { return mIcons; }
inline const QList<Service>& DevicePrivate::services() const { return mServices; }
inline const QList<Device>& DevicePrivate::devices() const { return mDevices; }
inline bool DevicePrivate::hasParentDevice() const { return (mParentDevicePrivate != 0); }
inline Device DevicePrivate::parentDevice() const
{
    return mParentDevicePrivate ? Device(mParentDevicePrivate) : Device();
}
inline RootDevice* DevicePrivate::rootDevice() const { return mRootDevice; }

inline void DevicePrivate::setProperty( const QString& key, const QString& value )
{
    if( key == keys[Type] )
        mType = value;
    else if( key == keys[FriendlyName] )
        mFriendlyName = value;
    else if( key == keys[Manufacturer] )
        mManufacturerName = value;
    else if( key == keys[ModelDescription] )
        mModelDescription = value;
    else if( key == keys[ModelName] )
        mModelName = value;
    else if( key == keys[ModelNumber] )
        mModelNumber = value;
    else if( key == keys[SerialNumber] )
        mSerialNumber = value;
    else if( key == keys[UDN] )
        mUdn = value;
    else if( key == keys[PresentationUrl] )
        mPresentationUrl = value;
}
inline void DevicePrivate::setParentDevicePrivate( DevicePrivate* parentDevicePrivate )
{
    mParentDevicePrivate = parentDevicePrivate;
}
inline void DevicePrivate::setRootDevice( RootDevice* rootDevice )
{
    mRootDevice = rootDevice;
}


inline bool DevicePrivate::isKey( const QString& key )
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
