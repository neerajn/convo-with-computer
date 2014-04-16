/**
 * All messages are parsed and handled here.
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
        void process (char* buffer, int bodylength, char* returnBuffer, uint16_t& returnBufferSize);

    private:
        int m_currentType;

};

#endif /* MESSAGEHANDLER_H_ */
