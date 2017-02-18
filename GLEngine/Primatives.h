#pragma once

class Mesh;
namespace Primatives
{
	Mesh* Plane(const unsigned int _rows, const unsigned int _cols);
	Mesh* Sphere(const float _radius, const unsigned int _rings, const unsigned int _sectors);
}
