#include "../include/3ds_nand_reader.h"

char	*concat(char *s1, char *s2)
{
	auto char	*result = calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));

	if (!result)
		errx(EXIT_FAILURE, "Malloc error");
	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}

char	*seekDevice(void)
{
	auto struct dirent	*st_directory = NULL;
	auto char			*block_name = NULL;
	auto DIR			*directory = NULL;
	auto ino_t			inode = 0;

	directory = opendir("/dev");
	if (!directory)
		err(EXIT_FAILURE, "opendir error");
	while ((st_directory = readdir(directory)))
	{
		if (!(st_directory->d_type ^ DT_BLK) && st_directory->d_ino > inode)
		{
			inode = st_directory->d_ino;
			block_name = st_directory->d_name;
		}
	}
	return (block_name);
}

void	dumpNand(char *device)
{
	auto int		fd_file = 0;
	auto int		fd_device = 0;
	auto char		buff[4096] = {0};
	auto off_t		nandSize = 0;
	auto ssize_t	size = 0;

	fd_device = open(device, O_RDONLY);
	if (fd_device == -1)
		err(EXIT_FAILURE, "open device");

	nandSize = lseek(fd_device, 0, SEEK_END);
	if (nandSize == -1)
		err(EXIT_FAILURE, "lseek");

	if (lseek(fd_device, (off_t)0, SEEK_SET) == -1)
		err(EXIT_FAILURE, "lseek");

	fd_file = open("./dump/nand", O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd_file == -1)
		err(EXIT_FAILURE, "open nand file");

	while (nandSize)
	{
		printf("%d              \r", nandSize);
		size = read(fd_device, &buff, 4096);
		if (size == -1)
			err(EXIT_FAILURE, "read");
		if (write(fd_file, &buff, size) == -1)
			err(EXIT_FAILURE, "write");
		nandSize -= 4096;
	}
	printf("\rFinish\n");
}

void	prepareDump(void)
{
	auto struct stat st = {0};

	if (stat("./dump", &st) == -1)
		mkdir("./dump", 0666);
}

int	main(int argc, char **argv)
{
	auto char	*device = NULL;

	printf("Plug your 3ds now, then press a key\n");

	getchar();

	device = concat("/dev/", seekDevice());

	printf("Device name : %s\n", device);

	prepareDump();
	dumpNand(device);
	free(device);
}
