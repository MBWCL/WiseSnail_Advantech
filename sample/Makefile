
#CC=arm-openwrt-linux-gcc
#CPP=arm-openwrt-linux-g++
#AR=arm-openwrt-linux-ar

CC=gcc
CPP=g++
AR=ar

INCPATH=-I../release
LIBPATH=-L../release
LIBS=-lpthread -lrt -lWiseSnail -lWiseCore_MQTT -lWiseCarrier_MQTT_Paho -lpaho-mqtt3cs -lssl -lcrypto -lm
LIBS2=-lpthread -lrt -lWiseSnail -lWiseCore_MQTT -lWiseCarrier_MQTT_Mosquitto -lmosquitto -lssl -lcrypto -lm

CFLAGS=-g
LDFLAGS=

TEST_ProgramName=test
TEST_DEPEND=test.o

TESTLIMIT_ProgramName=testlimit
TESTLIMIT_DEPEND=testlimit.o

SERVICE_ProgramName=service
SERVICE_DEPEND=service.o

all: $(TEST_ProgramName) $(TESTLIMIT_ProgramName) $(SERVICE_ProgramName)


$(TEST_ProgramName): $(TEST_DEPEND)
	$(CC) -o $@ $^ $(CFLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $(LDFLAGS) -Wl,-rpath,.


$(TESTLIMIT_ProgramName): $(TESTLIMIT_DEPEND)
	$(CC) -o $@ $^ $(CFLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $(LDFLAGS) -Wl,-rpath,.


$(SERVICE_ProgramName): $(SERVICE_DEPEND)
	$(CC) -o $@ $^ $(CFLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $(LDFLAGS)

.c.o:
	$(CC) -c $(INCPATH) $(CFLAGS) $<

.cpp.o:
	$(CC) -c $(INCPATH) $(CFLAGS) $<

install:
	mkdir -p ../release
	cp -af $(TEST_ProgramName) ../release
	cp -af $(TESTLIMIT_ProgramName) ../release

clean:
	rm -rf *.o $(TEST_ProgramName) $(SERVICE_ProgramName)
