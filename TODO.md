# TODO Liste pour Valisp

## Correctifs prioritaires
- [ ] Finaliser l'implémentation de `ramasse_miette_liberer()`
- [ ] Compléter l'algorithme de marquage et balayage du GC
- [ ] Ajouter le support des nombres à virgule flottante
- [ ] Corriger la fonction `div_valisp` pour gérer correctement la division
- [ ] Corriger pour que `div_valisp 4` renvoie 0.25 au lieu de 0
- [ ] Reecrire les tests pour les adapter aux nouvelles implementations

# Correctifs intermédiaires
- [ ] Corriger la gestion de la mémoire dans l'allocateur
- [ ] Résoudre les potentielles fuites mémoire dans `allocateur_free()`
- [ ] Améliorer la gestion des erreurs dans le parseur
- [ ] Améliorer les messages d'erreur pour mieux localiser les problèmes
- [ ] Ajouter des commentaires de style Doxygen

## Extensions du langage
- [ ] Mettre à jour les primitives arithmétiques pour supporter les floats
- [ ] Enrichir la bibliothèque standard (lib/stdlib.val)
- [ ] Ajouter des fonctions de manipulation de chaînes
- [ ] Implémenter des structures de données supplémentaires (tableaux, maps)
- [ ] Implémenter des macros plus avancées
- [ ] Support des boucles génériques (loop, for, etc.)

## Améliorations techniques
- [ ] Optimiser l'interpréteur
- [ ] Réduire les appels récursifs dans `eval` pour éviter le débordement de pile
- [ ] Améliorer la mise en cache des résultats d'évaluation
- [ ] Renforcer les tests
- [ ] Ajouter des tests pour le ramasse-miettes
- [ ] Créer des tests pour `allocateur_free()`
- [ ] Améliorer la couverture de tests pour l'interpréteur
- [ ] Documenter le code
- [ ] Générer une documentation de référence automatique

## Fonctionnalités du REPL
- [ ] Implémenter l'historique persistant entre les sessions
- [ ] Sauvegarder et charger l'historique des commandes dans un fichier
- [ ] Ajouter la complétion de code
- [ ] Auto-complétion des symboles définis et des primitives
- [ ] Créer un mode pas à pas pour le débogage
- [ ] Ajouter des commandes de debugging dans le REPL

## Extensions du système
- [ ] Implémenter le chargement complet de scripts
- [x] Finaliser l'option `-s, --script`
- [ ] Ajouter une primitive `load` pour charger des fichiers pendant l'exécution
- [ ] Créer un système de modules/packages
- [ ] Implémenter un système d'import/export de définitions
- [ ] Gérer les espaces de noms

## Interface utilisateur
- [ ] Améliorer l'affichage dans le REPL
- [ ] Coloration syntaxique de l'entrée
- [ ] Indentation automatique des expressions
- [ ] Ajouter une interface graphique simple
- [ ] Éditeur de code intégré
- [ ] Visualisation de l'environnement et de la mémoire

## Optimisations de performances
- [ ] Optimiser l'allocateur de mémoire
- [ ] Améliorer l'algorithme de recherche de blocs libres
- [ ] Mettre en œuvre une stratégie plus efficace pour la fusion des blocs
- [ ] Accélérer le parseur
- [ ] Réduire les allocations mémoire pendant l'analyse
- [ ] Optimiser le traitement des chaînes longues

## Documentation pour les utilisateurs
- [ ] Créer un guide du langage
- [ ] Manuel de référence des primitives et fonctions
- [ ] Exemples de code pour les débutants
- [ ] Ajouter des exemples plus complexes
- [ ] Algorithmes classiques implémentés en Valisp
- [ ] Mini-projets d'exemple (jeux simples, calculs mathématiques, etc.)

## Portabilité
- [ ] Assurer la compatibilité avec différents systèmes
- [ ] Tester sur Windows et macOS
- [ ] Éliminer les dépendances spécifiques à Linux
- [ ] Créer des scripts de build pour différentes plateformes
- [ ] Ajouter un script CMake ou des configurations pour divers IDE