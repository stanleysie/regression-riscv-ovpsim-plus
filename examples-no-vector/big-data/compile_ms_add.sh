riscv-none-embed-gcc Matrix-Scalar-Addition.c ../../vsupport.o -o Matrix-Scalar-Addition.elf  -Wall -Werror -Isupport -mabi=lp64d -march=rv64gc -g -DVVER=8 -Wl,--start-group,-lg,-lgloss,--end-group -lm -Wa,-march=rv64gv