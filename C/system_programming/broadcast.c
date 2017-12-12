#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>

#include <unistd.h>

#define TRIALS			20
#define CONDITION_COUNT	2

#define CALL_WAIT	0
#define SIG_FOO		1
#define SIG_BAR		(SIG_FOO << 1)
#define SIG_SPAM	(SIG_BAR << 1)
#define CALL_READY	(SIG_FOO | SIG_BAR | SIG_SPAM)

#define SET_STATE(src, cond)	(src |= cond)

typedef unsigned char State;

typedef struct dynamic_mutex
{
	pthread_mutex_t *mutex;
	pthread_cond_t **conditions;
	State cur_state;
	State done;
	size_t cond_size;
} DynamicMutex;

DynamicMutex *init_dynamic_mutex(size_t cond_size);
void free_dynamic_mutex(DynamicMutex *src);
void *foo_main(void *args);
void *bar_main(void *args);
void *spam_main(void *args);

void broadcaster(DynamicMutex *src);

int main(int argc, const char *argv[])
{
	DynamicMutex *dyn_mutex = init_dynamic_mutex(CONDITION_COUNT);
	pthread_t th1 = 0;
	pthread_t th2 = 0;
	pthread_t th3 = 0;
	int err1 = 0;
	int err2 = 0;
	int err3 = 0;

	err1 = pthread_create(&th1, NULL, foo_main, (void *)dyn_mutex);
	err2 = pthread_create(&th2, NULL, bar_main, (void *)dyn_mutex);
	err3 = pthread_create(&th3, NULL, spam_main, (void *)dyn_mutex);

	if (err1 != 0 || err2 != 0 || err3 != 0)
	{
		puts("Failed to initialize threads.");
		exit(1);
	}

	broadcaster(dyn_mutex);

	if (pthread_join(th1, NULL) || pthread_join(th2, NULL) ||
			pthread_join(th3, NULL))
	{
		puts("pthread_join has failed.");
		exit(2);
	}

	free_dynamic_mutex(dyn_mutex);

	return 0;
}
void broadcaster(DynamicMutex *src)
{
	char buffer[128] = { 0 };
	pthread_mutex_t *mutex = src->mutex;
	pthread_cond_t *from_caster = src->conditions[0];
	pthread_cond_t *to_caster = src->conditions[1];
	State *state = &(src->cur_state);

	do
	{
		pthread_mutex_lock(mutex);
		while (*state != CALL_READY)
		{
			pthread_cond_wait(to_caster, mutex);
		}
		pthread_mutex_unlock(mutex);

		scanf("%s", buffer);

		pthread_mutex_lock(mutex);
		*state = CALL_WAIT;
		pthread_cond_broadcast(from_caster);
		pthread_mutex_unlock(mutex);
	} while (strcmp(buffer, "exit") != 0 && strcmp(buffer, "quit") != 0);

	pthread_mutex_lock(mutex);
	src->done = true;
	pthread_cond_broadcast(from_caster);
	pthread_mutex_unlock(mutex);

	pthread_exit(NULL);
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
	new_mutex->cur_state = CALL_READY;

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
	pthread_cond_t *from_caster = dyn_mutex->conditions[0];
	pthread_cond_t *to_caster = dyn_mutex->conditions[1];
	State *state = &(dyn_mutex->cur_state);
	State *done = &(dyn_mutex->done);

	while (true)
	{
		pthread_mutex_lock(mutex);
		while ((*state & SIG_FOO) && *done == false)
		{
			pthread_cond_wait(from_caster, mutex);
		}
		pthread_mutex_unlock(mutex);

		if (*done == true)
		{
			break;
		}
		printf("foo_main received broadcasting.\n");

		pthread_mutex_lock(mutex);
		SET_STATE(*state, SIG_FOO);
		pthread_cond_signal(to_caster);
		pthread_mutex_unlock(mutex);
	}

	pthread_exit(NULL);
}
void *bar_main(void *args)
{
	DynamicMutex *dyn_mutex = (DynamicMutex *)args;
	pthread_mutex_t *mutex = dyn_mutex->mutex;
	pthread_cond_t *from_caster = dyn_mutex->conditions[0];
	pthread_cond_t *to_caster = dyn_mutex->conditions[1];
	State *state = &(dyn_mutex->cur_state);
	State *done = &(dyn_mutex->done);

	while (true)
	{
		pthread_mutex_lock(mutex);
		while ((*state & SIG_BAR) && *done == false)
		{
			pthread_cond_wait(from_caster, mutex);
		}
		pthread_mutex_unlock(mutex);

		if (*done == true)
		{
			break;
		}
		printf("bar_main received broadcasting.\n");

		pthread_mutex_lock(mutex);
		SET_STATE(*state, SIG_BAR);
		pthread_cond_signal(to_caster);
		pthread_mutex_unlock(mutex);
	}

	pthread_exit(NULL);
}
void *spam_main(void *args)
{
	DynamicMutex *dyn_mutex = (DynamicMutex *)args;
	pthread_mutex_t *mutex = dyn_mutex->mutex;
	pthread_cond_t *from_caster = dyn_mutex->conditions[0];
	pthread_cond_t *to_caster = dyn_mutex->conditions[1];
	State *state = &(dyn_mutex->cur_state);
	State *done = &(dyn_mutex->done);

	while (true)
	{
		pthread_mutex_lock(mutex);
		while ((*state & SIG_SPAM) && *done == false)
		{
			pthread_cond_wait(from_caster, mutex);
		}
		pthread_mutex_unlock(mutex);

		if (*done == true)
		{
			break;
		}
		printf("spam_main received broadcasting.\n");

		pthread_mutex_lock(mutex);
		SET_STATE(*state, SIG_SPAM);
		pthread_cond_signal(to_caster);
		pthread_mutex_unlock(mutex);
	}

	pthread_exit(NULL);
}


