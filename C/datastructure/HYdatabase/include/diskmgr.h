#ifndef __DISKMGR_H__
#define __DISKMGR_H__

#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>

#define DATABASE_NAME "database.hy"
#define SLASH_DATABASE_NAME "/database.hy"

#define PAGE_SIZE 4096
#define RECORD_KEY_SIZE 8
#define RECORD_VALUE_SIZE 120
#define RECORD_SIZE (RECORD_KEY_SIZE + RECORD_VALUE_SIZE)

/*
 * Open existing data file using 'pathname' or create one if not existed.
 * If success, return 0. Otherwise, return non-zero value.
 */
int open_db(const char *pathname);

/*
 * Insert input 'key/value'(record) to data file at the right place.
 * If success, return 0. Otherwise, return non-zero value.
 */
int insert(int64_t key, const char *value);

/*
 * Find the recrod containing input 'key'.
 * If found matching 'key', return matched 'value' string.
 * Otherwise, return NULL.
 */
char *find(int64_t key);

/*
 * Find the matching record and delete if found.
 * If success, return 0. Otherwise, return non-zero value.
 */
int delete(int64_t key);

#endif /* __DISKMGR_H__ */

