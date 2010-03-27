CC=g++
CFLAGS=-I. -Igosu `gosu/bin/gosu-config --cxxflags` -g -Itinyxml -Iportaudio/include -ISDL_ttf
LDFLAGS=-Igosu `gosu/bin/gosu-config --libs --cxxflags` gosu/lib/libgosu.a -lportaudio -lSDL_ttf

#-lrt -lasound -ljack -lpthread portaudio/lib/.libs/libportaudio.a -g 
#tinyxml/tinyxml.a -lboost_regex -g

OBJECTS=main.o juego.o estadoImagenFija.o \
	estadoMenu.o FFT.o analizador.o estadoAnalizador.o colores.o animacion.o

EXE=programa

actual: $(OBJECTS)
	$(CC) $? $(LDFLAGS) -o $(EXE)


analizador.o: analizador.h
FFT.o: FFT.h
juego.o: juego.h
main.o: estado.h juego.h
estadoImagenFija.o: estadoImagenFija.h estado.h juego.h
estadoMenu.o: estado.h estadoMenu.h juego.h customFont.h animacion.h
estadoAnalizador.o: estado.h estadoAnalizador.h juego.h analizador.h
animacion.o:animacion.h

colores.o: colores.h

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXE)