#!/bin/bash

# Configuration
IRC_HOST="localhost"
IRC_PORT="6667"
PSS="jj"
NAME0="alain"
NAME1="bernard"
NAME2="charlie"
NAME3="david"
NAME4="ed"
NAME5="fab"
NAME6="gael"
NAME7="henri"
NAME8="iznogood"
NAME9="joe"
NAME10="kfc"
DDD=""
SESSION_NAME="irc_test"
CHANNEL="#t8"
MSG=`printf '%s---------' {1..1024}`

# Vérifier si tmux est installé
if ! command -v tmux &> /dev/null; then
    echo "Erreur: tmux n'est pas installé"
    exit 1
fi

# Tuer la session si elle existe déjà
tmux kill-session -t $SESSION_NAME 2>/dev/null

# Créer une nouvelle session tmux en mode détaché avec le premier client
tmux new-session -d -s $SESSION_NAME "telnet $IRC_HOST $IRC_PORT"

# Diviser horizontalement pour le deuxième client
tmux split-window -h -t $SESSION_NAME "telnet $IRC_HOST $IRC_PORT"

# Diviser verticalement le premier panneau pour le troisième client
tmux split-window -v -t $SESSION_NAME:0.0 "telnet $IRC_HOST $IRC_PORT"

tmux split-window -v -t $SESSION_NAME:0.1 "telnet $IRC_HOST $IRC_PORT"

# Arranger les panneaux en mode tiled (disposition équilibrée)
tmux select-layout -t $SESSION_NAME tiled

sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "PASS jj
NICK $NAME0$DDD
USER tvoisiny t y" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.1 "PASS jj" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.1 "NICK $NAME1$DDD" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.1 "USER lhermite$DDD" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.2 "PASS jj" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.2 "NICK $NAME2$DDD" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.2 "USER Corine$DDD1" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.3 "PASS jj" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.3 "NICK $NAME3$DDD" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.3 "USER lhermite1$DDD1" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "JOIN $CHANNEL" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.1 "JOIN $CHANNEL" C-m #les 2 premier sont sur le canal
sleep 0.01

tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG personne :de $NAME0 a personne" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG $NAME3 :de $NAME0 a $NAME3" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG $CHANNEL :de $NAME0 a $CHANNEL" C-m 
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG $NAME3,$NAME1 :de $NAME0 a $NAME3 et $NAME1" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.2 "PRIVMSG $NAME3,personne,$NAME1 :de $NAME2 a $NAME3 ,personne et  $NAME1" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG $NAME3,$NAME1 message1 message2" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG $NAME3,$NAME1 message1 :" C-m
sleep 0.01
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG $NAME3,$NAME1 :" C-m
sleep 1
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG $CHANNEL :$MSG" C-m
sleep 0.01

# Attacher à la session
tmux attach-session -t $SESSION_NAME
1---------2---------3---------4---------5---------6---------7---------8---------9---------10---------11---------12---------13---------14---------15---------16---------17---------18---------19---------20---------21---------22---------23---------24---------25---------26---------27---------28---------29---------30---------31---------32---------33---------34---------35---------36---------37---------38---------39---------40---------41---------42---------43---------44---