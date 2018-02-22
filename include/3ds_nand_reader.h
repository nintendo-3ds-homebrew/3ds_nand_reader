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
#include <stdint.h>

#define BUFF_SIZE 4096

#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define END "\033[0m"

char	*seekDevice(void);
char	*concat(char *s1, char *s2);
ssize_t	getNandSize(int fd_device);
bool	is3ds(int fd_device);
bool	dumpNand(char *device, uint8_t nbNand);
void	prepareDump(void);
void		usage(void);

#endif
