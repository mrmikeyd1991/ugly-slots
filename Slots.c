#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//
// machine making
//
struct machine {
  int money;
  int moneytaken;
  int moneypaid;
  int mini;
  int major;
  int Jackpot;
  char aone[10];
  char atwo[10];
  char athree[10];
  char bone[10];
  char btwo[10];
  char bthree[10];
  char cone[10];
  char ctwo[10];
  char cthree[10];
};

//
// wheel making
//

char wheelone[7][10] = {
    "Eagle", "Buffalo", "Star", "Boot", "Hat", "Bear",
};

char wheeltwo[7][10] = {
    "Eagle", "Buffalo", "Star", "Boot", "Hat", "Bear",
};

char wheelthree[7][10] = {
    "Eagle", "Buffalo", "Star", "Boot", "Hat", "Bear",
};

void Banner() {
  printw("-----------------------------------\n");
  printw("-      Mikeys Slots Machine       -\n");
  printw("-----------------------------------\n");
}

void Pics(int a) {
  printw("Boot = %d Hat = %d Eagle = %d ", a, a * 2, a * 3);
  printw("Bear = Mini!  Star= Major!, BUFFALOS= JACKPOT BABBY!!!\n");
}

void moneyinfo(struct machine a) {
  printw("Machine money:  %d  ", a.money);
  printw("Machine took:   %d  ", a.moneytaken);
  printw("Machiine paid:  %d  \n", a.moneypaid);
  printw("Mini:   %d Major:  %d  jackpot:  %d  ", a.mini, a.major, a.Jackpot);
}

void machinestats(struct machine a) {
  printw("\n-------------------------------------------\n\n\n");
  printw("A-         %s        %s        %s\n\n\n", a.aone, a.bone, a.cone);
}

void machinestatsb(struct machine a) {

  printw("B-         %s        %s        %s\n\n\n", a.atwo, a.btwo, a.ctwo);
}
void machinestatsc(struct machine a) {

  printw("C-         %s        %s        %s\n\n\n", a.athree, a.bthree,
         a.cthree);
}

void pstats(int a, int b) {
  printw("------------------------------------\n");
  printw("Player Money:  %d\n", a);
  printw("Player Bet:    %d\n", b);
  printw("-------------------------------------------");
}

void controls() { printw("\n\n\n\n\nControls:  w= bet+1 s= bet-1 z=spin"); }

int main() {
  srand(time(0));
  int money = 100;
  int bet = 1;
  int pick;

  initscr();
  cbreak();
  noecho();
  start_color();

  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_CYAN, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);

  struct machine Slots = {100,      100,    0,         100,
                          1000,      10000,  "Buffalo", "Star",
                          "Buffalo", "Star", "Buffalo", "Star",
                          "Buffalo", "Star", "Buffalo"};
  // printw("Slots machine money:  %d", Slots.money);
  while (1) {
    if (bet > money) {
      bet = 1;
    }

    if (Slots.money <= 0) {
      clear();
      printw("We ran out of money, get out of here\n\n");
      printw("Press something to leave");
      refresh();
      getch();
      endwin();
      return 0;
    }

    attron(COLOR_PAIR(1));
    Banner();
    attron(COLOR_PAIR(2));
    Pics(bet);
    attron(COLOR_PAIR(4));
    moneyinfo(Slots);
    attron(COLOR_PAIR(7));
    machinestats(Slots);
    refresh();
    machinestatsb(Slots);
    refresh();
    machinestatsc(Slots);
    refresh();
    attron(COLOR_PAIR(3));
    pstats(money, bet);
    attron(COLOR_PAIR(5));
    controls();
    pick = getch();

    if (pick == 'q' || pick == 'Q') {
      endwin();
      return 0;
    }

    if (pick == 'w' || pick == 'W') {
      if (bet >= money) {
        bet = 0;
      }

      bet = bet + 1;
    }

    if (pick == 's' || pick == 'S') {
      bet = bet - 1;
      if (bet <= 0) {
        bet = 1;
      }
    }
    // shitty spin thingy
    if (pick == 'z' || pick == 'Z') {
      erase();
      money -= bet;
      Slots.moneytaken += bet;
      Slots.money += bet;
      Slots.mini += bet;
      Slots.major += bet;
      Slots.Jackpot += bet;
      strcpy(Slots.aone, wheelone[rand() % 6]);
      strcpy(Slots.atwo, wheelone[rand() % 6]);
      strcpy(Slots.athree, wheelone[rand() % 6]);
      strcpy(Slots.bone, wheeltwo[rand() % 6]);
      strcpy(Slots.btwo, wheeltwo[rand() % 6]);
      strcpy(Slots.bthree, wheeltwo[rand() % 6]);
      strcpy(Slots.cone, wheelthree[rand() % 6]);
      strcpy(Slots.ctwo, wheelthree[rand() % 6]);
      strcpy(Slots.cthree, wheelthree[rand() % 6]);
      // machine must have enough money to payout the jackpot, good luck
      // "Eagle", "Buffalo", "Star", "Boot", "Hat", "Bear, Rabbit, Snake"
      if ((strcmp(Slots.atwo, Slots.btwo) == 0) &&
          strcmp(Slots.btwo, Slots.ctwo) == 0 &&
          strcmp(Slots.atwo, wheelone[1]) == 0 && Slots.money < Slots.Jackpot) {
        strcpy(Slots.atwo, wheelone[1]);
        strcpy(Slots.btwo, wheeltwo[1]);
        strcpy(Slots.ctwo, wheelthree[2]);
      }
      // machine must have enough to pay out bet BOOT
      if ((strcmp(Slots.atwo, Slots.btwo) == 0) &&
          strcmp(Slots.btwo, Slots.ctwo) == 0 &&
          strcmp(Slots.atwo, wheelone[3]) == 0 && Slots.money < bet) {
        strcpy(Slots.atwo, wheelone[1]);
        strcpy(Slots.btwo, wheeltwo[0]);
        strcpy(Slots.ctwo, wheelthree[5]);
      }
      // machine must have enough to pay out bet * 2
      if ((strcmp(Slots.atwo, Slots.btwo) == 0) &&
          strcmp(Slots.btwo, Slots.ctwo) == 0 &&
          strcmp(Slots.atwo, wheelone[4]) == 0 && Slots.money < bet * 2) {
        strcpy(Slots.atwo, wheelone[3]);
        strcpy(Slots.btwo, wheeltwo[5]);
        strcpy(Slots.ctwo, wheelthree[2]);
      }

      if ((strcmp(Slots.atwo, Slots.btwo) == 0) &&
          strcmp(Slots.btwo, Slots.ctwo) == 0 &&
          strcmp(Slots.atwo, wheelone[2]) == 0 && Slots.money < Slots.major) {
        strcpy(Slots.atwo, wheelone[1]);
        strcpy(Slots.btwo, wheeltwo[0]);
        strcpy(Slots.ctwo, wheelthree[3]);
      }

      if ((strcmp(Slots.atwo, Slots.btwo) == 0) &&
          strcmp(Slots.btwo, Slots.ctwo) == 0 &&
          strcmp(Slots.atwo, wheelone[5]) == 0 && Slots.money < Slots.mini) {
        strcpy(Slots.atwo, wheelone[5]);
        strcpy(Slots.btwo, wheeltwo[2]);
        strcpy(Slots.ctwo, wheelthree[3]);
      }

      if ((strcmp(Slots.atwo, Slots.btwo) == 0) &&
          strcmp(Slots.btwo, Slots.ctwo) == 0 &&
          strcmp(Slots.atwo, wheelone[0]) == 0 && Slots.money < bet * 3) {
        strcpy(Slots.atwo, wheelone[4]);
        strcpy(Slots.btwo, wheeltwo[0]);
        strcpy(Slots.ctwo, wheelthree[3]);
      }
      if ((strcmp(Slots.atwo, Slots.btwo) == 0) &&
          strcmp(Slots.btwo, Slots.ctwo) == 0 &&
          strcmp(Slots.atwo, wheelone[6]) == 0 && Slots.money < bet * 4) {
        strcpy(Slots.atwo, wheelone[4]);
        strcpy(Slots.btwo, wheeltwo[0]);
        strcpy(Slots.ctwo, wheelthree[3]);
      }

      attron(COLOR_PAIR(1));
      Banner();
      attron(COLOR_PAIR(2));
      Pics(bet);
      attron(COLOR_PAIR(4));
      moneyinfo(Slots);
      attron(COLOR_PAIR(7));
      machinestats(Slots);
      machinestatsb(Slots);
      machinestatsc(Slots);
      attron(COLOR_PAIR(3));
      pstats(money, bet);
      attron(COLOR_PAIR(5));
      controls();

      if (strcmp(Slots.atwo, Slots.btwo) == 0 &&
          strcmp(Slots.btwo, Slots.ctwo) == 0) {

        if (strcmp(Slots.atwo, "Boot") == 0) {
          printw("\n\nSlots atwo:  %s\nSlots btwo:  %s\nSlots ctwo:  %s",
                 Slots.atwo, Slots.btwo, Slots.ctwo);
          money = money + bet;
          Slots.moneypaid = Slots.moneypaid + bet;
          Slots.money = Slots.money - bet;
          printw("\n\nYou win!!! $%d   press enter", bet);
          sleep(2);
          printw("Press something to continue....");
          refresh();
          getch();
        }

        if (strcmp(Slots.atwo, "Hat") == 0) {
          printw("\n\nSlots atwo:  %s\nSlots btwo:  %s\nSlots ctwo:  %s",
                 Slots.atwo, Slots.btwo, Slots.ctwo);
          money = money + bet * 2;
          Slots.moneypaid = Slots.moneypaid + bet * 2;
          Slots.money = Slots.money - bet * 2;
          printw("\n\nYou win!!! $%d   press enter", bet * 2);
          refresh();
          sleep(2);
          printw("\nPress somthing to continue....");
          refresh();
          getch();
        }

        if (strcmp(Slots.atwo, "Eagle") == 0) {
          printw("\n\nSlots atwo:  %s\nSlots btwo:  %s\nSlots ctwo:  %s",
                 Slots.atwo, Slots.btwo, Slots.ctwo);
          money = money + bet * 3;
          Slots.moneypaid = Slots.moneypaid + bet * 3;
          Slots.money = Slots.money - bet * 3;
          printw("\n\nYou win!!! $%d   press enter", bet * 3);
          refresh();
          sleep(2);
          printw("Press something to continue....");
          refresh();
          getch();
        }

        if (strcmp(Slots.atwo, "Bear") == 0) {
          money = money + Slots.mini;
          Slots.moneypaid = Slots.moneypaid + Slots.mini;
          Slots.money = Slots.money - Slots.mini;
          printw("\n\nYou win!  $%d", Slots.mini);
          printw("\n\nSlots atwo:  %s\nSlots btwo:  %s\nSlots ctwo:  %s",
                 Slots.atwo, Slots.btwo, Slots.ctwo);
          Slots.mini = 100;
          refresh();
          sleep(2);
          printw("Press something to continue....");
          refresh();
          getch();
          getch();
        }

        if (strcmp(Slots.atwo, "Star") == 0) {
          money = money + Slots.major;
          Slots.moneypaid = Slots.moneypaid + Slots.major;
          Slots.money = Slots.money - Slots.major;
          Slots.major = 1000;
          printw("\n\nYou win!!  $%d", Slots.major);
          printw("\n\nSlots atwo:  %s\nSlots btwo:  %s\nSlots ctwo:  %s",
                 Slots.atwo, Slots.btwo, Slots.ctwo);
          Slots.major = 1000;
          refresh();
          sleep(2);
          printw("Press something to continue....");
          refresh();
          getch();
        }

        if (strcmp(Slots.atwo, "Buffalo") == 0) {
          money = money + Slots.Jackpot;
          Slots.moneypaid = Slots.moneypaid + Slots.Jackpot;
          Slots.money = Slots.money - Slots.Jackpot;
          printw("\n\nYou win!!   $%d", Slots.Jackpot);
          printw("\n\nSlots atwo:  %s\nSlots btwo:  %s\nSlots ctwo:  %s",
                 Slots.atwo, Slots.btwo, Slots.ctwo);
          Slots.Jackpot = 10000;
          refresh();
          sleep(2);
          printw("Press something to continue....");
          refresh();
          getch();
        }
      }

      if (money <= 0) {
        /// clear();
        erase();
        printw("\n\nSorry, your out of money!\n\n\n\n     Press Something to "
               "leave my casino");
        refresh();
        getch();
        /// clear();
        erase();
        endwin();
        return 0;
      }
    }
    refresh();
    // clear();
    erase();
  }
  endwin();
  return 0;
}
