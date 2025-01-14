# philosophers_42

### Skills learned from project: ✅
- The basics of multithreading
- How to use mutexes to prevent data races
- Optimising code for slow hardware

### Project Goal: 🎯
- Solve the [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- The philosophers are reprisented by a thread, the forks by a mutex
- Data races and deadlocks should never occur
- The programme should still work with 200 threads and mutexes, even on older hardware
    (i5-7500 with 8GB of RAM)

### Example:
The programme should be run as: `./philo philo_count time_to_die time_to_eat time_to_sleep [max_eat_count] (optional)`
Here the programme is being run with 4 philosophers, that need to eat every 410ms.
It takes them 200ms to eat and sleep and once they've all eaten 8 times, the simulation stops

### The start of the output of the programme:

![image](https://github.com/user-attachments/assets/e853b2dc-b11c-453f-abe7-91534aca104a)

### The output in a [visualiser](https://nafuka11.github.io/philosophers-visualizer/):

![image](https://github.com/user-attachments/assets/452fd616-bbca-45a8-91bb-ea50e8a93c4d)

### 200 philosophers also run fine:

![image](https://github.com/user-attachments/assets/c55f3601-bc09-4a9e-bde5-58d510c88ae6)
