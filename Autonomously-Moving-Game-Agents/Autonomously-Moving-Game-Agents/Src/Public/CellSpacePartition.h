#include <iostream>

template<class entity>
struct Cell
{
	//all the entities inhabiting this cell
	std::list<entity> Members;

	//the cell's bounding box (it's inverted because the Windows' default coordinate system has a y-axis that increases as it descends
	InvertedAABBox2D BBox;

	Cell(Vector2D topleft, Vector2D botright) : BBox
};


class CellSpacePartition
{

};