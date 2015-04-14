#include <stdio.h>

int brace,brack,paren;
void in_quote(int c);
void in_comment();
void search(int c);

/* rudimentary syntax  checker for C program */ 
int main()
{
	int c;
	extern int brace, brack, paren;
	while ( (c = getchar()) != EOF)
	{
		if( c == '/')
		{
			if (( c = getchar()) == '*')
				in_comment();				// inside comment //
			else
				search(c);
		}
		else if ( c == '\'' || c =='"')
			in_quote(c);					// inside quote //
		else
			search(c);

		if (brace < 0)
		{
			printf("unbalanced braces\n");
			brace = 0;
		}
		else if (brack < 0)
		{
			printf("unbalanced brackets\n");
			brack = 0;
		}
		else if (paren < 0)
		{
			printf("unbalance parentheses\n");
			paren = 0;
		}
	}

	if (brace > 0)
		printf("unbalanced braces\n");
	if (brack> 0)
		printf("unbalanced brack\n");
	if (paren > 0)
		printf("unbalanced parentheses\n");
}
	
/* search: search for rudimentary syntax errors */
void search(int c)
{
	extern int brace,brack,paren;
	if (c == '{')
		++brace;
	else if (c == '}')
		--brace;
	else if (c == '[')
		++brack;
	else if (c == ']')
		--brack;
	else if (c == '(')
		++paren;
	else if (c == ')')
		--paren;
}

/* in_comment: inside of a valid commet */
void in_comment(void)
{
	int c, d;
	c = getchar();							// prev character //	
	d = getchar();							// curr character //	
	while (c != '*' || d != '/')			// search for the end //
	{
		c = d;
		d = getchar();
	}
}

/* in_quote: inside quote */
void in_quote(int c)
{
	int d;
	while ((d = getchar()) != c)
		if (d == '\\')
			getchar();
}
