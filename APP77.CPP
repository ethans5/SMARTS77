/********************************************************************/
/* A Small Real Time System for the Real-Time laboratory            */
/* built by: A.Teitelbaum on an idea of H.G.Mendelbaum              */
/* Jerusalem College of Technology, 5759-64 (1999-03)               */
/* update  Tishrey   5777                                           */
/* APP77.CPP, an application to demonstrate SMARTS77  functioning   */
/********************************************************************/
#include "smarts77.h"

// user Functions
void a( )
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j=0; j <10; j++)
	{
		for (int i=0; i <10000; i++);
		SMARTS.contextSwitchOff();
		cout << "A";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   A Finish   *********************";
	SMARTS.contextSwitchOn();
}

void b( )
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j=0; j <10; j++)
	{
		for (int i=0; i <10000; i++);
		SMARTS.contextSwitchOff();
		cout << "B";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   B Finish   *********************";
	SMARTS.contextSwitchOn();
}

void c( )
{
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Start    *********************";
	SMARTS.contextSwitchOn();
	for (int j=0; j <10; j++)
	{
		for (int i=0; i <10000; i++);
		SMARTS.contextSwitchOff();
		cout << "C";
		SMARTS.contextSwitchOn();
	}
	SMARTS.contextSwitchOff();
	cout << "\n *************   C Finish   *********************";
	SMARTS.contextSwitchOn();
}

void main( )
{
	// clrscr();
	// SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, roundRobin);
	// SMARTS.declareTask(a,'A');
	// SMARTS.declareTask(b,'B');
	// SMARTS.declareTask(c,'C');
	// SMARTS.runTheTasks();
    clrscr();
    // Utilisation de l'algorithme EDF ou Round Robin (a decommenter selon le besoin)
    // SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, EDF); 
    SMARTS.externalFunctions(timerInterruptHandler, scheduler, myTaskEnd, roundRobin); 

    // Declaration des taches avec leurs parametres periodiques (fonction, nom, cycleTime, cycleCount)
    SMARTS.declareTask(a, 'A', 5,  3);  // cycleTime=5,  cycleCount=3 (s'executera 3 fois, un cycle tous les 5 ticks)
    SMARTS.declareTask(b, 'B', 7,  4);  // cycleTime=7,  cycleCount=4 (s'executera 4 fois, un cycle tous les 7 ticks)
    SMARTS.declareTask(c, 'C', 10, 5);  // cycleTime=10, cycleCount=5 (s'executera 5 fois, un cycle tous les 10 ticks)

    SMARTS.runTheTasks();

}



