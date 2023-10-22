/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-jama <sel-jama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 22:32:43 by sel-jama          #+#    #+#             */
/*   Updated: 2023/10/21 01:26:59 by yboucha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define PROMPT "Minishell~>>"
# define TOKEN_DELIMETERS "|><"
# define SPECIALS "\\+-#@=:%^/."

# define OUTPUT_RED 1
# define INPUT_RED 2
# define APPEND_RED 3
# define HERE_DOC 4
# define IN_OUT 5
# define IN_APPEND 6

extern int				g_exit_status;

typedef struct s_content
{
	char				**cmds_arr;
	int					sep;
	int					redi;
	int					out;
	int					in;
	int					append;
	char				**infiles;
	char				**filenames;
	char				**eof;
	int					expand;
}						t_content;

typedef struct node
{
	int					cmds_num;
	char				**envirenement;
	char				*content;
	struct node			*next;
}						t_env;

typedef struct cmds_node
{
	int					cmds_num;
	int					red_num;
	int					start;
	int					end;
	char				*cmd_line;
	char				**tokens_arr;
	int					num_of_tokens;
	int					remove;
	int					modify_exitstatus;
	char				*value;
	char				*first;
	char				*last;
	char				*str;
	char				*quoted;
	int					rank;
	int					expand_doc;
	int					filenames_num;
	int					space_found;
	int					ambig_file;
	t_list				*indexes;
	t_env				*env;
	struct cmds_node	*next;
	t_content			*cmd_info;
}						t_cmds;

/*parse*/
void					tokenize_input(t_cmds **input);
int						check_d_del_errors(char *line, char *delimeters);
int						check_successive_del(char *line, char *delimeters);
int						display_error(char c);
char					*check_double_redirection(char *line);
char					*check_double_right(char *line);
char					*check_double_left(char *line);
t_cmds					*creat_cmds_list(t_cmds **all_commands);
void					fill_node(t_content **content, t_cmds **cmds,
							int *start);
void					count_commands(t_cmds **cmd);
void					ft_lstadd_back_cmds(t_cmds **lst, t_cmds *new);
t_cmds					*ft_lstnew_cmds(void *content);
t_cmds					*ft_lstlast_cmds(t_cmds *lst);
char					*check_double_redirection(char *line);
void					ft_init_param(t_cmds *input, t_content *content,
							t_env **lst);
int						check_del_position(char *line);
int						check_syntax(char *line);
int						is_redirection(char *token);
void					fill_redirection(t_content **cntnt, t_cmds **all_cmds,
							int s);
int						which_redi(char *redirection);
void					ft_clean_up(char **token_arr);
void					input_redir(t_content **cnt, t_cmds **cmds, int start);
void					output_redirection(t_content **content,
							t_cmds **all_cmds, int s);
void					heredoc_red(t_content **cntnt, t_cmds **all_cmds,
							int s);
void					quote_handling(t_cmds **input);
int						is_quote_skipped(char *line, int index);
int						is_expandble(t_cmds **input, int rank);
char					*replace_with_expansion(t_cmds **input, int *n,
							int start, int end);
void					expand_to_key(t_cmds **input, int *i, int *j);
void					expand_token(t_cmds **input);
char					*concatenate_strings(char **arr);
char					*quote_removal(t_cmds **input, int n, int *index);
char					*ft_getvalue(t_cmds **input, char *value);
char					*get_exitstatus(void);
t_cmds					*start_minishell(t_cmds *cmds);
void					read_and_check_input(t_cmds *input, t_env **sega);
char					*skip_specials(char **line, int start, int *end);
char					**remove_token(char **token_arr, int index,
							int num_of_tokens);
char					**get_array(t_list **tokens_lst);
char					*trim_input(char *line, int end);
char					*extract_token(char *line, int start, int end);
char					*remove_skips(char *token);
void					remove_skipping(t_cmds **lst);
int						is_between_quote(char *cmd_line, int index);
void					signal_notify(void);
void					signal_action(int sig);
int						get_end_of_quote(char *line, int *index);
char					*remove_one_skip(char *token, int index);
char					*skip_char_inbetween(char *line, int s, int *e);
void					insert_spaces_between(char **str, int start, int end);
void					retrieve_start_and_end(char *line, int *start, int *end,
							int index);
int						get_dollar_index(char *line, int rank);
int						validate_redirections(t_cmds **list);
int						error_redi(void);
int						manage_result(t_cmds **input, int i, int *j);
void					ft_lstclear_cmds(t_cmds **lst, void (*del)(void *));
void					set_redi_value(t_content **content);
int						ft_count_files(t_cmds **cmds, int start);
void					load_command(t_content **ctnt, t_cmds **cmds, int *s,
							int i);
int						new_len_counter(char *token);
char					*copy_with_specials(const char *line, int start,
							int *end);
int						check_and_alloc(int *index, int *i, const char *line,
							char *result);
void					alloc_error(void);
void					get_start_and_end(int *s, int *e, char *line, int i);
char					*produce_unquoted_line(char *line, int start, int end,
							int red_before);
void					init_vars(int *s, int *e, int *i, int *index);
void					fill_portion_with_spaces(char **str, int start,
							int end);
void					extract_interval(char *line, int *start, int *end,
							int i);
int						process_token(t_cmds **input, t_list **lst_token,
							int i);
int						process_regular_token(t_cmds **input, int i, int *end);
int						process_delimiter(t_cmds **input, int i, int *end);
void					check_and_getend(t_cmds **input, int i, int *end);
void					spaces_skiping(t_cmds **input, int *index);
char					*expand_doc(t_cmds **input, char *str);
void					extract_filenames(t_cmds **all_commands, int start,
							int *len);
void					extract_output_red(t_content **cnt, t_cmds **cmds,
							int *j, int *v);
void					process_input_redir(t_content **content, t_cmds **cmds,
							int s);
void					output_redirection(t_content **content,
							t_cmds **all_cmds, int s);
void					eof_len(int *len, t_cmds **cmds, int s);
int						error_redi(void);
char					*skip_quotes(char *value);
int						dollar_only(char *line, int index);
int						check_if_skipped(char *line, int rank);
int						ft_strcmp(const char *s1, const char *s2);
t_cmds					*ft_ambigous_handler(t_cmds **all_cmds);
void					signal_proccess(void);
void					store_value(t_cmds **input, int start, int end, int i);
void					store_last(t_cmds **input, int i, int len, int end);
void					store_first(t_cmds **input, int start, int i);
void					expand_special(t_cmds **input, int i, int *j);
void					c_process(int sig);
void					backslash_process(int sig);
int						no_out_append(t_content **cnt);
int						special_char_inbetween(char *line, int start, int end);
void					store_value_doc(t_cmds **input, char *str, int start,
							int end);
void					store_first_doc(t_cmds **input, char *str, int start);
char					*get_exitstatus_doc(void);
void					store_last_doc(t_cmds **input, char *str, int len,
							int end);
void					ft_do_that_doc(t_cmds **input, char *str, char *get);
void					ft_do_this_doc(t_cmds **input, char *str, char *get);
void					expand_special_doc(t_cmds **input, char *str, int j,
							int *end);
void					expand_to_key_doc(t_cmds **input, char *str, int *j);
void					renetialize_content(t_cmds **all_commands);
void					manage_space_presence(t_cmds **input);
char					*insert_limits(t_cmds **input, int i);
void					check_args(int ac, char **av);
void					get_red(int *red, t_cmds **input, int n, char **line);
int						ft_ambig_red(t_cmds *input, t_cmds **list);
int						ft_syntax(t_cmds *input);
int						ft_empty(t_cmds *input);
void					skips_in_redi(t_cmds **tmp);
void					backslash_deleter(char **red);
/*execution*/
t_env					*load_environement3(t_env *lst);
int						handling_export(char **interput, t_env **env, int d);
int						handling_cd(t_env **env, char **interput, int d);
int						handling_echo(char **interput, int d);
int						handling_pwd(t_env **env, int d);
int						handling_env(t_env **env, int d);
char					**load_environement2(char **env);
void					ft_cd(char **interput, t_env **env, int j, char *ptr);
void					ft_cd_back(t_env **env, int j, char *ptr,
							char **interput);
int						exec_cmd3_helper(char **ptr, int i, char **interput,
							char **env);
int						exec_cmd3(char **interput, char **env, int i);
char					*ft_join_5(char *content, char *ptr);
char					*ft_join_4(char *content, char *ptr);
void					exec_v2(int t);
void					exec_1(char **interput, int t);
int						exec_cmd3_v2(char **interput, char **env);
int						ch_in(char **interput);
int						exec_cmd4(char **interput, char *str, char **env,
							char **ptr);
char					*get_path(char **env);
char					*get_path2(char *ptr, char *str, char **env, int i);
int						ft_pipe1(t_cmds **input_1, t_env **lst, int next[2]);
void					ft_pids(void);
void					ft_execution(t_cmds *input, t_env **lst, int next[2],
							int prev[2]);
void					ft_first_cmd(t_cmds *input, t_env **env, int next[2]);
int						redi_file_2(t_cmds *input);
void					check_num_2(t_cmds *input, t_env **lst, int file,
							int fd[2]);
void					execute_files(t_cmds *input, int t, int file,
							t_env **lst);
int						open_files_4(char **filenames, int j, int i);
int						open_files(t_cmds *input, t_env **lst, int i);
void					execute_files_2(t_cmds *input, int fd[2], t_env **lst,
							int file);
int						open_files_2(t_cmds *input, int fd[2], t_env **env);
char					*herdoc_file(t_cmds *input, t_env **lst, int *t);
void					execute_herdoc(t_cmds *input, t_env **lst, int fd[2],
							int herdoc[2]);
void					infile_redi3(t_cmds *input, t_env **lst, int fd[2]);
int						ft_cd_back2(int j, char *ptr);
void					ft_export_3(char *interput);
void					ft_export3(char *interput, t_env **env);
int						check_i(t_env **env, char *interput);
char					*check_env2_h(char *content, char *ptr, int j);
int						check_env2(t_env **envi, char *in, char *ptr, int j);
int						check_env2_2(char *interput, char *content, int i,
							char *ptr);
char					*check_env3(char *content, char *ptr, int j,
							char *interput);
void					display_env(t_env **lst);
void					ft_multiple(int fd_2[2], char **interput, int fd[2],
							char **env);
t_env					*load_environement(char **env, t_env *lst);
void					pipe_handling(char **env, t_cmds **input_2, int i);
int						exec_cmd(char **interput, int input, int output,
							t_env **lst);
int						check_redi(t_cmds **input_2, int fd[2], t_env **lst);
char					*before_the_last_list_(t_env *node);
char					*get_path(char **env);
void					ft_export_2(char **interput, t_env **env);
void					ft_multiple_pipe(t_cmds **input_1, t_env **lst);
void					ft_echo(char **interput);
void					exec_cmd_redirection(char **interput, int input,
							int output, t_env **lst);
void					ft_pwd(t_env **enve);
int						handling_b_v2(t_env **env, char **interput);
char					*get_path(char **env);
void					ft_lstadd_back_(t_env **lst, t_env *new);
void					handling_b(t_env **env, char **interput);
t_env					*ft_lstlast_(t_env *lst);
t_env					*new_list(char *content);
void					ft_export(char **interput, t_env **env, int j);
void					ft_export4(t_env **env, t_env *ptr2, char *str2,
							char *ptr);
int						check_interput(char *interput);
void					change_oldpwd(t_env **envi);
void					ft_lstdelone_(t_env *lst);
void					ft_unset(char *interput, t_env **env);
int						ft_join(t_env **env, char *interput, int a);
int						check_content(char *ptr);
void					change_pwd(t_env **envi, char *ptr);
int						exec_cmd_2(char **interput, char **env, t_env **lst);
int						check_parametre(char *interput);
int						check_env(t_env **lst, char *interput);
void					ft_exit_(char **interput, int i, t_env **lst);
void					load_env_2(t_env **lst);
void					ft_cd_home(t_env **env, char *ptr, t_env *enve, int j);
int						home_check(char *ptr, int j);
int						ft_cd_oldpwd(t_env **env, char *ptr, t_env *enve,
							int j);
int						check_oldpwd(char *ptr, int j);
void					ft_cd_own(char **interput, int j);
void					ft_cd_back(t_env **env, int j, char *ptr,
							char **interput);
void					ft_cd_exf(t_env **env, char **interput, int j,
							char *ptr);
int						ft_cd_check(char **interput, int j, char *str);
void					ft_cd_access(t_env **env, int j, char *ptr, char *str);
int						ft_cd_mult(char **interput, int j);
void					rl_replace_line(const char *s, int i);
void					ft_export_h(t_env	**env, char **interput);
#endif
