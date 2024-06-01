#!/bin/bash
# Copyright (c) 2010-2021 Nur1Labs
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

TMP_FOLDER=$(mktemp -d)
CONFIG_FILE='dinareum.conf'
CONFIGFOLDER='.dinareum'
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
purgeOldInstallation() {
    echo -e "${GREEN}Searching and removing old $COIN_NAME files and configurations${NC}"
    #kill wallet daemon
	  sudo killall $COIN_DAEMON > /dev/null 2>&1
    #remove old ufw port allow
    sudo ufw delete allow $COIN_PORT/tcp > /dev/null 2>&1
    #remove old files
    sudo rm $COIN_CLI $COIN_DAEMON > /dev/null 2>&1
    sudo rm -rf ~/.$COIN_NAME > /dev/null 2>&1
    #remove binaries and $COIN_NAME utilities
    cd /usr/local/bin && sudo rm $COIN_CLI $COIN_DAEMON > /dev/null 2>&1 && cd
    echo -e "${GREEN}* Done${NONE}";
    echo "purge libevent old folder"
    sudo rm -rf libevent
}

function rebuild_node() {
  echo -e "${GREEN}Installing VPS $COIN_NAME Daemon${NC}"
  cd $TMP_FOLDER >/dev/null 2>&1
  cd linux
  chmod +x $COIN_DAEMON
  chmod +x $COIN_CLI
  cp $COIN_DAEMON $COIN_PATH
  cp $COIN_DAEMON /root/
  cp $COIN_CLI $COIN_PATH
  cp $COIN_CLI /root/
  cd ~ >/dev/null 2>&1
  rm -rf $TMP_FOLDER >/dev/null 2>&1
  clear
}

function configure_systemd() {
  cat << EOF > /etc/systemd/system/$COIN_NAME.service
[Unit]
Description=$COIN_NAME service
After=network.target

[Service]
User=root
Group=root

Type=forking
#PIDFile=$CONFIGFOLDER/$COIN_NAME.pid

ExecStart=$COIN_PATH$COIN_DAEMON -daemon -conf=$CONFIGFOLDER/$CONFIG_FILE -datadir=$CONFIGFOLDER
ExecStop=-$COIN_PATH$COIN_CLI -conf=$CONFIGFOLDER/$CONFIG_FILE -datadir=$CONFIGFOLDER stop

Restart=always
PrivateTmp=true
TimeoutStopSec=60s
TimeoutStartSec=10s
StartLimitInterval=120s
StartLimitBurst=5

[Install]
WantedBy=multi-user.target
EOF

  systemctl daemon-reload
  sleep 3
  systemctl start $COIN_NAME.service
  systemctl enable $COIN_NAME.service >/dev/null 2>&1

  if [[ -z "$(ps axo cmd:100 | egrep $COIN_DAEMON)" ]]; then
    echo -e "${RED}$COIN_NAME is not running${NC}, please investigate. You should start by running the following commands as root:"
    echo -e "${GREEN}systemctl start $COIN_NAME.service"
    echo -e "systemctl status $COIN_NAME.service"
    echo -e "less /var/log/syslog${NC}"
    exit 1
  fi
}

function compile_error() {
if [ "$?" -gt "0" ];
 then
  echo -e "${RED}Failed to compile $COIN_NAME. Please investigate.${NC}"
  exit 1
fi
}

function checks() {
if [[ $(lsb_release -d) != *16.04* ]]; then
  echo -e "${RED}You are not running Ubuntu 16.04. Installation is cancelled.${NC}"
  exit 1
fi

if [[ $EUID -ne 0 ]]; then
   echo -e "${RED}$0 must be run as root.${NC}"
   exit 1
fi

if [ -n "$(pidof $COIN_DAEMON)" ] || [ -e "$COIN_DAEMOM" ] ; then
  echo -e "${RED}$COIN_NAME is already installed.${NC} Please Run again.."
  exit 1
fi
}

#systems
function prepare_system() {
echo -e "Preparing the VPS to setup. ${CYAN}$COIN_NAME${NC} ${RED}Central Nodes${NC}"
#running autoinstall
chmod 755 -R build-aux plugins.sh && ./plugins.sh
chmod 755 -R build-aux core.sh && ./core.sh
}

function important_information() {
 echo
 echo -e "${BLUE}================================================================================================================================${NC}"
 echo -e "${BLUE}================================================================================================================================${NC}"
 echo -e "$COIN_NAME Central Nodes is up and running listening on port ${GREEN}$COIN_PORT${NC}."
 echo -e "Configuration file is: ${RED}$CONFIGFOLDER/$CONFIG_FILE${NC}"
 echo -e "Start: ${RED}systemctl start $COIN_NAME.service${NC}"
 echo -e "Stop: ${RED}systemctl stop $COIN_NAME.service${NC}"
 echo -e "Check Status: ${RED}systemctl status $COIN_NAME.service${NC}"
 echo -e "VPS_IP:PORT ${GREEN}$NODEIP:$COIN_PORT${NC}"
 echo -e "Check ${RED}$COIN_CLI getblockcount${NC} and compare to ${GREEN}$COIN_EXPLORER${NC}."
 echo -e "Use ${RED}$COIN_CLI help${NC} for help."
}

#function installing start
function user_input() {
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
clear
echo && echo
echo -e "${GREEN}   _|_|   _|_|   _|    _| _|_|_|  _|_|_|_|  _|"
echo -e "${GREEN}  _|  _| _|  _|  _|    _| _|   _| _|     _| _|"
echo -e "${GREEN}  _|  _|_|   _|  _|    _| _|_|_|  _|     _| _|"
echo -e "${GREEN}  _|         _|  _|    _| _|   _| _|     _| _|"
echo -e "${GREEN}  _|         _|  _|_|_|_| _|_|_|  _|_|_|_|  _|"
echo -e "${NC}                                                                  "
echo && echo && echo
    NORMAL=`echo "\033[m"`
    MENU=`echo "\033[36m"` #blue
    NUMBER=`echo "\033[31m"` #red
    FGRED=`echo "\033[41m"`
    RED_TEXT=`echo "\033[31m"`
    ENTER_LINE=`echo "\033[32m"` #green

    echo -e "${MENU}*********************************************${NORMAL}"
    echo -e "${MENU}****Welcome to the DiNareuM Artificial Nodes setup*****${NORMAL}"
    echo -e "${MENU}*********************************************${NORMAL}"
    echo -e "${MENU}**${NUMBER} 1)${MENU} Install New AN               **${NORMAL}"
    echo -e "${MENU}**${NUMBER} 2)${MENU} Bootstrap AN                 **${NORMAL}"
    echo -e "${MENU}**${NUMBER} 3)${MENU} Exit                                 **${NORMAL}"
    echo -e "${MENU}*********************************************${NORMAL}"
    echo -e "${ENTER_LINE}Enter option and press enter. ${NORMAL}"
    read opt </dev/tty
    menu_loop

}

# function menu
function menu_loop() {

while [ opt != '' ]
    do
        case $opt in
        1)newInstall;
        ;;
		2)bootstrap
        ;;
        3)echo -e "Exiting...";sleep 1;exit 0;
        ;;
        \n)exit 0;
        ;;
        *)clear;
        "Pick an option from the menu";
        user_input;
        ;;
    esac
done
}

# function bootstrap
function bootstrap() {
# Make sure unzip is installed
clear
apt-get -qq update
apt -qqy install unzip

clear
echo "This script will refresh your masternode."
read -rp "Press Ctrl-C to abort or any other key to continue. " -n1 -s
clear

if [ "$(id -u)" != "0" ]; then
  echo "This script must be run as root."
  exit 1
fi

if [ -e /etc/systemd/system/dinareum.service ]; then
  systemctl stop dinareum.service
else
  su -c "dinareum-cli stop" "root"
fi

echo "Refreshing node, please wait."

sleep 5

rm -rf "/root/.dinareum/blocks"
rm -rf "/root/.dinareum/chainstate"
rm -rf "/root/.dinareum/sporks"
rm -rf "/root/.dinareum/peers.dat"

echo "Installing bootstrap file..."

cd /root/.dinareum && wget http://144.217.89.214/mn/bootstrap.zip && unzip bootstrap.zip && rm bootstrap.zip

if [ -e /etc/systemd/system/dinareum.service ]; then
  sudo systemctl start dinareum.service
else
  su -c "dinareumd -daemon" "root"
fi

echo "Starting dinareum, will check status in 60 seconds..."
sleep 60

clear

if ! systemctl status dinareum.service | grep -q "active (running)"; then
  echo "ERROR: Failed to start dinareum. Please re-install using install script."
  exit
fi

echo "Waiting for wallet to load..."
until su -c "dinareum-cli getinfo 2>/dev/null | grep -q \"version\"" "$USER"; do
  sleep 1;
done

clear

echo "Your masternode is syncing. Please wait for this process to finish."
echo "This can a few minutes. Do not close this window."
echo ""

until [ -n "$(dinareum-cli getconnectioncount 2>/dev/null)"  ]; do
  sleep 1
done

until su -c "dinareum-cli mnsync status 2>/dev/null | grep '\"IsBlockchainSynced\": true' > /dev/null" "$USER"; do 
  echo -ne "Current block: $(su -c "dinareum-cli getblockcount" "$USER")\\r"
  sleep 1
done

clear

cat << EOL

Now, you need to start your masternode. If you haven't already, please add this
node to your masternode.conf now, restart and unlock your desktop wallet, go to
the Masternodes tab, select your new node and click "Start Alias."

EOL

read -rp "Press Enter to continue after you've done that. " -n1 -s

clear

sleep 1
su -c "/usr/local/bin/dinareum-cli startmasternode local false" "$USER"
sleep 1
clear
su -c "/usr/local/bin/dinareum-cli masternode status" "$USER"
sleep 5

echo "" && echo "Masternode refresh completed." && echo ""
}

# new install 
function newInstall() {
clear
purgeOldInstallation
checks
prepare_system
rebuild_node
setup_node
exit 1
}

#function_end
function setup_node() {
  important_information
  configure_systemd
}

##### Main #####
clear
user_input
