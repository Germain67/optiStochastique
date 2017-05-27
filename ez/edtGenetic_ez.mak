

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

edtGenetic_ezLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =  -fopenmp	-O2 -g -Wall -fmessage-length=0 -I$(edtGenetic_ezLIB_PATH)include -I$(EZ_PATH)boost

OBJS = edtGenetic_ez.o edtGenetic_ezIndividual.o 

LIBS = -lpthread -fopenmp 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :

  CPPFLAGS+="-std=c++11"

#END OF USER MAKEFILE OPTIONS

TARGET =	edtGenetic_ez

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(edtGenetic_ezLIB_PATH)/libeasea.a $(EZ_PATH)boost/program_options.a $(LIBS)

	
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^

all:	$(TARGET)
clean:
ifneq ("$(OS)","")
	-del $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
easeaclean:
ifneq ("$(OS)","")
	-del $(TARGET).exe *.o *.cpp *.hpp edtGenetic_ez.png edtGenetic_ez.dat edtGenetic_ez.prm edtGenetic_ez.mak Makefile edtGenetic_ez.vcproj edtGenetic_ez.csv edtGenetic_ez.r edtGenetic_ez.plot edtGenetic_ez.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp edtGenetic_ez.png edtGenetic_ez.dat edtGenetic_ez.prm edtGenetic_ez.mak Makefile edtGenetic_ez.vcproj edtGenetic_ez.csv edtGenetic_ez.r edtGenetic_ez.plot edtGenetic_ez.pop
endif

