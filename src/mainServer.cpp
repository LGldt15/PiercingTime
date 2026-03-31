#include <SFML/Network.hpp>
#include "IHMServeur.h"

int main(int argc, char* argv[]) {
    IHMServeur serveur(static_cast<unsigned short>(std::stoi(argv[1])));
    serveur.run();
}