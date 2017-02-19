//
// Created by jesse on 2/14/17.
//

#include "QuadState.h"

extern "C" {
#include <avr/io.h>
#include <avr/interrupt.h>
}

Quad::QuadState::QuadState() :
    tenHzTimerExpired( false )
{

    states[Shutdown] = false;
    states[MainProcessesing] = false;
    states[ReceivedMsg] = false;
    states[CanTx] = false;
}

bool Quad::QuadState::abort(void) {
    return states[Shutdown];
}

bool Quad::QuadState::canTx()
{
    return states[CanTx];
}

bool Quad::QuadState::received()
{
    return states[ReceivedMsg];
}

Quad::QuadState &Quad::QuadState::reference() {
    static Quad::QuadState ref;
    return ref;
}

void Quad::QuadState::set( Quad::State state ) {
    states[state] = true;
}

void Quad::QuadState::unset( Quad::State state ) {
    states[state] = false;
}

bool Quad::QuadState::getstate( Quad::State state ) {
    return states[state];
}
