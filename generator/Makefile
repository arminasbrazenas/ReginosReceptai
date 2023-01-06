CC              =   gcc
OUT_DIR         =   .out
OUT             =   generator.exe
ASSETS_DIR      =   assets
COPY_ASSETS     =   xcopy /i /y "$(ASSETS_DIR)" "$(OUT_DIR)/$(ASSETS_DIR)"
DIR_GUARD       =   if not exist "$(OUT_DIR)" mkdir "$(OUT_DIR)"

all: main.o html-generator.o
    $(DIR_GUARD)
    $(COPY_ASSETS)
    $(CC) -o $(OUT_DIR)/$(OUT) $(OUT_DIR)/main.o $(OUT_DIR)/html-generator.o
    cd $(OUT_DIR) && $(OUT)

main.o: main.c
    $(DIR_GUARD)
    $(CC) -c main.c -o $(OUT_DIR)/main.o

html-generator.o: html-generator.c html-generator.h
    $(DIR_GUARD)
    $(CC) -c html-generator.c -o $(OUT_DIR)/html-generator.o

clean:
    rd /s /q $(OUT_DIR)