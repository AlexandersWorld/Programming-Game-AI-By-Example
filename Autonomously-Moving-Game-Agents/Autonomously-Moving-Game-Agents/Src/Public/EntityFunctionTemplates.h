#pragma once
#include "Vector2D.h"

class EntityFunctionTemplates
{
	
public:

	template<class T, class conT>
	void EnforceNonPenetrationConstraint(const T& entity, const conT& ContainerOfEntities)
	{
		//iterate through all entities checking for any overlap of bounding radii
		for (typename conT::const_iterator curEntity = ContainerOfEntities.begin(); curEntity != ContainerOfEntities.end(); ++curEntity)
		{
			if (*curEntity == entity)  continue;

			SVector2D ToEntity = entity->Pos() - (*curEntity)->Pos();

			double DistFromEachOther = ToEntity.Length();

			//if this distance is smaller than the sum of their radii then this
			//entity must be moved away in the direction parallel to the ToEntity vector
			double AmountOfOverlap = (*curEntity)->BRadius() + entity->BRadius() - DistFromEachOther;

			if (AmountOfOverlap >= 0)
			{
				//move the entity a distance away equivalenmt to the amount of overlap.
				entity->SetPos(entity->Pos() + (ToEntity / DistFromEachOther) * AmountOfOverlap);
			}
		}
	}
};