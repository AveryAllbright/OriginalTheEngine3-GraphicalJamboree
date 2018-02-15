#include "Material.h"

//I exist now!
//I currently do nothing!

Material::Material(SimpleVertexShader * a_Vert, SimplePixelShader * a_Pix)
{
	vertexShader = a_Vert;
	pixelShader = a_Pix;
}

Material::~Material()
{
}

SimpleVertexShader * Material::GetVertShader()
{
	return vertexShader;
}

SimplePixelShader * Material::GetPixelShader()
{
	return pixelShader;
}
