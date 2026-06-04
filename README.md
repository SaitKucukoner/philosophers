*This project has been created as part of the 42 curriculum by skucukon.*

# Philosophers

## Description
This project is an implementation of the classic "Dining Philosophers Problem" designed to teach the fundamentals of multi-threading, process synchronization, and memory sharing in C. The core objective is to manage concurrent threads (representing philosophers) and shared resources (representing forks) using mutexes to prevent fatal issues such as Data Races and Deadlocks. The simulation requires philosophers to alternately eat, sleep, and think without starving to death.

## Instructions

### Installation

	Clone the repository:

	git clone <repository_url>

	cd philosophers

### Compilation
	To compile the project, navigate to the project root directory and use the provided Makefile.

	make
	make clean
	make fclean
	make re

### Execution
	Run the executable with the following arguments:
	./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

	Example; ./philo 5 800 200 200

## Resources

    https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
    https://www.geeksforgeeks.org/operating-systems/posix-threads-in-os/
	https://man7.org/linux/man-pages/man7/pthreads.7.html
	https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html

## AI Usage Disclosure

During the development of this project, AI was utilized as an educational tool and technical advisor. Specifically, AI was used for:

	Reviewing thread synchronization principles and memory barrier patterns.

	Validating the asymmetric even/odd strategy to break circular wait conditions (preventing deadlocks).

	Analyzing edge cases such as single-philosopher executions and thread initialization delays to eliminate race conditions on simulation startup.
	All architectural decisions and actual code implementations were executed by me and remain my sole responsibility.