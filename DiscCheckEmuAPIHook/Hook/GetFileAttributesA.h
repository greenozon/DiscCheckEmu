/*
	Copyright 2024 Luca D'Amico

	This file is part of DiscCheckEmu.

	DiscCheckEmu is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	DiscCheckEmu is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with DiscCheckEmu.  If not, see <http://www.gnu.org/licenses/>
*/

#pragma once

#include <Windows.h>
#include "..\ApiHook.h"
#include "..\Util\StringUtils.h"

static DWORD(WINAPI* OGGetFileAttributesA)(
	LPCSTR lpFileName) = GetFileAttributesA;

DWORD WINAPI HookedGetFileAttributesA(LPCSTR lpFileName)
{
#ifndef NDEBUG
	std::cout << "---> GetFileAttributesA(" << (lpFileName != nullptr ? lpFileName : "NULL") << ")" << std::endl;
#endif

	for (dce::GetFileAttributesAConfig& conf : apiConfig.getFileAttributesAConfigs)
	{
		if (string_utils::areEqualIgnoreCase(lpFileName, conf.lpFileName))
		{
#ifndef NDEBUG
			std::cout << "<--- GetFileAttributesA(" << (lpFileName != nullptr ? lpFileName : "NULL") << ")" << std::endl;
#endif
			return conf.returnValue;
		}
	}

	auto it = apiConfig.fileRedirections.find(string_utils::toLowercase(lpFileName));
	if (it != apiConfig.fileRedirections.end())
	{
		lpFileName = it->second.c_str();
	}

#ifndef NDEBUG
	std::cout << "<--- GetFileAttributesA(" << lpFileName << ")" << std::endl;
#endif

	return OGGetFileAttributesA(lpFileName);
}