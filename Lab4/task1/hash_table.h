#ifndef HASH_TABLE
#define HASH_TABLE

#define KEY_ALPHABET_SIZE 62
#define MIN_HT_SIZE 128
#define MAX_HT_SIZE (1ULL << 58)

typedef unsigned long long ull;
typedef long long ll;

typedef enum 
{
	OK,
	INVALID_INPUT,
    INVALID_PARAMS,
    WEIRD_VALUES,
	OVERFLOW,
	ALLOC_ERROR,
	FILE_OPENING_ERROR,
    ACCESS_ERROR,
	UNKNOWN_ERROR,
    RESERVED
}status_code;

static const char* errors[] =
{
	"Success\n",
	"Invalid input\n",
    "Invalid parameters were passed to the function\n",
    "The problem is unsolvable for the given arguments\n",
	"Overflow error\n",
	"Memory allocation error\n",
    "Access error\n",
	"Unknown error\n",
    "Reserved code\n"
};

typedef struct Ht_node
{
	char* key;
	char* value;
	struct Ht_node* next;
} Ht_node;

typedef struct Ht_cache
{
	Ht_node* node;
	ull big_hash;
} Ht_cache;

typedef struct Hash_table
{
	ull (*calc_hash)(const char*, ull);
	ull ht_size;
	Ht_node** chains;
	ull* chain_sizes;
	ull max_chain_size;
	ull min_chain_size;
	ull min_chain_cnt;
	ull cache_cnt;
	ull cache_size;
	Ht_cache* cache;
} Hash_table;

status_code htable_set_null(Hash_table* ht);
status_code htable_construct(Hash_table* ht, ull (*calc_hash)(const char*, ull));
status_code htable_destruct(Hash_table* ht);
status_code htable_rebuild(Hash_table* ht, ull param);
status_code htable_search(Hash_table* ht, const char* key, int create_flag, Ht_node** node);
status_code htable_contains(Hash_table* ht, const char* key, int* is_contained);
status_code htable_get_value(Hash_table* ht, const char* key, char** value);
status_code htable_set_value(Hash_table* ht, const char* key, const char* value);
ull calc_default_hash(const char* str, ull mod);

#endif