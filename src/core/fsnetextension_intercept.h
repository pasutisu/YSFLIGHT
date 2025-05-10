#ifndef FSNETEXTENSION_INTERCEPT_IS_INCLUDED
#define FSNETEXTENSION_INTERCEPT_IS_INCLUDED
/* { */

#include "fsnetextension.h"
#include "fssiminfo.h"

class FsNetExtension_InterceptMission : public FsNetExtensionBase
{
public:
	const double initRemainTime;

	double remainTime;
	FsInterceptMissionInfo info;

	FsNetExtension_InterceptMission();

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
