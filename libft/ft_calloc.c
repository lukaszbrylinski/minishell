/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dszafran <dszafran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:32:16 by dszafran          #+#    #+#             */
/*   Updated: 2024/12/30 19:22:05 by dszafran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	if ((size * nmemb) / nmemb != size)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
//could have changed overflow test for n_items > SIZE_MAX/size
// #include <stdio.h>
// int main() 
// {
//   int size = 8539;
//   int *myArray = ft_calloc(size, sizeof(int));

//   // Write into the memory
//   for(int i = 0; i < size; i++) {
//     myArray[i] = i + 1;
//   }

//   // Display the contents of the memory
//   for(int i = 0; i < size; i++) {
//     printf("%d ", myArray[i]);
//   }

//   // Free the memory
//   free(myArray);
//   myArray = NULL;

//   return 0;
// }
