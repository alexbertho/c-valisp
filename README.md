# Valisp - Un interpréteur Lisp simplifié

Ce projet est une implémentation d'un interpréteur Lisp simplifié appelé Valisp, écrit en C. Il comprend un allocateur de mémoire personnalisé, un système de types, et des primitives du langage.

Ce projet est réalisé dans le cadre de l'UE "Programmation impérative en C" enseigné par M. Balledon, professeur de cette UE à l'Université Côte d'Azur.

## Structure du projet

```
valisp/
├── include/                 # Fichiers d'en-tête (.h)
├── lib/                     # Bibliothèques interne en lisp
├── src/                     # Code source de l'application
│   ├── interpreter/         # Implémentation de l'interpréteur
│   ├── memory/              # Implémentation de la gestion mémoire
│   ├── parser/              # Implémentation de l'analyseur syntaxique
│   ├── types/               # Implémentation des types
│   ├── primitives/          # Implémentation des primitives
│   ├── utils/               # Implémentation des utilitaires
│   ├── valisp.c             # Fichier principal de l'application
│   └── main.c               # Point d'entrée du programme
├── test/                    # Code source des tests
│   ├── memory/              # Tests pour les composants mémoire
│   ├── primitives/          # Tests pour les primitives
│   ├── types/               # Tests pour les types
│   ├── utils/               # Tests pour les utilitaires
│   └── test_runner.c        # Point d'entrée des tests
├── build/                   # Fichiers de compilation générés
├── bin/                     # Exécutables générés
│   └── valisp               # Exécutable principal
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

Pour exécuter les tests:

```bash
make test
```

Cela générera et exécutera l'exécutable de test `bin/test_valisp`.

Pour nettoyer les fichiers générés:

```bash
make clean
```

## Tests

Le projet inclut une suite de tests pour vérifier le bon fonctionnement des différents composants:

- **Tests de l'allocateur**: Vérifie le fonctionnement de l'allocateur de mémoire
- **Tests des types**: Vérifie le bon fonctionnement des types (entiers, chaînes, symboles, listes)
- **Tests des primitives**: Vérifie le fonctionnement des primitives du langage

Vous pouvez configurer quels tests exécuter en modifiant le fichier `test/test_config.h`.

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

## Documentation Lisp
Une documentation de Lisp est disponible sur ce site: [Lisp Documentation](https://lisp-docs.github.io/cl-language-reference/)

## Auteur

Alexandre Bertho