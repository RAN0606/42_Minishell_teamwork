#include "minishell.h"


t_list *ft_token(int token, char *str)
{
	t_token	*token_ptr;
	t_list	*token_element;

	token_ptr = malloc(sizeof(t_token));
	if (!token_ptr)
		return 0;
	token_ptr->token = token;
	token_ptr->str = ft_strdup(str);
	token_element = ft_lstnew((void *)token_ptr);
	return (token_element);

}

void ft_free_token (void *token)
{
	if (((t_token *)token)->str)
		free(((t_token *)token) ->str);
	free((t_token *)token);
}

void	ft_print_token(void *token)
{
	printf("token: %d, str :%s\n", ((t_token *)token)->token, ((t_token *)token)->str);
}
int	main(int argc, char **argv)
{
	t_list	*token;
	t_list	*token_list;

	token = NULL;
	token_list = NULL;
	while (--argc >= 0)
	{

		//if (1==argc)
		//	token = 0;
		token = ft_token(argc, argv[argc]);
		if (!token)
		{
		//	printf("token_list %p\n", token_list);
			if (token_list)
				ft_lstclear(&token_list,ft_free_token);	
		//	printf("token_list %p\n", token_list);
			return (1);
		}
	//	ft_print_token(token->content);
	//	ft_free_token(token->content);
	//	free(token);
		ft_lstadd_back(&token_list, token);

	}
	ft_lstiter(token_list,ft_print_token);
	ft_lstclear(&token_list,ft_free_token);
	printf("token_list %p\n", token_list);

	return (0);
}
