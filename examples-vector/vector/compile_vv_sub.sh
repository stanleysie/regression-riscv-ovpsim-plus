riscv-none-embed-gcc Vector-Vector-Subtraction.c ../../vsupport.o -o Vector-Vector-Subtraction.elf  -Wall -Werror -Isupport -mabi=lp64d -march=rv64gc -g -DVVER=8 -Wl,--start-group,-lg,-lgloss,--end-group -lm -Wa,-march=rv64gv