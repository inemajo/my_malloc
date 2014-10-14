
int	main()
{
  char *f;

  f = malloc(400);
  free(f + 50);
  printf("coucou\n");
  free(f);
}
