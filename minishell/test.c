#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
extern int history_base;
extern int history_length;
extern int history_max_entries;
extern int history_offset;

extern int history_lines_read_from_file;
extern int history_lines_written_to_file;

extern char history_expansion_char;
extern char history_subst_char;
extern char *history_word_delimiters;
extern char history_comment_char;
extern char *history_no_expand_chars;
extern char *history_search_delimiter_chars;

extern int history_quotes_inhibit_expansion;
extern int history_quoting_state;

extern int history_write_timestamps;
extern int max_input_history;
*/

int	main(void)
{
	char		*line;
	HIST_ENTRY	**historyList;

	printf("extern int history_length = %d\n", history_length);
	printf("extern int history_base = %d\n", history_base);
	printf("extern int history_max_entries = %d\n", history_max_entries);
	printf("extern int history_offset = %d\n", history_offset);
	printf("extern int history_lines_read_from_file = %d\n", history_lines_read_from_file);
	printf("extern int history_lines_written_to_file = %d\n", history_lines_written_to_file);

	printf("extern char history_expansion_char = %c\n", history_expansion_char);
	printf("extern char history_subst_char = %c\n", history_subst_char);
	printf("extern char *history_word_delimiters = %s\n", history_word_delimiters);
	printf("extern char history_comment_char = %c\n", history_comment_char);
	printf("extern char *history_no_expand_chars = %s\n", history_no_expand_chars);
	printf("extern char *history_search_delimiter_chars = %s\n", history_search_delimiter_chars);

	printf("extern int history_quotes_inhibit_expansion = %d\n", history_quotes_inhibit_expansion);
	printf("extern int history_quoting_state = %d\n", history_quoting_state);
	printf("extern int history_write_timestamps = %d\n", history_write_timestamps);
	printf("extern int max_input_history = %d\n", max_input_history);
	line = readline("prompt>");
	while (line != NULL)
	{
		free(line);
		line = readline("prompt>");
	}

	int rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	int modes = O_RDWR | O_CREAT;
	printf("rights:%d || modes:%d\n", rights, modes);
	int	fd = open("file", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (isatty(fileno(stdout))) {
        printf("[1]: La sortie standard est un terminal.\n");
    } else {
        printf("[1]: La sortie standard est redirigée vers un fichier ou un autre flux.\n");
    }
	dup2(fd, STDOUT_FILENO);
	if (isatty(fileno(stdout))) {
        printf("[2]: La sortie standard est un terminal.\n");
    } else {
        printf("[2]: La sortie standard est redirigée vers un fichier ou un autre flux.\n");
    }
	// unlink("file");
	return (0);
}
