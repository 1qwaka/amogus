// variant 2

#include <stdio.h>
#include <string.h>

#define OK 0
#define ERR_INPUT 1

#define N_MIN 1
#define N_MAX 5
#define MAX_WORD_LEN 5


typedef struct 
{
	int size;
	char body[N_MAX][N_MAX][MAX_WORD_LEN + 1];
} square_matrix_t;


int input_mat(square_matrix_t *mat);

int count_correct_lines(const square_matrix_t *mat);

void print_matrix(const square_matrix_t *mat);

void print_result(int result);


int main(void)
{
	int exit_code = OK;
	
	square_matrix_t mat = { 0 };
	int rc = input_mat(&mat);
	
	if (rc == OK)
	{
		int result = count_correct_lines(&mat);
		print_matrix(&mat);
		print_result(result);
	}
	else
	{
		exit_code = ERR_INPUT;
	}
	
	return exit_code;
}


int input_mat(square_matrix_t *mat)
{
	int rc = OK;
	
	rc = scanf("%d", &mat->size) == 1 ? OK : ERR_INPUT;
	
	if (rc == OK)
	{
		rc = 1;
		// char tmp[MAX_WORD_LEN + 1 + 1] = { 0 };
		for (int i = 0; i < mat->size && rc == 1; ++i)
			for (int j = 0; j < mat->size && rc == 1; ++j)
			{
				rc = scanf("%5s", mat->body[i][j]);
				// printf("scanned %d: %s", rc, mat->body[i][j]);
				
			}
		
		if (rc != 1)
			rc = ERR_INPUT;
		else 
			rc = OK;
	}
	
	
	return rc;
}

int count_correct_lines(const square_matrix_t *mat)
{
	int result = 0;
	
	for (int i = 0; i < mat->size; ++i)
	{
		int all_equals = 1;
		for (int j = 1; j < mat->size && all_equals; ++j)
			all_equals = strcmp(mat->body[i][j],  mat->body[i][j - 1]) == 0;
		
		if (all_equals)
			++result;
	}		
	
	return result;
}

void print_matrix(const square_matrix_t *mat)
{
	for (int i = 0; i < mat->size; ++i)
	{
		for (int j = 0; j < mat->size; ++j)
		{
				printf("%s ", mat->body[i][j]);
		}
		printf("\n");
	}
}

void print_result(int result)
{
	printf("%d\n", result);
}
