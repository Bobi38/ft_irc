#include "server.hpp"

int main(int ac , char **av){
    if (ac != 3){
        std::cout << " WRONG arg number, send only 2 arg" << std::endl;
        return 1;
    }

    try{
        Server serv(av[2], av[1]);
        serv.GoServ();
    }catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
    
}

// #include "ACmd.hpp"
// #include "Maker.hpp"

// int main(){
//      Maker tt;
//      ACmd* rr = tt.makeCmd(2, "coucou JOIN popo");
//     rr->action();
//      delete rr;
// }