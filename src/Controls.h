#pragma once

struct Controls{
    bool up;//1
    bool down;//2
    bool right;//3
    bool left;//4
    bool pause;//5
    bool select;//6
    bool tab;//7
    bool back;
    bool next;
};



/*
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Window/Keyboard.hpp>
#include <map>
#include <string>

// On définit les actions possibles de manière propre
enum class Action {
    Up,
    Down,
    Left,
    Right,
    Pause,
    Select
};

class InputManager {
private:
    // Le mapping : Associe une Action à une touche SFML
    std::map<Action, sf::Keyboard::Key> keyMap;

public:
    InputManager();

    // Permet de changer une touche en plein jeu (ex: passer de ZQSD à Flèches)
    void remap(Action action, sf::Keyboard::Key newKey);

    // Renvoie true si l'action est pressée
    bool isActionPressed(Action action) const;

    // Version pour les événements (pression unique)
    bool isActionJustPressed(const sf::Event::KeyPressed* event, Action action) const;
};

#endif*/