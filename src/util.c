#include "../include/util.h"

#include <stdlib.h>

#include "../include/logger.h"

void sysexit(int exit_code) {
  log_info("Exiting program...");
  exit(exit_code);
}