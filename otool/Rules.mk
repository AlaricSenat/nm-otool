## Auto generated make tool, don't edit manually.
otool/$(OBJECT_DIR)/%.o: otool/%.c
	$(COMP) $@ $<
otool/$(OBJECT_DIR)/otool.o: otool/otool.c otool/otool.h opt/opt.h \
  common/common.h common/data_structures.h common/typedefs.h \
  libft/memory/memory.h libft/output/output.h
otool/otool.h:
opt/opt.h:
common/common.h:
common/data_structures.h:
common/typedefs.h:
libft/memory/memory.h:
libft/output/output.h:
otool/$(OBJECT_DIR)/otool_opt.o: otool/otool_opt.c otool/otool.h \
  opt/opt.h libft/string/string.h libft/output/output.h
libft/string/string.h:
