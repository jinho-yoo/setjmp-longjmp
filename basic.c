#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
 
jmp_buf mark;
 
void p(void);
void recover(void);
 
int main(void)
{
   if (setjmp(mark) != 0)
   {
      printf("longjmp has been called\n");
      recover();
      exit(1);
      }
   printf("setjmp has been called\n");
   printf("Calling function p()\n");
   p();
   printf("This point should never be reached\n");
}
 
void p(void)
{
   printf("Calling longjmp() from inside function p()\n");
   longjmp(mark, -1);
   printf("This point should never be reached\n");
}
 
void recover(void)
{
   printf("Performing function recover()\n");
}
