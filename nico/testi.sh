#!/bin/bash

# Configuration
IRC_HOST="localhost"
IRC_PORT="6667"
PSS="jj"
NAME0="Alpha"
NAME1="BRAVO"
NAME2="cHarl1e"
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

# Arranger les panneaux en mode tiled (disposition équilibrée)
tmux select-layout -t $SESSION_NAME tiled

sleep 1
tmux send-keys -t $SESSION_NAME:0.0 "PASS jj" C-m
tmux send-keys -t $SESSION_NAME:0.0 "NICK Alain" C-m
tmux send-keys -t $SESSION_NAME:0.0 "NAME Altrad" C-m
tmux send-keys -t $SESSION_NAME:0.1 "PASS jj" C-m
tmux send-keys -t $SESSION_NAME:0.1 "NICK Bernard" C-m
tmux send-keys -t $SESSION_NAME:0.1 "NAME lhermite" C-m
tmux send-keys -t $SESSION_NAME:0.2 "PASS jj" C-m
tmux send-keys -t $SESSION_NAME:0.2 "NICK Bernard" C-m
tmux send-keys -t $SESSION_NAME:0.2 "NICK Bianca" C-m
tmux send-keys -t $SESSION_NAME:0.2 "NAME Corine" C-m

tmux send-keys -t $SESSION_NAME:0.1 "MODE arg1 arg2 arg3 :   vois tu ce message" C-m
tmux send-keys -t $SESSION_NAME:0.1 "PRVMSG Bianca :Salut Bianca" C-m
tmux send-keys -t $SESSION_NAME:0.1 "PRVMSG mathis :Salut Bianca" C-m


# Attacher à la session
tmux attach-session -t $SESSION_NAME