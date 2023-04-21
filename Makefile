CC = gcc

CFLAGS = -Wall -Werror -ggdb -funroll-loops -DTERM=$(TERM)
LDFLAGS = -lncurses

BIN = cuberotation
OBJS = cuberotation.o

all: $(BIN) etags
$(BIN): $(OBJS)
	@$(ECHO) Linking $@
	@$(CXX) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)
%.o: %.c
	@$(ECHO) Compiling $<
	@$(CC) $(CFLAGS) -MMD -MF $*.d -c $<

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.* gmon.out