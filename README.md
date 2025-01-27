# Démineur-C

**Démineur-C** est un jeu développé en C en utilisant la bibliothèque graphique **SDL2**.  
Le but du jeu est de révéler toutes les cases sans tomber sur une bombe, en fonction des indices affichés sur le plateau.

---

## Fonctionnalités principales
- **Gameplay :**
  - Jouez au classique jeu du démineur avec plusieurs niveaux de difficulté.
  - Découvrez les bombes grâce aux chiffres indiquant leur proximité.
  - Utilisez une interface graphique créée avec SDL2.
- **Niveaux de difficulté :**
  - **Facile :** 10x10 cases avec 15 bombes.
  - **Moyen :** 15x15 cases avec 30 bombes.
  - **Difficile :** 20x20 cases avec 50 bombes.

---

## Installation et Configuration

### Pré-requis
- **Compilateur C** (par exemple, GCC).
- **Bibliothèque SDL2 :** Assurez-vous que la bibliothèque **SDL2** est installée sur votre système.
  - Vous pouvez télécharger SDL2 depuis [ce lien](https://www.libsdl.org/).

### Étapes d'installation
1. **Installation de SDL2 :**
   - Installez la bibliothèque SDL2 sur votre système.
     - Sous Linux : Utilisez `sudo apt-get install libsdl2-dev`.
     - Sous Windows : Téléchargez le fichier d'installation et configurez-le avec votre IDE.
2. **Compilation du projet :**
   - Clonez ou téléchargez le projet.
   - Compilez le code source avec la commande suivante (exemple pour GCC) :
     ```bash
     gcc -o demineur main.c -lSDL2
     ```
3. **Ajout des ressources :**
   - Placez les dossiers contenant les images nécessaires dans le répertoire du projet.

---

## Utilisation
1. Lancez le jeu à l'aide de l'exécutable généré après la compilation.
2. Choisissez un niveau de difficulté et commencez à jouer.
3. Essayez de révéler toutes les cases sans déclencher une bombe !

---

## Technologies utilisées
- **Langage :** C
- **Bibliothèque graphique :** SDL2
- **Outils de développement :** CLion
