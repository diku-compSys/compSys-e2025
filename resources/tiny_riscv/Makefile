PYTHON = python3 # or just 'python' on some platforms

%.elf: %.c lib.c Makefile
	$(PYTHON) ./gcc.py -O1 $< lib.c -o $@

%.dis: %.elf Makefile
	$(PYTHON) ./objdump.py -s -w $< > $@
	$(PYTHON) ./objdump.py -S $< >> $@

