//
//  CCPShape.h
//  Chipmunk-Cpp
//
//  Created by Lyha on 12/12/12.
//
//

#ifndef __Chipmunk_Cpp__CCPShape__
#define __Chipmunk_Cpp__CCPShape__

#include <iostream>

#include "chipmunk.h"

class CPPNearestPointQueryInfo;
class CPPSegmentQueryInfo;
class CPPBody;

/// Abstract base class for collsion shape types.
class CPPShape {
private:
    void* _data;
    cpShape* _shape;
    cpBB _bb;
    
    
#warning add CCPBody property
    
public:
    
    CPPShape();
    ~CPPShape();
    
    /// Sensor shapes send collision callback messages, but don't create a collision response.
    bool sensor;
    
    /// How bouncy this shape is
    cpFloat elasticity;
    
    /// How much friction this shape has.
    cpFloat friction;
    
    /**
     The velocity of the shape's surface.
     This velocity is used in the collision response when calculating the friction only.
     */
    cpVect surfaceVel;
    
    /**
     An object reference used as a collision type identifier. This is used when defining collision handlers.
     @attention Like most @c delegate properties this is a weak reference and does not call @c retain.
     */
    void* collisionType;
    
    /**
     An object reference used as a collision group identifier. Shapes with the same group do not collide.
     @attention Like most @c delegate properties this is a weak reference and does not call @c retain.
     */
    void* group;
    
    /// A layer bitmask that defines which objects 
    cpLayers layers;
    
    static CPPShape* createShape(cpShape *shape);
    
    /**
     An object that this shape is associated with. You can use this get a reference to your game object or controller object from within callbacks.
     @attention Like most @c delegate properties this is a weak reference and does not call @c retain. This prevents reference cycles from occuring.
     */
    void* getData() { return _data; };
    void setData(void* data) { _data = data; };
    
    /// Returns a pointer to the underlying cpShape C struct.
    virtual cpShape* getShape();
    
    /// The axis-aligned bounding box for this shape.
    cpBB getBB() { return _bb; };
    
    /// Update and cache the axis-aligned bounding box for this shape.
    cpBB chacheBB();
    
    /// Check if a point in absolute coordinates lies within the shape.
    CPPNearestPointQueryInfo* nearestPointQuery(cpVect point);
    CPPSegmentQueryInfo* segmentQueryFrom(cpVect start, cpVect end);
};

class CPPNearestPointQueryInfo {
private:
    cpNearestPointQueryInfo _info;
public:
    CPPNearestPointQueryInfo();
    ~CPPNearestPointQueryInfo();
    
    
    CPPNearestPointQueryInfo(cpNearestPointQueryInfo *info);
    
    /// Returns a pointer to the underlying cpNearestPointQueryInfo C struct.
    cpNearestPointQueryInfo* getInfo() { return &_info; };
    
    /// The ChipmunkShape found.
    CPPShape* getShape();
    
    /// The distance between the point and the surface of the shape.
    /// Negative distances mean that the point is that depth inside the shape.
    cpFloat getDist();
    
    /// The closest point on the surface of the shape to the point.
    cpVect getPoint();
};

/// Holds collision information from segment queries. You should never need to create one.
class CPPSegmentQueryInfo {
    cpSegmentQueryInfo _info;
    cpVect _start, _end;
    CPPShape* _shape;
    cpFloat _t;
    cpVect _normal;
    cpVect _point;
    cpFloat dist;
public:
    CPPSegmentQueryInfo();
    ~CPPSegmentQueryInfo();
    CPPSegmentQueryInfo(cpSegmentQueryInfo *info, cpVect start, cpVect end);
    
    /// Returns a pointer to the underlying cpSegmentQueryInfo C struct.
    cpSegmentQueryInfo* getInfo() { return &_info; };
    
    /// The ChipmunkShape found.
    CPPShape* getShape();
    
    /// The percentage between the start and end points where the collision occurred.
    cpFloat getT();
    
    /// The normal of the collision with the shape.
    cpVect getNormal();
    
    /// The point of the collision in absolute (world) coordinates.
    cpVect getPoint();
    
    /// The distance from the start point where the collision occurred.
    cpFloat getDist();
    
    cpVect getStart();
    cpVect getEnd();
};

/// A perfect circle shape.

class CPPCircleShape : public CPPShape {
private:
    cpCircleShape _shape;
    cpFloat _radius;
    cpFloat _offset;
public:
    CPPCircleShape();
    ~CPPCircleShape();
    
    static CPPCircleShape* create(CPPBody *body, cpFloat radius, cpVect offset);
    
    CPPCircleShape(CPPBody *body, cpFloat radius, cpVect offset);
    
    cpFloat getRadius();
    cpVect
};

#endif /* defined(__Chipmunk_Cpp__CCPShape__) */
