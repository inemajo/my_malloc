/*
** malloc.c for Malloc in /home/bellan_r/work/projet/inemajo2.0/malloc/from_scrach
** 
** Made by romain bellan
** Login   <bellan_r@epitech.net>
** 
** Started on  Mon Feb 22 14:11:32 2010 romain bellan
** Last update Thu Mar 25 18:31:28 2010 romain bellan
*/

#include		"malloc.h"

static memcase		*alloc_new_case(size_t size)
{
  memcase		*new;
  size_t		psize;
  
  psize = pow2up(size + sizeof(memcase));
  if (psize < PAGE_SIZE)
    psize = PAGE_SIZE;
  new = (memcase *)sbrk(psize);
  if (new == (memcase *)(-1))
    return (0);
  new->size = size;
  new->allocated_size = psize;
  return (new);
}

#include <stdio.h>

static void			*firstmalloc(size_t size)
{
  extern memcase	*memmap;
  extern void		*first_alloc;
  memcase		*res;

  getmalloc_conf();
  memmap = alloc_new_case(size);
  first_alloc = (void *)memmap;
  res = (void *)((size_t)memmap + sizeof(memcase));
  return (res);
}

void			*malloc(size_t size)
{
  extern memcase	*memmap;
  extern void		*first_alloc;
  extern malloc_conf	myconf;
  memcase		*tmp;
  void			*res;

  if (size == 0)
    return (0);
  if (memmap == 0)
    res = firstmalloc(size);
  if (myconf.maxalloc < size)
    return (0);
  else if ((tmp = find_memory(size)) != 0)
    {
      tmp->size = size;
      res = (void *)((size_t)tmp + sizeof(memcase));
    }
  else
    {
      tmp = alloc_new_case(size);
      tmp->next = memmap;
      memmap = tmp;
      res = (void *)((size_t)memmap + sizeof(memcase));
    }
  return (res);
}

void			*calloc(size_t number, size_t size)
{
  char			*res;
  size_t		rsize;

  rsize = number * size;
  res = malloc(rsize);
  while (rsize)
    {
      --rsize;
      res[rsize] = 0;
    }
  return (res);
}
