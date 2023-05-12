#ifndef CRYP_H
# define CRYP_H

# include <stdio.h>
# include <string.h>
# include <openssl/aes.h>
# include <openssl/hmac.h>
# include <openssl/sha.h>

# define ENCRYPT 0
# define DECRYPT 1

typedef struct s_cryp
{
	FILE *key_fp;
	FILE *outfile_fp;
	FILE *infile_fp;
	FILE *tag_fp;
	char *key_filename;
	char *infile_filename;
	char *outfile_filename;
	char *tag_filename;
	unsigned char *key;
	unsigned char *tag;
	unsigned char *infile;
	unsigned char *outfile;
	size_t key_length;
	size_t infile_length;
	size_t outfile_length;
	size_t tag_length;
	int operator;
}	t_cryp;

// parse.c
void parse_operator(t_cryp *cryp, char **operator);

// file.c
void open_key(t_cryp *cryp, char *filename);
void open_infile(t_cryp *cryp, char *filename);
void open_outfile(t_cryp *cryp, char *filename);
void open_tag(t_cryp *cryp, char *filename, char *mod);
void open_files(t_cryp *cryp);
void read_files(t_cryp *cryp);
void read_key(t_cryp *cryp);
void read_infile(t_cryp *cryp);
void read_tag(t_cryp *cryp);

// cryp.c
void init_cryp(t_cryp *cryp);
void free_cryp(t_cryp *cryp);

// encrypt.c
void make_hmac(t_cryp *cryp);
void check_hmac(t_cryp *cryp);

// print.c
void error(char *msg);

#endif