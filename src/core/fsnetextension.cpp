#include "fsnetextension.h"
#include "fsnetextension_closeairsupport.h"
#include "fsnetextension_endurance.h"
#include "fsnetextension_intercept.h"

FsNetExtensionCollection::FsNetExtensionCollection()
{
	AddExtension<FsNetExtension_CloseAirSupport>();
	AddExtension<FsNetExtension_EnduranceMode>();
	AddExtension<FsNetExtension_InterceptMission>();
}

std::vector <std::shared_ptr <FsNetExtensionBase> >::iterator FsNetExtensionCollection::begin() noexcept
{
	return extensions.begin();
}

std::vector <std::shared_ptr <FsNetExtensionBase> >::iterator FsNetExtensionCollection::end() noexcept
{
	return extensions.end();
}

YSBOOL FsNetExtensionCollection::HasRunningExclusive() const
{
	for(auto &extension : extensions)
	{
		if(extension->IsRunning()==YSTRUE && extension->IsExclusive()==YSTRUE)
		{
			return YSTRUE;
		}
	}
	return YSFALSE;
}

template <class T>
enable_if_base_of <FsNetExtensionBase, T> FsNetExtensionCollection::AddExtension()
{
	extensions.push_back(std::make_shared<T>());
}

template <class T>
enable_if_base_of <FsNetExtensionBase, T> FsNetExtensionCollection::AddExtension(std::function <std::shared_ptr <T>(void)> generator)
{
	extensions.push_back(generator());
}

std::shared_ptr <FsNetExtensionBase> FsNetExtensionCollection::GetExtension(const char *extensionName)
{
	for(auto &extension : extensions)
	{
		if(0==strcmp(extensionName,extension->GetExtensionName()))
		{
			return extension;
		}
	}
	return nullptr;
}
