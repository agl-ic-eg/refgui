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

#include "IC_DataPool.h"

IC_DataPool::IC_DataPool(QObject *parent) : QObject(parent)
{
    init();
}

void IC_DataPool::init()
{
    TurnR = false;
    TurnL = false;
    Brake = false;
    Seatbelt = false;
    Highbeam = false;
    Door = false;
    Eps = false;
    SrsAirbag = false;
    Abs = false;
    LowBattery = false;
    Immobi = false;
    EspAct = false;
    EspOff = false;
    HillDescent = false;
    GeneralWarn = false;
    GearAtVal = 1; // IC_HMI_AT_PARKING(1)
    SpAnalogVal = 0;
    TaAnalogVal = 0;
    OTempVal = 0;
    CruRangeVal = 0;
}

#define EMIT_SIGNAL(DATA, V)	if(DATA != V){DATA = V;emit signal##DATA(V);}

void IC_DataPool::WriteTurnR(bool on_off)
{
	EMIT_SIGNAL(TurnR, on_off);
}

void IC_DataPool::WriteTurnL(bool on_off)
{
	EMIT_SIGNAL(TurnL, on_off);
}

void IC_DataPool::WriteBrake(bool on_off)
{
	EMIT_SIGNAL(Brake, on_off);
}

void IC_DataPool::WriteSeatbelt(bool on_off)
{
	EMIT_SIGNAL(Seatbelt, on_off);
}

void IC_DataPool::WriteHighbeam(bool on_off)
{
	EMIT_SIGNAL(Highbeam, on_off);
}

void IC_DataPool::WriteDoor(bool on_off){
	EMIT_SIGNAL(Door, on_off);
}

void IC_DataPool::WriteEps(bool on_off)
{
	EMIT_SIGNAL(Eps, on_off);
}

void IC_DataPool::WriteSrsAirbag(bool on_off)
{
	EMIT_SIGNAL(SrsAirbag, on_off);
}

void IC_DataPool::WriteAbs(bool on_off)
{
	EMIT_SIGNAL(Abs, on_off);
}

void IC_DataPool::WriteLowBattery(bool on_off)
{
	EMIT_SIGNAL(LowBattery, on_off);
}

void IC_DataPool::WriteImmobi(bool on_off)
{
	EMIT_SIGNAL(Immobi, on_off);
}

void IC_DataPool::WriteEspAct(bool on_off)
{
	EMIT_SIGNAL(EspAct, on_off);
}

void IC_DataPool::WriteEspOff(bool on_off)
{
	EMIT_SIGNAL(EspOff, on_off);
}

void IC_DataPool::WriteHillDescent(bool on_off)
{
	EMIT_SIGNAL(HillDescent, on_off);
}

void IC_DataPool::WriteGeneralWarn(bool on_off)
{
	EMIT_SIGNAL(GeneralWarn, on_off);
}

void IC_DataPool::WriteGearAtVal(int pos)
{
	EMIT_SIGNAL(GearAtVal, pos);
}

void IC_DataPool::WriteSpAnalogVal(unsigned long speed)
{
	EMIT_SIGNAL(SpAnalogVal, speed);
}

void IC_DataPool::WriteTaAnalogVal(unsigned long rpm)
{
	EMIT_SIGNAL(TaAnalogVal, rpm);
}

void IC_DataPool::WriteOTempVal(signed short temp)
{
	EMIT_SIGNAL(OTempVal, temp);
}

void IC_DataPool::WriteCruRangeVal(unsigned short range)
{
	EMIT_SIGNAL(CruRangeVal, range);
}

