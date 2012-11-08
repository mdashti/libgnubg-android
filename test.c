#include "nativeAPI.h"

//UTILS: PRINT A BOARD
void printBoard(ConstTanBoard board) {
  int i, j;
  char buf[200];
  sprintf(buf, "");
  for(i = 0; i<2; i++) {
    for(j=0; j<25; j++) {
      sprintf(buf+strlen(buf), " %d ", board[i][j]);
    }
    sprintf(buf+strlen(buf), "\n");
  }
  MYLOG(buf);
}


//UTILS: PRINT A MOVE
void printMove(int move[8]) {
  int i=0;
  char buf[200];
  sprintf(buf, "MOVE: ");
  sprintf(buf+strlen(buf), "%d/%d ", move[0], move[1]);
  sprintf(buf+strlen(buf), "%d/%d ", move[2], move[3]);
  sprintf(buf+strlen(buf), " | %d/%d ", move[4], move[5]);
  sprintf(buf+strlen(buf), "%d/%d", move[6], move[7]);
  sprintf(buf+strlen(buf), "\n");
  MYLOG(buf);
}


//UTILS: PRINT A COUPLE OF DICES
void printDices(int dices[2]) {
  int i=0;
  char buf[200];
  sprintf(buf, "DICES: %d %d\n", dices[0], dices[1]);
  MYLOG(buf);
}


void testResignation() {
  char buf[200];
  int b[2][25] = 
  {
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15}
  };
  setBoard((ConstTanBoard)b);
  ms.fMove = 1;
  ms.fTurn = 0;
  ms.nCube = -1;
  ms.fCubeOwner = 1;
  ms.anScore[0] = 0;
  ms.anScore[1] = 0;
  ms.nMatchTo = 7;

  MYLOG("\nTEST ACCETTAZIONE RESIGN...\n");
  printBoard(msBoard());
  sprintf(buf, "RESIGN 1: %s\n", acceptResign(1)?"OK":"NO");
  MYLOG(buf);
  sprintf(buf, "RESIGN 2: %s\n", acceptResign(2)?"OK":"NO");
  MYLOG(buf);
  sprintf(buf, "RESIGN 3: %s\n", acceptResign(3)?"OK":"NO");
  MYLOG(buf);
}


void testDoubling() {
  int b[2][25] = 
  {
    {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0}
  };

  char buf[200];
  ms.fMove = 1;
  ms.fTurn = 0;
  ms.anScore[0] = 0;
  ms.anScore[1] = 0;
  ms.nMatchTo = 7;

  setBoard((ConstTanBoard)b);
  MYLOG("\nTEST ACCETTAZIONE DOUBLE...\n");
  printBoard(msBoard());
  sprintf(buf, "ACCETTAZIONE: %s\n", acceptDouble()?"OK":"NO");
  MYLOG(buf);

  ms.fMove = 1;
  ms.fTurn = 0;
  ms.fCubeOwner = 1;
  SwapSides(ms.anBoard);
  printBoard(msBoard());
  sprintf(buf, "ACCETTAZIONE: %s\n\n", acceptDouble()?"OK":"NO");
  MYLOG(buf);
}


void testPlayTurn() {
  int b[2][25] = 
  {
    //MEGLIO NON RADDOPPIARE
    //{0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    //{0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} //PC

    //RICHIESTA DI RADDOPPIO SU 0 A 0
    {1, 1, 2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0}, 
    {0, 2, 2, 3, 0, 3, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} //PC

    //RACE GAME..
    //{0, 0, 0, 0, 2, 5, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, 
    //{0, 0, 0, 2, 0, 4, 2, 2, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0} //PC
  };
  
  char buf[200];

  setBoard((ConstTanBoard)b);
  ms.nCube = 1;
  ms.fCubeOwner = 0;
  ms.fMove = 0;
  ms.fTurn = 0;
  ms.anScore[0] = 4;
  ms.anScore[1] = 6;
  ms.nMatchTo = 7;
  ms.fCrawford = FALSE;

  MYLOG("TEST TURNO IA...\n");
  printBoard((ConstTanBoard)b);
  sprintf(buf, "RESIGN: %d\n", askForResignation());
  MYLOG(buf);
  sprintf(buf, "DOUBLING: %s\n", askForDoubling()?"YES":"NO");
  MYLOG(buf);
  int dices[2] = {6, 3};
  int move[8];
  rollDice(dices);
  printDices(dices);
  evaluateBestMove(dices, move);
  printMove(move);
  MYLOG("\n");
}


void testAll () {
  initEnvironment("./");
  setAILevel(SUPREMO);
  testResignation();
  testDoubling();
  testPlayTurn();
}


int main (int argc, char** argv) {
  testAll();
}
