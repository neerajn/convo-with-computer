/*
 * messagehandler.h
 *
 */

#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#include "services.h"
#include "command.h"

class MessageHandler
{
    public:
        MessageHandler ();
        ~MessageHandler ();

        int process (RequestHeader& header);
        bool processBody (char* buffer, int bodylength, char* returnBuffer);

    private:
        int m_currentType;

};

#endif /* MESSAGEHANDLER_H_ */
