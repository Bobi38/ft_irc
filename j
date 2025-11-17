c++ .obj/Channel.o .obj/Channel2.o .obj/ChannelGet.o .obj/ChannelMod.o .obj/Server.o .obj/Client.o .obj/Bot.o .obj/fct.o .obj/Quit.o .obj/Join.o .obj/Part.o .obj/Kick.o .obj/co.o .obj/List.o .obj/Mode.o .obj/Msg.o .obj/bot.o .obj/Topic.o .obj/Request.o .obj/Maker.o .obj/Prefix.o .obj/split.o app/main.cpp -o ircserv
valgrind --leak-check=full --show-leak-kinds=all ./ircserv 6667 j4Jp
server good
4 PASS j4Jp
4 NICK titi
4 USER toto
je suis coooo -----titi
bu =-----NICK : titi
:server_irc 001 titi :Welcome to the IRC Network :titi!toto@127.0.0.1
:serveur 002 titi :Your host is serveur
:serveur 376 titi :End of /MOTD command.
:bot!bot@127.0.0.1 PRIVMSG : Coucou je suis le bot, veux tu jouer a pil ou face ?
----------4
in bucle =-----NICK : titi
:server_irc 001 titi :Welcome to the IRC Network :titi!toto@127.0.0.1
:serveur 002 titi :Your host is serveur
:serveur 376 titi :End of /MOTD command.
:bot!bot@127.0.0.1 PRIVMSG : Coucou je suis le bot, veux tu jouer a pil ou face ?
-------4
5 PASS j4Jp
5 NICK Bernard
bu =-----NICK : Bernard
----------5
in bucle =-----NICK : Bernard
-------5
5 USER lhermite
je suis coooo -----Bernard
bu =-----:server_irc 001 Bernard :Welcome to the IRC Network :Bernard!lhermite@127.0.0.1
:serveur 002 Bernard :Your host is serveur
:serveur 376 Bernard :End of /MOTD command.
:bot!bot@127.0.0.1 PRIVMSG : Coucou je suis le bot, veux tu jouer a pil ou face ?
----------5
in bucle =-----:server_irc 001 Bernard :Welcome to the IRC Network :Bernard!lhermite@127.0.0.1
:serveur 002 Bernard :Your host is serveur
:serveur 376 Bernard :End of /MOTD command.
:bot!bot@127.0.0.1 PRIVMSG : Coucou je suis le bot, veux tu jouer a pil ou face ?
-------5
4 JOIN #t1
bu =-----:titi!toto@127.0.0.1 JOIN #t1
:server_irc 353 titi = #t1 :@titi
:server_irc 366 titi #t1 :End of /NAMES list
:bot!bot@127.0.0.1 JOIN #t1
----------4
in bucle =-----:titi!toto@127.0.0.1 JOIN #t1
:server_irc 353 titi = #t1 :@titi
:server_irc 366 titi #t1 :End of /NAMES list
:bot!bot@127.0.0.1 JOIN #t1
-------4
4 JOIN #t2
bu =-----:titi!toto@127.0.0.1 JOIN #t2
:server_irc 353 titi = #t2 :@titi
:server_irc 366 titi #t2 :End of /NAMES list
:bot!bot@127.0.0.1 JOIN #t2
----------4
in bucle =-----:titi!toto@127.0.0.1 JOIN #t2
:server_irc 353 titi = #t2 :@titi
:server_irc 366 titi #t2 :End of /NAMES list
:bot!bot@127.0.0.1 JOIN #t2
-------4
4 MODE #t1
bu =-----:server 324 titi #t1 +kl 1
----------4
in bucle =-----:server 324 titi #t1 +kl 1
-------4
4 PART #t1
in #t1
nonono
bu =-----:titi!toto@127.0.0.1 PART #t1 :
----------4
in bucle =-----:titi!toto@127.0.0.1 PART #t1 :
-------4
5 QUIT 
siz=1
outttt
server down correctly 
close fd server
