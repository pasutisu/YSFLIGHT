#ifndef FSNETEXTENSION_IS_INCLUDED
#define FSNETEXTENSION_IS_INCLUDED
/* { */

#include <type_traits>
#include <vector>
#include <memory>
#include <functional>

#include <ysclass.h>

#include "fsnetwork.h"

template <class B, class I, class R = void>
using enable_if_base_of = typename std::enable_if <std::is_base_of <B, I>::value, R>::type;

class FsNetExtensionBase
{
public:
	virtual ~FsNetExtensionBase() {}

	virtual const char *GetExtensionName(void) const = 0;

	virtual YSBOOL IsExclusive(void) const {return YSFALSE;}
	virtual YSBOOL IsRunning(void) {return YSFALSE;}

	virtual void StartSimulation(FsSocketServer &server) {}
	virtual void EndSimulation(FsSocketServer &server) {}

	virtual void OnNetConsoleCommand(FsSocketServer &server,enum FSNET_CONSOLE_COMMAND command) {}
	virtual void OnSlashCommand(FsSocketServer &server,int clientId,const YsConstArrayMask <YsString> &argv) {}

	virtual void OnInterval(FsSocketServer &server,double passedTime) {}

	virtual YSRESULT OnChatMessage(FsSocketServer &server,int clientId,const char *msg) {return YSOK;}
};

class FsNetExtensionCollection
{
private:
	std::vector <std::shared_ptr <FsNetExtensionBase> > extensions;
public:
	FsNetExtensionCollection();

	std::vector <std::shared_ptr <FsNetExtensionBase> >::iterator begin() noexcept;
	std::vector <std::shared_ptr <FsNetExtensionBase> >::iterator end() noexcept;

	YSBOOL HasRunningExclusive() const;

	template <class T>
	enable_if_base_of <FsNetExtensionBase, T> AddExtension();
	template <class T>
	enable_if_base_of <FsNetExtensionBase, T> AddExtension(std::function <std::shared_ptr <T>(void)> generator);

	std::shared_ptr <FsNetExtensionBase> GetExtension(const char *extensionName);
};

/* } */
#endif
