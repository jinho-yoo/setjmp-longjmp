#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

#define JB_BX 0
#define JB_SI 1
#define JB_DI 2
#define JB_BP 3
#define JB_SP 4
#define JB_PC 5

int g_a=0;
int g_b;

static int ptr_mangle(int p) {
    unsigned int ret;
    asm(" movl %1, %%eax;\n"
        " xorl %%gs:0x18, %%eax;"
        " roll $0x9, %%eax;"
        " movl %%eax, %0;"
    : "=r"(ret)
    : "r"(p)
    : "%eax"
    );
    return ret;
}

main()
{
  jmp_buf env;
  int i;
  int v;

  i = setjmp(env);
  printf("\ni = %d\n", i);
HERE:
  printf("\nmain= 0x%08x", main);
  printf("\n&g_a= 0x%08x", &g_a);
  printf("\n&g_a= 0x%08x", &g_b);
  for (i=0;i<9;i++) {
     printf("\nenv[%d] = 0x%08x", i, env->__jmpbuf[i]);
     v=env->__jmpbuf[i];
     //printf("\nptr_mangle(env[%d]) = 0x%08x", i, ptr_mangle(v));
  } // end for
  printf("\n");
/*
  printf("\nenv[JB_PC] = 0x%08x", env->__jmpbuf[JB_PC]);
  printf("\nptr_mangle(env[JB_PC]) = 0x%08x", ptr_mangle((int)env->__jmpbuf[JB_PC]));
  printf("\nptr_mangle(env[JB_PC]) = 0x%08x", ptr_mangle((int)env[JB_PC]));
  printf("\nenv[JB_SP] = 0x%08x", env[JB_SP]);
  printf("\nptr_mangle(env[JB_SP]) = 0x%08x", ptr_mangle((int)env[JB_SP]));
*/

  if (i != 0) exit(0);

  longjmp(env, 2);
  printf("Does this line get printed?\n");

}
