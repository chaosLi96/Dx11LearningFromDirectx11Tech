#include "d3dUtil.h"

namespace
{
    bool FileExists(const WCHAR* fileName)
    {
        if (!fileName)
        {
            return false;
        }

        DWORD fileAttributes = GetFileAttributesW(fileName);
        return fileAttributes != INVALID_FILE_ATTRIBUTES &&
            (fileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    }

    bool IsFileNewer(const WCHAR* newerFileName, const WCHAR* olderFileName)
    {
        if (!newerFileName || !olderFileName)
        {
            return false;
        }

        WIN32_FILE_ATTRIBUTE_DATA newerFileData = {};
        WIN32_FILE_ATTRIBUTE_DATA olderFileData = {};
        if (!GetFileAttributesExW(newerFileName, GetFileExInfoStandard, &newerFileData) ||
            !GetFileAttributesExW(olderFileName, GetFileExInfoStandard, &olderFileData))
        {
            return false;
        }

        return CompareFileTime(&newerFileData.ftLastWriteTime, &olderFileData.ftLastWriteTime) > 0;
    }
}

HRESULT CreateShaderFromFile(const WCHAR* csoFileNameInOut, const WCHAR* hlslFileName, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob** ppBlobOut)
{
    HRESULT hr = S_OK;

    bool shouldUseCachedShader = csoFileNameInOut && !IsFileNewer(hlslFileName, csoFileNameInOut);
#if defined(DEBUG) || defined(_DEBUG)
    shouldUseCachedShader = shouldUseCachedShader && !FileExists(hlslFileName);
#endif

    if (shouldUseCachedShader &&
        D3DReadFileToBlob(csoFileNameInOut, ppBlobOut) == S_OK)
    {
        return hr;
    }
    else
    {
        DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
        dwShaderFlags |= D3DCOMPILE_DEBUG;
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
        ID3DBlob* errorBlob = nullptr;
		hr = D3DCompileFromFile(hlslFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint, shaderModel,
			dwShaderFlags, 0, ppBlobOut, &errorBlob);

        if (FAILED(hr))
        {
			if (errorBlob != nullptr)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
			}
			SAFE_RELEASE(errorBlob);
			return hr;
        }

        if (csoFileNameInOut)
        {
            return D3DWriteBlobToFile(*ppBlobOut, csoFileNameInOut, TRUE);
        }

    }
    return hr;
}
