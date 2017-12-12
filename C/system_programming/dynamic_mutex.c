#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define TRIALS			20
#define CONDITION_COUNT	3

typedef enum state_data
{
	CALL_FOO,
	CALL_BAR,
	CALL_SPAM
} State;

typedef struct dynamic_mutex
{
	pthread_mutex_t *mutex;
	pthread_cond_t **conditions;
	State cur_state;
	size_t cond_size;
} DynamicMutex;

DynamicMutex *init_dynamic_mutex(size_t cond_size);
void free_dynamic_mutex(DynamicMutex *src);
void *foo_main(void *args);
void *bar_main(void *args);
void *spam_main(void *args);

int main(int argc, const char *argv[])
{
	DynamicMutex *dyn_mutex = init_dynamic_mutex(CONDITION_COUNT);
	pthread_t th1 = 0;
	pthread_t th2 = 0;
	pthread_t th3 = 0;
	int err1 = 0;
	int err2 = 0;
	int err3 = 0;
	void *ext1 = NULL;
	void *ext2 = NULL;
	void *ext3 = NULL;

	err1 = pthread_create(&th1, NULL, foo_main, (void *)dyn_mutex);
	err2 = pthread_create(&th2, NULL, bar_main, (void *)dyn_mutex);
	err3 = pthread_create(&th3, NULL, spam_main, (void *)dyn_mutex);

	if (err1 != 0 || err2 != 0 || err3 != 0)
	{
		puts("Failed to initialize threads.");
		exit(1);
	}


	if (pthread_join(th1, &ext1) || pthread_join(th2, &ext2) ||
			pthread_join(th3, &ext3))
	{
		puts("pthread_join has failed.");
		exit(2);
	}

	free_dynamic_mutex(dyn_mutex);

	printf("ext1: %s, ext2: %s, ext3: %s\n",
			(char *)ext1, (char *)ext2, (char *)ext3);
	free((char *)ext1);
	free((char *)ext2);
	free((char *)ext3);

	return 0;
}

DynamicMutex *init_dynamic_mutex(size_t cond_size)
{
	DynamicMutex *new_mutex = (DynamicMutex *)calloc(1, sizeof(DynamicMutex));

	/* Conditions */
	new_mutex->conditions = (pthread_cond_t **)calloc(cond_size, sizeof(pthread_cond_t *));
	pthread_cond_t **cond_ptr = new_mutex->conditions;
	pthread_cond_t **cond_end = new_mutex->conditions + cond_size;
	while (cond_ptr < cond_end)
	{
		*cond_ptr = (pthread_cond_t *)calloc(1, sizeof(pthread_cond_t));
		pthread_cond_init(*cond_ptr, NULL);
		cond_ptr++;
	}

	/* Mutex */
	new_mutex->mutex = (pthread_mutex_t *)calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(new_mutex->mutex, NULL);

	/* Condition size */
	new_mutex->cond_size = cond_size;

	/* Current state */
	new_mutex->cur_state = CALL_FOO;

	return new_mutex;
}
void free_dynamic_mutex(DynamicMutex *src)
{
	pthread_cond_t **cond_ptr = src->conditions;
	pthread_cond_t **cond_end = src->conditions + src->cond_size;
	while (cond_ptr < cond_end)
	{
		pthread_cond_destroy(*cond_ptr);
		free(*cond_ptr);
		cond_ptr++;
	}

	pthread_mutex_destroy(src->mutex);
	free(src->mutex);

	free(src);
}
void *foo_main(void *args)
{
	DynamicMutex *dyn_mutex = (DynamicMutex *)args;
	pthread_mutex_t *mutex = dyn_mutex->mutex;
	pthread_cond_t *cond_foo = dyn_mutex->conditions[0];
	pthread_cond_t *cond_bar = dyn_mutex->conditions[1];
	pthread_cond_t *cond_spam = dyn_mutex->conditions[2];
	State *state = &(dyn_mutex->cur_state);

	int i = 0;
	while (i < TRIALS)
	{
		pthread_mutex_lock(mutex);
		while (*state != CALL_FOO)
		{
			pthread_cond_wait(cond_foo, mutex);
		}
		pthread_mutex_unlock(mutex);

		printf("foo ");

		pthread_mutex_lock(mutex);
		*state = CALL_BAR;
		pthread_cond_signal(cond_bar);
		pthread_mutex_unlock(mutex);

		i++;
	}

	char *ret = (char *)calloc(4, sizeof(char));
	strncpy(ret, "foo", 3);
	ret[3] = 0;

	return (void *)ret;
}
void *bar_main(void *args)
{
	DynamicMutex *dyn_mutex = (DynamicMutex *)args;
	pthread_mutex_t *mutex = dyn_mutex->mutex;
	pthread_cond_t *cond_foo = dyn_mutex->conditions[0];
	pthread_cond_t *cond_bar = dyn_mutex->conditions[1];
	pthread_cond_t *cond_spam = dyn_mutex->conditions[2];
	State *state = &(dyn_mutex->cur_state);

	int i = 0;
	while (i < TRIALS)
	{
		pthread_mutex_lock(mutex);
		while (*state != CALL_BAR)
		{
			pthread_cond_wait(cond_bar, mutex);
		}
		pthread_mutex_unlock(mutex);

		printf("bar ");

		pthread_mutex_lock(mutex);
		*state = CALL_SPAM;
		pthread_cond_signal(cond_spam);
		pthread_mutex_unlock(mutex);

		i++;
	}

	char *ret = (char *)calloc(4, sizeof(char));
	strncpy(ret, "bar", 3);
	ret[3] = 0;

	pthread_exit((void *)ret);
}
void *spam_main(void *args)
{
	DynamicMutex *dyn_mutex = (DynamicMutex *)args;
	pthread_mutex_t *mutex = dyn_mutex->mutex;
	pthread_cond_t *cond_foo = dyn_mutex->conditions[0];
	pthread_cond_t *cond_bar = dyn_mutex->conditions[1];
	pthread_cond_t *cond_spam = dyn_mutex->conditions[2];
	State *state = &(dyn_mutex->cur_state);

	int i = 0;
	while (i < TRIALS)
	{
		pthread_mutex_lock(mutex);
		while (*state != CALL_SPAM)
		{
			pthread_cond_wait(cond_spam, mutex);
		}
		pthread_mutex_unlock(mutex);

		printf("spam\n");

		pthread_mutex_lock(mutex);
		*state = CALL_FOO;
		pthread_cond_signal(cond_foo);
		pthread_mutex_unlock(mutex);

		i++;
	}

	char *ret = (char *)calloc(5, sizeof(char));
	strncpy(ret, "spam", 5);
	ret[4] = 0;

	pthread_exit((void *)ret);
}

