void foo(long len, long list[len])
{
}

int main()
{
  long larray[10];
  long *lpointer;
  foo(10, larray);
  foo(10, lpointer);
}
