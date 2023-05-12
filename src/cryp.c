#include "cryp.h"

void init_cryp(t_cryp *cryp)
{
	cryp->operator = 0;
	cryp->key_fp = NULL;
	cryp->infile_fp = NULL;
	cryp->outfile_fp = NULL;
	cryp->tag_fp = NULL;
	cryp->key_filename = NULL;
	cryp->infile_filename = NULL;
	cryp->outfile_filename = NULL;
	cryp->tag_filename = NULL;
	cryp->key = NULL;
	cryp->infile = NULL;
	cryp->outfile = NULL;
	cryp->tag = NULL;
	cryp->key_length = 0;
	cryp->infile_length = 0;
	cryp->outfile_length = 0;
	cryp->tag_length = 0;
}

void free_cryp(t_cryp *cryp)
{
	if (cryp->key_fp != NULL)
		fclose(cryp->key_fp);
	if (cryp->infile_fp != NULL)
		fclose(cryp->infile_fp);
	if (cryp->outfile_fp != NULL)
		fclose(cryp->outfile_fp);
	if (cryp->tag_fp != NULL)
		fclose(cryp->tag_fp);
		
	if (cryp->key != NULL)
		free(cryp->key);
	if (cryp->infile != NULL)
		free(cryp->infile);
	if (cryp->outfile != NULL)
		free(cryp->outfile);
	if (cryp->operator == DECRYPT && cryp->tag != NULL)
		free(cryp->tag);
	init_cryp(cryp);
}

