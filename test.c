// char    get_match(char c)
// {
//     if (c == '(')
//         return (')');
//     else if (c == '{')
//         return ('}');
//     else if (c == '[')
//         return (']');
//     else if (c == ')')
//         return ('(');
//     else if (c == '}')
//         return ('{');
//     else
//         return ('[');
// }

// int testScope(char s[], short scopeEnd)
// {	
// 	return (0);
// }

// bool isValid(char* s) {

// 	bool	valid = 1;
//     short   scopeEnd;
//     char    deepthDegree;

// 	while (*s) {
// 		if (*s != '(' && *s != '[' && *s != '{')
// 			return (0);
// 		scopeEnd = 1;
// 		deepthDegree = 0;
// 		while (s[scopeEnd]) {
// 			if (s[scopeEnd] == *s)
// 				deepthDegree++;
// 			else if (s[scopeEnd] == get_match(*s)) {
// 				if (deepthDegree)
// 					deepthDegree--;
// 				else {
// 					valid = valid && testScope(s, scopeEnd);
// 					scopeEnd++;
// 					break ;
// 				}
// 			}
// 			scopeEnd++;
// 		}
// 		s = s + scopeEnd;
// 	}
// 	return (valid);
// }

typedef struct s_stack {
	struct s_stack	*next;
	struct s_stack	*previous;
	char			letter;
}	t_stack;


void	add_node(t_stack **stack, t_stack *node) {
	if (*stack == NULL) {
		*stack = node;
		node->previous = NULL;
	}
	else {
		node->previous = *stack;
		(*stack)->next = node;
		*stack = (*stack)->next;
	}
	node->next = NULL;
}


void	remove_node(t_stack **stack) {
	t_stack	*last_node = *stack;
	if ((*stack)->previous)
		(*stack) = (*stack)->previous;
	else
		(*stack) = NULL;
	(*stack)->next = NULL;
	free(last_node);
}	


t_stack	*create_node(char letter) {	
	t_stack	*node = malloc(sizeof(t_stack));
	if (node == NULL)
		return (NULL);

	node->letter = letter;
	return (node);
}

int match(char new, char old) {
    if (old == '(' && new == ')')
        return (1);
    else if (old  == '{' && new == '}')
        return (1);
    else if (old  == '[' && new == ']')
        return (1);
    return (0);
}

bool	isValid(char* s) {
	t_stack	*stack = NULL;
	t_stack	*node = NULL;

	while (*s) {
		if (*s == '(' || *s == '[' || *s == '{') {
			node = create_node(*s);
			if (node == NULL)
				return (0);
			add_node(&stack, node);
		}
		else if (match(stack->letter, *s))
			remove_node(&stack);
		else
			break ;
		s++;
	}

	if (stack) {
		while (stack)
			remove_node(&stack);
		return (0);
	}
	return (1);
}