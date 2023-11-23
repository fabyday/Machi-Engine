#include "RootSignature.h"

#include "dxhelper.h"
using namespace Machi::NativeGraphics;
void RootSignature::init(std::shared_ptr<Device> device, RootParameter& root_params) {
    
    D3D12_FEATURE_DATA_ROOT_SIGNATURE featureData = {};

    // This is the highest version the sample supports. If CheckFeatureSupport succeeds, the HighestVersion returned will not be greater than this.
    //featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
    featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;

    if (FAILED(device->check_feature_support(D3D12_FEATURE_ROOT_SIGNATURE, &featureData, sizeof(featureData))))
    {
        featureData.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_0;
    }
    
    D3D12_ROOT_SIGNATURE_FLAGS rootSignatureFlags =
        D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
        D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;

    CD3DX12_ROOT_SIGNATURE_DESC rootsignature_desc;
    //rootsignature_desc.Init(root_params.size(), root_params.Get(), 0, nullptr, rootSignatureFlags);
    rootsignature_desc.Init(root_params.size(), root_params.Get(), 0, nullptr, rootSignatureFlags);

    ComPtr<ID3DBlob> signature;
    ComPtr<ID3DBlob> error;
    try {
    ThrowIfFailed(D3D12SerializeRootSignature(&rootsignature_desc, featureData.HighestVersion, &signature, &error));

    }
    catch (const HrException& e) {
        std::string t = HrToString(e.Error());
        MSTRING str(t.begin(), t.end());
        Logger::MLogger::get_instance().debug(MACHI_DEFAULT_CONSOLE_LOGGER_NAME, str);

    }
    //ThrowIfFailed(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&m_rootsignature)));
    ThrowIfFailed(device->create_root_signature(0, signature->GetBufferPointer(), signature->GetBufferSize(), m_rootsignature));

}
