/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

#include <boost/bind.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/signals2.hpp>

#include <Swiften/Elements/MUCOccupant.h>
#include <Swiften/Elements/StatusShow.h>
#include <Swiften/Elements/VCard.h>
#include <Swiften/JID/JID.h>

#include <Swift/Controllers/Roster/RosterItem.h>

namespace Swift {

class GroupRosterItem;
class Presence;

class ContactRosterItem : public RosterItem {
    public:
        enum Feature {
            FileTransferFeature,
            WhiteboardFeature
        };

        enum BlockState {
            BlockingNotSupported,
            IsBlocked,
            IsUnblocked,
            IsDomainBlocked
        };

    public:
        ContactRosterItem(const JID& jid, const JID& displayJID, const std::string& name, GroupRosterItem* parent);
        virtual ~ContactRosterItem();

        StatusShow::Type getStatusShow() const;
        StatusShow::Type getSimplifiedStatusShow() const;
        std::string getStatusText() const;
        std::string getIdleText() const;
        boost::posix_time::ptime getIdle() const;
        std::string getOfflineSinceText() const;
        boost::posix_time::ptime getOfflineSince() const;
        void setAvatarPath(const boost::filesystem::path& path);
        const boost::filesystem::path& getAvatarPath() const;
        const JID& getJID() const;
        void setDisplayJID(const JID& jid);
        const JID& getDisplayJID() const;
        void applyPresence(std::shared_ptr<Presence> presence);
        const std::vector<std::string>& getGroups() const;
        /** Only used so a contact can know about the groups it's in*/
        void addGroup(const std::string& group);
        void removeGroup(const std::string& group);
        void clearPresence();

        MUCOccupant::Role getMUCRole() const;
        void setMUCRole(const MUCOccupant::Role& role);
        MUCOccupant::Affiliation getMUCAffiliation() const;
        void setMUCAffiliation(const MUCOccupant::Affiliation& affiliation);
        std::string getMUCAffiliationText() const;

        void setSupportedFeatures(const std::set<Feature>& features);
        bool supportsFeature(Feature feature) const;

        void setBlockState(BlockState state);
        BlockState blockState() const;

        VCard::ref getVCard() const;
        void setVCard(VCard::ref vcard);

        boost::signals2::signal<void ()> onVCardRequested;

    private:
        JID jid_;
        JID displayJID_;
        boost::filesystem::path avatarPath_;
        std::shared_ptr<Presence> presence_;
        std::vector<std::string> groups_;
        MUCOccupant::Role mucRole_;
        MUCOccupant::Affiliation mucAffiliation_;
        std::set<Feature> features_;
        BlockState blockState_;
        VCard::ref vcard_;
};

}

