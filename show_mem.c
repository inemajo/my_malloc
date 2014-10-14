/*
** show_mem.c for Coucou in /home/bellan_r/work/projet/inemajo2.0/malloc
** 
** Made by romain bellan
** Login   <bellan_r@epitech.net>
** 
** Started on  Mon Feb 15 16:37:17 2010 romain bellan
** Last update Thu Mar 25 15:11:29 2010 cyprien diot-
*/

#include "malloc.h"

static void		pnbr(int val, uint bas)
{
  char			*base = "0123456789abcdef";
  char			res;

  if (val < 0)
    {
      val *= -1;
      write(1, "-", 1);
    }
  if (val > (int)bas - 1)
    pnbr(val / bas, bas);
  res = base[val % bas];
  write(1, &res, 1);
}

static void		pstr(char *s)
{
  uint			i;

  i = 0;
  while (s[i])
    ++i;
  write(1, s, i);
}

static void		display_mem(memcase *memmap)
{
  if (memmap->next)
    display_mem(memmap->next);
  pstr("0x");
  pnbr((size_t)(memmap + 1), 16);
  pstr(" - 0x");
  pnbr((size_t)(memmap + 1) + memmap->size, 16);
  pstr(" : ");
  pnbr(memmap->size, 10);
  pstr(" octets\n");
} 

void			show_alloc_mem()
{
  extern memcase	*memmap;
  memcase		*tmp;

  tmp = memmap;
  pstr("break: 0x");
  pnbr((size_t)sbrk(0), 16);
  pstr("\n");
  if (tmp)
    display_mem(tmp);
}
