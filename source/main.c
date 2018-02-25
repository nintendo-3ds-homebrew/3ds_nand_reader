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

bool	is3ds(int fd_device)
{
	auto uint32_t		ncsd = 0;

	if (lseek(fd_device, (off_t)0x100, SEEK_SET) == -1) // go to offset  0x100 for checking NSCD
		err(EXIT_FAILURE, "lseek");

	if (read(fd_device, &ncsd, 4) == -1)
		errx(EXIT_FAILURE, "lseek");

	if (NCSD ^ ncsd)
	{
		printf("%s3ds not found%s\n", RED, END);
		return(false);
	}
	else
		printf("%s3DS found\nDump start%s\n", GREEN, END);

	if (lseek(fd_device, (off_t)0, SEEK_SET) == -1)
		err(EXIT_FAILURE, "lseek");

	return(true);
}

ssize_t	getNandSize(int fd_device)
{
	ssize_t	nandSize = 0;

	if (lseek(fd_device, (off_t)0, SEEK_SET) == -1) // Be sure we are at file start
		err(EXIT_FAILURE, "lseek");

	nandSize = lseek(fd_device, 0, SEEK_END); // Go to end of file to get size
	if (nandSize == -1)
		err(EXIT_FAILURE, "lseek");

	if (lseek(fd_device, (off_t)0, SEEK_SET) == -1) // return to start file
		err(EXIT_FAILURE, "lseek");

	return (nandSize);
}

int	createNand(char *nandFile, off_t nandSize)
{
	auto int	fd = 0;

	fd = open(nandFile, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		err(EXIT_FAILURE, "open nand file");
	printf("%s created\nSize nand = %lu\n", nandFile, nandSize);

	return (fd);
}

bool	dumpNand(char *device, uint8_t nbDump)
{
	auto int		fd_file = 0;
	auto int		fd_device = 0;
	auto char		buff[BUFF_SIZE] = {0};
	auto off_t		nandSize = 0;
	auto ssize_t	size = 0;

	fd_device = open(device, O_RDONLY);
	if (fd_device == -1)
		err(EXIT_FAILURE, "open device");

	if (is3ds(fd_device) == false)
		return (false);

	for (uint8_t i = 0; i < nbDump; i++)
	{
		nandSize = getNandSize(fd_device);
		if (i == 0)
			fd_file = createNand("./dump/nand1", nandSize);
		else
			fd_file = createNand("./dump/nand2", nandSize);
		while (nandSize)
		{
			printf("%sBytes left : %lu                 \r%s", GREEN, nandSize, END);
			fflush(stdout);
			size = read(fd_device, &buff, (ssize_t)BUFF_SIZE);
			if (size == -1)
				err(EXIT_FAILURE, "read");
			if (write(fd_file, &buff, (size_t)size) == -1)
				err(EXIT_FAILURE, "write");
			nandSize -= size;
		}
		i == 0 ? printf("\n%sNand1 dump Success\n\n%s", GREEN, END):printf("\n%sNand2 dump Success\n\n%s", GREEN, END);
	}
	printf("%sFinish\n%s", GREEN, END);
	return (true);
}

void	prepareDump(void)
{
	auto struct stat st = {0};

	if (stat("./dump", &st) == -1)
		mkdir("./dump", 0666);
}

void	usage(void)
{
	errx(EXIT_FAILURE, "Usage : ./3ds_nand_reader 1 (for one dump)\n\t\t\t\t ./3ds_nand_reader 2 (for two dumps)");
}

int	main(int argc, char **argv)
{
	auto char	*device = NULL;

	if (argc != 2)
		usage();
	printf("%sPlug your 3ds now, then press a key%s\n", YELLOW, END);
	getchar();

	device = concat("/dev/", seekDevice());

	printf("%sLast device plugged : %s\n%s", YELLOW, device, END);

	prepareDump();
	dumpNand(device, (uint8_t)atoi(argv[1]));
	free(device);

	return (0);
}
