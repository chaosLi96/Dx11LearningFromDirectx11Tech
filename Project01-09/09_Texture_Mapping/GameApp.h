#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
#include "LightHelper.h"
#include "Geometry.h"


class GameApp : public D3DApp
{
public:

    struct VSConstantBuffer
    {
        DirectX::XMMATRIX world;
        DirectX::XMMATRIX view;
        DirectX::XMMATRIX proj;
        //没明白这个逆矩阵干啥的
        DirectX::XMMATRIX worldInvTranspose;
    };

    struct PSConstantBuffer
    {
        DirectionalLight dirLight[10];
        PointLight pointLight[10];
        SpotLight spotLight[10];
        Material material;
        int numDirLight;
        int numPointLight;
        int numSpotLight;
        float pad;
        DirectX::XMFLOAT4 eyePos;
    };

    enum class ShowMode
    {
        WoodCrate,
        FireAnim
    };

public:
    GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight);
    ~GameApp();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();
private:
    bool InitEffect();
    bool InitResources();

    bool ResetMesh(const Geometry::MeshData<VertexPosNormalTex>& meshData);

private:
    ComPtr<ID3D11InputLayout> m_pVertexLayout2D; // 3D顶点输入布局
    ComPtr<ID3D11InputLayout> m_pVertexLayout3D; // 3D顶点输入布局
    ComPtr<ID3D11Buffer>m_pVertexBuffer;   //顶点缓冲区
    ComPtr<ID3D11Buffer> m_pIndexBuffer;     //索引缓冲区
    ComPtr<ID3D11Buffer> m_pConstantBuffers[2]; //常量缓冲区
    UINT m_IndexCount;
    int m_CurrFrame;
    ShowMode m_CurrMode;

	ComPtr<ID3D11ShaderResourceView> m_pWoodCrate; //木材纹理
    std::vector<ComPtr<ID3D11ShaderResourceView>> m_pFireAnims;
    ComPtr<ID3D11SamplerState> m_pSamplerState;


	ComPtr<ID3D11VertexShader> m_pVertexShader3D; //顶点着色器
	ComPtr<ID3D11PixelShader> m_pPixelShader3D; // 像素着色器
    ComPtr<ID3D11VertexShader> m_pVertexShader2D; //顶点着色器
    ComPtr<ID3D11PixelShader> m_pPixelShader2D; //像素着色器


    VSConstantBuffer m_VSConstantBuffer;
    PSConstantBuffer m_PSConstantBuffer;

};


#endif