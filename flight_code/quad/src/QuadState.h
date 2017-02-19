//
// Created by jesse on 2/14/17.
//

#ifndef COMMS_QUADMGR_H
#define COMMS_QUADMGR_H

namespace Quad {

    enum Status {
        SUCESS
    };

    enum State {
        MainProcessesing,
        ReceivedMsg,
        CanTx,
        NumStates
    };

    class QuadState {
        public:
            static QuadState& reference();
            bool abort(void);
            //bool tenHzProcessing();
            bool canTx();
            bool received();
            void set(State);
            void unset(State);
            bool getstate(State);

        private:
            QuadState();
            bool tenHzTimerExpired;
            bool shutdown;
            bool can_tx;
            bool rx;
            bool states[NumStates];
    };

}

#endif //COMMS_QUADMGR_H
