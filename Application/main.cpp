/*
 * Copyright 2020,2021 Panasonic Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QDir>
#include <QQmlContext>
#include <QDebug>
#include <QThread>
#include <QTimer>

#include "IC_Receiver.h"

int main(int argc, char *argv[])
{
    QSurfaceFormat defaultFormat;
    defaultFormat.setSwapBehavior(QSurfaceFormat::TripleBuffer);
    defaultFormat.setRenderableType(QSurfaceFormat::OpenGLES);
    defaultFormat.setProfile(QSurfaceFormat::NoProfile);
    defaultFormat.setVersion(2,0);
    defaultFormat.setSwapInterval(1);
    defaultFormat.setDepthBufferSize(8);
    defaultFormat.setAlphaBufferSize(8);
    QSurfaceFormat::setDefaultFormat(defaultFormat);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("CurDirPath", QString(QCoreApplication::applicationDirPath()));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    //*****
    QObject *root = engine.rootObjects().first();
    IC_Receiver *receiver = new IC_Receiver();
    QThread *ic_client = new QThread();
    QTimer timer;

    QObject::connect(receiver, SIGNAL(signalTurnR(bool)), root, SLOT(slotTurnR(bool)));
    QObject::connect(receiver, SIGNAL(signalTurnL(bool)), root, SLOT(slotTurnL(bool)));
    QObject::connect(receiver, SIGNAL(signalBrake(bool)), root, SLOT(slotBrake(bool)));
    QObject::connect(receiver, SIGNAL(signalSeatbelt(bool)), root, SLOT(slotSeatbelt(bool)));
    QObject::connect(receiver, SIGNAL(signalHighbeam(bool)), root, SLOT(slotHighbeam(bool)));
    QObject::connect(receiver, SIGNAL(signalDoor(bool)), root, SLOT(slotDoor(bool)));
    QObject::connect(receiver, SIGNAL(signalEps(bool)), root, SLOT(slotEps(bool)));
    QObject::connect(receiver, SIGNAL(signalSrsAirbag(bool)), root, SLOT(slotSrsAirbag(bool)));
    QObject::connect(receiver, SIGNAL(signalAbs(bool)), root, SLOT(slotAbs(bool)));
    QObject::connect(receiver, SIGNAL(signalLowBattery(bool)), root, SLOT(slotLowBattery(bool)));
    QObject::connect(receiver, SIGNAL(signalImmobi(bool)), root, SLOT(slotImmobi(bool)));
    QObject::connect(receiver, SIGNAL(signalEspAct(bool)), root, SLOT(slotEspAct(bool)));
    QObject::connect(receiver, SIGNAL(signalEspOff(bool)), root, SLOT(slotEspOff(bool)));
    QObject::connect(receiver, SIGNAL(signalHillDescent(bool)), root, SLOT(slotHillDescent(bool)));
    QObject::connect(receiver, SIGNAL(signalGeneralWarn(bool)), root, SLOT(slotGeneralWarn(bool)));
    QObject::connect(receiver, SIGNAL(signalGearAtVal(int)), root, SLOT(slotGearAtVal(int)));
    QObject::connect(receiver, SIGNAL(signalSpAnalogVal(unsigned long)), root, SLOT(slotSpAnalogVal(unsigned long)));
    QObject::connect(receiver, SIGNAL(signalTaAnalogVal(unsigned long)), root, SLOT(slotTaAnalogVal(unsigned long)));
    QObject::connect(receiver, SIGNAL(signalOTempVal(signed short)), root, SLOT(slotOTempVal(signed short)));
    QObject::connect(receiver, SIGNAL(signalCruRangeVal(unsigned short)), root, SLOT(slotCruRangeVal(unsigned short)));

    QObject::connect(&timer,SIGNAL(timeout()), receiver, SLOT(receive()));
    timer.setInterval(10);

    receiver->moveToThread(ic_client);
    ic_client->start();
    timer.start();

    return app.exec();
}

