#ifndef GLOB
#define GLOB

/// /// /// /// SOUND /// /// /// ///
#include <MediaDefs.h>
#include <Sound.h>
#include <SoundPlayer.h>

struct SoundStuff {
	BSoundPlayer sp;
	BSound *moveblip,*stopblip,*explblip;
};

enum {	dmSTOPPED,
		dmOK,
		dmSEARCHING,
		dmEXPL,
		dmDEATH
		};

const uint32 LEVELCOMPLETE 	=	'lvcp';
const uint32 LEVELABANDONED	=	'lvab';

#endif