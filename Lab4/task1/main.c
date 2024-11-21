#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "hash_table.h"


int is_separator(char c)
{
	return c == ' ' || c == '\t' || c == '\n';
}

status_code fskip_separators(FILE* in)
{
	char c = ' ';
	if (in == NULL) return INVALID_PARAMS;
	if (feof(in)) return OK;
	while (is_separator(c))
	{
		c = fgetc(in);
	}
	ungetc(c, in);
	return OK;
}

status_code fread_word(FILE* in, char** word)
{
	char c;
	ull size = 2;
	char* tmp;
	ull i = 0;
	if (in == NULL || word == NULL || feof(in)) return INVALID_PARAMS;
	*word = (char*) malloc(sizeof(char) * size);
	if (*word == NULL) return ALLOC_ERROR;
	c = fgetc(in);
	while (!is_separator(c) && !feof(in))
	{
		if (i + 2 == size)
		{
			size *= 2;
			tmp = (char*) realloc(*word, sizeof(char) * size);
			if (tmp == NULL)
			{
				free(*word);
				*word = NULL;
				return ALLOC_ERROR;
			}
			*word = tmp;
		}
		(*word)[i++] = c;
		c = fgetc(in);
	}
	(*word)[i] = '\0';
	tmp = (char*) realloc(*word, sizeof(char) * (i+1));
	if (tmp == NULL)
	{
		free(*word);
		*word = NULL;
		return ALLOC_ERROR;
	}
	*word = tmp;
	return OK;
}

status_code fread_line(FILE* in, char** line)
{
	char c;
	ull size = 2;
	char* tmp;
	ull i = 0;
	if (in == NULL || line == NULL || feof(in)) return INVALID_PARAMS;
	*line = (char*) malloc(sizeof(char) * size);
	if (*line == NULL) return ALLOC_ERROR;
	c = fgetc(in);
	while (c != '\n' && !feof(in))
	{
		if (i + 2 == size)
		{
			size *= 2;
			tmp = (char*) realloc(*line, sizeof(char) * size);
			if (tmp == NULL)
			{
				free(*line);
				*line = NULL;
				return ALLOC_ERROR;
			}
			*line = tmp;
		}
		(*line)[i++] = c;
		c = fgetc(in);
	}
	(*line)[i] = '\0';
	tmp = (char*) realloc(*line, sizeof(char) * (i+1));
	if (tmp == NULL)
	{
		free(*line);
		*line = NULL;
		return ALLOC_ERROR;
	}
	*line = tmp;
	return OK;
}

int main(int argc, char** argv)
{
	FILE *input, *output;
	Hash_table macro;
	status_code status;
	char *word, *key, *value;
	char c;
	int is_contained;
	if (argc == 1)
	{
		printf("Usage: cmd_path <input> <output>\n");
		return OK;
	}
	if (argc != 3 || !strcmp(argv[1], argv[2]))
	{
		printf(errors[INVALID_INPUT]);
		return INVALID_INPUT;
	}
	
	input = fopen(argv[1], "r");
	if (input == NULL)
	{
		printf(errors[FILE_OPENING_ERROR]);
		return FILE_OPENING_ERROR;
	}
	output = fopen(argv[2], "w");
	if (input == NULL)
	{
		fclose(input);
		printf(errors[FILE_OPENING_ERROR]);
		return FILE_OPENING_ERROR;
	}
	
	htable_set_null(&macro);
	status = htable_construct(&macro, calc_default_hash);
	word = NULL;
	while (!status)
	{
		key = NULL;
		value = NULL;
		status = status ? status : fread_word(input, &word);
		if (!status && !strcmp(word, "#define"))
		{
			free(word);
			status = status ? status : fskip_separators(input);
			status = status ? status : fread_word(input, &key);
			status = status ? status : fskip_separators(input);
			status = status ? status : fread_line(input, &value);
			status = status ? status : htable_set_value(&macro, key, value);
		}
		else
		{
			status = RESERVED;
		}
		free(key);
		free(value);
	}
	if (status == RESERVED) status = OK;
	fseek(input, -1, SEEK_CUR);
	c = getc(input);
	if (is_separator(c))
	{
		ungetc(c, input);
		fseek(input, -strlen(word), SEEK_CUR);
	}
	else
	{
		fseek(input, -strlen(word), SEEK_CUR);
	}
	free(word);
	word = NULL;
	
	while (!status)
	{
		c = getc(input);
		while(is_separator(c))
		{
			putc(c, output);
			c = getc(input);
		}
		if (!feof(input))
		{
			fseek(input, -1, SEEK_CUR);
		}
		else status = RESERVED;
		
		status = status ? status : fread_word(input, &word);
		is_contained = 0;
		status = status ? status : htable_contains(&macro, word, &is_contained);
		if (!status && is_contained)
		{
			value = NULL;
			status = htable_get_value(&macro, word, &value);
			fprintf(output, "%s", value);
			free(value);
		}
		else if (!status)
		{
			fprintf(output, "%s", word);
		}
		if (!status)
		{
			fseek(input, -1, SEEK_CUR);
			c = getc(input);
			if (is_separator(c))
			{
				fprintf(output, "%c", c);
			}
		}
		free(word);
		word = NULL;
	}
	if (status == RESERVED) status = OK;
	
	htable_destruct(&macro);
	fclose(input);
	fclose(output);
	printf(errors[status]);
	return status;
}