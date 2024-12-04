#include "../include/logger.h"

#include <stdio.h>

void log_error(char *error) {
  fprintf(stderr, "%s\n", error);
}

void log_info(char *info) {
  fprintf(stdout, "%s\n", info);
}