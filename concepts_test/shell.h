#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

char *_getenv(const char *name);

#endif
