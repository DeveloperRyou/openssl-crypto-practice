#include "cryp.h"

unsigned char iv[]= {0x3d,0xaf,0xba,0x42,0x9d,0x9e,0xb4,0x30,
					0xb4,0x22,0xda,0x80,0x2c,0x9f,0xac,0x41};

void make_hmac(t_cryp *cryp)
{
	typedef struct aes_key_st AES_KEY;
	AES_KEY aes_key;

	// set key
	if (AES_set_encrypt_key(cryp->key, 256, &aes_key) < 0)
		error("Error while setting aes key");

	// allocate outfile memory
	cryp->outfile_length = (cryp->infile_length + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE * AES_BLOCK_SIZE;
	cryp->outfile = malloc(sizeof(cryp->outfile) * cryp->outfile_length);
	if (cryp->outfile == NULL)
		error("Error while allocating outfile memory");
	memset(cryp->outfile, 0, cryp->outfile_length);

	// encrypt
	AES_cbc_encrypt(cryp->infile, cryp->outfile, cryp->infile_length,
		&aes_key, iv, AES_ENCRYPT);
	if (cryp->outfile == NULL)
		error("Error while encrypting");

	// hmac
	cryp->tag = HMAC(EVP_sha256(), cryp->key, strlen(cryp->key), 
				cryp->outfile, cryp->outfile_length, NULL, NULL);
	if (cryp->tag == NULL)
		error("Error while making hmac");
	
	// open outfile
	open_outfile(cryp, cryp->outfile_filename);
	// write to outfile
	for (int i = 0; i < cryp->outfile_length; i++)
		fprintf(cryp->outfile_fp, "%c", cryp->outfile[i]);

	// open tag file
	open_tag(cryp, cryp->tag_filename, "w");
	// write to tag
	for (int i = 0; i < strlen((char *)cryp->tag); i++)
		fprintf(cryp->tag_fp, "%c", cryp->tag[i]);

	// print
	for (int i = 0; i < cryp->infile_length; i++)
		printf("%02x", cryp->infile[i]);
	printf("\n");
	for (int i = 0; i < cryp->outfile_length; i++)
		printf("%02x", cryp->outfile[i]);
	printf("\n");
	for (int i = 0; i < strlen((char *)cryp->tag); i++)
		printf("%02x", cryp->tag[i]);
}

void check_hmac(t_cryp *cryp)
{
	typedef struct aes_key_st AES_KEY;
	AES_KEY aes_key;

	// set key
	if (AES_set_decrypt_key(cryp->key, 256, &aes_key) < 0)
		error("Error while setting aes key");

	// makc hmac
	unsigned char *hmac = HMAC(EVP_sha256(), cryp->key, strlen(cryp->key), 
				cryp->infile, cryp->infile_length, NULL, NULL);
	if (hmac == NULL)
		error("Error while making hmac");

	// compare hmac with tag
	if (strcmp((char*)cryp->tag, (char*)hmac) != 0)
	{
		printf("VERIFICATION FAILURE\n");
		exit(1);
	}

	// allocate outfile memory
	cryp->outfile_length = cryp->infile_length;
	cryp->outfile = malloc(sizeof(cryp->infile) * cryp->outfile_length);
	if (cryp->outfile == NULL)
		error("Error while allocating outfile memory");
	memset(cryp->outfile, 0, cryp->outfile_length);

	// decrypt
	AES_cbc_encrypt(cryp->infile, cryp->outfile, cryp->infile_length,
		&aes_key, iv, AES_DECRYPT);
	if (cryp->outfile == NULL)
		error("Error while decrypting");

	// open outfile
	open_outfile(cryp, cryp->outfile_filename);
	// write to outfile
	fprintf(cryp->outfile_fp, "%s", cryp->outfile);

	// print
	for (int i = 0; i < cryp->infile_length; i++)
		printf("%02x", cryp->infile[i]);
	printf("\n");
	for (int i = 0; i < cryp->outfile_length; i++)
		printf("%02x", cryp->outfile[i]);
	printf("\n");
	for (int i = 0; i < strlen((char *)cryp->tag); i++)
		printf("%02x", cryp->tag[i]);
}
