#pragma once

#include <vector>
#include <string>
#include <iosfwd>


struct Vector2D
{
	float x,y;
};

class BaseGameEntity
{
public:
	

	enum { default_entity_type = -1 };

private:

	static int  m_iNextValidID;

	int         m_ID;

	int         m_iType;

	bool        m_bTag;

	Vector2D    m_vPos;

	double      m_dScale;

	double      m_dBoundingRadius;

	void SetID(int val);
	
	
protected:
	virtual void Update(time_elapse) = 0;
	virtual void Render() = 0;

public:
	BaseGameEntity(const int id)
	{
		SetID(id);
	}
	
	virtual ~BaseGameEntity() = default;

	// entities should be able to read/write data
	virtual void  Write(std::ostream& os)const {}
	virtual void  Read(std::ifstream& is) {}

	Vector2D      Pos()const { return m_vPos; }
	void          SetPos(Vector2D new_pos) { m_vPos = new_pos; }

	double        BRadius()const { return m_dBoundingRadius; }
	void          SetBRadius(double r) { m_dBoundingRadius = r; }

	int           ID()const { return m_ID; }

	bool          IsTagged()const { return m_bTag; }
	void          Tag() { m_bTag = true; }
	void          UnTag() { m_bTag = false; }

	int           EntityType()const { return m_iType; }
	void          SetEntityType(int new_type) { m_iType = new_type; }

	double        Scale()const { return m_dScale; }
	void          SetScale(double val) { m_dScale = val; }

	template<class T, class conT>
	void TagNeighbors(const T* entity, conT& ContainerOfEntities, double radius)
	{
		//iterate through all entities checking for range
		for (typename conT::interator curEntity = ContainerOfEntities.begin(); curEntity != ContainerOfEntities.end(); ++curEntity)
		{
			//first clear any current tag
			(*curEntity)->UnTag();

			SVector2D to = (*curEntity)->Pos() - entity->Pos();

			//the bounding radius of the other is taken into account by adding it
			//to the range
			double range = radius + (*curEntity)->BRadius();

			//if entity within range, tag for further consideration. (working in distance-squared space to avoid sqrts)
			if (((*curEntity) != entity) && (to.LengthSquared < range * range))
			{
				(*curEntity)->Tag();
			}
		}
	}
};

#endif
