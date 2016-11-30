#include <stdlib.h>
#include <stdio.h>

#include "ast.h"
#include "parser.h"

int main(int argc, char **argv)
{
	struct ast *tree;
	char *postfix;
	char *infix;

	for(int i=1; i < argc; ++i) {
		tree = parse(argv[i]);
        infix = ast_infix(tree);
        postfix = ast_postfix(tree);

		printf("%s\n"
			   "    infix:    %s\n"
		       "    postfix:  %s\n\n", argv[i], infix, postfix);

		ast_release(tree);
		free(postfix);
		free(infix);
	}

	return EXIT_SUCCESS;
}
