#include "cryp.h"

void open_key(t_cryp *cryp, char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		error("key file error");
	cryp->key_fp = fp;
}

void open_infile(t_cryp *cryp, char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		error("in file error");
	cryp->infile_fp = fp;
}

void open_outfile(t_cryp *cryp, char *filename)
{
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
		error("out file error");
	cryp->outfile_fp = fp;
}

void open_tag(t_cryp *cryp, char *filename, char *mod)
{
	FILE *fp = fopen(filename, mod);
	if (fp == NULL)
		error("tag file error");
	cryp->tag_fp = fp;
}

void open_files(t_cryp *cryp)
{
	open_key(cryp, cryp->key_filename);
	open_infile(cryp, cryp->infile_filename);
	if (cryp->operator == DECRYPT)
		open_tag(cryp, cryp->tag_filename, "r");
}

void read_files(t_cryp *cryp)
{
	read_key(cryp);
	read_infile(cryp);
	if (cryp->operator == DECRYPT)
		read_tag(cryp);
}

void read_key(t_cryp *cryp)
{
	fseek(cryp->key_fp, 0, SEEK_END);
	cryp->key_length = ftell(cryp->key_fp);
	rewind(cryp->key_fp);

	cryp->key = (unsigned char*)malloc(sizeof(unsigned char) * (cryp->key_length + 1));
	if (cryp->key == NULL)
		error("key malloc error");	
	memset(cryp->key, 0, cryp->key_length + 1);

	size_t count = 0;
	while(1)
	{
		size_t len = fread(cryp->key + count, sizeof(unsigned char), 4, cryp->key_fp);
		if (len < 0)
			error("key file read error");
		if (len == 0)
			break;
	    count += len;
	}
	cryp->key[count] = '\0';
}

void read_infile(t_cryp *cryp)
{
	fseek(cryp->infile_fp, 0, SEEK_END);
	cryp->infile_length = ftell(cryp->infile_fp);
	rewind(cryp->infile_fp);

	cryp->infile = (unsigned char*)malloc(sizeof(unsigned char) * cryp->infile_length);
	if (cryp->infile == NULL)
		error("infile malloc error");
	memset(cryp->infile, 0, cryp->infile_length);

	size_t count = 0;
	while(1)
	{
		size_t len = fread(cryp->infile + count, sizeof(unsigned char), 4, cryp->infile_fp);
		if (len < 0)
			error("infile read error");
		if (len == 0)
			break;
	    count += len;
	}
	cryp->infile[count] = '\0';
}

void read_tag(t_cryp *cryp)
{
	fseek(cryp->tag_fp, 0, SEEK_END);
	cryp->tag_length = ftell(cryp->tag_fp);
	rewind(cryp->tag_fp);
	
	cryp->tag = (unsigned char*)malloc(sizeof(unsigned char) * (cryp->tag_length + 1));
	if (cryp->tag == NULL)
		error("tag malloc error");
	memset(cryp->tag, 0, cryp->tag_length + 1);

	size_t count = 0;
	while(1)
	{
		size_t len = fread(cryp->tag + count, sizeof(unsigned char), 4, cryp->tag_fp);
		if (len < 0)
			error("tag read error");
		if (len == 0)
			break;
	    count += len;
	}
	cryp->tag[count] = '\0';
}