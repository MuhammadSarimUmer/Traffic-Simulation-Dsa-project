/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "onLoadMapAreaClicked",
        "",
        "onMapDataLoaded",
        "data",
        "onMapLoadFailed",
        "error",
        "onFindPathClicked",
        "onClearPathClicked",
        "showDetailedRoute",
        "Graph::PathResult",
        "result",
        "onAreaSelected",
        "areaName",
        "onRerouteClicked",
        "onStartSimulationClicked",
        "onStopSimulationClicked",
        "onResetSimulationClicked",
        "onAddVehicleClicked",
        "onAddPriorityVehicleClicked",
        "onSimulationSpeedChanged",
        "value",
        "onAddJamClicked",
        "onVehiclesUpdated",
        "QList<TrafficSimulator::Vehicle>",
        "vehicles",
        "onTrafficLightsUpdated",
        "QList<TrafficSimulator::TrafficLight>",
        "lights",
        "onEdgeCongestionUpdated",
        "from",
        "to",
        "status",
        "onPathSourceChanged",
        "index",
        "onPathDestChanged",
        "on_actionBackToLogin_triggered",
        "on_actionChat_triggered"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'onLoadMapAreaClicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onMapDataLoaded'
        QtMocHelpers::SlotData<void(const QByteArray &)>(3, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QByteArray, 4 },
        }}),
        // Slot 'onMapLoadFailed'
        QtMocHelpers::SlotData<void(const QString &)>(5, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'onFindPathClicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onClearPathClicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showDetailedRoute'
        QtMocHelpers::SlotData<void(const Graph::PathResult &)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 10, 11 },
        }}),
        // Slot 'onAreaSelected'
        QtMocHelpers::SlotData<void(const QString &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Slot 'onRerouteClicked'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStartSimulationClicked'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onStopSimulationClicked'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onResetSimulationClicked'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddVehicleClicked'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddPriorityVehicleClicked'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSimulationSpeedChanged'
        QtMocHelpers::SlotData<void(int)>(20, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 21 },
        }}),
        // Slot 'onAddJamClicked'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onVehiclesUpdated'
        QtMocHelpers::SlotData<void(const QVector<TrafficSimulator::Vehicle> &)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Slot 'onTrafficLightsUpdated'
        QtMocHelpers::SlotData<void(const QVector<TrafficSimulator::TrafficLight> &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 27, 28 },
        }}),
        // Slot 'onEdgeCongestionUpdated'
        QtMocHelpers::SlotData<void(qint64, qint64, const QString &)>(29, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 30 }, { QMetaType::LongLong, 31 }, { QMetaType::QString, 32 },
        }}),
        // Slot 'onPathSourceChanged'
        QtMocHelpers::SlotData<void(int)>(33, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'onPathDestChanged'
        QtMocHelpers::SlotData<void(int)>(35, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 34 },
        }}),
        // Slot 'on_actionBackToLogin_triggered'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_actionChat_triggered'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->onLoadMapAreaClicked(); break;
        case 1: _t->onMapDataLoaded((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 2: _t->onMapLoadFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->onFindPathClicked(); break;
        case 4: _t->onClearPathClicked(); break;
        case 5: _t->showDetailedRoute((*reinterpret_cast< std::add_pointer_t<Graph::PathResult>>(_a[1]))); break;
        case 6: _t->onAreaSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->onRerouteClicked(); break;
        case 8: _t->onStartSimulationClicked(); break;
        case 9: _t->onStopSimulationClicked(); break;
        case 10: _t->onResetSimulationClicked(); break;
        case 11: _t->onAddVehicleClicked(); break;
        case 12: _t->onAddPriorityVehicleClicked(); break;
        case 13: _t->onSimulationSpeedChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 14: _t->onAddJamClicked(); break;
        case 15: _t->onVehiclesUpdated((*reinterpret_cast< std::add_pointer_t<QList<TrafficSimulator::Vehicle>>>(_a[1]))); break;
        case 16: _t->onTrafficLightsUpdated((*reinterpret_cast< std::add_pointer_t<QList<TrafficSimulator::TrafficLight>>>(_a[1]))); break;
        case 17: _t->onEdgeCongestionUpdated((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 18: _t->onPathSourceChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: _t->onPathDestChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 20: _t->on_actionBackToLogin_triggered(); break;
        case 21: _t->on_actionChat_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
