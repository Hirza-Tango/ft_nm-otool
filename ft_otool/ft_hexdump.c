#include "ft_otool.h"
void	ft_hexdump(void *region, size_t size, int fd)
{
	size_t			i;

	i = 0;
	if (!region)
		return ;
	while (i < size)
	{
		ft_printf_fd(fd, "%0zu %0hhx", region + i, *(char *)(region + i++));
		while (i < size && i % 8)
			ft_printf_fd(fd, " %0hhx", *(char *)(region + i++));
		ft_putchar('\n');
	}
}

int main()
{
	char *a = ft_strdup("Hello Darkness My Old Friend");

	ft_hexdump(a, ft_strlen(a), 1);
}
