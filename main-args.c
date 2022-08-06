#define _g_xstr(a) _g_str(a)
#define _g_str(a) #a

int argc = 5;
char *argv[] = {
	"core.exe",
	"-v0",
	"-w" _g_xstr(W_WORKERS_NUM),
	"-c" _g_xstr(C_CONTEXT_NUM),
	"-i" _g_xstr(I_ITERATION_NUM)
};
