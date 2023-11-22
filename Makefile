CC = gcc

TARGET = meowscript
SRC = main.c
INSTALL_DIR = /usr/local/bin

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) -o $(TARGET) $(SRC)

install: $(TARGET)
	install -m 755 $(TARGET) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(TARGET)

clean:
	rm -f $(TARGET)
