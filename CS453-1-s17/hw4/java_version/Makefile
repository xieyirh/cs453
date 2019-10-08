.SUFFIXES: .class .java
.java.class:
	javac $(JFLAGS) $<

JFLAGS=

all:FileAccess.class FileAccessMonitor.class TestFileAccess.class Timeout.class

clean:
	rm -f *.class

