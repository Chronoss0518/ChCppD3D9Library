
#include<Windows.h>
#include"../../../ChCppBaseLibrary/BaseIncluder/ChBase.h"
#include"../../BaseIncluder/ChD3D9I.h"

#include"ChLight9.h"

///////////////////////////////////////////////////////////////////////////////////////
//ChLight9メソッド
///////////////////////////////////////////////////////////////////////////////////////

ChLight9::ChLight9(LPDIRECT3DDEVICE9 _dv) 
{
	device = _dv;
	device->SetRenderState(D3DRS_LIGHTING, TRUE);

	//TypeSet(光源の種類)
	light.Type = D3DLIGHT_DIRECTIONAL;

	//DirectionSet(ライトの角度)
	light.Direction = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	//Position(lightの位置)
	{
		auto tmp = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		SetPos(&tmp);
	}

	//DiffuserSet(光源色)
	SetLightDif(1.0f, 1.0f, 1.0f, 1.0f);

	//SpecularSet(光沢効果)
	SetLightSpe(FALSE, 1.0f, 1.0f, 1.0f);

	
	//AmbientSet(環境光効果)
	SetLightAmb(FALSE, 1.0f, 1.0f, 1.0f);

	//RegisterLight
	device->SetLight(0, &light);
	device->LightEnable(0, TRUE);

	
	//RangeSet(ライトの範囲)
	light.Range = 25.0f;

	//AttenuatSet(長距離へ行った時のライトの強さ計算)
	light.Attenuation0 = 0.0f;
	light.Attenuation1 = 0.2f;
	light.Attenuation2 = 0.0f;

	
	//PositionSet(Point,SpotLight時のライトの位置)
	light.Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}

void ChLight9::SetLight(bool _flg)
{
	device->LightEnable(0, _flg);
}

void ChLight9::SetDir(const ChVec3_9& _dir)
{
	ChVec3_9 tmpVec = _dir;
	tmpVec.Normalize();
	light.Direction = tmpVec;
	RegisterLight();
}

void ChLight9::SetPos(const D3DXVECTOR3 *_pos)
{
	light.Position = *_pos;
}

void ChLight9::SetLightDif(const float _a, const float _r, const float _g, const float _b)
{
	light.Diffuse.a = _a;
	light.Diffuse.r = _r;
	light.Diffuse.g = _g;
	light.Diffuse.b = _b;
	RegisterLight();
}

void ChLight9::SetLightSpe(bool _SpeFlg, const float _r, const float _g, const float _b)
{
	device->SetRenderState(D3DRS_SPECULARENABLE, _SpeFlg);
	light.Specular.r = _r;
	light.Specular.g = _g;
	light.Specular.b = _b;
	RegisterLight();
}

void ChLight9::SetLightAmb(bool _AmbFlg, const float _r, const float _g, const float _b)
{
	device->SetRenderState(D3DRS_AMBIENT, _AmbFlg);
	light.Ambient.r = _r;
	light.Ambient.g = _g;
	light.Ambient.b = _b;
	RegisterLight();
}

void ChLight9::RegisterLight()
{
	device->SetLight(0, &light);
}
