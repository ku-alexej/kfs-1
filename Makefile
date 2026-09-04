CC      := gcc
AS      := as
LD      := ld
GRUB_MKRESCUE := $(shell command -v grub2-mkrescue 2>/dev/null || command -v grub-mkrescue 2>/dev/null)
GRUB_MODULES ?= $(firstword $(wildcard /usr/lib/grub/i386-pc /usr/lib/grub2/i386-pc))
QEMU    := qemu-system-i386

# ---------------------------------------------------------------------------
# Compiler / assembler / linker flags
# ---------------------------------------------------------------------------

CFLAGS      := -m32 -ffreestanding -fno-builtin -fno-stack-protector \
				-fno-pie -fno-asynchronous-unwind-tables -mno-mmx -mno-sse -mno-sse2 -msoft-float \
				-nostdlib -nodefaultlibs \
				-Wall -Wextra -Werror -std=c99 -Iinclude
ASFLAGS     := --32
LDFLAGS     := -m elf_i386 -T ft_linker.ld -nostdlib
GRUBFLAGS   := --install-modules="multiboot configfile"

# ---------------------------------------------------------------------------
# Project directories
# ---------------------------------------------------------------------------

BUILD   := build
KERNEL  := $(BUILD)/kernel.elf
ISO_DIR := iso
ISO     := $(BUILD)/kfs_1.iso

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------

C_SRCS		:= src/kernel.c \
				src/screen.c \
				src/string.c \
				src/printk.c
C_OBJS		:= $(C_SRCS:%.c=$(BUILD)/%.o)
ASM_OBJS	:= $(BUILD)/src/boot.o
OBJS		:= $(ASM_OBJS) $(C_OBJS)

# ---------------------------------------------------------------------------
# Targets
# ---------------------------------------------------------------------------

.PHONY: all kernel iso run clean fclean re check

all: kernel

kernel: $(KERNEL)

# ---------------------------------------------------------------------------
# Kernel
# ---------------------------------------------------------------------------

$(BUILD)/src/%.o: src/%.s
	@mkdir -p $(@D)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD)/src/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL): $(OBJS) ft_linker.ld
	@mkdir -p $(@D)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

# ---------------------------------------------------------------------------
# ISO
# ---------------------------------------------------------------------------

iso: $(KERNEL)
	@test -n "$(GRUB_MKRESCUE)" || { echo "Error: grub2-mkrescue or grub-mkrescue is required"; exit 1; }
	@test -n "$(GRUB_MODULES)" || { echo "Error: GRUB i386-pc modules are missing; install grub2-pc-modules or set GRUB_MODULES=/path/to/i386-pc"; exit 1; }
	@mkdir -p $(ISO_DIR)/boot/grub $(BUILD)
	cp $(KERNEL) $(ISO_DIR)/boot/kernel.elf
	$(GRUB_MKRESCUE) -d "$(GRUB_MODULES)" $(GRUBFLAGS) -o $(ISO) $(ISO_DIR)

# ---------------------------------------------------------------------------
# Run
# ---------------------------------------------------------------------------

run: iso
	$(QEMU) -cdrom $(ISO)

# ---------------------------------------------------------------------------
# Check
# ---------------------------------------------------------------------------

check: $(KERNEL)
	readelf -h $(KERNEL)
	readelf -S $(KERNEL)
	executable=$$(command -v grub2-file 2>/dev/null || command -v grub-file 2>/dev/null) && $$executable --is-x86-multiboot $(KERNEL) || true

# ---------------------------------------------------------------------------
# Clean
# ---------------------------------------------------------------------------

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(ISO_DIR)/boot/kernel.elf

re: fclean all
