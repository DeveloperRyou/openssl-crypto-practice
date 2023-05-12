#include "cryp.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 10)
		error("Arguments error");

	t_cryp cryp;
	
	init_cryp(&cryp);
	parse_operator(&cryp, argv);
	open_files(&cryp);
	read_files(&cryp);
	// print
	printf("key length: %zu\n", cryp.key_length);
	printf("key: %s\n", cryp.key);
	
	printf("infile length: %zu\n", cryp.infile_length);
	printf("tag length: %zu\n", cryp.tag_length);
	for (int i = 0; i < cryp.infile_length; i++)
		printf("%02x", cryp.infile[i]);
	printf("\n");

	for(int i = 0; i < cryp.tag_length; i++)
		printf("%02x", cryp.tag[i]);
	printf("\n");


	if (cryp.operator == ENCRYPT)
		make_hmac(&cryp);
	else if (cryp.operator == DECRYPT)
		check_hmac(&cryp);
	else
		error("Invalid operator");

	free_cryp(&cryp);
	return (0);
}
