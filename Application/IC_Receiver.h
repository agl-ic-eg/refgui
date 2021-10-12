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

#include <QThread>
#include <QString>

#include "IC_DataPool.h"

class IC_RException
{
public:
    IC_RException(const QString &str) : info(str){};
    ~IC_RException() {};
    QString& message();
private:
    QString info;
};

class IC_Receiver : public IC_DataPool
{
    Q_OBJECT
public:
    explicit IC_Receiver(QObject *parent = 0);
    ~IC_Receiver();
    void receive();
};

