/*
** utils.c for Utils in /home/bellan_r/work/projet/inemajo2.0/malloc/from_scrach
** 
** Made by romain bellan
** Login   <bellan_r@epitech.net>
** 
** Started on  Mon Feb 22 14:16:15 2010 romain bellan
** Last update Thu Mar 25 18:12:52 2010 cyprien diot-
*/

#include "malloc.h"

void			p_error(char *err)
{
  int			i;
  extern malloc_conf	myconf;

  i = 0;
  while (err[i])
    ++i;
  if (myconf.info & CONFINFO_MSG_ON_ERR)
    write(2, err, i);
  if (myconf.info & CONFINFO_EXIT_ON_ERR)
    exit(1);
}

void		byte_copy(void *from, void *to, uint size)
{
  char		*f;
  char		*t;

  f = from;
  t = to;
  while (size)
    {
      --size;
      t[size] = f[size];
    }
}

size_t		pow2up(size_t nb)
{
#ifdef __FreeBSD__
  __asm__("bsr %%eax, %0\n"
	  "mov %0, %%eax" : "=r" (nb) : "r" (nb));
  return (2 << nb);
#else
  register int	i;
  
  i = 0;
  while (nb)
    {
      nb >>= 1;
      ++i;
    }
  return (2 << (--i));
#endif
}
