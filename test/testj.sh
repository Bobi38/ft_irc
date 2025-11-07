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

sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "PASS jj
NICK $NAME0$DDD
USER tvoisiny t y" C-m
sleep 1
tmux send-keys -t $SESSION_NAME:0.1 "PASS jj" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "NICK $NAME1$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "USER lhermite$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "PASS jj" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "NICK $NAME1$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "NICK $NAME2$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "USER Corine$DDD1" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.3 "PASS jj" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.3 "NICK $NAME3$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.3 "USER lhermite$DDD1" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "PRVMSG $NAME2$DDD :de $NAME1 envoie a $NAME2$DDD Salut $NAME2$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "JOIN #t1" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "JOIN #t1" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "JOIN #t1" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "JOIN #channel" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "PRVMSG #channel :message de $NAME0$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "TOPIC #channel :TOPIC de $NAME0$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG niroppp :message a niroppp de $NAME0$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "JOIN #channel" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "PRIVMSG #channel :message a tout #channel de $NAME0$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "PRIVMSG #channel :message a tout #channel de $NAME1$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "PRIVMSG #channel :message a tout #t1 de $NAME1$DDD" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "TOPIC #channel" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "JOIN #channel" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "PRIVMSG #channel :message a tout #channel de XXX" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "JOIN #t8,#10,#t11" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.1 "JOIN #t8,#10" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "JOIN #t8" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.3 "PRIVMSG #t8 :message a tout #t8 de $NAME3" C-m
sleep 0.5
tmux send-keys -t $SESSION_NAME:0.3 "JOIN #t8" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.3 "PRIVMSG #t8 :message a tout #t8 de $NAME3" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "MODE #channel +i" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.3 "JOIN #channel" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.0 "MODE #channel -i" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.3 "JOIN #channel" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "PART #channel" C-m
sleep 0.1
tmux send-keys -t $SESSION_NAME:0.2 "PART #lavicclaire" C-m

# Attacher à la session
tmux attach-session -t $SESSION_NAME