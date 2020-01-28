
#include "AwesomeEngineApp.h"
#include <iostream>
#include <sstream>
#include <direct.h>
#include <string.h>
#include <windowsx.h>
#include <tchar.h>

#include "Common/d3dUtil.h"
#include "Events/EventManager.h"


extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include <LuaBridge.h>

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace luabridge;
using namespace AwesomeEngine;

const int gNumFrameResources = 3;

AwesomeEngineApp::AwesomeEngineApp(HINSTANCE hInstance)
	: D3DApp( hInstance )
{
}

AwesomeEngineApp::~AwesomeEngineApp()
{
}

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void displayProcessorArchitecture(SYSTEM_INFO &stInfo)
{
	std::cout << "CPU : ";
	switch (stInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL: //0-(x86)
		//printf("Processor Architecture: Intel x86\n");
		std::cout << "Intel x86"; 
		break;
	case PROCESSOR_ARCHITECTURE_ARM: //5-ARM processor type
		std::cout << L"ARM";
		break;
	default:
		//printf("Unknown processor architecture\n");
		std::cout << "Unknown Architecture";
	}

	std::cout << std::endl;
}

bool CheckMemory(const DWORDLONG physicalRAMNeededInMB, const DWORDLONG virtualRAMNeededInMB)
{
	MEMORYSTATUSEX status = { sizeof status };
	GlobalMemoryStatusEx(&status);


	status.ullTotalPhys = status.ullTotalPhys / (1024 * 1024 * 1024);		// GB
	status.ullAvailPhys = status.ullAvailPhys / (1024 * 1024);				// MB
	status.ullTotalVirtual = status.ullTotalVirtual / (1024 * 1024 * 1024);	// GB
	status.ullAvailVirtual = status.ullAvailVirtual / (1024 * 1024);		// MB

	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile / (1024 * 1024);	// MB
	DWORDLONG availVirtualMem = memInfo.ullAvailPageFile / (1024 * 1024);	// MB

	std::cout << "Total physics physics = " << status.ullTotalPhys << " GB" << std::endl;
	std::cout << "Current Physical Memory Available: " << status.ullAvailPhys / 1024 << "GB" << std::endl;
	std::cout << "Total virtual memory = " << totalVirtualMem / 1024 << " GB" << std::endl;
	std::cout << "Current Virtual Memory Available: " << availVirtualMem / 1024 << "GB" << std::endl;

	if (status.ullAvailPhys < physicalRAMNeededInMB)
	{
		std::ostringstream msg;
		msg << "CheckMemory Failure: " << physicalRAMNeededInMB << "MB Required" << std::endl << "Memory Available: " << status.ullAvailPhys << "MB" << std::endl;
		MessageBoxA(NULL, msg.str().c_str(), "Not Enough Memory", 0);
		return false;
	}

	if (availVirtualMem < virtualRAMNeededInMB)
	{
		std::ostringstream msg;
		msg << "CheckMemory Failure: " << virtualRAMNeededInMB << "MB Required" << std::endl << "Memory Available: " << status.ullAvailVirtual << "MB" << std::endl;

		MessageBoxA(NULL, msg.str().c_str(), "Not Enough Virtual Memory", NULL);
		return false;
	}
	
	return true;

}

LPWSTR GetRegistry(LPCWSTR StringName)
{
	DWORD dwType = REG_SZ;
	HKEY hKey = 0;
	TCHAR value[1024];
	DWORD value_length = 1024;
	LPCWSTR subkey = L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
	RegOpenKey(HKEY_LOCAL_MACHINE, subkey, &hKey);
	RegQueryValueEx(hKey, StringName, NULL, &dwType, (LPBYTE)&value, &value_length);
	std::wcout << "CPU Type : " << value << std::endl;
	return  value;
}

DWORD AwesomeEngineApp::ReadCPUSpeed()
{
	DWORD dwMHz = 0;
	HKEY hKey;
	//open key where proc speed is hidden
	std::string myString = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";

	std::wstring stemp = s2ws(myString);
	LPCWSTR result = stemp.c_str();

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		result,
		0,
		KEY_READ,
		&hKey);

	if (lError == ERROR_SUCCESS)
	{
		DWORD dwLen = 4;
		if (RegQueryValueEx(hKey, L"~MHz", NULL, NULL, (LPBYTE)&dwMHz, &dwLen) != ERROR_SUCCESS)
		{
			return 0;
		}
		RegCloseKey(hKey);
	}

	GetRegistry(L"ProcessorNameString");
	
	return dwMHz;
}


bool AwesomeEngineApp::Init(unsigned long diskRequiredInMB, unsigned long memoryRequiredInMB, unsigned long virtualMemoryRequriedInMB, int cpuSpeedRequiredInMHz)
{
	if (!IsOnlyInstance(L"test"))
	{
		MessageBox(NULL, L"the game has multiple instances", L"ERROR", 0);
		return false;
	}

	// Ask for 100 GB
	if (!CheckStorage(diskRequiredInMB))
	{
		return false;
	}

	// First variable passed in is total RAM needed (in GB), second is total virtual RAM needed (also in GB)
	if (!CheckMemory(memoryRequiredInMB, virtualMemoryRequriedInMB))
	{
		return false;
	}

	//Checks if system has minimum of 500Mhz CPU Speed.
	DWORD cpuSpeed = ReadCPUSpeed();

	if (cpuSpeed < cpuSpeedRequiredInMHz)
	{
		std::ostringstream msg;
		msg << "Check CPU failed, below required minimum of: "<< cpuSpeedRequiredInMHz << "Mhz" << std::endl << "Actual: " << cpuSpeed << "Mhz" << std::endl;
		MessageBoxA(NULL, msg.str().c_str(), "CPU Requirements Check!", 0); 
	}
	else {
		std::cout << "Check CPU Speed Okay" << std::endl << "CPU Speed: " << cpuSpeed << "Mhz" << std::endl;
	}

	SYSTEM_INFO stInfo;
	GetSystemInfo(&stInfo);
	//displayProcessorArchitecture(stInfo);

	if (!D3DApp::Initialize())
		return false;

	// Reset the command list to prep for initialization commands.
	ThrowIfFailed(mCommandList->Reset(mDirectCmdListAlloc.Get(), nullptr));

	// Get the increment size of a descriptor in this heap type.  This is hardware specific, 
	// so we have to query this information.
	mCbvSrvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	LoadTextures();

	BuildRootSignature();
	BuildDescriptorHeaps();
	BuildShadersAndInputLayout();
	BuildMaterials();
	BuildRenderItems();
	BuildFrameResources();
	BuildPSOs();

	// Execute the initialization commands.
	ThrowIfFailed(mCommandList->Close());
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until initialization is complete.
	FlushCommandQueue();

	// event handler
	EventListenerDelegate mouseMoveListener(this, &AwesomeEngineApp::EventMouseMoved);
	EventManager::GetInstance().VAddListener(mouseMoveListener, EnumEventType::Event_Mouse_Moved);

	EventListenerDelegate mouseClickListener(this, &AwesomeEngineApp::EventMouseClicked);
	EventManager::GetInstance().VAddListener(mouseClickListener, EnumEventType::Event_Mouse_Clicked);

	EventListenerDelegate keyDownListener(this, &AwesomeEngineApp::EventKeyPressed);
	EventManager::GetInstance().VAddListener(keyDownListener, EnumEventType::Event_CharKey_Pressed);


	return true;
}

void AwesomeEngineApp::Update(const GameTimer& gt)
{
	//OnKeyboardInput(gt);
	//UpdateCamera(gt);

	// Cycle through the circular frame resource array.
	mCurrFrameResourceIndex = (mCurrFrameResourceIndex + 1) % gNumFrameResources;
	mCurrFrameResource = mFrameResources[mCurrFrameResourceIndex].get();

	// Has the GPU finished processing the commands of the current frame resource?
	// If not, wait until the GPU has completed commands up to this fence point.
	if (mCurrFrameResource->Fence != 0 && mFence->GetCompletedValue() < mCurrFrameResource->Fence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, nullptr, false, EVENT_ALL_ACCESS);
		ThrowIfFailed(mFence->SetEventOnCompletion(mCurrFrameResource->Fence, eventHandle));
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}

	UpdateObjectCBs(gt);
	UpdateMaterialCBs(gt);
	//UpdateMainPassCB(gt);
}

void AwesomeEngineApp::Draw(const GameTimer& gt)
{
	auto cmdListAlloc = mCurrFrameResource->CmdListAlloc;

	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	ThrowIfFailed(cmdListAlloc->Reset());

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	ThrowIfFailed(mCommandList->Reset(cmdListAlloc.Get(), mOpaquePSO.Get()));

	mCommandList->RSSetViewports(1, &mScreenViewport);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	// Indicate a state transition on the resource usage.
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	// Clear the back buffer and depth buffer.
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), DirectX::Colors::LightSteelBlue, 0, nullptr);
	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

	ID3D12DescriptorHeap* descriptorHeaps[] = { mSrvDescriptorHeap.Get() };
	mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	mCommandList->SetGraphicsRootSignature(mRootSignature.Get());

	auto passCB = mCurrFrameResource->PassCB->Resource();
	mCommandList->SetGraphicsRootConstantBufferView(2, passCB->GetGPUVirtualAddress());

	DrawRenderItems(mCommandList.Get(), mOpaqueRitems);

	// Indicate a state transition on the resource usage.
	mCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	// Done recording commands.
	ThrowIfFailed(mCommandList->Close());

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { mCommandList.Get() };
	mCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Swap the back and front buffers
	ThrowIfFailed(mSwapChain->Present(0, 0));
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	// Advance the fence value to mark commands up to this fence point.
	mCurrFrameResource->Fence = ++mCurrentFence;

	// Add an instruction to the command queue to set a new fence point. 
	// Because we are on the GPU timeline, the new fence point won't be 
	// set until the GPU finishes processing all the commands prior to this Signal().
	mCommandQueue->Signal(mFence.Get(), mCurrentFence);
}

void AwesomeEngineApp::DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems)
{
	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = mCurrFrameResource->ObjectCB->Resource();
	auto matCB = mCurrFrameResource->MaterialCB->Resource();

	// For each render item...
	for (size_t i = 0; i < ritems.size(); ++i)
	{
		auto ri = ritems[i];

		cmdList->IASetVertexBuffers(0, 1, &ri->Geo->VertexBufferView());
		cmdList->IASetIndexBuffer(&ri->Geo->IndexBufferView());
		cmdList->IASetPrimitiveTopology(ri->PrimitiveType);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(ri->Mat->DiffuseSrvHeapIndex, mCbvSrvDescriptorSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + ri->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + ri->Mat->MatCBIndex * matCBByteSize;

		cmdList->SetGraphicsRootDescriptorTable(0, tex);
		cmdList->SetGraphicsRootConstantBufferView(1, objCBAddress);
		cmdList->SetGraphicsRootConstantBufferView(3, matCBAddress);

		cmdList->DrawIndexedInstanced(ri->IndexCount, 1, ri->StartIndexLocation, ri->BaseVertexLocation, 0);
	}
}

bool AwesomeEngineApp::IsOnlyInstance(LPCTSTR gameTitle)
{
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(NULL, gameTitle);
		if (hWnd)
		{
			// An instance of your game is already running. 
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;
}

bool AwesomeEngineApp::CheckStorage(const DWORDLONG diskSpaceNeededInMB)
{
	// Check for enough free disk space on the current disk. 
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const bytes_per_cluster = diskfree.sectors_per_cluster * diskfree.bytes_per_sector;
	unsigned __int64 const neededClusters = (diskSpaceNeededInMB / bytes_per_cluster) * 1024 * 1024;

	unsigned __int64 const avaliableSpaces = (unsigned __int64)
		((double)diskfree.avail_clusters / 1024.0 / 1024.0 * (double)bytes_per_cluster);

	if (diskfree.avail_clusters < neededClusters)
	{
		std::ostringstream msg;
		msg << "CheckStorage Failure: Not enough physical storage. only has " << avaliableSpaces << "MB in the disk" << std::endl;
		MessageBoxA(NULL, msg.str().c_str(), "ERROR", 0);
		return false;
	}
	else
	{
		std::cout << "CheckStorage Success: " << (avaliableSpaces / 1024) << "GB in the disk available" << std::endl;
		return true;
	}
}


void AwesomeEngineApp::LoadTextures()
{
	
	auto skullTex = std::make_unique<Texture>();
	skullTex->Name = "logoTex";
	skullTex->Filename = L"../Assets/whatever_logo.png";
	//ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(md3dDevice.Get(),
	//	mCommandList.Get(), skullTex->Filename.c_str(),
	//	skullTex->Resource, skullTex->UploadHeap));
	ThrowIfFailed(
		DirectX::LoadFromWICFile(m_d3dDevice.Get(), resourceUpload, L"cat.png",
			m_texture.ReleaseAndGetAddressOf()));

	mTextures[skullTex->Name] = std::move(skullTex);
}

void AwesomeEngineApp::BuildRootSignature()
{
	CD3DX12_DESCRIPTOR_RANGE texTable;
	texTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);

	// Root parameter can be a table, root descriptor or root constants.
	CD3DX12_ROOT_PARAMETER slotRootParameter[4];

	// Perfomance TIP: Order from most frequent to least frequent.
	slotRootParameter[0].InitAsDescriptorTable(1, &texTable, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[1].InitAsConstantBufferView(0);
	slotRootParameter[2].InitAsConstantBufferView(1);
	slotRootParameter[3].InitAsConstantBufferView(2);

	auto staticSamplers = GetStaticSamplers();

	// A root signature is an array of root parameters.
	//The Init function of the CD3DX12_ROOT_SIGNATURE_DESC class has two parameters that allow you to
		//define an array of so - called static samplers your application can use.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(4, slotRootParameter,
		(UINT)staticSamplers.size(), staticSamplers.data(),  //6 samplers!
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	ComPtr<ID3DBlob> serializedRootSig = nullptr;
	ComPtr<ID3DBlob> errorBlob = nullptr;
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		serializedRootSig.GetAddressOf(), errorBlob.GetAddressOf());

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	ThrowIfFailed(hr);

	ThrowIfFailed(md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(mRootSignature.GetAddressOf())));
}

//Once a texture resource is created, we need to create an SRV descriptor to it which we
//can set to a root signature parameter slot for use by the shader programs.
void AwesomeEngineApp::BuildDescriptorHeaps()
{
	//
	// Create the SRV heap.
	//
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1;
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	ThrowIfFailed(md3dDevice->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&mSrvDescriptorHeap)));

	//
	// Fill out the heap with actual descriptors.
	//
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(mSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart());

	auto logoTex = mTextures["logoTex"]->Resource;

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};

	//This mapping enables the shader resource view (SRV) to choose how memory gets routed to the 4 return components in a shader after a memory fetch.
	//When a texture is sampled in a shader, it will return a vector of the texture data at the specified texture coordinates.
	//This field provides a way to reorder the vector components returned when sampling the texture.
	//D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING  will not reorder the components and just return the data in the order it is stored in the texture resource.
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

	srvDesc.Format = logoTex->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	//The number of mipmap levels to view, starting at MostDetailedMip.This field, along with MostDetailedMip allows us to
	//specify a subrange of mipmap levels to view.You can specify - 1 to indicate to view
	//all mipmap levels from MostDetailedMip down to the last mipmap level.

	srvDesc.Texture2D.MipLevels = logoTex->GetDesc().MipLevels;

	//Specifies the minimum mipmap level that can be accessed. 0.0 means all the mipmap levels can be accessed.
	//Specifying 3.0 means mipmap levels 3.0 to MipCount - 1 can be accessed.
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;

	md3dDevice->CreateShaderResourceView(logoTex.Get(), &srvDesc, hDescriptor);
}

void AwesomeEngineApp::BuildShadersAndInputLayout()
{
	mShaders["standardVS"] = d3dUtil::CompileShader(L"Shaders\\VS_Anisotropic.hlsl", nullptr, "VS", "vs_5_1");
	mShaders["opaquePS"] = d3dUtil::CompileShader(L"Shaders\\PS_Anisotropic.hlsl", nullptr, "PS", "ps_5_1");

	mInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};
}


void AwesomeEngineApp::BuildPSOs()
{
	D3D12_GRAPHICS_PIPELINE_STATE_DESC opaquePsoDesc;

	//
	// PSO for opaque objects.
	//
	ZeroMemory(&opaquePsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	opaquePsoDesc.InputLayout = { mInputLayout.data(), (UINT)mInputLayout.size() };
	opaquePsoDesc.pRootSignature = mRootSignature.Get();
	opaquePsoDesc.VS =
	{
		reinterpret_cast<BYTE*>(mShaders["standardVS"]->GetBufferPointer()),
		mShaders["standardVS"]->GetBufferSize()
	};
	opaquePsoDesc.PS =
	{
		reinterpret_cast<BYTE*>(mShaders["opaquePS"]->GetBufferPointer()),
		mShaders["opaquePS"]->GetBufferSize()
	};
	opaquePsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	opaquePsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	opaquePsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	opaquePsoDesc.SampleMask = UINT_MAX;
	opaquePsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	opaquePsoDesc.NumRenderTargets = 1;
	opaquePsoDesc.RTVFormats[0] = mBackBufferFormat;
	opaquePsoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	opaquePsoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	opaquePsoDesc.DSVFormat = mDepthStencilFormat;
	ThrowIfFailed(md3dDevice->CreateGraphicsPipelineState(&opaquePsoDesc, IID_PPV_ARGS(&mOpaquePSO)));
}

void AwesomeEngineApp::BuildFrameResources()
{
	for (int i = 0; i < gNumFrameResources; ++i)
	{
		mFrameResources.push_back(std::make_unique<FrameResource>(md3dDevice.Get(),
			1, (UINT)mAllRitems.size(), (UINT)mMaterials.size()));
	}
}

void AwesomeEngineApp::BuildMaterials()
{
	auto skullMat = std::make_unique<Material>();
	skullMat->Name = "skullMat";
	skullMat->MatCBIndex = 0;
	skullMat->DiffuseSrvHeapIndex = 0;
	skullMat->DiffuseAlbedo = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	skullMat->FresnelR0 = XMFLOAT3(0.05f, 0.05f, 0.05f);
	skullMat->Roughness = 0.5f;
	mMaterials["skullMat"] = std::move(skullMat);
}

void AwesomeEngineApp::BuildRenderItems()
{
	auto skullRitem = std::make_unique<RenderItem>();
	skullRitem->ObjCBIndex = 0;
	skullRitem->Mat = mMaterials["skullMat"].get();
	skullRitem->Geo = mGeometries["skullGeo"].get();
	skullRitem->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	skullRitem->IndexCount = skullRitem->Geo->DrawArgs["skull"].IndexCount;
	skullRitem->StartIndexLocation = skullRitem->Geo->DrawArgs["skull"].StartIndexLocation;
	skullRitem->BaseVertexLocation = skullRitem->Geo->DrawArgs["skull"].BaseVertexLocation;
	mAllRitems.push_back(std::move(skullRitem));

	// All the render items are opaque.
	for (auto& e : mAllRitems)
		mOpaqueRitems.push_back(e.get());
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 7> AwesomeEngineApp::GetStaticSamplers()
{
	// Applications usually only need a handful of samplers.  So just define them all up front
	// and keep them available as part of the root signature.  

	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC mirror(
		6, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_MIRROR,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_MIRROR,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_MIRROR); // addressW

	return {
		pointWrap, pointClamp,
		linearWrap, linearClamp,
		anisotropicWrap, anisotropicClamp, mirror };
}




// Event Listener

void AwesomeEngineApp::EventMouseMoved(EventParam param)
{
	//std::cout << "Mouse moved x = " << param.param1 << " " << param.param2 << std::endl;
	//swprintf(&eventType[0], _T("Mouse x : %d, y : %d             "), param.param1, param.param2);
}

void AwesomeEngineApp::EventMouseClicked(const EventParam param)
{
	//std::cout << "Mouse clicked x = " << param.param1 << " " << param.param2 << std::endl;
	//if( param.param1 == 0 )
	//	swprintf(&eventType[0], _T("Left Button pressed           "));
	//else if (param.param1 == 1)
	//	swprintf(&eventType[0], _T("Right Button pressed          "));
}

void AwesomeEngineApp::EventKeyPressed(const EventParam param)
{
	//std::cout << "Mouse clicked x = " << param.param1 << " " << param.param2 << std::endl;
	//if (param.param1 == 0)
	//	swprintf(&eventType[0], _T("%c key down                   "), (char)param.param2);
	//else if (param.param1 == 1)
	//	swprintf(&eventType[0], _T("%c key up                     "), (char)param.param2);
}
//


void AwesomeEngineApp::UpdateObjectCBs(const GameTimer& gt)
{
	auto currObjectCB = mCurrFrameResource->ObjectCB.get();
	for (auto& e : mAllRitems)
	{
		// Only update the cbuffer data if the constants have changed.  
		// This needs to be tracked per frame resource.
		if (e->NumFramesDirty > 0)
		{
			XMMATRIX world = XMLoadFloat4x4(&e->World);
			XMMATRIX texTransform = XMLoadFloat4x4(&e->TexTransform);

			ObjectConstants objConstants;
			XMStoreFloat4x4(&objConstants.World, XMMatrixTranspose(world));
			XMStoreFloat4x4(&objConstants.TexTransform, XMMatrixTranspose(texTransform));

			currObjectCB->CopyData(e->ObjCBIndex, objConstants);

			// Next FrameResource need to be updated too.
			e->NumFramesDirty--;
		}
	}
}

void AwesomeEngineApp::UpdateMaterialCBs(const GameTimer& gt)
{
	auto currMaterialCB = mCurrFrameResource->MaterialCB.get();
	for (auto& e : mMaterials)
	{
		// Only update the cbuffer data if the constants have changed.  If the cbuffer
		// data changes, it needs to be updated for each FrameResource.
		Material* mat = e.second.get();
		if (mat->NumFramesDirty > 0)
		{
			XMMATRIX matTransform = XMLoadFloat4x4(&mat->MatTransform);

			MaterialConstants matConstants;
			matConstants.DiffuseAlbedo = mat->DiffuseAlbedo;
			matConstants.FresnelR0 = mat->FresnelR0;
			matConstants.Roughness = mat->Roughness;
			XMStoreFloat4x4(&matConstants.MatTransform, XMMatrixTranspose(matTransform));

			currMaterialCB->CopyData(mat->MatCBIndex, matConstants);

			// Next FrameResource need to be updated too.
			mat->NumFramesDirty--;
		}
	}
}

void AwesomeEngineApp::UpdateMainPassCB(const GameTimer& gt)
{
	//XMMATRIX view = XMLoadFloat4x4(&mView);
	//XMMATRIX proj = XMLoadFloat4x4(&mProj);

	//XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	//XMMATRIX invView = XMMatrixInverse(&XMMatrixDeterminant(view), view);
	//XMMATRIX invProj = XMMatrixInverse(&XMMatrixDeterminant(proj), proj);
	//XMMATRIX invViewProj = XMMatrixInverse(&XMMatrixDeterminant(viewProj), viewProj);

	//XMStoreFloat4x4(&mMainPassCB.View, XMMatrixTranspose(view));
	//XMStoreFloat4x4(&mMainPassCB.InvView, XMMatrixTranspose(invView));
	//XMStoreFloat4x4(&mMainPassCB.Proj, XMMatrixTranspose(proj));
	//XMStoreFloat4x4(&mMainPassCB.InvProj, XMMatrixTranspose(invProj));
	//XMStoreFloat4x4(&mMainPassCB.ViewProj, XMMatrixTranspose(viewProj));
	//XMStoreFloat4x4(&mMainPassCB.InvViewProj, XMMatrixTranspose(invViewProj));
	//mMainPassCB.EyePosW = mEyePos;
	//mMainPassCB.RenderTargetSize = XMFLOAT2((float)mClientWidth, (float)mClientHeight);
	//mMainPassCB.InvRenderTargetSize = XMFLOAT2(1.0f / mClientWidth, 1.0f / mClientHeight);
	//mMainPassCB.NearZ = 1.0f;
	//mMainPassCB.FarZ = 1000.0f;
	//mMainPassCB.TotalTime = gt.TotalTime();
	//mMainPassCB.DeltaTime = gt.DeltaTime();
	//mMainPassCB.AmbientLight = { 0.25f, 0.25f, 0.35f, 1.0f };
	//mMainPassCB.Lights[0].Direction = { 0.57735f, -0.57735f, 0.57735f };
	//mMainPassCB.Lights[0].Strength = { 0.6f, 0.6f, 0.6f };
	//mMainPassCB.Lights[1].Direction = { -0.57735f, -0.57735f, 0.57735f };
	//mMainPassCB.Lights[1].Strength = { 0.3f, 0.3f, 0.3f };
	//mMainPassCB.Lights[2].Direction = { 0.0f, -0.707f, -0.707f };
	//mMainPassCB.Lights[2].Strength = { 0.15f, 0.15f, 0.15f };

	//auto currPassCB = mCurrFrameResource->PassCB.get();
	//currPassCB->CopyData(0, mMainPassCB);
}