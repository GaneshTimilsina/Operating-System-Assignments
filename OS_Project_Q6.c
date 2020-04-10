#include <pthread.h>
#include <unistd.h>
extern int initialize_bowls(unsigned int bowlcount);

extern void cat_eat(unsigned int bowlnumber);
extern void mouse_eat(unsigned int bowlnumber);
extern void cat_sleep(void);
extern void mouse_sleep(void);
int NumBowls;  // number of food bowls
int NumCats;   // number of cats
int NumMice;   // number of mice
int NumLoops;  // number of times each cat and mouse should eat
struct semaphore *CatMouseWait;
static void cat_simulation(void * unusedpointer, unsigned long catnumber)
{
  int i;
  unsigned int bowl;
  (void) unusedpointer;
  (void) catnumber;
  for(i=0;i<NumLoops;i++) {
    cat_sleep();
    bowl = ((unsigned int)random() % NumBowls) + 1;
    cat_eat(bowl);
}
  V(CatMouseWait); 
}
static void mouse_simulation(void * unusedpointer, unsigned long mousenumber)
{
  int i;
  unsigned int bowl;
  (void) unusedpointer;
  (void) mousenumber;
  for(i=0;i<NumLoops;i++) {
    mouse_sleep();
    bowl = ((unsigned int)random() % NumBowls) + 1;
    mouse_eat(bowl);
 }
  V(CatMouseWait); 
}
int catmouse(int nargs, char ** args)
{
  int index, error;
  int i;
  if (nargs != 5) {
  kprintf("Usage: <command> NUM_BOWLS NUM_CATS NUM_MIC NUM_LOOPS\n");
    return 1;  // return failure indication
  }
  NumBowls = atoi(args[1]);
  if (NumBowls <= 0) {
    kprintf("catmouse: invalid number of bowls: %d\n",NumBowls);
    return 1;
  }
  NumCats = atoi(args[2]);
  if (NumCats < 0) {
    kprintf("catmouse: invalid number of cats: %d\n",NumCats);
    return 1;
  }
  NumMice = atoi(args[3]);
  if (NumMice < 0) {
    kprintf("catmouse: invalid number of mice: %d\n",NumMice);
    return 1;
  }
  NumLoops = atoi(args[4]);
  if (NumLoops <= 0) {
    kprintf("catmouse: invalid number of loops: %d\n",NumLoops);
    return 1;
  }
  kprintf("Using %d bowls, %d cats, and %d mice. Looping %d times.\n",
  NumBowls,NumCats,NumMice,NumLoops);
  CatMouseWait = sem_create("CatMouseWait",0);
  if (CatMouseWait == NULL) {
    panic("catmouse: could not create semaphore\n");
  }
  if (initialize_bowls(NumBowls)) {
    panic("catmouse: error initializing bowls.\n");
  }
  for (index = 0; index < NumCats; index++) {
    error = thread_fork("cat_simulation thread",NULL,index,cat_simulation,NULL);
    if (error) {
      panic("cat_simulation: thread_fork failed: %s\n", strerror(error));
    }
  }
  for (index = 0; index < NumMice; index++) {
    error = thread_fork("mouse_simulation thread",NULL,index,mouse_simulation,NULL);
    if (error) {
      panic("mouse_simulation: thread_fork failed: %s\n",strerror(error));
    }
  } 
  for(i=0;i<(NumCats+NumMice);i++) {
    P(CatMouseWait);
  }
  sem_destroy(CatMouseWait);
return 0;
}

