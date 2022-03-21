A compiler project written in c, the language is called np (not pascal), its a weird mix between C and scripting languages.

The progress has stalled since 2022 but i will maybe resume at some point.

Done:
- Documentation
- Scanner
- Parser
so roughly:
| Code | -> |Token Array| -> |Token Tree| -> |Intermediate Language (3ac)| -> |Machine Code|
[^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^]
this part is done by now.

Any contributions in any way appreciated. Just clone and make a pull request. 

The following is a code snippet based on the grammar i created for this language.
######################################
##########test_program.npc############
######################################
#PROGRAM main;
#using std.system.println;

int main(char[10] argv) {
	int i = 30;
	int b = i * 30 * 8 + (20*3) + 1834 * 83;
	if (sizeof(argv) < 2) {
		println("ERROR: Program requires at least 1 argument");
		return 2;
	};
	char[10] str = "Hello World";
	for (int i = 0; i < sizeof(str); i++) {
		if (str[i] <= 91) {
			println("lower");
		};
	};
	println("\n");
	println("Program exit successful!");
	return 0;
}
######################################
######################################
######################################
