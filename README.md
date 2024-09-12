# philosophers_42

### Skills learned from project:
- Multithreading
- How to use mutexes to prevent data races
- Optimising code for slow hardware

### Project Goals
Philosophers is a project all about multithreading. The project takes in a user-defined amount of philosophers, which follow these rules:
- One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying!

Each philosopher is represented by a thread and each fork is a mutex. The programme needs to be able to handle up to 200 philosophers (threads), so it takes some optimising to get it running properly on older hardware (an i5-7500 with 8GB of RAM). There's also the risks of deadlocks and data races (where multiple processes try to access the same piece of memory), so mutexes are needed to keep everything running smoothly. These add quite a bit of performance overheat though, so these need to be optimised as much as possible.
