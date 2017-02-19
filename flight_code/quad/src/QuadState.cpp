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

}

bool Quad::QuadState::abort(void) {
    return shutdown;
}

bool Quad::QuadState::canTx()
{
    return can_tx;
}

bool Quad::QuadState::received()
{
    return rx;
}

Quad::QuadState &Quad::QuadState::reference() {
    static Quad::QuadState ref;
    return ref;
}

void Quad::QuadState::set(Quad::State state) {
    states[state] = true;
}

void Quad::QuadState::unset(Quad::State state) {
    states[state] = false;
}

bool Quad::QuadState::getstate(Quad::State state) {
    return states[state];
}

