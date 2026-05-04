/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory                 */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum                  */
/* Jerusalem College of Technology, 5759-64 (1999)                            */
/* SchedAlgo64.CPP, short-term scheduler algorithms                */
/****************************************************************/


#include "smarts77.h"

int far roundRobin()
{
    int total = SMARTS.getTotalTasks();
    if (total == 0) return 0;

    int count;
    int nextTask = (SMARTS.getCurrentTask() % total + 1) % total;

    for (count = 0;
         SMARTS.getStatus(nextTask) != READY && count < total;
         count++)
        nextTask = (nextTask + 1) % total;

    if (count == total)
        nextTask = total; // IDLE task

    return nextTask;
}
int far EDF()
// Algorithme d'ordonnancement EDF (Earliest Deadline First)
// Selectionne la tache dont la date limite (deadline) est la plus proche
{
    int nextTask = -1;
    int earliestDeadline = MAXINT;

    // Parcours de toutes les taches declarees pour trouver la plus urgente
    for (int i = 0; i < SMARTS.getTotalTasks(); i++)
    {
        // On ne considere que les taches pretes a etre executees (READY)
        if (SMARTS.getStatus(i) == READY)
        {
            // Comparaison de la deadline de la tache avec la plus petite trouvee jusqu'a present
            if (SMARTS.getDeadline(i) < earliestDeadline)
            {
                earliestDeadline = SMARTS.getDeadline(i);
                nextTask = i; // On sauvegarde l'index de la tache la plus urgente
            }
        }
    }

    // Si aucune tache READY n'a ete trouvee (par exemple, elles sont toutes en attente)
    if (nextTask == -1)
        nextTask = SMARTS.getTotalTasks();  // -> IDLE task (comme dans roundRobin, tache fictive de repos)

    return nextTask;
}


