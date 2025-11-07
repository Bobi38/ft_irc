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
SESSION_NAME="irc_test1"

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

sleep 0.5
tmux send-keys -t $SESSION_NAME:0.0 "PASS jj
NICK $NAME4$DDD
USER tvoisiny t y" C-m
sleep 0.5
# tmux send-keys -t $SESSION_NAME:0.0 "NICK Alain" C-m
# tmux send-keys -t $SESSION_NAME:0.0 "NAME Altrad" C-m
tmux send-keys -t $SESSION_NAME:0.1 "PASS jj" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "NICK $NAME5$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "USER lhermite" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.2 "PASS jj" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.2 "NICK $NAME6$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.2 "USER Corine1" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.3 "PASS jj" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.3 "NICK $NAME7$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.3 "USER lhermite1" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "PRVMSG $NAME5$DDD :Salut $NAME5$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "JOIN #t1" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.2 "JOIN #t1" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.0 "JOIN #t1" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.0 "JOIN #channel" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.0 "PRVMSG #channel :message de $NAME4$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.0 "TOPIC #channel :TOPIC de $NAME4$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG niroppp :message a niroppp de $NAME4$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "JOIN #channel" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG #channel :message a tout #channel de $NAME4$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "PRIVMSG #channel :message a tout #channel de $NAME5$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "PRIVMSG #channel :message a tout #t1 de $NAME5$DDD" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.1 "TOPIC #channel" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.2 "JOIN #channel" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.2 "PRIVMSG #channel :message a tout #channel de XXX" C-m
# Attacher à la session
tmux attach-session -t $SESSION_NAME