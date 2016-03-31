/*
 * Copyright (c) 2013-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <string>

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Base/Override.h>
#include <Swiften/Elements/Payload.h>
#include <Swiften/Elements/PubSubEventAssociate.h>
#include <Swiften/Elements/PubSubEventDisassociate.h>
#include <Swiften/Elements/PubSubEventPayload.h>

namespace Swift {
    class SWIFTEN_API PubSubEventCollection : public PubSubEventPayload {
        public:

            PubSubEventCollection();

            virtual ~PubSubEventCollection();

            const boost::optional< std::string >& getNode() const {
                return node;
            }

            void setNode(const boost::optional< std::string >& value) {
                this->node = value ;
            }

            boost::shared_ptr<PubSubEventDisassociate> getDisassociate() const {
                return disassociate;
            }

            void setDisassociate(boost::shared_ptr<PubSubEventDisassociate> value) {
                this->disassociate = value ;
            }

            boost::shared_ptr<PubSubEventAssociate> getAssociate() const {
                return associate;
            }

            void setAssociate(boost::shared_ptr<PubSubEventAssociate> value) {
                this->associate = value ;
            }


        private:
            boost::optional< std::string > node;
            boost::shared_ptr<PubSubEventDisassociate> disassociate;
            boost::shared_ptr<PubSubEventAssociate> associate;
    };
}
