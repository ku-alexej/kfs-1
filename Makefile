CC      := gcc
AS      := as
LD      := ld
GRUB_MKRESCUE := grub-mkrescue
QEMU    := qemu-system-i386

# ---------------------------------------------------------------------------
# Compiler / assembler / linker flags
# ---------------------------------------------------------------------------

CFLAGS  := -m32 -ffreestanding -fno-builtin -fno-stack-protector \
           -fno-pie -fno-asynchronous-unwind-tables -mno-mmx -mno-sse -mno-sse2 -msoft-float \
           -nostdlib -nodefaultlibs \
           -Wall -Wextra -Werror -std=c99 -Iinclude
ASFLAGS := --32
LDFLAGS := -m elf_i386 -T ft_linker.ld -nostdlib

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

C_SRCS  := src/kernel.c src/screen.c src/string.c
C_OBJS  := $(C_SRCS:%.c=$(BUILD)/%.o)
ASM_OBJS := $(BUILD)/src/boot.o
OBJS    := $(ASM_OBJS) $(C_OBJS)

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
	@mkdir -p $(ISO_DIR)/boot/grub $(BUILD)
	cp $(KERNEL) $(ISO_DIR)/boot/kernel.elf
	$(GRUB_MKRESCUE) -o $(ISO) $(ISO_DIR)

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
	executable=$$(command -v grub-file 2>/dev/null) && $$executable --is-x86-multiboot $(KERNEL) || true

# ---------------------------------------------------------------------------
# Clean
# ---------------------------------------------------------------------------

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -rf $(ISO_DIR)

re: fclean all
