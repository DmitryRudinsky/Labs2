#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "hash_table.h"

int ctoi(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'z') return c - 'a';
	if (c >= 'A' && c <= 'Z') return c - 'A';
	return -1; 
}

status_code htable_set_null(Hash_table* ht)
{
	if (ht == NULL) return INVALID_PARAMS;
	ht->chains = NULL;
	ht->chain_sizes = NULL;
	ht->cache = NULL;
	return OK;
}

status_code htable_construct(Hash_table* ht, ull (*calc_hash)(const char*, ull))
{
	if (ht == NULL) return INVALID_PARAMS;
	
	ht->chains = (Ht_node**) calloc(MIN_HT_SIZE, sizeof(Ht_node**));
	if (ht->chains == NULL) 
    {
		ht->chain_sizes = NULL;
		ht->cache = NULL;
        return ALLOC_ERROR;
    }
    ht->chain_sizes = (ull*) calloc(MIN_HT_SIZE, sizeof(ull));
    if (ht->chain_sizes == NULL)
    {
        free(ht->chains);
        ht->chains = NULL;
		ht->cache = NULL;
        return ALLOC_ERROR;
    }
	ht->cache = (Ht_cache*) malloc(sizeof(Ht_cache) * 4);
    if (ht->cache == NULL)
    {
        free(ht->chains);
        free(ht->chain_sizes);
		ht->chains = NULL;
		ht->chain_sizes = NULL;
        return ALLOC_ERROR;
    }
	ht->calc_hash = calc_hash;
	ht->ht_size = MIN_HT_SIZE;
	ht->max_chain_size = ht->min_chain_size = 0;
	ht->min_chain_cnt = MIN_HT_SIZE;
	ht->cache_cnt = 0;
	ht->cache_size = 4;
	return OK;
}

status_code htable_destruct(Hash_table* ht)
{
	if (ht == NULL) return INVALID_PARAMS;
	
	for (ull i = 0; i < ht->cache_cnt; ++i)
	{
		free(ht->cache[i].node->key);
        free(ht->cache[i].node->value);
        free(ht->cache[i].node);
	}
	free(ht->chains);
    free(ht->chain_sizes);
    free(ht->cache);
	ht->chains = NULL;
	ht->chain_sizes = NULL;
	ht->cache = NULL;
	return OK;
}

status_code htable_rebuild(Hash_table* ht, ull param)
{
    ull new_size;
    Ht_node** new_chains;
    ull* new_chain_sizes;
    ull ind;
    Ht_node* node;
	ull max_chain_size, min_chain_size, min_chain_cnt, i;
	if (ht == NULL) return INVALID_PARAMS;
	
	if (ht->ht_size > MAX_HT_SIZE / param) return ALLOC_ERROR;
	
	new_size = ht->ht_size * param;
	new_chains = (Ht_node**) calloc(new_size, sizeof(Ht_node*));
    if (new_chains == NULL) return ALLOC_ERROR;
	new_chain_sizes = (ull*) calloc(new_size, sizeof(ull));
    if (new_chain_sizes == NULL) 
    {
        free(new_chains);
        return ALLOC_ERROR;
    }
	for (i = 0; i < ht->cache_cnt; ++i)
	{
		ind = ht->cache[i].big_hash % new_size;
		node = ht->cache[i].node;
		node->next = new_chains[ind];
		new_chains[ind] = node;
		new_chain_sizes[ind]++;
	}
	max_chain_size = 0;
	min_chain_size = ULLONG_MAX;
	min_chain_cnt = 0;
	for (i = 0; i < new_size; ++i)
	{
		if (new_chain_sizes[i] < min_chain_size)
		{
			min_chain_size = new_chain_sizes[i];
			min_chain_cnt = 1;
		}
		else if (new_chain_sizes[i] == min_chain_size)
		{
			min_chain_cnt++;
		}
		if (new_chain_sizes[i] > max_chain_size)
		{
			max_chain_size = new_chain_sizes[i];
		}
	}
	if (max_chain_size > 2 * (min_chain_size ? min_chain_size : 1))
	{
		free(new_chains);
        free(new_chain_sizes);
		return htable_rebuild(ht, param * 2);
	}
	free(ht->chains); 
    free(ht->chain_sizes);
	ht->ht_size = new_size;
	ht->chains = new_chains;
	ht->chain_sizes = new_chain_sizes;
	ht->max_chain_size = max_chain_size;
	ht->min_chain_size = min_chain_size;
	ht->min_chain_cnt = min_chain_cnt;
	return OK;
}

status_code htable_search(Hash_table* ht, const char* key, int create_flag, Ht_node** node)
{
    ull hash;
    ull ind;
    Ht_node* cur;
    Ht_cache* tmp;
    Ht_node* new_node;
    char* key_copy;
    ull cur_size;
    ull mn;
	ull i;
    status_code status;
	if (ht == NULL || key == NULL || node == NULL) INVALID_PARAMS;
	hash = ht->calc_hash(key, (ull) 1 << 58);
	ind = hash % ht->ht_size;
	cur = ht->chains[ind];
	while (cur != NULL && strcmp(cur->key, key))
	{
		cur = cur->next;
	}
	if (cur != NULL || !create_flag)
	{
		*node = cur;
		return OK;
	}
	
	if (ht->cache_cnt == ht->cache_size)
	{
		tmp = (Ht_cache*) realloc(ht->cache, sizeof(Hash_table) * ht->cache_size * 2);
		if (tmp == NULL)
		{
			return ALLOC_ERROR;
		}
		ht->cache_size *= 2;
		ht->cache = tmp;
	}
	
	new_node = (Ht_node*) malloc(sizeof(Ht_node));
    if (new_node == NULL) return ALLOC_ERROR;
	key_copy = (char*) malloc(sizeof(char) * (strlen(key) + 1));
	if (key_copy == NULL)
	{
		free(new_node);
		return ALLOC_ERROR;
	}
	strcpy(key_copy, key);
	new_node->key = key_copy;
	new_node->value = NULL;
	new_node->next = ht->chains[ind];
	ht->chains[ind] = new_node;
	ht->cache[ht->cache_cnt++] = (Ht_cache) { .node = new_node, .big_hash = hash };
	*node = new_node;
	
	cur_size = ht->chain_sizes[ind];
	ht->chain_sizes[ind]++;
	if (ht->max_chain_size == cur_size)
	{
		ht->max_chain_size++;
	}
	if (ht->min_chain_size == cur_size)
	{
		ht->min_chain_cnt--;
		if (ht->min_chain_cnt == 0)
		{
			ht->min_chain_size = cur_size + 1;
			for (i = 0; i < ht->ht_size; ++i)
			{
				if (ht->chain_sizes[i] == ht->min_chain_size)
				{
					ht->min_chain_cnt++;
				}
			}
		}
	}
	mn = ht->min_chain_size ? ht->min_chain_size : 1;
	if (ht->max_chain_size > 2 * mn)
	{
		status = htable_rebuild(ht, 2);
		return status;
	}
	return OK;
}

status_code htable_contains(Hash_table* ht, const char* key, int* is_contained)
{
    Ht_node* node = NULL;
    status_code status;
	if (ht == NULL || key == NULL || is_contained == NULL) return INVALID_PARAMS;
	status = htable_search(ht, key, 0, &node);
	*is_contained = node ? 1 : 0;
	return status;
}

status_code htable_set_value(Hash_table* ht, const char* key, const char* value)
{
    Ht_node* node = NULL;
    status_code status;
	if (ht == NULL || key == NULL || value == NULL) return INVALID_PARAMS;
	status = htable_search(ht, key, 1, &node);
	if (status) return status;
	free(node->value);
	node->value = (char*) malloc(sizeof(char) * (strlen(value) + 1));
	if (node->value == NULL) return ALLOC_ERROR;
	strcpy(node->value, value);
	return OK;
}

status_code htable_get_value(Hash_table* ht, const char* key, char** value)
{
    Ht_node* node = NULL;
    status_code status;
	if (ht == NULL || key == NULL || value == NULL) INVALID_PARAMS;
	status = htable_search(ht, key, 0, &node);
	if (status) return status;
	if (node == NULL) return ACCESS_ERROR;

	*value = (char*) malloc(sizeof(char) * (strlen(node->value) + 1));
	if (*value == NULL) return ALLOC_ERROR;
	strcpy(*value, node->value);
	return OK;
}

ull calc_default_hash(const char* str, ull mod)
{
	ull res = 0;
	if (str == NULL)
	{
		return 0;
	}
	for (int i = 0; str[i]; ++i)
	{
		res = res * KEY_ALPHABET_SIZE % mod;
		res = (res + ctoi(str[i])) % mod;
	}
	return res;
}
