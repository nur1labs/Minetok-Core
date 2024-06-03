MuBdI BlockStream Artificial Symatic System
=====================================
[![CircleCI](https://dl.circleci.com/status-badge/img/bb/nur1labs/mubdi/tree/release%2Fcore.svg?style=svg&circle-token=ed14022cea6f337da9429cf9e10c1af965764288)](https://dl.circleci.com/status-badge/redirect/bb/nur1labs/mubdi/tree/release%2Fcore)
[![Build Status](https://app.travis-ci.com/nur1labs/mubdi.svg?token=HH19Fjydf13B3YsoJWsy&branch=release/core)](https://app.travis-ci.com/nur1labs/mubdi)

MBASS is Platform Blockchain for QaWiYyu.Desclaimer note. After Consensus we herby make split aria-tokenizer and aria self. Cause distribute scammer. Auditing stop
make tokenizer aria is stop listing project on 20th January, 2019. And total stop services and do swap to AriA[Public] or Imanity[Private] And MBASS as official new platform at 25th January, 2019

On August The Blockchain Become BA or Blockchain Artificial needed for more transaction and more wided processing(this need support super computer). make
this blockchain can make light wallet more faster no need saving the chain to local disk.

MBASS signed on new Fork(commited 07466c3) as Dirham/Dinar trace make USD is more bad way system since general viruses comes Covid-19. And make gold, Dirham and Dinar as alternative.
while AriA care for this time to put cold storage wallet. And as used based continental from dubai community agreement number 15(committed 81e71b3).
It's called "from ummah to ummah". or people to people. Make MBASS signal for whole fiat enemy and e-wallet based bank resides.

MBASS Signed On New Policy(commited 4c89076) As The Platform For All System OutRun On Blockchain system. MBASS new protocol used block stream on 2021 as more speed and transaction and plus for degenerate new system for MBASS ecosystem(commited e3bced4).

MuBdI become transform From Artificial Works to Core Artificial Works or called MBASS(MuBdI BlockStream Artificial Symatic System)(commited f0e22db)

there is directory tree below :

1. builder : place installer MBASS Engine.
2. client  : place updates client MBASS Engine[DEPRECATED].
3. core : code base for MBASS like devices core to wallet[no need soon as we have many repos]. here HardFork settings too.
4. .circleci : this for expert of the core developer only.

Repos Structure :

1. release/core             : This Main Final For Updates.
2. hotfix/upgrade           : This Development Team Work(Core).
3. releases/single_nodes    : This For HardFork Or SoftFork Sub-System.
4. feature/last_pow         : This For HardFork of End ecosystem cycle of proof of work(prevent new illegal forking).

listed nodes developement tags(builder/nametag_install.sh).

1. cn = core nodes. for main cores system install.
2. wn = mainly for wallet nodes.
3. mn = masternodes only.
4. en = for exchanger nodes.
5. tn = testing nodes. for test nodes only.
6. rn = rebuild nodes. easily upgraded nodes.
6. an = artificial nodes with multi systems. this make sure install if running super computer.(POS II(BA) Supports)

# AIRLogic Algorithm(MOVED) ##

[AirLogic](http://192.168.0.187/mediawiki/index.php?title=Airlogic)
[AirLogic2](http://192.168.0.187/mediawiki/index.php?title=Airlogic2)

# COMPABILITY OS ##

| OS NAME     | COMPABILITY                                        |
| ----------- | -------------------------------------------------- |
| Ubuntu 16.x | Deprecated                                         |
| Ubuntu 18.x | Deprecated                                         |
| Ubuntu 20.x | OK[No Bug/Glitch]                                  |
| Ubuntu 22.x | OK[No Bug/Glitch]                                  |
| Debian 9    | Deprecated                                         |
| Debian 10   | Deprecated                                         |
| Debian 11   | OK[No Bug/Glitch]                                  |
| Debian 12   | OK[No Bug/Glitch]                                  |
| MuBdI  0.1  | Deprecated                                         |
| MuBdI  0.2  | Deprecated                                         |
| MuBdI  0.3  | Deprecated                                         |
| MuBdI  0.4  | OK[No Bug/Glitch]                                  |
| MuBdI  0.5  | OK[No Bug/Glitch]                                  |
| Armbian64   | OK[No Bug/Glitch]                                  |

# BOOST LIBRARY COMPABILITY ##

| OS NAME     | COMPABILITY                                        |
| ----------- | -------------------------------------------------- |
| Boost  1.67 | Deprecated                                         |
| Boost  1.74 | OK[No Bug/Glitch]                                  |

# COMPABILITY QT ##

| QT NAME     | COMPABILITY                                        |
| ----------- | -------------------------------------------------- |
| QT 5.5      | Deprecated                                         |
| QT 5.6      | Deprecated                                         |
| QT 5.7      | Deprecated                                         |
| QT 5.8      | Deprecated                                         |
| QT 5.9      | OK[No Bug/Glitch]                                  |
| QT 5.10     | OK[No Bug/Glitch]                                  |
| QT 5.11     | OK[No Bug/Glitch]                                  |

# Specification ##

Name : MineTok

Ticker : MTK

Supply : 1.500.000 MTK

Pre-Sale : 100.000 MTK

Bountry And Reward : 1.000 MTK

AirDrop : 500 MTK

ICO : Not Yet

PoW : 499k Blocks

PoS : Active after 500k Blocks

Block Reward : 0.001

Masternode : Enable

Masternode Collateral : 1.000 MTK

SuperNode : Enable

DEX : Soon

PEG : Diamond Price Real

Contact : https://t.me/SoraDv

# Installation ##

Clone this by

```
gh repo clone MineTokNetwork/MineTok-Core
```

Install Plugin All below

```
sudo apt install -y software-properties-common net-tools build-essential >/dev/null 2>&1
echo -e "Installing required packages, it may take some time to finish.${NC}"
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" git ufw curl >/dev/null 2>&1
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" libtool autotools-dev autoconf pkg-config automake libssl-dev libgmp-dev libboost-all-dev >/dev/null 2>&1
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" libminiupnpc-dev libzmq3-dev qtbase5-dev qttools5-dev qttools5-dev-tools libqt5charts5-dev libqt5svg5-dev libprotobuf-dev protobuf-compiler libqrencode-dev >/dev/null 2>&1
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" cargo libsodium-dev >/dev/null 2>&1
#libevent
git clone https://github.com/libevent/libevent
cd libevent
./autogen.sh && ./configure && sudo make install && cd ~
#libzmq
git clone https://github.com/zeromq/libzmq
cd libzmq
./autogen.sh && ./configure && sudo make install && cd ~
#db
sudo apt install libdb-dev libdb++-dev -y
```

Then Running this

```
#chmod
chmod 755 -R share/genbuild.sh && chmod 755 -R depends/config.guess && chmod 755 -R depends/config.sub
#main
./mubdi.sh && ./configure CXXFLAGS="--param ggc-min-expand=1 --param ggc-min-heapsize=32768" --with-incompatible-bdb --disable-tests --without-gui --enable-mining-rpc && make && sudo make install
```

# HOW TO MINE ##

Running Terminal/Console/CMD

```
mtkd -daemon
mtk-cli setgenerate true
```

Running QT

- Go to settings > console
- wrote same setgenerate true

# DEVELOPMENT TAGS ##

tags is list for easy what we change. so make sure that arrange.

| DEVTAG | README                                        |
| ------ | --------------------------------------------- |
| aci    | all ci integrated                             |
| all    | all sources + QT + db + anything inside cores |
| cdc    | codacy integrated                             |
| con    | consoles like android, iphone, raspi,etc      |
| db     | for db purpose                                |
| doc    | for documents all inside                      |
| lang   | for language tags                             |
| lib    | for all type library                          |
| nod    | for all node deployment install               |
| rem    | for remote yml network connection             |
| rpt    | for report db system                          |
| src    | change for core sources not QT                |
| sql    | sql scripting system                          |
| gui    | qt not source                                 |
| web    | web based                                     |

# License ##

Copyright (c) 2010-2022, Nur1labs
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

*   Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

*   Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

*   Neither the name of Nur1Labs Technology nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
