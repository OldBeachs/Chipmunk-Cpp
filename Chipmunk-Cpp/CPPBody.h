//
//  CPPBody.h
//  Chipmunk-Cpp
//
//  Created by Artyom Peshkov on 12.12.12.
//
//

#ifndef __Chipmunk_Cpp__CPPBody__
#define __Chipmunk_Cpp__CPPBody__

#include "chipmunk.h"

class CPPBody {
private:
    
    /// A unit length vector vector that stores the current rotation of the body as a 2D spinor or complex number. Can be used for fast rotation.
    cpVect _rot;
    
    /// Returns a pointer to the underlying cpBody C struct.
    cpBody _body;
    
    /// Get the kinetic energy of this body.
    cpFloat _kineticEnergy;
    
public:
    
    /// Mass of the rigid body. Mass does not have to be expressed in any particular units, but relative masses should be consistent.
    cpFloat mass;
    
    /// Moment of inertia of the body. The mass tells you how hard it is to push an object, the MoI tells you how hard it is to spin the object. Don't try to guess the MoI, use the cpMomentFor*() functions to try and estimate it.
    cpFloat moment;
    
    /// The position of the rigid body's center of gravity.
    cpVect pos;
    
    /// The linear velocity of the rigid body.
    cpVect vel;
    
    /// The linear force applied to the rigid body. Unlike in some physics engines, the force does not reset itself during each step. Make sure that you are reseting the force between frames if that is what you intended.
    cpVect force;
    
    /// The rotation angle of the rigid body in radians.
    cpFloat angle;
    
    /// The angular velocity of the rigid body in radians per second.
    cpFloat angVel;
    
    /// The torque being applied to the rigid body. Like force, this property is not reset every frame.
    cpFloat torque;
    
    /// An object that this constraint is associated with. You can use this get a reference to your game object or controller object from within callbacks.
    void *data;
    
    /// Maximum velocity allowed for this body. Defaults to @c INFINITY.
    cpFloat velLimit;
    
    /// Maximum angular velocity allowed for this body. Defaults to @c INFINITY.
    cpFloat angVelLimit;
    
    bool neverSleep;
    
    CPPBody();
    ~CPPBody();
    
    CPPBody(cpFloat mass, cpFloat moment);
    
    CPPBody* bodyFromCPBody(cpBody *body);
    
    cpVect getRot() {return _rot;}
    cpBody* getBody() {return &_body;}
    cpFloat getKineticEnergy() {return cpBodyKineticEnergy(&_body);}
    
    /**
     Convert from body local to world coordinates.
     Convert a point in world (absolute) coordinates to body local coordinates affected by the position and rotation of the rigid body.
     */
    cpVect local2world(cpVect v) {return cpBodyLocal2World(&_body, v);}
    
    /**
     Convert from world to body local Coordinates.
     Convert a point in body local coordinates coordinates to world (absolute) coordinates.
     */
    cpVect world2local(cpVect v) {return cpBodyWorld2Local(&_body, v);}
    
    /**
     Reset force and torque.
     Set the force on this rigid body to cpvzero, and set the torque to 0.0.
     */
    void resetForces() {cpBodyResetForces(&_body);}
    
    /**
     Apply a force to a rigid body. An offset of cpvzero is equivalent to adding directly to the force property.
     @param force A force in expressed in absolute (word) coordinates.
     @param offset An offset expressed in world coordinates. Note that it is still an offset, meaning that it's position is relative, but the rotation is not.
     */
    void applyForce(cpVect force, cpVect offset) {cpBodyApplyForce(&_body, force, offset);}
    
    /**
     Apply an impulse to a rigid body.
     @param impulse An impulse in expressed in absolute (word) coordinates.
     @param offset An offset expressed in world coordinates. Note that it is still an offset, meaning that it's position is relative, but the rotation is not.
     */
    void applyImpulse(cpVect j, cpVect offset) {cpBodyApplyImpulse(&_body, j, offset);}
    
    bool isSleeping() {return cpBodyIsSleeping(&_body);}
    bool isRogue() {return cpBodyIsRogue(&_body);}
    bool isStatic() {return cpBodyIsStatic(&_body);}
    
    /// Wake up the body if it's sleeping, or reset the idle timer if it's active.
    void activate() {cpBodyActivate(&_body);}
    
#warning add CPPShape
    /// Wake up any bodies touching a static body through shape @c filter Pass @c nil for @c filter to away all touching bodies.
    //    void activateStatic(CPPShape *filter) {cpBodyActivateStatic(&_body, filter.shape);}
    
    /**
     Force the body to sleep immediately. The body will be added to the same group as @c group. When any object in a group is woken up, all of the bodies are woken up with it.
     If @c group is nil, then a new group is created and the body is added to it. It is an error pass a non-sleeping body as @c group.
     This is useful if you want an object to be inactive until something hits it such as a pile of boxes you want the player to plow through or a stalactite hanging from a cave ceiling.
     Make sure the body is fully set up before you call this. Adding this body or any shapes or constraints attached to it to a space, or modifying any of their properties automatically wake a body up.
     */
    void sleepWithGroup(CPPBody *group) {cpBodySleepWithGroup(&_body, group->getBody());}
    void sleep() {cpBodySleep(&_body);}
    
    //    /// Get a list of shapes that are attached to this body and currently added to a space.
    //    cpArray* shapes();
    //
    //    /// Get a list of constraints that are attached to this body and currently added to a space.
    //    cpArray* constraints();
    
    //    /// Implements the ChipmunkBaseObject protocol, not particularly useful outside of the library code
    //    void addToSpace(ChipmunkSpace *space);
    //    /// Implements the ChipmunkBaseObject protocol, not particularly useful outside of the library code
    //    void removeFromSpace(ChipmunkSpace *space);
    
    
    // accessor macros
    #define getter(type, lower, upper) \
    type get##lower() {return cpBodyGet##upper(&_body);}
    
    #define setter(type, lower, upper) \
    void set##upper(type value) {cpBodySet##upper(&_body, value);}
    
    #define both(type, lower, upper) \
    getter(type, lower, upper) \
    setter(type, lower, upper)

    
    both(cpFloat, mass, Mass)
    both(cpFloat, moment, Moment)
    both(cpVect, pos, Pos)
    both(cpVect, vel, Vel)
    both(cpVect, force, Force)
    both(cpFloat, angle, Angle)
    both(cpFloat, angVel, AngVel)
    both(cpFloat, torque, Torque)
    getter(cpVect, rot, Rot)
    both(cpFloat, velLimit, VelLimit);
    both(cpFloat, angVelLimit, AngVelLimit);
};

#endif /* defined(__Chipmunk_Cpp__CPPBody__) */
