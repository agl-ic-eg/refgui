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

import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Scene3D 2.14

import "./FPSItem"
import "./ACC"
import "./CruisingRange"
import "./Header"
import "./Map"
import "./Menu"
import "./Meter"
import "./ShiftPosition"
import "./Telltale"
import "./TurnByTurn"


Window {
    id: winl
    visible: true
    width: 1920
    height: 720
    color: "black"
    flags: Qt.FramelessWindowHint
    maximumWidth: width
    maximumHeight: height
    /* SLOTS */
    function slotTurnR(on_off){
        if(on_off){
            header.turn_r_on.visible = true
            header.turn_r_off.visible = false
        }else{
            header.turn_r_on.visible = false
            header.turn_r_off.visible = true
        }
    }
    function slotTurnL(on_off){
        if(on_off){
            header.turn_l_on.visible = true
            header.turn_l_off.visible = false
        }else{
            header.turn_l_on.visible = false
            header.turn_l_off.visible = true
        }
    }
    function slotBrake(on_off){
        telltale.telltaleBrake = on_off
    }
    function slotSeatbelt(on_off){
        telltale.telltaleSeatbelt = on_off
    }
    function slotHighbeam(on_off){
        telltale.telltaleHighbeam = on_off
    }
    function slotDoor(on_off){
        telltale.telltaleDoor = on_off
    }
    function slotEps(on_off){
        telltale.telltaleEps = on_off
    }
    function slotSrsAirbag(on_off){
        telltale.telltaleSrsAirbag = on_off
    }
    function slotAbs(on_off){
        telltale.telltaleAbsWarn = on_off
    }
    function slotLowBattery(on_off){
        telltale.telltaleLowBatt = on_off
    }
    function slotImmobi(on_off){
        telltale.telltaleImmobi = on_off
    }
    function slotEspAct(on_off){
        telltale.telltaleEspAct = on_off
    }
    function slotEspOff(on_off){
        telltale.telltaleEspOff = on_off
    }
    function slotHillDescent(on_off){
        telltale.telltaleHillDescent = on_off
    }
    function slotGeneralWarn(on_off){
        telltale.telltaleGeneralWarn = on_off
    }
    function slotGearAtVal(pos){
        switch(pos){
        case(1): // Parking
            shiftPosition.shiftId = 1
            break
        case(2): // Reverse
            shiftPosition.shiftId = 2
            break
        case(3):  // Neutral
            shiftPosition.shiftId = 3
            break
        case(4):  // Drive
            shiftPosition.shiftId = 4
            break
        case(6):  // Low
            shiftPosition.shiftId = 6
            break
        default:  // Parking
            shiftPosition.shiftId = 1
            break
    }
    function slotSpAnalogVal(speed){
        meter.speedValue = speed / 100
    }
    function slotTaAnalogVal(tacho){
        meter.tachoValue = tacho
    }
    function slotOTempVal(temp){
        header.outsideTemperature.tempValue = temp
    }
    function slotCruRangeVal(range){
        cruisingRange.slotCruRangeVal = range
    }
    Item{
        id: rootItem
        width: 1920
        height: 720
        focus: true
        clip: true
        property int mode: 0 /* 0:normal 1:adas 2:map */
        property string car_state : "normal_default"
        property string arrow_state : "arrow_normal_default"
        property string set_state : "set_default"
        signal transNormalToAdas()
        signal transAdasToMap()
        signal transMapToNormal()

        signal keyPressed_Up()
        signal keyPressed_Down()
        signal keyPressed_Left()
        signal keyPressed_Right()
        signal keyPressed_Enter()
        signal keyPressed_Menu()


        Item{
            id:viewdata
            property int tbtArrow: 0
            property int tbtValue: 200

            onTbtArrowChanged: {
                turnByTurn.receivedArrowId = tbtArrow
                stage.received_id = tbtArrow
            }

            onTbtValueChanged: {
                turnByTurn.receivedTbtValue = tbtValue
            }
        }

        Item{
            id:acc3d_parts
            width:1920
            height:1080
            Item{
                id:acc3d
                Item{
                    id:ddditem
                    x:548
                    y:-23
                    width: 1920
                    height: 1080
                    scale:0.6
                    Scene3D {
                        anchors.fill: parent
                        aspects: ["input", "logic"]
                        multisample: false
                        cameraAspectRatioMode:Scene3D.UserAspectRatio
                        Stage {
                            id:stage
                            ACC_Animation{
                                property int direction_acc_line : 0
                                property int direction_acc_car : 0
                                id:accc_view
                                acc_line_pos: 1
                                acc_car_pos: 1
                            }
                        }
                    }

                }
            }

            Image{
                id: acc3d_mask
                width:1920
                height:720
                source: "qrc:/Images/ADASView/ACC/3D_parts_mask.ktx"
                visible:true

            }
            Image{ source:"qrc:/Images/ADASView/MAP/acc_cover.ktx"; width:1412; height:98; x:508; y:622 }

        }

        Map{
            id: map
        }

        TurnByTurn{
            id:turnByTurn
        }
        Menu{
            id: menu
        }
        Meter{
            id: meter
        }
        ShiftPosition{
            id:shiftPosition
            shiftId:0
        }
        CruisingRange {
            id: cruisingRange
            cruisingRangeValue : 750
        }

        Header{
            id:header
        }
        Telltale{
            id:telltale
        }

        Keys.onPressed: {

            switch(event.key){
                case(Qt.Key_C):

                    if(mode === 0){
                        transNormalToAdas();
                    }else if(mode === 1){
                        transAdasToMap();
                    }else if(mode === 2){
                        transMapToNormal()
                    }

                    mode++;
                    if(mode > 2) mode = 0;
                    break



            case(Qt.Key_1):
                if(shiftPosition.shiftId < 5) {
                    shiftPosition.shiftId++
                }else{
                    shiftPosition.shiftId = 0
                }
                break

            case(Qt.Key_2):
                if(accc_view.direction_acc_line === 0){
                    if(accc_view.acc_line_pos == 1) {
                        accc_view.acc_line_pos++
                        if(mode == 0){
                            rootItem.arrow_state = "arrow_normal_middle"
                        }else{
                            rootItem.arrow_state = "arrow_adas_middle"}
                        rootItem.set_state = "set_middle"
                    }else if(accc_view.acc_line_pos == 2){
                        accc_view.acc_line_pos++
                        if(mode == 0){
                            rootItem.arrow_state = "arrow_normal_near"
                        }else{
                            rootItem.arrow_state = "arrow_adas_near"}
                        rootItem.set_state = "set_near"
                    }else if(accc_view.acc_line_pos == 3){
                        accc_view.acc_line_pos--
                        if(mode == 0){
                            rootItem.arrow_state = "arrow_normal_middle"
                        }else{
                            rootItem.arrow_state = "arrow_adas_middle"}
                        rootItem.set_state = "set_middle"
                        accc_view.direction_acc_line = 1
                    }
                }else{
                    if(accc_view.acc_line_pos == 3) {
                        accc_view.acc_line_pos--
                        if(mode == 0){
                            rootItem.arrow_state = "arrow_normal_middle"
                        }else{
                            rootItem.arrow_state = "arrow_adas_middle"}
                        rootItem.set_state = "set_middle"
                    }else if(accc_view.acc_line_pos == 2){
                        accc_view.acc_line_pos--
                        if(mode == 0){
                            rootItem.arrow_state = "arrow_normal_default"
                        }else{
                            rootItem.arrow_state = "arrow_adas_default"}
                        rootItem.set_state = "set_default"
                    }else if(accc_view.acc_line_pos == 1){
                        accc_view.acc_line_pos++
                        if(mode == 0){
                            rootItem.arrow_state = "arrow_normal_middle"
                        }else{
                            rootItem.arrow_state = "arrow_adas_middle"}
                        rootItem.set_state = "set_middle"
                        accc_view.direction_acc_line = 0
                    }
                }
                break

            case(Qt.Key_3):
                if(accc_view.direction_acc_car == 0){
                    if(accc_view.acc_car_pos == 1) {
                        accc_view.acc_car_pos++
                        if(mode == 0){
                            rootItem.car_state = "nornal_middle"
                        }else{
                            rootItem.car_state = "adas_middle"}
                    }else if(accc_view.acc_car_pos == 2) {
                        accc_view.acc_car_pos++
                        if(mode == 0){
                            rootItem.car_state = "normal_near"
                        }else{
                            rootItem.car_state = "adas_near"}
                    }else if(accc_view.acc_car_pos == 3) {
                        accc_view.acc_car_pos--
                        accc_view.direction_acc_car = 1
                        if(mode == 0){
                            rootItem.car_state = "normal_middle"
                        }else{
                            rootItem.car_state = "adas_middle"}
                    }
                }else{
                    if(accc_view.acc_car_pos == 3) {
                        accc_view.acc_car_pos--
                        if(mode == 0){
                            rootItem.car_state = "normal_middle"
                        }else{
                            rootItem.car_state = "adas_middle"}
                    }else if(accc_view.acc_car_pos == 2) {
                        accc_view.acc_car_pos--
                        if(mode == 0){
                            rootItem.car_state = "normal_default"
                        }else{
                            rootItem.car_state = "adas_default"}
                    }else if(accc_view.acc_car_pos == 1){
                        accc_view.acc_car_pos++
                        accc_view.direction_acc_car = 0
                        if(mode == 0){
                            rootItem.car_state = "normal_middle"
                        }else{
                            rootItem.car_state = "adas_middle"}
                    }
                }
                break
            case(Qt.Key_4):
                telltaleSwitching();
                break

            case(Qt.Key_Up):
                keyPressed_Up()
                break

            case(Qt.Key_Down):
                keyPressed_Down()
                break

            case(Qt.Key_Left):
                keyPressed_Left()
                break

            case(Qt.Key_Right):
                keyPressed_Right()
                break

            case(Qt.Key_Space):
                keyPressed_Enter()
                break

            case(Qt.Key_M):
                keyPressed_Menu()
                break

            default:
                break


            }
       }


        Timer { //test
            property int num  : 0
            interval: 5000
            repeat: true
            running: true
            onTriggered: {
                num++;
                if(num == 5){num = 1}
                viewdata.tbtArrow = num;
            }
        }

        Timer { //test
            property int v  : 200
            interval: 5000
            repeat: true
            running: true
            onTriggered: {
                if(v - 20 >= 0){
                  v = v - 20
                }else{
                    v = 200
                }
                viewdata.tbtValue = v;
            }
        }
    }

//  FpsItem{}

    function telltaleSwitching(){
        telltale.telltaleMasterWarn = !telltale.telltaleMasterWarn
        telltale.telltaleGeneralWarn = !telltale.telltaleGeneralWarn
        telltale.telltaleBrakeEnergyRecovOff = !telltale.telltaleBrakeEnergyRecovOff
        telltale.telltaleBrakeEnergyRecovLv = !telltale.telltaleBrakeEnergyRecovLv
        telltale.telltaleMotorWarn = !telltale.telltaleMotorWarn
        telltale.telltalePopupHoodWarn = !telltale.telltalePopupHoodWarn
        telltale.telltaleDecharge = !telltale.telltaleDecharge
        telltale.telltaleEvSystemWarn = !telltale.telltaleEvSystemWarn
        telltale.telltaleChargingPlugWarn = !telltale.telltaleChargingPlugWarn
        telltale.telltaleLowBatt = !telltale.telltaleLowBatt
        telltale.telltaleBattWarn = !telltale.telltaleBattWarn
        telltale.telltaleBattTempWarn = !telltale.telltaleBattTempWarn
        telltale.telltaleHighVoltBattCut = !telltale.telltaleHighVoltBattCut
        telltale.telltaleAeb = !telltale.telltaleAeb
        telltale.telltaleLdw = !telltale.telltaleLdw
        telltale.telltaleBsd = !telltale.telltaleBsd
        telltale.telltaleSrsAirbag = !telltale.telltaleSrsAirbag
        telltale.telltaleEpsOff = !telltale.telltaleEpsOff
        telltale.telltaleBrake = !telltale.telltaleBrake
        telltale.telltaleAbsWarn = !telltale.telltaleAbsWarn
        telltale.telltaleEspAct = !telltale.telltaleEspAct
        telltale.telltaleHillDescent = !telltale.telltaleHillDescent
        telltale.telltaleAutoParking = !telltale.telltaleAutoParking
        telltale.telltaleTpmsInd = !telltale.telltaleTpmsInd
        telltale.telltaleImmobi = !telltale.telltaleImmobi
        telltale.telltaleDoor = !telltale.telltaleDoor
        telltale.telltaleSeatbelt = !telltale.telltaleSeatbelt
        telltale.telltaleSeatbelt2 = !telltale.telltaleSeatbelt2
        telltale.telltaleEpbWarn = !telltale.telltaleEpbWarn
        telltale.telltaleEps= !telltale.telltaleEps
        telltale.telltaleHighbeamAssist = !telltale.telltaleHighbeamAssist
        telltale.telltaleHighbeam = !telltale.telltaleHighbeam
        telltale.telltaleRearFog = !telltale.telltaleRearFog
        telltale.telltaleLowbeam = !telltale.telltaleLowbeam
        telltale.telltalePosition = !telltale.telltalePosition
    }
}


