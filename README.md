# Valisp - Un interpréteur Lisp simplifié

Ce projet est une implémentation d'un interpréteur Lisp simplifié appelé Valisp, écrit en C. Il comprend un allocateur de mémoire personnalisé, un système de types, et des primitives du langage.

## Structure du projet

```
valisp/
├── include/                 # Fichiers d'en-tête (.h)
│   ├── memory/              # Gestion de la mémoire
│   │   ├── allocateur.h     # Allocateur de mémoire personnalisé
│   │   └── memoire.h        # Interface de haut niveau pour la mémoire
│   ├── types/               # Types de données
│   │   └── types.h          # Définition des types du langage (sexpr, etc.)
│   ├── primitives/          # Primitives du langage
│   │   └── primitives.h     # Fonctions primitives du langage
│   └── utils/               # Utilitaires
│       ├── couleurs.h       # Gestion des couleurs pour l'affichage
│       ├── erreur.h         # Gestion des erreurs
│       └── tests.h          # Utilitaires pour les tests
├── src/                     # Code source
│   ├── memory/              # Implémentation de la gestion mémoire
│   ├── types/               # Implémentation des types
│   ├── primitives/          # Implémentation des primitives
│   ├── utils/               # Implémentation des utilitaires
│   ├── tests/               # Tests des fonctionnalités
│   └── main.c               # Point d'entrée du programme
├── build/                   # Fichiers de compilation générés
│   ├── memory/
│   ├── types/
│   ├── primitives/
│   ├── utils/
│   └── tests/
├── bin/                     # Exécutables générés
├── Makefile                 # Configuration de compilation
└── README.md                # Ce fichier
```

## Fonctionnalités

- **Allocateur de mémoire personnalisé**: Implémentation d'un système d'allocation mémoire avec ramasse-miettes
- **Système de types**: Support des types de base (entiers, chaînes, symboles, listes)
- **Primitives du langage**: Fonctions de base du langage Lisp
- **Tests intégrés**: Suite de tests pour vérifier le bon fonctionnement des composants

## Compilation

Pour compiler le projet, utilisez:

```bash
make
```

Cela générera l'exécutable `bin/valisp`.

Pour nettoyer les fichiers générés:

```bash
make clean
```

## Exécution des tests

Le projet inclut plusieurs tests pour les différentes fonctionnalités. Pour exécuter les tests:

```bash
make test
```

Vous pouvez également exécuter des tests spécifiques en modifiant le fichier `main.c` pour n'appeler que certaines fonctions de test.

## Système de mémoire

Le projet utilise un allocateur de mémoire personnalisé avec les caractéristiques suivantes:
- Allocation dynamique de blocs de mémoire
- Système de ramasse-miettes basique
- Fonctions d'allocation et de libération explicites

## Système de types

Les types principaux supportés sont:
- **Entiers**: Nombres entiers
- **Chaînes**: Séquences de caractères
- **Symboles**: Identifiants pour les variables et fonctions
- **Listes**: Structure de données fondamentale en Lisp
- **Primitives**: Fonctions intégrées du langage

## Contribution

Pour contribuer au projet:
1. Assurez-vous que votre code respecte les conventions existantes
2. Ajoutez des tests pour les nouvelles fonctionnalités
3. Mettez à jour la documentation si nécessaire

## Auteur

Alexandre Bertho
