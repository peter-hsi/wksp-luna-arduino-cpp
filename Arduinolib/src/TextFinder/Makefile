

CC=gcc
CFLAGS=-I.
DEPS = TextFinder.h TextFinder.cpp
OBJ = TextFinder.o 

#avr-ar= "${dir.arduino.home}/hardware/tools/avr/bin/avr-ar.exe
AR=${dir.arduino.home}/hardware/tools/avr/bin/avr-ar

TARGET=$(OBJ)

all: $(TARGET) 


$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
	${avrgcc} ${gcc_switches}  ${includes}  ${dir.src}/@{fnc}  -o ${dir.src}/@{fnc}.o
	${avrgpp} ${gppswitches}  ${includes}  ${dir.src}/@{fncpp}  -o ${dir.src}/@{fncpp}.o


ar:$(TARGET)
	${avr-ar} ${ar-switches} ${path.lib.a} ${dir.src}/@{fnc}.o

clean:
  	$(RM) $(TARGET)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# hellomake: $(OBJ)
# 	gcc -o $@ $^ $(CFLAGS)
