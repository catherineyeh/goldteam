/* 
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
 */


/*
 * 
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>


/*
 *
 * Constants
 *
 */

/*
 * Number of cars created.
 */

#define NCARS 20

/*
 * Directions
 */ 

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define RIGHT_TURN 4
#define STRAIGHT 5
#define LEFT_TURN 6

/*
 * Global variables
 */

struct lock *leftturnlock;
struct lock *nApproach;
struct lock *eApproach;
struct lock *sApproach;
struct lock *wApproach;
struct lock *segments[4];
struct lock *carvar;
struct cv *nWait;
struct cv *eWait;
struct cv *sWait;
struct cv *wWait;
int numcarsleft;

/*
 *
 * Function Definitions
 *
 */


/*
 * gostraight()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement passing straight through the
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
gostraight(unsigned long cardirection, unsigned long carnumber)
{
  /*
   * Avoid unused variable warnings.
   */

  (void) cardirection;
  (void) carnumber;

  switch (cardirection) {
    case NORTH:
      lock_acquire(segments[0]);
      lock_acquire(segments[2]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(nApproach);
      lock_release(segments[0]);
      lock_release(segments[2]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case EAST:
      lock_acquire(segments[1]);
      lock_acquire(segments[0]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(eApproach);
      lock_release(segments[1]);
      lock_release(segments[0]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case WEST:
      lock_acquire(segments[2]);
      lock_acquire(segments[3]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(wApproach);
      lock_release(segments[2]);
      lock_release(segments[3]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case SOUTH:
      lock_acquire(segments[3]);
      lock_acquire(segments[1]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(sApproach);
      lock_release(segments[3]);
      lock_release(segments[1]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
  }
  lock_acquire(carvar);
  numcarsleft = numcarsleft - 1;
  lock_release(carvar);
}


/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnleft(unsigned long cardirection, unsigned long carnumber)
{
  /*
   * Avoid unused variable warnings.
   */

  (void) cardirection;
  (void) carnumber;

  switch (cardirection) {
    case NORTH:
      lock_acquire(leftturnlock);
      lock_acquire(segments[0]);
      lock_acquire(segments[2]);
      lock_acquire(segments[3]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(nApproach);
      lock_release(segments[0]);
      lock_release(segments[2]);
      lock_release(segments[3]);
      lock_release(leftturnlock);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case EAST:
      lock_acquire(leftturnlock);
      lock_acquire(segments[1]);
      lock_acquire(segments[0]);
      lock_acquire(segments[2]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(eApproach);
      lock_release(segments[1]);
      lock_release(segments[0]);
      lock_release(segments[2]);
      lock_release(leftturnlock);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case WEST:
      lock_acquire(leftturnlock);
      lock_acquire(segments[2]);
      lock_acquire(segments[3]);
      lock_acquire(segments[1]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(wApproach);
      lock_release(segments[2]);
      lock_release(segments[3]);
      lock_release(segments[1]);
      lock_release(leftturnlock);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case SOUTH:
      lock_acquire(leftturnlock);
      lock_acquire(segments[3]);
      lock_acquire(segments[1]);
      lock_acquire(segments[0]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(sApproach);
      lock_release(segments[3]);
      lock_release(segments[1]);
      lock_release(segments[0]);
      lock_release(leftturnlock);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
  }
  lock_acquire(carvar);
  numcarsleft = numcarsleft - 1;
  lock_release(carvar);
}


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long cardirection: the direction from which the car
 *              approaches the intersection.
 *      unsigned long carnumber: the car id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long cardirection, unsigned long carnumber)
{
  /*
   * Avoid unused variable warnings.
   */

  (void) cardirection;
  (void) carnumber;

  switch (cardirection) {
    case NORTH:
      lock_acquire(segments[0]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(nApproach);
      lock_release(segments[0]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case EAST:
      lock_acquire(segments[1]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(eApproach);
      lock_release(segments[1]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case WEST:
      lock_acquire(segments[2]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(wApproach);
      lock_release(segments[2]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
    case SOUTH:
      lock_acquire(segments[3]);
      kprintf("Car %lu is entering the intersection\n", carnumber);
      lock_release(sApproach);
      lock_release(segments[3]);
      kprintf("Car %lu is leaving the intersection\n", carnumber);
      break;
  }
  lock_acquire(carvar);
  numcarsleft = numcarsleft - 1;
  lock_release(carvar);
}


/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long carnumber: holds car id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createcars().  Each one must choose a direction
 *      randomly, approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 */

static
void
approachintersection(void * unusedpointer, unsigned long carnumber)
{
  (void) unusedpointer;
  int cardirection;
  int turnChoice;

  turnChoice = (random() % 3)+4;
  cardirection = random() % 4; 


  kprintf("Car %lu is approaching the intersection\n", carnumber);

  switch (cardirection) {
    case NORTH:
      lock_acquire(nApproach);
      cv_wait(nWait, nApproach);
      break;
    case EAST:
      lock_acquire(eApproach);
      cv_wait(eWait, eApproach);
      break;
    case SOUTH:
      lock_acquire(sApproach);
      cv_wait(sWait, sApproach);
      break;
    case WEST:
      lock_acquire(wApproach);
      cv_wait(wWait, wApproach);
      break;
  }

  switch (turnChoice) {
    case RIGHT_TURN:
      turnright(cardirection, carnumber);
      break;
    case LEFT_TURN:
      turnleft(cardirection, carnumber);
      break;
    case STRAIGHT:
      gostraight(cardirection, carnumber);
      break;
  }
}

void stoplight() {
  int i;
  while (numcarsleft) {
    for (i = 0; i < NCARS; ++i) {
      cv_signal(nWait, nApproach);
      cv_signal(sWait, sApproach);
    }
    for (i = 0; i < NCARS; ++i) {
      cv_signal(eWait, eApproach);
      cv_signal(wWait, wApproach);
    }
  }
}

/*
 * createcars()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createcars(int nargs, char ** args)
{
  int index, error;

  leftturnlock = lock_create("leftturnlock");
  nApproach = lock_create("nApproach");
  eApproach = lock_create("eApproach");
  sApproach = lock_create("sApproach");
  wApproach = lock_create("wApproach");
  carvar = lock_create("carvar");
  nWait = cv_create("nWait");
  eWait = cv_create("eWait");
  sWait = cv_create("sWait");
  wWait = cv_create("wWait");
  segments[0] = lock_create("nw");
  segments[1] = lock_create("ne");
  segments[2] = lock_create("sw");
  segments[3] = lock_create("se");

  numcarsleft = 20;

  /*
   * Avoid unused variable warnings.
   */

  (void) nargs;
  (void) args;

  /*
   * Start NCARS approachintersection() threads.
   */

  for (index = 0; index < NCARS; index++) {

    error = thread_fork("approachintersection thread",
        NULL,
        index,
        approachintersection,
        NULL
        );

    /*
     * panic() on error.
     */

    if (error) {

      panic("approachintersection: thread_fork failed: %s\n",
          strerror(error)
          );
    }
  }

  /*
   * Start stoplight
   */

  stoplight();

  return 0;
}
