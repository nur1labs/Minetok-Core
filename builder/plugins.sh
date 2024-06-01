#!/bin/bash
# Copyright (c) 2010-2022 Nur1Labs.Ltd
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

TMP_FOLDER=$(mktemp -d)
CONFIG_FILE='caria.conf'
CONFIGFOLDER='/root/.caria'
COIN_DAEMON='dinareumd'
COIN_CLI='dinareum-cli'
COIN_PATH='/usr/local/bin/'
COIN_TGZ='http://nur1labs.net/lf/dinareum.zip'
COIN_ZIP=$(echo $COIN_TGZ | awk -F'/' '{print $NF}')
COIN_NAME='dinareum'
COIN_EXPLORER='http://chain.nur1labs.org'
COIN_PORT=46031
RPC_PORT=46131

NODEIP=$(curl -s4 icanhazip.com)

BLUE="\033[0;34m"
YELLOW="\033[0;33m"
CYAN="\033[0;36m" 
PURPLE="\033[0;35m"
RED='\033[0;31m'
GREEN="\033[0;32m"
NC='\033[0m'
MAG='\e[1;35m'

#function start
#systems
function prepare_system() {
echo -e "Preparing the VPS to setup. ${CYAN}$COIN_NAME${NC} ${RED}Plugins Features${NC}"
#this for autoinstall
sudo apt upgrade -y >/dev/null 2>&1
DEBIAN_FRONTEND=noninteractive apt update > /dev/null 2>&1
DEBIAN_FRONTEND=noninteractive apt -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" -y -qq upgrade >/dev/null 2>&1
sudo apt install -y software-properties-common net-tools build-essential >/dev/null 2>&1
echo -e "Installing required packages, it may take some time to finish.${NC}"
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" git ufw curl >/dev/null 2>&1
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" libtool autotools-dev autoconf pkg-config automake libssl-dev libgmp-dev libboost-all-dev >/dev/null 2>&1
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" libminiupnpc-dev libzmq3-dev qtbase5-dev qttools5-dev qttools5-dev-tools libqt5charts5-dev libqt5svg5-dev libprotobuf-dev protobuf-compiler libqrencode-dev >/dev/null 2>&1
sudo apt install -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" cargo libsodium-dev >/dev/null 2>&1
if [ "$?" -gt "0" ];
  then
    echo -e "${RED}Not all required packages were installed properly. Try to install them manually by running the following commands:${NC}\n"
    echo "apt update"
    echo "apt -y install software-properties-common net-tools build-essential"
    echo "apt update"
    echo "apt install -y git ufw curl &&
  apt install -y libtool autotools-dev autoconf pkg-config automake python3 libssl-dev libgmp-dev libboost-all-dev &&
  apt install -y libminiupnpc-dev libzmq3-dev qtbase5-dev qttools5-dev qttools5-dev-tools libqt5charts5-dev libqt5svg5-dev libprotobuf-dev protobuf-compiler libqrencode-dev &&
        apt install -y cargo libsodium-dev"
 exit 1
fi
clear
#this is plugin for needs
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

#zipped simple
cd ~/coins/mubdi/core && unzip -o plugin.zip && cd ~
}

function important_information() {
 echo
 echo -e "${BLUE}================================================================================================================================${NC}"
 echo -e "${BLUE}================================================================================================================================${NC}"
 echo -e "Plugins is installed and running"
}

#function_end
function setup_node() {
  important_information
}

##### Main #####
clear

prepare_system
setup_node
