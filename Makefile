# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: denizozd <denizozd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/14 13:10:56 by denizozd          #+#    #+#              #
#    Updated: 2024/01/21 16:36:07 by denizozd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#			Variables				#
# The name of the executable
NAME = pipex
# The path to the libft library
LIB = $(LIBDIR)libft.a
# The directory containing libft source code
LIBDIR = ./libft/

# The compiler
CC = cc
 # Compilation flags
FLAGS = -Wall -Wextra -Werror

#			Source files			#
SRCS = main.c pipex.c utils.c

#			Targets					#
 # Object files to be created
OBJS = $(SRCS:.c=.o)

# Default target is to build the executable
all: $(NAME)

# Build the libft library
$(LIB):
	$(MAKE) -C $(LIBDIR)

# Build the executable using object files and libft
$(NAME): $(OBJS) $(LIB)
	$(CC) -g $(CFLAGS) $^ -o $@
# $^ represents all the prerequisites (object files and the libft library)
# -o specifies the output file
# $@ represents the target, which is the name of the executable

# Compile each source file into object files
%.o: %.c
	$(CC) -g $(CFLAGS) -I$(LIBDIR) -I . -c $< -o $@
# -I$(LIBDIR): This flag specifies an additional directory to include header files from. In this case, it includes header files from the libft directory.
# -I .: This flag includes the current directory as a directory to search for header files. The dot (.) represents the current directory.
#-c: This flag tells the compiler to generate object files (*.o) without linking. It essentially compiles the source code into an object file.
# $<: This is an automatic variable that represents the first prerequisite (dependency) of the rule. In the context of a compilation rule, it typically represents the source file (*.c file).
#-o $@: This flag specifies the output file name. $@ is an automatic variable representing the target of the rule, which, in this case, is the object file (*.o). So, -o $@ indicates that the compiler should output the compiled object file with the same name as the target.

 # Remove object files, clean libft object files
clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBDIR) clean
# Remove the executable, remove libft library and its object files
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBDIR) fclean
# Recompile everything
re: fclean all

# Declare these targets as phony (not real files) to avoid conflicts
.PHONY: all clean fclean re
