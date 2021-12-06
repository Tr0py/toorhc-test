all:
	cd lib; make
	cd app; make
	cd app; make run
	cd app; make ivrun

clean:
	cd lib; make clean
	cd app; make clean
