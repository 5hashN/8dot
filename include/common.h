#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <locale.h>

#define CALLOC(T, n)   ((T*)calloc((size_t)(n), sizeof(T)))
#define MALLOC(T, n)   ((T*)malloc((size_t)(n) * sizeof(T)))
#define REALLOC(T, p, n) ((T*)realloc((p), (size_t)(n) * sizeof(T)))