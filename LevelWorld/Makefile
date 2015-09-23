LevelWorld: *.cpp *.h LevelWorld.rdef
	gcc -g *.cpp -I ../DynaMate/headers/ -o LevelWorld -lbe
	rc -o $@ LevelWorld.rdef
	xres -o $@ $@.rsrc
