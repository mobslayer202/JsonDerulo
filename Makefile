CXXFLAGS = -Iinclude -Iinclude/handlers # set include paths

all: main.o CharReader.o HandlerHelper.o Json.o JsonPrinter.o ArrayHandler.o BoolNullHandler.o NumberHandler.o ObjectHandler.o StringHandler.o # Target names not filepaths
	g++ $(CXXFLAGS) obj/main.o obj/CharReader.o obj/HandlerHelper.o obj/Json.o obj/JsonPrinter.o obj/ArrayHandler.o obj/BoolNullHandler.o obj/NumberHandler.o obj/ObjectHandler.o obj/StringHandler.o -o output

main.o: main.cpp obj
	g++ $(CXXFLAGS) -c main.cpp -o obj/main.o

CharReader.o: src/CharReader.cpp obj
	g++ $(CXXFLAGS) -c src/CharReader.cpp -o obj/CharReader.o

HandlerHelper.o: src/HandlerHelper.cpp obj
	g++ $(CXXFLAGS) -c src/HandlerHelper.cpp -o obj/HandlerHelper.o

Json.o: src/Json.cpp obj
	g++ $(CXXFLAGS) -c src/Json.cpp -o obj/Json.o

JsonPrinter.o: src/JsonPrinter.cpp obj
	g++ $(CXXFLAGS) -c src/JsonPrinter.cpp -o obj/JsonPrinter.o

ArrayHandler.o: src/handlers/ArrayHandler.cpp obj
	g++ $(CXXFLAGS) -c src/handlers/ArrayHandler.cpp -o obj/ArrayHandler.o

BoolNullHandler.o: src/handlers/BoolNullHandler.cpp obj
	g++ $(CXXFLAGS) -c src/handlers/BoolNullHandler.cpp -o obj/BoolNullHandler.o

NumberHandler.o: src/handlers/NumberHandler.cpp obj
	g++ $(CXXFLAGS) -c src/handlers/NumberHandler.cpp -o obj/NumberHandler.o

ObjectHandler.o: src/handlers/ObjectHandler.cpp obj
	g++ $(CXXFLAGS) -c src/handlers/ObjectHandler.cpp -o obj/ObjectHandler.o

StringHandler.o: src/handlers/StringHandler.cpp obj
	g++ $(CXXFLAGS) -c src/handlers/StringHandler.cpp -o obj/StringHandler.o

obj:
	mkdir -p obj

clean: 
	rm output obj/*.o

