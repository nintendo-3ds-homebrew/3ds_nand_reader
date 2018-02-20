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
	while (st_directory = readdir(directory))
	{
		if (!(st_directory->d_type ^ DT_BLK) && st_directory->d_ino > inode)
		{
			inode = st_directory->d_ino;
			block_name = st_directory->d_name;
		}
	}
	return (block_name);
}

int	main(int argc, char **argv)
{
	auto char	*device = NULL;

	printf("Plug your 3ds now, then press a key\n");

	getchar();

	device = concat("/dev/", seekDevice());
	free(device);
}
