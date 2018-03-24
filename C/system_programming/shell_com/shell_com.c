#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHELL_COMMAND_DELIM	';'
#define ARGV_DELIM			' '

typedef struct string_data String;

/* It follows C99 standard. */
struct string_data
{
	size_t len;
	char text[0];
};

void shell_command(const char *command_line);

static String *char_to_string(const char *src);
static String *nchar_to_string(const char *src, size_t len);
static String *strip_string(String *src);
static char **split_string_tokens(String *src, char delim);

int main(int argc, const char *argv[])
{
	const char *test_string = "    echo Hello,   World(1) ;   echo Hello, World(2) ;   echo Hello, World(3); ls -a;";

	shell_command(test_string);

	return 0;
}

void shell_command(const char *command_line)
{
	String *raw_cmd_line = char_to_string(command_line);
	String *cmd_line = strip_string(raw_cmd_line);
	char **cmds = split_string_tokens(cmd_line, SHELL_COMMAND_DELIM);
	char **cmd = cmds;
	int status = 0;
	int wpid = 0;

	while (*cmd)
	{
		pid_t pid = fork();

		/* Error */
		if (pid < 0)
		{
			fprintf(stderr, "Fork error\n");
			exit(1);
		}
		/* child */
		else if (pid == 0)
		{
			String *raw_str_argv= char_to_string(*cmd);
			String *str_argv = strip_string(raw_str_argv);
			char **argv = split_string_tokens(str_argv, ARGV_DELIM);

			execvp(argv[0], argv);

			free(raw_str_argv);
			free(str_argv);
			free(argv);

			exit(0);
		}
		/* parent */
		else
		{
			/* intentionally empty */
		}
		cmd++;
	}

	while ((wpid = wait(&status)) > 0)
	{
		/* intentionally empty */
	}

	free(raw_cmd_line);
	free(cmd_line);
	free(cmds);
}

/*
 * It computes out the length of string
 * before it calls nchar_to_string.
 */
static String *char_to_string(const char *src)
{
	char *p = (char *)src;
	char *s = (char *)src;

	/* strlen */
	while (*p)
	{
		p++;
	}

	return nchar_to_string(src, p-s);
}

static String *nchar_to_string(const char *src, size_t len)
{
	String *str = (String *)calloc(1, sizeof(String) + len + 1);
	str->len = len;

	char *p = str->text;
	char *s = (char *)src;

	while (*s)
	{
		*p = *s;
		p++;
		s++;
	}
	*p = '\0';

	return str;
}

/*
 * Return a new String stripped of
 * leading white space and trailing.
 */
static String *strip_string(String *src)
{
	char *p = src->text;
	size_t len = src->len;
	char *sot = NULL;
	char *eot = NULL;

	for (size_t i = 0; i < len; i++)
	{
		if (p[i] != ' ' && p[i] != '\t')
		{
			sot = p+i;
			break;
		}
	}

	for (size_t i = len-1; i != (size_t)-1; i--)
	{
		if (p[i] != ' ' && p[i] != '\t')
		{
			eot = p+i;
			break;
		}
	}

	return nchar_to_string(sot, eot-sot+1);
}

/*
 * Returns a null-terminated set of pointers to each token
 * separated by delim.
 * It mutates source, and the caller must not delete the source.
 */
static char **split_string_tokens(String *src, char delim)
{
	if (src == NULL)
	{
		return NULL;
	}

	char *p = src->text;
	size_t count = 1;
	size_t len = src->len;

	/* Count delims in string. */
	for (size_t i = 0; i < len; i++)
	{
		if (p[i] == delim)
		{
			p[i] = '\0';
			count++;
		}
	}

	char **tokens = (char **)calloc(count+1, sizeof(char *));
	char **index = tokens;
	char *token_ptr = src->text;

	p = src->text;
	for (size_t i = 0; i < len; i++)
	{
		if (p[i] == '\0')
		{
			*index = token_ptr;
			index++;
			token_ptr = p+i+1;
		}
	}
	*index = token_ptr;
	*(index+1) = NULL;

	return tokens;
}

