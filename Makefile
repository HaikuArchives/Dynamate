DEST_DIR ?= /boot/system/non-packaged/apps/DynaMate

ALL: LevelWorld/LevelWorld DynaMate/DynaMate

install: DynaMate/DynaMate LevelWorld
	cp Dynamate/docs DynaMate/levels-* DynaMate/DynaMate LevelWorld/LevelWorld $(DEST_DIR)

LevelWorld/LevelWorld: LevelWorld/*.cpp LevelWorld/*.h LevelWorld/LevelWorld.rdef
	gcc -g LevelWorld/*.cpp -I ../DynaMate/headers/ -o $@ -lbe
	rc -o $@ LevelWorld/LevelWorld.rdef
	xres -o $@ $@.rsrc

DynaMate/DynaMate: DynaMate/source/*.cpp DynaMate/headers/*.h DynaMate/DynaMate.rdef
	gcc source/*.cpp -I headers/ -o $@ -lbe -lmedia
	rc -o $@ DynaMate.rdef
	xres -o $@ $@.rsrc
