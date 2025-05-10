#ifndef FSNETEXTENSION_ENDURANCE_IS_INCLUDED
#define FSNETEXTENSION_ENDURANCE_IS_INCLUDED
/* { */

#include "fsnetextension.h"

class FsNetExtension_EnduranceMode : public FsNetExtensionBase
{
public:
	const double initRemainTime;
	const double initGLimit;

	double remainTime;
	double gLimit;
	int nEnemyMax;
	YSBOOL allowAAM;
	YSBOOL jet;
	YSBOOL ww2;

	FsNetExtension_EnduranceMode();

	virtual const char *GetExtensionName(void) const;

	virtual YSBOOL IsExclusive(void) const;
	virtual YSBOOL IsRunning(void);

	virtual void StartSimulation(FsSocketServer &server);

	virtual void OnNetConsoleCommand(FsSocketServer &server,enum FSNET_CONSOLE_COMMAND command);
	virtual void OnSlashCommand(FsSocketServer &server,int clientId,const YsConstArrayMask <YsString> &argv);

	virtual void OnInterval(FsSocketServer &server,double passedTime);
};

/* } */
#endif
