/**
*
*  @file abs_get_mem.h
*
*  @brief Gets the memory pointer and returns in and changes the new memory pointer
*
*  @param size The size of the memory going to be taken up
*
*  @return The pointer of old memory or null if not enough memory
*
*  @copyright Copyright 2013, Got Robot? FTC Team 5037
*
*/
#ifndef ABS_GET_MEM_H
#define ABS_GET_MEM_H

/** macros */

char* abs_get_mem(int size)
{
	/** makes sure that we dont corrupt any memory */
	if(&g_buffer + DYNAMIC_MEMORY_SIZE > g_next_available_memory_ptr + size)
	{
		char* old_memory = g_next_available_memory_ptr;
		g_next_available_memory_ptr = g_next_available_memory_ptr + size;
		return old_memory;
	}
	else
	{
		return NULL;
	}
}


#endif /* ABS_GET_MEM_H */
