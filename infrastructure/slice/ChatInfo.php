<?php
// **********************************************************************
//
// Copyright (c) 2003-2010 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

// Ice version 3.4.0

// <auto-generated>
//
// Generated from file `ChatInfo.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>


if(!interface_exists('LbaNet_ChatRoomObserver'))
{
    interface LbaNet_ChatRoomObserver
    {
        public function Message($Sender, $data);
    }

    class LbaNet_ChatRoomObserverPrxHelper
    {
        public static function checkedCast($proxy, $facetOrCtx=null, $ctx=null)
        {
            return $proxy->ice_checkedCast('::LbaNet::ChatRoomObserver', $facetOrCtx, $ctx);
        }

        public static function uncheckedCast($proxy, $facet=null)
        {
            return $proxy->ice_uncheckedCast('::LbaNet::ChatRoomObserver', $facet);
        }
    }

    $LbaNet__t_ChatRoomObserver = IcePHP_defineClass('::LbaNet::ChatRoomObserver', 'LbaNet_ChatRoomObserver', true, $Ice__t_Object, null, null);

    $LbaNet__t_ChatRoomObserverPrx = IcePHP_defineProxy($LbaNet__t_ChatRoomObserver);

    IcePHP_defineOperation($LbaNet__t_ChatRoomObserver, 'Message', 0, 0, array($IcePHP__t_string, $IcePHP__t_string), null, null, null);
}

if(!interface_exists('LbaNet_ChatRoomParticipant'))
{
    interface LbaNet_ChatRoomParticipant
    {
        public function Say($Sender, $data);
    }

    class LbaNet_ChatRoomParticipantPrxHelper
    {
        public static function checkedCast($proxy, $facetOrCtx=null, $ctx=null)
        {
            return $proxy->ice_checkedCast('::LbaNet::ChatRoomParticipant', $facetOrCtx, $ctx);
        }

        public static function uncheckedCast($proxy, $facet=null)
        {
            return $proxy->ice_uncheckedCast('::LbaNet::ChatRoomParticipant', $facet);
        }
    }

    $LbaNet__t_ChatRoomParticipant = IcePHP_defineClass('::LbaNet::ChatRoomParticipant', 'LbaNet_ChatRoomParticipant', true, $Ice__t_Object, null, null);

    $LbaNet__t_ChatRoomParticipantPrx = IcePHP_defineProxy($LbaNet__t_ChatRoomParticipant);

    IcePHP_defineOperation($LbaNet__t_ChatRoomParticipant, 'Say', 0, 0, array($IcePHP__t_string, $IcePHP__t_string), null, null, null);
}
?>
