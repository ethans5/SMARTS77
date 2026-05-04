# SMARTS77 - Système Temps Réel : Gestion de Tâches Périodiques

Ce projet est une extension du système d'exploitation temps réel minimaliste **SMARTS**, réalisée dans le cadre du cours de **Systèmes réactifs et temps réel (153203)**. L'objectif principal de ce projet est d'ajouter le support pour la **gestion de tâches périodiques**.

## Objectif du Projet

L'objectif initial du projet est d'enrichir le noyau SMARTS de base (qui ne gérait que des tâches uniques) pour permettre le traitement de **tâches périodiques**. Le système est désormais capable de :
1. Planifier et exécuter des tâches qui se répètent à intervalles réguliers (`cycleTime`).
2. Limiter le nombre d'exécutions d'une tâche à un nombre défini de cycles (`cycleCount`).
3. Gérer les priorités d'ordonnancement de façon dynamique (via des algorithmes temps réel).

## Concepts Clés

### Ordonnancement Temps Réel
Dans les systèmes réactifs, chaque tâche doit non seulement produire un résultat correct, mais aussi le produire **à temps** (avant sa _deadline_). 
L'algorithme de planification choisi est donc essentiel :

- **EDF (Earliest Deadline First) :** C'est un algorithme dynamique optimal pour les processeurs uniques. À chaque instant, la tâche dont la date limite (deadline) est la plus proche est sélectionnée pour être exécutée. Cela garantit une réactivité maximale pour les tâches les plus urgentes.
- **Round Robin (Tourniquet) :** L'algorithme classique d'ordonnancement préemptif. Chaque tâche obtient un _quantum_ (une tranche de temps) de processeur à tour de rôle. Contrairement à EDF, il ne prend pas en compte l'urgence (les deadlines) d'une tâche mais s'assure qu'aucune tâche n'est affamée.

Dans ce projet, vous pouvez sélectionner l'algorithme désiré (Round Robin ou EDF) au démarrage du système dans `APP77.CPP`.

## Fonctionnement Technique

### Gestion des Cycles via `handleTimers()`
Le temps dans SMARTS est rythmé par l'interruption de l'horloge. La fonction `handleTimers()` est appelée régulièrement. Elle a été mise à jour pour :
- Décrémenter le `cycleCounter` de chaque tâche à chaque "tic" d'horloge.
- Détecter lorsqu'un cycle est écoulé (`cycleCounter == 0`).
- Si la tâche doit encore s'exécuter (`cycleCount > 0`), elle déclenche la fonction `reDeclare()` de la tâche.

### Relance de Tâche avec `reDeclare()` et Restauration de Contexte
Pour qu'une tâche puisse s'exécuter à nouveau, il ne suffit pas de changer son statut à `READY`. Il faut **réinitialiser son contexte (Stack / Pile d'exécution)**.
Dans `Task::reDeclare()`, nous effectuons une restauration complète de la pile :
1. Les registres du microprocesseur (BP, DI, SI, DS, ES, DX, CX, BX, AX, FLAGS) sont réinitialisés pour éviter les effets de bord d'un cycle à l'autre.
2. Le pointeur d'instruction (`taskCode`) est replacé en haut de la pile, ce qui ordonne au processeur de recommencer l'exécution de la fonction au début.
3. L'adresse de retour (`taskEnd`) est replacée pour garantir que la tâche termine toujours proprement si elle atteint sa fin.

## Sécurité et Robustesse : Mécanisme de "Deadlock" (Failure Handling)

Un aspect critique d'un système temps réel strict est la détection d'erreurs d'échéance.
Dans `reDeclare()`, une vérification de sécurité (Failure Handling) est effectuée :
```cpp
if (status == READY || status == RUNNING) {
    printf("ERREUR : tache %c encore active au debut d'un nouveau cycle!\n", name);
    exit(1);
}
```
Si le cycle précédent s'est écoulé et qu'un nouveau cycle doit démarrer, mais que la tâche n'a pas encore eu le temps de finir (elle est toujours en état `RUNNING` ou `READY`), cela indique un non-respect flagrant des contraintes de temps réel. 
Dans ce cas, le système déclenche un arrêt d'urgence ("Deadlock") car il n'est plus en mesure de garantir les échéances.

## Instructions de Compilation

Le code a été développé et testé pour fonctionner sous environnement DOS. 

- **Compilateur :** **Borland C++ 3.1**
- **Compilation :** Pour compiler le projet, un script batch est fourni. Lancez l'environnement de commandes (DOSBox si vous êtes sur Windows 10/11) et exécutez simplement la commande :

```bat
make.bat
```
Cela compilera les fichiers `.CPP` et liera les objets pour produire l'exécutable final. Il suffit ensuite de lancer l'exécutable généré (`APP77.EXE` ou équivalent) pour observer l'ordonnancement temps réel.
