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

#include "IC_Receiver.h"

extern "C"{
#include "cluster_api.h"
}

QString & IC_RException::message()
{
    return info;
}

IC_Receiver::IC_Receiver(QObject *parent) : IC_DataPool(parent)
{
    if(!clusterInit())
    {
        throw IC_RException("Cannot initialize cluster api.");
    }
}

IC_Receiver::~IC_Receiver()
{
    clusterTerm();
}

void IC_Receiver::receive(void)
{
    WriteTurnR((bool)getTurnR());
    WriteTurnL((bool)getTurnL());
    WriteBrake((bool)getBrake());
    WriteSeatbelt((bool)getSeatbelt());
    WriteHighbeam((bool)getHighbeam());
    WriteDoor((bool)getDoor());
    WriteEps((bool)getEps());
    WriteSrsAirbag((bool)getSrsAirbag());
    WriteAbs((bool)getAbs());
    WriteLowBattery((bool)getLowBattery());
    WriteImmobi((bool)getImmobi());
    WriteEspAct((bool)getEspAct());
    WriteEspOff((bool)getEspOff());
    WriteHillDescent((bool)getHillDescent());
    WriteGeneralWarn((bool)getGeneralWarn());
    WriteGearAtVal(getGearAtVal());
    WriteSpAnalogVal(getSpAnalogVal());
    WriteTaAnalogVal(getTaAnalogVal());
    WriteOTempVal(getOTempVal());
    WriteCruRangeVal(getCruRangeVal());
}

