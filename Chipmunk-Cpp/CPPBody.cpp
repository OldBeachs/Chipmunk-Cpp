//
//  CPPBody.cpp
//  Chipmunk-Cpp
//
//  Created by Artyom Peshkov on 12.12.12.
//
//

#include "CPPBody.h"

CPPBody::CPPBody()
{
    cpBodyInitStatic(&_body);
    _body.data = this;
}


CPPBody::CPPBody(cpFloat mass, cpFloat moment)
{
    cpBodyInit(&_body, mass, moment);
    _body.data = this;
}


CPPBody* bodyFromCPBody(cpBody *body)
{
    CPPBody *obj = (CPPBody *)body->data;
    return obj;
}


CPPBody::~CPPBody()
{
    cpBodyDestroy(&_body);
}
