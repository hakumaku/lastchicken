#include "btr.h"
#include "util/my_string.h"

/* Database file descriptor. */
static int database = 0;

/*
 * The name of file is 'pathname' + DATABASE_NAME.
 */
int open_db(const char *pathname)
{
	string_t *path = char2str(pathname);
	const char *name = NULL;

	/* Does it contain '/' at the end? */
	if (path->text[path->length-1] == '/')
	{
		name = DATABASE_NAME;
	}
	else
	{
		name = SLASH_DATABASE_NAME;
	}

	string_t *db = concate_char(path, name);

	/* Database already exists. */
	if (access(db->text, F_OK) == 0)
	{
		fprintf(stderr, "%s already exists.\n", db->text);
		exit(1);
	}

	database = open(db->text, O_RDWR|O_CREAT, 0666);

	free(path);
	free(db);

	return 0;
}

