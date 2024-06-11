

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"
#include "../libs/libft/libft.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "files_fd.h"

static void process_init(t_process *process)
{
    process->pid = -1;
    process->input[0] = -1;
    process->input[1] = -1;
    process->output[0] = -1;
    process->output[1] = -1;
}

t_process *ft_allocate_process(void) {
    t_process *process = (t_process *)malloc(sizeof(t_process));
    if (!process) {
        perror_msg("malloc");
        return NULL;
    }
    process_init(process);
    return process;
}

t_cmd_new   *ft_allocate_cmd(t_cmd_new *cmd)
{
    cmd = (t_cmd_new *)malloc(sizeof(t_cmd_new));
    if (!cmd)
        return (NULL);
    cmd->str = NULL;
    cmd->arr = NULL;
    cmd->env = NULL;
    cmd->path = NULL;
    return (cmd);
}

void    ft_init_cmd(t_cmd_new *cmd, char *str, char **envp)
{
    ft_allocate_cmd(cmd);
    if (!cmd)
        return ;
    cmd->str = str;
    cmd->arr = ft_split(str, ' ');
    cmd->env = envp;
    cmd->path = command_path(str, envp);
}


void ft_open_files(int fd[2], int argc, char **argv)
{
    fd[READ_END] = open(argv[1], O_RDONLY);
    if (fd[READ_END] == -1)
        perror_msg(argv[1]);
    fd[WRITE_END] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd[WRITE_END] == -1)
        perror_msg(argv[argc - 1]);
    printf("files opened\n");
}

void    ft_close_process_input_fds(t_process *process)
{
    if ( process->input[READ_END] != -1)
        close(process->input[READ_END]);
    if ( process->input[WRITE_END] != -1)
        close(process->input[WRITE_END]);
    process->input[READ_END] = -1;
    process->input[WRITE_END] = -1;
}

void    ft_wait_for_all(t_process *process)
{
    while (process)
        waitpid(process->pid, NULL, 0);
}


void    ft_print_process_data(t_process *process)
{
    printf("\n\npid: %d\ninput: read: %d write: %d\noutput: read: %d write: %d\ncmd: %s\ncmd path: %s\n\n", process->pid, process->input[READ_END], process->input[WRITE_END], process->output[READ_END], process->output[WRITE_END], process->cmd_new.str, process->cmd_new.path);
}

void print_open_files(int *fd, char *call)
{
    printf("files opened by: %s\n read: %d\n write: %d\n", call, fd[READ_END], fd[WRITE_END]);
}

void ft_manage_child(t_process *process, char *command, char **envp)
{
    process_fds(process->input, process->output, FT_FD_INIT | FT_FD_DUP);
    if (process->input[READ_END] == -1)
        process_fds(process->input, process->output, FT_FD_ERROR | FT_FD_CLOSE);
    else
        command_call(command, envp);
    process_fds(process->input, process->output, FT_FD_CLOSE);
    exit(0);
}

void    create_node(t_list **list)
{
    t_process *process;

    process = ft_allocate_process();
    if (!process)
        exit (1); //clean here
    ft_lstadd_back(list, ft_lstnew((void *)process));
}

void    add_node_output_process(t_process *process)
{
    if (pipe(process->output) < 0)
        perror_msg("pipe");
    // print_open_files(process->output, "add_node_output_");
}

void    fork_process(t_process *process)
{
    process->pid = fork();
    if (process->pid == -1)
        perror_msg("fork");
}

t_process *ft_get_before_last_process(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while (tmp->next && tmp->next->next)
        tmp = tmp->next;
    return ((t_process *)tmp->content);
}

void    add_input_to_process(t_list *list, t_process *process_last)
{
    t_process *prev_process;

    if (list && list->next)
    {
        prev_process = ft_get_before_last_process(list);
        process_last->input[READ_END] = prev_process->output[READ_END];
        process_last->input[WRITE_END] = prev_process->output[WRITE_END];
        return ;
    }
    return ;
}

void    add_input_to_first_process(t_process *process, char *file)
{
    (process->input)[READ_END] = open(file, O_RDONLY);
    if ((process->input)[READ_END] == -1)
        perror_msg(file);
    (process->input)[WRITE_END] = -1;
    return ;
}

void   add_output_to_last_process(t_process *process, char *file)
{
    process->output[READ_END] = -1;
    process->output[WRITE_END] = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (process->output[WRITE_END] == -1)
        perror_msg(file);
}

int		pipex_new(int argc, char **argv, char **envp)
{
    t_list    *list;
    t_process *process;
    int     i;
 
    printf("envp: %s\n", envp[0]);
    list = NULL;
    process = NULL;
    
    i = 1;
    while (++i < argc - 1)
    {
        create_node(&list);
        process = (t_process *)ft_lstlast(list)->content;
        if (!list)
            return (1);
        if (i == 2)
            add_input_to_first_process(process, argv[1]);
        else
            add_input_to_process(list, process);
        if (i == argc - 2)
            add_output_to_last_process(process, argv[argc - 1]);
        else
            add_node_output_process(process);
        fork_process(process);
        if (process->pid == 0)
                ft_manage_child(process, argv[i], envp);
        fd_close(process->input);
    }
    fd_close(process->output);
    // ft_lstiter(list, (void *)ft_print_process_data);
    ft_lstclear(&list, free);
    return (0);
}