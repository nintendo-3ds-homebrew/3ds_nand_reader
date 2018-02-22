#ifndef NAND_READER_H
#define NAND_READER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>
#include <stdbool.h>

#define BUFF_SIZE 4096 * 10

char	*seekDevice(void);
char	*concat(char *s1, char *s2);
ssize_t	getNandSize(int fd_device);
bool	is3ds(int fd_device);
bool	dumpNand(char *device);
void	prepareDump(void);

#endif
