#include "cryp.h"

void parse_operator(t_cryp *cryp, char **operator)
{
	if (strcmp(operator[1], "enc") == 0)
		cryp->operator = ENCRYPT;
	else if (strcmp(operator[1], "dec") == 0)
		cryp->operator = DECRYPT;
	else
		error("Invalid operator");

	for (int i = 2; i < 10; i+=2)
	{
		if (strcmp(operator[i], "-key") == 0)
			cryp->key_filename = operator[i + 1];
		else if (strcmp(operator[i], "-in") == 0)
			cryp->infile_filename = operator[i + 1];
		else if (strcmp(operator[i], "-out") == 0)
			cryp->outfile_filename = operator[i + 1];
		else if (strcmp(operator[i], "-tag") == 0)
			cryp->tag_filename = operator[i + 1];
		else
			error("Invalid argument");
	}
}


