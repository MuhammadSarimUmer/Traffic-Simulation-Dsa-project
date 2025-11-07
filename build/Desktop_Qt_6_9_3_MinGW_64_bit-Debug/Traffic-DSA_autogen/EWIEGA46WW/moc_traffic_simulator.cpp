/****************************************************************************
** Meta object code from reading C++ file 'traffic_simulator.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../traffic_simulator.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'traffic_simulator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16TrafficSimulatorE_t {};
} // unnamed namespace

template <> constexpr inline auto TrafficSimulator::qt_create_metaobjectdata<qt_meta_tag_ZN16TrafficSimulatorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "TrafficSimulator",
        "vehiclesUpdated",
        "",
        "QList<Vehicle>",
        "vehicles",
        "trafficLightsUpdated",
        "QList<TrafficLight>",
        "lights",
        "edgeCongestionUpdated",
        "from",
        "to",
        "status",
        "congestionAlert",
        "message",
        "updateSimulation",
        "updateCongestion"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'vehiclesUpdated'
        QtMocHelpers::SignalData<void(const QVector<Vehicle> &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'trafficLightsUpdated'
        QtMocHelpers::SignalData<void(const QVector<TrafficLight> &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'edgeCongestionUpdated'
        QtMocHelpers::SignalData<void(qint64, qint64, const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 9 }, { QMetaType::LongLong, 10 }, { QMetaType::QString, 11 },
        }}),
        // Signal 'congestionAlert'
        QtMocHelpers::SignalData<void(const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Slot 'updateSimulation'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updateCongestion'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<TrafficSimulator, qt_meta_tag_ZN16TrafficSimulatorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject TrafficSimulator::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16TrafficSimulatorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16TrafficSimulatorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16TrafficSimulatorE_t>.metaTypes,
    nullptr
} };

void TrafficSimulator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<TrafficSimulator *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->vehiclesUpdated((*reinterpret_cast< std::add_pointer_t<QList<Vehicle>>>(_a[1]))); break;
        case 1: _t->trafficLightsUpdated((*reinterpret_cast< std::add_pointer_t<QList<TrafficLight>>>(_a[1]))); break;
        case 2: _t->edgeCongestionUpdated((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 3: _t->congestionAlert((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->updateSimulation(); break;
        case 5: _t->updateCongestion(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (TrafficSimulator::*)(const QVector<Vehicle> & )>(_a, &TrafficSimulator::vehiclesUpdated, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (TrafficSimulator::*)(const QVector<TrafficLight> & )>(_a, &TrafficSimulator::trafficLightsUpdated, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (TrafficSimulator::*)(qint64 , qint64 , const QString & )>(_a, &TrafficSimulator::edgeCongestionUpdated, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (TrafficSimulator::*)(const QString & )>(_a, &TrafficSimulator::congestionAlert, 3))
            return;
    }
}

const QMetaObject *TrafficSimulator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrafficSimulator::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16TrafficSimulatorE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int TrafficSimulator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TrafficSimulator::vehiclesUpdated(const QVector<Vehicle> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void TrafficSimulator::trafficLightsUpdated(const QVector<TrafficLight> & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void TrafficSimulator::edgeCongestionUpdated(qint64 _t1, qint64 _t2, const QString & _t3)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1, _t2, _t3);
}

// SIGNAL 3
void TrafficSimulator::congestionAlert(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}
QT_WARNING_POP
