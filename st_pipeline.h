#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Math.h"
#include "ActiveObject.h"

/**
 * @brief Task2 prints generated number, checks if it is prime , add 11 and transfer to Task3
 */

void Task2(void *, ActiveObject *);

/**
 * @brief Task3 prints generated number, checks if it is prime , decrease 13 and transfer to Task4
 */

void Task3(void *, ActiveObject *);

/**
 * @brief Task4 prints generated number, checks if it is prime , add 2
 */

void Task4(void *, ActiveObject *);
