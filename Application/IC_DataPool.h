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

#ifndef REFGUI_IC_DATAPOOL_H
#define REFGUI_IC_DATAPOOL_H

#include <QObject>

class IC_DataPool : public QObject
{
    Q_OBJECT
public:
    explicit IC_DataPool(QObject *parent = 0);
    void init();
    // Telltale
    void WriteTurnR(bool on_off);
    void WriteTurnL(bool on_off);
    void WriteBrake(bool on_off);
    void WriteSeatbelt(bool on_off);
    void WriteHighbeam(bool on_off);
    void WriteDoor(bool on_off);
    void WriteEps(bool on_off);
    void WriteSrsAirbag(bool on_off);
    void WriteAbs(bool on_off);
    void WriteLowBattery(bool on_off);
    void WriteImmobi(bool on_off);
    void WriteEspAct(bool on_off);
    void WriteEspOff(bool on_off);
    void WriteHillDescent(bool on_off);
    void WriteGeneralWarn(bool on_off);
    // Shift Position
    void WriteGearAtVal(int pos);
    // Speed
    void WriteSpAnalogVal(unsigned long speed);
    // Tacho
    void WriteTaAnalogVal(unsigned long rpm);
    // Trip
    void WriteOTempVal(signed short temp);
    void WriteCruRangeVal(unsigned short range);

signals:
    // Telltale
    void signalTurnR(bool on_off);
    void signalTurnL(bool on_off);
    void signalBrake(bool on_off);
    void signalSeatbelt(bool on_off);
    void signalHighbeam(bool on_off);
    void signalDoor(bool on_off);
    void signalEps(bool on_off);
    void signalSrsAirbag(bool on_off);
    void signalAbs(bool on_off);
    void signalLowBattery(bool on_off);
    void signalImmobi(bool on_off);
    void signalEspAct(bool on_off);
    void signalEspOff(bool on_off);
    void signalHillDescent(bool on_off);
    void signalGeneralWarn(bool on_off);
    // Shift Position
    void signalGearAtVal(int pos);
    // Speed
    void signalSpAnalogVal(unsigned long speed);
    // Tacho
    void signalTaAnalogVal(unsigned long rpm);
    // Trip
    void signalOTempVal(signed short temp);
    void signalCruRangeVal(unsigned short range);

private:
    bool TurnR;
    bool TurnL;
    bool Brake;
    bool Seatbelt;
    bool Highbeam;
    bool Door;
    bool Eps;
    bool SrsAirbag;
    bool Abs;
    bool LowBattery;
    bool Immobi;
    bool EspAct;
    bool EspOff;
    bool HillDescent;
    bool GeneralWarn;
    int GearAtVal;
    unsigned long SpAnalogVal;
    unsigned long TaAnalogVal;
    signed short OTempVal;
    unsigned short CruRangeVal;
};

#endif /* REFGUI_IC_DATAPOOL_H */

