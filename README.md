# Piercing Time - UE LIFAPCD

Projet réalisé dans le cadre de **(LIFAPCD)**.

## 👥 Contributeurs
- **Développeurs :**
    - Nicolas de Brebisson : 12402839
    - Lina Guellali : 12405561
    - Charlie Merchadou : 12303354

## 📋 Description
Piercing Time est un jeu de type ROGUELIKE développé en C++ utilisant la bibliothèque SFML et une config en .json. 
Le jeu intègre un système de vagues d'ennemis, une gestion d'inventaire, une boutique d'objets, et un mode multijoueur EN LIGNE.

## 📚 Bibliothèques utilisées
- **SFML (Simple and Fast Multimedia Library) :** Utilisée pour le rendu graphique, la gestion des fenêtres et des entrées clavier/souris.
- **nlohmann/json (json.hpp) :** Utilisée pour la gestion et le parsing des fichiers de configuration au format JSON (système de vagues). 
  *Auteur : Niels Lohmann.*

## ⚙️ Prérequis
Pour compiler et exécuter ce projet, assurez-vous d'avoir installé :
- Un compilateur C++ compatible (g++).
- La bibliothèque **SFML** (3.0 ou supérieur).

## 🌐 Configuration Réseau (Multijoueur)
Le projet supporte le mode multijoueur via une connexion réseau. Pour configurer l'adresse IP du serveur :

1. Ouvrez le fichier source correspondant (vérifiez à la **ligne 443**).
2. Localisez la ligne suivante :
   ```cpp
   sf::IpAddress ip(88, 184, 64, 49);

## 🚀 Compilation
Le projet utilise un `Makefile`. Pour compiler, placez-vous à la racine du dossier et exécutez la commande suivante dans votre terminal :

```bash
makeclean && make
```
-Puis entrez la commande:
```bash
./bin/PiercingTime
```


**NOTE IMPORTANTE :** Un avertissement (warning) concernant l'utilisation de `memcpy` peut apparaître lors de la compilation. Ce warning peut être ignoré sans risque, car il n'affecte pas le bon fonctionnement du programme.

## Liste des fichiers du projet

### Fichiers Sources (.cpp)
- Bullet.cpp
- Enemy.cpp
- Game.cpp
- IHM.cpp
- IHMServeur.cpp
- Inventory.cpp
- mainDispatcher.cpp
- MainMenu.cpp
- mainTest.cpp
- Map.cpp
- Player.cpp
- Position.cpp
- Shop.cpp

### Fichiers Headers (.h)
- Bullet.h
- Controls.h
- Enemy.h
- Game.h
- IHM.h
- IHMServeur.h
- Inventory.h
- Item.h
- MainMenu.h
- Map.h
- Player.h
- Position.h
- Shop.h
- stats.h
