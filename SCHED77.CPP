/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory                 */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum                  */
/* Jerusalem College of Technology, 5759-64 (1999)                            */
/* SchedAlgo64.CPP, short-term scheduler algorithms                */
/****************************************************************/


#include "smarts77.h"

int far roundRobin( )
// Round Robin short-term algorithm 
{
	int count;
	int nextTask = (SMARTS.getCurrentTask()+1)%SMARTS.getTotalTasks( );
	for (count=0;
	     SMARTS.getStatus(nextTask)!=READY && count<SMARTS.getTotalTasks( );
	     count++)
	     nextTask=++nextTask%SMARTS.getTotalTasks( );
	if (count == SMARTS.getTotalTasks( ))	// no found READY task to run
		nextTask = SMARTS.getTotalTasks( );
	return nextTask;
}
int far EDF()
// EDF (Earliest Deadline First) short-term algorithm
{
    int nextTask = -1;
    int earliestDeadline = MAXINT;

    for (int i = 0; i < SMARTS.getTotalTasks(); i++)
    {
        if (SMARTS.getStatus(i) == READY)
        {
            if (SMARTS.getDeadline(i) < earliestDeadline)
            {
                earliestDeadline = SMARTS.getDeadline(i);
                nextTask = i;
            }
        }
    }

    if (nextTask == -1)             // aucune tâche READY trouvée
        nextTask = SMARTS.getTotalTasks();  // → IDLE task (comme dans roundRobin)

    return nextTask;
}


