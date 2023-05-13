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

	if (cryp.operator == ENCRYPT)
		make_hmac(&cryp);
	else if (cryp.operator == DECRYPT)
		check_hmac(&cryp);
	else
		error("Invalid operator");

	free_cryp(&cryp);
	return (0);
}
