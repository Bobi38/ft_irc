#include "Server.hpp"

volatile sig_atomic_t stop_server = 0;

void clean_std(std::string& rest){
    for(size_t i = 0; i < rest.size(); i++){
        if (!isprint(rest[i])){
            rest.erase(i, 1);
            i = 0;
        }
    }
}

void handle_sigint(int signum) {
    (void)signum;
    stop_server = 1;
}

void send_msg(int fd, std::string msg){
    send(fd, msg.c_str(), msg.size(), 0);
}

void send_msg_v2(int fd, std::string msg, Server* serv){
    send(fd, msg.c_str(), msg.size(), 0);
}


// void bucle_server(Server* serv){
//    while(1){
//         if (poll(serv->_fds.data(), serv->_fds.size(), -1) == -1)
//             throw std::runtime_error("poll failed");
//         if (serv->_fds[0].revents & POLLIN){
//                 int nfd = accept(serv->_server_fd, (struct sockaddr *)&c, &client_len);
//                 if (check_psswd(nfd) == true){
//                     addFd(nfd);
//                     addClient(nfd);
//                     std::cout << "new client add " << std::endl;
//                     std::string gg = "welcome to ft_IRC\n";
//                     send(nfd, gg.c_str(), gg.size(), 0);
//                 }
//                 else{
//                 std::cout << "wrong password" << std::endl;
//                 std::string error = "password incorrect boloss\n";
//                 send(nfd, error.c_str(), error.size(), 0);
//                 close (nfd);
//                 }
//             }
//         for (size_t i = 1; i < _fds.size(); ++i){
//             if (_fds[i].revents & POLLIN) {
//                 int n = recv(_fds[i].fd, buffer, BUFFER_SIZE, 0);
//                 std::cout << n << " message = " << buffer << std::endl;
//                 for (size_t j = 1; j < _fds.size(); ++j) {
//                     if (_fds[j].fd != _fds[i].fd)
//                         send(_fds[j].fd, buffer, n, 0);
//                 }
//             }
//         }
//     }
// }