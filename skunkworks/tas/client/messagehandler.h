/**
 * messagehandler.h
 * The client side message handler
 */

#ifndef MESSAGEHANDLER_H_
#define MESSAGEHANDLER_H_

#include "services.h"
#include "messaging.h"

class MessageHandler
{
    public:
        MessageHandler ();
        ~MessageHandler ();

        int process (ResponseHeader& header);
        bool processResponse (char* buffer, int bodylength);

    private:
        int m_currentType;

};

#endif /* MESSAGEHANDLER_H_ */
