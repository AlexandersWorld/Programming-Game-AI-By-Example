#include <iostream>

template<class entity>
struct Cell
{
	//all the entities inhabiting this cell
	std::list<entity> Members;

	//the cell's bounding box (it's inverted because the Windows' default coordinate system has a y-axis that increases as it descends
	InvertedAABBox2D BBox;

	Cell(Vector2D topleft, Vector2D botright) : BBox(InvertedAABBox2D(topleft, botright))
};


template <class entity>
class CellSpacePartition
{
private:
	//the required number of cells in the space
	std::vector<Cell<entity> > m_Cells;
	//this is used to store any valid neighbors when an agent searches
	//its neighboring space
	std::vector<entity> m_Neighbors;
	//this iterator will be used by the methods next and begin to traverse
	//through the above vector of neighbors
	std::vector<entity>::iterator m_curNeighbor;
	//the width and height of the world space the entities inhabit
	double m_dSpaceWidth;
	double m_dSpaceHeight;
	//the number of cells the space is going to be divided into
	int m_iNumCellsX;
	int m_iNumCellsY;
	double m_dCellSizeX;
	double m_dCellSizeY;
	//given a position in the game space, this method determines the
	//relevant cell's index
	inline int PositionToIndex(const Vector2D& pos)const;
public:
	CellSpacePartition(double width, //width of the environment
		double height, //height ...
		int cellsX, //number of cells horizontally
		int cellsY, //number of cells vertically
		int MaxEntitys); //maximum number of entities to add
	//adds entities to the class by allocating them to the appropriate cell
	inline void AddEntity(const entity& ent);
	//update an entity's cell by calling this from your entity's Update method
	inline void UpdateEntity(const entity& ent, Vector2D OldPos);
	//this method calculates all a target's neighbors and stores them in
	//the neighbor vector. After you have called this method use the begin,
	//next, and end methods to iterate through the vector.
	inline void CalculateNeighbors(Vector2D TargetPos, double QueryRadius);
	//returns a reference to the entity at the front of the neighbor vector
	inline entity& begin();
	//this returns the next entity in the neighbor vector
	inline entity& next();
	//returns true if the end of the vector is found (a zero value marks the end)
	inline bool end();
	//empties the cells of entities
	void EmptyCells();
}