# define which architecture you're targeting
ARCH = x86_64
# define your target file here
TARGET = ../BOOTX64.efi
#define your sources here
SRCS = $(wildcard *.c)
# define your default compiler flags
CFLAGS = -pedantic -Wall -Wextra -Werror  -O2 #--ansi
# define your default linker flags
#LDFLAGS =
# define your additional libraries here
#LIBS = -lm

# leave the hard work and all the rest to posix-uefi

# set this if you want GNU gcc + ld + objcopy instead of LLVM Clang + Lld
#USE_GCC = 1
include uefi/Makefile
