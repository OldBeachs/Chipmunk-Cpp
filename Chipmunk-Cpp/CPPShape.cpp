//
//  CCPShape.cpp
//  Chipmunk-Cpp
//
//  Created by Lyha on 12/12/12.
//
//

#include "CPPShape.h"

// Shape base class --------------------------------

static CPPShape* createShape(cpShape *shape)
{
    CPPShape *obj = (CPPShape *)shape->data;
    cpAssertHard(dynamic_cast<CPPShape*>(obj), "'shape->data' is not a pointer to a ChipmunkShape object.");

    return obj;
}

CPPShape::CPPShape()
{
    
}

CPPShape::~CPPShape()
{
    cpShapeDestroy(_shape);
}

#warning make getter and Setter for CPPBody


// NearestPointQueryInfo ---------------------------

CPPNearestPointQueryInfo::CPPNearestPointQueryInfo()
{

}

CPPNearestPointQueryInfo::~CPPNearestPointQueryInfo()
{
    
}

CPPNearestPointQueryInfo::CPPNearestPointQueryInfo(cpNearestPointQueryInfo *info)
{
    _info = (*info);
}

CPPShape* CPPNearestPointQueryInfo::getShape()
{
    return _info.shape ? (CPPShape *)_info.shape->data : NULL;
}

cpFloat CPPNearestPointQueryInfo::getDist()
{
    return _info.d;
}

cpVect CPPNearestPointQueryInfo::getPoint()
{
    return _info.p;
}


// SegmentQueryInfo ------------------------------

CPPSegmentQueryInfo::CPPSegmentQueryInfo()
{
    
}

CPPSegmentQueryInfo::~CPPSegmentQueryInfo()
{
    
}

CPPSegmentQueryInfo::CPPSegmentQueryInfo(cpSegmentQueryInfo *info, cpVect start, cpVect end)
{
    _info = (*info);
    _start = start;
    _end = end;
}

CPPShape* CPPSegmentQueryInfo::getShape()
{
    return _info.shape ? (CPPShape *)_info.shape->data : NULL;
}

cpFloat CPPSegmentQueryInfo::getT()
{
    return _info.t;
}

cpVect CPPSegmentQueryInfo::getNormal()
{
    return _info.n;
}

cpVect CPPSegmentQueryInfo::getPoint()
{
    return cpSegmentQueryHitPoint(_start, _end, _info);
}

cpFloat CPPSegmentQueryInfo::getDist()
{
    return cpSegmentQueryHitDist(_start, _end, _info);
}

cpVect CPPSegmentQueryInfo::getStart()
{
    return _start;
}

cpVect CPPSegmentQueryInfo::getEnd()
{
    return _end;
}

