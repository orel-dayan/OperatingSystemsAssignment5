# **Operating System Course Assigment 5**

University assignment 5 for Operating System course in Ariel University.

## **Description**

 This assignment divided into 4 parts:
    -  **st_pipeline** - The main program that runs the program.
    -  **Queue** - The blocking queue of the program.
    -  **ActiveObject** - The active object of the program that runs the threads.
    -  **Math** - The math part of the program that checks if the number is prime.
 In this program, we use the Active Object Pattern to create a pipeline of active objects that generate, print, check and manipulate numbers.
 Each active object is independent and safe to use concurrently with the others.
 The method invocation on the active object  is decoupled from its execution by a queue which is thread-safe due to the use of mutex locks.



## **Requirements**
- Ubuntu 22.04 LTS
- GNU C compiler
- Make

## **Getting Started**


```sh

  make all
  ./st_pipeline <SEED>
   ```

## **Authors**
- Orel Dayan
- Evaytar yosef

## **Links:**

- https://jyos-sw.medium.com/blocking-queues-implementation-in-c-7ee9f9e84307

- https://rosettacode.org/wiki/Active_object

- https://stackoverflow.com/questions/44175151/what-is-the-meaning-of-lm-in-gcc


