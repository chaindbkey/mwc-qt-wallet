// Copyright 2020 The MWC Developers
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef MWC_QT_WALLET_Y_SELECTMODE_B_H
#define MWC_QT_WALLET_Y_SELECTMODE_B_H

#include <QObject>

namespace bridge {

class SelectMode : public QObject {
Q_OBJECT
public:
    explicit SelectMode(QObject * parent = nullptr);
    ~SelectMode();

    //  get wallet running mode id. Values: config::WALLET_RUN_MODE
    Q_INVOKABLE int getWalletRunMode();

    // Change wallet running mode. This call will retart the wallet app.
    // walletRunMode :  config::WALLET_RUN_MODE
    Q_INVOKABLE void updateWalletRunMode( int walletRunMode );
};

}

#endif //MWC_QT_WALLET_Y_SELECTMODE_B_H
