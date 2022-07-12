int is_number(char* ptr)
{
	return *ptr >= 48 && *ptr <= 57;
}
int is_underscore(char* ptr)
{
	return *ptr == 95;
}
int is_latin(char* ptr)
{
	return (*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z');
}
int is_newline(char* ptr)
{
	return *ptr == 10;
}
int is_space(char* ptr)
{
	return *ptr == 32;
}
int is_tab(char* ptr)
{
	return *ptr == 9;
}
int is_whitespace(char* ptr)
{
	return *ptr == ' ' || *ptr == '\t' || *ptr == '\n' || *ptr == '\v' || *ptr == '\f' || *ptr == '\r';
}
