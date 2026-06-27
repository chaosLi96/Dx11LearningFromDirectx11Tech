#ifndef GAMEAPP_H
#define GAMEAPP_H

#include "d3dApp.h"
class GameApp : public D3DApp
{
public:
    GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight);
    ~GameApp();

    struct VertexPosColor
    {
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT4 color;
        static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
    };

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();

private:
    bool InitEffect();
    bool InitResource();

private:
    ComPtr<ID3D11InputLayout>m_pVertexLayout;
    ComPtr<ID3D11Buffer>m_pVertexBuffer;
    ComPtr<ID3D11VertexShader>m_pVertexShader;
    ComPtr<ID3D11PixelShader>m_pPixelShader;
};


#endif
